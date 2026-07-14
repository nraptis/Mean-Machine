#include "TwistExpander_Betelgeuse.hpp"
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

TwistExpander_Betelgeuse::TwistExpander_Betelgeuse()
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

void TwistExpander_Betelgeuse::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0x90A9438FEBFE03E5ULL; std::uint64_t aIngress = 0x9C9F32E0D24517B8ULL; std::uint64_t aCarry = 0xF4F2F7EFAF9336D1ULL;

    std::uint64_t aWandererA = 0xCB1717952E47D01AULL; std::uint64_t aWandererB = 0xA640C30C8A3DDC00ULL; std::uint64_t aWandererC = 0xC36E0FBD632C4B05ULL; std::uint64_t aWandererD = 0xAED2EC9475D2727EULL;
    std::uint64_t aWandererE = 0xC5C04B97DC146B19ULL; std::uint64_t aWandererF = 0xAC3A8D9F1E68E937ULL; std::uint64_t aWandererG = 0xC685E74561EC5694ULL; std::uint64_t aWandererH = 0xBFBD0F24AC915670ULL;
    std::uint64_t aWandererI = 0xA221C155353D4EF5ULL; std::uint64_t aWandererJ = 0xFD5D24661D5B5DF6ULL; std::uint64_t aWandererK = 0xA0EB3DEA8DB132C1ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 14868405556612573577U;
        aCarry = 13071601186173894084U;
        aWandererA = 13211948833633856300U;
        aWandererB = 17012660490797286047U;
        aWandererC = 12912110819526463075U;
        aWandererD = 15033631977925531873U;
        aWandererE = 16741587464875085497U;
        aWandererF = 9555619860670191899U;
        aWandererG = 13267924294754054476U;
        aWandererH = 18052462485469209910U;
        aWandererI = 9883877111295945109U;
        aWandererJ = 11232399788519953184U;
        aWandererK = 17542764027497650196U;
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
    TwistExpander_Betelgeuse_Arx::KDF_A_A(pWorkSpace,
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
    TwistExpander_Betelgeuse_Arx::KDF_A_B(pWorkSpace,
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
    TwistExpander_Betelgeuse_Arx::KDF_A_C(pWorkSpace,
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
    TwistExpander_Betelgeuse_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Betelgeuse_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Betelgeuse::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xE884BE81B0AC84BFULL; std::uint64_t aIngress = 0xEA3D876888469AD7ULL; std::uint64_t aCarry = 0xA13CBF23FE599D04ULL;

    std::uint64_t aWandererA = 0x81423F4FA8E0B6F5ULL; std::uint64_t aWandererB = 0xE27A2EE78B210B9AULL; std::uint64_t aWandererC = 0xCC3820452DE301BDULL; std::uint64_t aWandererD = 0xCB2EF029B71D6EC6ULL;
    std::uint64_t aWandererE = 0x9C7562F6BB7EF3E8ULL; std::uint64_t aWandererF = 0x83919856D1EEBE6BULL; std::uint64_t aWandererG = 0xC68D69606BCD8680ULL; std::uint64_t aWandererH = 0xBDC1734F2E9A62DDULL;
    std::uint64_t aWandererI = 0x8413D887CC82B121ULL; std::uint64_t aWandererJ = 0x979DE416CD8AE146ULL; std::uint64_t aWandererK = 0xE41AE81706F763EEULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 9661007484488667236U;
        aCarry = 11001416546066908195U;
        aWandererA = 17418155949382565074U;
        aWandererB = 9459395268274435278U;
        aWandererC = 17093756007775108891U;
        aWandererD = 13465495827915920614U;
        aWandererE = 12028414586670861778U;
        aWandererF = 16486704626634192855U;
        aWandererG = 13875177340664832759U;
        aWandererH = 11759669347266330823U;
        aWandererI = 11988125691673558383U;
        aWandererJ = 16953735046552604661U;
        aWandererK = 15045710477479593194U;
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
    TwistExpander_Betelgeuse_Arx::KDF_B_A(pWorkSpace,
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
    TwistExpander_Betelgeuse_Arx::KDF_B_B(pWorkSpace,
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
    TwistExpander_Betelgeuse_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Betelgeuse_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Betelgeuse::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xD75C9BFEB001BEB3ULL;
    std::uint64_t aIngress = 0x9EDDB0114C20DF66ULL;
    std::uint64_t aCarry = 0xFA700ED8B75E2B4EULL;

    std::uint64_t aWandererA = 0xF851E5ACC9AC774CULL;
    std::uint64_t aWandererB = 0x8A74B5B4C982E7CFULL;
    std::uint64_t aWandererC = 0xF1125877B7CA066BULL;
    std::uint64_t aWandererD = 0xA3494BB9B1755E1EULL;
    std::uint64_t aWandererE = 0x96A8444026F31DAFULL;
    std::uint64_t aWandererF = 0xB45564591388F60CULL;
    std::uint64_t aWandererG = 0xE04662637F13AA13ULL;
    std::uint64_t aWandererH = 0xD22D4C7E53E71A46ULL;
    std::uint64_t aWandererI = 0xB313ADCB11826EE1ULL;
    std::uint64_t aWandererJ = 0xD5B0897F97BE136FULL;
    std::uint64_t aWandererK = 0xB5A2D6D96CB5E1F9ULL;

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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneA);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneD);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneB);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneG);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneE);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneH);
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
    TwistExpander_Betelgeuse_Arx::Seed_A(pWorkSpace,
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
    TwistExpander_Betelgeuse_Arx::Seed_B(pWorkSpace,
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
    TwistExpander_Betelgeuse_Arx::Seed_C(pWorkSpace,
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
    TwistExpander_Betelgeuse_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Betelgeuse_Arx::Seed_E(pWorkSpace,
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
    TwistExpander_Betelgeuse_Arx::Seed_F(pWorkSpace,
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
    TwistExpander_Betelgeuse_Arx::Seed_G(pWorkSpace,
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
    TwistExpander_Betelgeuse_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Betelgeuse_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Betelgeuse_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Betelgeuse_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 13 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1848 / 1984 (93.15%)
// Total distance from earlier candidates: 22325
void TwistExpander_Betelgeuse::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 224U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 389U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1293U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1387U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 2004U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1468U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 779U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1147U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 933U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 216U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 946U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1460U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1359U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1076U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 435U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1530U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1184U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1171U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 694U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1291U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 254U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 911U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1255U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1085U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1539U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 440U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1341U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1212U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1685U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1149U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1664U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1657U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 533U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 365U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 820U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 904U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1801U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 184U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1944U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1683U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1496U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1403U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 928U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1057U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1879U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1516U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 702U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1096U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 330U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1098U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1691U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1216U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1529U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 876U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1286U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1367U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1312U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 616U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 203U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 991U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1617U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1511U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 485U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1144U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1253U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 296U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 654U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1753U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1854U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1773U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 864U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1886U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1636U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1481U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1718U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1522U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 370U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 922U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1898U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 602U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1289U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 98U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1065U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 579U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1775U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 631U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 10U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1418U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 682U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 448U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1159U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 338U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 739U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 686U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1447U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1090U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1207U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 905U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 691U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1844U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1661U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 327U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 670U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 62U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1158U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 2024U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 968U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 2008U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1220U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1276U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 996U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 50U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1926U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 517U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 2018U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1150U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 797U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1693U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 751U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 273U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 320U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 182U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 695U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1443U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 364U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 218U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 324U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1770U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }
}

void TwistExpander_Betelgeuse::TwistBlock(TwistWorkSpace *pWorkSpace,
                                       std::uint8_t *pSource,
                                       std::uint8_t *pDestination) {
    TwistExpander::TwistBlock(pWorkSpace, pSource, pDestination);
    if ((pWorkSpace == nullptr) || (pDestination == nullptr)) { return; }
    std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    std::uint64_t aPrevious = 0xDBBB12214AB8360AULL; std::uint64_t aIngress = 0xDF1832152F091112ULL; std::uint64_t aCarry = 0xAAD86F9311B42595ULL;

    std::uint64_t aWandererA = 0x9E32C900609B4842ULL; std::uint64_t aWandererB = 0xFA5153FDFEF00E9BULL; std::uint64_t aWandererC = 0xB56B438890750FA2ULL; std::uint64_t aWandererD = 0xB31D22DBC965B8CDULL;
    std::uint64_t aWandererE = 0xD4F29DE2349E4E94ULL; std::uint64_t aWandererF = 0x958D6D7A7538CE60ULL; std::uint64_t aWandererG = 0xD0B5132A170DCDADULL; std::uint64_t aWandererH = 0x8F5775C5B2389C25ULL;
    std::uint64_t aWandererI = 0xF1957C1F5A7E634EULL; std::uint64_t aWandererJ = 0xD5865DF09E157E85ULL; std::uint64_t aWandererK = 0x936E548D9B9586F5ULL;

    // [seed]
        aPrevious = 16179983116683943337U;
        aCarry = 17172384407396342044U;
        aWandererA = 10391551784957191664U;
        aWandererB = 13166093218976865618U;
        aWandererC = 9382347522298239796U;
        aWandererD = 10852304592827459902U;
        aWandererE = 14552326549254612150U;
        aWandererF = 11562353493145416931U;
        aWandererG = 16355428154876884026U;
        aWandererH = 13503870999931595673U;
        aWandererI = 13529063855568789735U;
        aWandererJ = 14361303266705165699U;
        aWandererK = 15780106612578999433U;
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
    TwistExpander_Betelgeuse_Arx::Twist_A(pWorkSpace,
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
    TwistExpander_Betelgeuse_Arx::Twist_B(pWorkSpace,
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
    TwistExpander_Betelgeuse_Arx::Twist_C(pWorkSpace,
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
    TwistExpander_Betelgeuse_Arx::Twist_D(pWorkSpace,
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
    TwistExpander_Betelgeuse_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Betelgeuse_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Betelgeuse_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 13 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 6596; nearest pair: 470 / 674
void TwistExpander_Betelgeuse::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3156U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 293U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3586U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3088U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2975U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2955U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3388U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2198U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7666U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2080U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1151U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4974U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2521U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5233U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5997U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7973U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1911U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 231U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 874U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 364U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 880U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 463U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1719U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 777U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 954U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 346U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1534U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 551U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 988U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 870U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 677U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 256U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 122U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1820U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 412U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 204U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 13 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 6600; nearest pair: 505 / 674
void TwistExpander_Betelgeuse::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3042U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1609U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3179U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 527U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2561U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6017U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4715U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 44U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2903U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6912U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 642U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2934U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2090U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4474U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4965U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2523U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1536U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 918U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1143U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1642U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 192U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 606U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 17U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1230U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1914U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 204U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 264U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1543U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1484U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2001U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1558U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1931U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1571U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1138U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 558U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1394U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Betelgeuse::kPhaseASalts = {
    {
        {
            0x887C2C8D0FAAE53FULL, 0x0CBB8957414CF221ULL, 0x3C9A8F45DFE26307ULL, 0x054F0F8C781998CAULL, 
            0xD64D12DF81CA351DULL, 0xE2FC97B139BA2A9CULL, 0x064BF4196083BF6FULL, 0x6B4FCCB836C94AA9ULL, 
            0xDF2E165868124CA3ULL, 0x824A3630DF60AA78ULL, 0x6A458ABC50B111A2ULL, 0xD54192DD77E92C6FULL, 
            0x08C3590674FBE97CULL, 0x86573C58D0A0137AULL, 0x1FF392B8606442FDULL, 0xABC564AF090C0B60ULL, 
            0x736E25BF52D707C9ULL, 0xF0223AEE6062A409ULL, 0xA275A6473F0A9B7FULL, 0x627A4816A2F70B4FULL, 
            0xC96E6B3A0B02EDDAULL, 0x5A75A3EBB6ABE1EFULL, 0x9D774737A91E82DFULL, 0x9BD96AC4A6155062ULL, 
            0xB90C8A0A4B475325ULL, 0xBCD60312AA36847EULL, 0x97C99A2ED702DCD7ULL, 0x93A9640BC95E4CE5ULL, 
            0x24B72F8216E266D9ULL, 0x0B4F84425E83CB22ULL, 0x1DA28AF1FC10AC7FULL, 0x7494AD4E8B285FCBULL
        },
        {
            0xDBEC5C399EE93A6AULL, 0x9BA60195D1A07F86ULL, 0x5D95D3D44D5172D9ULL, 0x5D2205C30D7E17D3ULL, 
            0x139227CD44232D80ULL, 0xEEDF4C9F9E88B13BULL, 0xF98AFCEEFCB4F4B3ULL, 0x89EBC371812AE3F2ULL, 
            0x737CA9C7567C7EB7ULL, 0xBF24706D69A35F32ULL, 0xE4DF932477EC0863ULL, 0xAA8EF16216D75305ULL, 
            0xE86AFB54869700BCULL, 0xCCC61E92C9DAC199ULL, 0x9278E119883D685DULL, 0xA9EF4112EB1CF603ULL, 
            0x23213857D48C4BF3ULL, 0x43E7B9FDC64C55A3ULL, 0x756F3DB11174C62FULL, 0x74DE2118150BE545ULL, 
            0x124C24B8155686A2ULL, 0x27EBC778BDF73D0CULL, 0xDCF450C44608759DULL, 0x908F846F740ABA87ULL, 
            0x20E88231E29E3B27ULL, 0x8545D4A677E4EF80ULL, 0x40375C62F0D5CDF2ULL, 0x9F90B8F8BECE7D0BULL, 
            0x608E06FBB0DFC184ULL, 0x9F9F5B5CD227A418ULL, 0x302F7739CD86DB58ULL, 0x5CA7CC32095AE8F9ULL
        },
        {
            0xA0B36555048BA132ULL, 0xB661F899DDB56106ULL, 0xE02980050E151E9AULL, 0xEA3BE263BEC78E93ULL, 
            0x81B5F98017D3BB4AULL, 0xD11B4B78C864A3E3ULL, 0x314D9F2219698C37ULL, 0x01C5A846276C0E73ULL, 
            0x12E40A954FB9ED94ULL, 0x8E41D82AA99FB542ULL, 0x5FE22227B6612A42ULL, 0x8323A6846EFB0CB0ULL, 
            0x38EB65DBEF658CCEULL, 0xCF902D9D6BC24148ULL, 0x3DB623058120A329ULL, 0x8049B75B77BD0F68ULL, 
            0x6A4A2EB89DCF3097ULL, 0x2BE33336F0E52CD5ULL, 0x7C72420D537DCA8AULL, 0xD0A283F839445CEAULL, 
            0x95311398251144A2ULL, 0x89432331BC3FC633ULL, 0xA293FB403E58DA22ULL, 0xEA058A9CF0EA8B2FULL, 
            0xEDD86B4D97C9664EULL, 0xBE090AAEB1807DCFULL, 0xBFDCA37EDEB454D7ULL, 0x73AC87EE8FCFEB60ULL, 
            0xF8C04CEAC801FC9CULL, 0x7876E8ABCD4E212DULL, 0x5189EA29E22307A3ULL, 0x06158D4DD38BAE56ULL
        },
        {
            0x774839A957440D77ULL, 0x85C90882B66E5907ULL, 0xC3F8E08D2FAF6226ULL, 0xE792DC6B1DCAB64BULL, 
            0xB6E91949C63A92FBULL, 0x7AEACD88252D2004ULL, 0x7A5A0375643CC9D7ULL, 0x773BEFBD71B4BD01ULL, 
            0x32675FD62A224BA7ULL, 0xFCE5357B1483F689ULL, 0x44B95104C598A6DFULL, 0xD35ABF4618EE428CULL, 
            0x73BBD3AD2E1A4D80ULL, 0xA783DA1514DAFCE8ULL, 0x0E1A83D8EF7975E1ULL, 0xD6641B0484FEA623ULL, 
            0x19C08E20A90C1DB7ULL, 0x42BAE8B3E654B7ECULL, 0x0D91FC51B9248BEEULL, 0x4CA3C045A7C0B1B2ULL, 
            0x4C0DFF72CD5F4D7DULL, 0xA7075DCB3BCE0BB3ULL, 0xAB296291C38AA10BULL, 0x3B375A94DFA298E4ULL, 
            0xF658FF6E240E0E80ULL, 0xCA6F8D82204E4E63ULL, 0xF136EC32183A32EDULL, 0x8297572DCE07DAACULL, 
            0xDAF54B3244888F51ULL, 0x5D51D11DF7A68824ULL, 0x76501F763F35DE40ULL, 0x673D07BBBE262265ULL
        },
        {
            0x1971EB782633C58CULL, 0x3968371B42192FE0ULL, 0xDB5B4A40E1828DE2ULL, 0x2584E1EACD75BB0FULL, 
            0x9F01514489987172ULL, 0x5EAF28E9709F8030ULL, 0xEEDA0A1A8633E694ULL, 0xD8465BD9EFAF65A4ULL, 
            0xA57E1E3A477A5023ULL, 0x41E884851875AEA4ULL, 0x0691166CAECB76A3ULL, 0xE69EA11DB0FBE6B4ULL, 
            0x47B633E7964FAE0CULL, 0xD1268F7C1ED58FA5ULL, 0x7DE0239BB64FA069ULL, 0xDF282C9CFE7C100FULL, 
            0x297472AD503ED5FBULL, 0x2B0607EEA6ADA89FULL, 0x0935FC3E5BC5C4FBULL, 0xE8B61F1AD23E05F8ULL, 
            0xC3F66FBFA6500D91ULL, 0xAFB16A414406B696ULL, 0x4D86E30EC9C31D01ULL, 0x7C818FE793A3EA6FULL, 
            0xB48FA80B0908E739ULL, 0x1495E70D6E693B88ULL, 0x6EE114711ACF8ABFULL, 0x177DC1A9C0806AA5ULL, 
            0x11DB547648CDE551ULL, 0x061C45275A4AC19BULL, 0xCAA4A6E084DDCE2FULL, 0x6A60EFDF2CFDF6AEULL
        },
        {
            0x424D893E0F27EE45ULL, 0x1F7231509FCAEFF3ULL, 0x034A086A057B408BULL, 0xE58A2A19978B5EB6ULL, 
            0x26608D57EE2F8F8BULL, 0xA55D888176E3FACDULL, 0xAAB69266325449C7ULL, 0x7567D09F4DF41E1AULL, 
            0x97F98BA7C13A9E9FULL, 0x9F827905F1E24A31ULL, 0x8EFCB5B16175CBBAULL, 0xBC131634CF11A541ULL, 
            0x0914E6967336676DULL, 0x43378469C370C8C4ULL, 0x2AD4BD69763DA180ULL, 0x5F3531472436FF48ULL, 
            0x83AF6ED2EB06E094ULL, 0x175EFA739F412D47ULL, 0x7C919E64A273D17FULL, 0x2D6999257DAAC9F0ULL, 
            0xE4A6AB31713D9615ULL, 0x8D4DD43F2868A475ULL, 0x9CA2BC07C3A74990ULL, 0x4F93F4E3BC015864ULL, 
            0x93CF5ADE308E27B3ULL, 0x545148F294EC0F03ULL, 0x7F1F4C8DD67FA1F9ULL, 0x669118D94A69C2ECULL, 
            0x6587A0397883F59FULL, 0x98ADD272000B7235ULL, 0xA7E18CC48160277AULL, 0x79BD047A17925FBFULL
        }
    },
    {
        {
            0x0047DED38AF3AF1BULL, 0x273C04FE89B603A3ULL, 0xB54EF981B387D504ULL, 0x2861858AB5B2BD93ULL, 
            0x82755F6F2A59951EULL, 0xF305E34D7A4FFC8DULL, 0xB2B41E04DE94CDF8ULL, 0xB384D2E347729E7EULL, 
            0xBF637CB466099383ULL, 0xA7D04470CE6F4A2FULL, 0x31F2D610E5B1ECA2ULL, 0x9EB2EEBFB23E1C9BULL, 
            0xE5E92883759C34CEULL, 0x56127694E633139AULL, 0x6BC59378F9EA341BULL, 0x48CEE9DE644C61BEULL, 
            0xB22058CD67297939ULL, 0x7D1FC646737AE9E2ULL, 0xADD494DC46BCC345ULL, 0xF79E4CA6C61C6CC9ULL, 
            0x67CA67F50669A5B3ULL, 0x85D8E27CFD3C1C18ULL, 0xF34C43A6678463D7ULL, 0x38D0A2F53088E994ULL, 
            0x22093007450EC877ULL, 0x4371B6617F45A7E0ULL, 0xA314996190C942A5ULL, 0xA9089546B0F5564BULL, 
            0x3F288BFED8B72F05ULL, 0xEF65D29D73933EA0ULL, 0x9C41634C109E541BULL, 0x4C575EF6E277E763ULL
        },
        {
            0xE5A787BC0AA4FA3FULL, 0x64D9604085C91C9AULL, 0x0C284D871850FF86ULL, 0x30BD15A2FE9F6087ULL, 
            0xF8A182ACEA11C8DDULL, 0x4DA29A5543CC3BA3ULL, 0x2BB6ADDEA4C18D5DULL, 0x402EC08EA4ABF195ULL, 
            0x064CEB7BD714B427ULL, 0xEDEEB5F816040323ULL, 0x9842F2F16523D94EULL, 0x96F9A04491317426ULL, 
            0x57B190CDF7E22E9BULL, 0xABFCB59AEAA8E0A7ULL, 0x2D76AF0FAE83A8A1ULL, 0xBE3CC4CB5026CF04ULL, 
            0x4387A0EE3C632494ULL, 0xFE4BDF838A47163EULL, 0x80BA6D6C256019EEULL, 0xC8B288429B92D9B5ULL, 
            0xE866B90FAAD5D5E2ULL, 0x7F9A7313000BD59CULL, 0x3FB370773C88E19CULL, 0x1FFA24AD7B00CDC8ULL, 
            0x2BB40ABEDC29EB86ULL, 0xA76632B62FFD6442ULL, 0x401D49E1902CA5D0ULL, 0xB138A91A86F7131CULL, 
            0x9AE8AF8A62303B46ULL, 0xEDCB4C6EADFE7AC2ULL, 0x3FACE641AEFEB935ULL, 0x15B45336E8FFEB3FULL
        },
        {
            0x5F826DA2F2C3F889ULL, 0x29F116C76C3A3A39ULL, 0x01BC5D25B8A8C600ULL, 0x5303EC99B33ECD2CULL, 
            0xDE1FBEC833099908ULL, 0x2823513D15148CA9ULL, 0x361CAE3AF9241981ULL, 0x5DE97EFA332C5DADULL, 
            0x277A4FC9CAAD26AFULL, 0x4676D9ABD9265C50ULL, 0x2B32C710B7ACF1D6ULL, 0xD5D7B3777632569DULL, 
            0x9793D97E8C843F74ULL, 0xC35CFC2BF16ABF9EULL, 0x46CA9526E9B66446ULL, 0x4D5ED1736752A344ULL, 
            0xB72C478969EAF61AULL, 0x6CCFD69401D3061BULL, 0x3C0FD777D4F47614ULL, 0xFC044FCD20A6F8DBULL, 
            0xE277235DEBEF9B67ULL, 0xF6BF7AD1866470EBULL, 0x2E2B087E0B623276ULL, 0xA8E019744445A2C5ULL, 
            0xA32C3BCA2937DC24ULL, 0xD8149BE6DDFF8BABULL, 0x57A1E26CE733F638ULL, 0x17FA09B0B61B9A8DULL, 
            0x941FD30BE4004B76ULL, 0x929B189EF2787C1CULL, 0xE50A11BF74353146ULL, 0x83D60F8E45B903C1ULL
        },
        {
            0x0EF5CFA3E01DAD53ULL, 0xF21521D12B8D58DFULL, 0x9CD2073511DE4F9AULL, 0x98A6D156A6413289ULL, 
            0x642CE091B0EA1FEFULL, 0x2A4E29C30E1709EEULL, 0xC2DACDFEF54FC371ULL, 0xCDAA9F44568E222CULL, 
            0x079598CF3633B42DULL, 0xC286861EFD7EF17AULL, 0x2FE25B048E12B93CULL, 0x8F0D32556013B64DULL, 
            0x03FA38DBF150CE41ULL, 0xA7EDAC761E6E6F6AULL, 0xF6D9842E27352B4CULL, 0x82B1E0CA7C7D85C3ULL, 
            0xDF61DD6309C5B18EULL, 0x2E451D629F83974CULL, 0xDD844D4C1E9A8E21ULL, 0xC2004A86093DD9C6ULL, 
            0x518361F8F619C948ULL, 0x76481C2B82C95081ULL, 0xB1936D1167A65EF4ULL, 0xBC82F602C6AEA64EULL, 
            0xB661111AD95191D8ULL, 0x39E2323877899A7FULL, 0xC12449F06A5998EAULL, 0x5F30E7F547F172A6ULL, 
            0xA97CED95B23340FFULL, 0xB15AC92E414010F1ULL, 0xFFAEE11FFFF2C261ULL, 0x218FEF50AA90F407ULL
        },
        {
            0xD9DA9E66D351AF7DULL, 0xD8D8C8B8FE253D91ULL, 0x43F7848B1F8BB42EULL, 0x21B69B6A8D106A38ULL, 
            0x97DF6411CAE84F4BULL, 0xD718891DFC5DDB1CULL, 0x992E09DB06A309EEULL, 0x3690B802581A9520ULL, 
            0x803E6AA20FCB13A3ULL, 0x169DC24A939570E5ULL, 0xDD43B2A58554AF04ULL, 0x83E3EE75E80F75E0ULL, 
            0xD2C2CB30E02E038FULL, 0x7AF6C374D5952B87ULL, 0xB593C19D77D9C407ULL, 0x2B33EA3B4D1CF88EULL, 
            0x5FA944C1E2F11357ULL, 0x3DA786EA70E1C075ULL, 0xDFE9DD2606D0AC80ULL, 0xAF9E62CACD97F488ULL, 
            0xDB3B6BC63F2BD19CULL, 0x1401CBC63F6D000BULL, 0x796827266ECBC39BULL, 0xA07C7DE1CBECA988ULL, 
            0x3181FE55E624BB3AULL, 0xCB920D15D773BA87ULL, 0x6ED2A48545F1CDBFULL, 0xFC605798769CB0A2ULL, 
            0x4C007CFAC453650BULL, 0x125EDED8BC22CF40ULL, 0x2CE2399AC1E15C8FULL, 0x7584CFF57B0ABCADULL
        },
        {
            0xA35C8E06AA831875ULL, 0x75C1BDA3BBCAAF19ULL, 0x7CE23CA506CCCB13ULL, 0xB57CFF3EC12DF87FULL, 
            0x0E122DF9C9DFE774ULL, 0x446F3B2F7FDA0977ULL, 0x72A5DBFF7A81981EULL, 0x2F4A1C92D023774EULL, 
            0xAA0809409129426DULL, 0x0707084AC45E4E56ULL, 0xDF6D53EB2E33525CULL, 0xEE34A9BB423E3192ULL, 
            0xA5023392260B0D61ULL, 0x6A9DDDC028713109ULL, 0x721A6B8EA7901D95ULL, 0xFA0444BFF83CC679ULL, 
            0x9FE39D06FC2F19C2ULL, 0x1799234905D79191ULL, 0x57C6DD8035B4C4EAULL, 0x3E40252A64ED9AE0ULL, 
            0xBE6D6103BC0EC135ULL, 0x1DE3557EE56C6936ULL, 0x6BE52B1E4FA5A942ULL, 0xF09A6DD193D6D848ULL, 
            0x2D4270A5B27A81E8ULL, 0xCD905B655781B753ULL, 0xCC051F972D2E7A82ULL, 0xFA2623460CD856B9ULL, 
            0x19E5F9E8BC60F685ULL, 0x5DA42A48DC6AA6C1ULL, 0x1DF7BE52E7B15432ULL, 0xA258106E05D4099BULL
        }
    },
    {
        {
            0x2D83899EF01F6944ULL, 0xEF79BEDF62D021C0ULL, 0x04908BF452612A85ULL, 0xA4E63E598988676AULL, 
            0xD6C67069971E3588ULL, 0x964BB338BBE6EC6EULL, 0xC32AF39CA8484328ULL, 0x2AE9106041054260ULL, 
            0x421EED17CBA73693ULL, 0xF16585847A8AC636ULL, 0x53789AAEDD611C74ULL, 0xB34F4C13D2D9F806ULL, 
            0x73F67839B0B9780AULL, 0x64EF38F0194BABE0ULL, 0x925A8C47F2387C5FULL, 0x40A7135AB1AB56B4ULL, 
            0x69F306B777C5A490ULL, 0xD77F547C967F3B91ULL, 0x3F91BFF43DF58991ULL, 0x7869F789FECDD1C2ULL, 
            0x396C4E6758A1CC38ULL, 0x0E673D56699FF6B0ULL, 0x8A6C37000D4AFC50ULL, 0x817E099721BE4B8DULL, 
            0x866D7EE6C440443FULL, 0xC674158BD2E8CFECULL, 0x128CAD8EDEAD945BULL, 0x5F6DEC46AD006ED5ULL, 
            0x956C7E21144E15B5ULL, 0x91F8113F60980283ULL, 0x67C7CEDCF011B152ULL, 0xAE4257665A4FFD49ULL
        },
        {
            0x0217872A8A734F65ULL, 0xF4AA2DFBD04CE694ULL, 0x6D2715FA2BDBC5FDULL, 0x97B54207324AB529ULL, 
            0x234F129C9ACE9822ULL, 0x5E5D4417CDE751C3ULL, 0xF632CF2BE5526273ULL, 0xB1A568969B4A7956ULL, 
            0x55654829D4D89B57ULL, 0xA308DB054739AF65ULL, 0x75BEE857034CD8C6ULL, 0xB2BB55E3DBE7ADFDULL, 
            0x4BE1652E8ADABD62ULL, 0xA4C2DC919B2F0509ULL, 0xC7DFC9CFA29ACD3BULL, 0xA2E530E4F9F28745ULL, 
            0xCC60C8DA9D478C9FULL, 0x6DDE2EDAF359032CULL, 0xB503333BA37DBD29ULL, 0x5454822730C01658ULL, 
            0x4345BC4349D47602ULL, 0xC1EC025CCF5C496FULL, 0x4B47AAD74EE4204CULL, 0xE31AC2B5EF4ACB35ULL, 
            0xAA7C0787BC152336ULL, 0xC8730111C0768025ULL, 0x63EB6F4C5B4A07A1ULL, 0x28279D5E93EE568FULL, 
            0x296EF5B66B0E123BULL, 0x036499C409AEB53DULL, 0xA8F6C1767C0E6FC0ULL, 0x193B2315BE9CF9F1ULL
        },
        {
            0xCEF3A695760D9931ULL, 0x36A9A88D517A15E1ULL, 0x70DE90AA273CBD81ULL, 0x8607959B149391A0ULL, 
            0x166A716E60BEDF7BULL, 0xEEE40F8B34CDC8FEULL, 0xA931A674B1C9D9CDULL, 0x5B05A3B58FE10CAAULL, 
            0x092D3B50236827A7ULL, 0x0A1E8655F3B3B36EULL, 0x65804319882A0E25ULL, 0xB9621C459D433732ULL, 
            0x1C796948A1AD4B27ULL, 0x2FE9E9A38E2BC5C7ULL, 0x22F86936B3D77A6EULL, 0x370959DEE5AAD3AAULL, 
            0x9568E27A09FE0430ULL, 0xA71C9BF0CA7706F0ULL, 0xCF4EAEC51753D66FULL, 0xE956421340B1714BULL, 
            0xC42DD6F88AC28E81ULL, 0xF28FBA0AF496ABF9ULL, 0xBFE32FEACCAD82D5ULL, 0x51065EA5CDAB9C66ULL, 
            0xD9B988E397E5A381ULL, 0x0A759B8C68FBF438ULL, 0x86F312025937DA6AULL, 0xB607C9283CB0A14CULL, 
            0xA5B0E909EA20886BULL, 0xFAE22E1809109744ULL, 0x3C148E4A49297697ULL, 0xEF1A8E7256172C80ULL
        },
        {
            0x7461731B612239D4ULL, 0x691CBE22DBF92056ULL, 0xB90899E19ADDDCBEULL, 0x5B4204834388FD0CULL, 
            0xE51E61599CC490ACULL, 0x42A01C608AD35357ULL, 0xBB4C1AC8EC16CC50ULL, 0x148BF778FE63E481ULL, 
            0xD773C583863CABF3ULL, 0xEF5E1E45224E4522ULL, 0x5C65AC0DE1DB111BULL, 0x6777FC0E3516FD23ULL, 
            0x8A2900AB3BB4473EULL, 0xB173AA74953410DDULL, 0xF01172F80ABE6C93ULL, 0x0467E395F3C645CAULL, 
            0xC1D3EAC1E911FB87ULL, 0x60438160829B5865ULL, 0x770C691E94519EF3ULL, 0x844E7EC2EE84798AULL, 
            0xC00636BC08CD729EULL, 0xE759E56AA63B5884ULL, 0x925B825F8797343FULL, 0xCA1CEB04B33A7B89ULL, 
            0xD16783A245EA3643ULL, 0xC8AAAA44C4291020ULL, 0xA533EF3E92747DDBULL, 0xED2D5CDDA3DC0654ULL, 
            0xB2BC3E546F27739CULL, 0x789BD40BF43573FDULL, 0x9A4A129428C57E0AULL, 0x8B0566E1E4D2B4D5ULL
        },
        {
            0x8E616EACE1E2B36DULL, 0xF1FE94DECF5AF57FULL, 0x05B107D21636747DULL, 0xCC475F7E65263053ULL, 
            0x3A9CE9F15B143422ULL, 0x7C777986042EF5A4ULL, 0xF251D64E29310C28ULL, 0x8B4C5C54E8B4B640ULL, 
            0x6F95B5D2A4FA3D33ULL, 0x6E928B9C7FF71CB2ULL, 0xFFB38BFAE82D291DULL, 0x64E810F67F134B7FULL, 
            0x7756D8ABCBA39DEDULL, 0x4EB14E83E1A1BF50ULL, 0x9D3F64ED80FA3454ULL, 0xA1DE86FA9CE4025CULL, 
            0xDEA89FED1BC55511ULL, 0x9CE4722661AFA1AAULL, 0xCA644E45FD577CC8ULL, 0xD0530344C9D61985ULL, 
            0x4BB7BFFA26C53BB4ULL, 0xDC0A5553214CAA85ULL, 0x60C0C7FFDBE3EB6DULL, 0xE50F8FCEB91623C0ULL, 
            0x7A1607BCAA8F8B0AULL, 0x1D5BB1D1E8358905ULL, 0x29C8A2583D91BD56ULL, 0x6C80E1B32CD830E3ULL, 
            0x45ED7CD2733B566CULL, 0x9D5622EEDE7A027BULL, 0x083615C681A8A9E4ULL, 0x5C1AD9574A52EDF0ULL
        },
        {
            0xD69FD95014B3321BULL, 0x5CF5DEEBE37AF591ULL, 0xD2CB4B52A18DCD87ULL, 0xD5AA3A00DB9EBA24ULL, 
            0x3E16361BBD95A164ULL, 0x3B08E3D6304874CFULL, 0xF5A7D46D1C833837ULL, 0x9C34D727B9FCBA24ULL, 
            0x1D0E384E72D2CAEDULL, 0xE7249B2C9BB233D8ULL, 0x29A8FE01C2F22B71ULL, 0x5DCCB571BA2C4B41ULL, 
            0x34714A9890C999ACULL, 0x53BE51B938546326ULL, 0xD4156DC7025EEAF0ULL, 0x653266AB12B7A0CBULL, 
            0x062C687D4C90B9C5ULL, 0xF3A7F1C42B090FF7ULL, 0xA320ECD98D41D954ULL, 0x0360B7668AC2C234ULL, 
            0x47877D07EDE7248BULL, 0x7D69318699A61364ULL, 0xC6E2EE14132BC4D1ULL, 0xB154252C898C33EBULL, 
            0x4ACCD319B0E05E60ULL, 0xD19152E23D664845ULL, 0x572C43BD1655CD08ULL, 0x2D25DF8250B78913ULL, 
            0xDFDB5F889663939BULL, 0xE9DDBEB562326AA0ULL, 0xACC742FF932D2DB0ULL, 0x48608BC72D496C4BULL
        }
    }
};

const TwistDomainConstants TwistExpander_Betelgeuse::kPhaseAConstants = {
    0xF94BD9658A4E0544ULL,
    0x02FD92EA2BDD72F3ULL,
    0xE3EB665EAEFB1087ULL,
    0xF94BD9658A4E0544ULL,
    0x02FD92EA2BDD72F3ULL,
    0xE3EB665EAEFB1087ULL,
    0xA32B6C34DF7DCDA9ULL,
    0x296A8867A28ACFE0ULL,
    0xCF,
    0xCE,
    0xCF,
    0x9F,
    0x8E,
    0x93,
    0x69,
    0x53
};

const TwistDomainSaltSet TwistExpander_Betelgeuse::kPhaseBSalts = {
    {
        {
            0x72CA21F976CF7D9DULL, 0xD9EB0A9C567A5EBAULL, 0x8069A905902A3352ULL, 0xCF7C415E4F029011ULL, 
            0x2C21BF4910AE8755ULL, 0xDDE8D033DBDCFDDCULL, 0x6FAEB2B026C442E7ULL, 0x9E1EE607F0C5F0A2ULL, 
            0x9872C000FFA9AD41ULL, 0xA2E88D44A28F2D04ULL, 0x5D5D6E6048394044ULL, 0xDA1DBB651F7CCE20ULL, 
            0x263851B23A7BB3B4ULL, 0x72ED1CA542438370ULL, 0xE227B58237571543ULL, 0x23B5A0AD67A66197ULL, 
            0x1B157696058744A7ULL, 0x9E3872C30258DF1BULL, 0xE810873442AF617CULL, 0x83944E2F99059771ULL, 
            0x83146032793D6F53ULL, 0x844845CEF6883B34ULL, 0x5F598D8CA831F2A0ULL, 0x7820D417E00EECA2ULL, 
            0xA498703050DD3F75ULL, 0x87C31A2891F19C12ULL, 0x109D8B2DE89C5961ULL, 0x873177363BD3324AULL, 
            0x1856157B38745098ULL, 0x6ADFDD7CCC914FDDULL, 0xA3404A32B0F97123ULL, 0x559FE359B0FD5D6FULL
        },
        {
            0xDE483E0BEE662035ULL, 0x3477BC4DE3CCFC58ULL, 0x738BBF14612EE84EULL, 0x9C3C6BE9DCD77FA1ULL, 
            0xE94FBFCA8263D841ULL, 0xD025B2C390788302ULL, 0x1BC5EDC9C5C9CCB9ULL, 0x23B483D1A9601F19ULL, 
            0x3D509E0E18390F0EULL, 0xA7229DEB241E3EC7ULL, 0xF7187C5758469043ULL, 0x59F11406C00713E0ULL, 
            0x7C926C2FE366B46CULL, 0x86A447AC4FB0BA18ULL, 0xF6C90A3B5C75F01BULL, 0xC26D1E60C147E60FULL, 
            0x2187670885A338BBULL, 0x4EABCE6E6F64EF54ULL, 0x616030E956293AEFULL, 0x059A5E05CF0C64E6ULL, 
            0xCC78AF99DDD8A59EULL, 0x7854F0243E7F3EA8ULL, 0x6819B067FC8C642DULL, 0x59B885B97C936DF5ULL, 
            0xBB95952C9423E345ULL, 0xFD6E72C7C11C7A94ULL, 0xE1B3B5CDC17530F1ULL, 0x9A8A47A138108C01ULL, 
            0x3228126E2CAA19C5ULL, 0x04B77AC2C51BDBE7ULL, 0x7092A55668671C52ULL, 0x4FD510B4DE073977ULL
        },
        {
            0x660615C5F33D06ECULL, 0x93C92082FA1805BCULL, 0xB65113FBE327ECD0ULL, 0xB1CFFC864BF774FBULL, 
            0x167F279FA4F57657ULL, 0x509AC04BB65D7536ULL, 0x31557E18EC3AE491ULL, 0x9BDA5938E155DB12ULL, 
            0x4407429158841EEEULL, 0xBD5F69B1BC74E653ULL, 0x1D4B8FD0EAFAB0ABULL, 0x52531F32B4B7D5A2ULL, 
            0xBF60785DFA252A37ULL, 0x2B411A1F1EE25DA5ULL, 0x07C63CD0FC5F433FULL, 0xA8276AAD6A07F565ULL, 
            0x201D7CAE3E16C55DULL, 0xBA0BC40955071419ULL, 0x11E17A9927E310F5ULL, 0xE80133945A3F8ECFULL, 
            0x93A6ED9572A7027FULL, 0xA0E50E4FCC08965BULL, 0x08F8E488A32B4963ULL, 0xB3D29991E96AF276ULL, 
            0x3E9D65B6DA7150C2ULL, 0xB9F2DE196820AD92ULL, 0x0CC1B3B0C7E7DFCFULL, 0xC3920B16F5A598B4ULL, 
            0x917A01A7743CE3B9ULL, 0x0C252ED55D3F8BC7ULL, 0x137F1244B176FEB5ULL, 0x174E42C9AA50AA3CULL
        },
        {
            0xF9AA64D385A17FCEULL, 0xF0C332DD2318D954ULL, 0x6915BD6BEFE61C65ULL, 0x3EB80C15C27FD656ULL, 
            0xC3FD54EB20341565ULL, 0x4B5187AB2DD1F8C9ULL, 0x9BD97E458455AFECULL, 0x322DFCE36258DD4BULL, 
            0x5C7B5469B49865D8ULL, 0xB07F026CABD932F9ULL, 0x914624C9A2BC030DULL, 0xB454E5F3C17C6AF4ULL, 
            0x87441F1099E02F60ULL, 0xFDD064A03117981BULL, 0xA9253BCBE4DE1917ULL, 0x8F0E983B6420B54FULL, 
            0xDCDBECDC386DD2A6ULL, 0x4606042E26DA72CFULL, 0x3CC7D51EE2D28895ULL, 0x70CCC919093E42B1ULL, 
            0x390DDE18C1473D50ULL, 0x4B891DA3041C5914ULL, 0x8647F84673390786ULL, 0xEB9B27C490311212ULL, 
            0x5FFAEB381A301C15ULL, 0xF63E3E813A8AD844ULL, 0xD2551124016851CDULL, 0x928E7A4DE23082DDULL, 
            0x9D586454CBBF16F0ULL, 0xCA7FBD11B18A9031ULL, 0xF2731294885A7E94ULL, 0xD97409447CCDB07CULL
        },
        {
            0x553EEA8519E726ACULL, 0xF9A41160A8FF3CF8ULL, 0x717B5828866C8ECDULL, 0x4AD6B62286A086EFULL, 
            0x5DB31DE1BAB6FB20ULL, 0x355F688E8DAD3957ULL, 0xB432F2EB9150E297ULL, 0xD9E39B1E82832161ULL, 
            0xA3E456E8A71629F5ULL, 0x4C57139490847C27ULL, 0x2D6BAA39AB76A779ULL, 0x4DF2F8AC316EE059ULL, 
            0x4710DF44DAF51302ULL, 0xB0CE07EE0AA2E2A4ULL, 0xE7B94373DEE590AFULL, 0xE29535DB43FFB3D6ULL, 
            0x082EF32B8E9B52E9ULL, 0xB5ACFB3AA803159EULL, 0x1AD75600DF598137ULL, 0x972D2568BB0F9813ULL, 
            0x7DCDE2BCEEE38643ULL, 0xBBE6106F469E8F81ULL, 0x9BFE331F8DE29870ULL, 0x1819B4E840B4B5C0ULL, 
            0x9814C10FC7DFDB16ULL, 0xA6C9025640EFA10DULL, 0x6E96BD49D2CB8FF2ULL, 0x7E47D8F1178AADB1ULL, 
            0x2698CBB1622ACB2BULL, 0xC3B8F51695CA59B4ULL, 0x2116A99B8B4B8E1BULL, 0x157FE888CF85E090ULL
        },
        {
            0xE3855375ED923552ULL, 0xA5C22B38AD4BBFD9ULL, 0x2A6793299B472593ULL, 0x59707DDBF93AB0C4ULL, 
            0x1831D79F1298B3BCULL, 0x0D5887333E363212ULL, 0x413CDDC7A4783FA2ULL, 0x0BE12ED207C09FECULL, 
            0x74632585FF60FF87ULL, 0xD3FBF0B038D7E04FULL, 0xB8AE956A687DB617ULL, 0x4A7AD9670528AB20ULL, 
            0x6707EEC6578A1BB5ULL, 0x2A7F61A91AEC2772ULL, 0x095A2A89A69DD372ULL, 0x5307A611972284CCULL, 
            0x17E308EDDE74685BULL, 0x3D57EB59DF4CBDC4ULL, 0xE8A0C13F77197AC7ULL, 0x581BED6F70B0F64EULL, 
            0x1E122B7B810F4858ULL, 0x503315FFBA9DA5C6ULL, 0x9160119D5381633CULL, 0x5FE21F810F005911ULL, 
            0x0092715D328E921AULL, 0xCADB760C8A586046ULL, 0xBEF8148A1C15CF01ULL, 0x72213DDC9A60D751ULL, 
            0xB39276625871D077ULL, 0x0CF7D91B21181D73ULL, 0x74A08CA135B242C5ULL, 0xD028FF19B889B066ULL
        }
    },
    {
        {
            0xB3F74832B874259FULL, 0x06553D3EF7C5C269ULL, 0x7C26E72D00D3E814ULL, 0x4BBBBE7539ED0880ULL, 
            0xCAC4A2490EF0EFF1ULL, 0xFC6AF5BD48CE8FA3ULL, 0xFA3FCB8A0D074BA2ULL, 0x2311226A0673A0E0ULL, 
            0x2335D9F0F6168AE6ULL, 0xE1A2C9FE71CFFDA2ULL, 0xF30F22DB7BC92A4BULL, 0x33D1B62D1DCFFED4ULL, 
            0x67B1FB888305268FULL, 0x759A7AD8290A073BULL, 0xA4AB185EF7A009FAULL, 0xF6B4E420649B800CULL, 
            0xACA3DDCC72504782ULL, 0xF25EDF8EA48C5DF3ULL, 0xE16E86D064AAA3D4ULL, 0xA18DBC2A4AD8FCFCULL, 
            0xB348AA5A9DFA8809ULL, 0x3B68170DA46DC0D4ULL, 0xECCA454BFA2EF2C8ULL, 0x83DA97459D6960D0ULL, 
            0xCD8E803F9107D227ULL, 0x823EBC8D65D25401ULL, 0x263C9E593C2DB824ULL, 0x25A3E92557D702ABULL, 
            0xF43E049079EC946EULL, 0x7D59549ADCF3D1A3ULL, 0xF394CB298145B3A3ULL, 0xA614BC341B59CEC1ULL
        },
        {
            0x3914405FBA0273AAULL, 0x1E0ABE1670795077ULL, 0x799B337C86492D06ULL, 0x9F3A8C9B255D43A1ULL, 
            0xE6E4760ADDB086D2ULL, 0xC5CEE0249C41E663ULL, 0xB2D3075520CC8768ULL, 0x389B90BD2F361F0DULL, 
            0xAD02B7A3DD91490BULL, 0x7F521C232FCA34DDULL, 0x9A7C586E8BB3144AULL, 0x49BCF47D7B2F6699ULL, 
            0x603C06F7341C81C4ULL, 0x5A2EB36CA9749899ULL, 0x07C31A183F0C823EULL, 0x7B71174E1B09604EULL, 
            0x7AE031DFF49CC7F4ULL, 0x47D10A5D9ADC5B2FULL, 0xD14EA1EA92238963ULL, 0x045709F78F088AE1ULL, 
            0xB3B53C3F3F3C6E87ULL, 0xC3689E093D35B45AULL, 0x740C246CD66D6A25ULL, 0xC7CA0369CF0543B5ULL, 
            0x4FA654EE557E58EFULL, 0xD25C17E4196832E0ULL, 0x36CB18D6B180CDC4ULL, 0x0537145105E18929ULL, 
            0x677A256437C2C448ULL, 0x1F0AE16C5B409B01ULL, 0x34274487E74203EBULL, 0x84FD5F4A3ABAE81CULL
        },
        {
            0x026CC60181C49BE6ULL, 0x51A0FB6C5D7DEBF1ULL, 0xCC9CAAE27807D183ULL, 0x2A41376D94A27977ULL, 
            0x56EDEFD341619C28ULL, 0x322F547A37EEB584ULL, 0x7DB7FD78DA091E0BULL, 0x9DA85A86E7E0AC16ULL, 
            0x3781780376C4CE90ULL, 0x1DCDFC7D88DF20F4ULL, 0x3207B44CC0DF24FFULL, 0x025C18C52313125CULL, 
            0xDC0DAC3A146C52AEULL, 0xB93762C7C26B42BFULL, 0x4EB08912CB34A16EULL, 0x758D2D46E5DA1970ULL, 
            0x5DBC487454A561BBULL, 0xC7710E7E0D932C40ULL, 0x6E9C49F048B18362ULL, 0x9FD882CAC3175983ULL, 
            0xB2757EBC16045FFCULL, 0x41E3E3080BD28E8CULL, 0x5C04BE888B568121ULL, 0x0BA56D87B69287DEULL, 
            0xE9639532630845C7ULL, 0x1CD17806155D16DCULL, 0x674660AC76704B6FULL, 0x8439AF4A78F1EB14ULL, 
            0xC81023D6D480D0AFULL, 0x57B7069A6803CF9AULL, 0x130245F19B48A0EEULL, 0xD9881ECA18A8BFA4ULL
        },
        {
            0x53B7FC6B280C5B0DULL, 0x9E655C4ADEA5020CULL, 0x00E4832B92AE6E85ULL, 0xD557D71C61D4BD22ULL, 
            0xE06761B3AD839A1CULL, 0xDCEDDB9B58CDCE40ULL, 0xD637C0D57D97CA21ULL, 0x5CA2983033468444ULL, 
            0xC9C80F2FC45465C7ULL, 0x32C39752EBF0E425ULL, 0x8EDBE8F35C48BEDAULL, 0x33AC356338718A6EULL, 
            0xE30CA7BAD147EC79ULL, 0x34051C4D7D5EB28EULL, 0xFA628FA6590CD07AULL, 0xC95EF41A9BC7AD01ULL, 
            0xAE6621EA75748F4FULL, 0xA311C3D92D4C0868ULL, 0x175F1DC79DB7CEF6ULL, 0xCA27D5FA39E5017EULL, 
            0x36361B154E837652ULL, 0x119EE3DB26A3A87DULL, 0x1F5B06A276493F47ULL, 0xEBC24271EBE1CC5FULL, 
            0xB47CBE2E9D65030CULL, 0x4359D5FC1B5C8F18ULL, 0xCB3AEDB6CEA76308ULL, 0xDB4610B2A2766E6DULL, 
            0xD486ACEEC8CFDB5AULL, 0x1E72573EDB7824B5ULL, 0xAD966037E00BF4B0ULL, 0xC4F66DEFCB034457ULL
        },
        {
            0x6A06120FEDC4F79CULL, 0xDA61F4638ED1A0C0ULL, 0x3A481AA980CAD643ULL, 0x48F3203E80110E44ULL, 
            0x01BE2C65F64C5C96ULL, 0x246E1D8FDE7C3904ULL, 0xA4E178E386BA4AECULL, 0x04AB4113308FF2AAULL, 
            0x9545BCBB264E79CCULL, 0x3E84D09C5125EE0FULL, 0xEC51111C223F61C5ULL, 0x505CDA89D5121537ULL, 
            0x282ED83DD5E757E1ULL, 0xBC1B1D7DD04A081DULL, 0x452AA0B41C01065EULL, 0xC82587A8C4FFB99AULL, 
            0xCCAC01EB9E4332F6ULL, 0x9F2934A1289C3548ULL, 0xAD11B9EBD80ACA9DULL, 0x461153C0D4029A77ULL, 
            0x98EB1A6D1DB89957ULL, 0x43570768FA90F579ULL, 0x612242496F2740DFULL, 0x24E55AF659BCED28ULL, 
            0x134E69D0804B8A8CULL, 0xD3807A0371E5A4C8ULL, 0xF718841FE8C503E2ULL, 0xDE0DEAEF8E3FBB12ULL, 
            0xABE24E7213EB4073ULL, 0xEC25B1B99A3DADE6ULL, 0x0635414C72885A55ULL, 0xC15DB603B95D5C63ULL
        },
        {
            0x2FBE207BEC78BF44ULL, 0x9D4E2F1102C412CCULL, 0x4E6E924D6E5AB43DULL, 0x77F344901ED800E8ULL, 
            0x5C0FC9F27886C91FULL, 0x400C536B23FAA259ULL, 0x378EE496897E8508ULL, 0x1CF1C43D6E6A0AFBULL, 
            0xD352044571934B33ULL, 0x0098AA2B348C9338ULL, 0xD2AC4E7E7D726D15ULL, 0x6171AAC592C5B6A2ULL, 
            0xB55E74B25BF62020ULL, 0x3A6BA50D58D7F7C1ULL, 0xFCED12382769C35DULL, 0x4A5B397D29A668D8ULL, 
            0x8694FD5F1B42D03DULL, 0x38132DF015239981ULL, 0xCF33974DA4323D97ULL, 0x4C5A17A21C26C580ULL, 
            0x4F48D965459C51DAULL, 0xC6880DB61BE7C9A2ULL, 0xBD8D4A0C1BB4F9D1ULL, 0xDD7E9D43B53FD562ULL, 
            0x406C4B59D6AB5A49ULL, 0x9954C3CD233575E0ULL, 0x9003446F51D8249DULL, 0xB5260EAB4E780274ULL, 
            0xC40FC4E9EBFB3A85ULL, 0xEBFAE041D35CA23BULL, 0x6C04349496A2D748ULL, 0xCEFE1EA0C5F7B2BEULL
        }
    },
    {
        {
            0x04741243DE1D3E95ULL, 0xDE2E4738C5AC558AULL, 0xDA22D6EFDDC1DE23ULL, 0x6ACA60FE0746F165ULL, 
            0x911A723AD229A1EAULL, 0x0067C589863A613EULL, 0xBBB747148C08F1F7ULL, 0x7DDBC397765614DCULL, 
            0xDC9DCE16B855EA5EULL, 0xDF63C249BBA41FFEULL, 0xE6FFF9A6C969661BULL, 0x9CB6E5F62EA2320CULL, 
            0x4E1E0803E70E1354ULL, 0x843872402EE6A815ULL, 0x85609C223306171BULL, 0xA8CFB23FE4DAAB2AULL, 
            0x9CAB29CE2913D531ULL, 0x04183E374EF9F009ULL, 0xF89EECADCD96D53BULL, 0x3D2F6FCA0AC7AB17ULL, 
            0x5B6814C2180B9729ULL, 0xFC57900B9A9B6B76ULL, 0x90749B28B244E51BULL, 0xDC54CA33B76399A0ULL, 
            0x79D7ADDADF4750ECULL, 0x38E36A472302EDEAULL, 0x7E909680264E954AULL, 0x8BF004C826A46E59ULL, 
            0xE9EAC3647E49E472ULL, 0xE3FEAA73F5AB5DF9ULL, 0xEDEAF98212754A93ULL, 0xCE31F4E5D4CDA560ULL
        },
        {
            0x9613434F1A3D5425ULL, 0x60509C5BC8122381ULL, 0xF29E71B4D05782C3ULL, 0xACEF2A5EACBB341DULL, 
            0x541C985F99D7B62AULL, 0xD5482878D4F5517EULL, 0x92E66C657B522AE1ULL, 0x5521757E9256104FULL, 
            0x7BA798274B88AD77ULL, 0x853FAD4EB32C9602ULL, 0xF43F4F6B34B8A797ULL, 0xD4BE823A6559AD5BULL, 
            0xF1B125D3E20FE4D5ULL, 0x08650D0385FBB34DULL, 0x44FA6EE25AAEF2DEULL, 0x216406B0F607C608ULL, 
            0xAEE800349FD1EAC8ULL, 0x881F862EAD2B8152ULL, 0x719CA3F2BF4C21B9ULL, 0xC3847F34C85AA71EULL, 
            0x0F6B73EE6EA3BA03ULL, 0xAE824B9455DF1DB3ULL, 0xA3694B508BAE4E95ULL, 0xE9F3887B3A2F5E42ULL, 
            0x8F289C9FFCB4352AULL, 0x1854D4AE76D71960ULL, 0xDDF36DD0390DA480ULL, 0x7265ACE75FE1272CULL, 
            0x4DC5BD331AABDEF2ULL, 0x386B1D30DBE85BFFULL, 0xD5CF8D5F34BB2FC1ULL, 0x5E9C4F9AB85AAEB4ULL
        },
        {
            0xC65F0648BDA65EA4ULL, 0x794E84FA270E0ECFULL, 0x02A365BE2D76F9B5ULL, 0x089C730C68F724EEULL, 
            0xCB99C42B34A7D9BDULL, 0xF8B2B94222744034ULL, 0x4A3CD016D3524242ULL, 0x4EF04DF49B7F872AULL, 
            0xB070D314EBB42FFAULL, 0x820A148CC3DCB70AULL, 0x4F91C001D0CC1E65ULL, 0x70AD23EF6398B27EULL, 
            0x102509ABB794C1C9ULL, 0xC20FE002CB1557F0ULL, 0xEB921F9121308AB4ULL, 0xBEFDD0D202C79689ULL, 
            0x33C73DAFEED29960ULL, 0xDF62A2431948952EULL, 0xD96F5B563B7F4C34ULL, 0xBB50445598138D9FULL, 
            0xACEB0845969B0881ULL, 0xDA88BACBB0DDC288ULL, 0x0A6590FAF78BA151ULL, 0x18DEE0543B1A02EBULL, 
            0x398A2027197ABE71ULL, 0x570AFF4B48A17A17ULL, 0x2F6A290BD964FC10ULL, 0x549E34BF2FAB49A8ULL, 
            0x110FDE2AB9C8093CULL, 0xCD06DE4E05D68754ULL, 0xD8D7D0525D92582BULL, 0x72224A9C2BC31130ULL
        },
        {
            0x5F6896FFDBADC428ULL, 0xD0E52FDC3368CCE9ULL, 0x95F11033ABBF3924ULL, 0xF546E73BAA8C7DD9ULL, 
            0x23FC7FA3E9B3FA59ULL, 0x1DA4403F1C2DBAE8ULL, 0xA59272B2F9AC99FBULL, 0xD649F0A00E4A1318ULL, 
            0xCF13BA65BCD77000ULL, 0x4457948F598D2E64ULL, 0xA67E7F209E7AE003ULL, 0x7589722F867F60B5ULL, 
            0x7BCD25285A8CEC24ULL, 0x3E37CA31CDD8E0A6ULL, 0xC47E8D6FB4243E3DULL, 0xB6C255F2ABE662D1ULL, 
            0xF50F3264ED1ADD66ULL, 0xBC0560A59775BD08ULL, 0x54D33CA8E75EE96DULL, 0x8415BF6C7EBA4B85ULL, 
            0x6763331BEDDA05BCULL, 0x74178722415E7C22ULL, 0x3A92CB8E842CCB0CULL, 0xAF6006544B1BE47EULL, 
            0xC969FAE9E60BC400ULL, 0x8596B9E917455B47ULL, 0x45368D7EC220C197ULL, 0xEB7A5D95D731E03EULL, 
            0x6002B410626E47BDULL, 0x0DED9037A632BDD5ULL, 0xB6C22E545B7BEF8DULL, 0x4ACDD86E10BE6681ULL
        },
        {
            0xC213BF9442EC321DULL, 0x7440DFD91888A1FFULL, 0x6A16C2D341E154FBULL, 0xC7A4FA8060DE1314ULL, 
            0x74CC639E358505E4ULL, 0xAF955FBAF5A1589BULL, 0x4C37B49D482E6722ULL, 0xC5E4A8F9327570D1ULL, 
            0x28A57D76F8BC885EULL, 0xCD9B61CC7B441573ULL, 0x798A83AF0F18E47BULL, 0xA4B673278D0E2E0CULL, 
            0x84420B485C75EECCULL, 0xACFB8BA42FBDBA8DULL, 0x24336C5C99B35794ULL, 0x0D717BA9B6D0B9AAULL, 
            0xC187D6E0213A24DFULL, 0xDD2176F028DA76D5ULL, 0x09323B2BEFF07DBEULL, 0xB32A4D8A7D057AB5ULL, 
            0x940796A0FFE0676AULL, 0x9CFFB0903B2ED1C5ULL, 0xF5CD0C66C8EEA51BULL, 0xE638256B29292C7EULL, 
            0xD2B22EA6A913A0B8ULL, 0x54528BBCBDEB0B67ULL, 0x88207E9B7E31B6D0ULL, 0x3C7165FA7AD8AA0EULL, 
            0x0366AA84FF0CFD81ULL, 0x0C9DC7BFA7A42CD5ULL, 0x792923663851B3FBULL, 0xDC410936C3C71893ULL
        },
        {
            0x6F58AEBEC8B4A563ULL, 0xC9A31470CAB691C1ULL, 0x09C5312E39576EE6ULL, 0x79C56A149E0895F5ULL, 
            0x6FE1E470870DC2E8ULL, 0xF8FC6D0B891A9B19ULL, 0x807EE4B0A31B7FB5ULL, 0x2D281ECCCC042088ULL, 
            0x760EA93795779C54ULL, 0x147975FC89F41C8EULL, 0x8CE0B4B869A9A88CULL, 0x0BA370B75CC4F782ULL, 
            0x0D945CF75F98ED61ULL, 0x17362C61F01533BBULL, 0x948A7E4539BC88CCULL, 0xCB826A1CF802BFCDULL, 
            0x05E7E07C44DBCFD3ULL, 0x3403E3D4E1289DC7ULL, 0xB556355F7FFE23ADULL, 0x15FA4F0278BC1939ULL, 
            0x6DE9A33DAB0C802CULL, 0xA210FC90EFF3CA65ULL, 0xFB89A24E5BDF9D8AULL, 0x40BB4C12A4E9CC83ULL, 
            0x8E0465FA71C7ED69ULL, 0x2A4D9FB3C14EE6D4ULL, 0x35AB23FB5C00D586ULL, 0xA8368113A662551CULL, 
            0xDD34FC75E5FB96B2ULL, 0xE26BFF25D8137A16ULL, 0x0DFE8F78D1CAA452ULL, 0x69B9A8902F1CD167ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Betelgeuse::kPhaseBConstants = {
    0x097675A6867511E5ULL,
    0x4318B41024EE6545ULL,
    0x080CAA290741A629ULL,
    0x097675A6867511E5ULL,
    0x4318B41024EE6545ULL,
    0x080CAA290741A629ULL,
    0xA53BC172D77E32D0ULL,
    0xD42FE6BBEE0116C3ULL,
    0xE7,
    0x2B,
    0xEE,
    0xC3,
    0x89,
    0xB6,
    0x80,
    0xD6
};

const TwistDomainSaltSet TwistExpander_Betelgeuse::kPhaseCSalts = {
    {
        {
            0xCAFFE966A8E0D7A2ULL, 0x03454ECC851102ABULL, 0x5ADC80B9B6587E21ULL, 0x3235C18D284A0809ULL, 
            0x6AAD6683DBAA5ACCULL, 0x069DE9C4534E276AULL, 0xE7F3D2E5F1E245F3ULL, 0x3C4936C919DFA09BULL, 
            0x7E88227F23387504ULL, 0xA916FEB53213E234ULL, 0x6E5E2CD5A8D8F237ULL, 0xB587437F51D82E32ULL, 
            0xC4CFC21F7A91CEFEULL, 0xE027CE612E7610CDULL, 0xE3D2966889C260D0ULL, 0x564B8B614230BCE4ULL, 
            0x3E88313C656FA146ULL, 0x40F378198848D21DULL, 0x0C7DFBC772F4D338ULL, 0x33EE122DE38943DFULL, 
            0x534DDC305F51E054ULL, 0x48CE4B2FC14092B5ULL, 0xCDC41F161BAE17D5ULL, 0x9FD79994E5825268ULL, 
            0x8304D2E55B69C36FULL, 0x4E530CA7F787EC8AULL, 0x9F80D54433994438ULL, 0x13844C0E2DAFD179ULL, 
            0xCBE8C41BF093B2D5ULL, 0x5D2F9523DAC91346ULL, 0x611A0490D7BCDC4CULL, 0x8ED539BFEC8B3442ULL
        },
        {
            0x1F54078E4971BAD1ULL, 0x7EFF09455FB2AE4CULL, 0xA24FA8AA5DD85D21ULL, 0x8BC823EC81EC7570ULL, 
            0xE390DD9D27303148ULL, 0xA5B61C8CE480B92DULL, 0xE712CA9E1C8B041FULL, 0xC677E203876C56A0ULL, 
            0xE2DDF365D6FD3EAAULL, 0x960FC1CDF0B8F5C7ULL, 0x126F09C1A56490E5ULL, 0xD510CFB805A5F225ULL, 
            0x8E27CD532DDAD194ULL, 0x51CA0907CEBE79C5ULL, 0x1886DB5FFD470443ULL, 0xEC28997FD2A0FC20ULL, 
            0x16132D1D14EB2DADULL, 0x132E57477420F26AULL, 0x04AE7FA0FB992AE3ULL, 0xA714C2388A70E0FAULL, 
            0xEF243B2FC1520005ULL, 0x373A8124D1667173ULL, 0x396E8CDFF5162FC1ULL, 0x3971A01112E19D98ULL, 
            0x36A507D233DD3985ULL, 0x7DA06699161BB364ULL, 0xE3890F5414AD68C6ULL, 0x0838A29C66DDC4A7ULL, 
            0x18AC91A3E8B101BBULL, 0x1499A9F55829A44BULL, 0x0CB1E563B0671FC7ULL, 0xC86C68C95D4AEECFULL
        },
        {
            0x3C05249B3A6CB319ULL, 0x34D16390198A092AULL, 0x34E320CFC2895FA7ULL, 0xF75E94C5374DB309ULL, 
            0x323EA5214809CBE5ULL, 0xE5BEFBB05C48C512ULL, 0xDF60925CEF6C7E5BULL, 0xC91D9C7AF170BB03ULL, 
            0x39F685CF05E9319FULL, 0x7FD7038155CCAB0CULL, 0xC0846F77EA2F7B8CULL, 0x90F32D2CFA664E49ULL, 
            0x3168526E253CC478ULL, 0xF10318060D819E45ULL, 0x297488CDE9D6592AULL, 0x5729D0FA638B07B6ULL, 
            0x5E1B8D2CF3C83719ULL, 0x93EFC95E100E0663ULL, 0x2E5824B449A7919EULL, 0xDA2FF38E4FEF1CD6ULL, 
            0x9413C029FAAB027CULL, 0xB86B23EDA9659252ULL, 0x8A3E278D4FC5EDC5ULL, 0x94070BA26471111AULL, 
            0x77C8E8573E3E8391ULL, 0x847B9BDBBE01793EULL, 0x76FFE5510EDD998CULL, 0xCC45F302BE04FF4CULL, 
            0x56877F1F889BB723ULL, 0x1AF7AE353BE3C332ULL, 0x6051BB0C19396BD6ULL, 0xE9188141A394642BULL
        },
        {
            0x6A6CD0F87323FB14ULL, 0x39159E60CD505862ULL, 0xED66DC2E4D561E0FULL, 0x25E63B9E6BB9FE2EULL, 
            0xFA9FDB466670750FULL, 0x8415ABA5B11EB6BAULL, 0xAAF71D4BC79D8733ULL, 0x9FBCC72825EA2D3CULL, 
            0x783FEBAA7C2E5736ULL, 0xF4F3C37220881F34ULL, 0x551A02411329E90AULL, 0xC53E8336BE12E9CAULL, 
            0x8C2FB9CCA3FFB3CDULL, 0xF57F5EF752B87F75ULL, 0x42D952E41120D955ULL, 0x4F3B441F902BDC18ULL, 
            0xC9FEF1088DA4EE68ULL, 0x29264C9BF36CD9ECULL, 0xEC63C2DF63D76F5CULL, 0x136B1C68E59E8B39ULL, 
            0x0A94F59A16287AE0ULL, 0x4E56BE5227387A2EULL, 0x286CECFE4A6D896EULL, 0xB891D338AA8D5C4EULL, 
            0x223545EC6A2BCE63ULL, 0x44545F66C8FBFA53ULL, 0x9E5268CD12B0255DULL, 0xC5CBE5A7BE793125ULL, 
            0xDE09C27CD08A6A3BULL, 0x740EC5EEA9F27754ULL, 0x7FB7643791CF3A4FULL, 0x29BDC14EB52ADDCEULL
        },
        {
            0xDB06DF97FC7857AFULL, 0x9ED76762A4347E70ULL, 0x7D0CB66306CCEA72ULL, 0x4E68B9E082E86CFBULL, 
            0x96A3F5596F0D882AULL, 0xD8284C3D58AA3920ULL, 0x3F51AAB8F87F05D6ULL, 0x5FFD0E759C261792ULL, 
            0xAD7C315AACEACD9EULL, 0xA500B856C307504BULL, 0x2C39857A8CC4D70AULL, 0x813C5D645DA980AFULL, 
            0x1BA734DCB3453980ULL, 0x5DAA5A62C4C848ABULL, 0x31D3446C6629801AULL, 0xEDA0BFC1AA148E03ULL, 
            0x318C30C11C39D064ULL, 0x4912E1BBC4B7A8D1ULL, 0xF3F97FEA20662077ULL, 0x66AE2190373C6267ULL, 
            0xCD5DBC43DB761FF9ULL, 0xA273A99D57A92E6FULL, 0xAC935D33E5A40A02ULL, 0x57A0720C61FD689CULL, 
            0xA4ED32C6167A8052ULL, 0x7890CDC8F35144F0ULL, 0x6C738A48E347B13FULL, 0x9643331CD7F0BB02ULL, 
            0x4DD35A6C7D422E59ULL, 0xFA8447AC2ED68D73ULL, 0x8AE2E35E9458154CULL, 0x71060EA5769F18AFULL
        },
        {
            0x7AFF6558A302E85EULL, 0xB207DE0EB71BAF48ULL, 0x0E317E3865F87D39ULL, 0x66157BA4F5DB372AULL, 
            0xB72ED6BC65955918ULL, 0x1F2AA92DA1B9FD73ULL, 0x5586360FF2367274ULL, 0xF210AD79823BE9DBULL, 
            0x8EC3B6956AFC4CB5ULL, 0x4DD014D3C009AC14ULL, 0x61D9D3AC824C4B3FULL, 0x652F09F360D2C26AULL, 
            0x4572EF30A1A4F8C9ULL, 0x64A7E14804A08F9BULL, 0x3D04E3E509768F13ULL, 0xAC0633BB960BEF2AULL, 
            0xE8423B8F2C9DDDBAULL, 0x4F4EE82A55FA1C0EULL, 0x95240999E7D5E710ULL, 0xABC6CEBEAAFE6E1AULL, 
            0x66C6E7396BBC608DULL, 0x8FCE29AA80A4F65FULL, 0xC4825DD3DE11ADA2ULL, 0xFDF1F81494CB1AE7ULL, 
            0x7375D521F278C828ULL, 0x21847A92C93B0316ULL, 0x217D9D00C9F13D36ULL, 0xFFDCDF67FC90AEA6ULL, 
            0xA1F77E24B1E681D3ULL, 0x61C8CAFA2FBE6F94ULL, 0x591F462D48CAF740ULL, 0x2E0F0904BC4F70B5ULL
        }
    },
    {
        {
            0x146AEF7AE5C2ABB0ULL, 0xF9455B198AADAB42ULL, 0xBFE1EEA308F92BA4ULL, 0x698E7B7B8DC111A5ULL, 
            0x68CA9AC1CF018D94ULL, 0x2CBA2A42DC595AFDULL, 0x7B7AA83E35CEA339ULL, 0x98B3645B403562FCULL, 
            0xCDDA4A818FCBF589ULL, 0xA37FAEF0977DDFE2ULL, 0x1398B6D9CA3F5F16ULL, 0x4FBB3FC17A7DE0E4ULL, 
            0x588DE7541D635884ULL, 0xEC8BBE4DAD680704ULL, 0x8765AEA66B4FB2ADULL, 0xA5784D8214DE0090ULL, 
            0xB98E92F00BE5451EULL, 0x9C79389A5EFF3C2FULL, 0x4AAEF56AC34F98CDULL, 0x69B7721F98841ECAULL, 
            0x9A234EE217CE0EB5ULL, 0x81A46883DBAED40FULL, 0xD5C38FAE8B74D03CULL, 0x931D3F9D2F6E6143ULL, 
            0x2875878D08449409ULL, 0x1B2974F4D7050DDAULL, 0x4DED21628983DFAAULL, 0x6D3372BD1A25566CULL, 
            0x525DA96FC21F10B5ULL, 0xD7A8F4AF1DD27EE3ULL, 0x4EBE379FCAE489A1ULL, 0x808948B35A4413EAULL
        },
        {
            0xC03C61F3C8F3D894ULL, 0x2131AA0414918B73ULL, 0xD1939F46C899BA07ULL, 0x4CBA52E2C8AA4874ULL, 
            0x51F94BB0E0291EFDULL, 0x346180AAC85D6520ULL, 0x3DBB5D9BFE479B2EULL, 0x4074167822CF0B2DULL, 
            0x390F888F93507473ULL, 0xA16C1E88F4E71478ULL, 0x732DF167D6393134ULL, 0xC92EF398E11A6992ULL, 
            0x365AE849EA25D396ULL, 0x610E3191E3ECC216ULL, 0x07C70D01522393D9ULL, 0x212EB2FFD791EF7EULL, 
            0x3BFEE2F58F2BBF21ULL, 0xC91E4C30C3BC64C5ULL, 0x05833B6AC8F20ED7ULL, 0x3EE9DD839B1A36F8ULL, 
            0xE7CE99A1D11F31A4ULL, 0xB96F1BAD9B1BC569ULL, 0x01220DC087FC53E0ULL, 0x9F7F26CA90E47F48ULL, 
            0xA97939E2BC56DA43ULL, 0xA0C7A22F96E1E890ULL, 0xC04FD1825B5647A4ULL, 0x7979629FE6282D5AULL, 
            0x6096070F920CF309ULL, 0xFDBBF77F5932BC1FULL, 0xB077DD0844B93474ULL, 0xF34836AFCB455D21ULL
        },
        {
            0x3878D5ABED6D28F5ULL, 0x214180D8960EC155ULL, 0x07BA9F166AF33556ULL, 0x22203747A2F64E17ULL, 
            0x1AE4DEF2328C0E6BULL, 0x63D70CBCEDCEA554ULL, 0xC06DBE3A4E5026E7ULL, 0xF8633319597AE5BCULL, 
            0x6AE5D6F5E488ADFCULL, 0xB86B94C48A278280ULL, 0xE486FB9C7A62BC63ULL, 0x51F1C532DADF5891ULL, 
            0x1FE75BA49FBCDCFDULL, 0x4053C5DB4A29AA1DULL, 0xC2FEEBA3DE48155EULL, 0x92C4433131FD39E5ULL, 
            0x40B9A520548B8206ULL, 0x97F8267B6B953543ULL, 0x1122DB9FF11E19F6ULL, 0x4220FB4BA770376EULL, 
            0x286CD0742E44BC6BULL, 0xE40A01EA4F4B7E6BULL, 0x252A99ABB2EB9CA5ULL, 0x8671FB3167C953DEULL, 
            0x95F83DA687AB07C1ULL, 0x004092D80E47CBC7ULL, 0x60546D567703CAC2ULL, 0xEEB5B13ABE2E9DE6ULL, 
            0x7F0C9F48C19F30C3ULL, 0x6931C232184F146AULL, 0x983233E6DD30C4A6ULL, 0x54198BBFDFAFC9C3ULL
        },
        {
            0x248A02EAC90AB86DULL, 0xF4FE86E26469B6F8ULL, 0x66E04F4CC9E8D15CULL, 0xC302540EC02A1B40ULL, 
            0x90A68298980843A9ULL, 0x7E34C8D46B7F26ACULL, 0xDED20447CC565463ULL, 0x19FA15843D54C2F0ULL, 
            0x319FF00B86825FF2ULL, 0x41CDC6B12ACDC318ULL, 0x5C6792FCB4B369CBULL, 0x6FB363315C036A56ULL, 
            0xB4A9281CA3FCA6ECULL, 0x2C5079483D460306ULL, 0xAF1379D520D84789ULL, 0xA9660DCC175C7E5BULL, 
            0x07EB8723B1F77969ULL, 0xD4D31018209CBCBCULL, 0x5873871510ABD98DULL, 0x7FA72F00B5E42666ULL, 
            0x510FB170F02CAC26ULL, 0xF21906218DC8B6A4ULL, 0x4672A60DB303150BULL, 0x5EA7ED0B0F82955EULL, 
            0xAD18B116E07BBD0CULL, 0x7ECD23FA4C9A0FBAULL, 0x39685DD4970B9124ULL, 0x8B37DBFF447EEEDFULL, 
            0x3B3227E13BA6FF1DULL, 0x7A79334097760D4BULL, 0x560A9C575CC78F0AULL, 0xF92D0B4EFDB91FB6ULL
        },
        {
            0x022F248B460DBB2DULL, 0x90D185BA0AE2E929ULL, 0x3BC63C10E6E6A41DULL, 0x3CA81A57EF039FFEULL, 
            0x79A5A77781591A23ULL, 0xA0EE75A39FAF8C89ULL, 0x2F959681C4D1436CULL, 0x1E7538ABAEF94B74ULL, 
            0xF4FA4D5AF63736A7ULL, 0x28889FBD948EBF5BULL, 0x312E12DA5F7EA879ULL, 0x944F8A529F01778EULL, 
            0xB901BBEAFE253923ULL, 0x415FE8F88F7DF8B6ULL, 0xA61CFA30EF837D10ULL, 0x9C00ED142F63752FULL, 
            0xB00EA2C0D4B2B8FFULL, 0x9BBBE6A8DBF99605ULL, 0x9AEF890D708F770AULL, 0xEF5C3456D9BDDECEULL, 
            0xBD2D09BF6A1D5906ULL, 0xDA65284A28817184ULL, 0xB92E974DF9587BD2ULL, 0xBFB9459DAD284943ULL, 
            0xA51A3C388443E705ULL, 0x61B940B35B38E0BDULL, 0x7597BAB052B3D22EULL, 0xB5B60A6DEA386187ULL, 
            0x4A403EC0C364EB8AULL, 0x04BD173E42825867ULL, 0xDC0D73828E54F80BULL, 0x7A9687BE7522CE6AULL
        },
        {
            0x1942F902293F5295ULL, 0x31BD52CAB121502BULL, 0xEA736CCC24624D5DULL, 0x4D727A89444BFBA9ULL, 
            0xA95D030412856C1DULL, 0xF9FE79311912056CULL, 0xBCAA4C503042D563ULL, 0xB098AFCF16BBC308ULL, 
            0x359184911F6CF4C5ULL, 0x5E133DFA2B949FF4ULL, 0xC5D099703594C35CULL, 0xAB3E39D38384EDA1ULL, 
            0x7A7D42AEEB1CDEFEULL, 0xFF0A3BE4B14E23A1ULL, 0x12641E99DCE40AB8ULL, 0x3D98C1C28C254483ULL, 
            0xB89A5B3ADE7E26BCULL, 0x9F3B9D167BB56F9EULL, 0x149D214E098B5A38ULL, 0x4325D039B9989DF3ULL, 
            0x1880D2563F611D71ULL, 0x82680F488A2BDEF6ULL, 0x100689468A2E9FD0ULL, 0x17B3E4FE27C591C1ULL, 
            0xC3AB56A06CDE240FULL, 0x9DD2CF96BF7F49B7ULL, 0x16363D29DD6D6025ULL, 0xC61D74958384B587ULL, 
            0x205835604DA7C835ULL, 0x8240A8EC36F9FE51ULL, 0x70796808B896930FULL, 0x873B3FADB9E26C4DULL
        }
    },
    {
        {
            0x63431E4FDDABC972ULL, 0x5366B1DFDDC8306DULL, 0x514AAAB9BCD81680ULL, 0x2C70A9B93E9F9966ULL, 
            0xA0A51787A1F33992ULL, 0x36B9DA5C905BF0B8ULL, 0x6808D4BB0AC823A2ULL, 0x7EC95EDEC223E72FULL, 
            0x3CCC1B5D87B4888AULL, 0x9AE969C743E66EB4ULL, 0xFD2923BF95D4B70BULL, 0x1977125BA95895B3ULL, 
            0x3669AE354A3C3FADULL, 0x2B643EA1F5FE2D6BULL, 0x396C779168D45CC8ULL, 0x8027F89CF637A79BULL, 
            0x187A1799A1CFDF81ULL, 0x572BBAFB7F752434ULL, 0x253A5DEBC0491527ULL, 0xD481DD79B67FF8F0ULL, 
            0x76DD98975FB22C8EULL, 0x3D13F1680DE89B63ULL, 0x76D6C131904DEBA8ULL, 0x414FAA3EC633AB93ULL, 
            0x12B16DB4F2301653ULL, 0x170F400BE387DCA8ULL, 0xB8D25E363A7FE8A3ULL, 0x9BCBB872CCC5EC8AULL, 
            0x964B5FF143A42536ULL, 0x20B484DDC6ADB121ULL, 0xBCE97032328EE30DULL, 0xC5FC56DF43571EFBULL
        },
        {
            0xA830708ECC0A7417ULL, 0xBA2BF074BE971A5EULL, 0xD02426AD8560CC91ULL, 0x5D42D7680008EDA9ULL, 
            0x9438FF865A66C5E0ULL, 0xCAE6DD3671C83D39ULL, 0xF6E58CA67065CF16ULL, 0xFC2E85705A82D37EULL, 
            0x2FF35124F990D97CULL, 0xB3E5FDF0FB2978B3ULL, 0x3E0DDE5F5334F48AULL, 0xFCF63E460912E06BULL, 
            0xF66620DDBBE0B7E0ULL, 0xA79D733C5C916E8AULL, 0xA07A46796D5B6D2BULL, 0x4F4064B072DCF2B5ULL, 
            0x8875F4CA8144D2BBULL, 0xF8C76592EFFC1B6EULL, 0xA4D63BB9BE6219D7ULL, 0x88D25F504FBD0758ULL, 
            0x834DFCD85FBB1FFDULL, 0x52E2ABC034ECD0EFULL, 0x64926121BF661F69ULL, 0xC0D2FC3D9FDEE65DULL, 
            0xC7817FAE4D779AE7ULL, 0xD46E1554907F9EB9ULL, 0x83CC3C96ABF5CA94ULL, 0xEE34D1DDDB938E14ULL, 
            0x0DF83597F2425B53ULL, 0x50467906CB5BB7AFULL, 0xA6897885D50EB8DBULL, 0x5998A0E6EEBD7EDEULL
        },
        {
            0xE0824DD4EB78D18CULL, 0xEE9B13804BD71D61ULL, 0x74625C58ECF3D917ULL, 0x578ED236F6E41866ULL, 
            0xA760DAEB95334302ULL, 0x97567226A4D4B0ACULL, 0xAB4C140308C0374DULL, 0x3FFCA141CDA54F94ULL, 
            0x63E094E1EF08E611ULL, 0x12B18F63D11CFC7FULL, 0x4AB7569416257B92ULL, 0xCEDEE3801EDBC963ULL, 
            0x77F43436E7B87A58ULL, 0xCC4EAF7244580894ULL, 0x92FCE3CBF0B94768ULL, 0x597C316D213B1F9EULL, 
            0x8B2711F7CB9B1DAAULL, 0xFBC077B94AD8BC5AULL, 0xB8D1CCFB1CF10BDFULL, 0xFC6CA621DB2EA948ULL, 
            0x3CCF02A322252569ULL, 0x50FE64DA080351A0ULL, 0x87683CB3219A8715ULL, 0xC2DB157ACDEC3002ULL, 
            0x637FCF24F40962E0ULL, 0x7CFB16204811FF6FULL, 0xB4176B43BFAC5A7BULL, 0x5A40FDCBDDA5BBA1ULL, 
            0xA8A6F05A31B96472ULL, 0xE8282AA06DF72ABCULL, 0xBF6ED62EEF5E6B93ULL, 0x9131DE5334EC178BULL
        },
        {
            0x66B95079F85FE456ULL, 0xBFD42A5797DE8347ULL, 0x01D7904B5130157EULL, 0xB5C6BEE0368EE072ULL, 
            0x2320C6F5793988E5ULL, 0x240A69F2DBE1A4F3ULL, 0xC3AF61CF7B9F7625ULL, 0xAEAFF669960AB9E3ULL, 
            0xA4482E0196B8B392ULL, 0x7C8F8FAF1975DCA3ULL, 0x26DE011C84CF878CULL, 0xD8D37BDC1115AB35ULL, 
            0x731D9AAB396A44CEULL, 0x7926E214405CF0A7ULL, 0x3A7741E63B689024ULL, 0x24BEBDA177593688ULL, 
            0x506CFAE332B83CF3ULL, 0x17BFEE6C2CCDFB99ULL, 0x4EE63F4D80AA3381ULL, 0x5476CFDA9C71BC7AULL, 
            0x41389FD8ABF4E785ULL, 0xD36215F3DE70086AULL, 0xCE6817DAB1B0AEB9ULL, 0x8B1B4D3FCAF271ABULL, 
            0x860A5A8BF362EB8FULL, 0xE6EDB0A627497F97ULL, 0x3F5A27CA85A1D38DULL, 0x102FB98BFDCF5EFEULL, 
            0xFD3FE323E5ECD999ULL, 0xA4C53B4A096D1BE9ULL, 0xA2D287DE63B7D09BULL, 0x9C5F16FF27910DFFULL
        },
        {
            0x3A2F4B6158533CF9ULL, 0x13869489D7CBEB1BULL, 0xC57523BBBCA4CEEFULL, 0x6334D0C33B414186ULL, 
            0x92A810A6DE07E11AULL, 0x23D3595894D68001ULL, 0xCB70E466EA65290CULL, 0x7F6DC6DCA1FFF83EULL, 
            0xB6155C103B456B0BULL, 0x713101E2AA4F7B63ULL, 0xB3A12BCDC3E2F551ULL, 0x6094CC704B8C6BD9ULL, 
            0x354FA7C2C283F88BULL, 0xCA5E8B4A364D6E7DULL, 0x1551D6A9C38B908CULL, 0xB41916C584F0F6FBULL, 
            0x511FF2AB4871D1DCULL, 0x3EA001D9AFFDFF7AULL, 0xDD81C573495032E3ULL, 0xD2C07CB4DAC10AE2ULL, 
            0x0B97C4156D717E96ULL, 0xA7ABC05E7081F3F7ULL, 0x0A019C8201D28845ULL, 0xCD4F41FB5827B0C3ULL, 
            0xE80F04F3D81C4C5EULL, 0x42971BA067AE321AULL, 0xEA485F8C51575604ULL, 0xF17AD71F7A31ECFBULL, 
            0xC421328E0838ADDAULL, 0xD09BA8A6759699D5ULL, 0xD55391F4B3C25B29ULL, 0x9D89CD58B184FBADULL
        },
        {
            0x8301C456B9896635ULL, 0x418640D507293D3EULL, 0xBD407096C10DAB56ULL, 0x258FD110E38904C3ULL, 
            0xCE7DDC0AA1CD1A16ULL, 0x73B27F9A36CB1664ULL, 0x60940D8EC6E364B7ULL, 0x7F19E8B5C0C5CF7CULL, 
            0x9AA66ED47E26C07DULL, 0xF03E48F836CEBA0EULL, 0xA4255541D69E0525ULL, 0xE21D3FA6A5E2B232ULL, 
            0xEAA33B56C4D9C818ULL, 0xB97043912ACA332CULL, 0x73CBA524B0C7E4CCULL, 0x1B07EE836F114919ULL, 
            0xA386B237724F9D90ULL, 0xABF19AF019C3E3E5ULL, 0x1E22FE8F3AA13CA9ULL, 0xBAB4D34914B4C657ULL, 
            0x097B6E36E9203CADULL, 0x03E4FCC13A3F3510ULL, 0xFDC79A9823DFD0F0ULL, 0xF3208BDCB3C8A863ULL, 
            0xE165469C278EFE9DULL, 0xABD9D7DA0D087A2BULL, 0x9DB1D8F4904AA6A1ULL, 0x73DBD0C83F80704DULL, 
            0x32320506CB3403E7ULL, 0xCDBAE03CDBC7D48CULL, 0xD3B4033BFDC64A90ULL, 0x6A0666A3ABBDA300ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Betelgeuse::kPhaseCConstants = {
    0xA504BD05454E13E2ULL,
    0x5D2A336D0B3A1379ULL,
    0xF2B392BE944C372BULL,
    0xA504BD05454E13E2ULL,
    0x5D2A336D0B3A1379ULL,
    0xF2B392BE944C372BULL,
    0x10D9B76148860499ULL,
    0x4E0724D6596ACD9EULL,
    0x82,
    0x4E,
    0x47,
    0xF6,
    0xFD,
    0x53,
    0x4A,
    0xB7
};

const TwistDomainSaltSet TwistExpander_Betelgeuse::kPhaseDSalts = {
    {
        {
            0x90AFB64828B52DB1ULL, 0x30E74584357218F2ULL, 0xFBE6E6C1D55ADEDEULL, 0xF7C5CF5886DAAFAEULL, 
            0xFFED4D80D065AD3FULL, 0x43CF9A489F1A2CF1ULL, 0xA34DB08A900BFBD2ULL, 0x9088EB41FCB31F99ULL, 
            0xFEC05E2CF7402BA0ULL, 0xB2336E94BEA44C67ULL, 0x5B95B11F6C9D4A70ULL, 0x30B489D723C701FFULL, 
            0x9C2064C69B1028C2ULL, 0x993CECB8E56A5E1FULL, 0xD089FDE2185CDBA5ULL, 0xDA240117D6D36AD1ULL, 
            0x0CE174A35CF4D0F2ULL, 0x8821C8FDB441B04EULL, 0x29D87631B4B50D02ULL, 0x97C9DE1380C6872CULL, 
            0xF0F6CE6744EA7E5FULL, 0x8E8ADF0CF2AB8DBDULL, 0x1DAC2923D7C3024FULL, 0x0CA707374023F1F6ULL, 
            0xCF7E9DDAE70A3D75ULL, 0x0BDAAB1AC202B25AULL, 0xDE6906957FA5AE65ULL, 0x437029552F3916F1ULL, 
            0xA0F122160BF98C11ULL, 0x515A2D00B177F488ULL, 0x7A4279B534387D21ULL, 0x7FB6F957CD39AAF9ULL
        },
        {
            0x8BA66000888649BAULL, 0xB2009CF5F5BE5110ULL, 0x0CF559FB503737EBULL, 0x310D6033D4F4E18EULL, 
            0xA675670AEC66D1D2ULL, 0x40029C1F52AA5412ULL, 0x450F42EB0A35526EULL, 0x90687F906E698522ULL, 
            0x78E3C3B7ABB0CED9ULL, 0x5CF1CA0C22424DD3ULL, 0x5764379D92D88B37ULL, 0xB1C4A3BDA27563FCULL, 
            0x0D65FE104F1CAD43ULL, 0x08905A8A801DEAF2ULL, 0xE60206B413C0534DULL, 0x667FFDCFD30D9E34ULL, 
            0x8925457FB3C26C95ULL, 0xF010DC2E1766D6FEULL, 0x3128593855FF988AULL, 0xF0F2F8EFFC9E5CB9ULL, 
            0x3F1AD6A46F97A1E4ULL, 0xAB419A9A272D6B2EULL, 0x22C21FFD25433193ULL, 0xAEB4F7187C8A93E0ULL, 
            0xE6C64245CD11B1C6ULL, 0x19ACBA55DBEEB555ULL, 0xA3916A8903472EC8ULL, 0x87C0F90FDB072553ULL, 
            0x0D30A649F81B6424ULL, 0x53C277A98150CB70ULL, 0x052895620A3736FCULL, 0x366D0A4F18B2608DULL
        },
        {
            0x16EE12C905572C73ULL, 0x9D9CC462A03FF19BULL, 0x6BCDD14B61F26BEAULL, 0xEB237F35E67BEDE8ULL, 
            0xCD3576E94AFCB939ULL, 0xDC12F8BB2689B81FULL, 0xF4ABB3C8945F1DE2ULL, 0x7B7A990E63138AA7ULL, 
            0x3CFF5CD9DFCCC92DULL, 0x722E3FFCFE2E5D0EULL, 0xDFF9FE5FB383E817ULL, 0xE6D7655CC2742746ULL, 
            0xA79295C949CC6162ULL, 0xE7EF6C92E364575FULL, 0x9877B03B66A681A3ULL, 0xD0EB1EA17B2A2C08ULL, 
            0x6A91DE15C3B6492CULL, 0x380A582E9A16FC6BULL, 0x53A154D54435A1EAULL, 0x8F953DF2CFA97303ULL, 
            0x3F0E6122551A88E7ULL, 0x985405FC6F95A5AAULL, 0xC06165F2E3750A85ULL, 0x3329BC0E48B61BECULL, 
            0xA5D2967820582486ULL, 0x5C2B67A91344A93AULL, 0xBCE0D069C368FCC7ULL, 0x2929C7555E7D6CF1ULL, 
            0x158124A2397D028BULL, 0xD98CE0464F01D47AULL, 0x30CB92955FCE7A18ULL, 0x5F5E663F91C0CB0BULL
        },
        {
            0x459F792C6EB4ADA9ULL, 0x61E896C124F01F6EULL, 0x273D2273EEE592BCULL, 0x60A0644C7D0F04A1ULL, 
            0x12F98C791C576086ULL, 0x62746121A4A7850AULL, 0x25236DD67D8097ACULL, 0xED2F9AB7B1C3DB1DULL, 
            0xA7DB265F62DA1CC9ULL, 0x9ED830A78790B087ULL, 0x06D36B247CE915F1ULL, 0x2A3BEE8D27861976ULL, 
            0x652AB0EB70A81FA7ULL, 0xC529E6FEC97EE85EULL, 0x4ECBDA3A1167991CULL, 0x3F5580F25E91AD40ULL, 
            0x896F8BAFF8A1135EULL, 0xFD64BFEF3F2AEC9AULL, 0x50E28C808798484EULL, 0x88BFE3DA91105C20ULL, 
            0x0BFDEF55E7F89149ULL, 0xA4413914B11E5A83ULL, 0xB7945DF94F4F734DULL, 0xA4C703CCD75C567DULL, 
            0xE2C2343ECBE7BF3CULL, 0x38FFB89A8B1BD271ULL, 0x1F21E45A280D3CBAULL, 0xC8CC04EE303B09C9ULL, 
            0x8A1590D68226EB66ULL, 0x7A406D7393C4C361ULL, 0xC47841DB9F63DB61ULL, 0xB291C11196EB3CFCULL
        },
        {
            0x1361EA78FF322DCEULL, 0x03357C5F87DBD7AEULL, 0x57131AE6159C38A8ULL, 0xC28BE75C87746193ULL, 
            0x633A62D2C976B09AULL, 0xC4C48B50136C1C82ULL, 0x2E4AD0E796EC1EF3ULL, 0x6C1524FBA97440EEULL, 
            0x50AFE99F55690F74ULL, 0x6388772BB262F56AULL, 0xA1E0F407BC6E1EC1ULL, 0x455E05364A9F7516ULL, 
            0x6C70E7049BE0789DULL, 0x5C48763A72022526ULL, 0x3B9CB3B8D93C1C15ULL, 0xF855A7FB639FD625ULL, 
            0xA5FE5B96EA80BB6FULL, 0x8656458FF8D3E946ULL, 0xB9E47B156DCFBC21ULL, 0xF9C7B5375F9A3AB8ULL, 
            0x52D51D86A9006C61ULL, 0xDDB2D08036BD3825ULL, 0xF79B9882E055F9C6ULL, 0x3D74F37868800D78ULL, 
            0x57C4FD0885FAD0D2ULL, 0x09BBB03AC4D7E6FBULL, 0x47B8E30D1880C562ULL, 0x10DFE9011A9E7405ULL, 
            0x80C05CE33E639919ULL, 0x03E28F5203227024ULL, 0x25F18A7B06B8FED7ULL, 0x58CD05120AFADAC2ULL
        },
        {
            0x75701BBA83E35B2EULL, 0x6A216B6F68889178ULL, 0xD5CF7D0E62546F54ULL, 0x492A55A4E8FDBA3BULL, 
            0x241F6F921840C3C4ULL, 0x1138318745FD0264ULL, 0x281AA95D45F220CDULL, 0x4EDDA486B59285A0ULL, 
            0x47A36B13A0587918ULL, 0xB4B7617832CD66C8ULL, 0x682AAD97D6909153ULL, 0x0232303C0788E78EULL, 
            0x7F37E0FD814C95DEULL, 0xEDB0DACE21217246ULL, 0x83D1BE625C4EA1CBULL, 0xB8416AD2A0CCD552ULL, 
            0x6087F89442F23C3EULL, 0xB99AEAA1555C2694ULL, 0x11CC571931A7D79DULL, 0x85D15D2D4E53C0A2ULL, 
            0x7BDBC6853DE3D665ULL, 0x2802F14938BDD671ULL, 0x007363DA2F56277DULL, 0x6DC62D8BAA1ABF60ULL, 
            0xFD337CC744FA92E2ULL, 0x0ABDE43A4378CABAULL, 0x7F50AE7785790377ULL, 0x393CD4592A6E7C39ULL, 
            0x3DB04A15C20039ADULL, 0x3756169720589A8EULL, 0x0911D320A092F220ULL, 0x1B5D195F2ECF679FULL
        }
    },
    {
        {
            0xB9BB31E0B7E512A8ULL, 0xDD41DCCA5C4729EBULL, 0x118E1312DA853A14ULL, 0xB9284CEFE632D2F1ULL, 
            0x4EF91E2A06389B50ULL, 0xF49EC5EB242F544BULL, 0x1AB530E332537123ULL, 0x4D618AF0BCEA08E8ULL, 
            0x1D57D1623DDC4EE1ULL, 0x6533A1D25C284AFFULL, 0x59158D4AE269C40CULL, 0xA12B3EFFF48FBD8DULL, 
            0xADA383A06C6250BCULL, 0xDECF51BFFBE68194ULL, 0x86C57B5AF30D3F78ULL, 0x9149BBDD6A57A23AULL, 
            0xB918ECD5EFB2CA83ULL, 0x4A3A4C9F285F7721ULL, 0x2CC6661DFDB4E93DULL, 0xA7EA6D78942B27EFULL, 
            0x45A7FE9C1E48FF95ULL, 0x37C76FC9D51F47FDULL, 0x7A571CC5D158994DULL, 0xAD0A5F628FEDA748ULL, 
            0x9E5C53070ECABB08ULL, 0x7B8D41162444DCAFULL, 0xE353BDEC44657CF2ULL, 0xC779DCB5F12F9A8BULL, 
            0x097C6E0E9B025C8FULL, 0xC915DAF3B5E587DBULL, 0x63007EA942A397BCULL, 0xC3CE1F2D56073C7AULL
        },
        {
            0x2B5C9377739B93F8ULL, 0xAA160109606481BBULL, 0x940D4ED60D66EC34ULL, 0xD7417FD12B0BEF46ULL, 
            0x03DA8EE36688C216ULL, 0xDB885B7C90795109ULL, 0x51DCBD4FC94E1654ULL, 0x59C886877EC331BAULL, 
            0xB1E9D7E25ACB7DBCULL, 0xD3DD68ABAD4774BAULL, 0x9BDAEAB69623C7FCULL, 0xB07015C405CE0A6CULL, 
            0x603E3C9E9742F0F3ULL, 0xF45C3C18DA0C9A91ULL, 0x0901323710507932ULL, 0xC664F1D3EB66F2ECULL, 
            0x07BE428EAE7C497BULL, 0x83393B82A225BAE9ULL, 0x47DA1C43E44B2722ULL, 0xAE59AF8F8C62191CULL, 
            0x15428710941FF247ULL, 0x30E1729427949BE9ULL, 0xB8155ED020D8EBA2ULL, 0x8AFFA000A341F095ULL, 
            0xF452F71800F6C732ULL, 0x1C544D1ABFEA787BULL, 0x0FFB476E6F844243ULL, 0x089B0411463E8E8CULL, 
            0x6AB219013B880296ULL, 0x3DF11F4BF487CAC8ULL, 0x0EB8B2439A1B3594ULL, 0x9C577C629FB11900ULL
        },
        {
            0x21FB81729756D9A0ULL, 0x3263B2AD3316ECC5ULL, 0x1D7CBC35B0B765C7ULL, 0xC1B11E4CA44E53FFULL, 
            0x15D5CEFDB5D5304CULL, 0x5662EE62AE22B57BULL, 0xFACD50889EEBC447ULL, 0x04EE7E0B8D421BFBULL, 
            0x6568C32A0718CAF9ULL, 0xDB21182F9866C850ULL, 0x66FFEABBF031A30CULL, 0xD622B8F3F510779FULL, 
            0x3CB4860F0B5DE9B6ULL, 0xF371901FB2105AA6ULL, 0x4BF337900B4C3BAAULL, 0x0F3950C1CE31C240ULL, 
            0x99FACA7CA012CF50ULL, 0xA2F4563DADE9310DULL, 0xE017D8EA75602FDFULL, 0x3F3BC3A4D3551945ULL, 
            0xE281C34C46DAD2B3ULL, 0x72FF2B305A4DB307ULL, 0x0AB87CFFE8B3E2D8ULL, 0xF8285B0405349910ULL, 
            0xADDCF05DF9409FE1ULL, 0xE84FF7EEC388DFAAULL, 0xF911CB4AB2CFDEEDULL, 0x8A72CDD388FAC4B9ULL, 
            0xE1039197F3A1812EULL, 0x27D00F885381804CULL, 0x31F3158C55565FE6ULL, 0xBED640D6FBF6987CULL
        },
        {
            0xCFDF652CB83B7D23ULL, 0xC39523BD0C403EB7ULL, 0x5161E62FB5A58C96ULL, 0xA3A7C69875832F2CULL, 
            0x44B8F57ABCAB8C01ULL, 0x8F6A673A0A5CB71CULL, 0xBAD0678BAC0B25ABULL, 0xC5CA0AB28C38E712ULL, 
            0xFB17DBA9B440155CULL, 0x06CEF72B600F7214ULL, 0xD3A2C46A94012150ULL, 0xAEA22D57F87B2B5FULL, 
            0xB45B00BCA660F195ULL, 0xABFA334D2AD46B30ULL, 0x5B6E16CD87B2E5F0ULL, 0x65BFFF6229A0120FULL, 
            0x2C6C85BB28D9AC0CULL, 0x76B587688376A9CFULL, 0x6BFE8A99FD1407E0ULL, 0x66800001FF17A3B9ULL, 
            0x54AD6D476E32D7E0ULL, 0x2121E205A902CCC8ULL, 0xEDFE9A0F5FE41D24ULL, 0x819AF3720F27C585ULL, 
            0x07162E4AB3C8D32DULL, 0xE4040ED5D7558289ULL, 0x76C43E178035CAC1ULL, 0x126286C8AB31C157ULL, 
            0x7BE72D58089F442BULL, 0xA95CF39E29804E0CULL, 0xC38CE542D43D1605ULL, 0x86C65D5497BB6878ULL
        },
        {
            0x5588E800AD2DB0BBULL, 0xDA31020E281F541EULL, 0x0E4F9DCD4C6CB322ULL, 0x862A54C275F15D71ULL, 
            0xA0958E6B3EF54989ULL, 0xE22E6C4A497148DDULL, 0xAD96C96FB857FB54ULL, 0x33E84F957412C85CULL, 
            0x9846365CBFEF2D58ULL, 0x6D9E19E89BD1348CULL, 0xED34C97CD450F3BDULL, 0xA341C734AA7378ABULL, 
            0x2C8C2DEBDE0F9222ULL, 0x6DCF90B3A3AB8425ULL, 0x723EA178C59F857FULL, 0xCAF08C3B49E5394CULL, 
            0x2CF447D1497BD6ACULL, 0x981A0919F04F2C98ULL, 0x9DDDCB1A7B18254DULL, 0xF7E03CD97625DAF8ULL, 
            0xA364F23736480288ULL, 0x37456CBE5C95BB6CULL, 0xBA618206E5A538C2ULL, 0xB8DC4527C4ED777AULL, 
            0x86DC1C69F3230061ULL, 0x034A851DF577C260ULL, 0xD883721A38FEF5A6ULL, 0x6D86217751CB1BF9ULL, 
            0x307A9D245BF7B607ULL, 0x5BBD46BEF9C0D07FULL, 0x9E2C25B7CDE2C034ULL, 0x0E10993CB2164892ULL
        },
        {
            0x0211E446DE61D60CULL, 0x6F04BEA0843F420FULL, 0xE344DB7F8AB8DFE4ULL, 0x392E5A134D262781ULL, 
            0xBAF89FFA6460609AULL, 0x52D07183DB17AC0DULL, 0xD4EF25192C5F3E71ULL, 0xE5D4BAE8714171B5ULL, 
            0xA4E370547D5D261AULL, 0x9E074C413628FD92ULL, 0xC5887ABCADA96270ULL, 0xD76E488F1E3C9C67ULL, 
            0xC0700046434201FFULL, 0xDBEBAF53D6913724ULL, 0xD582BFD6A74393D2ULL, 0x8DFD8315A827CAA5ULL, 
            0x281D8C6BD8B7E87AULL, 0x1B6F95A685598511ULL, 0xB46725BCD6D63CF2ULL, 0x3B89BD7F005418C1ULL, 
            0x7CFA43B5610AE6A7ULL, 0x1433DB681CF83A31ULL, 0x277CF68DF5ADC833ULL, 0x7BD9D2FF715420D1ULL, 
            0xD730CEEC96217D2EULL, 0x25B14141FBE26A0BULL, 0xAA613D662F0E7171ULL, 0x5F677FE57A5A6D28ULL, 
            0xC298A93C51113FD9ULL, 0x68C1E46E2024CFE4ULL, 0x960836CC2AE60B39ULL, 0xE90DEF22E9BBCC34ULL
        }
    },
    {
        {
            0xF834C0E6E3C01BD6ULL, 0x2C552D4129F63E97ULL, 0x57264D4A8176544DULL, 0x920E59C2B0EAEC76ULL, 
            0x08248992DC65DC2BULL, 0xAC33A579E17EAECAULL, 0x568EA5D9E12CD4B1ULL, 0xD771FF5A3C97BDEDULL, 
            0xCF1AE7E049470339ULL, 0x91284B1BE0AF482DULL, 0xCA6320BEE165E172ULL, 0x87618FF49F922FC5ULL, 
            0x5A398EA58A283991ULL, 0xDF4E3F231833D38EULL, 0x5179F080FBDFFC40ULL, 0x84609F930A0A4E8BULL, 
            0x7818B619FDC2781DULL, 0x91E05773E53B9768ULL, 0xFDD182DF444D5D38ULL, 0xC6A59572411B1FE3ULL, 
            0xE8DB76FCA36F746CULL, 0x18131D25AF881236ULL, 0x3E0C5DABE578853CULL, 0x91B159C0A7A9D3C9ULL, 
            0x8F44C9D9F5659A1AULL, 0xC527D430AFD75189ULL, 0x012E3463D864CEEDULL, 0xB63A76E8453B8D31ULL, 
            0x2D8E9FA267C70265ULL, 0xB44A7F8132DD0940ULL, 0xFC51BAC3FB08AFE2ULL, 0x1205FBD4436AF5B6ULL
        },
        {
            0x70D51983A694B5A0ULL, 0x0F198D0933097B64ULL, 0x25EBD021324EBCE7ULL, 0x10144B23E45D0AD5ULL, 
            0x1D91CC77EC0EF1CDULL, 0x4FE2078FABF3B9FEULL, 0x629574AE8A8FBBDEULL, 0xFB05FCA7F01535C5ULL, 
            0x21BF44E492A9B14CULL, 0xB15B25359694CB0AULL, 0x07570D1211BB70DAULL, 0xE0B8E31CED6B370AULL, 
            0x6A1F95AE37F236D5ULL, 0x0809F06C7C25EDF0ULL, 0x007BF7217E1974D0ULL, 0x7D09F0D8E46030C0ULL, 
            0x188DF01F83BF94D2ULL, 0xCF9D293ADB3343E0ULL, 0xDEF107C71B801693ULL, 0x77CF52B5596E6D89ULL, 
            0x9A16E726294DF3D8ULL, 0x85805AE0412933CBULL, 0x8CA486C0750EB59AULL, 0x66F40603FA451ACDULL, 
            0x075DB59DFBD17EA9ULL, 0x922E0D66002E313AULL, 0x094097CE7E5574AEULL, 0xE543B53FE605E7D2ULL, 
            0xB19A200BC554268FULL, 0x04E23755E5991A5AULL, 0x5708A9F9CF0480CCULL, 0x56CCA3F614A3DF1CULL
        },
        {
            0x14377A5C3B79B312ULL, 0xCBAA88F1DCE48E19ULL, 0xE931C6DE0FFC0989ULL, 0x1F086CC31E65B346ULL, 
            0xF66163BDB65D998DULL, 0x275361D10A205432ULL, 0xC278DF7E9D98C185ULL, 0x3676006EE4C98166ULL, 
            0xB74426EA7B45156AULL, 0xA7C0D9DFFAD7985AULL, 0x0E388916717BCD24ULL, 0x0EC69E073E498B9AULL, 
            0x27A838F7CA3BEF2BULL, 0x9A9A921CD8C9FD7CULL, 0x9E6DB238C0A71278ULL, 0xAEC8D556D3F19E25ULL, 
            0x9DE64ACF77C2E605ULL, 0x6B791152B9002867ULL, 0x0B956B2E9D0A580EULL, 0x94FA781660F70DD6ULL, 
            0x8F12CE3DED7B24A5ULL, 0xBDF9F39EFDE01DF0ULL, 0xB5881E560252ED99ULL, 0xFA073C4C3D21A0CFULL, 
            0xDA0F7E95FC810A1DULL, 0x51BD90AD6FCD0E6BULL, 0x83A7333B2DCB3335ULL, 0xECACC9C0A42276C6ULL, 
            0x24E054B340F4D942ULL, 0x286043CB0E24ACA9ULL, 0xD8AB060CB8916D58ULL, 0xF463A048544E7A83ULL
        },
        {
            0x63B590F448E508EBULL, 0xE5126F3DB665EF05ULL, 0x12A1C972EAA18C96ULL, 0xDC813A177B72E154ULL, 
            0xD7641BF174CBC1ADULL, 0x7EF19E5C194FCCCFULL, 0xFF1F0E43BAEB308DULL, 0x8016E0E65410F19CULL, 
            0xBB6BD8BAFE9233DAULL, 0x3036AC1504BBD3B4ULL, 0x5AF09A62567E4AD7ULL, 0xFA00CFFE130272FFULL, 
            0xF4D5B95900F3BFFFULL, 0x9F8B59695B900B9DULL, 0x4D123ED5B7E19F59ULL, 0x092BCBC9294B3D16ULL, 
            0x96AF5AF0FB861C4DULL, 0xC18A6BD40BECAD87ULL, 0xC99AB3343703ACD6ULL, 0xA7FE5F1FCE1E993BULL, 
            0x8BE8D12DD4D58FA7ULL, 0xD25438A954EE729AULL, 0x63169D4DA9D1DABEULL, 0x7D5430720D9063C1ULL, 
            0x0D158078F54C1456ULL, 0x44BEB96650E86F65ULL, 0x536BFF23B0D76517ULL, 0x7FEB1D323D5A37D7ULL, 
            0xE5D167A1E398CC77ULL, 0x13C5319EB7A8E8C3ULL, 0x8D66F3C7C343AC95ULL, 0xFFE49A5D22012D57ULL
        },
        {
            0x2B9693AF9B5AF08AULL, 0x1946DEB16A17B8CDULL, 0x9BE35BBD3D927BC0ULL, 0x47E2C188549728B0ULL, 
            0x9760435CDC696029ULL, 0xA2EE441B043E36B2ULL, 0xF1F98841B5B94A5FULL, 0x3D99739BEA4D8347ULL, 
            0x11784F68BCBCD7C2ULL, 0xF719F0E7611567BFULL, 0x0345E9EF4F79C579ULL, 0x69EA980CFEC577ACULL, 
            0x4EF9843D0D0611ABULL, 0x1AD44FA978F8830EULL, 0x228DA2288BF160C1ULL, 0x5B46C75346C8CED0ULL, 
            0x2A9B41F8F8AEB99AULL, 0x753532343EB72693ULL, 0x669C141F84CFB1D9ULL, 0x56F4A07D01772519ULL, 
            0x57777F2737246AC9ULL, 0x1956AC1D73D2363DULL, 0xAD4CF215BA6AFC3AULL, 0x464C4BB15922A1B6ULL, 
            0xE16CB2C003B47B9DULL, 0x57212B17DD1E3877ULL, 0xFEDFEAEA405B514FULL, 0xD2B47E8581D8729AULL, 
            0xFF32F711E73700A8ULL, 0x30F560A4AAAAEA32ULL, 0x94CDE604739BF0E4ULL, 0xBD12685D73024819ULL
        },
        {
            0x9962A8661A35DE74ULL, 0xC5EA32C1A6F557A7ULL, 0xE7FF11BC74829BC0ULL, 0xAC52C716F0A5241FULL, 
            0x02574EA0BC6542F5ULL, 0x9D1102DAE652A948ULL, 0x521FF5E8B44F8CB0ULL, 0x39ADAAF14685FF03ULL, 
            0x6A35CA42E04F2E31ULL, 0x1B6706D8380D4DD3ULL, 0x9AAFE34FA18AE4F5ULL, 0x97B09AE9DE7E96A5ULL, 
            0x3FD2330CE0B1FBC6ULL, 0x4AB6932C2E1018ABULL, 0x66227D0A3AFDB894ULL, 0x4BFEB7CDC320697EULL, 
            0x43000C1DE3BAECECULL, 0x448CC537E1806146ULL, 0xC29FC18A4E7309E4ULL, 0x1EFBBB4C1EB1D6C3ULL, 
            0x40F2C7D5162636D9ULL, 0xB5F1828825E84FA8ULL, 0x0613360E00D545EEULL, 0x1326C29CDE9AAAC7ULL, 
            0x777C2485FF01F879ULL, 0x06C6F7F7CAD28EF5ULL, 0xD6CC2955AD26CF17ULL, 0xE7E450482D415663ULL, 
            0x5F8D199FC9FC2584ULL, 0x6342CC1DE1228E80ULL, 0xB0A0008438AF3F79ULL, 0x5E167D1B5B76E548ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Betelgeuse::kPhaseDConstants = {
    0x96DCD6732F51959DULL,
    0x46A13C90AA98BA63ULL,
    0xC034DF3130028B6EULL,
    0x96DCD6732F51959DULL,
    0x46A13C90AA98BA63ULL,
    0xC034DF3130028B6EULL,
    0x78C5C6DE5DB2B3BBULL,
    0x4C54746E6BB61450ULL,
    0x71,
    0x2D,
    0x68,
    0x47,
    0xFD,
    0xE1,
    0x6F,
    0x31
};

const TwistDomainSaltSet TwistExpander_Betelgeuse::kPhaseESalts = {
    {
        {
            0xD897AA36F36B2B64ULL, 0x454954BB3FD84A76ULL, 0x0D22A4B64532D9C7ULL, 0xADB3DB1DE23A3448ULL, 
            0x860BA8D3BA6527ACULL, 0xA9D3E3F597AC46EAULL, 0xB8A506582B2AE8DFULL, 0x630B1214095B651FULL, 
            0xC1971690D40CDC2DULL, 0xE233DD73B21E2F16ULL, 0x9E439F4F12B790FCULL, 0xCCE1300FA3A27096ULL, 
            0xF248CF3143423095ULL, 0x605D6C67854DDBAFULL, 0x7097018B616C1127ULL, 0xCB70E14ED69FFA5AULL, 
            0xE97BEEB36803CDB3ULL, 0x4B9227A7028E7DFCULL, 0x7690E83E6DFF237CULL, 0x432DF74901BEA115ULL, 
            0xBCCB80D41B83F420ULL, 0xFC13CFDE9D8CA5E5ULL, 0x1E9B41E6C345B42EULL, 0x2F3BD1BAE0806F07ULL, 
            0xB33C4984FBE6BA5CULL, 0x0ED6B6A19681D5F1ULL, 0xE8F772FE6D7EB512ULL, 0x3B1CF0CB157B5D60ULL, 
            0xD10B83FDC843BC2BULL, 0x1E9CB2CBBF8C2FE1ULL, 0x86DD4AF39B34D7BEULL, 0x5CAB6C9615DA2F00ULL
        },
        {
            0x08FE05504CD4C1FAULL, 0xB95B105529756721ULL, 0x5D4E454B059F0859ULL, 0xBA474D5702432FF8ULL, 
            0x5D8A7559197910AAULL, 0xBDC7D0C747612FCEULL, 0xDFAA1C615BC01168ULL, 0x6BFDE3E362A6BD4EULL, 
            0x3E4E3096663318B6ULL, 0x8F5282D92D7B9585ULL, 0x021B07E818CEC33CULL, 0xD4CB5889DE1CEC69ULL, 
            0xEC1D28CCEC3CC65FULL, 0x8A5B28F644772A93ULL, 0x32EA24C016B48F72ULL, 0x82B5A5CEA59B99E4ULL, 
            0x65B922013D2EDFC7ULL, 0x226FE47522454C21ULL, 0xED5EE78FC365C339ULL, 0xA107E75EE606EDDBULL, 
            0x726F6203BDC913ECULL, 0x3F65914AEC759F0FULL, 0xCC41D8F8AA09E48AULL, 0x4F874DA5E92DE628ULL, 
            0x6066D0CBA21826C2ULL, 0x2F3029CDFC5E9EE1ULL, 0x7537F0876B9487A6ULL, 0x8CA60D334D43E0BBULL, 
            0x74CC45A5C58D3FB9ULL, 0xD0DE719E28B9AF1CULL, 0x1C8A4A957FE83D60ULL, 0x88844E77B8EA75C2ULL
        },
        {
            0xF31C6684E59791BDULL, 0xA7BDC20C494C332CULL, 0x4E7912A7DE8A6E16ULL, 0xBE2430124B6F79F7ULL, 
            0x111FCAA6A5100EA3ULL, 0xD4F95235DDB90A74ULL, 0xFB52A3A10F447CDEULL, 0x2C9E9DC57D9B999EULL, 
            0x4A204A40495D4F8DULL, 0x00BA462EA77E4AFDULL, 0x36E84D5C20F2912CULL, 0x65926B7D06272F77ULL, 
            0x5B1B7B611C0A28F2ULL, 0xA2F1DF976F487FFDULL, 0x186A3EB72CBEAFA2ULL, 0x6DD7D857E09C2EAFULL, 
            0xDC0271822963DF96ULL, 0x7162DE1677F6E7C7ULL, 0x5DE57AFC85D67244ULL, 0xB1FDE5BF4380B0E0ULL, 
            0xBA8D36989CC70523ULL, 0xE363D4E60971F5B3ULL, 0xE78E7A204F99BDD9ULL, 0x960F406E4C1213D8ULL, 
            0xFBFC555B9CADFD23ULL, 0x8277199A185C425EULL, 0x76F2B54882FB988CULL, 0xBCBD919078D75AB8ULL, 
            0xA1069CD40108EB96ULL, 0x0C130C76CF016817ULL, 0x2695DD870C0D75A2ULL, 0x196F11DFF1DBC7C3ULL
        },
        {
            0x471EB0744741DF37ULL, 0x65DA5C2FBAEC04EBULL, 0x4B492E8F50F8E356ULL, 0x3733B280B0332054ULL, 
            0xF405CDDDF22ABA69ULL, 0x338696AF1EC3FB6DULL, 0x783B45B307453A7BULL, 0x7AD6CB23FFF06C20ULL, 
            0x47F09CC39C7427C6ULL, 0xCD4C2CFD42EAEEE1ULL, 0xDB02F4876983D856ULL, 0xEA51F5F4B627FF3DULL, 
            0x112023C674732E51ULL, 0x7A678C1C2A342B01ULL, 0x7FDC56CE19E911C6ULL, 0x4180B87E8DD5D1F3ULL, 
            0xF84AA8C04525D59AULL, 0x84E474DEF1FE1AEEULL, 0x901840E63C062F27ULL, 0x79211592B7738E87ULL, 
            0x48A774120A2AE54AULL, 0x21BC5D43F365A4B6ULL, 0xFC2745AE61955B89ULL, 0x0259F12DE8E1379AULL, 
            0x8436F47A0777CBEAULL, 0x907CC267B7315831ULL, 0xEDF2E911E0DF9909ULL, 0xF46D939FF150C566ULL, 
            0x8656B80BFC4C4CD5ULL, 0xACBD01B880ABAEDDULL, 0xF11B10F2571CF558ULL, 0x840DDFDB146F4A98ULL
        },
        {
            0xC80BA7B461919AD2ULL, 0x7919543E6F7E698DULL, 0x469143B1E0BF242CULL, 0xDF4534D3DCA5E4EAULL, 
            0x962833A0544302ADULL, 0x15CBE1B356836AD3ULL, 0x85E9AE038A0D49D2ULL, 0x2D96823B099E654CULL, 
            0xF86B46B10D84B715ULL, 0xF5F2B84C6381A638ULL, 0x3B39BB927F7459FDULL, 0x7233A6C05868502BULL, 
            0x6E37988F5006FDE3ULL, 0xCA041BF55AADA178ULL, 0x467747AC333BFFDEULL, 0x0CD988FD17C8F88AULL, 
            0xDB2A1555FBA4D0EDULL, 0x551EDDF21A37143AULL, 0x8E05403444D10BAFULL, 0x34332F0FFB71CC01ULL, 
            0x0FDD0487572F326EULL, 0x08C76D4B30EF2770ULL, 0x93F48811698F1DB6ULL, 0x5475210464B19547ULL, 
            0x64D4B6322DE40C65ULL, 0x2A0EC613D0F35B66ULL, 0xF82446CBA324BA4DULL, 0x6FCB2E5803B6E2E8ULL, 
            0xDF924C041FA1130AULL, 0x259F8165F10D7C61ULL, 0xA1F6FCDC75C02CB9ULL, 0xE85B9FC77A96A33CULL
        },
        {
            0x60F0E9F557C72E42ULL, 0x0A8CA22384D548AEULL, 0x128421081845C56EULL, 0x35D06ADCA4E1838EULL, 
            0xA30E6CACF93B3AA6ULL, 0x62B816D273F7D3E7ULL, 0x1AA5D24FC26EA2B3ULL, 0xEB4EFA9392FA27CCULL, 
            0x78DB6B32FBA0587BULL, 0x705232597AF52BF1ULL, 0xA1274BB9918C6FDBULL, 0x811377BE19624C9DULL, 
            0x2632A6F851DE1038ULL, 0x1A19F9268FEA2332ULL, 0x6AC5ACCA2DD7EBE9ULL, 0x39E6616B8A33A716ULL, 
            0xA42A9F219AA716D9ULL, 0xBCF3E455EB993CDAULL, 0x3CC70A47EB685DBFULL, 0xA443E4CE65B348B6ULL, 
            0xA89ABFA8BF182E1FULL, 0xBF9F8F62D88D4AD8ULL, 0xACFE48B8FDEBA32BULL, 0x3A3737EDDCAB7E90ULL, 
            0x32A3344375A534A9ULL, 0x1747B7B877E85346ULL, 0x728A91711CFF04C4ULL, 0x6059B4B6061391C2ULL, 
            0x19FD2F4ED8DD2835ULL, 0x1D5C773AC382CFBBULL, 0x0F3DE96A60F632A0ULL, 0x36BEDAFD06049B30ULL
        }
    },
    {
        {
            0xB7FD1BB2E0EB0A33ULL, 0xAF9A81C951CB08F2ULL, 0xEC4BF6C17C148FFEULL, 0xC7251DA37A727CE6ULL, 
            0xB76EEE319ACF0B7DULL, 0xDA2395FEA616834CULL, 0xCD1249089D61B95BULL, 0x5B518FF7110270D1ULL, 
            0x01F326C563EB6537ULL, 0x45D7FE3B9FD9D8CFULL, 0x92092C2ADFFE2C2FULL, 0x1680CBDA9B981AEAULL, 
            0x3467A451365014ACULL, 0xE652B5920FBD6676ULL, 0x33232AAB223825C2ULL, 0xFC2154847E873CDDULL, 
            0x07BAE1FBFBD9D476ULL, 0x5E7CAD2CFA80942DULL, 0x46C53D962CDF0E1FULL, 0x4F8F3CB58272CFA3ULL, 
            0x1147BE5BAB3FAE06ULL, 0xD92EBEA3273C43C7ULL, 0x6808A32D32B4F522ULL, 0xDFBC8BD81CD02C49ULL, 
            0xC0F840E06A3C24FEULL, 0x27241B16510753BFULL, 0xF09266775AA4CA7FULL, 0x7A2FB2CBDCD02948ULL, 
            0x28D6C6F96B53E0B1ULL, 0x8CD9ADEEC072D845ULL, 0x0A174134F9BDDBD7ULL, 0xE553FE6BF461558EULL
        },
        {
            0xBD01D33DAAC0353CULL, 0x5848DEE6EDCB0C71ULL, 0x96944B2832C176C5ULL, 0x447D9216AB73252CULL, 
            0xDBC65AA203496738ULL, 0x91F40EC15276199FULL, 0xA60BE69C7F47A7E6ULL, 0xD96053FA17897CAEULL, 
            0x8CE8ACB388F84E9BULL, 0xA0512DD1872FC29EULL, 0x4D074F46D504D30EULL, 0xF11135E70C461580ULL, 
            0x2F8037180E87F9B1ULL, 0xC00561907728597AULL, 0x58ED29073378FEE4ULL, 0xDFF42684FA9CD650ULL, 
            0x75E0D7130776AC31ULL, 0x64CD6C645066B583ULL, 0xAD47446241588AE2ULL, 0x3B3FD29401F4DA92ULL, 
            0xB232F1F857633E84ULL, 0x9153D34E962F4826ULL, 0x62739D73D69580B7ULL, 0xB0566D1219C3E7D4ULL, 
            0x904E1A0B9A203C01ULL, 0xE36E402C5E6D82B6ULL, 0x39E09EC081189F51ULL, 0x8C1B7648CC50D178ULL, 
            0x4DC30B1CB7462CE4ULL, 0xF75B3F5E53AA688AULL, 0x36C29BD62CACC262ULL, 0x641A7011F510DD03ULL
        },
        {
            0x90E8D1426DA5AA02ULL, 0x72CF12B8A6009654ULL, 0x28D11C78694357C7ULL, 0x803254E97BAF4E29ULL, 
            0x832C44573DD580A4ULL, 0x6F623F9CF8946A8FULL, 0x9413B8932A77B6FAULL, 0xD99096A6C4856FBFULL, 
            0x705283D285651F98ULL, 0xD648A39A58ED2F84ULL, 0x47BC0DF67F3BDA6CULL, 0x5F6D8D09A4385999ULL, 
            0xE072894C9DBDB399ULL, 0x223C6E5BAB7A77C6ULL, 0x593B45C444153FF7ULL, 0x9B55666EB5C51C6EULL, 
            0x8B7A283E5C22CF17ULL, 0xD8C80877908C7BC4ULL, 0x00EF6DB19F74CD7EULL, 0x6113074322F3FAE7ULL, 
            0xA7AFB5CC2373565CULL, 0x2D518060A55B93F7ULL, 0x6FDAE1CFD7EF50FFULL, 0x3C740C7EC9E568E3ULL, 
            0xB766404389995D9AULL, 0x10683F9610DBB443ULL, 0x92859C3D50E7C3AAULL, 0x2A2BF79E3DF862F7ULL, 
            0x587FC5C6BAC8260AULL, 0x52CF955A55215491ULL, 0x07F3D6D10FF0C8DCULL, 0xDECCF7001847B432ULL
        },
        {
            0x09695DAB88E576E5ULL, 0xE9DE10432E6CDA24ULL, 0xF1A71FECF870F4FAULL, 0x93D8431323FCF10DULL, 
            0xE55452008516FE27ULL, 0xD1464535F816B40BULL, 0xDD92DF6DE9F943F3ULL, 0xFA505088508C98D7ULL, 
            0x780EE7D247BB9355ULL, 0x64CD9A059C57461FULL, 0x40FD2E693235F693ULL, 0xDEB145746702240BULL, 
            0x14CF802255F0E8A1ULL, 0xC98061B0261EE036ULL, 0xE8E36696D256F5C6ULL, 0x961E3148AD0B3D61ULL, 
            0xFD5729566BB71029ULL, 0x65F9F3D011EB67ACULL, 0x195BAD0157379E0AULL, 0x63C05292FB426978ULL, 
            0x31281634E894A18EULL, 0x94147011B5AEF62DULL, 0xFA3CFE16678FB6EEULL, 0xDA3E12C06AA08609ULL, 
            0x6265AF20B2755FCAULL, 0xBF5463D8709691C2ULL, 0xC53DF7E9E75F6DC6ULL, 0x3421E4609E8B2AB0ULL, 
            0x3CB56330628B66CBULL, 0x2CD23E1BF0FE3439ULL, 0xB79721EB0785A875ULL, 0x363E2D084F6ED217ULL
        },
        {
            0xBEB84FB1C47825DDULL, 0xB5EC9A2A1268DC4EULL, 0xFE1200D29BA9BDF1ULL, 0xA9ACD4EC9D007D86ULL, 
            0x3D59841B941039FCULL, 0xFCFEB61577CECC7CULL, 0x5A52C33C249AAEB8ULL, 0x43EEEACA47F8B2C2ULL, 
            0x5EAEA6F13A4327A8ULL, 0x389F8D8833C9E489ULL, 0xF472824FCFA8D043ULL, 0x4708FB8E458EA2FBULL, 
            0xCF77EA99722F4399ULL, 0xC30A23139A32819FULL, 0x40A42753E445C3EBULL, 0x85D327714B7E5D5BULL, 
            0x5F3EA61BDDC34D48ULL, 0x39BAC7D9DFBE6A09ULL, 0x90F3873F8BAED1C0ULL, 0xA4262EA777FA84AAULL, 
            0xCA60FD6AFDFB1271ULL, 0x4F3215D1499180CCULL, 0xA1C0470F6E682A78ULL, 0x308A990D447F1018ULL, 
            0xAE9CE02A5EBED390ULL, 0xAB4C0367B693E256ULL, 0x29144FE5141B86EBULL, 0xCD4345902242E0DCULL, 
            0xC79381BDE8078740ULL, 0x308EEBBC4F6B1761ULL, 0xBA4C06C685CC4E42ULL, 0xC92E568E2220B07EULL
        },
        {
            0xA8C2428B19AD4F47ULL, 0x6766FAF866169931ULL, 0xD334D0970229827EULL, 0x35919461E2A6A67FULL, 
            0x0A2AE317834E9262ULL, 0xCF39636A795DF83AULL, 0xB8A5A993E35914E5ULL, 0x3B8106FF73DF7C31ULL, 
            0x977E7B1B35365531ULL, 0x31DBCB605503E48DULL, 0x1DB0AE0F15584050ULL, 0x6A305646F2FEFD56ULL, 
            0x224F52ECFFEAF56DULL, 0x41689649EDD53088ULL, 0x273C5C86B24DB39FULL, 0x69DD130C6692BD2CULL, 
            0x826166AAA5D6B0BEULL, 0x4DA046E792BFCBD9ULL, 0x781F62F82A3A2131ULL, 0x59F6EBDD4F8FF982ULL, 
            0x418FF6FB9F30E556ULL, 0x47309B66E7403D00ULL, 0xBD817EF663C13D30ULL, 0x8FF8C3B31B02800AULL, 
            0x509D9EFB02F8BF33ULL, 0xA56109AEEE069854ULL, 0x24FE5A74F8DCBFFFULL, 0xAB48E2ACDB486A07ULL, 
            0x5CA68694FF8FBF9DULL, 0x90C2F4E7685C9B93ULL, 0x828F14321FB4E9BFULL, 0x74634BFE6C0702B9ULL
        }
    },
    {
        {
            0x474C2EC7A49E5BBEULL, 0x96485641FB7A2CA9ULL, 0x1D5D8BEAFDAA8C5AULL, 0x09E96D5D6D5AE6E1ULL, 
            0x73490287C713C30AULL, 0xA1DFEDB3FAA131BAULL, 0xA8F686D166EA334DULL, 0x312B7FD750CF6973ULL, 
            0x3A9F92D8B0970D75ULL, 0x8BFD133177B52A98ULL, 0x4F58A31112E48884ULL, 0x3FD810A759825A62ULL, 
            0x3FDC6904211F3537ULL, 0xF2EE36528510300EULL, 0xB5D17363CB7FD5C7ULL, 0x18936651EE2B0503ULL, 
            0xE7D797361D56624AULL, 0x7023C75F75062DABULL, 0x6C721D60FDD1502EULL, 0x05DFE20AD5448A95ULL, 
            0xD2F21654BE464FC3ULL, 0xFAEC25697FA46A73ULL, 0x9DCC67D94613168CULL, 0xFE98F683569FA4BFULL, 
            0xB1656BC41074C66BULL, 0x7E1468C1499444FCULL, 0x803373B32C3B474EULL, 0x514341F8ACA256E8ULL, 
            0x681004AB2531BBD6ULL, 0x2941487A5EE52297ULL, 0xCA2E6D0E581D58C9ULL, 0x2BBE098A8183A683ULL
        },
        {
            0x1C87F93289B44ABCULL, 0x7FDE02EEA534F713ULL, 0x3B43647289B9671AULL, 0x7FA27047A4186B87ULL, 
            0x4C52E6D7871E8B78ULL, 0x39329A2A0812473DULL, 0xD9FB010E8D3B5D29ULL, 0x8B52E9DD6868A1C3ULL, 
            0x0CC213D49D194F05ULL, 0x37E951A556F290A9ULL, 0x148729540B5CF00FULL, 0x44EA0EF3496AAAC6ULL, 
            0xD5A05DE46DF22C78ULL, 0xBA6C9B1F89B9FB1BULL, 0xA0B9FEDE2D9219DAULL, 0x7DF37F5479CBD2B1ULL, 
            0x610C3664A4B7D8D4ULL, 0x06A4171E5A27FF1CULL, 0x3A20A43726F052E5ULL, 0xD49CB5D2C464E3A7ULL, 
            0x7C579B0E3F39D40DULL, 0x23B7A08DDF1A6DEAULL, 0xC66273A3352F6EA8ULL, 0x62B611A02FE26E44ULL, 
            0x0FD1B8B347EA9269ULL, 0x7B7E0DD1E62B49E3ULL, 0x66811DD9F72A086DULL, 0x7E0B7D811BD2F393ULL, 
            0x30B0EB90B4182D9DULL, 0x7291E1215CE6E992ULL, 0x3C5DAFCFCFD59B0EULL, 0x2579AC9C0A0A0464ULL
        },
        {
            0x9CD3F192774976CBULL, 0x7D959DF46BE923B7ULL, 0xFF3F553E18E67E12ULL, 0x64D7D290F53DFD27ULL, 
            0x7AE0B23A29D7C7E3ULL, 0xF6CAEDA3A5AF63CFULL, 0xA32FC182A5C3E933ULL, 0x168F4868E3165087ULL, 
            0xF1D3B9B9D38BCF1DULL, 0xFBC7BD2D5A0706DCULL, 0x988DCE3C90FAB391ULL, 0x44E7898BA0343C2CULL, 
            0xF61CE7F99E2F43CAULL, 0x85B580DC07B821A9ULL, 0xD224677E6EC42092ULL, 0x80AB93C9882837CEULL, 
            0xE27BE4E78DF68789ULL, 0xED84D1AB228399EBULL, 0x547A9042FC9A92E2ULL, 0x944DB1F9DC6920ECULL, 
            0x1E904EECAA14D0B6ULL, 0x5EE3AAC922243592ULL, 0x64FB26A267F1E9DFULL, 0x1A3A4A937C45D0D6ULL, 
            0xFE7B83A5529A6281ULL, 0x677986CD6B40D231ULL, 0x7B1DD5E47AE628C8ULL, 0x96919A42E5CF88A4ULL, 
            0x28102B8EC21DF372ULL, 0xFB5A07900F803C67ULL, 0xD36C0DFF682606B8ULL, 0xC8519D2E5B966FD9ULL
        },
        {
            0xA93AF6DAF6DA480EULL, 0xCF436440A703E03AULL, 0x98D9BF44E87EB666ULL, 0xD94F936BC9FF6DF2ULL, 
            0x7DD41FFC8E24AE22ULL, 0x5E2C5A4723E6F95CULL, 0x70817DF51A17D4AAULL, 0xCDA166ECAE25CA08ULL, 
            0x8DD1A2B898DD5C79ULL, 0x50F571CCA84E60DBULL, 0xEECF21E974D93E00ULL, 0x132419B0DECCA58DULL, 
            0x952160043EA9EC6FULL, 0xFE24DF10CE8C619AULL, 0x023AF38EF7029E48ULL, 0xBDC227120EF00A46ULL, 
            0x97F60EC65A314BE7ULL, 0x5A2E67602B35612EULL, 0x190F153B4E4F2EE2ULL, 0x373F11D566E8B7C2ULL, 
            0x15F05EB6D2871D0EULL, 0x7516FFD12FBD1770ULL, 0x3BCAA86C23A49A62ULL, 0x6EBABE2E3BC60CD1ULL, 
            0xACC795A7EA0E1EC0ULL, 0x8C847DD6329A1DDAULL, 0x365705DB3992D282ULL, 0x2D22DF3DAE8F4F56ULL, 
            0x9D216C973D9DD960ULL, 0x87E9407346E4F2A2ULL, 0xB3C30BBADA53B586ULL, 0xF657FAEB38CD73A3ULL
        },
        {
            0x09FB1F9A7429032EULL, 0x65AEB819D76AA160ULL, 0xBC937DB82B36EA14ULL, 0x6D19E7D52AD2C1EDULL, 
            0x3DC9EDB3A80EA928ULL, 0x84A391326E56619AULL, 0x89666FCCB1901AA0ULL, 0xDA0432E7780D2A53ULL, 
            0xB3B57F2DC3206F4AULL, 0x2D6F634BFCC038E4ULL, 0xDBC10C33E4140856ULL, 0x702F0CFB7AE7102CULL, 
            0x8553A7FFD64E778BULL, 0x947D0B2251C7D0A7ULL, 0xE93F7818A9DBB70BULL, 0x672E99ACCE43E807ULL, 
            0x800D6F337F4B60FDULL, 0x19962861B6A81428ULL, 0xEDF0CC778D9D574DULL, 0xD33F0FC01FF40276ULL, 
            0xBB1E9F3FCE0B3FC0ULL, 0x9B612E1C7CD8A0F8ULL, 0x5C63DB57A19C0815ULL, 0xA97A66DCC2D3F9D6ULL, 
            0x789F397B961A1F43ULL, 0xC5663D32CF0251C8ULL, 0x26AFB8969C58AB97ULL, 0x029393978526A5A0ULL, 
            0xBC2CF4F228837A23ULL, 0x43816E3F88AD5F1FULL, 0xAFA19EAFBC376D35ULL, 0x46648D0CCDA1FF82ULL
        },
        {
            0xEFBB1A66F2D556A8ULL, 0x6DF14A2F6DF19CCCULL, 0x6D866EC73BCCFDE9ULL, 0x8C0C33E4B19D7049ULL, 
            0xA5860B9C14C18476ULL, 0x880829AA75B7A4F9ULL, 0x01314E14A18D3B13ULL, 0xC131C550155AB3B0ULL, 
            0xE2095A5747506256ULL, 0x3A605AE990770123ULL, 0x80A3BA657BCDCE08ULL, 0xFC65094DB8DD1F48ULL, 
            0x81E524BA4CBF362FULL, 0x1CCD51921E74435BULL, 0x4AA7C6D9F82C0A1FULL, 0x884FEAF64EB1E17CULL, 
            0x0245D18672571F17ULL, 0x1F94174A714530D4ULL, 0x4871122D55D93BB8ULL, 0x773624756B8E7411ULL, 
            0x7D5F8811A1C1C80BULL, 0x26C4BFB51F7FF0D8ULL, 0x9B9F8CE49B6FDB59ULL, 0xC6558B823F6991CFULL, 
            0x53171E843BC967FFULL, 0xE2A218293938370EULL, 0x5F748071C7890963ULL, 0xA2E8F0E8A4148D9AULL, 
            0x9A2A73BD80EEEA16ULL, 0x4FAA0F7083CA120BULL, 0x9BFAF7DD3A599447ULL, 0x68540107C740E927ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Betelgeuse::kPhaseEConstants = {
    0xDFD73C2993B558C3ULL,
    0x3BC2CC8512376455ULL,
    0x26FA23B7A72E96ACULL,
    0xDFD73C2993B558C3ULL,
    0x3BC2CC8512376455ULL,
    0x26FA23B7A72E96ACULL,
    0xD2C135B05D13A7A8ULL,
    0x631111FD6F7B215BULL,
    0xC3,
    0xD9,
    0x29,
    0xFB,
    0xEB,
    0xBF,
    0x5B,
    0x2C
};

const TwistDomainSaltSet TwistExpander_Betelgeuse::kPhaseFSalts = {
    {
        {
            0x0B66D794406499CEULL, 0x28AB667729BAA9FBULL, 0x4ADAFEB71452ABBBULL, 0xA75E80DCB6C1644EULL, 
            0xF2781E1BBED7188FULL, 0xDBF145DF856DC52FULL, 0x75634AC4129ED4E5ULL, 0x1F41B6DD767177FCULL, 
            0xBFDF952359F8A9DBULL, 0x53624A2480A69523ULL, 0x7D013A42D30F12D6ULL, 0x80A4942E7FD6F75DULL, 
            0x1DDB2BC4CE37A538ULL, 0x4EEC56B2C2FEBAA5ULL, 0xB64C10F1D75367A0ULL, 0xD56B1347D0D0642CULL, 
            0x636042B745B8E2CEULL, 0x4FDAA6278B2A87FBULL, 0x6A611E403B6C419FULL, 0xA6CCCA0DE71033ACULL, 
            0x99285D433ABCAE0DULL, 0xA3569A310D311C35ULL, 0xC2BD0C981C975874ULL, 0x27EBCD3A83A0411AULL, 
            0xC6EA0A8DAE9FDABCULL, 0x08D8D429150F5F76ULL, 0x5C33A93D6A6CE510ULL, 0x1D3F4A121B701C96ULL, 
            0xBA9803C0C42040A4ULL, 0x1C6B6E9BAD01F042ULL, 0x1B5493C3FE6AE3D7ULL, 0x366348EF57847862ULL
        },
        {
            0x9BF7622EC618F8D8ULL, 0x4788B81A50F21716ULL, 0xE1F264877FB80154ULL, 0x89CDEB8150085121ULL, 
            0x6E7D8CBE87AB8FF4ULL, 0xA2E615E83F36A192ULL, 0x1B1AAA98D0B703DEULL, 0x2556F965742906FBULL, 
            0x3B413EAF6BD163CFULL, 0xA35E07BB039A1C24ULL, 0x5BADE9CBE86A8D10ULL, 0xDB28DBB2853BAC05ULL, 
            0xC34FC3D583FEF21AULL, 0x42DBD15772E2F14CULL, 0x0F5C839367823C7FULL, 0xC12E3E703395F1A6ULL, 
            0x4DF8945E78B7ADEEULL, 0x924B32313DDC0E91ULL, 0x94C85B70BD77C05FULL, 0xFA51ECF20D432D29ULL, 
            0x0BD07F4FE42ECD80ULL, 0xC8C1B9FD9F39DB5EULL, 0xD04850ED86CD728FULL, 0x6E4A383D90BE1254ULL, 
            0x0FBFA3DCAE355AAAULL, 0x808C2AC19F1E5C8FULL, 0xF8B65EB23AAB61A0ULL, 0x403AB16AE86F94AFULL, 
            0x4A30CDCCCFCDA866ULL, 0x63A330FE993E9FFFULL, 0x23F22AFE0E05B031ULL, 0x6CD62E987512FA6DULL
        },
        {
            0x69CF9DAF8AD23E02ULL, 0x5E485650FC8E7257ULL, 0x7ED5B164D64CCCD0ULL, 0x7F54D75BB7C1B565ULL, 
            0x5698CEF042650D44ULL, 0x501490DA3B3AE145ULL, 0x46FE71C7482D837DULL, 0x605AEBF26F7AAD38ULL, 
            0xBB4814A52462484DULL, 0x54920E8184BD83DEULL, 0x90F8D66B53245E75ULL, 0x56F00DA7BDA9AE4EULL, 
            0xADB942D260D462DCULL, 0xEBFB41AB5044F924ULL, 0x6054853974725133ULL, 0x6A0907FF339E4F98ULL, 
            0xF4EA27CC9B82782BULL, 0x4794C44C0A71EDBCULL, 0x04B2558896528211ULL, 0xBE5650E1A01013CDULL, 
            0xCC46A48B5F1B933EULL, 0x26F7170F8D317516ULL, 0x5A80CE588991F4C9ULL, 0xB7D7FF8699097B0CULL, 
            0x367A2EE620C51C09ULL, 0xA019FC18B8C410B3ULL, 0x162EC73224779BC7ULL, 0x7E0B07CDA34032BCULL, 
            0xE698C26B0007220AULL, 0x092259F62D80D3C4ULL, 0xF7FF46EEFD54D9C3ULL, 0x80A77317E281035CULL
        },
        {
            0x24B5B173D08C904BULL, 0xE19FB63630EFB82FULL, 0x0AF26A8E7929B3F8ULL, 0xF312C864731F33D7ULL, 
            0x5EF853F73371B5AAULL, 0xFD35E9CCF2C3E655ULL, 0xE77AEBF3356F9FA2ULL, 0xCD657F7117F023E4ULL, 
            0xC0B06F6DBAA5DF85ULL, 0xBCDA4AEB8474F7F6ULL, 0x4418DC0450D5A989ULL, 0x84A5B2F3A6877BC7ULL, 
            0x3B5ADD5DA181892AULL, 0x3B76B1ED387C31B3ULL, 0x99145E83FC8A664FULL, 0xBB7E0270E02672FBULL, 
            0xAD3CC76716CFAA68ULL, 0xE412A5842CC082EEULL, 0x1253E555E6734B77ULL, 0xAC453AFF991DCA4CULL, 
            0xE6FF876D4047B491ULL, 0x258D142CE1466086ULL, 0xE71A8EDA52D8CC1CULL, 0xA893CACB9F7DD7B7ULL, 
            0xC7D52796D81884CFULL, 0x7F6804A287A3A7E7ULL, 0x25AC1FE4AC2F9662ULL, 0x99F02F1281618850ULL, 
            0x5E30EF635D5E89AEULL, 0x00C39FD801D0D335ULL, 0x179150B56D55667AULL, 0x0CF77F055041CF25ULL
        },
        {
            0x9C93ACE340305458ULL, 0xEE47A25ACA50FF29ULL, 0x0C3E917ECE3405CDULL, 0xDFBC734973E36605ULL, 
            0x8496CFECEC088F68ULL, 0x67D9343B094902B9ULL, 0x04F6A11EE4616559ULL, 0x65F0F7933DFE80AFULL, 
            0xB37219010CC0F3F2ULL, 0x1526FD5B1882C415ULL, 0xF19BA8C6B834677CULL, 0xBEF53AB824D30F12ULL, 
            0xF90A486902307B14ULL, 0x1583780C2770DE45ULL, 0xF985CA47248BFB7CULL, 0x91EF50F257FB1524ULL, 
            0xD999562140979A45ULL, 0x39BB76D3C879B744ULL, 0x2662094EF07724DBULL, 0xFFE6268C5375DDBEULL, 
            0x8B59B95390D5267DULL, 0x8746D79D46FFA8C5ULL, 0x04FE22A83424C0F0ULL, 0x10A545682F1327DDULL, 
            0xBC2AF65C5C9653A2ULL, 0xB063674167FE38A5ULL, 0x87E2BD5A40CE76E3ULL, 0xA82654C8AE0ABC75ULL, 
            0x118B4A4EB9D7CD00ULL, 0xCD2BE69B546A1132ULL, 0x5A285866F4D7CBF7ULL, 0xE221EF15EE98DE35ULL
        },
        {
            0x8D11633CB5EA4D06ULL, 0x752563D0FB96BB44ULL, 0x053BC768AAD92D88ULL, 0x99626F6DC0625D33ULL, 
            0x8EDBF3BC3E7C3AAAULL, 0xA397469BBFB2D17BULL, 0x1DBB9D01E96F8145ULL, 0x31BD2F545B46B6C2ULL, 
            0x530CCCCF146AAF90ULL, 0x2C4266BE5B83EF7BULL, 0x08D00E2779D257C5ULL, 0x0652254F3C26526CULL, 
            0xF00FB09E80FFE89EULL, 0x684B55486C928661ULL, 0xF3227FB9FDF4E4AAULL, 0x456DBDA3F0D0958FULL, 
            0x7B672FF4195A209FULL, 0x94661344232C5DA4ULL, 0x981E0A3F1D9A272FULL, 0xE37B74899C052C6CULL, 
            0x999FC57428D601B8ULL, 0x20F4F9D44DCD78C5ULL, 0x8147855F7E87C46DULL, 0x2924AADBF4B93D11ULL, 
            0xA9B132374ED7F77DULL, 0x9E960E1294C597AEULL, 0x24588F393DB4E83FULL, 0x1CF934B477CD455BULL, 
            0xFAFC7D3DA75AF362ULL, 0x15A4B21A8389FD73ULL, 0x5A7EB4BD76AEFF79ULL, 0x8694CFF96276EF31ULL
        }
    },
    {
        {
            0x4344AB0DD2F098CCULL, 0x6EBA9A39A0ED0C14ULL, 0x9E9456E15C3A3A6DULL, 0xBE21254951178EC0ULL, 
            0xB514CE8923173326ULL, 0x4B52374389554954ULL, 0xC65514F4DD65EABDULL, 0x4ACF8CF7261043B5ULL, 
            0xA735556A61E61C67ULL, 0x25093109F818DE49ULL, 0x9266F44C1B8AF076ULL, 0xC9DA49902A656460ULL, 
            0xC010C292C78227ABULL, 0x619F9100F2840D05ULL, 0xB41277EAAFF164E6ULL, 0x4611D0DBEA01E79FULL, 
            0xA4751C3589ABB49CULL, 0x0994427EEC3A4629ULL, 0x786FC8F9B2DAA99FULL, 0x9465D0D1F452EB07ULL, 
            0x48C0D299D40CE266ULL, 0xCA1F108BF2F7EADEULL, 0x560C268AED107290ULL, 0x97CF2569DDA690BDULL, 
            0x181F884A343F8BF2ULL, 0x0F27F5FD6669C496ULL, 0xC8C8445E81F41FFCULL, 0xF90BAAF5339A762DULL, 
            0x6D090162F5DC06C6ULL, 0x897AF238B4EE1077ULL, 0xBD2C7397781B2847ULL, 0x8E58C44EFC4BA0BEULL
        },
        {
            0x3B29EB39F9E0F972ULL, 0xA4F9E755D43407EDULL, 0xBA9475ED90F5D49FULL, 0x59A815F0DA99FC04ULL, 
            0xCD38761F4C29C90BULL, 0x389D914AA9C037EDULL, 0x4510E6A175E15CFBULL, 0x2D08DE6C1778F57DULL, 
            0x6F54F57F4F75756BULL, 0x670472C3CA2E6DC9ULL, 0x488E1BCF87C9E636ULL, 0x3D1B2DEEC87443AFULL, 
            0x60F7CA66767EC64FULL, 0x4D8C83F9920BBF4CULL, 0xB9BB9F1C2DAEF661ULL, 0x5D5571B60D77EE69ULL, 
            0x34047B77DF8BB9E5ULL, 0x713A7F5987A9F226ULL, 0x22EF4E7DE2E06047ULL, 0x0FE7FB15EF379E9CULL, 
            0x37EA08F62DD4D50CULL, 0xD9AC90E45EB11D61ULL, 0x0ED970D1AD173A23ULL, 0x4D98A437F6F46317ULL, 
            0x51C500EDAFBCE6B0ULL, 0x99B6AE57C7D9E328ULL, 0xC307E06BA4AF9A11ULL, 0xF53CA9057383BFC6ULL, 
            0xB503512E1E45E3F4ULL, 0x9AAE77DC4085CA43ULL, 0xD2B53FF852AE9EDAULL, 0xA6849CDBDA722FB3ULL
        },
        {
            0xAE3884F2A4E6835DULL, 0x6A65E61236DADDA2ULL, 0x9FEA1ED8E83FD4FFULL, 0xF0FBEF50894C783BULL, 
            0x99C712FDB3CEF031ULL, 0x0B97DBCDCB06212AULL, 0xAE59303E7EB1E039ULL, 0x1B092991C76BEAD7ULL, 
            0x196F84CE384EC83BULL, 0x62F2CD8580F7D7B0ULL, 0x545B8BC698396D7CULL, 0xF9A4141850D134C9ULL, 
            0xBFF1E8CD819E24DDULL, 0x1D46A4C94C7D3AA8ULL, 0x3861366D1BB0897AULL, 0x3CA5E42793E01FBFULL, 
            0x6C4622B2E83E997DULL, 0x9EA9F20D91762FF8ULL, 0xCBB9A420208690F0ULL, 0x2D476FD5114EAA1DULL, 
            0x84B159AF2EC52852ULL, 0x3607FA10F2CD77A7ULL, 0x28737BF69F4B3121ULL, 0xB4841B187E9505FBULL, 
            0x50513121CB0862AAULL, 0x5EEC1467A99B7351ULL, 0x6C5545597E9779AAULL, 0x0677930F15BC8CD1ULL, 
            0xF48B8A52BEC06DAFULL, 0xFA291FFC1F3B99D2ULL, 0x4DA6AE8142542D8CULL, 0xD7CBAEEE45268823ULL
        },
        {
            0xDF0548BB7484D596ULL, 0xB02962015998C8C1ULL, 0xFC94EAC9B5B14900ULL, 0x1A3032281B3CC360ULL, 
            0x426CB50F953B77BCULL, 0x2A1F8A405368C6C8ULL, 0xD666FEB0AD750442ULL, 0x1338210EFA6D41C6ULL, 
            0xD51A17AE46C33208ULL, 0x79E3B14F9239F4DCULL, 0xCBCAD816A12A037DULL, 0xF3D5150C3019224CULL, 
            0x32D0791B1C616237ULL, 0xD2690DF77E071D07ULL, 0x808F44A1F2C9F19BULL, 0x5F1453682F050C78ULL, 
            0xA6CABD37E3FCE368ULL, 0x0888FCBE41BFFF02ULL, 0xE41E4E1E4A145B96ULL, 0x61480AC9377553DFULL, 
            0xDC1B0D8C0B233EA5ULL, 0x0F078B74982D79AFULL, 0xBC4EEB1B3A92924AULL, 0x88D728F785AE559EULL, 
            0x1524F80131D79CBBULL, 0x00F24E6F1A314632ULL, 0xFB60ED345400508CULL, 0x5AA0B4234A8BAED8ULL, 
            0x94CCA7D2AF3E70B9ULL, 0xD349D7DE4AD0757EULL, 0x5B6D2F8FBA017970ULL, 0xE27BA441E9C9B6C8ULL
        },
        {
            0x82DA7C173C142EB9ULL, 0xFBBAE3E09E1AE702ULL, 0xC1BA6FE9917B340CULL, 0x9C57937E9013821BULL, 
            0x9B955D6A1338A342ULL, 0x392CA7690F2F9DD1ULL, 0x4B29E8D193C720DFULL, 0x95F46F65927CA039ULL, 
            0x618D9FA966C7DECBULL, 0xAD5E214213DA00F3ULL, 0xC8974C45B2490DC5ULL, 0xFD78339B8644BAC0ULL, 
            0x2B033CBEA8951463ULL, 0xCCFE6C1808153ED8ULL, 0xAC54A87DA491547FULL, 0x4F6CCA39068A0E43ULL, 
            0x20147EAC553F5E3FULL, 0xB8B0047401864D09ULL, 0x6B547759F9E1D3C3ULL, 0xB6434C494F0F3932ULL, 
            0xC49A0B825C6D9B45ULL, 0xA4EE5ACE87EE5FA0ULL, 0x3C2515185B30A800ULL, 0xF206D2FA3D0D2942ULL, 
            0x44CB4E872C15A808ULL, 0x022327A8C2E12770ULL, 0xFA02447675C441D0ULL, 0x19729CA4E74E949BULL, 
            0x3CCF4B9FBA4E50D0ULL, 0x2508CE791D5A9444ULL, 0xD8C28D093653A488ULL, 0x3B10833AF2CC18B4ULL
        },
        {
            0x54ECD7C5B0D57CFCULL, 0xA3B71A354EDA6624ULL, 0x12F2D7A74000EF3BULL, 0x70EE0C32317DA64AULL, 
            0x7BF3862069BC7741ULL, 0x894AAF5649CD5B44ULL, 0xF617C7007018E8BDULL, 0x58C5F78A991FBF8DULL, 
            0x1B1981A67D215F18ULL, 0x240C0FB7923F67F9ULL, 0xFE16B9AC592FD3F2ULL, 0xB88C2C04BBB0BFB4ULL, 
            0xA2E65F07551B7DBBULL, 0xDE2B8EB8A8CA5BD4ULL, 0x85EF0412F069BC15ULL, 0x1AC889D15578ABDFULL, 
            0xC842DAE452E714ACULL, 0xEE799A66D99F951FULL, 0x0A22B4AF721FCD82ULL, 0x3516FABBA3EE0FA5ULL, 
            0x8CD52EE53FFDBCBCULL, 0xEB3C5C4C9AC29D4EULL, 0xD8E42DA592DEB3FBULL, 0x5A2832AA7E5C9A20ULL, 
            0x06527FC2CB7C3D2AULL, 0xCD029085BBACE3FCULL, 0xFFCC081D8F62FFB9ULL, 0xDABFE660F2922D6BULL, 
            0x908BFDCF5D330A9CULL, 0x05BDDD7CC000EB9CULL, 0x54AF8A63DEBD654DULL, 0x2D030A0E8D62A380ULL
        }
    },
    {
        {
            0x69EF919E46F55DE5ULL, 0xFAF631368B0226C9ULL, 0x93AEC579625EDB3AULL, 0xEA2A41635E68A8A2ULL, 
            0xF61F52B0E0D185AAULL, 0x19204A8CD57F855FULL, 0x6F89F89944CB0635ULL, 0xD48A19FEFE8613F7ULL, 
            0x70CC7DAA42C54B58ULL, 0xCFB4D083C0F2805FULL, 0xB497DE70A67AB5A2ULL, 0x6464734060D1E141ULL, 
            0x25B8633ACE9975AAULL, 0x3D1BA0D8C2B2EBABULL, 0xD93B1319F953EDE3ULL, 0xEBE9BB7F7E74E96CULL, 
            0x0A27EC512F4723ADULL, 0x02CF9B6468AE77C1ULL, 0xD014DE7B77455386ULL, 0x6D12596326CC55C3ULL, 
            0x2B9B4F1518B5713AULL, 0xA16024451C715364ULL, 0x11171B88CA333400ULL, 0x5DF1DDB40CB1D649ULL, 
            0xE43EB4B3BD700FF8ULL, 0x3B3C231D469E8BA7ULL, 0xA9F61A7C6BC3626BULL, 0x1CE704CB6475E792ULL, 
            0x6DE0AF86F09D4407ULL, 0x89CACF358F8345A4ULL, 0x0BEE3569A38C3BCEULL, 0xC5C761C3BA4F5E63ULL
        },
        {
            0xAE2F74D1D4EC6A47ULL, 0x5D5D8CFD0B71734EULL, 0x4A64EF3E6A777A51ULL, 0x9CEB66EF6326B71DULL, 
            0x7BFC8B6C363CB3B9ULL, 0xAE833A75D4E59550ULL, 0x051C8D5B82593698ULL, 0xD5BB95478DB1668DULL, 
            0x6D3298A7920E39AAULL, 0xDECD7A6B164C51C5ULL, 0x1D8583B0E512DF1DULL, 0x278BF432D65E7853ULL, 
            0x4AA69DE1A76DF989ULL, 0x34AD42201FAF4798ULL, 0xBA04E3A5CE206039ULL, 0x621ABCD7054386ABULL, 
            0x0C2766DDFF2D30EEULL, 0x7C6451296ABC0F37ULL, 0x64D94346DBE75DBDULL, 0xD673C6C675B09623ULL, 
            0x72E5BB11C23D38FCULL, 0xE879474B97C0606FULL, 0xEB91A7705E4D6E44ULL, 0x58107224F5C6969FULL, 
            0xA67CED40743D07A6ULL, 0x7E7BAF22D5A70B42ULL, 0x0CF19FDEB1973CC0ULL, 0xF17BCF6797E47C34ULL, 
            0xA246C79FFCBFCA8AULL, 0x4FC307923B95202DULL, 0xF72AE3F14F429092ULL, 0x3E6A80475DD67C7FULL
        },
        {
            0xC464AA3E09EE46A6ULL, 0xC1D91BBDB5B2F7C0ULL, 0xD32D4739F6135DB1ULL, 0x5748E44A9E3925A6ULL, 
            0x461EDE7AB2C3E051ULL, 0xAA4E172073A04204ULL, 0x05119A13C79C115DULL, 0x84AA986CB32DC13FULL, 
            0x8918B0B4E7784F7FULL, 0x8DE29297794D3268ULL, 0xA4AA4A53BFF22E83ULL, 0xED0BCE3AA964B23EULL, 
            0x1023D4F6EFE54DBFULL, 0xF2F8060757D01FA7ULL, 0x017A7906F3A53FC8ULL, 0xA42B45F5D6DD2ED2ULL, 
            0xB90CAD7AE03D0C3EULL, 0xBEEF82397291A9E0ULL, 0xDD222D86952B210DULL, 0x128C18EC6B00235EULL, 
            0x84E33988B4512BECULL, 0x2356C264310FF8DDULL, 0xB868683CD48B5FDEULL, 0xB4C363AE352628D5ULL, 
            0xD24638160F21B982ULL, 0x268DF8846B1BBC2FULL, 0x1F0B9B275D90B036ULL, 0xF1E681B3180F6AE1ULL, 
            0xE39383E08026D9BAULL, 0xA3AE7CCC1FC8D2E9ULL, 0x112844C78D0F8734ULL, 0x86FA5B2D079D67F2ULL
        },
        {
            0x03A9DFAD6BAFA27EULL, 0x979B959561817381ULL, 0x337B2307D308BBCBULL, 0x74BCD5263BF1BCBAULL, 
            0x88907BA205675448ULL, 0x5F1FDC3F7ACFB6E9ULL, 0x2FC1CCE772DD8E5AULL, 0x56431FC940982040ULL, 
            0xA50A02D03672B453ULL, 0x5419EC574220D6ABULL, 0xB66482B19CD4E2D2ULL, 0x91B88DED52D85301ULL, 
            0x91884CB08077F6C4ULL, 0xFCBF613AD53E6718ULL, 0x8C043E6AA609BD1EULL, 0x333440F1C4A1A79EULL, 
            0x9F6C875AFA197459ULL, 0xC66E8F3ED706D0D9ULL, 0x9DACA547BEB757FCULL, 0xE19745FA4C051620ULL, 
            0xC0DDA4DCB56C0C6CULL, 0x170FF1D66E851556ULL, 0x0A2D88045171E6EFULL, 0x0F29B5A8D007B2EEULL, 
            0xEFD7D071F4E89C11ULL, 0x54213AE9A3EF1F37ULL, 0x88E21D5B86ADE5D1ULL, 0xB0FC911B4A08DE8BULL, 
            0x1BB5FDC6E67D05C8ULL, 0x1A6699E4B0B223B8ULL, 0xC30609A3A91C5A10ULL, 0x9ADBF57324780D07ULL
        },
        {
            0xD55AD3F9939CEF2EULL, 0xD6AA09E41B26D84AULL, 0xD310501E7B60F7F5ULL, 0x09588A49264675C3ULL, 
            0x4C941C525F502DFBULL, 0x8EC748F71DE2383AULL, 0xCE1EEB22ABAAFA39ULL, 0xB001BB9922B34748ULL, 
            0x6111983E13CB511DULL, 0x9064DC124FBD8CFAULL, 0xED483B08F03C6276ULL, 0x5B84A510CE5B601BULL, 
            0xCE8F9C5B6A93CCF8ULL, 0x4C8C31B842E9802BULL, 0x6EC2C7023E875D67ULL, 0x3149308073CB1B29ULL, 
            0x56B16E378D724DC5ULL, 0x7295DEB483AE9A87ULL, 0x0B78EDDE1E07E27FULL, 0xCA69436A41F8E9D1ULL, 
            0xF18D206F54C83CECULL, 0xB62960CEC1884E80ULL, 0x4F5A024334D9EB42ULL, 0xAC345C28266C8608ULL, 
            0x52B0896198EF50F2ULL, 0xE15DA5461C87228EULL, 0x1710AF4A2557824EULL, 0x0C42CC5D6FEF239FULL, 
            0x338ACD6AF53948E2ULL, 0xC4A5FFD1E2A8CB7FULL, 0xBCBBBEB3D06C638AULL, 0x49D36248139D896FULL
        },
        {
            0xB636F3C248B8D12CULL, 0x0228CDFCD1A0AF08ULL, 0x029D14331968ED8EULL, 0x1D087AEC91E2B3EDULL, 
            0x08C3E970FC51C76DULL, 0xC7ACDC6289C015ECULL, 0x6C4F4FBC7100D404ULL, 0xE0A090A0EE8FEA02ULL, 
            0xDC2D5CFF2A540677ULL, 0x3EA0B65FF4206811ULL, 0x8254FDBD45A6B836ULL, 0x65EECFB8FC302B9AULL, 
            0xA0E804E3EC3F3E3AULL, 0xB0D3FB520A96B5EBULL, 0xA7D418846F9011C6ULL, 0x70E65562256CCED8ULL, 
            0x822A7C9613F3C7B6ULL, 0x806F87C94EAF8E76ULL, 0x045D0D18016D3309ULL, 0xC629D3AC70C7DD66ULL, 
            0x50ED9A4F0E4E6008ULL, 0xE1BA2A53086DBEAEULL, 0x34DED9BD025BF7D9ULL, 0x2500A924CAD8D372ULL, 
            0x3EBBC1ECAC3976EFULL, 0x7F2CD7D7D1F41453ULL, 0xB7C348C5E9A4C3EBULL, 0x4F670DEA54106830ULL, 
            0xADABBCA55DDFD991ULL, 0xF62D6E597A561F1FULL, 0x56AD332852AAC942ULL, 0xEB6063A5C2E2056DULL
        }
    }
};

const TwistDomainConstants TwistExpander_Betelgeuse::kPhaseFConstants = {
    0x5CAE225E2064A513ULL,
    0x6F4EA90D41CF83E2ULL,
    0xA2EE6BD7BD76500FULL,
    0x5CAE225E2064A513ULL,
    0x6F4EA90D41CF83E2ULL,
    0xA2EE6BD7BD76500FULL,
    0x2769DAE1D9380171ULL,
    0xEE28519D3F1AD80BULL,
    0xE8,
    0xEB,
    0x9F,
    0x24,
    0xFC,
    0x96,
    0xB7,
    0x78
};

const TwistDomainSaltSet TwistExpander_Betelgeuse::kPhaseGSalts = {
    {
        {
            0x802CB8AE3BC789B1ULL, 0xFC8313A297D5D63FULL, 0x099D2B87E94C3D36ULL, 0xF9018D53C61741C6ULL, 
            0x6F9E9052F709C277ULL, 0xE1B2AAE85E8343DAULL, 0x68B2C7B9A3957B11ULL, 0x7804CD725F0495F4ULL, 
            0x8CFD3A184AB03EFFULL, 0x8BFF1738DFCD04E6ULL, 0x2404473B52E98D91ULL, 0xC086832B03A75CE8ULL, 
            0xCE9012A4972AADA1ULL, 0x965A47BF238BDD3CULL, 0x25019C2D1962FD01ULL, 0x3FAB538ED39A3158ULL, 
            0x38BE15C90C06260EULL, 0x52DAC5A286969439ULL, 0xA05C60A3FB601B4DULL, 0xF3AF3CD0AE4BEAACULL, 
            0x57660F312E9D7E31ULL, 0xFB96511DE3690A33ULL, 0xE1765E814F1CC6D4ULL, 0x5142E122498119C9ULL, 
            0x2CC8DC9D54FF7294ULL, 0xE2BFE84F1BBBCCB0ULL, 0x7CF427C85C895E11ULL, 0x8B2DFA4C51446EC6ULL, 
            0x581238AE0EC83083ULL, 0x98BE0B4CAF055976ULL, 0x00FC9E20A7FCE32EULL, 0xD7B084A53C33EE9AULL
        },
        {
            0x0B1EEB866FC83FA1ULL, 0xCCE406FD13B4A973ULL, 0xA8FAEBC88D27C8DFULL, 0xDE1F8F661395E351ULL, 
            0x7FE50D9FB2EEB25BULL, 0xABF86F0C62B6CC50ULL, 0x1BD17B7879D04E2EULL, 0x24FA559DE2C7EDA4ULL, 
            0x5B2732ABD9363FB1ULL, 0x44EC52B2BD5D62CFULL, 0xD00BE91414993A2FULL, 0x53FCA8620FBBECCAULL, 
            0x43D0147516068F6EULL, 0xC0F2FB6E8B7FD983ULL, 0xA68E7210AD57EAF2ULL, 0x0955EA9EB6C99ECDULL, 
            0xE8EBC85B9905FDEAULL, 0x8472682653EEC4A8ULL, 0xA76AEB8199C76A74ULL, 0x813EE63A6E1E28F1ULL, 
            0x3184AA3B30CEAE35ULL, 0xD2627DB206CDD392ULL, 0x63E39578D54370C4ULL, 0x038C1FA6972162B8ULL, 
            0xEEF9B3C3B06FB10DULL, 0x79A1FF54DB784B5AULL, 0xC700BEF6D2E52924ULL, 0x46CBFE341476022EULL, 
            0xF55954CBA1390565ULL, 0x64DBF85FAA24663CULL, 0x7770C00C1B6F6F88ULL, 0x033EB9743CA5656AULL
        },
        {
            0xABF4C2B481453572ULL, 0x492774924C5FF020ULL, 0x8B6DF090F8883A78ULL, 0x92263DF70F6AC4E4ULL, 
            0x26E1F68CF1FD846FULL, 0x61D1C978AE99247FULL, 0x8B37539649E49F49ULL, 0xF157AE8F1A003993ULL, 
            0xCEB333882B903E46ULL, 0x6D881F6B8802B932ULL, 0x15C002A4A21330BBULL, 0x6ECB4B203F11E532ULL, 
            0x1092C0027D916F73ULL, 0x2EB8AE53F01281EBULL, 0x0B88EE0E8A350CBCULL, 0x341925292BFEDCC9ULL, 
            0xB12E91877720060CULL, 0xFF5A7ED0195AD98FULL, 0xE9E54AD5365C56EEULL, 0xFA013473C41E9C8FULL, 
            0xAFDFFC4739649437ULL, 0x346A8381C6009640ULL, 0x2FD5CCEC471A8743ULL, 0x6C0CCE0268321EABULL, 
            0x44CF4098D63C5AD8ULL, 0x35EE2B8EB4BE5441ULL, 0x77AC0033A17EC6AAULL, 0x9BEEA458782CC468ULL, 
            0x00528084BDFDC8C0ULL, 0xBE23A291C8A94B20ULL, 0xD67150CB11E428A5ULL, 0x6344017F91B7B0B1ULL
        },
        {
            0x14FBE220746CDB32ULL, 0x7DD10C7EF1ADDBE8ULL, 0x03F5A8513ECD88C8ULL, 0x6B8A86389EF4DA84ULL, 
            0xAA5EEC85160C20CCULL, 0xEC1ADF929237462FULL, 0x5CE53FA121AA30C4ULL, 0x4504BA76BE3739CEULL, 
            0x2081B9877C83A9B1ULL, 0x4C11D2EA01AC4F5EULL, 0x255203D76ABEEBEBULL, 0x9F5DFDA31733217DULL, 
            0xD6E9380CFF0F3C51ULL, 0xE92079FBC83164EDULL, 0x8ADA7C93B9526278ULL, 0x773F79A90BB095E0ULL, 
            0x8031B6E6E3CE0D8BULL, 0x953237A2171B046FULL, 0x4286A4C454371374ULL, 0x81B5210C6D71CA9AULL, 
            0xBED7D7C24E267F4CULL, 0xAA4232E976F2B095ULL, 0x0E1EF7D9E2990867ULL, 0x9C5A0EBACE1B27F2ULL, 
            0x86F8B3DFE08BBE45ULL, 0x7C206828BC8F447EULL, 0x4D8EBF46B48B64DAULL, 0x64758703EFA64A46ULL, 
            0x617D178476225E11ULL, 0x1DF930ECB549A5CBULL, 0x75B14A52F197B77BULL, 0x8652BAA97464BBD7ULL
        },
        {
            0xC97AA09580CF64B3ULL, 0x32E081C790778766ULL, 0xC671994277B8D8E6ULL, 0x3BFCDE2E168ABB50ULL, 
            0x1E21A0B11655E10BULL, 0x8DEEAD654CBAB727ULL, 0x47E5BBCF24328DDBULL, 0x241368B4C295DECAULL, 
            0x8A37959E6A2DB3ADULL, 0x46795C7782DBF9DAULL, 0x747B3BD848BF4E6FULL, 0xEA3E4A05DE160973ULL, 
            0x8157397A6D4AFCA3ULL, 0x03FF97534093CFB5ULL, 0xB3015FF894FE96E4ULL, 0x68670D947BCAC3BAULL, 
            0xBB07A2FDA0AC9F08ULL, 0x8D572666B63BE3CBULL, 0x020D65808E9002F5ULL, 0x6F2CDF75C1B3FAFFULL, 
            0xFC021233581B0D6EULL, 0x9D2579890106E567ULL, 0xF150B1921A32252FULL, 0xF944F8160FA97772ULL, 
            0x6D383D37AFA2D8FAULL, 0xD4266AF47ED028CAULL, 0x37950E25C979CD4DULL, 0xEF5CCADFDEBC48F1ULL, 
            0xCE02E5E78638E1D0ULL, 0x90C3AE5FE78DE1EBULL, 0x9357E7621F082E43ULL, 0xECEA2E64D42BBA94ULL
        },
        {
            0x753D0993C30DF937ULL, 0xD444246D0A006730ULL, 0xBDAB494542CD5362ULL, 0xDCDA7D6B124E1AB4ULL, 
            0xCB1146B4045B04C4ULL, 0xDEAE2E98A4725FF6ULL, 0xE58DDCA3DC0B62ECULL, 0xA184F70C43DBFBBBULL, 
            0xB76529E98DE3A91CULL, 0x09166F807E6157DBULL, 0x2CA265E1EF7618EBULL, 0x8131BA068365617FULL, 
            0x973DEB463B9635B9ULL, 0x618B4BD633596D86ULL, 0xED6A878ACED8BA44ULL, 0xF56E998688F0CCD2ULL, 
            0xD70CBF1086CC877BULL, 0xA55EF0A4B30AD5F7ULL, 0xAAD11CDC482B98C2ULL, 0xCADD271DADDB0ABEULL, 
            0x9B391160F2CB081CULL, 0x7B9D232C78FB9368ULL, 0x2D3E83C8C4E3CD1CULL, 0x5BC469219C682F40ULL, 
            0x453DBEB68A9B948EULL, 0xF20965F6EB19BA8AULL, 0x251A4514CB07925EULL, 0x2D9072602233AD9FULL, 
            0x3B92F5BEF7FD40FCULL, 0x472EB75F704F1F53ULL, 0x4A931BD4CF040B57ULL, 0xB44C139FDAE4E470ULL
        }
    },
    {
        {
            0xFA554AA46BC13589ULL, 0xC288AE862B184AE6ULL, 0x196DB0616E8D8A66ULL, 0x43B2101ECBC61025ULL, 
            0xA954D723F95F6002ULL, 0x2F5505AC098E253DULL, 0xB0C42F358226D99FULL, 0xF01DB1B1260E6DAEULL, 
            0x178D193238D223DCULL, 0xF54C552110EB9B7EULL, 0xCA2AFA5FA1A09BC8ULL, 0xBC748498F2F23A4CULL, 
            0xA460F5D6F6784F2FULL, 0xF44AE53B3F79E96DULL, 0xFF787FB38A071979ULL, 0x80400C1F41ACD746ULL, 
            0x2C31AD0193778190ULL, 0x4530B815BA113A68ULL, 0xCBE5F3EFC96A3094ULL, 0xDA6F74E1BE4447C4ULL, 
            0x77A71B5ECE366D90ULL, 0xD982ACDD1F71ED80ULL, 0x70D12CCF15615C9BULL, 0x5973D584DDD8CA42ULL, 
            0x5B66E2BC67658413ULL, 0x2F5E6791C352E372ULL, 0xCC624A04E9F2DFB2ULL, 0x8AF016B7797374D1ULL, 
            0x3609D42BC9BD43E4ULL, 0x2EBC1E2A715E1309ULL, 0x09D6FEE9E4B69C55ULL, 0x064979BC3D8160BFULL
        },
        {
            0xE21B7C8BA1BDA2C8ULL, 0xB3BACCAE31C8D0D6ULL, 0xC08E02FC64F66BC4ULL, 0x04A1E23A5BC73D34ULL, 
            0x252D285525F9B27EULL, 0xE93C4C88D997C218ULL, 0x643E9AAAE3663B3AULL, 0x4F750C909905670FULL, 
            0xA206E9CF57ECA475ULL, 0x9AEEADD166F6926DULL, 0x8E467813F8DF74AFULL, 0xBB3790361F528C62ULL, 
            0xF9AA8F18E92E4662ULL, 0x04E7536B2C57B802ULL, 0x5730BF0D83F98CBFULL, 0x56C166B04857BE63ULL, 
            0x9A4E7E85D0C64E62ULL, 0x39EAC04CBB228982ULL, 0x8E820A84ADD350D3ULL, 0xD1C2D71E994DB137ULL, 
            0x06D09BB20336EB16ULL, 0xB4C86B8D679F37F7ULL, 0x92FDACAC6A31822BULL, 0x9118CC123B15DAB3ULL, 
            0xD79A3AD956B3CB2BULL, 0x7D4CB971782CED5EULL, 0x2B7F866F4611D699ULL, 0x2482CAF4D8A63DA7ULL, 
            0x103DC177E9B0E385ULL, 0x5C18B2D681CAEA81ULL, 0xAB6FCF579EBC5DD3ULL, 0xBC28938DBA37ECE1ULL
        },
        {
            0x87001296A8BB7EF6ULL, 0x6B6B03DBE572A710ULL, 0x2D7CB59BDEBAE815ULL, 0x2196B7738C3D4096ULL, 
            0xEC7D5678FDDACC44ULL, 0x0833146F8EB00043ULL, 0x50D546D411D8E5CEULL, 0x693B23FE5BCB6BDCULL, 
            0x673ADEB700692631ULL, 0x07BBAA4A1A991770ULL, 0xAD7984489FF22116ULL, 0xEA92C752D490612FULL, 
            0xE4C92F444669EAA4ULL, 0x6DCB93B41579D7CDULL, 0x8A5ED05297CF6211ULL, 0xCD19D6EFBAE7E2FDULL, 
            0x50806E1D63103B77ULL, 0x80BACBC6042FCDEDULL, 0xBA41C3E99F7ADA22ULL, 0x8C655231618E13F0ULL, 
            0xEFABE02614A94999ULL, 0xD69F462ADEF05B23ULL, 0xDA028F2EF484249AULL, 0xFF5ABCA6EB68DC52ULL, 
            0xF6791E94E3F93EEEULL, 0x235E93F5B60D0CD7ULL, 0x86817A985C685722ULL, 0x4C614A2DFF1B8286ULL, 
            0xA5CDF95BA77146FBULL, 0x39D8F4BFD0178D65ULL, 0x02E58A7AC5A60429ULL, 0xC2AEA004FF509AB1ULL
        },
        {
            0xE259C47996EF2E47ULL, 0x2B640EFD071241C7ULL, 0xFD0F38624C8B73BAULL, 0x424CE283FB23777DULL, 
            0xCCA6B948E98F48B7ULL, 0xA95142142BE528E7ULL, 0x4C3A64740233C249ULL, 0x8D73BD7915448A34ULL, 
            0x1C7A3612E2339E51ULL, 0x15F289287E0046B2ULL, 0x19C14D9BBA698AC3ULL, 0x0E0C3FB888966D9BULL, 
            0x1A0401D2BCBE1BFFULL, 0xE282C8AC76A96AA1ULL, 0xD3A9339A15FC038AULL, 0x35BF42D15D781BDEULL, 
            0x3E7EF2409FE69E08ULL, 0x76AA69EACA126B45ULL, 0x872DF5DF74C862CAULL, 0xFB83DF3D93E423C2ULL, 
            0xE75540BA0CAC39EDULL, 0x1B088F4132A2C4D9ULL, 0x5148F026E71227F0ULL, 0x149BC641E674A399ULL, 
            0x6F0BB1AD7D6580D9ULL, 0x80CA4326371023CBULL, 0x0F3589242239853DULL, 0x3B2327EBEDC95188ULL, 
            0x3F928D74C789AF26ULL, 0x63300B04F24D6B28ULL, 0xAAF235719FD5F460ULL, 0xE861ED24A9899558ULL
        },
        {
            0x3E1B85DDFF135CD0ULL, 0x30705DF64A6D6FBAULL, 0xC54E0E81ADF11C06ULL, 0x70F06465FAD468D8ULL, 
            0x6131090B43EDD4EBULL, 0x24875429AC71ECD8ULL, 0x46CACCD14AE46CCCULL, 0xAD6A3ED6EDBCCB37ULL, 
            0x39BC8F8842549753ULL, 0xBEC5AC06B9DB997EULL, 0xC2D64297F6604840ULL, 0x6668CEF148FC0984ULL, 
            0x2CF660DD62AD9C33ULL, 0x98356B1F869AAC21ULL, 0x726D332F7CACAE20ULL, 0x463D470EEE9603DCULL, 
            0x8326BCEA0F1D175BULL, 0xD06110D21D4ED969ULL, 0x07A3111BA1175FA3ULL, 0x73049256A3A3F025ULL, 
            0x345EB63AF5396EAFULL, 0x13763C621C60B0B8ULL, 0x7095E9007DA56B68ULL, 0x3D2ADCC58BA8AA72ULL, 
            0x81C257B49CF315F3ULL, 0x677B22DF608469EEULL, 0xE486D80EA3315F36ULL, 0xA1972DF421438863ULL, 
            0xE8CFB2184F889596ULL, 0xEEDECFE339C77013ULL, 0xBBC8DC70D6A89B7AULL, 0x73E72E98B97F26A8ULL
        },
        {
            0xA15C933A272AF362ULL, 0x7B472E03DEECF677ULL, 0xE00158265FBAE793ULL, 0x65498A19EC094729ULL, 
            0x15C0A41B69F987C4ULL, 0xC597E47D60A75F24ULL, 0x9D5A6B7BA1884210ULL, 0x5AE72675957B5A2EULL, 
            0x394E8C05235A8EC0ULL, 0x9986185BAC78DB2EULL, 0xC071852CF518F11DULL, 0xD5CD432ACFCAC047ULL, 
            0xCB01FAF6469A90E3ULL, 0x8AB3BAAADCB0E6F7ULL, 0x5080536DDB663F1AULL, 0x18CD2C0B531BD3BFULL, 
            0x68C40406611A4D07ULL, 0x4D37A4549D81FF2EULL, 0xEF3A0DF9174A0F60ULL, 0x6425BF628C36AECCULL, 
            0xCA064B56C7841293ULL, 0xB5CAE970B07C15E0ULL, 0x307144B2BF6C4489ULL, 0x00C3C828EE3E3E2AULL, 
            0x75C43F3FE9C7687DULL, 0xC17D40136D930B95ULL, 0xDE74E91A3F9F9EB9ULL, 0x6726FCADE0CF55E8ULL, 
            0xBD4D0DCA02FDAAE4ULL, 0x9BDE6E63A44810E5ULL, 0x9277D3E0F6181EB8ULL, 0xC9D635035D3C26D0ULL
        }
    },
    {
        {
            0x787A4D867E06E1FBULL, 0x54B6D00E3EEBE8B7ULL, 0xBA1E5D31B903E09BULL, 0xA642D44D23F97738ULL, 
            0xE0B1323F1CB7DF0FULL, 0xB8FDEFFB90818D90ULL, 0x4083DDF44276A6E2ULL, 0xA411A0F68EE6C724ULL, 
            0x0AB084609EE46F12ULL, 0x96EAAA16274CF86BULL, 0xF1748813EBD86E25ULL, 0x224640FAA194A8A2ULL, 
            0x6C5F689E8A04E419ULL, 0x4C08AC52A2845F64ULL, 0x70FA53FFCDCDA686ULL, 0x975868FB240AAB33ULL, 
            0x6C9E9B9FCDAEAB22ULL, 0x7C56A05EDE36E8E7ULL, 0x7F88BC7041142D4EULL, 0xFB453A1D8ED3E845ULL, 
            0x873E0B9909F721ADULL, 0x95C0AB246B1514B5ULL, 0xD1F3C6170C73F31BULL, 0x6B1995B18444141DULL, 
            0x859DF6B28FE01EB0ULL, 0x88DB30034ACE179FULL, 0x2C8B49BC1561BD32ULL, 0xA9E44DAE9BF833DAULL, 
            0x71EB69DFC24E396CULL, 0xDB7F439FEF437F7EULL, 0x3213A5B733020328ULL, 0x92A549E4E9AE61CEULL
        },
        {
            0x56B8836972898674ULL, 0x3485DBC0A0F985BCULL, 0xB5DF65389D1E2407ULL, 0x987DFD84FEB56E1AULL, 
            0xF1BB3EB0A5FF37E7ULL, 0x3F6F87AF10655E2FULL, 0x7A8DE9F33F3C1F4DULL, 0xB479C845D5F711CBULL, 
            0xB958812E74989CE2ULL, 0xD33BBA8D2F925C78ULL, 0x0033E9CCD863CFE2ULL, 0x3FA42D0DB9E1B664ULL, 
            0x795E9525229FC4A2ULL, 0xAAB45F90A65E2D71ULL, 0xDA2B51FE048C7BEEULL, 0x39B082D260CC0BA7ULL, 
            0x54CCA0A39DB485C9ULL, 0x08D4F9BFE0A3655BULL, 0x196949C3FC63A1B0ULL, 0xB4FBA17A9FB94A5CULL, 
            0xD12B03364481DBF3ULL, 0xE382ACE49F499C9AULL, 0x2B206CA9E6B6DFC2ULL, 0x6BB5DF6E5AF95C62ULL, 
            0xC8D1C8426862419EULL, 0xA933BA75874C9B3FULL, 0x4306249CE8280BE7ULL, 0x6E11E6DF9B73CF97ULL, 
            0xB71971B30A3ADBBEULL, 0x673B66EF369E131FULL, 0x4B57AF932EA5589AULL, 0x4641A2F8E9E8088EULL
        },
        {
            0xBF29240D77DFD413ULL, 0x57DBD4DF78E1CDD6ULL, 0x1F2EB8FE241368C7ULL, 0x1D5A39262E0C9579ULL, 
            0xDE4DC6DEED81501EULL, 0xCBBDDB7C3FC2648BULL, 0x18C39E218E102658ULL, 0xB9BC725790395D35ULL, 
            0x46FEA433FFDCBBD6ULL, 0x9C3049601E6E132AULL, 0x88FE8D7CEA1FE76CULL, 0xF8A655FA29E92E9FULL, 
            0xC22651C674BEEEFFULL, 0xCB5EA458B2FDFDC2ULL, 0x9C638FB83E7CC8C0ULL, 0xA6C6AE5D824A2506ULL, 
            0xC869ED0BDEE80A4DULL, 0x911246C24B282534ULL, 0x9E51F8657AA18D59ULL, 0x8E9482DE94BAE988ULL, 
            0x42FCA0246682FEA7ULL, 0x4DE43558870AD9E5ULL, 0x36FF745B7B9E6077ULL, 0x7C609DDA39743F2AULL, 
            0xDDD0AAF503EC2281ULL, 0x5FDA15827C7155B0ULL, 0x069286A980AF8AC1ULL, 0x0B01265809093029ULL, 
            0x9EF40AF8B5264B42ULL, 0xF422D1BFC34767ECULL, 0xDAF1803B950D184CULL, 0x06F011BD3F92BAF5ULL
        },
        {
            0x3A8F73BE1C81655AULL, 0x541DB9002938D399ULL, 0x89E82019FFE4F39FULL, 0x2D82E73A77AFE465ULL, 
            0x52667E842A6DAC7AULL, 0xD2C731FFA0E3737AULL, 0xD02264467FA53A19ULL, 0x4491ACE61DC2D5CCULL, 
            0x4CFBE8811FA964EFULL, 0xCDC79CAE58CA11FBULL, 0x56CC4679297B37B7ULL, 0x10BCFEFFB6820CB0ULL, 
            0x161E36778B0A2BD6ULL, 0x6325DC007FC9EC86ULL, 0xCCC8860DD546C2EDULL, 0xAAEAD2677C136C64ULL, 
            0x13BBEF2418519AE7ULL, 0xBC7E391AE6D14104ULL, 0xC1BFC920EF41784FULL, 0x28E570C1064B3D47ULL, 
            0x4E0CB2125E7EE630ULL, 0xDE2C2C9A2E50D3EAULL, 0x9EB56136406B7BCFULL, 0x2F37B06922EBE686ULL, 
            0xF7E2A14B4EC03885ULL, 0x819C36181EA67AE2ULL, 0x393555771B854FD3ULL, 0x8CFE8F2872AB3DC6ULL, 
            0x7D7BABAA9DA50EA7ULL, 0x995E46879466F72AULL, 0xA156576D94BEC9AFULL, 0xA3FC9DE6808D1ECDULL
        },
        {
            0xF5A37AECE484A5EFULL, 0x1F09AC2C82CC21F8ULL, 0xA30329626CE22D27ULL, 0x599E24118FA45269ULL, 
            0xA8F717C626DC13E0ULL, 0x499258547BEE4E04ULL, 0xEE984FFABCC1A455ULL, 0x5AE0651CE720D6B8ULL, 
            0xA5B2A368883B984CULL, 0x4CFB4D0C86E16875ULL, 0x1903A7D94A97E404ULL, 0x58572304EC2BF577ULL, 
            0x54E5FC8D204CA5EFULL, 0xFF85BAA282A3A32AULL, 0x729EE66EA5B96133ULL, 0xC32F49C976BF7AA9ULL, 
            0x9CCF0B7D56AFE3DFULL, 0xB3E10439A7F63997ULL, 0xE2BDDB98BCCD9715ULL, 0x16856795223785DAULL, 
            0x0D4025670FF22931ULL, 0x92DAC51DDF99F9EAULL, 0xA8C5AABDE2167C37ULL, 0xD4F5C51B07854D27ULL, 
            0x4909675D8560F6B7ULL, 0xC77CC9FD508D199FULL, 0x2501F43795E086ADULL, 0x2DBCDBF7C3FC030FULL, 
            0xB98098D999DCF363ULL, 0x99EFF9F74C7BDCCBULL, 0xCDE94D154D62F1E9ULL, 0x95E9B4F8F1691575ULL
        },
        {
            0x37A8842470606F30ULL, 0x28212868FAF72009ULL, 0x472D97F7D9676EDAULL, 0x77DEE27BFD38ED8CULL, 
            0x13E88F77C3A1149AULL, 0x0997CA200B095DD1ULL, 0x881BC398914838F8ULL, 0x0BAB8E38F9573F4DULL, 
            0xE126AD803F9875BAULL, 0xC09671C2F5A72165ULL, 0x789DABB94856B1DAULL, 0x9253914C6132E576ULL, 
            0x02E1E333A2F4597DULL, 0xBA8D78F59CC12DECULL, 0xEB194B83A92C2FF7ULL, 0x5D024AE3CAED4C9BULL, 
            0x4386A6287F316560ULL, 0xBEC4112561DEBC96ULL, 0x809BF05AD80E5BC0ULL, 0xC602722031E0A9FBULL, 
            0xA3944741406A834EULL, 0xCD1860948153C08AULL, 0x12D784E92CD36D07ULL, 0x6019311E4CC30343ULL, 
            0xD2CE2ACD18F4E010ULL, 0x89290B3AC4C91EEFULL, 0x324687F7E9DDB7BAULL, 0xBDE5EAAEBA4F35E8ULL, 
            0x2632F1D78118402BULL, 0x4F2DCDF084382B60ULL, 0xC561DF21A8319F1CULL, 0x20C59F30B29318DCULL
        }
    }
};

const TwistDomainConstants TwistExpander_Betelgeuse::kPhaseGConstants = {
    0xCB66C28CB5C5FB3CULL,
    0x72CCF7FCBCDFC60EULL,
    0xF20567DFF93AEF5FULL,
    0xCB66C28CB5C5FB3CULL,
    0x72CCF7FCBCDFC60EULL,
    0xF20567DFF93AEF5FULL,
    0xF78BA0662737F0FFULL,
    0x98089B01BE9D11CCULL,
    0x3A,
    0x0B,
    0x2B,
    0xDA,
    0xA5,
    0x4A,
    0x11,
    0x27
};

const TwistDomainSaltSet TwistExpander_Betelgeuse::kPhaseHSalts = {
    {
        {
            0xFA8A5CEC1B466E49ULL, 0x0822C203B8E199D3ULL, 0xBD5C3B7A48ECC8CCULL, 0xC47C29167481F5BFULL, 
            0xBCF5EFE18868B833ULL, 0x6083F184C58F5F37ULL, 0x17E9F2155AD4EF27ULL, 0x0691B084C859D118ULL, 
            0x04ABFFF534EDAABEULL, 0x37A7DA445617048EULL, 0x1756BE4EB5E37D06ULL, 0x2FAAE3587A23311AULL, 
            0x4FBC43102E517C03ULL, 0xB6C22FD013224C95ULL, 0x15BF07BA6395F5A5ULL, 0xC975ED558D47922EULL, 
            0x26095F10BB57051AULL, 0x03F851915E49A04AULL, 0x34A6A735508AAC1CULL, 0xFEF0D15F16E03D9DULL, 
            0x0B9FAA9360A35036ULL, 0x13E382B8C1A63B35ULL, 0xDA056634A9B625D4ULL, 0x0E1A6289CD889312ULL, 
            0x3151AA50AE6CDD3FULL, 0x6A9E240C57F4C890ULL, 0xE093FE8617066B09ULL, 0xE404BD0D818B2B63ULL, 
            0x8B9DD95E6063B84EULL, 0xEF7A037D0A14A10AULL, 0x4F4682D21CC3CE09ULL, 0x815E94FE716F96B6ULL
        },
        {
            0xE9BFA6C243D9EDEFULL, 0xADE4745A1EBBAD30ULL, 0x792425F850A031DDULL, 0x303652B30879A38FULL, 
            0x9E536B62D70F56FDULL, 0xFD96EEB2D03378DFULL, 0x433690FF3CF7290DULL, 0x1710B40F55D26DF8ULL, 
            0x75ECD6F3995B7ABFULL, 0xDBE0C1E303FECE53ULL, 0x18EBBC5CE9B87808ULL, 0x26325890C554D0C7ULL, 
            0x2821D148643B1836ULL, 0x1671D361F78FB2F6ULL, 0x94AAA5A1D3F95879ULL, 0x2EAF4F9A0C8FB88FULL, 
            0x1DDFD13B49B2C755ULL, 0x38664A2326C82F89ULL, 0x8802E9BB3FF73024ULL, 0x00C3E57ADEAA65CAULL, 
            0x2376865133AE0B85ULL, 0xF58AC1B029663D88ULL, 0xE6EE6C749812E5B6ULL, 0x93D2C2F697878710ULL, 
            0x1D17752F5D49A323ULL, 0x81BB50E923FAC819ULL, 0x1A96A1AC7A2BD225ULL, 0x3A3DB6346B206764ULL, 
            0x548BF864B7FC503FULL, 0x31051A65E19A3730ULL, 0x8B78BA016F34DCC4ULL, 0x52CA58C301B69420ULL
        },
        {
            0x793D4CD157C26189ULL, 0x52CBA48F6F98D019ULL, 0x8C81C35422929A2BULL, 0xC94290D06325E4AAULL, 
            0x17F7D4FAF9EF497EULL, 0x9BFE85A9DF31BAF5ULL, 0x14EA3CC91CBA9443ULL, 0x276A122ED4E43390ULL, 
            0x7A418B22F9DD0A01ULL, 0x88EB6E68B831CBA9ULL, 0xE786B1AABF6C3883ULL, 0x6B1EE15E4E451F47ULL, 
            0x7F87EC24AF1B3F4AULL, 0xC18E9F24597A7EC8ULL, 0xF383DA0D3FA1C9AEULL, 0xBF8994AC75630DB8ULL, 
            0xB99C46F4A3AF3AFFULL, 0xB56A54A79C49FE47ULL, 0xB47D5A137404AB22ULL, 0xE5D8951E76FD960FULL, 
            0x027D6D4EF1843064ULL, 0x3DB5FBC6048FC605ULL, 0x91FE42993A539A2FULL, 0xCF2B34BFA7AA4E2CULL, 
            0xB788B5DB8BDE5EDDULL, 0x08E0C15A16B5706AULL, 0x7AA9050A195A1C91ULL, 0xC2E74DC023937A54ULL, 
            0x38458DC532C7E688ULL, 0x7B3EE5C2BA2ED14CULL, 0x3234CD421BB686D4ULL, 0x12FAECB5F5220D24ULL
        },
        {
            0x74EF93D0C8C389F9ULL, 0x052223A7C8139C1CULL, 0x33EEA268AB61F40FULL, 0x42FE052C248090B3ULL, 
            0x27CE0894CF7039B0ULL, 0xCE5070531F3BF1C8ULL, 0x647245AA44F49A23ULL, 0x75E8FF7CAADF8C58ULL, 
            0x8399A2ECFF085C7AULL, 0x0492063C52EBB0E8ULL, 0xB0CA7D8A9E4B8423ULL, 0x4E6F919E94D21A2EULL, 
            0x6A9313ABE93813CCULL, 0xCBA7B59DA4393A14ULL, 0x6325D5092BF37DBBULL, 0x92EA1379AA2574ADULL, 
            0xA6F81DC70AC0AF6FULL, 0x201B99D05C32C41AULL, 0x2030B9A6083B8AC0ULL, 0xBAA2D58636D3D78CULL, 
            0x30195FB009FD9C4EULL, 0x93C67CBE153C7F1CULL, 0x49EC4F4161361091ULL, 0xBA7CC8B400839835ULL, 
            0x2BCA1B60439D06CDULL, 0x361669F65EB37977ULL, 0x53F0892DE8FA2500ULL, 0xC4CF5B7517782366ULL, 
            0x9E5EE587ACE070BFULL, 0xB642F209233FE948ULL, 0x576ECE5A4570B172ULL, 0xBB58CDCC127F9894ULL
        },
        {
            0x9EC4FC43CB498F68ULL, 0x15E684A2C2CF2A16ULL, 0xE12DA5955DF036A3ULL, 0x0C04708FBF4A70C6ULL, 
            0xD1159D9D45E7F963ULL, 0xD2300F79C75FA4C4ULL, 0xC6F7555DC0FC7CDDULL, 0x1CA55D4F88970A8BULL, 
            0xE1044B51EBAFBE8EULL, 0xC72FB9EE720ACB13ULL, 0xC4E515F0E6984FD5ULL, 0xEB68E01088E2F704ULL, 
            0xA2F355498778EE52ULL, 0x54705935728D050FULL, 0x529C4684CCBB4C62ULL, 0x782B8FFC2A7B32B5ULL, 
            0x0376FED4C0CBA233ULL, 0xE51A112618988FF0ULL, 0x3744EA26649056AAULL, 0x96BB8399D8B5742FULL, 
            0x6AEE6C6B906CC3AFULL, 0x1BE3CA97176DD1B8ULL, 0xD0E3A96962668EDAULL, 0xE42E792672643754ULL, 
            0x0034831087A2AA58ULL, 0xE87BE09DC388CD76ULL, 0x33D454D3EABF996DULL, 0x93E9410CEFE8EDEBULL, 
            0x7A6E9A69EDC5D9F3ULL, 0xC841410231468898ULL, 0x809EEFFCCF17E140ULL, 0x4ED978E6F422C987ULL
        },
        {
            0xA2B40510FF49BD4FULL, 0x5A374BAA0B095227ULL, 0xBF17C0FF7289A438ULL, 0x0C4432E217A1E63AULL, 
            0x0B841451A2BE702EULL, 0x13BF068580798F15ULL, 0xA9C832487679C508ULL, 0x93C940D81B9AEB7DULL, 
            0x25724700DE445C4FULL, 0x56D105213F9DA6B4ULL, 0x9902935CEE6690A8ULL, 0x0E00F144AF349A17ULL, 
            0x89693E38AB41E77DULL, 0x7B5679DEE91D676DULL, 0x4AB55958CF433D4EULL, 0x04B2AF76ECA4593BULL, 
            0xB92F45388AA4123AULL, 0xDAC0C65497F28DBEULL, 0x85F307101B140874ULL, 0xD31FCC8813930866ULL, 
            0x18B9224B5000E46FULL, 0x29B37314C0498393ULL, 0x5187277F277DCACEULL, 0xC904D214D428AED0ULL, 
            0x3957715F77AFD02BULL, 0x687024DFDC81C1DDULL, 0xE03E61D304DE78DCULL, 0x60AB8BA5EAF8F1C7ULL, 
            0x51BF37F2C2F4272BULL, 0x4F614E7CE425ABC8ULL, 0x6E4ACA8DFBB53ACCULL, 0xFA86E995E50772D0ULL
        }
    },
    {
        {
            0x4A089F16197CE395ULL, 0x1C07651687A78D17ULL, 0x48A81EFCD0B3E779ULL, 0x91BE32295868449FULL, 
            0x9962798383334538ULL, 0xC76ADBB3AFFABBE5ULL, 0xCC6CB869A25AF47FULL, 0x9A6E0515259BAC81ULL, 
            0x36EC6181458090D6ULL, 0x31C4E6433F52186EULL, 0x0B84836C21834030ULL, 0xEA57E4B208C11AE7ULL, 
            0xBDB57F5D3F8EEB8DULL, 0x1BF5BF7D84376052ULL, 0xC4B41DEA53D6736DULL, 0xF93E27A0E26ACE4FULL, 
            0x32731574CA5646A9ULL, 0x1279C4138BCF2F86ULL, 0xD389EC1523B61E01ULL, 0x9D0C09A1119F23E1ULL, 
            0x4AC28290E803844AULL, 0xCD98CB8CEE2CE0B0ULL, 0x6E7F538E72C55598ULL, 0x43FAB1150C6B0E48ULL, 
            0x021F15A96BCD5431ULL, 0x32AA803CE51AB7DCULL, 0xE5D8022244E80560ULL, 0x97262B7D96F39ABBULL, 
            0x846C239770755C3CULL, 0xBD2BB098253ED751ULL, 0xD4925E859040A0C6ULL, 0x1974EE281A02B5D3ULL
        },
        {
            0x88386AC72D08E4A1ULL, 0x5D777C974AB4DD6BULL, 0x656211D9A1560A51ULL, 0xEECD8C0C3F5C2628ULL, 
            0x4313461AEC0702C5ULL, 0x3659DDEC203DA6C3ULL, 0x114477E6B5CFEF50ULL, 0xD6C8F9603221EBB1ULL, 
            0xF8E8DA5B6BFF6489ULL, 0x63119E0BCE6681D9ULL, 0xA1F0B4259F71DB54ULL, 0x127905153947DC62ULL, 
            0x35146BBC503F94B2ULL, 0xD143B6F78E619513ULL, 0x5DDF235EB31D9D78ULL, 0x93DA3CB2C3EFD82CULL, 
            0xABC33A93B3D52F22ULL, 0x8C2B0908A5AEB2DBULL, 0x57C8894FFAF26CB1ULL, 0x59003C73BED312EBULL, 
            0x32B0F54DA39A9BFCULL, 0x39CD8AB0F4792F86ULL, 0x2EE40BB88C8E93EFULL, 0x6F0171A44449986EULL, 
            0xAB129C828E62E455ULL, 0xEC45054FF78DD4B6ULL, 0xA3FABD2297B7D753ULL, 0x7139A99B0A087CD4ULL, 
            0xDCC7BD3EC6C38DD2ULL, 0x6ADEF9BFAB09F1D8ULL, 0xF18276E85F41D375ULL, 0xB0764790251B51F0ULL
        },
        {
            0x60CF7CC0BA60B062ULL, 0x14CDB66C2A2FF894ULL, 0x549E3CDAA7AE0AD9ULL, 0x94FEB3C8BD0E9333ULL, 
            0xC7BDE2E809DDA86CULL, 0x7BF4C1687E056902ULL, 0xE25EA3C89AE583CAULL, 0x4F06DAD019D73087ULL, 
            0x8F23DE8FC40C87EBULL, 0x3F733C8713885D78ULL, 0x5877444E094FD3D8ULL, 0x2217341F97FDD391ULL, 
            0xE970445C6F6AFDCCULL, 0x104571A680BED42DULL, 0x4E03019923931FA2ULL, 0xBE9317B5D86482ADULL, 
            0x335F25BBFB3979B6ULL, 0x566F222EBCF282DBULL, 0x3FD59497C9123FF4ULL, 0xE451165FB5B3CEDAULL, 
            0xA949FB6690B8D3CAULL, 0x5E16F032BBA3B422ULL, 0x930D39A3234A6448ULL, 0xF8578D2F134F4D8FULL, 
            0x39E12C87EBE15F0EULL, 0xAB95A1D6FA00846EULL, 0x020B9EE37E5606A0ULL, 0xE24305A8398763A5ULL, 
            0xEFB77B90D329E23AULL, 0x9E396AD188494AD3ULL, 0x3AF2D563F379E051ULL, 0x0E1D0E4EC054DE0BULL
        },
        {
            0xFE3A68BFFCA07B04ULL, 0xC2C88A68F7CB7AA2ULL, 0x089FA051A0C76998ULL, 0xA7162E33B9F29CCAULL, 
            0x6CED5B50A2DD3A64ULL, 0x184A4C22C694CACCULL, 0x5021D5A0C2E735B2ULL, 0xAA789DC6F1194D40ULL, 
            0xF2AAE426FC2E24ABULL, 0xF1307077D2A79DD1ULL, 0xB7FBCBDF350B45ECULL, 0x83ECD55306F9666CULL, 
            0xFDBBA3B76B9B3062ULL, 0x615DD8AEEEA21F28ULL, 0x42A7AED9ADAA4542ULL, 0x396203EB1286A194ULL, 
            0x6C9589864F72B6F2ULL, 0xA336D94F070C85D7ULL, 0x216C7EBA5F76E9EEULL, 0x4DFE0A5C90D5101EULL, 
            0x1F1FE1984C249C98ULL, 0x128601C3C75778AFULL, 0xAD0303F1C0F4C0BBULL, 0xCAF0BCC4A2442820ULL, 
            0xAA868E1B9DFD6456ULL, 0x812DA76AC5AE75D8ULL, 0x61DDDF2EECD80FB8ULL, 0x799E6BE067E4A7B3ULL, 
            0xCACF1E40C30C243AULL, 0xAD631E561B0DB392ULL, 0xD4E800E4507A5C89ULL, 0xE7CBF6BF75A366F8ULL
        },
        {
            0x7A9AEE391811FB29ULL, 0xC7D48F51285A345CULL, 0x3F92B98A9423E2C2ULL, 0xBFEEB121C353DE10ULL, 
            0xAA8BFC525CA9416BULL, 0xEA0F00CBEB1848E0ULL, 0x28DED242B9998229ULL, 0xFFAB120423DD2290ULL, 
            0x3BD565CBAC89F9EEULL, 0xDD94816472EE79F7ULL, 0xF2EAC9EFC122FF53ULL, 0x629008BF390F73B2ULL, 
            0xA2E713F3DDF915C4ULL, 0x314D6D35DF64DD30ULL, 0xAA67EFAF5CC152D1ULL, 0xC8C60496F60F660EULL, 
            0xF0B821D2325F0AADULL, 0xB0BA89673DFAB3EEULL, 0xCFD48671EA44C08AULL, 0x0CB647B4BE69581DULL, 
            0xDBBD7AA7B59629D9ULL, 0xD46F11601D005388ULL, 0x46599772C2E8DCF8ULL, 0x87C2CC2F152CA679ULL, 
            0xA3134B5309B4E186ULL, 0xEA1190814884A7BFULL, 0xC4E96C4098E361CBULL, 0xAE022D6D7E36A74FULL, 
            0xE46BFA4CE82E4892ULL, 0xFDB81BCC0BD9F569ULL, 0xF66AEC605ED36591ULL, 0x0CB243666138BDAAULL
        },
        {
            0x8D73CEB00F1A6B28ULL, 0xE04F120AFF40230CULL, 0x1AD8CD30601246C0ULL, 0x2310D57BEE1B37CBULL, 
            0xF7A8C20BDC797D53ULL, 0x04D6DA95BC6E9574ULL, 0x952EE0EF8DA1FFF4ULL, 0x5AC1AF7DAE6B02B4ULL, 
            0x2D7FDFC2A7BE601FULL, 0xB840B7A9B54BA020ULL, 0x50F719470FD218D9ULL, 0x095F4D0177AEDF6EULL, 
            0xA48C16F20B451796ULL, 0xC20A3D8174C473AEULL, 0xF1087DDD3FF02AEFULL, 0xA372F85BA906C6F2ULL, 
            0xA698B99F819C9066ULL, 0x340B4B1D628B9998ULL, 0x0A3C482081AC09BAULL, 0x0D799677138A9CE6ULL, 
            0xA64750512BA69EE4ULL, 0xEAD19BB491618D06ULL, 0x4F6D864A9AC5E8CDULL, 0xF3293AEE248A604CULL, 
            0xB07EB37EFD70150AULL, 0xFBD9B8165F79A476ULL, 0x16FDA397B2184E1EULL, 0x4C2AE913B9D53F0AULL, 
            0xDD21B93DA5D99667ULL, 0x88B0DE1FC3A340FFULL, 0xF1EE122D504D109AULL, 0x14A6094E00C773B5ULL
        }
    },
    {
        {
            0xE0671DD71819F2C7ULL, 0x66E77F2E604C9ECAULL, 0x72C0B2BB8F88A2B5ULL, 0xA80622839DD246CCULL, 
            0x64919A22A5A11FBDULL, 0xB1BF034FA96E5427ULL, 0xA80129F39374B699ULL, 0x785D67EF81290770ULL, 
            0x854C4D5BAECFFFC1ULL, 0xB7651CD3CC3C9388ULL, 0xF398F7FD6B8B0AE8ULL, 0x42A6388F26BAC455ULL, 
            0x589673DA35CC284CULL, 0x8C7EB09BE61859D9ULL, 0x719B7240AF7581DBULL, 0xD67424A269C9BEC8ULL, 
            0xAA71195F178954A5ULL, 0x0AAAAEECEECC0BEDULL, 0x77BF48A5D717AA09ULL, 0x39CA1B67F61D5272ULL, 
            0xB326D5E8736C9275ULL, 0xF40450F23B7C62C8ULL, 0x0A75B22CE65B0A7EULL, 0xCB93F4A184887D69ULL, 
            0x9413A858AE059FB3ULL, 0x2B05F82A2040FBA3ULL, 0x6554875725649178ULL, 0xFCBCB760D1B2F531ULL, 
            0x48539E7EE51A0A94ULL, 0x97D1C3763B548716ULL, 0xAAF287292F8A0D91ULL, 0x836AAC0A7A0D1CC0ULL
        },
        {
            0xBD16D0DAEADAB9F3ULL, 0x8D714302234D6CC1ULL, 0x5A83A2A190CBC134ULL, 0xA78D6C701EFEF4CFULL, 
            0x01336BE6451734EFULL, 0xB7243558011C28ABULL, 0x79BB33FC33C6B638ULL, 0xD9C11C11A9F6EB6EULL, 
            0x8EF2771A6497B9AEULL, 0x2AE26D6C67863848ULL, 0x917ACA1A7BD1AFC0ULL, 0x159DD3521E9A0369ULL, 
            0xB93787A9E9685893ULL, 0x8BE7637D41F72BFCULL, 0xAF75F9B8DE5248CAULL, 0x9117F7619C1324BAULL, 
            0x650201CB40916F8BULL, 0x49E1152514E805AAULL, 0x58BF4826D5F4955EULL, 0xC5A1C43D395FE2D8ULL, 
            0xE49ADC03BFEBBCE6ULL, 0xFA071CCE10850D60ULL, 0x5618E069AF57332CULL, 0x395A106F011C829EULL, 
            0xB09636015F2B223BULL, 0x64C26BCD7AC3991EULL, 0xE486D398057A0A05ULL, 0x628154113CFABD24ULL, 
            0xB885FB10C0B5ADBEULL, 0xD1C1AE5D4D9B6317ULL, 0xBB30170F1B28AE0BULL, 0xD8DCEC078DDA08D7ULL
        },
        {
            0x1957314932573FFDULL, 0x3B6BB275F7C3D813ULL, 0x59C7B35976906988ULL, 0x9DAF943E6B4F61DFULL, 
            0xAD394BB51B8681B8ULL, 0xE29247ABDCD0F615ULL, 0xDECFB68DBF1FF51DULL, 0x36A874B2E0B23C35ULL, 
            0xFF931C19B5AB305DULL, 0xCF31336699EEDD5DULL, 0xA7FC550968DF3675ULL, 0x7A799DE17DC8E8D5ULL, 
            0x56702F1FE4DDEE44ULL, 0x20131DF9A0F2C95FULL, 0xFF2382182BDE4710ULL, 0x3D2C5E44DF6B3CADULL, 
            0x4FF4B8A6F92F6BBAULL, 0x5F3943C3396DA4FFULL, 0x4ED57935147DD181ULL, 0x7D0C3C32845F79F1ULL, 
            0xB3725E99F251A838ULL, 0x60EBB517EF043338ULL, 0x84131B5768592A53ULL, 0x9E5686CA1D20F198ULL, 
            0x3C4E271110AD01EEULL, 0x51FE17B3D5FE38BBULL, 0x6462A538F6AB0E2BULL, 0xE9CF3786B4E05DF4ULL, 
            0x27FFF0BC33F72AA3ULL, 0xBAAAF4E768AE5682ULL, 0xE79BB159861842DCULL, 0x4935929EC824A1D2ULL
        },
        {
            0x391A0012A9533C67ULL, 0xFAC5FA55C4B72F44ULL, 0x0CFF0EA7020531B4ULL, 0xD7EA4082270396F4ULL, 
            0x0870C58CBE8E8147ULL, 0x4721EBE3A84AFE8FULL, 0x67AF40AD24D5E9B5ULL, 0xB854BA8E94280BFFULL, 
            0xBABB789EBDBDACA0ULL, 0x0593B96AA7039E9DULL, 0x6FE22535A102CFECULL, 0x8FDC23913DD99626ULL, 
            0x6C99CBE0BBB0E8D4ULL, 0xF1675E0F7BBA931FULL, 0xC5DECB853FB1B111ULL, 0x5E3EBFD65E5E2365ULL, 
            0xDAE4A26DDBC2E3F6ULL, 0x6B5D413ABECEB75FULL, 0xD1F1D4E7CBD1A223ULL, 0xE19F62C6844F31EEULL, 
            0xE5FDF22FD4EECA11ULL, 0xF0A15DF2E265C04CULL, 0xDC52C3A6A6866DFDULL, 0xD878542F04C4D230ULL, 
            0x0E6040822A216AB0ULL, 0x16AAA9FB7F62079FULL, 0x130CE7C5C438266DULL, 0x66A50A0387B4FB4BULL, 
            0x806DD6CA666DCEB0ULL, 0x7D0FB0104CA2497FULL, 0x9A99378486FB6DE4ULL, 0x4D6082A9FB9C5613ULL
        },
        {
            0xAC0C65A6BC37A7BEULL, 0x1D548A72E5210152ULL, 0xBFD3B76EA629B300ULL, 0xDAEB6040B16B633DULL, 
            0xB698E625A12AB765ULL, 0x3C2329D66047DC0AULL, 0x943B5AB632ADE016ULL, 0xED60B841AC45A16BULL, 
            0xEB66259C804C7935ULL, 0x002D6746B5AA6065ULL, 0x8D7AB57EBF5EA70FULL, 0xD37C1BE6E47193B0ULL, 
            0xAF43095C415DD4E4ULL, 0x79458DF839709D47ULL, 0x7DA23CB5E1E0B632ULL, 0xF5EA086AD1435A36ULL, 
            0x9FABC49628292104ULL, 0xC8BC1E149DC39DA8ULL, 0x1E9156DB7D243C6EULL, 0xE395AA0245A3541CULL, 
            0xA71A0EF5F8BB28A0ULL, 0x6DCE36FC27A11A64ULL, 0x98E90453ECE8E53CULL, 0x39D0918DB35BCB5EULL, 
            0x696D1A830104B4FDULL, 0xDF8D5C8F9DCA625AULL, 0x698DC18FADF9DC98ULL, 0x31D4F1E08603A1FDULL, 
            0x164988E98AC48F80ULL, 0x6409249CA5AA6C99ULL, 0x73CF16CF6F3EDB7CULL, 0x99A02B73CD265FFEULL
        },
        {
            0xA866D09C8BBC5888ULL, 0xDF081160ACF8ED26ULL, 0xDB5FDE59A57E50C0ULL, 0x3C43FBC510E0D505ULL, 
            0xAA1065747F5E769EULL, 0x875C45BDF23AB4E2ULL, 0x8F74F23BD3979F43ULL, 0x52D8EC98669ECE2CULL, 
            0x24FFB793B97798AFULL, 0x86674D5BBEBEC3A7ULL, 0x1BBF929FBE3773F6ULL, 0x24AF9769AAFC42D9ULL, 
            0x81853638E588DE0FULL, 0x257D67449CC7D447ULL, 0x5595430BA0A9D44FULL, 0x98941DEB98A7DC7BULL, 
            0x1671BFE46FBF69CAULL, 0x1C9072BB8C23DABCULL, 0xD99990B1F3EB7914ULL, 0xCB5A007C31A2AA88ULL, 
            0x9EF2C64FEE72AF97ULL, 0x68C993CD0601B316ULL, 0x0770682F81BBC45CULL, 0x26899F64225B3BF4ULL, 
            0xF9890E68114020C1ULL, 0x967713CE47CDA46AULL, 0x333B646661296774ULL, 0x054D7FEDF89A446FULL, 
            0x5BC65F1B22094FCCULL, 0xD88336717FEB3847ULL, 0x9AC4A4FBAD358154ULL, 0x6F23621711A8B543ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Betelgeuse::kPhaseHConstants = {
    0x9991FCBEA4313080ULL,
    0x8033E4A626D79C53ULL,
    0x06680782E3B8B384ULL,
    0x9991FCBEA4313080ULL,
    0x8033E4A626D79C53ULL,
    0x06680782E3B8B384ULL,
    0x967E3BD28C93B246ULL,
    0x1EC3A5D5FCD02A36ULL,
    0x0F,
    0x09,
    0x92,
    0xC5,
    0x6F,
    0xF2,
    0xEC,
    0x3B
};

