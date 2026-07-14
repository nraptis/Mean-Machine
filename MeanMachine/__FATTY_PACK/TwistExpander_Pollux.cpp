#include "TwistExpander_Pollux.hpp"
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

TwistExpander_Pollux::TwistExpander_Pollux()
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

void TwistExpander_Pollux::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xC065A1722D170A61ULL; std::uint64_t aIngress = 0xCDDA2B4BF262A5CFULL; std::uint64_t aCarry = 0x836BF0F3286106DEULL;

    std::uint64_t aWandererA = 0xE7BE1A45588A61A5ULL; std::uint64_t aWandererB = 0xD65D5D6E11CA9FC2ULL; std::uint64_t aWandererC = 0xC7B137146E1E7663ULL; std::uint64_t aWandererD = 0xAECFA7362E3B70CBULL;
    std::uint64_t aWandererE = 0xD0C9495881E90176ULL; std::uint64_t aWandererF = 0xA5454F815AF8DBFFULL; std::uint64_t aWandererG = 0xF562875BC88D1EF8ULL; std::uint64_t aWandererH = 0xA686C23D7ED5641DULL;
    std::uint64_t aWandererI = 0xF44DBCD02D0C5A6EULL; std::uint64_t aWandererJ = 0xDCABED1D441B7CDEULL; std::uint64_t aWandererK = 0xF88E98436DAFD6E4ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 9707847345250171939U;
        aCarry = 10445265193035403614U;
        aWandererA = 15188829906607829969U;
        aWandererB = 11901191334635120541U;
        aWandererC = 17494069752986145374U;
        aWandererD = 14651240969788569114U;
        aWandererE = 17613815492475465345U;
        aWandererF = 13033849535580864951U;
        aWandererG = 12855369777594277207U;
        aWandererH = 18301452380079610277U;
        aWandererI = 18263846923556842843U;
        aWandererJ = 9479665543100217999U;
        aWandererK = 11121875518677779723U;
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
    TwistExpander_Pollux_Arx::KDF_A_A(pWorkSpace,
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
    TwistExpander_Pollux_Arx::KDF_A_B(pWorkSpace,
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
    TwistExpander_Pollux_Arx::KDF_A_C(pWorkSpace,
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
    TwistExpander_Pollux_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Pollux_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Pollux::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xCC347A58F9D6B94DULL; std::uint64_t aIngress = 0xACE27ABFB7C8D64DULL; std::uint64_t aCarry = 0x827D84454C762A93ULL;

    std::uint64_t aWandererA = 0xCA54D9FFCA343A54ULL; std::uint64_t aWandererB = 0xD9727C9E3C573207ULL; std::uint64_t aWandererC = 0xFEB6C0AFDBD20CEAULL; std::uint64_t aWandererD = 0xF0A2E2BA64B093F8ULL;
    std::uint64_t aWandererE = 0xAB4C283A8A9C9CC8ULL; std::uint64_t aWandererF = 0xA253C00F1B38E722ULL; std::uint64_t aWandererG = 0x977DB39083EA665BULL; std::uint64_t aWandererH = 0x912DC125FFC7955DULL;
    std::uint64_t aWandererI = 0xC00AEA5DA258CE5BULL; std::uint64_t aWandererJ = 0xD397D4A259ADD76FULL; std::uint64_t aWandererK = 0xE7D5F810CD7D33A7ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 17831606445214249608U;
        aCarry = 10503121176780960916U;
        aWandererA = 18253061666336596085U;
        aWandererB = 10302706972722321777U;
        aWandererC = 14261440327622882149U;
        aWandererD = 16642152784090835870U;
        aWandererE = 15807741482002083910U;
        aWandererF = 14371483186996140726U;
        aWandererG = 13237048459414794403U;
        aWandererH = 11572900345424292793U;
        aWandererI = 14083947643085149177U;
        aWandererJ = 17714090011308766909U;
        aWandererK = 11382861818963899529U;
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
    TwistExpander_Pollux_Arx::KDF_B_A(pWorkSpace,
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
    TwistExpander_Pollux_Arx::KDF_B_B(pWorkSpace,
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
    TwistExpander_Pollux_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Pollux_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Pollux::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xC2CAE843331B0AC0ULL;
    std::uint64_t aIngress = 0xE4C195F615B4F2D1ULL;
    std::uint64_t aCarry = 0xB1AA35BA16CF4578ULL;

    std::uint64_t aWandererA = 0xC9D8449A6EDEDC52ULL;
    std::uint64_t aWandererB = 0xF7F1376E9D551DA0ULL;
    std::uint64_t aWandererC = 0xCBF34CBB470CCFF3ULL;
    std::uint64_t aWandererD = 0xA74EDA4506A98D09ULL;
    std::uint64_t aWandererE = 0xE1FE51FF65CC0BBEULL;
    std::uint64_t aWandererF = 0x91A1EBD15C001AC7ULL;
    std::uint64_t aWandererG = 0xA4F7A6CD8B6B3ADCULL;
    std::uint64_t aWandererH = 0xFC2CAA9843A5A7B8ULL;
    std::uint64_t aWandererI = 0xBBA2A2191D5DCF35ULL;
    std::uint64_t aWandererJ = 0xF120D3D33CA969C9ULL;
    std::uint64_t aWandererK = 0xE61D13ECD324E7BEULL;

    // [seed]
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneA);
        TwistSnow::Sha256Counter(aSource, aSnowLaneB);
        TwistSnow::AES256Counter(aSource, aSnowLaneC);
        TwistSnow::Aria256Counter(aSource, aSnowLaneD);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneE);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneF);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneG);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneB);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneD);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneA);
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
    TwistExpander_Pollux_Arx::Seed_A(pWorkSpace,
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
    TwistExpander_Pollux_Arx::Seed_B(pWorkSpace,
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
    TwistExpander_Pollux_Arx::Seed_C(pWorkSpace,
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
    TwistExpander_Pollux_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Pollux_Arx::Seed_E(pWorkSpace,
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
    TwistExpander_Pollux_Arx::Seed_F(pWorkSpace,
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
    TwistExpander_Pollux_Arx::Seed_G(pWorkSpace,
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
    TwistExpander_Pollux_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Pollux_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Pollux_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Pollux_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 25 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1796 / 1984 (90.52%)
// Total distance from earlier candidates: 43600
void TwistExpander_Pollux::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1350U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1160U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 818U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1402U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 638U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 220U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1918U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1634U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 353U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 465U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1851U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1661U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 919U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 2043U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1921U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1401U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 2004U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 2002U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1074U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1032U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 84U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1965U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1110U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1223U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1477U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1546U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1608U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 974U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 142U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1815U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 374U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1330U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 448U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 522U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1705U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 216U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 498U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1678U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 531U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 841U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 430U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1776U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 106U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 422U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 314U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 2033U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1760U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 880U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 459U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1525U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 932U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1308U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1994U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 307U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 409U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1777U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1593U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1906U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1513U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1534U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1860U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1363U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 126U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1369U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1329U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1589U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1392U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1257U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1111U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1558U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 56U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 143U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1342U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 664U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 631U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 612U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 262U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1028U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1426U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1202U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1644U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 539U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 204U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 920U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 178U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 69U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1475U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 481U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1394U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1648U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 441U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1795U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 927U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 644U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 338U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1789U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 467U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1125U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 402U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1154U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1838U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 18U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1850U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 910U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1012U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 302U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 212U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1341U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 179U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 182U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1638U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 234U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 672U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1943U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1382U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1427U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 185U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1218U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 233U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 187U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 16U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 715U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 80U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1238U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1255U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 989U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1079U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 916U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }
}

void TwistExpander_Pollux::TwistBlock(TwistWorkSpace *pWorkSpace,
                                       std::uint8_t *pSource,
                                       std::uint8_t *pDestination) {
    TwistExpander::TwistBlock(pWorkSpace, pSource, pDestination);
    if ((pWorkSpace == nullptr) || (pDestination == nullptr)) { return; }
    std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    std::uint64_t aPrevious = 0x89D62A2AD5A290D7ULL; std::uint64_t aIngress = 0x8BFD6C2D6CD14DE8ULL; std::uint64_t aCarry = 0x80F5CCCB658A59B7ULL;

    std::uint64_t aWandererA = 0xEC16686F59125C03ULL; std::uint64_t aWandererB = 0xAE62F0B3A29EB028ULL; std::uint64_t aWandererC = 0xC34735EE078F8168ULL; std::uint64_t aWandererD = 0x94B02379BD6602C1ULL;
    std::uint64_t aWandererE = 0x884645DD09C7EC58ULL; std::uint64_t aWandererF = 0xC52E79853A030560ULL; std::uint64_t aWandererG = 0x97E207F241261ED4ULL; std::uint64_t aWandererH = 0xD2F6AC941D70989DULL;
    std::uint64_t aWandererI = 0xCD7C2B1FEB627726ULL; std::uint64_t aWandererJ = 0xA1D1EA2DD1D73DB5ULL; std::uint64_t aWandererK = 0xF7D73AF403A8FE7AULL;

    // [seed]
        aPrevious = 16372614513077395331U;
        aCarry = 17309778038873497673U;
        aWandererA = 13549849797880161471U;
        aWandererB = 13991009329968317614U;
        aWandererC = 12277426763436184290U;
        aWandererD = 11345721680478080413U;
        aWandererE = 14135648287854595201U;
        aWandererF = 18179261338375653074U;
        aWandererG = 9582553985000935150U;
        aWandererH = 9542471625727167663U;
        aWandererI = 11677576579842518899U;
        aWandererJ = 13388189278251411167U;
        aWandererK = 17721997432164099587U;
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
    TwistExpander_Pollux_Arx::Twist_A(pWorkSpace,
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
    TwistExpander_Pollux_Arx::Twist_B(pWorkSpace,
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
    TwistExpander_Pollux_Arx::Twist_C(pWorkSpace,
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
    TwistExpander_Pollux_Arx::Twist_D(pWorkSpace,
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
    TwistExpander_Pollux_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Pollux_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Pollux_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 25 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 13011; nearest pair: 492 / 674
void TwistExpander_Pollux::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4150U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5659U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5986U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1041U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7139U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 108U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7544U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1333U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5795U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4231U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6522U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6590U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1490U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6492U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3712U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7420U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1088U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 874U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1588U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1054U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 753U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 278U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1472U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 878U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1177U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2038U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1183U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 60U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1490U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 355U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1949U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 259U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1818U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1294U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1772U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1648U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 25 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 13023; nearest pair: 484 / 674
void TwistExpander_Pollux::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1410U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1227U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7167U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2668U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5970U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1534U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7969U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4985U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5489U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3577U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4088U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1307U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6338U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5500U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6229U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7096U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1136U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 660U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 978U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1237U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1187U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 492U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1077U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 926U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1380U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1620U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1386U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1078U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1567U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1719U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 725U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1665U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1659U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1784U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1220U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 2037U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Pollux::kPhaseASalts = {
    {
        {
            0xBFA79B33AAD58BC5ULL, 0x2F5D4C3CC0E72290ULL, 0x1517E8569B7B28CAULL, 0x0B60FB87F8EECB5BULL, 
            0xEC33B475CC549F27ULL, 0xAD2298B3AF9F9752ULL, 0x3A2362B295762C64ULL, 0x96EA0D181AE2009DULL, 
            0x8E52368ED0820F73ULL, 0xB988C28CA02A402AULL, 0xDF8390E636A533CCULL, 0xDDE585C1ED920A97ULL, 
            0xB7024B6069AEECC2ULL, 0xEFE88F44774CB70AULL, 0x75B6732FC003E459ULL, 0x6858D21B457D59FEULL, 
            0xE18F09D252D0D7A8ULL, 0x545E6BC1BDF5CD70ULL, 0x366A24B08EAB74B6ULL, 0xB04F964E7070A6EEULL, 
            0xF0364405C484D689ULL, 0xDE361742AD7DB618ULL, 0x5AE5E42D5FBDB757ULL, 0xF2EC3C15A5267D52ULL, 
            0x369E6DDA16252EF2ULL, 0xC3ECF9FC0375E14AULL, 0xCF2B366F9268A76FULL, 0xD1F94848071AF49BULL, 
            0x1017CDCE0B048B74ULL, 0xA1C55EC69C6DCEB8ULL, 0x6A55EE0C03FC93E3ULL, 0x2814D346B0ECEE43ULL
        },
        {
            0x268F52813523A535ULL, 0x48D191DBD3DDBC86ULL, 0x161670B309F24C9CULL, 0xE29A60CB910D5A1DULL, 
            0xBF8C84AA4FE739F3ULL, 0xA9DF03297AE88FF3ULL, 0x07814E9EC6991751ULL, 0xE4758BF85C41FED3ULL, 
            0xC3A337351E317389ULL, 0xECABCE8752CE3BC6ULL, 0x903EFFA55A05BCD0ULL, 0x1FCDE77F7B584511ULL, 
            0x5839A442D4BE6303ULL, 0x8FDDF479B01148FDULL, 0x4E60ADED4AE759ECULL, 0xF4F3558A1A6AA3BAULL, 
            0xBC3D146926EADB3FULL, 0x03E6773A5DC0CDDEULL, 0xD8543EB61F6B11ADULL, 0x39816BB8F3607E66ULL, 
            0xD3990F9FF8FF613FULL, 0xE2AF1283878CB1E8ULL, 0x2CC0B3159D9A3425ULL, 0x2B62EB3541A8C731ULL, 
            0x635689A5776F43BCULL, 0x0109BB290BA24BC9ULL, 0x6461870B2E856AECULL, 0xB5E9F0731849BBEBULL, 
            0x5751B37E0FC29BFDULL, 0xFAC4BA837E3A5998ULL, 0xE2BEE942AE4AB08AULL, 0xFB4ED0CE83FCC60CULL
        },
        {
            0xEB29BC49D4D7E1B0ULL, 0xBB4DAA448A2DD86BULL, 0x25F95D8668B6DB64ULL, 0x57EE244363E5EF5EULL, 
            0xB21F77BBB1B6570FULL, 0x8820B8B4146CCB9DULL, 0xB9532E01BB0E7D23ULL, 0xDCA2259ADF3E70E3ULL, 
            0xEAC04927F7D37AF0ULL, 0x79AC62772DC39FB9ULL, 0x6EB7CA1686675733ULL, 0x006398F13E7BFE50ULL, 
            0xCDE81DE392C266B2ULL, 0x5CEB63BCA96F7DDAULL, 0x50CE7C8044D3CCF5ULL, 0xD59BD3364D1B89BAULL, 
            0xB0F2EFEB0E1A5D88ULL, 0x2D74E97A1DB51743ULL, 0x5845AA2E99258EB3ULL, 0x0835211D675CE81CULL, 
            0xE43A2B7152B5C395ULL, 0xF1ED79DDD7506332ULL, 0xF51B005DD78F8AF8ULL, 0x8EEA3B75DF8692A4ULL, 
            0xDE61008BE741327BULL, 0x4BBBB67CA9E37E4EULL, 0x717690E2759DAC76ULL, 0xAE3C228071D2BA23ULL, 
            0x3A1C5AA3A10D28DAULL, 0x85F8E70C8838A17BULL, 0x250A0EEC5164F559ULL, 0x95297112B6868BC0ULL
        },
        {
            0xA061126AA49661C7ULL, 0xB86A86C029C5F065ULL, 0xE3E7345F25A9D8DCULL, 0x9C2CD1BD2A7FFCACULL, 
            0x953D6568C19C7C6EULL, 0xE0BD93404ECF7072ULL, 0xCA548A97450598EDULL, 0x966652393AA3A989ULL, 
            0x30EAA47B20BDBE92ULL, 0x4330293902073FA8ULL, 0x889666F22C93011EULL, 0xB9ED2165D0AA685AULL, 
            0xDA514199FC65C61AULL, 0x5B78E95304F6846FULL, 0x5FFCB2EC19800F93ULL, 0x43BB9B27765E13B9ULL, 
            0x8BBB746B3A468490ULL, 0x02A32877AE470C38ULL, 0xD0BD81F05D219202ULL, 0x2D76E62BE2235B8FULL, 
            0x0C9B91CB67195DBAULL, 0xCADD697C16271299ULL, 0xEE17F4E360440BE6ULL, 0xC0492EE7E8D2CD05ULL, 
            0x81D6586DA545C8B1ULL, 0xC0201169E2292B08ULL, 0xFC22570A500CC8C4ULL, 0x6D380B68F7E7A34CULL, 
            0x019213EEEC654A21ULL, 0xCDED5BBF4893510DULL, 0x306B1C679FEFB970ULL, 0x655C33BB50C98A4AULL
        },
        {
            0x4D7C3C93D577FD8BULL, 0x0D6B346AB1A8886BULL, 0x06885BF349D345C8ULL, 0x2BFA405CE2B1DFE4ULL, 
            0xB25F667CA972D11AULL, 0x0A19E9A7520E938BULL, 0xE5C0DDC5EA0DF653ULL, 0xF615D2095CC2747AULL, 
            0xC80FB093FAAF6295ULL, 0x8419F4A9BFD8B481ULL, 0x999BE4AC0D149E90ULL, 0xE5B322E2539E4C99ULL, 
            0x0AD10B9369EA96C0ULL, 0xEE39B6691765B9F2ULL, 0xDD1699092F7EB0E9ULL, 0xE3D371BDA75E8445ULL, 
            0x066A752CE3E47E17ULL, 0x59256DF7C3E35C77ULL, 0xA69C1F15A431B610ULL, 0x44B119F7E9432CF7ULL, 
            0x13CC5B734331E334ULL, 0x050862C3024F34C7ULL, 0xFC18BC06BE058430ULL, 0xA26B06F37670FBC2ULL, 
            0x3420A3CB13501118ULL, 0xC75316004E7323CBULL, 0x4EF688AF120EF20AULL, 0x7F33D980BDEF94DEULL, 
            0x5FD6C321A8399784ULL, 0x0DE9E4A386E8525DULL, 0xF88FBB7028539A48ULL, 0x63A3F6CA0004FDEBULL
        },
        {
            0x646B2140405486CEULL, 0x4F85E8200C4DD619ULL, 0x0E5C477D8FBAAF42ULL, 0x7B1507C980EAF965ULL, 
            0x7A9853039EAEB535ULL, 0xF747B3D80E9E06F9ULL, 0x90825BD585A59FD9ULL, 0x415E20CD26399AC0ULL, 
            0xBA10AFAD92AB20BDULL, 0xF99843D5026E8F04ULL, 0xF5B3224AB98F7FE7ULL, 0xDBE6C5CA525A19A7ULL, 
            0xA4FAF0722425B89CULL, 0x76BF1FE8504D3F2BULL, 0x62AAF4FADD37A851ULL, 0xF6BF2F9B910582C1ULL, 
            0x5B568ED0878FF7BEULL, 0x8C9A85AC5D7770F0ULL, 0xFFE9795CB05D3C35ULL, 0xD8600940A5CD1377ULL, 
            0x7C37C3B4FD78A3E0ULL, 0xCB64BCF7A79ABA66ULL, 0x776BD31E673E6DE7ULL, 0xF4E624008430992AULL, 
            0xCDA7825FB57CE0CBULL, 0xF4D86E16F7762048ULL, 0x0A40DDAA02F3878DULL, 0x2209E14F5213DF81ULL, 
            0x280ED56E2AD63ABAULL, 0x7EF3E7A69EC214AEULL, 0xCB9AFEA465C8E4DEULL, 0xB82B88776A63E7ADULL
        }
    },
    {
        {
            0xBEA579B79F204C56ULL, 0x884F985F9FD447D4ULL, 0xD3423369D102A155ULL, 0xAD221315AE54E9E6ULL, 
            0xFD45C1D66560F814ULL, 0x9F8336A12CBF9898ULL, 0x4927BFE80ED59513ULL, 0xA6F3409A23C40086ULL, 
            0x562CF895B015C3DCULL, 0x9403AB390A24A05EULL, 0x9B59BC8B723B53E3ULL, 0x6F7CE333A132AFB6ULL, 
            0xAD182FECF775BC19ULL, 0xF276E6B7E6CB4162ULL, 0x3D2105385258D67DULL, 0xCCBD88DDCB9E3513ULL, 
            0x757B979BFEBBE6FEULL, 0xF818DBE3BDE8EAA9ULL, 0xFA512A940FA5C3F3ULL, 0x8A8BBD4C1AF7F21DULL, 
            0x18B2C397E8BBD3F8ULL, 0x06F0CE3DF0570B5EULL, 0x6DD80AD43B2D441FULL, 0x6544DD23D342421FULL, 
            0x96E3F464A77B22D8ULL, 0xF8AA2443BFD42F8DULL, 0xA854EE4BF73AE720ULL, 0x649DC8FFEA4AA823ULL, 
            0x220348A613A2986BULL, 0xDBDF577608D69186ULL, 0x6F59D5E0111652D5ULL, 0x234E38243B62C1F3ULL
        },
        {
            0x9589D82E140E7424ULL, 0x6617A821466FDC6BULL, 0xD96DEF2FA7CA91B8ULL, 0xD58ABF9C9E5CE3B8ULL, 
            0xDE31CBA87030E2E2ULL, 0x3AEB9A5315712280ULL, 0x93A2C0F3D687461BULL, 0xB64584AFB0F85953ULL, 
            0x6A33BD076C949DA2ULL, 0x64C7CD9B960F497DULL, 0xB52A27ABC5EC1BD8ULL, 0x43132087600130AFULL, 
            0xA6C4DE99B3A52EC2ULL, 0xFA87C8EDD1FC3E42ULL, 0x49E38E43B75CED0AULL, 0xCD02C1B948298B27ULL, 
            0x8ED1B430058D20CCULL, 0xF5C4FA18CDE5AF20ULL, 0x4581AF213DFDD8DAULL, 0xDBAAFDF56A9F876EULL, 
            0x1E857A2D5B25B154ULL, 0xDBB13BE785295D29ULL, 0xE3BF6C183F769204ULL, 0x36D96A51E24F5AF6ULL, 
            0xE77285D6BDD5C9F1ULL, 0x3787A1630B42EE2DULL, 0x8321F54F0BE12058ULL, 0x34954D1347834A76ULL, 
            0xB697EF22A3B63E38ULL, 0x12C08E1179004E2BULL, 0xD000A59DCAD71A89ULL, 0xCEEB6D4CB5C9DAA3ULL
        },
        {
            0xB814FBF75390DD82ULL, 0x5639432739C762D0ULL, 0x77239EDEE209E1A4ULL, 0x8E670C15339B23B6ULL, 
            0x78F4D5C44047267FULL, 0x0FDA522213255F40ULL, 0xD0CAB6D42912E9A5ULL, 0xC4F7AA3FA0C07B05ULL, 
            0x21E4F17A4F0BECBFULL, 0x1C2DEA6AE2BD5939ULL, 0x74BA9DF0D8C49778ULL, 0x161AA5438499FCF2ULL, 
            0xB20FB6AD1151CC8EULL, 0x138A0AC2D060F29CULL, 0xF37EA5C63009F86EULL, 0x4D8C44464B9F7102ULL, 
            0xF2C22FED9C755215ULL, 0x3DB0C333DAF9A3F1ULL, 0xFA409167027B570AULL, 0xD0FC85FDA33CEA16ULL, 
            0xCA58DCE06649D0ACULL, 0xE6B15AFE8216B923ULL, 0xBB59B104BC44A2A5ULL, 0xAA13F73684B3866BULL, 
            0x96C492D685EC7EF3ULL, 0x66D1C94523DC9A53ULL, 0xD094EDA18F222AA1ULL, 0x1922251B8EF435C1ULL, 
            0x1E8251A53C3DABEAULL, 0x027E928E344E57AEULL, 0xA8ED61494B300BB1ULL, 0xC78B7E85CC176776ULL
        },
        {
            0x0E7EF762A6B1BC61ULL, 0x4293E2C8F9BA561BULL, 0x7C30655A97A6D0A1ULL, 0xABE377CC13B357B1ULL, 
            0x13381D7E61BBCE86ULL, 0xC46B35501375AAD8ULL, 0x09778DDE2D990C3EULL, 0xD7FF587D9CFD9797ULL, 
            0xBB637AABA08C2FC4ULL, 0xB0503541DA48CADBULL, 0x764DD82A0AD07BE6ULL, 0x8B5D01A4A25368F5ULL, 
            0x9FB95083012761B1ULL, 0xB0DB77A90E820345ULL, 0xFED7ADFDFA47FC37ULL, 0x0E023FB7C255E89CULL, 
            0xF5097E9CF142B367ULL, 0x5416E72A0C79D09CULL, 0xE0BC48AC829DC65DULL, 0xE0C75C0CC59ECE2BULL, 
            0xBD37FA0932F0B8ADULL, 0x5D4F617CE118BD3CULL, 0xAAD3726D5570F751ULL, 0x9325386933D90A96ULL, 
            0xDDE968DE69C592DDULL, 0x94D9897BE57D9164ULL, 0xCF5B973DC2CE5DC4ULL, 0x5F5AAE04888CA0FCULL, 
            0x2882E29885314FE3ULL, 0xFFB77A4D9A266193ULL, 0x03037B4B64329C2DULL, 0x7A1189F7E27B239BULL
        },
        {
            0x745285DA6E6BB862ULL, 0xDB374951ADC2EB8EULL, 0x0AD92201426DF59BULL, 0xEFD185E42D7A2FF6ULL, 
            0xD0A02922BEF25B0FULL, 0x2E8846C9C0A35421ULL, 0x4B7948037D524866ULL, 0x4BCE7BA6E5874934ULL, 
            0xEAFB5501BAF4DB3DULL, 0x7241D08E42AFA1E7ULL, 0x4956B80A6369E788ULL, 0xBE8BB9F8126816A0ULL, 
            0x9485EA21F41D5CF3ULL, 0xB1887EB40D1AC560ULL, 0xE4A7E9935761E8B4ULL, 0x6CE1C03C5D7E1235ULL, 
            0x203B5E9BDA673589ULL, 0xC03BC0259B7ED779ULL, 0x6D2CB45C1CB53CE3ULL, 0x8EB03B226BB1B9F7ULL, 
            0x9851807E111E6C24ULL, 0xFDFC6D409F8C92F1ULL, 0xF045F62375E62288ULL, 0xCAD586B55C601737ULL, 
            0xFA7E5A6EC778A7E3ULL, 0xD29D0FD032938F24ULL, 0xDE7B1D26B0D4637FULL, 0xD4A908F35A92B8BBULL, 
            0x982742FA8414E766ULL, 0xA3BA68403714CCFFULL, 0x2DB0594333442A2EULL, 0x0FB6B77D6A135941ULL
        },
        {
            0xCF850DA399472462ULL, 0xD8787BF67A2A618BULL, 0xA52E198FFF10605CULL, 0x256FC33616DF58AFULL, 
            0xEDF0677402C8FDC5ULL, 0xD66B56704A4BFDE8ULL, 0x9AD67BAB405ED7F7ULL, 0xFE819720180D4A59ULL, 
            0x2BF3F0A02DEA9A48ULL, 0x404F3BD533194FF4ULL, 0x5063FEF407EC4B69ULL, 0x2426F4117A669903ULL, 
            0xD91FF7A2D90C5CDCULL, 0x8518832485E207D8ULL, 0xA05D27440881774BULL, 0x07286FFCBF506535ULL, 
            0xFDC148D637363060ULL, 0xE9F99F38FA7C7423ULL, 0xF7E7DC5C28898BC1ULL, 0x2DE53A5806194348ULL, 
            0x07A70CBDD813D57EULL, 0x432877A2A12B55A4ULL, 0xBA9E309E5C0EE92EULL, 0x4392398F13C1F1E1ULL, 
            0xD6B50BF3880A95EFULL, 0x1EFBF18248FF67F0ULL, 0xF5339CC9FC68C1C5ULL, 0x35FE616CA3197C51ULL, 
            0x3F32181519DA0654ULL, 0x3996C94A783E19CBULL, 0xD090EECC5F9C129EULL, 0x91D08476ED6ADA3EULL
        }
    },
    {
        {
            0x9D76DBE44C7F911DULL, 0x73B875FA5810E61FULL, 0x973BBDCFD1B6CAE1ULL, 0xA172496B26B7EF8FULL, 
            0x9F06966853ED038BULL, 0x57455AD7E11B6F7AULL, 0x269F7924211CF31AULL, 0x3478B003F3E59432ULL, 
            0xCAAE26957456AA54ULL, 0x7736702C81997F03ULL, 0x1E538609E3DDC1A8ULL, 0x558706D395E4E94EULL, 
            0x1B2089FA5422A5EDULL, 0x1EA0C7D9A33CE18DULL, 0x39754B9EB26A5351ULL, 0x77C0A0521732FBBAULL, 
            0xA2BE6EA5C08BF559ULL, 0x020F62EACA474ABCULL, 0xD346C4A838868A81ULL, 0x251ABA71B456A970ULL, 
            0xCEABFF7D2C4A4FCAULL, 0x37F5877DBB3EDEB9ULL, 0x32C198E03791B6CAULL, 0xC3749F972B3882BCULL, 
            0x319860FEFD32FC0AULL, 0x8C1D8D6410B4D33FULL, 0x076EF7D5CE2B08E5ULL, 0x6E1C79D698CD944CULL, 
            0x92BE76159EB29D71ULL, 0x6D1D4FE7B2469B3CULL, 0x4C372AEAC5989F32ULL, 0x6AD220819BB40BE4ULL
        },
        {
            0x4E85D1006CEE58EEULL, 0x8F3D03A682F5A5FEULL, 0x125CA28A6D55999BULL, 0x206CC22527285DDCULL, 
            0x47A0179FFAF30F55ULL, 0xCCB3E23292330C2BULL, 0xBA118977B74980FAULL, 0xBED344A3A97E6FB5ULL, 
            0x61A3083218EAD1EDULL, 0x674E16388C980DD1ULL, 0xC599FB34B7E7100CULL, 0x08A31EFB44DE0292ULL, 
            0x250C8CAE1CAC0F9AULL, 0x1840104E6549035DULL, 0x31F27D2977DB1B82ULL, 0xC82133852FF35319ULL, 
            0x4D685661052EE7FBULL, 0x1E22DDBDE9745C7EULL, 0x802D915D2B3DC8A2ULL, 0x6E2CB76DD6FB19C4ULL, 
            0xE2E83C2F9175C427ULL, 0x46A5BAA401054A37ULL, 0x4D1DD18799DC529EULL, 0xB81DA7E42F0B3684ULL, 
            0xF955935867311C76ULL, 0xF5C1B5F2B8A6FD30ULL, 0x13FFE7DFD74AAFC4ULL, 0x259DF1F199947F06ULL, 
            0xB6031E0812657AF8ULL, 0x718E82DEAD2CF377ULL, 0xC48E778D6412F046ULL, 0x7CFA8A7DF6D56425ULL
        },
        {
            0x8F94A7AF5B8BE735ULL, 0xC1CC68A0F47F307BULL, 0xC664C5C59F13E08AULL, 0xB8002ADC7A9B4906ULL, 
            0x0806D6D763C17772ULL, 0xE8FD6E61601C44F8ULL, 0x53211794A86240C7ULL, 0x678443F7072EB11CULL, 
            0xFF0686DADF4D3E84ULL, 0xBA53C4E39B5E8A4BULL, 0x8F8DC5E9B583FAEAULL, 0x8E0EDF14E241088EULL, 
            0x70E516A96C7E0027ULL, 0xFC7F91F6C8F943B1ULL, 0xB6BA66DD36FDE222ULL, 0xCF57FCE606B62AAAULL, 
            0x96406B3A217444F7ULL, 0x53E031D0AAC66F66ULL, 0x5A19F69676911AA1ULL, 0x4C303082DF4CAE69ULL, 
            0x08EE0E346F3B0773ULL, 0x4DD146CE67C82A2CULL, 0x8758658DE4A371CAULL, 0x840C717443F61CF9ULL, 
            0x813F471487392F8BULL, 0xAD723E443EB7BBBDULL, 0x87213368B45FC94FULL, 0x46BBABB8964244EDULL, 
            0xBCB040BED4BB6CBCULL, 0xF7FF14A471003DCFULL, 0x4BFD3DDF0616DED8ULL, 0x25254D9223D53A34ULL
        },
        {
            0x9B02330CDC726FDBULL, 0x7874354B33DA34C6ULL, 0x7D2B44CAB0551FE5ULL, 0x87C208A40000F85AULL, 
            0xC58E401232B32095ULL, 0x765AC8ED82D7E390ULL, 0x7A763CA695947A46ULL, 0xC1E4C0D432A1AAF3ULL, 
            0x6057941909A7CD70ULL, 0x5BB94E07F546A8B7ULL, 0xF8FF1BD711B63F4FULL, 0xF420E035C35EA92EULL, 
            0x91CDBFFD1E678A70ULL, 0xB7A04606FA88DAF2ULL, 0x839D384C702696A1ULL, 0x96189D88710FC003ULL, 
            0x2EC1E66127B31090ULL, 0x4DEA37F8C179F47BULL, 0xDEA2B2D0FD86D061ULL, 0x9A109CD45DE7D24BULL, 
            0x4164D3CE002D27D0ULL, 0x1C07403598C43463ULL, 0x6F907E6DBF123F9FULL, 0x4D2C18753AFE44F5ULL, 
            0x13BFD8D0DE62840BULL, 0x6A122DF9A6EC6C08ULL, 0xBB4DA38EF993EF67ULL, 0x869664E055005721ULL, 
            0x91E0294C4DCAB0E9ULL, 0x62A65D451C7B2893ULL, 0x30C13104E3D33FC9ULL, 0xBF60A80C7C9FE964ULL
        },
        {
            0x4624D46F8BE2FE40ULL, 0xA9EEE45FEF740827ULL, 0x798D51BD59E1A4B2ULL, 0x54ED6291D3A0DDDEULL, 
            0x6E7B7D9205D5994BULL, 0x934954B0A20115F2ULL, 0xE990C7D41F59C6D3ULL, 0x6EEB7363992780BFULL, 
            0x390AA133F6737F63ULL, 0x2B7994724BE89B87ULL, 0xB9F664A265FB478AULL, 0x3F6ED2AE528DFF4AULL, 
            0x930863B3423F0354ULL, 0x746BB3D537BB2D5EULL, 0x345CECA026C8C3CFULL, 0x49018A0AD74BFD62ULL, 
            0x8BB51B0A37821EDCULL, 0x52BEBA6B2D9CCD7DULL, 0x8B64C95C1C85819AULL, 0xC4CFFBD73377BF26ULL, 
            0xF40CAD46E9A71868ULL, 0xE84414CD9723C66AULL, 0x1F0F19B6FA746636ULL, 0xAD08974F807FB507ULL, 
            0xB44058DC831BF7D7ULL, 0x400366FADF757B00ULL, 0x1FAD061C86E69DA3ULL, 0x1EEE39BDAF48F622ULL, 
            0x02616E7B90C7092CULL, 0x93F27CC973848108ULL, 0xE650309395F95EB6ULL, 0x1B83DD82060604EBULL
        },
        {
            0x32370C5BA1666079ULL, 0xACF3C39A5587A72AULL, 0x68348A7C7E84439FULL, 0x00C09798C06507D3ULL, 
            0x13D299634DA2032BULL, 0xDBA85FD8928024EBULL, 0xFFD34D67CD74DCCBULL, 0x2643B6BF003245C3ULL, 
            0x976863B8A4544184ULL, 0x327369DE488E3487ULL, 0x4E11834E1F4E7A1FULL, 0x7191227F63B61019ULL, 
            0xD604D625CFD2A725ULL, 0x235B04D9E1AACF21ULL, 0x0AB61E720DBFD973ULL, 0xF14C7BE052E33F57ULL, 
            0x6F7704A9D899BA1EULL, 0xF537741E3C08E8B9ULL, 0xCD30132EE79E1748ULL, 0x11BD69436812531AULL, 
            0x5C40BE90B827243CULL, 0x077EA890405E3A2CULL, 0xE9E76CFAD412F424ULL, 0x8672E0690BD94E38ULL, 
            0xFEFE9B67AF18D9C4ULL, 0x4306A3E3F129DC99ULL, 0x7FC0C5955B824F87ULL, 0x8CDF4E375DAE35B9ULL, 
            0xAF96373C252275BFULL, 0x4FD630312408A6FAULL, 0x84E42AA98B5DD715ULL, 0xDCAA9CB9977C454EULL
        }
    }
};

const TwistDomainConstants TwistExpander_Pollux::kPhaseAConstants = {
    0x08593DC6A2292603ULL,
    0xA56F3173309D21C3ULL,
    0xDFB4F3E5D7490520ULL,
    0x08593DC6A2292603ULL,
    0xA56F3173309D21C3ULL,
    0xDFB4F3E5D7490520ULL,
    0x0C2A943D9E0EDF41ULL,
    0x71ADF521CE092B2AULL,
    0x12,
    0xBF,
    0x47,
    0xE7,
    0xA4,
    0x87,
    0xBB,
    0x5D
};

const TwistDomainSaltSet TwistExpander_Pollux::kPhaseBSalts = {
    {
        {
            0x2B5A2C75936EED6FULL, 0xD4E7D39C14B8BD92ULL, 0x6B78E43D614A06DFULL, 0xF6AB51ADBBEA27CFULL, 
            0x93B0F04B47706C28ULL, 0x8CA27F6FF974F233ULL, 0x75E6C4AD0BF1A34FULL, 0x43AFA1D4954D4CD6ULL, 
            0xAAF798AE42F6AC0BULL, 0x9890DE8F69FFC604ULL, 0x1B9056B0C3A719FAULL, 0x0F17F539E6EBB111ULL, 
            0xF435C132BA79504BULL, 0xC360D41B99763932ULL, 0xD51206FE3841F4D1ULL, 0xA704E1247D686214ULL, 
            0x0C849A20D9EF6FD0ULL, 0xF0E132CCD9BC0B04ULL, 0xEB7838DE1DB72131ULL, 0x95CDB478803550BDULL, 
            0x4CB2AD7AB574FD62ULL, 0xC3B165FA06D6D1E5ULL, 0xB9E3831C462E0E4EULL, 0x464B171FE34EF51FULL, 
            0x04A3E29B4075ACFEULL, 0x11BA750C03AB49C4ULL, 0x8371F6012081A2D6ULL, 0x169683C57DECBCD7ULL, 
            0x555634AEAD79F296ULL, 0xE8CBFA74BCA83D51ULL, 0x699157DFBA8D5475ULL, 0xFA8FAF1DA0EAC497ULL
        },
        {
            0xE94A9BCEA72B88F5ULL, 0xE3B67FADF558C3F0ULL, 0x7580E07A8F738EFAULL, 0x30BB1B489EAB959AULL, 
            0xEFAE8A7F65E672D0ULL, 0x76C41E7DF454226DULL, 0x3C372D51A8AB848AULL, 0x57E4AD335A43848DULL, 
            0x749E79D55035981BULL, 0xB4835F42D6BCA1ADULL, 0x050402A27125F367ULL, 0x9FC1F5412EB8888EULL, 
            0x7736DD3B9C22853CULL, 0xCB72DE54B45877CCULL, 0xB61383248E2717B8ULL, 0x0E7EA95D547E2B38ULL, 
            0x3CE1C8C22BB89A36ULL, 0x7B6B80143A5ACDEBULL, 0x3B5DA8A216EE0BE6ULL, 0xD8F685B84F19BC33ULL, 
            0x3CA75E62C289F6DDULL, 0xE708EFB33057904EULL, 0xF33DB0716E655ECBULL, 0x86D15BA541EAD5B0ULL, 
            0xFEE3F3A0C630C3A0ULL, 0x6B5E3C17FEF8433BULL, 0x72B487F2A58D1DD1ULL, 0x33D1A9C06C81BF39ULL, 
            0x1657A7A4798B9B52ULL, 0xF77597A524B5DACDULL, 0x177E9D10902D4A10ULL, 0x874FA99C422A52F2ULL
        },
        {
            0xBEDBD4F3515B5FBAULL, 0xBCE2C4A2178D41D7ULL, 0xC8A0FCC7FE62F83FULL, 0x16871CB40A03BE73ULL, 
            0x7358ABD92A3429FEULL, 0x042740DF1591583AULL, 0x7DE7ED7918DA0B6AULL, 0x3E16AFD8B49BA1DAULL, 
            0x3E45953B80363F50ULL, 0x86BAA14397339A64ULL, 0xBA88C872D253D6E0ULL, 0x197F665E4AF51D6CULL, 
            0x437572DF58FDEE6BULL, 0x8B696270375C19B8ULL, 0x4CCCF08D869E4EC3ULL, 0xC5AC6101B7AC1DBCULL, 
            0x56D71504533B098BULL, 0x01CDD64AFF3F9F5BULL, 0x5DA9E7C9C392D66CULL, 0xBFF8E1963C087319ULL, 
            0x2A761733839D92B5ULL, 0xA436C4AD7399D1CDULL, 0x491DC3980F00B514ULL, 0x88D642FB2B2592D6ULL, 
            0x276E69C368A0EE50ULL, 0x072B60CBE6B3B797ULL, 0xC68891B83697653CULL, 0x171E6B135410ED74ULL, 
            0x57C4D8E128928DDEULL, 0x0E6FBB438F04225FULL, 0xB29F68246760D734ULL, 0x9560D28B3014647BULL
        },
        {
            0xF09A71586DED40A5ULL, 0xD595AE3D8FEF07D7ULL, 0x23EBD71D0F31D5EFULL, 0x7D40052CD4F3B466ULL, 
            0x6043BED9AC64AC10ULL, 0x194D1A54A11F26E6ULL, 0x229CD6157240E9FBULL, 0xB13FAD31E40A7DE8ULL, 
            0x46A052E8F171196CULL, 0xB63451A9356CFC9CULL, 0x02C3501084D93273ULL, 0xE6E7140256ED976CULL, 
            0xAE1B6CBC52198101ULL, 0xE572D1DF423724F7ULL, 0xE3C7CF3279D98D71ULL, 0x6B94D72601CF553EULL, 
            0x22061BEBFD419466ULL, 0x6DA7016B46AF67FBULL, 0x1BD4EB2F7443A732ULL, 0x55EA94A588BC7BF3ULL, 
            0x57452F7FCC96419DULL, 0x3B161D8184BC9C28ULL, 0xF2009BB0D14A77A4ULL, 0xBAEC04CAE78BBD85ULL, 
            0x4F69708A742EBC28ULL, 0xD58EAD479AD7F340ULL, 0x1D54BAC6BF9A6772ULL, 0xE8CED62BB0032C38ULL, 
            0x6CB774DD9432E081ULL, 0x11B17039DF592964ULL, 0x5519DDD0E6733F9DULL, 0x7BBC66D904EDC721ULL
        },
        {
            0xC274FB03D3A5FF0EULL, 0x06E28E9C59159DEAULL, 0x4976BAFF29EBFE74ULL, 0x5903AB4706649ABFULL, 
            0x6F51B65C83A20EB9ULL, 0xD6321531124EC2E8ULL, 0x9B3829FFB748D484ULL, 0x2813AAED129A5407ULL, 
            0x3C7BA1FD99DF3872ULL, 0xA691AF3FA6E38A64ULL, 0xCA6BE7373E2F9609ULL, 0xDF72E8544047EF74ULL, 
            0x48DC8704C9E56C63ULL, 0x5F9AC434EF17C35AULL, 0x9646EE6318BCD93BULL, 0x5046481A5720CC32ULL, 
            0x104EBB415CA81E8EULL, 0x7172F1B1515F4BDBULL, 0xF2C94095B225967EULL, 0xDDB4719902651662ULL, 
            0x9B3FFA3B3F57BF93ULL, 0x8DDD3C76221BA5A5ULL, 0x5E5863296CA22563ULL, 0xE2BECB6AB5400BEAULL, 
            0x729DEB59564A587FULL, 0x0B86DD4B5DFA1EE8ULL, 0x38E955DEC3C38F87ULL, 0x0C002E652E96D0DEULL, 
            0xFDBC49F2FC7449D3ULL, 0x111A3CB7B31EC897ULL, 0x368B7A4BF5802E76ULL, 0x20B2EDB23E089C96ULL
        },
        {
            0x291B29EDC1ABFFCAULL, 0x7B508BF42C874B94ULL, 0x466C9B71E22BE2A0ULL, 0x6522C6D449959B6EULL, 
            0x25717FBF54EFA1DFULL, 0x4D38F82ACB5CD638ULL, 0xCAB539F6016987B5ULL, 0x47DF2BEB9007A96BULL, 
            0xA09204EDDAC3FB89ULL, 0xCBFF9DC100B1CB24ULL, 0x528AA14D82E162F9ULL, 0xAE7C4C10528D9F2FULL, 
            0x5A1ECEDA4B56F148ULL, 0xED9CB52377EBBF5BULL, 0x3A92621DE5A2C7F2ULL, 0x98B3DFE99B0F53E7ULL, 
            0xEE3E41D981ECE146ULL, 0x70D31D3FC4B7E5DCULL, 0x0F8DED61FD2499F9ULL, 0xAE403553C61993F8ULL, 
            0xB44BC5382E5CBF06ULL, 0x69C33A6D0BB496F4ULL, 0x9CA2F3CD6E3E21A6ULL, 0x4A748825AD3BFD6DULL, 
            0x06EB3BB5DB33F9B2ULL, 0x0756AD4FBCBF2308ULL, 0x6D8FC866F1A89E2FULL, 0x74C2A917D22A92BBULL, 
            0xC577B2627EADFFC4ULL, 0xD0865ECED2ABCC56ULL, 0xF1B49507DF436802ULL, 0xFEECE197CE5BFCD5ULL
        }
    },
    {
        {
            0xB7F0166548B5B685ULL, 0x8443C2C92238B900ULL, 0x8D05EECB5E685ACCULL, 0x0E8E1F5DBE80D170ULL, 
            0x2BF5219F01C60E51ULL, 0x534B6CAC216B5022ULL, 0x5F51FF2C6AD9DFF2ULL, 0x27CA549B2134472EULL, 
            0xBD4936B74B1ED8D9ULL, 0x0ADD4F84DCA57302ULL, 0x502B3C2CD5F6012EULL, 0xEBA912E271786A65ULL, 
            0x661B6C0F8F752B31ULL, 0x64C3CB5EB7472446ULL, 0x483F7CF4609A23B3ULL, 0xA789413974403CBBULL, 
            0xB09BFDDAE67E58BEULL, 0x57EB376EC09EAC7BULL, 0xDE73D2F861D84362ULL, 0xC753AB1CEA8FC05CULL, 
            0xB637D93CC682255EULL, 0xDEA5DF13A0311B5AULL, 0xAB6CE47F6C28ECF8ULL, 0x4F6FB424B12126F3ULL, 
            0xF6C6B564AB810AA0ULL, 0x24DD335EE9B61463ULL, 0xEAB753BB31D6FAD8ULL, 0x01A529C41BBC7BADULL, 
            0x37C8395CCE097AFBULL, 0x4016D740FCCBF590ULL, 0x963A295DED61DFA2ULL, 0x5190253F8D287BEAULL
        },
        {
            0x82EF5C9459F2412AULL, 0x2006740B3ECBA894ULL, 0x4E0E2EFDBED965B4ULL, 0x50940056921D7F9FULL, 
            0x57236D242BE9FA44ULL, 0x75F122DC22F15515ULL, 0x62696E72A8FD64EAULL, 0x118CE2BEE577C6A4ULL, 
            0x60C3437E270F7BCDULL, 0x4853CB6B717EC6FDULL, 0x00E84845877ADF9EULL, 0x34CD9D62AC1480D7ULL, 
            0xFB2183213F59E846ULL, 0xC1DC6A2A3F44D15FULL, 0xB638D9F1B1BC067DULL, 0xF8176F1F4A97A1EFULL, 
            0xD2B3F1DC6DC3DAB6ULL, 0x9514158FE8549998ULL, 0xE57E961CBFC50119ULL, 0xA4F669B82ACF09CCULL, 
            0xBFE3C04F69300591ULL, 0x393EAC17EAAB2BDBULL, 0x55B2405451ECED96ULL, 0x733C488D7E9C3A62ULL, 
            0xA1C6BC7A36B1D70AULL, 0x8BF584EFFDB626DDULL, 0xAF70B881CB754458ULL, 0xE99F5C374497E290ULL, 
            0x5EDEE2B4B5056A7AULL, 0x008197A345675601ULL, 0x6AC6EB552D871FB1ULL, 0x122243708404C8CAULL
        },
        {
            0x966D44203503EA1DULL, 0x154E121CE3582A93ULL, 0xC79AD708B184A617ULL, 0x966120D135A942A3ULL, 
            0xAC61F1F840A40DADULL, 0x66F4AA35BA90D518ULL, 0x26BE0F2820150D70ULL, 0x73518BA8DAFCD264ULL, 
            0x692FE85B9D6E6CBEULL, 0xE60D876B1BE4654CULL, 0xA87647551802C874ULL, 0x4693D444BBF884BCULL, 
            0xF1B8E5369C53FA24ULL, 0x1DF316370FB14E3BULL, 0x6B7825B1B61D5B5BULL, 0x9A76D11B2BC30BF2ULL, 
            0x6D81F8A7673B8914ULL, 0xB57BC0F1B20B990FULL, 0x55538319286D4AF2ULL, 0x800B559820D6364DULL, 
            0x530E36DE3ADF065FULL, 0xE6091010B89CFF26ULL, 0x509B6A786919349BULL, 0x510D25B8AE0E437BULL, 
            0x6FF0F3DAACEB136CULL, 0xF6256255D06A160EULL, 0xEFF29851004983AAULL, 0x8A38A9F5926045E8ULL, 
            0x38C47ED9829A8AFFULL, 0xB77AB32FEBC626C9ULL, 0x40DF54FE224C3305ULL, 0xEE731CB94E18029FULL
        },
        {
            0x3146629FBF64F44EULL, 0x41D2B43158F18342ULL, 0x5ED838E623339DE5ULL, 0x37BB047B871F5530ULL, 
            0xFB8E1E178E33DD0BULL, 0x72B3409190F2E760ULL, 0x824DB23DDF345657ULL, 0x0DA3AC40A1EA0444ULL, 
            0xC3592602895B2CA8ULL, 0x48BA7D9BC5CEC38AULL, 0xAF5C4DACA3A9AF8AULL, 0x5426EBEE4C182F5EULL, 
            0x92CD9F1BEDE70CA4ULL, 0x026634C173D875D5ULL, 0xD42FB4EB16EC8789ULL, 0x354038891640080FULL, 
            0xFBAD60C76C0FABFBULL, 0x66F0FF67A889FCD2ULL, 0x4D8A227E116EC100ULL, 0x1440178063DCBB4BULL, 
            0x38E739413B390EFFULL, 0x3CE5F7F0D5EB262BULL, 0x7F25626C9D7335DEULL, 0xB4C32D2533157E4EULL, 
            0xA791BEA1413452B8ULL, 0x76FF3AF8F6316F03ULL, 0x3CD0ED7817800EBCULL, 0xF46179E239909908ULL, 
            0x137E3F523D87AADCULL, 0x6D0B355C98A92F94ULL, 0x9471ADABF5525018ULL, 0xB969F5142EEB38CFULL
        },
        {
            0xFA139E58CDE5A8B4ULL, 0xF7CAC22CF71EADE5ULL, 0xC7D137AC1C6C2E50ULL, 0x839076263C2523E1ULL, 
            0x6ECB1AF0C574CCF9ULL, 0x8B2D2EBFB084C6FBULL, 0xDCF9B1BA83C27E66ULL, 0xBA5F1A71FD9797C7ULL, 
            0x3666906F3C190F84ULL, 0xD895A84E21B23914ULL, 0xAECF131DCAD85836ULL, 0x21FFDD4AA4087310ULL, 
            0xFD74A05D48534D5CULL, 0x925848D8C2D678DCULL, 0xC85656AA37CB7A38ULL, 0x70344B69F3918546ULL, 
            0xCA9798B3DFBE2642ULL, 0x684466A6C7DCD4A9ULL, 0xBC2F73C77FEF525AULL, 0x1714D5A143475323ULL, 
            0xB69A0956412351B3ULL, 0xEF615A084F86CD35ULL, 0xF70762763215CB03ULL, 0x19D6B6545ED04400ULL, 
            0x4438F10BAC939CB8ULL, 0x13BD3C7D0C4C01ABULL, 0xDE7806228C6D0974ULL, 0x32D8D1E8044FDD57ULL, 
            0xED4ABD328ED9F857ULL, 0xE1482C2332DD7866ULL, 0x802A8B326D13870DULL, 0xB9466F01AF60E9BBULL
        },
        {
            0x544F9127CE93B86DULL, 0x27AEF9AC59A53CC4ULL, 0x1C93FB5CB810BC64ULL, 0x04DAA44BC4C4F759ULL, 
            0xFA46457E35CDFA07ULL, 0x5D15A3B14A3D4D5FULL, 0x4333DE37BD5AC248ULL, 0xF0D8209231113696ULL, 
            0x5EA03D60CB4CAEBDULL, 0xF54C174FC63D6C4EULL, 0x6737E27B9A94325BULL, 0x54629D4F78C67368ULL, 
            0x0C8D7FFA94C7C947ULL, 0xDA0C7648291A7E65ULL, 0x0E6208F6D8CDEB11ULL, 0x1A9A4E14EEEB25F9ULL, 
            0xE2914145166F0EACULL, 0xFC706146ACE85031ULL, 0xCD8C33395120AD7BULL, 0x8BB25D1ACE4C9F2FULL, 
            0xFA485621D237B843ULL, 0x01C0AAB4C1D08346ULL, 0x6D508C42DB1D93B3ULL, 0x0BCF51E5789C5757ULL, 
            0x308F450AD4DA116EULL, 0xFC78AB19EB393830ULL, 0x1BFCEB0C264D6C5AULL, 0x37F8F55AF24CDE1CULL, 
            0x936A4969938BFFF3ULL, 0xA2737C5BDC6352CBULL, 0xE9B8F29B865BC3B9ULL, 0x28BF0FB85F2E85AFULL
        }
    },
    {
        {
            0x26424C0FEF2703BFULL, 0x2EF61943D50105E8ULL, 0xE1AC5057C1E74F4EULL, 0xE67D93D246B31D37ULL, 
            0x319D60B7B1F33F03ULL, 0x6C7ADF432E2C8776ULL, 0xFA72BBF1A31358E2ULL, 0xA94A8F6A8B850071ULL, 
            0x7424962DA3DBB890ULL, 0x4AE25F5CFA0E59D3ULL, 0x483709D62FFF953EULL, 0xE42FCFCC5466EB66ULL, 
            0xA4B058A249895C0CULL, 0xF29B5365E889406FULL, 0xE0993875DED2F09EULL, 0xA4FD099A988EBAFEULL, 
            0x92B0D9DA27A0F3CFULL, 0xE7F2E99A5C128FFEULL, 0xA486BA56DA9F3D43ULL, 0x44911B12FE41C524ULL, 
            0x873CDA65A5DC331FULL, 0x4E0B9DE25424C0BFULL, 0x126CA26BB3AE6897ULL, 0xBEE1B5DFE2C38A87ULL, 
            0x49A147AD6898462FULL, 0xD11B7421E577AB64ULL, 0x95B1D65730794C82ULL, 0x59D7610F5610FF46ULL, 
            0x416E2F9B354B13A3ULL, 0x5A64A45BF34F6168ULL, 0x1B0776B22E0D4CA4ULL, 0x4900AC8A36C1580DULL
        },
        {
            0xAE4822098FA79F29ULL, 0x9B5202CBE91211A6ULL, 0xE5A21B0AEE99BEC2ULL, 0xBFA5A1DB8DEB1A9FULL, 
            0xBBD5C0EC8E995E43ULL, 0x47C9CD88ECB41C26ULL, 0xAE28D977A33221C4ULL, 0x6580925336A9A117ULL, 
            0xF61137B8DE10A8A0ULL, 0xA6490A4BE7079710ULL, 0xC6B58A681459DA75ULL, 0x2DD5887ACF8DBF68ULL, 
            0x06C16FDB09669DEBULL, 0x974F028564450D6FULL, 0x8B9667C0A30F2645ULL, 0x36135701B14FA65FULL, 
            0x2F23A37949C8453BULL, 0x13D9CB20102E53FFULL, 0xC0125009AA257E97ULL, 0xBB654C45312B61AEULL, 
            0x8876C2E0CF493C34ULL, 0x5B507DBFB019CE95ULL, 0x178A8AF598FA5757ULL, 0x9D9E1D5292A268A9ULL, 
            0xFF3788F838F1FFFCULL, 0xE33251A591A6165FULL, 0x2027C6E27C7C85DEULL, 0x7C58FBE600A38E3CULL, 
            0xD2C17485515D8413ULL, 0x75329DD5316CEFF5ULL, 0xB85A858FD44CC759ULL, 0x7623F5404FC0DC50ULL
        },
        {
            0x24F2B8A13C0A02AEULL, 0x8BBF6FD47BAC396FULL, 0x89D54B129E3B9142ULL, 0x90D8575C3F6DBA78ULL, 
            0x71F86608834E10EBULL, 0x95EBB31F4568CEC1ULL, 0xBD4B90DDFE1D0CDCULL, 0xC256EDBD54F7BD25ULL, 
            0x7FAAB75BD0E34A15ULL, 0xBBBF4E2A50DDB032ULL, 0xAA320D3FC9654B08ULL, 0x070245F70FEAB766ULL, 
            0x9A3E5514D484BB53ULL, 0x7340BA347EF5D5F3ULL, 0xA3EA76121D5F4E1DULL, 0x37659E69B30BCF88ULL, 
            0xDE435E92CBDBB326ULL, 0x88034E514A1E1D78ULL, 0xCD3F3FC588059128ULL, 0x271350BAB779342CULL, 
            0x2CE3C2050EA5D63CULL, 0xE1B9D67E814FFF00ULL, 0x11DA200CFE367CD1ULL, 0xBCD00FDF28E650A6ULL, 
            0x30C38373ECCFDF7BULL, 0x41CDC42555B22D59ULL, 0x8B6A204AB7EAC639ULL, 0x20FEB73BF5EF3809ULL, 
            0x0E10BC812C28C539ULL, 0x2AC7459C9FCE0FC8ULL, 0x29EE54EA1DD6BDEBULL, 0x49569E82FE9E2AA1ULL
        },
        {
            0x673B4B549792F699ULL, 0x81A268C105904539ULL, 0xAE184DDA7C645CD1ULL, 0x76D02F1970780AC7ULL, 
            0xD946C6E01B768B30ULL, 0x9487FFF0F3397E60ULL, 0x5A8459F3AF964C59ULL, 0x485F8AD1DD70C0C9ULL, 
            0xC0543776449D6860ULL, 0x2D19D1E0D57BC2BFULL, 0xCB7D8FEB73CAC26FULL, 0xBC6036AF667A07E2ULL, 
            0x3ADCDE7317E6D289ULL, 0x6CFA4BFCE17FD1A1ULL, 0x7E7539F0E8CFA227ULL, 0x7BF0003815B39F96ULL, 
            0x3C2F480A00AFE55AULL, 0xD984465124E9485BULL, 0xF09C6FF8140E5930ULL, 0xAF23792E0DEA1958ULL, 
            0xA346BE4189BB03A7ULL, 0x325481D3835AA858ULL, 0xEB9F7C4217D3F748ULL, 0x5F4C9890BCE78440ULL, 
            0x09FC3FC98FC88B54ULL, 0x11C3A1495C68ABC2ULL, 0xF6FCA3B1480F9910ULL, 0x6FEC5BDDA0CBBD66ULL, 
            0xF3FD28FE0C4A5CEEULL, 0x48F3787FEE795694ULL, 0xD8ACC7950611CD39ULL, 0xF46555F38F53E1C1ULL
        },
        {
            0x4C07218D5C5B3252ULL, 0xDDAF22B6722F06A3ULL, 0x6B8DC3DCF68FE8FEULL, 0x15A095EFDE782A4BULL, 
            0x98DC797472B19C83ULL, 0xC86EB1D411413762ULL, 0x9A0C782EC97F9863ULL, 0x6213A2B6D0DD85B5ULL, 
            0x87406A46F9AE206EULL, 0x961FA9572A7B3151ULL, 0xBA995D35A50353E1ULL, 0xA98016C14BCB04D6ULL, 
            0xF10CC13544CFF499ULL, 0x3C163DD400B682D9ULL, 0xEBD75BCB64C15761ULL, 0xACF3D605025DB5CEULL, 
            0x81962E45DDA2F6FFULL, 0xE8CB969C82DC75D1ULL, 0xE503C19BBA11315FULL, 0x07F73B5BD05781CEULL, 
            0xF32FB19D1951DE6DULL, 0xD7333526AB192FD4ULL, 0xA1BEFF40E24955D7ULL, 0xE6B294748960A87DULL, 
            0xD012DFD5175D5F94ULL, 0x80AC42BB575251C8ULL, 0x2AA94AAE15EB729BULL, 0x77CEE87C9B1A78A7ULL, 
            0x4B5F02CD6FC73C97ULL, 0x5CFDF20430E6E716ULL, 0x8BE4CC0FE45A53B9ULL, 0xF27DAFA147928C32ULL
        },
        {
            0xE97F2B0BABAC4859ULL, 0xC5A80BF90D89631EULL, 0x9F80F7B78D06BA3AULL, 0xCC869CC9FDFC1C6EULL, 
            0x56DC09FA9A9DADD5ULL, 0x681D5FF8285B0D02ULL, 0xFF8FE714546FA710ULL, 0x247AF6E651EA6A72ULL, 
            0x8C5D21553A4BD9FAULL, 0xBC53DC7B4397106EULL, 0x06604DAF963C14D0ULL, 0xFFEF7CBAD8509E80ULL, 
            0xFFE2E41C4FBF3543ULL, 0x9D611AA9243D33F7ULL, 0x4DD6BD51B1E25AF6ULL, 0x04A538B7FAA99C5CULL, 
            0x7D7615F12D77C7CCULL, 0xAEBC212830F50BD9ULL, 0xDA5B8B25A90A1833ULL, 0x9B5EF31836BF41FAULL, 
            0x03702BD2EDEE8986ULL, 0xE39FA4CF01D04EABULL, 0xB5D8CDA8373CDF25ULL, 0xC1E2A4B2F40F6C7EULL, 
            0x62E23D5161B87206ULL, 0x0DB1089BB4510C01ULL, 0x133AB2ADF7DF0C72ULL, 0x5C84B765750659D8ULL, 
            0xB63FBA142781F89DULL, 0x0C0C0BA5E3A9AB71ULL, 0xE158B6F1AE6B02BCULL, 0x19E64635E1F90C46ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Pollux::kPhaseBConstants = {
    0x1DEF5DD0FAD62D49ULL,
    0xB8A0339A2D3A3C17ULL,
    0xCF7D71C9D9729AB8ULL,
    0x1DEF5DD0FAD62D49ULL,
    0xB8A0339A2D3A3C17ULL,
    0xCF7D71C9D9729AB8ULL,
    0xA6E267D8BCAB166BULL,
    0x0DE8261D8349A86EULL,
    0x10,
    0x0E,
    0x5C,
    0x12,
    0xBE,
    0xA8,
    0xAC,
    0x31
};

const TwistDomainSaltSet TwistExpander_Pollux::kPhaseCSalts = {
    {
        {
            0xF78629278450DDE4ULL, 0x32A566121599A2E4ULL, 0x7D5D141D429E6668ULL, 0xC1BD1FF66AEE0C5DULL, 
            0x2C787DD21DD52C45ULL, 0x62F5DEF967BD329DULL, 0x02F66DDAB47086F6ULL, 0xCFAFD661AA982FB0ULL, 
            0xD30D8D637795893CULL, 0xF44A85845DDAE74FULL, 0x10A69643BBEC02B3ULL, 0x0F15C4D00EA8875CULL, 
            0x94BDCD0D8CB0BE11ULL, 0x2601CED67771067BULL, 0x3C0ED8C82B87AEFBULL, 0x434D30B295D2B19EULL, 
            0x9EA8B8501D8ADFE0ULL, 0x677304D48C03BFD3ULL, 0x54839E168E3B9AC8ULL, 0xE2F907910CF77AE5ULL, 
            0xAC6B825BA3D1DB52ULL, 0x69CC56BFB9FEF6A3ULL, 0x89027D95ADAFC51AULL, 0x5D12DA72B28D3AF1ULL, 
            0xEC4C75E5EE4FC1CBULL, 0x815EC704615359FEULL, 0x81C3AC0CA8273947ULL, 0x5803A403B2927740ULL, 
            0xE5A79CDF9BFEB0A4ULL, 0x4D4131008B004B85ULL, 0xFB8EB2D390519599ULL, 0x918D3DB9A2E3C5F4ULL
        },
        {
            0x28260498C07FD55DULL, 0xC9E79C4BB5768398ULL, 0xD5D20B662D0AC9FAULL, 0xB4D8D994069E89FDULL, 
            0xDC0EBDDDDFA73DEEULL, 0xDF19302AB5B2DF60ULL, 0x87481C55D33C5C0AULL, 0x7BCDAEB3C1BFECF5ULL, 
            0x989A6AE0CC03B920ULL, 0x29FB5326700267D9ULL, 0xF62C7BFD14047BBDULL, 0x26B72A18AF01837CULL, 
            0x39D6FAE4C0E5A0DFULL, 0x84F4CFF2BAA9D59BULL, 0x441E1B8FCA52475CULL, 0x5860C6FE1457F4F1ULL, 
            0xA7E7F60EAECB405AULL, 0xD0AFD568E563D457ULL, 0x1A943124EB2388F0ULL, 0x700058C586A82536ULL, 
            0x64842EB04A4D889AULL, 0x3FE294741717CB63ULL, 0xE40A5B2888270D13ULL, 0x2DECC81D8F9E3A80ULL, 
            0xD66EDEC0F7643902ULL, 0x225711CDDDA85A43ULL, 0xB2C0B08C328176F6ULL, 0x6310079DC871FBF9ULL, 
            0x1370A704E22057EFULL, 0x5DA5FA09BE25101AULL, 0x8A04AB84C1C89BDEULL, 0x5DC17FBA3525FFB2ULL
        },
        {
            0xF5CBF94F514B34E4ULL, 0x40CB743D61A5609FULL, 0x32EA2C7A374B0228ULL, 0xF30239B6A20B861AULL, 
            0xE10B791A95727478ULL, 0xF4FA7BDD94C92910ULL, 0x4063A1668BC2CE4FULL, 0x24197CCF8D36E3B0ULL, 
            0x0F27BC2DB5800119ULL, 0x4DDFACD3F0BE16F5ULL, 0xAF899CD57C851078ULL, 0x9DE22EA50A719557ULL, 
            0xB2300A05322F2946ULL, 0xD8F9F6359DA475F2ULL, 0x9CA53880F959191AULL, 0x5C64001BDADC3D27ULL, 
            0x5B5B634C27218175ULL, 0x0DBB6022ED0FF928ULL, 0xC0D55BA93B1CD760ULL, 0xA358D8D9C20D5FA4ULL, 
            0xD8EE07D55741D68BULL, 0xA351E589DD91477BULL, 0x5E9D91EB90BA024EULL, 0x392CDA4E3957A00FULL, 
            0x7484AC611E0A5418ULL, 0x46D4BED3902F7CBFULL, 0xE1AA8C2D0487F90EULL, 0x02ABC31F4BE83C07ULL, 
            0xA9DFCCA8C635A76CULL, 0x86547EB6B6EAD1F7ULL, 0x3566F43B3BC5E78EULL, 0x0363E4822BD46838ULL
        },
        {
            0x85AA4852B8DB4755ULL, 0x2AC7A36D4469AE11ULL, 0xEEC5A78C87FA3948ULL, 0xC34AA01FF9A4C548ULL, 
            0xFA2B7C900A191DB2ULL, 0x52342A7F85A04927ULL, 0xDB40DA3CC2D42B12ULL, 0xDC2A673762B38E19ULL, 
            0x54E8B398D9EF087AULL, 0xB68318694B9B9AEDULL, 0xCF7A062709A733ACULL, 0x1954C28331EC7351ULL, 
            0xAD16E7A919D33AC6ULL, 0x72E28B4DC9EE9824ULL, 0xD2DE247A21E7638AULL, 0xE28D214268AE4FFAULL, 
            0xC798DDDA5813E3D0ULL, 0x39C7F8E394C14158ULL, 0xFEFF432A8604302EULL, 0xE702314E03851F46ULL, 
            0x9571497DB027D4F2ULL, 0xB6CAB2C76BEE92C8ULL, 0x1F6B806F60FC23CEULL, 0x01A1CA295B4C0564ULL, 
            0x36769EA88552EA06ULL, 0xC2E8507DC326D325ULL, 0xB3E084382371E886ULL, 0xD8506B36F3DB39B9ULL, 
            0xFFA22BDD26CC9039ULL, 0x271861B09D90B93DULL, 0x3EBCF7C971BC3ADCULL, 0x3E0CE1ADD52912A3ULL
        },
        {
            0x56D9195F6193F18CULL, 0x0EF38D72B57926A9ULL, 0xCA44976CC3D167C2ULL, 0x2C727F67EB0A25AEULL, 
            0xCFEF6665EEFD4CB0ULL, 0xE456672958044A70ULL, 0xDCB363FDEA84793AULL, 0x12FAB64E57A45A34ULL, 
            0xA0859C2B69533AC6ULL, 0x13F1443F71E2EF97ULL, 0x3A05BBAE397DB222ULL, 0x9033EF69B54AB93BULL, 
            0x53A69A4B3AB15532ULL, 0xCDA44B3989F6CCF6ULL, 0x2A46F730F055B0E0ULL, 0xC8F462B09477BDD2ULL, 
            0xB4D2D32852FD7B32ULL, 0x148EB4FCAF51F9C7ULL, 0x6FBF597A76BFEF46ULL, 0xB5B9C4B724E78EECULL, 
            0xAFBCDAD2B297E808ULL, 0x162CABB6A953E8DBULL, 0x4890EFB6DB134F57ULL, 0x2A92FE5EFF7B660AULL, 
            0x6FACFE1B27DE3143ULL, 0x32736091AF88CD48ULL, 0xBA0FBEB8FCDEA825ULL, 0xD339A7924EA48088ULL, 
            0x191C63CBD6EE06D6ULL, 0x90BC328224B4FE69ULL, 0x179CC4EF86F01966ULL, 0xDAC0DE0111B8AD70ULL
        },
        {
            0x121699A72FDE68CFULL, 0x6DD5B49E624BD406ULL, 0x3427B121B25AE53DULL, 0x8E9DD9E36260CB40ULL, 
            0xFF4F622B28ED926FULL, 0xF6CC5302D69B14B9ULL, 0x863B4497AC1E25F7ULL, 0xA36ED72A033CD08CULL, 
            0x21CE19A1B00011C2ULL, 0xEE84B512309FA5C8ULL, 0x9163D8513C2AA01BULL, 0xDC1837521D9F999EULL, 
            0xCA19B8C7D5725B1CULL, 0x639AEDE2D991D96DULL, 0x778B8F27E525C8E7ULL, 0xFF4F6BD687EF8277ULL, 
            0xF456F6ABE9D80A16ULL, 0x2F5D607ACBA0A1D8ULL, 0x1DF2C856759F4F7EULL, 0xAB6357F392B155D2ULL, 
            0x7B4A699D9DF46F22ULL, 0x13AB39AC5BCEC37BULL, 0x8D26DE0564E718EBULL, 0x87FA365AF75BAC15ULL, 
            0xE6339C89666BAF1BULL, 0xCD173E903E8AB2F6ULL, 0x2BF48916296DAE90ULL, 0x56E9EA4540186829ULL, 
            0x203D17152031F8D3ULL, 0x2CE160BB6A4C853FULL, 0x01138F08ECE97E12ULL, 0xF2DE946F69FD9DCDULL
        }
    },
    {
        {
            0x48FCD0B11D1F1850ULL, 0x6FF6788A98BA9DA9ULL, 0x9EE44F2B4A741791ULL, 0xBE24323BF44C7D4AULL, 
            0xBC13B30C710E6B3DULL, 0x56ABA709A95BC40BULL, 0xF7AFFECAC959C109ULL, 0xE6AEC30136818889ULL, 
            0xEB63F8EDC743519EULL, 0x125CA7AF7C3B7291ULL, 0x9955E4E8E3CB9AB9ULL, 0x79274A1AC2FE4837ULL, 
            0xE9BAA22B90405E61ULL, 0xEE3496E441108685ULL, 0xA7828C5F4A26BBFCULL, 0xA1B259D3C007B920ULL, 
            0x2972E724E51FCA4EULL, 0x4682A59FD9C862C0ULL, 0x16C1D19E06073ED9ULL, 0x6BA9D00E5F76154DULL, 
            0xBC9E0D9C351D3F86ULL, 0x5FF0BA98055CECE6ULL, 0x1C65921F9031CA5FULL, 0xD1F18412C9F226A7ULL, 
            0x8AE7620F89ACF277ULL, 0xA4BB039CEAA9D0B6ULL, 0xA305A6410E1887E8ULL, 0xFE6BAD6350FB07B3ULL, 
            0xD7954A63ABB9CF41ULL, 0x2EC742DB63238175ULL, 0xC5D39F39FF452244ULL, 0xE923D00542182449ULL
        },
        {
            0xC99EB0BECB58B97BULL, 0xBA0A093B5F742F71ULL, 0xF8E2C566924E8352ULL, 0x446C96C2986B07CDULL, 
            0xB164A3653150353FULL, 0x5195A274CFAE6B5FULL, 0x1DD28E8B324C365BULL, 0x5C2F01A13AC12E6AULL, 
            0x86BF1A5894ECB222ULL, 0xEAC3790877A923FFULL, 0x81331BD0E6D44CE4ULL, 0x31BE32A4A0CB7CB2ULL, 
            0xF83F854FACA85492ULL, 0xE7134769C01679A6ULL, 0x51388E2B2973EBA3ULL, 0x4F70D9064890D21FULL, 
            0x9A6DA5C55C110060ULL, 0x8D6F50ADB89A7AE0ULL, 0xB60083C556FD8737ULL, 0xA74D26FB50C99502ULL, 
            0x722DD71913869889ULL, 0x5A2353E8C2E78733ULL, 0xC98084AE58682A59ULL, 0x3D3790440C9CACB2ULL, 
            0x15618858BEFF0B01ULL, 0x78B1A9C39033F344ULL, 0x9D5285378854B15AULL, 0xC67B2F4AFFC1D724ULL, 
            0x63F4F7E8B639E5D9ULL, 0x0A89D773350B6B8CULL, 0x5BA9D53EB4B653B6ULL, 0x7F0BCCD70C98130FULL
        },
        {
            0x2DF60AEF4F121860ULL, 0x3538486F84C39CB8ULL, 0x4AF072958798B7B2ULL, 0x4D6463ADAB5A82ECULL, 
            0x602B8D0E72457DC0ULL, 0xCCFCAD4490C40017ULL, 0x8A0A4EE5A2063DAEULL, 0x54C35E3B3A1AFB1CULL, 
            0x92D7E8B17FAB1840ULL, 0x8EDE4BCF452FD67FULL, 0xC76B632794E6C150ULL, 0x372236DA99116C64ULL, 
            0x784B76475AEC5E23ULL, 0x6D583C97DBE5A86FULL, 0x6101AD83101323BFULL, 0x66A3C7FCC7FCD457ULL, 
            0xE353B442CFF335ACULL, 0xFF73D33886317631ULL, 0x8276E04C61F0E284ULL, 0x78E76F9EB293B5FCULL, 
            0xE89388771A0C86BFULL, 0x292BCC634FA0E640ULL, 0x00C27985586F3D1FULL, 0x755E1423D327F32BULL, 
            0x0CDEF8A5D570130CULL, 0x6A7AB0EB0032922AULL, 0x2A25B606237C4539ULL, 0x5F13C301A2E8CAE6ULL, 
            0xF9878D3138841CBAULL, 0xD616DD3D4E6C7DDFULL, 0x5BD3A3FBD8BC96B6ULL, 0x221789635CB839EAULL
        },
        {
            0xDA1327BF025E9622ULL, 0xD13F35D220748F7CULL, 0x8D9CEE398D63725EULL, 0xD898876DFF451C40ULL, 
            0x394677460931B3C7ULL, 0x37292F8D2887BF1CULL, 0xD9C0AFA285B810F1ULL, 0x7CADB2B01827752BULL, 
            0x8BFD7679E2E39018ULL, 0x0ECEA0EFB571A92CULL, 0x4FBA4C9280AE9838ULL, 0xF0FDA3AD6E5D2EF8ULL, 
            0x26A73C7A32D7A6B8ULL, 0xD1CBA9954DEAE5D5ULL, 0x96146766D3567E9BULL, 0x1B2F40853B766EFDULL, 
            0x478260EEF145EEC1ULL, 0x166C9D802C67027EULL, 0x4F5352B74637699AULL, 0xD1B05F578ED70E71ULL, 
            0x5324DC7D6FC46745ULL, 0x63BBFC2E97219F80ULL, 0xBF30B9C19FACB9E9ULL, 0x01E2FC790F5E764BULL, 
            0xC62C7D659CA04541ULL, 0x686E3361D1A313ADULL, 0xDA475EA1A8EF6E1FULL, 0x269709E431F685BBULL, 
            0x4BC919C649A9539CULL, 0xEA1E84A7FE73F325ULL, 0xE4A97ECF61E5CD78ULL, 0x5E733C3E6A1D0788ULL
        },
        {
            0x92E1DF80086053D1ULL, 0xE36F3503EEC8FC06ULL, 0x0BA830874B778439ULL, 0x5C54B20F755E9734ULL, 
            0xC64BE174AACEB114ULL, 0xF55361009E0B6877ULL, 0x6FEF8802890B8012ULL, 0x9BF065376036446AULL, 
            0x05B2E19723B80C9AULL, 0x913BF07A4708C76EULL, 0x9ADE524F68D85300ULL, 0x9A3D794505770139ULL, 
            0x3349D02D1571CD74ULL, 0x086C58F3ABDA8766ULL, 0x49354279474C55B5ULL, 0x75B6E27D37B4BE2DULL, 
            0x4F9AF633F66F7ADFULL, 0xAC3E194A28940EC7ULL, 0x49E72D8DD4B1B83DULL, 0x18948AFEE882DF68ULL, 
            0x1F89A19A00E37DF8ULL, 0x700EDBA4C447318EULL, 0xFF516EC58C5A43FFULL, 0xBB797E17FF01F104ULL, 
            0x06279CDAE7A1C766ULL, 0x22B14E7F54B9315AULL, 0x26DC3CAF4F407E2BULL, 0x36985F97096D2B17ULL, 
            0x1B556035E4C4FDAAULL, 0xAE726C9BFE89A684ULL, 0x89F4DF195D01D9A6ULL, 0x14A7497537F539DFULL
        },
        {
            0x158EE65CBD3EDE5EULL, 0x553CF6F185B15154ULL, 0x8FE939DBBC707F1EULL, 0x9177628A6BD541A0ULL, 
            0xBC92CBFA341525F0ULL, 0xF7DA08268F8A108BULL, 0x8A756FCA2CF5F761ULL, 0x1EFEFDA7C4371A9FULL, 
            0xA5B64F97F7C933D7ULL, 0x25D4B17F47C3625EULL, 0xDB255B1CCF34A806ULL, 0x25A759CEFE50DC6AULL, 
            0x131E52955D53BE20ULL, 0xD0E4426E21D1EAD6ULL, 0x5BF1D6AE71E09836ULL, 0x941D691C19EA361EULL, 
            0xF2636C332425F88DULL, 0x6F2AF00DB2733791ULL, 0x398DDFE78755129CULL, 0x7706CD48E920EB15ULL, 
            0x874D813821DB584FULL, 0x4FC300F3A0EA2EDDULL, 0x687093357B3D1EF6ULL, 0xE0B0517578F4C496ULL, 
            0xE3921C00077F3027ULL, 0x553B5BC3E43877FEULL, 0x252D835672BE98E5ULL, 0x24286C08F6C801D9ULL, 
            0x36C84A69E0B827ACULL, 0x389D98EE22875BF1ULL, 0x9BFA74A95577BA36ULL, 0xCD81D487B9103ACFULL
        }
    },
    {
        {
            0x10E418101F3BAD98ULL, 0xBCE269889161701FULL, 0xD59A9AC02C472D01ULL, 0x39ADBDD072AE5298ULL, 
            0x5966F76D7D2C55A5ULL, 0x07441894BF8E069CULL, 0x4753C744E7F8E9F8ULL, 0xCFA1B324D1940991ULL, 
            0xE34DD410F16A7637ULL, 0x1DD8DACFD6362EA6ULL, 0x6922C07DE5BD0E3CULL, 0xF4158B1D9C72866AULL, 
            0x2FC0996F7968784DULL, 0xEA73544D7D7BABD5ULL, 0x13ABF56CB8E17159ULL, 0x6CBF88F01419BE8EULL, 
            0xFE3FABA1A441C5C3ULL, 0x35D550ED4102DBC5ULL, 0x796C732DEE8D6DCEULL, 0xD60AD1F737A44A47ULL, 
            0xBA104E326B32F81EULL, 0xCBB20905204698FBULL, 0x7C2AC49F4F09740EULL, 0xAD3A4C2A0AE6A84BULL, 
            0x86C47B85028EC65FULL, 0xF2DC4B00E197417AULL, 0x9E5ECC4A5D60CBF6ULL, 0xBB9F31D41E617B1DULL, 
            0xB540722C9DC87EA1ULL, 0xA838478B5429699AULL, 0x20C958FC3C8E9F39ULL, 0xFC91F735FC2AE824ULL
        },
        {
            0xA33356778950F01EULL, 0x83FB1BDEA254B796ULL, 0xED01C6BD7464FA7BULL, 0x6AF82450D8A0DB8BULL, 
            0x2BA0F9569D193CFCULL, 0x3B452210620D7F32ULL, 0x9D58B82D685C65EAULL, 0x07504DCC367A4161ULL, 
            0x5B40F3E3490E284CULL, 0x02D99BB5C4CF707CULL, 0xBB87446032824A5DULL, 0x8205E809BC8C3B02ULL, 
            0x9156460C9B25B358ULL, 0x4A71444DD03F4BFBULL, 0x1546DC85AB7591C8ULL, 0xEDD6F3C1AD5E9FA1ULL, 
            0x124A85B1BCD71A93ULL, 0x7CA7B5410C582738ULL, 0xD2C16B6BAF991A3AULL, 0x622D06264C8698D5ULL, 
            0x0BBC76F7D463899DULL, 0x22EF96855957A352ULL, 0x228C0E206BFC2FD4ULL, 0x9E730443AF582592ULL, 
            0x7070BF8527ECC3F0ULL, 0x845C8373ACCF7F6EULL, 0xF3B9282D1864967EULL, 0xD2770FC2B2BEACAEULL, 
            0xCC248FCE11CFB51BULL, 0x43B39C80E4B0E3FBULL, 0xC083A8C8AE6B40C7ULL, 0x1AA732581E3DCCE6ULL
        },
        {
            0xB3B97943E47BBE4AULL, 0x0FC3B2116FEDB572ULL, 0xEA7E9BD1A5A2EB71ULL, 0x6E7E0BE4D56FC75FULL, 
            0xA67357E97A4641A6ULL, 0x89C6FFA98C110C5DULL, 0x43DF8A059DF02990ULL, 0x2BCCE384257DA575ULL, 
            0x7580C25EF37D8805ULL, 0xD75AC1620AF6203DULL, 0xA4FCA3E9D1316557ULL, 0x4916AEF59E8E7EA6ULL, 
            0x5D6AB1D7987B8A34ULL, 0xBDC83620272FC8F6ULL, 0xE9DB27F01A04F3E0ULL, 0xAED09577B4883288ULL, 
            0x911095EA182C1BCEULL, 0x0CB4842EF2A0374BULL, 0x132BB994F5EF11BFULL, 0xDE9DC3F71A71EB9AULL, 
            0x6C72C0BD8F689BFBULL, 0xD44CE09A396C9C25ULL, 0xF955B37D35655A1BULL, 0x3CDFA503126FB25BULL, 
            0x59CE1C3442094C9BULL, 0x1EA6BE3FCC8A67B4ULL, 0x0A1222CEB9825BEDULL, 0x8BDCB157C48F26CFULL, 
            0x071BE127B5ABDFB2ULL, 0x9A79257625C76562ULL, 0x61CE240AEF2042F0ULL, 0xFFF876FF5A824866ULL
        },
        {
            0xA808D5126A81A14AULL, 0x912B5925884836E0ULL, 0x815F5F6E2D0B6EEBULL, 0x1DC380C542932F64ULL, 
            0x403DB9117120EE89ULL, 0x8D330D70AF97835EULL, 0xDED152EC681D9356ULL, 0x47C0C6540E7EAC2CULL, 
            0x717763A474D5F474ULL, 0xF45C11B5E0C42C6CULL, 0x895276DE652ABCE4ULL, 0xF912A6E238401584ULL, 
            0x5FCDC081A57DDA03ULL, 0x1D96D48995582003ULL, 0xC46192323B37920FULL, 0x3DA0A6B83A174A64ULL, 
            0xCDCF9280C5594F51ULL, 0xFBED3AE1C8A46235ULL, 0x3C417F414EF2BFD1ULL, 0x0897D99BAE8105B6ULL, 
            0xF00596D1A6858722ULL, 0x38A595AD81A556C3ULL, 0xACBDB892BB725278ULL, 0x68DDC41F1C79DB77ULL, 
            0xBD977C987ABD5EA2ULL, 0xC4EAA0285E02FDD4ULL, 0xAFC37D52137E0252ULL, 0x6C01114B62D91219ULL, 
            0x47832C274EBEA673ULL, 0x5B17A2771072CCAEULL, 0xCEF57944CBA3C3D1ULL, 0xC2617158B76105B9ULL
        },
        {
            0xB93F09F2BE6D9129ULL, 0x7527C1E6EEF6F252ULL, 0xD7630AB03048E53AULL, 0xEDC442D3D36C7F53ULL, 
            0x940EECA600B5D495ULL, 0x9D8BEABE39DAAD3AULL, 0xB6BE321B35EF2D34ULL, 0xE4B5CC1C44389211ULL, 
            0x3FEC8A2147EA3CACULL, 0xCCA540064DA6106BULL, 0x703307DAD2A8E485ULL, 0x2BE85ABCEC289BCBULL, 
            0xD072E3505ADB8B6CULL, 0x208D8EC9BC63F148ULL, 0x3427FD8510BA79B2ULL, 0x0A71D350FFCFBFF9ULL, 
            0x3A2259D454FB68B5ULL, 0xA9FA8E008F617927ULL, 0xD78D442CA5A3CEEDULL, 0x4FADDCF55B996642ULL, 
            0x9377F153FB3E5712ULL, 0x2015909696E9B27CULL, 0x188F821F571970B2ULL, 0x296C31188718B190ULL, 
            0xFB9360F741191DEFULL, 0x929D4C1D35663678ULL, 0xB01858C181B5D854ULL, 0x3ECBA0053F3930DDULL, 
            0xBAD6D8B580AEFCC3ULL, 0xAB8AE396C822C62AULL, 0x6822A77292D35CA9ULL, 0x9C4361809397BC09ULL
        },
        {
            0x99E50235B2EE3D23ULL, 0xE2B3BEF597C73706ULL, 0x0451728659BFAA44ULL, 0x65F5F7FF8B34449BULL, 
            0x25D1ADE11B0DD333ULL, 0x921A7A2F80FD9AF5ULL, 0xF497CC16B1699C47ULL, 0x62E454A69F9F0A5EULL, 
            0x447F9972F14A70FAULL, 0x6A09F1F936F28318ULL, 0xE8967A6644359B8DULL, 0xF666485502522C46ULL, 
            0xD287FC0CDB288E54ULL, 0x163F9857D991359DULL, 0xCA589C20B583CFF2ULL, 0x41C2A8584CF6FDFEULL, 
            0xD04E7680192B3642ULL, 0x517C79799162C8AAULL, 0xA8D7D7123BE10153ULL, 0x7A3BF96E27AA4179ULL, 
            0x78407DD1E061CAA6ULL, 0x90431F2C572691F5ULL, 0x5AA614670C25E1F5ULL, 0x1E9EB92382DC58BDULL, 
            0x2F974D27FAA028C5ULL, 0xB6F23D911DF3A238ULL, 0xA051C50196CBE6BDULL, 0x8159E3119E095C3CULL, 
            0x1F733DDD59193CEFULL, 0x973212493A3FC589ULL, 0xD32DB72ABB8EEC87ULL, 0x8157BDBBAD737925ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Pollux::kPhaseCConstants = {
    0x7B6EC2C00EB6CE56ULL,
    0xEE85D14E9C236BB8ULL,
    0xA0A6901B5C5A8505ULL,
    0x7B6EC2C00EB6CE56ULL,
    0xEE85D14E9C236BB8ULL,
    0xA0A6901B5C5A8505ULL,
    0xDCF3846133618CE9ULL,
    0x3308A3C684016F7AULL,
    0xE2,
    0x7E,
    0xCF,
    0x75,
    0x20,
    0xC7,
    0xF7,
    0x37
};

const TwistDomainSaltSet TwistExpander_Pollux::kPhaseDSalts = {
    {
        {
            0xD57941D1EEE371F4ULL, 0xAF052355D4E176CBULL, 0x38769B28364D862FULL, 0xCF11886BFEAAD351ULL, 
            0xA84E547C828D4B1AULL, 0xCA7B2A2C6186B767ULL, 0x09779C6E05E7C81FULL, 0x39AC11A43A59DB76ULL, 
            0x3F99AA11295EE544ULL, 0x45A94690341E5FDFULL, 0xA4AF77C52B641C02ULL, 0xE2B1EC3E32C4A374ULL, 
            0xA99FEF656318C22FULL, 0xF6875A47D8ADD039ULL, 0x5BA7302361AA18A0ULL, 0x5A9742563D4187FFULL, 
            0xA308B0E7343935C2ULL, 0x759DC52628F59308ULL, 0x8B24B61209C4F55CULL, 0xA595B9EB979551AEULL, 
            0xE23D32995AE5978EULL, 0x952ED172DC833711ULL, 0x26D01076AB335C32ULL, 0xCE2F1B3F42004C53ULL, 
            0x8D0C71ACD6DA487EULL, 0x29C27DCDA894C059ULL, 0x666EEFC6942534BBULL, 0x6AA76B36305ACA1DULL, 
            0x25512965116FDF43ULL, 0x4F98F31FDB5BD728ULL, 0x6C4CD01CB7CCEA5EULL, 0xB9C5077F0CE4B855ULL
        },
        {
            0x2D7C8258C2BA783DULL, 0x041FD687A5BA20DEULL, 0x38158C833CF0BAB4ULL, 0xAB766DC96C6FFD67ULL, 
            0x532C6731B68CC5DEULL, 0x733FCCC21FFA26ABULL, 0x65BDE7186B837C55ULL, 0x5CD5DB69CF04BE2FULL, 
            0x11035CBE723F9EACULL, 0x9FF1305087F0888CULL, 0x2F8803FFC1D18F71ULL, 0x71B50CCA3D5A13FCULL, 
            0x6B24132FA72E4AD3ULL, 0xF0A06E06BE61EF40ULL, 0x18E444031A3237BDULL, 0x36936BA3DE160789ULL, 
            0xE5DCA9B72D157E5CULL, 0x8E4DBE23EEF73CAAULL, 0x4137708B0C946481ULL, 0xD8A2CFF7EEACE63CULL, 
            0x628937007982D5FBULL, 0xDFBF8D459578C110ULL, 0x3130949BF2CC563AULL, 0xF949362B21EC19A3ULL, 
            0xA8460BB6ABEC7FBBULL, 0x7A68AC3EC2F02A06ULL, 0x891E71D262DFA7A2ULL, 0xEFF6ADC8E38E644AULL, 
            0xC2BA361E5928945BULL, 0xCAB0B66FD0855F00ULL, 0x6B52ADE84F504D44ULL, 0xD0974D4194ED4F33ULL
        },
        {
            0x0C302C4BD63B31FFULL, 0x458C911769427136ULL, 0xF4AF56853B3CC203ULL, 0x20C7882AF01A891EULL, 
            0xF324EBF5F6D50D64ULL, 0x5D6583A5FC322912ULL, 0xB1D33E1B02244017ULL, 0x21066CE8C8B0A793ULL, 
            0x62646821D34EC341ULL, 0xA2F0B2B3864539B1ULL, 0x746D7B7C7F0888FEULL, 0xB563EB30CFE014EAULL, 
            0xBAD9EB12E6D578ACULL, 0xE3974A0D69D0FE11ULL, 0xA77A2E40C68E87EBULL, 0xE82757C434AB0519ULL, 
            0x53851F7B40665A13ULL, 0xFD0A94A047B03F12ULL, 0xA5CF55BF23C9B2F9ULL, 0x279B01ECFAFAF4CAULL, 
            0xD7455B174E3FA9DEULL, 0xD752A5257017E6A9ULL, 0xC90B888430FAE300ULL, 0x879E7A18C08875D7ULL, 
            0xA043E7C0FFBC71F0ULL, 0xF4A0E6C1F77394B0ULL, 0x107E28F9493CA852ULL, 0x274C866860048698ULL, 
            0x87877D12758207B2ULL, 0x65B41CAF2148573BULL, 0xF90BBF1B93F8B6B6ULL, 0xC486A5760161D755ULL
        },
        {
            0x8EF2B87F1FECF459ULL, 0xAC7FB802DBB5BEB8ULL, 0xC524211FEA38D103ULL, 0x429363BC2CA1442EULL, 
            0x9789D88E899A95D3ULL, 0xB7D247A2E633C330ULL, 0xE393CB054B6211B0ULL, 0xFDB7EC7F177695EAULL, 
            0xE6EF9AC45C31C96CULL, 0xC8EDBAA464867549ULL, 0xB877F1B5BC2A5FF8ULL, 0x558614AFC692C99AULL, 
            0x3C831CE675460231ULL, 0x6BCE9D4B5A186F37ULL, 0x8F92D6D98A2A2D1CULL, 0x674E83F07F8F4244ULL, 
            0xA015C828707424F3ULL, 0x366931BFC81C8A82ULL, 0x8DB1B057FDB593F6ULL, 0xB2179C314BA60AEAULL, 
            0x6EF1A73CECA43C90ULL, 0xD92AC85AB321A794ULL, 0x5707D36963915013ULL, 0xB5F7B4F944769291ULL, 
            0x94D0CDC4A932AD0CULL, 0xA4E535F08A2131C4ULL, 0xFB4539AF1516EA36ULL, 0xF8E6AA818427BF1FULL, 
            0x09D02AE54E814128ULL, 0x63DFD5934EE6313EULL, 0xF0BDE875DF0F5616ULL, 0x673051AAAAD375D4ULL
        },
        {
            0x2EC13B53EF533B3BULL, 0x380C559A66FCA9DDULL, 0xDC4D4220459A2C7CULL, 0xA9A822250F8CB4E2ULL, 
            0xE7462DE26FC4FF86ULL, 0x81B168AA0F76C24EULL, 0x88F7DB36A06C7D2AULL, 0x614B92DDA7D846C3ULL, 
            0x7A361CE28B0F4332ULL, 0x61384207521BA0D3ULL, 0xA5FD70FBC013D33EULL, 0x137425152E47CC30ULL, 
            0x2E3D238995FD7AEDULL, 0x62257390A5D4C8CBULL, 0x4450FDD50D6789EFULL, 0x510002573DE3DD5AULL, 
            0x914A629F9DDD0664ULL, 0xCA8E384DED29538CULL, 0xEBB50555043B3CCCULL, 0x4B97AD91C531BA72ULL, 
            0x13AE59AD561B9A47ULL, 0x2D201009F53080B5ULL, 0xD2617124A14CE98BULL, 0x6775F524967181E7ULL, 
            0x7CE8CB516437037DULL, 0xC5E67C6AC9ECFCFFULL, 0xDEE403613882FC0BULL, 0x4F5C78D35929F3F3ULL, 
            0x35B2F58F85641297ULL, 0x086FDB96F9E7F4EAULL, 0x1C872F64E18FE541ULL, 0x48D5918A072EF1B9ULL
        },
        {
            0x3DFAF0AF8F031EDBULL, 0x6F434FDFE2BB93F5ULL, 0xECE0DF18F4BDC663ULL, 0x46C6218CC65101FEULL, 
            0x9775046CBDBE2524ULL, 0x716AC3E98FB262ECULL, 0x44CD69547E3C1D2AULL, 0x883790DF5507F934ULL, 
            0x04787B493986394CULL, 0xD106EFE5F2BA4CA9ULL, 0x9A5549712F558666ULL, 0x8F6E89008581794AULL, 
            0xFDE2F442D89961C0ULL, 0x2B7E1F8F4715D3F6ULL, 0x136B07A586BB4DB6ULL, 0xE3465B83E983CE02ULL, 
            0xE5726CA481C32155ULL, 0x660B07594991E0A1ULL, 0xCBC485A3C54BAEDBULL, 0x48CA58574AE07784ULL, 
            0x16011C0A649B6FFFULL, 0x58DC8BCCEDC0699FULL, 0x536AF78AA2499B19ULL, 0xA53B473123782C58ULL, 
            0x1B3DC8FCFD5E00CAULL, 0x79E4C762FDFDA606ULL, 0xEF8E25600EB7F8B9ULL, 0xE7AB34E06E5CCD61ULL, 
            0x46E825B5844DAADAULL, 0xE4C5570AD2DD6547ULL, 0xE0CEFC3D0C699A6EULL, 0x9C76095562204F14ULL
        }
    },
    {
        {
            0x42EB2CD2C1B51B9DULL, 0x23D263588E95A4D7ULL, 0x6A16D89FDD9CC153ULL, 0x4C56D916C79A5112ULL, 
            0x1E4F570A027FA62BULL, 0x0B2304F36E11FB06ULL, 0x2C8C76E3712E3421ULL, 0xD46121702CFCD919ULL, 
            0x053056FD467428E4ULL, 0x31645FEE8E5BEC22ULL, 0x90AE5AB11523CC96ULL, 0x3A78C81D91DDBD07ULL, 
            0x989BC702F6A71EE3ULL, 0xB80904FA00DE1077ULL, 0xC338843682AA7FE8ULL, 0x974E6D8902234C42ULL, 
            0x560BE9DE7EE02136ULL, 0x93B0F3C42A00FB0CULL, 0x89552074FAEE750CULL, 0xF2803598BF780A01ULL, 
            0x99107030B6085115ULL, 0x85813EF43CBB2125ULL, 0xB0BCDAD1B67BFBEDULL, 0x7A4069BB9E3364B2ULL, 
            0xCABE4E3EE5A79CEAULL, 0xCDC185DCD4D8A850ULL, 0x2A049D054EB4BD51ULL, 0x64810E68524E708DULL, 
            0x274BC985CE829664ULL, 0x6DB523A0E553BD65ULL, 0x7AA001CA56325587ULL, 0x988F99632A8409C6ULL
        },
        {
            0x0ED8EC6AA0314C92ULL, 0x810C3FFABC2EAED9ULL, 0x73240E986FEE9446ULL, 0x98803D9311DA70E0ULL, 
            0xB5151CE28E639BAFULL, 0xF3984D318B723044ULL, 0x26EBC621AEC9B551ULL, 0xBF0F487DC5C30F2BULL, 
            0x73F7B82236A2E9B9ULL, 0xEBA680CAD89709DAULL, 0x286B0A5A5FB7E503ULL, 0xA095FA94794B28C3ULL, 
            0x4167D4D3DC68DC38ULL, 0x2F1324EFF5942E89ULL, 0x552D4EE267DEEF09ULL, 0x01EC8A5D0EDE1688ULL, 
            0x8C3509A3561E842BULL, 0x26E1B376F74C11B1ULL, 0x7389F6E6F603DE21ULL, 0x84181D4798EB2DF8ULL, 
            0x6594649341480BEFULL, 0xA4D5CF50B2A7DC55ULL, 0xF7CA00FBC71EED7EULL, 0x281B6CAB1FC8CEC4ULL, 
            0xC0D73C18DFF15F01ULL, 0x77E423D43ED0A6F6ULL, 0x801E7595CF8E2C35ULL, 0x7BA20D902997701AULL, 
            0xC732209419DB2CE2ULL, 0x9998B60329AEB83BULL, 0x5C0D19E4C3FF6973ULL, 0x426144CE45017417ULL
        },
        {
            0x7010130267DF6123ULL, 0x2D0CDE02A3F8C9BDULL, 0x43D24A0B12C3D948ULL, 0x8914052D3A50CC81ULL, 
            0x3F0E4323823B79C4ULL, 0x5C683C3A4139505CULL, 0x587E0741E43A7FC6ULL, 0xDA09BB58709D6048ULL, 
            0xA20267E595F870D6ULL, 0x625654C600D66958ULL, 0xFB68A1DFDCE0A9A9ULL, 0x4F3B9DF7F639B78DULL, 
            0x3571F003A240E1BDULL, 0x29427E7A0706280DULL, 0x422D4E03D46012FDULL, 0x70524C334A75F1DBULL, 
            0xC958EBD05C687185ULL, 0xEEE903BB1C920465ULL, 0x109DBAD808D3A9F0ULL, 0x7F312DBD5A69696BULL, 
            0xEE1F440A64D21DB6ULL, 0x107D478877FA183EULL, 0x0CA8DCD0F26BF397ULL, 0xC652342F1CF7891EULL, 
            0xF030BB3069A1EC84ULL, 0x5CF150823FEAE8EBULL, 0xBF30D8F5E96F58B1ULL, 0x833D5BC3744F1BDAULL, 
            0xE5B43F011B6A8946ULL, 0xE6571A1F9BC901E7ULL, 0xF90606770E14812EULL, 0xE494EAB11269D559ULL
        },
        {
            0x90525BEDC8D30FF2ULL, 0x0C21BEAEA7215745ULL, 0xDAFDA47C7DBFEFBAULL, 0x447E73452295E74DULL, 
            0x6082D6BE19ED9864ULL, 0x0AABC9F89EF3474CULL, 0x7EBEE1CA53263629ULL, 0x7AD0C0C8FB5CA3DEULL, 
            0x00E83CBC6DCB95EBULL, 0xBC5238D60409549DULL, 0x5A0ADF9325453DA0ULL, 0xA584A729047C8621ULL, 
            0xA0F0D4756928BC8AULL, 0xCACC1EB27B02B3C7ULL, 0x452CEFD9DBF068D3ULL, 0x18EC51206162E811ULL, 
            0xD852FFEDF804FA99ULL, 0x17E607E3BD49AB36ULL, 0xFD8BE599C5E2AC54ULL, 0x42257EE74DEF8CF4ULL, 
            0xA4B7DB975A5C3AEFULL, 0xA6F985D88BF74479ULL, 0xFF091D9D2158CA71ULL, 0x69294CB708A6AF55ULL, 
            0xB38556474D3380A3ULL, 0x0717E818114A5D17ULL, 0xC137DE4E6B384F9CULL, 0xF7C28FF22A78A43FULL, 
            0x3B7BA7BD29259630ULL, 0xB2B44CF2C3163DA0ULL, 0xABBBBFF8B6195820ULL, 0x70262FC7E6D918DCULL
        },
        {
            0x2419C120EB4EFA18ULL, 0x1D4E6877F10FC4A9ULL, 0x00DBC35ECF164A56ULL, 0x75283E4B21C4A397ULL, 
            0xB290E01B110F1438ULL, 0xF574BCD56E55D3BEULL, 0x2CB2A5B43F9A0B09ULL, 0x0369021E76224C00ULL, 
            0x58E84003930BC82BULL, 0x05094C0A0E4BE6A2ULL, 0xA0A3B0F6E3471B2EULL, 0x5ADCC79BE12CA482ULL, 
            0xCB25DE5F95A83106ULL, 0xFF76E40A96912BEDULL, 0x2CF1FA6222CC5D26ULL, 0x16EA2C918326E323ULL, 
            0xD5DC47F114F63763ULL, 0xC362D482CD3AB914ULL, 0x2FFBD84C907018DAULL, 0x504FF33F2E1EA377ULL, 
            0x86B7A636DBBDA3DDULL, 0xC8FF01C9C36E3AB1ULL, 0x44CAC00305B2A56AULL, 0x6986A4B0193BB752ULL, 
            0x06F6ED27C3A55924ULL, 0x075A2BE3CC0FD400ULL, 0x02C5E320F55E5CECULL, 0xB853DDE10C53B2C5ULL, 
            0x9E9E74D372875D7CULL, 0xB596313E389C92CFULL, 0x13A32EE3A3D4B508ULL, 0x096394F5897D9498ULL
        },
        {
            0xC272397080C3C80DULL, 0xBE98B55771EBB6C0ULL, 0x8C1824693DC88A95ULL, 0x816C487FAFD6FC88ULL, 
            0xCA07E654260C6DA8ULL, 0xD5132A8AB50DD28DULL, 0xB7DC3EB7919F37BAULL, 0xF3EA34271EF9060EULL, 
            0x80DFC3150E28F0CDULL, 0xEE024526D999B7DCULL, 0x72311599E6DD1B7CULL, 0xAF149ADC63CDFCB7ULL, 
            0x44D0220F6989F143ULL, 0x3B4484B8BADB087BULL, 0xC30B0B37D43C2540ULL, 0x09AA5E37BF9C882CULL, 
            0x6455F58567F042ECULL, 0x42833C048B5C5E52ULL, 0x775308F965E89E1BULL, 0xB8947A8F7CFB2CF5ULL, 
            0x0BD721ED922D9349ULL, 0x3B5FC71DA0E2A783ULL, 0x32CD186DCCA7A8BCULL, 0xA896DEC6398D6617ULL, 
            0x4ABAB86FCA18BBE5ULL, 0x9CCB3961722A6DDAULL, 0x60B3F538BA2B4812ULL, 0x3DFC5666110FE085ULL, 
            0x76ECFA68D25A0B94ULL, 0xA1706A43E3C269FFULL, 0x1DAC3F8F77323066ULL, 0x3EBDDA95BA082BA9ULL
        }
    },
    {
        {
            0x2BBE7B8F0D1BEA18ULL, 0x495537D586CEC92DULL, 0xF5FEF4FD04E53B5AULL, 0xEEFD315FF28117DDULL, 
            0x7BA31D4849DF9084ULL, 0xB4E274EFA07F6E6AULL, 0x70C641576881553BULL, 0x9F5FB8CAD01CFBF8ULL, 
            0x66DF760B45B762ECULL, 0x1A2F56AF2C0FE609ULL, 0x8CA37D23D01A3B6EULL, 0x869E3D66907CD506ULL, 
            0x7C0A2E39606C8C32ULL, 0xFE76FF1100746751ULL, 0x2DEA1AD13F3DF349ULL, 0xB48889F0CB069EB3ULL, 
            0x36F2EFB932D01091ULL, 0x76BC8CC845CD7423ULL, 0xE3891F3F0B89495EULL, 0x8A9EB9E28AA5E857ULL, 
            0x0C2CED9D4F1DE3CEULL, 0xABE0C85E4EE38A44ULL, 0x3952C68091F914ACULL, 0xC8D2B84D49641509ULL, 
            0x53FC9AE28DE4FE8CULL, 0x22969DB40DEFD030ULL, 0xB6F2A78A163EA18CULL, 0xC3BDD12C0D43D88AULL, 
            0x0DD6EB8300665712ULL, 0xFBECF6D14579AFE4ULL, 0x4A79080D42284CCDULL, 0xB6B75DEFA77D5116ULL
        },
        {
            0x24BB0CFE0CB31F9AULL, 0xE98D2DB6DF9A67FEULL, 0x337D0BEA5439BC85ULL, 0x22124DA9182008C3ULL, 
            0x2F56A9300FF4C887ULL, 0x82CF0751D02617B8ULL, 0x99DA8C817B227CABULL, 0x54A4C9BE21F0607AULL, 
            0xA6B6E00B5217C930ULL, 0x5DEAFBF2FF686265ULL, 0x7A19629E8774D2B6ULL, 0xF82C42AC5CAE9CF9ULL, 
            0xC491DD481590F81DULL, 0x8CC85F2CF64156E8ULL, 0x423DA33E93579A4DULL, 0xB64E8181F5866C64ULL, 
            0x63189A0853234B7CULL, 0x028EA4C62C7AC567ULL, 0xB06E986974A4A6ECULL, 0x32D29441A5C71294ULL, 
            0xF3401F7E2C8DCA1CULL, 0xA70384DC2BA4DAE3ULL, 0x910C7651E955CB5EULL, 0x9A0C9CE78000711EULL, 
            0x9C20599F354FB389ULL, 0x5403402EB364AFE5ULL, 0x4942C4549B8EC1F2ULL, 0x73E9733A77084E8BULL, 
            0x55F634D0CE5AF626ULL, 0xBCEC280BDF74F617ULL, 0x8D9B25A1645981D7ULL, 0x6A3285A14A39CF2BULL
        },
        {
            0x52D022C86F4E6863ULL, 0xC766143F82336F17ULL, 0xB678A8EBC187F7DCULL, 0xE9961B1A7928249EULL, 
            0xBC12822F03CB87D4ULL, 0xC86CF1C10921A934ULL, 0xCE45D5F3C771E7E3ULL, 0x5801E94108BC7EF8ULL, 
            0x30683830F5C51934ULL, 0xC6E8BFEDA0A967A2ULL, 0x7F409E98C05332D9ULL, 0xC49793A51F3C9479ULL, 
            0x44C66062E8571D1DULL, 0xC9FE7EDE8DD60B8EULL, 0x8243C00E266642FFULL, 0xBB8447EB82F17C62ULL, 
            0xDBBEB4506043E4D3ULL, 0x15A3623A7E2DD6BCULL, 0x1DB6921DC08EB788ULL, 0xB9B5A73D2D182388ULL, 
            0xC69374EE9FB88FB8ULL, 0x87853C38E82B407BULL, 0xE8DC2577D4293B76ULL, 0xC46C6DB13E02374BULL, 
            0xFE3E44C92848D563ULL, 0x1BFBD457085B650DULL, 0x2DD217759CDF41C5ULL, 0x985C95A26C8416C7ULL, 
            0x5E25B34BB1387F4EULL, 0xD7F5A48544A99049ULL, 0x39F81917DBAB9173ULL, 0x5C03B221C70602E0ULL
        },
        {
            0x6D9EE674F7412EBDULL, 0xDB7B72B30993B6F6ULL, 0xC4CDCE2D8C8B3ECAULL, 0xB3EF430AA31724ADULL, 
            0x99B9C992FCEB9A6BULL, 0xBA37367EF44F1FEBULL, 0xC191EBE664DCADB1ULL, 0x7FBB654C6C20B04BULL, 
            0xC9BA739013D24D70ULL, 0x4A3C6DE5EB7EB192ULL, 0xE7537ACA0E9A8272ULL, 0x672FBC26E9C81457ULL, 
            0x1B898E8DC0E50992ULL, 0x34976DC7F59FC02AULL, 0xFEA0F08C9D6D2ACAULL, 0x5135C0DB22AC3E3DULL, 
            0x0E5F8921897D5BCEULL, 0x4B8D6F412D6EF3E9ULL, 0x0EE39D82D6B9B9DCULL, 0xB674D396524E64C4ULL, 
            0x1F0C40EBAE18F539ULL, 0xEDF8B7B19A9892B9ULL, 0xA766110FFD4C69A7ULL, 0xAC6E30C8AE53BCBFULL, 
            0xCC3CE501B3FAB8B7ULL, 0x31A17D231A853596ULL, 0xDA1D22B43F9A0BCAULL, 0xA097E4033CB80EA7ULL, 
            0x206E4AB630F47CFCULL, 0x1227F8B25D7FE353ULL, 0x6EBC45B8B19EC30CULL, 0xB4B834C5CC0C03B8ULL
        },
        {
            0xD3A27AADEE675E31ULL, 0x7399865ACE462CF1ULL, 0x66AFB0811E4EB2A7ULL, 0xC5DB9CD822EC17B2ULL, 
            0x69DAAFF781947767ULL, 0xB7786B3DA05A54DFULL, 0x75D1214D54652EB3ULL, 0x3E99EEC5F3DD7E66ULL, 
            0xAC81AD7DEC4D9FF5ULL, 0xE73BCEF475893A40ULL, 0x4995EC788BAC6FCFULL, 0x1E33F5E61C69B766ULL, 
            0x368A069DBED347F6ULL, 0xB241FB7FEB1FB322ULL, 0xC794CCAE2FC70C0FULL, 0x4E056A750E650DA7ULL, 
            0xF8CAFC9260B870C2ULL, 0xEC5B5CFB2FE80D07ULL, 0xA3B400BDB54087AEULL, 0x3DC68063444E34C9ULL, 
            0xACEF6DF53E0D7CC1ULL, 0x15078ABD57014508ULL, 0x66AC977E507C6D32ULL, 0x9AB1D79A3968E69CULL, 
            0xAD1AADC51E65A330ULL, 0xCD69FFBF0ED12BC1ULL, 0x6176C9FFAB968A77ULL, 0xAAA6663D48E124EBULL, 
            0xBBF8589FAB8DC615ULL, 0xDF46F2554ECE53B1ULL, 0xDAF52DC76ED9C3C3ULL, 0x45C7B77CDC440B1BULL
        },
        {
            0x6F13AAB9980E2DFBULL, 0x6A34899558A543DDULL, 0x5B4F151FA427BA12ULL, 0x4E522FEF2FACDAC9ULL, 
            0x28BA96276E6C5F7DULL, 0xC056B57D99EA0113ULL, 0xC3900728196C9011ULL, 0xAA56D8045D528C00ULL, 
            0x1F8A73E0DB12C9B8ULL, 0x64B3B746D1A986E9ULL, 0x967F5B095B673123ULL, 0xCAF54AD4EEE3398DULL, 
            0xD48961542A9761B6ULL, 0x25F51177235805D8ULL, 0x091D7D678EE77D5CULL, 0xCAC8328AF5FB2DF1ULL, 
            0x77AEEF74AA532E48ULL, 0xBB7ABC99A76D17EBULL, 0x875A0242792E70DEULL, 0xE778873532A0DC12ULL, 
            0x5A10953412C15517ULL, 0x330DB46FD0EFC277ULL, 0x29AEB74BAEEEBCDEULL, 0xBB5F8DA76BBCF650ULL, 
            0x39FECE5FF6BBF4B9ULL, 0xD73E2F28E5C883E2ULL, 0x88D2CF501274A1A9ULL, 0xA5DF65C0C2BB7B39ULL, 
            0xD3DAE89C03B93F99ULL, 0x79C21867B6128277ULL, 0x82014D698B687071ULL, 0x63A244B42AE11E30ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Pollux::kPhaseDConstants = {
    0xE491D0DB80F24CA6ULL,
    0xFC13E5F481729DA8ULL,
    0xC8603F550D054D7FULL,
    0xE491D0DB80F24CA6ULL,
    0xFC13E5F481729DA8ULL,
    0xC8603F550D054D7FULL,
    0x52A6DBEE89B839B4ULL,
    0x9B53BD934031F914ULL,
    0x77,
    0xD8,
    0x65,
    0xD5,
    0x7E,
    0x74,
    0x58,
    0xC2
};

const TwistDomainSaltSet TwistExpander_Pollux::kPhaseESalts = {
    {
        {
            0x25782C379A63096BULL, 0x8C0E35F0000207B9ULL, 0x0E025850CCF9FC4EULL, 0x3EE82CC68C99F5CCULL, 
            0x9F8D5E56AC013D3BULL, 0x5AE37530949E2C03ULL, 0x94CE924D86D3CFC2ULL, 0xE256E33EFB997083ULL, 
            0xE1227C786A9B86FDULL, 0x787756835B9788F9ULL, 0x4CE12D6F73F319B2ULL, 0xDC0FA9B8867C5658ULL, 
            0x3AB41F3685191F05ULL, 0xA6983505486FF6F9ULL, 0x8A3C192F0434B858ULL, 0x1FFA0CAA4CA47B05ULL, 
            0x9FB83074C0EC92D4ULL, 0xE90CD09E6536EB7DULL, 0x71A6AAC90187D00EULL, 0x66DD9914FBA9AF04ULL, 
            0x134045CA2E12A0F9ULL, 0xE19F54C69319EE31ULL, 0x1B1E6001131D37EBULL, 0xDD2D73F265063B04ULL, 
            0xBC81D251A68EF199ULL, 0x294AF84979C698E0ULL, 0x6D851501D57BA434ULL, 0x2FE4054F943F5E9DULL, 
            0x0B314D17B40C2113ULL, 0x498A41676E6927FDULL, 0xB460158969C8891BULL, 0x217950A8DA9A2E1CULL
        },
        {
            0x6B697CF6B0C1E9C2ULL, 0xFDA69BA465BBD301ULL, 0x73B38DEC8A8FC042ULL, 0x6E0194B4C54F6805ULL, 
            0x338686B94E1C5C3AULL, 0x6A2C6077DBC394F6ULL, 0x825AA57EB486A48FULL, 0x35BB59D6AE8D88F4ULL, 
            0xB7FC6DE3425C7542ULL, 0xA6E29029E6ABEB30ULL, 0x050D2AF7E99411D4ULL, 0x973943ECF7F78705ULL, 
            0x53BAE20E7C4C3F71ULL, 0x5EAC8F24E764B029ULL, 0x1DE25CA37BEB83D8ULL, 0xB82361B63AAED934ULL, 
            0x194CB0311A9018E8ULL, 0x6792A41EE85D4C9FULL, 0x67285913EE774483ULL, 0x0785CF26B789FDC2ULL, 
            0x5A6BD8E4393484EBULL, 0xBB90A8546B1CD98EULL, 0x22E52AE51E7FD265ULL, 0x5665ED0E41207D26ULL, 
            0xE1534ECC6A127585ULL, 0xCE4704F397882602ULL, 0xF22261A5903E66F3ULL, 0x0A4E4718C569F05DULL, 
            0x333A27A6C10BBAE5ULL, 0x0184405558B5E3C2ULL, 0x8BCB29908F51ECE8ULL, 0x09C7BE8AF8BF31FBULL
        },
        {
            0x3ED4861AA75F0F6FULL, 0x9D8918B2DE974376ULL, 0xCBA1F15BAB5AB465ULL, 0x42CCD3155E44DE24ULL, 
            0xA89273B97EC7EB45ULL, 0x2BE6F8CFF83C9BAEULL, 0x6CA9303A522FE885ULL, 0xCB9638D885F4F21DULL, 
            0xEEB2FA19B02A0E1EULL, 0x23BE8AAED3983640ULL, 0xFE87794E1242C597ULL, 0x13209369826CFAD9ULL, 
            0x70BBB7BAC7033246ULL, 0x41781AD0824361E7ULL, 0xC4388C7F63938E9EULL, 0x2A81FB08699C83A5ULL, 
            0x8DA4F90D1AA3EB79ULL, 0xEB3723875B0439CDULL, 0x66DD9F69964ADE98ULL, 0x8C526F54D7376B2CULL, 
            0x491494F20F5E74F7ULL, 0xD79F5EB23F8BEA2DULL, 0x01BF7E6BAFDC1D19ULL, 0xA5D01BFC557BE792ULL, 
            0x1B1F97A753841E16ULL, 0x3D5048DAB336CDC3ULL, 0x6556EFE36326D953ULL, 0x5CA6F6603041083FULL, 
            0x2DC5D5BC92371269ULL, 0xF56F980D8C6BBD92ULL, 0x956939A1EFE7F539ULL, 0x026B42A396A7DCE7ULL
        },
        {
            0x062C8668BB85F917ULL, 0x6C7A67D18165CC5AULL, 0xC938D6E569E054B7ULL, 0xB36A92B7BDFA8775ULL, 
            0x08C08701E687D829ULL, 0x78784B2A6DE92522ULL, 0x006CECE2573113D3ULL, 0xAA88A7D98DFA30E6ULL, 
            0xA40CAE65171893C2ULL, 0xD3F40A2D2C285437ULL, 0x98C09EE8E72305C5ULL, 0xB7A6AEEEFD1B5AF2ULL, 
            0xBB31982D072ABA14ULL, 0xAD5EBCEA797A9448ULL, 0x9EB2033B71BB3EC1ULL, 0x6C4BE191E6B183EBULL, 
            0x27A4ECA9FCF58DABULL, 0x899ECC793E0BD5BEULL, 0x09F64F3B29E66F16ULL, 0xFF8BD00C17BF62B4ULL, 
            0xA1526FA1D39EADA5ULL, 0x490F8F1553F9C5F2ULL, 0xE4A0B8142AFB97CCULL, 0x0C49F3F0659BC8C7ULL, 
            0x476C3D82B6F8BBCCULL, 0xA80571C26C01A32CULL, 0x136DBBE7BFAB2A53ULL, 0x396FDE3F0EA336C4ULL, 
            0x8BBB12BF02D48FECULL, 0x8460FAB6851911D0ULL, 0x9C9ECB6BCC56D197ULL, 0xEC56A21C28131DD7ULL
        },
        {
            0xC458C7464CBC7F13ULL, 0xD5E6E818011DE568ULL, 0x7AA7B2286747E074ULL, 0x49088E7AC9A18E80ULL, 
            0x01987CEA280E20B2ULL, 0x7C2187E4F920392EULL, 0xD4C85F375F9F7BA9ULL, 0x3210595A39591A8EULL, 
            0x815FB702A3921E39ULL, 0x827DCBBE0AB6E56DULL, 0xD7204BF6C891ECDEULL, 0x22FD627D2FDB5171ULL, 
            0xBA63B50056DB2D30ULL, 0x5AA73C51FF936750ULL, 0x01708579722B8CBEULL, 0xF6684C92DDA80950ULL, 
            0x570DC8B08200AD17ULL, 0xB36F24B8B0CE2FC2ULL, 0xEACEF903A383DB94ULL, 0x0B3BCF2DE1B30486ULL, 
            0x1DFD48D9CCE0A1D1ULL, 0x295C7A15415E33E6ULL, 0xCECE7FBA288BCF94ULL, 0x280E7CABA3A931E1ULL, 
            0xE2E4C6371C3B34B3ULL, 0x4336E71C6A9CF9B4ULL, 0x423A8AEE42E3E2D8ULL, 0x9144406E4F227C19ULL, 
            0xDBF622A9917ADDEEULL, 0x8589F533AD2169CBULL, 0xE72170C12DFC7838ULL, 0x35DA5066752AF9B6ULL
        },
        {
            0xFDC1AACDA2BA0B9DULL, 0x92A95EAD37B77BBEULL, 0x11A85CDDAB38E1C9ULL, 0x8033234843357FDCULL, 
            0x06FD5EB9188EBA14ULL, 0x0FEE60F5C4247FDCULL, 0x37986AD52EA50B57ULL, 0xB1A926CF047833E8ULL, 
            0x33CDA4C17F076523ULL, 0x4848950CE37E49A9ULL, 0x0CD29984E1AD5292ULL, 0xECB86B380D0064C0ULL, 
            0xB02911803BF5B671ULL, 0x48656FF5C55126A8ULL, 0xF6C061557B7A8DB2ULL, 0xD272D96D643A5173ULL, 
            0xBADB12001B60C55DULL, 0x19158B72C1A697DFULL, 0xA279B6FF7D223515ULL, 0x09D05627919C6AFFULL, 
            0x829D1AC8C02E6FFAULL, 0x7EB820EBF24855A1ULL, 0xD42F1AE8F5E45670ULL, 0x6AC09816EF791FA3ULL, 
            0x223EFED91A5D3867ULL, 0x7CC1F67ED3AD6777ULL, 0x20B59BD6E02FA1B6ULL, 0x7A2D9FE159411B0DULL, 
            0x75EE68AB027C5432ULL, 0x3F42CC2A69B68BB1ULL, 0x24AABB07D529AEB3ULL, 0x8F0FE28A48186211ULL
        }
    },
    {
        {
            0x6749951A450AA69BULL, 0x5F53F83EBC26BDFCULL, 0x491E6F8538EE0B1FULL, 0x4F2C672777079127ULL, 
            0x15FD9654382980DFULL, 0x050C9FB66A828A0FULL, 0xE25EBF15FB3718A7ULL, 0x5B78727ADDF7175BULL, 
            0xDC6B0DF010F9F0EEULL, 0x2AA98C41E8CDF59CULL, 0x61E252DE10CD4A4CULL, 0xCD1603129757BF0FULL, 
            0x6B14179DA79E1063ULL, 0xAF9C78B3ADFB7F58ULL, 0x26820AC8E5A81E0BULL, 0xC8F225DAF5F46F5CULL, 
            0x8BBA310C30A670BDULL, 0x859FB9DB96C93E3BULL, 0x8EA4F5CD19DCB81FULL, 0xBBB622B605234B00ULL, 
            0x23682B12564E9AF7ULL, 0x8B075677148361CDULL, 0x1A30CFA0AB112719ULL, 0xDFCF0CFFFF79E29CULL, 
            0xDA9C1ADA5E07E58DULL, 0x12B399C5968A12FDULL, 0xFD26D8036B3EC806ULL, 0x005CE302281B43FFULL, 
            0x6CB0969BA4525CB4ULL, 0x6B108264249C440EULL, 0x1219A482C9587E2CULL, 0x55B0141930906F53ULL
        },
        {
            0x23FF522AF8065917ULL, 0x980E62EC1AA9F4D9ULL, 0xE868ED2837459AD9ULL, 0x0BF1FAC3BE05EDC8ULL, 
            0xE0B8CAFABFDCBF3FULL, 0xFB40BC31BFCDB93BULL, 0xB3FD6EDF300F95A6ULL, 0x8314EF32C51CECE9ULL, 
            0xB9EA785EA7CD19AAULL, 0xAF37F4C1F89CF309ULL, 0xD75F10F4E8177DB0ULL, 0xB4111B6451B95C6FULL, 
            0x67B4255A86D1FB3FULL, 0xC87577D0FBFC69F4ULL, 0xA332B0DCD818F668ULL, 0x6A9CE6592D939D54ULL, 
            0xD8A733B1139CB395ULL, 0x68EC47662B91602FULL, 0x0BDEA60D23B141E6ULL, 0x302DB6CA3103C42FULL, 
            0xA87EEEE68DC81377ULL, 0x819B030F6A597EFFULL, 0x21A9222C77AD5B35ULL, 0xC2F2E83CAD2D0D20ULL, 
            0x4D3CEAAEBE71725BULL, 0xD97DD040A8764E78ULL, 0xFFD33E89151CB87AULL, 0xDD17932B5E3CBC04ULL, 
            0x9A02C6F64513B3F6ULL, 0x78092BBFE1175800ULL, 0x87B3ABB2D934ADFFULL, 0xB6B6CF60E9FD2EE3ULL
        },
        {
            0xF3E51BC6CA18C1C1ULL, 0x9EA719B091172781ULL, 0xF4C2C35FB887C349ULL, 0x87205C81602A25DCULL, 
            0x87A8D8239E9D7EBEULL, 0xDA3F808D0FCCC07BULL, 0x865F5EF675E1824DULL, 0xC4B65B260124FBB5ULL, 
            0xFA45DD16B1A8326EULL, 0x9BB0A935D2D1DC1FULL, 0x565EA7E4ADA4B209ULL, 0xB11AC8FF2F186CD3ULL, 
            0xB76BC19FE879E091ULL, 0x4EE3D5A8AF5C8863ULL, 0xB96FCED1FE387508ULL, 0x3C73888FE6882F0CULL, 
            0x93497E25A33F3C86ULL, 0x17DEA2C29775889FULL, 0x8D4E1AA20D186B5AULL, 0x4E780B7E9AE24A13ULL, 
            0xB030D01A6AE20FAAULL, 0xB48A79C6CA6D85AAULL, 0x3357A4A9079D9A9EULL, 0x219971511578B04CULL, 
            0x9972E76FB2C27BC5ULL, 0x09F125470D7D99A6ULL, 0x9320F7CB4799A859ULL, 0xE9E495C6D569E053ULL, 
            0x6B928826107C54BAULL, 0xB9C2777A93CF43C4ULL, 0xB0FA248FE3D3ADAFULL, 0xB8162A75008B9C6DULL
        },
        {
            0x20885EE73534174BULL, 0x46056866B9EDC60FULL, 0xF1F4BCF064E8B424ULL, 0x6230D79FE98AEA20ULL, 
            0xF9171FA35FBFA643ULL, 0x5DFE6F4DF614E161ULL, 0x0361D62C9385C011ULL, 0x6B3D225F61CFE859ULL, 
            0xE9A2BC1D72783A08ULL, 0x05CC23911F4E5E5AULL, 0x718A524AFD764F8AULL, 0xBFC3A1B2189BF9B9ULL, 
            0x0A16F80D3B782EC4ULL, 0xAA56A0846E0C680BULL, 0xCDE6D5D7DADD1AD4ULL, 0xE58062FBF45E6786ULL, 
            0x102629D77C19AC9DULL, 0x33CA862E1D91402AULL, 0x0E949E4CB0084CEEULL, 0xAEE84F0397E60483ULL, 
            0x66C9CBDE8EDDF777ULL, 0x0CB2193820C93163ULL, 0x59AD3DC6D7A79465ULL, 0xA14D641C1A119419ULL, 
            0x8B737A4F8B522C0DULL, 0xB701F1D14E21B012ULL, 0x3110CD86E7671E2AULL, 0xCC10C439B0EE6D6AULL, 
            0xD6B1C1E045916E39ULL, 0x98967835010C8D6CULL, 0x836FF95C29C5B0ECULL, 0x6C5C85C2B2CBE2CAULL
        },
        {
            0xA7560CEC17280E15ULL, 0x47ADBBD0D2F7290AULL, 0x1B437BD9E02AED5DULL, 0xF8C900A0D2693CF1ULL, 
            0x13D7B6521099E18FULL, 0xE9E23D6360290DEEULL, 0x819842A71096A9FFULL, 0x99CF4F1B4C7D77CFULL, 
            0xB4A39F4D3AFD3429ULL, 0x8C43BF483ED7C2F7ULL, 0x769DD8A1C9C45030ULL, 0x225EF7472125B558ULL, 
            0x2641DFC3EBC3666FULL, 0x87615F468939B5E5ULL, 0xBF9E348591283E02ULL, 0xB05B5B276F64EF8CULL, 
            0x39622FC270CC05E1ULL, 0xBAA7CA3177F665C2ULL, 0x3172168E3941FB24ULL, 0xCF95F0FBEE774761ULL, 
            0x8790280FF0B1DB6AULL, 0x0AE6FCB99F0AC669ULL, 0x73B7B79E3D687E05ULL, 0x5BD5459C6F3FD03FULL, 
            0x2A3F06FC1B1D8F40ULL, 0x6C648B01082ABA99ULL, 0x1E62D59D2AF3C1A7ULL, 0x620E889B227035E8ULL, 
            0x786C6A6A82275E0BULL, 0x278CD0CB6D42A686ULL, 0xD484EB635E43BD82ULL, 0x8F27D05B2B2C7A45ULL
        },
        {
            0x59676366706AA432ULL, 0x27BBE67292AD07DCULL, 0xDFF02A373115FD36ULL, 0xA4B2BB629485087EULL, 
            0xDB71B6DE0CEC2490ULL, 0xBA41FA96D486D851ULL, 0x303A2E9F49B47746ULL, 0x1308335867C3F07BULL, 
            0x1ECBD7C187FD3D1DULL, 0x2ECE49DF7A4BA082ULL, 0x35E8713479430543ULL, 0x5B27A5AF598AB714ULL, 
            0x5AF933DC16345E7CULL, 0x7156780224194312ULL, 0x4055BF0B27C26F9EULL, 0x141173A88342961BULL, 
            0x2D09E0F39FFC7B80ULL, 0x8AB4FC6DF02B3251ULL, 0xA913DA80128D6BF8ULL, 0xAB10A69F36B88E4DULL, 
            0x0DA83EEEC402DD47ULL, 0x9E4E0EA59F00EE29ULL, 0x02D61157209F9774ULL, 0xB438C026A3019F0FULL, 
            0x0BE136F7302B6055ULL, 0xD9868078CF0AA87CULL, 0xA7B34298730DAA75ULL, 0x6444B60DA12745BCULL, 
            0xB2D21E75F92720FCULL, 0x6D7C71060F696A65ULL, 0xDF1D3E553D12FC99ULL, 0xBF966506344630C4ULL
        }
    },
    {
        {
            0xFCE890DD26866198ULL, 0xAB52DFEF312B9C3CULL, 0x35730DF375CAC585ULL, 0xF92244FD1BCE5485ULL, 
            0xD00615F74244990AULL, 0x62656E659538B8FEULL, 0x511D52BED5236533ULL, 0xC18CD95BB60A1FB9ULL, 
            0x2535C4B9BA9997C6ULL, 0xB543B4A03CF690A5ULL, 0x9D86FF3B776C6F84ULL, 0xE1C393AAF670595BULL, 
            0xF4075EE230B944FAULL, 0xA32D9A3E565A280EULL, 0x0E718DA88CE0C8D7ULL, 0xE31993E21BBA04EBULL, 
            0x29C20D13F0E209EAULL, 0x21E261D4288DB1F3ULL, 0x2CB14F87B225DB6AULL, 0xC9EE9FD5D883CEF6ULL, 
            0xAC8F9A60C6C822ADULL, 0x081644CC8FE9B04FULL, 0x4C8EB77007C32365ULL, 0xEF7F0BFC2A17717FULL, 
            0x9AEB97865F8D2576ULL, 0x35528EA8BFC0E8B5ULL, 0xE750018297414207ULL, 0x03AAB308545FCB4AULL, 
            0x4684B2EE24FCFE61ULL, 0x2D407657921652E0ULL, 0xC8BE9E63D26F1DC6ULL, 0x012CD7F90AA6CF37ULL
        },
        {
            0x0AF4095718861BF1ULL, 0x21E958113C129A6FULL, 0x0FA100AFA7F87861ULL, 0x79EE2838A9EA4037ULL, 
            0x837B7CCF0FF5F03AULL, 0x287ED8B6F9A074F9ULL, 0x4F8D94E876E7EA32ULL, 0x2DFBA0DE2A20A8BCULL, 
            0x81D4153576AAF429ULL, 0x368C42EF50A2CB4EULL, 0x93029894CBE7AA5AULL, 0x9143B85D72376116ULL, 
            0x7BAD9099AAFBABD7ULL, 0x56DD7987E3B02738ULL, 0x96BEF02E0CC62BBFULL, 0xA2F1441F26334879ULL, 
            0x77BC7BEA5D31B504ULL, 0xBDB2F99D9D9F9A3EULL, 0x6F7FFDC304C0F263ULL, 0xFCB7E67B63D83E2DULL, 
            0xC3F1948DA5395640ULL, 0x416FB8EACA1A0884ULL, 0x6B8648C0A9943312ULL, 0x5E3E9B3EFFEE9208ULL, 
            0xF34DCEE8BF87983BULL, 0x663594307DDB5D79ULL, 0xE9E3393B563E224FULL, 0xE377A78DA99458DFULL, 
            0xAB35738750178C06ULL, 0xD7D89B3A41C32419ULL, 0x8452B0399E9F27EDULL, 0xFEECB12C680BAD83ULL
        },
        {
            0xD8E52C943BE4D7F4ULL, 0xA5544EA6ABD0413CULL, 0x7176F389E3C2D469ULL, 0xB5A20882FA4C0D76ULL, 
            0x6106E712D4A8AD03ULL, 0x43743228D137EC61ULL, 0x497C716A1B5076F9ULL, 0x6FBFE44B79F08052ULL, 
            0xEDFA5ED1EBF02067ULL, 0x1C2DF9112359D49BULL, 0x850CF0AB73B9D67AULL, 0x24A014C07BD84EEAULL, 
            0xBD6EAD24323BE855ULL, 0x30BE35311118263DULL, 0x435B8DF3072C0A71ULL, 0x45C4E883D47B6D9EULL, 
            0x36ABAA3F32E33BB6ULL, 0xAAACF542C747340AULL, 0x2297D032AF7E6984ULL, 0x335A3919A348CE37ULL, 
            0xED36600B1A314F86ULL, 0xDA53F7B1C05C6763ULL, 0xBD651DFAA9CF4C66ULL, 0x4576ED9EF11ECA75ULL, 
            0x656C83944726A9F3ULL, 0x3FEA8183EBBF0545ULL, 0x85ADADB9B6A7B132ULL, 0x7A56FF2E4ED4333EULL, 
            0xB34EBAFA4F4A7533ULL, 0x32B0BBF148C592EFULL, 0xFCB9BACDD500FE0DULL, 0x7538DFA4FBEE2F01ULL
        },
        {
            0x7348E83B2CE26A2CULL, 0x63A41DE7803DAA59ULL, 0x66060239E7693C23ULL, 0x9C9595BC186FB62FULL, 
            0xB97962BA68805833ULL, 0xF3B5A2F0192AEF2AULL, 0xC97BBA85F9A117F8ULL, 0x26297F87D77DEC3AULL, 
            0xBA05FE3303B94E26ULL, 0x5B3236C8D1FEBC7EULL, 0x2A4161442D64C7A1ULL, 0xCF29D4AFFFA834E4ULL, 
            0x0AFE7043713C1A1BULL, 0xAFE1505D189471C6ULL, 0xF85DF3AB31A10EC6ULL, 0x19C0CC562462ADF2ULL, 
            0x367E24687B1FAB2FULL, 0x5CF6B1E09B1716EDULL, 0x8DE993F448CF93F5ULL, 0x2000A06F7F4AF81DULL, 
            0x37172AB585C49362ULL, 0x0FF21DB9918146E5ULL, 0x937F06AD58D03DEBULL, 0xC526B868D60E15FDULL, 
            0x54D08E2EFA6FA240ULL, 0xEEB54486DF112E0AULL, 0x606E642B3DC6B77BULL, 0x36C0D6E45BAD2646ULL, 
            0x5B813C31AB463EA7ULL, 0x4CBF0FFEA0009D84ULL, 0x7E45C150371ADA95ULL, 0x81B2FCB03D7331A2ULL
        },
        {
            0xBF3BCAC4E682DE63ULL, 0x7329190C05973BDEULL, 0x459F5A91293B7FEAULL, 0xEBE73DBC9CCCD6F3ULL, 
            0x3C17CA602392E7F9ULL, 0xFADEB1E2A063E25DULL, 0xA978CEFB6AAB0614ULL, 0xB958A920A4F224FCULL, 
            0x11FF93C89337B654ULL, 0x67D6658BD6F1F5CAULL, 0x094352399683BE05ULL, 0xB53F17708B3BB3CDULL, 
            0x4B9793CC9BA4D754ULL, 0xEE5DE88B2A8EC661ULL, 0x3680A39F90DFEC89ULL, 0x5B4EAEA1942E2687ULL, 
            0x3FB20243C8F92B01ULL, 0x10AA331C2536CF97ULL, 0x70C2C5BDB5978ECCULL, 0xB7672779A934B338ULL, 
            0xD45A040BEF4DCE11ULL, 0xC809C3E20411D777ULL, 0x66CD94288528D3C1ULL, 0xAC49ABD4184313D9ULL, 
            0xDF2EE609CF5086E9ULL, 0x6F5C4E1A82625703ULL, 0x8C52AC6463C57A01ULL, 0x7612027DB6626FF5ULL, 
            0x4BEF305DC3745D38ULL, 0x9E2D32FCDF968503ULL, 0x5BEAC32F6F5B1118ULL, 0x0C17FF86BDF62FFFULL
        },
        {
            0x40FA8DA0BC489116ULL, 0xBCD88975F4AD6233ULL, 0x38ADE5526D888CA0ULL, 0x4FD6939CEBADFD0BULL, 
            0xF679F87FF7BD14C9ULL, 0x9507B32797DA5B4DULL, 0xB19C1FE2AE5981D9ULL, 0x6728C35EF7C35EC5ULL, 
            0xB38A3DF4FBFC719DULL, 0xAC6FBD0EC85C010EULL, 0x8D64D2FE92418E79ULL, 0xBA3518CD01E6D4B8ULL, 
            0x33293B3A006D9B78ULL, 0x9240F25FCB133186ULL, 0x9895DA530613F6D7ULL, 0xDCAB3B1BCC3FF7DDULL, 
            0x6BAA967C34D7AE9CULL, 0x40FB959B4BD5AA60ULL, 0x91CFC01E8DCF8A85ULL, 0xAD641EFC51B03BA1ULL, 
            0xA74B74311CA75E9DULL, 0xD0B98B89F125B4B7ULL, 0x153315124D2FD5B8ULL, 0xAAD2D91F91945F63ULL, 
            0x82B5A8A8057540F5ULL, 0x0C49454ADEA31746ULL, 0x2F67FC355BECC933ULL, 0x64461BED1328DA0BULL, 
            0x8B92FD0D7CAFBF24ULL, 0x0DB31ABF6275364DULL, 0x75D18A0CBBF0CE6AULL, 0x4B5C28E770856A87ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Pollux::kPhaseEConstants = {
    0xF48B325913BEEBDBULL,
    0x84D69CED391499F9ULL,
    0xDD79A36CBDF93D53ULL,
    0xF48B325913BEEBDBULL,
    0x84D69CED391499F9ULL,
    0xDD79A36CBDF93D53ULL,
    0x4368F691AE5F326BULL,
    0x8342DFB5AAE5449CULL,
    0x44,
    0x8F,
    0x6D,
    0x7B,
    0x90,
    0xA1,
    0xC1,
    0x0E
};

const TwistDomainSaltSet TwistExpander_Pollux::kPhaseFSalts = {
    {
        {
            0x2AD669AA55556DE5ULL, 0x102767FC2FFBD1BAULL, 0x9200D2F6CDF73855ULL, 0x794B39C020146872ULL, 
            0x30D6EC2AE19B8047ULL, 0x5367D630AA645C87ULL, 0x3E7DD95335975EF8ULL, 0x1634FF9BDDD63FF0ULL, 
            0xBE785E670441F4F1ULL, 0xFB1C7A5A278C96CAULL, 0x9485B9832E35924EULL, 0xF297EFE381835D9AULL, 
            0x33B166E5CAA1C606ULL, 0x2D2C36BBBFC6A7A5ULL, 0x69ABB04CF8FEDB17ULL, 0x827BA51CAE474FDFULL, 
            0xD7B2B8C76A85BADBULL, 0x8C1F1AA211926862ULL, 0x09028D7AD0384022ULL, 0x1778986CA6138DE0ULL, 
            0x7782BD8D7052FC29ULL, 0xF94A6299FCD14991ULL, 0xBAA2D38AACCCA4F6ULL, 0xADA6910D86C8BDFCULL, 
            0x472B7B67759F37D9ULL, 0x11C3E4404D38350CULL, 0x8D5079B192AF6DCAULL, 0x41FD88BA02749314ULL, 
            0x52B60FC4B58211AFULL, 0x7EB24C2A1C129651ULL, 0x8F19842ABDF5B020ULL, 0x3AD2132D3915EDA9ULL
        },
        {
            0xD44BD9AB2396ADFFULL, 0xBFA1A7E66BCBBE53ULL, 0x4D86AD7907F54FF6ULL, 0xDC83CA8E178B188CULL, 
            0x783E9D72E79226E2ULL, 0xA4CDB8F68021D70EULL, 0x5A8CBF65E5A83E45ULL, 0x8F56A97B74F390ABULL, 
            0x82CD6B6116A43891ULL, 0xBE1F60E2D2B6FDE5ULL, 0x9F4AC370C6D1BDC6ULL, 0xD47C0CD7C1944B22ULL, 
            0x2DDB5742ADDB7D40ULL, 0xA1AB965A1CD68741ULL, 0x874E917A52313EACULL, 0x04076810BB9815F8ULL, 
            0xD132228BE9754DD1ULL, 0x9691C36758322E6FULL, 0x2FF738143FF2D3B8ULL, 0x818A3DF9C97080D7ULL, 
            0xAFB3112A24F625D2ULL, 0x2D44E9E5DE37C791ULL, 0x4C1F6E3628D519EBULL, 0x4B0008DCAF4DDF9BULL, 
            0x9C1EE357E970EBD9ULL, 0x1349A339A16542F9ULL, 0x3D085BA99EA1C9B4ULL, 0xEF4AA274FA8DE7A2ULL, 
            0xB26E9BF93CB133A6ULL, 0xD9A5E2C76E1F8DBAULL, 0x4CE13F2D235D1A69ULL, 0x76AC0E05792D0445ULL
        },
        {
            0x7112FFF3876260B0ULL, 0xC1CA303C99ACB4BFULL, 0x1DBFE60F10B2D0F2ULL, 0x69E8670F2C5C94E3ULL, 
            0x8951B3BCF56B671CULL, 0xA316AE583A624A1DULL, 0xBE3571D8E15E3483ULL, 0x7052B6CAEBC4C3BAULL, 
            0x29E130B8A7224C6DULL, 0xFFCBA4D2631A6B77ULL, 0xE1BD9A8F0F04EBDCULL, 0x57BB9F97E443801DULL, 
            0xB57B93A3854BD31EULL, 0x9BCBB43DA85159D4ULL, 0xFD3A924DBC9079A5ULL, 0x558326388F66DCF1ULL, 
            0x3D40B04AAD76BF46ULL, 0x96FA61F216F788CCULL, 0xE9128CAF5399DF13ULL, 0x7CD9E32495580C60ULL, 
            0xFF1FD64AC494D39EULL, 0x4E5096F2CA1A1DFAULL, 0x0C448E91B2C08177ULL, 0xCE1EAA486150652CULL, 
            0x2D285072D2F49F7FULL, 0x39440809C464E175ULL, 0xE2D1FC39E39860E1ULL, 0x7B065998CD6B5257ULL, 
            0x9F2110DF3AD70948ULL, 0xDF2803192DDD5174ULL, 0x8658F7AEA8913163ULL, 0x85CFCEDE8870821AULL
        },
        {
            0x82F399A7A1ACECE0ULL, 0xA89252C302473B09ULL, 0xE03B633148275EFBULL, 0x1EEC9440D6F79784ULL, 
            0x11B41C971C6222A4ULL, 0xD4A7CE7F60844FAAULL, 0xC082F95AB8635D46ULL, 0xE3A2573A9CCD9D0CULL, 
            0xA3E30FEE667EC493ULL, 0xB3E5C1DD4F3E091FULL, 0xB720E937B2D9C3C7ULL, 0x693B081EF53D7D13ULL, 
            0x49590A13F994B4DCULL, 0x578D54D7EB9D7DA8ULL, 0x8375A1751A06E0F3ULL, 0xE7BE3C91F8AA191AULL, 
            0x079B4B28C2E07EDAULL, 0xB6C3E56F65C91055ULL, 0xCC1849FCCE4B66ABULL, 0x6FDBD7C2B90E6E84ULL, 
            0xCD17128046F31694ULL, 0x36D8201F0F350A0AULL, 0xC307FB8AE697C089ULL, 0xF763A08BFEB1106CULL, 
            0x6BA82177ADE8EBADULL, 0x145588E3C620B2F4ULL, 0x7E81A25256C1F570ULL, 0x723540EE9932CA8BULL, 
            0x62A0AF2F0A7C0BE1ULL, 0x48547F99B85A73A8ULL, 0x13C4063C1F04835AULL, 0xC7D244A249FE31C7ULL
        },
        {
            0x97A4AB49B20B1ECEULL, 0x7CE0C44897F178BDULL, 0xDF978BB30BBEED8DULL, 0xE00FC346A54CD345ULL, 
            0x34BC0CE703B55A24ULL, 0x70B5B8BE837941F9ULL, 0xF272ADC561A2D7D9ULL, 0x0456CE0EB86E5440ULL, 
            0x95CDCD47CC951633ULL, 0xD26D3D93D5DE4699ULL, 0xC3A1378C7A59163FULL, 0x0E1334D58FD9CFBFULL, 
            0xFEF35A1721ED6B3DULL, 0xD49226A59E12331CULL, 0xD5914027A4AACE15ULL, 0xD72BE74E43BCB5B6ULL, 
            0x1E3FBAED100D949EULL, 0x1F1EF86B944A8214ULL, 0x4835DFEFE8B7C5F3ULL, 0xE191874041E9FB72ULL, 
            0x3B526C7A9DD4821CULL, 0xA6A75D171C55EFD0ULL, 0x68C0E9F90C6B4677ULL, 0x5767101E0998C61EULL, 
            0x51B9863BEAE89F18ULL, 0x1149D442771F95F1ULL, 0xC79DE06E00DD8AEEULL, 0x92B416BA42417B8BULL, 
            0x169C32F708FAF5B4ULL, 0x321B01D60E0257F8ULL, 0xB66776C8237D8EF8ULL, 0xB1717CF195A1125BULL
        },
        {
            0x8AA8C866C0BEFD5FULL, 0xD73BE32BC7E91F9CULL, 0xA17128516E899FA2ULL, 0xA755048FC619888BULL, 
            0x91D83E72F372E475ULL, 0xD24DB49FB726D533ULL, 0x78601C71AB523386ULL, 0xF7F590FF767CDA6FULL, 
            0x019C6B79678183FDULL, 0x7666896F110EDF4FULL, 0x596A29571E98E0DFULL, 0x1C04E2CD4E38C6ACULL, 
            0xFB70B8736F0D23C2ULL, 0x2B38C659C498C6FEULL, 0x1E6FCDAB64DEDF95ULL, 0x281F844B5C22BB0BULL, 
            0x21BE0E843DA4F2FAULL, 0xB9909A836BF2605FULL, 0x84424277BB5887DEULL, 0xE3A7F8E41F42F3E9ULL, 
            0x59EE9C338C3B52C9ULL, 0x407612EDE908FCE4ULL, 0x35D0FFC38A5B2BAEULL, 0x1C16B6A5AAAC81AFULL, 
            0xF70B3C56E2A7491FULL, 0x9D67315ECF8F1CC7ULL, 0x93A40F2E1140DA27ULL, 0xE191AB656274E367ULL, 
            0x859C4435DF7043F4ULL, 0x23AAC8D1BCF04E92ULL, 0x523D5C7455A2B1DEULL, 0x165110D0BDF90D41ULL
        }
    },
    {
        {
            0x75E333801885D4AEULL, 0x6C6EF5D6915E25AFULL, 0x145FEADA31B63752ULL, 0x7387EED619DD1B09ULL, 
            0x64847C9FB90BE3C6ULL, 0x1D8027B3941E64A0ULL, 0xCED444E6B376C722ULL, 0x971B6DB9CD9BF746ULL, 
            0xF115CC66C2EEBE76ULL, 0xF54445EC1A2BAC8FULL, 0x27863D63CE7052F1ULL, 0xCED0EEEA384E92DFULL, 
            0x7BAAF59B2693163DULL, 0xACD3B89072417773ULL, 0xC739BFC829969683ULL, 0x030686790083C938ULL, 
            0x1F7F9C0C9260A4E3ULL, 0x35BEC077A6C5FB7FULL, 0xE848DE0D8FAF760BULL, 0xC88C1E427F94AB17ULL, 
            0x76BB202B3CEAC8B7ULL, 0xFF0EC0BCD866A45FULL, 0x13929B0128D2410AULL, 0xB6C96535B50460DAULL, 
            0xDA77DA423D78D505ULL, 0x53E3FEDEF9217591ULL, 0x25CE069457FE5E39ULL, 0x7003979C0E0D5CF2ULL, 
            0x6084E1E38BC3B27EULL, 0x0BF7D3C7528D53B3ULL, 0x8BB9CC4FC80A460CULL, 0x0CD44B70D7F88F39ULL
        },
        {
            0x697690D3205C47ABULL, 0x94636F85D178FBD4ULL, 0xCA23B20A1323F63CULL, 0x72B887608AF5AEA6ULL, 
            0xBC499B509C308F34ULL, 0x61BEC463624D0F60ULL, 0xA36A2A90ABE08C43ULL, 0x7F25088C2658F9B7ULL, 
            0x4BC20868C19E989AULL, 0xAE671F88A05EED11ULL, 0xB13827030A85519EULL, 0xED8C801D89C46280ULL, 
            0x17F12634C548C662ULL, 0xD2D6763B45D65055ULL, 0xAEB0154B816B0918ULL, 0x5B91017515A32D7EULL, 
            0x7C046A9EFDAC766BULL, 0xD40D3F021CAF6392ULL, 0x5977277CE3810814ULL, 0x006CC220B1880D2EULL, 
            0x8134344BA4D080FDULL, 0xBDBF857E44E3A474ULL, 0xF09BF22291B4C5E0ULL, 0x70D2B73D2D9DCAA7ULL, 
            0x6F884CFAE6A815D5ULL, 0x2BE0B2DF0FC0825CULL, 0x8DE04790CFC9F68BULL, 0x062CA1E4D46197A3ULL, 
            0x2918A14834E72249ULL, 0x39F0757F420DC002ULL, 0x9E7E9159E25190AAULL, 0x6E25157FF12085D9ULL
        },
        {
            0xC3844341A424CE49ULL, 0x07F6BB561BEBABCCULL, 0x5751FB14FB9DF931ULL, 0x09BFCAE7ED8776FCULL, 
            0xC1D03009D54B5AC7ULL, 0x713DEF8948F0960EULL, 0xA7DB7C1C55A81F71ULL, 0x70A085E38777ECDEULL, 
            0x5718EADC6E51DDC5ULL, 0x675ABC89D56FEA88ULL, 0x448DBD185E275FB9ULL, 0x779ADB197EA22EEDULL, 
            0xF107B7166435B656ULL, 0x29972C010B290408ULL, 0xAE424C84B9D131ACULL, 0x83757778C50C8233ULL, 
            0x5EF7563F35748847ULL, 0xE2E639EA610532F4ULL, 0xB4711FED34513FCDULL, 0x495E298A30F5111AULL, 
            0x70F7CAD511A28E11ULL, 0xE0C91470FD979A46ULL, 0xCA05CDB24C5084DFULL, 0xBD1A26C2C9E7A4B8ULL, 
            0x5645418D2ACDE991ULL, 0x061AE648BF183D6EULL, 0xC9F87F8FD69E97F2ULL, 0x59A6CAD3D2B060CAULL, 
            0x4CFDC3C5A5DDDCF2ULL, 0x9ABDC1582EDC5A30ULL, 0x5E37F94B84897E4EULL, 0xE3A84A31A8E0D2CBULL
        },
        {
            0x3877DDBBC8EC3A28ULL, 0x00780F5C23626226ULL, 0xA9B52068D1D2F013ULL, 0xC682D8964E9795E9ULL, 
            0x7B28D616FC634A32ULL, 0x33FC80F1608221E2ULL, 0x51B835ED2E17B014ULL, 0x4A7D81D2FFCDE98CULL, 
            0xE70F03352EEA9FAEULL, 0x76DD15CD6CF6C17CULL, 0x2DFB24D4345854CCULL, 0x0FB1BA8D6BFAECDFULL, 
            0x354171B2D57D8C57ULL, 0x3CECA2F2C4FE8F82ULL, 0x1F38B4F1E961E962ULL, 0xE0BD23859B672F0EULL, 
            0x5432E5B365EAC493ULL, 0xD023F67B095F82C1ULL, 0xAAC12C0C6CA69AC9ULL, 0xF358658A9BD0A981ULL, 
            0xB074E85390FE3892ULL, 0xFF69EC8DE5708489ULL, 0xA2E2EEF985DF60F7ULL, 0x2FD740A6D88D2C18ULL, 
            0x3CF4C133B91FA80AULL, 0xBC6CFED7DD5AE4F9ULL, 0x3E20CBEC076F9911ULL, 0x5F209F02C75F23DEULL, 
            0x23350CFB7A03AD70ULL, 0x97CB97BBCD2AC371ULL, 0xD383F70921EAEBBCULL, 0xA9D7E6CE1B010982ULL
        },
        {
            0x5323DD040D565C6EULL, 0x1A2DC15B1FE4B829ULL, 0x6A23E98288E2D487ULL, 0x038D567E57D56620ULL, 
            0xA7C9B9702466A8A0ULL, 0x7C3E79A97F26CE3CULL, 0xFB6055392B47E74AULL, 0xF272DC8A17877DF1ULL, 
            0xA8D6768830EEB252ULL, 0x88EAD5CC251B5B2EULL, 0x4FF10709D1180E6CULL, 0x94B3B8F5E48E601DULL, 
            0x620B36F7E0E3CB71ULL, 0x93535BCDB4A0EB37ULL, 0xB4B23BDDD2F0FDFEULL, 0x1A966229BB6BD0A0ULL, 
            0xC9D15A2ED54FA469ULL, 0xFFC323F7A2F78962ULL, 0x022F0BDD5B5E01FBULL, 0x3B2144669F818279ULL, 
            0x757BA7AB5BF165A9ULL, 0x7297F0A0FE1CCAA3ULL, 0xEAF79F20B77A2A9EULL, 0x97C2CAE545083689ULL, 
            0xF479F1F9667BBBA6ULL, 0x4F949FE4D4D8CE5EULL, 0x39AB69F3EC8FA089ULL, 0x0B2922E8D7D17C75ULL, 
            0x1119C48EEBFF1106ULL, 0x52C0DF04B08D3B71ULL, 0xAAB039A45D1377EEULL, 0x275792C22A60C501ULL
        },
        {
            0xBB42E0C906C2843DULL, 0xC703C1CB5F266C8EULL, 0x6DB2368A8A6B4AF6ULL, 0x22DD738110EF20FBULL, 
            0x9508A8AB65028B3CULL, 0x8B8931ACC4F0372EULL, 0x15AC5D53351723C1ULL, 0xD4FFC93D0044C823ULL, 
            0x3010AAE3D74CAA0AULL, 0x726836D646B0A477ULL, 0xB4E275EB64090259ULL, 0x6BF6707858192FCEULL, 
            0xD85C3C623DFC42F5ULL, 0xA9D608CA10675973ULL, 0x9BC98C3B1E953720ULL, 0xADA94995F1F9D70DULL, 
            0x552980B128E9F347ULL, 0x9B1499FBC1B3017FULL, 0xDBC7A46024330BDBULL, 0x0EBBEDD87131FB69ULL, 
            0x9C73BCFAADD18611ULL, 0xF205231919995859ULL, 0xC634186CA3F99E37ULL, 0x92510E1A1D83BC2FULL, 
            0x2D500C5D47344B33ULL, 0x939299158B9A0A60ULL, 0x880719D3C106C4DBULL, 0x22D92A6521CC06FFULL, 
            0xD64E3DEBD2CF7E34ULL, 0xAA35A8A7FBB0EC17ULL, 0x7B2E8C47CFF93019ULL, 0xE6983FDF6D23985FULL
        }
    },
    {
        {
            0x1E2CCFEBBBE55E74ULL, 0x21C18862B1E94DB4ULL, 0xF5AFE8210E80D3C0ULL, 0xDBE5D3533B7D52B5ULL, 
            0xCF72E48E0452CE76ULL, 0x5D81642ADA49F129ULL, 0xB3593E6C231B7616ULL, 0xF0896A1191E12734ULL, 
            0xB62B1B04D3F26DBEULL, 0xAAC948EAFD3A2763ULL, 0xC3AE1FBA6CDAFE7AULL, 0x029DCD42BB8ACCA3ULL, 
            0x7BB75422EC49708EULL, 0xE3B9CF3EDAD4128DULL, 0x9E96FAC176A15C65ULL, 0xC2269104721BB137ULL, 
            0x29DABAB9FFCE4F56ULL, 0xB136AEFE7C1CD8A3ULL, 0x4BC900CF96F148DBULL, 0xCEA4FAB74A1A7C63ULL, 
            0x6ED9B76FCFC2FC75ULL, 0x0175E4353EFEE303ULL, 0x51B757EDBA92A117ULL, 0x766C9E540477C35FULL, 
            0xB0C647FA8CE8D4C2ULL, 0xA134025B535EC392ULL, 0x5805CCAC0CEC928EULL, 0x2DD5E79CD88485A3ULL, 
            0x45FE8CDD6A4A7765ULL, 0xC1D4F6EEE510279CULL, 0xDBE97C2422E3E771ULL, 0xF2C0FAD7918C19EAULL
        },
        {
            0x5CA8A601367F062FULL, 0xCE1A037C06D44114ULL, 0x52760AA3BC60A406ULL, 0x2587217D0356B728ULL, 
            0x59A6262F59565C65ULL, 0x0FB6773DF39B966AULL, 0x7749103C5DD42DF7ULL, 0x45069A4704D57AA1ULL, 
            0xAE8F8DBE85B071E8ULL, 0x6390683CAB80D522ULL, 0xBBD7877D9820BA66ULL, 0x8AA018A5F2BAA8A4ULL, 
            0xA1703A2DFBBA76CDULL, 0x639573646F7E9BF2ULL, 0x45C7293C98F9B15AULL, 0xA8B07BBA235E3AFAULL, 
            0xADBFFEE736BE7140ULL, 0x63BE68C05DE9298FULL, 0x82B974F24955B909ULL, 0x2406EF75E5919ECFULL, 
            0x496361559DA27ED4ULL, 0xB7C94F5B3FD16EBCULL, 0x0C019CA734A4B473ULL, 0x58949FA520CC1DB0ULL, 
            0xEBB5D341D63AC559ULL, 0x838E1FC59A60BBD3ULL, 0x6ADCD4121C36480AULL, 0x01A334695E719B28ULL, 
            0xA3BEC064D6D7E85AULL, 0x248CBED51BF46597ULL, 0xF48058CFC184A43AULL, 0x20E929D726EC2179ULL
        },
        {
            0x91C00D25B9A3CEBBULL, 0x42FB32CD10F5EF0CULL, 0xFAD0FA9D73BC73EAULL, 0x9AE4DE381B0DBE0BULL, 
            0x117746B95DB2540BULL, 0xF241A3D96298ACABULL, 0x36300DC847C33FE9ULL, 0x00802877E0BF5EBFULL, 
            0x061001AA56F181E9ULL, 0x3D5091AD4C02642DULL, 0x00599A43A99019F4ULL, 0x09F6DBC76EFA050AULL, 
            0xD1A8DBE4438F0F18ULL, 0x6463CC63C72C2B66ULL, 0xABDDF56E2F38FBB3ULL, 0xF0B1C0D42203A5BEULL, 
            0xFDECDD8DB319F59BULL, 0xE36098B95894F94FULL, 0x020519974B1E4080ULL, 0x790A05975ABC019DULL, 
            0x4792C0CEA5451CEEULL, 0xEB43F9388543B09BULL, 0x776AA8CDC9B4A5E6ULL, 0xA64067FF35EF79A9ULL, 
            0xA1DBD92DCD97E3DCULL, 0x81D855D3F643EB01ULL, 0x9FA9125D47E0D2E2ULL, 0xC6FC745690EB951EULL, 
            0xDEC4EBBE20A2AA3DULL, 0x1347F62F36342D69ULL, 0x4E499FBF8BE20705ULL, 0x0AC574199045F852ULL
        },
        {
            0x573B1C6B22CD523BULL, 0x31487A1D05FC7377ULL, 0xAA0C643E4D4DB887ULL, 0x2B7A3D43E9681BA6ULL, 
            0xA91DC241DE4CDA1EULL, 0x5941AC3E8110011BULL, 0xE231DA193BC01418ULL, 0x8597C51296B68CD0ULL, 
            0xDB10063075A7EBF4ULL, 0x65A7FEDD97CC30E8ULL, 0x4173E7DDA4ECFD76ULL, 0x8D2025D25EA06925ULL, 
            0x14DADADE495ED154ULL, 0x7F6B7531498F3304ULL, 0x3A272AA41E5042FAULL, 0x4F82D1D08CC337EDULL, 
            0x2E856C3C850AC10BULL, 0x985AB4AEBF8DF7A8ULL, 0xFD3FB6C374747371ULL, 0xDA81A41A284E736EULL, 
            0x89D3632CAEB91621ULL, 0x1DEF1DC087992A5BULL, 0x76AFA9B0E47C8A5FULL, 0x4DA46E89B0B38F50ULL, 
            0xED77847F14EE7FDDULL, 0x776BA268BE59A7E0ULL, 0x961C8347513E9A81ULL, 0x07128ECEFDEE3ACAULL, 
            0x0193D10230BF674DULL, 0xFAE65E39EC1E0983ULL, 0xED82635AFBB8F851ULL, 0x92E74067E3EFBF6AULL
        },
        {
            0x15DAA5B79AC61FBDULL, 0xEC7EE2E032BE229DULL, 0xFFA3BE557629C5CDULL, 0x4C9FDC46A7733B9BULL, 
            0xEDA813A67A25AFA4ULL, 0xD6A49F31DE78AB33ULL, 0x1EEA77FFD1C80DACULL, 0x6B335CDC75487317ULL, 
            0x3CB401BBE96A8B73ULL, 0x58D7D18A9385B345ULL, 0x6C0782E7A211A24BULL, 0xC714270CF2DFAF85ULL, 
            0xD9848A710E560857ULL, 0x484E23B3AE23B17DULL, 0x648FC6489D6CB802ULL, 0x250409397DC6A28AULL, 
            0x7C48861DE78A43F9ULL, 0x6F906257CE10323FULL, 0xA164A7CA9A86C09EULL, 0x73ED5E0AE552DCE9ULL, 
            0x5FF4E114F0E07810ULL, 0x30401FF5822F6879ULL, 0x878CE6835ABC6ADBULL, 0x2140F38A69D25760ULL, 
            0xF349F172768B5308ULL, 0x1208C7A3061AAB73ULL, 0xCE28AEC4B14B1642ULL, 0x326E955F2BCDC31FULL, 
            0x577055B5B9569079ULL, 0xFCB31FD1AA4517E0ULL, 0x5952A0B153953EADULL, 0x251FB1AA64C31309ULL
        },
        {
            0x99B1CCE563DE587CULL, 0x0056F99B6875533AULL, 0x1D30E92889C7EB42ULL, 0x120F0EA1D5CA0B2AULL, 
            0x083CEC8ED1795E85ULL, 0x4E805CED0D38A263ULL, 0x874F12DF3CC06B3AULL, 0x0B16F3B4ACAA0EA1ULL, 
            0x1BFB4500FA45AA3DULL, 0x88C8C8470137F189ULL, 0x0433018BF333F4D0ULL, 0x01AA6E440FA9F94CULL, 
            0x9888CADE46449A82ULL, 0xC2D76716EAB081B4ULL, 0xC8919AF872EF4579ULL, 0xBB92C6BCD803B8AAULL, 
            0xC21433B8B2D43308ULL, 0x5437B1C9ECB8DD99ULL, 0xFC3DA8E4CD658EF1ULL, 0x7B82D0678FE2F52AULL, 
            0xBAD84FAED4B9C9ADULL, 0xE888B256A4DDB7D7ULL, 0x2C778C1D171D2C44ULL, 0x1430841210AA704AULL, 
            0xE144CE3E219B05EDULL, 0xB9894177F071798DULL, 0x24DEA4DCD64B6796ULL, 0x33E9CA411B278A21ULL, 
            0xC56108E46016D25AULL, 0xCE2DE3BE6E00AC58ULL, 0x5BAE06B1230E1123ULL, 0x9D20CE7273AEBA4FULL
        }
    }
};

const TwistDomainConstants TwistExpander_Pollux::kPhaseFConstants = {
    0xF8BDFBFAC7F203A5ULL,
    0x90F5991FEC816DA8ULL,
    0x6DEB924281AA720EULL,
    0xF8BDFBFAC7F203A5ULL,
    0x90F5991FEC816DA8ULL,
    0x6DEB924281AA720EULL,
    0xFA736371858B5E1AULL,
    0x16965345E8CBE5C6ULL,
    0x4E,
    0x3D,
    0x65,
    0x7B,
    0x3D,
    0xE1,
    0x2E,
    0x98
};

const TwistDomainSaltSet TwistExpander_Pollux::kPhaseGSalts = {
    {
        {
            0xDA5C0A96C882ABD6ULL, 0x85F3365455913C80ULL, 0x74B0B6FCB51FE12AULL, 0x1203C2EC600DEB89ULL, 
            0x524AE998791DED62ULL, 0x529E27C06C109188ULL, 0xAF6B541FC0D7E53AULL, 0x09E3506E085428C6ULL, 
            0x434DECD24E204C57ULL, 0x35F2DF2703A3104FULL, 0x41C62AD61E609076ULL, 0x1BD11795D5216C83ULL, 
            0x2059D93DDEA0AD80ULL, 0x29793ECEDB22EDBDULL, 0x31B153C6A2F7EABBULL, 0x4CCB0D7EEC3E47B1ULL, 
            0x473C2A01591EF064ULL, 0xDD5E9E21DBF2BCE4ULL, 0x2B14FCB7F8E7C162ULL, 0x5169FE3A641F0625ULL, 
            0x413424D79329E8CAULL, 0xCD02D261E8CE4CB2ULL, 0x5E3987F9BC96E006ULL, 0x7E8E145B6D3D3DDAULL, 
            0x7721FE21974FE3A7ULL, 0x59321F15F1D5FA5EULL, 0xA280E3562E9C2B1CULL, 0x83EA08E3BA255A93ULL, 
            0x2756C66416DDF78BULL, 0x357826442E71D913ULL, 0x9F41607C7DB4AC89ULL, 0xF979C807ED58B3E0ULL
        },
        {
            0x1A9077221B33324DULL, 0x5654174C26D9B89EULL, 0xD56A3426E75C1CF1ULL, 0xB6039D4B3AC804A1ULL, 
            0xD089C6520CE6AD53ULL, 0xCD1675A8646E4DB0ULL, 0x58AB017E23ED0D9EULL, 0x0510360C17A72FB2ULL, 
            0x531DE6DDFC94A1A4ULL, 0xC1A687D425F014F7ULL, 0x88F518432E151B94ULL, 0x0EE6A9B680089BB0ULL, 
            0x4C84AF71540FE4DCULL, 0x28C6E91858040955ULL, 0x0B2A3FEBBF106683ULL, 0xEB622456EB3AAABDULL, 
            0x76512AE3E13391B8ULL, 0x4474096149143802ULL, 0x58BD72543542FF2CULL, 0x083E540AD97C47D3ULL, 
            0x6D5774615999BECAULL, 0xC565329EB361184CULL, 0xE114FBE11559720EULL, 0x1474127EE26F6ACEULL, 
            0x26860882E477B270ULL, 0xD3AFFA64D3E62698ULL, 0xBD1C734C47E1D99EULL, 0x5DF9C4984AFE4067ULL, 
            0xD5B36431317F8570ULL, 0x2894C339AFECFDFCULL, 0xD728BD3511A4C638ULL, 0x450F0BED12B52539ULL
        },
        {
            0x084AE7EEF09CCF3BULL, 0x44964ACF88FCDE0FULL, 0x8AA32BD98F8F7986ULL, 0xB9233F040FDD3912ULL, 
            0xAF6BA229828A5AA4ULL, 0x80F55DD79CC72B4BULL, 0x74FFC046FFBA9900ULL, 0xF0A5A36A10503596ULL, 
            0xBFBFF1D9F0CA89B3ULL, 0x2355AB9927124EA8ULL, 0xB7FF09A61A226B85ULL, 0x27F9CDC5A4BCC489ULL, 
            0x60D26A84F61DBEB5ULL, 0x9DB0F91D28FD1B44ULL, 0x29E701A5A3FC9440ULL, 0xCE7D79188A097AC9ULL, 
            0xA1CEB56B19D89C51ULL, 0xB353E82862885B35ULL, 0xADC7137FC139E0A0ULL, 0xA8F26F621EBA3451ULL, 
            0x80AAF0B116FF6BA5ULL, 0x3A7971A07C13509FULL, 0xE944716FAC8B9F67ULL, 0x55536836065A21BAULL, 
            0xC7A81C6F49549DF3ULL, 0x38A3202367C80EC2ULL, 0x9DCD49135F507230ULL, 0x7DEF7950C5224481ULL, 
            0xD530AFE235FB511BULL, 0xAA000A038BDAE0D3ULL, 0x9A2815C8F659D7DDULL, 0x4821F3FEAF7A2D85ULL
        },
        {
            0x64EFFFA1E486C30DULL, 0x56CFE6F1FCB7F613ULL, 0x328DD8DAA9186E12ULL, 0x96DAE5652401E1A4ULL, 
            0x6ED828774CA2850CULL, 0x60F65BC51C28FEA8ULL, 0x6E411C1717DAE5D2ULL, 0xF082503A066B14D4ULL, 
            0xC4701E37CEF08814ULL, 0x0381CB6E129C3FF8ULL, 0x9F2AF72D4BA27F9DULL, 0x6D97A50B6F98FE49ULL, 
            0x203DBA9F515EA8FAULL, 0x5FBB3BC6BB05560FULL, 0x31CE8A7E4ABE75ECULL, 0x2D59C9051E08B215ULL, 
            0x7C4300F26B8EBF8EULL, 0xF9C3B9C274836BD7ULL, 0x3A352620C3C908B4ULL, 0xE0C699FB90E2389CULL, 
            0x232BB178728D702EULL, 0xD84A5D10C2BE3778ULL, 0xADB9358872D1366AULL, 0xAEE86A0BC74C26C2ULL, 
            0xAF9D44B45179A5EEULL, 0xDAE1BD5272118336ULL, 0x73596FAF6D6F64A4ULL, 0x6B4D8492C778A5BFULL, 
            0x6443117D37E2DCCCULL, 0x1FD03BB128EFE144ULL, 0x91E412A9EC384926ULL, 0xBB1006726F8DCA33ULL
        },
        {
            0x8E54B46C3D27F1CCULL, 0x44A2EAEA417DB207ULL, 0x3846DDAC90073B4EULL, 0x72E9EFE3D3400B5BULL, 
            0xE481072C0015369BULL, 0xFA1FDDC88B1546B2ULL, 0x63137A7BD4F9CA5AULL, 0xD6BEE468F07D6E1EULL, 
            0xBBC4E46D238FA03AULL, 0x692EB308C9561585ULL, 0x96B4C2FA79948539ULL, 0xE9CC138A9889EF9DULL, 
            0xB5423D7FB500E984ULL, 0xD490086E9F4794CBULL, 0x9FECF1003F2C49CFULL, 0xE5176F3FBA1A7082ULL, 
            0x0D1EA49294F95A4FULL, 0x457B25318A2F9430ULL, 0x04B64584A0C4D249ULL, 0x9DB81622D525A049ULL, 
            0x8EA3F1A6E08DB665ULL, 0x98D0C2A588DF15D3ULL, 0x5AD37B18BF45AD4AULL, 0x128377B8E96FD6F5ULL, 
            0x52F723F91A376419ULL, 0xA6932FF49D454409ULL, 0x9CD0CA9A4EE8FC06ULL, 0x1FCEFCE38571C6B2ULL, 
            0x9BF66CEA315BB15DULL, 0xB8E0FD3783A98A5EULL, 0xCA0CE3290BEF734DULL, 0x0EFC22E53EF126B0ULL
        },
        {
            0x809793AD910BA31FULL, 0xDD03C3EC624D744EULL, 0xEF789E3282CECD8DULL, 0x8997B408164AE505ULL, 
            0xD4013D4526EB7CE4ULL, 0x052B8224A526FD72ULL, 0x2CA4FD23DA891538ULL, 0xBAC54A91EE9DD21DULL, 
            0x126E3925197B8788ULL, 0x8AFF45BD3FC2575DULL, 0x2BCE84F75B6ED81AULL, 0xEED2B47408D8E674ULL, 
            0x3F9999D250EE137FULL, 0x597A8F104F9158ABULL, 0x554F8E6770D01091ULL, 0xC97AB0C5FF8F4E94ULL, 
            0xDA7B4C6E7C895142ULL, 0xFFB22FA40F864E6BULL, 0xEE090E8C6B242338ULL, 0x8C18EB9377BA940FULL, 
            0x890DB09A5AB64EC7ULL, 0x4F7091AC6B94343CULL, 0x225C9F6F4EDF4F71ULL, 0xEF47F080F1D80CC0ULL, 
            0xCD67C78EE09E20D5ULL, 0xE51C2DD0A944E81BULL, 0x5E37B217FD008753ULL, 0xF4FE9D2A52B3DC63ULL, 
            0x9C5DDD6645372A81ULL, 0xAA71F680202985CDULL, 0x4C7302014C10339BULL, 0x7A2F41C7A19B3830ULL
        }
    },
    {
        {
            0x443B6FD31BF35E35ULL, 0x9EA4AA416F04D156ULL, 0xC50DFADCFCC4B247ULL, 0x2240EF812750384BULL, 
            0xB3E2FCF6BF79D6FFULL, 0xF28F8C2618360D75ULL, 0x116FB0DFE85EA4FBULL, 0x865309307F3EF49FULL, 
            0xC2281BF8FB1B9C4AULL, 0x84F9EED3EEF5013DULL, 0x4E50C2BB2D1501F9ULL, 0xBBF996338F48E281ULL, 
            0xCC58AFBD76EC9A60ULL, 0x99E0393DB1F0935CULL, 0xCDC03FC8FABB813BULL, 0x97FA92650D5AA7F8ULL, 
            0x5A87BCDFE970D406ULL, 0x4E110E0866628D77ULL, 0x3ACF8D364495B2B0ULL, 0xE7723241EFD09EFDULL, 
            0xBBE2AFF05780626EULL, 0x3797699D7ECCBA21ULL, 0xE299C6EBE1110918ULL, 0x367509B74F33C828ULL, 
            0xDD1A0B9EF86B646AULL, 0x1A6E4FA934576E6EULL, 0xCDEAE3D73293A47AULL, 0x093BEBC9CDAC93F7ULL, 
            0xCB764BCC56FE7971ULL, 0x31F82522CA1CC5F4ULL, 0xF061E4EAB94412DCULL, 0x6EAD70183BF6E193ULL
        },
        {
            0xAE159AE76CA8DBFDULL, 0x4E56215110DD86CCULL, 0x89A2759B66DEB668ULL, 0x42FC9C431D25777FULL, 
            0xEC9E434D2D083E3CULL, 0x96322C5D436BA88DULL, 0x98D240EA3D44F56BULL, 0x0367AACCF7A688D8ULL, 
            0xBE61EB9D60D958E6ULL, 0x78B37A54F3CF79EDULL, 0x2F4BF68866870EF8ULL, 0x12F50D028D4C5B47ULL, 
            0x1475B15F3D889721ULL, 0x4940A1AF75EB9521ULL, 0xD9FBF25B6CED917BULL, 0xD4F0D710CF40EF22ULL, 
            0xDE5EAFBADEE97C9FULL, 0xEA6510534611AE03ULL, 0x9BA79D749614360FULL, 0xCD39AAB59E58391CULL, 
            0xE6DFBCFEF313BF49ULL, 0xE387900F22C9A5F9ULL, 0x7CB4D1D317C2DB99ULL, 0xDD53E4B3DC5F1774ULL, 
            0xAD868509C8725D7CULL, 0x9AF4A7084E349D78ULL, 0x594A19CCFE75B91CULL, 0xA6CDE14F003DF9F1ULL, 
            0x947FCFB5F5F97648ULL, 0x823D3191A98C3A58ULL, 0xE4BF1260EDD8F638ULL, 0xAD06314DE05C8EA3ULL
        },
        {
            0x628458FE33CC9A8DULL, 0x769B2B7060DB0F2EULL, 0x370116D2DEEF5BAFULL, 0x6DE56800C2A5D02CULL, 
            0xD4C990C67DE901D9ULL, 0xB8B6DE493085FA52ULL, 0x813E2659110D3D66ULL, 0x7A3A54BEB8321459ULL, 
            0x87F5173ECFEFC7AAULL, 0x1B95A4AC7B0FF741ULL, 0x888F1F4879CA062AULL, 0x6D60883F96F657C5ULL, 
            0x83A5B2DB6014A06FULL, 0x01D4FF9D7BA2F257ULL, 0xE752CE864BD01AACULL, 0xA024BA9EC2C0E335ULL, 
            0x01C874838CCEC727ULL, 0x7CD3553BCFE7000EULL, 0x36BE35C870EE0D97ULL, 0x5CE6F46A70F68D4BULL, 
            0x61276DF87D9FE726ULL, 0x687DB05FB1CAFADCULL, 0x14B8E2CDB840FA97ULL, 0xFF69E93DAF6EC7AAULL, 
            0x77DB578FE639C5DFULL, 0xB60AAA8BDA968F32ULL, 0xD66BFE50A9D1A79CULL, 0xCBD71CF59F6ADB65ULL, 
            0x5FFEA208C7780456ULL, 0x22F6562F1F41F6D0ULL, 0x431659FAE389D199ULL, 0x360A96283A18A41FULL
        },
        {
            0xCD08516A119C939AULL, 0x38161ABAE4083CA8ULL, 0x8F9D749985F9C41EULL, 0xC0BB2F31075BFAF6ULL, 
            0x99B54E663CDDE8D6ULL, 0x5E343CCA8F818FC4ULL, 0xDBD11B734A2B3598ULL, 0x652E558BAD7FFD08ULL, 
            0xA8C003D64DC2A75CULL, 0x9FA872A3E81D5184ULL, 0x8E4C10494101A797ULL, 0x92CE156B02DA48AFULL, 
            0xC490E9D726215BBCULL, 0x3AC461569B8C4339ULL, 0xF73751027934489AULL, 0xA45A5BC2E3D035BEULL, 
            0xAD18280C2827DF85ULL, 0x76B792B938B6128EULL, 0x1505542D77E0A885ULL, 0x1A66F487999E5AF8ULL, 
            0x3A8063C81127B18CULL, 0x08C73F94A1F2340BULL, 0x13B27B78907BE97BULL, 0x7ED040E3DDD5D3BCULL, 
            0x7A684439E039F67DULL, 0x43A87E453A9AE246ULL, 0xA68C0AC5367C174FULL, 0x6CF4103233B0029BULL, 
            0xE4436ECCFFCD0DBAULL, 0x0C318BABE3E2F5E5ULL, 0xCBE39CBA2B5F1703ULL, 0xA4AEEEC9DA73CE43ULL
        },
        {
            0x9734C00484F54FE7ULL, 0xDDE05C239E84F9EDULL, 0x7DD830F06C6BD1A7ULL, 0xD9556B4AE7268A72ULL, 
            0xF7E63E346A97D60CULL, 0x7733D8CF28253BB2ULL, 0x7409C7338499FF59ULL, 0x1925E592BD1ADB5DULL, 
            0xF42661E477B5BBECULL, 0x7F8605E485D324F1ULL, 0x1575D2F1CDA31038ULL, 0x6057D2E5C484997EULL, 
            0xB1FC29750B245541ULL, 0x0B3E97F9D4B36D70ULL, 0x62F8C87E3DD26ECEULL, 0x84D5737CFE10B7ACULL, 
            0x25B7E46ED03B4295ULL, 0xB1598D45CF0C8A37ULL, 0xEE6EC355ADC72D09ULL, 0x0D16A43E971976B6ULL, 
            0x9ED58A6CE58F37FBULL, 0x3C7038C4C98A7914ULL, 0x2078AE18590B7454ULL, 0x18DCC98EBA4329C0ULL, 
            0x88F8D197FE2CA71FULL, 0xED88379855FF804CULL, 0x35CF69702A72CC03ULL, 0x63E8F1AEA84DECB3ULL, 
            0x42B5FCEF2CD7FE57ULL, 0xD7901AB817668D9DULL, 0xB996533143EE8C46ULL, 0x2A0AC0B4456F60A0ULL
        },
        {
            0xFFD642D9D0A8D776ULL, 0x0C03641017A0A796ULL, 0xCC8543C620A5B205ULL, 0xAB13CA7E1FCA62EAULL, 
            0x63A35D45240D6C59ULL, 0x399FD60CDA16E7A4ULL, 0x80EBE8474EB0FE7FULL, 0xC27D994E0144EA64ULL, 
            0x6D79661175185FE0ULL, 0x6F595436C9D7DB10ULL, 0xB8DF6483AD0331B6ULL, 0x23080630DCECA3F8ULL, 
            0xF31FA4BDA4D46A24ULL, 0x21BBCC05E1C9DD93ULL, 0x26558A9AE90BA708ULL, 0xADEC95A0610E34C4ULL, 
            0x7F5C8AA08D6A8DB8ULL, 0x4F7E579C1D156C5CULL, 0x9CA40F0E7D949908ULL, 0x7034C787AE5CE189ULL, 
            0x9CEC939945C7C519ULL, 0xFCF24A177096796DULL, 0x1F884CBF519AA26AULL, 0x623107C86E52A1EAULL, 
            0x4888595B13FD21C0ULL, 0xBB441DCBC0267E54ULL, 0xD91C7836A245F6CAULL, 0xDA6E084F9D48C238ULL, 
            0xB6EE4F605A0E2C15ULL, 0x6D242F6A7D8CF4BAULL, 0x81875ADB1872D30BULL, 0x771DB0C0292A9EADULL
        }
    },
    {
        {
            0x8C73C780793AA897ULL, 0x559692BCFF686E42ULL, 0x911EA88C728DBCE9ULL, 0xEBD58CF707D28B07ULL, 
            0x4ACE716DDFD5EED3ULL, 0x71E0DEDC37B56CA1ULL, 0xEA7A7884D9578D70ULL, 0xE706660DC167375AULL, 
            0xC02586B63FACD118ULL, 0xA38F8B097CD79E58ULL, 0x10D68C0E89F5190BULL, 0x59750B4BFDC98007ULL, 
            0x8CBDF744259B3BD9ULL, 0x50E05653E6B44A81ULL, 0x856AB0BED344C909ULL, 0x6C9DF2D18DAF3B22ULL, 
            0xAF23166A742DE5C8ULL, 0x1F9D01E542A36A7AULL, 0xB021F18FF8ABC3B0ULL, 0xB55935A37E9E46C5ULL, 
            0xEE11CDC1FE9E3BD0ULL, 0xE11E2E75A54F02BFULL, 0xB685A1A77762BF56ULL, 0x314CF6F1A5F2CEDEULL, 
            0xDA5CC6474FB2ADFFULL, 0x373AF8BCF3DFF73AULL, 0x23DB7396AE14405AULL, 0xD7AA6F6B31B85BC8ULL, 
            0x36FF001CA1E4F358ULL, 0x8EF2F0EDC1A03C0CULL, 0xDEF83C5CD03244DBULL, 0xB7662FE922ED3D6BULL
        },
        {
            0x7476B20603EB84ABULL, 0xEA04C90040E2AB95ULL, 0xB82820FA28369695ULL, 0xAEFBAA49E6B46157ULL, 
            0x15AB1D6474A7DEE7ULL, 0x2EE502713218E6EBULL, 0x23539E881639697FULL, 0x9447DBC267EDA428ULL, 
            0x4F99007934EF2403ULL, 0xE1FFBF3C39C63CBCULL, 0x4B475860BA2E0810ULL, 0x229AA2AC5C1C68E0ULL, 
            0xEC7C6D174A5D6C48ULL, 0xC6DC00A71C637442ULL, 0xEF0FDFB4DED097ADULL, 0x99E0467EDB1C639CULL, 
            0x405032A3229B344EULL, 0xD01FA4A94B28F4DAULL, 0x2A0EDE2A01691476ULL, 0x7C68500B17A706D9ULL, 
            0xAB46D21552E999BCULL, 0x1628FB76477F370EULL, 0x963C243A43784051ULL, 0x00B3F7A36C93E6F2ULL, 
            0xE736376D0D188D25ULL, 0xE61D027E859911CBULL, 0x5670572F3504B939ULL, 0x107FFD85E9F62913ULL, 
            0xC890C710E80C79B5ULL, 0xB99EFCC3183A5976ULL, 0xA2CBDE25D8073C2EULL, 0x06B6C6AB28F83CFDULL
        },
        {
            0x485E29A786908883ULL, 0x13A1F56CD974BF4EULL, 0x6BA18641F4A7864BULL, 0xCCDD1CA66C8D52F3ULL, 
            0xE6E34562698BF557ULL, 0x956C0594F054BD34ULL, 0xFCAA5283757CC269ULL, 0xB39C52B0DD963C5DULL, 
            0x89030093B4194CC1ULL, 0xFEA60B8F4A087A67ULL, 0x31A2109B88FE9835ULL, 0x94CA0D26C3460286ULL, 
            0x43FBD69F7D3FF0F1ULL, 0x6BA41FA0E39D2090ULL, 0xA1B2EE6E42A05BFBULL, 0x19678EB67058E13BULL, 
            0xBF046289980BFC5FULL, 0x5C2BA0667700BB08ULL, 0xE2D8E02D6607D31FULL, 0x31535BCC39FBD6B5ULL, 
            0x498C4E292C42CFE4ULL, 0x0EBBFD6D2542EA28ULL, 0xDDB43D9BBBD9B0AAULL, 0xCCDF2F6BC893F442ULL, 
            0xE0A31BFC39844F41ULL, 0x1FC02B78A7CFE131ULL, 0x25472B74D7AF4407ULL, 0xE915AC2FA601E186ULL, 
            0xD6BB2A298EBADCB6ULL, 0xCF8C6793E9B1DCDAULL, 0x84B0A8590ACA954DULL, 0x91CC168AF1CEA51EULL
        },
        {
            0x6F37FD6AE44D04D8ULL, 0x172BC258B043EFA4ULL, 0xEA0085BD22738BDAULL, 0x02E5204D362D94D6ULL, 
            0x89DABB35A3CF552AULL, 0xCDEE47FFE28007CBULL, 0xFAF016F695477A61ULL, 0xF37D0FF3947E3865ULL, 
            0x035EB2222CDE47EFULL, 0xA74AF364C4046936ULL, 0x1BA6A72AA03F9C34ULL, 0xE22C9DCBC0F5DD91ULL, 
            0x6B0FEFD6C566D8AFULL, 0x9582D4983575CCF1ULL, 0x3DD94542B33FB9A4ULL, 0x000147BB8406DBDAULL, 
            0x5DE2A8E94734D585ULL, 0x6535C38FCC30515DULL, 0xE27B2F31C757B4B6ULL, 0x26FA3B4040F73117ULL, 
            0x36A6F81F83104AE7ULL, 0x9C52E54D91B65A77ULL, 0xBB6B050BF2ECF757ULL, 0x2C955037B3450ECDULL, 
            0x23CCD1128F972C27ULL, 0x07CA2F1152FE9F6FULL, 0x80D6E57CEF760C4AULL, 0x21B3613A19357CBBULL, 
            0x94C6BC58103A1E47ULL, 0x4C30CFFB2E3D18DDULL, 0x2BB91643411D2F22ULL, 0x7FA6F766AFE7B26FULL
        },
        {
            0xC1EE07383AB294DAULL, 0x65C2F88470D9DE65ULL, 0xC589B35CFA8C4B12ULL, 0xF07F4027E0BFF01FULL, 
            0x58A7D2214567D7B0ULL, 0x9BF421D994461277ULL, 0x782722989C646BA2ULL, 0x4F22E066A731A434ULL, 
            0x12F5F03A3AA5B79FULL, 0xFF01EFC889020DC6ULL, 0x8CD15E595574BB19ULL, 0x0058F2A9646BC915ULL, 
            0x72BCEA52F46CBD6FULL, 0x821A4E13A6A9C33DULL, 0xB425AD61B8890EA4ULL, 0x43CA855E4EFE1773ULL, 
            0xF9CC07F3ECC8DE7DULL, 0x294440727F0D59BAULL, 0x4D5B8139D7B53104ULL, 0x1DB019C91EABFFAFULL, 
            0x1CEEB84E62213117ULL, 0x73FFBDBEAC0FA1BBULL, 0x03D062550F15F5D6ULL, 0x76AFC9A8A1CBABB9ULL, 
            0x99EC5D64852766C9ULL, 0x64B2277FA5DCAB15ULL, 0x5529EA89B6222A5AULL, 0x3E4D6BA30C011BCCULL, 
            0x7A1CFC1ABED9C965ULL, 0x81501FF214651CF9ULL, 0xB0BAA2D836EC2696ULL, 0x6B617E0393301669ULL
        },
        {
            0xA51427707A31D957ULL, 0x295793F6E288780CULL, 0x3E2AEF6AC57F55C7ULL, 0x55DAF691CFBA1B91ULL, 
            0xD9196A0BAB91A4C3ULL, 0x2DEFF0D7960C799EULL, 0xF9B7C39B3BC728E8ULL, 0xD1CCEB3A061673E4ULL, 
            0xEF0D8282985C72ACULL, 0x6B9BA39B19ECDA71ULL, 0xC0EA2A5636B293F1ULL, 0x4CF4A957525EC675ULL, 
            0x79167A629CA25A77ULL, 0x5FC631022E91A220ULL, 0x990D491B81DB61FDULL, 0x923E3A78B3D2E540ULL, 
            0x3573C3DB17C271E1ULL, 0x45A1D117B2ECBC8EULL, 0xB80F1682EDE6DAA0ULL, 0x83B33CF3E58B20F7ULL, 
            0x2A703F41A76F2FA3ULL, 0x0DC17A585602017AULL, 0x91090EB3E602467BULL, 0xC1E14BDF013F1027ULL, 
            0x670636126E4CC0C1ULL, 0x23FAAF3DD481A992ULL, 0x573A93EDDA1890F0ULL, 0xBEE78D887A2DBD8BULL, 
            0xCACB07935911A538ULL, 0xB373825152758F26ULL, 0xF89FE6F396DCF8D5ULL, 0x673DAF3F6346719BULL
        }
    }
};

const TwistDomainConstants TwistExpander_Pollux::kPhaseGConstants = {
    0xFEB3B89211483FC8ULL,
    0xA9C7F26DB5AA7F1AULL,
    0xAC859EFBE5711255ULL,
    0xFEB3B89211483FC8ULL,
    0xA9C7F26DB5AA7F1AULL,
    0xAC859EFBE5711255ULL,
    0xF83C55A53886A09AULL,
    0xCD64F4F44276DB27ULL,
    0x66,
    0x8E,
    0x40,
    0x38,
    0xBC,
    0xDB,
    0x35,
    0xE3
};

const TwistDomainSaltSet TwistExpander_Pollux::kPhaseHSalts = {
    {
        {
            0xF1BE5C7442BE052FULL, 0x86FC93ABC12CC6CFULL, 0x08FF1BB5A0C4613DULL, 0xC3A238F426662777ULL, 
            0xCFABC5459EC63CEDULL, 0x110A11659BF1788FULL, 0x89E7744A0B07EC4CULL, 0x80F4810AE76AC6BEULL, 
            0xADECFE32F070D795ULL, 0x3C6A05A326B49EEFULL, 0xCA6332A44BDFEC9EULL, 0x4E09B99DAA5C5B0FULL, 
            0x7BEB0CECB4B5DA10ULL, 0xDAD9F55FB5B83339ULL, 0xA7539503CF15A516ULL, 0x7441B1CDFAF0C66FULL, 
            0x599D6B2FD2FF15DEULL, 0x567A82C957F4832BULL, 0x7F3559949F7B4089ULL, 0x1B4322805B53F6D1ULL, 
            0x979CFFC9177421A1ULL, 0xCBF252369757EBB7ULL, 0xCD24E8F04DE05B6BULL, 0x5FD272E467BEE97CULL, 
            0x445820CBBD35788BULL, 0x2810C3755911222BULL, 0xAD4EEAB326406ADCULL, 0x4DFEDAEC8F2AE9A7ULL, 
            0x8EFC2AEE2B9C778FULL, 0xFF7BF106D43EF71CULL, 0xD851E7CC7FCACB6CULL, 0x4A8C7F822EBDF85FULL
        },
        {
            0xB70FA1CA2648D8E5ULL, 0x35DE6D7FF2FFFE93ULL, 0x1040867E205AB080ULL, 0xD5D9A4089FE10C3CULL, 
            0x1A7C3ED1B3BDB076ULL, 0x6987DFD12EF29B49ULL, 0x70DF2FC68D9F4030ULL, 0x582F649277080F09ULL, 
            0x3324B9E442FBC8AEULL, 0x902FFCD223D99A27ULL, 0x9ED0025A1DEA32F3ULL, 0xC7C269E781699765ULL, 
            0x456292DA13E69A98ULL, 0xA1B5D0FF48EE07AAULL, 0x6DC8ED1859C79CE5ULL, 0x7E4F09E486D9CA78ULL, 
            0x4DA1BEA2FD226AC8ULL, 0x589567744BD91E4FULL, 0x194BBF8B40D592C9ULL, 0xFDC058013A2F3913ULL, 
            0xC0E4218B96055543ULL, 0xFEC3DACBB251B95EULL, 0xECFF638CCA38D92DULL, 0xFCBD0C18882A59B5ULL, 
            0x7384D1724BC8A83CULL, 0xCD011E283CC3369AULL, 0xCB4B0DB1BBD45D03ULL, 0x4B16509F29F43CC8ULL, 
            0x04651A3838DCD2E7ULL, 0xB16D3C27F89947BEULL, 0x91578CA7B6BE44E4ULL, 0x4345577FB64ACC71ULL
        },
        {
            0x4706DCB92DEC8025ULL, 0x4F2F239377C67DB2ULL, 0xFDC868A709650903ULL, 0xA1D8366ACC73E5B4ULL, 
            0x28B59CDA78554308ULL, 0xEFB0BEA7211D5E96ULL, 0xBFA32628F72BED54ULL, 0xCF4A7E779F8FDCD2ULL, 
            0x507CD428BFB0A0F8ULL, 0x5421F84F07CDADDDULL, 0x31E252BCED31AAE2ULL, 0xC5C8831726DB76E0ULL, 
            0xCA866231B6E3C5A7ULL, 0x7D8C9FCC83BC73ECULL, 0x6B3FA6CB6A523178ULL, 0x97CB55431F982467ULL, 
            0xB088F3A3DF2936EAULL, 0x23718445C96970BAULL, 0x73CB8A7A2376E8A1ULL, 0x66F38446010940A7ULL, 
            0xF74976E1C4E43192ULL, 0x710E565E844F93A0ULL, 0x250FEF86C57BC417ULL, 0xF74C352E8CAF00F6ULL, 
            0x212FEEFDE2F85EA3ULL, 0xB30C216E7B140D48ULL, 0xA2C3255AE1C01A90ULL, 0x64905C28E1DF098CULL, 
            0xF350CE00BCAE27D0ULL, 0x1F04C213894841F9ULL, 0x6A20FB6BFC482827ULL, 0x1E8930437ACAB5CEULL
        },
        {
            0x6E8B7AF09F8E1B80ULL, 0xE879F4304FCBE210ULL, 0x5D0109DC7493B5DEULL, 0x693FFE834341CF9BULL, 
            0xD9F50C64B82EE536ULL, 0x40F1B64413ED2EF0ULL, 0xCDB0CE9437D06BEBULL, 0x3316B47A2D139F9DULL, 
            0xE7474A7B3B67B96EULL, 0xE6FD6263D8544E25ULL, 0x58D095B89A5F14F5ULL, 0x5B706DEE19CF9138ULL, 
            0xF6981D4F0714844CULL, 0x4C179761E3B0534BULL, 0x25C230B9E9ABB235ULL, 0xD2DD5AF66B8C9173ULL, 
            0xA827EE2F9E7E0551ULL, 0xFAAF3265C6365B78ULL, 0x68D789A7D9495513ULL, 0x16177A7D5ADA66E9ULL, 
            0x37793F2204EC5F54ULL, 0xAAB704D01E20F54AULL, 0x3C7F928D1190C215ULL, 0x221038CF0449F808ULL, 
            0xB0FEBBF99DD0C21BULL, 0x6CA0ACF5A7C30E98ULL, 0x7AEB11F73614B6FEULL, 0xF47819C857B4D61CULL, 
            0xFDE3BDEA174A09C5ULL, 0xB6440D6ABB998A0EULL, 0xDE8C7D44178F85D8ULL, 0x7FDDBA308BD015F8ULL
        },
        {
            0x2173BC0017487C65ULL, 0x8C19726E685F67D1ULL, 0x96FD225D94ECF3A0ULL, 0xF8B35459B16F95E7ULL, 
            0x3AFE980A92BAF6E5ULL, 0xC45D39598F6D6297ULL, 0xA98A3AF155F90175ULL, 0x6BCCC68A171923CCULL, 
            0x74DD5356C9B05FB6ULL, 0xEE7101FDC0EBA1D9ULL, 0xD5BC6EEB181FDD9CULL, 0x408B68D195A8CA95ULL, 
            0xCDB1D10B6CA9124DULL, 0xAFE5E4FDB6984A2EULL, 0x6F4830BAB456E91FULL, 0xC87B1DD935B7B018ULL, 
            0x42CE96BA88D68589ULL, 0x13CBA4FFA1F8E9CCULL, 0x8091AF3FCDC34591ULL, 0xBF3363247817C937ULL, 
            0xD0C38B08E9F2CB0EULL, 0x9C679528A6DDA173ULL, 0x11887233FC180ABCULL, 0x7C1110A71869A278ULL, 
            0x1590353AD20BB211ULL, 0x610B9304B281873FULL, 0x33613D3C4FEEB515ULL, 0xB4869B64CDA3889AULL, 
            0xEC2CB06364DF45C9ULL, 0x5E12BDB824BF6971ULL, 0x5A24C361D5913DB3ULL, 0x5BF4E795515939D1ULL
        },
        {
            0xF60CCFCF22E59665ULL, 0xF03CE63EA09DCE47ULL, 0x8F034AC06D549CD0ULL, 0xAD5209083E1D25FBULL, 
            0x4FF952C9E6E0DB50ULL, 0xB20D3A2B5D534D32ULL, 0xC3CFC38A8B663922ULL, 0xDAC800CA7887324FULL, 
            0xAE51808B048A188BULL, 0xA8A9D4B75DE7CF92ULL, 0x4017820F8C87BDD6ULL, 0xDF77E3AE1637FE39ULL, 
            0x05E3DF9AD8C2CE41ULL, 0x27E04E6AF9E4D8B6ULL, 0x87C581E04937B590ULL, 0x7E3F5A2CEC41D6CBULL, 
            0xBE0598F5CEB28AC3ULL, 0x0560673DD5BAE376ULL, 0xA1040AA8EE8193A1ULL, 0x8F136A43AB2F4ED4ULL, 
            0xFBF8788A4A8D6A58ULL, 0x472DB99020DAE9ACULL, 0xAD7904BD186DB779ULL, 0x2693D814084AD868ULL, 
            0x177E7297E5BE931DULL, 0xDFEA68319DA99659ULL, 0x358FF5D3C45BCF6EULL, 0x62B1220D141504BCULL, 
            0xE2A374EDA1314912ULL, 0xB126A30DCB94F340ULL, 0xFA28463C81F81878ULL, 0x8F309AB11D412BCDULL
        }
    },
    {
        {
            0x2B66BB99FCDF5094ULL, 0x2B573408402FCB65ULL, 0xB60165C8ED154C23ULL, 0x65A253F4DF99D227ULL, 
            0x20C4B07CE98601D8ULL, 0xECFAA72E5BCB091DULL, 0xCF84E946D064D15BULL, 0x62B8A13FF3AEAF4AULL, 
            0xA188E06BF4CEF97FULL, 0xD4CE692947CE6A20ULL, 0x0D43553ACCE9F057ULL, 0x332CEED2244D0BACULL, 
            0xC4B0FF483F9E51F9ULL, 0x268FF23E12CCD50FULL, 0xB93B46906D48AC92ULL, 0x9EF40467B3A27866ULL, 
            0xD135710B4166459DULL, 0x668CA73584F13D4CULL, 0xB01C72D677CE8AF1ULL, 0xF848366DF86DAC26ULL, 
            0x9C7EDAA02D9704E5ULL, 0xD32F3D6E9BC62A98ULL, 0xCC73E6494EF1C7CFULL, 0xC26E23AE647E661BULL, 
            0xEFB19CB671302F8AULL, 0x70064E073BADBD58ULL, 0x5C497A59E94F81FCULL, 0xE7F95E7FE0613212ULL, 
            0x5E7C81D16BB1AF91ULL, 0xF829C2A57E4D2147ULL, 0x9A5AA3E6C5AA7DA9ULL, 0x91E6E3942552C4A8ULL
        },
        {
            0x83CBF819625AA7F3ULL, 0x5F5423FA7A377384ULL, 0x91B8A2BD88CC4B14ULL, 0x3838975E8A699DF7ULL, 
            0x7F19ADD4CB1B9517ULL, 0xB18AFB84A1B876F0ULL, 0xF5998DAD4F5E5313ULL, 0x42A9E8FF07A3A360ULL, 
            0xBC014A710CA664E6ULL, 0x47D0E8A8119A5703ULL, 0x13B5E289F7FF8113ULL, 0x736CFE5A61DEB039ULL, 
            0x0C11E05BC8F0A9D6ULL, 0xACE70771F17A706DULL, 0xB238F1543AEF050BULL, 0x39E02027212B426DULL, 
            0x5299E3A9AE874713ULL, 0xEDE5EA912ADE6078ULL, 0xAAD78A5432A64472ULL, 0x4894C4EBB0B752B7ULL, 
            0x4BA352C823B6D3C3ULL, 0x8EEB848DB8E86748ULL, 0x168D42488F1B7691ULL, 0x991EB6675673DE24ULL, 
            0x713806F4EF09D2AEULL, 0xE06C97D861A30992ULL, 0x5D5A40499FB05AB2ULL, 0x20B4155622062615ULL, 
            0xD4D2EAA6F52602E0ULL, 0x03D93E74F6D04087ULL, 0xBCA0B2207286E4BEULL, 0xDD0E96FCB6421337ULL
        },
        {
            0x9541C81698CCBEEDULL, 0xFD5B03DC4D8ADF67ULL, 0x941E0E71C4F36CEEULL, 0xA352D1E178488914ULL, 
            0xBA8FB1A7596FB64AULL, 0x1B748A168271EB36ULL, 0xA4499D3BFDAC8928ULL, 0x2135F0D74F3DC9F1ULL, 
            0x893FB569C85013B7ULL, 0xC87F674B5375653CULL, 0xE7748E11128D17E0ULL, 0xFE8CE564F09BFF5EULL, 
            0xB8F86D2D95E69291ULL, 0xEAB587CF14CCADEAULL, 0x5EEC0F5125C65F15ULL, 0x7113BFE6604221CAULL, 
            0x8EC65276141F50F4ULL, 0x1C8C3ABA53263496ULL, 0xA278A679DEFDE16CULL, 0x68FCF4EB13A5B707ULL, 
            0xF53DDFCF3D59E8A6ULL, 0x2AE63A46865AD267ULL, 0x41FEE752723F2B80ULL, 0xD32E5073E746BCDEULL, 
            0xBE75549A1E39C41FULL, 0x2FB33387876F13B1ULL, 0xC2AE791B27F1839EULL, 0xB5BA0EDE894F8025ULL, 
            0xEB06B4FCA18BB6B0ULL, 0xAE252A776B34E6D7ULL, 0xCE2CF1C21016B1CAULL, 0x3C035632FBD1BE0EULL
        },
        {
            0xA550FF25D0932A04ULL, 0xD81626E4805AF4C2ULL, 0x3079BCE814C7AE1BULL, 0x4D076F04D6C91EE2ULL, 
            0x68EB7FA9CAE411FEULL, 0xE85FEFC060B8BF6FULL, 0x447473FF23E80E8FULL, 0x6D1ECF9F5C03FC1AULL, 
            0xF2431C4040516692ULL, 0xE83A0B9F4D0CD132ULL, 0x00972B1E2156E018ULL, 0x2E46F0D706D7F8E2ULL, 
            0xD508082D17F81A44ULL, 0x34DB921D7B126F45ULL, 0xCFB68328C5611BB9ULL, 0x6464E71C9E63EA18ULL, 
            0x134110A332E93E95ULL, 0xDCD4AF43A44BFB4BULL, 0xD0307D54CDBEE45AULL, 0xF0A6580540442828ULL, 
            0x1225BBC6529D51DCULL, 0xCB7DA9DE87190C49ULL, 0xB897604897BE337AULL, 0x2827E2B6230CE74AULL, 
            0x6ED0E5BCD78FDD77ULL, 0x3962823F54CF6C10ULL, 0x60E189664A2C4549ULL, 0x5ED84F069995A72DULL, 
            0x7428906D909616FBULL, 0xB39AADCDB5E222B3ULL, 0x28E3A8404163B5FEULL, 0x6F4CEE92E2A2CECDULL
        },
        {
            0x46118FD9A0985C1FULL, 0xE859B93820AC8941ULL, 0x2AB4603461E1AD9BULL, 0x46A9BC8E6D17217AULL, 
            0x6966FFC5D8538483ULL, 0x18D627DB48ED9A39ULL, 0x72E61508FF3AE758ULL, 0x7F766E51F80AAC6AULL, 
            0x52A47808F87213C6ULL, 0x0F4D9EF1C6ADCF77ULL, 0x5FDC5EC9EAEEE1CBULL, 0x4CC68D772325CEAAULL, 
            0x7BA86FE2C90DE3BCULL, 0x67C2EAE5C9EC13C8ULL, 0x88147EECFD14223FULL, 0x21EF61B31828B9F4ULL, 
            0xEED9FB5D7E59A65DULL, 0x1B9014ADD218F4BCULL, 0x4463F49062ACA789ULL, 0x3EF620ECBA3204CFULL, 
            0x86F22F0129FBBA55ULL, 0xDBD2B6A592550C5EULL, 0xE691E012F8C879E3ULL, 0x8FE25F19BB09FDA7ULL, 
            0x5CFDB5AC20CEE2B6ULL, 0x24834C5462C7242BULL, 0x8933D668AB4E4C28ULL, 0xCBF0F5734338BE27ULL, 
            0x5F1F140549D8DFACULL, 0xCB091B27AE2CDF06ULL, 0x37C019EF0CFA21E3ULL, 0xF1008650E0C71936ULL
        },
        {
            0x14B7D6C5FEF77C41ULL, 0x5B5CABB8BBC72AB8ULL, 0x37D437BB63823811ULL, 0x86062E4E047C8325ULL, 
            0x914ADD98BB8E8104ULL, 0xF08CF46A86899904ULL, 0x4880734866226EEDULL, 0x1026140DF7F986C4ULL, 
            0x12B4A9FB510BB14DULL, 0x950810407B3A1115ULL, 0x0886AC5CC4D30369ULL, 0xD009BA37B688D38BULL, 
            0x4323814E3A8FDBEDULL, 0xC9DDDAFBAE69F99DULL, 0xC39DE5891C01ECFEULL, 0x0835B145EBE7C58CULL, 
            0xB6A2994DB20C03A2ULL, 0x4668FD2634C6CE29ULL, 0x01B381B3435B005AULL, 0xD79E55C2485D01E4ULL, 
            0xDE35F72D5ED2E799ULL, 0x14167243DF086AEEULL, 0x315F1412D9368375ULL, 0xEBE944D8F959C105ULL, 
            0x5D59D2A6EB9587D5ULL, 0xAC23C7C0F1924DD1ULL, 0xBD93C5241CB55D74ULL, 0xFC5AE506D9907246ULL, 
            0x7DEC925992E72EA0ULL, 0x771297957CC06C3EULL, 0x569DBC32605E929AULL, 0x2AE387E90EC9EECAULL
        }
    },
    {
        {
            0xDAD23D67E5D5EB8BULL, 0xAE3ECC31809FF9A3ULL, 0xA7DF1527FB972B2BULL, 0xC5F77A30C7E13E02ULL, 
            0x153F96793D03789BULL, 0xB89CF2DA00AE2A60ULL, 0x81FD29FCBF819757ULL, 0x50CA7355D9620A93ULL, 
            0x24AE5C4C7F904A8AULL, 0xD1B6D0DC1E67B7D3ULL, 0xB1A44FA0BF18F30DULL, 0x0402532326934938ULL, 
            0xF75FF170703301B6ULL, 0x009DDD88BD245161ULL, 0x0B0E712A26B6A5BFULL, 0x09F0342ED3C38C0AULL, 
            0xBC43270E7F2A5E42ULL, 0x0B1B063F501D8BC6ULL, 0x1C77C6B3B2A9689CULL, 0x3FA1E46E0781A338ULL, 
            0xCBB85C6083C69680ULL, 0x6604CE3BF44D4A8CULL, 0xE581A063E186C8DBULL, 0xB9B04DBAA313E49DULL, 
            0xE0FADAB589460C66ULL, 0xECBF541C6BC59430ULL, 0xB5A8B8A090C4CE38ULL, 0x6097DEC31C8BEFC6ULL, 
            0x2BED066C232CF891ULL, 0xA3F79E9BB4056948ULL, 0x53995936FC8CFC41ULL, 0x5DB3F639086919AAULL
        },
        {
            0xDDAA350A838B638FULL, 0xA7EE6CEEF0939D40ULL, 0x89D2546E00659FF9ULL, 0x3F573BC12EE1E244ULL, 
            0x9949CAF473D5E1AEULL, 0xA0C54C20BBB5D3C1ULL, 0x9B1579E5FD046A98ULL, 0xB0679F89FB1A6F11ULL, 
            0x9A6B9F61D9B0173FULL, 0x6521124F579F0119ULL, 0xB1BAEB2A6830ADA9ULL, 0xF48548ABD3F373B8ULL, 
            0xCADD79DC4A1D7EF6ULL, 0xF54263DE1C5C3022ULL, 0xC2170F32A0D011DAULL, 0xE9B1DA68BC0FE3E3ULL, 
            0xC05C1C577FBE7C2AULL, 0xEB9CE7513101C3ABULL, 0x724F03C37BA338E8ULL, 0x21E6DDAE1492A1C8ULL, 
            0x6902E4DD35DE743CULL, 0x08F49D575A06F8E5ULL, 0x9AFCF3FD6A9DB610ULL, 0x92291087F53E8859ULL, 
            0xADD7314800CC431EULL, 0xA602F9ADF11B5F41ULL, 0x42B0355EACE0CFB8ULL, 0x39FB33E924390770ULL, 
            0x34FEDDD9A6ABF15EULL, 0xF54148D54EEB61B5ULL, 0x7032D5161230FDEBULL, 0xB654C33CB867D0ECULL
        },
        {
            0xAA33CFD944D202E1ULL, 0x6A38B6602E4E6B52ULL, 0xAFA22DCB65C0547FULL, 0xDE5E9C940165D8F2ULL, 
            0x8401C7DEC603BD00ULL, 0x4EEA51C824A071FBULL, 0x4440132B3D1479FDULL, 0xE0D70F2D133CFC3FULL, 
            0x11AA1E0A40043EF2ULL, 0x95EF215B78984CDEULL, 0x234B5DF414136809ULL, 0xC98DB6A47C54F156ULL, 
            0x92D5ECB268C1E244ULL, 0x0BDFE60CAED27EBFULL, 0xA75501B91B686A69ULL, 0x69729A90D76C9042ULL, 
            0xD0A4C97042A2EF0EULL, 0x3ADE0AF335A86EB6ULL, 0x2A52D61C0D1B1DECULL, 0x3109357D6B891CAAULL, 
            0x9DF1130359084950ULL, 0x315112465C5717FBULL, 0x45DCECEDF358EBE7ULL, 0xEBABC8A11D168A85ULL, 
            0x870CBF5CE5C33D00ULL, 0x1A8DE954DC7B76ECULL, 0x96499521948F9999ULL, 0x5C54AE393E083305ULL, 
            0x52E4F2E9C911DFAEULL, 0xE7E1690A8A566538ULL, 0x5394FC56E4BA0811ULL, 0x040DC82E13B8C998ULL
        },
        {
            0xE82309963A39CFC9ULL, 0x6A514666D842524DULL, 0x060618CCBC366C63ULL, 0x5EEE75799A52276AULL, 
            0xE3C7E7B722CFC734ULL, 0x37886EA39C4C1957ULL, 0xA03868F3654AF08DULL, 0xB38D04A364A3866BULL, 
            0x141B9DBE3DC5737CULL, 0x96C47D54BB12F224ULL, 0x801820F2FDEAB5BFULL, 0xDAF4DDBCE8650B82ULL, 
            0x74576370B1414AC7ULL, 0x04F5FA745F208C1AULL, 0xD8CF72EB196D5C9BULL, 0xE91907754A6891D6ULL, 
            0x7DD74737A309D428ULL, 0x2F565E737D248DEBULL, 0xFE16F678F54693D5ULL, 0x7D700A9F03E0C190ULL, 
            0xFF8926C7D3B7C1F3ULL, 0xE27E7CCF8823CC7CULL, 0x7DC3FCFDA1D755B3ULL, 0x9989A36B44AA6F84ULL, 
            0x5A9BDD5380CDC928ULL, 0xE063D714964D0049ULL, 0xECC882F0E06BC378ULL, 0x6613E69425AEE524ULL, 
            0x4AE73826D2E9CC2FULL, 0x2C0CE2BE4B22237AULL, 0x218923CCFDF8FCF5ULL, 0x9B2611D379B71899ULL
        },
        {
            0x82A637BA44830491ULL, 0xFE41C1B04932DE94ULL, 0xD861A07CC16F8843ULL, 0x8EB95827A76710E8ULL, 
            0x1304D9A5EFE829B2ULL, 0x3808D04225FC560DULL, 0xA09D195C025125C3ULL, 0x4C21FA5FF79D7815ULL, 
            0x0B70734C77BE6843ULL, 0x530CFB3D1A8479B3ULL, 0x8110B49D3BF6141FULL, 0xA5566AD5138115ADULL, 
            0xE8BF960B85EBB954ULL, 0xDC8E4CE077937FA3ULL, 0x170B8A63E5142139ULL, 0xADD1F2909FDBC805ULL, 
            0x115CC518957E89CAULL, 0xFE2D8AAAC38E7235ULL, 0xBCDAAC0E6B4CA13EULL, 0x5BCD55BF0189FDFBULL, 
            0xD36DC9A19A141E7AULL, 0xDC7E9421E9722155ULL, 0x02372242FF5B477EULL, 0x750B16D020C4841CULL, 
            0x12721E1DF5215AB8ULL, 0x420BDBAC2D1E42F4ULL, 0x2F45A04BD6D6DBD6ULL, 0x380FBE654765F293ULL, 
            0xA3798CE060FC435BULL, 0x0A9AF528343B57D7ULL, 0xF64EEB2BFA46AF98ULL, 0xBE5C5A90ABBF92ADULL
        },
        {
            0x7A03528BC4EFE712ULL, 0x7D05EEE3372519BAULL, 0x892EB0E503C0632CULL, 0x6188C93840E2E88EULL, 
            0x518D0DF6F0ADE191ULL, 0x6AFCB75697FC66D8ULL, 0x2C12425D61466880ULL, 0xE270A3F992BAA88FULL, 
            0x27CA77ECFB21FC6DULL, 0xA1E50E94305FB503ULL, 0xF2FFEFE9C7DDC58DULL, 0xC519204F7D9A5382ULL, 
            0x9FFE768472CDF2D0ULL, 0x328336CE0D1504F1ULL, 0x97D5749A54D63748ULL, 0x3FBEE57DE791C0C3ULL, 
            0x22E8DFB5FD706658ULL, 0x6D75F558C6851B05ULL, 0x4ADB9DF4FAC4A913ULL, 0xF2C3DDCA25E1524BULL, 
            0xCB21B66D6B56AA6EULL, 0x73B622016B46E4B2ULL, 0x0D6712C59A944CADULL, 0x3597F65CE1D5FF22ULL, 
            0x3515566099AE9D14ULL, 0xBEFD6A0A4E75B93AULL, 0xC7E6AAB2E45B0DCDULL, 0xD23785D6A16FD6ADULL, 
            0xB2D7FF0F8E871071ULL, 0xB8772504F20765A0ULL, 0xB7E2E528E4C3DE2AULL, 0x39D93FC56EB70CD7ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Pollux::kPhaseHConstants = {
    0x5B11F10964A748EDULL,
    0xD8AC02C43D3D315AULL,
    0xF3538385D057AB53ULL,
    0x5B11F10964A748EDULL,
    0xD8AC02C43D3D315AULL,
    0xF3538385D057AB53ULL,
    0x04B3A20D6718265EULL,
    0xD224D1EEC2112D38ULL,
    0xC1,
    0xDB,
    0x29,
    0x41,
    0x98,
    0xC5,
    0x83,
    0x33
};

