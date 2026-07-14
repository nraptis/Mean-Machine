#include "TwistExpander_Mothallah.hpp"
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

TwistExpander_Mothallah::TwistExpander_Mothallah()
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

void TwistExpander_Mothallah::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xFD1FC48B55367CA5ULL; std::uint64_t aIngress = 0xFE31D1B96FA088EEULL; std::uint64_t aCarry = 0x94518812D6DB0C61ULL;

    std::uint64_t aWandererA = 0xC2E6D6523971E628ULL; std::uint64_t aWandererB = 0x9B325169565A203AULL; std::uint64_t aWandererC = 0xBCACD93417630AEEULL; std::uint64_t aWandererD = 0xDC1B00930BAC635CULL;
    std::uint64_t aWandererE = 0x96F223BBB89E6D50ULL; std::uint64_t aWandererF = 0xD9D254648E80C585ULL; std::uint64_t aWandererG = 0xA2C630344002C28FULL; std::uint64_t aWandererH = 0xF522A6945775CF6AULL;
    std::uint64_t aWandererI = 0x9F0E7E6DB49E97F2ULL; std::uint64_t aWandererJ = 0xB649B6F23027EBFFULL; std::uint64_t aWandererK = 0xDBB74048C70C5A36ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 14599468172233763194U;
        aCarry = 13623233201400468319U;
        aWandererA = 13925143284033659452U;
        aWandererB = 13488851261855525363U;
        aWandererC = 14785067986106258402U;
        aWandererD = 16011503194861425072U;
        aWandererE = 10918577402568627269U;
        aWandererF = 9378570816370259649U;
        aWandererG = 16347032384721843256U;
        aWandererH = 14313115991362702406U;
        aWandererI = 11608106444388803183U;
        aWandererJ = 10847126830349250952U;
        aWandererK = 9666498289885570859U;
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
    TwistExpander_Mothallah_Arx::KDF_A_A(pWorkSpace,
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
    TwistExpander_Mothallah_Arx::KDF_A_B(pWorkSpace,
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
    TwistExpander_Mothallah_Arx::KDF_A_C(pWorkSpace,
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
    TwistExpander_Mothallah_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Mothallah_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Mothallah::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0x80721A257A893591ULL; std::uint64_t aIngress = 0xF13176C9BC18FF2BULL; std::uint64_t aCarry = 0xCC963F232C52D38AULL;

    std::uint64_t aWandererA = 0xDB4A9AEEC31988B7ULL; std::uint64_t aWandererB = 0xD3FCD55934745C8AULL; std::uint64_t aWandererC = 0xCEB6FD82EA561B3AULL; std::uint64_t aWandererD = 0x8B9E359B10E43F59ULL;
    std::uint64_t aWandererE = 0x8401BC9A7F4F11D5ULL; std::uint64_t aWandererF = 0xA526DA0367059936ULL; std::uint64_t aWandererG = 0xE34FC1343B898972ULL; std::uint64_t aWandererH = 0xB4B2B7E02BABA6B1ULL;
    std::uint64_t aWandererI = 0xB5B38E01377FD6CDULL; std::uint64_t aWandererJ = 0xF8781DD8BB92C3D0ULL; std::uint64_t aWandererK = 0xCF6240012629C3DDULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 16053077349896609927U;
        aCarry = 13579475910805802355U;
        aWandererA = 11223871711280418952U;
        aWandererB = 15028490143310513316U;
        aWandererC = 13070738494197148985U;
        aWandererD = 12247713994957103944U;
        aWandererE = 16710323609613042776U;
        aWandererF = 16734946635279933118U;
        aWandererG = 10628793993126489664U;
        aWandererH = 17289650701571303481U;
        aWandererI = 12490503643699697266U;
        aWandererJ = 17832016355202469284U;
        aWandererK = 9745271252015239414U;
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
    TwistExpander_Mothallah_Arx::KDF_B_A(pWorkSpace,
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
    TwistExpander_Mothallah_Arx::KDF_B_B(pWorkSpace,
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
    TwistExpander_Mothallah_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Mothallah_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Mothallah::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xBAF55674A2FB32E5ULL;
    std::uint64_t aIngress = 0xC56DC9C8AC0C3898ULL;
    std::uint64_t aCarry = 0x87C3BD087FB69D50ULL;

    std::uint64_t aWandererA = 0xD5F44E77EFB5E474ULL;
    std::uint64_t aWandererB = 0xD102F8E761FEE615ULL;
    std::uint64_t aWandererC = 0xE78D73ADBE723FC2ULL;
    std::uint64_t aWandererD = 0xBCE75559EC0FA9F4ULL;
    std::uint64_t aWandererE = 0xA7A82D7BADE43AD3ULL;
    std::uint64_t aWandererF = 0x89ECD6AF3F60A794ULL;
    std::uint64_t aWandererG = 0xFE21D13A98F95D4FULL;
    std::uint64_t aWandererH = 0x893FE37A046871DEULL;
    std::uint64_t aWandererI = 0x90EBB933347A7174ULL;
    std::uint64_t aWandererJ = 0xBFB8C48862FE05B0ULL;
    std::uint64_t aWandererK = 0x98E18A6D4A7D1C30ULL;

    // [seed]
        TwistSnow::AES256Counter(aSource, aSnowLaneA);
        TwistSnow::Sha256Counter(aSource, aSnowLaneB);
        TwistSnow::Aria256Counter(aSource, aSnowLaneC);
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneD);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneG);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneH);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneF);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneD);
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
    TwistExpander_Mothallah_Arx::Seed_A(pWorkSpace,
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
    TwistExpander_Mothallah_Arx::Seed_B(pWorkSpace,
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
    TwistExpander_Mothallah_Arx::Seed_C(pWorkSpace,
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
    TwistExpander_Mothallah_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Mothallah_Arx::Seed_E(pWorkSpace,
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
    TwistExpander_Mothallah_Arx::Seed_F(pWorkSpace,
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
    TwistExpander_Mothallah_Arx::Seed_G(pWorkSpace,
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
    TwistExpander_Mothallah_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Mothallah_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Mothallah_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Mothallah_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 22 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1794 / 1984 (90.42%)
// Total distance from earlier candidates: 38044
void TwistExpander_Mothallah::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 2032U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 225U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 573U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 208U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 478U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1495U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 616U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 664U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 583U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 653U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 41U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 350U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 207U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1965U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 79U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 2030U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1268U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 160U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 899U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1987U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 994U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1314U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 156U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 326U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1033U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1137U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1265U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1005U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1139U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 908U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 937U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 909U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1722U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 979U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 590U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1109U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 955U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 2019U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1234U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1607U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 2U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 736U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 738U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1177U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 309U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 406U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1977U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 840U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 227U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 447U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1145U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1409U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 451U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1996U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 476U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 536U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 284U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 659U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1704U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 674U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 556U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1312U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1343U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1432U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1857U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1473U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 574U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 22U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1734U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1854U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 388U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1418U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1388U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1342U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 231U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 468U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1340U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 644U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1890U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1043U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1789U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1439U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 17U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 124U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 578U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1730U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1310U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1068U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1838U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1765U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1834U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1943U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 671U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1929U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1917U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1973U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 278U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1098U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1111U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1328U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1581U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 949U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1001U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1038U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 336U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 40U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 144U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1602U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1240U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 340U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1526U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 200U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 370U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 732U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1552U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1575U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 402U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1238U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1513U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1697U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 761U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 985U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 6U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1376U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 2006U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 83U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 88U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 752U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }
}

void TwistExpander_Mothallah::TwistBlock(TwistWorkSpace *pWorkSpace,
                                       std::uint8_t *pSource,
                                       std::uint8_t *pDestination) {
    TwistExpander::TwistBlock(pWorkSpace, pSource, pDestination);
    if ((pWorkSpace == nullptr) || (pDestination == nullptr)) { return; }
    std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    std::uint64_t aPrevious = 0xE458B1354582FFAFULL; std::uint64_t aIngress = 0x963059FB3B500D58ULL; std::uint64_t aCarry = 0xAAD7AE560E7F0FA4ULL;

    std::uint64_t aWandererA = 0xF76D5AB88387CACDULL; std::uint64_t aWandererB = 0xA1F4D767FFECE8B1ULL; std::uint64_t aWandererC = 0xBCB885C467422F97ULL; std::uint64_t aWandererD = 0xBE135799641597E8ULL;
    std::uint64_t aWandererE = 0xDFB78C8842EA71B7ULL; std::uint64_t aWandererF = 0xD1F0CF822D7751DCULL; std::uint64_t aWandererG = 0xF91B6FA84C567644ULL; std::uint64_t aWandererH = 0xF032F5F541B3AF06ULL;
    std::uint64_t aWandererI = 0xBDBF424554B017F8ULL; std::uint64_t aWandererJ = 0xCA7F8F8EAA61E6EAULL; std::uint64_t aWandererK = 0x8BE1B1239BFE7C2EULL;

    // [seed]
        aPrevious = 14777147250856425584U;
        aCarry = 9907938212194674387U;
        aWandererA = 15640620648996567992U;
        aWandererB = 13404542793827187818U;
        aWandererC = 17208680094102950501U;
        aWandererD = 16609792462639319166U;
        aWandererE = 12237985406960120175U;
        aWandererF = 11783242960202539797U;
        aWandererG = 12800915592812184759U;
        aWandererH = 13013361966483524307U;
        aWandererI = 18206286659275970036U;
        aWandererJ = 12517599933066049844U;
        aWandererK = 11736251746220075351U;
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
    TwistExpander_Mothallah_Arx::Twist_A(pWorkSpace,
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
    TwistExpander_Mothallah_Arx::Twist_B(pWorkSpace,
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
    TwistExpander_Mothallah_Arx::Twist_C(pWorkSpace,
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
    TwistExpander_Mothallah_Arx::Twist_D(pWorkSpace,
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
    TwistExpander_Mothallah_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Mothallah_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Mothallah_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 22 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 11389; nearest pair: 472 / 674
void TwistExpander_Mothallah::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1311U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5849U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1842U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5531U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6890U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6561U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3965U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2359U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 150U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2954U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 887U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 628U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3686U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2499U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7543U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7680U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 310U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1832U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1418U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 19U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1858U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1611U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 583U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 813U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2010U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 343U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 740U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1535U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1118U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 112U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2040U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 180U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1718U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1084U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 773U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 108U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 22 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 11397; nearest pair: 457 / 674
void TwistExpander_Mothallah::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1093U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 688U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 109U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4339U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4166U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1973U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1951U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7607U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7943U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3294U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6961U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3967U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6978U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6799U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3516U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7162U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 623U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2014U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1832U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 240U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1120U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 356U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1265U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 447U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 417U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1478U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 555U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 456U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 622U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 41U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 396U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 50U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 35U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 923U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1044U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1068U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Mothallah::kPhaseASalts = {
    {
        {
            0xB7E09A422A4E5C6AULL, 0xC04272AC843183D5ULL, 0xAB3EE9F738EEC028ULL, 0xA06058E0EBDA7751ULL, 
            0x2EE187ED7759CDE1ULL, 0xBE7416A0F98E77E5ULL, 0xDD2FB963EFDEBC59ULL, 0xCB63272DC0D9F59AULL, 
            0xEBB416BB4643E8E6ULL, 0xEECEE3A30D04FA38ULL, 0xCAFCFEBD13850F5BULL, 0x96640DF5A7B451B6ULL, 
            0xA0DBFAF8187DA262ULL, 0x9BFC1FF53F7EBDA5ULL, 0x46BCFA7EA865C7B9ULL, 0xD99577E433E8EBBEULL, 
            0xE94C2EC1AE814F07ULL, 0x89B344B26C1D63BCULL, 0xE0EAB6E120A542DCULL, 0xD0EEE5E74AB10CD3ULL, 
            0x2084EF4D5875B142ULL, 0x06D990F671D82EA2ULL, 0x24C8E33C4EEFED08ULL, 0x4B78A47C000455DFULL, 
            0x84E289ECD5594EA1ULL, 0x0759F1D584C2DBFCULL, 0xB7C828C7C74C1EA5ULL, 0xCEAA7E41F96D5DD6ULL, 
            0x6A301EC2ED201F49ULL, 0x6370A0C0C20F6C7FULL, 0x98D48BDEEF498D05ULL, 0xC26B75DBB65A9277ULL
        },
        {
            0x9CC9634BC1BC148CULL, 0xBBBC245075DF764CULL, 0x5F2028B8F887E640ULL, 0x47055DB66696D9E9ULL, 
            0x24D1B7AED68DB97AULL, 0x3BF02BCBC8ADDEAEULL, 0xE2BDC040B8644934ULL, 0xA3335E8009E269FDULL, 
            0xE30660565804B405ULL, 0xA097BB01C36C960BULL, 0x20A4A7625E0F3B71ULL, 0x37815CD849DED86AULL, 
            0xA04D333AE2C99243ULL, 0x2D53EA7316078FDCULL, 0x7D562127C0C5FB31ULL, 0x390CB022088BFCB4ULL, 
            0x8E682EACA16E7E35ULL, 0xB46927CF2C0AAC34ULL, 0x81337045DC5BCD8EULL, 0x817BCAA1FF1FDECDULL, 
            0x235E4A24BB062111ULL, 0x1C6C7756587AF2EBULL, 0x4DAE3CE09ED7BB67ULL, 0xFE1156D962BD6F73ULL, 
            0xC4F09924CA0376CDULL, 0xEC3F1F69B82AFCFFULL, 0x9013EBCFBC72A300ULL, 0xBDE57978EEB552A1ULL, 
            0x09864A774650A6B0ULL, 0xA326F8803C8FA061ULL, 0x17CEB1EAE3F6BB20ULL, 0xB13D56FA77DB196CULL
        },
        {
            0x74D3D1E146C78DEFULL, 0x598C863C874F094EULL, 0x3436C7D808CD7217ULL, 0x7D08C7388CBB17F2ULL, 
            0x29D3759E66085B75ULL, 0xF123F022D4DADD73ULL, 0xFCDD1624483C661BULL, 0x083E3B4B9C3E448DULL, 
            0xC8F45C315939EC89ULL, 0x7CD9027301C633C6ULL, 0xDC7F6AE1DF79C0CFULL, 0x2504EB05ADCB29CDULL, 
            0xB844B444C6E81BA7ULL, 0x0CCC713E621D2100ULL, 0x165EBD4765A77BECULL, 0x63391BE433B5F448ULL, 
            0x170D10446D9B833BULL, 0x761BE45D0A794B36ULL, 0xD419C0E5D84007E7ULL, 0x1F5673E33B417F27ULL, 
            0x7FF67717CDF1F459ULL, 0x3E91AD05CF41DE0EULL, 0x9D9FD95692A226D5ULL, 0x06B36590568A37B9ULL, 
            0xA78FA8AB6E9EDCDDULL, 0x455335C76109A140ULL, 0x109BC1749AD4CE36ULL, 0x537F0C9E730B50F2ULL, 
            0x30FB694C8406E697ULL, 0xBF8C94D0A799A427ULL, 0x5E9C7B1125CF2AE2ULL, 0xE066561CC73BAA30ULL
        },
        {
            0x903112E4BFCE192FULL, 0xB497BA21241FC2ABULL, 0xE30006243A598AB3ULL, 0x2A6D0CCC4048F116ULL, 
            0xBAF75F5B3A9F1758ULL, 0xCBDBD784CE0714CCULL, 0xFCA81A7A73CB7308ULL, 0x27503E6FFAD83D19ULL, 
            0x8F73F2662A3A34E5ULL, 0xC82FDB7EA342BE21ULL, 0x4E9F229321081DB0ULL, 0x432EE54420F884B7ULL, 
            0x478B72E06D4517A4ULL, 0x2FCB12230C2B5317ULL, 0x4F7EEE38C0E5FBF8ULL, 0x3C6A2C7E9E121444ULL, 
            0x63DF5F38466E9066ULL, 0x71AD5354A92B5533ULL, 0xC8AB6B370D278CEBULL, 0x913383351F4B0824ULL, 
            0x4FB42A337D8C051CULL, 0x2A3A446FD14EF22DULL, 0xB885711002AD7B2FULL, 0x60ECF6FB0A465931ULL, 
            0x351D3AF9AE697E33ULL, 0x70330681FD8B191BULL, 0x65D1FC1B488CAD0BULL, 0x075E37C71FC29995ULL, 
            0x25AC3BF29DC1D169ULL, 0xA6404B6CC3957388ULL, 0x2642D98DD701BF27ULL, 0xFF43F814FA00931EULL
        },
        {
            0xAB26F6BF84043817ULL, 0x21F8AC2FDFFF3963ULL, 0x091D3ED139C88F44ULL, 0x877BEAFBB5118342ULL, 
            0xE2B7D32FFFBCEC6CULL, 0xEC6411BDD547D877ULL, 0x770B7C712CA8652CULL, 0x7E010FC55A6FE8FFULL, 
            0x0D6DACF71AD219E2ULL, 0xD0F95524BC640779ULL, 0xC480346C155454C0ULL, 0xA676A23B59FAD98EULL, 
            0x23C431880849E542ULL, 0xA772E632E86DBF0AULL, 0xD0F4228E4B83F94DULL, 0xEA0D17C3442155BDULL, 
            0xEE39E7351DE522AEULL, 0x0FC8260D03A4A59FULL, 0xFD5810D28AE28283ULL, 0x21DE03B73E57D50AULL, 
            0x4E153CE81FAAEC01ULL, 0x87A8EFA27F4E84C9ULL, 0x5BEEE8D29E92B0D9ULL, 0x2173F41CCCFD603FULL, 
            0x930F8254D1B7352EULL, 0x0FE31363ED1CC38DULL, 0x73511E27608044C4ULL, 0x209CC75109F3A7E3ULL, 
            0x124D7D9D076BBC93ULL, 0x34474934267C26F6ULL, 0xEDFFC0ED3217441EULL, 0xA15745A6B99A7B8EULL
        },
        {
            0x17F69588065CD14BULL, 0x00A18551E48F24F0ULL, 0x7D243314754C9134ULL, 0x4EB250B5DB80CD6AULL, 
            0x5F62BFEE0E2E709DULL, 0x604AE646A1C21F9AULL, 0x7AD2372568FAEA72ULL, 0x5087F28B99C4BB9EULL, 
            0x3C17236CB2A7E495ULL, 0xC6DA816EA1083DA5ULL, 0xFC50104C4A2F9CABULL, 0x72D8EC13CC85C8B5ULL, 
            0xF4FBD7FF97662882ULL, 0x509B6B6CE2856461ULL, 0x55D19B39D910E7B8ULL, 0x52F17FC4A9DADBF2ULL, 
            0xB13948C058F3F16AULL, 0x1A5C1CE3F50E53DFULL, 0xAD2B04DF0CC6CF37ULL, 0xBC26ADB1B968BA80ULL, 
            0xAD08FE96E0AC564AULL, 0xE974D15965C02A2AULL, 0x6B9CF460D0ED57CFULL, 0xDA8F290497E51DCEULL, 
            0x61D8DBEC943DE2AFULL, 0xF561DD89E8E3BAA4ULL, 0x73576EDFA788C8F3ULL, 0x1A086F3EBDF7FD35ULL, 
            0xC06B64C530219E2BULL, 0x8CCA997979A3C893ULL, 0xB6CB1364C5592F92ULL, 0xD4CE3D4FC9A8443FULL
        }
    },
    {
        {
            0x3F5D3D76520E526BULL, 0x9625838182A437CFULL, 0x44A9BC3DF95F01C4ULL, 0x02B89584C897194CULL, 
            0x0FD11033D55FB2E1ULL, 0xDEBDAB75B22ACC35ULL, 0xC5621FC384EF9E12ULL, 0x5E7344BDF74D5C1AULL, 
            0x892EC80A79CB2FEEULL, 0x5A24829E535E5FA6ULL, 0x6B91B11BBE8ED2B1ULL, 0x9A18D723B7EFD0E2ULL, 
            0x21B064C91EEF97FFULL, 0x19FAE780FECD8D37ULL, 0xF82C570BA277DB8DULL, 0x50168B224A073DBFULL, 
            0xD39E20524E97E3D9ULL, 0x7C1F4CBD68C5DF90ULL, 0x409368C1BB39A8A6ULL, 0x9E23BBA697E18455ULL, 
            0xD62353E263A5C275ULL, 0x88A166CABA3CB937ULL, 0x4F9EF36E4EAC5736ULL, 0x227276AE4FB25240ULL, 
            0x46D0FCD1710DFC1CULL, 0xD845995EA7D7FB60ULL, 0xCB9C1B702E1AE4D2ULL, 0xFA8CACBC4367CA80ULL, 
            0xAAB355DD1622B709ULL, 0xF7496FD377B240D8ULL, 0xB14A6BEDBFE3FC19ULL, 0x9EB55FBACE3D08AEULL
        },
        {
            0xC2B49018394B71E5ULL, 0x91BBCC3B18C9F822ULL, 0xFECCA9ED9C4048EAULL, 0x289631740C86F627ULL, 
            0x5CAA0F5321B8DDAFULL, 0xC722A96E163B3C30ULL, 0xB0BA031DD760E7A9ULL, 0x4E6E3A182988A449ULL, 
            0xB1457D363E5273F9ULL, 0xFB606EFEF1979930ULL, 0x413E1F6093641B6EULL, 0x30BF11EC6747ABB9ULL, 
            0x6A261D52441AE4E3ULL, 0xA3C16DDC3FF7AA38ULL, 0xFF911D71FF3193C3ULL, 0xEF5F019663518D77ULL, 
            0xEC7044C6902FBA41ULL, 0x618F87654EE8D309ULL, 0xE5684B18BF6C06BAULL, 0x290D7F91D757F408ULL, 
            0x47A3784300BC71DBULL, 0x184FF21D0F76A876ULL, 0x1EA03B37B25C9E42ULL, 0x031C05FB1C4A4F30ULL, 
            0xD18FAC6C4D7C1DFAULL, 0x02024F1C9BF9AD83ULL, 0x479B60FDACFC1B30ULL, 0x00891C2AE48D9278ULL, 
            0xFE30206936E71704ULL, 0x107F67AC5B08B66DULL, 0x47B556B27EEE4E1DULL, 0xE6AC0178BA942C42ULL
        },
        {
            0x07DBBA80B1C65ED8ULL, 0x417B4CB38092A836ULL, 0x6A850387E1871357ULL, 0xBFEF91598C38F910ULL, 
            0xFA3A1A170DA0946AULL, 0xB2D64646AF8FEC0BULL, 0x18695D811AEFE766ULL, 0x1868C132304D437CULL, 
            0x98F873A45E22BDBFULL, 0x8E269834D6442F61ULL, 0x6037F6D7C2214FF0ULL, 0x8291DF30AC13EE39ULL, 
            0x4FDE1FC9A145E31EULL, 0x22D9032B6A96734AULL, 0xE82FD695879DDC70ULL, 0xCAEDD34E577F194EULL, 
            0x6FBD74A2732B24C2ULL, 0x1742BA2BE2D802A7ULL, 0xBE819D44FFC5F9EFULL, 0x16213C55144B6A6DULL, 
            0x0908AFE0D0812075ULL, 0xBD98935A5636AEEEULL, 0x4B8A833EE75FC003ULL, 0xB55BB29FCDCC713EULL, 
            0x52AE44EDE162632BULL, 0x256252FD634E8728ULL, 0x1CBAA1CA9909FEC9ULL, 0xC1D55F012D750F67ULL, 
            0x61A9804697BB5325ULL, 0xBC0A1477382C3F0DULL, 0xD305504FAFC27273ULL, 0x0C66575FCB2F93EFULL
        },
        {
            0x2F47C5F24A47099EULL, 0x64B9002C4FD39EACULL, 0x1AE941C65A4DAFA4ULL, 0xD21FC348E9989C8EULL, 
            0x2D30D09AAAE0A828ULL, 0x1ECD1BBEE960CF7BULL, 0xA51E016900E2B777ULL, 0x94C308783EC1F641ULL, 
            0x7D9121E1CBCF1F73ULL, 0x988FC30F67F4855BULL, 0xCE3FD6C32D1A8958ULL, 0x5F0A5F3A374B0F29ULL, 
            0x14D5C098B6F1FA7CULL, 0x74BBDFEEA3A1142AULL, 0x7E4732058E4C6B34ULL, 0x282F71C10D9D4BC8ULL, 
            0x3AF6F3EE084BB99EULL, 0xEC238B7DA68CB3D2ULL, 0xB15B0C1BF74B82D9ULL, 0xECAAECCF046D91CFULL, 
            0x305639333E4EB0FCULL, 0x55F78B2EE729B7EDULL, 0xD9D2B9CCE02D3C7FULL, 0xD9558AA8E5D445F3ULL, 
            0xAA0B02C81B17F434ULL, 0xAD723B741A6E240AULL, 0xF77D1DE441AE2EA0ULL, 0x2DD9D2FB4A49879CULL, 
            0xA8456C32093FFA60ULL, 0xF3C335AF06476D47ULL, 0x3FD9682AB8CF6BEBULL, 0xBDEF7331A8F72833ULL
        },
        {
            0xED5B1108EF8004D2ULL, 0x6432C635B7C344FBULL, 0xAAECA3FC21E1A9FDULL, 0x2895AE8140DED482ULL, 
            0xA1F183D5E2E45474ULL, 0x5EE7878E6C025863ULL, 0x74191D0D12B346C6ULL, 0x5E8F12AC4EE12D1CULL, 
            0xB38A9A0EF99DF976ULL, 0xD9BA03E659F6E5DAULL, 0x784AA305C3EF95D6ULL, 0xA21E48DB1F5E87E6ULL, 
            0x522233235C8A8429ULL, 0xA63825CF7C435E7FULL, 0x8DB269A4D4A68EB1ULL, 0x856E73010AB1D9D1ULL, 
            0xFB21580800538527ULL, 0x3BBE1E5C3D021F97ULL, 0x2323FBB3BAEB0FF6ULL, 0x21193E75D777D0EAULL, 
            0xB8885A863718B6E2ULL, 0x5458766792B78265ULL, 0x728800422952C51AULL, 0x521111E35E07C9DAULL, 
            0x92EC7C40652D1A33ULL, 0x5606F68A0489779EULL, 0xF2AE9E26E60870A7ULL, 0xBA8D33AD2324A64EULL, 
            0xC07F77620368D3F4ULL, 0x5955C38AB9D8FDFEULL, 0x35A2C86C169559FEULL, 0x168E6A4FED386EF0ULL
        },
        {
            0xCD382E8AA0D212A5ULL, 0x782892D8AF0A7A79ULL, 0x8924FD88D3C0F4EBULL, 0xB993D383F857B886ULL, 
            0xF3247C0C0C787AB9ULL, 0x02F410FC4E2C54B9ULL, 0xDE6D9671DA1D4153ULL, 0x7395C7B9F868569EULL, 
            0x2D704CCB9DD3B93CULL, 0xA895E53562FB3516ULL, 0xB6954E755E13D057ULL, 0xC4996ADE379B939EULL, 
            0x21D8C460A27534A1ULL, 0xB6DA3927C94A7077ULL, 0x0762C34CE1DC9814ULL, 0xADA8BA34FDF784E5ULL, 
            0xA1776EB008DFFBEBULL, 0x529C3D36A17EF2C5ULL, 0x96905E41723465C5ULL, 0x1AC241FDD6C31E27ULL, 
            0x8982214965873706ULL, 0xB6DBE55C2FC07B69ULL, 0xA2A2C82B9FFEE233ULL, 0xDBE1B2F50AB18658ULL, 
            0x5B6C5F19EA2E3029ULL, 0x3BE4D7CF5ABC3EC0ULL, 0x5925EB6C6B03C4D8ULL, 0xB4D152258E8EB19AULL, 
            0xD48C817A29F93D6AULL, 0x097C0E29ED5BF3F3ULL, 0xC612673D74228B00ULL, 0x91A2FC7DF2D2B6CAULL
        }
    },
    {
        {
            0x2EA4E4324BFE0258ULL, 0x59F08A9EB194F24BULL, 0xEB0CF9209EFFDA3AULL, 0x73B65F5E406B263AULL, 
            0xCA288E8080793EA0ULL, 0x9D1B4A687AF39E51ULL, 0x3DBD8DF5F1D93961ULL, 0x121A9E2DEC0CAB27ULL, 
            0x5C4DE3F8EE4ADEDFULL, 0x2E896B15D21C24FDULL, 0xA379E3D3A444963AULL, 0x67C251DEC0E23414ULL, 
            0xAF2E2B0409EEA01CULL, 0x48E6840C11E701DDULL, 0x5446A4584609A189ULL, 0x04BCABD3CC618726ULL, 
            0x7299A8621735DC27ULL, 0xA0B25F8BD5B66430ULL, 0x0391C7CD1D03BB73ULL, 0x6D6081B472E188E7ULL, 
            0xBE1D975737EAC244ULL, 0xEC212DB3F17D6865ULL, 0xF009D33D6A4A84C3ULL, 0x11B88F6E0F94179DULL, 
            0x19BAD28584939DF3ULL, 0xF525233EC8EFE825ULL, 0x0CCE7D893300858EULL, 0x0EC00BE4CA1465FFULL, 
            0x790615C8D60E0904ULL, 0x0484FF4FFD81926CULL, 0xAB13A6F94981D0ABULL, 0x8B89090413BC7B21ULL
        },
        {
            0xCFFF07277169B15BULL, 0xB87718C8266652C1ULL, 0x9A1CAA8ED4A172A9ULL, 0x399E9AFD158042A6ULL, 
            0xA405D666678EF4F1ULL, 0x76EB8D5CB88C7220ULL, 0x37F13E3EF210766EULL, 0x810E56A4FE2A212EULL, 
            0x5BEC652F7FF1E7A8ULL, 0x33DE6DA5002DEA85ULL, 0x6EFFD4C2B41796A2ULL, 0x91B02B3568F42963ULL, 
            0xF2766242F5778E7AULL, 0x26EE875E79DAA2B4ULL, 0x4BFAB45DF43B6AF7ULL, 0x890CCE4A0DA6B8D2ULL, 
            0x2410FDADE74B3178ULL, 0xD46E992CB83AF11CULL, 0xB85DED22D9C2553CULL, 0x3176258F8D8D4339ULL, 
            0x8C329716D55A340DULL, 0x5665F50017D93766ULL, 0x3A7B5680A7E2BD26ULL, 0x392651494E432BA3ULL, 
            0x82982E1AE77FEC4BULL, 0x345F970770C2E664ULL, 0xD41457C95B57527BULL, 0x41C79B1109ECBB92ULL, 
            0xF4F004255F4C638AULL, 0x6FCFDC302F13EDB8ULL, 0xEB64CA30CC20E6DCULL, 0x7E616E46FE6B752AULL
        },
        {
            0x9908AF4824842137ULL, 0x6A660E9B8FBBD59BULL, 0x22F08043EA330571ULL, 0x5B3B33068897D602ULL, 
            0x0E4861848FFB8924ULL, 0xCF12EE0B059A7AE9ULL, 0xFE36B798B145CF93ULL, 0xA582843E5BD9BE9FULL, 
            0xD3139C00C98978DAULL, 0xD3C05A8FDD1F674FULL, 0x41771CB9FEEE1039ULL, 0x1330EB31D2905FD1ULL, 
            0xC94ECF48DB9CD85EULL, 0x175B4BBCAC481852ULL, 0xC1826A762581968DULL, 0x5D6795A8A47E0A44ULL, 
            0x90320DC634007994ULL, 0xEE57EF540E348180ULL, 0x84DB293E6A748AD7ULL, 0x6293791058E3DF6CULL, 
            0x463FE9BB910D8067ULL, 0xAC4D2ECAF92EBB62ULL, 0xD12BC268451815C5ULL, 0x4DD4768F365550C9ULL, 
            0x2FEC296EB7B9E1FEULL, 0x792F863F2EEBA1E5ULL, 0xBAA7B601703D3761ULL, 0xF1649EAAF43B2F0CULL, 
            0x0F72FA6CD0AB851DULL, 0x5A909E71181F6A62ULL, 0x17D9EDFA33183534ULL, 0x6CD426F6D63D1291ULL
        },
        {
            0x8BB5211FA32706E9ULL, 0xADE2533CB7CC3B2AULL, 0x030D48CDC56E9E3DULL, 0x75DA92E59AC6C3E4ULL, 
            0x5E933BF056BF980EULL, 0x98F4760EA7D2D379ULL, 0xDA7931857BFD3980ULL, 0x65F70D7A23C2494CULL, 
            0xA07F622024C285DEULL, 0xD29CF25E3A6C1316ULL, 0xAB2A7D6B82C5A411ULL, 0x160B9AF2B15B7DC8ULL, 
            0x67B34FE66F84231AULL, 0x08D885801500ECC4ULL, 0xCDFB0408197C64BAULL, 0xF58A7E2DA2C66C2DULL, 
            0x5AE1332CF366BE18ULL, 0xF673C64D5B7A4E87ULL, 0xCBD37D36C8B29270ULL, 0xF80252B849B2A60FULL, 
            0xE7D1B6C16E99C0A3ULL, 0xB0D834E72F76310EULL, 0x2BCD1E4DE0054D00ULL, 0x9190A23175273154ULL, 
            0x9A07F48FCA78A119ULL, 0x85085C9B1F9C7DA5ULL, 0x301997DECA2546A4ULL, 0x59F390B0103FB8C8ULL, 
            0x693E4C56EA49259CULL, 0x5167C6CA5CBFF13AULL, 0x7CB0C21D3A499B41ULL, 0x8A5FE7B579266F55ULL
        },
        {
            0xDA6B096E7E809777ULL, 0x426034CE99DF3294ULL, 0x914445FD8D4860D8ULL, 0x362AB294AE7CDA82ULL, 
            0x0D4FDCA2D598F9D7ULL, 0x3F2427FE80CD03B2ULL, 0x26F3F9A67FB2C382ULL, 0xC2DB2A1993A208F4ULL, 
            0x210E2A83A4DAEA81ULL, 0xE51FC871F2B74A43ULL, 0x843D69E1D3BFDAF7ULL, 0x43ED46CC9C157CDEULL, 
            0x2F74DADB1001D81DULL, 0xBF06E59BA511D133ULL, 0x0F35AA37C68BE1D4ULL, 0x85965437D81C9757ULL, 
            0x79B7F51176830E8BULL, 0xB9287F5FD576323DULL, 0x8B832BB88073953DULL, 0x0402F94998FAA2E9ULL, 
            0x29C155E430D4CDAAULL, 0x84A43F66AF6A7E17ULL, 0xDDBA0325A996A9DFULL, 0x6362FF0CB5EF8051ULL, 
            0xECF4533DE7D2967BULL, 0xD7E92B61C1ED82F9ULL, 0x409F77976F7D5507ULL, 0x53DD3773D8A78587ULL, 
            0xF43E35634DF5AA56ULL, 0xDFD7D35EAD3D8A0AULL, 0x1A33D08C542A696FULL, 0x05B2C432981AE903ULL
        },
        {
            0x19E4F0CBF339CCA2ULL, 0x728F1262F96ABA7AULL, 0x7037BF9CFDAE52BAULL, 0x37F03E992A9D464BULL, 
            0xDE4DA6CF3E037F34ULL, 0x89E679CC2401F0E0ULL, 0x6962C5724BB58BD2ULL, 0x694F953A9670FD78ULL, 
            0xE4A96CE0F4D0F7ABULL, 0x48AEC3CCF4758F57ULL, 0x32B7149F97144402ULL, 0x988CE9916826D8E2ULL, 
            0x81B9D57DB8953C9DULL, 0xFB1899BBC1D8C9A2ULL, 0x6EDD6F750DD591EEULL, 0x85016428DFE46DE2ULL, 
            0x6E4B141CC8352281ULL, 0x7B15F86ED990D3C9ULL, 0x208403D33B237952ULL, 0xCE49B1E36FC98499ULL, 
            0x8BCC6439169FFDB2ULL, 0xCAA78C8F4CACA8AAULL, 0x33C08855EC275E16ULL, 0xD9B30F259D4E2075ULL, 
            0x22FF3ACB6A0F8B44ULL, 0x35CBE787099EBC55ULL, 0xA7B865C6EAFD7A68ULL, 0xCCFBB76D874B1BF2ULL, 
            0x2C07BE9A0230DCD7ULL, 0x715295D007D51135ULL, 0x8E89E28D3DECE3B1ULL, 0xC5A92D30EBCB4E75ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mothallah::kPhaseAConstants = {
    0x992C5260F6A11B47ULL,
    0x7E2861AC6FCF085BULL,
    0x824C6709A545A5A2ULL,
    0x992C5260F6A11B47ULL,
    0x7E2861AC6FCF085BULL,
    0x824C6709A545A5A2ULL,
    0x1062CB705AEAED85ULL,
    0x0269F8489861DF24ULL,
    0x5C,
    0xC4,
    0xE2,
    0xDE,
    0x73,
    0x65,
    0x73,
    0x3A
};

const TwistDomainSaltSet TwistExpander_Mothallah::kPhaseBSalts = {
    {
        {
            0x103C9D9BB4C55068ULL, 0x94DC56A4FF6DBDB4ULL, 0x4BB0C30921ED50C7ULL, 0xB3B4A64EF09DE2BEULL, 
            0xB811D8AD6F62C97BULL, 0xDE719ACFB085335DULL, 0x32D17B96314EE935ULL, 0xA25D36D7703F8C45ULL, 
            0xC3DA5C0C08779F91ULL, 0x48148363642318B2ULL, 0x2CF0EC4B1BEC8396ULL, 0x00EE5191700FC911ULL, 
            0x6A9A9BA91E66AFBEULL, 0x2E2E102F0A52F9BBULL, 0x1D4F9DE1D83C0FF4ULL, 0x08426ADA686F7E6EULL, 
            0xFA64102335027647ULL, 0xEB0BDBF7E471FC90ULL, 0x7376E4463C051541ULL, 0x32618D291181FBD1ULL, 
            0x27202F54F6F23072ULL, 0x085031EB0F096EE8ULL, 0xFAEECC124BE7CEA2ULL, 0x3D1526615D952EEAULL, 
            0x12F0118752CCA12EULL, 0xA94F0DF9A03089D9ULL, 0xDBB6E68AAD6DDD47ULL, 0x68987153AE70292FULL, 
            0x1946F215E0A5D09AULL, 0x9DDB8019C5D3CF24ULL, 0xFDAC9263FDFC4A9FULL, 0x09E084CEEDC67905ULL
        },
        {
            0x82C2F0F15269528CULL, 0xF55157DAEC191103ULL, 0x4D2092F529C03059ULL, 0xA7F907081739EFE8ULL, 
            0xE5F9354643FC02E1ULL, 0xECCEFF6B1FD8DCE3ULL, 0x30C65E6E36597F23ULL, 0xC4ACB8B6F43B2F42ULL, 
            0x9F868BBA068E0BBCULL, 0x3D504E2EE1A0F009ULL, 0x2B5CF4CAFD55BA43ULL, 0xF82CAAFC3A3215CCULL, 
            0x8BAC0CA4A8C2CC5FULL, 0x9D318208C89B12B1ULL, 0x6F5AC43B17B97414ULL, 0x6561D1E5018620EDULL, 
            0x17390FE92EB43232ULL, 0x7CA59C6C2799499DULL, 0x5104C8E884021468ULL, 0xA7F19CC071385C4EULL, 
            0xD6AC51532A22C5B0ULL, 0x4E7A0E305BDDFABCULL, 0x0A80B984486495BCULL, 0xD24961739D8575AFULL, 
            0xD4EDCD9D26C2DF35ULL, 0x6FD6DCC94120483BULL, 0x741222E5DA5CEDF2ULL, 0xC18A6E184578282CULL, 
            0x089F1166964DA938ULL, 0x4479D51A84B00092ULL, 0xB52083D97E204EFEULL, 0x45609A0E14D54502ULL
        },
        {
            0xC11E56E664B8A715ULL, 0x47393AD1E6DBBE64ULL, 0x2751595EFAA72730ULL, 0x65519D45A72F42BBULL, 
            0xD7C4CA4C0DEEF8E1ULL, 0x354C7195F6C7FDC8ULL, 0xABF8888130036BE2ULL, 0xFF135EDD042DFE6FULL, 
            0x1C85A29066F0A0B9ULL, 0x092857CAD32D963BULL, 0xFF47C926FF3E9D1BULL, 0xC1F4E5DDCBF1895AULL, 
            0x33766E82D7C2D28BULL, 0x5F6C8DC13E1F01A8ULL, 0xC37137CAE12779BDULL, 0x32FDAF322505912AULL, 
            0x86E389EA6E61C5F4ULL, 0x6A6175C6DFE30DD7ULL, 0x1A21525FD1C736F6ULL, 0x61062884B8C6081AULL, 
            0x7F5A25355AD73C49ULL, 0x56C47D2DF79D4054ULL, 0x2D77FBD59B0626F8ULL, 0xE2B38076F18E797EULL, 
            0x7C3BF6444CF641D1ULL, 0x11B40E0661FB3613ULL, 0x0A7ED784ADCFE627ULL, 0x9E6FF5DD111C6591ULL, 
            0x63A814FC3DB9ABCDULL, 0xA1B1898CBE972583ULL, 0xF000F8D37BBF8A08ULL, 0x8351149FA90145C1ULL
        },
        {
            0x0FAD70074331FDBAULL, 0x9FB2F2B44C2F8EEAULL, 0xBB10B420A3BA714AULL, 0xAB715698415619E6ULL, 
            0xA692EB3F075BD0D0ULL, 0xAFC43D2278CB73A2ULL, 0x36DA114C3EAF3C28ULL, 0x36AFB4CE8BE54819ULL, 
            0x7824CF615A393D72ULL, 0x905FDD6456921A0AULL, 0x8973CD5C30ECBC3EULL, 0xE910FFD157A5C198ULL, 
            0xAFCDD334F7982876ULL, 0x4817EAF21782AF64ULL, 0xB47505A703A7CABEULL, 0x88C72B0C21E2D358ULL, 
            0x00E8524FAF67AC96ULL, 0xB4A68F901B435906ULL, 0x59F084A9ED6D9CB8ULL, 0x2C70E3DA3AA5A2F2ULL, 
            0x70EA496C6755DD46ULL, 0xDBF83CB1AAC99216ULL, 0x2FE1053F1B763B9BULL, 0xAEE9B0AC1399A4FFULL, 
            0x5C60B89908F567CEULL, 0x32D3D81C8206B64CULL, 0x9ACE376414BF5563ULL, 0x5614957FB6DDC0EFULL, 
            0xE07DB936C6F5EE1BULL, 0x2DD62F568C6E905AULL, 0xE80C7EFEE557FAD8ULL, 0x64D06B5EFCA26D51ULL
        },
        {
            0x2CCB126E99E874C9ULL, 0xDD45ACE4C8AD5F54ULL, 0xEFAB85F537206774ULL, 0x7D95AB795EF10079ULL, 
            0x9188A6174CC51284ULL, 0x123A0F1B28C76408ULL, 0xE52D0743163CF3BDULL, 0x47FF4725CC9C9503ULL, 
            0x35DB17F3E5EE0357ULL, 0x4DDE063F876BB838ULL, 0xD94C23D5F81C0A84ULL, 0x72B5E46766F780DFULL, 
            0x1902A3D2BC1F34EAULL, 0xDBC5D67DD95592B3ULL, 0x16F2E31F912AAD1BULL, 0xA721524C3402BBFDULL, 
            0x8895875089473147ULL, 0x25C4801AA3356984ULL, 0xD929D4EE63C1939FULL, 0x5E52BA37AA8DF5DCULL, 
            0x2B1E2911DEDD846CULL, 0x21526F3F92BC2DAEULL, 0x052B51E809FF64CEULL, 0x4DFCB482BB9FFBE3ULL, 
            0x24A635EA056EFF25ULL, 0x52E615A8D22E1501ULL, 0x25A5AF3216EAC684ULL, 0x45681ED36E074696ULL, 
            0x7BD1F5293F38D009ULL, 0x488203550BD7253BULL, 0xED778AA8B56017CCULL, 0x5511F79F58025AA1ULL
        },
        {
            0x1060143723F0885BULL, 0x84BB2CC957799A83ULL, 0x92E995071FDF24BCULL, 0x01054DC734A40900ULL, 
            0x39D086580E212A2FULL, 0xD81124E33D7EDCA1ULL, 0xF88AADE93001ADEEULL, 0xC8049F2AB24C3996ULL, 
            0x4C7713BC37828054ULL, 0x9B6D6DD7639A5385ULL, 0xBAE2BB1196E1ADB4ULL, 0x3D7D038FFBE732FBULL, 
            0x4E2E8E105E69596EULL, 0x76AC2DA6F4A6DD38ULL, 0x691A59FCB65068B1ULL, 0x422519D6724D6D2FULL, 
            0x44CCF2550463994CULL, 0xB0ECE5B6565A7F29ULL, 0xF75F27C7FFF4CE53ULL, 0x9106C6988E673852ULL, 
            0x8019FD29B5C0DC0CULL, 0x246BDD7527896910ULL, 0x13E2B0979E6A25F3ULL, 0xBCC784F970931980ULL, 
            0x8B5C47581D6BA16FULL, 0x4A20A88FA4216A53ULL, 0xC7877D7385B89627ULL, 0xCAF037B464F5CD0DULL, 
            0x3E19F1DF40F97AF6ULL, 0x32FF5AC4CA33D180ULL, 0x5E3AC2620F40575DULL, 0x9AB25C8AF7DEDDB5ULL
        }
    },
    {
        {
            0x9F6383F5D1848C0EULL, 0x0479B85D0C9450D8ULL, 0xCFDC79085D0A116FULL, 0x490A54C5F18D637CULL, 
            0xACDF41B85453589FULL, 0xCF7A15FD89B29E4AULL, 0x812C27D54874C99DULL, 0x13A5F6C42EC0752FULL, 
            0x788D13EAE4191C65ULL, 0xD3868877C177F3F5ULL, 0x4312BA4FEA7AD4CBULL, 0x69E94FD55D6D7BA1ULL, 
            0x599D318EC52EF1C8ULL, 0x412815D26A084158ULL, 0xB856A399402841E5ULL, 0x4C7737AA976F18EDULL, 
            0x740E614DFF369336ULL, 0x992DDC43F4D5B899ULL, 0xD929BBD863DD9C90ULL, 0xE88EB25B59E52D06ULL, 
            0x89FF3932279C493CULL, 0xEFCF85635DBDB0EFULL, 0x908ECB44E041D5D7ULL, 0xFEF7E45BED47FC45ULL, 
            0x6A3483B4D4014DBAULL, 0x844A1BEBF6A5EA94ULL, 0x4B0290410E3437D4ULL, 0xB3F8B00BCB687B58ULL, 
            0xE28DE43EC85A128FULL, 0x9487779D07273A3BULL, 0xC78122F8F0AFD139ULL, 0x50CFCC74F6C68699ULL
        },
        {
            0x7CFC02DFDB6CE8F1ULL, 0x9C4EBCF48C5E5070ULL, 0x8A99858C73B9105AULL, 0x7F9F001C1C43FDBEULL, 
            0xFC2A5714DFA61588ULL, 0x01FF2FC4CFEE0D2EULL, 0xFF31406BCAFFE484ULL, 0xF9456AB4F4A3B276ULL, 
            0x3918E727B8273B84ULL, 0x8684546F66567283ULL, 0x9B2D96CB1C85DC6EULL, 0x8254D3497DFE3197ULL, 
            0xA6808F94757D1F33ULL, 0xDD09BB88B5F0431BULL, 0x913C46CADBAD2FCEULL, 0xAD77E0F5345C43E2ULL, 
            0x0AB9B7E180CE9848ULL, 0xB95F64CC301E55C3ULL, 0x6D473DB0719C01E7ULL, 0x75FBECEB6587FCC0ULL, 
            0x62788D5642C7E8ADULL, 0xB1E2B9D2A14D83ACULL, 0xE306A3B5BEE92D81ULL, 0xDB4CECF8D61A6E7FULL, 
            0xE6E9D4D30CB29C42ULL, 0x55DD3314333716A4ULL, 0x274738EDE99C305BULL, 0x694CD43262F4B82DULL, 
            0xEAE7DAAB1497F110ULL, 0xA2C7BE978DF28166ULL, 0x938C48C7CEF4B138ULL, 0x771B5DB4A19EDB8BULL
        },
        {
            0x92C631A29AAB7958ULL, 0x8383DCBDBBAB87AAULL, 0x2E9AD6F8214AEE8BULL, 0x62E2C49439BCDACEULL, 
            0x15121DB623211937ULL, 0xC2D34624E8C5CBCAULL, 0x8A2A5AAAE0AB3E2BULL, 0xBD7863552F6C5EC4ULL, 
            0xAB61B731C1EE4AE8ULL, 0xD3A86D6ED7B82539ULL, 0x8029F51DA2873C71ULL, 0x32D73EEABB309705ULL, 
            0x42D6D030927EB15BULL, 0x860A2BE2A421883FULL, 0x6A7D31581467FB10ULL, 0x904835064B353EC7ULL, 
            0x538456BE344086DBULL, 0x6ACC11CCF4BB98A2ULL, 0x6276F707A9B79DEFULL, 0xAC1F76318DAED27DULL, 
            0xFE4BAAC0F5ED58EBULL, 0x2FD792576E1D389EULL, 0x49D3E2C3A62EFB38ULL, 0xF83B2B9DECF0B55BULL, 
            0xBC734B03F6DB0848ULL, 0x58E7E72C5B2D94DBULL, 0xC53A3225E4E326FDULL, 0x9BD0C3881F9C5FF3ULL, 
            0x18116E2ADCA802AFULL, 0xF5BCFD982D194F42ULL, 0x07EC1B42FEEEF7EAULL, 0x499DE8831995E15CULL
        },
        {
            0xF68286DE82D6D85FULL, 0x10EA105661FC5C24ULL, 0x5E49D14695B86516ULL, 0xFAB69C7753BB85B9ULL, 
            0x8B5FC3A8BE8D75DEULL, 0x3829AF06794B2024ULL, 0xACE2422175B513C6ULL, 0x1C993A990CAC9E30ULL, 
            0xC278F20DCFFF7845ULL, 0xB7785245B1DBDBB9ULL, 0xB3F5CD826E9443A2ULL, 0x9F59FBF01797E9DFULL, 
            0x298FF3EDFC2D8BB5ULL, 0xE283CD2C3F56E7A6ULL, 0x8C558A249BDD77F6ULL, 0x3CAE94FFECE44568ULL, 
            0x7815F3535C710C0DULL, 0xCE4CAF2EEB5192C2ULL, 0xD7E1F6AAB209081EULL, 0x1E51026E17DE1C69ULL, 
            0x7C96CA5C0B7B5423ULL, 0x9C53A1ADD83A9046ULL, 0xF3EDAB8616D49FA7ULL, 0xCA5627CEEE83FCA2ULL, 
            0x44E1918349184FBBULL, 0xB265B2C0B4DC78CDULL, 0x00EF17857EFAD69BULL, 0x685DDD71ED2A2117ULL, 
            0x61745D4923D76CC2ULL, 0xF9C08F0FF17A5DCBULL, 0x07310E97263EEB2AULL, 0xA3EFEE5706CF6C73ULL
        },
        {
            0x8EC0ECB5BA8F9B92ULL, 0x4C1E7126CCA66AEAULL, 0x426DEDA8AE38031CULL, 0x955B38B4C28081EAULL, 
            0xE4C96E1713506C88ULL, 0x03D111C1A471D21DULL, 0x8902DB13663B20D3ULL, 0x1C9A5B0AB1A412EBULL, 
            0x101FBBAF08BFAAB6ULL, 0xC4B9C3D49A4E11E3ULL, 0xCEEFA7DFEB9424A0ULL, 0xA7656E7A278D558EULL, 
            0x1C895D8D902CB19FULL, 0x8994DDBDE5A5DE46ULL, 0x54EA3F716F345785ULL, 0xAE40912CCFA329B6ULL, 
            0x585835674CC1ADE9ULL, 0x6B71534A4C535441ULL, 0x19E45416096E49FCULL, 0x890DC2681228D76FULL, 
            0xD3486499AE64347FULL, 0x83316E211ED9BC05ULL, 0x7B4EF3AB094C4592ULL, 0x2BA82BDBCAC5939DULL, 
            0xD07374F0CDF5C0B6ULL, 0x30F2C183B478C92EULL, 0xD87107E97D582614ULL, 0x72D3468D0085C593ULL, 
            0x13E4FD5BDE2262B0ULL, 0x550577577E6E89F2ULL, 0x86FBBE5299ED2D4EULL, 0xF0628CE8CAA6E0E6ULL
        },
        {
            0x4CC8AEE9CAC1B9B9ULL, 0x7B3A51CA7A5E5F1CULL, 0xC1FCEAB4AC9C746FULL, 0xA75E750D976E4E5AULL, 
            0xDBF5AE858EB5C333ULL, 0x91FC4DDCA504F3ACULL, 0xDB93B7469A88E679ULL, 0xE6E498A3F6EBC36BULL, 
            0x00F50682C607F064ULL, 0x1374B80F8E459018ULL, 0x05D42836CD28A901ULL, 0x3B289CF66A4A1473ULL, 
            0x4C4CC5885E2F73C5ULL, 0xCA5E716FA901D839ULL, 0x13D61266EAAD9935ULL, 0xE136E8DAF17A3709ULL, 
            0xB000FF8326BB5BD9ULL, 0x323CC08EBEF4AADCULL, 0x9B9DB1056765E261ULL, 0xF7A57F4C454469DCULL, 
            0x3B45735F33880159ULL, 0x896136314BA55111ULL, 0x5C813B2868654221ULL, 0x21A4B40A699CA5E7ULL, 
            0x8F22DE2B52D5C21CULL, 0x9C435899E75117A4ULL, 0x795EE6DCB0E53134ULL, 0x978A374F3ADC3CC4ULL, 
            0x8E004624A4CACCA4ULL, 0x52F4AA1154F5F410ULL, 0x6D9D63E3A9FE4B78ULL, 0x8FECE1CB1294628FULL
        }
    },
    {
        {
            0xB1AB006276F51B56ULL, 0x38393CEB07E4C3CFULL, 0x093463CB7AEBDB8AULL, 0xB13FB90C3CEB7106ULL, 
            0xDA98D5B38D31F5CCULL, 0xD46AAB853D5C95A4ULL, 0x25E3B00AC4CDA506ULL, 0x050769ADFFAD7C3CULL, 
            0x66514DE330B6DEA3ULL, 0xC762EB42842C648EULL, 0x959415195E370C59ULL, 0x07B57095319AB0E3ULL, 
            0xE1BE8707BCD8959EULL, 0x0F9204DF0ADD3D8AULL, 0x9D4BF192C7D1A3A6ULL, 0xCC529B3D26DD0290ULL, 
            0xAFC4F238711320E0ULL, 0x36366205843AD032ULL, 0x407AAE03E7302A29ULL, 0xE7EDDD809DD3E93CULL, 
            0xDBA042D1F0D778BBULL, 0x6C4E8D9D3CFFF395ULL, 0xD53AA1A98DD691E2ULL, 0x1C1D7D78C2B15C67ULL, 
            0x3A5A71EA92E4642FULL, 0x01E4380A3224BC25ULL, 0x67D4FCF372F34202ULL, 0xABFACA9E8C823633ULL, 
            0x149DCEEB47DF2E1EULL, 0x44D27CB9416120FCULL, 0x28707C94F878621FULL, 0xDEB727BE77826766ULL
        },
        {
            0x660FC1E2354718ECULL, 0xC8DD5F1083719510ULL, 0x450F2CDD9C2079A8ULL, 0xFB2B3BC7374BAA06ULL, 
            0xE891F31DD375820BULL, 0x6F6B2CED39889EC3ULL, 0x2ABE3570B0EAFD30ULL, 0xFA7A232773D344ECULL, 
            0x9B7D032E3C4A8FD2ULL, 0xA4EDE4E26F94A643ULL, 0xB668382D12AB9575ULL, 0x8270D27D7E3A0C5BULL, 
            0xD3F030551BEDA7BBULL, 0x3590829E4B3F0A15ULL, 0x0D17A8215F0AA93FULL, 0xCEE6AF842ED51FB5ULL, 
            0x28C7FA1908886BE9ULL, 0xD06F31DB08E91ACDULL, 0x57F0391AED5EA5F4ULL, 0xB073DBF651B0C06FULL, 
            0xE544C151A2E79C2BULL, 0xE1AF3148112248EBULL, 0xB4B444CFE0168E76ULL, 0x70EC825B71DB4C6CULL, 
            0x9AB70AE3C548866DULL, 0xDA274A0243DB4F93ULL, 0x2D6389DE11E85954ULL, 0x9B2F06A846706E4BULL, 
            0x73B3CB3DFD80ADCEULL, 0x1D4F3DE412D54DAAULL, 0x8FC8B7DDA3A94B24ULL, 0x1C3477FFAB77EFC4ULL
        },
        {
            0xF169C2F4304FC268ULL, 0xCA1A5DFE1D7BBC6EULL, 0x1AF103C6A72B027CULL, 0x39D9E2409F4FDF45ULL, 
            0x3B379E302F7B9B32ULL, 0xAFC1D40433E1D96AULL, 0x094DB5C40AD53B80ULL, 0x0AD49DCFD846AAE7ULL, 
            0xB4AFB9A955B2D9BBULL, 0x3CC47D916E649932ULL, 0x19B0C00EF7B47F7EULL, 0x171A12627595AB10ULL, 
            0xF90F2AEFDD4CF85DULL, 0x907E93FB711937A0ULL, 0x728F7DA07DD032D3ULL, 0x83DA3A613BEEC576ULL, 
            0xB550944E9CC6E58CULL, 0x6D3EAA563C7DF23DULL, 0xF4711E7117FDF4C6ULL, 0x157F246EFAE36EE3ULL, 
            0x6A5FA2D90DD843F6ULL, 0xB1EC9A5973836217ULL, 0xF45226597A6F783BULL, 0x04BE5869F5B78E35ULL, 
            0x9280650F7119B32CULL, 0x54043FD1FD01AB72ULL, 0xF11FF1A436467E83ULL, 0x422F2E5302FFAB42ULL, 
            0x034AA0CA9F21C7BCULL, 0x758507B9A209AEFCULL, 0xE8367969815412CFULL, 0xF1049ACFE502E74DULL
        },
        {
            0xF3AB93800F147737ULL, 0x92FAC2F04A32A27FULL, 0x2D4AEA4256DE0E84ULL, 0xA1CB667962724B13ULL, 
            0x13EF9842B87A3E64ULL, 0xF50B91DE753808F8ULL, 0x1A1D88C9CA63D709ULL, 0x0FF221B5C9E8A6FBULL, 
            0xCB0A4ADC0A5A206BULL, 0x40A404035708AB31ULL, 0x19DFDBA511EE4E46ULL, 0x4983FD577AB7F019ULL, 
            0xB584CC41D90732C5ULL, 0x79651B5E448F9C67ULL, 0x730AD906AE988B76ULL, 0x37EB47EC1EAA8D2FULL, 
            0xF769E5630C6962C2ULL, 0xF857C413A9FCF1E5ULL, 0x4DDDBCE7224D3931ULL, 0x648CE4F86320C8ECULL, 
            0xF82A126A26974FE7ULL, 0x80EEC90C6AA5BAB1ULL, 0xB1EAEB0F83DA88CAULL, 0xD105D8533A90E3CEULL, 
            0x8DB2707735B8BAD5ULL, 0x188B8373128F2404ULL, 0x6B31A15099E18577ULL, 0x501B891E134B2693ULL, 
            0xAA65EA73E29AF141ULL, 0x021C10C87442C413ULL, 0x82CC386A81A62BB7ULL, 0xF99F25DBF849BAC4ULL
        },
        {
            0x366FB07FBCCDE111ULL, 0xE7E1461408CD84ABULL, 0x1876AFCDACFC5F2CULL, 0xA712818CF19E73A5ULL, 
            0x54A964A8D9F13634ULL, 0xC20F320AB7FC78F8ULL, 0x493751F63486CEE3ULL, 0x7C844CEB45408EEDULL, 
            0x611BF53E8CAF1F05ULL, 0x790104D233637236ULL, 0x4A0F4A6F98B75982ULL, 0xE67CC217E0F60686ULL, 
            0xC698C6705B4F8F60ULL, 0x99461FE9A2DF555EULL, 0x82BD5229DB9F576DULL, 0x2D8F735C0CBA5799ULL, 
            0xF4EDED6F2D67DC00ULL, 0x558DA6429E54941EULL, 0x08BB7D6617799B30ULL, 0x625C7A68E56FE279ULL, 
            0xE6567D67F500AC87ULL, 0x2E44E36ED9720E36ULL, 0x632A065FB230BA99ULL, 0x08C5CC33F7537EA4ULL, 
            0x302A49926B93902BULL, 0xBCA1494EA4A3AF8BULL, 0x398F994B1A43D1EFULL, 0x383ED86AFD373E10ULL, 
            0xB5E1488AF979DB31ULL, 0x87FDE4D6F6B025A9ULL, 0xFA8B1DAEFA09E227ULL, 0xA1A907A094695AA3ULL
        },
        {
            0xBAC61BDCCBAF3382ULL, 0x088BBAABE7D043A6ULL, 0x3728CB5727FAAEC8ULL, 0x5CCEFDF29EAF4AA4ULL, 
            0xBBCFA65843AD1466ULL, 0x77D8781CE541C807ULL, 0x707AF922D4B36038ULL, 0xBEDF2E4C067E9791ULL, 
            0x988C4BEBAC6AA4E2ULL, 0x051B6BE77A9B0361ULL, 0x068F38431EBA3D69ULL, 0x00C876EB40B366CEULL, 
            0x5E65ABA3833E5189ULL, 0x09ECCCAF4926D804ULL, 0x322F0F4E8FA0741AULL, 0x1B76582210EA6362ULL, 
            0xFFF89F20D19352B6ULL, 0xD813BCFEBD52D999ULL, 0xBFBF409B5ED43B46ULL, 0x20B2CF06B8C01D14ULL, 
            0xE7B19F0BDCC5E081ULL, 0x96F82618285CDAA3ULL, 0x3BD106216CB62A0BULL, 0xFA341DDD4C28FE8FULL, 
            0x3BAA4589C8A20B8EULL, 0x8B24F9D922DEEA53ULL, 0x00288272DE5233C9ULL, 0xBFA80DC802C5EDA9ULL, 
            0x89EC9DBBF83E1DCEULL, 0xA82802F378DC2BDAULL, 0xB78A922DA547A7C3ULL, 0x251ECDBE4EAE0168ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mothallah::kPhaseBConstants = {
    0x899A920DDC8747F3ULL,
    0xA0AAC7ECBD2BC9E3ULL,
    0x73EC6EB562BDA57DULL,
    0x899A920DDC8747F3ULL,
    0xA0AAC7ECBD2BC9E3ULL,
    0x73EC6EB562BDA57DULL,
    0xAEC2C4B7DBC01FD9ULL,
    0x1209413A53744E61ULL,
    0xD2,
    0xFA,
    0x3A,
    0x36,
    0x15,
    0x55,
    0xF3,
    0xA9
};

const TwistDomainSaltSet TwistExpander_Mothallah::kPhaseCSalts = {
    {
        {
            0x99EDAEAA8F9282F7ULL, 0xE7435ECD377FA85EULL, 0xBED3BD7F534F88D4ULL, 0x7CF99C6ECEF6EFFDULL, 
            0x58D18A7E7BDC97B3ULL, 0x2C7A5BB47D18F0A7ULL, 0x6A357D48AC2AE3C0ULL, 0x69EA296647C8A55FULL, 
            0x5AC86C731764F346ULL, 0x2A1EAD7D13468DD7ULL, 0xF6230115E3D162ADULL, 0x9ED261EC3DA2469AULL, 
            0x33A292C9716AF324ULL, 0x99220D5A4B3BEEAAULL, 0x9D44C08D1F4BEDC0ULL, 0xA7FCE0419F7A3C45ULL, 
            0xEBC70A0C9E4ACB6AULL, 0x4F9CD278FB86EF9FULL, 0xA2D495636735D17CULL, 0xD63D9F0EA9609869ULL, 
            0x8CEC9033E8EBC905ULL, 0x8C0C310C518BAC72ULL, 0x6D0058DE4A446DD4ULL, 0x6DAEF012BAB6FEC7ULL, 
            0x963D603495030C73ULL, 0xD57271F3EA263874ULL, 0x0DE5ED07522AD8DDULL, 0x938E7F6E72870898ULL, 
            0x0130C86D4369C275ULL, 0x60E941218B716014ULL, 0x0D1F90433F93A3D3ULL, 0x868F70D1DAB6FF77ULL
        },
        {
            0x168F095AE694D22AULL, 0x7A4DBD01072865CAULL, 0x1B92358186516BDDULL, 0xCEC5E2787FD61320ULL, 
            0x00016F784CCA725FULL, 0x1AC4268F69FB78EDULL, 0x3BC9CEBB24306801ULL, 0xD9FCE66E91386B7DULL, 
            0xF8168536A99BFE12ULL, 0x79A602527B41BD2EULL, 0xB930A0836F4B0A62ULL, 0x0D67AB9A9894BE7FULL, 
            0x6B71EC3EAC42350BULL, 0xA28619052FB9F560ULL, 0x83AC79FA5B5F68A8ULL, 0x3B9B72B3D89FF133ULL, 
            0xB3D0713410EAC59BULL, 0x21BEC99D7808CC41ULL, 0xBABE090D5B241FE4ULL, 0xFA9094F75DA33CE3ULL, 
            0xD8B81BB37DDE5526ULL, 0xFC50DFCA6A5B4B82ULL, 0xF00FA3EF6A2BFA31ULL, 0xEABEF17CA3371E50ULL, 
            0x6619DAC051BD8A5AULL, 0xF692896B40A92F50ULL, 0x793D1D6F4E47F41BULL, 0x66288894EF97D74FULL, 
            0x2614CD7533325DB9ULL, 0x4047250E241A30E1ULL, 0x0294D2488A133AE9ULL, 0x62D2D960DE762DD1ULL
        },
        {
            0xCEC889986172F53BULL, 0x6183522738F3A1C6ULL, 0x142270892A6FF3FCULL, 0x0BA0730CD92CBF84ULL, 
            0xE2933C931930AEBFULL, 0x7D727BFAF87F2B8DULL, 0x5E60F1C25F83468CULL, 0xAC64ADDA9FA7E1AEULL, 
            0x47833F3F2D1A25A3ULL, 0xD29938AB13AE311AULL, 0x7F1AEE59696FD141ULL, 0x47CFC146E6DE1E63ULL, 
            0x5937283C6F444391ULL, 0xA731D5BFE470AF7FULL, 0x615AAF44FD6EE20CULL, 0x950A2B6DE2CC955BULL, 
            0xA9E1B76F800D89A4ULL, 0x04C7ABE0CA254288ULL, 0x643003A265370D45ULL, 0x2339210782790856ULL, 
            0x118B22699AA01A16ULL, 0x8050983759109786ULL, 0x84409A2FBE659C73ULL, 0x0A017FFCDB81CF52ULL, 
            0x83643DAA2DFCADF4ULL, 0x2DF06CB6643D96B1ULL, 0xA082F32EA27D642FULL, 0xCAB81096AE1AE790ULL, 
            0x0FF7D903710DDF31ULL, 0xD3853E20C49832A4ULL, 0x607174FBEFB974A6ULL, 0xC17B64517054D594ULL
        },
        {
            0x0C4B6686B845BE18ULL, 0xCB92E4F3CD0F6001ULL, 0x8491C70DBC57A604ULL, 0x85CC617099DA795DULL, 
            0x3B4575E48380E8C0ULL, 0x8D4F14174D0911C0ULL, 0x133853502AAD9960ULL, 0x3355D08CCDCD0F53ULL, 
            0xDB66D9C9261B71C3ULL, 0xCAD781CD509988A9ULL, 0xFA31A2E7F48705EAULL, 0x33F2BF7DB0FA9FE1ULL, 
            0x620CB2A8551A277FULL, 0xB0B651EF6C41C25AULL, 0xE108501707B55A80ULL, 0xDEA40D509ADFA917ULL, 
            0xBA9F873B55201CD6ULL, 0x263FD1DE727DC7E1ULL, 0x19573DC53B1CC5CAULL, 0x3F63BC2F85A0A457ULL, 
            0xF5C0E9189BD1C307ULL, 0x96897C8F38FE70BAULL, 0x5A753BFBC8318D44ULL, 0x7F9FC792793915B2ULL, 
            0x31675802991C451DULL, 0xD96D6D0681BEF05CULL, 0x58CDE0992452C3B6ULL, 0xE57A6D7213DB1DDBULL, 
            0x44A6EC61B0612845ULL, 0xDFF50C03BF6ED973ULL, 0xA902DBC186C9BF64ULL, 0xF8986F5CA9D08046ULL
        },
        {
            0xFE0511D5BFB1969AULL, 0xB157DA849C37EE33ULL, 0x1B5BC41D9B7DCA06ULL, 0xF81D892DB3FBFA50ULL, 
            0xA7971B91950D8BC6ULL, 0x215EE4FCE4D42E38ULL, 0x4E2685584C656792ULL, 0xABC4118A09EA53C4ULL, 
            0x17236FCDA6DD05B1ULL, 0xDF2B4BD2F3CB8661ULL, 0x122D1586BC93710FULL, 0x8365FFAE258F25BDULL, 
            0x1404482C319A78D7ULL, 0xB5C8E3CC434DEE64ULL, 0x42F300618C326470ULL, 0x267EFB165C4499E1ULL, 
            0xF970AA072E21B197ULL, 0x6AC9DFDE46DA234FULL, 0xC2CA31FAE3E84861ULL, 0x1A02C5110DAEE4E2ULL, 
            0x2E0DA99D3AD6E2EBULL, 0x91A89BE1C8B4A2C7ULL, 0x5DBAC339B86B4790ULL, 0x10C4C804ED95F1BFULL, 
            0x52059593D5E8AF65ULL, 0xF99BF50A341AE805ULL, 0xB2E6437DE4780B2EULL, 0x96C8F0734722033CULL, 
            0xC72D68DB48DBBBCAULL, 0x4EB74450D4CD015CULL, 0x8D288E625060F828ULL, 0xE956623598D9565EULL
        },
        {
            0x364B4A1B22EED814ULL, 0x0A67B42C797B9EE8ULL, 0xC7E17CA9577FEA76ULL, 0x3FB4EB2FE6B51B6EULL, 
            0x4EBD17B934BAD3E2ULL, 0xFFC5FE2307505A2EULL, 0x613F49C5D84B924AULL, 0x464C28CE53A7A465ULL, 
            0xB02E36C4583B35E9ULL, 0x22EBE71FAFD7EB76ULL, 0x20C6BC78AC877CADULL, 0x1858B37980E9EEC2ULL, 
            0x307227D64B9F2C68ULL, 0x26B93A295DBB7B86ULL, 0x20A668607AD8ACBBULL, 0x7A42D8F234A87438ULL, 
            0x13949D000B4E4DD8ULL, 0xF044F6CD0AE5BF36ULL, 0x737EE7F53D36053CULL, 0x3883D8D03E8576B5ULL, 
            0x80E6574CB8B3819FULL, 0x6564FAE7ED7BBAB6ULL, 0xC8A442CF7EBD73A9ULL, 0xE787B0EBA0BDC6CBULL, 
            0x2B3290F95A130F0DULL, 0x04EB4F3A815FEE71ULL, 0x710E604CBB9B9761ULL, 0xA416CF9952A8F784ULL, 
            0x43959DC6F772312FULL, 0x0C56831D61677417ULL, 0x8368EDC1534D1D9CULL, 0xF6C4BD8031D0055DULL
        }
    },
    {
        {
            0xE7A379383E4D3724ULL, 0xEDC3FA19F688E7FCULL, 0x80EB79D5E4CC75EAULL, 0x20095B59CE8F95E6ULL, 
            0xD985F25B63EFE60DULL, 0x3B78F4A7E4354FB4ULL, 0xC1BD40CEA212BB50ULL, 0x49624B381E255F0AULL, 
            0x7E883193FA0F617DULL, 0x818CF25C2E2CEC3FULL, 0xAC148178387B2840ULL, 0xC959C183F21CC64FULL, 
            0x76F94433713F3F42ULL, 0x8F883527BACCEE6EULL, 0x4F1D34D564112561ULL, 0xA5D5DA64FB0AF527ULL, 
            0xDD5B7A7937D8D605ULL, 0x118C1FDF01018B9DULL, 0xE0B1815097CE1530ULL, 0x285CF5D9D0144509ULL, 
            0x929086052AF3583DULL, 0xC402C07306144EDEULL, 0xA9E9081FF1E477C5ULL, 0xE6DD78823778E7D4ULL, 
            0x6EB0D0ECE1A83CCFULL, 0xA41272F417797DDAULL, 0x28872DC9EB5B20A3ULL, 0x2EC65404CB5CCEC3ULL, 
            0x522CFF8A3B592821ULL, 0x7066428CCDB91418ULL, 0x102F2AF1E20BE044ULL, 0x634C5B96E13EFF0BULL
        },
        {
            0x569ABB259E8A3D12ULL, 0xC72378369DBA2461ULL, 0x24AEE5D3D8FC219DULL, 0xF0B92CD4FBFFFFC8ULL, 
            0xED9C7DE508475E4AULL, 0xAD484C8CB8AF8D77ULL, 0x373071B5A72DF3F2ULL, 0x07CC2DE3BF3940A2ULL, 
            0xA8778BE7CDA05405ULL, 0xD83E9E12F0BB2927ULL, 0x34E5C2994A4BAE40ULL, 0xB9F38689107CEF85ULL, 
            0xD468144AEB88AF16ULL, 0xE862B9C105F767CBULL, 0x43EF7EF7A871094AULL, 0x49D9CE407EE4C0C7ULL, 
            0x400F6754E246C71CULL, 0xFBC107915EDADECDULL, 0x3A3297733B678D7FULL, 0x37EDFBF809E0F9DEULL, 
            0x368B401994E07B94ULL, 0x63C5245865844191ULL, 0xA5813BEE54AD32C4ULL, 0x98AA12ABB5DAEFF5ULL, 
            0xDE4E504C47697C99ULL, 0x6FB5C51891113742ULL, 0xAE753220B596B326ULL, 0x94CD39CC028EF3EFULL, 
            0x5AB59D11C048CE4AULL, 0x2083242944EF6C89ULL, 0x94D810BAFA11CCD3ULL, 0x43B18817216A5EACULL
        },
        {
            0x13D17B728D281758ULL, 0x98BB663C604CEAFFULL, 0x615523B6DBDBA87AULL, 0x5F59FDB22BB00B44ULL, 
            0xFAFE693027830CE8ULL, 0x8214EAE24AC9ABDEULL, 0x1E0DAA4278E1C558ULL, 0x44FBE398284A90DAULL, 
            0x9C007EF3BDA55E0EULL, 0xF362DA930E4AAD61ULL, 0xCCE0B6EEF9442554ULL, 0xDBBD2FEBE2959036ULL, 
            0x00CA5C9B9F825F84ULL, 0x7306A51BC1AC4895ULL, 0x322C027566580DB6ULL, 0x37F69E6C043C69F8ULL, 
            0x30B5BBD335DB1038ULL, 0xE399455ED60F93E8ULL, 0x63F369CCCDFE079AULL, 0x831AE1237DE87EF8ULL, 
            0x0C094160AB3C33DCULL, 0x850FB5EDA4CC014FULL, 0xA40991164D1C5F0EULL, 0x22544ED3A67FA496ULL, 
            0x4817BB4E8CA72D99ULL, 0x7154871649AAA081ULL, 0x82F14633E6E370BEULL, 0x821183FE257B2C83ULL, 
            0xD987C365A625D7A8ULL, 0x0F78BA452C6D263AULL, 0x17D766AEB66FA852ULL, 0xD746E7C0E382B22EULL
        },
        {
            0x20F6B7E350DBC5F1ULL, 0xD375B0B1360987CBULL, 0x568680145CF90357ULL, 0xB7CBE30ECD149C3AULL, 
            0x161FE63C0596EB79ULL, 0x61E8ADBB01BF752BULL, 0xB57149C69132F180ULL, 0x9B907845329E4977ULL, 
            0xAF65E179321DE31AULL, 0xC6EB3790298917AAULL, 0x2E7A382E81C1509AULL, 0x6F2F2D29470232C0ULL, 
            0x38273921859605EDULL, 0x59B53C692D45ECB6ULL, 0x8C75B24196C971EFULL, 0x144C42F685256208ULL, 
            0x9B19A7C5668B54F3ULL, 0x4321BCC634A2E09CULL, 0x19C3D7C8D1D41600ULL, 0xE7C1D5A10081254FULL, 
            0xA18D88100B82311AULL, 0xB44C7E586B329232ULL, 0x31933956084D0002ULL, 0x293D590F72FE3C5CULL, 
            0xDE9624A4CE449399ULL, 0xC792375A4DA92ED2ULL, 0xECCDDE3976A8E247ULL, 0xDBE384C1DBF53BB8ULL, 
            0x4AAAD47A2551F1DAULL, 0x66365DB7009CEC1CULL, 0x0445D2A58999B93CULL, 0xA546C8F84CD39B08ULL
        },
        {
            0xD635BEEF0A060CA0ULL, 0x21514BD4FEA89553ULL, 0xAB248F7DBD681E5AULL, 0x828ABB263F6D3A16ULL, 
            0xA387C6763D7B29F9ULL, 0x09E5137EC8B4B2FBULL, 0xCFEA899EE5E036B4ULL, 0x40EAAB0DE1B135D8ULL, 
            0x0A8D9ED60E1F4ADEULL, 0xF974D8B1D1101A3EULL, 0x8A68F4EB5A5D0A3EULL, 0x3948BFA4B631F4ECULL, 
            0x6E7B1B240D0F7A25ULL, 0x0FC31D0978FC8DC3ULL, 0x63264EA6C771E656ULL, 0xBB7B2CC867F7B026ULL, 
            0x262B8E25C77500F5ULL, 0x0B966476CF444BCCULL, 0xB22804A834F5B788ULL, 0xCC8A12DF1613EC5BULL, 
            0x5F5AB8F6BCABDA9AULL, 0xC55458852E032FB7ULL, 0x5F6171662834FBF3ULL, 0x5E944BBCE1857A4EULL, 
            0xA3731B2EC8F422DAULL, 0x19EBC696C517591FULL, 0x83D1DB15965A471CULL, 0x2F37A45E0C9181C5ULL, 
            0x42F7C34DC8FEFDD9ULL, 0x2E3FDA6EAB848EF0ULL, 0x6E1C0FF249A9804AULL, 0x5F1EC573BF0C1EE3ULL
        },
        {
            0x1734D2C983C9FB5FULL, 0xCEDF6EE1431C60BCULL, 0xCE171FDF8E32DCA1ULL, 0x84651A9993916C64ULL, 
            0x6A590382B3F43DBEULL, 0x47FFAC9A8435FB61ULL, 0xE2D9073FBF3E256EULL, 0x00CE16F625D47463ULL, 
            0x23C8830FD29065C2ULL, 0x8ACB23EEB51AF73CULL, 0xD831DCA7D4BA8717ULL, 0x81E3876D65CD6EADULL, 
            0x2D757FB1C5ABBC53ULL, 0xED098E648E83DC36ULL, 0x714ED738851D611EULL, 0x338F90F4F9759C3CULL, 
            0x236E940E5BCA93C7ULL, 0x74A27887684665EDULL, 0x24CD8F261B082688ULL, 0x9BACC80451E532CFULL, 
            0xF117841EB3EF1655ULL, 0xD2BAB4264CA0518AULL, 0x982482AB0CDF8A2FULL, 0xBAD55C9B645AABE9ULL, 
            0x383529F3C1C1CC42ULL, 0xBFBE3F6D59244A0DULL, 0xA3B98BC25DD1E7F0ULL, 0xC592EBDFF3072037ULL, 
            0xED2E02AFA17909A6ULL, 0x1BF4F2CF66030146ULL, 0xADE8701D76DF0221ULL, 0xD73AA670C9B175BAULL
        }
    },
    {
        {
            0xE974288CE29E5A4AULL, 0xCA57E675D3FBF492ULL, 0x3931F2CA650CFD46ULL, 0x3DE89AC3F4A01743ULL, 
            0xE14F4EA269DF6495ULL, 0x0D57946EB69EE34EULL, 0x808ECB8BBC1AB45EULL, 0x4AE65C73C6A48CC7ULL, 
            0xA95BDE9BF27C409AULL, 0x39576DB9FB7327FDULL, 0x7D109E833C719CDFULL, 0xED3E939F121402EBULL, 
            0x1FEC92F87E1087C2ULL, 0x831FD5459B363290ULL, 0x86EEA6C8CE6B37C4ULL, 0x0FDE9D3DC62D110CULL, 
            0xF7FC5151F1A3BE35ULL, 0xC07641546175FBE1ULL, 0x72158DF9A547AABCULL, 0x77766E5C3CDCFFA5ULL, 
            0xDFEC1378E3B6B66EULL, 0x2FD10B2F4C9D74D3ULL, 0x2AD28D455B5C14FDULL, 0x6C2F226425084782ULL, 
            0xF5F9B9AAC5F793A7ULL, 0xF23794EE122667DFULL, 0xA082ADB89657475DULL, 0x8373183122635CCCULL, 
            0xCD0B7BC9B10BDB61ULL, 0xF676FFE3EF5ECCDDULL, 0xB3D37C7EDBB867D2ULL, 0x51B13577DCE4316EULL
        },
        {
            0x7E9834645EBF9AE6ULL, 0xD4858AC58DEE0ABEULL, 0x033C57EB8A1E6161ULL, 0x635005513EB5EB6EULL, 
            0x220992DA16AAC318ULL, 0x2A135D01DD8EACD2ULL, 0x0BA39DD7114E3043ULL, 0xE9598B63BD64D0D6ULL, 
            0xDCD0A3D96238CA47ULL, 0x0F608DFB78C57915ULL, 0x5C873D77F97ADE0DULL, 0x86C55A094B4C68BAULL, 
            0xA70513F2F3D220C1ULL, 0x41CA8BB105A3F89FULL, 0x83488D73BCF4D0D1ULL, 0x06B2C695D8145819ULL, 
            0x75C1FB3FDAD3828FULL, 0x932C877043958993ULL, 0x057C1C237EF85111ULL, 0xBEE1B43B58D4E51DULL, 
            0x6DFBE6FF0F1A5B69ULL, 0x5E5F9652DC772351ULL, 0x38EB203FB215B9ADULL, 0xD8C5E5CF557B5B3FULL, 
            0x0C209B7AB290394EULL, 0x24E2FCFFCE31419CULL, 0xE4AFD254CFE21DEDULL, 0xC9800ECDEA62B26CULL, 
            0x61EFB2A04CA3B4AAULL, 0xCAF3CE05420E75B8ULL, 0xDEE40C226511F6D7ULL, 0x321414FB1D8E165BULL
        },
        {
            0x37C52A933170BB0EULL, 0x88201EC96CB91DFEULL, 0xC23C88AA355FBAA8ULL, 0x776896EBDF412FF0ULL, 
            0x957361C12BF0B012ULL, 0xACA174F6CB39C2D2ULL, 0xAE118EBB32FF9D76ULL, 0x73BA6AD6878AA0C2ULL, 
            0x1C0EEB91093E0284ULL, 0x585594DC7D36D762ULL, 0x2545C01A4EB1610FULL, 0x4D6EC295A0B83D41ULL, 
            0xAD1EBF00EF331EAEULL, 0xE8772ACF315C373DULL, 0xBCA6D8073ADEC967ULL, 0x42A2C37F74F42501ULL, 
            0x61F165C34FACEA6CULL, 0xE660C24DA6979984ULL, 0xC442C188446CD0D9ULL, 0xFAFDE1B0EB0C5EF7ULL, 
            0xF5D6B98C8BD7CA4AULL, 0x3359F1CE69470255ULL, 0x5E52668B5BC52720ULL, 0xCDDF4C2D37250E81ULL, 
            0x5388F6DB69B876F1ULL, 0xB5A0C12C14AF2716ULL, 0x8FED2E7134BB9C7FULL, 0xFCDD8A41123B0F99ULL, 
            0x92600548FEC5C2F7ULL, 0x23E4B64BA924D446ULL, 0xDFDED106652542FEULL, 0x4BCD1E1881CD23ABULL
        },
        {
            0x92FA1ACD7F99088AULL, 0x98C0CD953C152DDBULL, 0xEACB3672830E1A34ULL, 0x4563B67CD1D658B5ULL, 
            0x80E99A623FC63A05ULL, 0x84A73EED094DA979ULL, 0x4131C30FBE40A11AULL, 0xDAAAF7D6EA4108CAULL, 
            0xF6139A1BB4F222CDULL, 0x79A77F8C99E04D40ULL, 0x93C98B37D22AAF29ULL, 0x1894A373F3CC56D5ULL, 
            0x4882E4588E2D8867ULL, 0x203493E9F9FDE2FFULL, 0x11947BF219647652ULL, 0x2B2B06737676181AULL, 
            0x50D96ABAE1E3B356ULL, 0x9FDF597D7F01FF09ULL, 0xF3D41D2DD5964054ULL, 0x64C471696DD203A5ULL, 
            0xBE8B83809ABB938AULL, 0xCAABCFE47BEC38EDULL, 0x53F9CF60A9B23AEEULL, 0x80294C1B3A62164FULL, 
            0x18B5F4C9B4DA7E33ULL, 0x26B6CDF34A65BD83ULL, 0x4A13EDFC59606EFEULL, 0x078E010E03798D7DULL, 
            0x4B5BEF4745153B0BULL, 0x7A9907FE3B5A77DFULL, 0xFF86D43D5D191B73ULL, 0x3D4756D942391AE6ULL
        },
        {
            0xCE72C90274F9956CULL, 0xC05725B9EE3449C4ULL, 0xD28532F31E66DDEBULL, 0x29583C63A22EB45EULL, 
            0xA8C455779382A5AEULL, 0xD51589A23DD8AFB9ULL, 0x64A108A84397B880ULL, 0x70A641075A352385ULL, 
            0xFC599A848524B6D0ULL, 0x854018368588513BULL, 0xABCDEC6E12AFD7B5ULL, 0xE963C6AE39CCF459ULL, 
            0xBFBB205D66645258ULL, 0x784754D9F46196E0ULL, 0x5DFFDECBCBDDBB58ULL, 0xCB318FF4960E0578ULL, 
            0xCC6B5D305E1B6026ULL, 0xEBAB6DCF79C1266FULL, 0xB0A147C995147ED5ULL, 0xC7F69FB6C48D1D7DULL, 
            0x42FAA2B5C2B8FBE4ULL, 0x9DE2B42F18E9B52FULL, 0x7DDF8F9DD61A3D7FULL, 0x20C312C6E72C1719ULL, 
            0xC5FC0FD85BD265DCULL, 0xB4B3A032D6F7FF83ULL, 0xFE6447942101BB78ULL, 0x7421A9363EBBCCADULL, 
            0x7EE7F083902B4233ULL, 0x5F0FD68C0B0D6E11ULL, 0xFC35644A7D80BA7EULL, 0x7DA2E99EA436CC32ULL
        },
        {
            0xA928815EECE9C8F5ULL, 0x274F208A6881A2F6ULL, 0x58201C8DE7BE66D3ULL, 0x67789F2B7540E339ULL, 
            0xC8BBE399E08FD91DULL, 0xCF0ED8A5EFB0E921ULL, 0xEDE3D621E3B24620ULL, 0xFDEA940F9890A262ULL, 
            0x212621CA421B519FULL, 0xFE74D73E99F317D1ULL, 0x30B103681960FAF1ULL, 0xDBE6D2A653BCC8C0ULL, 
            0x53C779FAD07A2819ULL, 0xBD9D2EF71D52A522ULL, 0xF9E9517C0FDCCCA6ULL, 0x3FD548C959FAE27DULL, 
            0x6BE3B9C81A6C031AULL, 0x1D7A6143416FD2A3ULL, 0xE05EEE87CE539900ULL, 0x3478447A217F440FULL, 
            0x6D8F15E9E39E8709ULL, 0x19E726022A84F016ULL, 0x77917F85C6EB989BULL, 0x3BA5051E2B60E762ULL, 
            0x6402B7631FCBC961ULL, 0x562873F23FA8453CULL, 0x8EE5ECE2EFB421A9ULL, 0x0852647FDE636E09ULL, 
            0xFD5DA47586E070E0ULL, 0x41E15325D09ED470ULL, 0x02DBC1F8ECC71881ULL, 0xC32A3AF03A6D7261ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mothallah::kPhaseCConstants = {
    0x0249FD22FEB7AF13ULL,
    0x2F9D96D5F79D5749ULL,
    0xD1E29022F29CDBB9ULL,
    0x0249FD22FEB7AF13ULL,
    0x2F9D96D5F79D5749ULL,
    0xD1E29022F29CDBB9ULL,
    0x749CE0F41D8EDFA3ULL,
    0xA1BE0227DB19D017ULL,
    0xF9,
    0x3A,
    0x5F,
    0x4D,
    0xE3,
    0x60,
    0x42,
    0x11
};

const TwistDomainSaltSet TwistExpander_Mothallah::kPhaseDSalts = {
    {
        {
            0x4AEF0B97EAE65940ULL, 0x4DDEBD56186C0F8EULL, 0xDDD7C93693BC233DULL, 0x44D181CC7A9E2339ULL, 
            0x1C8FB779BD68E649ULL, 0x5538329172338657ULL, 0xF5A63F35FDB1F2F2ULL, 0x19586DF3820FC433ULL, 
            0xC754412184B5CE94ULL, 0x2B93A6FAD695AFEFULL, 0xF6C0B7769A5FB3F2ULL, 0x1FE506DBC12C7B70ULL, 
            0x543A968A3640B97FULL, 0xD467C1569CA7426FULL, 0x68F33701F5263384ULL, 0xB86D278139FD5249ULL, 
            0x5B4ABBA0267F3687ULL, 0x9EF61152935B5964ULL, 0xFBB798468B5E41F8ULL, 0x36D056B7C40401FBULL, 
            0x88D7D6C83C8BD7BFULL, 0xC5419596F5C24958ULL, 0x08954D1AD0D1993BULL, 0x9109CA2BD501B60EULL, 
            0xB57603F297354E46ULL, 0xD4791FB4BAEB326DULL, 0x62F2B69ECF55C938ULL, 0x1CAE5F35BFA106AFULL, 
            0x933342E0CB05F378ULL, 0x4908D465581C3EF0ULL, 0x61995A0F3D5C0793ULL, 0xB1596E3631F7328DULL
        },
        {
            0xFB8A2E44BDB16E4BULL, 0x92A11B859867C324ULL, 0x2C87B3CA7E71336AULL, 0x3CF08C475B9E4003ULL, 
            0xFE84194303FD3571ULL, 0x14E5898555534B66ULL, 0x3DEFDF53564D48B8ULL, 0xFF014511F9CE8B66ULL, 
            0x49749B0646A27450ULL, 0x5DF61DF9FD92A01FULL, 0x9D8F67FB9F4C740EULL, 0xB28BE1516CD5D095ULL, 
            0x90825661E5169007ULL, 0x274A40782D96B1D2ULL, 0xB268CA9C155EF161ULL, 0x04C228A3D0FE2851ULL, 
            0xCB32A07D72E7DEF5ULL, 0x9C0542ACD3EA435EULL, 0xBA28ACB6E12B3D23ULL, 0xEA78585ADBD3FC42ULL, 
            0x41C31872FC022209ULL, 0x5443DCFFFC95A960ULL, 0xDC3DE5F4847A5640ULL, 0x813DB58980985B8EULL, 
            0x3D9D3232257C1B98ULL, 0xC779D54D462F4B6FULL, 0x7F2A220F9E90D81AULL, 0xDAE51E37B497FEE7ULL, 
            0x5CB7772383864C3CULL, 0x9F2E51E501A316AEULL, 0xE73143033354B76CULL, 0x0D14C4355627C245ULL
        },
        {
            0x7236D7CAADA66230ULL, 0xDC2C255F0A7D9245ULL, 0x63599E096ACF9613ULL, 0xE7CF765DAFF7089BULL, 
            0x4449ACDE01A2CBD4ULL, 0x25D38F21EA881823ULL, 0xE0CB25120B6F3248ULL, 0x1713A5E3F0F135E7ULL, 
            0x75D065501FC37BC1ULL, 0x673E318242B967A1ULL, 0x0B3EC98048026F24ULL, 0x74B142DF5DECF2F2ULL, 
            0xB091900C16768F88ULL, 0x747182A41D80476BULL, 0x42080F2EC3AF4B8CULL, 0x183B935C16DBF066ULL, 
            0x5BAD4033DE92A929ULL, 0x42294757B9224060ULL, 0xB3F7E1610D4D957DULL, 0x32C97D87F27D62B5ULL, 
            0x9EFB1606101CF5F9ULL, 0x724C1A2A7003AE5EULL, 0x214586E8B2CAF22CULL, 0xE4F89B2C1E085A72ULL, 
            0x703C0825BB796625ULL, 0xE8675FB83B7937AEULL, 0x3D01C73ADCA50A34ULL, 0x0B15D31C65DF74AFULL, 
            0xA5A1D8884A655131ULL, 0xBA4EEDB07FD41362ULL, 0x8873F90BB79458CEULL, 0xDE434A7DBB943F25ULL
        },
        {
            0x3C47F0411E2E969BULL, 0x0AC84C91E28D2560ULL, 0x55112B498DA228CFULL, 0xFC984D20D49C886EULL, 
            0x5BE51F7FD1DBA18DULL, 0x19B6817C948791DBULL, 0xAFC86B8013C0F1FCULL, 0x770E022B119443B2ULL, 
            0xBE7D7FCC46F577F2ULL, 0xDC6888148918C405ULL, 0x5BB34EF306967078ULL, 0xFEAA979F30D081F4ULL, 
            0xF67984F8777F9A72ULL, 0x887FAD78D03B7808ULL, 0xBF6C20899558A322ULL, 0xD2B6AFFAF8E8473FULL, 
            0x5733F18EABFE5CDBULL, 0xDA811098D4435B24ULL, 0x44E60061E7385129ULL, 0x8EE4B5167EB075E5ULL, 
            0xDF89C0F9F5BC1DAEULL, 0x9418C518BE3D70E3ULL, 0x12E2D612FA3E5AF4ULL, 0x2D9A8839E2F06C83ULL, 
            0xA2174DF53C9A1755ULL, 0xD36613DDDEB3FEE1ULL, 0x0853BB25CC1A5BEEULL, 0xA940D3AEB7A96116ULL, 
            0xB693922D87C6E732ULL, 0x548643CD3DE3EEECULL, 0x5295BC0FD626FBC6ULL, 0x46CB55C0CD064643ULL
        },
        {
            0x3A6599EDFE52D921ULL, 0x3427F33BD9E62072ULL, 0x7D9783E60744E965ULL, 0x8963E3051A70F830ULL, 
            0x0AC8BA939A5DEE37ULL, 0x2FA33A9BDDB5DF60ULL, 0xED4AFACB5753A912ULL, 0x26836C3200086F8BULL, 
            0xB0AF1F7D6DF1582DULL, 0xFA9B065B519009B9ULL, 0x99A2DD08FC7829A2ULL, 0xB286D9D7A9273B1AULL, 
            0x0737C356C483DEEBULL, 0x4565BA75F4355AC4ULL, 0x8E49F7EAE7C01831ULL, 0x1B6AC8C98348EE4DULL, 
            0xA36884488A60E136ULL, 0x3D2FB9A439200FE7ULL, 0xC186CCCF2D022974ULL, 0xDFCE5BBE06B59966ULL, 
            0x46B000A0466E345AULL, 0x355266F1F8BF5657ULL, 0xFAA0B7E5EFE18CD7ULL, 0xE108CB0C863BD9C4ULL, 
            0x546B4BCB10459CCFULL, 0x7E79CC473953A865ULL, 0xCE1068748344A4F9ULL, 0x8F21115DFFC7F28BULL, 
            0xFCA8E7E45C29188FULL, 0xBF2213823FB5B62CULL, 0x2AADC7E4DF0DA945ULL, 0x95D52C512A364FA7ULL
        },
        {
            0xC089E2083EB4BAD0ULL, 0x900939C6A6412ACDULL, 0xF0B56109446881A4ULL, 0xDAEBD5C0BC5FF594ULL, 
            0x4F0D3EC59C3F055CULL, 0x4246B03F29E8C9DCULL, 0x374D8E9D6799EBF8ULL, 0x6978774850EA6B95ULL, 
            0xEBE81493939EAEBBULL, 0x2FA1E75C45F8F09BULL, 0xEFD2B295AD5A588FULL, 0xF180C05C7FDBA3A9ULL, 
            0x7F2C0D46BD400145ULL, 0xD167CB50F5F18D45ULL, 0x58AF7C5421BF3B70ULL, 0x30A44B55DDF159EFULL, 
            0xCBDCA7BA70D33613ULL, 0x09E916D70120D731ULL, 0xBBBC2BB0836A1E84ULL, 0x3130D86F57C63D70ULL, 
            0x5E60E90365DD0709ULL, 0x32DB7ED8E2F788B6ULL, 0x1B7D078B84A423E3ULL, 0x336A35985340C931ULL, 
            0xE2C9DFB058F02BCFULL, 0x3C90EA136414B772ULL, 0x5F9C469449604CFFULL, 0x392917606045215FULL, 
            0xEA05061CB8CF1651ULL, 0x5CB14F49857036CAULL, 0x8BADDE26FA2CEBFFULL, 0xE1DB5AD9CE91FB8AULL
        }
    },
    {
        {
            0xB0DE269B11F7ADDEULL, 0x19C71D186FEB6B89ULL, 0xC7EB7B7FEA8B549EULL, 0x1C98876E1A3A7087ULL, 
            0xCD2176FF92ED4A78ULL, 0x18AC6C05367CD49CULL, 0x33A3EA14F166979AULL, 0x554FEE2F57AE2EBCULL, 
            0xCCEE01F74A931230ULL, 0xE950E79074E11093ULL, 0x85A37B0DF2357D1FULL, 0xE424D5177A4FA7FFULL, 
            0xBF9EC8AB6D6CD15EULL, 0x75347040F40B9BF3ULL, 0xA7ABF94860A3D45CULL, 0x36732F0FDFED2B30ULL, 
            0x5D37A56D3A29B51FULL, 0x7063AA46BA4DB05CULL, 0xA232657EC8EEBEA2ULL, 0xF2042065065D562AULL, 
            0xE9A95417B68556C1ULL, 0x4B836ED7D09B261BULL, 0xE68CCEAC35FC444AULL, 0x2BBB00136E812734ULL, 
            0xCC652C19B4E4EE7CULL, 0x6961DC7F790785DDULL, 0xF86F7775801BE8FDULL, 0xBA4D977317A1C1A1ULL, 
            0x571258260F061E98ULL, 0x0AAB211954148508ULL, 0x4579D651E970455BULL, 0x15B79C80BA3DFAE2ULL
        },
        {
            0x85721927EB4A7082ULL, 0x54DDD843324D8017ULL, 0x90D05AA5A8EBCD68ULL, 0xA83F225E006CD3EFULL, 
            0x3ADC97BE232DF16EULL, 0x82B621C8F30805CEULL, 0xD25CE9ABDC3D620AULL, 0x42E4711D8184D9C4ULL, 
            0x6895D9933CFA0032ULL, 0xE565DA68C93EDDDBULL, 0x2E52A362757BFAA4ULL, 0xC5EE751AA8DACE39ULL, 
            0xAFA02E78CF878EAAULL, 0xC575E5C6B9DEB6DAULL, 0x7A0839715E3E1E7BULL, 0x33ECC4E3CC906D0AULL, 
            0xC77722792E393337ULL, 0x7837E424ECB23BB4ULL, 0x5DF74223300584CAULL, 0x3A3FC700EC56A471ULL, 
            0x9720E2FEFB4E06DAULL, 0x99C70725ACE67C90ULL, 0x7245977D8B2F6472ULL, 0xA5019C905FA131EDULL, 
            0x076B1BEE42922E88ULL, 0x631EC5E1E309CF02ULL, 0xD09F436517A13598ULL, 0xC14045C9FCE5E177ULL, 
            0x9C08F37FE1427790ULL, 0xF52DB101DC3DB986ULL, 0x32DDE7A8100FEB1FULL, 0xC87270C34E2825C8ULL
        },
        {
            0x828CA20B8768C059ULL, 0x4025AFC67FCBB8E4ULL, 0x806FD711396B9145ULL, 0xF68CBEC31412F7ECULL, 
            0xD5C8B84A2254AA14ULL, 0x1E9227B0EC2F148EULL, 0xF333BF078C20A565ULL, 0x8B90256076489A33ULL, 
            0x72E39AD98496ED2EULL, 0xBBE1780E1AFA0987ULL, 0x5C98E75357946EDDULL, 0xF8274FCB4815633EULL, 
            0x80EA872AD854218FULL, 0x71B04AF7F60DAEF1ULL, 0x80497CD2F5ED47F4ULL, 0x1BFA0E043BCE6377ULL, 
            0x9ED4BDDE8E72C72FULL, 0x19EC8CBB572F68CAULL, 0x4702E0428AB9D40FULL, 0x18B232090116EFFBULL, 
            0x5FBFFDFBA2D65626ULL, 0x881B69BC399F4044ULL, 0xA71CAAC76A66DD98ULL, 0xBDC84295BB34ADEEULL, 
            0x41041A49EE2BD135ULL, 0xEBE990AFC9E1F003ULL, 0x2442BB8A8348C4EBULL, 0x306F6F9566B47AF8ULL, 
            0x0BE40A072D0CB6A8ULL, 0xA2FC51107C69874FULL, 0xEDC6B6B0019CA320ULL, 0x2DBC3FA00D46904DULL
        },
        {
            0xFC9C9A82EB9DCD1AULL, 0xFA3A704199910988ULL, 0x1814C22426B55AD7ULL, 0x76012A10982C76A4ULL, 
            0x1354BAF10E21FA80ULL, 0x350B38B9265AF329ULL, 0xF3A676B2B92BA491ULL, 0xD04B860ECBCD059AULL, 
            0x7BBD6E6B2BD22572ULL, 0x9DE248DF89CC0D46ULL, 0xE891AF86B7D826DBULL, 0x62724F8C35FBF6E9ULL, 
            0x04C0867B81805D3EULL, 0xA972994731B531D3ULL, 0x5A7FCFB628B5F261ULL, 0xD998DBAC271D7AAAULL, 
            0xAD876295F4E7C453ULL, 0xE6076EB3114A90E8ULL, 0xA0CD5FB683F47477ULL, 0x947EDB18B6FF83DFULL, 
            0x5B62A8B7214E32A1ULL, 0x02E177CA777DDF56ULL, 0x574041A2FD5868ACULL, 0xED0C2DD4292AB9C8ULL, 
            0xE200B944B8BCA567ULL, 0x50176298EB3E8C47ULL, 0x6CB3494002266946ULL, 0xDB558DD67CEA0BFEULL, 
            0x1544201B6CA9257CULL, 0x57D9FB1D27D14A64ULL, 0x25598916C7F12E42ULL, 0x117F00AD6677A5F2ULL
        },
        {
            0x3D89ECF2C56EA1E5ULL, 0x4547EDD20AE7DE06ULL, 0xDBDA7B117AE37BA4ULL, 0xB2E6ECDD58F0BA28ULL, 
            0x2BA77B366E77FB9FULL, 0xD3E9D648EF0812CDULL, 0xF2553823E0EC3475ULL, 0x4A674DF83374EA2FULL, 
            0xB08DBBD2F5A3934DULL, 0xF651CBBA310A5F9CULL, 0x1C96690BD6ACC40BULL, 0xAF1540071B6F47BCULL, 
            0xDA76F4E8A0DBB808ULL, 0xB081534F0E780CA8ULL, 0x2A704676537F6CB8ULL, 0xF2EFD054D926F9AFULL, 
            0x9B524DE7B17AC1D5ULL, 0xD232F303FA0A337AULL, 0xA83A5A8EEF79CEAEULL, 0xC12703F512FC87C0ULL, 
            0x74F0C6DCE1807EE2ULL, 0x83270AB9E7A9EAFEULL, 0xD625173C68AA91DAULL, 0xA0D30F969E08E927ULL, 
            0x9793B880FAA98345ULL, 0x607BA5C869EA8E5CULL, 0x04CE03E90CD9DA54ULL, 0xE31F1B0B2F3C9320ULL, 
            0x86805F9AE98A28C8ULL, 0x0195B20307EBC58CULL, 0x7272ADDC52E1068EULL, 0xF8B91386FBAD1CAFULL
        },
        {
            0xA4550A7122EB3904ULL, 0x8D6FE0DED0ABAA0AULL, 0x434FADE9EC4DE911ULL, 0x54283A71C37A412EULL, 
            0xDE388F75296D73A7ULL, 0x97BDDAD3B52D13F9ULL, 0x87D5D07BF9C8D248ULL, 0xB7BD5658D35DAD32ULL, 
            0x1E70B89AB469C750ULL, 0xB045374B01A1B4DDULL, 0xF8ABA06F0E118BFAULL, 0xFB034BB076FD7166ULL, 
            0x65CC67EB16206079ULL, 0x1B84BFD74F06C50DULL, 0xAE4C661B19675FA8ULL, 0xE0BEA72F3DA3A2F4ULL, 
            0x85C6E4D0AB7F23A0ULL, 0xBCAD94DFCAFD1363ULL, 0x6E616E345FC7E3FAULL, 0x69966D461C065613ULL, 
            0xD685EB83539ABD28ULL, 0x53779481578EA9CCULL, 0xC6C0E3660C62F979ULL, 0xF9203ED9CF50915DULL, 
            0x4CE24C41B0007D5BULL, 0xCD6903D9C73D2299ULL, 0xF7230AAAC7B104A6ULL, 0xA58BA978242DA901ULL, 
            0xB005F9596AFC3FC9ULL, 0x31138F8FF1F08E4FULL, 0x67689D7515A8BF51ULL, 0x77BEA37DB2304339ULL
        }
    },
    {
        {
            0xD2ACD271CE4B0E26ULL, 0x057B6FB0629ABD9FULL, 0xF904F22E034B9B8CULL, 0xBDD5B8A9B98FA18EULL, 
            0x4DE08B32F28137BAULL, 0x52CC8ABA00451485ULL, 0x1E57104D902CF2B9ULL, 0x91E5CCFC94719E36ULL, 
            0x433458FBC664D0E2ULL, 0x80787F9D35E742BAULL, 0xA8FBCFC94FD4B1ECULL, 0x689C434A7636F287ULL, 
            0xFA9812BE82E2F9A7ULL, 0xD55A2DE2DE920E31ULL, 0xEBDC290C390DDDF9ULL, 0xE7A3C29FF1CDD4ADULL, 
            0x951315BEA20CBCD5ULL, 0x209BD66F8CF397A2ULL, 0x553C26B2F177A719ULL, 0x77FCD3461ABC9053ULL, 
            0x2FA7A2D4069EDD97ULL, 0xED0984637EC057A3ULL, 0xDD88F2B2A8A46E3EULL, 0xF6A78FA47409C0A9ULL, 
            0xE980989488AD13B7ULL, 0x9F278881AA5CE47FULL, 0x8D7DE176320007E2ULL, 0xF8B47B0404CBFCD6ULL, 
            0x53CBCA5A0424DDDFULL, 0x9F0223AE0B141BAFULL, 0xC2F2D1CAF6882387ULL, 0x8198642D210060B4ULL
        },
        {
            0x11CE2183F0CED2A7ULL, 0xA3577141FB3AC750ULL, 0x1DC4012967605DC8ULL, 0x9A519826079F411BULL, 
            0x578C78C29AE80A85ULL, 0xCA2B5558F318B37DULL, 0x3C6F50E6EA036FD4ULL, 0xAEE3EDEA2D857EEBULL, 
            0x756EB40399763E71ULL, 0xAD9DF001500EA20AULL, 0xE10D4E314731828AULL, 0x0640B39073554E7BULL, 
            0x427D955EC46802D3ULL, 0xF5B68FA365A2F884ULL, 0x93432327C9ACB76AULL, 0xA4B8FAA8011C7574ULL, 
            0x460ED2D72F47DA71ULL, 0x3895F0C2B7A4007AULL, 0x393D1946063C45DBULL, 0xE26894D1C0D700D9ULL, 
            0x6540F912B48E7B77ULL, 0xA3E30C40EAF101A9ULL, 0xBF5C034B6F66E569ULL, 0xEE3473D69D0836B7ULL, 
            0x9CE406FE46B016D8ULL, 0x6434D2F525ED733CULL, 0xB55772EE74D813E0ULL, 0x430F01F5AC06CC8FULL, 
            0x1290F9ED499433FEULL, 0x7B96D76F3B89BF15ULL, 0x64CA98034E6E5296ULL, 0x3A88AFF7BBC4D543ULL
        },
        {
            0x47C4DE6B8D966C38ULL, 0xC08739994A4A51AAULL, 0x14923FCF0A4ED41CULL, 0x9F8774B61CA44B02ULL, 
            0x4BD7C2246B8766D0ULL, 0x16A8DE9B092DCB79ULL, 0x3F3EF37789A26097ULL, 0x05451D755012ACC6ULL, 
            0x450423B02E65FDC8ULL, 0xC04A6865EE6CBA9AULL, 0x8B9E65A4803B6BA7ULL, 0x578D96B7775959B3ULL, 
            0x04444A8B41818C4EULL, 0x40A3DC8A8379194AULL, 0xBF3461D4CB0A9BC8ULL, 0x317B3DCF54A72ABAULL, 
            0x1CD611550FC0A166ULL, 0xF5938E9CCA59BB91ULL, 0xDAFF7E82262DE798ULL, 0x5B046954BE746EE2ULL, 
            0x5C7EB72BE9234327ULL, 0x43F08058C7CBF1E2ULL, 0x285FE8578A3DD1CAULL, 0xD9FD950BB29187FFULL, 
            0x422DBC432AA20C56ULL, 0x71807FCDB45CDF0FULL, 0xABB40718A07DB0A3ULL, 0x9F1520178EB9880FULL, 
            0x71281B78F60CD18EULL, 0x3F31252C3A63C456ULL, 0x4EF29C9498397C48ULL, 0x4D81D65EC28827FDULL
        },
        {
            0x5689E029E72593ACULL, 0x6485E64E939FEE2CULL, 0x1E9017A741E2C825ULL, 0x0043426FDE946FC4ULL, 
            0xE4482C36FD7D4E56ULL, 0xA9A19F1DF2757F90ULL, 0x1AAC8004244B45C7ULL, 0x0128D8FBDC85BB0CULL, 
            0x9F8D6CCACBA36084ULL, 0x71BC4B67DBB2087EULL, 0x9A22A4E8775241BEULL, 0x16A7F1D69842D31EULL, 
            0x84103C03F32FB643ULL, 0x547BB05BE6288AEBULL, 0x7609B7CE0D7C0DC0ULL, 0x6AFD1C512C531E8EULL, 
            0xAECD42EED7F04DA9ULL, 0x4FC22A738C89DB74ULL, 0x6CAA95FB4AACFA5FULL, 0xFAA95A052DD3EFF0ULL, 
            0x4CB5D23C047CC452ULL, 0x605456D8BD5489A3ULL, 0x1A1F8AC9E88297B2ULL, 0xBABFB4199B52FCBEULL, 
            0x5EF6E3B7859BD7ACULL, 0x7AEEE919F5C44EC2ULL, 0x6DD9A3ABE3A042C6ULL, 0x31782C1D494EB1A9ULL, 
            0xAA21B2CD8325690FULL, 0xEB07480A730DCBE3ULL, 0x95C548E400F8A691ULL, 0x72E0034AEA7FEDA0ULL
        },
        {
            0x9A37CA650D41554FULL, 0x7C65C54E05CB044CULL, 0x7A67C99EFA98EE5AULL, 0x3E4B535404E40DCCULL, 
            0x2C51F66CBCBBC100ULL, 0xB621967ABE5D241BULL, 0x35D7413ACC0C92C3ULL, 0x1D245D3D0085A111ULL, 
            0x1E56A38FAF8EAA66ULL, 0x2FB4B344DFA7E60EULL, 0x53D30005D7F985A0ULL, 0xF3BD84A1E5D9669BULL, 
            0xFF5BE4F935C64747ULL, 0x284858B5817365AFULL, 0x84C4552F2C263C4EULL, 0x73787D792E834353ULL, 
            0x4242CD55E5B867ECULL, 0x888DA663436929A3ULL, 0x04481638C1BBC129ULL, 0xB856D7FE40CF4C8CULL, 
            0x00B00106256684DBULL, 0xFC97DC8B7D499546ULL, 0x9353CA6531E101F1ULL, 0x2269AA44E10E545FULL, 
            0x6327B68120B1CC4FULL, 0x5A482AC44BC790B3ULL, 0x6C9B6A95DC73BE2CULL, 0x6CF4F87AAE69D189ULL, 
            0x41FD9F7B5C9B8CC0ULL, 0x2A699A122D771E9FULL, 0x80DFBDEDCABBAA4CULL, 0x94467BE913A55001ULL
        },
        {
            0x7A44C45C32855060ULL, 0x365CC8648F6D1C2BULL, 0x2E13FD0C0554DD11ULL, 0x2029EA80E213EA3DULL, 
            0x4D82AC7B78EC8449ULL, 0x688836A8415697F3ULL, 0xB36152C7DCC3FC64ULL, 0xB248A06420E5D65BULL, 
            0xF749A3C7973F873FULL, 0xEF686FCD9A044C42ULL, 0x9AC2622CDB171DD4ULL, 0xDF63292857857229ULL, 
            0xCE43BA45BDE7A072ULL, 0xFE325AF4B3426A3DULL, 0x859856B51B9C8BC2ULL, 0x6E1F5B58ED669B98ULL, 
            0x3AEE28A157C48AA6ULL, 0x59A306A160D93A46ULL, 0xCE75BAAD686660AAULL, 0xC93AC2D8F8A31A7FULL, 
            0xEF6B30F3DF3C7DC1ULL, 0x3C0B816553B5FFE1ULL, 0x5560C4EB220462D1ULL, 0x5CE5670669DCDC13ULL, 
            0xF9218F71678A434EULL, 0xB86A0C0FA724E2BEULL, 0xC7022FE454D9FADBULL, 0x7230D669FB1B0447ULL, 
            0xF10AA2C02357C3F0ULL, 0x5A2066BC1F1BAC11ULL, 0xA9D88E70C56980B7ULL, 0x5FFF83744D7AA119ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mothallah::kPhaseDConstants = {
    0xD0AC985D86F28DD7ULL,
    0xCD4C6E9E478DA6BAULL,
    0x62056BD06D03464EULL,
    0xD0AC985D86F28DD7ULL,
    0xCD4C6E9E478DA6BAULL,
    0x62056BD06D03464EULL,
    0x774F8FFBE0F3E7E2ULL,
    0x0BE90A3260BD9CD0ULL,
    0x22,
    0x4E,
    0x76,
    0xF0,
    0xFB,
    0x7E,
    0xB6,
    0xB8
};

const TwistDomainSaltSet TwistExpander_Mothallah::kPhaseESalts = {
    {
        {
            0x615BF3A2E65B5A7BULL, 0x247A35463CCBA683ULL, 0xED348FD3AE75D90DULL, 0xA42067D1DA1244F0ULL, 
            0x6B444FCE50B219A9ULL, 0x423EB766E0C2F9A4ULL, 0x11A885F7E119F030ULL, 0x871B3A6AE7B087E9ULL, 
            0xB47E23BA763C1B35ULL, 0xA0DCB3F271886984ULL, 0xC15C43980B3FC42CULL, 0x00D7EA4BC7B01B0AULL, 
            0x81C4169759714BC1ULL, 0xA5BB6C1954B5A679ULL, 0xC6A586B84C7AF7DEULL, 0xC553F87675805258ULL, 
            0x12DF1FA5F06880C2ULL, 0xD919B85A86A8D565ULL, 0x2DDE7F25A64BF1EDULL, 0x6D0244AD898615F4ULL, 
            0x35C5FB139D66B9CEULL, 0x81DDDEFCE283A1BDULL, 0xEAB5CFDA98DD45A0ULL, 0x272613DA45C3CA96ULL, 
            0x6C8E9BB6A923339BULL, 0x07F5E0E9059495EBULL, 0x9C20B6A3EA7A3811ULL, 0xDA9924A68199137CULL, 
            0xD42C6E2989269BE4ULL, 0x2CC7282D78EAE341ULL, 0x7D8BA53BB1492849ULL, 0xE74687778BD539A4ULL
        },
        {
            0x72B829EF4718EA25ULL, 0xAD19DECBE2C5B888ULL, 0xBF9B9FE29A9BF66FULL, 0xDC0EB877732889AEULL, 
            0x6913346E561CE9DBULL, 0x4C5BC9AD4B7708BCULL, 0xEE190A6F76C1A4DBULL, 0x33F2C53F93460CE0ULL, 
            0x0F849A7AF7803168ULL, 0x171A6E70A4772ABEULL, 0xB592A3EAF5EFF1FAULL, 0x7F33702CECC6CA3CULL, 
            0xDC8558077F76E670ULL, 0x4FE7EC5B75FF16FDULL, 0xF461A0534C5951F0ULL, 0x0BAF32F6FAB5B505ULL, 
            0xFB7C52340F854F8AULL, 0x5C92C92DBFAE5DAEULL, 0x379B353F19B3D517ULL, 0x52C0296928045FDAULL, 
            0x1B6E51E9E94B7EE4ULL, 0xB66314033ADFC1EDULL, 0x540779FFF537DCAEULL, 0x13133DD0B7E35F14ULL, 
            0xFBD7BEEA6003370CULL, 0x47E7A42B8CBE5360ULL, 0xC1E209082FE407C5ULL, 0xF2871EA4E2441C5FULL, 
            0x19E6EC3A9EFF4884ULL, 0xB9CC84AD63789D81ULL, 0x7D876AC47FA8F087ULL, 0x0DA95B54AB545EBEULL
        },
        {
            0x3F6A8E5A5774288AULL, 0xDEFE6419A8578F0FULL, 0x7A7554A17971FE7CULL, 0xD7B3922702B67B62ULL, 
            0x985CC1191B8FE62BULL, 0x23403905ECB7E885ULL, 0xB66FC77D6F6E3134ULL, 0x3BD4000117BADB78ULL, 
            0x671B8DBC4D9B5356ULL, 0x7104F16A1E499CE5ULL, 0x48B313C8B38118CCULL, 0xE2414408C18F702AULL, 
            0x7AC3AC985C5B5EC8ULL, 0x72CE3BFE9A60D628ULL, 0x5475B32830617164ULL, 0x6084ABC50E0560D8ULL, 
            0x7151A14A6DDFB775ULL, 0x369A58ACD5D96C6AULL, 0xD1A4CB65CB0D10A3ULL, 0xCA6609AF946AF2BAULL, 
            0x677044BF10FA9E03ULL, 0xE6CDB80F8893AC5BULL, 0x9D4009CFABC304A5ULL, 0x561D9CE1A5383BA3ULL, 
            0x7DC94B3A692517F2ULL, 0xF40E9E3C8AB5233AULL, 0xAFFC44725CFA270AULL, 0x3D24D25B67C1C807ULL, 
            0xAD9926EA2535C688ULL, 0xA940EC14EE124C93ULL, 0x438A1DC6D4FBBE96ULL, 0x565F1C7211756B31ULL
        },
        {
            0x3911909D110B714DULL, 0xA66CDDC7BB944EEEULL, 0x28558A031E95114BULL, 0xBC0B951A27EA227DULL, 
            0xD46CE4358F95FC2FULL, 0x199F7AFFE8C312DAULL, 0x10E47E838348686AULL, 0xAB70B5C8A25D5E7CULL, 
            0xC82DB665E40E1AAAULL, 0x783B9ED0C2B6B1C8ULL, 0x9150B687D273DC1EULL, 0xFC862AA929F1C2F3ULL, 
            0xE652784E91B342DDULL, 0x9C4B02514CE51C05ULL, 0x0512CD5CAD9FE1C9ULL, 0x0D207D3BEFCC43DFULL, 
            0xEE6CDBF06947C00DULL, 0x3B0BC5AB70B99937ULL, 0xA1AC9EEDF270C823ULL, 0xF32ADF616DF1685CULL, 
            0x567F295063730B03ULL, 0xC3AAE72D800069B0ULL, 0xA7E6F28825758A68ULL, 0x2A10912CF690C723ULL, 
            0x18F48C7FB6DB9661ULL, 0x4B136F751C02785CULL, 0x67EDE440536173FFULL, 0x891A5C7DE012F747ULL, 
            0xD5526FC892498D86ULL, 0xC4A46D709E817888ULL, 0x5758907149B984E5ULL, 0x60AB1D0257C9D552ULL
        },
        {
            0xA42D0FA4908C25AAULL, 0xAAE0215016D5FD90ULL, 0xEA27F7416A4F316CULL, 0xA89C9421F076271EULL, 
            0xD99F8B9900AE6F09ULL, 0x39B97C7F0B26677EULL, 0x3C499C2221BDA9C9ULL, 0xC143EA003E074F8EULL, 
            0x7E2CD5A6E3E7931DULL, 0x35085FF999D6DC5CULL, 0xA81315956DA333D8ULL, 0x55CD30C9E4CEEC51ULL, 
            0x93B5CEEB447B2DA8ULL, 0xEA1903680FA15F4BULL, 0xBA3AE531E99B6CC5ULL, 0x7DB53F83CE9B5044ULL, 
            0x3F3A30DAFB7C0612ULL, 0xC524F1978FAD3145ULL, 0x29AA84176C9AE11CULL, 0x5BEC48567117EBD8ULL, 
            0x91C8AE730BE2EFB5ULL, 0x500FAD3700EC139EULL, 0xB96EF1EDBFB3D886ULL, 0xEC86BA8EC05E7E0AULL, 
            0xBE6B415ACA7C0F3DULL, 0x14E72EAFE41D9965ULL, 0xE2D8FC3189EFC013ULL, 0xF4A97A9CF82441AFULL, 
            0x5BAEB134405D88B9ULL, 0x87669CC081C22625ULL, 0x677840D38AC119BDULL, 0x14F2E40C4A911215ULL
        },
        {
            0x7D7068417A795A13ULL, 0x0E1940A682566D39ULL, 0x9309AF714462C577ULL, 0x2BE888785889B26DULL, 
            0x62414C18A04ABB70ULL, 0xB2E3D41A2CEB5F10ULL, 0x38B6E77A463839BCULL, 0xBE267603768250B1ULL, 
            0xA3E344E7A21C19FCULL, 0xA284536443C1194AULL, 0xF9B46190EB7CE311ULL, 0x1770F9C25CA3B8FDULL, 
            0x0BB1CD9AD59E2BA3ULL, 0xE14264CD87CD880BULL, 0x8B45972A55B717EAULL, 0x85D9B2C7E4B982E5ULL, 
            0x5BC966747A4658ACULL, 0x7F0C3057931B26B6ULL, 0xF73FD2584181943AULL, 0x213A9444BE290579ULL, 
            0x80B9C23D0AE61070ULL, 0x20F523B2203F87FDULL, 0xB32DC1FBA7424BB8ULL, 0x3A777F467336305DULL, 
            0xDE3F2FD873D700E1ULL, 0x62BBB60F156F92EEULL, 0x030C27759394FC34ULL, 0x8C8FA45B4495D13FULL, 
            0xF249AC091F8E5E21ULL, 0xE82BAA88652B453CULL, 0x1945CA196ED69A39ULL, 0x9FD6D47E48AC6393ULL
        }
    },
    {
        {
            0x7202B1E1AD9985FBULL, 0xB1519C795861D8D5ULL, 0xF1A3F3548D998E4DULL, 0x544AB8C1261C7F17ULL, 
            0xF7CD1918552C88E6ULL, 0x1BAA59DA0A68C68CULL, 0x942F111B3943564CULL, 0x343B352F2FEC721AULL, 
            0x8AB032912561C2A9ULL, 0xA979677AC44587D4ULL, 0xEA738A373F421265ULL, 0xD76EC9977A748224ULL, 
            0x5D62A135A0CA8ECEULL, 0xF6FBC5A86F31CB5CULL, 0x40129E5EDB1B45E6ULL, 0xE84B0079E6DD5F99ULL, 
            0x272E97E204DF7EDAULL, 0x20A09174BA9D088AULL, 0x8FC8A17E4CDF5E10ULL, 0x7D2629FF32E0C7F0ULL, 
            0x8E9695A1A87E1EF2ULL, 0xDD372F5E1FEA8360ULL, 0x2FA1D4F56C1C0C70ULL, 0x6B69DC8F041F880FULL, 
            0x24B0D927C2437481ULL, 0xAD091E2DE535760AULL, 0xDDB5F4EBBDD67114ULL, 0x43D093B6B7573C7CULL, 
            0x01C96F276783B5B4ULL, 0x39654BF5B3949C13ULL, 0xF98AB3944AC06B27ULL, 0x21D063DB02F9749BULL
        },
        {
            0x1C8D144C956A1998ULL, 0xF03DB9EC69100536ULL, 0xB2DFDC7B5F937010ULL, 0x70A01ACE2AF383C0ULL, 
            0xA43CB0A24823BC6CULL, 0x43BAF39F7AFBB22CULL, 0xE8425553775904B6ULL, 0xB883991D74800D7BULL, 
            0xDD932F7910D1853FULL, 0x7A10C5E60FBC9A7CULL, 0xEDCD9074E23486BBULL, 0x704E377B7CC4FD9AULL, 
            0x999E59B31CFD505FULL, 0x0F2CC833D0217935ULL, 0x35A4BE0AD5397E3EULL, 0x71FA75B0E2A106F6ULL, 
            0xA26F3D5A89135E0FULL, 0xC7D2485B9D424370ULL, 0x4DFD7B98D5BEF119ULL, 0x7A4CAD6B7DF2A96FULL, 
            0xBC19805DC19ABEA0ULL, 0x0A76F73F3A93C484ULL, 0xFA3C4E2DEAE1A66EULL, 0x42DD16C2BAE431D9ULL, 
            0x44E0BB95FE478B61ULL, 0x6326F667EE35A700ULL, 0x279655F1CD2A4A36ULL, 0x97BE61C540213500ULL, 
            0xFADF3178399517E6ULL, 0x128BC811E90A6234ULL, 0xC224D6211184E12CULL, 0x303BA10BF16798BEULL
        },
        {
            0x84A71859346C36D0ULL, 0xDEF6378D0739A531ULL, 0x7F1901D4F04ABE37ULL, 0xBD4E9EE39E3C749CULL, 
            0xECF2D48695704381ULL, 0x3F5A98FF2C02C73BULL, 0x36165FEEB7113922ULL, 0x7CF9A251D3D1547CULL, 
            0x36CA9F1FF3DA3E3AULL, 0x78D644E76EDD159BULL, 0x030763A2FE0F69BEULL, 0x127CFEA91AFB645EULL, 
            0x254221211CCDAA89ULL, 0xE083E30ECE121766ULL, 0x65B507E03266A9C3ULL, 0x809C8615FAD7F322ULL, 
            0xA664AA291DFE6A75ULL, 0x0FE352E9F35150BCULL, 0xA190403540D49F3EULL, 0xA41C663CE47E09E8ULL, 
            0x99C21C9BB1704BD1ULL, 0xB998A536E1A0702FULL, 0xF789576E393990CAULL, 0xE97142CFEA02E28CULL, 
            0xF702096B208E7448ULL, 0xC7415286B9BDD637ULL, 0xDB4D593FBA7B07C6ULL, 0xB52503B80F03BACEULL, 
            0xE9998F7499E81278ULL, 0x54DAE108FF127E18ULL, 0x6E92D81B66EA7F9CULL, 0x1A163910D02BB1CCULL
        },
        {
            0xE969CF75EB0737F0ULL, 0x7D31D1BEC0AFB068ULL, 0x5DAB281D8EEA0B83ULL, 0x52586A1BAB6A27FEULL, 
            0xE6FBCEA25AC8583CULL, 0x0DBBF6297B00EF12ULL, 0x5C56CE09A28C7F8AULL, 0x80D78A3CFF0167F8ULL, 
            0x1F9346E75593169BULL, 0x35F7FB577E7D2464ULL, 0x733485EA12EB4ADFULL, 0x10C9078450C3A536ULL, 
            0xCF9AC4F98ED7B931ULL, 0x8840C4CD69D13BF1ULL, 0x80C0C9A2EDE8FFFDULL, 0x1ADE3A0001D0B21EULL, 
            0x121BA4B1F6D7D841ULL, 0x4CA110B3AC4FA664ULL, 0x588A99ECB3D9320BULL, 0x1E46F07B73A190A4ULL, 
            0xE7F9A5692847BB2FULL, 0x166BEB650CBE334EULL, 0x961AB993F60199F0ULL, 0xC27D6A5A58AD4D26ULL, 
            0x1C73562F2FF91F0AULL, 0x3A3A4DA65CBD6191ULL, 0x43DD011A4FB6761EULL, 0xA5A8408270B3483CULL, 
            0x62FF66D35D704D13ULL, 0x6879888D1F728DDEULL, 0x8081D40AE2A04622ULL, 0x376954DD36CD2161ULL
        },
        {
            0xB94C7FED94C1F529ULL, 0x28185B49AA084225ULL, 0x7D5865A91AE7DF91ULL, 0xB2D4312A4C129C33ULL, 
            0x500602CF6A718509ULL, 0xD90F14615336B5C1ULL, 0x75EE234EB1D49159ULL, 0xA4A610478B4F181DULL, 
            0xCE24C95FBA87085DULL, 0x9F26FAA83E8786DEULL, 0xF275DC1B8DBA7479ULL, 0xDA667A916943B4FFULL, 
            0x8D2E5A0E7DAB7E6AULL, 0x6876DD6FB89216BEULL, 0x667EDCFD3EB443F4ULL, 0xCF7E6B4064AAA595ULL, 
            0x64F61FCEDAF04CDBULL, 0x954E69E5D1DE0BABULL, 0xAB2505BC3A69E108ULL, 0x884963FE91D8EC27ULL, 
            0xF7C00694831DE18BULL, 0xF8E971777657F1F8ULL, 0x4509338EFF9006C3ULL, 0xDFA68DDE5C10E6D9ULL, 
            0x57ADC2DC769F7704ULL, 0x9B386B828B2ADA31ULL, 0xDF457ACD40CC9F7AULL, 0x2E702B437F2190A2ULL, 
            0x76FD6EA8E9F2AE73ULL, 0x2C296222FF8F6614ULL, 0x7BEDB9506DFBFCC8ULL, 0xE0053E260BA28833ULL
        },
        {
            0x1140C4D49A52952AULL, 0x094BB599E64E3FDFULL, 0x84AC13F5259A187BULL, 0xFD672BE97463C021ULL, 
            0x64497C8D3DA7E9ABULL, 0x8B9C3DC4E07657B7ULL, 0xA8CEB69677D60229ULL, 0xD566BA2C5E990863ULL, 
            0x954EA0D50BD73372ULL, 0x44DC25F98055DE35ULL, 0xC27D538641D9D73BULL, 0xCF30D73DDF46DA92ULL, 
            0x9F21828C869A142CULL, 0x43B4659BE3C01BFAULL, 0x6016696C0517F637ULL, 0x12585ED5BB8FE2F5ULL, 
            0x29DE524B67E9CE8AULL, 0xBBC8162D9EAEBF48ULL, 0xE2B4314BAB84D7F0ULL, 0xC104F76B3A685281ULL, 
            0xC8CF353DA9440265ULL, 0xB7A20E2FF1D1FA82ULL, 0x5DC1CA1DE8CA0BB6ULL, 0x89B52D9548755887ULL, 
            0xDF78E83DECFF4880ULL, 0xDB0CA990018A5AB1ULL, 0xC3FD50CE9C3DE739ULL, 0x3FB1CE8B841916FCULL, 
            0x40925BE9A199375AULL, 0x9BABAB49E8A1FEC3ULL, 0xB40282495E56055BULL, 0x2D7D4836D4EEB383ULL
        }
    },
    {
        {
            0xB443A4D4A138B56FULL, 0xBC3C20D7EFACACFFULL, 0xA9FFF5220D30D55FULL, 0x513504ECD8875C19ULL, 
            0xF715C7C923A6E4EAULL, 0xA41960A85965DC0CULL, 0xFE18DDA2CB5E5569ULL, 0x17A8180FED48B300ULL, 
            0x1FF5A6CC7A74A77CULL, 0xD9C3B87700ED0740ULL, 0x3DE0356B7767E9E9ULL, 0xAA285582182FAAB4ULL, 
            0x5C584E7D41D5C08AULL, 0xC6DA9B2DCB4FDA77ULL, 0x6B082F6F286485EDULL, 0x68B89B8C9A3A7B3FULL, 
            0xD888E011214E8D1AULL, 0x903CAA06526DA8CFULL, 0xB3378AF6B4649118ULL, 0x3DD4F4C748CBFCE3ULL, 
            0xBB4E09CDB654380BULL, 0x1E9F9AA47A1E0043ULL, 0x0C12769BB6DB6291ULL, 0x7E9BA4A893E4612BULL, 
            0x1E407B2EDFDD80C3ULL, 0xBA4A031DD94ABD32ULL, 0x3FA818663AF10AE4ULL, 0xBED013E698351EB1ULL, 
            0x9126BF3099AE5689ULL, 0x79512CA999EA9508ULL, 0x66AFB3AB9FE446C4ULL, 0xCAE2CA13BDEBF1B2ULL
        },
        {
            0x74CAAE34E9044771ULL, 0x95BB0E452BDEE145ULL, 0xD13416A9440C94A7ULL, 0x40AF385C0526B61EULL, 
            0x9C19B83E38C14A7AULL, 0x86B6101015B5B5A9ULL, 0x75B6D824EC492672ULL, 0x5BCD63087561DF9AULL, 
            0x80FADA61285948ABULL, 0x455627E538F1CA04ULL, 0xBE998B27C6879EC4ULL, 0xDD15FED017567F35ULL, 
            0x7CEB27A3588E5940ULL, 0xA928BB4FEF9CEC6CULL, 0xB7157DCE8987B3EAULL, 0xF23D0C770D18B57FULL, 
            0x0A2ECFE727A213B2ULL, 0x4A48E359BF463D58ULL, 0x92B1CF3D068B55F4ULL, 0xAE4EF47BD31529C6ULL, 
            0x8404B2BC685DACC7ULL, 0x49334994C99A9217ULL, 0x24B8B0C2AAF48D71ULL, 0x5727003C5469B15BULL, 
            0x2B7C2F6B5B49AB85ULL, 0x716548AFABEFFD6FULL, 0x4D44CEB17711F6C4ULL, 0x78140F64FA1B6188ULL, 
            0x8ECA4DA153FC5B3FULL, 0x50518BB2AE906BD8ULL, 0xE8AB1CE4B66E4DCBULL, 0xFD7887A3841FC790ULL
        },
        {
            0x8B3341574675310AULL, 0xBCA8D0389B503A5BULL, 0x2C314AA85553D426ULL, 0xF45D77E9FA673EFAULL, 
            0xB79B2B9253E22F41ULL, 0x0CD9E789150215DDULL, 0xD3801304E5A044E1ULL, 0xE7447DC6B7FBA5AEULL, 
            0xD5B2D5D755DFBD23ULL, 0xDFF436CAE8A01E58ULL, 0x7C85AD51567AC46CULL, 0xF2C4141AC97D4224ULL, 
            0xF9D41D18C7A34360ULL, 0x372D0649F6F79F2CULL, 0x36DBDE2187A6BEF3ULL, 0x4543017C84D4FAB5ULL, 
            0x51FAD5E5402A057AULL, 0x827306F4DC4FA75CULL, 0xAC8DE976A7295AFAULL, 0xE8E81E5BFE24644DULL, 
            0x2D3FA6C1F22F3D27ULL, 0x83BCA26E4AFBE200ULL, 0x4992D17754A9DE6CULL, 0x53B7D837EAB6985FULL, 
            0x6CFB5C902CACE835ULL, 0x4D4BBA3D224083F2ULL, 0x67DA0D7C4316A3A2ULL, 0x5160450EBDC6493BULL, 
            0x93446805350100BFULL, 0x8BA50930FD71EDB1ULL, 0x55B651C8F1C483D0ULL, 0xBD68211DB02BA0DEULL
        },
        {
            0xDB382AD8A3BF7915ULL, 0x2A905551B0C1118CULL, 0x8BA54797C77AB68FULL, 0x48F5FD545D363C85ULL, 
            0xB3BBFBDD2A810ED0ULL, 0x5E6609C1E90C36E0ULL, 0x4E0BFBA185F8DCD8ULL, 0x47CAA8E32282C789ULL, 
            0xA67863AA6561CF09ULL, 0xC84F410F2F2EF991ULL, 0x602374D272BC364AULL, 0x5D99A68CD8BC02E3ULL, 
            0xB18F50E115766710ULL, 0xA86023C31EFC5F80ULL, 0x9EFC96B77C4D3F25ULL, 0xB65FFC74FFA86E1CULL, 
            0x133C905226D30240ULL, 0xDA4EE87B679C6BBEULL, 0x6DF91802EC9FA8F1ULL, 0x1673ABCF0942581DULL, 
            0xB0AFC74533368A10ULL, 0x37EC3EBFDA903229ULL, 0xD166C8F4F1C0C349ULL, 0x939E2B96FBCCB769ULL, 
            0xC6A2C7C09561DBADULL, 0xF2A41179D480B642ULL, 0x603E328960DF8137ULL, 0x583778E2C9AF8F63ULL, 
            0xAAED1B3EF411CDD1ULL, 0x770D15BC9773E2DAULL, 0x0F2F8FEA2DABC670ULL, 0x49C7B23C39693E87ULL
        },
        {
            0xB4667418A1EB6DC9ULL, 0x5CCC61E4BF5F3839ULL, 0x5A474848DB349B13ULL, 0x527E90C0207B2FDAULL, 
            0x732175BF8EA7CB0FULL, 0xE2B332E5222453DBULL, 0xDDE0B3352F6D561CULL, 0x9FD03A3CA57098B4ULL, 
            0xD39F7AD5DCCB59E9ULL, 0xEBB79AB6DAE3AA1DULL, 0xE7B7D5289046D377ULL, 0xA1F42285E1A209F5ULL, 
            0x01CE5E679F0BE386ULL, 0xD78D87CDA65DD04BULL, 0x126BE4D2542428A4ULL, 0x27BBD8E22224D48AULL, 
            0x336604C16C5C1F28ULL, 0xA523588DC4DA8EA6ULL, 0x655E07989D79BB5EULL, 0xFC71654EEFEB8E9BULL, 
            0x86D97C1346701781ULL, 0x15133B7451F8E66CULL, 0xBD8823AD53A43BF2ULL, 0x3C27B32DF83D5585ULL, 
            0x7EA0E17D42F50BA5ULL, 0xB2A3CB34B9046E9EULL, 0xC3514A0C489B61EDULL, 0xF310C204E94BCCF2ULL, 
            0x6B53B97A6B802EB7ULL, 0x1477B5EA019F8F17ULL, 0x355C85287F469F0FULL, 0xD284E3D316589F79ULL
        },
        {
            0x38E02FF3BBE86CA6ULL, 0x27395559559A7ED2ULL, 0x93A4721053478186ULL, 0x3E7B6A2928E215C0ULL, 
            0x95CCB72E35FB75EAULL, 0xDD479B4A6D585DD0ULL, 0x2E05120CBE3FD20EULL, 0x7F521D3CEA8EFB7BULL, 
            0xD5E21EF191325EA2ULL, 0x9B63F13A0FDF9EA8ULL, 0xDD464E765D1A5EE5ULL, 0x596EA99D5F73C215ULL, 
            0x5261844A5555A432ULL, 0x82418CEB2BB55C6FULL, 0xA125531BE86EE3E2ULL, 0xD2ED01CC08FDF881ULL, 
            0xA634CE11AC776CE2ULL, 0xF6F2DB99B8A3344AULL, 0xC03B8E65BF7D7C6FULL, 0xD629AB05E06EA85BULL, 
            0x8DF349741B00386BULL, 0xBB7A9C42D8247EF9ULL, 0x6D2D474165E44827ULL, 0xF7BB7ED903129588ULL, 
            0xE8B99706CE14980AULL, 0xC682F4B46AA19DE5ULL, 0x2AB23EF9B6699A43ULL, 0x65762FFC73F67FD5ULL, 
            0xE88C0BC204CBA3A0ULL, 0x8C801EAEFDFF79F8ULL, 0x2D16FFA14D930EFEULL, 0x7B4D43E5FAC87B05ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mothallah::kPhaseEConstants = {
    0x98CC2221CBDBEA2AULL,
    0x01DEF0E9E7A78DEFULL,
    0x9FF9B6DC36C0F325ULL,
    0x98CC2221CBDBEA2AULL,
    0x01DEF0E9E7A78DEFULL,
    0x9FF9B6DC36C0F325ULL,
    0x6499698D223E23C3ULL,
    0x18C6ABCC91C95109ULL,
    0x41,
    0x5C,
    0x01,
    0xA4,
    0x0A,
    0x45,
    0x94,
    0x6E
};

const TwistDomainSaltSet TwistExpander_Mothallah::kPhaseFSalts = {
    {
        {
            0x24D1461285D327CDULL, 0x90E74D5A78DE47BAULL, 0x0E21B082806F8BD9ULL, 0xCA1323E2A6F77668ULL, 
            0x45010DA61CEFE0BBULL, 0xC57E7AFCF50983F1ULL, 0x578A4509D05893D2ULL, 0x6A7B359CDBBF2DEAULL, 
            0x9167F45CD2860833ULL, 0x9DDE966C5DD16D23ULL, 0xB4E85E243723D88DULL, 0x13C5FBD0B4627793ULL, 
            0x4713CDDBAA96F9C5ULL, 0x08CBD92C1BC2773FULL, 0x3599B528F4E968A2ULL, 0xE194FB315E73942CULL, 
            0x79B4303BD920F450ULL, 0x6AE3FB8DED0622C4ULL, 0xB9BFC8782D25638FULL, 0x7C6A12A69B69DC4BULL, 
            0xD024CBCEFEB2A7E4ULL, 0x7406C98639261A67ULL, 0x5B51775D96226B81ULL, 0x4CFEFA7B4FDEF76AULL, 
            0x4DDB146890EE79A6ULL, 0x773817CAB2B26A58ULL, 0x41822E9DF32DCA94ULL, 0x77AE6A8F9980EA93ULL, 
            0x7BA7C6183E7F0AC1ULL, 0xE58142EFDB3F9526ULL, 0xA29BB2AF3266A7A2ULL, 0xB81E57F1A4F7791EULL
        },
        {
            0xA3AD3A21A59C37FEULL, 0xDABB984C6FF9CDFCULL, 0x804BA3D5EDE82E72ULL, 0xE739F6D4B0DDD456ULL, 
            0x24BA9A5B11BF696AULL, 0xE8EDCCB76C5F8FACULL, 0xF0EC0CA6FE383014ULL, 0xB2C8F23C53A122E8ULL, 
            0x35E95C3FBEB0B03FULL, 0x16A08B828C3C0DCDULL, 0xBF09E67179DA4E0FULL, 0xE2DA08BFDD2178C5ULL, 
            0x141C71CADA83F34FULL, 0x192F51797D8CADD8ULL, 0xCEEA36DF6590AC4DULL, 0xF6E30B31DFDF5DBEULL, 
            0x6A25D19BCACF514DULL, 0x7D063C4ACA19744EULL, 0x313C4EEE448FBA18ULL, 0x2C4CF4F71C9E4402ULL, 
            0xA48825D00A801685ULL, 0xAE5D83F577FB988DULL, 0xDC0A9EC350E36F0BULL, 0xE0BF4D5F27A1E956ULL, 
            0xA0FDA72F58F24285ULL, 0xCCF826211C7B970EULL, 0x62D60728AA971275ULL, 0x46006B6B2F129631ULL, 
            0x99CB0A062B530CEAULL, 0x913981C654B9ECB5ULL, 0xA78E04418B03EF91ULL, 0x507588C9DF93A816ULL
        },
        {
            0xEE098C7E22018545ULL, 0xC976A8D1490507D5ULL, 0x371A84F5A17A6052ULL, 0x25E8F90779B0B5D9ULL, 
            0xDCC73AB44D7F7EF7ULL, 0x5E3E556A8136A912ULL, 0x691A7440043A4059ULL, 0x7FCAE764D2FAFAF0ULL, 
            0xB66743EB8C5DEDFBULL, 0x3A26B4442A9AF1FAULL, 0x617E912567F77257ULL, 0x61F1034009D75D15ULL, 
            0x68681CCC48B609BDULL, 0xFF531C43C9697855ULL, 0x0712D0A0DBDFF760ULL, 0xA8A5FAF83C94B480ULL, 
            0x6D165E5109A13D1DULL, 0x6EEDA6EC7FAA9BDFULL, 0x398B274406C7E5BAULL, 0x9F96CC1AC56EBEF9ULL, 
            0x91D924E0EBA05498ULL, 0xE4CA57EF91E3B372ULL, 0xD3AB77A2FDA5AE4FULL, 0xFE1BCE68928E3D4FULL, 
            0x24C212F4278B73A7ULL, 0x64445E4782F5F8CEULL, 0x9D3B839B775865FCULL, 0x7FCC6A1BAF8D5C3BULL, 
            0x85109B4D5E937D00ULL, 0x22BF2930356414FAULL, 0x5EED9DA1BD20B8FBULL, 0x1E61B2CA086DD89AULL
        },
        {
            0xD39CD0198352B257ULL, 0x9FF153453B8BCFA4ULL, 0xE17D398C53416F5EULL, 0xF5B39E31E618EA4FULL, 
            0xBDEFB86B08D163CDULL, 0x9F62B0E6342AAF15ULL, 0x5466393658B827D4ULL, 0xE90D53A1C752FD09ULL, 
            0x4DAF81569EF9E1A4ULL, 0x55082891E9EB3950ULL, 0x9052E0A9AF4C00BDULL, 0x086D12B1ACBAD9BFULL, 
            0x57C6BECD5B257549ULL, 0x78B1190DA48C436AULL, 0x72195C31AFFF18B0ULL, 0xF3962A0806235263ULL, 
            0x92F912195F018B97ULL, 0x4676101DC9C67A27ULL, 0xDB5BB6F5E33BDCACULL, 0xBCE67186D7A25FC8ULL, 
            0x485A99B6C0F13698ULL, 0x256F6FD1E13A060CULL, 0x39D859CA94AFA70BULL, 0x9942C5E49AE7B711ULL, 
            0xADBC485EF0680315ULL, 0x12E3AE72FE2E98EEULL, 0x199C8D2448996D74ULL, 0x4E5A66225AB8E0B4ULL, 
            0x0631196B9F12ABC1ULL, 0x6E357FF254B3ADC9ULL, 0x43A244DF217003E2ULL, 0x9269299C4BD969A4ULL
        },
        {
            0x6E528059FC9DB141ULL, 0xD2774F39642CC448ULL, 0x298F9B4BF4D5A07CULL, 0x5F490848397FB335ULL, 
            0x16ECBA920E6568FCULL, 0x0224E41068B92AF7ULL, 0xF874FDB62CAEE4AFULL, 0xA23069B227570C2AULL, 
            0x5643884726FBCDCFULL, 0x5E757F622B83BCFEULL, 0xC84E8E4E13D7293CULL, 0xE3B54F729A0EB1DAULL, 
            0x42D81133555033B2ULL, 0x7BFFB758A94CADD2ULL, 0x30D83879FB0B3141ULL, 0x1CE0092033414588ULL, 
            0x871A9CC026CCE8C6ULL, 0xA43791D2A81346DAULL, 0x15387173D4676C01ULL, 0xAAF3C0DE849832E7ULL, 
            0x69E2455DCDEDF6CAULL, 0xC7888D19486D5981ULL, 0x22DF8DDDB603FF1BULL, 0xBA1D5FBAAECF52F2ULL, 
            0x7FB418E149691E02ULL, 0xBCF7E36BF015574BULL, 0xA190A04156F0431BULL, 0x7F147F4D3FAE4E26ULL, 
            0x8D2C25E7095DED8AULL, 0x0674736DA5898EFEULL, 0x6C4B89CB57EB35D5ULL, 0x5A01830D194ABC8AULL
        },
        {
            0x978DD9D1C30C15DCULL, 0xD58DAD79873FEBD7ULL, 0x9D0CED380FF8A58EULL, 0xBF11D2F83CD628F0ULL, 
            0xC4D3B9D0FC43F8FFULL, 0xF05C1978A59ACDB0ULL, 0x196D2084EDAC82BEULL, 0x7F7FCFB01848C069ULL, 
            0xED2D0E8440F41CEAULL, 0x90A207D4EEF8DC22ULL, 0x5F48957EA6AB3696ULL, 0xA8283D9827F44B98ULL, 
            0x23DEBA50EE705C4BULL, 0x9E35F88823A07A7DULL, 0x3B8D5CD132E3E26EULL, 0x691134E966293E68ULL, 
            0x4B1AC5CA3A6ED538ULL, 0x61C7D236CEFD8B5FULL, 0x6897DBD184213328ULL, 0x8F6F07014B4E964FULL, 
            0x76CF17E97A14D082ULL, 0xC3D3B5098D5D047EULL, 0x74AB0B622C887858ULL, 0xC35195A381452CDAULL, 
            0x072A16B94571EE6AULL, 0xDB93734D20798813ULL, 0x864330A69C44E9C7ULL, 0x2E1282D9656D951DULL, 
            0xBD803AF5843695B9ULL, 0x856A1C61FC7A71F9ULL, 0x4897B793B12EEF1EULL, 0xB5ABE96EE87E72DFULL
        }
    },
    {
        {
            0x05E6184BCD33135FULL, 0xE8B4F4872071097BULL, 0x71948644D3F6DF13ULL, 0xCB4399A2AF3996BDULL, 
            0x2486EE3282AC854EULL, 0x248FCF16FA5D39CBULL, 0x4F252D095C0D2989ULL, 0x067461B222DD74C3ULL, 
            0xB37F7A34F5062A3FULL, 0xC9C07B157347361FULL, 0xF2F6D3D0F9AF4E93ULL, 0x59569AD808A62143ULL, 
            0x700C649ACDBD31C6ULL, 0x605A413ED2B3DD36ULL, 0xB9B5286FB67DA668ULL, 0x02848435C6558291ULL, 
            0x8209CC545CCE1AC8ULL, 0x84C6B87FB6A03788ULL, 0x82502FEA84511DC9ULL, 0x48B518E4EC29FDF0ULL, 
            0x31F6506C169AAF8FULL, 0x918862B6EC0E2840ULL, 0x42D59B2C61FC99CAULL, 0xD93F76151076B61CULL, 
            0x8DE7AEC0EDD52C06ULL, 0xFA45483846B70DCEULL, 0x171045605F96B05EULL, 0xDCC79428F5B3E0D7ULL, 
            0xE29C5AF2E4EE7FFEULL, 0xA3D353070AA47F69ULL, 0x717FA91E4C0F49B0ULL, 0x7105660D94ACB548ULL
        },
        {
            0x24109DF4251F1223ULL, 0xB9969BDB0032A36DULL, 0x684B7735DE05C34FULL, 0x2BAB479416B480E7ULL, 
            0x218C0D619B4CCF09ULL, 0xFD5DB990B7C2224CULL, 0xE875767EBF69F08FULL, 0xA61FDB8B068DCA86ULL, 
            0xDB182F080B78CA5BULL, 0x86FA0C00D26A0541ULL, 0xB70A625E106B8AD5ULL, 0xA1817210F79C6A49ULL, 
            0xE7BEA9F50E29F646ULL, 0x313A7E6DA1901034ULL, 0x698227F7B6B6CD5EULL, 0x33A71CBF08A09AB2ULL, 
            0x0A33311F25D8F80CULL, 0xD4D545F803D4E287ULL, 0xDC37B61DFBD2C404ULL, 0xF31E1D6B0F78BA2CULL, 
            0x6CE88B81214EAB97ULL, 0x6452F2142445BF3FULL, 0x935C712BD42800EBULL, 0x1FA5341E118C1D55ULL, 
            0xBDC0B1CF13E8A11AULL, 0x68A9670C0E5784C0ULL, 0xEA11ABD3E16C918AULL, 0x0FC86A5E9ED4086DULL, 
            0x5E25BB4C18CE24D5ULL, 0x4265865E2FE23515ULL, 0x3E40C3508142292FULL, 0xFE6EF242F48F5C94ULL
        },
        {
            0x400AF206EA7602A1ULL, 0x826CE2E52DA5716AULL, 0x6EF21CDDFEF218C6ULL, 0x08883959861943C6ULL, 
            0x1C8CBCA627C2D4F6ULL, 0x83541653A1D3CD96ULL, 0xF4843E86C93DF124ULL, 0x26CE7850F493F5BFULL, 
            0xEB1DDB917DE40B07ULL, 0x618BB1F367253693ULL, 0xB28782E7C9F361AEULL, 0x6AA7A12E19EA91CEULL, 
            0x6EFE29BDBFAE4989ULL, 0x6510D9395484F638ULL, 0xC430CDF0021BCCE5ULL, 0xA141C08492FE7568ULL, 
            0xD1B5A18779F06273ULL, 0x1351E1D2AB18F556ULL, 0x1C3649F4E652B8AAULL, 0x755201F7B97A995FULL, 
            0x1FCBD7340088C9B9ULL, 0xD161B0D6488EEC30ULL, 0x0269224C75698F51ULL, 0xF1E3ECC126A7C12CULL, 
            0xB658BE639B2C4486ULL, 0x183CEAC214F5A20EULL, 0xD654C72A1A73E370ULL, 0xF51792A7F1F0649CULL, 
            0x254D937169A736E3ULL, 0xB4A2E7812DCCC55CULL, 0xCBAC622120DFBF70ULL, 0x5C7C9AB8F6B01F6EULL
        },
        {
            0x5659B18F34D00859ULL, 0xF7BDB14B981996F3ULL, 0xBE79F700D51D7C3DULL, 0x5442270999E2B335ULL, 
            0xCE4656F2F0892474ULL, 0x39702A66A1C9CBFAULL, 0xEE26BEEE87D17166ULL, 0x2EB7B52F2AE0FE83ULL, 
            0x8C8F0CD6D7FAD8D8ULL, 0x2C2C4424FEBE1F29ULL, 0x95F168D68DB54C5DULL, 0x70E023C5F755527EULL, 
            0x8E5CE51B74EBC6A1ULL, 0xDA0F726B8DC952A5ULL, 0x181E17FD173E5AF9ULL, 0xAC9B97C19E10DAE8ULL, 
            0x6443FE05E4B35D6BULL, 0xE9CAE9B99ECB2207ULL, 0x44F2A1FCAAF909B6ULL, 0xB1B9BB95501D2A80ULL, 
            0x8757809FDBB96F4CULL, 0xFF7EC0B3D8B4C650ULL, 0x417937524E5080E7ULL, 0x972740545741A039ULL, 
            0x7737770B567D631DULL, 0x3BF217CCC404485CULL, 0x02B7252763D3FB3DULL, 0x665C4AD281802E43ULL, 
            0x24917EA29515AD55ULL, 0xBD19FEA25F562B12ULL, 0x554C85AAAFC9DAD4ULL, 0xC2C0DB52AD2DF4C5ULL
        },
        {
            0xA2E2F483AD063ED3ULL, 0x9F9BCB143CAA3C20ULL, 0x76FF42C60AB3E58EULL, 0x394CA85C7FDE4CC5ULL, 
            0xA14E5FD52E9CA7A7ULL, 0x7F14AA9448DDD9A1ULL, 0xD865E21B6DCF084CULL, 0x9D718A8D9F9FA7FDULL, 
            0xA7083BD18D9E63F7ULL, 0x45FD5D1B7067A661ULL, 0x5C65B07CECDD7FAAULL, 0xD5D647BA4922A801ULL, 
            0xCB7FFC50BFEA5893ULL, 0xFBC96CE672EC2886ULL, 0xB13269CB20573907ULL, 0x599EF4D88C9D52D2ULL, 
            0x78128DAAA4D26D45ULL, 0xBD37114035A3435FULL, 0xF94CA44A5EFACA42ULL, 0x712484644ED8AB44ULL, 
            0x61DB48CF3F909412ULL, 0x0C92E6D30827BDAAULL, 0xF9180309B6938BD2ULL, 0x00E34CC02595B292ULL, 
            0x364C69D9F3B6C86FULL, 0xAF5C006687554BFDULL, 0x10523C817156920EULL, 0xCFC3A97AF1B143B3ULL, 
            0xA534FB4D4F37DED9ULL, 0x59C81060ECB83A43ULL, 0x96DB17D1770E4B9DULL, 0xB35157D8BD757F58ULL
        },
        {
            0xFB3CE022BB6DD994ULL, 0x355E8C008C04A454ULL, 0x459586B01C469549ULL, 0xC67378ED35EB0219ULL, 
            0x0B2387E7D25F5AB0ULL, 0x672967A622DE4C11ULL, 0xC027F0F60DD062FFULL, 0x80FF79F958B27872ULL, 
            0xF6E68F7F754FF716ULL, 0xCB294199AE2CA4E9ULL, 0x213420617F93EECCULL, 0x876C66F68CFED9EEULL, 
            0x0C6D004446FDD3FDULL, 0x3308804067AA870FULL, 0x5D500B73D19D6C08ULL, 0x932B42729887565AULL, 
            0xA3C57E29CD6594C6ULL, 0xB2889CDA6192152BULL, 0x98B3390DD4EC267BULL, 0xCF639551AE666BC8ULL, 
            0x7DA1E4F0AE707B78ULL, 0xB7A465ED87B08E41ULL, 0xEC8A14286A3E1DE6ULL, 0x3F9557A7D5BE6E3FULL, 
            0x6FEE6E14D2CF50A9ULL, 0x18C156CCE7C889AAULL, 0x056E7D30A7162500ULL, 0xF882534B3FCA0649ULL, 
            0x9FE0DFC0DFF217E1ULL, 0x93F47B5C303256EDULL, 0xEAC2C5E353578541ULL, 0xE81E11D19562E02AULL
        }
    },
    {
        {
            0x781E6EA7215531C3ULL, 0xB02F64BAB26F2A3FULL, 0x8E7D09E17EAB25ABULL, 0x9A2781B5B2645547ULL, 
            0x36067FB330557FE7ULL, 0xA3280154A05E85ECULL, 0x7651505AA6393A2EULL, 0xDA0508FBA507B28DULL, 
            0xD7368F844707B6B8ULL, 0x2D1A1B234C611C5DULL, 0xA67BAD37812305C5ULL, 0x402C4D8F872D9FD8ULL, 
            0xD590581CD0F29676ULL, 0x4572AE980362A76AULL, 0x4361CC99178DC8FCULL, 0x4C48EA6030E15633ULL, 
            0xEEAC62CCCECAD157ULL, 0x632658F4F8212C05ULL, 0xD875FA857A00F141ULL, 0x72B8AF70ECE17E83ULL, 
            0xCCA94092E8153E7BULL, 0x0250C4554427308FULL, 0x7151F748604E5F3AULL, 0x32192C567DCA2E84ULL, 
            0xE797B3020F7185F8ULL, 0xCDA689C1E93A9A68ULL, 0x9A89CBDADFA8281CULL, 0x2A8D11813B8978A6ULL, 
            0x54E9E96FA14F8B77ULL, 0xAE434C76F626C690ULL, 0x04A3962EDFFE6728ULL, 0xB750A7BE09E3CA7DULL
        },
        {
            0xE0622E778EFCD03EULL, 0x0D009B693232C0EFULL, 0x29C81EF22A1E4100ULL, 0x9C9A4EEEC38304FAULL, 
            0x85454ADC1F1D5847ULL, 0xD23F91558B3ACD7BULL, 0x9E512C3E99C08F69ULL, 0xDBC6FB127318909AULL, 
            0x1E95F5C884A5301AULL, 0x8EDBA14FDE270FFAULL, 0x7449B4E3A0886C6AULL, 0x149A8E4C77ED4C9CULL, 
            0xD2F048D400F4B551ULL, 0xFAE84C1E0731A72BULL, 0x07E40595E8505A84ULL, 0x86A14FCC041C33B3ULL, 
            0xDD33CA0B05048CEBULL, 0xE79BED59D011DFC4ULL, 0x12FBD023DCFEA88AULL, 0x129C7B0EBED7A07AULL, 
            0xC60D80BACA1B0268ULL, 0x5CE0366908702869ULL, 0xF9908669469E1907ULL, 0x391555B311AED600ULL, 
            0x612350D4D725583FULL, 0x8EB232EC84DBBF75ULL, 0xCC90E5D6CE3F6FFAULL, 0x226AEE8B8C2AC792ULL, 
            0x88066D92DC0661A5ULL, 0x68FB839F00A66780ULL, 0xEAC8D01699C47E51ULL, 0x566EACD984AD0F32ULL
        },
        {
            0xF3B863BB38BFFC2FULL, 0x4F038F59AF125A35ULL, 0xA7B59D0C4D11DAD4ULL, 0x0DB6C25D058BAB09ULL, 
            0xD06F04A7355855D7ULL, 0x8774B767ABC76920ULL, 0xCA04FE9CDB3A4155ULL, 0x72C186E30E80A877ULL, 
            0x5C3809A46F08C82EULL, 0xC1B8FADA12608C21ULL, 0x965941A0AB558210ULL, 0x25D925C611800EFAULL, 
            0x420CF405981E55E0ULL, 0x879DCEAAF402BE8CULL, 0xC99D5ED597413678ULL, 0x7BB6961C1FC272D0ULL, 
            0x8CB92D7092C2EE10ULL, 0xA952A10003DAE720ULL, 0xBC5B1C8393FDB520ULL, 0xA1D153638274E1DEULL, 
            0x50901646EAA7A4D1ULL, 0x19015E2040461016ULL, 0x9F6641FF41B8F865ULL, 0xA42825E0651C1E26ULL, 
            0x9D0B5C69BAB8775FULL, 0x9DD9830EC3F8B33FULL, 0x525231F066AEE237ULL, 0x8D21837955FCC04AULL, 
            0x30F001FD520045E0ULL, 0x8F0D7A5A8D0E0B2FULL, 0x516B8F5CFD013529ULL, 0x130F657F78CC556BULL
        },
        {
            0xB4F59F703D1F1D9DULL, 0x71C2DF7FC65082DCULL, 0xAD7534B50C58E73EULL, 0x4FE9180F3DED51FDULL, 
            0xADEC4EAB92621AA7ULL, 0xF0D3ACBF377BDFABULL, 0x88A95E3D8BD8BB62ULL, 0x31F12B669A8751BEULL, 
            0xBCF0A78666019112ULL, 0x04BF38A035F8B999ULL, 0xEDC047C84ED8DBEBULL, 0xBBFED4021110387AULL, 
            0x95F19F179F5EA85CULL, 0xA13F3941B006634FULL, 0x8231744F5D5D85ECULL, 0xBBA15931F8CDE940ULL, 
            0xDE83E4C24FA53326ULL, 0x4EF8E83E5A2C3DF9ULL, 0x050B4486C1C8CD1FULL, 0xBB23A168233BC54AULL, 
            0x06CD76E8A20813BCULL, 0x464865CAD009C6F2ULL, 0x9C6448E304C56655ULL, 0xF9AC0C546CD7DDBEULL, 
            0xDB273D5F1CC22E66ULL, 0xE1F943485479D869ULL, 0xDCC3AB6A3013476FULL, 0x2665722946767926ULL, 
            0xEA1D913B82FB7AD1ULL, 0x0C7F865D983FC95BULL, 0x95F01C33E5B03C4EULL, 0xC25D10BFD42E532FULL
        },
        {
            0x4BE83D3A25DBFFF9ULL, 0xF8D742A537EDE2FDULL, 0x2AB8EE5794EF9DEAULL, 0xC2FF8868DB96268EULL, 
            0x4F32B9BDDE2CDBCCULL, 0xB18D7DF11790663FULL, 0xD5D2FD975FBD1398ULL, 0xA60E618B99338A77ULL, 
            0xF3022E55048F6D97ULL, 0xD095210B9C51D9EDULL, 0x921C954AC67D51AAULL, 0x91FEBBB66C30D4D8ULL, 
            0x0654BEF3EC0F0BC5ULL, 0x92336A079D70E226ULL, 0x25B70915EF23BB9CULL, 0xED98C6A9CBCDD93EULL, 
            0x5D25A4F255FBAE8AULL, 0x40AE48594CFB4DFBULL, 0x2D200D4B0497C966ULL, 0x8EAE25C044BF42EDULL, 
            0x4CBC136A95F50378ULL, 0x984C4D94AEE07160ULL, 0x2E92B88D62C6599BULL, 0x551467F43CF6B69CULL, 
            0xFA631732240852E6ULL, 0xB153305DB11982EBULL, 0x75685EB756B216A9ULL, 0xB90AC1106B14BF20ULL, 
            0x77EF01AB22302E06ULL, 0x893DD7B6AF2970C4ULL, 0x9080EEA4CFF52AECULL, 0xCF86247E7CF666EEULL
        },
        {
            0xB2BEF570D14ED543ULL, 0xC8B202F71A042AE7ULL, 0x6694B0E68E279E01ULL, 0xFBD7D49E8E74F671ULL, 
            0xEBACB1210226AA1FULL, 0x7856D5564CA50A44ULL, 0x157744D13CDAA968ULL, 0x6975DCD4131B1D29ULL, 
            0x903E72C9558DDBADULL, 0x530ED6E44DEB4E07ULL, 0xFD3F29AE8F8E5F8BULL, 0x30EECE51A0AE4D47ULL, 
            0xEBEC46E3C452655DULL, 0x683A14F550FB97F6ULL, 0x00B27F07F32313E1ULL, 0x659A8B02D024491CULL, 
            0x52359E62A0E399D5ULL, 0xDF26757F111474B4ULL, 0xBE3F2D94F164D2B5ULL, 0xC431FFC4FE780B06ULL, 
            0xB1147C1844534CECULL, 0x470B9B23D765DF5FULL, 0x5500EC5BE799DE9CULL, 0xE67BEA2D44603113ULL, 
            0xD464DF58E9806E3BULL, 0xFEC0840B5212A87FULL, 0x2822AFA8703C9787ULL, 0x176DA7229541D709ULL, 
            0xE0D4B48B966AD44AULL, 0x8735240C31B4809CULL, 0x161DC48C968957FDULL, 0xC688E5FAEF153C8CULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mothallah::kPhaseFConstants = {
    0xEFE80B10788AC562ULL,
    0xAD342C79D9D8B4A9ULL,
    0x661E137D4E1E9895ULL,
    0xEFE80B10788AC562ULL,
    0xAD342C79D9D8B4A9ULL,
    0x661E137D4E1E9895ULL,
    0xA510FA82986BD4D5ULL,
    0x494F6901C53D336FULL,
    0xDF,
    0x1D,
    0x97,
    0x5C,
    0xC6,
    0x3E,
    0x2C,
    0xA6
};

const TwistDomainSaltSet TwistExpander_Mothallah::kPhaseGSalts = {
    {
        {
            0x2EB1FA1F4BE57946ULL, 0x36417850BA5BC685ULL, 0x63D6C974DBBEC9C9ULL, 0xC1E102F4F636482BULL, 
            0xC891F9888D79869DULL, 0xE768EC207F7A2C5EULL, 0xA8F3E637A5E055B5ULL, 0x1B5174588D982E64ULL, 
            0x8BB7A5B97021117EULL, 0x947A718D89D7F7E6ULL, 0x1C935980637A89E8ULL, 0xD87856D7D12A4489ULL, 
            0x875C16DF00BFBCD2ULL, 0x46B6C839F2DFD74DULL, 0x6DFB29044E23C6BEULL, 0x0EBFA036B77DB245ULL, 
            0xFA5F12210146BAA3ULL, 0xF4D4CDE754FD66A0ULL, 0x004548FFA01FFB33ULL, 0xBA5A42495830EA32ULL, 
            0x75E8323F5F08BF8FULL, 0x9ECBE736ECEF02CAULL, 0x9655DE41FF7CF5AEULL, 0xD0601D5F541D3BFEULL, 
            0x193D566D5779627AULL, 0x5CC077DCF41B67F6ULL, 0x7B64F6D75C8DFF1AULL, 0x2070D0B20F62A4D3ULL, 
            0x1374752FCC490FACULL, 0x3E1603D416C60665ULL, 0x6B6F379F2880D7CCULL, 0x7908CECD31D183E1ULL
        },
        {
            0x9080154E8DAE5AECULL, 0x8352E6EA25F5543EULL, 0x3F2CF79BCB963650ULL, 0x75C1F9BBA076A2ACULL, 
            0x4E469AA3936FC91FULL, 0x047F7EBEDA1DC3FDULL, 0x3953125E67EEE4DAULL, 0x476B59DDAD74E485ULL, 
            0x187C6D3F543ECD28ULL, 0x3D74D2EAE941FE69ULL, 0xFD0DEFCDD2CE4BFFULL, 0x525D6B97BFF17849ULL, 
            0xB1712EAC284F63D3ULL, 0x41F27A823EE8E1B1ULL, 0x638214E8648F81C3ULL, 0x2174DF53CC5D9619ULL, 
            0xCF7833117EABEDF5ULL, 0xBC9C87D6782D9419ULL, 0xB09E1730BACED537ULL, 0x4E7E1AFC5D75A54AULL, 
            0xCBCEB788A217C018ULL, 0x42846C116B72B466ULL, 0x86A2E7F7C0B4DB92ULL, 0xE2B384D71637EB56ULL, 
            0x2D8BB357BA8F326DULL, 0xFE3343C5E4E95298ULL, 0x6AA80FF839462450ULL, 0x0E0DB512FB480B77ULL, 
            0x52687FB4FF310344ULL, 0xC10DE2B6B0CFCF47ULL, 0xAE90446E4B737354ULL, 0xE89D69757DAF8C88ULL
        },
        {
            0x551DCC484508B206ULL, 0xB1EF7FB57537C0BEULL, 0x98D2CBE08044879AULL, 0x11F8F7DFB69B5E21ULL, 
            0x7D400C3F8BF00CA2ULL, 0xA07B0C15FDFEF0FDULL, 0xDE73B01CEF55E199ULL, 0xCD11872515E1562BULL, 
            0x437E39CE1E7F209BULL, 0x52303CCA2C378B05ULL, 0xF5BC8995842525A8ULL, 0x949B253DFD5DB206ULL, 
            0xA099ED0476047CF6ULL, 0x74E1CD71A202A65AULL, 0x2CA8BAFBC74584F5ULL, 0x8ABDE43A9C9240B6ULL, 
            0x90BEDCA33E33B648ULL, 0x94F54840782C6222ULL, 0x00A186C9952FBE34ULL, 0x5BBE3EE90FB66522ULL, 
            0xDC5252815D760FC6ULL, 0xD56E5CEEF147E9B7ULL, 0xD68DF9AA41DB7BB4ULL, 0xA3ADEAD53D8B89D6ULL, 
            0xBE594B9C39BFAA81ULL, 0x4F3D76FCA1B026BBULL, 0xC5AA9440FB4CC35CULL, 0x7119EB3B8A87D26FULL, 
            0xDA99A5432DDD3CDEULL, 0x7A7146D08C9FC8BCULL, 0xBFC3F78C8ACCDD44ULL, 0xADE79DEEE610145CULL
        },
        {
            0x0D3EA226C5DE3278ULL, 0x1AB42966FD814E49ULL, 0x3CC6C41E6828A68DULL, 0xBAABD0C19175EE0DULL, 
            0x60F0A4BC948DBE81ULL, 0x382351DEBCAF6B1AULL, 0xDB7DA4E2E4F65515ULL, 0xDED10693910C323FULL, 
            0x9842D19C3089B54BULL, 0xCEA155363542BE66ULL, 0xD4DF674BF61E86AAULL, 0x862D97A65DB47ED8ULL, 
            0x20EE92D5D7CEE641ULL, 0x1327D9091EB5A026ULL, 0xBEF32F3E1B7AD912ULL, 0x893C015D861BEFAAULL, 
            0x1B013FF3E4972C24ULL, 0xC21E6C967663B25DULL, 0xB57F01F859DC20FDULL, 0x059273C9EA12629CULL, 
            0x64887CD97E547F5EULL, 0x11B17C1018FB457AULL, 0x038D303EDEED9037ULL, 0x81C477F20DB9BCE9ULL, 
            0x145B0A9B2FFF5B16ULL, 0x7A33ACE5A7C2B17AULL, 0x522E3BFE745DDBEEULL, 0xCAE1A849D4022C1BULL, 
            0x0707A27F174E8908ULL, 0x24E309D7B9F689D2ULL, 0x2463754D8890F9D7ULL, 0xE16379E1C82728F4ULL
        },
        {
            0x91E7F09189858F56ULL, 0x5807E3322F111907ULL, 0xF11347E3C3EECCACULL, 0x17ABAAB0D7065218ULL, 
            0x8FC148B0DF3E2CF0ULL, 0xFE829403AE997045ULL, 0xB1614E78E53267E6ULL, 0x757F295162FA1F18ULL, 
            0xD85635DE2B12325FULL, 0x00496DCFDA5B3034ULL, 0xC020B48631AD598CULL, 0xACA5ABA32C56C77DULL, 
            0xC7EB7831178C1A8CULL, 0xBAA7CE53BF9CA13EULL, 0xAEE3ACDF927D78C5ULL, 0xE41CB78878C8462AULL, 
            0x2176F2393828736DULL, 0x3986CD94EB1B2EBAULL, 0x51AC0020D26E0058ULL, 0x9B2989EE293630E1ULL, 
            0xD7C54AAFE11286FDULL, 0x6196C0ADE4537341ULL, 0xF363B935E27412F2ULL, 0x4095B166AE1E1487ULL, 
            0x8658A0A6AAAE126EULL, 0xA7A27A3BAA1D7A70ULL, 0xDDA471DA745DA0ECULL, 0xDF2E313B71B08E66ULL, 
            0x863B494D0D1F0213ULL, 0xA5C38876E53D1596ULL, 0x9B077BD07FB6F879ULL, 0x72C89CFE6EF2E58BULL
        },
        {
            0x6B63790269AA236EULL, 0xA65F94731EE0B99DULL, 0x9C7C1995D0564386ULL, 0x6036C65EE0C91834ULL, 
            0xDEDCF7B136723827ULL, 0x53EE7E354C57F582ULL, 0xBBEB43A5F8EEC7A7ULL, 0x25DC562BC43E1354ULL, 
            0x6687175799379AA5ULL, 0x63F24D60D54A9AC2ULL, 0xDA67A5E0CFBFD188ULL, 0x80AF58BEC8C2B315ULL, 
            0x6267A79DBE463CC4ULL, 0x8AE5827F45009993ULL, 0xDBE3DD3107B719D4ULL, 0xDDE50C3AFD39C9B0ULL, 
            0x4FF8D01DB0542C6DULL, 0x55199AC047F0136FULL, 0x8A5DF1BC1A6F72B5ULL, 0x4D456E6F3FD0550AULL, 
            0xEBA74D2134F8F773ULL, 0xC246B2E4B1E54F6DULL, 0x469A43972436E15BULL, 0xFC0E7253B192BACDULL, 
            0x9162174439176BD2ULL, 0x9C340D39D8B473ECULL, 0x446D7A060606CC35ULL, 0x91A6F6F8F0DBF7BAULL, 
            0x9AA4F195A5DB0A87ULL, 0xFE62231B8507AB78ULL, 0x380EF51FC82FAE9FULL, 0x1352E894ED465FE3ULL
        }
    },
    {
        {
            0x64AC91BB3C741D6DULL, 0x5C3C5D98916B9D4CULL, 0x66DCE1B05C3E0AD6ULL, 0x00DBF3A0C00B6730ULL, 
            0x0038775C20F8EC3AULL, 0xF7C83A402406C2DBULL, 0x966BFE88DB480849ULL, 0x7FE0CAC361139A84ULL, 
            0xF66267ED58BE7D41ULL, 0x92EE8ECA0F0A8D17ULL, 0x096C2683B61CDB79ULL, 0xBCA9CD42AB70C02DULL, 
            0xF9CA5C1F64F44E36ULL, 0x029EF76AA7E6ACE5ULL, 0xCF501797D6D016C8ULL, 0x0D44386FCE642D86ULL, 
            0x02CD84E28CACA370ULL, 0xE9B1F12D4ACD7396ULL, 0xEA420D6CED86A431ULL, 0x1824984113DB7E26ULL, 
            0x133E01F36B9D68D6ULL, 0x6538C0979C5DE269ULL, 0xD18EEE96BB7FCCF4ULL, 0x68CB839180BEB1A9ULL, 
            0x036B26E86AC1689FULL, 0xF67AF4D102E30490ULL, 0xBB42E0E83097FCBBULL, 0xC4764B27862CC2ABULL, 
            0x9794EA098B17D27DULL, 0xE7103FD1FC07BB5BULL, 0x8C855463D1C06777ULL, 0x521B02CF635549E2ULL
        },
        {
            0xA04CE43047317308ULL, 0x361D3042E52942E3ULL, 0xD4EDDF98C602C76CULL, 0x0E4FB80D12D658E6ULL, 
            0x5B16BD6CD0117D89ULL, 0x1D82AF41FE9CA22CULL, 0xE1FC8EEA4050DA00ULL, 0x8871243DC41F5DF0ULL, 
            0x3F250E577B5263CCULL, 0xAB356B49FC700D35ULL, 0x2CAA31A2D2DDB5A7ULL, 0x7DDFE935B3A0C859ULL, 
            0xAB36443999EFB025ULL, 0x4F5C8E70465B43C9ULL, 0xFBD62B984FC197C4ULL, 0xC1ADFB98B367EC0EULL, 
            0xE5CD484537528F16ULL, 0xA0584D6603057F50ULL, 0x314E501009C4A9C4ULL, 0x23C7A50CF4B4D1B9ULL, 
            0x06E5432BFF92130FULL, 0x2DBDDE2CDCA6548DULL, 0x57DD1EB5F3014B73ULL, 0x298EC1930A62C5CAULL, 
            0x1B53AEFFEFE31E65ULL, 0x981305FBA7A58778ULL, 0xECDBBDA5CE6526A5ULL, 0xC6D31B8FD7E1F9D9ULL, 
            0x3649C85CA91A062CULL, 0xF70544633BCB04FCULL, 0x8B0035F2D196D747ULL, 0xB3D64A9E768CB51EULL
        },
        {
            0xAA60B7DB68E8F182ULL, 0x692B0A5AA9731F9DULL, 0xA10BB33871BD9D63ULL, 0xC4DDB3DAA1891B82ULL, 
            0x80FBA1D074B32775ULL, 0x47CAFF0E80AF9743ULL, 0xE139204DCA565400ULL, 0xA534DD205BDDA22FULL, 
            0xE5819C5E2EFE26D6ULL, 0x13250643B675DD25ULL, 0x1237BEBEDEB80C3EULL, 0x8AF7DADC13194150ULL, 
            0xE5953C667635F513ULL, 0xB7E98B5DDE849EE3ULL, 0xE21A8689D92558F3ULL, 0x64F950A7FAB70383ULL, 
            0x6A697079A9FFCA19ULL, 0x7A0EA0D99CD0F5AEULL, 0x0DB793CE35113825ULL, 0x043648B96A89C12FULL, 
            0xACF1407703177CDFULL, 0x02DCA02891A4D3CBULL, 0xD8198E2654BC3788ULL, 0x349156E41DA5ECBCULL, 
            0xFB495EB37CF91758ULL, 0xEB1D19CBAD263419ULL, 0x626E4155E794EC96ULL, 0x1E1F3CBF1E8DD168ULL, 
            0x0E0B6907BF0A672CULL, 0x9133FE4401C52296ULL, 0x17778BE5AD8DAAD7ULL, 0xA9AB55FEB6E5A5A1ULL
        },
        {
            0x8E9DC9B355EADF4BULL, 0x25789D7D6143767BULL, 0xA62406701883635AULL, 0x4CA25ABD6FEF820CULL, 
            0xD92E4BF38C3E12ABULL, 0x25F188F63371CC4DULL, 0xC91968963EA87BD2ULL, 0x8C844D7735BCC672ULL, 
            0x7EC3CE3FB6460DA6ULL, 0x77D5250C43BA4EE1ULL, 0x755983541F10968EULL, 0x46411BE6AFA0F539ULL, 
            0x41BCCF2D9599665AULL, 0xC4B1C1F07347A369ULL, 0x9936CD10CAAB067EULL, 0xFA06A78F3D701BB5ULL, 
            0xE6391783CCADD30FULL, 0x830F2D1C82952AC6ULL, 0xBF49B06B6968DAB4ULL, 0x7F4FBF132AAC69ECULL, 
            0x245873F5BB8B3F24ULL, 0x2F3C5F89C1BFC1C1ULL, 0x54742BA7CA4668E6ULL, 0x28B5C02677CDE7B9ULL, 
            0x869D4D2DADEC95E4ULL, 0xDE409445A5BA061CULL, 0x40C6D5FD2E05897BULL, 0x0F1BBA706E35FF44ULL, 
            0xAD33B93FA93EF0D9ULL, 0x1758F8D07747215CULL, 0x36B0DEA3ABA74F73ULL, 0x7E25639D4B6CE0D3ULL
        },
        {
            0xAD0FC54D01E7256BULL, 0x0EF31FF8AE6E2836ULL, 0x4CF84BE85E15969FULL, 0x219BE187A39E1380ULL, 
            0x915F1449149CA815ULL, 0xC45F7E7BBA930BDCULL, 0xB7140821A0BA2728ULL, 0x8683A6122ED4C9FAULL, 
            0xBE6E349BB5ACB396ULL, 0x5B722F882556F6F5ULL, 0x688694FE3D9F195FULL, 0x7B2C9EF520B115EEULL, 
            0xE121F0CE03E968C4ULL, 0x49D9DEF005DB7B35ULL, 0xA60FB0F5D87E2A83ULL, 0xCB1281BBFA48C233ULL, 
            0x5141E3722DE7CE22ULL, 0xB69992D067D9F207ULL, 0x4B053E765285809AULL, 0x70FA6BE12C2D0190ULL, 
            0x6250D1CC64CF6E1FULL, 0x9680A38AE6293917ULL, 0xF1A68BA57EF15C90ULL, 0x441D0A979B6222B3ULL, 
            0x5E6E4158D7D9BE77ULL, 0x1607AFF7257497F8ULL, 0x6D2E5297C5745EC2ULL, 0x2BFEEB4286C55087ULL, 
            0x86FC66DCA70A1725ULL, 0x58C98AEAB334430DULL, 0xBF0B28EA7A16C7F2ULL, 0xC9ADC284ECED9C15ULL
        },
        {
            0xF2F69CBE203178D6ULL, 0xF7D2D336A2D28F95ULL, 0xC5F3F2EDB8AF1081ULL, 0x5DCF4AAB6EEF4BBCULL, 
            0x1D45285072B2AC83ULL, 0x5A6A6392C6126DA0ULL, 0xC6845986F53D6E39ULL, 0x10682B15FA17E323ULL, 
            0x1C854335B9AEEA02ULL, 0xB3D17C385CC093AFULL, 0x5365571A3FF847ACULL, 0x8F705B901FEEFB21ULL, 
            0x40066844D10BFCE5ULL, 0x7360D0650A8916AEULL, 0x954AB1B8F996F4A0ULL, 0x5C0A6798789F6715ULL, 
            0x127F1F821D9E90F1ULL, 0xF11138BD5139AA04ULL, 0x0959C4FEE1911520ULL, 0x5DE160A3955E880CULL, 
            0x853B2D7F2162A31FULL, 0xB074D2B5403B509AULL, 0x434EBF0213649126ULL, 0x63844E372520F257ULL, 
            0xF279A040FCFA455CULL, 0xF627B6F4B8D11265ULL, 0xABC04A662D79A014ULL, 0x0B666C0E5411D410ULL, 
            0xDB858C8BB83DC024ULL, 0xCA880AB0318B35BAULL, 0x893549F5BEFC2621ULL, 0xB38C683B375A6D36ULL
        }
    },
    {
        {
            0xCA51F73CF8876293ULL, 0x130B44A7D2521DE0ULL, 0x2A50FA84C8146F4DULL, 0xDC42E2830EA96E2EULL, 
            0x599D36DD171E39DDULL, 0x7417E168EED5E1DDULL, 0xD5EEBD5DF9CE8D51ULL, 0xEC6265BFEBCBA280ULL, 
            0xA5623C5D74F2231BULL, 0x25315C318DCBA061ULL, 0xB7DFEF5F2C5384FEULL, 0xA7E16D1011854878ULL, 
            0x8288182F75CC0865ULL, 0x67F7DBA1255F5B59ULL, 0xE2564A75F044C09BULL, 0xBA1ED572DBC224B5ULL, 
            0xB9CF422FFF38F73AULL, 0x0AB2FEC8F2719758ULL, 0xA3660A37C65969F6ULL, 0x51BB3B4222CC1248ULL, 
            0x0A90EAB3A42868A7ULL, 0x3900905D4829BD74ULL, 0x05606252E1A0648BULL, 0x3B556FAF287FFC82ULL, 
            0xFFE0A5C22A152173ULL, 0xF52DF46AFF511DA8ULL, 0xA4A04CB92DE6948FULL, 0x0CC39B4EC3D193A7ULL, 
            0x26A437F22BE13883ULL, 0xBD27BE933A49F1BFULL, 0xE72160A08BE1804EULL, 0xA0DA486B184D5866ULL
        },
        {
            0xC577BF7120EB7785ULL, 0x79ECD96D89366096ULL, 0x489A1DECDDA82AA5ULL, 0x7A8F9E512B108417ULL, 
            0xD673552C0A161993ULL, 0x17D1E0EFD1D9B128ULL, 0xD076E2ABB0DEF71CULL, 0xA3157F847BE5AF13ULL, 
            0x2AD46466AC0B5091ULL, 0x23CF8FDBFC030A5AULL, 0x75AB9A34FD926172ULL, 0x102869F4BD91DDA7ULL, 
            0x0243C7ACAC934FD0ULL, 0x2845AAA73B9FA46BULL, 0x3C532D0338E96DA3ULL, 0xDE2C05F5164DDE33ULL, 
            0x6DA3FB054AF3CD5DULL, 0x6F6130F263883C2CULL, 0x81633F60A43119FBULL, 0x3C1B5AC3E80653A6ULL, 
            0xC5DFBFB95435C005ULL, 0xDFE8876B61C2AF1CULL, 0xA69185786D6282BCULL, 0xC611D943AA6891ECULL, 
            0x487CC5DA74055065ULL, 0x50273F18F64CAAF3ULL, 0x27A2C8A8CBCDE330ULL, 0x8521B5165A9A66B5ULL, 
            0x31F47FB1F7980E6EULL, 0xE9E43D6C1ED5ABA3ULL, 0x79339903541C4AA0ULL, 0xBFA4E02900C1901EULL
        },
        {
            0x0CAAAFE6CA35D479ULL, 0x249D1D89544FE334ULL, 0x7222AC34B557A043ULL, 0x7618F9AF5220EBD8ULL, 
            0x79ADA400DFD642DCULL, 0xE6C7430751B4D3D0ULL, 0xEBF68555D5FE80A5ULL, 0x5CB34B0E877C4DACULL, 
            0xC3864AFC649B99F4ULL, 0x2F09AC397B1AA57FULL, 0xBCED2354ADDC88C6ULL, 0x2F3FC5A96BC7213CULL, 
            0x6E862FF0CFFDADBBULL, 0xD10C75462717A6E8ULL, 0x5810C54F9B0F741EULL, 0x6F73587EB77C0ADDULL, 
            0xADF0B887996AC402ULL, 0x0FEE8B2E344EA371ULL, 0xD126861DB904E59DULL, 0xE7BDCD9731EBEEFAULL, 
            0xFBACAD5F2376AB5EULL, 0x93DC6E64506E3E3AULL, 0x79A4AF5342B761B0ULL, 0xAA5EBDF94A34E381ULL, 
            0x0F525824109EC684ULL, 0x64DC30E1838B3AC0ULL, 0x960DD4CA2865E24AULL, 0xC5AE69E1C1CAE3E9ULL, 
            0x1D577A1016A38D8BULL, 0xEE2DCCF77029F67DULL, 0x2B87AC73E908DCD8ULL, 0xD8651B1B619D45BCULL
        },
        {
            0xAD8EAC218EE07E69ULL, 0x16EDB9768C84D24EULL, 0x74D6FA9A15A48073ULL, 0x79BD591BFD270AEAULL, 
            0xFD7E6D5583AB4B95ULL, 0x46B0676968A0468AULL, 0x9E1B72CF77204012ULL, 0xDBF7A0F1542091F8ULL, 
            0x7BD964253AF04644ULL, 0x57E0410C1FA19CBDULL, 0xA03C8F179A95B0E0ULL, 0xBCC2AD46606F6539ULL, 
            0x674FBE9F6FEE5100ULL, 0x063CF20DE01E09D0ULL, 0xE4D864A7506E4F12ULL, 0x3E416EBDBB7F44BEULL, 
            0x95FA9AE9F7E1DA80ULL, 0x6098E20E7EBCABDDULL, 0x90F3778D0397384EULL, 0x58334053CF87F795ULL, 
            0xF9C1E3A8CC7491C8ULL, 0x47F5E24CB04F42B5ULL, 0x1E2B34E9F6B78C96ULL, 0xA8B86CA469D75ED0ULL, 
            0x4EAB23B36FDEF04DULL, 0x3A3B62C4EF547BB1ULL, 0x43441300528F16A7ULL, 0x9D444C97C6B36FA0ULL, 
            0x4914AED6F64ADBD1ULL, 0x9EAD64EAB768B471ULL, 0x78D3E9EB11F5B2F4ULL, 0x89637C800FA7BBE4ULL
        },
        {
            0xF7AE8EEF4933610CULL, 0x70F2A7FD39A65B46ULL, 0x94486141209D8482ULL, 0x061F62325BAA193FULL, 
            0x6D791889279C16D2ULL, 0x11A055E02F7A2D5EULL, 0x87E777EBA287DA9EULL, 0x6F4754CF80C0E5C6ULL, 
            0xA7B3A64189FF277FULL, 0x65C21C7E05D59E8CULL, 0x2B7EC15F5F91D722ULL, 0x8BD844573BA808E7ULL, 
            0x03314F60A869C86EULL, 0xAE10F50169C6AE4FULL, 0x9B2B57A16BE21A15ULL, 0xEE98A36A23A30932ULL, 
            0xFE573A5E9AEA3A94ULL, 0xCA8CC108A73AE3A1ULL, 0xA5F9CD2711D6F87FULL, 0x72AA9A836C5E53E1ULL, 
            0x627AD544FC0CE83AULL, 0x13BD734504EBE881ULL, 0x350D5D2B1F4C95B4ULL, 0xE495CD217F6037A9ULL, 
            0xA0806FFF1A6211BEULL, 0xAEC1E759C4CE1F47ULL, 0xBE4375ED766D0DA9ULL, 0x5A47CAB84D39BF67ULL, 
            0xA13E1298DF7C81DFULL, 0x7DABD8344E1FFCAFULL, 0x2485CA0AFFA9C540ULL, 0x5B8B3EA501CBFFC8ULL
        },
        {
            0x1A5939C5E52A1FD5ULL, 0xB96242126B632BC4ULL, 0xB5814498AA5E4356ULL, 0x6EC57C5204AE5A51ULL, 
            0xDC961049EEA92C54ULL, 0x99D27BACDA266841ULL, 0x71CA75E3FDD5D8BAULL, 0x184C1D21AC0EB9D7ULL, 
            0x8F898844396C568FULL, 0x32616A7348B99CCAULL, 0x91772B835DE175EDULL, 0x8B1C96AFE4886070ULL, 
            0xF45BB39B2B04DCDEULL, 0xBE0557F5C9F129CFULL, 0xB291B4C28384F254ULL, 0xF0A13D1FD2270F2EULL, 
            0x13D674EC625B5C99ULL, 0x6BC7B48617228053ULL, 0x94EB4CF98CF7A37FULL, 0x05A7B8A45C80D0DAULL, 
            0xC253343ABE27D6C2ULL, 0x1C45F96AF0E510E1ULL, 0x57525AB19FE2900FULL, 0xAFE5B4CF134A972BULL, 
            0x9F06DDB1E1ADD30BULL, 0x60AE6EB793D6B579ULL, 0x142B6B009331C715ULL, 0x1A565D382493EFFEULL, 
            0xB88ECB52BF7D3165ULL, 0x0899A0CE375FB69BULL, 0x998A53641957CF4FULL, 0x269AB2D4BC236012ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mothallah::kPhaseGConstants = {
    0x6D0398C5315D1848ULL,
    0x64A704E289A3AB9EULL,
    0x45114C4F2681912BULL,
    0x6D0398C5315D1848ULL,
    0x64A704E289A3AB9EULL,
    0x45114C4F2681912BULL,
    0x05C2162ED9CC703DULL,
    0x0F5F5623591062CDULL,
    0x98,
    0xFA,
    0x99,
    0x46,
    0xF5,
    0x4D,
    0x09,
    0x21
};

const TwistDomainSaltSet TwistExpander_Mothallah::kPhaseHSalts = {
    {
        {
            0xE900839C760E8654ULL, 0xF5A25A37CF4704A6ULL, 0x01A3414723DF8441ULL, 0xDA74456F2DA9C601ULL, 
            0x98A09D353F26209FULL, 0x438FC99DF798EFD4ULL, 0x7C5FBE198FDA47E5ULL, 0x77F12C726AD98F7DULL, 
            0xE4F700A63554B1FCULL, 0x8B7EDB5BBEF07F4FULL, 0x860E2BFF54159B6BULL, 0xC38BBD77510ED8BDULL, 
            0xAD3F391B53F8B82BULL, 0x9B2FC2737B97E19BULL, 0x42670CC5531ACCAEULL, 0x6A15F47C1422FF99ULL, 
            0xF8A13701DB61F3CFULL, 0xE686F6622E43F796ULL, 0x2C2909231085EB72ULL, 0x616DE117893293FCULL, 
            0xB4D9770B115BD15CULL, 0x77C9054527184E1DULL, 0x8BBF30A5706D0445ULL, 0x8FD43AE11264A421ULL, 
            0x9C335C4693509941ULL, 0x889FE0BE2E98578DULL, 0xA1FEBE34CB508727ULL, 0x5CFEEFB0699E1C3AULL, 
            0xCEF1258792A7BEADULL, 0x11E3B28FB759E009ULL, 0x3AE6808F43ED7349ULL, 0x8D4DA6C14AB343D7ULL
        },
        {
            0xDE65BCE0BC6B4953ULL, 0x4EB6614AFE0E287CULL, 0xDE4B29E648C3037DULL, 0x3A890D3EBC4E74ACULL, 
            0xED0C684B7F78D530ULL, 0x4DFE19A3B3651642ULL, 0x4C5BA0F909A42511ULL, 0x7E690C5A26DBEA26ULL, 
            0x8013C99EAADEB959ULL, 0x5F1BF73423650A2EULL, 0xD4B60AE6DEB21763ULL, 0x45774612FA3B153DULL, 
            0x475CB34D3326A6AEULL, 0x0EF790E565AE6641ULL, 0xB084C2E541A111A0ULL, 0x70D1F535B541F360ULL, 
            0x253C229D77B47AB3ULL, 0xBEF2FBF8E64FDC01ULL, 0x7F319B25FD59ECD5ULL, 0xDB5DFF0030A83EBDULL, 
            0x931D4A7DED3BE34BULL, 0xA0EC33DBC7E53D14ULL, 0x1918AD42F8DBA432ULL, 0x84B0B78A9EFAF0BBULL, 
            0x00B1E468BBD2B9CDULL, 0xD090AEA35F540CF4ULL, 0xD4A1026E88A7639DULL, 0xA5786396B3B3AD6DULL, 
            0xD065717037BAF0EBULL, 0xAAD8305A52FC3367ULL, 0xF6A27EAC2C247733ULL, 0x7809C5381B747A85ULL
        },
        {
            0x467F98CBE52A8D7DULL, 0x0DE93682B6EB3544ULL, 0x002E0D3AC4BADBDBULL, 0x65033777753776BAULL, 
            0x606321301410CBCFULL, 0x51F88872D1EA3BB9ULL, 0xF8BF4DD764D0FB01ULL, 0xB1590D5375BE7920ULL, 
            0xF85B1736E1B89B29ULL, 0x50B433BEE2A93DF1ULL, 0x599997A4129B93C2ULL, 0x6D4800FD5CED54F6ULL, 
            0xF2E6F83BB3A64DBDULL, 0x96472071CDBB8900ULL, 0x638DFD51BCEC13DBULL, 0xBEA420699C96DA34ULL, 
            0x882C9BAA29CD1A16ULL, 0x2C78A9A668828938ULL, 0x03AF2422F944DA86ULL, 0x2BFDE2C4B36A0037ULL, 
            0xCEECE66CF90813A7ULL, 0x622B3B2405E271FEULL, 0xD93B470C5528B439ULL, 0x01B2960FA54A1EDCULL, 
            0x3A3A0DA18F1C5B70ULL, 0x82F92BBFC47F02C9ULL, 0xDE77FFCBA42F2F6CULL, 0xEFB2BD163AD80866ULL, 
            0x2D88E7D3E91D8A8EULL, 0xC20019F6D7649B5FULL, 0x6A93FF0E5400BADEULL, 0xA022D3161DF7E784ULL
        },
        {
            0x9AB3D21E4C1C0622ULL, 0xD3FAB4FB440D2E8FULL, 0x5CDF4EFFA9896631ULL, 0xE45F1CEC0C5B7B8EULL, 
            0x289C797D05D5D0DFULL, 0xB94F8EFF3960DCB6ULL, 0xAC774E1C1374DE2AULL, 0x45BF3D321EF4C419ULL, 
            0x445F6E2CC8ED1176ULL, 0xFD7A2B61246DB5B3ULL, 0x57F8D13BA6A67876ULL, 0x689EF1841ED57FC6ULL, 
            0x81CC49455311E296ULL, 0xE5349A99C5C693F6ULL, 0x3A589B15B669ABA4ULL, 0x5DEE87AE23D6E828ULL, 
            0x0750838C3ACFB0D9ULL, 0x7FFA0C0F20F19E7FULL, 0x1C0E71620F5AEC51ULL, 0xB26C589460BE95D1ULL, 
            0xF36AF6D6620E4BC6ULL, 0xC2D7EB7FCEF66303ULL, 0x5E02B106C78E0104ULL, 0xF6CAC9672F02EF33ULL, 
            0xB14FAD758F2D559DULL, 0x2BD39791858C19C3ULL, 0xA0A923047FDE9E29ULL, 0x016DBCE64BDED63CULL, 
            0x6227393AED1BA836ULL, 0xDED3E29341D12F36ULL, 0x621518C637CD3EA6ULL, 0x1B682A06D9F7BEA2ULL
        },
        {
            0x298E1681072539DCULL, 0x5D1E796D7FA3A38EULL, 0x02100735AE85D793ULL, 0x773E0C19CD588805ULL, 
            0x7D6477F1BFC574FBULL, 0xA3529AE6559951A6ULL, 0x00CC09EC8B6090CDULL, 0x214074976B62808AULL, 
            0x8324582C401AE902ULL, 0xC4D461E9B65C2BADULL, 0x3B0EE18B8842C370ULL, 0x2EE0459BA35A1937ULL, 
            0xB76CF091289F7BE5ULL, 0x45366DA7AF800168ULL, 0x81DFC3A7480909AAULL, 0x8CA7D784FC96CA33ULL, 
            0xB8980ABD301B5273ULL, 0xE598D259D033CA35ULL, 0x411AA6E03BEFCABEULL, 0x932D33CD068B1868ULL, 
            0x24BDA0F4556A5926ULL, 0x1D8D611585F29FEEULL, 0x0DA955A4A043774FULL, 0x8DE34A5800B2FD57ULL, 
            0xBDD2986EAC0065B5ULL, 0x394C10098E55E4F5ULL, 0xE54F250CE4F0921DULL, 0x89019F47BDADC0DAULL, 
            0x8F3E2C0C5D7CA95AULL, 0xEEC4CAC8150F30BCULL, 0xF2ED0D40B418391CULL, 0x6AEFB8E4766C5D19ULL
        },
        {
            0xDC046B095B883881ULL, 0xB446CB894686C5F0ULL, 0x84DC5681E2418290ULL, 0xECB929586C5AA8CBULL, 
            0xF8C1A8335DB6F2E2ULL, 0x409A6F966FC127B4ULL, 0x297DB32E2D751672ULL, 0x7A78AF68E57AAA9AULL, 
            0xB9DD478A543C09FCULL, 0x173FE12162304522ULL, 0xDD730900757CA39CULL, 0x0F3A01A858A93694ULL, 
            0x99EAAFD78D446A81ULL, 0x464C533BCCF9EB3FULL, 0x2CF9CB613684E9C2ULL, 0xEA657BA4774FA13DULL, 
            0x95E7C5BC9FE41C33ULL, 0x7A005141A5308B10ULL, 0x1A4C0F7EE2941B11ULL, 0x39E1CAFAFD61C89FULL, 
            0x076AE0268C337DC1ULL, 0xE410B2CAE1054C47ULL, 0xCBCE805A247DE2E5ULL, 0x18EB01F2D985FDCAULL, 
            0xEF2169FB71541250ULL, 0x78C510EF34DD1EAFULL, 0x8E5FDCF7F81DF56FULL, 0xD6023B9A1A89CD27ULL, 
            0x31A92B7C4A60F236ULL, 0x598F0EDFFD9ABB7FULL, 0xE8413C54862C522FULL, 0x00D98B3D1E9F357AULL
        }
    },
    {
        {
            0xB73F51BAB6345918ULL, 0x9752E2F1F1EC3DA9ULL, 0x889E1080524D5E07ULL, 0x49B9263698D766B2ULL, 
            0xA9EF02382BCD27F6ULL, 0x1E7E4C4FB04412CBULL, 0xA5E3E55BB2388CA4ULL, 0x35AE8977BD155F70ULL, 
            0x8292256D03D79150ULL, 0xEB44AD35015A9506ULL, 0xA39A4E940EA97241ULL, 0x712BCF819BF99ABAULL, 
            0xF9C264470577B35EULL, 0x72B37DC6E81C2384ULL, 0x15F1A55722309BADULL, 0xEC54039DE07384B6ULL, 
            0xD0C8C5DC94B9FA98ULL, 0x4C2E01E9EA649024ULL, 0x6BB4CE62FCBFF5F8ULL, 0x0BD41CAF811C9199ULL, 
            0x659DF42C06D5F892ULL, 0xAE3B97D5FEF9467AULL, 0x0A3F158E1FEADE6EULL, 0xB8FA8DD2429FF0C4ULL, 
            0x803E061223A52F2AULL, 0xE70BD300B2CDBB5FULL, 0x7C60E1C75C6D1DF2ULL, 0x0E2F892E3E53586AULL, 
            0x4B607742B807F8D9ULL, 0x03775A686D696778ULL, 0x6B76BFA1720CD32AULL, 0x0E5AB43B7B48718FULL
        },
        {
            0xE789B603F9DFD39AULL, 0xE0B533D5E4751B0AULL, 0xAD93E6976DAE5969ULL, 0xFB6AA67EEE749797ULL, 
            0xF2905257F4155B67ULL, 0xBAA17E53EEFE2214ULL, 0x279C637BB468ABC6ULL, 0xED87C3D8DE2A2754ULL, 
            0x1E9DED149230480BULL, 0xF162FE96B8FB0C89ULL, 0x777AC9BD0582C6CEULL, 0x9C76B47631202FAEULL, 
            0x7371D3088444ADABULL, 0x4316BBE5BEA79C90ULL, 0xBD5514F491CBD7C8ULL, 0xA81C882ACEC8EFECULL, 
            0xDC4431348C5DF558ULL, 0x08380AECF62CC004ULL, 0xB2CDF864D450EF78ULL, 0x5B93B17A84537C58ULL, 
            0x248F8939A4DE90F6ULL, 0x97070C2334466A39ULL, 0xEBB9CC321CCB4417ULL, 0x7082BAACD8ABD1C3ULL, 
            0xB0745C72E4B53526ULL, 0xD54761A72179504FULL, 0x69F9C30D0DF9C9C9ULL, 0xFE5E7DAF6854EB54ULL, 
            0xCA51B2F6B6C7EC9EULL, 0x997E4A482F7799EAULL, 0x8312DB0A962AFC28ULL, 0x9858519CDEAB1253ULL
        },
        {
            0x4AE9F5E57D98C7A6ULL, 0xA099F6E7CFA0B6C3ULL, 0x8D712EC04F6A8CD9ULL, 0x452360E1585F5355ULL, 
            0x0D2670D8A2FCE9B3ULL, 0xC263A969329D95F5ULL, 0xC2E5E067C56F739DULL, 0x8A533E6525DFF701ULL, 
            0x9D6257AB1A739E96ULL, 0x839CCD3ABB2F73F6ULL, 0x84B57B9766E01CE6ULL, 0x6ECDC0E1687EA47FULL, 
            0xAB3EE204048F4A47ULL, 0x396B3FB18351EB32ULL, 0xC7FD10FC9AFFE259ULL, 0x2B3E34C64433FDBEULL, 
            0x605D3EF1891671EAULL, 0x57C51AE9B8474118ULL, 0x7DFD0717F0300A95ULL, 0x8DB946BB3B096CEFULL, 
            0x7B7C1EB06CE9A3E2ULL, 0x2B1C6051C794DEACULL, 0x38ADCA1387E8FCA8ULL, 0xF0BDCBD5BC1860A1ULL, 
            0x6DA31734F38E212BULL, 0x9FD11DF087485D2FULL, 0xA217B285ACCCFB5EULL, 0x6342360372BBA5DBULL, 
            0xD8961C462B8F210BULL, 0x9C4E5D482AB45BD1ULL, 0x0D2B806432E4EEFEULL, 0x5A51345321CEC4A5ULL
        },
        {
            0x9308E92E8A3FFDD6ULL, 0xECCEAB50A100555EULL, 0x186EF08B705CBAE8ULL, 0xFBDDE9D72E10B9DCULL, 
            0x688F674076D93060ULL, 0xA3039A1460D25C85ULL, 0xBEE6D4D53A9342E2ULL, 0x9BC684B5388061D9ULL, 
            0x69D238CE367C6C03ULL, 0xA8035B8261E5E8E2ULL, 0xEB43306EDAF421E8ULL, 0x8FE447F9B9A870B0ULL, 
            0x305EF172CC01BBF5ULL, 0x45882AA31A2F1F82ULL, 0x213454340337CB3DULL, 0x94FC8D0AB922C97CULL, 
            0xDECAB5EF4747AE78ULL, 0x11A1A0DBC32DCD12ULL, 0x25B5759326AB12C9ULL, 0xF6B4263783556825ULL, 
            0xBEBB7607110E48F2ULL, 0x11E681A5B2502F49ULL, 0x3A8F4AF7E1145483ULL, 0xE0859A25B24B04FCULL, 
            0x217370B647801710ULL, 0x376CD6B37C5FBA50ULL, 0x4069FF72B90B5195ULL, 0x884F70252C2FE106ULL, 
            0x4B002AAA29651E88ULL, 0x308F78C6E411CC0CULL, 0x3C7874070FE23917ULL, 0x15F1E0AECB926D38ULL
        },
        {
            0xF3D07EF492D6DFB3ULL, 0x45CF054BE87B225EULL, 0x196723071FF22D35ULL, 0xCD53EB12FFDB68B9ULL, 
            0xA9C557A23DE909F4ULL, 0x5E42B45ED3F6D1E7ULL, 0xD2F52CC436E53FA2ULL, 0x88C32F80EB6FADAAULL, 
            0xB901564810B9F34AULL, 0x415F2F2438538692ULL, 0x7ADDD1F23BB9A0E0ULL, 0x3702F418B00D77F5ULL, 
            0xC0EED169FE2AE018ULL, 0xA3EB6351A3AF43D7ULL, 0xA0D6F803E1083F1BULL, 0xF3BA1323FA92BD5FULL, 
            0xAC99192F7B74788EULL, 0xF2C422932D09F547ULL, 0x5CC74B3641760A3BULL, 0x18A84FE4FB63939AULL, 
            0x77ECD7BD9CF070D0ULL, 0xAA002C9214B5E3CBULL, 0x195866C2DDC856C3ULL, 0x1F3703BDD912C8ACULL, 
            0xC18E423697447846ULL, 0x4840A13081E3FC42ULL, 0x1CD2D6073072727BULL, 0x23E67DE6567907B9ULL, 
            0xBCE2988B076B1170ULL, 0x93DDCBE2E6C40793ULL, 0xAF8775052CABA81AULL, 0xB8F8333E280420CFULL
        },
        {
            0x440187E09A845C91ULL, 0xCABE6753C30D05F0ULL, 0xBAEB5C56C0AA77C3ULL, 0x5AE5BB6AFCFFE67EULL, 
            0xB953BD0EADBC1061ULL, 0xB37610A4730720F1ULL, 0x6EC1B74B2AD66382ULL, 0xB9FB881071BC13D6ULL, 
            0x323414425453E89DULL, 0x3F1CC36243A0715CULL, 0x54CD6AF231A5413DULL, 0xAB9EBB3DB6C9E123ULL, 
            0xB40D2E8E309B1AF9ULL, 0xE401918B07B3FCDFULL, 0x3963B70EA9634A02ULL, 0x0DCAFDAEEE29C2F6ULL, 
            0x146F3EE2625D0B71ULL, 0x4B91BEC88C9382F3ULL, 0x95CAA14A189DEDEEULL, 0xB9291E0E93AD8986ULL, 
            0x1C4D136D8C0CE432ULL, 0x522692FA02E91356ULL, 0x2D630CC63B6C12B1ULL, 0x00B1D6A126DA64A6ULL, 
            0x5E5893DECA90CF47ULL, 0xDC82FB0541E567EBULL, 0x123CB246C2621CADULL, 0x459F884203B51E0BULL, 
            0x8E76F9DAD943AC65ULL, 0x81CA20DB056E91CBULL, 0x194A803D20A634BEULL, 0xD31D0F7BA50A3E05ULL
        }
    },
    {
        {
            0xA4697B33243A86F5ULL, 0x0A3F3CDBC87DF260ULL, 0xFB3998419B70E767ULL, 0xA3E646A95180A795ULL, 
            0x1CB9559D3E290684ULL, 0x7A421BB73F04B5E2ULL, 0xA27D3E47300D491FULL, 0x2FD1E8BB13C7A9DDULL, 
            0x579B70BCEBE6F430ULL, 0xB97579F3D975618DULL, 0xEA668EB229C7F6CDULL, 0x4BDB7B551C110C23ULL, 
            0x1CC22CD051128739ULL, 0xD5ACF8C4E57E3472ULL, 0xE2F89AA611E2603CULL, 0x1B361454A72054CEULL, 
            0x00AADFE2726DF914ULL, 0x10C5AA7F24944F0AULL, 0xDDEADF65096B2BBBULL, 0xDD53FC91849561C0ULL, 
            0xFEDC5B97E3627A10ULL, 0xD6612395BF9E7C87ULL, 0x751D7697BD3CA953ULL, 0x3D1F6860D42E5353ULL, 
            0xF961441232D51A19ULL, 0xE5827D2D311F4E3CULL, 0xFAB3F18AF5B598D4ULL, 0x726DA354A3D522A5ULL, 
            0x5BF7EB59A2F120C8ULL, 0x3B16167B0C40D826ULL, 0xB3ED4D39AAAE7A02ULL, 0xE25CBFE3C45D1E3AULL
        },
        {
            0x6665D70E48DACAF0ULL, 0x0D4BBCDC64A55FB1ULL, 0x80AA76B414A7DD49ULL, 0xF649D075B787D829ULL, 
            0xDC123CB9A79A85DEULL, 0x34582C7AD5920DDCULL, 0x34C183E4A2CE42BDULL, 0x51048ED8DA0F4D22ULL, 
            0x518C7466DE8912AAULL, 0x59F5D93ABD210E9FULL, 0xC87F88B13F8E2A5EULL, 0xE8D2853D400CE654ULL, 
            0xE65DAB4E39751E4AULL, 0xAC2A7FC87F734C3AULL, 0x6E9317DA176E033DULL, 0xCFD335D21AB29907ULL, 
            0xF7ACCC2BF43B5A9DULL, 0xFF90A60CF4D63E65ULL, 0x40F513280E394C81ULL, 0x0AAFE0ECFDC3E5F8ULL, 
            0x9C11842BC97C30CFULL, 0x874A086C151480D5ULL, 0xF3B168CDE20FD1C0ULL, 0x4FA25C6B88AC8695ULL, 
            0x9B4E769A5BA26CE9ULL, 0x31276EB847DA73D2ULL, 0xF0CC80420D22D504ULL, 0xE0B507B1A2F927C6ULL, 
            0x7AA66C9092ED49B6ULL, 0x7A243B3EF81A9CF5ULL, 0xD96FEDB5D7EE71EFULL, 0x9D221DC31BE36A02ULL
        },
        {
            0xF43F59519F040425ULL, 0x96606DFAF945606EULL, 0x09609F3F5F4325E5ULL, 0xE58B96ECF15B48A0ULL, 
            0x1B8700ED07F82964ULL, 0x96A40041F5FDE2CEULL, 0x46A50DDEA54B6C42ULL, 0x02C0F0B6EE20E081ULL, 
            0x1D6AA09EB0B427C6ULL, 0xD0D98AB274CF1342ULL, 0x009B04184465E327ULL, 0x448B9C3759F2D029ULL, 
            0x24FB832981C83261ULL, 0x79CE4DBAE1E93AF3ULL, 0x37B7D667557E268AULL, 0x59E85F48E87152F8ULL, 
            0xB4BA0CD75804B6E6ULL, 0xE53759B5B166AF99ULL, 0x459A8D021A090B59ULL, 0x0877DB05C3572AA4ULL, 
            0xC163B8C20BBD7FCEULL, 0x73C91138E7AB448FULL, 0x56ABECDAC68CD27EULL, 0x9CA151C16E2CE286ULL, 
            0x28902DBC92CD022EULL, 0x99F554EACAB7CC95ULL, 0xE82785CE2A162066ULL, 0x61B753C92924EEF2ULL, 
            0x505D1ECB53ED1920ULL, 0x386E98126866A285ULL, 0xE66FCD9E39D66375ULL, 0x05B4E2E6766315FBULL
        },
        {
            0xDD4B1F022C16F655ULL, 0xE68D1171EDBF347EULL, 0x985739CEA2B47373ULL, 0x5C27DA654FC9CBC1ULL, 
            0xA41CA9A82B6C7B2DULL, 0x52362E2D69FCDACCULL, 0xF1A0728BF9D75633ULL, 0xCBEE855BAC848114ULL, 
            0x5E44AF6EED53D397ULL, 0x4E8BA3414B8753BEULL, 0x7494D9B94EEEA248ULL, 0x64CAFA03ADDD84FBULL, 
            0xE2E331EACBB8D834ULL, 0xA7F2D47FC44D27C6ULL, 0x8A373C0D9431AE64ULL, 0x6AB2310C9E8CBD63ULL, 
            0xCA47BDDE345466CBULL, 0xBCD883E94151A87EULL, 0xBFF0F5976B31D864ULL, 0x91DB54DB54B7CC5BULL, 
            0xDCC2E43C602CC986ULL, 0xD9AF578EBECFF881ULL, 0x1527B72D791CAE98ULL, 0x2F9116BF6A9DD6A7ULL, 
            0x15F6D40FD5C85D05ULL, 0x9A16DDC0414C5BB2ULL, 0xA94EAE36CD794E77ULL, 0x702F6153A4AB317FULL, 
            0xAE2DB08683E8A5FFULL, 0x6458A66A8A07C088ULL, 0xA954DE3B544B5FD7ULL, 0xD41919D1D2233ABBULL
        },
        {
            0x957AC09A398F927DULL, 0x5B573143D98B5C73ULL, 0xE2C8DEF9F8FBE48AULL, 0x450AAB6045AA8C66ULL, 
            0x46A10064FA781B2EULL, 0xF3542CD0AD660FCFULL, 0x6C259DE3B9898AC7ULL, 0x523E15899AC5585CULL, 
            0x5D1BBD88338AC39EULL, 0x2F32EC32843A9DC4ULL, 0x3F3DB2E233382AB0ULL, 0x33D641E9A96E0D0EULL, 
            0x227D9C493D8DEA00ULL, 0xF73354A7CC74094BULL, 0xE68565B6B37A799BULL, 0x4BE2F1E2927E2565ULL, 
            0xF982E59343FAD1D5ULL, 0xE4609444CF87C00EULL, 0xBEF31B82596908C5ULL, 0xA195F70470FA6E8CULL, 
            0x83694AA71D3AAB85ULL, 0x0F0AC6FA6297830BULL, 0xD457C5EE00555CD4ULL, 0xBFEC4CBBC4B3555EULL, 
            0x0E0F5B7F41D2D9FDULL, 0x750246DA66082BD7ULL, 0x11F2ACAD1CF369D5ULL, 0xBE07F152F8857C06ULL, 
            0xC90ABDB7C09E35C9ULL, 0x2ABB6B568D65F244ULL, 0xEC0136B7D8CB11BFULL, 0x137C0F5E3F316640ULL
        },
        {
            0xCFFCC2BD84D457F0ULL, 0xF638DC18E549C269ULL, 0x5D46E1CC58851F52ULL, 0x5875FFFBBA911273ULL, 
            0x8D8E4D5D1B3E9B12ULL, 0xEB941D35456FFDBBULL, 0x6A178EF00526C40BULL, 0x5BB09DD0C0105020ULL, 
            0x2FD2FA5E86D6C1C5ULL, 0x562FC8E611A4AACFULL, 0xE5801116C6AC09ABULL, 0x7012DFFB71EF0361ULL, 
            0x63EBF95B826A559DULL, 0xF2F285ABAF8A0718ULL, 0x39FA0CE65EAC229CULL, 0x06BB2A499F094FD7ULL, 
            0x0B678143BA2EF00AULL, 0xB1590F7CBD997996ULL, 0xF72D7B311AEFD984ULL, 0x64B7CEBEA0D61B86ULL, 
            0x303A67E81F322FCCULL, 0x6CF4EBB9935A3254ULL, 0x7E4B6D85730771D9ULL, 0x93A830521CB91558ULL, 
            0x8ADABF7487B6BF86ULL, 0xD2176F37BA9E4B5DULL, 0xA25C29C36349A519ULL, 0x88319AEA5978136DULL, 
            0x593D53E670F097C7ULL, 0x2F37548B4D3DC7A6ULL, 0x45DC421F4BE14653ULL, 0xB87F4930C04BB9A3ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mothallah::kPhaseHConstants = {
    0xA8598AC98DE5D897ULL,
    0x1688B81055B91F08ULL,
    0x9111BB37A3EDFCB1ULL,
    0xA8598AC98DE5D897ULL,
    0x1688B81055B91F08ULL,
    0x9111BB37A3EDFCB1ULL,
    0xC6024357C24D1C55ULL,
    0x90260D694A2CBB00ULL,
    0x4A,
    0x9F,
    0x04,
    0xDD,
    0x67,
    0x23,
    0x98,
    0xFE
};

