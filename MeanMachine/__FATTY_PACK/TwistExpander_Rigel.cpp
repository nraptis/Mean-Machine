#include "TwistExpander_Rigel.hpp"
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

TwistExpander_Rigel::TwistExpander_Rigel()
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

void TwistExpander_Rigel::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xFD69954ECF222A56ULL; std::uint64_t aIngress = 0xB50ED1F6DCBCCE0DULL; std::uint64_t aCarry = 0xD5C4893348287000ULL;

    std::uint64_t aWandererA = 0xAF1DC35D763D53CAULL; std::uint64_t aWandererB = 0x9BC23D8E84F8E295ULL; std::uint64_t aWandererC = 0x8F22035797C1246EULL; std::uint64_t aWandererD = 0xD8B6CDF82CB52271ULL;
    std::uint64_t aWandererE = 0xB7B1A0314795D66CULL; std::uint64_t aWandererF = 0x8901EB147C773344ULL; std::uint64_t aWandererG = 0xD0661125648D63D7ULL; std::uint64_t aWandererH = 0xD31A970F9ABE54B3ULL;
    std::uint64_t aWandererI = 0xF1D52B55FF0B35A4ULL; std::uint64_t aWandererJ = 0xEA9FEA434FF5160DULL; std::uint64_t aWandererK = 0xBA44517C3940D233ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 11811448168971764341U;
        aCarry = 10539892621804332303U;
        aWandererA = 15893927102444023344U;
        aWandererB = 17730048501017059547U;
        aWandererC = 18104011214839257159U;
        aWandererD = 11814868254396152551U;
        aWandererE = 11387129818118454957U;
        aWandererF = 11489376646007735700U;
        aWandererG = 14663225980204718883U;
        aWandererH = 15417700643344367150U;
        aWandererI = 12075675687819003010U;
        aWandererJ = 10996949066407360790U;
        aWandererK = 17089717131732245387U;
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
    TwistExpander_Rigel_Arx::KDF_A_A(pWorkSpace,
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
    TwistExpander_Rigel_Arx::KDF_A_B(pWorkSpace,
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
    TwistExpander_Rigel_Arx::KDF_A_C(pWorkSpace,
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
    TwistExpander_Rigel_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Rigel_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Rigel::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xEC7D8BE4D04F39BFULL; std::uint64_t aIngress = 0xCCBCBBED127CD9DDULL; std::uint64_t aCarry = 0xD654A94B2874D767ULL;

    std::uint64_t aWandererA = 0x9DFC2F8B82C201F5ULL; std::uint64_t aWandererB = 0xD5DF8DD7B82F58A3ULL; std::uint64_t aWandererC = 0x8B673249EDAAD19AULL; std::uint64_t aWandererD = 0xAD7A8B598F7F3ACBULL;
    std::uint64_t aWandererE = 0xA87FEF94F8E32229ULL; std::uint64_t aWandererF = 0x9A26E5DF8C7329F4ULL; std::uint64_t aWandererG = 0x9064E720B9CEA1C8ULL; std::uint64_t aWandererH = 0x9834EF9522BB819BULL;
    std::uint64_t aWandererI = 0xF1B823EE066605ABULL; std::uint64_t aWandererJ = 0x97E758963194B982ULL; std::uint64_t aWandererK = 0x8120ADA932137E7EULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 17644998933478604740U;
        aCarry = 9991502517285888822U;
        aWandererA = 12649968258805997071U;
        aWandererB = 14805546189729527235U;
        aWandererC = 12791182065962640590U;
        aWandererD = 9487351467494823044U;
        aWandererE = 10940301713957223396U;
        aWandererF = 12068062906168849833U;
        aWandererG = 13863648596828951126U;
        aWandererH = 18270509544823462563U;
        aWandererI = 17102245357274080383U;
        aWandererJ = 10706307624985088530U;
        aWandererK = 16475074951678005321U;
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
    TwistExpander_Rigel_Arx::KDF_B_A(pWorkSpace,
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
    TwistExpander_Rigel_Arx::KDF_B_B(pWorkSpace,
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
    TwistExpander_Rigel_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Rigel_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Rigel::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xD4A4E16D9B878553ULL;
    std::uint64_t aIngress = 0x94334B470CDAF17CULL;
    std::uint64_t aCarry = 0xE8C74B0E71BFDFDCULL;

    std::uint64_t aWandererA = 0x9C304E9B09B88E62ULL;
    std::uint64_t aWandererB = 0xB023D992405D711BULL;
    std::uint64_t aWandererC = 0xE8F4D2E97F5D3F67ULL;
    std::uint64_t aWandererD = 0xE00F9C567FEC3E32ULL;
    std::uint64_t aWandererE = 0xEB6DC48304613ECBULL;
    std::uint64_t aWandererF = 0xBE7713D134E34225ULL;
    std::uint64_t aWandererG = 0xBCBC0871BA608AA2ULL;
    std::uint64_t aWandererH = 0x84061B3A0E3B737AULL;
    std::uint64_t aWandererI = 0x935B1D1F6E997B0BULL;
    std::uint64_t aWandererJ = 0x99FA570257EFB9BAULL;
    std::uint64_t aWandererK = 0xDAC1402D54CE6957ULL;

    // [seed]
        TwistSnow::Sha256Counter(aSource, aSnowLaneA);
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneB);
        TwistSnow::AES256Counter(aSource, aSnowLaneC);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneH);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneA);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneD);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneF);
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
    TwistExpander_Rigel_Arx::Seed_A(pWorkSpace,
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
    TwistExpander_Rigel_Arx::Seed_B(pWorkSpace,
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
    TwistExpander_Rigel_Arx::Seed_C(pWorkSpace,
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
    TwistExpander_Rigel_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Rigel_Arx::Seed_E(pWorkSpace,
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
    TwistExpander_Rigel_Arx::Seed_F(pWorkSpace,
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
    TwistExpander_Rigel_Arx::Seed_G(pWorkSpace,
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
    TwistExpander_Rigel_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Rigel_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Rigel_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Rigel_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 29 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1791 / 1984 (90.27%)
// Total distance from earlier candidates: 50974
void TwistExpander_Rigel::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1374U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1478U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 226U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 547U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1839U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1534U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1824U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 63U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 118U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 806U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 672U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 216U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 316U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1015U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 812U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1472U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 960U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 13U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 790U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 994U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 47U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 272U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 39U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1659U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1548U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1592U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 497U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 953U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 534U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 595U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 434U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1587U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1139U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 477U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1767U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 37U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 940U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1006U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 221U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1984U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1253U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1035U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1378U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1315U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 315U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 499U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1336U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 546U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 690U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1732U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1719U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 770U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 200U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 203U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 255U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 492U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 0U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 217U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1300U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1213U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1981U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 199U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 456U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 376U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1215U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1693U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 310U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1241U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 565U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1384U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1658U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1939U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 977U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1740U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1055U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 379U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 414U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 30U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 906U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1861U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1688U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1373U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1186U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1053U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1751U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 679U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1500U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 463U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1607U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1264U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 894U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1596U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 642U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1736U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1298U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1034U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 144U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 508U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 907U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1342U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 284U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 389U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1048U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1608U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 275U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 2026U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 580U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1741U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1820U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 75U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 113U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 638U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 397U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1613U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1089U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1114U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1638U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 542U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 911U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 789U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1411U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1851U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1346U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 331U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1070U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1102U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 119U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 693U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }
}

void TwistExpander_Rigel::TwistBlock(TwistWorkSpace *pWorkSpace,
                                       std::uint8_t *pSource,
                                       std::uint8_t *pDestination) {
    TwistExpander::TwistBlock(pWorkSpace, pSource, pDestination);
    if ((pWorkSpace == nullptr) || (pDestination == nullptr)) { return; }
    std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    std::uint64_t aPrevious = 0xAE6BF64603356894ULL; std::uint64_t aIngress = 0xDE54DC0D546C042CULL; std::uint64_t aCarry = 0xFB11E638B98E4B99ULL;

    std::uint64_t aWandererA = 0x8D7EC8A24C71EBCCULL; std::uint64_t aWandererB = 0xA4A711B20200A43FULL; std::uint64_t aWandererC = 0x8BCEC9BACB643B77ULL; std::uint64_t aWandererD = 0xC46520E69D5FD9C7ULL;
    std::uint64_t aWandererE = 0xADBA60C155972A4EULL; std::uint64_t aWandererF = 0xB7CE064DEE800CE6ULL; std::uint64_t aWandererG = 0xE4A9525C0C91EF3AULL; std::uint64_t aWandererH = 0xD6BA340920142194ULL;
    std::uint64_t aWandererI = 0xF118E7E6BCD34A1FULL; std::uint64_t aWandererJ = 0xFEBE6E7E4AFF597FULL; std::uint64_t aWandererK = 0xF05961A1AE86F219ULL;

    // [seed]
        aPrevious = 9666542023407982009U;
        aCarry = 15277948339050076161U;
        aWandererA = 14018629054391346059U;
        aWandererB = 17756841639766696540U;
        aWandererC = 16948369579685664810U;
        aWandererD = 17474637731208029159U;
        aWandererE = 12560528694593754302U;
        aWandererF = 14385518795471138008U;
        aWandererG = 13204312029645310821U;
        aWandererH = 15630333508935843403U;
        aWandererI = 17199610300176977594U;
        aWandererJ = 13363884494241605730U;
        aWandererK = 16002811729048912191U;
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
    TwistExpander_Rigel_Arx::Twist_A(pWorkSpace,
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
    TwistExpander_Rigel_Arx::Twist_B(pWorkSpace,
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
    TwistExpander_Rigel_Arx::Twist_C(pWorkSpace,
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
    TwistExpander_Rigel_Arx::Twist_D(pWorkSpace,
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
    TwistExpander_Rigel_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Rigel_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Rigel_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 29 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 15130; nearest pair: 477 / 674
void TwistExpander_Rigel::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2650U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6540U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1734U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4001U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 395U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1371U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3948U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6680U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4991U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4497U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4920U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6290U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2462U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2574U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 500U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 8063U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 216U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 211U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1915U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 407U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1202U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1054U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 473U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 325U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1051U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 829U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1667U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1416U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 497U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1489U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1767U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 657U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1796U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 980U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 327U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1800U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 29 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 15145; nearest pair: 485 / 674
void TwistExpander_Rigel::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1189U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2044U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3010U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5688U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5765U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6132U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6103U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7446U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 577U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7253U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6616U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4135U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7598U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5239U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 891U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3861U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1677U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 362U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 327U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1682U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1322U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2001U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1171U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 932U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1162U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1204U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2029U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 717U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1696U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 148U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 40U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 580U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1891U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 201U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1286U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1606U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Rigel::kPhaseASalts = {
    {
        {
            0xB0FC858A9D81541AULL, 0x765A3CB4A9F950AEULL, 0x185C51FE0648D3A3ULL, 0x70313C3E459F08BFULL, 
            0xEBBAF263DF8F4BC2ULL, 0xE6EF0780FB1B426CULL, 0x5DD0AA19FACDC05EULL, 0x3C4039C77DA35EF6ULL, 
            0x3010F00498B01CA1ULL, 0x8FE79FE2C621E8E8ULL, 0x0F1DB418DE6C2830ULL, 0x3A58C5295B640CEEULL, 
            0x10DA115AEC558317ULL, 0x80105F37C85A7A43ULL, 0x2F5D6053E9487917ULL, 0x78A4EB0443E18F4BULL, 
            0x3EC47300849455EEULL, 0xBFC265F28CE8A4B5ULL, 0xE8070B0548F48372ULL, 0x341C285293B2DD47ULL, 
            0x70A7FFDDAD550B41ULL, 0x35A8C02FC91C8881ULL, 0xD6824A40575D280BULL, 0x5FDA8813476AB79DULL, 
            0xA9B5BE07BC5BA696ULL, 0xAF60EC484CF95AA6ULL, 0x436C560C08CEF030ULL, 0x32AC45DB73B87851ULL, 
            0xFFE1F356E2D75FFFULL, 0x7C2D151E42F56C6BULL, 0x99180B0B3EF1B639ULL, 0xB4637878C17C42D2ULL
        },
        {
            0x93EC23771A601375ULL, 0xF0B931FC42BAAF68ULL, 0xB65B45A3BF2289DEULL, 0x160E991B07CD03B8ULL, 
            0xAA4D660BFF46CE34ULL, 0xBF2D939B86676919ULL, 0x84D5F8A73D9DAF00ULL, 0x87367589E37FE75AULL, 
            0xC869623999746A4BULL, 0x893E48C8C65DBE20ULL, 0x8E6AEFD865823DC8ULL, 0x578415F33389C3D1ULL, 
            0x479B452FC5454167ULL, 0x11F7D7E1A9043362ULL, 0x97814B89F52DBEB6ULL, 0x289122AA0B2A4C17ULL, 
            0x592FF2EBD93BAE98ULL, 0xF0A0BFB28ADE2530ULL, 0x63ABCEC12C13BAB6ULL, 0xDDADAE444B7170D4ULL, 
            0x380819A69875E36CULL, 0xB1B4836A72CA80EAULL, 0x296CC928F2A7D4B0ULL, 0x59E0BD4F5862A8DFULL, 
            0xD63D15B2D205822BULL, 0xB3BE9306120781DAULL, 0x96FDB69B664E283AULL, 0x67123A516F882330ULL, 
            0xBF02301C2CD32837ULL, 0x08C762471673CB0FULL, 0x2DC6D83D2C132BBEULL, 0xE1DA1FD6C83C2C6AULL
        },
        {
            0xE6F070EB227BBA41ULL, 0x5110E55EA1D22818ULL, 0xD3E804A8E521F8D4ULL, 0x6371BDDAACEC76C2ULL, 
            0x71C2360CC4ED7D09ULL, 0x337AB7C04DD9364DULL, 0x8EED943D40DB2686ULL, 0xD80088657DFE9A02ULL, 
            0x12A9F315121ADE24ULL, 0xC35765A495FE8758ULL, 0xAF4C3AEE77F0EE7DULL, 0x2315C3465441DBF1ULL, 
            0x55062E4787D17120ULL, 0xE6EA9D0C9FF2DA72ULL, 0x1B28355A6FFC4859ULL, 0x1A5B4517F6DBB5F0ULL, 
            0x1E3FDD40613F061BULL, 0x5BDD2FE58CFD0476ULL, 0xC3F774EE55295CC7ULL, 0x9AC2814691627FF2ULL, 
            0x30D58B1B4B379458ULL, 0x56B8F612763D44D9ULL, 0x1B1C89E7508E4E49ULL, 0x7608AB6730E7AEF6ULL, 
            0x15075B19F6C3EAC4ULL, 0x28B8496EB91823B4ULL, 0x5C7B8FE6D5AC7BA9ULL, 0x92E128F8E31663A7ULL, 
            0x310C957F7E82F7CAULL, 0x5D8A2D7C341BE97DULL, 0xF948EBB9DB5663CEULL, 0xB2CA4375F7146039ULL
        },
        {
            0xBDF0A722DF985748ULL, 0xAC1682BD1B74790FULL, 0x8AEBAF706DDD8F21ULL, 0x1B76C558C1716E48ULL, 
            0x5A1F1F2B021DA3A9ULL, 0x2B671B7D3C496CF2ULL, 0x1D44E6AF524E0F40ULL, 0x8BE900693AF0A8E6ULL, 
            0x64DFEBD376E808C8ULL, 0xCCF602594A87DB3AULL, 0x485CA301EA5231ECULL, 0x76ECC37018C53A4DULL, 
            0x15C03F8011150554ULL, 0xCB5BA75E0C298433ULL, 0x2748AEA13FD11421ULL, 0x01217E7A07F7183CULL, 
            0xC148EE9F274DE2D3ULL, 0x83D93A96D37F99C8ULL, 0xA29AE29E13A8E83AULL, 0x5E9FEC654C6ECBEBULL, 
            0x8E268E6D71DA3F70ULL, 0x593D5DD8C36EBE64ULL, 0xCC13B7FEB21A2839ULL, 0xAA2ED269BAE7AE7BULL, 
            0x4BC546E01DB397ABULL, 0xBECAFDD832118D4EULL, 0xBAA0641DB530DAE1ULL, 0x39DFF4246F5B51F6ULL, 
            0x2F38FA741606EA42ULL, 0xF3FEB9250524721AULL, 0x2B52E916B913756EULL, 0x7E9BD93188EF71CEULL
        },
        {
            0x62D0B4F5FD780B67ULL, 0x0844F768237E7479ULL, 0xDC4C23712663834DULL, 0x5FB8CDED631DDDBAULL, 
            0x2122FCFAD4BD16D3ULL, 0x3F230A64D83B1C5CULL, 0x621FAE27E4110917ULL, 0x9357BB687C96F155ULL, 
            0xBE122351F0708FD8ULL, 0x16F0A59E19A0A560ULL, 0x25492B9BDD8E84D2ULL, 0x5595A2821970CDB7ULL, 
            0xCA2BD571E82F6307ULL, 0x3D7E958C5B2D5FF0ULL, 0x70EE9509D72E0203ULL, 0x116916FA919ADA2FULL, 
            0xBBE7B8B933052034ULL, 0xBA4114DC04358CFEULL, 0xA2B90737C19387ECULL, 0xA03F7DB9960BE3E8ULL, 
            0xABA1CA6A139547FEULL, 0xCDE72DA2BD7B38C3ULL, 0x524405C7D022D8F3ULL, 0x25DD9289497E40CEULL, 
            0x36193C6ACAD8965AULL, 0x7F25028530E66E7AULL, 0x1BBF0C27239D6469ULL, 0xEB66950A55B3AF8AULL, 
            0xA70FF89A4DBAC62CULL, 0x7CDEE99BFD926208ULL, 0x02EB73C04143E943ULL, 0x08EC659093C4A3C3ULL
        },
        {
            0x13A83861AFCB0F8EULL, 0xBEB3DBFF7DB41B67ULL, 0x73DFD974223D4A31ULL, 0x74869D10DBDFC875ULL, 
            0xDB06938B8D684B5DULL, 0xFF3B40A2A9266424ULL, 0x4F802FD7B5E2D67DULL, 0x698DB946D86C9A8EULL, 
            0xB6CEFD8079B3F09EULL, 0x44B63E3DBC29EF98ULL, 0xB2B87B9BE38A5E66ULL, 0x0883ACCADD7AB8F6ULL, 
            0xD1F22D6991CBEB58ULL, 0xDC0803C43268B66CULL, 0xF51461072CEFAB1FULL, 0x750C5752B1496F83ULL, 
            0x535DA1D36ACDB7CDULL, 0xB086B555EC48BED0ULL, 0x3C264792CF611155ULL, 0xBF104B6EA9B90225ULL, 
            0x9517FE3D39D59080ULL, 0x1629527972AE2B2FULL, 0x0D8B0536000A521CULL, 0x9E9534ED84E9779CULL, 
            0x0EF76E9E61671BF9ULL, 0x7C036D81467964D3ULL, 0x7C95A76E8495939DULL, 0xEB144218CFBBE0A0ULL, 
            0x1F2FE1F1C7AD4704ULL, 0x8CCB2E3DAA1930CBULL, 0x7C6520DF48CCDE8CULL, 0xBD2E878B6D259DAEULL
        }
    },
    {
        {
            0x67748DD7EFFF9A14ULL, 0xB08A8BF958BE1174ULL, 0x962B7FE22D110425ULL, 0xE6BDF4E74B6B9AE5ULL, 
            0xBC4D152424E4E123ULL, 0xB651146519620A65ULL, 0x903444F10201E3D5ULL, 0x5677EB91E2C46899ULL, 
            0x74FCC7472E505303ULL, 0x88AC676EC0E20872ULL, 0xB8C749DC1295F85EULL, 0xD3C771B168DCD779ULL, 
            0x282E549C3FC21284ULL, 0xE8CC8E90C33A553AULL, 0x1F0B67072ED57AFFULL, 0xB87F569B9FC68F4DULL, 
            0x82DBEDE11B94F5EEULL, 0xD38445048445625BULL, 0xB978483F6E864EB9ULL, 0xB7CBE4D523A41668ULL, 
            0xF472446293BA5A29ULL, 0xAD5855135EF8362CULL, 0xC2687F6B5291BD7CULL, 0x1A65CFEB40EDD746ULL, 
            0xDA8B7E641763EB38ULL, 0x1EBDA4F98B30AA4CULL, 0xB182EA3FFBD25BB6ULL, 0xC5A1B1B24EF98FC4ULL, 
            0x74F85752D0E87751ULL, 0x1347C215AC87AA3CULL, 0x4AD93F86121693FAULL, 0x4089FB71EA434A10ULL
        },
        {
            0x91D6804D4B8D5296ULL, 0xD43D41F17D15D5F1ULL, 0xDF9F823B90AF8E0CULL, 0x390AA1E424F0BEE9ULL, 
            0xDE676FFA8B13771DULL, 0x1E7A06ACAEFE59B9ULL, 0xC273098299226144ULL, 0x8E77C904A8E4C93CULL, 
            0x8B748668FBB5DF20ULL, 0x1253341B119322CDULL, 0x000523D1669927EFULL, 0x676081EAECC474F8ULL, 
            0x4B98A2AA3FA4A32CULL, 0x55DBC22835F47577ULL, 0x9ED0DF5634AC78ADULL, 0x1C812C1F31599F43ULL, 
            0x9C422BACEAB96E34ULL, 0xA0928E2325711870ULL, 0xD9A6B905533E9508ULL, 0xEBB6526EBE0531FAULL, 
            0x8A27EAF54D00D3ABULL, 0x4CD21D71CE191EADULL, 0x2E7A8ACA38BBFDE3ULL, 0xA9E05E3FA51AAC35ULL, 
            0xB8BB3D1F64F96EC9ULL, 0xE09EF33D4A8BEC81ULL, 0xD7B692276B7A18B8ULL, 0xAF20447FB2276A25ULL, 
            0xF5473FFA91A5AB4EULL, 0x2D13A49A7BE47D7DULL, 0xB0974DC42E7AFE48ULL, 0x53B77698EECA7C0DULL
        },
        {
            0xCD7C101ACF752619ULL, 0x662B4304B75B2B8DULL, 0x835BF8214DEF3FF2ULL, 0xCA70B4F9777E45F9ULL, 
            0x4CAB09AC4A659F0EULL, 0x928E4AFD5356A175ULL, 0xA3C93749C9284E35ULL, 0xEBE092F088992916ULL, 
            0x31B294E1184F3414ULL, 0x8D13B5FB82E294E4ULL, 0xE32868970BFD703FULL, 0xD2886E88ABE7D0BFULL, 
            0x018970C5D7480F6CULL, 0x901399D67E19F5CCULL, 0xA63EDEB72308788DULL, 0x7AA8B8DF7E6FECF4ULL, 
            0x3F3B57CEB047E9FCULL, 0x1544BF6320CD959DULL, 0x0B0E9345AA3C0C66ULL, 0x5A497BEE4C9E9C62ULL, 
            0x7E1EC8C46680D6A1ULL, 0x03B4779DBF8C1745ULL, 0xD2C845F4F19902D4ULL, 0xEC4CD87CAF61D1E0ULL, 
            0x635D32845ED39609ULL, 0x1FE3F9483B2B09B0ULL, 0x98FE52022F6DFEA9ULL, 0x2A64BB87AD228CE8ULL, 
            0x3DE13C31725240D1ULL, 0x3D3C5D3E85DB974CULL, 0x232457DFF1D24F07ULL, 0xB1A0DE0A1A891AA1ULL
        },
        {
            0x1563ACA571C9C40AULL, 0x75E6DF72D4ABB853ULL, 0xAE38806E5FA5A3A7ULL, 0xC370F9A9A9CB1AF6ULL, 
            0x9C2C1E19A9C2A6DAULL, 0xFCD4485C1F15C95BULL, 0x3B5325E7A6B4800EULL, 0x765E0487EE90423CULL, 
            0xFFED376FFE01CD70ULL, 0x9180D470D1F070C1ULL, 0x224D410FA137490DULL, 0x03026AE68E46078BULL, 
            0x8223C8542A494AD2ULL, 0xB27495C9CE3ADE6EULL, 0x63A29390A4BC88D7ULL, 0xCEE04C43FBF2830BULL, 
            0x2ECDBB9AE35EB505ULL, 0x6D2434F0B5D6A173ULL, 0xD96DABF65A07C25EULL, 0x72B5E9F0D85FCEBEULL, 
            0x47A48C1C3D652E42ULL, 0xDDD318E77C77C4EDULL, 0xC6A8DFCEA35CE3CEULL, 0x130ECF2AD0736996ULL, 
            0x1629B27449B0964CULL, 0x05305FAAC0970B32ULL, 0x2670E156DB2121E0ULL, 0x76BA6246F7D0AC2EULL, 
            0xBE172E0400212F77ULL, 0x9E27C8B6173F9F98ULL, 0xD66D2B8D39EE6728ULL, 0x10A35544498650EAULL
        },
        {
            0x2AD953652B423A7FULL, 0x6E97798C15DE3421ULL, 0x045B99CE0EE3A48BULL, 0xC4CC9BBE0ADF4F94ULL, 
            0xBF485B1C639EFDE3ULL, 0x1FF531C402ACC886ULL, 0x1F7127AB04A9511BULL, 0x202D0D4A87199254ULL, 
            0x78A8B3DD66534A97ULL, 0x7DA342A0BC07A3FEULL, 0xAB22183FDB275908ULL, 0x8DC35822A98E1BF3ULL, 
            0x600449585C366B83ULL, 0x19BE9DCE15200E6EULL, 0x0BC147CB25961BDDULL, 0x78322F4ADCAE66B2ULL, 
            0x5D603DE8BE6FFA87ULL, 0xA386113D1CB503ACULL, 0x74ED1E8B56976F1BULL, 0x70394618D7C31C13ULL, 
            0x0C8E98E57199052FULL, 0x72FEE9ADA934A2E6ULL, 0x8C4D3788FC0C1AF3ULL, 0xB210D005C0541369ULL, 
            0xCB23B77C0EAE26B9ULL, 0x39BA4E13FB96548DULL, 0xD0AC671F667581D9ULL, 0x76A7FA7A649AA279ULL, 
            0x9D6E9C24939E1BE9ULL, 0xFD57E7676F177377ULL, 0x1495A55F1AF9120EULL, 0xCCBA4845912660E0ULL
        },
        {
            0xD8490B68C0E5F8E3ULL, 0x402A1A9A1BE1F5F9ULL, 0x0ED0223C35E9FD4EULL, 0xA9F91A60B3C7595AULL, 
            0xAA22534856E15D38ULL, 0xB250AE909936C613ULL, 0xC9C25A1EBB8AF8F8ULL, 0xBC5FDE5E2A307564ULL, 
            0x25486310B015E2BEULL, 0x01F12F69C3CCD111ULL, 0xFF6A62CFEF0E43BFULL, 0xE77407EF942250B1ULL, 
            0x9CD4552301DAE091ULL, 0x5350C0C1DD83173CULL, 0xC768EB25EEEC034BULL, 0x6B99EAA4CFAE53AAULL, 
            0xA4569A00BC394476ULL, 0x9EFAC3A6CF30AF8CULL, 0x2A75813D69ADFDCEULL, 0xFB9D71669380076FULL, 
            0x4BC0D0A8560B1A72ULL, 0x88B27D7284C4855FULL, 0xBCD22F1EA4B63A4BULL, 0x308F993438699176ULL, 
            0x93E878B33BCFE454ULL, 0x5427D73FD8152855ULL, 0xD4085A3D2692E2CBULL, 0x77208166D6B1BB4FULL, 
            0xC953E560B3076738ULL, 0x04BBC0B5C2444723ULL, 0xC6EAA34BC95D5CBDULL, 0xF6C307DC237E8D61ULL
        }
    },
    {
        {
            0x4E8B5A646C954077ULL, 0x91D1BCBDF683A38CULL, 0x7233F6E72FEC04CCULL, 0x1B18E58C2221622DULL, 
            0xE9942B0B172A399BULL, 0x31ADCF081EB9CCC4ULL, 0x18B03934A35FD677ULL, 0x398FE3C8994243D6ULL, 
            0xEDF829EB85E0C081ULL, 0xCEAF1F5CED3FEDE0ULL, 0x86F14BC0964FADC9ULL, 0x30B932E14EAAD9EDULL, 
            0xA557463A246E6721ULL, 0xF907274C071A353CULL, 0xFD56A93ED7F00A50ULL, 0xA1E3D2AEE7D1431BULL, 
            0x97290C9F419B1C09ULL, 0x69A44C5CA15E6D86ULL, 0x833DFF55662B13F1ULL, 0x68CD9FDCA2FA36FBULL, 
            0xC3B2076C95EFEF4AULL, 0xCEFBD5FE721DE931ULL, 0xC23AE522D91D8112ULL, 0xCC4C5B347260ABB2ULL, 
            0xDBE243AC542C6064ULL, 0x1BD095EFFE88A3EDULL, 0xDA208B1C85911A2FULL, 0xF6BB9D12FA94A51DULL, 
            0x4BF3268A090143F7ULL, 0x154291CE94CA1B44ULL, 0x9CB1E7BA8588F99FULL, 0x3C4AD873EFFDC881ULL
        },
        {
            0xFEEFDB68B1BDA22AULL, 0x148CFC32B1D27A49ULL, 0xF588655A1C162C0FULL, 0x400E2C64CEE756A1ULL, 
            0x50287E55C4F734D2ULL, 0x1594E10785F1BB99ULL, 0x3DF4B6BE961CD39FULL, 0x1DF9A80D5FBFE7C1ULL, 
            0x92DEBD5867BBE8ACULL, 0x825C721AEA778771ULL, 0xD634D6B00E5D99C9ULL, 0x9F4FCD27279BE81BULL, 
            0x093A5815EFA03D1BULL, 0xEAEBAAC4C86CE5BBULL, 0xD1C3FFBD8AD160CDULL, 0xCC463A6F5D30B769ULL, 
            0x71C115FBE6F81EFFULL, 0x7A7F1D418178B7EBULL, 0x70E43A6226AD0A6AULL, 0x3D56712203EF73DEULL, 
            0x913ECF0940282B2CULL, 0x07F29CF459FCAA15ULL, 0x8EDEA6DA22813BC0ULL, 0x190DFF2692C81CE0ULL, 
            0xECAFEDB095557A73ULL, 0x454C5FD4BF26B015ULL, 0x8DE7199454E41D30ULL, 0x93184486D3088F02ULL, 
            0x70E95CDFF8D045C1ULL, 0x7FEA68CE3BB4456DULL, 0xE79C54A8305FED9AULL, 0x7569B65A0EAE6B72ULL
        },
        {
            0x898066B480746B24ULL, 0xDA904F44FCCA8C62ULL, 0x5A1CFC5C413DC2DBULL, 0x44168EA30C8C258EULL, 
            0x47CC6DDF4C311A01ULL, 0xEF8C071943AB351FULL, 0xB67ED1ACE8F96144ULL, 0x7600C9AB95FBC883ULL, 
            0x97C46A7D658CDB3FULL, 0xFAE8ACDFC401215BULL, 0x277CE7B761A63A08ULL, 0xA82C919F2ED849BBULL, 
            0xA35F3FBE6D768923ULL, 0xF4D698B42C7CE694ULL, 0x75C6BAF3C368765FULL, 0x5FC5D0AF6FD7E172ULL, 
            0xEB4DA0CC2A6C27A2ULL, 0x4DA2E47112BE6809ULL, 0xF544CE7F642064BAULL, 0x7BDDA91CEAC39961ULL, 
            0x9921B04C6F2356E5ULL, 0x628EDFFD1426C49AULL, 0xDDE6222004DA1F49ULL, 0x7AC5495A3C4F27E3ULL, 
            0xD4B82D4BB60B5D8CULL, 0xFDF4DFD9560075B3ULL, 0x1B38578620D9E8F0ULL, 0x9FE06BD522936935ULL, 
            0x3F94D2BC7A4EB329ULL, 0x42D62D3DBB756E75ULL, 0xE30FC3A8AF9C8F3AULL, 0xF322C3D0236A51E7ULL
        },
        {
            0x97F92227DFFF0457ULL, 0xE442FC3263EAA303ULL, 0x1B9352FDCFC1BB6CULL, 0xCCF5D2F6C7001B6AULL, 
            0x695C16A7341E7134ULL, 0xBE9782617C6EF63CULL, 0x832E3B3F0A2E28D9ULL, 0x1C7741B38BA5096BULL, 
            0xD47441CA213040C0ULL, 0xDACF252F88EB5956ULL, 0xCFAEC5649F025B43ULL, 0xE048764787127883ULL, 
            0x63847F854209ACF2ULL, 0x193A6D163C709B58ULL, 0xF2CD68D4118BD10BULL, 0x9B1692DC39329A73ULL, 
            0xCF86C5897CAF3C6BULL, 0xA062D1759B2FA509ULL, 0x9439EADD21C8D435ULL, 0x7DDCC30FE6FA4C35ULL, 
            0x0C07C93D459EE84FULL, 0xDCF00EF32ABDF314ULL, 0x3131BA904F7F6509ULL, 0x5AD4E67F0083DCFAULL, 
            0x314B8570AF6EF3E5ULL, 0xC2FFADE76BDD77A4ULL, 0x47F3005E22E449F2ULL, 0x01850F7D4A595015ULL, 
            0xA8005BECB143F0F7ULL, 0x355429A67AD5CB1EULL, 0xCEE0640AB823C467ULL, 0x7731E8462BA2F2AEULL
        },
        {
            0x1B9E7EE89A28A936ULL, 0xB6F0499DC69FC25AULL, 0xD31659E9D68F969BULL, 0xF531E49D8BB08FF8ULL, 
            0x7782E26D606B725CULL, 0xD7C6DEBA3C13F663ULL, 0x7CDD014FFCF8BC7CULL, 0x2204B6A71BC9F6C3ULL, 
            0xF6938F678CA49860ULL, 0xCCD536C5851D4C1DULL, 0xA00ECFFE1AA61F4EULL, 0xD6AC5D76948CBE18ULL, 
            0x0B2CAF0254F231F0ULL, 0xEEFB15012445DC89ULL, 0x4D16782E2E45EC03ULL, 0x8742E390ABE3540DULL, 
            0x81B81A7F92A459BAULL, 0xCB8B94185B394650ULL, 0x5275CEE614E544E8ULL, 0x99A1021A225CFDA7ULL, 
            0xBBC865249EA214DCULL, 0x7B857B063BDBB9DBULL, 0x90DBE62A64EBE88BULL, 0x4487811F248BE751ULL, 
            0x445109827A195A89ULL, 0x2481F2C1BB38ECECULL, 0xEFE71F9AD09861DCULL, 0x1BD185BB90AEBFB9ULL, 
            0xA068E069D36BEA77ULL, 0x7FADC624C774EA8FULL, 0xCE80C175A6718A69ULL, 0x3AB5FDF0182573F6ULL
        },
        {
            0x1AD05722B4E02E55ULL, 0x1BF33B1D01BA094EULL, 0x57FDF721E2FDE96AULL, 0x5168DA3BAA845A89ULL, 
            0x6F7C53CBC444E9E8ULL, 0x058B9BE9AB041D27ULL, 0xF0B7905FD6D5A829ULL, 0xEAB5571AFAB2F214ULL, 
            0x41E919224F30B604ULL, 0xCBA76D470C77BAB8ULL, 0xF613EF3AA9CE49C4ULL, 0xBB40A85F856FF21EULL, 
            0x492798E6B4119E85ULL, 0x8803CB2A575FB7A1ULL, 0xC162E24F499EC570ULL, 0x69507F8C4C4747EEULL, 
            0x3B72E9191168205CULL, 0x3CE8D68EBB0B7613ULL, 0x7A60BD30089B58F1ULL, 0xE2AD17900554286CULL, 
            0x0145346769401370ULL, 0x63F6258AFD38DCAFULL, 0x7483FAE0E152C164ULL, 0x36C203D5009598EFULL, 
            0x014E41459D3D8CC2ULL, 0x24263ACE08E93BCEULL, 0xA21437F86556B7D6ULL, 0x79F8907452017A42ULL, 
            0xB5B0CA016A804838ULL, 0xB8E22A1314A4D78FULL, 0x2C56D33052BF0A28ULL, 0xC4712CA3EEAFBD03ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Rigel::kPhaseAConstants = {
    0xC380ED1950981B4EULL,
    0x5881372F29121C7DULL,
    0xD45DC1372013D6A8ULL,
    0xC380ED1950981B4EULL,
    0x5881372F29121C7DULL,
    0xD45DC1372013D6A8ULL,
    0x9F8FB469CA9B2297ULL,
    0x874EEB6FF5F57239ULL,
    0x23,
    0xA9,
    0x75,
    0xEA,
    0xC5,
    0x80,
    0x3F,
    0x75
};

const TwistDomainSaltSet TwistExpander_Rigel::kPhaseBSalts = {
    {
        {
            0x9D4A9C39F8BC3CA4ULL, 0xA404FB6B8DF91627ULL, 0xD17C34E38FEA47AAULL, 0xDC34AE25F22E29D4ULL, 
            0xC73EF73E96F464ACULL, 0xB091764046D9D9F5ULL, 0x131A9C049945569AULL, 0xB30CDDBC086655A5ULL, 
            0x74BFFFCEE26EF2EBULL, 0x92D127A7B87B3DC5ULL, 0xC1FE0F08594F4E7BULL, 0x00DDC1346A039E91ULL, 
            0xE340DA1CEB1980AEULL, 0xEF6F30EF86D94098ULL, 0x7D639ECF5C238AB5ULL, 0x3B4F82F2447F670FULL, 
            0xF303C683877CD99CULL, 0x98A656FCBCF0F601ULL, 0xDCA1858A324C63B9ULL, 0x4D9AE572FC4879EFULL, 
            0xB8F7093FEBA38DAEULL, 0xF2A87E0CCF4D2477ULL, 0x709389D89C836E13ULL, 0x4BCE686E997C39F8ULL, 
            0x886613C16887B75AULL, 0xDE7F2C9FF8772E1AULL, 0xB1458EC2ABAA9C44ULL, 0x319D005EF6E7D9AFULL, 
            0xD407BB0E18040CFEULL, 0xFF703FD875727E2FULL, 0x75AEF6FDFF5E2A43ULL, 0x90A561EC2FE5EBBBULL
        },
        {
            0xBFF151A579A5424AULL, 0x2D0D36A628B7FAFBULL, 0x9049EAF7D3A56311ULL, 0xC02FF7D96AB6737DULL, 
            0xE4F328626F20D2FAULL, 0x5A2246F9618D226FULL, 0xBF3113DE38AA69E4ULL, 0x10F333653025268EULL, 
            0xCD9E6CB0A8DAA443ULL, 0x49AE32AFF1818824ULL, 0xEC7DC1A462666C84ULL, 0x2FEC82C979E173CCULL, 
            0x3CA48E143156D1B8ULL, 0xF3132FD27F580BD5ULL, 0x65816CD5617FD523ULL, 0xFED5FFDDC39292E7ULL, 
            0x5AF0653605C3F896ULL, 0xEC35D8FDBD81EEBDULL, 0xEBECDB84D2B2FE69ULL, 0x25326B0A23C14D8CULL, 
            0xBC551B244716F2EDULL, 0x5A8693529141E2CEULL, 0xF75CB98DEDC51B0FULL, 0x4534682CD1C9DC9CULL, 
            0x32EF658420F562A6ULL, 0xF17BD9E68E2120EFULL, 0xDA9E01090C378ED6ULL, 0x35954A4030827FA1ULL, 
            0x7608FE70BC1D1259ULL, 0xD6DBA16187118B1CULL, 0x8EE62D122E2A7965ULL, 0x60E7E7D4F6B00EBBULL
        },
        {
            0x78B453AA208BEC42ULL, 0xCBA98E263056F28FULL, 0x5168888B9047A967ULL, 0xB9A6A91D5EDDE811ULL, 
            0x27997C310B60EE7BULL, 0xCF57B31ABE1DFDCAULL, 0x366ADF811B15921EULL, 0xB06A4AC4C84C11E2ULL, 
            0x47F7E6EDD7852CC7ULL, 0x2B3197448CFF569BULL, 0xA9E8A75983C58506ULL, 0x7845FA3F417107E8ULL, 
            0x9B424BD9946EB878ULL, 0xB8BD069FA8CFA33AULL, 0xFD5CA5EBC5A7CE73ULL, 0x6B6D76EF588FB901ULL, 
            0x7F40FEFCF7DBB6DAULL, 0x6D2D9709F5BB15FAULL, 0x67A4DF1B997CC52BULL, 0xA42BAD463E1E03CAULL, 
            0xD7EC3DEA4D091F71ULL, 0x1D2A2071E551E6DAULL, 0xE90A1B650A4F44AEULL, 0xCD5ECFFA01DAABB3ULL, 
            0x8C7255E951F3F23DULL, 0xEA94B007C81B41E7ULL, 0xBD13F6F7D2EF6D4DULL, 0xDBBC0AA707CCDA0BULL, 
            0x2E96E6297D04CC93ULL, 0xD305675C03111780ULL, 0x58FAC08F6C0120FFULL, 0xB04CE238BB842B38ULL
        },
        {
            0x56BADAF6E0CA6C0DULL, 0x1A269A3B5C1B0D1CULL, 0x95AECE56DD812CC8ULL, 0x57A8494D6B2734A8ULL, 
            0x5A63ACB78A5346BFULL, 0x8AB1195690E30F85ULL, 0xBCE1BD43B49E2A6AULL, 0x2C8C258B594C030EULL, 
            0x8A27A2DE0EBAFCA3ULL, 0x87E70C0E7A4C0B64ULL, 0x9FE7135125956F90ULL, 0xA98CF6A339C1ED43ULL, 
            0x18231DC54B1F98C5ULL, 0x97C62284BD87F403ULL, 0xDFF1056B567FCEDBULL, 0x8ECB1925EEEBDB46ULL, 
            0x6617FBE451212DAEULL, 0x7AAEB515726F80E5ULL, 0xBC82B676214EE82BULL, 0x23D098AE8D17E592ULL, 
            0x25107202AE72CF48ULL, 0x25F46FF10C74032AULL, 0xAB021D3F931873F6ULL, 0xB828C2E14AA0C8A3ULL, 
            0x25D461B3A67F4C0AULL, 0x1A5D606407BDCCADULL, 0x5AAD21079AB3650CULL, 0x1A8DB50D845ABCEEULL, 
            0x05A472B2AA4AE1D3ULL, 0x7292BEFBA5B11878ULL, 0xA64AAC1BC4FAEF96ULL, 0x5F2973FFFAC2FBD8ULL
        },
        {
            0xF707754DA43DB3ADULL, 0x6C7DAA6009DA7B94ULL, 0xC234C9CC48B88ABDULL, 0xEEAAD636FE197EA8ULL, 
            0x6F8A30A3B2EB4993ULL, 0xC025B9D1EFC3868DULL, 0xEC6D9EA2FFE77D91ULL, 0x6777F6443D29C5FBULL, 
            0xEFD87545E50F2879ULL, 0xA8914EE486685772ULL, 0xDF9A168F203CCBADULL, 0x43B52C4345E36C5FULL, 
            0xC85ABB1517169A8DULL, 0xA2728BEF94F00861ULL, 0xC2393BF098707BD9ULL, 0x8F2D056935647572ULL, 
            0x668718465CD2DB9EULL, 0x65E351D445A79081ULL, 0x5F96AD0F6B9D930BULL, 0x2A1BAAFCC9044BB5ULL, 
            0xB838F133156FFF43ULL, 0xC3DAADE01E1BEC96ULL, 0xE5C54E7E2029A1FDULL, 0x92583190C074C200ULL, 
            0xE1BE42E70A3728D6ULL, 0xCB1CF236BA79E2E9ULL, 0x62091835C9364A9CULL, 0xF388332656EF0697ULL, 
            0x8AD2057DB9234715ULL, 0x9AE629957D78ABB8ULL, 0x0A3E37AB02493832ULL, 0x0356F3BB651707CAULL
        },
        {
            0x0123EC468479C93FULL, 0x87C866AE1B729EB6ULL, 0xB076A63841FABFC3ULL, 0x35162A926E10E2EBULL, 
            0x3459CC042B557CA3ULL, 0xCC20D01285083D19ULL, 0xC20437B2FE5DDE03ULL, 0x348755892A15FC80ULL, 
            0x76ABAFA7DBC4FF46ULL, 0x06D4D7878A14A0F4ULL, 0xD85F76E0CB344CF5ULL, 0xDF3F626B5FC69FDFULL, 
            0x84AAD11B05B5D9ECULL, 0xD7BE51D4E6866637ULL, 0x29AED3C15B96D740ULL, 0xF26FF9B39015FBBBULL, 
            0x4D04F0098AE5F3CEULL, 0xEAAC2D1626DBA721ULL, 0x85019ECFE143ECD8ULL, 0xA0EE457EA1594145ULL, 
            0xD879FD9B109D4020ULL, 0x894461D32ED4D55DULL, 0x33BCF11289DBCDC1ULL, 0xFEBE2137DB5E38CAULL, 
            0xBE3F848B5708B728ULL, 0x06277789EF6A4AA4ULL, 0x8808C9EA21F716C4ULL, 0xA16C1E0B8895CF47ULL, 
            0xA9E509A5E6A5B240ULL, 0x1DC0B850073535D7ULL, 0xE381C74D66F5C374ULL, 0x0732C9813ECE1231ULL
        }
    },
    {
        {
            0xE839C4FD7E63C6BFULL, 0xBE2FAEED0A537A61ULL, 0xE8D3CA119C597D4EULL, 0xA2552DF6170C5363ULL, 
            0x9B3B6B8833EA94E3ULL, 0x6833A3E7FCDA1440ULL, 0xCC4CD2AB6F3A3B3EULL, 0xDBB0504906B56175ULL, 
            0x38BA980ABEFDC855ULL, 0x4CB720D4C60AD6C0ULL, 0x39416F3CE980C1B5ULL, 0x9216770DCF9073D1ULL, 
            0x22E036B3F3617E0CULL, 0x46567D7849309438ULL, 0x5CD077AA6B5742F3ULL, 0xA2BD672D5E2E3668ULL, 
            0x7930D537B721D5A9ULL, 0x683E40E4727510D5ULL, 0x4ACE8ADF452B8682ULL, 0x2297EE64BDE274BDULL, 
            0x1F9DB42B34C5E336ULL, 0x6027938B57FB715FULL, 0xCB27A45F7B3033F8ULL, 0x9C213841E0B8B2E2ULL, 
            0x90A8FBED81155010ULL, 0x89A0B97759577C87ULL, 0xA59D2170963D914BULL, 0x68D65FAC9E1D6802ULL, 
            0xE04AACBDAC5CF874ULL, 0x011E01221782C3C8ULL, 0x6897390CA213D2C7ULL, 0xBA40978C6A778A02ULL
        },
        {
            0xF02BE11E270A1AADULL, 0x1F70C191534C0CDFULL, 0x6DEF85B42334BC32ULL, 0x846606499997C58EULL, 
            0x167D0ABFD866034DULL, 0x2CD7C1F2D3633545ULL, 0x40F8D9052BB33346ULL, 0x8E6F4ACA849FC160ULL, 
            0x7A958802355469BCULL, 0x312BBCC6095A278AULL, 0x2EC373CDC604542CULL, 0x05575FB6DA64D520ULL, 
            0x99C910A4990EEB2EULL, 0xB2012DEA09B4EFDCULL, 0x21015B590E9E272FULL, 0x1A74AF1D676B694EULL, 
            0x07AEF0AA72F7C76BULL, 0x1996A897E1D8F087ULL, 0xED0D18CA3FEBCA7BULL, 0xDC69BC30EC124C11ULL, 
            0x9D9509C89D0AB037ULL, 0x299227371D8CD9F0ULL, 0x94E7B37765613536ULL, 0xC3F753BAE2C0AB27ULL, 
            0xECEFB9FDA1E25706ULL, 0xCFF44926BB735FCCULL, 0x47D5C043E95D8BFBULL, 0x6BC0EC875A3957D2ULL, 
            0xD055D8F31BC0D5D3ULL, 0x79A1BE9C6EC1E9B4ULL, 0xF532D34C18E466C2ULL, 0xF194A61179DE7E06ULL
        },
        {
            0x318E78BB6B55D03DULL, 0x3CEA6E791769711BULL, 0x064C22E0773284DEULL, 0x8DEF538EC0A4243CULL, 
            0x67FEC230B7C8F697ULL, 0xA59E319695E3E974ULL, 0x13069D5DD6C3F529ULL, 0x64CF8CEAF1B59F91ULL, 
            0x0EC49D17BD73A9ABULL, 0xD71B1F1DF58EFD6DULL, 0xEB25598DD91C9293ULL, 0x249F573102825253ULL, 
            0x91175CDF14ADCFA3ULL, 0xB0E2FA6E3D644B62ULL, 0x9F1800D70244E647ULL, 0x68FE90313FB21180ULL, 
            0x0ED40E8777D0F1CCULL, 0x62694C605E57F2BDULL, 0x025EEF7FF18CC183ULL, 0xC49222701FDED0DBULL, 
            0x5EE9D33769EF62D5ULL, 0x9ED3D0EB00ACA85BULL, 0xFE14AA38833EECAEULL, 0x3DDE7FB9FC302BDFULL, 
            0xC7B8FE8D7E24BC0DULL, 0x2F9770E55B1F72C3ULL, 0xAAA9F9A911CAC71FULL, 0xD311F48ED221C095ULL, 
            0x564CD5727DE93FDCULL, 0x09592B130CA3862EULL, 0x9BB6AC75CCE7FB3EULL, 0x69A42357C7B80470ULL
        },
        {
            0x1E858CFB848956F5ULL, 0x811AC0D3C9296432ULL, 0x258BCC1BFCE6FC63ULL, 0x9028C2B13A23B477ULL, 
            0x6135C5B7210084F4ULL, 0xA11DCB3B0EBE7C1BULL, 0x5972573AF685867DULL, 0x611928DD2BAE9B38ULL, 
            0x08AC8612DEC9C090ULL, 0x866569FB3F033C4BULL, 0x22236D296D44D037ULL, 0x6B0437418CDD28A3ULL, 
            0x03466CBAA9D582BAULL, 0x00E5C2585CBC9FEEULL, 0xA6B8BB128E92C4FAULL, 0x1E1066CE60A9C640ULL, 
            0x2D50E2F69C03FE03ULL, 0x372E75BB773B2B52ULL, 0xD065BDB8764CAFDAULL, 0x058EE37E23ECD1B6ULL, 
            0x38EB8D47455EDBF1ULL, 0xDCC7A64385906D0DULL, 0xC0D2A345C854AA6DULL, 0xE0F201DCECCC9165ULL, 
            0xA808B1D1D10E92C3ULL, 0xEDD5DBF354A76B3BULL, 0x7C37F154CCFCB5A9ULL, 0xFAB5ED300D6685D2ULL, 
            0x2B40CB1AC17C93B7ULL, 0x9A68E1B32AE5BE85ULL, 0x2F7B0F92EFFF8192ULL, 0x2A45528CCBF40728ULL
        },
        {
            0x2DF9AB655BBCA61FULL, 0x2688C2437C1DA32DULL, 0x48F534129570B8FBULL, 0x59435E41EB99A799ULL, 
            0xE23A30B691300341ULL, 0xEB41244ABD0C6A6BULL, 0x392F77EA407FAD06ULL, 0xB40E42D2B8D990BEULL, 
            0xDC3179472E43A243ULL, 0xBA418E84BF73C2BCULL, 0xDCE7EF632FD03460ULL, 0xCAA6734CBFC4BB7CULL, 
            0xF82498C17BC1D245ULL, 0x4BD105EDAD2F1AEDULL, 0x4B37C1A9E6CDA6D9ULL, 0xBF6D689B421DF243ULL, 
            0x0F23774C306A3188ULL, 0x9D418E778E36B943ULL, 0x321B30714C8E16B3ULL, 0xA7CB4FA109B023D6ULL, 
            0xB6D90A4A83E74193ULL, 0xBC3116EB67912C86ULL, 0x722032F56AE62587ULL, 0x5237D8DA9B49A105ULL, 
            0x2CD87000553B30DAULL, 0x49353D31AACABD0AULL, 0xD83F84C7C5DAE36BULL, 0xE8915CF842D0CCBCULL, 
            0xEC8072C52AC36718ULL, 0x1508E0C74A6C14AFULL, 0xA1D65FA22314BB15ULL, 0xDCFF3434F5569925ULL
        },
        {
            0x435A403C2C1E8457ULL, 0x8238A38DDA65D3F7ULL, 0x208F0529692D4660ULL, 0x0C991008BB5FF221ULL, 
            0x03F1ECA86F478B1EULL, 0xEE649EF65432E5A3ULL, 0xB5F395514544841CULL, 0x48CC94FD2069B5CDULL, 
            0xF53755944CAEB8AFULL, 0x1D1F9E2D2111B4E5ULL, 0x2182FE559D53DE5CULL, 0xF2C2CB07B1303169ULL, 
            0x5895B6988029AEF4ULL, 0x4BE1C4457D394DCBULL, 0x92A5166482FC77EEULL, 0x843B16B5800E81F4ULL, 
            0x68317E225890E1D1ULL, 0x378E06B0A8339469ULL, 0x24EFCE17134DC4C9ULL, 0xB13328FCA6362FC7ULL, 
            0x5D2726917596F04CULL, 0x406F7649747C5586ULL, 0x662412D424001485ULL, 0x846224FC9C50B3DCULL, 
            0x1DD664196534C143ULL, 0xE84CCC37FA75BC00ULL, 0x0EFE822514C3BA8AULL, 0x56FD7AE4862882C3ULL, 
            0xFE5E87E1602C3499ULL, 0x41AE58E80DC62E1BULL, 0xE84652B2C464C093ULL, 0xAE5B509AF9A638C7ULL
        }
    },
    {
        {
            0x6FE3C5D75047CB3BULL, 0x5FC691D5CC5BCB05ULL, 0x546BB0280C5C4201ULL, 0xEDEB75D3AC0A193FULL, 
            0xE0E32C2905AF8AC0ULL, 0x28556E633CF2CF46ULL, 0xC42E644CFE4C596AULL, 0x7AD0F8189064F0D6ULL, 
            0x5DC458BD4853B29BULL, 0xCAF38C55FC491E13ULL, 0x25FD6716DFD8B9E0ULL, 0xAB9EC953C9C956F5ULL, 
            0xB42756683D3E87E5ULL, 0xEB4D073C322118CFULL, 0xDD4DDFF957EC463BULL, 0x0BCC2F2A1EC47B92ULL, 
            0xB8280694F2E51455ULL, 0xFF91D9EA1787165FULL, 0x330C784EDFD32C92ULL, 0xB5E213A5461A9D25ULL, 
            0x29614FF9B9BC26E2ULL, 0xA05F68144C0E5C5DULL, 0xA5482A97F96C107CULL, 0x89992C6CA1A91473ULL, 
            0x5DBD01194697AFB2ULL, 0xF31248112C9AF7A9ULL, 0xBD561B92A1084A9AULL, 0x637DB6CD416BDB0FULL, 
            0x6DE5DE7C02EC87D2ULL, 0xCA2B0860EBB7A10BULL, 0x3D50DF6CBA2266E7ULL, 0xCBAA4DA0C560452DULL
        },
        {
            0x0BEE97EDEA08C0CEULL, 0x9ED7753B45A7EDCCULL, 0xC9AB43A5C3B424A1ULL, 0xF53D877DC679B233ULL, 
            0xA6D336F716719A94ULL, 0x30C9EC75D04FE7AEULL, 0x196B69C52CD89167ULL, 0xF9ECC92127D29C50ULL, 
            0xA9BC83B2F7E35324ULL, 0x932072D31065901AULL, 0x0FE264E9D92CD338ULL, 0x01D499024B4526DDULL, 
            0x8F556CBA6B54E9C3ULL, 0x771EB0969DA114EEULL, 0x9B85257E95B3A69EULL, 0x670FB9FEFA9B22C7ULL, 
            0x6ED2D19B4CBE4DE0ULL, 0xDEC60FC3DD9D21DAULL, 0x1AF4C371502B1815ULL, 0x5A2F9FD0C3C32EBBULL, 
            0x3D8BDCF8F522BFB4ULL, 0x38153E0020B8F357ULL, 0x398F7258A77D3488ULL, 0x8B8A8C68BC042676ULL, 
            0x3C8E843D3CF5E6A2ULL, 0x80D9C464E712F34AULL, 0x5873F4B1A129AAF1ULL, 0xDDCC1B2A07AB9C9FULL, 
            0x38A5FAA1996901FEULL, 0x832B3D5B7FE3EE96ULL, 0x5D66BCA7A812A8A2ULL, 0x49FE7846563DAFF6ULL
        },
        {
            0xBA3F8844ACD796CFULL, 0x9F99E26A40884197ULL, 0xEB2649120F25C59FULL, 0xB5436388088E6F91ULL, 
            0xCB0532FA2FE75A40ULL, 0x5510C51229BE7345ULL, 0xC7B4896F4C318DD3ULL, 0xC5AB3D5EF682D89BULL, 
            0x46EBD72B9E3364DBULL, 0xDD79E24E8D81BA57ULL, 0x4712A8AF38E65FCFULL, 0x39F904B49FB1EB01ULL, 
            0xE7D096D3FA4F1F30ULL, 0xCBE06A4B929F7FF2ULL, 0x4015EC8946B22975ULL, 0x61E40E86C96F0BE6ULL, 
            0xC505D5A15D403440ULL, 0x401BAA293AF68233ULL, 0x15DA3D3B086DD50CULL, 0x9BBCE86B2176CDDEULL, 
            0xA78B248B16C2F1E9ULL, 0x81E0509A08731C28ULL, 0xC9E9761AD6441182ULL, 0x1F436D55475A69B3ULL, 
            0xB1A5172A9D4556B0ULL, 0x74EBC9318FF68E29ULL, 0x896A5975A0636836ULL, 0x24269D46FCF7A266ULL, 
            0xD00B3590AF9EE031ULL, 0x28DE80955A8FE60AULL, 0x98AAF63B36912D8CULL, 0xE0E282D7F8DECD49ULL
        },
        {
            0xAB953857B71EBC4CULL, 0x2E2C24CC983F8A22ULL, 0xB24B5F32520F685AULL, 0x11491BF0B704E629ULL, 
            0xA7BF2334998A010AULL, 0x5CFDF11A9613680AULL, 0x99D813D3267240CCULL, 0x203A238E987A3DDBULL, 
            0x1C48A27C43CB4F12ULL, 0x5A9462B2BA919FBFULL, 0xF7636463CF2A5F7BULL, 0x67003832A74AF67EULL, 
            0xD6BA9A5BF8441289ULL, 0xD9E72583BF7B1FF0ULL, 0xFA184C4E481524E5ULL, 0x6FB5AFCCF44B114AULL, 
            0xC1A3F9E7FB77D602ULL, 0xF55675F25410B44EULL, 0x22F027447CC088B2ULL, 0xD28FA7CBDDD85B30ULL, 
            0x5E6EBE6F83455C13ULL, 0x72EA9D6B639D7DD3ULL, 0xFD70618A54CBC42EULL, 0xA58D6359999BEC7FULL, 
            0x319904C49763CBD0ULL, 0xE7A8EF4C079F71C1ULL, 0xE3C7F9434612F6BAULL, 0x9562AE4793847A59ULL, 
            0xD2194105C3EB88A2ULL, 0x9D097A4E7BFBDDA1ULL, 0x7D81753BB5A86ADFULL, 0xFFBD9440080CC76BULL
        },
        {
            0x64F28DEE0BDAD4E3ULL, 0xD842B66BEE39210AULL, 0xE8D27AB12823900BULL, 0xF7AEBABB19227091ULL, 
            0xE69B2CF9BAC8EA72ULL, 0xB9673F51E784888EULL, 0x2E5B6165741E8C4CULL, 0xC3C66AC84C389AE3ULL, 
            0xA9AC26665BF7BC8BULL, 0x305DFFBE44A465BAULL, 0x3EF3F380E27B036FULL, 0xA7FC8348AC251C9CULL, 
            0x666803D81BD750DAULL, 0xDD0459F7CDF152C0ULL, 0xB14FBB47BD4D6930ULL, 0x6752A845FB4D966DULL, 
            0xCABEA2CAECE23349ULL, 0x95A1E9BF486953DEULL, 0xA917C2390AB936B3ULL, 0x9261FFCAE6554CA4ULL, 
            0x24F7A0AAB46AE0A1ULL, 0x69D27F9E9E5B0AA1ULL, 0xC8B48754AC91EA81ULL, 0x6C7DA383892DB5F3ULL, 
            0xB229B9F5BBB22E9AULL, 0xA9DD750083C43D20ULL, 0x9CE1ABC4CB915353ULL, 0x2B2CE5E509536326ULL, 
            0xE5C14A455A716C4AULL, 0x8D684EF20C683F50ULL, 0x32D17292F33954F9ULL, 0xDD0B92C2915207CEULL
        },
        {
            0x8782CE9C9FA94F80ULL, 0xBD63A1CD3F4B73E7ULL, 0x841C7A6BB5D9C82DULL, 0xE1353BD32EFE2E34ULL, 
            0xB7FB0CF8A6601B50ULL, 0xD976B59E68FD6B00ULL, 0x474D6C4A7E0AEC0AULL, 0xC46D7A4E2EF87989ULL, 
            0x205892A5B1AD23D0ULL, 0x4EBE165B9F4C89C9ULL, 0xD4916C4F3D3BD608ULL, 0x78DA18B91E966323ULL, 
            0x01DF3A3376CC536EULL, 0xBB50CFE68C0590B1ULL, 0xC1F36650CD96B620ULL, 0xD2B29AD4323A73FDULL, 
            0xA8320E9A606A10EAULL, 0xFA4E3F2CD7F2ECDEULL, 0x1F8182ACF9946531ULL, 0x32A4FC9A7676D320ULL, 
            0x7C1CE9FB22E74BB6ULL, 0xB4BA146E976F1E25ULL, 0xD106964F72CF31BEULL, 0xB53A77BD807DF360ULL, 
            0x27AC547CDA0B9AC3ULL, 0x69F7BDBECC4E406AULL, 0x538F321DA77A1096ULL, 0x33D68E0058B93BBBULL, 
            0x7DB7A9CB08EDAE66ULL, 0x08A8243864C31D55ULL, 0x941489FF3A6208CBULL, 0xDE90FCFD273C2CD2ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Rigel::kPhaseBConstants = {
    0x2EF6034C70609891ULL,
    0xF70CB43C7BFEC542ULL,
    0xECC4067FEDAA04EDULL,
    0x2EF6034C70609891ULL,
    0xF70CB43C7BFEC542ULL,
    0xECC4067FEDAA04EDULL,
    0xDC5C88F625B6DB87ULL,
    0x2E65734EF8EB9D42ULL,
    0x9F,
    0xF0,
    0x56,
    0x96,
    0x0D,
    0xB3,
    0x5F,
    0xE8
};

const TwistDomainSaltSet TwistExpander_Rigel::kPhaseCSalts = {
    {
        {
            0xAD8D6B58EECCB1BCULL, 0x5E0AA0107D605B51ULL, 0xE7A1E3170B173CBFULL, 0xDC2835A4341F6452ULL, 
            0x43FEC5BD77ED6B9AULL, 0x38473ED57EB894EBULL, 0xC96DAC5CCAD7CD81ULL, 0x7367182645403543ULL, 
            0x676F8F611EA7DA3CULL, 0x7CE6BBE2B616573AULL, 0x015D01113FFAF323ULL, 0x41E76FD2004BE607ULL, 
            0xDFAB4A4D8D5D266DULL, 0xF5F576879DEACF9CULL, 0xECF29F40EE8BDB8CULL, 0xA31EBB4464E800F4ULL, 
            0xFA5953CEF407CECEULL, 0xE3649E6FC3A8D422ULL, 0xD88F02C1990F93CEULL, 0x236D98EACF49F8A5ULL, 
            0xFE456E2ECE4E3F0AULL, 0x05F420AA444BDC0BULL, 0x39653C4669751C8FULL, 0x65E14547FBA70907ULL, 
            0xC147624D225F85E4ULL, 0xADF07262DCD6835CULL, 0xAB2D588057504458ULL, 0x65FFAD64AA0BA24FULL, 
            0x6EC03F6A3F82D2FBULL, 0x8F09FDA36DFE6694ULL, 0x52F32BD06687360AULL, 0xBED27C335D8F517AULL
        },
        {
            0x9084681162B255C5ULL, 0x3B5D96569258852CULL, 0xAE0BCFEAEB8B588CULL, 0xE9773280773A5890ULL, 
            0xC782CE8DAB0232D6ULL, 0x242E60A3F207D259ULL, 0xC0F718049767B943ULL, 0xC92AB67725A68B8FULL, 
            0xB944CBCBACBC9119ULL, 0x2D0A430F56CC6914ULL, 0x34E38EA94ED5759CULL, 0x3D706E3BBCF97D73ULL, 
            0x5C2467225481AD65ULL, 0x8854FBAF538B52F3ULL, 0x0EBAC83AAA82ED5CULL, 0xFEF19F4B965C5AB2ULL, 
            0x1466BCFFDCE0DB66ULL, 0x7535B6C010579FD9ULL, 0x95E790966D51008BULL, 0xFBEDD00E49A4098DULL, 
            0xD32903D67EF0F721ULL, 0x774A0A29917C7361ULL, 0x83B7A2DDBC107F9BULL, 0xB8F2311EC4FC5650ULL, 
            0xCC9D43059248826EULL, 0xACED11AC796F0CDFULL, 0xA08C979B1129929AULL, 0x404AF48E64AF19C1ULL, 
            0x63BD5C2256F1C212ULL, 0x47C68874AE6C0E67ULL, 0xCFFE03B5BBBCCE5CULL, 0x6681B9C8A8F41540ULL
        },
        {
            0x629EBD6E755D112DULL, 0xD76BCB7ACF8D0D51ULL, 0xF1188F712F6DB9DFULL, 0x9524E060D3CE908BULL, 
            0xBF161EADC77639BFULL, 0x87C4A89AD3E28554ULL, 0xCD70A15D5F7F0EFDULL, 0x2BE292EE2FCB2C22ULL, 
            0x94D37628E9448FBCULL, 0x5C3680DE97028944ULL, 0x289C306D05742FC7ULL, 0x49A94885A6359E12ULL, 
            0xFCE46315B5E99C47ULL, 0xE8E8EFE51D3A4648ULL, 0xA79DBEF98443DF0AULL, 0x380DE55B2F126F3FULL, 
            0x666703796DE54044ULL, 0x928DAA2326210ED3ULL, 0xB517A4C593506B3DULL, 0x3DAA12D8C9829809ULL, 
            0xA0DD76D43A8616B5ULL, 0x02D096976A07C9F0ULL, 0x837D63886710962BULL, 0xFE35DEC22C54A048ULL, 
            0xFBE9CF9D457107F9ULL, 0xD5837FB0FDE92B68ULL, 0x986BFC4677426FC0ULL, 0xDA7896CCE1EC9621ULL, 
            0xC90BCCB13367E4C4ULL, 0xE43ED9F64806416DULL, 0x21353456D1FA2E5CULL, 0x63C713647EA8E846ULL
        },
        {
            0x8C80C4C287758E7FULL, 0x168E536C73D0BB7AULL, 0x4434A05DD230450BULL, 0xB35AA792F2DFC7ADULL, 
            0xBB79793F787EBD51ULL, 0xED15C0E1A86527A5ULL, 0x2C4AEF95C7894BBEULL, 0xF703C5B132A5DE65ULL, 
            0x6C4647D3F8CFB383ULL, 0x48F66C5918FE1744ULL, 0xB88EE48791681757ULL, 0x7637A2BC1575EC33ULL, 
            0xDEE7FF32EF981C87ULL, 0xD75C1CCD10E1AE2BULL, 0xD0C69E78C0F24246ULL, 0xE50288686CCE7DE1ULL, 
            0x47B7DD28158CEC2DULL, 0x2FAA1E8A8EF5DD00ULL, 0xF72DE7DED509C370ULL, 0x9799A90FADE5FC08ULL, 
            0x46EC2FB35A7BBDC3ULL, 0xBAC8AFF3B76D8C19ULL, 0x7C5436EB9A415140ULL, 0xE27A343D169333FDULL, 
            0x9410A7588DB5E16FULL, 0x5C32D24CD6B0BB97ULL, 0x35ADB150C061371AULL, 0x65B7D8B4F1287543ULL, 
            0x8182C1D9EF50DD32ULL, 0xDD49186AAC14124FULL, 0x8B3A02FC9541EE10ULL, 0x84413B20D5117ECAULL
        },
        {
            0x09253B3A0AF537ECULL, 0x5370CD333548E1CFULL, 0xFC78205B5A210ED6ULL, 0xE1914176BA0F4336ULL, 
            0xDD67A8FD37604764ULL, 0x3031910B6CAF35A9ULL, 0x9DEEA8C1F8B9526FULL, 0xCA737DEE09139341ULL, 
            0x0881B413DFA08E5FULL, 0x80874FFACFC0B07FULL, 0xE0A42B387D25FFFEULL, 0xFF7A64BACE1A08C8ULL, 
            0x2855348CD3E8680BULL, 0x5E61E0E2E08A90FBULL, 0x6EB932C4927B4B56ULL, 0xB8A1CC168786FB5CULL, 
            0x6ADBB666DBDE6D17ULL, 0xC5F914D5E7D22123ULL, 0x0EF25297F38E4D7EULL, 0xB14725FF082DDEE1ULL, 
            0x5503905142512AA3ULL, 0xBCE489800959CDF6ULL, 0xA2F025E9506DCD7EULL, 0x0CEAB8164CBFA730ULL, 
            0xAB9F73EC8ED2F145ULL, 0x69D0E144FB4C6173ULL, 0x65AC6E0470031B70ULL, 0xED05ACBDC515ED47ULL, 
            0x777FB6C13E8A4963ULL, 0xA1303FCEE6BF207FULL, 0x737510045617E8AAULL, 0x82AB67D45314904CULL
        },
        {
            0x016DDF6614D33F5BULL, 0x39456B912EA9D492ULL, 0x437A98314DA01A8FULL, 0x176438818FB17A01ULL, 
            0x15EFBAF4C1F44196ULL, 0xAE0736CA5C905CECULL, 0xD741D0A510803AF0ULL, 0xBDF51CD71221FF93ULL, 
            0x3ABFFC3D5E6794BCULL, 0x574457087B9F5803ULL, 0x29A5EACB9E89E762ULL, 0xCD2C70C7B43E85D0ULL, 
            0x11C05E9730A62004ULL, 0x2FBDD7D9C4E44C67ULL, 0x1EE8424226F1FF79ULL, 0xDD409F210697383DULL, 
            0x9E39C426B4B4E7DBULL, 0x0A4B3F53F27633C1ULL, 0x39E23E5A50187F65ULL, 0xF01EFF6D90508300ULL, 
            0xC3EFF03EBE3AA186ULL, 0x3339525A076029D6ULL, 0x67EDF8F338C6A856ULL, 0xC4921D954E95F202ULL, 
            0x44472E1F59549EF6ULL, 0x248AA32A1A5B3155ULL, 0xCFA7D5F95B2402C1ULL, 0x59E6AB1CF1B3DDF0ULL, 
            0xEB7540179C801357ULL, 0x5FBCF5ECF7ADACA4ULL, 0x01C7DA77946EA206ULL, 0x145576D7037F5A1AULL
        }
    },
    {
        {
            0x04E69B2BF6C93B23ULL, 0x8EFBD4612C512684ULL, 0x675AC9352CAC96CCULL, 0x1472188AFD5FEDD8ULL, 
            0xD8D971FDC4680161ULL, 0xDE6ECFF5FB6B7FFAULL, 0xD0C1F531E37E7285ULL, 0x880EB7FEBA8D28F4ULL, 
            0x62597A0ED6EFF551ULL, 0xABEAE880CDB20A42ULL, 0x00C7E17083027A0EULL, 0x72DB24CE1EE055C2ULL, 
            0x6D5347D375759638ULL, 0xD8AEB49695AEF3AFULL, 0x37DB55A9DCE5C11EULL, 0x3D057D10867BB5B4ULL, 
            0xF8CB6887AC50C428ULL, 0x46B28DD586FE7AA5ULL, 0xB2569BA0DF1CB430ULL, 0xF92826CABC312615ULL, 
            0xC52150E5295AD44AULL, 0x3C40E1486DB33F56ULL, 0x726906BF761AE1EAULL, 0x07F20962EF567B52ULL, 
            0x8B8FF11B34D4D376ULL, 0x87AF656B01465B54ULL, 0x033664736E87E8E7ULL, 0x52977F75CEF5F734ULL, 
            0x092AD92D068AB520ULL, 0x4558943D74202E9FULL, 0xDB105D172F3F8D89ULL, 0x13DE7835A2F5F3D5ULL
        },
        {
            0xB5D3FE46BA3C0F56ULL, 0x31E34DF7ABA8D9C2ULL, 0x1EF3588AEC7B210AULL, 0x925A28E609202ECAULL, 
            0x616FA79421ECB64CULL, 0x55EE7EB587A322CAULL, 0x43D533A549D0AB09ULL, 0xA5B35981B6AD02F0ULL, 
            0x67ACA66A1F2DE518ULL, 0x26DADBC2B6870220ULL, 0x5A321077284E37B5ULL, 0xD1A2C402C29C30E7ULL, 
            0xA6CA29A8B7C7D9D4ULL, 0x844EC54B1811B8FAULL, 0x507362E658E81558ULL, 0xD6B7BE64B7BCA1B4ULL, 
            0xA978E98E332D630DULL, 0x01E43B14AC940C8EULL, 0x5A276E287F4110A9ULL, 0x67A21C623B8C8984ULL, 
            0xF7D34D1F972A5C31ULL, 0xC58FD0AF1B24EC51ULL, 0x389637894B1A3364ULL, 0x967DBB4685F8F663ULL, 
            0xB387066B3FB07A07ULL, 0x2E7AA9427CE1FF08ULL, 0xFFA38927E042ECB7ULL, 0x8A3A2077FAD1A2FCULL, 
            0x720A13A0AF4731E3ULL, 0x099C85DA579AC27FULL, 0x47A575D6ABA88492ULL, 0x6941F79DDD6C0C51ULL
        },
        {
            0xF0D9CAE589825F6BULL, 0x95CE2FB72282048DULL, 0xD0828A3DC8F2F47EULL, 0x4529314E8D4F588DULL, 
            0x6C1F1F09BF76041EULL, 0x360D88AB04B6DD6BULL, 0x8CC48E6C2423B4C9ULL, 0x504C53F7B06C1C69ULL, 
            0x49FCA87CD4A57B0AULL, 0x4EF756E3A138DACAULL, 0xFED1ED22DC6B7456ULL, 0x96DAD9C52D2C1ED8ULL, 
            0x459E2B403DF8E09FULL, 0xBFDD832560FE20DBULL, 0xF2C8658F35F41ACDULL, 0x80A7D93AF4E257A1ULL, 
            0x27434EC7F8003A09ULL, 0x4561BAED29BB1284ULL, 0x6459F52A5BA0BF75ULL, 0x0D46FBA8C4A95981ULL, 
            0x6931F685529B81B4ULL, 0x6D4670BC5981D1E4ULL, 0x098F15F90219A503ULL, 0x58532C895CA77C44ULL, 
            0x2FE029FFC09E6B2AULL, 0x995CB7FF5BDD3B8BULL, 0xA75EF2F21A3358B2ULL, 0x9155C35AF05FA565ULL, 
            0x32BA04CA082A03F1ULL, 0x77C9749F4713DDB8ULL, 0x7A01490463167136ULL, 0x440EC374637D91F1ULL
        },
        {
            0xC175574E23995C73ULL, 0xCCD6EF7209F8EF58ULL, 0xA28E41DA45A40B67ULL, 0xF8DA6EADDBDC79FFULL, 
            0x8818490CAFFB50E7ULL, 0xC5849E9687F28149ULL, 0xF3ADEDB0E06518CBULL, 0x1CE3F898C096F42AULL, 
            0xFBB8162B59D17CA7ULL, 0xADC6648D614483B7ULL, 0xCEE11F958323A531ULL, 0x7EF2029CBEF2F6EAULL, 
            0x552B5EB56DEF1228ULL, 0x002280A6291FEBD7ULL, 0x57A56E664094468DULL, 0x778363E60BB6C9FAULL, 
            0x7DABDF388B16A601ULL, 0x7FCD317349512835ULL, 0xA0CB90925BC9259EULL, 0x1824B27565DE49EDULL, 
            0xAB5A085D43120B57ULL, 0x22944F13C0690870ULL, 0x1DB5099E0DFF9AE5ULL, 0x9B6F7C1845CD9B29ULL, 
            0xDD0E6BF4EBD1AA35ULL, 0xB4963D6E7851E334ULL, 0x111F03C33CC7F693ULL, 0xF73F12C9665796D7ULL, 
            0x0A5CB3EE1C96680CULL, 0x7817ABBBF5B96AB9ULL, 0x773582FD20376602ULL, 0x3D9CEA957AEC52D9ULL
        },
        {
            0x7D4A02E4205C99B6ULL, 0x5BC924B6AD345F2FULL, 0xE9ED23AB3A58CC43ULL, 0x385930A58DD18E58ULL, 
            0x920AF77637DD209FULL, 0x54758AE8844BA3F7ULL, 0x723F32F0D7055B6CULL, 0x2DDCB9F36888B74DULL, 
            0xAC01C84094FB606AULL, 0x9CD68E32B43A1F7EULL, 0xCE07AF879E5D07F1ULL, 0xA01D353A7E328988ULL, 
            0xBC89605CBB542654ULL, 0x208A9C290F85F245ULL, 0x99A3B1E26F7112BAULL, 0x7FC2881B3AA8DCC7ULL, 
            0xCD7DF3FABDA44F54ULL, 0xB1557768974ABED0ULL, 0xF555B707855FABAFULL, 0xA5F876686078976CULL, 
            0x642C9B6D379BBE4BULL, 0x39C383587DA9CB35ULL, 0x1D0755729C38C07BULL, 0xD3B311998C01E9C5ULL, 
            0x64D161B247E73410ULL, 0x2B0325FD1B868110ULL, 0xEBC0F89831778FBCULL, 0xA18383E6694A7081ULL, 
            0x875EB4E4382A4026ULL, 0xD8ECE5BE5BCD0CF2ULL, 0x6C8BA224EF5EF881ULL, 0xF91AED4979C80EA1ULL
        },
        {
            0x83051639E8AC310AULL, 0x413CBF52EA519C9DULL, 0x51044F24E41A033EULL, 0xD79CD8C194EB3173ULL, 
            0xF9C7451B747D551FULL, 0x4CE4EB9189ACA71EULL, 0xA9FA7E9530924855ULL, 0xEF430B5BED4B69FBULL, 
            0xE444CEFC0A3C96A4ULL, 0x94F7FFE27267338BULL, 0xD9D0271462595369ULL, 0x76D8209EC636C454ULL, 
            0x9836D1BD73F741F5ULL, 0x1B2D5BD8B2612713ULL, 0xF2435F0E0C43542AULL, 0x9EC8EDD880D6B9B9ULL, 
            0x4A84E82718EDEE62ULL, 0xB364C19B4E87C0C6ULL, 0xF6ACCB2EC84EA0DCULL, 0x92C8F691EE20F82EULL, 
            0x6A86D920ABA19B28ULL, 0xC213058F9FC31D6DULL, 0x51A2E7650B0B4CBBULL, 0xA4AB7D6E2C03CF24ULL, 
            0xFDA36416336AECB7ULL, 0x80CAEACF45B146DCULL, 0xB04F5934F37E4445ULL, 0x74524C1756B7E4E6ULL, 
            0x76383FC620F01D07ULL, 0x13B76F38BED8B6E8ULL, 0x1FE7FAB904A89152ULL, 0x450621FB51CA1998ULL
        }
    },
    {
        {
            0x3E1FD5C9E2EE1FA3ULL, 0x2F0E62002F166BBCULL, 0x0B6E5EE6A88C0289ULL, 0x7D1FF7670FC1DF45ULL, 
            0x05C6F7D3436FC880ULL, 0x9C720DF4691C2A5FULL, 0x8D114AD99BE7A2D2ULL, 0x25E73FF5AB759D82ULL, 
            0xC46FAFEB35A12E1CULL, 0xF633234CA28F4E67ULL, 0x8F6D54C55BE5297BULL, 0xB8EB18ECC6DA4F68ULL, 
            0xB2DCC3C72335D372ULL, 0xB69D26490253EC8BULL, 0xB90863F1F3D98239ULL, 0x55595353A98FDCCAULL, 
            0x31889FFA8DF85D6EULL, 0xEA0B03D1DEF32076ULL, 0xE75277DBF617D58DULL, 0x86A49C89A671B67CULL, 
            0xB425EB143D214DCEULL, 0x46FE65A374CC381FULL, 0xC20DEB736FB17616ULL, 0x33B0F26B89279613ULL, 
            0x4ED42A37C0F9C012ULL, 0xBDE3EFC241BF40A7ULL, 0x9A39566D4F9040D7ULL, 0xCA77A4555A15A22BULL, 
            0xE691F1630B4541A8ULL, 0x25DD3D371156B691ULL, 0xDFC4FDD1A6AC792BULL, 0xE90E5D4F36BB11B1ULL
        },
        {
            0x981B040399C05E41ULL, 0x6FDB349B7621B09FULL, 0xE526075C0D30F336ULL, 0x33AB566D8F9A0B24ULL, 
            0x1EE7BEAFA66E0336ULL, 0x59FF0D2C69622B2BULL, 0x6033CC104F16E4F7ULL, 0x77D41B3AA81D43F5ULL, 
            0x8F554CFF54003B74ULL, 0xC2F8945762C5F956ULL, 0x35E34A8D171F50DDULL, 0x62A594F842DDBBA2ULL, 
            0x29C97C8A6221E815ULL, 0xC4B8280CF87571D8ULL, 0xE9063C43C1DFA515ULL, 0xB28CAF91F06C6D17ULL, 
            0xE853EA244E575C32ULL, 0x269C0D88A7094DFFULL, 0x1805CD6C8C1F34FDULL, 0x6A37FD3AA8673020ULL, 
            0xFE58EF030C40099AULL, 0xA5E82A7A22D3C8E5ULL, 0xD8FBC12617DFE7A9ULL, 0xED74275730B6255CULL, 
            0xFF42722F26F4918FULL, 0xCCF3184E5809639DULL, 0x5D71383AC60DFC0EULL, 0xA331D8A9AE600497ULL, 
            0x4D8F2BD0EE4CC05EULL, 0xD91309A77DC3438AULL, 0xDCF624F863575CE3ULL, 0xC42E0AAB650490EEULL
        },
        {
            0x8134F3DED8774044ULL, 0x2D7892DB4A89ECC6ULL, 0xC8FE9CA269C1B395ULL, 0x212F1736BFB8F0CDULL, 
            0xD89460DA04DFFCC7ULL, 0x7E6954B14DB76848ULL, 0x9EC8F0F95F9BBA2EULL, 0xF4FE4C415D6ADAFAULL, 
            0x287577DEB456B8FAULL, 0x875A243BFAA6F56DULL, 0xFFEE1BABE59C12A6ULL, 0xE25AD704236E7BD9ULL, 
            0xB8956FA1CC95B2DCULL, 0xAD19B71937E5EC7EULL, 0x043BEB478D347260ULL, 0x4FFB2E918649F57DULL, 
            0xB7EB83887CA17170ULL, 0xBBE1CEF175814433ULL, 0xB41202B92A7F22D3ULL, 0xD03DA51CF4CF1A20ULL, 
            0x7AA2766156A0CF97ULL, 0xFF0E8ECD709A6D94ULL, 0x11F9A7CB2FC2EB31ULL, 0x4C907D48DBA38FE1ULL, 
            0x19AC9232B4FD069AULL, 0x7C75862CF17F7D44ULL, 0xD0FDEC8EE2060B93ULL, 0x9ABFB3BE84001869ULL, 
            0x38A5F914DC2BA648ULL, 0x53C7D482A435A60FULL, 0x51A1DCB73A8092D2ULL, 0x7700C0B80D603017ULL
        },
        {
            0xE8D81B359570B34BULL, 0x63387A186C8AAE16ULL, 0x7CAB0A8F421ABE02ULL, 0x75AF48FE4BDE6B0EULL, 
            0xADA5E5960E3FAE48ULL, 0x003FC1FD99EC92A4ULL, 0x8862F80A357771A4ULL, 0xF5C9754015384CB9ULL, 
            0x3431507B334BB7C4ULL, 0x9F21BDDA36DA8FEEULL, 0x588354FEA7161485ULL, 0xE0E14CA872B97935ULL, 
            0xA8E8EF23AB847204ULL, 0xFD77555307747D3EULL, 0x0ED1F7A0B0363324ULL, 0xE0A4E5C2A90EFFFAULL, 
            0xA5AD3637F95BBB06ULL, 0x6B8C1CEADB3C0B68ULL, 0xD94F1F3E4779E7D8ULL, 0x9C5D9C660A35CD12ULL, 
            0xF24C895C6FF6C307ULL, 0xCD1BFECFD024142BULL, 0xA2D3114990DFBA51ULL, 0xBF9B428BA3379D21ULL, 
            0x0682020F7A6A9BDBULL, 0x00653E8F539DC4CAULL, 0x59E5B68B629F363DULL, 0x4948E42CEA35A416ULL, 
            0xB57C4F331D336E14ULL, 0x879EB7A240AEF6BBULL, 0xFC07D2A9A3F73E49ULL, 0xA354822FDFD6EAB8ULL
        },
        {
            0xB0A320932A3F8DD4ULL, 0x24382C86B1D1954DULL, 0x0C075900EC71CBD9ULL, 0x059ECD85D461D508ULL, 
            0xD72E7C2A508046C2ULL, 0xC13E3C338D74941FULL, 0xF33AB7E6CF275A64ULL, 0x92F38786E047D38FULL, 
            0x3FF0535D36EB6C8BULL, 0x7DD3BEA1FB1171DFULL, 0xC613C7476119BEA6ULL, 0xAD061C8057CAFACBULL, 
            0x872B5CF1B0C83E0AULL, 0x7990E64B3EBB8C45ULL, 0xC83CA46C43DECB1AULL, 0x190D51A2DE60C719ULL, 
            0x86981D5AC5722088ULL, 0x652448905E55E53FULL, 0x6E4FFA39A7FA672AULL, 0x775EEBE470593BAFULL, 
            0x8EC0A7E3B6DF92CDULL, 0x65DF3FE07F44F774ULL, 0x5BF303B918D9D5BDULL, 0xC1429E80217E3072ULL, 
            0x9E3F7E003968BDA6ULL, 0xC10306E939BB1241ULL, 0x7E94CD9E7A504F45ULL, 0xB2559B1B5A4124E9ULL, 
            0x87655FB14B1A7BBEULL, 0xC1137DB2B1383A91ULL, 0xD8486A662B2B92C1ULL, 0x9A3567C429DC0DB9ULL
        },
        {
            0x7EB5DC02A0A6AFDBULL, 0x70EBDF08A04322B5ULL, 0x9D025AD38CFE62C3ULL, 0x98133EF6F1F0C5A9ULL, 
            0x3644337040BB3361ULL, 0x48EE13D171AEBECCULL, 0x38C3162F9D1A8A06ULL, 0xF5F36F8D6B05B562ULL, 
            0x53D72E07C8D844BBULL, 0x6DE9C45ECBC96EEFULL, 0xD7E6473AD59B91D0ULL, 0xF5516E75EEC013D8ULL, 
            0x54F49DA62C9BBE5DULL, 0xF721BA8ED3F37520ULL, 0x540AD6A62105DA77ULL, 0xBDCDAF35AFE9D636ULL, 
            0xE3EF9A4A28B9DFF5ULL, 0x3AAF32A40160C274ULL, 0xC80BB4075DFE06F0ULL, 0x4E9EE4CD904E6BB4ULL, 
            0x4B96B5774DD55EB7ULL, 0x655B0BE6E69EB5D4ULL, 0xF989767A2221AECAULL, 0x49186D9BDE0C1933ULL, 
            0x5AC0941AC819E58EULL, 0x20CE0C35D1F3EA88ULL, 0x456AAB83BCA18E18ULL, 0x587F8F975CFA8601ULL, 
            0xE8B4CAF2D5A8EC4AULL, 0x88EBE82D7CB42B6EULL, 0x69FED086767DB4A0ULL, 0xEEDD644B0DC21678ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Rigel::kPhaseCConstants = {
    0xA31DDAF87A4C31B4ULL,
    0x98CAB81B93F7CC15ULL,
    0xBE326434390FC2C8ULL,
    0xA31DDAF87A4C31B4ULL,
    0x98CAB81B93F7CC15ULL,
    0xBE326434390FC2C8ULL,
    0xE988E73EF6917C63ULL,
    0xB77D10E74CB31B80ULL,
    0xCD,
    0xD0,
    0xFA,
    0x98,
    0xA7,
    0xDC,
    0x7E,
    0xE2
};

const TwistDomainSaltSet TwistExpander_Rigel::kPhaseDSalts = {
    {
        {
            0x37CFAFE6792D5FF3ULL, 0x417E33BC9C6C88B1ULL, 0x534082244303FB17ULL, 0x22953ED4D64D51ABULL, 
            0xEC1DB590F491AFA2ULL, 0xCA22874777574F0BULL, 0xA60E7B688CC2D32DULL, 0x81FF50B8D4E373BAULL, 
            0xE7DE0F8565A9A3B6ULL, 0x22DD6E3B5E5E959EULL, 0xEDD8B6EA3B32660DULL, 0x8000DECB4CBE4778ULL, 
            0x898522FC0589F648ULL, 0x7027EF53D7088BCDULL, 0xB8706DDE750E85C9ULL, 0x1EEC455138138327ULL, 
            0xB37B525E577714DAULL, 0x4F4CA28535ED87B7ULL, 0xD4A54C3D4D3E3F73ULL, 0xF3EC1539512EE6ACULL, 
            0xCE4837451842241EULL, 0x5B66321A94253B8EULL, 0xDCE94E4FDCD57794ULL, 0x4D56BE73383BEE46ULL, 
            0x4567196CC583E989ULL, 0xBBD2B7A76840940AULL, 0x594E888843C60EFFULL, 0x2F31E076BD977ED1ULL, 
            0x9C0F9015FD9EF180ULL, 0x97135FBCB2C49EA7ULL, 0x7B3B05A0AECB426EULL, 0x90B306503BE44366ULL
        },
        {
            0x563F3E1A11079322ULL, 0x1C653F3A88754851ULL, 0x87858BDC549371ADULL, 0x72513CE249ADF3F4ULL, 
            0x46D6278EE7FE2687ULL, 0x51DBEA58D63C729CULL, 0xB58ECCEE9A595B95ULL, 0x4BA4A4846B4E6108ULL, 
            0x5C9FE297C2399E23ULL, 0xAAF59A0CBEE4A2F0ULL, 0x3594127DA7765F29ULL, 0x389B9ABBCBF6AA84ULL, 
            0x433DD77473FC4D71ULL, 0x9B3B12A6F2F48E01ULL, 0xE234987FB5F16CB2ULL, 0x74C536333142BA10ULL, 
            0x792B78E4C2DFB9C2ULL, 0x3FED8C637A200135ULL, 0xC4992F66BF7D748FULL, 0x883F69CE1BC1DCB8ULL, 
            0xA348E6D7C3689834ULL, 0x792D0CA50DD0D2E5ULL, 0xF0DC232F24D86D3FULL, 0x26289AF76989E356ULL, 
            0x85A7C5096E3F267BULL, 0x2DA0204AC9D851B6ULL, 0x57C5A2849CB80BACULL, 0x3398E16E4FE1A24DULL, 
            0x4AB778EBFC33C7E3ULL, 0x27EEA064AE0A58B1ULL, 0x8B89FCC7B8FF63F7ULL, 0xF6C63F46812A3E7EULL
        },
        {
            0x15AD2B5B0939E815ULL, 0x0EF5A78EF920844CULL, 0xA6E7C88D9080EB8DULL, 0x2A82480FA2E97B05ULL, 
            0xB6AEA402044EB4C8ULL, 0xD298A32BA2B7FBC6ULL, 0xE4350DB0CEE68A88ULL, 0x1C5D66FFDFF34FC2ULL, 
            0x1F3093DEF2B9D55BULL, 0x4568FA19788E7B4BULL, 0x052C5CECADC4736AULL, 0xB04E01FC10B7E15BULL, 
            0x62C4A28E5117F28FULL, 0x15765E05DCF14931ULL, 0x3A1010E83050FA6CULL, 0x11741CA6489948ECULL, 
            0x400EF933025FC0AEULL, 0xAC90D67854885167ULL, 0x81282E83527DBF84ULL, 0xA7BBD7A9F40E06B4ULL, 
            0xE0E77CBAC7430000ULL, 0xA8352DD2EEC12942ULL, 0x610FCF0D0CF60F69ULL, 0xDE933F493290AB25ULL, 
            0x942DFF96E6876C45ULL, 0xD9ED8EF3A24B9D05ULL, 0xD2E5338C23427E38ULL, 0x42D638902D9BBA3BULL, 
            0x0A2B93811DFA0043ULL, 0x1D74E6CA244838BBULL, 0x8801F46A2AD39C3CULL, 0x28A83B597DBFB731ULL
        },
        {
            0x4D3DB76414D2F54AULL, 0x3D7D3824417951C5ULL, 0x8D2E07534F498FE6ULL, 0x1AA20692D9349461ULL, 
            0x57C44F02648AB0AAULL, 0xEBFC51300F72DE63ULL, 0xFF9043451E6BA7D9ULL, 0xDDA4C0EB0A00D09BULL, 
            0x467D7E8CC42FE145ULL, 0xA315E1F8F34253FEULL, 0x777B348CC95ECBC6ULL, 0xF16CEFC9E95D6935ULL, 
            0xA761E98A49093C4DULL, 0xF9EA4C61E67276EBULL, 0xB91CCD34123F4B7CULL, 0xAB55BE16339612F8ULL, 
            0x2A9808085F9D3E2EULL, 0xEE61A652E097A739ULL, 0x75AA9AAFE87F1729ULL, 0x82E76F970594238FULL, 
            0x8F78B02F7C59BD19ULL, 0x122001363435AF6AULL, 0xF905DD060FFE4ABEULL, 0x95ABBF307C28367EULL, 
            0x9703E992AEBD334FULL, 0x8DD8A368D8D8A772ULL, 0x27FC5380F035A6F1ULL, 0xA6033EE6D4211B0DULL, 
            0xAC6659C4982CD023ULL, 0x186086A51CEC782EULL, 0x3F84E73B0333E90CULL, 0xB19557FD125EE069ULL
        },
        {
            0x03D017D2ECE15A29ULL, 0x8FE6477E5B7D3459ULL, 0xED844B47B2691FD0ULL, 0x26C1087E1FAD14D0ULL, 
            0x94477B2DDD4303C3ULL, 0xBC0583D427FCAEBBULL, 0x20D80C6C419F0C7CULL, 0x04B6FB3106C71F38ULL, 
            0x631E98820200578FULL, 0x5926E12308621CFFULL, 0xBD2DB40AA7AA1CA8ULL, 0xDB98ABC986D25B60ULL, 
            0x05D64C1149962158ULL, 0x263827A8358FAF05ULL, 0xE4CD7B1AE6AECF83ULL, 0xAB3E2B70860A6F58ULL, 
            0xF24ECFE1A1CBF5EBULL, 0x8820FAEA4D793C2CULL, 0x95365EB7AE029743ULL, 0xA3557F8F49F768C4ULL, 
            0xC588B7A4A22795F6ULL, 0x7C7424795C8DCE94ULL, 0x346ECE310E9DC58EULL, 0xA1EDFE9B2A44B2BDULL, 
            0xA2E3121253FB377EULL, 0xBBFF5EE9428B811FULL, 0x9EED413895FBFFFFULL, 0x8F4B2E3D6D091448ULL, 
            0x92C4990B19826A77ULL, 0xD53A96528D17743CULL, 0xFE434DDEB0937F2CULL, 0x608C8E779DC7CC30ULL
        },
        {
            0xA8A88BA22FA16ABCULL, 0x62943C65E78A05EBULL, 0x272DDF85468F11B8ULL, 0xCC3747A627731729ULL, 
            0x40D004CA4F1FE177ULL, 0x42892977B75ECBD6ULL, 0x79DB10BEE7A09E06ULL, 0xFA6E7872181A236BULL, 
            0x2433BDAD2AAAE82CULL, 0xF2AB6F78CA76C690ULL, 0xBFD8301D69D71066ULL, 0xBC02B41B0D93F743ULL, 
            0x12EBF6413C40F19EULL, 0xB4FD25976729DA21ULL, 0x4E28223C02401DB4ULL, 0xA3545696D26E29A2ULL, 
            0x08FAA00A4EB0C04AULL, 0x834CF563EB829D3EULL, 0x3AE431AC97FE75E4ULL, 0x2861F38202C61A8CULL, 
            0x9C03B45BF686BFBDULL, 0x87B874021286B990ULL, 0x5C6766AB4F3CF61CULL, 0x5C6B5080FBB5652BULL, 
            0xD5A4075498E2A92CULL, 0x9B6A9502229EE6F0ULL, 0xC57F01EAC32FB905ULL, 0x05212A3F29B29A0FULL, 
            0x167FCDD7341E1FC3ULL, 0xE3CAF100C1DDDA1BULL, 0xE8729AD7DD377888ULL, 0x894DBBDC65A15466ULL
        }
    },
    {
        {
            0x882CB44C404C8916ULL, 0x37777CDD6B091FB1ULL, 0x30958FCC19A80B27ULL, 0x7AF6CD7132AB519DULL, 
            0xF3DD88E8A9FE9B67ULL, 0x07C4B0FEC82FB21DULL, 0x61B709C2B3CC894CULL, 0xE830F744E008F072ULL, 
            0x32F7D4200EA82B5BULL, 0x17B197A65C95D406ULL, 0x103EE6D924702DBCULL, 0xE8696E075A6C35E6ULL, 
            0x0543C8397A8F3035ULL, 0xD538169BAFDB84CAULL, 0xE94C503E0EEE26C1ULL, 0x7E3B3422AE4C36E6ULL, 
            0x1483BE093CDF4D45ULL, 0x23E1A5B0682EC46FULL, 0xD320974D0201FF56ULL, 0x1D411E3C2DF83CF4ULL, 
            0x63DE14995A51BFEEULL, 0x7293ECC155302E2EULL, 0xF1488D34CB057EC6ULL, 0xEF66D5692C9FEF4DULL, 
            0x56F7F5DB595A2896ULL, 0xB6011A15366E534DULL, 0x74666DBD5A1CE034ULL, 0x27980BDB5BA8A500ULL, 
            0x8C187DB22B9B51ABULL, 0xEAC37F56AE0FE6CEULL, 0x1CD848DFC56DCBBBULL, 0x47ABC01214FA9EBAULL
        },
        {
            0xF16268AE9AE9A66EULL, 0xCE813E3D2BB21087ULL, 0x9D379C9293D5259EULL, 0xBD4E9C8E6DE548D4ULL, 
            0x4FBA641ABAB9E4BDULL, 0xA83B48DA4C3B43A1ULL, 0x1BD23C44389A420CULL, 0x35E048560003A819ULL, 
            0x1B466A52CFFECCEAULL, 0x1007FA24CCA47439ULL, 0x2BE70DC386019748ULL, 0xBF954E8D51F1E248ULL, 
            0x5D1EAFA30E53C321ULL, 0xC4AD437D0E93AEE7ULL, 0x590FD5E911FD1030ULL, 0xB8D8DA605EFDA33CULL, 
            0xA700D0758803642EULL, 0xB66A8B085A53907FULL, 0xDA7D4279080149CBULL, 0x106912CCE85B9E35ULL, 
            0x54FE93197E462ABFULL, 0x7550E4FD78487F84ULL, 0xEBFAEA9F26E9B098ULL, 0x3063B25BF8762539ULL, 
            0x6978526520DA79D9ULL, 0x2C91B426ABF08C1FULL, 0x239D5C2E66FD48E8ULL, 0x5D7E97E28A450E6DULL, 
            0x02366A348CB8FB35ULL, 0x8BD2430B49645A69ULL, 0x5F007C5CDD7117AAULL, 0x2DF10B2F9C4F3E2AULL
        },
        {
            0x524B7FC683F67493ULL, 0x58D845C26391C5C0ULL, 0x488DD79C86E2A086ULL, 0x63F471D4767DF773ULL, 
            0xA8C90C0A7C135B33ULL, 0xB7041C11A0800D7BULL, 0x0D80AC161FDA1BB9ULL, 0x439099EFA39249BAULL, 
            0x239D8E5DD15F6B13ULL, 0xF00620038CCBDF4AULL, 0x08EE3238C8F7647DULL, 0x37568D242556678CULL, 
            0x296639C981BBA26CULL, 0x94BA8EAC85FF92AEULL, 0x91FC3304886C4DA5ULL, 0x63DC482EB68471E5ULL, 
            0xDFCA2516155E336FULL, 0xF3961A8487238059ULL, 0x0E7BEE3F37551083ULL, 0xF4C50183F352AB18ULL, 
            0x89112ED651851C57ULL, 0x9B7B6C55FC50EA25ULL, 0xFC1942936FD0D0C1ULL, 0x8ABD6DA26C3DEAA2ULL, 
            0x46A2502D45BE8E76ULL, 0xFCC9886F02D0AF47ULL, 0xC6228E70A46259F6ULL, 0x7F35AD395B505D9FULL, 
            0xE27A4F9EF2A0810EULL, 0x560A379C624BDFCDULL, 0xD71351D7FCB3FEE5ULL, 0x311EA773865C0BD7ULL
        },
        {
            0x0E6E0B438B2242D9ULL, 0xB26822399F262D15ULL, 0xC872D3A53C776D32ULL, 0x99EEA145A1A95445ULL, 
            0x7A9119531AB0624FULL, 0x58EC4B1663F0E126ULL, 0xEA98D7244A9C1EA7ULL, 0xA2BCEBDF1A4D0A2EULL, 
            0x9D09193FCEC67DB2ULL, 0xB2A50C251387A544ULL, 0x57A84181AA1C0E06ULL, 0x85888B535E6C889FULL, 
            0xD92313F847C8B9C7ULL, 0x3515483198EF4426ULL, 0x7869B78A2739D454ULL, 0x72AEBDADD5835576ULL, 
            0x5A0BD0FCA1B38CF0ULL, 0x402271BA8D8F1F74ULL, 0x1E03C1EDA4780E11ULL, 0x1019DEC9D839F9AAULL, 
            0xAD7BD3DC15AA79BFULL, 0x91F6F09AA90A0898ULL, 0x661C871ACC84613AULL, 0xBCDB494C6872D7ACULL, 
            0x4D6748C2106B547BULL, 0x91DEE776AE5B4184ULL, 0x60E476A6B7D6E7C8ULL, 0x43EBB8B9D5DD4DAAULL, 
            0x6EC0A0E2C2663004ULL, 0x2B872750FA4332D3ULL, 0xA7DDF3F36A44DA3CULL, 0x1E6CBD8F282A9BF8ULL
        },
        {
            0x898600B1A7FB1054ULL, 0x75E9C1F49839EF15ULL, 0xF17E3271782E1621ULL, 0x08B3433BB27EDCAFULL, 
            0x0DBFE1F21B6C693FULL, 0xEC5B6E18C364B4CCULL, 0xE6A4AC4AB4CE5188ULL, 0x20DE805515A0FEF1ULL, 
            0xB452F47D31FF2DA5ULL, 0x597A19949AAAD2C3ULL, 0xB8CA190C2F5B4353ULL, 0xC600EF77D0CBBD33ULL, 
            0xB15B28B97DA3E595ULL, 0x2631727980B1539FULL, 0x2991565E48E4FAFDULL, 0x7695ED9A4A70B645ULL, 
            0xEE76161B0FEB65B6ULL, 0x1B6D4DF05A4F8AE0ULL, 0xECD788EE7E26E306ULL, 0x273FEA5A1526967DULL, 
            0x0382DD6FB2F181D6ULL, 0x6E62E93ECA0E1C92ULL, 0x30D16F4C284EC5F2ULL, 0xD79240A75B0F3769ULL, 
            0x72D0622E5FDB5984ULL, 0xFCB32DD70E4F39CDULL, 0xAF933EA7A1800030ULL, 0x917B6F8BD143F3AAULL, 
            0x804C774620048B2CULL, 0x818982F0F9AF695FULL, 0x5E8CE782446B2748ULL, 0x34A3B67E5EDE2F12ULL
        },
        {
            0xCD8D7CB6F3D12421ULL, 0xA50D02AD1225F1CEULL, 0x9A79BAA91F4CFCD1ULL, 0xC4DBF52D6275BCF9ULL, 
            0xCB0A53E894E77C95ULL, 0x396B4A29EB8DC54EULL, 0x1834188E182B3438ULL, 0x7CF1E95043FA34A6ULL, 
            0x80F414B6F344E32BULL, 0xEA8432FC380BE857ULL, 0x44F9A2F8EEF86757ULL, 0x9989ADBB05FC2C5FULL, 
            0xB5EAA9BB20C61851ULL, 0xBE58A6358B5259DEULL, 0xE434B79984C27A84ULL, 0xBFF2134E775E7B09ULL, 
            0x16836C6D6CAB0F9CULL, 0x683FC58411F64E08ULL, 0x90128DEC677E1381ULL, 0x6A4C479E1AE3D826ULL, 
            0xAE9FCDC583127670ULL, 0x9F7327F520060156ULL, 0x320D2CAE962E782CULL, 0x4F130B5FDF546E3CULL, 
            0xCBCC749FADCEEE3DULL, 0xB582393CEC30F67AULL, 0x3AD08EE07579D6F3ULL, 0xB51F2486961827C7ULL, 
            0xCDBB6C5F341F9EE8ULL, 0x5ADD8EE7DC0D6945ULL, 0xB71349E2B66F0167ULL, 0x34AAB03AA3AC961DULL
        }
    },
    {
        {
            0x329A2772B97949FDULL, 0x4A783BF4F115D4BDULL, 0x4E41ECBF2DFA6E6BULL, 0x02550DFFA18E33F6ULL, 
            0xEF26B4E93FFA5860ULL, 0x054320123D135207ULL, 0x951BD678B3B14AD4ULL, 0xFE1E28567FED2B6BULL, 
            0x46F6A5F078228A3BULL, 0xC5AF81D4C8F48708ULL, 0x335E3735DFC0E4EDULL, 0xE04CA49476D8D639ULL, 
            0xE915B5EE7D3F9079ULL, 0x1A2D1826B5D4DE4FULL, 0x4DAA884F3C6C8CDCULL, 0xB5D97C593F5ED7D4ULL, 
            0x60A30DA640CCF829ULL, 0xA637B57834FF6E36ULL, 0x6A91A866C941BEFFULL, 0x6277A7C2627E5081ULL, 
            0x7DAD74501A676D49ULL, 0x6E939917520AAE65ULL, 0x57E474208B3F6AD7ULL, 0xAF2CA101C8322FA7ULL, 
            0x50D4C83C0326531DULL, 0xC103AB07840D5F5BULL, 0x4C2D160C01B3DE23ULL, 0x3A88FB36C40E2168ULL, 
            0x7B4ABEEACC565D5DULL, 0x6BABB0E5839DF1CEULL, 0xAC02EDCE6404CC99ULL, 0xA2A6B8B7D6848A4AULL
        },
        {
            0xABB87E0AE2C09FB0ULL, 0x1A6C952739492EF5ULL, 0x30F375E85963DEBDULL, 0x034AAA180E78103AULL, 
            0x7248F6F6A176D5C8ULL, 0xF453C5BB5797CA34ULL, 0xF2326FC363FE62A3ULL, 0x2979494DB17DF5D7ULL, 
            0x6FCD5D7A97F31C4FULL, 0x9D1B82BAAE5E06CBULL, 0xEA82270B66472C62ULL, 0xAE84E18E54EEF45EULL, 
            0xD1B949AEC8EAFC65ULL, 0x9D4B6F1341E70A33ULL, 0xDE936D2C82D2755FULL, 0x189F10AB742B9075ULL, 
            0x8A12CA2790183B24ULL, 0xE9F6232DA552A49AULL, 0xADB08B4DD55F9257ULL, 0xC711B746895BB90EULL, 
            0x0A8C5E94B3702615ULL, 0x0AE90DEF0A302002ULL, 0x41ED1A23761D1DE2ULL, 0xD6533880D4D0712DULL, 
            0x0F18909269BB80C6ULL, 0xB613254C5778A0F0ULL, 0x324FF98D8B7BD8BBULL, 0xF184EBC271E5A1DAULL, 
            0x903EF2732B8632D5ULL, 0x4EC77C4A65E818DCULL, 0x6DC48DDF39453274ULL, 0x7A38D0CB5CA17E91ULL
        },
        {
            0x61E3FDCB4ECC2428ULL, 0x4CE7422AFC64ABA6ULL, 0xD15C95CC6F4926DBULL, 0x07125952A6FEDB2AULL, 
            0x346B18D904354C84ULL, 0x06537BFE54896C17ULL, 0x4263C6D041ED732EULL, 0xC24A6CEAFF87EF5DULL, 
            0xFC0424341D411FDFULL, 0x3438C763649BE345ULL, 0x12FE24A95C22F944ULL, 0x3ED3EADD1133DC62ULL, 
            0xA123D39C49A8390EULL, 0x6748668FC304039EULL, 0xB9963897F9BBAC16ULL, 0x149B25CCBF0B3E0EULL, 
            0x320E9F67236E2712ULL, 0xF843501B616C6601ULL, 0x77BE1D8810DD19D3ULL, 0x9BEFC4E0FA52E715ULL, 
            0x82514722248531FBULL, 0xEA7D1FE733734095ULL, 0x7261DBFECCC97BFFULL, 0xC269A0B41E169765ULL, 
            0xB5C064D9919ED9F5ULL, 0xFC96E783EA60269FULL, 0x678314DE4DD8BA93ULL, 0xE8BAADC43E97936EULL, 
            0xD98960B262143436ULL, 0x71B025544697DF66ULL, 0x62F5053F41E98D17ULL, 0x9679B8A1CFAD7CBAULL
        },
        {
            0xFF6C5DDDA55222BBULL, 0xF94016C16B43E849ULL, 0x20B475B0DDF08DB8ULL, 0xEAF7702C90459928ULL, 
            0xEEF3C96657C73106ULL, 0xF04F9AFBF244A9DAULL, 0xE21D6E493FBE29B2ULL, 0xA6596523151B737FULL, 
            0xE744C766E3293026ULL, 0xBBC6C9E988A46CD9ULL, 0xE65C43F38BCE6888ULL, 0x8F928B45420E6A8DULL, 
            0x014F70BAF96FC0E2ULL, 0x3689D2800785BD21ULL, 0xBBF3E39BDAD9ED33ULL, 0x7D5B2344AF261569ULL, 
            0x9DEFB3BE53C316B3ULL, 0x63C5A8A64747DA29ULL, 0xEF139E370317C2BBULL, 0xBC675FAFD350BF6AULL, 
            0x0F190B3F670E3F7FULL, 0x834C3B7C61633E21ULL, 0x57CA638B5B90B0AAULL, 0x76BAE4E0BB69287EULL, 
            0xBB9CA285A5D72EE7ULL, 0xE3860347E6F2B461ULL, 0xA9D4453A9CDC4B42ULL, 0xD4F0FCFAB8A8869AULL, 
            0xF3E04404A1D19918ULL, 0x12B2D3B702D83734ULL, 0xA98CE804773A1551ULL, 0x4D07BAE671C03A44ULL
        },
        {
            0x976DC2659702B8C6ULL, 0xBD60F0CAE4DF5A7AULL, 0x715A4A0BB366C58DULL, 0x1224BF81319698DFULL, 
            0x706104E8EF4035BFULL, 0xC9B8326E5A9D55ADULL, 0x12BA1CA2CB803C26ULL, 0x49F44DBFC19B7511ULL, 
            0x0C0DEC077CCCD36BULL, 0x8994DBDB71EFE4FDULL, 0x0E58E00E1DBF120BULL, 0x70FA75A3553BB68CULL, 
            0x45337321D0B613C2ULL, 0x38A9562DB1F02941ULL, 0xDEA0C3FF548C6DBFULL, 0xADD927EB841A8142ULL, 
            0xA53F1C099A640FB3ULL, 0x154235D9060F15B3ULL, 0x54ECB54AFC4AE3CCULL, 0x130DE16A1DB86905ULL, 
            0x2DE2142BF582901CULL, 0xB71CE6C43207A7C4ULL, 0x5C253916EB024E2AULL, 0xF34D1D1C203C1A7FULL, 
            0xEA7576D1AD1EB5CDULL, 0x425B129E230815CAULL, 0x82EDA16EF96EA90AULL, 0x32CE748094B87BB1ULL, 
            0x0AC59F3D08208AC5ULL, 0xB252C5EA999C246FULL, 0x2977AD55241FFDBCULL, 0xEEBE74FB519215EAULL
        },
        {
            0xD93F47B075530DC6ULL, 0x7A4162D6A7A7A53AULL, 0xE4DDBF9C966A3A2BULL, 0xAE161560962DC4A1ULL, 
            0xB2A1CF6FD078A616ULL, 0x6F24B7DFF78C59A2ULL, 0x958C14B89A81C328ULL, 0xCC887197F2DF0510ULL, 
            0x21A97F05D84CFA66ULL, 0x8E801175055BF10CULL, 0x8132042015AB0F9FULL, 0xBF075D215B8275B8ULL, 
            0x08E0603EAA6A16E9ULL, 0x191094BF4DE721C1ULL, 0x0B7693AB61D984FFULL, 0xB5EBA8C7E738B4C7ULL, 
            0xF7EE8282EC5DA7A6ULL, 0x82594FAFE1EB4CC7ULL, 0x7D8B16E8DD773E74ULL, 0x09D6E9753F71DEE4ULL, 
            0x54140B40600963EEULL, 0x7466388DAEBA9406ULL, 0xD65F633D84FF9751ULL, 0x4046CBB1D6C5097AULL, 
            0xC2B700DF16975313ULL, 0xD8533DC68F878590ULL, 0xE6AAE6945B9F8F4CULL, 0x5A44A20C3FDF7B2AULL, 
            0xFD9E6B9D8592F16EULL, 0x89DF74006D7AC5E0ULL, 0x78A29AA876B38C70ULL, 0x34AF91E73BC527F2ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Rigel::kPhaseDConstants = {
    0x2CF6BA1E69915CB0ULL,
    0xA10067E630772BA8ULL,
    0x0B6A289309E98890ULL,
    0x2CF6BA1E69915CB0ULL,
    0xA10067E630772BA8ULL,
    0x0B6A289309E98890ULL,
    0xBE458A4849DF9BA0ULL,
    0xFA5CF9B1EBE096A9ULL,
    0x5B,
    0x76,
    0xA4,
    0x4B,
    0xE8,
    0x58,
    0x73,
    0x77
};

const TwistDomainSaltSet TwistExpander_Rigel::kPhaseESalts = {
    {
        {
            0xDD23ADD5D88AA3F2ULL, 0xD2BF037769EA8BCAULL, 0xBBAEF1185AADD580ULL, 0xF95D8D3BFED54F4CULL, 
            0x9AE498C60037862EULL, 0x8A589309B5991A4CULL, 0xCCB3218C31F49B50ULL, 0x47DED9EE601E5917ULL, 
            0xD81A82F4AB96DB07ULL, 0x993E4195169A5B92ULL, 0x333D98BAF57659F2ULL, 0x6D81DE20FFB236B8ULL, 
            0x4250CC36ABEA87A3ULL, 0x2CC63F9592052B4FULL, 0x5861E215B7E139D2ULL, 0x067FAB686ADDEE02ULL, 
            0xFEBF22B37A10AA68ULL, 0x6D8272DC14E9C442ULL, 0xE19AB33FD5B87115ULL, 0x6EF3AB7E6F9F2ABAULL, 
            0xB01D753270BD1657ULL, 0x0D25E663EEE676EAULL, 0xE2BF75F1A40CD901ULL, 0xF19627910AD2FA5CULL, 
            0x02933A22B8E5F921ULL, 0x1678A20210B8EFF0ULL, 0x04276E0CFC566627ULL, 0xFF82576D4FDE316CULL, 
            0x02058F7ECD5D652EULL, 0xFF876071693B1205ULL, 0xF1B64B959A4BCBB2ULL, 0x8792BF5E32420B3FULL
        },
        {
            0x157355B7ED484687ULL, 0x333B176742243F35ULL, 0x0D211CC241034E8FULL, 0xAED48363A79C42BEULL, 
            0x169C4A2B3942F45BULL, 0x4FEE4766A58371C0ULL, 0xFD069E955D4DED0EULL, 0xC55578A1419A02E9ULL, 
            0x36EBBAB0EE0A414AULL, 0x4E48C5AD2B05FD28ULL, 0x6B57646090B141CFULL, 0x1382A9AE5CDC4329ULL, 
            0xCB5EADAC2EC26BBCULL, 0x04144596CB468BC0ULL, 0xC4C9AA66F0FEE08EULL, 0xA34058843E918D2AULL, 
            0x0AC7D02A2E297F56ULL, 0x6C2D656EE2141289ULL, 0xA8C76B227FBCCB3FULL, 0x91EEC9C708E87F52ULL, 
            0xCAE434CA0EFC5C6FULL, 0xCB8A8B424C913899ULL, 0xCC5F4E422FFABCDDULL, 0x99F542B6C405489AULL, 
            0x2A1123932FD632EAULL, 0x9165416903525293ULL, 0xCAB9D8244A9DFECEULL, 0x0DEA660F65B280FCULL, 
            0x5E86268CA30F2842ULL, 0x4E3B95ED7846A6C2ULL, 0x74E63DC03F1BEC43ULL, 0x9239AC4BD90DF75BULL
        },
        {
            0xDAF2FDF61C577A2CULL, 0x75475DF7240A82BEULL, 0x4C926418F2A41880ULL, 0x8197675285463978ULL, 
            0x97738570130288E4ULL, 0xE1887B1E3B20B143ULL, 0x05EF760FC4C47609ULL, 0x83055E1E73BBB190ULL, 
            0xAA4F1B03288F4D16ULL, 0x9C63FC2B7FCCEB5DULL, 0x4E5DF8D02F59114AULL, 0x74BD64189AF3FC75ULL, 
            0x065A29E6A53A874FULL, 0x3D31660CDDDB5C14ULL, 0x870A15756E42C04AULL, 0x6982A5B4A0E4329BULL, 
            0x2490C763D20B7423ULL, 0x8EA3C8391D74F412ULL, 0x81757905DDA882E8ULL, 0x55AD19E1F63A1C8BULL, 
            0x392CA52D15D95ECAULL, 0xDDE21959B4D5C47CULL, 0x1887CC9B7D196F1EULL, 0x551600472905FA4EULL, 
            0x308F540D7BEB273FULL, 0x3691B11B932102DEULL, 0x75AF38FDF50112BCULL, 0x12140E14DBDDBE83ULL, 
            0xA39C2A49759D8CE4ULL, 0xB7B73100F7517D5CULL, 0x3D95F8D1575B6AAEULL, 0xBE898F6B3E01A40AULL
        },
        {
            0xE752F3E79FA1215FULL, 0xEB13791AC54B71A8ULL, 0x3B36A9D3B5D7446CULL, 0x5B50A09804053186ULL, 
            0x7AB541EFF7AC600CULL, 0xB4D18D6D3A2551D1ULL, 0x9A8AED51A0A11B7BULL, 0x90060E6A795B7BC6ULL, 
            0xD54B09127F1329D7ULL, 0x3BBBC891295C9A62ULL, 0x8097F7F10C9EC090ULL, 0xAB26781F32BD4E28ULL, 
            0x84E55A78530D28F5ULL, 0xA1151A475CF12B02ULL, 0xDF9FF5E8F2490C5EULL, 0x0DA8A92573A451A1ULL, 
            0xF21083327A332F17ULL, 0x8BB37940A18B8440ULL, 0x5B034C10659D59FFULL, 0x7B40AD0D6ACBA735ULL, 
            0x8593A12BF48573D5ULL, 0x23943C64EE0B9960ULL, 0xF380A890B5627F73ULL, 0xF10EFE6E4FAEDFD1ULL, 
            0xE23D2D56FA4D6DBAULL, 0x2BDBB8682B3C93ECULL, 0x0EB0E8AC60566960ULL, 0x85E3CFAC074B4737ULL, 
            0x0B4D63098A40F715ULL, 0xF1C893D8577CD69CULL, 0xB30B41A6C980EE20ULL, 0x5BEE21AC183EE656ULL
        },
        {
            0xC1285A1B9DD088A0ULL, 0x8E2C94B10E5C8E4DULL, 0xAE9FF412D3EE532FULL, 0x4B42B2D37EF071D2ULL, 
            0x8D22BC2B14CF2E47ULL, 0xC67FEE0DF70A395CULL, 0x316716DD5FD82677ULL, 0xEB4131C8A261654DULL, 
            0xA4B79EE68693FD51ULL, 0x4B2AD54EA97679EAULL, 0x309F9CF7CB139407ULL, 0x574CE1DB3C4A99AFULL, 
            0x56B8E75FA5B44FCCULL, 0x114AE4F8D147404BULL, 0xB9A89D22E499C311ULL, 0x12444A788DCE82EEULL, 
            0x186FD03EFF796040ULL, 0xF99DF020BA6F8241ULL, 0x7FBBFA40EF4EE820ULL, 0x6F50CDEE1CF64BEDULL, 
            0x784ED8B56F1A2AB3ULL, 0xB3F18566E86A001EULL, 0x23FF65DDFA37DA71ULL, 0x0147D296ABCFAB36ULL, 
            0x95ED7FC444CC643CULL, 0x9CB7C9754A335074ULL, 0xA8F309E47E689D52ULL, 0xB44203A9C3C7F92CULL, 
            0x3035FA4FBD22004BULL, 0x236EF16A657DE491ULL, 0x428949FFAAB375ECULL, 0xDD53DD9927311E2DULL
        },
        {
            0x80DC3CB947C7C3CEULL, 0xD1F476DC800AE8E0ULL, 0x494DEF166739FB0FULL, 0xE2F465F99444E8EAULL, 
            0xB08665BC8016BC73ULL, 0x0B6AA15F2FBF40C3ULL, 0x6B1CAB8F583FB697ULL, 0x529AD0F171299937ULL, 
            0x5E15E613CE7F02E3ULL, 0x739C2B23E38A5D1AULL, 0x5550783F989208E7ULL, 0xD18B1E449D878FE2ULL, 
            0x2C1985DA5986CCA4ULL, 0xE00479A27D98906FULL, 0x62E48B776DEAC4D5ULL, 0xDE262A3A6F9AB7E2ULL, 
            0xF694887199E350C5ULL, 0x0E6AA2C40A23A162ULL, 0xBB22C2A13614FBB6ULL, 0x2A54214F8A9FF46BULL, 
            0xF90BFB12B84F8EC4ULL, 0xFD8BEA46CFBEA2F4ULL, 0x85D1CF5404CB2465ULL, 0xDC1B308463C6D55EULL, 
            0xCCBBB3B59E80E0BEULL, 0x68B2B1F2058289FAULL, 0x4B9C19A2F7809027ULL, 0x272E738C05414057ULL, 
            0x3ECAE2070353BE81ULL, 0xA932335B6813E083ULL, 0x6C3F417AE90E54B2ULL, 0xC41F98EFDF1F38DAULL
        }
    },
    {
        {
            0x21A4E52A81AC50E4ULL, 0x8649D4539139D8E4ULL, 0xB1CF8001F16A4F39ULL, 0x41DA71E7A656E69FULL, 
            0x542D3656DBE10F17ULL, 0x2A7D720A7494DB58ULL, 0x993993F74F2BE0BDULL, 0x871476971C1D8C5EULL, 
            0x9905C4B1F7BB13E0ULL, 0x7E43FBB16D35F38EULL, 0x30C78746B9B694C7ULL, 0xA39C43859C5557EEULL, 
            0x5D1EC26848F52B78ULL, 0x00A2CC6134BA5ACFULL, 0x6806685F42893B8CULL, 0xC639C8F3159A33BCULL, 
            0x9194DA50137C65CDULL, 0x2A81E8BE8E4AD8B9ULL, 0x9CC7D8D45543AF9EULL, 0x9DB6CD7501D7EF18ULL, 
            0xE04D9C250AFC84C8ULL, 0x6402046937BEF6E6ULL, 0x7D1D409C15D0C1EEULL, 0xAB92E769FA960331ULL, 
            0x739AE23407E50A0AULL, 0x79DD0AFD5210C5B6ULL, 0x1D602B243B9C10CAULL, 0x85805AB7A5DDBA4DULL, 
            0x5F5D5C7EDDC4A573ULL, 0xE333B41841F3FDDAULL, 0xDB459FA52A8016F6ULL, 0x0BD29F01E42EF42EULL
        },
        {
            0x843A53BBD7E5EFD1ULL, 0x1283177B76A6D82EULL, 0xB16CB32D99AA0A3AULL, 0x62EE66B000683660ULL, 
            0x7EBD7426342AC523ULL, 0x4876F8DA568BF67BULL, 0x3F07074EA7D354A7ULL, 0xF542672814E63BB4ULL, 
            0xC9D8256808D04828ULL, 0x87EDA3263DAD7E39ULL, 0x146173C8B8B89A9CULL, 0x01F4C0B03A0F45FAULL, 
            0x2679A462FA63E484ULL, 0xB517E6DFE1AEE967ULL, 0xFF917B1AFA12F806ULL, 0xD7E7AF433A2D52F3ULL, 
            0x4AE9EA2104C0D73DULL, 0x334EE90D7418E7C0ULL, 0xDA0DC47D6B43CC2AULL, 0x6F9F9A3D180D3859ULL, 
            0x0C6D8ADB91E07803ULL, 0x6D80945E2F808917ULL, 0x45782819C9C41312ULL, 0x8C45FA6F8D542AB5ULL, 
            0x9F0DDA8B22DB516FULL, 0xB41F442698F18B18ULL, 0xC16D65EE5EF051B2ULL, 0x8B16B1B1F8F94A7CULL, 
            0x0D702C964AAFE437ULL, 0x3B657068524EF6A3ULL, 0x7F35FD6A15E51A95ULL, 0x4B307B50EAD76D85ULL
        },
        {
            0x21CFB1E475B8FDFEULL, 0xA1C816078FC9348BULL, 0x9137C1C43DFB3960ULL, 0x0232202AB142B7A5ULL, 
            0x0376542EF2F4F32AULL, 0xB0421107C7696AE2ULL, 0xB60E5E63E8654D16ULL, 0xA8DEE7EDA1002133ULL, 
            0xA00394F76DC9CCB3ULL, 0xA5CF31ADA26E39FBULL, 0x15692A7CC309D4E8ULL, 0x7B84C6DE57CFBC47ULL, 
            0x0E79A230B372B7DBULL, 0x6D2675CD44887E6CULL, 0x8A7B8D0C91286EB9ULL, 0x5A6FC4507784A426ULL, 
            0xA9974964FE1BD898ULL, 0x0A594896CE314403ULL, 0x579FE67CA79B25CCULL, 0x1B141DF0B759373DULL, 
            0xBF37D10CBFF35FF8ULL, 0x44F5D5D8305811BFULL, 0xEEC7AD32A7663562ULL, 0x0B5EE72A0AAA531BULL, 
            0xC274288FD899BE6EULL, 0x140F041C3FB3D6D4ULL, 0x965C0B684D80E499ULL, 0xE2E14693028B3C53ULL, 
            0x9A9CAE1F45A97B77ULL, 0x80867829EB74D6ADULL, 0xD8F430D10C8695F2ULL, 0xC486A5DE7AD02241ULL
        },
        {
            0xBAC4504B6D9BBA78ULL, 0xAF40D106CEB488A1ULL, 0x43B73F78984E5A4FULL, 0xCD1B4D0EEE81760EULL, 
            0x98F5B7D121D3FA0AULL, 0xD5BAEC5740178FE7ULL, 0x224764A541F952BAULL, 0xE69ADEC51B174A5FULL, 
            0x838E627806422D5FULL, 0xDFD520DE83364F3AULL, 0x050DB8BEEBC0593FULL, 0x180C18A381BE6275ULL, 
            0xF947FA7391A78CC6ULL, 0xACA8B7775A1F40EFULL, 0x9873E1D1242AB3C3ULL, 0x644158E0061BE888ULL, 
            0xEC0DFB51604CBFAAULL, 0x4321AE61D93738FCULL, 0xE44A9C81A8A0503AULL, 0xABAD4D69C0326DF7ULL, 
            0xBAF2811DFDC0BDE9ULL, 0x901EEF8201FCFAF8ULL, 0xA012304A428D5F65ULL, 0xAF41EF2AF996EA83ULL, 
            0x32EC3671E29B1B63ULL, 0x1457A357573F66BAULL, 0x6BC27E9EFD2B019BULL, 0xCA63B4A6FBA7DF4BULL, 
            0x4D31D16531C53817ULL, 0x5F8043ADEF9FFA4AULL, 0xD364603410703C0BULL, 0x4B809792C64770DEULL
        },
        {
            0x75A407061663C93BULL, 0xF1AE201DE9180324ULL, 0x0667D6A7BF10AF2DULL, 0x6A0BB275BDB7A097ULL, 
            0xBD75706D09873E73ULL, 0x073036CB8B03531BULL, 0x96C9201D23FF45A5ULL, 0x4C229DF2227D7F3BULL, 
            0x9C469636A4A2AD7EULL, 0xD0D416E9D82502D8ULL, 0x653D36E2E6B1A8F6ULL, 0xC88C4B2F5AD8673DULL, 
            0xEECE24B9FD0DC86FULL, 0x7D6D2022184A466AULL, 0x386735F2DC3C26BEULL, 0x1326773BCC66F46FULL, 
            0x173105387F8C28BEULL, 0xC7DA75A7DFEF888DULL, 0x472CD7B2797534B3ULL, 0x50CB50FCEB7768DAULL, 
            0x348A0F2FA84D6642ULL, 0xB5F45333A43A1C76ULL, 0x2A0B132FC50E6986ULL, 0x8376540B9D7DA500ULL, 
            0x750A90B54EAAF402ULL, 0x8F79B8DC98512113ULL, 0xA5F7AF6564296FF9ULL, 0xC52FC3453C6395BAULL, 
            0x7178595F39A79087ULL, 0x6784A60C560DC4A4ULL, 0xF00D5C3C1496AD20ULL, 0x1D1B9DCC4408332BULL
        },
        {
            0xE21F4C30F7EE796BULL, 0x9E2E8C926DD3D623ULL, 0x03D84989BB360D48ULL, 0x6EC1648074686F54ULL, 
            0x7A0F53FA69E00A44ULL, 0xF90F553189A745DCULL, 0xAC9E48A3E644AC27ULL, 0x59B6D66B170036C7ULL, 
            0x722F61B70C92E5CEULL, 0xF1FC6CCE84BE08E7ULL, 0x7BBD0CB196B09EEBULL, 0x636E79CFB8928381ULL, 
            0x077D90659528B7D2ULL, 0xD70179E87CE7FD96ULL, 0xCB8EA67E6B863F8AULL, 0xC1A04129BF003477ULL, 
            0x51BC5905225812B9ULL, 0xA297B7C0B9F9AFA5ULL, 0x0BB0217FFE909362ULL, 0x314822E96CB85180ULL, 
            0x429C305DC152E9F4ULL, 0x09C93E58B7CAE9C7ULL, 0xE09712D48F59EBD3ULL, 0xC36EC98BFA69AB64ULL, 
            0xD17EEC72487AB0CBULL, 0x383070AF211A16A9ULL, 0x50F8F2139CE585ABULL, 0xBCA7E6BD8DA29F9AULL, 
            0x8A8CAB163CEAF252ULL, 0xB560DDBDC4BAC289ULL, 0x9ECBC590B63639E6ULL, 0xB74AC1D782E66FE0ULL
        }
    },
    {
        {
            0x2C634CDBF76F2048ULL, 0x282E1092F2249FDCULL, 0xA0F0830D1AABDB97ULL, 0xF5A9D669FC64DBFEULL, 
            0xB35BC7BB00EE868CULL, 0x3048C6314A9011FEULL, 0x7447756500FC804AULL, 0x1FD751CF897DC90DULL, 
            0x6C114DACA4C4EA96ULL, 0x07889544335AD4BFULL, 0xB6041ECBFEDA1F1FULL, 0x9EF1C3523884C1ABULL, 
            0x02C78F2F0FA058C0ULL, 0xAE345AA87FFB364FULL, 0x517AD393C43D4251ULL, 0x2B684C5A25761348ULL, 
            0xAE237C9D2E95BB9FULL, 0xDCE92387E4330C6CULL, 0x19CA63D4CBB59C0FULL, 0xD7CAD33F91D9B0DAULL, 
            0x5CC72210CDE9B9CDULL, 0x01D1628802AD5E5FULL, 0x1B152CD033DF176EULL, 0x4A174254CC40917DULL, 
            0xDF057F7FA2CF878AULL, 0x2B414CDC38CA24B5ULL, 0x1D3022CA02D405F9ULL, 0x2630BB305DCEBB12ULL, 
            0x19BB0579C95A6680ULL, 0xBDC3F79253A03A53ULL, 0xDA68CC352943415CULL, 0x6F2254C31C2CDE8BULL
        },
        {
            0x353F7FAE66DD8256ULL, 0xE8ED0E1E891E4018ULL, 0x8FFDBBA4A3029631ULL, 0xCF14B8851B797C51ULL, 
            0x8247B72E09B3BA1BULL, 0x1BC625159D2B02F2ULL, 0xCE548DCE3010E899ULL, 0x78B43E892115E192ULL, 
            0xB94AE2C004227B3EULL, 0xDFF9C989DF93F5E0ULL, 0xB6FFFBA87983A0D2ULL, 0xB50304DE75564A7FULL, 
            0x5A509D2D408E6176ULL, 0x52466E665E14656EULL, 0xD886AB39C3AFDC11ULL, 0xEA46E47117D202D3ULL, 
            0x8068B6045A764E29ULL, 0x5380112F09A87F00ULL, 0x09290B46D8C99A4EULL, 0x5E71078F4398C756ULL, 
            0x1456FE0A8604BD3CULL, 0x5BE48B7AEE3816F3ULL, 0x074EB5D27C145F1DULL, 0xA2ED862972FE07C1ULL, 
            0x27ED1E6A4D087222ULL, 0xE184A773B067DD41ULL, 0x3235D7550381C25FULL, 0x9594677BCDE573F6ULL, 
            0x346F905149E6FCF1ULL, 0xA418004378C551B6ULL, 0x44B6DBEB86F03427ULL, 0x4E3385CA43DCD803ULL
        },
        {
            0x0C6AE9180BD42B06ULL, 0xEA5F082C39DB58A6ULL, 0xDB02EF7912A81525ULL, 0x02A6CC40D474B090ULL, 
            0xAD1B03D9D948E39FULL, 0x66CAFA428BD02EE9ULL, 0x246324CEA9C70A5AULL, 0x05FE7ECBA4AD2FBBULL, 
            0xD86F7AEF99002928ULL, 0xF6824196845E8E37ULL, 0xDE2DB02569C1845BULL, 0x307ADCC6E7FA7232ULL, 
            0xA47DE5A14335E643ULL, 0x715C15E1BE12815FULL, 0x89A27A42BB26DB77ULL, 0x33B9741C2C0DD5EDULL, 
            0x3F53C772CBE279CFULL, 0x16E883D9DF64E0B7ULL, 0x5F1A0A0288911CDFULL, 0x29E06BF4272EC211ULL, 
            0xAE251BDA673E5B13ULL, 0x3604F28204816726ULL, 0x1E6167FEAB3D5B5AULL, 0xE834633749F969FFULL, 
            0x480403456FAD1018ULL, 0x411137A90E2578B0ULL, 0x7BADA7D4ADAE2CA6ULL, 0x42BB370BA7E8DB05ULL, 
            0x132DAB3B70B0B6F1ULL, 0x73D2C71C1B15F658ULL, 0x691490DE7AEC6770ULL, 0xBBE08B6F51DFA37BULL
        },
        {
            0xD72CA6307A4FC973ULL, 0x2E1C99B7B01AFBF9ULL, 0xECEEBFA7CD712AC1ULL, 0xF12E5891D5613B3CULL, 
            0x8CD2A3389AB1E0E6ULL, 0x95D7425C2F0654A8ULL, 0x98BE5352A5251D31ULL, 0x8A269EB10697B914ULL, 
            0xDB98F220B2FB65ADULL, 0x7A74B86EF977A9B9ULL, 0x3B4564C1AF5F1E89ULL, 0x9046A9AE9F849AC6ULL, 
            0x710156584D8ED4DFULL, 0xB8D6550C0562045EULL, 0x1F5F73E282C623FFULL, 0xEF111E4079C65C51ULL, 
            0x1BEAEA7017488F86ULL, 0xFC6C20F5B37AA161ULL, 0x9154126E4F8E7C51ULL, 0x77EE0D82BD6D9D11ULL, 
            0x722002C1BE980AE9ULL, 0x2ACA3C1EE71F11C2ULL, 0x71B0F6DAC2A400C8ULL, 0xE0AE5AF0C1416E3EULL, 
            0x4C90727342643008ULL, 0x5E1B741D9839A861ULL, 0x953293D88506CD82ULL, 0x99D252DF796CA208ULL, 
            0x1725CA7A68BBBE5CULL, 0x0396D9262B045339ULL, 0x4C2FAC95F7BC9342ULL, 0xE55FCD8CB81DB9B5ULL
        },
        {
            0xD3C9E884D0CDEC99ULL, 0x170497A7EB2D09AAULL, 0x953B226712BFC289ULL, 0xFE22D05E3E5BA485ULL, 
            0xC695A6EB2012B1E9ULL, 0x9B6F2D128F01AED3ULL, 0xD56AE2701066C031ULL, 0xC5850F7FE0ACF25CULL, 
            0x1B86497BE85F16B1ULL, 0x7A0D23CE7FBB3338ULL, 0x05FD4307387EFC55ULL, 0xCCBC73F954C58009ULL, 
            0x000364281421597AULL, 0x05A102194C96A336ULL, 0xB378B7CB714B7145ULL, 0xB58D4E8312F8E572ULL, 
            0xD165D6AA69E5EA4FULL, 0x64E23D6F31A505EAULL, 0xA7D4658ADBEB4ACDULL, 0xCD495242D716955DULL, 
            0x76E57A37C3895D60ULL, 0x16B024ECA44E01AEULL, 0xC326A7670A56EDA3ULL, 0x40CEEA50ADB4D22AULL, 
            0x20D21FFF954C8B9BULL, 0x7CB2813E3E136B52ULL, 0xBCF7583EDF65DAFAULL, 0xD1AAAC1CCB4FCD7BULL, 
            0x12559DA78FFD16B7ULL, 0xCD47881206475184ULL, 0xCCD55EEE4F2F9FADULL, 0xC1FAF10FDB74FE9AULL
        },
        {
            0xE2E5E8AF3EBB03B2ULL, 0x88FB3DD48873B272ULL, 0x084C260D95867347ULL, 0x073A3E8E3D4BF399ULL, 
            0x5C1EDEC1F86D23ADULL, 0xB025A8FB87644236ULL, 0xA3CEF29490FE6D12ULL, 0x41EFBBAD8A31DE0DULL, 
            0xDCC1538A87A58670ULL, 0x608352A4E79E2AE7ULL, 0x8DFDB38E95CCD97CULL, 0xA212D15626619768ULL, 
            0x93F9176774DBA6F3ULL, 0x6E48A1873F6ABFA1ULL, 0x2F9BBADC2A4D5B3EULL, 0xFDE8DC15B7F9F774ULL, 
            0x2627FC25CAE518EEULL, 0x64F73634D84874D2ULL, 0xAC762D336E1C5650ULL, 0xC71807D28DDCA4CCULL, 
            0x73DBD07CF0FCFB6FULL, 0x46E4A501CA917062ULL, 0x88258220C98A76EDULL, 0x744C6F52CD729428ULL, 
            0x3ED497C5B887574AULL, 0x28707B086E54177EULL, 0xB70D413612058B2DULL, 0xCAEF35AD420F8261ULL, 
            0x5810A04838A7E49CULL, 0x225DB1F3F0E1421AULL, 0x7DBCEF57997FDAFDULL, 0xD201D124514FC497ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Rigel::kPhaseEConstants = {
    0xD6E056470E8CE5C3ULL,
    0x42707BEFDC4D1EB9ULL,
    0xADC522D5BE535381ULL,
    0xD6E056470E8CE5C3ULL,
    0x42707BEFDC4D1EB9ULL,
    0xADC522D5BE535381ULL,
    0x6DF12CC542B8F266ULL,
    0xC52800FEE22D4FA6ULL,
    0x6F,
    0xAF,
    0x5D,
    0x1D,
    0x60,
    0x07,
    0x77,
    0x0E
};

const TwistDomainSaltSet TwistExpander_Rigel::kPhaseFSalts = {
    {
        {
            0x49B2D12BB999313DULL, 0x3E573F370A9FF670ULL, 0x7BF02DBCC7BF3C93ULL, 0x2815C0B558A962CBULL, 
            0xD33B8F3768928E7AULL, 0x45F632F87DFB74A0ULL, 0x5F22F269EEA06144ULL, 0x50C6CF56275F2831ULL, 
            0x498F3240E5322077ULL, 0x877ECD215CA8E9F8ULL, 0x8DDD8FD6A10F6A54ULL, 0x43CFECAE0BD37CF2ULL, 
            0x6FB7B7B853886A6BULL, 0x4C460507601434F4ULL, 0xCEFE8B29E1D41C74ULL, 0xF784E8D627D3A381ULL, 
            0x7233B4C5EC18E99BULL, 0xFCA3E326A02AB883ULL, 0x593BA161CE8D3BA0ULL, 0xACF19F522F6FB37EULL, 
            0xE1D66D530142A098ULL, 0x28BE594FE634761AULL, 0x022CF31E189FE87CULL, 0x1FF3328F37D4B423ULL, 
            0x5FAC57EC040EEA63ULL, 0xC88E7C05AFEEF90FULL, 0x56457120A6E59438ULL, 0x2E8009BA473DD9E0ULL, 
            0x942EE2F1524ADEB3ULL, 0x5B695DCCD19A652AULL, 0x7B44340F02ACBE95ULL, 0x0CCFD2417EBEF90BULL
        },
        {
            0xD79F5E11A3C4A7FBULL, 0x29CBEC7A5E5D3311ULL, 0xB3F2BC2785BF5603ULL, 0x7B4F253C68CC32F4ULL, 
            0xA5A1DE6144EC4927ULL, 0x49831A5979C9F4EAULL, 0xE48015BEE44D3135ULL, 0x3203A405CA3F1368ULL, 
            0x67AE36DC72721A9AULL, 0xFD6151DA8C24E0C4ULL, 0xF7F5BD4B49DBFE5CULL, 0x4B0804673A406D26ULL, 
            0x0589D5B9187F2A09ULL, 0x55C23B2E07A69110ULL, 0x591605C859ADFC11ULL, 0xFF13F0CAE7EFF3F0ULL, 
            0x44D5AC59FA4B5076ULL, 0x5645E52DA1A0FCD1ULL, 0xFC4788C5D0D1F35EULL, 0x57A00CDFC87ED81EULL, 
            0x6C91D1C364DECA9BULL, 0x6DD50262784D4600ULL, 0xDEE284520849F265ULL, 0x9AD4B46735A0668DULL, 
            0x1584D74DA4BEC84FULL, 0x4A5238B7B378A3BEULL, 0x192B7B374F86510FULL, 0x07337F57B398D0F0ULL, 
            0xD17F7C400E5CBF27ULL, 0xBE79D7624F88F6CBULL, 0x06ED7A47032109AAULL, 0x918535ED4B925E8DULL
        },
        {
            0xD82CD978FF5E9ABAULL, 0x5EACBEB32324CD39ULL, 0x90CEC381E6F566AFULL, 0x92A0C9995BC8ADFCULL, 
            0x6E9F5FACFC84F989ULL, 0xD57A1948DF9DF8C8ULL, 0xC7F73B0CF1D40CDFULL, 0xA2328E9934B06767ULL, 
            0x0C0C0165EB100207ULL, 0xF23A2DA8606014EBULL, 0x4EC4AFE84419B8ABULL, 0x079761D39D527F61ULL, 
            0x730D1D3D4015CB94ULL, 0xF3CBE868A458E4DEULL, 0x9126E7053FF1F3CCULL, 0x467FF38518FBAB72ULL, 
            0xDCFE334F0FB6BEECULL, 0x2D8AD38185CDE695ULL, 0xD349057CD4E7DB3AULL, 0xDB845AFEE7FD6F5DULL, 
            0x82105539A987EFD2ULL, 0x7B6BB9C59E36377EULL, 0xA73BC48A6567819EULL, 0x53EF8AD7BC52A1B6ULL, 
            0xE4E2F3D4ED0CD299ULL, 0x1FB02299AA0A9ADCULL, 0x5CCEB81987DBAFBCULL, 0xF42BB1187F64AF8CULL, 
            0xB7D8A48DB9734426ULL, 0x3CD7B532574809CCULL, 0x4D0E3C85C490298CULL, 0x4E3A4B71E5D4E20AULL
        },
        {
            0xC54F9451A23E6516ULL, 0xBD19A1EE53912799ULL, 0x61EDC69EE2607AA0ULL, 0x60AAC0358CE47038ULL, 
            0x8A10EAF187A25CAAULL, 0xDC78E79B5AC3F8B1ULL, 0xF6D786422DEFACB8ULL, 0xAA7706CE1FD5CF72ULL, 
            0xC2EE0E8F4A8A1D45ULL, 0xA577F676DEA8EDE1ULL, 0xF9BB5052CA00A8C6ULL, 0xBA3B975AB5B8A792ULL, 
            0x032969FFA6E7D61CULL, 0x822B30D332C59DFEULL, 0xE69EAAF9CF6BF709ULL, 0x20D657FE26B2E4A5ULL, 
            0x26629E5D2F8B53AFULL, 0x68B518997B293D8CULL, 0xA09A1C2707C5DC9FULL, 0xCC73DC6B5C499C94ULL, 
            0xE5645D3C66755050ULL, 0x25AD434984410D92ULL, 0x927DDD1E0BD64AE8ULL, 0xEA9C71660482F397ULL, 
            0xD1C7693C7DC55142ULL, 0x41CB304366A43147ULL, 0x390984B1F03960B3ULL, 0xBCC837FE329EB627ULL, 
            0x1E3140B52A92E5CCULL, 0x66738D76332BCEEDULL, 0xF28EB01C7A865DFEULL, 0x22AACFCB1BE1A215ULL
        },
        {
            0xE49937E49A6B1B2EULL, 0x0B178A08F57C26CCULL, 0x147DC3AF0FE63AADULL, 0x989E3FE1F8C44706ULL, 
            0x33198FF13443EB9BULL, 0xA27B1051BDC65D0EULL, 0x7A95FB92474B9CFEULL, 0x39099C3896E08897ULL, 
            0xCCD5F36C9BB7758DULL, 0xCC656BE448A18EC1ULL, 0x391B1A92FFB56B2BULL, 0x3731075D9F525190ULL, 
            0x23CBF3CD2B124D7BULL, 0x18B48AC807190046ULL, 0x5941B96327AE82BCULL, 0x2F33587A85738A76ULL, 
            0xE8C34894B9620CAAULL, 0x88076D4EAD619352ULL, 0x20D41CA68BA9A71CULL, 0xFC1F2EDF9C15EB1FULL, 
            0x6A6F94B466FEA46FULL, 0xC7406A4226EE10CFULL, 0x0335038145589746ULL, 0xAB5AFDE8A3EB9196ULL, 
            0x8AA48E254ABB8A3CULL, 0x4BD44E92B26FE1AEULL, 0x04798C0E1A67FD2BULL, 0xC3D08572C3D0B59AULL, 
            0x46F93CDF689B32DFULL, 0xE1FDC223E914BF21ULL, 0x1A87397D41593187ULL, 0x6465931B70FE8AB2ULL
        },
        {
            0x27DE8FCB873195EFULL, 0x04F3FE22890B729AULL, 0xB4906A3039B0B91FULL, 0x047088A484A0822FULL, 
            0xE56336BCF2738650ULL, 0xAF11D1006DC26B31ULL, 0xB359757012084DEBULL, 0xAC0B08122FD4F1B6ULL, 
            0x85DA893C047A7903ULL, 0xE2EF4738312E85FAULL, 0x52A8AF01D500C1B6ULL, 0x186FDC8A4A992AB3ULL, 
            0x1BF3A33097214B1EULL, 0x5E066AB4B228E6EAULL, 0x01516CD6B8D96EABULL, 0x5A8A7A0E31AA9D5AULL, 
            0x474D5E697D0E7BCBULL, 0x97F3AA4EC54A5B6EULL, 0x13040C3CCA2FCAA5ULL, 0x627845504BA7E7A7ULL, 
            0xD23EE8AE9AECA2CCULL, 0xE8C85ECA6B390BA7ULL, 0x4C08055F320AB11FULL, 0xED943B2F8F874307ULL, 
            0xDD051DE22C3B8EE7ULL, 0xCB0AD974B70B6619ULL, 0xDC958C8509C8EE58ULL, 0x0BED0CE93BF2BE3BULL, 
            0xDFA8BA8BAE4E80DEULL, 0xA04AE35147E1852DULL, 0x2A922C8D15466BE5ULL, 0xE4B6A0B10A8CDCA2ULL
        }
    },
    {
        {
            0x6AD67A3CE1F9E282ULL, 0xD39CC6B3FE1AAC4DULL, 0xC55BB45283E5FEC8ULL, 0xFA0BF5478081CFC4ULL, 
            0xADE608047AC0A2C8ULL, 0x66B52BE96C1AAF4BULL, 0xA0479A10DF03C45FULL, 0x6E9B3707EF4597E0ULL, 
            0xD523C28CE10E3480ULL, 0x2C6903B8EC8278DCULL, 0xBDB43F795DB80BCFULL, 0x880626FFA155FA2FULL, 
            0x40599F7EA6F9918DULL, 0x03C82DAF9C65F702ULL, 0xD5EA85E3A7E829E8ULL, 0x7D4698080D2A501BULL, 
            0x22D3026513BD561BULL, 0x51A96221082F8EBFULL, 0x3D8D446A9BA6D920ULL, 0xC8AF7D1DFB09A099ULL, 
            0x3FAF2D0C82AB1DC5ULL, 0x6B89322E1ACDD81AULL, 0xF48D8FCE1C24679AULL, 0x4BE98D38FC8958E5ULL, 
            0x5107510E6F69EC2FULL, 0x68250ADC2F8A6316ULL, 0xDD64D885E6815E72ULL, 0x8A482F8E829E2478ULL, 
            0x8F5A729043E40DC8ULL, 0xE27EAAFAA5A2DAFCULL, 0x1C2170D9E41F901FULL, 0x4F51D4C25678977EULL
        },
        {
            0x84207C0548F16433ULL, 0x0AB016352F692A1EULL, 0xA13FD7311EE2D118ULL, 0xD5CE5BC104E7D505ULL, 
            0xDFEC3DE12E985C85ULL, 0xB3669F66A26CC523ULL, 0xE3FCB339CD4DDDBFULL, 0xAAD9C6E079A9858BULL, 
            0xCAB41177835B5E18ULL, 0x8B37445C35FF80FAULL, 0x6B3A2C23B2777C7FULL, 0x0F7DE1D383E33BB0ULL, 
            0x2CA75407B6DD0BC2ULL, 0x8CFAA78DF3E6C8FBULL, 0x4709048454B311E3ULL, 0x39D34D1727C5F4F1ULL, 
            0x0047F3D03B0EC1FCULL, 0xF308AD4F5245B8DDULL, 0x38E86C30976ACF89ULL, 0x28CCFF0C688CE2D9ULL, 
            0x3695D0327D3B0D76ULL, 0x430D68EA9BF6FECFULL, 0x5727C77FA3A07D03ULL, 0x1AA14C77FC483D1AULL, 
            0xFE0E42B841E576A9ULL, 0xE5D700D9BB7B8624ULL, 0x05C11DE981FDEC6FULL, 0xCD4C43BBA3041571ULL, 
            0x7750C18DF1FFDAD0ULL, 0xDB13BBB4955D6DFAULL, 0x642C843B79BAAFA3ULL, 0x917E236F2D00C4A3ULL
        },
        {
            0x546DF66FFFA9BDD9ULL, 0xA5D7DD6535E88A35ULL, 0x196498A0C70E64BEULL, 0xD43503026550A529ULL, 
            0xF44EF226E7FB0F1AULL, 0x94395E9F46397DD2ULL, 0x7F78C330889D8C38ULL, 0xA5BB4C14D075A66FULL, 
            0x391400FE88515273ULL, 0x59B1ECDA68ABE0F1ULL, 0xB3684B74B0E6A023ULL, 0xE053E2EFC6FF10EBULL, 
            0x16BECC238CBB3720ULL, 0x62127E90E1E8D512ULL, 0x6346CA4B8EEB0E4FULL, 0xFFDD805D3A37E41AULL, 
            0x7928BD8D048E5DFFULL, 0xD893CF4850A8F41BULL, 0xF775CD97221A66ABULL, 0x0461C2CAE3C35C7CULL, 
            0xA16ABA617EEB6344ULL, 0x7E653C8F51C455EAULL, 0xA9E4E979FAC3D0EDULL, 0xE9EFC7CD10645D4FULL, 
            0x53C3E81E36D5F573ULL, 0x7896950019C9ABBCULL, 0xEEDB9D5EAD9B38ECULL, 0x99F105511568D145ULL, 
            0x3B2F697A3AC28BF7ULL, 0x16F6635044E86555ULL, 0x8BF6415F4E61427EULL, 0x3B6C3EF471B2F06DULL
        },
        {
            0xCFD4B9DD79076A94ULL, 0x777C500F01EFC0A2ULL, 0x10EB0F8DB9852047ULL, 0xBAB132AC92074362ULL, 
            0x68136CD68B1B1A37ULL, 0xADF81D2893143E52ULL, 0x64998DF6EAE1602AULL, 0x7939D7722EEF93B3ULL, 
            0xD04B3B554D3C2B0CULL, 0x06AA57C1796D906DULL, 0x4E61016C5BC4D0A8ULL, 0x80015A25043C2FEDULL, 
            0x35268AAB731902DAULL, 0xD36748EAD0DF9348ULL, 0x73D6EADCF4FDFEFCULL, 0x9F7B94727444E9E7ULL, 
            0xB94A13FBD00B812AULL, 0xF65F63B0F3E5EBA5ULL, 0x31454A609ADA17D3ULL, 0xDC8EF0B5714BB56DULL, 
            0x7F3737F80ED960F5ULL, 0x390B269BD7861210ULL, 0x2A73601793BED96BULL, 0xD5A35F57EBBE5E89ULL, 
            0xCF718B6B001B7398ULL, 0xA3045DE95D296E6BULL, 0xCB01D16A8ECBEEDEULL, 0x8CFEFE84AC754EE9ULL, 
            0x5EEF54E41D2F3C40ULL, 0x442396E67786BCAEULL, 0xB22AECCC27C4B2BAULL, 0x131B59C6C8036B35ULL
        },
        {
            0x136F7E4219C9256DULL, 0xE5A3524EE7A2874AULL, 0x530BB8A3F1262110ULL, 0xBBB55BE8CD8C45C3ULL, 
            0x006067B3ECA265D9ULL, 0xFC358D509C3386A2ULL, 0x83A00D5CC980D2FCULL, 0x528B003FA3F426C7ULL, 
            0xEBD2881634A38C10ULL, 0x7EA2944571E5BA8EULL, 0x322D466DDC9A610FULL, 0xCE29D1AA6736BBC3ULL, 
            0xACFF4FFA7CCB675FULL, 0xD58134C2DB7E304EULL, 0x9E98DC40AAFA7966ULL, 0x8F3F71117029BF08ULL, 
            0x5975B64CF48FA0B7ULL, 0x51B3EACB8BF0E433ULL, 0x39F0DE5888A227E0ULL, 0xD8FD1687A7FF0C85ULL, 
            0xBD76073483B3C1D3ULL, 0xC69EEC075F51F282ULL, 0xB2D224BAE76F00E1ULL, 0x98F9EF658EA82251ULL, 
            0xB6E24230192D9F67ULL, 0x24BF4EAF20F6AA0DULL, 0x36580BBD0876344EULL, 0x4E3B9F9349D52EC0ULL, 
            0xC139C5B29A7DEA17ULL, 0xA6E13E5E707AF5A7ULL, 0xA166EC2FD56F0039ULL, 0xF91588EE2D6E0CA9ULL
        },
        {
            0x2825BC4C6B1B6BDEULL, 0xE6EBABD2C7BF8141ULL, 0x44D41B66F444BF16ULL, 0xFF0A13063DAC8CCBULL, 
            0x4BA4E8D5F5FEAC9AULL, 0x73EC021553DD7835ULL, 0xC4E2C0EC235E9701ULL, 0x6D581E2CE6971F17ULL, 
            0x83ED8106903DFC0CULL, 0xEA7CA6985985CB65ULL, 0x4EEC6058F29708F2ULL, 0x86A813647252B162ULL, 
            0xCFE74235609F1379ULL, 0x52E1AB0165F57EE2ULL, 0xADC4FA751FD47387ULL, 0x5C277E43A851C7DCULL, 
            0xA494E43032976076ULL, 0xEE14D300E00821E0ULL, 0x09128935F9612101ULL, 0xB2B139E620F298D9ULL, 
            0x5DE1CA51F7634910ULL, 0x2E4544FB368EFF3BULL, 0xE35C5C4B5D6D4B20ULL, 0x820BBDE38DEB6DA7ULL, 
            0x4E2AB1894298F958ULL, 0x8BB374C9884DFD28ULL, 0x77B852DFC7436BA6ULL, 0xB259B2358EE804F5ULL, 
            0x1CA5912290BE5764ULL, 0xF7078C7763B8B05BULL, 0xC4431D7C08788E7DULL, 0xD8FCCB8480EF529AULL
        }
    },
    {
        {
            0x78E780157F33BE48ULL, 0xB5435BC284EBB9ECULL, 0x6720CEC6CA297A89ULL, 0xE942D2EDFD8B088DULL, 
            0xB941A33E122620A2ULL, 0xD1036E56FE0BA868ULL, 0x2AD572E0014EB050ULL, 0xF6725737C6D36EEBULL, 
            0x3BBE165784B79012ULL, 0x65DC34FFD165E81CULL, 0x7645B32F4FE4228CULL, 0x55CA1FBD2F6C2C42ULL, 
            0x92D2893528D9F935ULL, 0xE4ED730FEF53E682ULL, 0x728EB802C79F2332ULL, 0xC72370DA00E5CC18ULL, 
            0xB6C39C4C71B45B64ULL, 0x06929EA1D8E68C30ULL, 0x5CDCC95ECB28E2FBULL, 0x355B8E1ADDE84FD4ULL, 
            0x8ECF9D92EF54A162ULL, 0xC37E0308A0DCA63FULL, 0xB75C735239383AD3ULL, 0x77ECFD06623F4F0DULL, 
            0x64CD77C4D7448FD0ULL, 0xF1CF1CCDD8F3FF44ULL, 0xC73ED79651B352C8ULL, 0x3F98CA34A22DB05EULL, 
            0x50E0BE2A44EC1320ULL, 0x405048E823FDE098ULL, 0x625027E79668A826ULL, 0x5FAD6F7B03D15DF8ULL
        },
        {
            0x2187BC903A7A25ADULL, 0x87EF2BDFDD78D83FULL, 0xFA937C86D7254A2CULL, 0x3B4211C6FA155C5AULL, 
            0xF05F6728555E2EAAULL, 0xE93C5FB2F66573A3ULL, 0x141CD60FBC105DDFULL, 0xE2C7012CB2771C5EULL, 
            0x58DC21D24417FD44ULL, 0x1CDEAB8B91D801CBULL, 0xA2EC34A63A665CFDULL, 0xFDE83DA26D510958ULL, 
            0xB2F84DEE6D164A74ULL, 0x14E7F13623EEC9F9ULL, 0x0CA8840647FCC6D5ULL, 0x224C7A09754B27A9ULL, 
            0xFEDCC554D94D7AABULL, 0x139369BDA58E2DB4ULL, 0xE192DD6706C54564ULL, 0x5E3CBE1CE77D615EULL, 
            0xE4A5EAB21D7607D3ULL, 0xC5749C742A1B9B58ULL, 0x34A13BBF05B98945ULL, 0x7C2404466B530BDFULL, 
            0xEB8A09AFD479354EULL, 0x0BF38541DADCE58FULL, 0xB34F8A00C11330E6ULL, 0x44D9DCFF85C96EE8ULL, 
            0xDC11FB33009FFBEAULL, 0x55BE46F27FD35BA0ULL, 0x8046C5F8B37F31CAULL, 0x66899AAC425DA576ULL
        },
        {
            0x47616E9C8773C62EULL, 0x21115B1A2FF044C9ULL, 0x7B3A23D59A6E287BULL, 0x7EACDA7EE86ED0A9ULL, 
            0xB151C08918A36D92ULL, 0xE0B1A007E7B6ECAAULL, 0x391F27E11CBF7ECDULL, 0x5A6B07F131AD18A8ULL, 
            0xDB96A79429ABD104ULL, 0xCF77D184CA276AD1ULL, 0x52CE02AAFD89AF27ULL, 0x0CBD2114EEBF92E1ULL, 
            0x99B8E193AB17C9F4ULL, 0x6E4E0A296C62D9DAULL, 0x54587CB37F5C0491ULL, 0xE849898545FCEE00ULL, 
            0x5CADB1FD08183FFDULL, 0x9222CB8A1FDDDB9AULL, 0xC39EB7F03C27C3A4ULL, 0x2834172F2FC6C8B8ULL, 
            0xA4A39AD8B713366CULL, 0x1D0ECD322080B7A2ULL, 0x372400A8AE1ECFB2ULL, 0x45FABE5FEF475FACULL, 
            0x552DE407489D3796ULL, 0xC371694B4685886AULL, 0x770965A665CF219CULL, 0xDF9C999FB33DE166ULL, 
            0xE3E61B57DC7F2E86ULL, 0x8AA4FEDA273006C3ULL, 0x07D1B651A9499DB8ULL, 0x23D15C99034C9675ULL
        },
        {
            0x18BCD2170B17E38DULL, 0x5E8142ED374A8379ULL, 0x60B377A58D6879ABULL, 0xCB08AEB598434B81ULL, 
            0x4FBAC73A254FC1A5ULL, 0x05363221B0FD28A6ULL, 0xAD9F0BE892D0BD28ULL, 0xEEFE49DC76AC7ED3ULL, 
            0xB0257174E57CA1B6ULL, 0x8B3333DFF0B3E726ULL, 0x862E1C7032EC8DD0ULL, 0xFABB52BFDC50B567ULL, 
            0xB6A0C2B2857FC39BULL, 0x52A6EB5B4C3BBCF0ULL, 0x1B4F5026D8E797EDULL, 0xEDFDA6890FAF3FC4ULL, 
            0xC46BDD2DFCE7E8F6ULL, 0x9BBA4604E500DE95ULL, 0xC3063DBBA0FBD71AULL, 0x53C03A4304C5BB77ULL, 
            0x33CC9735DD8D3581ULL, 0xF1AFF0456D5BF7DEULL, 0x2667CB268D65EC52ULL, 0x25EFB804B13B8009ULL, 
            0x573A37377C7D7AD1ULL, 0x37B7B53FECADB2D3ULL, 0x005ADAEDB459D132ULL, 0x799BFA7C1D730FF1ULL, 
            0xE276322B39E5BCE8ULL, 0x2602A5FB32625AD3ULL, 0x11089139051808FFULL, 0xDF877E3B4B2D3DCBULL
        },
        {
            0x01B437EFC0CDFDADULL, 0x4DA9E847D5D69C52ULL, 0xB46C123B41EB3DAEULL, 0x236092A0F8C16CBDULL, 
            0x2AD1F8970A633A3FULL, 0xF8348DBB40AAAC38ULL, 0x66BEE621FBB1B5C5ULL, 0xDDE3C1B639C106C6ULL, 
            0x83BB0E1A93E72E6AULL, 0x4C2FC7AD72E5ABCDULL, 0x00A85CC2FD2D1F84ULL, 0x42A87C2314F159F2ULL, 
            0xD86E6F5A21894BC4ULL, 0xE5A0F34EE2BC0E30ULL, 0x120EDDADC162EC8CULL, 0x067F890448ABD37DULL, 
            0xE68B5BFE5D4C0502ULL, 0x2FA3F0D543265D28ULL, 0x12A9C575835C36BBULL, 0xEEE43EE9E28C9034ULL, 
            0x855B06CFF39D6D66ULL, 0x3B5461699C9EAC30ULL, 0x5C8C99001771B048ULL, 0xB4C06AC1A1C7C597ULL, 
            0x194A3CCA6AD364ABULL, 0x1126A910089F96A6ULL, 0xE9C470F8C841D106ULL, 0x407FF343BC546BE5ULL, 
            0x3B141B4801182AC4ULL, 0x94CE40A693725168ULL, 0xBB3A96605C3CE118ULL, 0xB9A4C4D809E7D22DULL
        },
        {
            0xC65422A2D5CEE224ULL, 0xC3388528938937CBULL, 0x6BAA04457C025B2BULL, 0x18528FD8014D0F5AULL, 
            0x729771903EEF6AADULL, 0x015A01FEAE3987B3ULL, 0xC994E93C0DEC488CULL, 0x3686554026902D82ULL, 
            0x98D833E24DD980F9ULL, 0x8516DCEC52F57375ULL, 0xCA4E98F043B39A0DULL, 0x910D986B64798040ULL, 
            0x9B665644B23B6024ULL, 0xFC96336B8EDED686ULL, 0xD14CE3DCA80C728BULL, 0x22B1A8D596AF5AF6ULL, 
            0x56E7969458EAE962ULL, 0xDCC8296F524CBC91ULL, 0x0865C92ABE574B14ULL, 0x0994425A604C750BULL, 
            0xBFBDCD9BC7400EBFULL, 0x2A69E1B7F7D3E19AULL, 0x98EE41ED3DE4A051ULL, 0x9E6B4632DF0C8693ULL, 
            0x7315CF0BA0DBAF03ULL, 0x2DF0FDEF7D8A666BULL, 0x529358AB7E308681ULL, 0x03D80298804DB65BULL, 
            0x091D615D3677A0FAULL, 0x55B78D2526208C0BULL, 0xE5D1854EF9D4245CULL, 0xF4EA4B55963B7332ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Rigel::kPhaseFConstants = {
    0x38463C0D1673057AULL,
    0x37A9271627ECA004ULL,
    0xD0E9E19C3FAA30F3ULL,
    0x38463C0D1673057AULL,
    0x37A9271627ECA004ULL,
    0xD0E9E19C3FAA30F3ULL,
    0xE0C223F69D92892AULL,
    0x90B5AA1819F87AA1ULL,
    0x35,
    0xA1,
    0x5A,
    0x9F,
    0xBC,
    0x9B,
    0x49,
    0x7D
};

const TwistDomainSaltSet TwistExpander_Rigel::kPhaseGSalts = {
    {
        {
            0x0734C2374E673291ULL, 0x95E5FD56178ED0B8ULL, 0x0E85F98684F92430ULL, 0x4ADA4BC3E836DF12ULL, 
            0xDF703B4B2F0CE77EULL, 0x5B62DE992B9327AEULL, 0x7EA6570CA88F9C55ULL, 0x844BC0B4088676DEULL, 
            0xC5CD7195FB5B810DULL, 0xDC48251749E50CAFULL, 0x77211395FB407EFEULL, 0x8135FD0C0D18B898ULL, 
            0x5F1E41404D4C2929ULL, 0xAE55F966C37B6FA8ULL, 0x8E3C6BB8053CCD95ULL, 0x89C2BA0825393E3AULL, 
            0xD92244167C80FC7CULL, 0xCC08C6EFCAB8D057ULL, 0xAA515AB18A95AA1AULL, 0x1B8DD11D207E7B97ULL, 
            0xF3BEF6EDC845B143ULL, 0x9A3E3E126DCF1060ULL, 0x4F5891F5E4D092C0ULL, 0xD861AF86D5AA67E8ULL, 
            0xC735BC3C0FFD2A8AULL, 0x9BA1021563296C77ULL, 0xD88AC095EBB2C1CCULL, 0xEDC03B49D14D8340ULL, 
            0xC442DB1520C6EAC8ULL, 0x7201994AD0EA0BE8ULL, 0x94668624F342A7B4ULL, 0xA59C1734017587FBULL
        },
        {
            0x0C844900A635E115ULL, 0x8AA4B219EFAB94F3ULL, 0xAA539792C94D03E9ULL, 0xBF5D0F27323B8389ULL, 
            0x6FEE0B2BA90CD107ULL, 0x1275757E17FC543BULL, 0xEF672659C17AEC7BULL, 0x7D520EC88215FF03ULL, 
            0xD94E8257E0E3CB41ULL, 0xBFC4A8BE9B865E21ULL, 0x06EA69C4EBB9F178ULL, 0xC479975855954378ULL, 
            0x41D85FF5E2AE3369ULL, 0x65D152E3F845E13EULL, 0x94873974B4688570ULL, 0x35B3DF2FBD2BED41ULL, 
            0x8D3CD4F6395A6153ULL, 0xDAA89E8BC0B93AD9ULL, 0x405E4DA0F55C3CD2ULL, 0xF6980FBF8207F7F5ULL, 
            0xE3CADE2B997286A0ULL, 0x4CD755EB80B95BD6ULL, 0x3995674D068DD909ULL, 0x796787983698CFF5ULL, 
            0xD46CDC694F7F75ECULL, 0x339EF6E257223E39ULL, 0x62D865713917A5C3ULL, 0x890419314BCB4B69ULL, 
            0xCEA0D57698377A5FULL, 0x8EDADA22BDD3E493ULL, 0x1C1914F4259F27FCULL, 0x7F8D6E3F625FDEF0ULL
        },
        {
            0x11299804E0E1A5EAULL, 0x72CB0318FF5B3439ULL, 0x83C103BE50CE1BE5ULL, 0x277721686073F535ULL, 
            0xE9449B2557F52387ULL, 0x60030E9B53D681A9ULL, 0x494388E724061E4DULL, 0x29D6321FC33D5352ULL, 
            0x9E69B1FC13B7EAE8ULL, 0x5EC86EA22AAAE7BCULL, 0xBA1FAA3126282CD2ULL, 0x44880608C14A8FE1ULL, 
            0xB0520567BFEC9F10ULL, 0xD30BC3BBD6CC100DULL, 0x0314DB2321CD9C58ULL, 0x62678007AC7F148FULL, 
            0xF5031D79C05D95AAULL, 0xC2D2098BA1E19854ULL, 0xF92C4F8FA079647FULL, 0xF155CF88BF4C027EULL, 
            0x8605321DDDCB65C9ULL, 0x72069BF881982317ULL, 0x747CF23A324C3B49ULL, 0xCAC2C6188F5AE6CAULL, 
            0x7A690F2B13A88DC0ULL, 0x6A5D50BC00BBDC90ULL, 0x146B07FAF27FFCFBULL, 0x6ED6908FD614A8B6ULL, 
            0x156EA146BCE0F2BCULL, 0x9B7F1150FD5D0A73ULL, 0xEF7F3A2B78EBC7E6ULL, 0x6319B882A331125BULL
        },
        {
            0xBF36CEE29E06D818ULL, 0xF9A4DC5831500C7FULL, 0x38E889A713C45176ULL, 0x40E5D9A26CFD4360ULL, 
            0x188A9AE498CA9CACULL, 0xF1B452FB438E40C1ULL, 0x51CBD26ECF6B63E3ULL, 0x5C58973AF7277527ULL, 
            0x06C2A3B698C9BED8ULL, 0x6C7BF333DDEC45D0ULL, 0x9D6CF55B2473EFF9ULL, 0x6A4316172D866D58ULL, 
            0xDD384A48C7431502ULL, 0xF274019E877CA647ULL, 0x700AF52037F3B1CFULL, 0x896B682ABE13ECFFULL, 
            0xC7B83C7D8FA01F3AULL, 0xC983F1D69ED33871ULL, 0x0DB9883255B20BFBULL, 0x9E7189F6149743D8ULL, 
            0x7CD974DF56A1D3FAULL, 0x539DDA066657C955ULL, 0x8327968439E3D85AULL, 0x4741E386AEAFC272ULL, 
            0x35738D5357F2209CULL, 0x0A1DF5E6E38C6736ULL, 0x6D33B23C3758BE2EULL, 0x642477B240E365D5ULL, 
            0xA162785A1EAA2177ULL, 0x400F6DFE770A143DULL, 0x608C0B5A6C7D3963ULL, 0xC5B9D896788FCD4BULL
        },
        {
            0xC02A62CCB346E0C2ULL, 0x5ABB22FEB08C7232ULL, 0x6729F1C8172EFE38ULL, 0x701250286DA09924ULL, 
            0x5827CC7D56727194ULL, 0x875FD0082BD107A4ULL, 0xCC4651EB767091CCULL, 0x873FB1CCC6FC0B9DULL, 
            0x74AEB39D24361731ULL, 0x7712A17F6A2C9ACBULL, 0x9E1323A5E11C6D02ULL, 0xDE979F0FFEC1A297ULL, 
            0xBE51CC1E69CC38C1ULL, 0xABCF0A03FE519478ULL, 0xDE347952A68AD48BULL, 0xF7FDDFA2AEA7AF1EULL, 
            0x181F004A4C8FD640ULL, 0xE6887DE8AD9097A3ULL, 0x2714C62336F642FFULL, 0x36B2FCDCA3ED090EULL, 
            0xB0059AD46FCED7C0ULL, 0x2DA016398CBE2FB9ULL, 0x4CE6AC1193957020ULL, 0x490B9E21CF0CF839ULL, 
            0xB574C4D606CB29C3ULL, 0x596640C8908DE18AULL, 0xC1B77CEB843BF107ULL, 0x2806CB62B0111D48ULL, 
            0x266996FE06EFC383ULL, 0x4C0ECA60F355D642ULL, 0xE6739F72C90E99AAULL, 0x29D8F25D3C554AB1ULL
        },
        {
            0x5E8C2C7017A25777ULL, 0x26A676D1E0DEF5FEULL, 0xAF1310B4191DBE88ULL, 0x12919F3DABEAF900ULL, 
            0x2C00DD72D611AA92ULL, 0x82821852241D0FF2ULL, 0x0CC24C54BA6E7823ULL, 0x7468339F75237934ULL, 
            0xE96FDF0AAB7FFF1EULL, 0x4B1D35A25B3BE06EULL, 0x98C5827A631BEF83ULL, 0x11A919E3AD8CA062ULL, 
            0xC0734812780370EDULL, 0x928DD1869C1AFA3BULL, 0x47791CA474AB3AE7ULL, 0x53B8D69A25663BE2ULL, 
            0xCAE0AE1E04233ADCULL, 0x44D301C1D2BCF135ULL, 0xDD6984D379E559D7ULL, 0xA66BE7260B8EE3C6ULL, 
            0xDB945A41D73855BBULL, 0x3159B92F7C1D7CACULL, 0xC9C0DD21E03F6082ULL, 0x1A804ADE1D390EA8ULL, 
            0xD9FE9B15B9F3FBEFULL, 0x4205B483E515B84BULL, 0x3B5CD2057A84AA3EULL, 0x79B4EF1E82E54006ULL, 
            0x367ED5A84114B7C0ULL, 0x708D43F19B489AA6ULL, 0xB34EF38521755C22ULL, 0xE232EE68E8A8725EULL
        }
    },
    {
        {
            0x7EFA6F47C84C3ABAULL, 0x8FBBAA1E9729F5C8ULL, 0x3110D793943CA84EULL, 0xA5277B8ED5341FFBULL, 
            0x4BFD49809F31FEC6ULL, 0x5CDDB82BFFC70B23ULL, 0xE26570AC0F69DF5FULL, 0xBFEA8C579CB4DEADULL, 
            0xE8E6AF6792C551D6ULL, 0x1696FC7E3325336CULL, 0x80C80B25771CDB0BULL, 0xB4B18FFD6D16E3C0ULL, 
            0x6598A39B6933EE3EULL, 0x71BB10D355F7AFBAULL, 0x3F2932355B79F3B2ULL, 0x993F2476B9583047ULL, 
            0x9ACE788B2BA16488ULL, 0x06926685ECFBFD37ULL, 0x922D013549132000ULL, 0xEA36C71D16A24F44ULL, 
            0xC84638A31D270C24ULL, 0x879362E75AB187B1ULL, 0x241DC9B1E330C083ULL, 0x894D0E8002D64070ULL, 
            0x172B8488BF1DF4E8ULL, 0x0735A5CABFA016DBULL, 0x6039A5B04E0E978DULL, 0xB9B8077140AEDA53ULL, 
            0x35B9F0FB29A42922ULL, 0x5E20F3132D913D00ULL, 0xFD1391C6C1FFFDC1ULL, 0x059D2E6B105C3529ULL
        },
        {
            0x21185F13F9AE1B8FULL, 0xB645818AAB207275ULL, 0x305B4956DDAA1D21ULL, 0x7D0807BA375C4E3EULL, 
            0x7679AF949DBB20F2ULL, 0x356FE76FC43F38C7ULL, 0xE99242DA3A6BB3CCULL, 0x858A8DF6D6E1BB1EULL, 
            0xA3F63B39AC601D89ULL, 0x050DBA3C3CD5D207ULL, 0x14E653ABB5318F07ULL, 0xF7FC4F9D19EABDBCULL, 
            0xA87E8D056E4A0BDCULL, 0x53A30E0BA1C411BBULL, 0x501EAB1C6986B43AULL, 0x02D1E06C9D42EDBEULL, 
            0x6B394D1176C166ABULL, 0x3185D63F73073F8BULL, 0x31B5F48317343F52ULL, 0xF65F7AA1A11F8B60ULL, 
            0xE364E5B8BB9B629AULL, 0x02C17628341A163FULL, 0x152A5732B106D4A3ULL, 0x534C0FC81CCE56B1ULL, 
            0x69581D372BA8DD65ULL, 0x93F950485BD6055DULL, 0xC04ECB514528B882ULL, 0x0D060C50CE4651E2ULL, 
            0x34A95045CC98D9E5ULL, 0xB4D33834DAC0AB17ULL, 0x8CF728601916E51CULL, 0x0AE37218632DAA7EULL
        },
        {
            0x458B2003C845D2C4ULL, 0x375079DF2A311E72ULL, 0xFCAB82D1813EF0B9ULL, 0x64DA595E134B2B08ULL, 
            0xD777C896BBA77060ULL, 0xB55BE0DA0AA920E2ULL, 0xD3A5E85A5F9D3DE4ULL, 0x731864A4ECD9C41DULL, 
            0x2B2E49D1BAA3A88DULL, 0x3610CB19DA675F95ULL, 0xBDCFABFA7F5BE5FCULL, 0xB9FA7AC87F178F08ULL, 
            0x8F1D0C12702A405CULL, 0x0D860CDF8DB9C963ULL, 0x9670E21EAA2EFCC1ULL, 0xD3A1CA72196B57A4ULL, 
            0x89047F8679DF2160ULL, 0xC753EC676CB04740ULL, 0xC4A4C32FB9606B69ULL, 0xD9091D39A8B40074ULL, 
            0xA5A2E175AB208804ULL, 0xAE937B62EADC09E0ULL, 0xF5FC504659847008ULL, 0xA8CA4ABF44978E83ULL, 
            0x1F53ED98E157F148ULL, 0xBAE0951FD8BBCBB1ULL, 0xFB048BE3C029C5C1ULL, 0x3A9004147C371AABULL, 
            0x747D874DED498B15ULL, 0x45E7B6AF4914179CULL, 0xAF0260E4D7EEF1A2ULL, 0x11F41163906CCD32ULL
        },
        {
            0x0EE3E66C7A1F0541ULL, 0x254C927B33695253ULL, 0x2691833BB253B274ULL, 0xEAA44642C29FFF00ULL, 
            0x995A5C6DFA7D70CCULL, 0x7FB558AA1953DFE5ULL, 0x9C2C00DFEB7C2822ULL, 0x879FF25CD741A62FULL, 
            0x2552587D24FE0BA6ULL, 0xA75FA6608B55D7F1ULL, 0xEF3B59DA6B93DEE5ULL, 0xDE485AB7465129F8ULL, 
            0x62CAF55E481C006DULL, 0x97B21E6F3297ADF6ULL, 0x87450F2712C2CC49ULL, 0x361D927DE6E7B6EDULL, 
            0x42DE30431D7C9EF7ULL, 0x45745D3A9F318810ULL, 0x8F65C881827E2A45ULL, 0x1783AD578022AE2DULL, 
            0x8D119EF231DAA957ULL, 0xC8DF269C664BB796ULL, 0x8621FFE1ADC16BF5ULL, 0xF1588E6127D42306ULL, 
            0xD039A31F770E32DAULL, 0x9F05C401A2006684ULL, 0x1927CF44BE08797DULL, 0x6FBE5CAEB1669E44ULL, 
            0xE13A292A4766E6CFULL, 0xDC1B0DB4636FA696ULL, 0x9221B72AE3D498EDULL, 0x488490D8C5D084D1ULL
        },
        {
            0x23EE698D27F96883ULL, 0xA087D4895FF95607ULL, 0xD9F753DB10A9E063ULL, 0x6E595A46F21B0162ULL, 
            0xB9548B95EB30FBB1ULL, 0x392C41F95208ABF1ULL, 0xA5D4B667BDF1E2BAULL, 0x9B0CB7A869D7D933ULL, 
            0xA5237EFD8A3D7BE3ULL, 0x7CDA18AD039A6352ULL, 0x05D1381F76746688ULL, 0x0ACE41EC13812E24ULL, 
            0x96133989F7615E62ULL, 0xC7C42C7A98550B28ULL, 0x943CD59CC5E6BE41ULL, 0x3AFED79F423EBE27ULL, 
            0x3308A6C93D5B67DEULL, 0x1CB739D0ACB6C371ULL, 0x1A503AD6AF07A188ULL, 0x84AEDE8E7C6505CEULL, 
            0xEAB54F9A747C7A10ULL, 0xA284D92E5A3B8A99ULL, 0x152F1F778773D439ULL, 0x14FF03DB181B07D9ULL, 
            0x2A5511ADF5AF8654ULL, 0xE3AB1392EC3ED2F2ULL, 0x3989D7D2D3DADB20ULL, 0x792A1F2DBDF0630EULL, 
            0xA9F3A863C06AAF58ULL, 0xBC08D6FDB2C49710ULL, 0xAEC246F701EB1966ULL, 0x9C752CC83784D59FULL
        },
        {
            0x54D46FE0685B8133ULL, 0x9B73B25BBD888895ULL, 0xBCB7901B8BB87BE3ULL, 0x8B08BAB0CFE3BBCDULL, 
            0xEE55D724FB7331ABULL, 0x78907A914F9CD271ULL, 0x2169EE63BA72BE80ULL, 0x3323D57CACFF27AFULL, 
            0x691E5CE7CE488B06ULL, 0x83FCCC120EF00567ULL, 0xA46E95D18336DF3EULL, 0x2EDE11DB9CE2D6A5ULL, 
            0x1AE3AA5C6ED76A89ULL, 0x029724FEEA640178ULL, 0x691B58EBDF1D88B8ULL, 0xE5712265FEA739D6ULL, 
            0xFD40F264517BBF17ULL, 0x8B3C2C13268FD3CCULL, 0x8E298238BA9FF1E7ULL, 0x158808A539D156F0ULL, 
            0xD0A23EA8EF36A7F1ULL, 0x595F9076C4FB3A84ULL, 0xC0B007486ADBB436ULL, 0xE3B7C89A611B9A9EULL, 
            0xEF8FFBFC6B7258FAULL, 0xDDCF83E4094A1F30ULL, 0x31840D227618DE18ULL, 0xE402D432B4F9269EULL, 
            0x5CF972FA2F078BB9ULL, 0x75221AEC231CA88EULL, 0x01A44496906661C5ULL, 0xA7BE8F0A1123368BULL
        }
    },
    {
        {
            0x3D6C86EA2178D3A7ULL, 0x839A52AC5675ADC1ULL, 0x6C5F9E8830D8E631ULL, 0x0828C11EACDD1EF5ULL, 
            0x0116CFD66987E071ULL, 0x384DC97B428208CEULL, 0xAB74146BA1542E6AULL, 0x6FEFDB618EBDF465ULL, 
            0xC1B0894387FCEC66ULL, 0xC395EDFC0F3FB588ULL, 0x2CB4B0B379D37A39ULL, 0xAAE5EB232B23936CULL, 
            0x213F9C53BBC320F9ULL, 0x6129A5923B7317CBULL, 0xB52552546C1CEE3CULL, 0x4C305EB068874684ULL, 
            0x96AC20AF1A5950B8ULL, 0xDA9A356AB551C641ULL, 0xC090617A470308EDULL, 0xBA92948F7DC9D819ULL, 
            0x71B7EA7296017699ULL, 0xD4871580CC04F695ULL, 0x6E0174AABE98A85EULL, 0xE419799D14734827ULL, 
            0x7C27E07715E8C3E6ULL, 0xD91DA56D9B89A4DAULL, 0x71393ADBBC2E993AULL, 0x83B9DAC78454E964ULL, 
            0xCC977332896A134EULL, 0xC47ED575E3362623ULL, 0x8C54ADD98B0560FCULL, 0xCB51C496BE06CD56ULL
        },
        {
            0xEB20FE417B0DD746ULL, 0x98DFE6BA164103C4ULL, 0x5C995B3ECC28D7A9ULL, 0xD3067F32245715F6ULL, 
            0xA243CE753C855A76ULL, 0xEB6FBC76F28F826BULL, 0x7CE69DB2DA504850ULL, 0xECD62458C808BE4AULL, 
            0x7A17C7640CB90940ULL, 0xAA379E8D3AEA37B7ULL, 0x42C8B1761100ECBCULL, 0x5F30784B4E892D78ULL, 
            0x56EC24F73B49D205ULL, 0xC48C78D0EE03CD88ULL, 0x495617EDCA4844CDULL, 0x5952F3D19FE1BB91ULL, 
            0x951CE4D4190B28C7ULL, 0xF44464E2555CFFF0ULL, 0x8F97C8D922508142ULL, 0x1330DF1041D3C54AULL, 
            0xFD226769DB8B845AULL, 0x7606FEE7DAEF4DFCULL, 0xD1FBC7FB366F3016ULL, 0x55F1BACBF36EFB37ULL, 
            0xD87BEE0496A2681FULL, 0xB51D14EC21949950ULL, 0xB488B128816BDB1DULL, 0x3A704310A269DE68ULL, 
            0xF8581E4A0AC07E11ULL, 0xE244D7A1C0CC9A1DULL, 0x409454C06690FD12ULL, 0xB32B668DE1F63D6BULL
        },
        {
            0xA482B8709CF72FDEULL, 0xB18843D048DD3DD7ULL, 0xE66430A945AC4783ULL, 0x02950072470227A9ULL, 
            0x6F94464F22CCA9E3ULL, 0xA2B9CF9F18D05A5CULL, 0x957D2B1499573A18ULL, 0x8E9EDE4BEEC2740FULL, 
            0x2BB3CEA380518AB8ULL, 0xF510222E90342685ULL, 0x5C53573FC464339AULL, 0xC0A230E4CD9C650CULL, 
            0x5F0319FC71BAC4E6ULL, 0x74AEF672F62B913FULL, 0xA0FA6EDF237CDE90ULL, 0xA2A60E63825DBB8EULL, 
            0x9522EE73BF96FD1BULL, 0x370923F7DECAA91EULL, 0x1CBBA3F274B99294ULL, 0x88DA6EAAFE98DDA4ULL, 
            0xC9FE2680479D03B1ULL, 0x18CE521A804820E4ULL, 0x129B214F7E4142EDULL, 0xBA4CABD9F1F2A0D0ULL, 
            0x3FD58731E8737BD7ULL, 0x0BFB08356489E308ULL, 0x7A784B7CECF55585ULL, 0x0B0E0FB850752757ULL, 
            0x798278640539840FULL, 0xB85FEE896E05F509ULL, 0xE5CCC7A609A562E0ULL, 0x6CE9A9C0B05BA7BAULL
        },
        {
            0xFEAB485B9848CDADULL, 0xF461B46B68891B47ULL, 0xFE0DCB5BE03DF168ULL, 0x5578B1A72F67D397ULL, 
            0xBFC5237EF9C7A859ULL, 0xFD9F9ABA0CDC7A45ULL, 0x54F56858280713FEULL, 0x842AB5368DA5D249ULL, 
            0x6655903DD669DC27ULL, 0xAA6B3A90BA53179BULL, 0x2D259BEFA979C67FULL, 0x06537713B5E75FD6ULL, 
            0x85DFEA36BA52352DULL, 0x1A7447F43815BEADULL, 0xCEB68C80C4B70E88ULL, 0xB8D064F5C7F2B9F9ULL, 
            0xE1D8665391FCCAC8ULL, 0x7E22F3D28785D419ULL, 0x99B021373E39FB9CULL, 0xF415B981B30A5D17ULL, 
            0x29CBB99D54FF838CULL, 0xCF0249738A9C0628ULL, 0xD7BBA4C2E0D421DAULL, 0xEB285AC08FB81DDDULL, 
            0xCEF306DFE4D0C880ULL, 0xE49E7C60C5743AB9ULL, 0xC08F43F72B5EEE6CULL, 0x42ABB8E89806D864ULL, 
            0xD41D4106742BF6B4ULL, 0x29DD860270BAE983ULL, 0x4761ACC7DAB88F26ULL, 0x225ACC59B6DE0280ULL
        },
        {
            0x7DF4414A3BE8A322ULL, 0x4F340AAB950CD4BEULL, 0xF40ECA49225ED402ULL, 0x9D155AE0EC6F0731ULL, 
            0xF8A56C8F3E8F53ADULL, 0xD3F47B94A20017F9ULL, 0x1DD9C50373001619ULL, 0xDA76E93DA1EEFAC0ULL, 
            0x7F21016CE15561D3ULL, 0x291088DB988EB584ULL, 0x0C11352942F843FBULL, 0x4C2CBDCE1EA8B7EFULL, 
            0x48A360E31669BE82ULL, 0x4270FAF42C7D2A1EULL, 0xE00CD061EE2596D1ULL, 0xAB6CC9CA3F669303ULL, 
            0x9BC047172FA83C0FULL, 0xEB84316911A119ADULL, 0x36E91196BE66EF3BULL, 0x42FBE6BB8FCEB93EULL, 
            0xBFE85E01539959FCULL, 0x797159CEDD5F16FEULL, 0x0D90CD27E1EA2656ULL, 0xF31EE101AE8EF86BULL, 
            0xA06F5AC4A667E100ULL, 0x9626B2E83054BC01ULL, 0xD70633A0506A6E40ULL, 0x2AD9CBBB13110D2BULL, 
            0x6C2DE0D88E0699C2ULL, 0xB4A8CFD303DC0101ULL, 0x7A70EC5A01F89C3EULL, 0x51CFE679D3922258ULL
        },
        {
            0x9CD03FDFC07DC8DFULL, 0xFA1A970B5DF1C6A1ULL, 0xB3250AF0FB4372D1ULL, 0x4F979D8362B303F9ULL, 
            0x27651E907FF8D3DAULL, 0xD299FB036DDA8E79ULL, 0x18A0A1D0A3259E51ULL, 0xE47EFFC414834D47ULL, 
            0x8FD8C0682E46F0C6ULL, 0x14750DBE91FED6F9ULL, 0xD02061EFF0E320A5ULL, 0x48078F1167D8A857ULL, 
            0x3228C53E77984F68ULL, 0x7AC2C8BCD439CF86ULL, 0xDF6A2618B22FB064ULL, 0x049B9AAD4170882CULL, 
            0x4979D154B0E0146CULL, 0x16F32C45630F1B45ULL, 0x90CCF51D415A637FULL, 0xCAEB8EC8BE94F418ULL, 
            0x6E4B7A7465B0AAE1ULL, 0xAE947D91CF436BB9ULL, 0x67E38DC900B168C2ULL, 0xADACBE1C86025F3FULL, 
            0x240994F656E12945ULL, 0xB176EEC5A485E9F1ULL, 0x130D1A2524315036ULL, 0x42F9005EA8A7735FULL, 
            0x26967EC634DF2B11ULL, 0x40F89932CA607C92ULL, 0xC990BC111FD53D57ULL, 0xE3ECDB2448944047ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Rigel::kPhaseGConstants = {
    0x6BBA97775DBF72CBULL,
    0xFAB591079AFE08C3ULL,
    0xE8EBFA73C73B82D6ULL,
    0x6BBA97775DBF72CBULL,
    0xFAB591079AFE08C3ULL,
    0xE8EBFA73C73B82D6ULL,
    0xF208B0286C0B8892ULL,
    0x209A0277BC1B4690ULL,
    0xBF,
    0x83,
    0x6F,
    0xF3,
    0x8C,
    0xF4,
    0x9B,
    0xB0
};

const TwistDomainSaltSet TwistExpander_Rigel::kPhaseHSalts = {
    {
        {
            0x41E8FFC8E6259C2AULL, 0x7A8381224F662A0EULL, 0xA290D3787AF949F6ULL, 0x7CE67178B76733C4ULL, 
            0x1F44644621802F7FULL, 0x66CE9B84B6C9548CULL, 0x8C7FDA07298435A6ULL, 0xE41B8C479482F843ULL, 
            0x43F3F26250EABE83ULL, 0xAA82C0912D493C1CULL, 0xC7B979A45FFDA592ULL, 0x5E4424E657814FC9ULL, 
            0x148323D9E328EA1DULL, 0xE26744186ABE89A8ULL, 0x734DE8C2250ECEE9ULL, 0xB0E3F946B167984EULL, 
            0x5BE1F441A3AE34B8ULL, 0xE162C3E5346C1DF2ULL, 0x6A96C3FBCDEDEC97ULL, 0xD44A23145E27ECFFULL, 
            0x6599961C4F14FFD2ULL, 0x905BFE635F1A917DULL, 0x621228AE4B51E70EULL, 0x20EF0BF7B0617DF0ULL, 
            0x50B669B7B3400C8FULL, 0xEE234DA6D079AAD5ULL, 0xD934428A3EAD4046ULL, 0xDE82708F4C291BD8ULL, 
            0xFB9C433AE272B50EULL, 0x6FE408F617996434ULL, 0x656B8889C9890A2CULL, 0x136F2C35E8D18B4CULL
        },
        {
            0x7434F590A5665374ULL, 0xF2073779E692B1CFULL, 0xE4E46A01DE5740D7ULL, 0xB32594C97B120CC6ULL, 
            0x2DDDF54E49902C1BULL, 0x6A4A7E0217B4993CULL, 0x76D3AFA544E7CD8BULL, 0x5D022ADE36AEC694ULL, 
            0xA59A7C54C567EF3FULL, 0xEDCE6BB05E97EE9BULL, 0x048169885C58C2A8ULL, 0x79A5338A83B5ECFDULL, 
            0x7F5FF2E9EEDBF2D1ULL, 0x966C7CB626649007ULL, 0x0D8A9621D9369610ULL, 0x082FCD2F8351E273ULL, 
            0xF4EB2D8E5A33AFA9ULL, 0x268CEF462C43AE5CULL, 0xCF6651C35238F5ACULL, 0x7331852BAA625D96ULL, 
            0xC62EF5E1425AD73BULL, 0x66B41DB23BA5E048ULL, 0x43681CD10CF623A4ULL, 0xF342F31A68603310ULL, 
            0xB71882B8C2E92508ULL, 0x217E7864788368EFULL, 0xD2D034340F3ADB1BULL, 0xC656A0DE84FF7C70ULL, 
            0x1ACC74ED7CE4EF39ULL, 0x58A0D3C4E6E4556DULL, 0x65A3461B69CB1258ULL, 0x594EB106EEF74CEDULL
        },
        {
            0x9B0C57696BCC0D42ULL, 0xD29C5A711EF61E1EULL, 0xA234D9535B276325ULL, 0x65977A3389CEB265ULL, 
            0x75F131E8D282E7CEULL, 0x47454D7F01CBAB53ULL, 0xD48CB4A8992FFE8CULL, 0x5B8B3172B51BB60BULL, 
            0xD74FA9CE6356A1C4ULL, 0x3391FFE9BAF0799BULL, 0x692AD708B541ED8DULL, 0xDC5F4B5C667B5161ULL, 
            0x625A3E690E3F04EEULL, 0x81CE716E3CC10792ULL, 0x239FC836D588DD08ULL, 0x9E1848DC42343187ULL, 
            0x8C828AC133365260ULL, 0xDCA4AFE0501F5898ULL, 0xD0D48174E5E53519ULL, 0x945DD8C784C8E856ULL, 
            0x3FA423E7B527694DULL, 0x3BFFFD95623F7CCEULL, 0x4CA96ED1235BBD8EULL, 0x09403B00D0414A36ULL, 
            0x90D43DE38263B146ULL, 0xDCF46D0CA20FCB79ULL, 0x49911E70CDDBBB0EULL, 0x6BD648603D50BC81ULL, 
            0xD13A901CF96038CAULL, 0x93D64C23A6D81385ULL, 0x712AFAEB8CB50464ULL, 0x2E72DCBC3BEC2D37ULL
        },
        {
            0xC6DD5AD63D774244ULL, 0x147160FEFD4492BCULL, 0x60CA23EC9E677F4BULL, 0x75CC4591744F5EF9ULL, 
            0x26260EEF4AA37CB9ULL, 0x29830EFD880B7F80ULL, 0xDD14426F112FCFCFULL, 0xC068A3C9A0344BA3ULL, 
            0x0F8B08293C1673E4ULL, 0xAAB00DAE49989325ULL, 0xF715B8C1DA6ED348ULL, 0x0319AB2CC3CD09DCULL, 
            0x8D84CEFAAFB64A84ULL, 0xC3F570611DEAC063ULL, 0x31BC0646A34DC08DULL, 0xD85A57044979B9B9ULL, 
            0x53DD9639409D9FAEULL, 0xFA8400050B7B0C56ULL, 0x0BC831B6A837EB11ULL, 0x23E2261A03D82455ULL, 
            0xD811257A2D39431AULL, 0x9E546FE83302B16CULL, 0x9C51E380BBA5A853ULL, 0x52239ECDF7FA8373ULL, 
            0xB32E3D178D3C74D8ULL, 0xC2D3FE8D84610FB5ULL, 0x1AF89C310C01DA4CULL, 0xDAC5AD831E096CF3ULL, 
            0x1DCC05392C9C7488ULL, 0x2FCF5FBF58BC3ABDULL, 0x784E0DA5941F432AULL, 0xC563270F89EFB3A5ULL
        },
        {
            0x0F106CD6365A55F5ULL, 0xAD0838ED61023404ULL, 0x4E0F6587B0A64386ULL, 0x24F07616146C44E3ULL, 
            0x479CA15E45CE1BBCULL, 0xF55456F86647AFE0ULL, 0x9DD70611395B1D1DULL, 0x470DC99AC65F3B15ULL, 
            0x643533AE5446F4EBULL, 0x82D3EE6ADB41CEB4ULL, 0xC3D28086137396BCULL, 0x1D724C790887B752ULL, 
            0xCC3E17D3EEB590FBULL, 0x4BC9F42A61407B43ULL, 0x3F1A1DE5C57A7535ULL, 0x3A54457E6E1B5EB8ULL, 
            0x707F6AAB3E13E5C8ULL, 0x45707F2AD80BB9F7ULL, 0x1AC2D328E295EAEBULL, 0x0A6E906225F06B39ULL, 
            0x5D660984D9ED1861ULL, 0x39611271913627E7ULL, 0x4EF14FB063A72654ULL, 0x2F754CDA0801362CULL, 
            0x57039707AF941D81ULL, 0x69DE02F76A4A3D75ULL, 0x961250F80ED46799ULL, 0x0FDFE04FEEEFBB0AULL, 
            0xB5426D61D59C4D36ULL, 0x6D213B1E87DDC82FULL, 0x7A976E122442A0BAULL, 0x311F8F90B8A29F72ULL
        },
        {
            0xA21F57354425968AULL, 0xAC61F468DCEA47F9ULL, 0x9F0A9D1062A7AD7DULL, 0x6183FC69C28B325FULL, 
            0xC9D8729F1606AE9CULL, 0x7FD9AC101A193892ULL, 0xCFA91E104542CF58ULL, 0x7A5BBA64272C7C06ULL, 
            0x3370DFDF8A04161BULL, 0xC51519444614EC0BULL, 0xC535422AC77C1A57ULL, 0xBA1876E41C931BC5ULL, 
            0x2675D84893B2ACFEULL, 0x0069645C2F47392DULL, 0x57C555E7A7794B8BULL, 0xF58283FCC33C8058ULL, 
            0xACF0C23FF309AC3FULL, 0x9886A4749E9C040DULL, 0x7DA7F8140DF1946AULL, 0xFA9D7C15FA0366FFULL, 
            0x3C17C4F270403D46ULL, 0xB0194A72A24CB8FFULL, 0xB6B0158D4EF83361ULL, 0xAA59C0E1CF6F4835ULL, 
            0x4FEFCF18D76BF68CULL, 0x9E6C4C6C6D56889FULL, 0x38A299A994F2C000ULL, 0x8D42B5CED0119D77ULL, 
            0xB5AB0B8550003988ULL, 0x33F15CA7831D8FBDULL, 0xFD6164DAFAE76C6DULL, 0xA5525299F66D6DC9ULL
        }
    },
    {
        {
            0x1067EDECD9E7B336ULL, 0xE1E463906A315914ULL, 0x9048C8755437625AULL, 0xBC20827EFFDAFA4AULL, 
            0xF4F1306EC696FA10ULL, 0x18457067C4B174D0ULL, 0x409863B55254FA8CULL, 0x988D24F76EFF6F24ULL, 
            0xE135AFD5F92AC931ULL, 0x54399E00F1696E07ULL, 0xCD5944A53C5B24ADULL, 0xA57583FDE3F9F4A4ULL, 
            0x09B8040EF49A3C4AULL, 0x067EAC860BAD3A45ULL, 0x78C76ED79A7256CAULL, 0x982CCBA6E56194ACULL, 
            0x13BDEE46D16EFE35ULL, 0x6E8059E876FC2004ULL, 0xB6F8CC56BB08EF7EULL, 0xB7964CCF265CFFB6ULL, 
            0x1B3FD1C20A80E748ULL, 0x74C15BFAB428FAADULL, 0xB50F9DD069B96346ULL, 0xEC6061BE01FE94AEULL, 
            0x5E86BC4A0AD246C6ULL, 0x714412FC07364D46ULL, 0xB33306157B9FF8CCULL, 0x66BF6E642DC9E229ULL, 
            0x4650785F492CF58EULL, 0x357B361099549B9FULL, 0x3F395F56AD165A75ULL, 0x88817D0B4085679FULL
        },
        {
            0xA1645D6EE765E19AULL, 0x7F1218ED06563143ULL, 0x63AB6CED463E2B3DULL, 0x26C2579BD7247B56ULL, 
            0x7893896422DF1235ULL, 0x1A2B29DC2599602FULL, 0x08BF6A5483FDB4F0ULL, 0xE83156CBC24B6E7AULL, 
            0x6D03B8553A8B6A33ULL, 0x73ED29732AB0A4D4ULL, 0x934314E2C0FEBCB1ULL, 0x81F771BEA58887A7ULL, 
            0xEADCC79CA7E6C523ULL, 0x50966B2E42449967ULL, 0x96A89D9B2CA8A022ULL, 0xE6CADCB8C2644D09ULL, 
            0x08AD7DCA99E3BDEDULL, 0xC68DA5E5BA993996ULL, 0x0E87E8126E421CFBULL, 0xD3C47C52AD6E7E5CULL, 
            0x2497D8205F73E643ULL, 0xB8B1E191D5456836ULL, 0x2790951AB0F765F2ULL, 0x366925349FC8308BULL, 
            0xF51C616A446F280FULL, 0xB679C1BDD16F7BC8ULL, 0xF622600D8AA0CCA6ULL, 0x9AE61709082204C8ULL, 
            0x116DC9185C9F4182ULL, 0xA8C27702CF1B3838ULL, 0x14577869BB5E23B9ULL, 0xE08027E9B68DAFE1ULL
        },
        {
            0x1AFD9E36664CEBD5ULL, 0xD88C42995D56B21BULL, 0x7478A6CE0EFB484BULL, 0xBCA7A567DE0DAC62ULL, 
            0xE9F94086B63B87D4ULL, 0x6FE5A40A6E5FF575ULL, 0x6A1FEA68530CDEECULL, 0x09460F5DA72202F5ULL, 
            0x7B5E78484D3C7CE8ULL, 0x5EA30B0F4A4F0017ULL, 0xDEB7D3B79E7171B2ULL, 0x506338ED88314383ULL, 
            0x573FFE242BD86B03ULL, 0x74A26FEA8F844ECAULL, 0x475568D37DC38420ULL, 0x565783AB27443342ULL, 
            0x2DC031EB671B2DFAULL, 0x42ECC3F06D6CF343ULL, 0x3E3D92C1A8E42268ULL, 0x1E1949377DDA8C17ULL, 
            0x47E3F02E3E7656E8ULL, 0xE3DE9946FD8146C4ULL, 0xD23CA881BFA49467ULL, 0xD9651224AFE7755CULL, 
            0x0AC232E5D6498ECCULL, 0xDC181F8A2F751AAEULL, 0xB673D15C2B08F84BULL, 0x0BDB51368CF1C812ULL, 
            0x5F00D145D432C2EDULL, 0xAF27D59CD42EF386ULL, 0x993058C7B0758A08ULL, 0xDC66531A164CC5B7ULL
        },
        {
            0xE97DDD7E80CFD0D3ULL, 0x8A15333C06073B2DULL, 0xC0B5F5D0F551F8A9ULL, 0x3C9C587BCFEB0C62ULL, 
            0xDB21E0E7C6BB997EULL, 0xDE47922113FC0660ULL, 0x12B1151A9F3929FAULL, 0xF902302E37020FEBULL, 
            0x79AE591E433CC81FULL, 0x7F80F4E3254D1B6DULL, 0xA1D851EC768FA966ULL, 0x8CB0F4480D09044AULL, 
            0xE0571A2B5CA0A62AULL, 0x9C12FF8121DF5897ULL, 0x0267A837BDCD3D30ULL, 0x1DBDD4B62F2409FEULL, 
            0x1BC87F8255E09E5AULL, 0x2A5D2260FBB9C739ULL, 0x59D783D2539438F6ULL, 0xE0A253AA23F3F75AULL, 
            0xB8D3DEFE8246140BULL, 0x2F59187A5C99802BULL, 0x91026A8976747236ULL, 0x2D662DEAC1DCD616ULL, 
            0xDC4B9264153428C9ULL, 0x2FD1D323C06AF19CULL, 0x4BDC37A287852CDBULL, 0x86183EC0FEB028F7ULL, 
            0x2E2A93D0FB3098B8ULL, 0xAE0EA0BA2CD1A95EULL, 0x0F3AA449B308A458ULL, 0x3223693A04079594ULL
        },
        {
            0x853515ECC67D59EEULL, 0xD3E2C22175B9B0B5ULL, 0x8B77A4D6D1210A71ULL, 0x13B8F474146B4388ULL, 
            0x4FA8419743BFDA8CULL, 0x07498AA530B879FEULL, 0x7A909D359E0D4A9EULL, 0xFD7EA51085E23F06ULL, 
            0xE94581E69A1D1F86ULL, 0x4E4AECFDB2A850AFULL, 0x8614C188FA0012F7ULL, 0xF40529C9A3B7C9F0ULL, 
            0x19136A1C07BF7D45ULL, 0x0A17E94DD7466962ULL, 0xF3AA0297E664AD4CULL, 0x35995CA84BC753CDULL, 
            0x653CEC86906BE8ECULL, 0x2EE83B6ADECFB5CBULL, 0xEFC3FB913A1F6C49ULL, 0x085CA30DA1DCD6F8ULL, 
            0xFB00C6EB962B332AULL, 0x8B0F4C10E0E411EDULL, 0xC997978354FA606BULL, 0xB7680A7F063C6B27ULL, 
            0x8EEA3DC500918649ULL, 0x50388D662F8DD813ULL, 0x6EC197203270DB4AULL, 0xB52242E755192D5FULL, 
            0x2B44AAAD4D496AB9ULL, 0x965C31F95A771AD5ULL, 0x19B7C5B7ED500A4CULL, 0xC205768856D04AF1ULL
        },
        {
            0xC2CCE4C4453D1A1EULL, 0x948BA63334EEDEFEULL, 0xCF0C5863971FF043ULL, 0x0F8CDD99FDC0F612ULL, 
            0xD74D1F1A1BA23D61ULL, 0x711EC24F4FD40597ULL, 0xC341819016B63C26ULL, 0xF39A9B25041E44BAULL, 
            0x449C49BA0FA0E007ULL, 0x4A6F2A6AA560DBAEULL, 0xA1DA9BB732815C9AULL, 0x19D84FDF773CDC83ULL, 
            0xEE8B589D1536611EULL, 0xA45B0AC62D8040DCULL, 0xD4965AF9C7505BCDULL, 0xD8A8C2F226298D35ULL, 
            0x1A4D9CDB9E1961B3ULL, 0x510501C49172925BULL, 0x44BDF4DAAA87ABB3ULL, 0x5E4383498705B892ULL, 
            0x8D3C81894A8D34EDULL, 0x43A9FDFD8DD0E105ULL, 0xA17DF42231A455DAULL, 0x011704C28843FB07ULL, 
            0x6048FBC670605F6FULL, 0x1B9BEFB7128BFDA5ULL, 0x3A5EE71DFB63FBAFULL, 0xF0738027F8AE351DULL, 
            0x4DE1E0DAFC43787FULL, 0x456C41D63F71E363ULL, 0x80052CD5D1DDFD3AULL, 0xE4E4F457DA2D1F8DULL
        }
    },
    {
        {
            0x93BF99C63150874AULL, 0x4F78C386F3CD1CFCULL, 0x2F88B6B2A99B5298ULL, 0xF107D00A69ED13E2ULL, 
            0xE5566C4DF432EB76ULL, 0xB61FB96BF7781A3FULL, 0x0CA8A34E00978DEAULL, 0xB5B4F9192B191521ULL, 
            0xB7B06AE0C45D1DFCULL, 0x30FE1CF3524CAFB0ULL, 0xE1BA69539D5A3DFDULL, 0xA7EF7A578CEF2873ULL, 
            0xF6AE5F040A429964ULL, 0x363EBB736D399057ULL, 0x3458D0F94B89B60FULL, 0x51762BF202D8AFE3ULL, 
            0xB8A481396138CF9FULL, 0xCB25CE454C3F0D59ULL, 0x4C48AE8CD21DFC36ULL, 0x54CA58ADFC70EAB7ULL, 
            0x3CCD4F19CF3C461AULL, 0x78DE547E52762D8AULL, 0xE62BB909CAC60462ULL, 0xC44262B605728CFAULL, 
            0x41249BBD11A18AFAULL, 0x1CEDD5E2885324AFULL, 0x2DD90AA1E8F5E1F1ULL, 0x36F9E69F3100E308ULL, 
            0x020089523AE52B8FULL, 0xADDED4412525B1CCULL, 0x90CF71ABFC457093ULL, 0xFD335A19303CC8F1ULL
        },
        {
            0xE0104B8C414D9FBBULL, 0x36401B117EAC3E4CULL, 0x8BFE3B154DA1A45BULL, 0x926A7FC47D0BCE8CULL, 
            0x3C66475ED43CCF74ULL, 0xB34C776C20B2AA12ULL, 0x573B7AEBF7A1F8FEULL, 0x4E38219DACF85A84ULL, 
            0x729F87178C370358ULL, 0x2CA24BE94DD7C082ULL, 0x94FCEB42636C2414ULL, 0xE1CBE6795A57BAF2ULL, 
            0xD13CF83BBCA59B29ULL, 0x48ADC9F6C213CE6DULL, 0x670DDD9F3F6CFEFFULL, 0x9F3250F0A6880989ULL, 
            0x20C6F24A79DCFD0CULL, 0x7060B04F7C1590C7ULL, 0x686AC7BD459C959BULL, 0x916E31AC1C8F27FCULL, 
            0xEA235994312E678CULL, 0xCB114620921EB1EAULL, 0x22C04CFA8F25A2DBULL, 0xA75A0C2065D8EE51ULL, 
            0x23F2D98E0102EF45ULL, 0x514E882D2F9D0AF8ULL, 0x93096239606B930BULL, 0x42C9058D23CD7EFFULL, 
            0x3675CE97F733500DULL, 0x76A2409E37F5A623ULL, 0xCF610145A3B4914BULL, 0x53878E343F4A49C8ULL
        },
        {
            0x05B8EB24170D2B6EULL, 0x090F038043AAB25FULL, 0xACA7A16F19BC3D94ULL, 0x2739263AB76CD247ULL, 
            0xBF557F7EA3C61342ULL, 0xAE7D0FAD3B978B63ULL, 0xF0D7EC7B74BC3B91ULL, 0xA5BE01262C4F6EC5ULL, 
            0xF5034B42A4B73971ULL, 0xFB67703F4AB46B1DULL, 0x8A1099B276A678DFULL, 0x10B2A16E2FB54C1BULL, 
            0x3BED7699316E1730ULL, 0xEC8121C4FE6B363FULL, 0x6262C18D4F5B5367ULL, 0x404E95B2C6ABEB38ULL, 
            0xFEE6587E28842954ULL, 0x15C532099A3D6430ULL, 0x01B4EF5D7BF14227ULL, 0xBF118828305CDDA0ULL, 
            0x4E96684420128E39ULL, 0x51E27D958BDE791FULL, 0x83437D03F82712F4ULL, 0xB5B38A3D4801CCA2ULL, 
            0x2F3BC85C5D62A8B4ULL, 0x048950497F8F31ECULL, 0x1527A76011A7681DULL, 0xF8F49FC863D05635ULL, 
            0x393F71D4F28D0289ULL, 0xEA0861C443643E09ULL, 0xE7EAD55DC2C0A573ULL, 0xCDE9FA6D851132A1ULL
        },
        {
            0xEF653563BDBED7D1ULL, 0xCEB0708E94EE9D34ULL, 0xABF2ACBE979A201CULL, 0xECFDF47B318400E9ULL, 
            0xD4C8345FFAB81106ULL, 0x1631AA8A6A1B4B11ULL, 0x74A8412EDC284292ULL, 0x8C99E326B7732F68ULL, 
            0x545ECA88A551B117ULL, 0xFBD81D07AF9B6C78ULL, 0xFEE234E6B31FD222ULL, 0x4C322B35D738A7E5ULL, 
            0x053A64448EA2ADD5ULL, 0x5F4345D34FBE4778ULL, 0x12776409B2B0226AULL, 0x77D138C478B07F81ULL, 
            0x9572B22CE381BF33ULL, 0x512D263367CD03D3ULL, 0x6356E14C37540D74ULL, 0x0108F724F9B6EF7EULL, 
            0x119C26184DA14805ULL, 0x0543BAF706623B42ULL, 0x3C7BD726E124565BULL, 0x0EC006E7178D5230ULL, 
            0x4BB4D09CAE3D3453ULL, 0x7BF7A3204E992247ULL, 0xB3F833851B5C647CULL, 0x123D273DB47CCF76ULL, 
            0xD7FB68CDACD965F7ULL, 0x56CCAFA549127343ULL, 0x87A49DE791B1EA2DULL, 0xD948F804055B37EDULL
        },
        {
            0xE9A99BB92A3B7C4DULL, 0x3DBA94C37586EAA2ULL, 0xA874497EC3798070ULL, 0xC6EADCFCA1419698ULL, 
            0x8A0B3EB117EA02D7ULL, 0x1F6CBECC149DCDF9ULL, 0x546FD1D51C554817ULL, 0xBC323602EF2C6A12ULL, 
            0xEF80B500F0B300A0ULL, 0xE3208A255CF9E8C8ULL, 0x8788837C00DE519CULL, 0x18C48024D50918D4ULL, 
            0x4127576E3708C57FULL, 0x0A759663B4F63E35ULL, 0x80561A773EEB3F19ULL, 0xF9675F0215EF79D7ULL, 
            0x1B1F34EF969BA12BULL, 0x0C86B1229E760158ULL, 0xC97BF942C2C344ACULL, 0x7DF018C378BEDC4FULL, 
            0x16F737F1AB660855ULL, 0xF00603284FBF0945ULL, 0x006963E6EE9AA654ULL, 0x48EA7B840E206E9DULL, 
            0xDC303AC342F8B447ULL, 0xB713282F3C63E7F3ULL, 0x458B04D92891917AULL, 0xC0C4655C97EABFC0ULL, 
            0x841DD4CE1C098876ULL, 0xFD8054F90E0F230AULL, 0xA48677D41EFA311AULL, 0x22C7C345FC2F5B6CULL
        },
        {
            0x2019F0F4256754FAULL, 0x054E4880C0B9BAA1ULL, 0xDE05EC5F98E157C6ULL, 0xBB2B8EE4F2EFEC5FULL, 
            0xD4F72A1983B7390FULL, 0x4DC6B84527314315ULL, 0x1BC84BC22C9309CCULL, 0x9850D481BDD70A5EULL, 
            0x9321FDE8AFAC10C7ULL, 0x89703BF7159A0F5CULL, 0xB9D063CD01A41046ULL, 0xF3175B3AE825FE2EULL, 
            0xB9B93D72437A6C1EULL, 0xCA6AD615E5A24493ULL, 0x8DD463B7B807A8B0ULL, 0x827A88E86217109CULL, 
            0xA7509CBB18DB451DULL, 0x8553BF9DD1CE0976ULL, 0xD02B9AFE33F6AAB2ULL, 0x735FD74427F65E0CULL, 
            0x79D977844F48CA6FULL, 0x2BA55616E067E47AULL, 0x70038BB9CE111FACULL, 0x02B08755B44CAE12ULL, 
            0xB19E4BF96A0E55F4ULL, 0x2E4AF3B62258587EULL, 0xBD9F0DF6150B0C39ULL, 0xE19447660350FA7CULL, 
            0x4E791210895057E1ULL, 0xE3FBEA2ED71724E9ULL, 0x329ABE479ACB577EULL, 0x5F9828F40B4BAB34ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Rigel::kPhaseHConstants = {
    0xC6746A9A4B41E85FULL,
    0x00E9E49814FEF74CULL,
    0x4FE830FF9DBBDA3DULL,
    0xC6746A9A4B41E85FULL,
    0x00E9E49814FEF74CULL,
    0x4FE830FF9DBBDA3DULL,
    0x2E39BA69A60E908CULL,
    0x287F44345D51DC1EULL,
    0x7E,
    0x68,
    0x29,
    0x52,
    0xE3,
    0xED,
    0xF5,
    0xFF
};

