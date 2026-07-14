#include "TwistExpander_Alnitak.hpp"
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

TwistExpander_Alnitak::TwistExpander_Alnitak()
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

void TwistExpander_Alnitak::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xF0E3493A13BBFF30ULL; std::uint64_t aIngress = 0xBAC0918C14E569F3ULL; std::uint64_t aCarry = 0xCD31C82977E32169ULL;

    std::uint64_t aWandererA = 0xF870EE8798BB19ABULL; std::uint64_t aWandererB = 0xF959EBC23194BF52ULL; std::uint64_t aWandererC = 0x9309F00201670F64ULL; std::uint64_t aWandererD = 0x8B5D889964A99CF6ULL;
    std::uint64_t aWandererE = 0xBCC5EE731AB33ECBULL; std::uint64_t aWandererF = 0xBC39C10DB5508262ULL; std::uint64_t aWandererG = 0xA2695D6C4DC196E6ULL; std::uint64_t aWandererH = 0xC29876B2F098BBF0ULL;
    std::uint64_t aWandererI = 0xA93A635F383A096DULL; std::uint64_t aWandererJ = 0xA96951BF16874504ULL; std::uint64_t aWandererK = 0x9425664F1073EF6EULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 9960479878860626658U;
        aCarry = 11327044120568031200U;
        aWandererA = 10493515472809042672U;
        aWandererB = 13400066567944513532U;
        aWandererC = 16504341615950948860U;
        aWandererD = 15062276361751111467U;
        aWandererE = 12946255192080645418U;
        aWandererF = 10874091715877394512U;
        aWandererG = 13450481799670795407U;
        aWandererH = 12624118729227167727U;
        aWandererI = 10543980227525514106U;
        aWandererJ = 16947175930356787118U;
        aWandererK = 12519600673364924230U;
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
    TwistExpander_Alnitak_Arx::KDF_A_A(pWorkSpace,
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
    TwistExpander_Alnitak_Arx::KDF_A_B(pWorkSpace,
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
    TwistExpander_Alnitak_Arx::KDF_A_C(pWorkSpace,
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
    TwistExpander_Alnitak_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Alnitak_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Alnitak::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xB2E9E946272927ADULL; std::uint64_t aIngress = 0xE8F96BBBA8F7CC29ULL; std::uint64_t aCarry = 0x814638E1BA4AA01BULL;

    std::uint64_t aWandererA = 0xD87D8BB30B9776E3ULL; std::uint64_t aWandererB = 0x98C413F3288B03ACULL; std::uint64_t aWandererC = 0x837F8F311B8A863EULL; std::uint64_t aWandererD = 0x823D32019E2A4994ULL;
    std::uint64_t aWandererE = 0xF673CA571F81BB32ULL; std::uint64_t aWandererF = 0xDCAD04C164429BE1ULL; std::uint64_t aWandererG = 0x96A020A20AD72240ULL; std::uint64_t aWandererH = 0xEE59396824133446ULL;
    std::uint64_t aWandererI = 0xF1DA21E26F6A564CULL; std::uint64_t aWandererJ = 0x829503311D9434ACULL; std::uint64_t aWandererK = 0xEEC59F0D16957A43ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 12497227535237240368U;
        aCarry = 10087968342511632416U;
        aWandererA = 16438823957968347470U;
        aWandererB = 12507039180159311587U;
        aWandererC = 11208235002548162728U;
        aWandererD = 15540780718974673765U;
        aWandererE = 16558624630624070159U;
        aWandererF = 14781563633625127221U;
        aWandererG = 10899439633761406365U;
        aWandererH = 10340981178549700244U;
        aWandererI = 17196125652900336072U;
        aWandererJ = 11561204769087270735U;
        aWandererK = 14737003977369417957U;
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
    TwistExpander_Alnitak_Arx::KDF_B_A(pWorkSpace,
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
    TwistExpander_Alnitak_Arx::KDF_B_B(pWorkSpace,
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
    TwistExpander_Alnitak_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Alnitak_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Alnitak::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0x9C428113C5F73D40ULL;
    std::uint64_t aIngress = 0xCC4D46E527850DA5ULL;
    std::uint64_t aCarry = 0xD41AD8440DE3E71EULL;

    std::uint64_t aWandererA = 0xDB01852E8C21E2BCULL;
    std::uint64_t aWandererB = 0xC72198D37E2E2BBDULL;
    std::uint64_t aWandererC = 0xC793C0A95C9B3F17ULL;
    std::uint64_t aWandererD = 0xFE56C3D076246476ULL;
    std::uint64_t aWandererE = 0xC810E3640B6BA40EULL;
    std::uint64_t aWandererF = 0xCD9F906B61E98953ULL;
    std::uint64_t aWandererG = 0x8BB48646F2E3D1FAULL;
    std::uint64_t aWandererH = 0xFA5650287EB14475ULL;
    std::uint64_t aWandererI = 0x892A880F5AD381E5ULL;
    std::uint64_t aWandererJ = 0xAA4EEEA1F49C3AD4ULL;
    std::uint64_t aWandererK = 0xD2E5DA82337D6D5BULL;

    // [seed]
        TwistSnow::Aria256Counter(aSource, aSnowLaneA);
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneB);
        TwistSnow::AES256Counter(aSource, aSnowLaneC);
        TwistSnow::Sha256Counter(aSource, aSnowLaneD);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneA);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneH);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneE);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneB);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneC);
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
    TwistExpander_Alnitak_Arx::Seed_A(pWorkSpace,
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
    TwistExpander_Alnitak_Arx::Seed_B(pWorkSpace,
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
    TwistExpander_Alnitak_Arx::Seed_C(pWorkSpace,
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
    TwistExpander_Alnitak_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Alnitak_Arx::Seed_E(pWorkSpace,
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
    TwistExpander_Alnitak_Arx::Seed_F(pWorkSpace,
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
    TwistExpander_Alnitak_Arx::Seed_G(pWorkSpace,
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
    TwistExpander_Alnitak_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Alnitak_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Alnitak_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Alnitak_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 6 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1924 / 1984 (96.98%)
// Total distance from earlier candidates: 9668
void TwistExpander_Alnitak::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 237U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1902U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1679U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 460U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1899U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1203U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1881U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1900U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 742U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1283U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1629U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 66U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 803U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 184U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 81U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1359U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 538U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1261U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 709U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 425U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 458U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 836U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 839U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 674U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1710U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1845U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1154U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1295U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 810U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1309U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 732U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 660U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 329U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 960U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1450U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 808U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 777U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1979U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1221U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 160U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 578U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1270U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1635U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 740U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 374U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 944U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 951U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1795U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 728U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 981U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 819U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 377U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1942U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1930U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1756U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 378U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 964U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 929U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1174U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 664U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1691U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 522U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1076U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 451U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 208U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1253U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 942U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 697U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 150U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 2037U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1773U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1757U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 181U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 900U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 872U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1977U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1746U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 794U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 102U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1926U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1248U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1218U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 492U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 924U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 745U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 282U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 122U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 49U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 790U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 32U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1092U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 465U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1068U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 756U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1311U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 501U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1576U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 400U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1009U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 801U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1202U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 2026U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1928U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1764U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 955U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1310U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 990U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 828U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 603U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1627U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 802U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1534U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1167U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 2015U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1729U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1975U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 143U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 304U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1035U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 636U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 920U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 605U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1713U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1308U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 368U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 48U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1696U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1095U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }
}

void TwistExpander_Alnitak::TwistBlock(TwistWorkSpace *pWorkSpace,
                                       std::uint8_t *pSource,
                                       std::uint8_t *pDestination) {
    TwistExpander::TwistBlock(pWorkSpace, pSource, pDestination);
    if ((pWorkSpace == nullptr) || (pDestination == nullptr)) { return; }
    std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    std::uint64_t aPrevious = 0x8211024EE348354BULL; std::uint64_t aIngress = 0xB21F99078D8F7B48ULL; std::uint64_t aCarry = 0xB9BE62F4901ACA2FULL;

    std::uint64_t aWandererA = 0xEDF4FD637D147B10ULL; std::uint64_t aWandererB = 0x814C8F309E6C6F2DULL; std::uint64_t aWandererC = 0xBB1B955F0A20EBF2ULL; std::uint64_t aWandererD = 0xEFF7DD8E1BF02DF0ULL;
    std::uint64_t aWandererE = 0xE76BF8D59C98F5EFULL; std::uint64_t aWandererF = 0xCF5BB2AF63799FF0ULL; std::uint64_t aWandererG = 0xABA71A1BA3B90445ULL; std::uint64_t aWandererH = 0xEBF4B0466298AA4AULL;
    std::uint64_t aWandererI = 0x87CC36B35868B411ULL; std::uint64_t aWandererJ = 0xD900B55A1BDA8361ULL; std::uint64_t aWandererK = 0xDD038C0956187B53ULL;

    // [seed]
        aPrevious = 13177521925686451376U;
        aCarry = 14184064460100593059U;
        aWandererA = 14100182083721917675U;
        aWandererB = 13321564342570851602U;
        aWandererC = 16269886613988320067U;
        aWandererD = 15539366445451019675U;
        aWandererE = 11952720971795604194U;
        aWandererF = 16451851239794959146U;
        aWandererG = 9434307200838610869U;
        aWandererH = 12154058552298355858U;
        aWandererI = 11260753926998715909U;
        aWandererJ = 17639532012143846669U;
        aWandererK = 13621193090383080504U;
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
    TwistExpander_Alnitak_Arx::Twist_A(pWorkSpace,
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
    TwistExpander_Alnitak_Arx::Twist_B(pWorkSpace,
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
    TwistExpander_Alnitak_Arx::Twist_C(pWorkSpace,
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
    TwistExpander_Alnitak_Arx::Twist_D(pWorkSpace,
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
    TwistExpander_Alnitak_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Alnitak_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Alnitak_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 6 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 2850; nearest pair: 521 / 674
void TwistExpander_Alnitak::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3634U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4097U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 208U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6186U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2431U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5566U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7779U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7117U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2707U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 803U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1874U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2383U) & S_QUARTER1);
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
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6844U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4772U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 8103U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 907U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 13U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 247U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1833U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1062U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1304U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1013U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1081U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2028U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1844U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 227U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1594U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 577U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 625U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1845U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1554U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 529U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 180U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 122U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 622U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1279U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 6 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 2854; nearest pair: 523 / 674
void TwistExpander_Alnitak::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5903U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5231U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5002U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7584U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6072U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5565U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 8079U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3295U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1547U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1098U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2767U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6547U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7270U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6573U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5315U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7556U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 785U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 326U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1975U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 763U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 95U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 72U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1276U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 51U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1663U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 579U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 578U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 23U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 723U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1971U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 279U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 736U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 828U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 31U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 322U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1626U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Alnitak::kPhaseASalts = {
    {
        {
            0xEE0DC20922D3364FULL, 0x22B92A98D5DF948EULL, 0x65B0293F0C6C8B25ULL, 0x47901751435995B0ULL, 
            0x73D42F226AE70DCDULL, 0xDA3C02DBC9B7397CULL, 0x3A5F2299037F1E47ULL, 0x8D15F1BB471A1400ULL, 
            0x7ED81DCB03923601ULL, 0xAE30E6A727D2FA40ULL, 0x10B006A3C9CB70D8ULL, 0x9444AB48C7E78E5DULL, 
            0x3BB8F0D934413503ULL, 0x3C3CF19279E3BBA5ULL, 0x5144224F6643E130ULL, 0xE8FB2F683EC8179EULL, 
            0x3249D83AAB8EA0CEULL, 0xBA0CD5061E5E192DULL, 0xCAB41952651B75D4ULL, 0x21D2AB1F4F89FDB9ULL, 
            0x1FA1E46D486698CCULL, 0xDF3DB839D62BE4E5ULL, 0xBBC17DAE1292810FULL, 0xAC06E8BB8E85B650ULL, 
            0x471A419DC4CC6E09ULL, 0xF76F085921CC5DF0ULL, 0xD0EDF7801A93E6B6ULL, 0x6D5716A21F71931EULL, 
            0x36BA3C02280F405BULL, 0x25D97D8231F9E804ULL, 0x88CC4B00518B5EECULL, 0x90D92A25357B257FULL
        },
        {
            0x067F775AD3502FEAULL, 0x5719EFD840BB239CULL, 0x741876070DBC5119ULL, 0x807762B6A451928DULL, 
            0xCC52043145E49836ULL, 0x60F628B803FAA23AULL, 0x593E0AD8DCAD1978ULL, 0x64ECA99EE3767317ULL, 
            0xE862CFA14630854AULL, 0xACE8FB059A34230EULL, 0xDA5D9E1D6AC30C51ULL, 0x4EC64A56E2B3C980ULL, 
            0xA71E62213BE6E096ULL, 0x9EC0A68A7451580FULL, 0x6A6362A566FDFF35ULL, 0x0126D92A17DDF5E7ULL, 
            0xDF48453B24B30FD0ULL, 0x849D0A9E42A221C7ULL, 0x352BC1021A760CF2ULL, 0x7525274AE22D5CA1ULL, 
            0x46C5482CC6356099ULL, 0x494FD22F273E17F1ULL, 0x12AF3611E3998507ULL, 0xDA592868ECDC83CAULL, 
            0xA3EE8AC1863C38B5ULL, 0x9B65CD314EE61EA9ULL, 0x64AF7E55C78E79B9ULL, 0x7CF733E5B5F82C1EULL, 
            0x1CB8065FBD17CB96ULL, 0xB67948B9F1D1C89DULL, 0xFD115363ECC81CB7ULL, 0x5AA351F56CA0CC99ULL
        },
        {
            0x4B9A96FE3B4C8E8DULL, 0xC1A1A193F168648FULL, 0x44090C0A9C6C549BULL, 0xD5E806D3A2388FBAULL, 
            0x4DE4F8E5361B8ABBULL, 0x2DA203C63E0CE58AULL, 0xF2EEF2D25A5A01A0ULL, 0xFBE9C2D6A549F1C1ULL, 
            0xD91992B8D8C3A3FFULL, 0x1357499805A11B99ULL, 0x0D1A4B41B366AA3DULL, 0xF2790ACBD83D8981ULL, 
            0x7983C50A0D793586ULL, 0x30EFAA7B9F1B6CE7ULL, 0x07340A903F473D59ULL, 0xBA4F4D15FE62029FULL, 
            0xA597C04079D3AB49ULL, 0xAC42641A2906CA25ULL, 0x338C6CF168ACB4AFULL, 0x2AC8620148E50144ULL, 
            0x187B4865383F61EEULL, 0x98CF45F6E392E89CULL, 0xAB209AC2414026E1ULL, 0x1118C996873F96FAULL, 
            0x1C0ADA1899A7C21CULL, 0xB4DD14500F443EC5ULL, 0xFC9CC6939C938A6FULL, 0x01C4B0580555E400ULL, 
            0x22312A0A91E2EF17ULL, 0x3482C3D9350E7391ULL, 0xDFAAFF362AF10C0BULL, 0xD16885586284FE5FULL
        },
        {
            0x0C1CD2E9BB1C0AB7ULL, 0x5DD77991D635E0E1ULL, 0x6AB8E158CAD729B5ULL, 0x2F2E90378EB609A6ULL, 
            0xDE273F6965BDDD8EULL, 0x693714226D7C3459ULL, 0x151A89566D801C66ULL, 0x1699288CC7C6A1D6ULL, 
            0x1CFC27FAC1744A44ULL, 0x104C9710A1CAA502ULL, 0xE2F2CCA6BEF40915ULL, 0xD3A06E1047043AE2ULL, 
            0xF21A8F9BF487AB5EULL, 0xDF1A678228C6711FULL, 0x1448351BF5E8228DULL, 0x71EF0D032A872969ULL, 
            0xE91D00AA86275E09ULL, 0xB43252289FD33683ULL, 0xCDDC61F82FC69AFFULL, 0x36AC66A37BCB9EF5ULL, 
            0xCE4E016A1824B355ULL, 0x11360DFAAE434F8DULL, 0x70AEFB09AA1A3546ULL, 0x73CC7C84A5C36666ULL, 
            0x839402DC1E01A73CULL, 0x642BE9F17C6DE4DCULL, 0x5CCE681C48C1E3BDULL, 0x5C6311B584A83008ULL, 
            0xDB7F8BC85A623445ULL, 0x8B7D95315FAD3993ULL, 0xDAC496F058692897ULL, 0x715F44D08875E809ULL
        },
        {
            0x491E6855F9B6FF95ULL, 0xAD987986B8E44E2CULL, 0x11EA33AAE3A8155CULL, 0x1B19D87DE4697D8CULL, 
            0x0E4ED54B49AD785CULL, 0xFACE4A73A4CBABB7ULL, 0x5D36B8ED596D4D8AULL, 0x6BA1EC271B1744E5ULL, 
            0x6E60AC32393B7AF5ULL, 0x6A716B946B053DE9ULL, 0x71352690754FE1E6ULL, 0x279883847842E9CDULL, 
            0xA888EFBB0FFF4F5DULL, 0x308C8C041B3E9696ULL, 0x0CE3D9FA443FAC17ULL, 0x0B799FE657F30F73ULL, 
            0x85DDF3B36FFBA67CULL, 0xF4AAF34CAE37905BULL, 0x8B2546BDE0EA024AULL, 0x454510A0D6637A42ULL, 
            0xA33DECB5D1AB1E1DULL, 0x0EDA803D7453777CULL, 0x47431C8982075419ULL, 0x9C03D5FB59F90B3BULL, 
            0xF2B183348E18251AULL, 0xAD347308254A8309ULL, 0x848588DDE8FC0A81ULL, 0x5C6B26BB24B9B2F6ULL, 
            0x4D4D82CE5A0110F8ULL, 0x4E1B836452EA5841ULL, 0x9C4BACCB4C331955ULL, 0x05C6275602DF76A7ULL
        },
        {
            0xF7C319420F6E434CULL, 0xD9134F8434B43455ULL, 0xE49E1581EB576A79ULL, 0x2ACA08A4AB724E0FULL, 
            0x18C332812684B707ULL, 0x6E98E395B7E4EC42ULL, 0x2B111319741987B5ULL, 0xE2D0EF2AE5EB87C9ULL, 
            0x381F06C5D6CE0227ULL, 0x94C7584C7A0130ACULL, 0x4C0004573446F43AULL, 0xE7EAB4B6EFF8A944ULL, 
            0xA9F429C7E5F8514FULL, 0xA0DFD61AF64B0BE4ULL, 0x226C17401E24607EULL, 0x0952FB331318EC51ULL, 
            0xF720C23167063331ULL, 0xB0983BC90A130123ULL, 0xCCE896F1C3D2384FULL, 0x4B285005AB8E4F4AULL, 
            0x11AD01613A2AC5DCULL, 0x70671619023CDACAULL, 0x5A98421497592D76ULL, 0x2B611C6A862F4406ULL, 
            0x1A0E2DF1A9476251ULL, 0x2643732AD0593587ULL, 0x68B3C6988F5A643BULL, 0xF666888E650BB427ULL, 
            0x64732DF79D13FDAEULL, 0x6EAAB6CB5B9D2F77ULL, 0x99F6C836FCD05076ULL, 0x02108F7202A6B8E9ULL
        }
    },
    {
        {
            0x4B29770D163CE1ADULL, 0x50E070EE1916C0CBULL, 0x0162F6C2BB2EB03AULL, 0xD212B946B04FB0C1ULL, 
            0x3B538696A47BEDDDULL, 0x8847A03859AC226DULL, 0x188AEFE90381FF6BULL, 0xFE1925A8A9CD7A0DULL, 
            0xEF387759AFC4B3EAULL, 0x2A0D3B5F8A570824ULL, 0x1985D0FE509AF41BULL, 0x68963F020F9210A1ULL, 
            0xF6888524E7A5BF9EULL, 0x1F22D0D279269D1DULL, 0xF71517B30E3E154DULL, 0x6A5FDCC32BDB286EULL, 
            0x726DFE82E0AE0245ULL, 0x55159435E202AC99ULL, 0x973696FB654FE1C6ULL, 0xCF34FE6602739689ULL, 
            0x5E0E03F43B21940CULL, 0x741AADFF5688DC5AULL, 0xDB4483135DC8D9F2ULL, 0x8BAB7B4E0F878CB9ULL, 
            0xE251D4043DC54EDAULL, 0xFE2CE25C442901E8ULL, 0xFC83CCF1509B8ED1ULL, 0x40BE8BAFEAFB5F8DULL, 
            0xFB1BD52A9D376DE8ULL, 0xA48FB75005B57BC1ULL, 0xE0BE5A7941229EC7ULL, 0xAE792FF16BA55D0FULL
        },
        {
            0x69DE38A2414B4F87ULL, 0xCC7A1E539BC401A6ULL, 0x097AFF0D76360ECCULL, 0xCD1C557F8489092AULL, 
            0x2F34512FEAB8DA7BULL, 0x1EAED723546BA03BULL, 0xBFC5B2365C69FF81ULL, 0x743B3D0F09DDD0EFULL, 
            0xC83DE347CD88212EULL, 0xC4DF2DED54792BAEULL, 0x5ADA19418C7E8263ULL, 0x571C5E1282CC02BAULL, 
            0x088CFECE1D508BB4ULL, 0x5A0285B1084BFD76ULL, 0x57029E2F5F79CA44ULL, 0xD4B58894A3BE7E5CULL, 
            0x687870571D272372ULL, 0x9A969BF295F2F91FULL, 0x9D5CA640C609006FULL, 0x20ABB290AD53E544ULL, 
            0x112A5AD999B93D96ULL, 0xD222BF672FAD25E1ULL, 0xEBC49A0687687DE6ULL, 0x98156CF842B3162CULL, 
            0xA09094D84199B2A4ULL, 0xA11F076BA35063C1ULL, 0x184C05967F11E7DDULL, 0x2447E74ADCDD6E4BULL, 
            0xC30BE066448BBA92ULL, 0x5CD0FCF2C5F5C4A4ULL, 0x6AEA907248493D49ULL, 0x64FEBE844DFC9FBAULL
        },
        {
            0xB04913767A0407AEULL, 0x563C2BDBD705F60CULL, 0x40E1A62D4B4F9981ULL, 0x3E4421EFFC1FDF7AULL, 
            0x8331F6632DB6FA79ULL, 0x74357E31896DE0ABULL, 0x40F4F063858201CFULL, 0x427377155343039FULL, 
            0x50D085B7BA40F3E9ULL, 0xE2343FA230FB74D8ULL, 0xEB999A74D1288B23ULL, 0x5B1509023627FB34ULL, 
            0x7C822B99311A2E67ULL, 0x7B25937222788289ULL, 0x5EBA4CA203BE82B0ULL, 0xBC64D7F9008686A0ULL, 
            0xCACA2B432E35E8B6ULL, 0x1B1C50EE9B582574ULL, 0xA426D28126311338ULL, 0x9453AD4D55E78E5DULL, 
            0x6F0AA83CECA0B6DBULL, 0xF4107C3052B8CB1BULL, 0x232534A02624D023ULL, 0x427B55BA032E1329ULL, 
            0x5945CAD5DF40F232ULL, 0x7690F60E1A45CE89ULL, 0xD3BBD871C2E183F4ULL, 0x5A1CE02EEC7FA7ECULL, 
            0x3CDA6B407C144BE6ULL, 0xF60549566C06F349ULL, 0x23449B6147CBAC7BULL, 0x519096E64A0F4A29ULL
        },
        {
            0x792884DEE9A80349ULL, 0xA82D923D8B314EE0ULL, 0xDE02CF0A9CDA6608ULL, 0x987983EC01D30903ULL, 
            0x2D9BDAEA00B287F4ULL, 0x4471909730331DB1ULL, 0x3F84EA3C0AD7D6C7ULL, 0xD97565D69C25C310ULL, 
            0xCA51A3916773548AULL, 0x2194A8709036A332ULL, 0x3DCAEE715E7DC631ULL, 0x4EC0B802EF5F94E3ULL, 
            0xE8C7A63F280AD7A6ULL, 0x7E2B24B0BB90323AULL, 0xFB5B78A9EC23CF11ULL, 0x81096A378197FA22ULL, 
            0xD8FC96C739B9B8A6ULL, 0x76FF93E4624923BDULL, 0x7026B35B14A6B1F4ULL, 0x7D0418DDEC2B0A9DULL, 
            0x5E98F72C2A9E5720ULL, 0x799EE2243DB7C42DULL, 0x4051699585F23264ULL, 0xFAA1455B9A3B2A96ULL, 
            0x0C8AEE0F4F276917ULL, 0xD4CDFF4009B4C870ULL, 0x34991CE6A15F3BB7ULL, 0x940CB613D7BDC8AAULL, 
            0xB1036C011D567D62ULL, 0xB01154E4C20151A1ULL, 0xD56A8C67245A21A3ULL, 0x9AC97E033B5ADCC3ULL
        },
        {
            0x54F4080161EA2376ULL, 0xBA77C6755D16062FULL, 0xB485C2A1211C6BA8ULL, 0xA8042DEAB0929E9DULL, 
            0x873AAA34EA1C70D7ULL, 0x8CCC253D512685F1ULL, 0x28B1448E5910FAB8ULL, 0x72D06EB6950C234AULL, 
            0x68267B7977832672ULL, 0x23FC437B56312D35ULL, 0xD376E0AE45B2475EULL, 0xB1BA2A345864EF6AULL, 
            0x3BE83BAB6B5D6EBAULL, 0x59F6299B4825CDCAULL, 0x953F44B154D53754ULL, 0x77ED58E8A8569A46ULL, 
            0x63490F00B40A326AULL, 0xC9A50B5065068A4BULL, 0x52396460C92EA074ULL, 0xD857312869B5E91EULL, 
            0x72ED3B88CE3BEAD7ULL, 0x7AAA8632F6566DCCULL, 0x0CE35C29EA7CBE16ULL, 0xE4FAD0E7E575CE4AULL, 
            0x247470A92764D455ULL, 0x6A3987C5FC734FCDULL, 0xD73B1D7CEEB5216FULL, 0x3BC4224F03B10E48ULL, 
            0x249D698C53B44DD0ULL, 0xB0707C3CB6F72313ULL, 0x4DC167AE39F82147ULL, 0x02C6AC6328883DCDULL
        },
        {
            0x3790839423902B3CULL, 0xA9536AD7061A97C8ULL, 0xF28341E1736DC285ULL, 0x5CF254A4DFEA085EULL, 
            0xA8A2438B93AEDC41ULL, 0x4FDFC5CC8EA8520EULL, 0x4BEE451B2684EDEFULL, 0x8F8CEAE12A6D17FFULL, 
            0x9D7E67C59CC5DEDBULL, 0xD009265399AE58A3ULL, 0xDCE4527EA3EB7EB6ULL, 0x44EF748703FEE964ULL, 
            0x75D35681CA5E191CULL, 0xDD90A0FB286D40D4ULL, 0x8DA01B40649CE8B9ULL, 0x1C0AD4810B0D5C7AULL, 
            0xF5AF452D4F1838BDULL, 0x4983D9B2C85A2B64ULL, 0x4F3567D595FC417CULL, 0x5FFF7FE50B839792ULL, 
            0x4945363793499B90ULL, 0xCED64418CB598D07ULL, 0xA93CA39BB2EB63D7ULL, 0x9EC8ABC1755985FAULL, 
            0x9D54F94245357485ULL, 0x891A9D3233626647ULL, 0x78BE4AFBB7BA81C7ULL, 0x0F5540F1F90BEED4ULL, 
            0x1A6C459C419BDD37ULL, 0x902CC6DBDA132D30ULL, 0xAB9B213B72D0D133ULL, 0xAE16A9AA8158489BULL
        }
    },
    {
        {
            0x5A89348A3967895FULL, 0x561059B60D7286DAULL, 0x863FA94BF147196DULL, 0xF52162B5B6339F7CULL, 
            0xA905A603072D2943ULL, 0x02592AD4C86A4EFEULL, 0x8226F054249E27D9ULL, 0x18E9763A33EADBE3ULL, 
            0x3563A8E3A9C4E478ULL, 0xFCCFB125726E6CB3ULL, 0x512D85BFB18BC8DBULL, 0xCA45D6BE43AE1467ULL, 
            0xDA3EDC1DD07806C6ULL, 0x1355BC7E73E20565ULL, 0xD74CA9C603EE66F4ULL, 0x63DE1CCFF2FCE2FBULL, 
            0x5A29FDCDD6553FEDULL, 0xAF62A3649773AD43ULL, 0xA37877150EAEF6BCULL, 0x3EFA212795A6AEAFULL, 
            0x8563DAE2A3FB0F03ULL, 0xBB53CE533CA84683ULL, 0x16E4A0A53100F96BULL, 0x9852FEF4F8C257E3ULL, 
            0x97AEEA8275901563ULL, 0x9C313006A4DEF940ULL, 0xAC9DB771015E4281ULL, 0x537FC2A9FB48A446ULL, 
            0xEB72BFB6C05137D6ULL, 0xEA1C6F7B03252575ULL, 0x069D6E6A8C4CD517ULL, 0x68107344DAE332BDULL
        },
        {
            0x22CF210E3ECAFE91ULL, 0xDBF598676FC8C17DULL, 0x274DF00F4D82C2FEULL, 0xE917E357B13468C7ULL, 
            0x26EB67B4D1CBA916ULL, 0xAA81F5B90A9457F7ULL, 0x7F4CB7FE4011021FULL, 0xC248140D5E64BA9BULL, 
            0x292337556468686CULL, 0x7BE07C059435E9C0ULL, 0x4C8651883CBC84E7ULL, 0xF1CF795476D2BD4CULL, 
            0xC1B56CD7A6FE8B00ULL, 0x795340797CE028E7ULL, 0x16ED261E7F4740DDULL, 0x23E2C436D155B57BULL, 
            0xD59BBA72BBB96BC5ULL, 0x726851E16B44381BULL, 0xC55E1BA67F2923A1ULL, 0x19733B93DFA3FCC6ULL, 
            0xCED2E7AE995A15A9ULL, 0x8956A06A5D3CD2E0ULL, 0xF1BE608DA8D2D125ULL, 0x83E2E2FA68385703ULL, 
            0x895AB57542FA99DFULL, 0x828441709AE4775EULL, 0xE7A9BA0B5DB04A2CULL, 0x2A1C1C25E4196872ULL, 
            0xA86AEA376263F606ULL, 0x805456976B215BA2ULL, 0x95BE515D451B9690ULL, 0xC0DD3259D11C78B8ULL
        },
        {
            0xD9179AE45CDEF4A6ULL, 0x27835D1001EEC19FULL, 0x9F588B7B9F4E5CB4ULL, 0xCE1572E60C372CF3ULL, 
            0x5B34EEAC424DE787ULL, 0xC12F0C4B0BD13494ULL, 0x33AEB1C555D0E4C0ULL, 0xBAB56F047729E422ULL, 
            0x090F6C0154C1218BULL, 0x0BB2E27AFDBE3C0DULL, 0xBFE9DE6C7183A019ULL, 0xE0DB8981AA82A450ULL, 
            0x7D78C2C2CF10324FULL, 0x3B20490F377639FBULL, 0xA8E33A1F07848238ULL, 0xE642442CCF3AEFD0ULL, 
            0xC8FEAF49518BE493ULL, 0xFC2A1D056305AF2CULL, 0xE980C1DD5782C462ULL, 0x101FE7A9FF6C0CD2ULL, 
            0xA8BF3A6845323BD6ULL, 0xCC58804B4550F593ULL, 0x30439A75D9F94042ULL, 0x7B5969D0EBB9F687ULL, 
            0xA9B18B86BF9FF56EULL, 0xCB6B884DD825B74CULL, 0x9C80736F10C05F37ULL, 0x56A99A5D2FEFE9AEULL, 
            0x373CC369DEED6371ULL, 0x84A54E1386130FB8ULL, 0xBABEF3E0619A7958ULL, 0xB758EBF34CC4CCE9ULL
        },
        {
            0xD5474CD59D96CEA2ULL, 0xB7ABBD4246ECE6DFULL, 0xEB0F9AA45623EE69ULL, 0xB96C1D959D9CE846ULL, 
            0xAFA8AAA26B92B8A1ULL, 0x73055B1FE38A6F89ULL, 0x4A2DC6980549B97CULL, 0x90CCF56218831370ULL, 
            0x7CB26BE587EA2B51ULL, 0x1EAD611C3988C1AFULL, 0xA14573FA02A6918BULL, 0x70C20EFF21164034ULL, 
            0x551831E54BED75E4ULL, 0x6817C11E24249DA2ULL, 0x68EFBD4FA1ED8B06ULL, 0xB3EC702F1F8FA51DULL, 
            0x792130B6866D1E46ULL, 0xD58631ED8B6F60C7ULL, 0x60335C75D537FE75ULL, 0x2C8EBE0F2E07108BULL, 
            0x0F6519A60CF62458ULL, 0x6249D25080F0A23DULL, 0xAA6D076442FC9C5AULL, 0xC704A7B4E984763FULL, 
            0x7DB1D4C96BE5EB2FULL, 0x0757D3E201906171ULL, 0x5B5FCE689A98360EULL, 0xD129072CB363586BULL, 
            0xE203A4296910B601ULL, 0x29081F142C3B1624ULL, 0xBCBD779D8133B139ULL, 0x2C0B0A475A446189ULL
        },
        {
            0x25808270E9A9E024ULL, 0x535759CE477877FDULL, 0x87D5EEC2DE0F2B92ULL, 0xFDF307502A39C5A4ULL, 
            0x5F081B7C2167C995ULL, 0x15EAA47FC1539A54ULL, 0x296B1E0236DF3847ULL, 0xD54987D22E525BACULL, 
            0xE5A81EFD946F1799ULL, 0x3BEBC9CFC1FCE377ULL, 0xBC4D99AC6DB8FE03ULL, 0x532C4EE9DB34CD5AULL, 
            0xF88B670B3BD11D8EULL, 0x070C3AA6F27096E3ULL, 0xA495A27C38EC60E0ULL, 0x4289066F67423BC4ULL, 
            0xD3504A4911E46BD1ULL, 0x0484E5578D1FDE75ULL, 0x04083F67A5F6A456ULL, 0x126633A9C8445464ULL, 
            0xAB5D38414906465BULL, 0x814CD22115B3B7A2ULL, 0xB48DB244BD51C3DBULL, 0xCE1E2692D8CBDF04ULL, 
            0x87FD73455FEB4993ULL, 0x5109188B0F04F20CULL, 0x4E8779745557BDFFULL, 0x4A9EDC8A39136FDAULL, 
            0xD9C8F04EB7DF4BEAULL, 0xE3494211EC06301EULL, 0xAAE010C3E1596977ULL, 0xEFD4A1541CF7A36DULL
        },
        {
            0x85C54EACBB3E074DULL, 0x12F0D15B76AA3213ULL, 0x93C234BF6223CE9AULL, 0x9BC31E8382431D93ULL, 
            0x6F6D46C09266CF7BULL, 0xD2192FDEAAD75DB2ULL, 0x85653D05A3548D9FULL, 0x07B660C0352F93ADULL, 
            0x69A6AC8D80FD7016ULL, 0x3F2028D0BB104236ULL, 0x3C3E0C6804C40FCBULL, 0x10375C10FE963188ULL, 
            0x58A39C8CC5A6C83AULL, 0xC99B26F71403D104ULL, 0xEF5042ED7EE56B50ULL, 0xD7AB067C1D251B98ULL, 
            0x84BF78D3C5FB342CULL, 0x0BF32B29B1D00F91ULL, 0x3EA55BD511084602ULL, 0xC7E4051A46DC9122ULL, 
            0x58E5A5967877FC3FULL, 0x728671D1FF6FC98BULL, 0xCF9D361D631DD221ULL, 0xB86FFC526576DFD2ULL, 
            0x6330BBD563ECD5C3ULL, 0x9D2EFB13FE07F12CULL, 0x7DBA4CE26B01D1ACULL, 0x5062C92E7B090850ULL, 
            0x5B2F6833F112ED65ULL, 0xEA141BD8CF76D561ULL, 0x520A9F4B046DF8CDULL, 0x30CC7076717F9663ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alnitak::kPhaseAConstants = {
    0x3523BE0ED6A44E35ULL,
    0xB89EBA444A00A7B2ULL,
    0x865AF36425559743ULL,
    0x3523BE0ED6A44E35ULL,
    0xB89EBA444A00A7B2ULL,
    0x865AF36425559743ULL,
    0xF6CC45E2020359FCULL,
    0xCB8F4193F2F2118AULL,
    0x0B,
    0x5C,
    0xBD,
    0x53,
    0x9B,
    0x2A,
    0x3F,
    0xE0
};

const TwistDomainSaltSet TwistExpander_Alnitak::kPhaseBSalts = {
    {
        {
            0x0D7EC6DBBDE4A341ULL, 0xE9F29516B6633426ULL, 0x5307A37FB459DC46ULL, 0x8E0460C6A821C87FULL, 
            0xF0C6BACE88391ABAULL, 0xE153ED5D3D4086E5ULL, 0x0D77FED5F4B7B293ULL, 0x4A61ACAE8A93366AULL, 
            0xA70C6BC699D16A4BULL, 0x4A03940DE22F6BA9ULL, 0x515B4FBAECF3DC39ULL, 0x9E95857D2B6B02BEULL, 
            0x59959D6A4DC909A7ULL, 0xBFC3AF32AD2511F7ULL, 0xCE15C72C45595E5BULL, 0xC6B15A72663D8D6AULL, 
            0x968C72DAF19F1F14ULL, 0xF3BDF3D3AF0D6B6BULL, 0xE3916DF45B1B733BULL, 0x0A2F72D3B831CF12ULL, 
            0x3624CB7E95A9B232ULL, 0xDEBDB2EE299D4D5CULL, 0x73E04EE0AC263FADULL, 0x04AFD5505F1E7A5CULL, 
            0x8FEB2F615415F125ULL, 0xF775006E359F3895ULL, 0x739B9AB99962738AULL, 0xC6AF43D88734D802ULL, 
            0x66C884C6C0B88E36ULL, 0x94FD34618334DE8FULL, 0x7BFB009748B5A123ULL, 0xB941A311D2741A93ULL
        },
        {
            0x7F6FFA97376E5FC8ULL, 0xB4680BA0A3E0038BULL, 0x69C54C9746759810ULL, 0xCA7C6B2243181088ULL, 
            0x0D8EB527F37BCCC7ULL, 0xBE2A04E91E902D57ULL, 0x0F71C296A4F6538AULL, 0x5A51A74E71FA2F44ULL, 
            0x6818C31481F0CF68ULL, 0xD3442FBD23CDD17CULL, 0x59137CAA63FE18A3ULL, 0xBC682D600696B65DULL, 
            0x35E627A63AF9BF21ULL, 0x68399460BC081CAFULL, 0x9562F66C24FBF192ULL, 0x7A9921AB5C0F638FULL, 
            0x9F687DFC10D78313ULL, 0xD2942BA69845889FULL, 0x23C94F89BFF1987EULL, 0x125CC4A46E82575DULL, 
            0x8C19AEE819E4D39CULL, 0x77E337EA57AFEADEULL, 0x0601487B557090DCULL, 0xDA15296A11EA0E26ULL, 
            0xC48777E0EC143904ULL, 0x4D62D6BF682A8A95ULL, 0xC89C6A2A0269CCF5ULL, 0xD8FC1253AA00DC3CULL, 
            0x54DDD91B85CBF457ULL, 0xE3921AEBF6A160FBULL, 0x4886423FAE42C309ULL, 0xE87C62B2030A7737ULL
        },
        {
            0x6056075E3414DDA3ULL, 0x2EBEF2113ACDAA02ULL, 0x37A9B2AB6BFB9DB3ULL, 0x07D9CEB4F8BAF960ULL, 
            0x5BA024BF4DC75B7BULL, 0x38EBBE55305DEB88ULL, 0x947BDEF2BAF05F9DULL, 0x680A2C44EF868C6BULL, 
            0xB991305F1FAA7CA2ULL, 0xD7C5EC585231E411ULL, 0x64516C48598AFC75ULL, 0x076932F70214ECA2ULL, 
            0xF9C529F189A97C00ULL, 0x1229D96E69D5CF26ULL, 0xEBB37EEC26718716ULL, 0xB48789B0489EE33EULL, 
            0x9C6FEAF7F4ADD7A9ULL, 0x1EB1796AD2FEA834ULL, 0xCACEA7DFD2D8CBBFULL, 0xC5ADBD5DDEFE1D00ULL, 
            0x7CA95627D22B6A8BULL, 0xA56A835975D28347ULL, 0xD53AAB5A1D6D1640ULL, 0x5AF4657DFCF426A1ULL, 
            0xC20A2EBB3C39793CULL, 0x47A4C5803BB1A95BULL, 0xE5989FF3521ABFD3ULL, 0xD53637997B19BA83ULL, 
            0x1EE5AEA9B9CA23FCULL, 0x272FA004BC383736ULL, 0x7D84158FA2A16F33ULL, 0x10F70505A3119E15ULL
        },
        {
            0xC6E8EEBEFACBC25FULL, 0x5CFCAE380FBB0819ULL, 0x4B07DF8F2087213CULL, 0x11243000E1E612BFULL, 
            0x85773EE448822819ULL, 0x457142DDBD6A12FDULL, 0xC5D718C5B9E79A39ULL, 0x61A54BEE7A7B01D7ULL, 
            0x7E7D1A27415B85F5ULL, 0xB4F8A7B52168EA4EULL, 0x7FAD7941AB5BB0E4ULL, 0x766299C11231D52DULL, 
            0xD92652F9217B5F03ULL, 0xE162492F1434574CULL, 0xA293789A819AF260ULL, 0x9F97119BF315BCACULL, 
            0xC94A4D8F6A7BFDECULL, 0x498D67079BDA5896ULL, 0xF484DE8940E69721ULL, 0xEAD397B8FE62B824ULL, 
            0x2A6A793B20BD10D9ULL, 0xD9720F7BE5D2644BULL, 0x0A0A6CF6FC6E90CCULL, 0xEC2BDAB4B87F0446ULL, 
            0xB1BCC4AB6579431EULL, 0xC3E8640604F7B422ULL, 0x1FDA24A0FED6122CULL, 0xE9C67E977E505C43ULL, 
            0x57043893D853F262ULL, 0x0A624FC121412AFCULL, 0x88737733EDD76DB9ULL, 0xD43136753FEA6158ULL
        },
        {
            0x45E9AE8F9AAA3934ULL, 0xE7A1C8182794CBE6ULL, 0xD5676D88A625407EULL, 0x2F3651BD53E36109ULL, 
            0xF67CFE1C4A4E0A20ULL, 0x24803C059717D1C4ULL, 0x8C6364A1182DF861ULL, 0x9708D95541C21107ULL, 
            0xC89E5F82D2C8A6FCULL, 0xE80E0FB7113EF74AULL, 0x9FB595B7A525E5C0ULL, 0xA8C0566E684497C1ULL, 
            0x11DF45CF9C457E8DULL, 0xA5EF4D63C8E43FEDULL, 0x6AA6F17B32331B00ULL, 0x8D13028C76D570E0ULL, 
            0xE8028BDD4C1CFE65ULL, 0xD57C5898BFEF9733ULL, 0xBCDBCB98FBDF6C91ULL, 0x05F2E9BCA3C51E03ULL, 
            0x918EC7A63BA01E2CULL, 0x00BD48E94901E638ULL, 0xA9B326B796DEB30FULL, 0x664651163283279EULL, 
            0xD9DE57BF2AF581B2ULL, 0x17AF2DDAB3BE9F0EULL, 0x3F77BFACFAA2DA6DULL, 0xB3D464165C313CE5ULL, 
            0x379EC543F1B3C2EBULL, 0xDD39240E1B98BA24ULL, 0x928FA7C95C408115ULL, 0x7F37DB62A68251D8ULL
        },
        {
            0xD3A2544DE35D9842ULL, 0xC588BB7344988380ULL, 0xE516CF645967CF48ULL, 0x4B6B01D6A3055537ULL, 
            0xE6CFAF3D8D23A2D2ULL, 0x4975A293E0FF36FDULL, 0x6814285CF890196BULL, 0x07A9FABA88499A27ULL, 
            0x333AFE41BDECB23CULL, 0x602F48F086BFA344ULL, 0x3F530070513D5312ULL, 0x1BABE1E5E4D9B3C0ULL, 
            0xF9D0540F5E488C51ULL, 0x0FE81D6A15EC11E8ULL, 0x11CF0F6544C16E1CULL, 0x2573FA2015441A02ULL, 
            0x327CF204D17878E8ULL, 0xB4142AD97E3F58C5ULL, 0x08AF16AD47750F67ULL, 0xE9327D09B3B7D7F4ULL, 
            0xBE14FDDF1E900635ULL, 0xE4DECFDEB0E5613BULL, 0xDD76B1942AC36BD5ULL, 0xAF2DED19D95E87E8ULL, 
            0x091CE27D598D055BULL, 0xF445DCC46E3C8EC4ULL, 0x938127ACF072B38AULL, 0x05AA005649CC83D4ULL, 
            0xC122868D2B2B34E8ULL, 0x587BA32C21597526ULL, 0x7CF23E951D14FD06ULL, 0x181CDFD5BE8A97FEULL
        }
    },
    {
        {
            0x65CD612E5C65B196ULL, 0x8036197EE01B3D60ULL, 0x692799FB76449E0CULL, 0x1B3D29F7695BD26FULL, 
            0x8C27BDE3111E7EE5ULL, 0x0C2A760F76D4744DULL, 0x6AB4FAFB28372DF1ULL, 0x37D6BA4CAD3BDD04ULL, 
            0x8B9D2E164576E77EULL, 0xFD8CA536FD03E259ULL, 0xE1B0198248B88AADULL, 0x17622F761045FAFBULL, 
            0x96551458C52C8777ULL, 0xF6F145F18B0BDEE0ULL, 0xFF6213FEFFD10C2BULL, 0x5A5EEEF88359E9BEULL, 
            0xBA9BE77412809573ULL, 0x8C9189E035FBCD71ULL, 0xC62F7B2895BF321FULL, 0xD4DA696242725629ULL, 
            0xF25B9926129BE882ULL, 0x821916254916D5AFULL, 0xE9F7CCC2B32C31A6ULL, 0xAA36D13E95E9F91DULL, 
            0x4A418403B44DC1D4ULL, 0xFB08E0451CF9A2DAULL, 0x6495A6D5C590B617ULL, 0xF73DBF06CA29F066ULL, 
            0x99613EB1338C0ED4ULL, 0xC1C2B3AE2E2008EBULL, 0xB90A45083E572CB8ULL, 0x17D785173030C161ULL
        },
        {
            0xFB4A556FCF8F88FFULL, 0x714BCE4E2AD03DC2ULL, 0x0B9BE40CE6B860D9ULL, 0x972D098FADA42A92ULL, 
            0xADE21525AEC6DD91ULL, 0xEA0AE24116A0E9F6ULL, 0x7EEF1C89DCA2D302ULL, 0xBCAB37FBBCCAC92FULL, 
            0xCB2AA24EBC05252CULL, 0xE838BDCD67B3DC12ULL, 0xF0F877F2C7F48F05ULL, 0x7B233ECE8CFE5AD3ULL, 
            0xDC72C7A037E11A86ULL, 0x2968231A233788C4ULL, 0x21C684C917BFA53AULL, 0xB5B24B333B55FA17ULL, 
            0x9CDE53C61461CE44ULL, 0xA959D160552D0E61ULL, 0x6B5C2913B6308988ULL, 0xB6BB70BC76AD123DULL, 
            0x2348679DF5E6E49BULL, 0x67FD324BD9BEC4BAULL, 0x376C494A1D34B4C3ULL, 0xBD1A4335305B831BULL, 
            0x35181203A6458CC3ULL, 0x0BC442C567503887ULL, 0xC1B8F1377A35DEA2ULL, 0x300404B475AF3A7BULL, 
            0x0F5F5C8AC01018F7ULL, 0xFB50C4064EEFE49AULL, 0xC197407E14B1A857ULL, 0x1A4061E8FF65EF64ULL
        },
        {
            0xB80F2CD36B037D8FULL, 0x34D6991E9F4477A4ULL, 0x8DD39081A52D3F2CULL, 0xF33340E0B08C6AF6ULL, 
            0xF873016A74A46F4BULL, 0x98B439D6A97A600CULL, 0x0CA66685E5F69E6EULL, 0x2EF84C4195A2C6F1ULL, 
            0x0D9D4BC9EF870A04ULL, 0xC8C1BA97900DD00BULL, 0x3F9EB63B7700D54CULL, 0x2D2FD8A4541DA448ULL, 
            0x9E390318666D8E5FULL, 0x14B51B544A12763AULL, 0x3A5660E66DAF7A10ULL, 0x72F361EC8CC22DB9ULL, 
            0xFA4829A4BFA7855EULL, 0x95C8D4BB68872B43ULL, 0x8C3C6B7C49DD9858ULL, 0x25684BF083070C74ULL, 
            0x9FE1327004AAB850ULL, 0xA3152B3EA0153174ULL, 0x70D248C2FE6C109BULL, 0x3086EFECD2F6CC16ULL, 
            0xE7FF933C929C80A5ULL, 0x52BAE635411E149BULL, 0xCE9620676C6379CDULL, 0xB0E342A7599A2222ULL, 
            0x67DC3BAAD695CA49ULL, 0x68C7F1D35C98D79CULL, 0x78F14A87C666D24CULL, 0xACBB0383C6C38B09ULL
        },
        {
            0x3E2B3C3EF6655740ULL, 0x904BD02EDAD739D0ULL, 0xFF0876D0246F0B8DULL, 0x804DFC78585FD3DBULL, 
            0xF7E600B3A40D5A45ULL, 0xBEAC858DC71BE3FBULL, 0xA7EC05F8C6445193ULL, 0xB857756B9DF928E7ULL, 
            0x80003D0E8FFEAE66ULL, 0x80E39B2B1ACE0620ULL, 0xA55437EDF7C25B47ULL, 0xA22C4ABCFE8E67E0ULL, 
            0xBA1D6172396B3FC2ULL, 0x8F8454DF612BA6C2ULL, 0x3A28CB57D78FC89EULL, 0x85AF55E59AEA10DDULL, 
            0x6EAC8F3AC5FF3B17ULL, 0x900CD9C9EAFB4A9AULL, 0x05638C6F32EBA2ADULL, 0xD2FF347079993CD7ULL, 
            0x0EE80799C44EE748ULL, 0xAB7C998779985A5AULL, 0xF6240ED31D77AE06ULL, 0x16BE38A3B3BC6561ULL, 
            0x602A552E29C30377ULL, 0xB7D22590AFD8A1CFULL, 0xFA470FF350688FBEULL, 0x97135236A7AA77A0ULL, 
            0x9C18307D64EA5AE4ULL, 0x1BF4E812672FAD33ULL, 0xDB60750BED06C523ULL, 0x8C27029140D4EF8AULL
        },
        {
            0x106D7C88470BE7FBULL, 0xFC874EBD8153C628ULL, 0x81323A3A1102E7D4ULL, 0xB61A950A1C469D63ULL, 
            0xDA787626B183F734ULL, 0x05C4BD296CAEB888ULL, 0x002DFFF5F7136F87ULL, 0x732EAF281A6C4C11ULL, 
            0x796658D583E97BA7ULL, 0x740ED96D60882914ULL, 0x2472D6514BB4BF77ULL, 0x8092A9208E8FA338ULL, 
            0x21C40F7120D0DD0CULL, 0x2DC967B0D845B991ULL, 0xBF66B1E81A48F3B6ULL, 0xCC1A4229B6691E32ULL, 
            0x93450068BE31A191ULL, 0xDEDDA16FA4BEBD0FULL, 0x5AEAEA51A16CFC4FULL, 0xF809A789E7DB7A54ULL, 
            0xA81DD25A7AC33788ULL, 0xC0F8D3F291A042FBULL, 0x9A35D0E0153CFFAFULL, 0x372E5731B17CCA6CULL, 
            0x2F0B91947E37C69BULL, 0x07419653CB06FC57ULL, 0x2182080D9168D6E8ULL, 0x4A0E2807E7D19F7EULL, 
            0x427CE24246326460ULL, 0x634B3406D4399533ULL, 0xF23C1D28FF8A8C66ULL, 0x7D3543E5F3630D4AULL
        },
        {
            0xC61DBAA0E99D4163ULL, 0x75A4FF97FA3424EEULL, 0xBF1BBAF059130468ULL, 0x5655DD5E9B691789ULL, 
            0xD029853A72AB7AB6ULL, 0xD17383AC4EDFABBAULL, 0xC80ACE305BE8E066ULL, 0x24ED41B167082F7CULL, 
            0xD33CF9701A765993ULL, 0x58D4A506A99396DCULL, 0x90C54F9565FBF21AULL, 0x3E7A69DA42E54E1BULL, 
            0xA1321A7C973BFD8AULL, 0x93FDB779FE77C687ULL, 0x34C39A92FACD443AULL, 0x6CAAA7C88A5F0975ULL, 
            0xF5D6A252F8D97C82ULL, 0x55F430F60A29C07BULL, 0xCD6DFD53D0107F33ULL, 0xB443DFAC5C4EE796ULL, 
            0x47766BAE71E71E3DULL, 0xA5248B49C5E7EAA4ULL, 0x1EEA1DA19CD2D212ULL, 0xFDE260A0E4AA50DAULL, 
            0x225B40BFF3836966ULL, 0x2AC9F3FB94A67FE4ULL, 0x528E6E7F97ECCE28ULL, 0xAC62EB43060374E6ULL, 
            0x8240263588C06071ULL, 0xBD10E1D0361F2D9CULL, 0x08299C27AFFBD61BULL, 0x69BAAEE0F02D3EC6ULL
        }
    },
    {
        {
            0x0B8D8DDA45D0A460ULL, 0x0C84A168D6542D98ULL, 0x129E67B06D0DF461ULL, 0xC5B4A1214EE69EC4ULL, 
            0x3436EE90B051BCB6ULL, 0x3DF4B6F67D0D764EULL, 0xFDB037A158A1F961ULL, 0x7973C57AB2AD59DFULL, 
            0xF60DB73C2DCB54CAULL, 0x94E9FF917EAB6F8FULL, 0x299E50D2B3434FD1ULL, 0x7EE8BB61F76ADE98ULL, 
            0x160638480E275338ULL, 0xC7DAA16677B02B30ULL, 0xD88683C0A0A80F93ULL, 0xDD8ACBC6418BD899ULL, 
            0xCDBD6D4FFD5C3C06ULL, 0xA6DBC00D9FAC0158ULL, 0xDE496D21ACB3180BULL, 0x0903A7EAF7E0EB31ULL, 
            0x5A66EEEB895A7F17ULL, 0x3E2F16DA6B60F371ULL, 0xDF9608A4A50BDF2CULL, 0x9C7067A8031EE770ULL, 
            0x1E84E6BB2E9CB8B7ULL, 0x5109F97D54F39153ULL, 0x4DD09BE91D04B317ULL, 0x522C4CC4E867DFC6ULL, 
            0xA7485C6D2C385CB5ULL, 0xADF9981EFEB4BAD8ULL, 0x669EED0C385C4929ULL, 0xCBEE54660DB6FDCEULL
        },
        {
            0xA8F1D1D9F37C316AULL, 0x5C51DFD361DB22E4ULL, 0x227B2CD4B9A2F024ULL, 0xEB5EF9A101746086ULL, 
            0x2DC3BC2EBBAD4B16ULL, 0x0C1399A1A709C5ADULL, 0xB9F0381D3BF9673FULL, 0xA6B7F339B29217A0ULL, 
            0xE8BCA60592EF804EULL, 0x8442E727FA00457AULL, 0xBC007341FAC57BC2ULL, 0x6D6A64E5BB477466ULL, 
            0x7AF75A8604BB30B3ULL, 0x71FB9C3E559C43DCULL, 0x5B9EDD540AED0BDBULL, 0xFC85C7C5A092F13BULL, 
            0x33795C822693DC12ULL, 0x28EB375C8996E801ULL, 0xEC516EB0CAF14E9FULL, 0x80DE041831E74BA3ULL, 
            0x992A07FAA11136DCULL, 0x5933FEB0858017F4ULL, 0x48D55A29DF52EF0DULL, 0x8F71EAD412B49269ULL, 
            0x7F5A8D72F7FC636BULL, 0x574FCD77F2729D55ULL, 0xD8E35F64788F38A3ULL, 0xBAABC4CCAD9F37D4ULL, 
            0x6AC3A511AA71ED3EULL, 0x8CD78A7F00672E1CULL, 0xCE896FEC16A84E84ULL, 0xB144056CD68ABEC3ULL
        },
        {
            0x87B4B4C76928ED73ULL, 0xBE9957AAF85D3167ULL, 0x8DD7D2D6E4237458ULL, 0x03E35637DDC8C2FEULL, 
            0xFE7D2DDF10F3E5B4ULL, 0x6185B5165C424915ULL, 0xBA45322337D73A6EULL, 0xA85142C68F69E44FULL, 
            0x833DD3CAF3F07B88ULL, 0x69CC98E262B7BD88ULL, 0x14F5DD5B91353FA5ULL, 0x97C035CE50A070A1ULL, 
            0xA09FFCFE0B0E26F0ULL, 0x73D05CCF81F1ED12ULL, 0xDEFC74E95E864877ULL, 0x5883C8C723EF366FULL, 
            0x3FD100F686500A84ULL, 0x1CD0ED0AC2F4545DULL, 0x5C711F379B2CE565ULL, 0x11F7DB906292EF88ULL, 
            0xCF7C7E6DE9BCC681ULL, 0x7118568F4295894BULL, 0xBB214D0BA7014F8AULL, 0xA78D641E5396450AULL, 
            0x14B1EEF4DC474E1CULL, 0x34764C0AEC37F392ULL, 0xDBDFDB9C6C1233CBULL, 0x8E2E7AB798ADF6DBULL, 
            0xFDAE83B40DAB5479ULL, 0x15BD914540D18A15ULL, 0x5B9F20405AB2F15EULL, 0x361BED56FD8807E9ULL
        },
        {
            0x65FC534E518EB29AULL, 0x6EC04C470308734BULL, 0xAC47F5F0251067FEULL, 0xA0EF3A0AE5035AB8ULL, 
            0x6996BAA14F120C9CULL, 0x43174EDC10ABBFE3ULL, 0xD9159A96956580E2ULL, 0xB3A2EB41C7D843BFULL, 
            0xEE834F671E615096ULL, 0x233D6DCB688BE60AULL, 0xD5EF644E68E3B70EULL, 0x4F7AA210D711EA0EULL, 
            0xD58D4BBA1DA582EAULL, 0xDA42272613CED1FAULL, 0x6E2C321D91EDF634ULL, 0x3353A7B61646597AULL, 
            0xDF3C583DA387F206ULL, 0x4A6006B1022F47C2ULL, 0x8F4761FE29B5C99BULL, 0x524B71E3E9DF1991ULL, 
            0x88FFA9E15FECF6A3ULL, 0x734E64081B1EE8B4ULL, 0x5D2D5ABA3D4538A9ULL, 0x4FA0037B47CBD7F0ULL, 
            0x6399A2298F0C3B26ULL, 0x2B074710B9E5D5C0ULL, 0xBDC44366780538ACULL, 0x90B4DF3A99717833ULL, 
            0xF4AEB82835E78D59ULL, 0x23FD9903D99FBFFBULL, 0x81FDF8B1A020E5ECULL, 0x1965ECC92C6617A0ULL
        },
        {
            0xCB252CB02290A8C4ULL, 0x6F85C7064236A059ULL, 0x5DF4F8CB301C0A8EULL, 0x68DA7B8AA758ECA1ULL, 
            0x068E8E90430A16EFULL, 0xF8AF53EC23033C25ULL, 0xC48FE29E2060628BULL, 0x5D832158E13AEB4CULL, 
            0xC1BBA227E964E2BDULL, 0xD936606032503A0CULL, 0x8C2A356ACFF9D740ULL, 0x47169A9A860D020EULL, 
            0xF9EC38C782617C4DULL, 0x7A9E3DAFA05E946EULL, 0x2BDCB4D043A9F645ULL, 0x58D43B1CA8BBB29CULL, 
            0x1CE8F42527690D40ULL, 0x6471D3897EB26B0CULL, 0xCECB30157216B5ECULL, 0x5811D914B32CB0E7ULL, 
            0x88C3146DDA8E7DAAULL, 0x09CC0DEF1E216845ULL, 0x88F335602A36053AULL, 0x6F2FAC58B5FA1D55ULL, 
            0x417B27D4A87CE23BULL, 0xC9A541CEE2B545AAULL, 0xBE5EECADB964B50DULL, 0xF84D2A35A56B47CFULL, 
            0x8D8C19F4AB354906ULL, 0xF54731C66028B95AULL, 0x60EE03F5A2945C91ULL, 0x9D3E2DA6D2F0DD36ULL
        },
        {
            0x59FE31A6F808851DULL, 0xED9CF3A18BC85BE5ULL, 0xAD7D4C9D615A6F96ULL, 0x81CFAA7B44E59592ULL, 
            0xF214F947CFF32D66ULL, 0xDBE7FFF5FB504F51ULL, 0x3321409C47A12F64ULL, 0x40C97A0542E00296ULL, 
            0x2DC642A98DEACA84ULL, 0xA27430D940C9DAF1ULL, 0x27B7B869A43774D3ULL, 0xA06B3BD4F2F51BFBULL, 
            0x9E15EAE89AB29D9CULL, 0x0533E022F203B89FULL, 0xAA289399F02DCB6AULL, 0x10C4CE53ACEE9873ULL, 
            0x2E1BFFF3FDB63F9CULL, 0x19E33659C498854CULL, 0xBC8E09ECAEFF97DCULL, 0x5977140BE6752AAAULL, 
            0xD03DE815FBAD2171ULL, 0x82F5C62CDC9819D8ULL, 0x5ADE1DD4C1A85D79ULL, 0x7F07496D7206BB7FULL, 
            0x5C471BBF87B767A2ULL, 0x71F52D732C4CF1F6ULL, 0x18E4D7F14CBFD43EULL, 0xB4C75607C53307F4ULL, 
            0xF8B486162D2B4276ULL, 0xD81436A47FB57C5CULL, 0x729DC75AD7520024ULL, 0xBF7D55DDC52CC07AULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alnitak::kPhaseBConstants = {
    0xD5AB187845005BBCULL,
    0x580E464E65AF64C3ULL,
    0x6F84601CC8D52F96ULL,
    0xD5AB187845005BBCULL,
    0x580E464E65AF64C3ULL,
    0x6F84601CC8D52F96ULL,
    0x098839ACE56D4941ULL,
    0x0AE4FFD0BD9B559AULL,
    0x55,
    0xFB,
    0xE3,
    0x86,
    0xB7,
    0xDD,
    0xBA,
    0x03
};

const TwistDomainSaltSet TwistExpander_Alnitak::kPhaseCSalts = {
    {
        {
            0x1F99A33633CC1126ULL, 0x44F94A867C0E5658ULL, 0x963643995BAF8E95ULL, 0x17504BAA40C59F81ULL, 
            0x4B5444FD6041AB77ULL, 0x1F2B333B7C09773EULL, 0xDF6D8C29B8590A6DULL, 0x8CBC5125AB953EA4ULL, 
            0x9250E03495794BEFULL, 0x930CB97FAA1097DAULL, 0x9FF67482391818E3ULL, 0xE40BED5CF325AE35ULL, 
            0xA5E44EF2849864CCULL, 0xF994281BD2B3D908ULL, 0x9045071C154F616CULL, 0x6DBC8BBB1F284934ULL, 
            0xF162FB01F3C59269ULL, 0xBC7A41E2EC8F3F0FULL, 0xF23EDC919310941BULL, 0x0176ABB6DC6C1785ULL, 
            0x6F44D8F64969B123ULL, 0x96EC66965514D04DULL, 0x5EE5D37B6EABA0F6ULL, 0x899F132F9854CFE0ULL, 
            0x41DEFFB90B8F9359ULL, 0x6FB768C743C70EF2ULL, 0xBC6C4CF1B177EE40ULL, 0x76E3D89D56DC3C52ULL, 
            0xD4591F2B43102A96ULL, 0x8C6774D66EE12027ULL, 0x5CD813F9C9A88F43ULL, 0xF3E0779F6CADBAF5ULL
        },
        {
            0x6508162D4C76C95CULL, 0x698B1CD0AA8D4B8DULL, 0xBAB6BF07559087CBULL, 0x5A73A0F13CD93D2DULL, 
            0xDC65D69F059FF9ABULL, 0xDA4BE428BAABC484ULL, 0x1A6B457FBE8E0EF2ULL, 0x433C36F2CD18D117ULL, 
            0x8E60042CC28E4E44ULL, 0xDE93FAA743E43EF8ULL, 0xDB34C56E35361D63ULL, 0x1244104560C074FBULL, 
            0x29CEF35100FC029FULL, 0x5F45A35B536B1FFCULL, 0x31613BF835D52654ULL, 0xEF8524258952F329ULL, 
            0xEAAFE7972BE3B0D3ULL, 0x05BCA54F5677D160ULL, 0x7EB7FF93A2FA6A53ULL, 0xBD1A194E980DE928ULL, 
            0xA4C22BB3E1C99769ULL, 0x5E4063028F0FE3A5ULL, 0x816E52444438007BULL, 0x564FA658C5D7521DULL, 
            0x615BF3F831A0E090ULL, 0xE7721625235A0DD9ULL, 0xCE22EA26A90F39A9ULL, 0x6BFDF89203386ABEULL, 
            0xFCF90C34BBFCCCF1ULL, 0x666B9AC07041CD03ULL, 0xF7ADC6608D0FBD7DULL, 0x5E14471FA04A8976ULL
        },
        {
            0xB0AC59AA55AA8954ULL, 0xF5228FD541DBEBC9ULL, 0x170804D498A456A2ULL, 0xB7A10E529AED0A6AULL, 
            0xCE433650401B1C66ULL, 0x073EA6C5BA1D9EDAULL, 0x4B8B1257C5F5D0DEULL, 0x291D594D9D6B5415ULL, 
            0xB2F0BA0104944F2CULL, 0x971F9C4FC294B121ULL, 0x2ECC3447837F5E2FULL, 0xF6D24F58596D44FDULL, 
            0xCCC095A8B422E551ULL, 0x4B0121912218853FULL, 0x8B8F72D729170B5EULL, 0x5BE6E1B51434D345ULL, 
            0xCF38EF7D742B0B99ULL, 0xFAB66AD8B28B0A1FULL, 0xFF5758C14091AEA0ULL, 0x4D51AF0C37A0C2B1ULL, 
            0x2D88A3BAD2DC7F96ULL, 0x7C43F3A459E26180ULL, 0x17A055C06C671B9EULL, 0xA3D3FC17F6F42ECCULL, 
            0x21D3BB5147E64BEAULL, 0x6B9D06BBAE55412AULL, 0xCBEC5F09208A41F1ULL, 0xCED2A3A5D3954D7DULL, 
            0x95630CB309AE64FEULL, 0xC0BDBEEEDB8058D2ULL, 0x0A6C99A77BFF00EFULL, 0x7AF7396EB604AF70ULL
        },
        {
            0x88F6F811E4DCB0BCULL, 0x4626AB65562637EAULL, 0x2FCAF50D1A6141D4ULL, 0x66042B4667DCDA7CULL, 
            0xD62B31CB204237ADULL, 0x3BD58300475FCE6EULL, 0x9E7D352E6093B998ULL, 0x65DC34528D8A87DEULL, 
            0x9A8D79E1FA3DFEDBULL, 0x9E92F6B65DDDA44AULL, 0xE3B973E1CAEB826AULL, 0x4E1C9DA7E158D630ULL, 
            0x5915940150D8F4C6ULL, 0xB377CE7BDDA6F301ULL, 0x5F18FDB8B898E92EULL, 0x98CF4D518CACAC20ULL, 
            0x22CE13A2260FE7AFULL, 0xB5A20985B19C710BULL, 0xB0D4D7152981792EULL, 0x346D8460D2F34D57ULL, 
            0x2CDA502A4C203D76ULL, 0xEFDC33C900A3272EULL, 0xB3132995CD154C70ULL, 0xF8B4D189C6F9C663ULL, 
            0x3F20F103ABF02FEBULL, 0x642C676D3E3E35A3ULL, 0x795C1645ECFA97A8ULL, 0x2B415707F45D0475ULL, 
            0x41290E86751E54AAULL, 0xE5F04429F4A3DDE8ULL, 0x5C361E5209A8EFCEULL, 0x2DE3716706769310ULL
        },
        {
            0x980E1C9433DB36C1ULL, 0x63CD0F7FDF4B193CULL, 0x37E36E705AF29E5EULL, 0x6AFE998BC9A465BFULL, 
            0x426F8F584C6690E7ULL, 0x86D8B429E782959AULL, 0x0AB58BE3B4083544ULL, 0x2FFDF4217CEF4B3FULL, 
            0xB9458549C2F1B793ULL, 0xD76767AABE164FBEULL, 0x68A12E2F4ECC88FFULL, 0xF11150D22251A139ULL, 
            0xEE416193C7342AA2ULL, 0x2B69AF031A4B0187ULL, 0x21880CB100A536C2ULL, 0x605CAD0F78E40671ULL, 
            0x2C3B35C88969F11FULL, 0xE9F95D4966D088C8ULL, 0xBA1C79390B08BEFBULL, 0x2018B4D5D90B5BDFULL, 
            0x465879F93A26F384ULL, 0xB2B068763F4B11EFULL, 0x49879E544797B0F3ULL, 0xDA21C4D713374DB3ULL, 
            0xC98FD2387D3DCF77ULL, 0xA45E3E3A424DFEFBULL, 0x0CAF0BCF19213F83ULL, 0x67A6C3FCBDAC045FULL, 
            0xF0D2D41C5E6523C2ULL, 0x55CEC33E05E389B4ULL, 0x224F9307090281FFULL, 0x3E48B20D10D166B7ULL
        },
        {
            0x52634F17755CFC87ULL, 0xA3261033424FE1B8ULL, 0x6F2C5F9CB0F10E2CULL, 0x2A648903C32E8783ULL, 
            0x6BA857C58CAEE687ULL, 0x8C81A2899E5283A0ULL, 0x7CF1578C346CD803ULL, 0x9E5BD15E6AD75000ULL, 
            0x59F8738EF85CB95DULL, 0x34D8EB12BEF8B220ULL, 0x3D24124B96485CA6ULL, 0x4414D859ED56685CULL, 
            0x9F4B2C2405C18A6DULL, 0x865B75FC9678D07BULL, 0x1546F351E5A942BCULL, 0x32E2AFC29CD01D44ULL, 
            0x699A841BA059047CULL, 0xA25AE70202D4F129ULL, 0xE6E29F161607B039ULL, 0xA9C0565C6F7C2168ULL, 
            0xA622A2336838A7CBULL, 0x4F855A363EC5DA05ULL, 0xC4F51CBB93276F84ULL, 0x4BA3FA9EB8053FFBULL, 
            0x1B795B6F0190C6D1ULL, 0x862E9415252BE0CBULL, 0x79DF421BDB46B9F1ULL, 0xA120999D27A310DCULL, 
            0xEDCD75771B49F696ULL, 0x4393B81E2FEE00B5ULL, 0x31A055F139340649ULL, 0x9F41FF2CE71AC0ADULL
        }
    },
    {
        {
            0x2D7C8C8B3DBC9792ULL, 0x81A9FB4967249D19ULL, 0xE4BD44A4E5BC78BCULL, 0x996857A1A9FDB191ULL, 
            0xCD491E3FBB719335ULL, 0xE07B8A340A9DD92CULL, 0x7E6A72D7E5D14207ULL, 0xD7A27703E1438DDBULL, 
            0xE4C0B07DE71C9788ULL, 0xB960E72C77BE793FULL, 0xFC7FA42E41E5640BULL, 0xE42F6F9090262D0DULL, 
            0x10A13A606A3E6A28ULL, 0x2C0C3E4746578C3CULL, 0xC818D4D95704E916ULL, 0x83019928DA8E5240ULL, 
            0xEDCB78D34C6AB7FEULL, 0x8D2C618ACE526232ULL, 0x5444A80691E64AAEULL, 0xE24EFD599D210806ULL, 
            0xE90E24B4DD2B8DFBULL, 0xA0EFE8B13C6B424DULL, 0x08535F2B314602F5ULL, 0x953EC76AC8D70777ULL, 
            0x57F0C11323676FDDULL, 0x69CD0E2DD0ACB6F0ULL, 0x837011B46C1AA022ULL, 0xF781A662D994368DULL, 
            0xEFEDE9DBD14031AAULL, 0x9E212A50059C6E99ULL, 0x457F163A7BDF00FAULL, 0xAE44907169AB8708ULL
        },
        {
            0xB99AA4F32284DA33ULL, 0x18306494E68BB55FULL, 0x5559012E07E24A54ULL, 0x8C0E8C1999AC10A2ULL, 
            0xC2C63210BDF40E66ULL, 0x34AB3E64E04D0A46ULL, 0xE865D922BD0B6857ULL, 0x6470AA80351C5B00ULL, 
            0x8F53C11815FB239EULL, 0xB4F58DED18868DC0ULL, 0x199BAB6DAC9EC827ULL, 0x1241D6EDA53D31A6ULL, 
            0x32F3B9B3DBBB9EF9ULL, 0xE14080D267D3C57DULL, 0xE3D80B046E8C8D2CULL, 0xA8953DA8A9118D22ULL, 
            0xA0EF8CA582916E8EULL, 0xB2D0526286493F0AULL, 0x5B7DFA2D4026FD16ULL, 0xA0533CD804AFE60CULL, 
            0x7626048B942C403CULL, 0x2427B6AB93E7A1A5ULL, 0x682D3270129FB963ULL, 0xE0B21818A090AF23ULL, 
            0xA958AF7B5C889B7CULL, 0xA538CDFF06124859ULL, 0x96386502A1D475BEULL, 0xA9E3FCF6C3A3AEA1ULL, 
            0x848F93864790FE8FULL, 0x816E2941D2229118ULL, 0xAD784BAA61EBDFE6ULL, 0x2A10943BA312FB7EULL
        },
        {
            0x21C9AA9F032AB2D1ULL, 0x54F382F0676150D2ULL, 0x24B03CE4F4A014C3ULL, 0x68D08E257F6224D5ULL, 
            0xCF4677FB9CB3019CULL, 0x4CBDB3C5891B92AEULL, 0x7986E00268E7D4EFULL, 0x13D22E5D82E3F5C0ULL, 
            0xAB223DB60C2B520BULL, 0x8458CA5A65D3515BULL, 0x4E384F68EEA051A4ULL, 0xA2A4807DF71FAA61ULL, 
            0x22032EFC55E12423ULL, 0xAA12AFC30A8F3E69ULL, 0xB48C5A8970B6E975ULL, 0xCCA25E50711B6ABDULL, 
            0xA6D46AFDDAECEAE1ULL, 0x5E09465EAB2FAE1FULL, 0x69FBD910188B45EFULL, 0x62EFA66C200C9D0DULL, 
            0xFC9B2651D0A25837ULL, 0x3AA193F81C290CDAULL, 0xA0F0D99A6453A288ULL, 0x7B0D361C6AD2A6C7ULL, 
            0xA280B930AAA94FBFULL, 0x6638C226AF294959ULL, 0x6A7E7AE53467CAB8ULL, 0x47D71ADF638D5134ULL, 
            0xCD141A50D0ADD7FFULL, 0xA3C3E903ECCC9366ULL, 0xFF1C164054FC64EFULL, 0x00E7B5FE5C723F8EULL
        },
        {
            0x27AC43E1DFB6A8A6ULL, 0x524407E8CDC2FFFDULL, 0x525997D8DF968DA0ULL, 0x09FB1813E2004A41ULL, 
            0xEEE3E682D6F1A4A4ULL, 0x8B87B2D58703BAF4ULL, 0xACB3ECCF34564629ULL, 0xD91DE40E0DDE0AC0ULL, 
            0xE10BA4C6B36F2DC3ULL, 0x4588096B855D4AAAULL, 0x0BA1530533658903ULL, 0x7667CEE562BF5EFBULL, 
            0xF8D5D00C87F6633FULL, 0x8E8ED7F2ABE324F8ULL, 0x529A0764E3A4D320ULL, 0x421CACE5012F94C4ULL, 
            0x0D9B494ED3A45C3EULL, 0xB85F107D7CEBDFBFULL, 0x1F80D19503B6ABE1ULL, 0xF06FA49638B2DE86ULL, 
            0xB30B79973E63C68FULL, 0x3488CD7DB661B286ULL, 0xB54430A09F4029ABULL, 0xAF3086CD1954F6D8ULL, 
            0x3512B36C54C987FDULL, 0x86F0F013188F6CD9ULL, 0x2D3453B485F8C463ULL, 0xE32381CB455F654AULL, 
            0x6C3AE41C4A540D01ULL, 0xBABDE6E928F22CF7ULL, 0x906985C486D0E450ULL, 0x2848E974C7C56A04ULL
        },
        {
            0x2666ED9B8690F907ULL, 0xB7CE42F15D0DB865ULL, 0xB8007D50DAC5DC97ULL, 0x5DECE351BC16F82FULL, 
            0x64F6364A40A69778ULL, 0x5A3F5DF545CC9E05ULL, 0x3573A17BB330586CULL, 0xAE8B42CC87F31FEEULL, 
            0x90676F56826FF6B0ULL, 0xDD7FD1B10169336FULL, 0xA8EF64DB7FD7D9A1ULL, 0x42B5E0E1F65C60C8ULL, 
            0x353EEAC349BAA77DULL, 0xC388A870E0F55EDAULL, 0xEF930DD37D6E23FEULL, 0xB6BFF53269EA4BACULL, 
            0x7ED6CAA12EEEEE80ULL, 0xF46E56D9B92C3DFEULL, 0xBA1FA08DFA6CB05AULL, 0x652A31D95D85ED79ULL, 
            0x027274F9D4B41385ULL, 0xFBDFE308F5AE14DBULL, 0x5D0F0DC034FFE394ULL, 0xDD3B199F660E5336ULL, 
            0xF14337A977E1F2D6ULL, 0x4D7AB35ED7D75163ULL, 0x162CBC1E7E2C0499ULL, 0xD94AEBD036B5784CULL, 
            0xAF878D3235871055ULL, 0xA20EDD8BCCE9710FULL, 0xC41E8FC102EFA852ULL, 0xAF1B2CF9F8732932ULL
        },
        {
            0xE680BC19A1586E0AULL, 0x5D9FE7A2582151D8ULL, 0xF62B3CAD7115A902ULL, 0x3E35751452AFC317ULL, 
            0xC9CEFF85904E60F0ULL, 0x8FB5F9317C169813ULL, 0x5053FD9CBFEFCA1EULL, 0xB0C11FD832B49CDCULL, 
            0x46BA6B31ABF6E805ULL, 0x5EB8EB6319E483EFULL, 0x5592C983D4269F3FULL, 0x1BDBE547039306EEULL, 
            0x39ABA6AEA5521998ULL, 0x15CA5ADD1761E0A0ULL, 0x10962CCA28C69F8AULL, 0xBB2F4F70DBE4B188ULL, 
            0xA75B72BA98015F5CULL, 0xEBBAAD1E3C62FC8CULL, 0x0A382305DDC1BB98ULL, 0x95FFCD3035CF6B91ULL, 
            0xD0C8B383F728C278ULL, 0x0914849A90F60A59ULL, 0xBF59EEB947EC348DULL, 0x9661F0ED923204FCULL, 
            0x9914CE0EADA96822ULL, 0xCD7AC7051CA6D12AULL, 0x6C6AA8A0FA4BD8F9ULL, 0x362015780F04F446ULL, 
            0x4BBA0513E6AD064AULL, 0x8E6DDC366FEBC89FULL, 0xCB46A5CBE6201B86ULL, 0x74401591E7F286E6ULL
        }
    },
    {
        {
            0xBCECDCABE606DEC4ULL, 0xA858B8CA66EE347AULL, 0x1E1ACB523D48EFBBULL, 0x16B306873B96BA3BULL, 
            0x9F0D63253429D86AULL, 0xE487671B50C0CA20ULL, 0x49E0A9798C22308CULL, 0xE2EBFBAA7B53FD6EULL, 
            0xFEF920FE7D6AE19DULL, 0x5F0763CD938173C3ULL, 0x0427C324CDFF7F03ULL, 0xD04D7542D0815617ULL, 
            0x975C5A1A0DFA3DB5ULL, 0x584A084A632AAEF7ULL, 0x8A9FCD57A0CE1136ULL, 0x142D13D7C4B6C076ULL, 
            0x86C9CF2D31D02C1FULL, 0xB05583BB111A27ACULL, 0xB15135C821C9CE29ULL, 0xE9D8C8E4D2CF17F7ULL, 
            0xDBEA518B9ED42C67ULL, 0xD579C71242854191ULL, 0x92E626C0C409BBF3ULL, 0x04254B437795218AULL, 
            0x3853B49CFF9205F3ULL, 0x24629F28BA6C0491ULL, 0xE47A3032F31B12ACULL, 0x26D7CBD06491AC3BULL, 
            0xDC99975BB65B153AULL, 0x6D3E0BBED0EA7C99ULL, 0xB25A9B861FA56F0DULL, 0xD52F67508E1F5310ULL
        },
        {
            0x31F4DA07755D5FA4ULL, 0x76E1A437B5BE584DULL, 0xD961DA64CC4FCC03ULL, 0x5BA69775BA5A3EF6ULL, 
            0x349C6E6983C89951ULL, 0x90F0EB2AABF19D93ULL, 0x4445252148C809D5ULL, 0xB924570C554C6A6AULL, 
            0xF98456B4B4F91329ULL, 0xC2EFA98ABC54B689ULL, 0x6B41B5C883118859ULL, 0x8394FE814E09CF30ULL, 
            0x33EB6D19EBAC4B9DULL, 0x7B8D0E9DA09ACD95ULL, 0xC67060D843C2A160ULL, 0x3D1DAC76DB212938ULL, 
            0x938FBA2F8EA21E6BULL, 0x34D66D6D2A8C1B02ULL, 0xCB04CA22FF2BA824ULL, 0xC775F37E8C3E7BD8ULL, 
            0xCD83301744C54A23ULL, 0xC82EF82D14A6E73CULL, 0x6CCA51A29F6750E1ULL, 0x00C01FEB1A0C2FDCULL, 
            0x9538E58BBC9B103BULL, 0xBFF2FBA2E00183BCULL, 0x423CB60E6250A51DULL, 0xB1D10A05FCB08E9FULL, 
            0x5455ABB473E098A2ULL, 0x9D6059B075A3F038ULL, 0x56AA5C20A5B97685ULL, 0x76156E6E45108285ULL
        },
        {
            0xF3F267B5E5B9CDE3ULL, 0x88CEC7B46644A2BFULL, 0x3DAB519CFCC573ACULL, 0xBCA02D2BC1B59B2AULL, 
            0xCFB6E51A02B11B4CULL, 0xDCAA993923E0D6E4ULL, 0xFA653503ED4C5723ULL, 0x41F7FECD50FC985CULL, 
            0x835635CAE5BEECEDULL, 0xBB048178FEA8B5F6ULL, 0x9A1DCEF374DD31B4ULL, 0xDE5B37A692B321A5ULL, 
            0xEA042EB7F008FC5DULL, 0x08953B5640E173D8ULL, 0x32A707805DCA75E3ULL, 0x5E37DF294AB3C5DFULL, 
            0x32E5A9859D640036ULL, 0x2E6CB6F49EE4A6ACULL, 0x0B2D7F6A41EE7DDEULL, 0x58D5D79477B07720ULL, 
            0xB63BF9B2A598AF74ULL, 0x601E4EC47DA0C5FDULL, 0x6CCA590B5C7F77A7ULL, 0x32C0BF8660F67852ULL, 
            0x4BB66A15A00875B7ULL, 0x2C7EBEB55F1AA623ULL, 0xAD971A4A7A1B9111ULL, 0x7EDC3EBB29C473B4ULL, 
            0x8CB45508358A18FCULL, 0xBE3D1BE95147F561ULL, 0x72688E9662C7D8EFULL, 0x4E1FA3B265BCB8FAULL
        },
        {
            0x019DAE451BCDD202ULL, 0x74A9FDDC54B5487CULL, 0xBA5C18C3385B6EE8ULL, 0x7926471CF946473CULL, 
            0xD7CD622C653C6654ULL, 0xB289ABE2BF0E15DFULL, 0x0FAF399F15F653F8ULL, 0x91903193FBC71A7AULL, 
            0x51113882D756F5BDULL, 0x40D833476FC6611AULL, 0x4082C738AE1FCC3FULL, 0xEF6CD2AA802EA4AEULL, 
            0x70D005B92389F10AULL, 0x53E028A70390E9E0ULL, 0x47BDD557799AEEE5ULL, 0xEBAAFA6AABB510B5ULL, 
            0xD3E4ED878E4E9726ULL, 0xD709F638CAF22085ULL, 0x37B34CBDA289B310ULL, 0xE3A127248DB69111ULL, 
            0x1F9C912EF5A3108AULL, 0xC81B7745211D3B61ULL, 0x71E8DDB86E55F3F1ULL, 0x99C934E72666DBE6ULL, 
            0x8D37D5EA4EBBA1F8ULL, 0x62E141FD23FD8CACULL, 0x24405E391D70859AULL, 0x492A8FE93712CD90ULL, 
            0x9495FFCE38E2FE0CULL, 0x8677FB7F0AF953FBULL, 0x90F8010E93A7F0C8ULL, 0x7E247DEF78275F5AULL
        },
        {
            0xED884CD733697608ULL, 0x204197508293011DULL, 0x746794DB891A0C22ULL, 0x8BD979CF122C3D4FULL, 
            0x7BAB4887FAB10D17ULL, 0x3EF5E12CB936E979ULL, 0x3B0F4A216E9E6653ULL, 0x87486A41A5BD964DULL, 
            0x20F39AE026CD0FF5ULL, 0x9DFA1FFA7BC33EAFULL, 0xE654B520604BAE1EULL, 0x2FE5F8471818C884ULL, 
            0xB7AE209D7400D307ULL, 0xF9F194F12DB24A23ULL, 0x1BC05055A5011D30ULL, 0xB8BB2F38058B317AULL, 
            0xE07A3DE68387CCA7ULL, 0x23EFA6DF444DA60BULL, 0x053C48726E7E0C40ULL, 0x1990DE772F44807DULL, 
            0x5072213B7E6D7FB0ULL, 0xEA0213A46F10ABEEULL, 0xE5D8152970E379C2ULL, 0xE317732BD40DA151ULL, 
            0xBEC0236064F069A5ULL, 0xF2C2D9D8DD50E7AFULL, 0xDBC142B9075A593CULL, 0x3ED34D4A66AA8643ULL, 
            0x0E822FF4EB34B9B2ULL, 0x12753FF3DFF911F8ULL, 0x8B83C12B60838EE0ULL, 0x64BA1B60FBC79F6BULL
        },
        {
            0x01DE76B83A4BFC72ULL, 0xFD20D3A1479802D4ULL, 0x3E0FB233131856FFULL, 0x13E136A2DABBAA80ULL, 
            0xC3E8E1D25637B89DULL, 0x6E625943F46CFC8DULL, 0x060D3FF02B6E19C6ULL, 0x37B1327209871588ULL, 
            0x8BE9DC55FF2654A3ULL, 0xC757CCAE6DFFC1EBULL, 0xC0D48D4881945D29ULL, 0x493DB9B7084C18FBULL, 
            0x05B9E13B1FF2239CULL, 0x6FFDFC6D6B57244AULL, 0x8B5E0EA67DA4702AULL, 0x508B1AF67E6845E3ULL, 
            0xF11C722BF0B4A101ULL, 0x5F92142CA874E1CBULL, 0x45C9034D7593BD22ULL, 0xE6696C37C8AEABF3ULL, 
            0x1FC038C59A8522B3ULL, 0xCC1732F92FF4C012ULL, 0x10CABAAC5E6D9F67ULL, 0x37F19B66EAE0FE37ULL, 
            0xDA48A73493546AA9ULL, 0x4222565301681821ULL, 0x549459EC03A48F21ULL, 0xFA48ED22E8F16ADAULL, 
            0x87C6D232984E8A30ULL, 0x266EE2FFC6526D8FULL, 0x6A727CB1B7B93AD9ULL, 0x419EF248A5EB05B1ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alnitak::kPhaseCConstants = {
    0x8348087E6D79BD52ULL,
    0x179523D8AB0B1B2DULL,
    0x73CA509B96D63D7EULL,
    0x8348087E6D79BD52ULL,
    0x179523D8AB0B1B2DULL,
    0x73CA509B96D63D7EULL,
    0x01AA15A674D936F5ULL,
    0x359052ED83C2CE79ULL,
    0x07,
    0x2B,
    0x33,
    0xCB,
    0x12,
    0x59,
    0xDD,
    0xDC
};

const TwistDomainSaltSet TwistExpander_Alnitak::kPhaseDSalts = {
    {
        {
            0xBBEB7AE6DDAAC3B7ULL, 0x85EBB95EA3B38098ULL, 0x6DD24E6A68DA8BAAULL, 0x943AB686B18C86E1ULL, 
            0x9C1F2DE4DC961254ULL, 0x9F9F94266E753746ULL, 0x26E1443D2D4FABBFULL, 0x9A7DFC5DA9AC8687ULL, 
            0x195B9B4C267F905CULL, 0x62EC065CBA1E2986ULL, 0x579FA5F33843AB4EULL, 0x50AE5D968F7D0571ULL, 
            0x58FEE34660DA58B6ULL, 0xDDF98CB1D3A1AE44ULL, 0xB73BF1AE513680B6ULL, 0x888CD1BE5B29678EULL, 
            0xD38B243806BAD0A7ULL, 0xB8CB5ECE27D19A0AULL, 0x8B7B8D7BCE36A4C5ULL, 0x5CA4A6E3156BEC31ULL, 
            0x99F87342DA060E22ULL, 0xAAF3F76DDEF5C8E3ULL, 0x7410751422BB94DEULL, 0x35F17AFD7E1077E1ULL, 
            0x9DB32D6D4142BFF1ULL, 0xA6063C7B2D1AB9AFULL, 0x63D5F2E73FD03AB7ULL, 0xF124351A265E89CAULL, 
            0x4DFF2183985D5943ULL, 0x5DB6F616D91BFBCCULL, 0x6E683C32417AB61BULL, 0x4BBCCF5D77A038C3ULL
        },
        {
            0xFF72E37C77F6216FULL, 0x6910717F28E49AD4ULL, 0x6F7DC931A25670D8ULL, 0xEF28B05136062DC9ULL, 
            0xF4AF3C91AFA0611EULL, 0x8BBAFCCAA9F1D58FULL, 0x1023BB58EC69CE3EULL, 0xC3CAFC62A4F94134ULL, 
            0x96042C7DAE7ACDBBULL, 0xF03FC213A46B35EDULL, 0xCF4EE7D46F6CBAF3ULL, 0x587214E985C1B364ULL, 
            0x5E5CDCB127B9F978ULL, 0x5D8982126E898962ULL, 0xDC6FBA6F6ECD1DBCULL, 0xCE34AF417F8B6438ULL, 
            0xAC67E8908CD53200ULL, 0x893EA7C80614F8D8ULL, 0x9FC3D404CD8DD34DULL, 0x32E45F2C97D18459ULL, 
            0xD928D42731E6913CULL, 0x9B612F6D4EEEC609ULL, 0x5ACF0304D3166277ULL, 0x35D30B08C1FC96D1ULL, 
            0x3482AF10293069BAULL, 0xBB6B6C1459F486E3ULL, 0xF46FC79BC7285FC5ULL, 0x4450529940EBFADCULL, 
            0xEE5E2E834E750B78ULL, 0x1C128849EB39DAE6ULL, 0xF163C9FDE432E592ULL, 0x25B471D7A0C9E6FFULL
        },
        {
            0x8128C73208113D70ULL, 0x93858536D31E3BC9ULL, 0x8B4A75F61CE74B78ULL, 0x0BE922448666EB15ULL, 
            0xE5A6C1B38A2D4048ULL, 0xADA94577D8CC6B00ULL, 0x09F5D90B8ADB41CEULL, 0xF058888D0DD4F422ULL, 
            0x88A9466B45C524ECULL, 0x97F9652A03F1722BULL, 0xA73213726046CF1BULL, 0x7545751843A02686ULL, 
            0x2AF10324EBEF8DF0ULL, 0x3A4921C3158F3FC4ULL, 0x0003246F3BE52ABFULL, 0x8C5CF640F535AC07ULL, 
            0x468B4C0ABAAC8511ULL, 0xB0D351B44C9B2CDEULL, 0xE4D400B0D98AEC1AULL, 0x7443D376B638A6C4ULL, 
            0x09AFF28D0FE0DD04ULL, 0xCDB3682EADE083D9ULL, 0x59E82CC8B7775062ULL, 0x1F129D56CFF511A1ULL, 
            0x0E16B8DAD2CCCADBULL, 0xD578200BC611D458ULL, 0xCD47E6144BD4A6CEULL, 0x06295CDEBEEE270DULL, 
            0x97359DE7F4D4517CULL, 0x869455148EDF87ABULL, 0xF631FA9BD4CCAE59ULL, 0xF9F2713AE0F37C9EULL
        },
        {
            0xAC44EFFEE32254F3ULL, 0x4CB95F686A4FB3EDULL, 0x727CBD3F48486080ULL, 0xF9E6CC253A79846AULL, 
            0x38EE4A594BAB30D2ULL, 0x3F0EE0F541AA121EULL, 0x40A8DF56C8A55B13ULL, 0x7CC24477960AD262ULL, 
            0x810379326DA1D9D4ULL, 0xB3C5627AA1860B18ULL, 0x2A7D6685FCDBD4AEULL, 0x47950F29E02A54DCULL, 
            0xA1A7603165A4C32FULL, 0x58FB929B253573B2ULL, 0xE1D675C691C49EBCULL, 0x0F836CAA7270D98AULL, 
            0x4628B119B4F5D482ULL, 0x7FC476BF0DAF916EULL, 0xB4021F151BA6DCE7ULL, 0xA20059B8F8F760E1ULL, 
            0xE649BA913759238FULL, 0xB098BB12E2E81ADAULL, 0x417A720E7290DB76ULL, 0x5DA87A5A444DD96FULL, 
            0xEB86CE0802AE1F51ULL, 0xACA162B506D70C0BULL, 0x45D4760EFBEE30ACULL, 0xE143141DF97D70C5ULL, 
            0xE6CB2C86F64BB430ULL, 0x918F7F3BF2CD1838ULL, 0x3C65380EC67A1273ULL, 0xFF7B7A98BD4F0926ULL
        },
        {
            0x10F06E240D54C2A2ULL, 0x724079A63E9EF586ULL, 0xEF1F578094F92FAFULL, 0x54FD230DB585945BULL, 
            0xF205143E379B728CULL, 0xB8F949066E8E5242ULL, 0x9F9BCFF34A360891ULL, 0xB48A017A3FC3B69DULL, 
            0x7BFECCFA2242634FULL, 0xE605AD2D0E71F058ULL, 0xD97C3B8503D33CBEULL, 0xD125D855FBCC207BULL, 
            0xA65165FA3BE1BF47ULL, 0xCB7DBCB1F5800316ULL, 0xEA6212D7C4C7D9B9ULL, 0x74A3E7C4B8C5EC9FULL, 
            0x52FD8BD9339DB31EULL, 0xBF9EC84B881B21F5ULL, 0x5204B73C31DD1AA0ULL, 0xA32912374A1D8667ULL, 
            0xE7CFF6CD11068A6DULL, 0xFEB4ED1465833E62ULL, 0x35A46AB168EB37A3ULL, 0x39536E04609240BFULL, 
            0xC80C60528EAFF7FAULL, 0x2C8B72019B21DBC2ULL, 0xBB5846195ED2A658ULL, 0x8E05427B25E4768AULL, 
            0x352E4AD90C4D9037ULL, 0x67B0A51D16424D3BULL, 0x7F23B4F5DA2E6FA0ULL, 0xB4E8CA58E33A66D4ULL
        },
        {
            0xE30759DDC0B8447EULL, 0x83ABDCB2FAD6111BULL, 0x5A070BEBA6BA84ABULL, 0xAF2169874069A5CBULL, 
            0x2E68EFA93FDB5775ULL, 0xC2A32A1AA4565891ULL, 0xBEB1551458F3D964ULL, 0x69A13073EF16A52EULL, 
            0xDD33AC41EB9F2513ULL, 0x1D5BE09E393BD676ULL, 0xCFEC151081959CC7ULL, 0x76AB0B14875A1367ULL, 
            0x62CE5D8B8093FEC6ULL, 0xA82BABFEB94958ECULL, 0xC60D86B658EEEE14ULL, 0xC19C8E7B3EFBCB8BULL, 
            0xFBBA84A632FA078AULL, 0xEE61FF500DF70DF6ULL, 0x60A13C45E2D76A9EULL, 0x0B4B7CCAF9588EAEULL, 
            0xA467488B89A1F612ULL, 0xE49C198B8C4397BFULL, 0x7E10BAF60182F738ULL, 0x971EC6C770E5A58AULL, 
            0xE5E9B58EAD976398ULL, 0x519CC9C368D27C5AULL, 0x3CB90FC9E635345BULL, 0x4A8EA33FA6D5B133ULL, 
            0xB51FBDE09E1A50B0ULL, 0x103C7D77DB064787ULL, 0x0DDBDCD0CA7AABDBULL, 0x6C65291854613DF1ULL
        }
    },
    {
        {
            0xE0FA6E4E0AC2F842ULL, 0x1D7EED6B19D83504ULL, 0xD3D3F34720705F67ULL, 0x87ED8A9A4E96B515ULL, 
            0x67F576776DBCCE1BULL, 0x203510F41ACB7107ULL, 0x65C225A72260C7A7ULL, 0x73C0B6BE55FCC516ULL, 
            0xABAF9321D2262156ULL, 0x62EBF32BFEAA6970ULL, 0x1EE95252750F9328ULL, 0xC698913628F0837FULL, 
            0x105530077816901DULL, 0x5D328422271F43E3ULL, 0x833C50A72A46419AULL, 0xDE1F5EEA96D39CF8ULL, 
            0xE5B4CECF1C7BBA27ULL, 0xBBE93741766E026BULL, 0xC8B345479FD2B120ULL, 0x6F6CE3018BECC62BULL, 
            0x2009B9295E7FC408ULL, 0x3F705E48E7C94488ULL, 0x48AD844F29161132ULL, 0xD91405865C71BBDFULL, 
            0x8196EE3DCD92421FULL, 0x7B269E4122456E6DULL, 0xB1400DACB5708B10ULL, 0x6FA8DFA70263526EULL, 
            0x34F2D767D922829BULL, 0x9409EA3F59D00AAAULL, 0x21D7379CBC362207ULL, 0xCC182A7A8BE62F4BULL
        },
        {
            0x78ED69C77141E757ULL, 0x5DCFB7095334D55FULL, 0x024DBAC7F2305148ULL, 0x53E668EA3FFA1633ULL, 
            0xD5CE96A9B9E7D005ULL, 0x6DBE3B383E01BD55ULL, 0xDB11FBA7F842542DULL, 0xE7F986C6A032EC58ULL, 
            0x4023825C1E4E096EULL, 0x49A2286CD71DA3F3ULL, 0x3B0F76DBB16970BCULL, 0x4DEF8CD99EF45521ULL, 
            0x89ADCA7788066AB1ULL, 0x22D9172AFFA0B3B1ULL, 0x84383D1216DDAA60ULL, 0x74E08F4DABC2D361ULL, 
            0xBCA95417741F23B8ULL, 0x12AE6106B931627CULL, 0x538C3786410AAA2AULL, 0x58A31619FBEAC86EULL, 
            0x5A12C5108E8B16CFULL, 0xDE34B4D06ED51EF6ULL, 0xE1049464376192C3ULL, 0x5A9EE1D0980AD654ULL, 
            0x1610CBE71BD769CEULL, 0x693FD2C35601CC2CULL, 0xC5ABD8C589BD340CULL, 0xC7C5B9CA7DF524F1ULL, 
            0x3BEF06C536F2D774ULL, 0xE321118A00E8F87EULL, 0x47148536899CF915ULL, 0xBC5996EED34FA07CULL
        },
        {
            0xB0022B966E5882F6ULL, 0x96C4472E7B0FC7EEULL, 0x608793E66AE541E4ULL, 0x90F1C03DF46E784EULL, 
            0x111124A37510026EULL, 0x4ADFA0E65AF74B97ULL, 0x0FB5C7BB5BEDD8B1ULL, 0x00EB60E639002D81ULL, 
            0x2A5EF78406F055B0ULL, 0x85BD58C49D5BAAB2ULL, 0x28B2358F7C800984ULL, 0x1DC6A8C71BAF2A82ULL, 
            0x76F19385C0B88C8EULL, 0x068B417A44297F59ULL, 0xE5AB3DBFE6F924C4ULL, 0xC4E07CBD2A6C1904ULL, 
            0x84C6015932D67501ULL, 0x67268F1746AE3617ULL, 0x10D793FD8C4FF014ULL, 0x8A700B011A2DD750ULL, 
            0xC8CF1EAEBF05F485ULL, 0xB35E322AA11FFE91ULL, 0xB03F7C802AF21D55ULL, 0x0C852D7CE24AB530ULL, 
            0xDCDF308B9865869FULL, 0x7F0D61D66AE45B54ULL, 0x64827CF9BA86BE2AULL, 0xF9C02AAF6614F5A9ULL, 
            0x4D37296699BFEC92ULL, 0xBE892EF94F79E1CCULL, 0xB4115F54B334FCCBULL, 0x41BC734418FD83D7ULL
        },
        {
            0xAD1F387A9BC8709BULL, 0xFDE71C3F3D786A4DULL, 0x324A3C23BC8B2392ULL, 0x545EF0B9370879A7ULL, 
            0x99422E58B7C751DFULL, 0x48459846115F54E9ULL, 0xFFD0B57B36FA7634ULL, 0x149C816305BD41D3ULL, 
            0xA2A7EF88DF45E794ULL, 0x27C6E433F67F1DB1ULL, 0x0CA84C1448479764ULL, 0x7881E5893AB6BD13ULL, 
            0xFE5854024B286623ULL, 0xE88EE1B241972530ULL, 0x05D09A55118487ACULL, 0x20534C9C79776A6EULL, 
            0x258B9C424C222983ULL, 0xDAF6E49C40F71E0BULL, 0x20BEB8E16C05098CULL, 0x4DDBE14D1545B817ULL, 
            0xF239CEC53B70674FULL, 0xD116588E5BE4CBB5ULL, 0x9092B7699E822514ULL, 0x69C9DFA47F98649BULL, 
            0x65FA3BBA158787C8ULL, 0xE4462694601A9F4DULL, 0x8B82D3C3713EAD58ULL, 0xCA19920A141FA4E3ULL, 
            0xB4406AEA7AB4DF5FULL, 0xF4996D38A37C2F3AULL, 0xF9F2D89C2E66464AULL, 0x8EABD4D96327E0BAULL
        },
        {
            0xC3508C8E9B3D695AULL, 0x874E9B1B82D098DFULL, 0x43D502D4C5BEEF05ULL, 0x5699905D8F80C7E8ULL, 
            0xBCE60ABBA73CB7D3ULL, 0x31FF3A8F7FD70497ULL, 0x731CB3CFCE5C8CEAULL, 0xFB6B4DAFC94C7AE8ULL, 
            0xE681F56345A31DC0ULL, 0x304E66009714E949ULL, 0x5384D73FBBBA7CA6ULL, 0x0F05356744122A5DULL, 
            0xE859B67EF081A51DULL, 0xAC9E0B6906293111ULL, 0xAD3A74151CC1E680ULL, 0xFCF9278DAB1D36DBULL, 
            0x5C9B6FD5912B50B8ULL, 0xD2EA4AC724F5356BULL, 0xB670D4B1204A7674ULL, 0x19B699DFBFAF529EULL, 
            0x72D71CA6B4156AE4ULL, 0xE9945968134F91B5ULL, 0x4715CB5FA03C52E6ULL, 0x009EC655204CA1C6ULL, 
            0xA8F6FF804261CA0EULL, 0x3D1BD8F58A4B4856ULL, 0x73CA10BE0A2BE705ULL, 0xE971957979259477ULL, 
            0x70F9590841B4D4D1ULL, 0x08854991C8CE8DFCULL, 0x612A7BCF408C5119ULL, 0x7550A1AB9F16CA38ULL
        },
        {
            0xF916D6369E792EE7ULL, 0x4EC72F782E960C1BULL, 0xCA5387C350FE8BD9ULL, 0x2EA1E5DF485A6461ULL, 
            0xAD929EA67C2F6B55ULL, 0xE81E20CEBAE14362ULL, 0x4B522CF86615D5F5ULL, 0xB91F0234697BD707ULL, 
            0x7853E45C4B6A7C34ULL, 0x493ADBEDD14EB0E8ULL, 0xD8323F5062915C14ULL, 0xC986D94A208EBA94ULL, 
            0x42F8A9C74420BA20ULL, 0xB8D82264425EE16BULL, 0x005A138F27D4B3F9ULL, 0xB58F440C519F64CCULL, 
            0x01912AD4BB9770FAULL, 0x3AF7E4B8EA0DDA28ULL, 0x8D57D2F991EBDE37ULL, 0x828F20AFD874CC8AULL, 
            0xDC85D46707B04147ULL, 0xBDA8B0EC955C4AC2ULL, 0x8CB42FB6302D566EULL, 0x88405DBB3EA84097ULL, 
            0xD4803BA405308D7BULL, 0x66DFD59EA745CB09ULL, 0x42846B50CFA2BE93ULL, 0x6742EDA0F270BF21ULL, 
            0x67F11010940DEE26ULL, 0xAB146740E303A308ULL, 0x37F0074F49CD9ABCULL, 0xA4690DD8DBF92B7EULL
        }
    },
    {
        {
            0x361CBD543BA08247ULL, 0x75F7ECA152146DD4ULL, 0xE4C200ABB7B487BEULL, 0xD75C4DB24719AEC2ULL, 
            0xF6B144604289A66AULL, 0x63A2D5F9ACAAEDBAULL, 0x9A145773288564BFULL, 0x406927B7DFB682CDULL, 
            0x3EB480D430298B5DULL, 0x559840D27729B129ULL, 0x6792BA07AF58C4E8ULL, 0xF7E78441F7ACA1A8ULL, 
            0x722ECA254024F0FCULL, 0xE5A9307CCC78E67FULL, 0xB7F2FDE04EC50DB8ULL, 0x5B768A585B285DB6ULL, 
            0x87FFAC1820335FA6ULL, 0x59E6AEF31C58E658ULL, 0xA47CD18B9E8CE03CULL, 0x4BC15AC1E8270CAEULL, 
            0x494E4E3B76B27C4CULL, 0xB68ABBD60B79FF11ULL, 0x16A8E1720B097182ULL, 0x171FD486D5F17084ULL, 
            0x2A7ABBD8CB3F1B20ULL, 0xFF87E2CA561048FDULL, 0xD036271CDDB84421ULL, 0xFCB6010212263FA2ULL, 
            0xF0E0DE4ADAF2A04FULL, 0xDFBCE17D986A713FULL, 0x0ED7774BA33BD0B5ULL, 0x9FF90012AA283197ULL
        },
        {
            0xBBC97AD905063B39ULL, 0x48863A5CD6AB7752ULL, 0xD5CA127DAEA8BBE1ULL, 0x729CDAE0F90172F4ULL, 
            0x392F176C2CD4A077ULL, 0x9B9A06A4AA42862DULL, 0xCDC99018CC99F543ULL, 0xC7098B799BFD4F7FULL, 
            0xFD1B95D19888DD8FULL, 0x20E9E12251D50067ULL, 0x27777A7D9C63E51AULL, 0xCBB304166A939816ULL, 
            0x7338ED3077373698ULL, 0xDA9C1E9E68A3FBE6ULL, 0xE2A94CF603B0D5C8ULL, 0xA59A35DE51991787ULL, 
            0x3737649F8473E29CULL, 0x48A3728252D3D265ULL, 0xACA9ACD00FABAC9EULL, 0xAE6EA871B0634077ULL, 
            0xC416602B9516FF31ULL, 0xCDD340698E6E0CBEULL, 0x5C704AD0918E4C8DULL, 0x6361C6AA4C1E7F43ULL, 
            0x5223709D82A5BE07ULL, 0x4607DDB9959D2F82ULL, 0x04E8DA1164636A3DULL, 0x5FC83066C613DBBBULL, 
            0x8FDAC3B66C8BF8F0ULL, 0xAFB92BAE517AE6E7ULL, 0x6B941EF13EB47059ULL, 0xA86157622914D8E4ULL
        },
        {
            0xB4B165C17FFC644CULL, 0x881387F872B0E184ULL, 0x60609B4E44F93104ULL, 0x222C2F357B59A85AULL, 
            0xA29D1FBA3D4440EBULL, 0xACB85550D3795544ULL, 0xD2CCAF2099CB9DF3ULL, 0x0A8ACF25AEA22378ULL, 
            0x0EFE94377CAF6608ULL, 0x558355B8CFF1592BULL, 0x67770782E844C3AEULL, 0xACEDF4C8BC84FAEEULL, 
            0x0EDF852E070A263BULL, 0x60BFA66D277B4CD6ULL, 0xDF65EE1B7D5451F9ULL, 0x2F2B921DA92CFF77ULL, 
            0x9F1E5F6D86CE3599ULL, 0x004E29E45A0E1A75ULL, 0xF000DB8BEC3A9D4EULL, 0xEB3BA265BC24AC24ULL, 
            0x2BDDDA59DF965EEFULL, 0x81D5AB78E25798EBULL, 0x245C909B87A329C1ULL, 0xF35DA476D238B4ECULL, 
            0x6BDB6F5CCFA3E4C1ULL, 0xEA029EC472CAD705ULL, 0x3DF8C48EA7B5D0FCULL, 0x4FFF8593A26A7108ULL, 
            0x3FB8AF1D10D3A57AULL, 0xC7AB3EEEB51F6EB2ULL, 0x742E9852E2FC1CDAULL, 0x9B872583191DEF57ULL
        },
        {
            0x420B1CC9A5397B29ULL, 0x3DAF6704A39FF833ULL, 0x43C539804517E530ULL, 0x25B3BD017A72FEFBULL, 
            0x60BD518A7F08DBB4ULL, 0x449E3C92ACB7A04CULL, 0x86DCE6199FEE5718ULL, 0x134E1B8F556C224BULL, 
            0x966A817982A23A12ULL, 0x563E1F54592256B5ULL, 0xFF2315DFA472C625ULL, 0x6C46FA6B82969CF7ULL, 
            0xCBB53790179C92D9ULL, 0xF431D74D175BD0F4ULL, 0x814648C511553724ULL, 0x020E234D0939C132ULL, 
            0xE958D440FF027C04ULL, 0xC99ACA42523C27DDULL, 0xA575C3FE5CD803F9ULL, 0x4D31B39E614F4AE3ULL, 
            0x6334087D7206FE80ULL, 0x297B68EFF122D31FULL, 0xFA910E5812243334ULL, 0x020B903F90FBAEE2ULL, 
            0xE7B83A689AD2150FULL, 0x9F4F7C52042EA883ULL, 0xEB44F8064A761D78ULL, 0xD39152415CD71CD8ULL, 
            0x10862636DF3DBD8AULL, 0x33D58B3EA8747430ULL, 0x94EDFB4BE4D9E628ULL, 0xB61AC46F9A62FA28ULL
        },
        {
            0x68DCCB466EB5C8C0ULL, 0xED3F0885D952B080ULL, 0x6D5BB161A7631F2DULL, 0xF2292229580CE9C2ULL, 
            0xDA55CB9E86B15999ULL, 0xA7047DCB778C9A83ULL, 0xFCCCA161ACD7F6A3ULL, 0x15696C0962C3B7F9ULL, 
            0xD6FB2FDC6A81DE2BULL, 0xC0B998EC45EB4D42ULL, 0x7100A135E787B6E2ULL, 0x02141E64F520DC97ULL, 
            0xA7F69856F5BCD0D2ULL, 0x14F887D9141EAD67ULL, 0x96E2640E658FCFBCULL, 0xA1ED087BA4D8C15BULL, 
            0x36B8AC11F8A583FBULL, 0x665983C77B8D05CEULL, 0x8BC7E790071D612FULL, 0x706E717E4AF37A83ULL, 
            0x21CE1F55B1317332ULL, 0x62D956C99BC9647BULL, 0x2EEB64D6393BB48CULL, 0xCEC6EEE11EAB49A3ULL, 
            0xA009547500D00831ULL, 0x79FFB40647BA5D83ULL, 0xCA0E463E4EF86B3CULL, 0xFDC1056967E15709ULL, 
            0x1BE29FA000729771ULL, 0x68AB31258C9DBE3AULL, 0x70153B32F786C97DULL, 0xAA754A76E276D03CULL
        },
        {
            0x4B5A44F858B43206ULL, 0xD92877BC937B5EA5ULL, 0x99BCD74ECB1101F1ULL, 0x04325C1ED33A2F6CULL, 
            0x5A0AC30C97F7ACDAULL, 0xAB7B41D4573BA042ULL, 0xA4EC4CEE83963C4AULL, 0x1F14321F7709C6A1ULL, 
            0x0A0191F2198B6B74ULL, 0x9B2B23A2AFE55900ULL, 0x8C8F6BAC3CAD85ECULL, 0xA190E23257CBAF08ULL, 
            0x54539251052D67DDULL, 0x84831B1229C76BEAULL, 0x574566CBFFDDF889ULL, 0x635A8718B78FBE73ULL, 
            0x956A1523985AD066ULL, 0xCB1D68BC921BC59EULL, 0xB387DD94A9ECE1CDULL, 0x624EDA1535FC65F3ULL, 
            0x30F45C8A7AADD12EULL, 0xD5B0CE401D834B58ULL, 0x1CA8B68DF8FC0225ULL, 0x1125E4B4F7F18BA5ULL, 
            0xD7F61E86DBFE7845ULL, 0xCBC0B853FC69A5A2ULL, 0x32649D1C848EE873ULL, 0xE972823BF2CFE807ULL, 
            0x9CB2647D5AD0EDB1ULL, 0x7A0433BECEF2CB03ULL, 0xB7B8623B9CE7B19FULL, 0x29DCDAD6CF9B44CEULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alnitak::kPhaseDConstants = {
    0xD9C43089479F6A29ULL,
    0x2C6BD9E70FEE815CULL,
    0xAB0C76009B3BAE87ULL,
    0xD9C43089479F6A29ULL,
    0x2C6BD9E70FEE815CULL,
    0xAB0C76009B3BAE87ULL,
    0xB66A359FE1FA31F5ULL,
    0xAD03D7B1A0AC942DULL,
    0x53,
    0x82,
    0xCD,
    0xED,
    0x26,
    0x59,
    0xA1,
    0xF7
};

const TwistDomainSaltSet TwistExpander_Alnitak::kPhaseESalts = {
    {
        {
            0xA4031F491D0D6F26ULL, 0xC3BF99B424571A86ULL, 0xD25011AD6FE6B958ULL, 0xA70A47173CDA4E75ULL, 
            0x18946A0BDFE5BECDULL, 0xCF28AFEBAC83416CULL, 0xE65C922B942208EDULL, 0x79ED863558DF54F6ULL, 
            0x009079AD70FB0410ULL, 0x936DB6A50466CEA1ULL, 0x4A8DAEC693E2756DULL, 0x97E8E967D817F6E9ULL, 
            0x1DDE363373CDD53DULL, 0x78649FBBF9049039ULL, 0x90FBF59FE0BCB489ULL, 0xEF1A32F211E95800ULL, 
            0xAEAF3E3FFF73541DULL, 0x06B53E5425C07736ULL, 0xD8432F93BF7AA54DULL, 0xB12D4E766B2262DDULL, 
            0x5A4CD2CA196AE673ULL, 0x2AC32DBE0B3E6A8FULL, 0x6D9AC45AA2438C1AULL, 0x29E9A8F40B6043B4ULL, 
            0x489F47AE83D1A20CULL, 0xB440CFD6EBCC1CBAULL, 0xC35EAC8B9FFF578BULL, 0xF67A68F0E46D338AULL, 
            0xCDFA44B2E52C2165ULL, 0x93291A38DE39FDF2ULL, 0x53541792E90668B4ULL, 0xC46FB4A7FC988A9BULL
        },
        {
            0xF385C1AD22602153ULL, 0x2FECA82654937D99ULL, 0x52197BDAF7A872F1ULL, 0xCCA1EB3D1110D052ULL, 
            0x502D68377B06920DULL, 0x5EFE714FBA7DBD7CULL, 0x32E2E5D43CD96351ULL, 0xAA6CB4CAD136C758ULL, 
            0x2467353C71920A02ULL, 0x6FA91489B12A3AF2ULL, 0x022B65C3A8BB7A75ULL, 0xA48DF6DE1028E2BEULL, 
            0x2B03B2FB2C42050BULL, 0xFE1AF0B13FEBB517ULL, 0x6C55E5C7FA2D5BE0ULL, 0xFA4060453C2AF1CCULL, 
            0x641014C3BE682C44ULL, 0x01A084C8AD8C5457ULL, 0x5D71ABFF54BE4BF3ULL, 0xD80EAFAC99CF7EDEULL, 
            0xF55B987C336EB488ULL, 0x893BF40A290D503AULL, 0xDB5356D2AC02D3ACULL, 0xD4DCF7FEADF4DDAEULL, 
            0xD5113E965554BC88ULL, 0xA230873298DF08D2ULL, 0xA9F221F2D3BB94E5ULL, 0x69EBE3262A609E3EULL, 
            0x41EEE594DCE69325ULL, 0x01F8214580A1D923ULL, 0x11E65C9BCAA41610ULL, 0x44BC88BE4F4AA995ULL
        },
        {
            0x235C0760639FE2C2ULL, 0x085A6388FC8922DEULL, 0xE3F7CCCD1C24E89CULL, 0x6216C10D222FCA1AULL, 
            0x7FA249C779B638ECULL, 0xEC4710BA6D04284FULL, 0x250FF5FA8461CB9EULL, 0x03A9221DC42A14CCULL, 
            0x5DE6DB54C612B7C0ULL, 0x96A821CF8978EFD0ULL, 0x84E9448E26C2D8FAULL, 0xA5090CCAC2B76E37ULL, 
            0x365B11046908960DULL, 0x29FC9DB13E5F3C5DULL, 0x2CBA3F0AC68D879FULL, 0xA49259EDD7447CB8ULL, 
            0x896D259EBF888D90ULL, 0xC1E33A70EC0C00FBULL, 0xA2D8716A59C16772ULL, 0x026D36D76947E9CBULL, 
            0x9F2D36920E37A6E7ULL, 0x178D0242B7FBEC7EULL, 0xB9C5CF4E15177415ULL, 0xAE5F80C1CF84D665ULL, 
            0x23302E41AD833CCAULL, 0xA9880C749373EE35ULL, 0xE42DA9CB8958C8C6ULL, 0xEC9DA2CF06C155BDULL, 
            0x15D565262B7A2B0AULL, 0x2767DD381CD14B64ULL, 0xE645E06DE9F3DDE5ULL, 0xE6FBF2D76968435FULL
        },
        {
            0x2A5314B082D308AEULL, 0x1986511E4E0A8F64ULL, 0xCE41FB9A4D5089EDULL, 0x859AFAB718677A25ULL, 
            0x1B7AAA3279A1AA29ULL, 0x7E7439507712832EULL, 0xDE487FA0828E818EULL, 0xDC1FA0F06C8B279FULL, 
            0x462C9BA08DB852D0ULL, 0x4BCE748CAB548EC2ULL, 0x797D953654C98E77ULL, 0x2D435F31026A6DEDULL, 
            0xC95E607F84058CB6ULL, 0x49235BFAB5D4C56AULL, 0x0891081FB5187F08ULL, 0xAC3BB34EE3AADD8FULL, 
            0x93421F652CBBE61EULL, 0xAB117A0D09C8D493ULL, 0x979B28470658B9E6ULL, 0x79C6DAE5382BB88DULL, 
            0x3116FFC574370DB1ULL, 0x5C01265BDDCF620DULL, 0xC9C9BF65C837216FULL, 0x72AFC21959F96D9DULL, 
            0x02C22F183EEEBC84ULL, 0xE7857058B5FF6EDAULL, 0x07238BBDF48E4960ULL, 0x5B95C4938F8C3447ULL, 
            0x19D5C4457EF99DBAULL, 0x76A41C5CF665170EULL, 0x6353367C0A347D63ULL, 0xAB4F1E92AAF12454ULL
        },
        {
            0xA56A136B94E58093ULL, 0x05A713D3583F81C4ULL, 0x25E5187D865F3BC6ULL, 0x9D93B503D4907B02ULL, 
            0xE79CE88B89E5ED92ULL, 0x17685624F19A47ACULL, 0xD3827C83A1244D6AULL, 0x63E4AC51081F5776ULL, 
            0x83F4FC7D39434695ULL, 0x38EBE6F1C5DEAD19ULL, 0x053C9A8D62092AF0ULL, 0x8113F66B30E7542DULL, 
            0x0C536166CA57EF39ULL, 0xDFC355874544F861ULL, 0xA599346682C94CB7ULL, 0xEE0982B59DDE6396ULL, 
            0x8DE1C8B4D56C2522ULL, 0x10CB30DB61437F8FULL, 0xF606D9A1C78DCA00ULL, 0xF6A49BEF790C00B5ULL, 
            0xAFB3F76E7BCABE4CULL, 0x39DCE9CA03B82D08ULL, 0xC6318A5482443B6FULL, 0xE55FD2D87659D42EULL, 
            0xE0BDEBD9B6ECF41AULL, 0x21DEF1D281248FD8ULL, 0xF464A7BBDFA61955ULL, 0x8F1D751D8C35CF75ULL, 
            0x1F7EF52AA63E2A81ULL, 0x429FAAF894E359EEULL, 0x2E6EB977D87C8214ULL, 0x8CA4D56DF419F246ULL
        },
        {
            0x8A5B0B070EDBEBEFULL, 0x07F6C786AA5E7C82ULL, 0xC3FF3978D73C1D9DULL, 0xDB55C51D0492C42BULL, 
            0x00E42C677BAB3900ULL, 0x61A3F3F79EBE9BE3ULL, 0xA50B03D983312C15ULL, 0x991B54EFB66D8B43ULL, 
            0xB544776AF73D7921ULL, 0x9C6665883EEDD5CCULL, 0xE5FF6FC8AF966BC3ULL, 0x595C9E48F688734FULL, 
            0x3AFEEEDFCC9352B8ULL, 0xAF71D536B9D3B0B7ULL, 0x92BD4F470CD81D83ULL, 0x09485B1FB6ADCEB8ULL, 
            0xC8D91D70A514FAC2ULL, 0x65843A49BDF75CD1ULL, 0x724792BE8942E6A1ULL, 0x1F12520EC2F6F727ULL, 
            0xBD60D98A4D4C7A8AULL, 0xE8196FD5DB3A329AULL, 0x74272E412D2B12A2ULL, 0x8C636FE6CAFFBA2EULL, 
            0xF61D8B8C70878B35ULL, 0x39EF00644E8ABA1EULL, 0xDDA48FB750F8CEC6ULL, 0x499062CA608B2424ULL, 
            0xA983733C0ABA54E5ULL, 0x336E7F959B3989D0ULL, 0xE0C1D5446352508DULL, 0x41D9447FB3351AF8ULL
        }
    },
    {
        {
            0x1DC50B631DE38BAAULL, 0xC2C3682A44262CB1ULL, 0xC33BBCD55BE029D6ULL, 0x3DB4182F776D6606ULL, 
            0x722AB4DAF4798FF7ULL, 0xFE0CAC2DE3918B64ULL, 0x3D7BFC5E9C735D5CULL, 0xC87AD18D630927C8ULL, 
            0x9833AE48952ACB0CULL, 0xF4447BE350741289ULL, 0x9F78158DC234EC17ULL, 0x505FD707C91D2FE7ULL, 
            0xB0DC90B3750C5103ULL, 0x1532EE6764C4C235ULL, 0x44EAB771828D448CULL, 0xD47AEA1A64157A2BULL, 
            0xBBAB39EBE1EAC070ULL, 0x2D7A48DC98C2ECECULL, 0xC90009586E1F2A5FULL, 0x1F6F7810446409A6ULL, 
            0x22C70988D3B54015ULL, 0x5CE53E7250D35152ULL, 0xA39B7049D2F4F67FULL, 0xCA205F0DF509FC85ULL, 
            0x3DDCEE389DD0AA84ULL, 0xC55C1F1E2F05BC99ULL, 0x8B7A77D26297D707ULL, 0x92C3459C71C81ACCULL, 
            0x09EB241EE3C07852ULL, 0x7DD56D580C98BFEBULL, 0x3FAA8213E1C57366ULL, 0xD95FFC6BA8407759ULL
        },
        {
            0x18DE8046A0D2724CULL, 0xF4B2B5C1D01AC62DULL, 0x1D358200924E8A28ULL, 0xFB5DC84C36BF8617ULL, 
            0x3F8445736709CF25ULL, 0x9ED713A1ED372772ULL, 0x40FD46C96426AFA7ULL, 0x8E4962A4B612487EULL, 
            0x34D1ABE8D7BC6041ULL, 0x0513E39EC1EDFED2ULL, 0xF9BDDE7BDA7B7E45ULL, 0xD28F9BFD7AA2FF2AULL, 
            0xAFB6A4D7EAA1E779ULL, 0xA4A4F5CE605AF559ULL, 0xD846334750261579ULL, 0xA589C7B01C89D179ULL, 
            0x81AF2343115BC28EULL, 0x6BD57A11C6D5B08EULL, 0xC44DE69C3D246ECFULL, 0xEE86ABE6A7AE2AB1ULL, 
            0x3E79DE739285381CULL, 0x73F9C38D27D85EAFULL, 0x1A02EC7FAA04AA85ULL, 0xA5DAA312535AC8E3ULL, 
            0xA224837EB15FC170ULL, 0x164C7FD2EDB4E671ULL, 0xD3BB2FB420DB7CC3ULL, 0xDBBFFD3FB75A9D2AULL, 
            0x0834662C8EB7069AULL, 0x6A3D43582BECA179ULL, 0xB1D43CCD10E76825ULL, 0xB97D49C791D753FEULL
        },
        {
            0xB8BD17049016C17AULL, 0x5C3131D7EC7DB8A9ULL, 0xCD121317ABB85C4EULL, 0x6DDB928F2B3EDB9BULL, 
            0xD598FE7CE8883060ULL, 0x117D8213A99F83F1ULL, 0xB81E961BFBBF88A0ULL, 0x56D73FFD14BBDF66ULL, 
            0x901973E218E0762CULL, 0x9AC3078C2AD28423ULL, 0x328EE0B6D1F15B7FULL, 0x02958B2164121A1FULL, 
            0xCE8C46F5903C51E4ULL, 0x1E7F8E8C049DE60FULL, 0xCEE8231F4951187BULL, 0xEE3F02978C9B7156ULL, 
            0xC7BEC4FE69DC413AULL, 0x31002DDEA418F86EULL, 0x405810D3C3F98759ULL, 0xB369E727CD802285ULL, 
            0x427D0D6F70C95E0BULL, 0x55F77A4E7FB5B3BCULL, 0xB6C62E6DF9B2AE2CULL, 0xC05FAEE26A11B048ULL, 
            0x0A3F517F44FD5985ULL, 0xCB08FFDEDFFF64C7ULL, 0x4365D24FBA3B1B98ULL, 0x6E893A6660C89A3FULL, 
            0xAC75F9CA3CFE1715ULL, 0x3332EF0D8BD3A837ULL, 0x060E851E0C823CD5ULL, 0x87FA07895F596650ULL
        },
        {
            0xDE8F3D75C12EE1B6ULL, 0xFAD79E4E544C5A68ULL, 0x6D5B0D9D7DC36A95ULL, 0x166021BCB078F205ULL, 
            0x5980C86D40E1D40DULL, 0xFCADAD13C466D21FULL, 0x700BB1CC51786D8AULL, 0x0D7DC29F3541F606ULL, 
            0x9002852DE6F9AFB9ULL, 0xB3BEBFE30FE48D09ULL, 0xCA9A202DE64B7CB2ULL, 0xF6ED1B98ADE5A545ULL, 
            0x3DAA884E7FFE8F0CULL, 0x047DB4048157A602ULL, 0x87A997F6E6A8A6B5ULL, 0x2E9AC66F8CDAA42FULL, 
            0x361294CB59C4544EULL, 0x790A0346A361EAB4ULL, 0xC010B3DA8D4AAD83ULL, 0x66F8F62E42EFCE81ULL, 
            0x65E660D3B81257F7ULL, 0x1CC98AEAD03ED247ULL, 0xEE9B5A043D41F84CULL, 0x43EEA13F27FB2666ULL, 
            0x1C372B3A2324B34FULL, 0x963265EEB877FAEAULL, 0x889600C03E60E02EULL, 0x674DC61809C96FB5ULL, 
            0xBA06290796842771ULL, 0xB96F37D6FBBB77F4ULL, 0x97C61D715E03CC4FULL, 0x32E10265EA10E20FULL
        },
        {
            0xD83C0DAF7B7CF09EULL, 0xF692014ED2EC98D2ULL, 0x119587A1E817A4ABULL, 0x47021DBE0E5AEE1FULL, 
            0x1225B0EF21D18CECULL, 0xDE05657E38F82A03ULL, 0xD3F17DC7F17E3386ULL, 0x1BF7FE86C5C5B1B3ULL, 
            0x8381274B3AB0FE91ULL, 0xE45E6F752DB80817ULL, 0x133B5B049FCE9B88ULL, 0x5A53D4E81CE88CA5ULL, 
            0x2D3986E15C51BBA8ULL, 0xE03789078FA0F4A9ULL, 0x1C2BBBC6CC01E978ULL, 0x18BF4AACA505205EULL, 
            0xD1C0DDFEBF2A4851ULL, 0xC507068206801518ULL, 0xCAAEEEF714B5B607ULL, 0xBE8232E336EA204DULL, 
            0xC2CF19D1935B9872ULL, 0x7E7CDFD63AE0B7AEULL, 0xD10206B3245AF67DULL, 0x56F378FFDA38CE99ULL, 
            0x282C9CB1DF4A5896ULL, 0x8CDBC3ACE1CB8F1EULL, 0xA090B22542376C3AULL, 0xA21D244C048910E3ULL, 
            0x04CB7908EC22C324ULL, 0x65CB6E60E95EFFC1ULL, 0xA4FDAAABF9BC839FULL, 0xCDDA1D4A9472292AULL
        },
        {
            0xBF4DA5045DED8083ULL, 0x35B2882712E3D8A7ULL, 0xE58BEED05CED5CD9ULL, 0x3335AE79852CA557ULL, 
            0xC352991DD31DEA4BULL, 0xC9E8F6BFF0DC0F2DULL, 0xBCC25CBECE668E21ULL, 0x96B6CE3F4749AE73ULL, 
            0x4641BF88B7300F49ULL, 0xF7BC28F0F568C623ULL, 0xA418243E479A0755ULL, 0x0BC9BFADF777A560ULL, 
            0xA1362251792E9EE2ULL, 0xDBC6953DD3FAF86AULL, 0xAA467C15D5F460B1ULL, 0x9DD2676FFF5215BDULL, 
            0x2B2449717B9305F1ULL, 0xA07D3C9B2F3645C7ULL, 0x38A6C0264358792CULL, 0xDC3E025988467348ULL, 
            0x1DA08ED3F881429CULL, 0x1390D8E53758ECF7ULL, 0x733DE7CA48A255F6ULL, 0xB0CC63EB38BBCF7FULL, 
            0xA274B74ECF9E09F9ULL, 0xB969D0823E162AC3ULL, 0xCE119FE46CF14B4CULL, 0x23AA126A5EF83095ULL, 
            0x2DFED9A7674C552FULL, 0x5FE1BB4EC1C192B1ULL, 0x0661DD352DCA04AFULL, 0xBCCC456E1CB2B6CAULL
        }
    },
    {
        {
            0x6FEC0F4D1DC67503ULL, 0x86FDC16CF8C119EBULL, 0xB6EFC81BE6A019E8ULL, 0xF5B043C9503066ACULL, 
            0x5422C6388FBC6E4CULL, 0x166CCF21D2548CA6ULL, 0xC9CA2F44110A2DE2ULL, 0xE7AF0013A4BC5CF6ULL, 
            0x7F269A444A168A64ULL, 0x838501AF0F96E533ULL, 0xB4329EFEF1CC3044ULL, 0xD8971625B700F8DBULL, 
            0xA4FDE4C598741DB6ULL, 0x49BDB5FBF8C46687ULL, 0x2D081F006AB06F01ULL, 0x499AD1824017D8A4ULL, 
            0x7EC1ED69223227D9ULL, 0x1F5672DBF6CC01A0ULL, 0x4FB3E1CEFA905859ULL, 0x26CD2AE32852557DULL, 
            0xAB1637850AE5F648ULL, 0xE30DC1001D1EA2EDULL, 0xC8DF32F1F77BE44EULL, 0x4C0ED3F28E535B05ULL, 
            0x507E18583D69677AULL, 0x2D99B19B4D48A4F7ULL, 0xF574CDD704082F2FULL, 0x03C17B085D028BA2ULL, 
            0xE293E2545AA5B7B2ULL, 0x4B2B6000ED52C0EAULL, 0xBE4FDE1A2CCAA4FDULL, 0xB16AEF71D809041BULL
        },
        {
            0xA4B48983A514718CULL, 0x3A7EDF13CC054BBDULL, 0x00CD93EFA1D12A6AULL, 0x35B24FE21CF81E61ULL, 
            0x4B7996A9AEA46555ULL, 0xC7FD956FA2DCAC8DULL, 0x235E6726B3B63C2CULL, 0xC88C760717498D89ULL, 
            0xCC36FF8780D41E14ULL, 0x5DFB428BC656EAA9ULL, 0x2702AE198C1236CCULL, 0x051FE0400E800A62ULL, 
            0xD6207D25DE4D0E30ULL, 0x07477FBEA2EF579DULL, 0x9673FC7AD468A13EULL, 0xC9F6E5722ADE174FULL, 
            0xD7D4372735247935ULL, 0x57A32AE93450FE9CULL, 0xBB8C6851147FE4EDULL, 0xDAF5B51711DDE789ULL, 
            0x28DAB942C6857BE8ULL, 0xC7A4DCB075FBF88BULL, 0x8EE4CA4F1F116DD9ULL, 0x86709C1B026FACB4ULL, 
            0x3D3ECB4FEE0DE209ULL, 0x0D5A603151825832ULL, 0x17CFDE50E7A9A894ULL, 0x7977A26E704F38B2ULL, 
            0xF27B1611D99F5818ULL, 0xF1354ECD13749EDCULL, 0xCB180E5FF04B6FE5ULL, 0x0C01E15C0D883317ULL
        },
        {
            0xDB65F758CF6FC686ULL, 0xA75291174BC91D0CULL, 0x8500C7BF8E71E86CULL, 0x1A4BBAF4DE180BB5ULL, 
            0xDDF05DF967ACCCD2ULL, 0xEDFD9C435C0BCE25ULL, 0x7134A160C4FBDDE5ULL, 0x8C72262C94D6E1A3ULL, 
            0xAFDD1AF35F1AD039ULL, 0x42E2792298E5A5C8ULL, 0x9A96106CB4F08E45ULL, 0xD4C967D3934CB9F2ULL, 
            0xE87B40BD54A4A727ULL, 0x2B28A3A558A79149ULL, 0xBD0FB909A237AE67ULL, 0x88C579203F573A94ULL, 
            0x72A7E4E162602A5EULL, 0x00DA72504E38E272ULL, 0x317F0BD8176A80A2ULL, 0x51D99BF92C403B61ULL, 
            0x265C101636375B57ULL, 0x5B0D33F14F69A65EULL, 0x67318DD123BECF40ULL, 0x26AB1A402D9106AAULL, 
            0xDE9BB4172A3943D9ULL, 0xF682F87DDF64056EULL, 0x73EFD4D93E9747D8ULL, 0x366A3B7B14E099B7ULL, 
            0xC90EDEC0111E3281ULL, 0x330E984D6DF2E1B3ULL, 0x5DAA5AE052BAF472ULL, 0xEB7F84C1C05B9F2CULL
        },
        {
            0x1453F5CE7F32EDECULL, 0x971C69049CB4B3B9ULL, 0x1ECC00DA4C2CC2F3ULL, 0x7AFA7AF5DDCB7F74ULL, 
            0x45B0B6127914F3ACULL, 0x5F0F177BE87D3084ULL, 0xED4717F67B146DDEULL, 0xA0F5B92808598DDCULL, 
            0x5094712A7125E311ULL, 0x76B7F5389360D657ULL, 0xBF2A1EDEA9A9A9E0ULL, 0x7E52DA4214150EBFULL, 
            0x24CB29DCEE67D970ULL, 0x6614A6E8F48791BAULL, 0x195ACE5294FC3D0DULL, 0x29CBA84730FF6487ULL, 
            0x0840BEC9A8916099ULL, 0x19E0FA979E473097ULL, 0x746421F673FC87BAULL, 0xB5E2DADE927C67A4ULL, 
            0xF4299D7092291E3CULL, 0xD7D7DDD4DE696CCBULL, 0x6868601C023A1419ULL, 0xE992126525C97200ULL, 
            0xECB561426691F4C5ULL, 0x8FA581958574C957ULL, 0x7D3BAAB53943D23FULL, 0x26FE5C14D6EE6EC4ULL, 
            0x8B109150B893EB76ULL, 0x430DC705DE92102EULL, 0x73E1C75D51A1B2A3ULL, 0x2ECD6329BAE2D266ULL
        },
        {
            0x93F571750DA7985EULL, 0x4DB0F8E9B12FEC25ULL, 0x4BF60E39B69D2B45ULL, 0xF1A31A7B49875C8AULL, 
            0x497AF552AEC704F8ULL, 0xDD6AD2D098D2E84CULL, 0xAB84068535E0B4A5ULL, 0x982BB4EE32BE9DF9ULL, 
            0xA0B173DCBA1E54A7ULL, 0x0E41DB0DA7F37885ULL, 0x075F014CD02DC986ULL, 0xE8F8314587716D5CULL, 
            0xDFE2F57920AA5656ULL, 0xF790B8DB565A274FULL, 0x9A3AB06D0F9DA6FDULL, 0xD25C5B67C1FACE7DULL, 
            0x30219664289CDADBULL, 0x9D31D9BCFA0FDE6BULL, 0xF954C36436FCBB69ULL, 0xF1286C835BE8E5A6ULL, 
            0xEA72069B5B94E0DFULL, 0x9EC25E5F2BACAF42ULL, 0xF7832F0AAD0514C4ULL, 0x3730AC29ECF5CCAAULL, 
            0xF38A80A1BF9A71B5ULL, 0x03F977A787147FB3ULL, 0x3EFC2FFC9135EA5DULL, 0x65C1AB0EA44134CEULL, 
            0x2A72AE93C9F33583ULL, 0x5EE29F12E0C9EEFCULL, 0x7E9D1A4F139F6DA8ULL, 0x2BD3C16F311FE933ULL
        },
        {
            0x6FE8C6C15747C3C3ULL, 0x990F8F9097944F7AULL, 0xE36F34636F73963CULL, 0xDBC83D5E1ABEC842ULL, 
            0xF4FD4319B38AD3C1ULL, 0x3E96034B8741153DULL, 0xE630B47372B5A32AULL, 0x8A16F77260424899ULL, 
            0xDC014AD9CFA32739ULL, 0x27DB81D3E1844760ULL, 0xB1C6B2956BF4C15EULL, 0xE276B1877E817290ULL, 
            0x18111C6E6B74C668ULL, 0x06BEE3D9C82A55BBULL, 0xC9E8186B530141A8ULL, 0x1CF0923FAA4590AEULL, 
            0x8ED35674BB25970AULL, 0x8B88271A6595EAEAULL, 0xB7F093E6992402EDULL, 0xD14A655C2410FD81ULL, 
            0x6E3B44E09C067234ULL, 0x9BEA043EA535976CULL, 0x847EFFACE74022F2ULL, 0x9389BB8C4C9323EBULL, 
            0xA74D333609E3D74AULL, 0x0954D6640B4B0CBFULL, 0x57449BC76985A139ULL, 0x6A811931365E8399ULL, 
            0x655447B77B98A3DCULL, 0xCAE93C995B7FDC63ULL, 0x285C896F0DA25611ULL, 0xC04F1F1BE274FAB2ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alnitak::kPhaseEConstants = {
    0x538F45F201B967E1ULL,
    0xD8F6492E5610133AULL,
    0x4BB0ADB4E2F54A44ULL,
    0x538F45F201B967E1ULL,
    0xD8F6492E5610133AULL,
    0x4BB0ADB4E2F54A44ULL,
    0xC51A89B2CE51189EULL,
    0x3B2BE49856580B91ULL,
    0xA4,
    0x86,
    0xDE,
    0x7A,
    0x91,
    0x86,
    0x08,
    0x9F
};

const TwistDomainSaltSet TwistExpander_Alnitak::kPhaseFSalts = {
    {
        {
            0x3357D37EB28BC494ULL, 0xD4EDCA783E08C642ULL, 0x2AC3DE185288D242ULL, 0x5C6D30D04D31F627ULL, 
            0x17B8FEDA91B8DB27ULL, 0x10E8C6CF4A0EBABEULL, 0x75C6E26330CF0AA0ULL, 0x55CBB3F8A6D06B5BULL, 
            0x5EDB3BDE753AB96EULL, 0xD13A6BFBE998BE6EULL, 0x27E5482ED8E71774ULL, 0xE9FD157751431E97ULL, 
            0xF70C4F8A7B6A4636ULL, 0x12034328826DE63BULL, 0xD542D3A7E0D03BBFULL, 0x472C50277C6F4516ULL, 
            0xA635542C79A26B32ULL, 0x52BDFA99DF4CCBADULL, 0x0B30CF83D5E2D625ULL, 0xF9EE22FB496EA851ULL, 
            0x5D32FF7EDE0E27CEULL, 0xD7D559A0FA3B36EEULL, 0xC7EEE5555BF1763FULL, 0xA987CDDE6B54E6A0ULL, 
            0x57FF04C834525F5BULL, 0xAD53BB9FA1DFDCE0ULL, 0x1B09A1142BC8767EULL, 0xE7630F313D562991ULL, 
            0x855A33E65661EA64ULL, 0x09A95C758521E162ULL, 0xDFBAFC8B00F92CB5ULL, 0x3FE6949A8453CB50ULL
        },
        {
            0x92DD058503049EF4ULL, 0x43457F85ACD414CCULL, 0xE5B53B21458C496CULL, 0xA4B9403D25766A00ULL, 
            0x3427138021E3310DULL, 0x3D42B0C3ED446F86ULL, 0x8011FA99FCF42DDFULL, 0x1EF2A6FD42575E25ULL, 
            0xA9B2C9B9A631EFF1ULL, 0x3B61AA08BFEF551CULL, 0x28DB07CB9F8DC9FCULL, 0x455125D28C5C4253ULL, 
            0x19017E30A127F039ULL, 0x57FA13654B8ADB66ULL, 0x6C8D32F49253E59DULL, 0x6E8174100CB038E3ULL, 
            0x4E074F3E3065CF67ULL, 0xABC023D5C6DAC566ULL, 0xFB69DF5DEE7E34B6ULL, 0x949846C128698968ULL, 
            0x9920F7A4CAA52064ULL, 0xC09AA914C79C133DULL, 0x0E59EE32FD7CC1FFULL, 0xFC2F64CF55856203ULL, 
            0xD3E5B1CD717BB555ULL, 0x9B6FF9F64D8D70FDULL, 0x34638FF9ED9A136BULL, 0x9E5DA737AA628079ULL, 
            0x3376A1BF5CBB9196ULL, 0x271FC12926E07729ULL, 0x8F6C9607F9E0791CULL, 0x63475BF9A71E8D02ULL
        },
        {
            0x73B160899FE55C97ULL, 0xE06696E5EBAB789FULL, 0xBF49CEFF63FEFDE8ULL, 0x0AFF063834E43209ULL, 
            0xAE5A035F3DB45B40ULL, 0x830F2BF838A3C58AULL, 0x93A701F2E78DF01AULL, 0x32131EB1857793A6ULL, 
            0xF223CE38360ABE04ULL, 0xCC9C27D4355558DAULL, 0x198D2F317B597DDDULL, 0xDAB8FB7FED50213BULL, 
            0x90310C773BB9DD68ULL, 0xAECFDDE693BD5095ULL, 0xEA40F8A1CAF0A2F1ULL, 0x46233E2ECB130DF9ULL, 
            0x93573DED38745AA2ULL, 0x5B3E936150EA5B3AULL, 0x5166FD59CCDB430BULL, 0x05E43524425BE153ULL, 
            0xAEE7B966A0FF1779ULL, 0x92CDBFABB7529619ULL, 0xECC96E449BAFF3F5ULL, 0x427F577AFF3D2F22ULL, 
            0xF24500188FC55784ULL, 0xCF9545BAA08AC617ULL, 0xD1D498EE49093C61ULL, 0xCF73FCE091968676ULL, 
            0xDE307BBD94D1AC47ULL, 0x5D876345AFCD2331ULL, 0xF6BABA28B79B5651ULL, 0x218807E462F26223ULL
        },
        {
            0xB9EECDE9DC2CE4A3ULL, 0xACF3C4261B161769ULL, 0x79A547CC1232814BULL, 0xFA1CB6D3D9EE133FULL, 
            0xCDF12CDD70421685ULL, 0x4C067CC8951330AAULL, 0xB750677EC71C1F12ULL, 0x3725A33ED0171913ULL, 
            0x5B7B5584B7213D26ULL, 0xEE5689019D9A35A1ULL, 0x2FED426F0B833246ULL, 0xBBAC7C2223BA67F3ULL, 
            0xB45E62E43ED82381ULL, 0x0FB3A540A4F1374FULL, 0x01F99AFC8FA8D5EFULL, 0x09134EF8711FB3BEULL, 
            0xB37469E15C8CDA05ULL, 0x145A1475F2D156D2ULL, 0x4D684A696CA8B7BFULL, 0x7663ED885B268ED4ULL, 
            0xD516474FE00D8968ULL, 0x93A32B51862726FEULL, 0xE32EAFC963FDB855ULL, 0xE4D7080E3F537C3FULL, 
            0xEA53075C22A0BE69ULL, 0x81008834BE4FA6C9ULL, 0xC0273AB532187228ULL, 0xDDD4AB705C6E3A94ULL, 
            0x25AC9E017F76C441ULL, 0xA148ACB0861C531DULL, 0xEC38D8F7CBEA920BULL, 0xB8EE1E3CDEFCD62CULL
        },
        {
            0x787F91198649F08EULL, 0x501B2DF76734B7F9ULL, 0x5D9F76034A2201B5ULL, 0xA08E8B4C578B4E7AULL, 
            0xB57F5A9C44E80C25ULL, 0xF742E67AA0C58544ULL, 0xAB544F63555E5FB0ULL, 0x1EC5331BA26EB48EULL, 
            0xAD881AB6CC45FAC7ULL, 0xDB1C5F4C5780B609ULL, 0x5BD6248F79676976ULL, 0x214DE99D3479D822ULL, 
            0x33F89BCD0901DE09ULL, 0xFE8581B52C3532DAULL, 0xF598F2A7D6B83F34ULL, 0x93D08D50BAF3E885ULL, 
            0x44634AF9F202E7DFULL, 0xC06CE95FF00DC75BULL, 0x2EBA15EA70296951ULL, 0xFA080E033E14AB3EULL, 
            0xC4E74BAC2D2581B9ULL, 0xF84225BB7D705A36ULL, 0x8322ED0FBA6FEFF1ULL, 0xBDA98257BE614CA6ULL, 
            0x311EE7F137619976ULL, 0x89C013582D45DC90ULL, 0x3262AD76DCB7793AULL, 0x272AC420EC274E34ULL, 
            0x628527B18D2ED7F9ULL, 0xE5CCB32DBC3BE39BULL, 0xA64BCF92E6D40D79ULL, 0x821BE91217D60688ULL
        },
        {
            0xA01E7FD97E7D4D23ULL, 0x942A2062CE7481C2ULL, 0x3B2F19A525EDF135ULL, 0x6C60B55FF71CD448ULL, 
            0xA4111A30201E8FD0ULL, 0xEE3E1F584A9ECB36ULL, 0x28A446BB2F9CFCF7ULL, 0x0EFAE9181AC28421ULL, 
            0xD2659E6AD71AD131ULL, 0x7DAA0A5BA8F37975ULL, 0x61DA0DB61258BDC3ULL, 0x16DA34462252873FULL, 
            0xD85D685051547690ULL, 0xCF0B49DD472EA4F2ULL, 0x7A7F714E4D36488DULL, 0x336198E63F76476BULL, 
            0x0E685E890F81ED18ULL, 0xF2F43DBE6AE90585ULL, 0x289A5D26EF2748B8ULL, 0x5AB3D5452ACDB2ABULL, 
            0x70998D1CBA63FF27ULL, 0x6D06C762747C3D4FULL, 0x9CD2F385A1BC580DULL, 0x8DA4446CF4F96B14ULL, 
            0xAE6A378153C09618ULL, 0xBAB54458F5E088D4ULL, 0x93E132DF6A139E34ULL, 0xAAD9B42AEA420EFAULL, 
            0x6369F78BD5539124ULL, 0xB5BDD70857F76C34ULL, 0xEF079CD3D30206A2ULL, 0xEE8E7C6680C4C09BULL
        }
    },
    {
        {
            0xB3E5B84006026221ULL, 0x78655833D93B402EULL, 0x8D55C983A9880D7EULL, 0x7469B381A3B0C6EEULL, 
            0x137027FE1C076086ULL, 0xE5AE253FAE211607ULL, 0xA7F3FB6378D3CBB6ULL, 0x864C3C294FD3C134ULL, 
            0xF6BEA8784C80A34EULL, 0x525DE6A2868E84DAULL, 0xC302EABA724F8188ULL, 0xD43A613C663010AAULL, 
            0xF4E78DC2F393C4EEULL, 0x58DD29CC659A9A51ULL, 0x0C2F717E551E54C7ULL, 0xFA4AB727904EF2A0ULL, 
            0x660487DD4EC579FDULL, 0xBCF4ECA9E18255E6ULL, 0xD21607490AB74DF3ULL, 0xE81CBCCBC06FE8B3ULL, 
            0xF161A37225D4ED9FULL, 0xA856C32C6D8C8F20ULL, 0x532897E4577E601DULL, 0x0ADD1D1612E3F742ULL, 
            0xB90C66AA1B545618ULL, 0x540306DC911011F7ULL, 0x34182A15D0F413F0ULL, 0xEF134B7DFF861CD2ULL, 
            0x2E7F0C5A247FB1B5ULL, 0x3F76104C9E4B9E06ULL, 0x1B7BBAF11C59D403ULL, 0x018D27ED27013CF0ULL
        },
        {
            0x0ACC1A1E2F97CE06ULL, 0x6F03EC0F74FA5A0EULL, 0x29432AD347E6E461ULL, 0x53F6CCD18436B0D7ULL, 
            0x7458252C628F0657ULL, 0x8B627E76C25667D8ULL, 0x5FDD219F2EBB53B5ULL, 0xC4A8ECE9F250D5A8ULL, 
            0x6DF1C97D8CCF121CULL, 0x0DA78618E40FB918ULL, 0x901E44F8D1538FFFULL, 0x3A8DF709641B9E1DULL, 
            0x41989D4D04BA9884ULL, 0x17E3A44740E4AFBBULL, 0x87ACF9BEE91AE2BFULL, 0xD2706B2625541AABULL, 
            0x689E76C16A495D7FULL, 0xDB08A022DD86F056ULL, 0x2F421E65473F0E1FULL, 0xD4E753743D334449ULL, 
            0x6090CD0E24A95CEAULL, 0x6ADBB7898714878BULL, 0xDFA337ED4866B1F2ULL, 0x1CB725283FD08B63ULL, 
            0x21E6BF54FB66DE9FULL, 0x1F95F68420AEA993ULL, 0x8D6F0AE69DE1BB92ULL, 0x7A9BAE1334F4F4ECULL, 
            0x8E4A3802E67940B4ULL, 0x91FB8B4B858AD124ULL, 0x3F1B4EE9AF43D414ULL, 0x8B6893A58141B6CDULL
        },
        {
            0xE343FE16B8C993EFULL, 0x2D92728B9AE1C52CULL, 0x5027879426A3998AULL, 0x8DA69BFE4C128967ULL, 
            0xCDBB1E28F4F002E2ULL, 0x41706E74EB4F3C0CULL, 0xA3EEC809DD41EA52ULL, 0xFCF4C4777CB4B1CEULL, 
            0xD1C1093CDF1BAAA8ULL, 0x70809462BA7B2CADULL, 0x5953DF15FC9EDAC2ULL, 0x9E5DF3F302F54FB1ULL, 
            0xAE438D115CB5B7A5ULL, 0xACCE1F7A967A0F33ULL, 0xD3B0203ECA772CE3ULL, 0x65D1060606FF1BD8ULL, 
            0x95AD647867647E3AULL, 0x1A8BC2AA0CDF6424ULL, 0x0201919B0A13ACFEULL, 0x646FFC51F129E6A4ULL, 
            0x350DF85E13976308ULL, 0xA9B579785EAB623DULL, 0x35A932244E2C5559ULL, 0x4D817CB1DA386D6AULL, 
            0x1189B44C1250AA7AULL, 0x69082DE31BAD8DA2ULL, 0x6B8634E62AA11A2BULL, 0xC293C6A2FC678A58ULL, 
            0x5774D87CC0D1107AULL, 0xE9740C5BD2143D9AULL, 0x0A14A0330644BA4FULL, 0x1FBE2FE3C8B07A4BULL
        },
        {
            0xB108AB827220019EULL, 0x135300A2BD120870ULL, 0x1E7B521AFFAD0BF1ULL, 0x0DF23BA723B8C6A8ULL, 
            0x0F7EC9B6E0CC4CCEULL, 0xC5604E7CA24EFA2DULL, 0xF06FEB010ED9D79CULL, 0x466E92BE96C7A3C0ULL, 
            0x3594D96D558F4124ULL, 0x016CA00204D433AEULL, 0xA2B1FF3099703460ULL, 0xD0D66A4E26F180ADULL, 
            0x1AB74CDF749AEC87ULL, 0x01B14365BCB43027ULL, 0xFD2864C803797923ULL, 0xE4088211DE8200FAULL, 
            0x087B04752C93591CULL, 0x223FF1D2A21FDCC3ULL, 0x891C7DF191BB3F1DULL, 0x76017BD5AFA988D4ULL, 
            0xA913147D4CC32905ULL, 0xAA0BA084E730CAF2ULL, 0x4B2D8AC27041FE1DULL, 0xF0BEB83BA8693BB0ULL, 
            0xC9902F7B6CEE6974ULL, 0xEBABE5E0BF77EE3BULL, 0xEEB2FAC62A503C0FULL, 0x8922C780C42A5904ULL, 
            0x65380058D82ED79BULL, 0x7B362FC845B1199AULL, 0x234372CBC7DA7897ULL, 0x575E9BC668A2A59FULL
        },
        {
            0xD2D45C47E2E27701ULL, 0x97D7C6C631F580E7ULL, 0xE7316C78993FF9BAULL, 0x37BA68C54477A3E0ULL, 
            0x974774B7A2ACEF77ULL, 0x50AB6035702E797AULL, 0x0BD8273892792375ULL, 0x56B8D5DB4340CBBAULL, 
            0xD123A4A9E17A1C38ULL, 0xF71394FB5B976F28ULL, 0x94AFEA2C24B41544ULL, 0x5BE3DE2892588160ULL, 
            0x88AE96C4E164176FULL, 0x07CBC7F4355D93E7ULL, 0xC0BC1E62CA0B7738ULL, 0x8DB959FA59097D15ULL, 
            0x4EE2892B85C6DC24ULL, 0x9A145E1C5F10F2D4ULL, 0x873206A429CF186BULL, 0xB16B0EB65AEBAC55ULL, 
            0x79D393308B8F890BULL, 0xCB90DD0ABF2116ADULL, 0xCBAAC803834A716CULL, 0x81D56064034451D6ULL, 
            0x36A2751EBC921393ULL, 0xDE6F9998669C1757ULL, 0x748AB28C69C2E0DBULL, 0xE99BC2171F11AFC7ULL, 
            0xE3DEDD8AEFE52DDCULL, 0xDF1AB03074BAEAD1ULL, 0xA253CCE86906F3C7ULL, 0xD9CAD593A971F7A0ULL
        },
        {
            0xF9F68E0C0A0C4B46ULL, 0x0802DDA1A1AFDCB6ULL, 0x638AE53D65BC3561ULL, 0xFD8029401E82ED56ULL, 
            0xEC79D4DB7C3D0A22ULL, 0x97C7A5C86301F70FULL, 0x3C459FBB9334C14BULL, 0x1E729E5DB34E155CULL, 
            0x5D3F2D7667300CBEULL, 0x472A28AC140E7C50ULL, 0x2DA213A4F7F1DA6BULL, 0x76F3E3C0D08D21B8ULL, 
            0x3044D087F34DB8B1ULL, 0x925D013ACBABA8BFULL, 0x6878A27CD6D28B1BULL, 0x46EC077D6E776446ULL, 
            0xA98B2388CBFCEF0AULL, 0x2FF0FA1545C6CD0BULL, 0xA3E85759705CA6A3ULL, 0x35C5A98435944B65ULL, 
            0xE37D80567DA9BC50ULL, 0x766A6E9744C88DC9ULL, 0x6EBF05CC7316D17AULL, 0xAD18536136C8000FULL, 
            0x61A69655BE809A33ULL, 0x484C2081D7E14525ULL, 0x44B1348103ED4CFCULL, 0x8F95E97C30E18132ULL, 
            0x3B9CF0F9277D07F8ULL, 0x45EBFBB6436E24B2ULL, 0x698F48D374F2A486ULL, 0x90078C90FD177992ULL
        }
    },
    {
        {
            0x38E6E25282D2C9E9ULL, 0x91A6EE92063731CDULL, 0xC687F3C18DB7104CULL, 0xC98DD0DEAFFCFFD6ULL, 
            0xB02FF5D1E5603C66ULL, 0xF03A75AE00E4D8D1ULL, 0x2AA213D0893D9F15ULL, 0x7F46F68B40E77BCDULL, 
            0x3920A12E8B498752ULL, 0xAE0E66C102DCAA61ULL, 0x1713FBCEB3F62B46ULL, 0x96C059F9E037C39DULL, 
            0xAC163998BF007E7EULL, 0x77FAC65FB2EF6DBAULL, 0x51680D204B6B05C9ULL, 0xFC83877DADF99EC2ULL, 
            0xAFB384D499956713ULL, 0x9C1BA4E0F60D8DBEULL, 0xDA436E9A57D7BFE0ULL, 0xD1CC71C1081ED57AULL, 
            0x651451F927AD7C4FULL, 0x5889BA661A935B42ULL, 0x28249F898E02888CULL, 0x75B77BF9F99BB885ULL, 
            0x2443F6ACCAD09899ULL, 0xAF5FCF907E9A971CULL, 0x085BD3778429A73CULL, 0x7BA6A347E42247ABULL, 
            0x523F729F48F969B3ULL, 0x0952FD561301C966ULL, 0x805667A1847C2264ULL, 0x67CDECCF9BA2B096ULL
        },
        {
            0x868DB2918DCC16A6ULL, 0x01B11FDD2D77134DULL, 0xF5066E31CA8F743BULL, 0xBBD511C36EE9029FULL, 
            0xE0BB453A2BDDAF34ULL, 0xA083A0368AFDE6C6ULL, 0xBCFD299156AD3EF5ULL, 0x5103BE90660C352AULL, 
            0x998AC84A4B5D5F03ULL, 0xA1D86BFCDAFF5D9BULL, 0x8F9C7CE677922C68ULL, 0x18FC10DE32C36095ULL, 
            0xBD80B2835B88256EULL, 0xF6DBEA6D3C6D5B38ULL, 0x1B6C92C8617040FCULL, 0x23743597FA2CC281ULL, 
            0x530C46D59E83846FULL, 0xFDF2587562A71E57ULL, 0x950512E9F28680D6ULL, 0xD0B893224C668E27ULL, 
            0x31C008A8A34B4933ULL, 0xB115DEEFFF6E4D82ULL, 0xAAC0B5BFCA47E9E8ULL, 0x577D00E3D0A78F1FULL, 
            0x7CA53F1321C9461CULL, 0x02BCC8DA62E29499ULL, 0xDDC42B71B8258F73ULL, 0x3570E3EED070F5ECULL, 
            0x025E76C4C07DD585ULL, 0x7D355B37275D3739ULL, 0x405DDBDDA8C365FCULL, 0xA36D98E2522599C9ULL
        },
        {
            0x2852EA6594B87E8FULL, 0x51BDEBE0F4390BBCULL, 0x733B8DD9A6C2FFB0ULL, 0x6603001F7F316E77ULL, 
            0xA774C1EECE2D41B6ULL, 0xB9AC7F29829527E4ULL, 0x60662844A0164004ULL, 0xDF83A7C8EAD2B175ULL, 
            0x7ABEEC7CA2EC8E25ULL, 0x69C2B3DF6C9AD009ULL, 0x98A30C7B0E31C7C9ULL, 0x74BBCE7C9EDACE1DULL, 
            0xB2BC7BC92CA122B0ULL, 0x0F58583F5F5657E4ULL, 0xE3E47BDA7D05CB7EULL, 0x41A706FC72F7FF15ULL, 
            0x41B0EF2DC7FC6741ULL, 0xCD204A1A4368DADCULL, 0xFB95D2BCA6488369ULL, 0xEF95452907E7336BULL, 
            0x5D85FD1BD8F351F4ULL, 0x352E15BF8C1AC05EULL, 0x16C17FD4598549ABULL, 0x4182B91478B4F675ULL, 
            0xF4A93589A1B943DFULL, 0xEAC20785C7D03619ULL, 0x11B1C38CE7D6A7ADULL, 0xE001E84A03054A7AULL, 
            0xBB8F279D2F053A77ULL, 0x47FEBA96F10C0E52ULL, 0xF2E7D1DFDA11E890ULL, 0xF7E8D48973D76159ULL
        },
        {
            0x137B232CEFCFD0AEULL, 0xD614380B888FCF75ULL, 0x3FB082D143F114CFULL, 0x72472299055EB64DULL, 
            0xA2A0D0B90A539CFBULL, 0x7B32EF985163D715ULL, 0x3EF22784917D1B5AULL, 0xF073F044396C7A6AULL, 
            0x5A888D53732741BFULL, 0x61159420CA5B05A2ULL, 0x0D9453F57542A0C8ULL, 0x12C465619EB7DF8CULL, 
            0xBBB55BC8E38CF20AULL, 0x404A74B1DF4C5211ULL, 0x6024D9B8D7C008EEULL, 0xE0577C7A810D6920ULL, 
            0xCC4DBDD4635FADAEULL, 0xD84F06FE7FF33217ULL, 0x16C532080729AFA5ULL, 0x7EB63F76DE02D522ULL, 
            0xE49EE5844C7A4CCDULL, 0x9765E907421A0F80ULL, 0x62A1A3B94B960DD6ULL, 0x37C871FAC7288B60ULL, 
            0x7EA1364915DD9EE3ULL, 0x324D158F270D6037ULL, 0x207BCAE899EFD8D0ULL, 0x2027A3F2DC2F3628ULL, 
            0x267938265367A8E7ULL, 0x737B0428225818C9ULL, 0xEC3D1FC06751810BULL, 0x4BD82CDF62CB45DAULL
        },
        {
            0xB6CDED0AE99C13F2ULL, 0x0CA107233ED216D3ULL, 0x7EBE7640BFE49B89ULL, 0xB4942825E41A868FULL, 
            0x215DD217A8B0394BULL, 0xD091B9A5A0D3564FULL, 0x2A33DB8DAD480D8DULL, 0xF394ADA8FB82784BULL, 
            0x7A9A2F2D507B9C30ULL, 0x4113C7F7257CADC3ULL, 0xCEAA4525F5EF168EULL, 0x790B8CFBF3E4D441ULL, 
            0x52F9EEBA48A41E7BULL, 0x1F5CDFF6FA354DC4ULL, 0x1894DB10E55FD154ULL, 0x7D4B58CEFB1DB628ULL, 
            0x5AD03359B192F4A0ULL, 0x1AC7A5DE8B83241EULL, 0x93E0BBAD27A45481ULL, 0xDC3C9A0B5BF5E473ULL, 
            0x623CBB8133125C9AULL, 0xCA46445A921D64BCULL, 0xAC9756E824047EB3ULL, 0x9ABB141FFCF7F27AULL, 
            0xE1C492B88564C207ULL, 0x9034124800981174ULL, 0xD3B0A2488D76EAB3ULL, 0x6F1E262434BD32FBULL, 
            0x315E555191A80713ULL, 0x08669253AD9A9F48ULL, 0xBB35E37800CA9EB1ULL, 0x3321EB1AC0AA76D0ULL
        },
        {
            0xF5DFDB5F9B99C4DFULL, 0xF33EA08BD33A08FEULL, 0x767937AB337BE762ULL, 0xC49A16BD7D41165BULL, 
            0x060D56B2B8550F31ULL, 0xB45635B7B2A90CCBULL, 0x139C1A028D21F89BULL, 0x641212B5F59553B2ULL, 
            0x2279178FC6D912C9ULL, 0x390795B77788DCA2ULL, 0x5434E8836116979AULL, 0x723EE6CB38A85A12ULL, 
            0xAA79DFA5C4A0B0A8ULL, 0x0B8B20F2AC79C958ULL, 0xB6887A3B2A832738ULL, 0xBF5201E8313674F2ULL, 
            0x12165821C366A678ULL, 0xC098C8C05F2E85B7ULL, 0xF965C6A8F2CFC065ULL, 0xF21A3CF50BE58FE4ULL, 
            0xF4AB227769B37A20ULL, 0xEC61B3DD7CB74514ULL, 0x9CD8E24D356D72C6ULL, 0x81F956AC9DCE8A2CULL, 
            0x52CEBF419029054BULL, 0x25D6D8C15DF7E197ULL, 0x48FA2BBC14F83FEEULL, 0xDD101C643CC852A6ULL, 
            0xCFB084163798C0F5ULL, 0x7C4D3272F56C7246ULL, 0x9328C515F58930D5ULL, 0x79C721156AD1FD3EULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alnitak::kPhaseFConstants = {
    0x2A4A3B39ACDD17A5ULL,
    0x31F5B12D3CE93B0FULL,
    0x2E466E9C244777CCULL,
    0x2A4A3B39ACDD17A5ULL,
    0x31F5B12D3CE93B0FULL,
    0x2E466E9C244777CCULL,
    0xC9F37DC1DCBBB46EULL,
    0x98B04983050976A6ULL,
    0xD6,
    0xD0,
    0xBC,
    0x10,
    0x38,
    0x35,
    0x0C,
    0x98
};

const TwistDomainSaltSet TwistExpander_Alnitak::kPhaseGSalts = {
    {
        {
            0xDF4B676148000868ULL, 0x82018B3A7F694920ULL, 0x938C52B0748E13E9ULL, 0xE0660D4685BEFEBBULL, 
            0x54611105E828FC02ULL, 0xFCDA3CA1F07D9591ULL, 0xFAE5BE1156638F8AULL, 0x6CA473AC6683ED0FULL, 
            0x74ABFFB5F55C2742ULL, 0x12C7D98E5E4FF54DULL, 0x4AE33CABFA4A15D2ULL, 0x6AC72E7DA7DA2BA4ULL, 
            0xF46983DA67683A64ULL, 0x3FF6C16F5129FF74ULL, 0x0B5914A3E6FAA3B2ULL, 0x04AD706E40AD442AULL, 
            0xEDE79B150A65D798ULL, 0x152B251864928594ULL, 0x597DCEEF1A86E7D3ULL, 0x413198F814ECADF6ULL, 
            0x7F3AD7AE517B5245ULL, 0x10A3FCBA304B9E85ULL, 0x592A442A315B7E6FULL, 0x25AD9AD89F484CCFULL, 
            0x0CB9C775F18F4D62ULL, 0xA73ED39C15106C85ULL, 0x9670EE6DA862E3C0ULL, 0x575858592333986BULL, 
            0x71E15E22D3D02669ULL, 0xE0575774D00BC8E1ULL, 0xC845148ED9A99148ULL, 0xCDAA86B87DDD2502ULL
        },
        {
            0x7363A969F0BFBEADULL, 0x851D5E8D3433BE8FULL, 0xDFC8F806D8B3DD4CULL, 0x661B0855C461B59DULL, 
            0x79359388BF0BB7BCULL, 0x75A1EAAEA1BBA0DFULL, 0x298A7CAA560D1BB0ULL, 0x07024734C82180DFULL, 
            0x2F0654895ADCC4A5ULL, 0xA459D3E0A5E2C9DEULL, 0x011DFD4A1D8E8E95ULL, 0x4A45D5F6175D81DDULL, 
            0x1B91DF8133906F18ULL, 0xD850D09BDEE02830ULL, 0xD4251309A4A23AC2ULL, 0x2363477454CE5712ULL, 
            0x477B247FF36DE18FULL, 0x08F964CD613E5B99ULL, 0x7107880E9B8F4995ULL, 0x1D162D096B078D4BULL, 
            0x9ED6D2634FE00D75ULL, 0xC7A47427E373AAF0ULL, 0xF3FB74A0CE28CF11ULL, 0xCF66EE7C4B5C51F0ULL, 
            0x461A6347FA57E197ULL, 0xA280D59894889237ULL, 0x503A846B5FB0AA25ULL, 0xB041E53CB1E0EB09ULL, 
            0xF1E7ED2C8DCCA7FFULL, 0x51A69F4391E0EEFBULL, 0xACAEDC69CE2A21DFULL, 0x8D8C0281FCF03FCEULL
        },
        {
            0xABB7E1BC2B9276B6ULL, 0x836361B340C4771CULL, 0x38ABDDBAD93A5B7CULL, 0xE6EC152F45685978ULL, 
            0x01EE1B00D9613DD8ULL, 0x5BE95AAD3EDD31F7ULL, 0x7E546F853CF86854ULL, 0xD2AF9CC1204E34B8ULL, 
            0xC88351FE1EDFED64ULL, 0x1AE5CA319086F98DULL, 0x8030965923666FE4ULL, 0x43B0C5627F315584ULL, 
            0x050A5DF70E34B965ULL, 0xCF76FC6759BE65D5ULL, 0x9899F650DEDF54F9ULL, 0xD2A349D93FB17F83ULL, 
            0x46416D199E14149EULL, 0xFE0B8659B553BE6BULL, 0xF1A10609D57FCFCAULL, 0xC6825A0C543881ABULL, 
            0x34F08E424923CE66ULL, 0xCFAE7E198137B7CCULL, 0xB3B6B5AC8B697B6DULL, 0x9492E1F1F4AEA14EULL, 
            0x0B3925681E4CCFB5ULL, 0xA82642A4FF995A60ULL, 0xF86F16E59DD0F30DULL, 0x345469BBB81837CFULL, 
            0xE82BCB0E2296B78BULL, 0x1870DDC58172E1C3ULL, 0x5153305E8F55A3FAULL, 0x5848A04891F9B843ULL
        },
        {
            0xAC156393141C8240ULL, 0xD4BA517F41C044B7ULL, 0x73F4FD094D49ACA5ULL, 0xCB897556B16CFBEAULL, 
            0x0D27E7F6CD594839ULL, 0xBA498D1847215435ULL, 0xE64EB99406C7FAAEULL, 0x1B9418B6D8814B71ULL, 
            0x22BCB8B3945AA04FULL, 0x906A94F929E88011ULL, 0x9047664239860F60ULL, 0x47AE97426D9DA2DCULL, 
            0x67D63064A63DC856ULL, 0xC3E95AB23D10168FULL, 0x34FD297C0C9F873AULL, 0xFD5D2789DD7F4A4AULL, 
            0xF071DA0CB00F37A4ULL, 0xB935690B5134AF3BULL, 0xA67AE0BCD2170D5FULL, 0x8E958DF65015F795ULL, 
            0x040659762CE6FE8BULL, 0x3125556DBFA0BCD8ULL, 0x8D5C221E0CA4C113ULL, 0xD06BB48289A7DAD8ULL, 
            0x043AB5BEB556E9A0ULL, 0xCBFCE18042C70E10ULL, 0x2EEC689D7755F3E2ULL, 0x9B486E9F6A9B2BC1ULL, 
            0x601FA0B12CEE4C05ULL, 0x87FA485823C3388BULL, 0x0E3433A35378A9DDULL, 0x62365FE2DFFAFFE6ULL
        },
        {
            0xC9F3B0F93A85654FULL, 0x927959781537E9F5ULL, 0x9A87E85E588C478CULL, 0x4D1870C175899467ULL, 
            0x27369C320D8112A4ULL, 0xF4B36B016BB5C6F5ULL, 0x826EEDFD82FDF80EULL, 0xD84C99602A93D763ULL, 
            0x5DA83FAFCC899124ULL, 0xF4805F151DA4504CULL, 0x91D34697C8AE8584ULL, 0x7137FBD139B06234ULL, 
            0x4D94C1BBFA36054DULL, 0xA09B553349845153ULL, 0xE3E6AD34BE1E956BULL, 0xBA5208AA5A87CF4BULL, 
            0x1F0112B7B68DCC49ULL, 0x37CE0C2C841153CAULL, 0x37C6032C7746E623ULL, 0xB2CA39D980881544ULL, 
            0x848FFA1588962317ULL, 0x8D1685C7BA467890ULL, 0xDBBC0AB0B5392966ULL, 0x37C95B8C07D72E65ULL, 
            0xC2CCF38816990DF0ULL, 0xB94CBF593AE90771ULL, 0xBD2C1B8D77991BBCULL, 0xBA4992148BBD7F1BULL, 
            0xE1939FEBD3ABC58EULL, 0xE23A86D3733E5053ULL, 0x55BE96036D76937FULL, 0x685A5982B3A2A0EBULL
        },
        {
            0xCEC88F8005BA55E3ULL, 0x6AB9404DDCB804CBULL, 0x5546D930B3955E29ULL, 0x305433B0F7588D32ULL, 
            0x0C7963C519A69CF0ULL, 0x510E49E8106064A8ULL, 0xC8C79FE1C5E9D1AAULL, 0xF7CECA2588BDED7BULL, 
            0xB7E74EFB4E73B56FULL, 0xF19B92BE746ECE85ULL, 0x961AF95E519E8068ULL, 0xADBD07E8209EB147ULL, 
            0xC2FAEC569690A7A7ULL, 0x1850D8A989B02F7DULL, 0x61661546C76DD62CULL, 0xEA8547CE2493A9AFULL, 
            0xCDE797F366D07184ULL, 0x77543479F9564EC7ULL, 0xF0F38D1E6D792FB5ULL, 0x5749C10664CA50D8ULL, 
            0xCB7CC3D03877A556ULL, 0x46E115616BD53603ULL, 0xC010976589507452ULL, 0x78619A91E71604E9ULL, 
            0x635972F96D45B443ULL, 0x022CCA041CC3466FULL, 0xCF5D7A38A37EF13AULL, 0xA73A49CD8F700C71ULL, 
            0xD05725185BD0486FULL, 0x9C3C8ACC29006A3AULL, 0xA0913A5FC5225DB0ULL, 0x342DF58500820513ULL
        }
    },
    {
        {
            0xF66EAE258B9CCB94ULL, 0xC4B247F6AF9BF66DULL, 0xE138265224A17126ULL, 0x65A598F8F939CC7EULL, 
            0xF8695EEA9F9C6FA1ULL, 0x8EC0644843D7FDA4ULL, 0x97F7052753EB76ACULL, 0x0A3B4289A432FC64ULL, 
            0x4DAC6F6FA9458BACULL, 0x009AA6A33D12444BULL, 0xC8376837E4A025A7ULL, 0x1D1D8475E9821E92ULL, 
            0xABBAFE7C9EC15DFFULL, 0x2C9A716056E6F3BAULL, 0x29A8D1EB9223C2AFULL, 0x2A53958FF2C824F1ULL, 
            0x65F3659F660BB51AULL, 0x3620E4AAB3A3CE7EULL, 0x8C5905DFCB9EAECBULL, 0x5606447A2E42E3D4ULL, 
            0x112630F74CF6682AULL, 0xF0C709E453A2CE95ULL, 0x73E34085C8C6D864ULL, 0xD0F553B207849F12ULL, 
            0x42BFD27D8E713C35ULL, 0x4C9D0B27B75F2AE8ULL, 0x0D3E22301DFFAEF1ULL, 0x4C95BCF12383DBE1ULL, 
            0xEF516B59C1F81EE0ULL, 0x2D2AD8F0161AF505ULL, 0xA84486E317853069ULL, 0x881D566BA20743CAULL
        },
        {
            0x3AEE645E5417D336ULL, 0x4B3368E6A3014E14ULL, 0x9D5065518AD1E15EULL, 0x0E998819B0CBC536ULL, 
            0x5BCBF60B1131E957ULL, 0xD8EFF48CA1C6B553ULL, 0x25FD0FA426FE5418ULL, 0x5CA3D0B441AD6712ULL, 
            0x22AF04FA66D27117ULL, 0xC34D20D42582C843ULL, 0x591F67B4F2C54305ULL, 0x6FB65A0D9D3A84ECULL, 
            0xA39D29F72CF0A7A4ULL, 0xC49C13B2BC62BEB6ULL, 0x10D5F39E2848FF3BULL, 0xD7B0F89EC857F130ULL, 
            0x61BE118BFF604F3EULL, 0x38079EE9A0FC7EF7ULL, 0xB23233C07087A42AULL, 0xDC7E95E2A05E5D65ULL, 
            0xB704833055A60E87ULL, 0x0A1EA8001C42D2B9ULL, 0x4AC913281587B2F9ULL, 0x84B528AA5A6A2969ULL, 
            0xE4897B3EE903A7A3ULL, 0x83CE902F0EDFA5C7ULL, 0xFD9E74F139ABCDC6ULL, 0x4CB786BE83704D3CULL, 
            0x11A60CF311DA0699ULL, 0x3CDFA86CB5C229B6ULL, 0x90EADE907E82B7B6ULL, 0x1B4E88C7138BF4AFULL
        },
        {
            0xA7ED8DFFFEB3D5E1ULL, 0xD11E271F709A8221ULL, 0xE43F8B554EB62F40ULL, 0x2A0D247E72BDA29DULL, 
            0x32FE01CBF21EBC37ULL, 0x7BE197D62576E3AEULL, 0x647B7B32CC959852ULL, 0x1828113C9CD3C4DFULL, 
            0x5EC2D94F2C0AAD98ULL, 0xFCDF97B8BE2793ADULL, 0x22F66D03C355BD83ULL, 0x5E48AF5B8B9866CAULL, 
            0xDA82F4D2F8788048ULL, 0x72643DAF398CDDD0ULL, 0x40E0AF0F1112585CULL, 0x1017DC183EEEE5C1ULL, 
            0xD3725A6CBAB6652AULL, 0x2C88B3D52A823EFFULL, 0x5AD795DB6019AAD9ULL, 0x94604BBD0E09FD80ULL, 
            0x3A6110379C93C694ULL, 0x4D05106B7A406174ULL, 0xA92357784753730EULL, 0x7F5CD13F0C38FADEULL, 
            0xE49D8C092C4959E0ULL, 0xD45BBAFA823F0FE1ULL, 0xD1D550F86339B02CULL, 0x6EFB352B0C948707ULL, 
            0x58C029827851F70CULL, 0x57DB4942F64E2B57ULL, 0x5102D0635B9DFF0BULL, 0xEDB26A0174C2EC8FULL
        },
        {
            0x33221EBA3928E21DULL, 0x5CF390E209558E7BULL, 0x3EE9F5B790C0ABDDULL, 0x4B8C554006986804ULL, 
            0x006FC77E9E2A83F3ULL, 0xD1FB5018D5C8B4F3ULL, 0x5D1994071D627A25ULL, 0x0020416AFCE9DBA6ULL, 
            0xC3E276C22283664EULL, 0xFC0123C749578E65ULL, 0x3E5CFC012A5E3F77ULL, 0xBCFE84EA03B5C9B8ULL, 
            0x02FED6D641D3CE30ULL, 0x5844CC50C986B4AFULL, 0x65DCE86F9106ED29ULL, 0x9175AAF10F4846D7ULL, 
            0x06F75BC1DB13A4AAULL, 0x5FE924D7A9B0733CULL, 0xE44493DA919FDCB6ULL, 0x8F3B975EBF6BCB31ULL, 
            0x6F4460DD664231A7ULL, 0x3BF83BCBA03DDDEAULL, 0x0610DE58980CEAB2ULL, 0x585677943698BB5EULL, 
            0x5F1B91718E4248B0ULL, 0xA5A2581CB46A6082ULL, 0x1AC944AFE928DC03ULL, 0xAD4B139CE3F4D280ULL, 
            0x13D08F7E19133FBCULL, 0x7FAE58E22716C489ULL, 0xDA88E05BBCC2D184ULL, 0x059ABB2EEFF32BADULL
        },
        {
            0xB6DCE07F4E78163BULL, 0x66F356639519E00EULL, 0x02E66755F7DADF15ULL, 0xF11E667DE07CA1A9ULL, 
            0x88DA84E87A23506FULL, 0x03919B7333E1A9DBULL, 0x12575CD219FF6DB0ULL, 0xA48FADD7E68CDCB0ULL, 
            0x1DB587043A0E37D7ULL, 0x282E647B9BAAF0D4ULL, 0x5B247D38680F578FULL, 0x812952CD34A2EE18ULL, 
            0x5ADC0AA1B4060818ULL, 0x57347A015261651DULL, 0xA4C4CCBB45855086ULL, 0xD4F7A3BE311B1C02ULL, 
            0xEBBC59FA68108A9AULL, 0xF6AD390FC5AA4D23ULL, 0x67693F776A922D09ULL, 0x471B538B603CE847ULL, 
            0xD641FDFB56052568ULL, 0xC35A5A215C13345FULL, 0xF2A94677D1E945F8ULL, 0xF260E3EA96C83BDEULL, 
            0x93DB93C789A0919CULL, 0x0760B513250CFAF5ULL, 0xE3F198896BD0E278ULL, 0xC4062EB62226C06CULL, 
            0xB8E0A7C0141C2C29ULL, 0xC752911C5B5FCA9DULL, 0x9486B245D2861770ULL, 0x11C2B1ACF8C2E9CAULL
        },
        {
            0x484444BBA8944A98ULL, 0x7E0F1105B2072736ULL, 0xCC8EDDDC084069ADULL, 0xC253034E952A7635ULL, 
            0x58C04E201E677700ULL, 0x5693F0E5EE89A579ULL, 0xEC5F1F5E64454C5CULL, 0x63EFBFAAC878972DULL, 
            0x728F6247CF6465CBULL, 0xA2D8BEF91092C60BULL, 0x0FAE50A5E8FD15DBULL, 0xA067C2AC988C9CF1ULL, 
            0x89AE6907044CFE03ULL, 0x01D86FFCCE2EE1C9ULL, 0x0381351D32B51682ULL, 0xFA39FE866CC13618ULL, 
            0xC8D55E4538EBDFF4ULL, 0x1065FF32BFC72C89ULL, 0xAAFD26E4803DD5F0ULL, 0xB90463AAFD70E1DCULL, 
            0x5DD983EDBDA86016ULL, 0x45B0B43FAA649258ULL, 0x944F0EC9C4BDB908ULL, 0x2708BFCDEBD2C8D1ULL, 
            0x6A11600A5BA9899DULL, 0xA87A1A35F429CB31ULL, 0xD1E9946CA6F94556ULL, 0xB0A56C9B0BB62246ULL, 
            0xAF89C9AAD6A7D75CULL, 0x5F983F8B560453B6ULL, 0x2BB831B8E52797ACULL, 0x9317B8B693E7B742ULL
        }
    },
    {
        {
            0x9C479CDA11F9D311ULL, 0x1EBC3FA2845FFFA0ULL, 0xACA37B147A0BBF6DULL, 0x76C5A9976039754BULL, 
            0x6C3A4247CF4729D3ULL, 0x2786EC7D7F0BC65CULL, 0x93365BA3F57B81F6ULL, 0x62E96E587E34F058ULL, 
            0xFE47BC83BE03EEAFULL, 0x9C6604FB0D489054ULL, 0x8A2D1FF86965182AULL, 0x40728377A060D947ULL, 
            0x894308057915E5A3ULL, 0xA0ADDB3DF222EB3AULL, 0x748C35B573FB8865ULL, 0x85FEA329EEA8F8E1ULL, 
            0x765A0ECE79E33B97ULL, 0x2A8559705A22756EULL, 0xD95F62964A350B34ULL, 0xB3A6D5AFE7AA5AFFULL, 
            0x1094A8605AC4F427ULL, 0x4A1A7A66EAD33E64ULL, 0x2EED2C1346B7B9AAULL, 0x2F38F3EE3664DCC3ULL, 
            0xF5FD4A8689D98E5DULL, 0x29212FAA7C912F4DULL, 0xD74F6B32DFC1E169ULL, 0x05877FC619B77347ULL, 
            0x94B76A067FD0B3B4ULL, 0x8F87C1E632E1B9DBULL, 0x364179BD6FDEA53EULL, 0x7167A195CCFE6645ULL
        },
        {
            0x9174212836DD33A5ULL, 0xBE9ADC7AEBF64152ULL, 0x62FD201E0744A9E3ULL, 0x869A3706637841DAULL, 
            0x6AFB13D57294B3B9ULL, 0xB6247FBAA8A20070ULL, 0xC40CC41EE8626EA1ULL, 0xC124F91C36ED4704ULL, 
            0x1B77850E9C26DA0FULL, 0x9D7EB725FDF57BECULL, 0x0686DB14BD2ABEC0ULL, 0xFDC698DFD0CD29E3ULL, 
            0x932AD994F6884FD5ULL, 0x9ED8F70846090880ULL, 0x1500A3FBCDA56AA0ULL, 0x8FE0EA3C91EE036EULL, 
            0xAFAF970ECEEB72CDULL, 0x70726E39697D3FABULL, 0x89F05DDB212C47CEULL, 0x741214808D97DC6CULL, 
            0x9E9656EC646BF278ULL, 0x195BD1151847883CULL, 0x58D9486BA087FC72ULL, 0x7B831E3D104CDC63ULL, 
            0x932CD8FB86412206ULL, 0x2D24393B00395C6CULL, 0x1FDD4464E323B728ULL, 0x79E6B2B6F46AA291ULL, 
            0x499D366965D8F7D6ULL, 0xBAF09F82121E5FA9ULL, 0x852F0AF7AA33010BULL, 0xF4C8320DB7D1222AULL
        },
        {
            0x348AE285A8B0B255ULL, 0xCF78D49AB94A85DCULL, 0xB93382D58914C250ULL, 0x6ECF941F43B9CE1EULL, 
            0x39E2231165BAD03BULL, 0x67D778B14402DB1CULL, 0x47076EF1A31CBF8BULL, 0xE23EBF1AA8BA2F64ULL, 
            0x375DD642AD7B6344ULL, 0x92D14979E6A8A667ULL, 0x978E56F15E32249FULL, 0xA5D3E4F09DAE5AC6ULL, 
            0xBDF18993881E4E07ULL, 0x6523DB7434642564ULL, 0xC5CD182BE97F9CECULL, 0x7237BB15FF78A094ULL, 
            0xFD3C4AFCA742966AULL, 0xA07DC64655236213ULL, 0xBFE1133D94E1B526ULL, 0x1282E2B0A57E9D42ULL, 
            0x66AE38F0A36F7045ULL, 0x5499C94C71A064B5ULL, 0x3BF8DEDEE812C5DEULL, 0x0F8AF606458A9879ULL, 
            0x3FF55B992A462B1AULL, 0x9C11362C1C7526BCULL, 0x104F5F616B617B4EULL, 0x89892C00695F1AF1ULL, 
            0x66C8483E5C4603D0ULL, 0x499C744B8EC0A556ULL, 0x43944E7E82872ADCULL, 0x439D6B870EF813BDULL
        },
        {
            0x730505E2B5EDF72FULL, 0x0C2150A58B4B3DDDULL, 0xE1183C5A64704024ULL, 0x25D6F98DF0A48144ULL, 
            0x80DF3249F9FEC99EULL, 0x9323885A4B1103FBULL, 0x07889DE24EDBC6E1ULL, 0xEBCD66CAB5CD215BULL, 
            0xE8F3619DBDBA3A43ULL, 0x4B4804CF67023D1DULL, 0xB8AC41F34F05BA6DULL, 0x6F24B5FB1B92B870ULL, 
            0xA692186DC94BCA28ULL, 0x0756F8A3525FC4B2ULL, 0x7934DC04CED1A940ULL, 0xFCECC80DE99A2D59ULL, 
            0x7D5E1ED242203D30ULL, 0xE891C736B7BF9398ULL, 0x5F7F86C1E8C3F25AULL, 0x52E637C744B601AFULL, 
            0x6A5691FB05FAD958ULL, 0xBF3749A0EFBE70BEULL, 0xECB79AB5903CB45FULL, 0x78CEA9C436F95D62ULL, 
            0xB86B1DEA61A7D1B9ULL, 0x2712373D4FF8EEEAULL, 0x65E0D40CC81FD19CULL, 0xCF53B52BF3F7E54DULL, 
            0x43CE69539520EC67ULL, 0x4254535FC326E6C6ULL, 0x2198E7AFF0EDA724ULL, 0x9B68A110E2198C37ULL
        },
        {
            0xF4F84D651C71B3AAULL, 0xDC5B1017E78C241DULL, 0x59E1C9CB5D96D88CULL, 0xC8A6B8571AB9557AULL, 
            0xC76CB43BC2E92AE3ULL, 0xB5FEFCD12745BA82ULL, 0x9FA2C6BAB2EDA21EULL, 0x5DD96D996789381CULL, 
            0x7D31152C50EB3B5BULL, 0xAA91D0A24C2BED3AULL, 0xD7D5AFC042CC85F6ULL, 0x9D564C166604FB5AULL, 
            0xB12D0C68E4F5881DULL, 0x947195E1D0A0E76BULL, 0x99AE38E8AE5E6CB9ULL, 0xBFEAFCE38E1D4653ULL, 
            0xFEB6321BBA966662ULL, 0x00B9AA3CDDD9E93EULL, 0xC60C097CBC97AE5EULL, 0x6AA8133017466EA9ULL, 
            0x37C9F9DDDE1DB7B2ULL, 0x7CA3F024ABB27E17ULL, 0xD717635628DBE212ULL, 0x219CCCCF122B5152ULL, 
            0xA41EB729E3E61DEFULL, 0xCF6FD42E0592FC0AULL, 0x92BA6F9CCAF8C361ULL, 0x9237694CECE1DB72ULL, 
            0x7813FF80E6646A70ULL, 0xAD056554192987A2ULL, 0x29D6D37ADFACBEBEULL, 0x88B4F3549FE5AEC3ULL
        },
        {
            0x94956D9535EFEB40ULL, 0x712D2873540B70A8ULL, 0xF3B1941244CA4686ULL, 0x746F51EA1C6B4909ULL, 
            0x397A6A2035651830ULL, 0xF2818CBB6EA57215ULL, 0xEFB24E3D9B3DC3F7ULL, 0xBBB3B6FFE49DCE76ULL, 
            0xEC3B0CD6D1B35DD2ULL, 0x2A3E34FECADD6125ULL, 0xCAEB10B6F33E00FCULL, 0xDC4186392CE6F243ULL, 
            0xD396971AD9EB2ECAULL, 0xF689B9A8DFEBDD1DULL, 0xA74C6F45897C175BULL, 0xE51FBA55DB80C203ULL, 
            0x8DCE5040BF6E7B36ULL, 0xD3F320056839FE47ULL, 0x2F7D35FE3AA03904ULL, 0x6F33B72AB1BBCC12ULL, 
            0xDBCDC2A4787A9067ULL, 0x216E3972D81891FEULL, 0x6F5C238657E44622ULL, 0xA7C516D66C29CB8CULL, 
            0x3E785F850CE7B72DULL, 0x49942C2ED36C4146ULL, 0xE1051DDAF88D8042ULL, 0x599AA0F2757E5E61ULL, 
            0x18600363B05DDB59ULL, 0x9D2B7248E8423124ULL, 0xD749340C1110389CULL, 0x2044245DFC973B1EULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alnitak::kPhaseGConstants = {
    0x89F86DAB104EA124ULL,
    0xB18AAA462890E5ADULL,
    0x79714CB5245737C3ULL,
    0x89F86DAB104EA124ULL,
    0xB18AAA462890E5ADULL,
    0x79714CB5245737C3ULL,
    0x40A2352CFE53FDF9ULL,
    0x0DC878D077771924ULL,
    0x5F,
    0x93,
    0x69,
    0xB7,
    0x0D,
    0xDF,
    0x93,
    0xD5
};

const TwistDomainSaltSet TwistExpander_Alnitak::kPhaseHSalts = {
    {
        {
            0x4ED468EC4ED5EDF0ULL, 0xDB5520BAD59D04E7ULL, 0xDFA31C5829DE6AC8ULL, 0xC3C46925D3EF89AAULL, 
            0x4DEBA2C7CCCFC836ULL, 0xC7D7B91C98B2D2D4ULL, 0x01B321CB34C96AB7ULL, 0x7E40EB2395F9144BULL, 
            0x1757514646C702E5ULL, 0x3C68104B63C334D9ULL, 0x5232675C2CCF9126ULL, 0x5B9AF6E8593F9B3AULL, 
            0xFC2FA51002F2EFAFULL, 0x31013D061A3EA599ULL, 0xF91325168E8159A1ULL, 0xBFB858FB7E512F63ULL, 
            0xF1A6B0F76803F0B5ULL, 0xD01137E27FE9C59DULL, 0xC5B6452009EA4E4FULL, 0x850795018DB776C6ULL, 
            0x571D23D797685DA9ULL, 0xB819643E546260DAULL, 0x22712E1C9DCFE326ULL, 0xCC35FE1CC1B0AAE8ULL, 
            0x0B9BA2AD7F98B362ULL, 0x46FA1C82C699012FULL, 0x3441E194E22460EFULL, 0x1E7864FB663B0A6EULL, 
            0xC30296B7338DBAD9ULL, 0x4545638249730859ULL, 0x028E28002E1EC79EULL, 0xD39D678B9C8EB423ULL
        },
        {
            0x42CDBD2181F25244ULL, 0x523A9652C430198AULL, 0xC1E98681375BE9C5ULL, 0xD71F395A6B93BFFEULL, 
            0xC059A13568713D88ULL, 0x700218BB92BA61EAULL, 0xB5A4EE85A619B8BAULL, 0x48798AC55CB1EA50ULL, 
            0x6AB20494725C826CULL, 0x7AEE5CE882201CE8ULL, 0x8C0924FDF0B027E2ULL, 0x49D1E3DD46139F16ULL, 
            0x6F6C3165E5A499BAULL, 0x7DFD92F71321B186ULL, 0xF18DFC776B4C18F9ULL, 0xEEAB967597C8A9E6ULL, 
            0x0E03C78DE39C4DA3ULL, 0xAD48110E9AB81512ULL, 0xE463DA07FE867A02ULL, 0x3E3E7D2A3FF850BCULL, 
            0xCFD13712C3623F01ULL, 0x7D9AE4A0CC362142ULL, 0x1346961BAEFA76FBULL, 0x626B8C76AFBF204AULL, 
            0x37BE8F92D6781533ULL, 0xD6E182BF6C761A7DULL, 0x37AAB6F688D23C05ULL, 0xBDD3626D62194215ULL, 
            0xAE3F9304DE597F83ULL, 0x8DC1B4AE588BFEE6ULL, 0x260282328C8C4CD4ULL, 0x909C2989E02C0500ULL
        },
        {
            0xCA227CD9E43928AEULL, 0x0502AF55FF780CCCULL, 0xBFC9BB1C80347840ULL, 0x3C2142F960F97EB6ULL, 
            0x6F9CE35862AD4A3EULL, 0xC87031931C82A022ULL, 0x66E36F42975C83E9ULL, 0xA00550747EA273F7ULL, 
            0xC17650F917F2C547ULL, 0x37AFD3BC26A6C564ULL, 0xF454267981562EF2ULL, 0xAF3665DEB1030369ULL, 
            0xBD8149B18D4549BFULL, 0x8D6D5D94477FDE7FULL, 0xA01323987FA80180ULL, 0x0903AC5728E0C2BEULL, 
            0xE548FA4A1311A9DDULL, 0x1FB6EBA1C962D4B3ULL, 0xE8157BAED1C69D53ULL, 0xA7AC2C32770BA005ULL, 
            0x700925E055454582ULL, 0xCD112E1D7B0750F4ULL, 0x3FAED8D4767B47EEULL, 0xED8A53D722C7C054ULL, 
            0x6D59A3F424A27DD8ULL, 0x649C0FB259FDCFF6ULL, 0x76B4D8F8F10ACD2AULL, 0x8998B874A1BB8A63ULL, 
            0x7F3F663553B2A6F1ULL, 0x1EFC91CC6D1FE9A9ULL, 0x36D8BB2DDA01990CULL, 0x06FBD347458B2615ULL
        },
        {
            0x066430CF4C66E2D3ULL, 0xF8D804695E36035DULL, 0x17ECEC520BEDC03DULL, 0xB5DBB38B0C43B4A9ULL, 
            0xAF525E61D9006773ULL, 0x767534BCABF09DD5ULL, 0x223D2D6F8322F65DULL, 0x61574015D37799C9ULL, 
            0x55F0B356499C7BE8ULL, 0x4BF79444F0337109ULL, 0x3BA2A7524BE43D24ULL, 0x404C39BCDBD3142BULL, 
            0xAAB539BBC7A1274EULL, 0x28F7198101C33A34ULL, 0xAA11DFD043D2A783ULL, 0xA6E4A81991189BC7ULL, 
            0x1BF39476953D60C5ULL, 0x6A676B306A3D2849ULL, 0xF557E4A3E7C2138EULL, 0x873CD6A03BDD98F2ULL, 
            0x0C37817C04734476ULL, 0x451FD803DA709319ULL, 0x9A0E07EA07AC195CULL, 0xF0FDBC9BC3B82364ULL, 
            0x352663A7D0711E7EULL, 0x9483FA025F3A7924ULL, 0x96E37FAC9F8992F8ULL, 0x624CD9017ACDD0E6ULL, 
            0xF46D9CC9D17D0D02ULL, 0xE52FA9961E37FE65ULL, 0xD7AA83A5D6A7FE94ULL, 0xE9ABA953769B58B9ULL
        },
        {
            0x21A9834D5F9122B5ULL, 0x4BD1C6CC3394D733ULL, 0x917B81D0E6F11FF4ULL, 0x34FBE2C976D9635FULL, 
            0x676326C7F6AC77F6ULL, 0x665944173F1C890AULL, 0x436038072DEE8E7DULL, 0xDB9C1CCE495258A4ULL, 
            0xD1BAECAB70F3FADBULL, 0x25AB28D0ABA879EEULL, 0xEECF1857E1D16DACULL, 0xE7A68DC145A7D98FULL, 
            0x3109F765C5EF0657ULL, 0xA695D24DFEA179BFULL, 0xB66C6AFA469A8763ULL, 0x2B4A1D06A9633A8BULL, 
            0x6A8476110E2EF1EEULL, 0x0F3FB2CE65F7D7F8ULL, 0x1826E5292F40AF47ULL, 0xFB5AFEE0EC7B3C20ULL, 
            0xD6EE47A01E7C6FF2ULL, 0xA7AEF540F173708CULL, 0x677257E6DC29C01CULL, 0xA52B2A4B9CB21E25ULL, 
            0x839D51A4C3091046ULL, 0xCB7B3C12584CFDF0ULL, 0x443F95DAE233F68BULL, 0x27B7C7F5DB17FAEEULL, 
            0x1A2752A0320862B6ULL, 0xFAFF7F6BE57E3F3DULL, 0x10B8256A447BC922ULL, 0xF21B86B197A840F0ULL
        },
        {
            0x88218443AA997D12ULL, 0x28A75D3285A91379ULL, 0x4B384AF61BD65323ULL, 0xD57A02923ABCFD98ULL, 
            0x2D0FC829A94F416DULL, 0x92169B22782C842DULL, 0x34FA624D49294F88ULL, 0x66EACAF18B5F569CULL, 
            0xB6EBABD3AB73AD73ULL, 0x3597CBAB57108CC9ULL, 0xBC1512CE4A3CAA2EULL, 0xD7139CCBC94836A7ULL, 
            0x8BE9E81B15D5486AULL, 0xC21B9F8AB41A3C9BULL, 0xF77B1B6CC2A177B4ULL, 0x564DBE2123467461ULL, 
            0x6917CBDB38CFFE8DULL, 0x77502D892EF40836ULL, 0xFB44AFF7F3FA26A2ULL, 0x4F0AE4A24946068BULL, 
            0xABC08A5118506820ULL, 0x591DD2ED0B62B1CAULL, 0x176C7D98154FE86CULL, 0x393E833FD2515F36ULL, 
            0x94AB6ACFFD691979ULL, 0x00B495341177DB72ULL, 0xCFB2DC802A8867CFULL, 0x67114D319CB56244ULL, 
            0x3E6F96955ACCFF31ULL, 0xA4235D8482944F1EULL, 0xF9887CAA622C64F6ULL, 0x208F6B71A0003DABULL
        }
    },
    {
        {
            0xAD76722C8C7DF2C1ULL, 0x414E2C28B8000431ULL, 0xCD2058CB11FCE912ULL, 0x1C41A18FC439BA66ULL, 
            0x44238A6DC6FA9CE1ULL, 0xFD9FFC88E0CB2D1BULL, 0x2935403B50B0BCD4ULL, 0x1C3EBFD3668D49FDULL, 
            0x888C0B7F80552D88ULL, 0xBDA2A51C9753E139ULL, 0xC7EB99E2C791CDACULL, 0x4BDADBA581877B9AULL, 
            0xDD2D7A0377F6DECDULL, 0x3E0F4A280C11879AULL, 0xBDF5260BC80F4F1BULL, 0x7A171607BBA04149ULL, 
            0xBA900D04DE883793ULL, 0x93ED926C34003B8CULL, 0xFEBEE052F11A52ADULL, 0xDBDBFA65127902A7ULL, 
            0x2D58FCC5C57AEF7DULL, 0xF0B349F4E929BB03ULL, 0x6E9B6ECF21C359E2ULL, 0x751BE05550ADB93FULL, 
            0x5167D5EA5C56AE04ULL, 0x27C88849FA6E1FBBULL, 0xCEB9141E9BBFD4F9ULL, 0xDEACA107F36766D1ULL, 
            0xA941A759C68D875CULL, 0x49C6FED0B23C783EULL, 0x70A20C302F46301BULL, 0x1E5A69ECB3DA5417ULL
        },
        {
            0x4BBF6DB7EBE5BBDCULL, 0x5760498F31ABB5ABULL, 0x34BE203B32949A17ULL, 0xD65CC20EB9BFDB5FULL, 
            0x31A37B594D2475A5ULL, 0x5F3575A0103FA5CEULL, 0xC1C658B3D5AB723BULL, 0x06BCFC9E787537F7ULL, 
            0xE22F7B580F4D38E5ULL, 0xF6067EC43E16FC88ULL, 0xEC759B7E6BC344C1ULL, 0xAED590D4191CB3C0ULL, 
            0x60447A8F52A4EAABULL, 0x0D0427C69827B92AULL, 0x7FB022EC5D20B635ULL, 0x80FC3BE6B091A018ULL, 
            0x355DC8B5CBC0A7C5ULL, 0x527CFA1263A94A6BULL, 0x76CEA0EDA14CBEE1ULL, 0x950A6A1DDC734B29ULL, 
            0x6388F7AF66001778ULL, 0xBCFA21888796B8CAULL, 0x1E59D970AD4FD707ULL, 0xFD59A9FECB325427ULL, 
            0x00FEF3309887AAEFULL, 0x3E1A39F019162E97ULL, 0x2E8326B76205D897ULL, 0x4C972B268FE183C0ULL, 
            0xF056B2B5B87A24E4ULL, 0x979089826014E167ULL, 0x7AC32FF9C00A28CCULL, 0xCA8242B96E049ADFULL
        },
        {
            0xB07DDA44A4393C96ULL, 0x79249A894F1F6308ULL, 0xD8077C74327F6BE8ULL, 0xDB82BBDCDA0095BAULL, 
            0xD3CCA969E56B50A5ULL, 0xEEF31C5A941F84B4ULL, 0x96A687CF15970482ULL, 0x3F9DD9B4D7D00E4EULL, 
            0x6B3092A0106A1173ULL, 0x5BB0B5479572F8ABULL, 0x0B350D2B4DD7F9A5ULL, 0xD9F231E1D8E81F44ULL, 
            0xD273B00345BF7CB3ULL, 0x9101DED268FE2922ULL, 0x29A0F093FEA42763ULL, 0x60A705C149D78D95ULL, 
            0x696517838D696B2CULL, 0x581FDD3946B6BE2FULL, 0x09501BB22C6AF58CULL, 0x4684FC319A2B1224ULL, 
            0x758547C58A8B55C7ULL, 0xE3652E0E747F3ECBULL, 0xB695FC32848DFC88ULL, 0x036D26C34F0CEC40ULL, 
            0x99ED8EFA8AAC231BULL, 0xAA93BDCC8AA0E278ULL, 0x5A405AC72738C712ULL, 0x5951EDF93D42D9D1ULL, 
            0xD9C0CF1DAF635537ULL, 0x3E3954CF26183043ULL, 0xA4A636EB3224FAC9ULL, 0xCB7B3BD9A6A7BB8BULL
        },
        {
            0x0E48A98206817D23ULL, 0xC76EBAD212207719ULL, 0x43E8EADE3BCCF09EULL, 0x69CCF7911BA0AAF7ULL, 
            0xC6CF42B04B6A0B79ULL, 0x04DF3A0020DCDE50ULL, 0xA81349C660C857B1ULL, 0x6B42724F1CB5155AULL, 
            0x1E030FCF0EFA6A17ULL, 0xFC24B621A8C88E3BULL, 0xD5ED7629CF91C96FULL, 0xAB3B89F727A29B52ULL, 
            0xDC62AB845BAE550FULL, 0xFB5BBC2B48F652B8ULL, 0xA80269D53B0CD5CDULL, 0x70976294E8BDE903ULL, 
            0x87EFE64795C87569ULL, 0x81A343F1D3FCF2EAULL, 0x9933A5B0C2AE392CULL, 0xBC523056BBAE2454ULL, 
            0x539BD017BD837E02ULL, 0x7392B68C055DEAC0ULL, 0x651F907455BFC1F5ULL, 0x35F061C28AD38B0DULL, 
            0xB1ED813C1B829A1EULL, 0x1A1590364D154778ULL, 0xE89242D5905AE0A3ULL, 0xBB8EEC48101667CBULL, 
            0x93A8D42C2445871BULL, 0x11EA1A3229297AA4ULL, 0xC14D105AB3184D80ULL, 0x23E9C670254CA6C9ULL
        },
        {
            0x40252776ED787CD9ULL, 0xDCB17F5E740867F2ULL, 0x31E0B9CA2185E240ULL, 0x1B8DE89BD5D01402ULL, 
            0x400A703293BE4CC9ULL, 0x4ADB225485504AFCULL, 0xD6E2E0D7DF78B3E9ULL, 0x7A096EF5A1A1232CULL, 
            0x276AB33CC1539CF1ULL, 0x1FB5F1BA84AA0718ULL, 0xF0E1DB44AAB361EDULL, 0x9EDDAD0DBF21C95FULL, 
            0x64846B2B1AB74ADCULL, 0xEA447347BB900627ULL, 0xD93D3585797E3A31ULL, 0x80F6F927561BA6AAULL, 
            0xF3440C9FCE76E1A8ULL, 0x2C4E98C6B7A88C4EULL, 0x56E75B7CBF867BB1ULL, 0x35B00C31DD4BEBF1ULL, 
            0x63880E88ED9CD57BULL, 0x009FC7EF45ACDEEBULL, 0x0403B827C2D8FEF7ULL, 0x40D76F1DDFE9ECC3ULL, 
            0x9CE112256F7D4186ULL, 0x87806972A616F09BULL, 0x893F41B135F37156ULL, 0x822CCFEACB18345FULL, 
            0xF6DA7648988CAAA9ULL, 0xF4D7F0FC63645C97ULL, 0x826D25596138A958ULL, 0x26320C0C3DA1AE93ULL
        },
        {
            0x8CFBC7CB8F649763ULL, 0x6589B1F56A3D0F95ULL, 0xD9457D06C9BB6BDEULL, 0x6FDD258568D0CD43ULL, 
            0x9B6D77A6161865BAULL, 0x26E0346915E1749EULL, 0x7253FE16960EE32FULL, 0xFF7093DD487D2A83ULL, 
            0x614932976CD3BB59ULL, 0x1DCDDD1CE8DB77D5ULL, 0x1C2C5467D7C472BFULL, 0x4611CD6938DE16FFULL, 
            0xEB6524B34F275DC2ULL, 0xF51C9F7889080405ULL, 0xAF795762450A8D8EULL, 0x32B0DE445D3791B8ULL, 
            0x6D905EFAA696B352ULL, 0xCC8A0C0EEA82539FULL, 0x960429466D66278EULL, 0x1E1325210337EB3EULL, 
            0x7CDA78B936405066ULL, 0x4E54F0CB53466D80ULL, 0x29D11672D699B903ULL, 0xBE2E9AE4E69BADDEULL, 
            0x071ED0284092232AULL, 0xCDE158CA15928BF6ULL, 0x5CF94679BC8EEBB5ULL, 0x97BBE9482D271A8CULL, 
            0xF19DB9D214DF0E2DULL, 0x9AE7D9DAC818110BULL, 0x34F7F1E31CFA224DULL, 0xE55A99A1E26F0D8EULL
        }
    },
    {
        {
            0x1D7F4D3409DA13D9ULL, 0x72559B3F4D7D0C8AULL, 0x546B393218E2F623ULL, 0xD2215416DBA74E5DULL, 
            0xEC287519DD65C4A7ULL, 0x573C3DC39C4B6D5CULL, 0x3DFC9BB2B1428A50ULL, 0x2DF84386F2733FE7ULL, 
            0x353559F09AA889D5ULL, 0x9048765DBC98F5D4ULL, 0x068B4D1B716C4380ULL, 0xA55CBDF784BF8BE6ULL, 
            0x3BB1E51CA6732BFFULL, 0x01FC4C38FFEE667DULL, 0x2A69220B0B59A224ULL, 0x29605D1FC0EB6E59ULL, 
            0xECEC8EF4D1C3E4AAULL, 0x8E0FA017BD5F0498ULL, 0x921762D14B981F9EULL, 0x64ADED199E5F75F2ULL, 
            0x6587E066B14A008AULL, 0x74503220D05B3EBDULL, 0x9EF0606ACB0BB14BULL, 0xA229F9C4F6B46EA2ULL, 
            0xC96FDA20ACEDED3DULL, 0xD1878041CFCAB6FDULL, 0x018494050581A732ULL, 0xCB539B66E263B107ULL, 
            0x933B2C4CC9C46CD1ULL, 0xB1A650D8C1A0332BULL, 0xB7EB9879F6E9829BULL, 0xC47B8190FBF65E4EULL
        },
        {
            0xF8F5C055EADFC8E6ULL, 0xD8EA3513D30219AFULL, 0x1F5C4FE206ADFB26ULL, 0xEA7392B3AEFCB324ULL, 
            0xE294D0EC2ECF2116ULL, 0x555DC5000F3C14DEULL, 0xE32EB704EA13797CULL, 0x86DB3796957F3822ULL, 
            0xBE3C666A86C5E205ULL, 0x8C3B3D1C03C84B0FULL, 0x72A1F66D0FC3E4F2ULL, 0x0D50B9CC31BFF2E2ULL, 
            0xFD385385ACC2705BULL, 0xBBF7225125501082ULL, 0x24942F0851EDC68FULL, 0x03D35DA91DA82569ULL, 
            0x10002503C9518A8DULL, 0x1CA8FE5F4617B744ULL, 0x38CAD3CB610FAFDFULL, 0x0EC419DDB4891409ULL, 
            0x96A28D839D945DFAULL, 0x9B6C0EAC36107688ULL, 0x184063AE62BC848DULL, 0x26A4C5301EC07827ULL, 
            0xFC7B346863658B11ULL, 0x9AD32C2640550A0CULL, 0x3109F38C7FB7EF7FULL, 0x4EC33C5F61519B53ULL, 
            0x9848A0614BE0CA08ULL, 0x0A819D8EA6B9507CULL, 0x28C0880EC81467C8ULL, 0x747C012067E24486ULL
        },
        {
            0xB78C6C338606A398ULL, 0xF9D88B186299EB1CULL, 0xA61A800CFABBF208ULL, 0x18F57E5534ABA451ULL, 
            0x018CF4A85F054EFEULL, 0x730561B3DB02CFD7ULL, 0x4299FF22B1992D2AULL, 0xFDCD4A196D4DB2FBULL, 
            0x5CCD6E1103E8A601ULL, 0x21A26C907536BA88ULL, 0xF335D107669366E0ULL, 0x8969C5D561BE76E9ULL, 
            0x9235C7749F456AC5ULL, 0x279A5DA2167B4AC2ULL, 0xCB6C994E07DF327FULL, 0xD7F763FCF1DC58B8ULL, 
            0x44938EF196A3C851ULL, 0x68482A8F362856BAULL, 0x453510D5D2958A87ULL, 0x32BB56FF573EECCAULL, 
            0x3D4028BED973BE8EULL, 0x4191227B4B061257ULL, 0x6DC0997F8A0A8B4FULL, 0xBF14E856E3F20B9FULL, 
            0x21389C3F38E6A726ULL, 0x47CCFAE152D40D42ULL, 0xF117021199913B27ULL, 0xAB8150910062857DULL, 
            0x9CF0B576D6DE803DULL, 0x61779E87724FFAFEULL, 0x99F3D2913F3333FFULL, 0x1E967A3FF0C6012CULL
        },
        {
            0x5176A9B7037587F4ULL, 0x58A5E000A7BA3D5CULL, 0xB3D13705B67B66B8ULL, 0xD8C3AB9983385C7CULL, 
            0xCFB99F1C23442188ULL, 0x4439F40CB73E2EA5ULL, 0x9CFAEA2A84709B0BULL, 0x1140ADB8C792AE05ULL, 
            0x4DC3E26EE28EB495ULL, 0x9ABDB28466EE598FULL, 0x0C9A14E3E661CEF2ULL, 0x7851123F213961EFULL, 
            0x6C90A48AA478087EULL, 0x5B452ADABF58F584ULL, 0x10D46C02A429869BULL, 0xF348C4FA0E0BE028ULL, 
            0x7C7F54C8DE645CBCULL, 0x6908196798FF9F02ULL, 0x51A1D37EA80E9FECULL, 0x81C1806D5B9596A0ULL, 
            0x87720AE41025CC08ULL, 0xB79195E35D831CF4ULL, 0xDC83D616DF21EC60ULL, 0xE84B838BC314B42DULL, 
            0x5A2EAAC0538ED064ULL, 0xA4A15A3EDB787AB6ULL, 0x7BD5D95954E42F8DULL, 0x5A93F0219FAF2F27ULL, 
            0x6999797D3BF36A80ULL, 0x4582D1AB235EB6D6ULL, 0xAAEE938DDB656E27ULL, 0x51F0C89E62104491ULL
        },
        {
            0x189147E9F6B76903ULL, 0x577A3844FC2219E8ULL, 0x8F2292AE18130DDFULL, 0xBE7AFD09B0D7D5F8ULL, 
            0x3378EAE42924E498ULL, 0x0BD76A7F2E87BA3DULL, 0x27CCEFB08936AD90ULL, 0xE10EF126FF5F0FA2ULL, 
            0xE3522CB798B77756ULL, 0xCFD0BC823953375EULL, 0x72EC197A65DDC533ULL, 0xC3280ED1F3417C2EULL, 
            0x7388E91198FCABDDULL, 0xEA0185C3C9F97694ULL, 0xB9634E9FEC774AB5ULL, 0xCD4FF37E688EFF76ULL, 
            0x2098ECC8EC06F215ULL, 0x97D93E40228201F0ULL, 0xFB78589BF6E5DBB9ULL, 0x6526EFBB8F170660ULL, 
            0x362A7FFCB1B08419ULL, 0x42E02D54F732BAFCULL, 0x1104029D1E4B6CA6ULL, 0xF213E0D42C5EDEC5ULL, 
            0x2D5EA73A2FFF9B70ULL, 0xEC6B032B783AA4DDULL, 0x1F3EDA36724E8345ULL, 0x7EE4BC1823A134F2ULL, 
            0xADD8DD9FD9CD7D9DULL, 0xE4B3461B04EBED72ULL, 0xB26E13F2FE45B25BULL, 0x07BCA079D83E8387ULL
        },
        {
            0xE2B233EDF674FBEDULL, 0xC429EC1DBC178899ULL, 0x697EBD92F0EC39B4ULL, 0x2A3AC54BB91C71DEULL, 
            0x007ACEF44FCBED6CULL, 0x8A833D1B2594BE38ULL, 0xEE829B71B5E6834EULL, 0x0960F375638FF29EULL, 
            0xD5EB06E3C0042CBDULL, 0xC4A77FE440A3DD90ULL, 0xDE995F8B2846709CULL, 0x344EF8F4FA318F92ULL, 
            0x64CBC928DA252AAEULL, 0x477DAC040348C1A2ULL, 0xDEFDC4F9DE4DF319ULL, 0xBB07C07A9DDF45B0ULL, 
            0xD0313182A14A37EBULL, 0x10AE5C869BA769E7ULL, 0x9DE02C86827CD606ULL, 0xA370FF36B7E9E2ECULL, 
            0xCDDB5A83D37345ACULL, 0x2A41B354661D0764ULL, 0x5B3BBC028D81852EULL, 0xD3D3AA3C8E335973ULL, 
            0x4A9CB8A22FD07B30ULL, 0x47222B657103A67BULL, 0xC34EA3B21006A101ULL, 0xC7FF96B813BDA4ADULL, 
            0x675A76F64B0A219EULL, 0x65EAA15FCEAD6F51ULL, 0x7BF2F8D48EE4AA53ULL, 0x4A7D05EE8D9406F5ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alnitak::kPhaseHConstants = {
    0x822684F2D97AE5E1ULL,
    0xDA4A8CCE50201645ULL,
    0x22EBD080F1D6FF28ULL,
    0x822684F2D97AE5E1ULL,
    0xDA4A8CCE50201645ULL,
    0x22EBD080F1D6FF28ULL,
    0xC21AF56DF3C790C0ULL,
    0xF945001A94A2802DULL,
    0x63,
    0x41,
    0x23,
    0x9F,
    0x67,
    0x53,
    0xCC,
    0x24
};

