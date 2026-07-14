#include "TwistExpander_Canopus.hpp"
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

TwistExpander_Canopus::TwistExpander_Canopus()
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

void TwistExpander_Canopus::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xFA03B980B4961FD0ULL; std::uint64_t aIngress = 0xB09562AF269B0818ULL; std::uint64_t aCarry = 0x8CAAE3E9A9192319ULL;

    std::uint64_t aWandererA = 0xB809765BA566BCCAULL; std::uint64_t aWandererB = 0xC3E35F05D71AB34AULL; std::uint64_t aWandererC = 0xEBEB44A53F362623ULL; std::uint64_t aWandererD = 0xA777CFA352174468ULL;
    std::uint64_t aWandererE = 0xDE5678125D9896E3ULL; std::uint64_t aWandererF = 0xEAA4629852A3228CULL; std::uint64_t aWandererG = 0xA1B342B5AED9C20FULL; std::uint64_t aWandererH = 0x94DA1E2575D7259BULL;
    std::uint64_t aWandererI = 0xAA5FF638D19C686DULL; std::uint64_t aWandererJ = 0x831F5A449CF8CD5DULL; std::uint64_t aWandererK = 0xB882B7DE0C47C0E2ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 9301353271120801634U;
        aCarry = 16911760845616191449U;
        aWandererA = 12768490948188212547U;
        aWandererB = 12030114002362880972U;
        aWandererC = 11527960939943066736U;
        aWandererD = 17791840355572352154U;
        aWandererE = 14446442388883343578U;
        aWandererF = 9360311663942805930U;
        aWandererG = 12110469865589054943U;
        aWandererH = 13772587531880187686U;
        aWandererI = 16824264305582591468U;
        aWandererJ = 14453310156479027769U;
        aWandererK = 14543646381363572928U;
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
    TwistExpander_Canopus_Arx::KDF_A_A(pWorkSpace,
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
    TwistExpander_Canopus_Arx::KDF_A_B(pWorkSpace,
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
    TwistExpander_Canopus_Arx::KDF_A_C(pWorkSpace,
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
    TwistExpander_Canopus_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Canopus_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Canopus::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xA8302CCDB1DEAFADULL; std::uint64_t aIngress = 0xD7FECFF843DF3736ULL; std::uint64_t aCarry = 0xC0E8FF2FCA6575C3ULL;

    std::uint64_t aWandererA = 0x9E43640B3948ED79ULL; std::uint64_t aWandererB = 0xDE4617BAF5F63046ULL; std::uint64_t aWandererC = 0xEA7293D4CB3F289BULL; std::uint64_t aWandererD = 0xD4DC680CD9D2A409ULL;
    std::uint64_t aWandererE = 0x8E3DFD5D7C04A09FULL; std::uint64_t aWandererF = 0x9CC18D4BC4ACB1F5ULL; std::uint64_t aWandererG = 0xDA6E17ACC2C84EC7ULL; std::uint64_t aWandererH = 0xAEEE2779CF654C0BULL;
    std::uint64_t aWandererI = 0xB7F409EACC6FA575ULL; std::uint64_t aWandererJ = 0xCED245155D58F554ULL; std::uint64_t aWandererK = 0xD3089B2F9F0F627CULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 18410694275972516558U;
        aCarry = 12672819362429186485U;
        aWandererA = 12819005953348047443U;
        aWandererB = 15830008756563768176U;
        aWandererC = 16325274543293756243U;
        aWandererD = 16885789947731575382U;
        aWandererE = 9387479045043943777U;
        aWandererF = 17626400517271651936U;
        aWandererG = 11887420409915285914U;
        aWandererH = 17051232452377344054U;
        aWandererI = 11306204663172596954U;
        aWandererJ = 11868510189837819054U;
        aWandererK = 10827387548493774402U;
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
    TwistExpander_Canopus_Arx::KDF_B_A(pWorkSpace,
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
    TwistExpander_Canopus_Arx::KDF_B_B(pWorkSpace,
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
    TwistExpander_Canopus_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Canopus_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Canopus::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0x89A956EB91EEC4DCULL;
    std::uint64_t aIngress = 0x99049629F5625C9BULL;
    std::uint64_t aCarry = 0xEA6F45B0304244B4ULL;

    std::uint64_t aWandererA = 0xBDA0B366B9B5D0D5ULL;
    std::uint64_t aWandererB = 0x857C04DE225B2A0EULL;
    std::uint64_t aWandererC = 0xB2E7DEEF1A341335ULL;
    std::uint64_t aWandererD = 0x8D03298D8097E1AEULL;
    std::uint64_t aWandererE = 0x8FFC00BE6034AAB4ULL;
    std::uint64_t aWandererF = 0xBD1A024A5C9AA389ULL;
    std::uint64_t aWandererG = 0xA1851EFA27C161FCULL;
    std::uint64_t aWandererH = 0x98F0400F75F641FDULL;
    std::uint64_t aWandererI = 0xBA1A934E4FEA860AULL;
    std::uint64_t aWandererJ = 0xB3EB3ACCC591C859ULL;
    std::uint64_t aWandererK = 0x9A441CD7310F9B68ULL;

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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneH);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneA);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneC);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneD);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneG);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneB);
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
    TwistExpander_Canopus_Arx::Seed_A(pWorkSpace,
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
    TwistExpander_Canopus_Arx::Seed_B(pWorkSpace,
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
    TwistExpander_Canopus_Arx::Seed_C(pWorkSpace,
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
    TwistExpander_Canopus_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Canopus_Arx::Seed_E(pWorkSpace,
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
    TwistExpander_Canopus_Arx::Seed_F(pWorkSpace,
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
    TwistExpander_Canopus_Arx::Seed_G(pWorkSpace,
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
    TwistExpander_Canopus_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Canopus_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Canopus_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Canopus_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 14 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1838 / 1984 (92.64%)
// Total distance from earlier candidates: 24142
void TwistExpander_Canopus::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 443U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1133U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 101U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1111U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 389U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 433U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1820U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 650U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 982U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 880U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1494U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1515U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 2040U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 971U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1564U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 182U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1656U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 799U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1469U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1215U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1594U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 872U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 662U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 858U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 59U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1360U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1122U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1021U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 135U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1420U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1449U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 876U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1955U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 2022U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1655U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 891U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1200U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 17U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1809U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1435U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1696U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1584U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 617U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1256U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1796U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1626U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 374U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1312U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1770U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1085U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1927U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 458U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 429U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 2023U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 525U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1545U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1811U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1815U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1016U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 0U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 42U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1269U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1003U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1491U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1649U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1349U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1959U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 45U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 868U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 995U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1115U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1236U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1418U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 138U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 234U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1429U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 855U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 800U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 465U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1072U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1322U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 100U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1636U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1279U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 23U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1608U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 648U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 860U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 361U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 104U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1548U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 149U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 249U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1982U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1744U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 796U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 466U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1918U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 131U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 883U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1185U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1368U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 892U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 235U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 231U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 394U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1695U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 373U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 422U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 790U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 642U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 545U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 30U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 405U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1393U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 709U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1710U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 492U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1742U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1917U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 289U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1885U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1238U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 179U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1835U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1908U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1358U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 166U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }
}

void TwistExpander_Canopus::TwistBlock(TwistWorkSpace *pWorkSpace,
                                       std::uint8_t *pSource,
                                       std::uint8_t *pDestination) {
    TwistExpander::TwistBlock(pWorkSpace, pSource, pDestination);
    if ((pWorkSpace == nullptr) || (pDestination == nullptr)) { return; }
    std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    std::uint64_t aPrevious = 0xA671F0F433CA8298ULL; std::uint64_t aIngress = 0x83FDC84E853D4490ULL; std::uint64_t aCarry = 0xC6DA08C45BCF4CA8ULL;

    std::uint64_t aWandererA = 0xCD7DCFB827AB6B11ULL; std::uint64_t aWandererB = 0xCE943BCC09A2EB22ULL; std::uint64_t aWandererC = 0xCD6C09FDAB2EB1DDULL; std::uint64_t aWandererD = 0xACBF74637C6AF8B9ULL;
    std::uint64_t aWandererE = 0xF259BABDB9DFAA4DULL; std::uint64_t aWandererF = 0xC58ACE57B2CD9896ULL; std::uint64_t aWandererG = 0xDD302B26DC396C4CULL; std::uint64_t aWandererH = 0xBBABB708C2957DDDULL;
    std::uint64_t aWandererI = 0x91913DB3367DF2ADULL; std::uint64_t aWandererJ = 0xF6A6842D71762406ULL; std::uint64_t aWandererK = 0xFD5D34F90C7D4555ULL;

    // [seed]
        aPrevious = 15623899658074883247U;
        aCarry = 9455689167142865472U;
        aWandererA = 10573136064903261219U;
        aWandererB = 12876227728734089673U;
        aWandererC = 9685343008128918376U;
        aWandererD = 9626962796925065772U;
        aWandererE = 17199289375996000838U;
        aWandererF = 14190960559839560350U;
        aWandererG = 10969858721809861156U;
        aWandererH = 14771139650359343527U;
        aWandererI = 12295822285183776296U;
        aWandererJ = 11318181844795917655U;
        aWandererK = 12846655218663246034U;
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
    TwistExpander_Canopus_Arx::Twist_A(pWorkSpace,
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
    TwistExpander_Canopus_Arx::Twist_B(pWorkSpace,
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
    TwistExpander_Canopus_Arx::Twist_C(pWorkSpace,
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
    TwistExpander_Canopus_Arx::Twist_D(pWorkSpace,
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
    TwistExpander_Canopus_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Canopus_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Canopus_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 14 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 7120; nearest pair: 509 / 674
void TwistExpander_Canopus::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5994U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2962U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7432U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3749U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3506U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2853U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7698U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5188U) & S_QUARTER1);
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
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5133U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3863U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4178U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3000U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1275U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1204U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3963U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3710U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 947U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1327U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 604U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 515U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 788U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1565U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1911U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1844U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 170U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 387U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1175U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1785U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 671U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 753U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1285U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 46U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1613U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 217U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 870U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1031U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 14 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 7134; nearest pair: 474 / 674
void TwistExpander_Canopus::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3894U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3649U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6433U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6246U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3606U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4842U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6771U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6940U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6660U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3795U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3369U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4701U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1471U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2528U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2638U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5523U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1192U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1150U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1207U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1732U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 943U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1210U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1862U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1431U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1316U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1907U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 300U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1603U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1310U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 144U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 343U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1681U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1152U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1405U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1754U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1619U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Canopus::kPhaseASalts = {
    {
        {
            0x5CF1363195069334ULL, 0xB9FA32F049ECFB2FULL, 0xF5C310586F97A15EULL, 0x7B4517732FC5955AULL, 
            0x8F1A6547CF17B669ULL, 0xD7C4CD70784D0B7BULL, 0x1C00AECD27C32C84ULL, 0x1DB85E07BE55E473ULL, 
            0x15CA86B0795D9861ULL, 0xA5351AEAEF70A509ULL, 0xD18E9E74758543C9ULL, 0x3A0155134CBD68F3ULL, 
            0x4C1318055718C129ULL, 0x4A55EF06850E6E42ULL, 0x957B93C38D4046C9ULL, 0x842862466532DB32ULL, 
            0x7B012DD2D3430F84ULL, 0x67B3083EF1F05836ULL, 0x2DB4898A8996797FULL, 0x9674C0C2CDC20EABULL, 
            0x333C7ED9FF52B240ULL, 0xA111117B5E4CC3A9ULL, 0x686640943A1B5ADDULL, 0xFB38C56A9E406E11ULL, 
            0x64074EF91BCCB0B3ULL, 0x2E639982E45ABE99ULL, 0xBBB70DDD95ABCF57ULL, 0x31BBD2E90E233EA7ULL, 
            0x20FBD2C8D2305F03ULL, 0xAD3FA68274E9945CULL, 0x3851283766F71608ULL, 0xAA87524ECC5A6BD3ULL
        },
        {
            0x617EF5F357DF72A5ULL, 0xD2D6085F06E8968CULL, 0x40A1A1632289A609ULL, 0xC57CECCA01A42807ULL, 
            0x0881384120357473ULL, 0xE2366E9C799CD441ULL, 0x09EEE1F0C4CF10F5ULL, 0xDF9D83CD7B0CB6DCULL, 
            0x5B112167F14D7806ULL, 0x11ED3917D00C0B99ULL, 0x19FF400ACC7C7B6DULL, 0x6471B957FAA14E65ULL, 
            0xB5C2650326C579BDULL, 0x3071327FA6E7AB91ULL, 0xE956CB23084E7922ULL, 0xBA5B56674F5DF182ULL, 
            0x002A63D35BF6F60EULL, 0xE7E3A0FE3B0F57A7ULL, 0x293EE22D77B6199FULL, 0xC497A8A0FDD2E5F4ULL, 
            0xEFE15CF25C0A8760ULL, 0x35C6FBDAEBD1CF8DULL, 0x6C87A7D601C5B2A7ULL, 0xEAC290CB5527EF29ULL, 
            0x4342DFF0AB3B556AULL, 0x0A8AC2615BA0695FULL, 0x25001AFEA40B078DULL, 0xC5E9CB88F0A79C7AULL, 
            0x8748687FB376AD18ULL, 0xC7A909D24DCB1C74ULL, 0xB8551AA25FBEA2A9ULL, 0xD89AD95D80748193ULL
        },
        {
            0x78EAD92E397CF70FULL, 0x5F8F2622B1BC0AD8ULL, 0x75E2841EA5AEC8AEULL, 0x3D7A1FAE18F5EA91ULL, 
            0xC09724FC282B563EULL, 0xF1BAA0F88776B45CULL, 0x1F7165CE7D69CF64ULL, 0xC1739BF9F28C463AULL, 
            0x217B07AF250890A9ULL, 0xA747AF278C905366ULL, 0x0B255EBBAED888BBULL, 0x5084A5E098C35D47ULL, 
            0xD882846EF1F7704DULL, 0xC73D31A32252971DULL, 0xF0DE0C171D5CD430ULL, 0x1DB191F241C9C2C6ULL, 
            0x713021F44D9ED930ULL, 0x139C6A5C2B0AC10FULL, 0x591EA2B22A7C00FCULL, 0xA4FE059548C4168BULL, 
            0x737792B828009170ULL, 0xBC4F8DBA805E2F38ULL, 0xEFA77B2DF2691870ULL, 0xEDC1AD6E0A7C6C3BULL, 
            0x36CA976CA7BA35B0ULL, 0x115FA957374045C4ULL, 0x92E0A24BF0383A1FULL, 0xECAC52DA9D843395ULL, 
            0x02DF95EE76161F1BULL, 0xF1BB9BF25FB942FCULL, 0x215B8526EC402CB7ULL, 0x490CFDA1F5FACCD7ULL
        },
        {
            0xC5A3A0C8481980F0ULL, 0xA4C9BF2C7C52E217ULL, 0x1136D143CE52905BULL, 0x3A0E673E10388441ULL, 
            0xA68DB76BF0F9CBF1ULL, 0xD97A2D45312A0746ULL, 0x36147248908364D9ULL, 0x694DA6276DB1CB5DULL, 
            0x0BB0D6DB826A7015ULL, 0xE6654481357B1AD5ULL, 0x83FD55975E964FEBULL, 0x62A0108218254DAFULL, 
            0x879B69BE88D4B62CULL, 0xD1E186AC438D0B6CULL, 0x5807FFF761A57AECULL, 0xB83F0173DDA65C3FULL, 
            0x06BEA9B083A4201AULL, 0x1E26A8FE7DB9ABC2ULL, 0xDF6D70739DD76814ULL, 0x055210392B21B12AULL, 
            0x64DEFD5BCF259920ULL, 0xD9BB2F0B9B6F5FE5ULL, 0x9C33DC530DC03E90ULL, 0xE245C2E30A1EF474ULL, 
            0xE772E9DC1902C1F1ULL, 0x338F6DA22517AE1BULL, 0x6E1E125702BFE7EEULL, 0xAD90BFC70DA8A0E3ULL, 
            0x27926536B87E44E9ULL, 0xEA7FF81449A9189BULL, 0x37D5F944E45373FEULL, 0xE30B16B42FD8B271ULL
        },
        {
            0x20EA27F314F09E74ULL, 0x53EC76CD5A53774AULL, 0x6E66321FC28875CDULL, 0x4ECC18F78B075247ULL, 
            0xD4DC44EBD8F773E7ULL, 0x7881ABF28AC05179ULL, 0xA26CA6E133EAD360ULL, 0x2E3B0188E0FCCA9BULL, 
            0x77EAEEE92C28C66FULL, 0xF96C76738F09D1FEULL, 0x533BB5F22E2D5B13ULL, 0x9B8FA020E0758EEBULL, 
            0xDA9FD342A16628A6ULL, 0xB38D407FDBD4BB24ULL, 0x3FCF7CC90D689AC0ULL, 0xF3D6CA5D452E937FULL, 
            0xA6B6467C69EE9043ULL, 0x6E8CF9FF27B573F9ULL, 0x298E66CF5408F66CULL, 0x361A496A8DFB3590ULL, 
            0xED95890E507A4ED0ULL, 0x74A8FFCF90E147E3ULL, 0xA1F197964A5219A8ULL, 0xEAA3EA4D292E3EB1ULL, 
            0xFADB44D10F6D8E6EULL, 0xB2D6ECBA94D099E4ULL, 0xB69849F159B11AB5ULL, 0x506985D9A631E07CULL, 
            0xB711F2B93310DCBDULL, 0xA0B90D00D412A424ULL, 0xDD505A9A313C0E31ULL, 0x0D80F83FBB20FC38ULL
        },
        {
            0x31C1CE037E0F63FEULL, 0x892AB61E35DB26EDULL, 0xD38FCC75A74FCC61ULL, 0x410FBA4A981A6F2BULL, 
            0x970CFCF607B85A4FULL, 0x6CB492DF95C9F513ULL, 0x91402A27999FE6E8ULL, 0xAA4F7E2CC455856EULL, 
            0x52D9CD0C5DC1FFA4ULL, 0xBC91C335A9605DD3ULL, 0x857209D20455DE10ULL, 0x592561D1E41803FDULL, 
            0x1EBE68A1E1C80E01ULL, 0x941BED3D397A734BULL, 0x79E1EAD41B91787DULL, 0x1078087E29BFB24AULL, 
            0x4EE789673F5AA4DEULL, 0x8FBA7A2921B7E106ULL, 0xBF2B5A9A4C6CA786ULL, 0x53875E5BA297FDC8ULL, 
            0x34EA1C592D615B97ULL, 0x9388AF02459E55D1ULL, 0x07BC643326C43E4CULL, 0x0ECEC680E5C91D53ULL, 
            0x97ED3E52D1F192E1ULL, 0xBCCB324BE8BA3880ULL, 0x2EC3DF19DC61F80AULL, 0x3AA8FDA98A46A02DULL, 
            0xDCAA766BA0AADADFULL, 0x6299F4B472A07AC2ULL, 0x4CDAE95FAA4FBE11ULL, 0xA1A2E6CB6BE1B2BDULL
        }
    },
    {
        {
            0xF1365F14AAF0B533ULL, 0x3836790731E3D198ULL, 0xD005488E6CD0D047ULL, 0x2A29009C44FAFFD3ULL, 
            0x7F7325F1975AF82CULL, 0xD6B709CCF5EB6C6EULL, 0xBFACBD4BAB96B668ULL, 0x92E304403EF57E8AULL, 
            0xFE6E582BEC6D7E9CULL, 0x21F4DECDC44D998BULL, 0xCC70163F565DD1E1ULL, 0xDADC32F2C7A6C40BULL, 
            0xCAB967A44184FB1FULL, 0x4FA5F6795136B0DEULL, 0x3BF55C843191CDC7ULL, 0x076A291A4DC14EC8ULL, 
            0x0ED36F1EB72790C3ULL, 0xEEF2937A9662C065ULL, 0x50825E2C8E5CD387ULL, 0x881FF7BD198A1DC8ULL, 
            0xAF2AC369060B5957ULL, 0x2A3663A5FF149E76ULL, 0xF5BAD793D5BD7053ULL, 0x72940B38F7402112ULL, 
            0x4D489C806257D00AULL, 0xD98F0C791ECC36BFULL, 0x3EE3EB59635A5CDCULL, 0x1660F103D76850D1ULL, 
            0x39073C474B11D5EBULL, 0x7DD263A2C3553A07ULL, 0x5A3A9F310B41D8C0ULL, 0x65EBC3F3BAF3E4EBULL
        },
        {
            0x0760FB1583240744ULL, 0x468000442AA15B19ULL, 0xB00ED70C08E9C9CBULL, 0xC2A5BEC9E300DD23ULL, 
            0xF93AEEDDAAB0A2D4ULL, 0xBBC450346C23E2DAULL, 0x2CBB22283A9D7A6EULL, 0x00FE901A7296A075ULL, 
            0x097DD87C54F3D518ULL, 0x23EC6D15FFC44F0EULL, 0x4634F36057E957C7ULL, 0x2944180EE26CACBEULL, 
            0x67EAC5498759F4A5ULL, 0x433802928307B8EAULL, 0x53112FAE9613E08EULL, 0xE71F7E59BFA295D3ULL, 
            0x2A0D0245D38B3356ULL, 0xE8D9534C6C38D567ULL, 0x6165A69DDFE7DE84ULL, 0xCE2B5AA1539F084DULL, 
            0x1281CB5FAA8EC570ULL, 0x3218B50F68A14CA1ULL, 0x329654D96F802DF4ULL, 0x3792D3C3A3EC1FF9ULL, 
            0xD9C899FC1F0C0017ULL, 0x65CAA4C9022A3AABULL, 0x82D86F4C62A957A9ULL, 0xB72DEA878D0562E3ULL, 
            0x2D5BE17E3F45F238ULL, 0x0A917DD3B9AC3435ULL, 0x34CAAEBFFE71ACF4ULL, 0xA4018E2111A06025ULL
        },
        {
            0x45754868D0F334EDULL, 0xFC3EF47C06775D35ULL, 0x3FD37A66F5D4F8AAULL, 0x5CFD861AFE1F8900ULL, 
            0x873E26B5A7A68F3FULL, 0x81401E64DF0056B6ULL, 0x0D6290A60EE7A7B3ULL, 0x0F254058B2EB0323ULL, 
            0xD956EF6E6D712493ULL, 0x65ABD6E029E6BB34ULL, 0x9E946B809D55569AULL, 0x3C848C9F30AE7850ULL, 
            0xDA616E46966D534CULL, 0xEF10B6AB0B9B7A2AULL, 0x83A5D03983F51EB0ULL, 0x8E37004506C025CFULL, 
            0x9CA9409D27A9E949ULL, 0x9CB4D115CAE72923ULL, 0x2674A0498D4717F1ULL, 0x53814F2B30DDCD24ULL, 
            0xB85C38958D620C12ULL, 0xED790654D4A72031ULL, 0x27115754A6CC96BDULL, 0xAFA57DC7060B763DULL, 
            0xA0DF60F28668D614ULL, 0x020B55348041B93BULL, 0xEDAEE6C731206CB7ULL, 0x20C349D817BA9FA5ULL, 
            0x66D855E2FE2A1A2CULL, 0xBD31C4472BBDB49BULL, 0xCDD11542D57D17A1ULL, 0x623D3255D4827A3EULL
        },
        {
            0x2B1A6C36AAC88548ULL, 0x2906C98F95773730ULL, 0xEF718BAA4038EE08ULL, 0x71D6D24BC41B4EA7ULL, 
            0xF6B47417CD432B72ULL, 0xCFBBC7273BD2AADCULL, 0xE9528C87ECC36F3EULL, 0xC9B3323B5F59FA80ULL, 
            0xA18F18D5AC5C2532ULL, 0xAD2FD195DCF5BF2FULL, 0xC51EC1E9E853D1C5ULL, 0x84FB7AA88D18C016ULL, 
            0x4CCDECD3FF6CD168ULL, 0x2BB5DF2A05D0A6DEULL, 0x6045A8C3DB53DC6EULL, 0xC9A82EEE4AEFF6C9ULL, 
            0xA0CC5FC2DE074B12ULL, 0x49DCBB14D78C7C7AULL, 0xF4C5F57C9B3E28C4ULL, 0xB62A3430F6416495ULL, 
            0xFB706745F874763FULL, 0xEFDAFA471E3D52C9ULL, 0x8CC658B74ED86A1DULL, 0xC53D027FADCC659AULL, 
            0x9874CC7C4DF07E0FULL, 0x78093B8F51B53BD6ULL, 0x1B9BF0308B3D2FE9ULL, 0x21811BA42EB3B4D5ULL, 
            0xD5B2CA65EC57C521ULL, 0x5B31DC20F13FA631ULL, 0x0ABD0BD7194DFD9CULL, 0xD58CC1835504A46EULL
        },
        {
            0xD3705128FE3B2187ULL, 0x5F1CA27D1505E541ULL, 0x3A255B11C9901F48ULL, 0x9725905067DBECE0ULL, 
            0xFB378585F7884222ULL, 0x6B6F94F14A85D021ULL, 0x9094600A4D8EF0C8ULL, 0x43927301A51BEB65ULL, 
            0xB5E93F78E66261ACULL, 0x12D5FC02C5CF9D24ULL, 0x472CF8359D0A7E41ULL, 0x6C79D5D6FF7B78B2ULL, 
            0xDD7FCD60FBFFAD80ULL, 0xA0DD27276594934DULL, 0x1706E0761F2DDEA6ULL, 0x0F974007EAEADAE0ULL, 
            0x2026B416777B7265ULL, 0x63112AAAC68B9DEBULL, 0x5E5CA05C939F0CE1ULL, 0xF5D0F98A5E658DDDULL, 
            0x3094770EE752E50FULL, 0xC055590902FFD3C7ULL, 0x6027B480BAF9410CULL, 0x5F8184A5EBD19DE5ULL, 
            0xFDB5C9D557EC8333ULL, 0xB9060203E435E70AULL, 0xE8734FB7D8671A66ULL, 0x8BB519104EBF9F12ULL, 
            0x2AE9F5C9C644A73FULL, 0x5C60CB0C9F376EFDULL, 0xC1797D58C7B6E82EULL, 0xC5392B62BB80FD5CULL
        },
        {
            0xD77B722758326BB2ULL, 0xBB5F72CBA0CF33F0ULL, 0x412222A8388A84CCULL, 0x5D8384AF3F6F6EEBULL, 
            0x2D3B57EB9949D33DULL, 0x02AFED9CCE29A335ULL, 0xCBEE1D4206A5BF3AULL, 0x809EEB5AEF28FEBAULL, 
            0xFBD7DF59E4750DDFULL, 0xE7E26076CD82688BULL, 0x0E37F93013F3D4E2ULL, 0xF1F3DC0EF96D0211ULL, 
            0x7F775F038706129AULL, 0x9F291D9E3E713424ULL, 0x55F3278971EA9951ULL, 0xC7E288F04E309F53ULL, 
            0xEACC52C06D575C56ULL, 0x9C1FC0828A2F6E21ULL, 0x52ABE3820837D7B6ULL, 0x2012C5BD8825CB27ULL, 
            0x9C8D5F980CF21BC3ULL, 0x5BF3BAF82710E1FAULL, 0x2E1B82BCBAB22082ULL, 0x458B57DF72D518BEULL, 
            0x63B8BB9FDAB363B4ULL, 0xC92472A8454188EEULL, 0x85227CA7DC66E7C1ULL, 0x7420910AA8B778D1ULL, 
            0x5EC4D68774FBEFFFULL, 0x341D1951E322A0BAULL, 0x3DF01D8F0F96D644ULL, 0x8EE200C7F43F34DCULL
        }
    },
    {
        {
            0x7244E89A98F2F34AULL, 0xB5E79C29C016E3FAULL, 0x824CF6461686592EULL, 0xF9336D74B7727DADULL, 
            0xDF3BC8B52559A3E1ULL, 0x99CD7C8F03748634ULL, 0x758356ADE6BEE044ULL, 0x88474A039CF279B0ULL, 
            0x0BD5B67CAF7CC1F7ULL, 0x7B3DDBB285D101B2ULL, 0xEF67857AC745313BULL, 0xE904899AE5D21510ULL, 
            0x07348FAEFF3FB6EDULL, 0x6D52552897414D8AULL, 0x382A92DC7E4E706CULL, 0x2675563B521EA84CULL, 
            0x888E43ACF5EBC80BULL, 0x241936F82E90A5A0ULL, 0x3BE756D692662C6BULL, 0x8BB02CB0D1AEE375ULL, 
            0x092428C3383BEBABULL, 0xB7FE12AD025ECB85ULL, 0xFCEC137C1612A48AULL, 0x6E41E78AC462EAFEULL, 
            0xA867B1ACEF7AF607ULL, 0x8F6F2A5F6FAE29F3ULL, 0xE890AD65FF8E5460ULL, 0x52F29957277D37E7ULL, 
            0xB148F03C1F44923EULL, 0xEBA5698BAA422A00ULL, 0x0429CC98C3598D6EULL, 0x1F5E8F8F5BEFF92BULL
        },
        {
            0x98E0CF24650E3179ULL, 0xA33E891F3ACAD626ULL, 0x3EB1197CDAC5512EULL, 0x1E5387C0BEAADAD9ULL, 
            0x05998FD340EE5AA6ULL, 0xE8D371177ABE66C7ULL, 0x28ED1ECCF40833A4ULL, 0x75B5EE182BF606A3ULL, 
            0x5D0868816FD65FDDULL, 0x6C1E3B92E3101DABULL, 0xEE2F98BD967864EAULL, 0xE4D5616DF6823454ULL, 
            0x128EE0B482FA48A2ULL, 0x279A6AD4A1D42D1CULL, 0x5028ECE94D5DC158ULL, 0x44D61E4968FFF50EULL, 
            0x61B8E40F0B9FA348ULL, 0xC1E4102B956292C7ULL, 0x9184B00F1370B992ULL, 0x7F48AED90ABA00D8ULL, 
            0xF0765C2B55F2DA21ULL, 0x10C61836BB51074AULL, 0xE3D6A89B32DB307BULL, 0xBC706C02A6D0CA28ULL, 
            0x8B59AD4CFE9A04ACULL, 0xD49E829043CAA0EEULL, 0x80D28275C4E15153ULL, 0xA061E1DAC028C89EULL, 
            0xCDC0387B7989CB17ULL, 0x60935EB2489E4B07ULL, 0x38C358C62B565D9FULL, 0x813DDAE369FEEFD2ULL
        },
        {
            0x6BA83B9553A2681DULL, 0x4D7B19CE0E392499ULL, 0x0EE139CCC6BD3490ULL, 0xCCDF3906F7E8F28FULL, 
            0xD6AD4827BDF0AE63ULL, 0xBFBCD3013FA53873ULL, 0x5888EC9430ADF2BFULL, 0xEDD89F76C6C363DCULL, 
            0x87A547169E8E8289ULL, 0x682CF8F25797A72CULL, 0x8D30AD186B21FACBULL, 0x2138153400D5317EULL, 
            0xB59BC04E2017551BULL, 0x49C7C95BBE27BAF2ULL, 0xF7C9B11A61668007ULL, 0x7A7182D1A370B690ULL, 
            0x67E4C86A0B6D20F6ULL, 0x7A2B86892837C143ULL, 0x74A4B96BA7BC31C6ULL, 0xB22F859076B7449EULL, 
            0x7D425133C52F4F2AULL, 0x77119966B54255ECULL, 0xBAADF4B4D572AEB7ULL, 0x770A93F62B691BDEULL, 
            0x7ADF227501C2D430ULL, 0x221452D2AFB07270ULL, 0x645E1F150A99EF5EULL, 0xB415759143E54B0AULL, 
            0x2A41A61E2794E25EULL, 0x3930C7C42AD499ECULL, 0x87E970064601A943ULL, 0xFDDF7A71670CDD95ULL
        },
        {
            0x6C08355FA5C98232ULL, 0xF92D547748488C14ULL, 0x363E2C68DFA85844ULL, 0x678C3173452A3515ULL, 
            0x5C12FCE6D3BB4FEAULL, 0x1327B61EE376E943ULL, 0xF505B5D2A945A01FULL, 0x403F95A1160EF30BULL, 
            0x8BE6BBC3E3CD983AULL, 0x92AC0F8557394491ULL, 0x24EC6F3550A63C3CULL, 0x8A15AA775E79C856ULL, 
            0x080CAB2A09F687E3ULL, 0x5D866399D20B37D2ULL, 0xD274BB1647991ADCULL, 0xF5440B36BBB22BBCULL, 
            0xA9EE0FDD6F8F37B4ULL, 0x92D8CEC162CFB5BDULL, 0x0062832F8E052B66ULL, 0x65A8C3E4D5389E49ULL, 
            0x61DB43A398E2498CULL, 0x59C16C94B7F4BFA2ULL, 0xE492CE3ACAE4F1BAULL, 0x87AA0A0BC38F66E1ULL, 
            0xCC7B392ACF1F865BULL, 0x7442929CB7460857ULL, 0x95B1916C170D0799ULL, 0xEBDEA7A9F7E76479ULL, 
            0x73BAFAE0C92598FBULL, 0x5E5BEE51F5800423ULL, 0xCA3657FEF28C651CULL, 0xACBF8D3C4173469AULL
        },
        {
            0x5CC3470E72670A02ULL, 0xCD4F8999B4D3CDD4ULL, 0x36152A74D13FC084ULL, 0xCA4E5F72691597E1ULL, 
            0xB5B359660DA8A511ULL, 0x0097F6E31442E623ULL, 0x80AAA0C837243F31ULL, 0xFCF6DF66682A2DEFULL, 
            0xA8685EF5DB6304EAULL, 0xC4C3CBD0E113517AULL, 0x4A637608936A2B96ULL, 0xCD5DAA4DD4F061F6ULL, 
            0xDB498D662E2D16C1ULL, 0xD435E99C40F98763ULL, 0xA6562CC83674F54BULL, 0x484F51DB88067771ULL, 
            0x1B0C0457BAE868ABULL, 0x762F02ABCEC13981ULL, 0xB06FA7E93121A4C2ULL, 0x619A9A534828407FULL, 
            0x6B83B6D173A03239ULL, 0x90E8EE380CAD4F02ULL, 0x04233E40F252FDABULL, 0xF29307600CE4FFDEULL, 
            0x814FECDEBA766CA0ULL, 0xB3F86B2ED6237EC7ULL, 0xD47DFEB9D38A1CE8ULL, 0xAEA1FD293039666EULL, 
            0xD692495CC2F4E023ULL, 0x97991864FEDDFB4BULL, 0xE7683C14864DF6ECULL, 0x75D9167DD57C9C09ULL
        },
        {
            0xCBC48D60657F7D26ULL, 0x7805675E8CB00FC0ULL, 0x084426232366F520ULL, 0x96EADFA6167E787FULL, 
            0x6EC28156CF3FDF88ULL, 0xF4B9F49F48075DBBULL, 0xAE636B4B55251576ULL, 0x93A98C9C496B8997ULL, 
            0xF168A877254C0CF7ULL, 0x9F190341C875D65EULL, 0xDCE6970EBA04A98DULL, 0x02FE607244C569AEULL, 
            0x5B1B271EA85BEDCFULL, 0xC0651DD6F0E9650CULL, 0x7A7D324DDE1B5A98ULL, 0x4E97A94995783D62ULL, 
            0x4F7CFA912E2E7C49ULL, 0xEE0E566E55544EC6ULL, 0x1B2E402BD222B831ULL, 0xBDADDE3311AEBEFDULL, 
            0xBA4E4728D3FA0E14ULL, 0x0EAA6730AAE6B33CULL, 0xB34156D98BB9AB12ULL, 0xFBDC1FF9F442F435ULL, 
            0x3A4701F2448E874CULL, 0xC9798B0B923BE372ULL, 0x8F172376F1629BF7ULL, 0xBD44D8A51A1C4A4CULL, 
            0xC176378C756E65A2ULL, 0x10FB7190550334E8ULL, 0xFBF22B5FA8708836ULL, 0xFDF2677872AA924CULL
        }
    }
};

const TwistDomainConstants TwistExpander_Canopus::kPhaseAConstants = {
    0xCB6167045A75D4F5ULL,
    0x499B6295330AF342ULL,
    0xD52218F93DB579B2ULL,
    0xCB6167045A75D4F5ULL,
    0x499B6295330AF342ULL,
    0xD52218F93DB579B2ULL,
    0x30446FBFF90BC323ULL,
    0x263BE7BB537207DEULL,
    0x67,
    0x7F,
    0xD3,
    0x6B,
    0x12,
    0xD5,
    0xFE,
    0xF6
};

const TwistDomainSaltSet TwistExpander_Canopus::kPhaseBSalts = {
    {
        {
            0xE7EBE2D87746D437ULL, 0x91088F9603E0973FULL, 0xBC9963ABBBB23D2DULL, 0xC80C548DFE92648AULL, 
            0x17044BBED3B63F9DULL, 0xC3598C8F0EA5F071ULL, 0x3DB336B6D31F1F3EULL, 0x748215826FD6EB56ULL, 
            0x50E96F68E966D335ULL, 0x75C7D0B883616A85ULL, 0x50752317FBA241BBULL, 0x9E83B15E693F14B6ULL, 
            0x37E30B4BC7B622C1ULL, 0x147F4691A76307E4ULL, 0xF8ECBE8D8602779DULL, 0xA20C286E86ECA6FDULL, 
            0x6FCA1429733C095EULL, 0x10157E1987210077ULL, 0xC7208FE327A96461ULL, 0xCC0C5A40530FCBA1ULL, 
            0x74010B920674C385ULL, 0x9B91C255869447FFULL, 0x690CAF9BC1810069ULL, 0x2AFB7416491608DDULL, 
            0x2D3DBCC6D3778303ULL, 0xD2E38D31A124CE1BULL, 0xDD43D8E0BF98A37BULL, 0xE219651E18F9CE37ULL, 
            0x56CCC05F1AB2716BULL, 0xE59C035FB0F2E891ULL, 0x341E1FD14B4601C9ULL, 0x2C631C3DFBC4CCAAULL
        },
        {
            0x6A8772CAAA855DCDULL, 0xC7C64D9A435FE4EFULL, 0x76C0F37369C929D3ULL, 0x52E1E470CE2FE2D6ULL, 
            0x5DC4016EF0A47AD0ULL, 0xDCDAC1348429F362ULL, 0xF3CE511D1F5DD0CBULL, 0x0B108B9FA88DD59EULL, 
            0x3250BDCBAF36359DULL, 0x35C6508B62AEBCCEULL, 0x69C9277665030E88ULL, 0xC6BDA863042B6EC1ULL, 
            0xA47E43B9245BA084ULL, 0xA13065D15A931485ULL, 0x1BC9507F402AD805ULL, 0x1D2EADD79B190049ULL, 
            0x2DA947E7B2972948ULL, 0x3DF46EEEA0757BB7ULL, 0x5E29F0350086F1A7ULL, 0x08BE99D0024AA668ULL, 
            0x63FB45D2D3691FCFULL, 0x0FC23E83F053CB99ULL, 0xDCA41C14A0B5D37AULL, 0x946C0B2D16F1E1E8ULL, 
            0xF4E7B2FB17CA8573ULL, 0xD8A27CDA3DC0D93BULL, 0xB0765D739A87FC23ULL, 0xF7836D39C044BF45ULL, 
            0x593F8362D2ED4CE9ULL, 0x05C2EACE3DF1665AULL, 0x07844B49F0946063ULL, 0x0180B49C8CB8CBC3ULL
        },
        {
            0xFC19B581A584D19BULL, 0xDC3F3CCDC69C9DA1ULL, 0x4CFAF3B592A0988FULL, 0x7F6CAB5784AAD0E2ULL, 
            0x951958AC0A34C0A4ULL, 0xC26824CBFB52EE8DULL, 0x475B5358A4C5B86DULL, 0x016D04F87AA13019ULL, 
            0xEC53206518A50522ULL, 0x4E512DCE62AC6075ULL, 0x4F4EDD895EDC50CDULL, 0x82B0EED94089FBEDULL, 
            0x6FDE25693FF8A92CULL, 0x160EF05CFD868539ULL, 0x64708DDCAE7E56BCULL, 0x733D5394F666F1ABULL, 
            0xA47AE57E2F9FFE4CULL, 0x133EF8493A0EED12ULL, 0x41D57CA7812C86E2ULL, 0x9DC799D4BE47B31CULL, 
            0x07E3C88C70F4F1AEULL, 0x9D7F159ABA50E15DULL, 0x68666C1D7E542818ULL, 0xE5B3970B08125BA8ULL, 
            0x1B9482216057B0B1ULL, 0xE28753260BC18519ULL, 0x81FECB2469B342DFULL, 0xF01F1AAAC573F873ULL, 
            0x30ACA68E86B3EF6DULL, 0x8EEE56A6B01EC9CCULL, 0xF3D19B41E8D85D8BULL, 0xE4580E92E9DDD529ULL
        },
        {
            0xECA1A2A39C6C0E53ULL, 0x2ADA9171AB923162ULL, 0xDB710D7036EB7119ULL, 0x72A99632DC8F32D4ULL, 
            0xB228BFE442F1D854ULL, 0x76AA122B64D54446ULL, 0x2E4557EECCF3C968ULL, 0x3873B7FF68C8EF36ULL, 
            0x632C66838396E4A9ULL, 0xEAE57FD199E65673ULL, 0x6C0031D6D31B216AULL, 0x65CC459D56C2EE0EULL, 
            0x4BA97C802AC6CA6BULL, 0x8C66C0F9F4E9E64AULL, 0x5D8FAE7C0C2B8B09ULL, 0x22C476EDFC286A2AULL, 
            0xD4E3958E4341DC75ULL, 0xE9A908F90A7B974DULL, 0xB16E4FDA7843C4C8ULL, 0xEA4C5C11324D4D11ULL, 
            0x78C66AF9D1D94B1FULL, 0xD8592F7127ECD9D2ULL, 0xCF3C027D0F07834BULL, 0x7013692B0078F95AULL, 
            0x9A9D51D9835C19F9ULL, 0x1E4F3BC991A20E4DULL, 0x276611B1ED4D278BULL, 0x3340EFBD3FCEC899ULL, 
            0x2EE76775EC6E23BAULL, 0xB58A1CA762604CBEULL, 0x2C91B386B2E7D501ULL, 0x539C7968E88DFE61ULL
        },
        {
            0x1331E1055E264343ULL, 0x9521FA89123ADF72ULL, 0xC10D1008B6EF52F3ULL, 0x97E920557004EEECULL, 
            0x9FDFE946920B601FULL, 0xD1B520CE0475BA3CULL, 0x8124EA777ED096B4ULL, 0xD9DD50ECF21C177AULL, 
            0x171A79AC64F5D2BCULL, 0x3F35F93237A82E86ULL, 0x30FA3F9B5486AD6EULL, 0x6A8C08DC092857AEULL, 
            0xD718E91E8F3C1D14ULL, 0x7FD2EF60A8A5A845ULL, 0x873B9F1A214CF1F8ULL, 0xD3D2F9F7329915F9ULL, 
            0xA03FC03E7B831508ULL, 0xF70AABCC63151748ULL, 0x20B6033AE6DA7F8EULL, 0x366E8E452D471E38ULL, 
            0xC2CF5BA702235186ULL, 0x080BF2F0508D925EULL, 0x25D275680E199534ULL, 0xCC6310011DC014A9ULL, 
            0x50A5814A7A4394F8ULL, 0xB70AB34B3BC9FC15ULL, 0x3563AD4DAD75172AULL, 0xB7265FCEABE8CA69ULL, 
            0x48CB4BACC8DE441DULL, 0x3A9DD19C21A0BBE5ULL, 0x1471993CFC371397ULL, 0x21CDA552ECBDD71DULL
        },
        {
            0x4FEF9D0E7D43C1AFULL, 0x8B9C15089DB3747FULL, 0x133CA313BAEB72C1ULL, 0xDADF01F887550188ULL, 
            0x62DF866CD0A131D7ULL, 0x9F972B7DF662AE68ULL, 0x15C37FB68518346CULL, 0x90B84C35A7AEC630ULL, 
            0xE97CB26643B47956ULL, 0x94B032AF92F0D017ULL, 0x7228637B00A12597ULL, 0x6C456DB61D8739F6ULL, 
            0xBBD5B7E79DCF200EULL, 0x3911955B1F611E33ULL, 0x3B9BF462D147D7BBULL, 0x4E7F4745B804B995ULL, 
            0xED62EA506B2830C4ULL, 0x896B8CB74771EEFEULL, 0xE3FA8B5A2D908453ULL, 0xCBB2B1D852917632ULL, 
            0xAAC4D4ECDC31EC0AULL, 0x2337E03519DC569DULL, 0x1C9B18ABE45099A3ULL, 0xA6BCAA90D64AB62CULL, 
            0x9490734263ECFA99ULL, 0xB43D2712E59B2093ULL, 0xF605C18141A5690EULL, 0xF4DD7B5CE2C68F6BULL, 
            0xF113A046E83F6567ULL, 0x9A8C5B9337E5C10EULL, 0x577E0E213FCED9A7ULL, 0xE6485E812898F8C0ULL
        }
    },
    {
        {
            0xACC805C4AC4FA53FULL, 0x3AA22BB6FC5E29FEULL, 0xBFE2F811ED8EA859ULL, 0x3E2AE6FA53A9803FULL, 
            0x0EA6C4DFF48851F6ULL, 0xEEBC2545C789C29BULL, 0x63A84688F1C476F1ULL, 0x466EEFB730F684EEULL, 
            0xB431C5F8AD367A97ULL, 0x85642BD0FD75396CULL, 0xF8069BBDC97433ECULL, 0xE345130D225A41D3ULL, 
            0x495D2E7186B17A6CULL, 0xECC12C5CEC54593EULL, 0x036E20357E026941ULL, 0x7245793C009175C9ULL, 
            0x38E85BD89B0C50CAULL, 0x4134B038159569DDULL, 0x9ABAC9B1BD28D0A7ULL, 0x875FB166CDBF6F5CULL, 
            0xE024F9C0127E96E3ULL, 0xC5165C256BD203B5ULL, 0xEE773C83BEB7D32BULL, 0xCE21BBC5F0D8277EULL, 
            0xAF273BA158DD12EEULL, 0x783751DA582F04CEULL, 0xC1C3EC91079085F6ULL, 0x9B2C8A6E11B9492AULL, 
            0x5C5695E98F202325ULL, 0x7F1F216F47AC372CULL, 0xEF9B5551FADECF9BULL, 0x804F7072A14EB076ULL
        },
        {
            0x6CC58A9A86486BB9ULL, 0x2FB53D3BBF202240ULL, 0xBA4DF31B0DBF40EDULL, 0x2CB4B5EFD1F0B8AEULL, 
            0xCEF96314C4DDF82BULL, 0xD0F521893A2415F0ULL, 0xDEEE2EE8AF52D531ULL, 0x86B001DB0EA7F132ULL, 
            0x91688E02ED3A2AA6ULL, 0x493D94CDE665EA27ULL, 0xF98ED280F2EB3B53ULL, 0xFEE5484C1AC00703ULL, 
            0x3D80ECB5E6A82B9AULL, 0x6AF5066FAD9747F6ULL, 0xD4E24064FE4564C6ULL, 0x7F2124D4F2C25DD3ULL, 
            0x846B173A1094A061ULL, 0x31BFFE3F7803D7ECULL, 0x74CBBEB82F74F980ULL, 0xB3B60FB4034EFA74ULL, 
            0xE050D016CE6826FFULL, 0xE4FD651CAC711167ULL, 0x46B1F02BFD19362EULL, 0xCDDB9590A92C8668ULL, 
            0x68BD3738CEDC3F99ULL, 0x9F578B5E1487A3CFULL, 0x5864C0C633D12EF5ULL, 0xB4CF51B870B88614ULL, 
            0xF660D124D127A112ULL, 0xD188DE189DF0566FULL, 0xDF13231AC468E912ULL, 0x454705D6F543A742ULL
        },
        {
            0x31435421A244C12CULL, 0x2395723DE5E21807ULL, 0x569501545FF0F080ULL, 0xA47981F74627A7CEULL, 
            0xB9FA9A97671FCC68ULL, 0x69E6816C2D8D8684ULL, 0x2063F15D2DD17FCDULL, 0xB2A0ECDE9D25489CULL, 
            0xCEFA2C11FE643210ULL, 0x91DB0CFB07F452BBULL, 0xEDF985AAEC34A0AAULL, 0x990D194A43B6929CULL, 
            0x292F79730E18FDC8ULL, 0x12390E4831C4859AULL, 0x189B668E288BAFFCULL, 0x901161A946DB61A2ULL, 
            0xD3C7BECCA7E37D42ULL, 0xD906E2B20A583120ULL, 0xA1794413DB807CF8ULL, 0x24E1863E2BE982A5ULL, 
            0x52CE2F4DB0721168ULL, 0x911A69989C369B0FULL, 0xFCDAD63837D90791ULL, 0xA8BC5DD77D3ADEC3ULL, 
            0xB08512D710E9B830ULL, 0x2D91EF31BD42161CULL, 0xC2295C60398F8C2FULL, 0x5E10B91EB00E461AULL, 
            0x1C7991F92DAE1397ULL, 0x663661093FB144CFULL, 0x6B7B7D06B143FEB5ULL, 0x52DD18E6D2A197F8ULL
        },
        {
            0x62EAB01D365D6387ULL, 0x66D9AE34072DA52CULL, 0x117C254FA4A52A80ULL, 0xAC4B62E3DD3EC948ULL, 
            0x6F4925D3977C4AC7ULL, 0xFB23CAB8F4BAA692ULL, 0x0890F8D68F65538CULL, 0x7AFD45518BEABC49ULL, 
            0xC58DD75005BC04A6ULL, 0xAED49AC8C77ED6A5ULL, 0x3FEC00D155A1829BULL, 0xBB27E11FB36D8245ULL, 
            0x4ED792781BF89194ULL, 0x38A7AFBA7ACDDB85ULL, 0xA572CC7BD87421BDULL, 0x45BCAFCCDE10CE19ULL, 
            0xA13CF57B46CB7582ULL, 0x7F183F929C9EC22DULL, 0xB11D601EF529C073ULL, 0xEB817F7241107EE3ULL, 
            0xC6AFB82095390829ULL, 0x4DF12BA916B55DC1ULL, 0xA05C2B3B1800B53BULL, 0xD3191E25BA2FFDFCULL, 
            0x6C8081937A908C1CULL, 0x7ABF21FDA0C6D7C9ULL, 0x2705F2596B4C4CA8ULL, 0xF9D2398B20EABC6BULL, 
            0x972CFE2A21A5EC31ULL, 0x19FE536BEF890E8DULL, 0xBCC99A3175D6BBEBULL, 0xD541446EB6991C65ULL
        },
        {
            0xE02BDF2C15B9380AULL, 0x31898CA8DE7F7DE4ULL, 0x085E24861CE552F8ULL, 0xE6BF6382ACB62144ULL, 
            0x522AB30D31E165A0ULL, 0x11EDB5C9EA182368ULL, 0x7DAB23596199F047ULL, 0x64F137B462E56411ULL, 
            0xE372CB1AC5159108ULL, 0x7E7CB65F90B5E825ULL, 0x2A8E9F4CEDC219ADULL, 0xC847652D8F931B30ULL, 
            0x2F84C4C20467FEB6ULL, 0x426DD7AB73679AADULL, 0x0196E97F5402584BULL, 0xD8B74C754BFFADCEULL, 
            0xBA12E70CB1394A8EULL, 0x803385A724F9AE23ULL, 0xD2284751300F7BE0ULL, 0xCC77915E2B125566ULL, 
            0x377C5BB29BCB481DULL, 0xBBF9CE40C8205A18ULL, 0x45A1216DB4E6A733ULL, 0xEDD8462CCF412195ULL, 
            0x73120A1D519B5A39ULL, 0x3DD2954E774B6C57ULL, 0xD1F1DA4C1F56DC2CULL, 0x2A74D9D922BF741DULL, 
            0x6880D7433F920705ULL, 0xD10764D5E191F919ULL, 0x4B519D0CC2FC7EDFULL, 0x4DEF6ACB6E4A2AD4ULL
        },
        {
            0xD29611C538761139ULL, 0x13B8E2932CF8421FULL, 0x0642F7E65EB5CFDBULL, 0xE57DBE4E2CC5A04EULL, 
            0xBCFE8E665281CC82ULL, 0x457DADCA18D15977ULL, 0x49483511C35D0790ULL, 0x6EB4F0317F49E41BULL, 
            0x2FD198C11EC7A725ULL, 0xB9A4C9EA61B12154ULL, 0x631D2AFF52412686ULL, 0xFF2D5EE4683C9BBEULL, 
            0x18F1D01A02AA82E1ULL, 0x824CAD64D892C43AULL, 0xA32207AD1E2233FBULL, 0x34FE135C22E923C4ULL, 
            0x9AFCC652AC18857DULL, 0xC4D46AEE90ECCBE6ULL, 0x8EC7D5FCA9D478E9ULL, 0x7D6A87B839E412B9ULL, 
            0xD6167477BFC167ECULL, 0x3DD85B9D8C13E15CULL, 0x9F6EDBE8C76A508BULL, 0x1D33A6B8AF2644EAULL, 
            0xF11E5331F7BDEACAULL, 0x420BA434605CD20FULL, 0x1A66DBE53A9F2063ULL, 0xB405855FC5D42B13ULL, 
            0x184DD8CCCB56F48EULL, 0x28B963EF2E85764BULL, 0xD3A13A5D59D1451BULL, 0xCDE5F00CDA6E50B1ULL
        }
    },
    {
        {
            0x7238C0B9499192D2ULL, 0x4C0C2D56EAA73910ULL, 0xCB38D3D1314EC567ULL, 0xA8835AFB8CADEEA4ULL, 
            0x10904342B10AC338ULL, 0x9DE8CDAC9F74A306ULL, 0x9817E6A3ACFDC6FBULL, 0x34946D86A79F70C4ULL, 
            0xD2124D979BAF4F34ULL, 0x923AC8C48D3250FAULL, 0xE2687BB14DD0B978ULL, 0x10AB1BD78A35FA8BULL, 
            0x18AEFA80C9071A3DULL, 0xB209F8CE83507A89ULL, 0x59857DDE7E3BA399ULL, 0xB8193EC1B8A35E22ULL, 
            0x9D1EB03CFEDEB0E0ULL, 0xAFA60134415047DCULL, 0xC8CC3EBEA758B551ULL, 0x23296ACF701C637DULL, 
            0x7CA249D88C677908ULL, 0x3E07EA5B7B40CF56ULL, 0x9D272AD01F631E05ULL, 0xB97770476D8E33E6ULL, 
            0x76396EAF0A9A1547ULL, 0x1F6FACC17D7E156FULL, 0x856670E738D5D5A0ULL, 0x1D80965E0505050BULL, 
            0x27F81D3D4946D3D3ULL, 0xE1F458509434EA10ULL, 0x5616E0BBC55D9826ULL, 0x9456E6527154CC7EULL
        },
        {
            0xAD157DEF71A9D3D3ULL, 0xB84E978459144996ULL, 0x4E0910E50C0FD93FULL, 0xDB609243DB91B0F0ULL, 
            0x12310B1E404C7E05ULL, 0x8DEB90B9F1839EE0ULL, 0xE5D67DB7BB35D4CAULL, 0x607213CBE09C0242ULL, 
            0xBA0772D7AE48C570ULL, 0x4BBA62673F048BF5ULL, 0x0AC2213D5BF4DC7CULL, 0x1E7E71B821EB4020ULL, 
            0x8729F353635A65D6ULL, 0x56D26991BC9FF195ULL, 0xC794C8BEBFBF97A2ULL, 0x2B5323FDF4F7B39DULL, 
            0x8F5FB091A494B3EAULL, 0xB3B0DC1C8F00965FULL, 0xE593403A444D320FULL, 0x88ABD0ED17D916E1ULL, 
            0xE949FAF956F8E183ULL, 0x41B5357184862419ULL, 0x3DCBCD96C8556D9DULL, 0xA52F04558F1A8007ULL, 
            0x15CBAFF3D4E68A42ULL, 0x8A739AF6B8C142D7ULL, 0xED78BCF58B27D71EULL, 0x7EE4E239CEA08DA6ULL, 
            0x702356A7EFD0A1DAULL, 0x4D9E7316CFF0ADADULL, 0xB2D975A4913C54B9ULL, 0x1927AB2A86644554ULL
        },
        {
            0x80A603DE9949E393ULL, 0x45AFCE3D88A88281ULL, 0x0100429C22D7CEF1ULL, 0xDE924AF31118D26EULL, 
            0x93D0903ABA9E7A77ULL, 0x7D6203CD98E47467ULL, 0x1BC551DCCB313084ULL, 0x3CCB08E4336EABCDULL, 
            0x3FE2BB78FB28D45DULL, 0x85D04875D5E3F3FAULL, 0xE255CE4C29958FA1ULL, 0x8F7303A4630C3FB4ULL, 
            0x9AB50A39F6FDCDA6ULL, 0x7B757EADA8964295ULL, 0x021E86C40DB473D6ULL, 0xCEF9A7118E5C2032ULL, 
            0x3A31B0DDF6995A25ULL, 0xE2EAF19557A4D363ULL, 0xBB991CA1A2D9C9A5ULL, 0xE364A8C4263059C7ULL, 
            0x20A1B1FBA6983D58ULL, 0x53AD18179C2AC342ULL, 0xAAD85C1212D2104AULL, 0x4CDA4DA1D478E263ULL, 
            0x18320810E0A43EC5ULL, 0x26C3D919CD5F6967ULL, 0x393F1C758B1D7FADULL, 0xECDB9525518A19A5ULL, 
            0xA71CEB671BE400CAULL, 0x6CB5D02CC31F209AULL, 0xDF0F16E970FDFA25ULL, 0xE0CC609C3A360601ULL
        },
        {
            0x28F64800DA24C9DCULL, 0x096BC0FD31FE5D35ULL, 0xDB13107DFDF0C652ULL, 0x3706355428DC1D06ULL, 
            0xE3A81545544F44D0ULL, 0x5E1DFE1DB96CCF2FULL, 0x1A5B63CC3D374752ULL, 0xB907893773D4E34EULL, 
            0x39E56E01F58CE730ULL, 0x056643522ACC190DULL, 0x8D9EE5BA7CC0E714ULL, 0x546ED5F684B262AFULL, 
            0x2BABF2C2F6188362ULL, 0x8F599955B7688C18ULL, 0x2D726FAA1EF383A2ULL, 0x11506FE9B4455F4CULL, 
            0x3D471B666B3541BFULL, 0x958929DCB5C251D2ULL, 0xB4C24F0F219A2D90ULL, 0xBCF0A3DA2437CA33ULL, 
            0x06A2A8F959F82981ULL, 0xBCAFFFAF2A7B0219ULL, 0x6E30079BF0BFD471ULL, 0xE6FA6AE80E09A1AAULL, 
            0x0689860754D9F825ULL, 0xB30D12EA030CFBD8ULL, 0x81B2B197AF0A1773ULL, 0xD1D3D1167FDA50BCULL, 
            0xD021FA3CE6708B38ULL, 0x9D0AE22D7D922333ULL, 0xBFC2F450146257CEULL, 0xBBE36628E84675E3ULL
        },
        {
            0xC403162655D694E8ULL, 0x1D12119C86A353A6ULL, 0x77956AB50D4861A5ULL, 0xBA82D25CEF8A94DAULL, 
            0x0AE62CB3769BCBACULL, 0x0399DA260FAAAB63ULL, 0xD6EFBC921400D92BULL, 0x9E1A6BF39DAED701ULL, 
            0xB158B11B76B4E00BULL, 0x5D15A956A5ED27E9ULL, 0xA27583333B29DB83ULL, 0xC45240D29C31BA81ULL, 
            0x1706912A1FAB3E48ULL, 0x5112F032FCA26C27ULL, 0x70DBFCF1A4D6D264ULL, 0x31A040073550CAFBULL, 
            0x086003D046B250A9ULL, 0x48C269045A3F3451ULL, 0x338ECD3680C97498ULL, 0x1634F041EA7B8381ULL, 
            0xFB73BB5166131F9DULL, 0xD4EDA6C8888532AFULL, 0xDA28E996412932B5ULL, 0x6746190E1E6AECABULL, 
            0x6BCB249E78638053ULL, 0x93B5A2EAF1A86288ULL, 0x3F894AB0C0F1AF86ULL, 0xC705E35EC9B2A790ULL, 
            0xF664BE40CC468D4FULL, 0x57036B57C422E90FULL, 0xE6BA8634440133B8ULL, 0x73947F87EB6959BCULL
        },
        {
            0xE8C51D540A6FDB3DULL, 0x3F31C0FEA6C66AF2ULL, 0xDA196B5909D5A8CBULL, 0x410D69BD33FB8F46ULL, 
            0x3EB014EDC317861BULL, 0xFC12A560C0288E5BULL, 0x549C19E048492B5BULL, 0x073B25A50ADA5FEEULL, 
            0x4E9439272043C82BULL, 0xCCC714275881A156ULL, 0x04048EB209DF0B5EULL, 0x6838CB44D42672F4ULL, 
            0x0B6082F9B927DCE6ULL, 0xF18C30E78043E38CULL, 0xBA807F8E4C1EEF63ULL, 0x4E2949D56FFC94F1ULL, 
            0x6EA1E2319E1EC63FULL, 0x3DB2F33E944FDF1DULL, 0x15D36C2BA6602E24ULL, 0x8531641BEE486885ULL, 
            0xDE120FF5B5B9E89CULL, 0x599DD49655D70E1DULL, 0x4CA217CB7D0D7CDAULL, 0x840DB76BE21CA4CAULL, 
            0xB0804E687BE86C3DULL, 0x453E268151DB9AA5ULL, 0x580693F5CC068621ULL, 0xB531A13DBA2CA3A3ULL, 
            0xAC1EE9A969D5EA5FULL, 0x4C7214F70BBE2871ULL, 0x058BD3BAF59DCD8BULL, 0xD68F44A4D101703BULL
        }
    }
};

const TwistDomainConstants TwistExpander_Canopus::kPhaseBConstants = {
    0x589C18171ED2469AULL,
    0xE6F04633C75DEDCEULL,
    0xB522729F9210474AULL,
    0x589C18171ED2469AULL,
    0xE6F04633C75DEDCEULL,
    0xB522729F9210474AULL,
    0xA38A45FF9F2249BFULL,
    0x6EB9BB5C738CD5DFULL,
    0xD4,
    0xD5,
    0x09,
    0x02,
    0x6A,
    0x1D,
    0xCB,
    0x85
};

const TwistDomainSaltSet TwistExpander_Canopus::kPhaseCSalts = {
    {
        {
            0xF53BD1B6FC4A09CDULL, 0x6B4DBC5CA8449463ULL, 0x43BF558EFECC20CEULL, 0xC7E3BD179E8837A9ULL, 
            0x2D96BBB3C725A545ULL, 0x86F7FB7C5912D77CULL, 0x6370B7DF634A80B0ULL, 0xDC2651A5F207D2BAULL, 
            0x96059B4C0A179782ULL, 0xC15D155FBE07733AULL, 0x659DAB2D7F9663A5ULL, 0xBDE4BCB33A8D1B43ULL, 
            0x474548AF41DA0536ULL, 0x693023D2656AAFF8ULL, 0x4B73828785EADA59ULL, 0x7D392E0333B6578DULL, 
            0x3D29E6F782B15450ULL, 0x6F192397C12974F2ULL, 0xDD1DA213D4C3CC4CULL, 0x0D0FF2AB48273706ULL, 
            0xBC9602FDF569DFD2ULL, 0x8A903F9F9B5B6DF6ULL, 0x662DBDE669643D09ULL, 0x2F071B8C5C460F02ULL, 
            0xDF7A8E0441036D0BULL, 0x3796D8891E0B2CA9ULL, 0xDCA116F539643322ULL, 0x0553292A19FB2AC3ULL, 
            0xBEA7CD89A4A93AE0ULL, 0xA6552A6F31B3AAE9ULL, 0x11CA57F335E82A88ULL, 0x64DEB8EB85007FA6ULL
        },
        {
            0x4F8F7F4FAD009ADEULL, 0x9E57AD8A9694920AULL, 0xB3765BD8C785CC1DULL, 0x1D2B7467D43C4A8CULL, 
            0x6C2845625EE34E87ULL, 0x822B0CBB01A3704DULL, 0xBEC371867E79D306ULL, 0x3D328882D0C77007ULL, 
            0x51AC8F0C077E39F2ULL, 0x0ADD483032EE4F37ULL, 0x49998CB116928845ULL, 0xE86A7405DCA5B081ULL, 
            0x28ECE3182465386CULL, 0xC3207DB2E7E5DBCEULL, 0x731F8E67B15E9B6AULL, 0x4C5C478C4551C669ULL, 
            0xE2F18E63F82B874EULL, 0x541D28A3BEDBA254ULL, 0x6382D8371445D4CFULL, 0xA9F304148118094EULL, 
            0xDCCD4ED663CCEFFBULL, 0xE6F14ECDF66C474AULL, 0x3EE2B0CE3C0BEF5CULL, 0xEBCCB7A8612C55D0ULL, 
            0xFB850F90A63EB03AULL, 0x67280EE2FC240D9EULL, 0x1FAC7E109DA9383FULL, 0x215BE82CB62D37E9ULL, 
            0xCFCBB2BFBDE73715ULL, 0x19E4E77EA3B43AF4ULL, 0x456E39E317D37B26ULL, 0x3F549E9C8710FAFFULL
        },
        {
            0xEE2ECA82124EF867ULL, 0x009B5A331AE7A3D7ULL, 0x1FECC6A5F1023619ULL, 0xA5C9C2990938C0A8ULL, 
            0x34E3D6B7C7B0D7FCULL, 0x27AADF725E41F597ULL, 0xD28FE3081ADBD7C4ULL, 0x6C744A23C0A39EB8ULL, 
            0x37AC8C67DA90D22AULL, 0x28E7C86717A65385ULL, 0x3215FF003292A38EULL, 0xC10C70AAB4883FBFULL, 
            0x0DF3945F7E357EB3ULL, 0xEFD5A401D9506652ULL, 0xCFB55B01604897A9ULL, 0xA30626C0080A842FULL, 
            0x51494819A760AA34ULL, 0xA8DF5BE316DA0FFDULL, 0x2DA6101437B7BE08ULL, 0xD52C013EAFA58236ULL, 
            0x03B1CF1ED90096E2ULL, 0x0AAE85DC0329BCE1ULL, 0x2B42BB92C4864143ULL, 0xD4DD7F937091DE31ULL, 
            0x1F1D3097567433F5ULL, 0x4CDDE0E04E1B55FAULL, 0x125CD8B2C54B7E98ULL, 0x9A05899BFD03029EULL, 
            0x336D54A21464EE41ULL, 0xA10DBD166816E7F3ULL, 0xEF3B04FE1CD404BEULL, 0xB5510B03970DA374ULL
        },
        {
            0xD886B5DE676238E5ULL, 0xFADD4C3B693867D1ULL, 0x3E76665076F0D425ULL, 0xA76E3245C1807086ULL, 
            0xB69E660E5442DC20ULL, 0x9C4E135A55268F86ULL, 0xFB0D1866567F139EULL, 0xEEF7123C58FA06B6ULL, 
            0x923BD210DDBAF517ULL, 0x679FEC746BC96C26ULL, 0xC95B0C5C39685088ULL, 0x7E27EE025BB9AA5FULL, 
            0x16BE456D700BC26BULL, 0xE08ABC960C4DF68BULL, 0xC9B0993E07036808ULL, 0xE2DBD975E2305EA6ULL, 
            0x5C20444C94747722ULL, 0xB481EB72C3D2153CULL, 0x889388F518C0D4E8ULL, 0x68C17ECA22DE3550ULL, 
            0xE73EDB9CA2804417ULL, 0x22B9DBD3F698B299ULL, 0xACAAB7A82DC79E6AULL, 0x7E730D052F3E245DULL, 
            0x04A510DE55339684ULL, 0x39D8BD4A80A5FD62ULL, 0xB437EB5B1888562AULL, 0xDA29894E474DFE02ULL, 
            0xCF5E963EB94B1040ULL, 0x61AACECEC4F3DE79ULL, 0x46C4AE5F7CE4F513ULL, 0x3BA0EF3E1B373919ULL
        },
        {
            0x0381D15DB7250C28ULL, 0xA321BAA3899EA86DULL, 0x3962FD9EFC338CE0ULL, 0x4A87455BF45CB814ULL, 
            0xE23841E27C35415EULL, 0x8EDC41EA6197C347ULL, 0xEFF84F25A25B4724ULL, 0x713DB3E10825B977ULL, 
            0xC8A784EB7C2C5160ULL, 0xD40E66F59A66868DULL, 0xBB36FF6172D53857ULL, 0x56A834A451E9850FULL, 
            0xBD4B0E5D252BF0DBULL, 0xE66F5602AC9945A8ULL, 0x5CCBD5FF7C97B379ULL, 0xBB0A2EFE402A13A4ULL, 
            0x9561DF5B0003B871ULL, 0x6866492611B9BC39ULL, 0xBD45EFEB66CC004EULL, 0x8C2819D189FF6C6BULL, 
            0x846344EB9212F187ULL, 0xE4E425B1F0C5CF75ULL, 0x4FDAEB237B15E508ULL, 0x1FCDBADCA5F6921BULL, 
            0x7FEA422254A19078ULL, 0x92AC736A27DFB4D7ULL, 0x98D825A31AB0DDF7ULL, 0x2270768F8EDDEEB1ULL, 
            0xCFAA51A214129FE3ULL, 0x17F39BE6B2032B66ULL, 0x58CCA65C309B82F7ULL, 0x3AE766698586ABB1ULL
        },
        {
            0x9A33AD8B45A5637EULL, 0xC588F2854025C984ULL, 0xD2FCEA965DFC3BC4ULL, 0x4B84F9B123FAF5B7ULL, 
            0x0478216410A247C5ULL, 0xC4C52406813A4732ULL, 0x1BE5B8C4D524C69EULL, 0x41087508B9EF1130ULL, 
            0xC4A17AE58A996C77ULL, 0xFAFA97554A812221ULL, 0xB6097078C2062820ULL, 0x54752F7B7D940380ULL, 
            0xF1EB84B8A8DAB716ULL, 0x3877CFC2F5C59A25ULL, 0xFB4EEDEBE0E18A15ULL, 0xE362989B9FAE6FC8ULL, 
            0x60FC9FC7BC07B365ULL, 0x67AFB28F0B228362ULL, 0xE7573F0A3DA61478ULL, 0x3286219667696E07ULL, 
            0xADCEDD0791D146F7ULL, 0x857A2E0F64C5330AULL, 0xB1AB3AD7F13644CCULL, 0xA7CD072D6456F63BULL, 
            0x9D7818A9E1032BB7ULL, 0xD528C38AEF4A97ACULL, 0xF076FE95D5EB6A87ULL, 0xFA3AA2F0A9715743ULL, 
            0xF8DAFD1F83F39DE1ULL, 0xD45450A1082402F1ULL, 0xBF2061B01666209FULL, 0x36618B11BBF6422CULL
        }
    },
    {
        {
            0x1CDC3532D093FB96ULL, 0x37C2593463B4C7A0ULL, 0x468032AEC8C41042ULL, 0x68C9725E93C9CC6DULL, 
            0x280846572FEB1C2EULL, 0xB6EEAE0169EB51FEULL, 0xC51C3240A166517DULL, 0xE7A7B26684435481ULL, 
            0x4AADCCCFF3E5B8EBULL, 0xBAE6EAC170EDB293ULL, 0xEA5B216D33974F63ULL, 0xCDD09BE9BA3AD7D1ULL, 
            0x96D9E4C7066F86E7ULL, 0xA4D8157C5F5FF43AULL, 0x256E1A86A2B3D093ULL, 0x84F8F91B77255199ULL, 
            0xE391F9A375DB5C7CULL, 0x8C3D31FF2C74F578ULL, 0x88A08546F72F2DEDULL, 0xB3318D03635E89A8ULL, 
            0xD158F4A203DA560DULL, 0x779AF773A2C81AA4ULL, 0xC429C87413CF2C78ULL, 0xEF060814B51278F2ULL, 
            0xA933AB5AB1487AEAULL, 0x97F71C30FC3361D5ULL, 0x6CE38E5FBD26EB9EULL, 0xD6C1A06D7A5CB3DBULL, 
            0x23421EB649341A57ULL, 0xFB02012544848DC2ULL, 0x8354C4116CAF4DE2ULL, 0xD416C8D213A52174ULL
        },
        {
            0x1DF08C5EF292F34AULL, 0x2F3C20568AF78220ULL, 0x1EB258790199658DULL, 0xE652634AAB768483ULL, 
            0x3D80F4FD695E0537ULL, 0xB831D7441E6B6FF7ULL, 0x76170422E9951712ULL, 0x72C8FDF07465360AULL, 
            0xF32C0BDAE70A11C6ULL, 0xF7340D7A1BA781EDULL, 0xB342C32BD6D3D588ULL, 0x2C87F8FE95A76223ULL, 
            0x054256A1D773F5DCULL, 0xBE629F33D1BCCA06ULL, 0x2DEFA4EFEA6AAD84ULL, 0xF5DF0A8EE732D041ULL, 
            0xD9B9970F0EC388DFULL, 0x024DC53E56D20FCBULL, 0xE6B1691DFFBD25A5ULL, 0xA1CE4FFE5BDC2FB9ULL, 
            0xB54976BDC6A5538BULL, 0xC54B2F3A38B76672ULL, 0x058A2D39850DB2D0ULL, 0xB41B75C3D0B49F85ULL, 
            0x332CFE214DC8D71FULL, 0x95561E3A61A1BE12ULL, 0xE271AE2E8BD65B37ULL, 0xBF5352EDF230706AULL, 
            0x39938B71F7713900ULL, 0xE9FFE5EF97D8A441ULL, 0x54D8DCDA33298027ULL, 0xEF7A0D5693EF849AULL
        },
        {
            0xFC7B00BE920A6E05ULL, 0xD1444FB08269CB2EULL, 0xCA11149D19313AD8ULL, 0xC5E2D30606CA0583ULL, 
            0xC7132D1C8A0A9DF8ULL, 0x6997A16C1F0C1951ULL, 0x44D01E85FEA24925ULL, 0xC2728D8E0C553A65ULL, 
            0xC5CAD2CF51235CE8ULL, 0x5442BE70C3E74D36ULL, 0x997325A81BA8E06AULL, 0x2B540758DC8D5197ULL, 
            0xFF08A07F6DA049DFULL, 0x3FDE0F1F01E52C2FULL, 0x6D328E3DEDBEA9A2ULL, 0x3204C6D3C07D2735ULL, 
            0x944265097935CD1AULL, 0xB8134109A92A7C2BULL, 0x06C45D0090BB804CULL, 0x2BC8EDD9CA186416ULL, 
            0xA6C985C5AC4D1870ULL, 0xCE7BC26F8EC16961ULL, 0xFAC1DD57959E134CULL, 0x258E4B12C7901868ULL, 
            0xB68AB855D07FDCB0ULL, 0x0BBE1148028EEEF6ULL, 0x6A1D9D2FB757243EULL, 0xB7AFB0DBCD408B9AULL, 
            0xA55B95FFB1B2E528ULL, 0x814480BA8BF4B19BULL, 0x00D74F48C03E581DULL, 0xFD7C2129A3A26BA5ULL
        },
        {
            0x6F4CFA3F76A61645ULL, 0xDCDCC9A7F6B0F210ULL, 0x438AFE06ABD94B78ULL, 0xCE7050C2BC542C42ULL, 
            0x4B9284E1DD8B823CULL, 0xEA0C43D00D69B017ULL, 0xD32EA3AFFDCF28BEULL, 0x9980F13BFE914C6EULL, 
            0xBE13F3647AA3A6D5ULL, 0x47D218609E3FC0B2ULL, 0xBB869B0B65393146ULL, 0xB2ACD70935E6FC2DULL, 
            0x8941D0E766C1A2A0ULL, 0x3FEB01DBD90BCDA5ULL, 0xE5417B0699E7E203ULL, 0x01340007CBDD2EACULL, 
            0xD5317673045565D6ULL, 0x3F53A388D1C216FBULL, 0x2E6466F346E0295EULL, 0xC6212084782A490AULL, 
            0xA5B4EA1B2F13C40AULL, 0xC97E31BAFB8314F8ULL, 0x3CAE44A85D9F82B0ULL, 0x106F0250CA6A4E1DULL, 
            0x6E0DE5777FD15DA9ULL, 0x8D8171BFEF315558ULL, 0xCA7EDD6A821FE6B8ULL, 0x90189835F717AA6DULL, 
            0xCC6646CC8AB1549DULL, 0xE6B0C504EC555A25ULL, 0x0C5899AA8988A75FULL, 0x838ABE26AAE7BD36ULL
        },
        {
            0x490D03B6E8FD2C78ULL, 0x9810F571F113DCE2ULL, 0x65B8B0032E16F941ULL, 0xF97E5E48720186D1ULL, 
            0x7B05E23D781D93A9ULL, 0x9FED343326D4B0E7ULL, 0x3C91133E6B8771DEULL, 0x9BB2ACFAADDF5167ULL, 
            0xD141DF5190005EBEULL, 0xB3AD0FFBB41E857FULL, 0xF158E81372D354DEULL, 0x1EA8CC2F8F199549ULL, 
            0xAE4B244C5947FFF3ULL, 0x19DA4DC07D374EC0ULL, 0x6E84CE819E762B36ULL, 0x381BA308384BDBC0ULL, 
            0x497D65FFB7F08B40ULL, 0x18EA1C712D7DBC48ULL, 0xC2E2B0C6BF2604F8ULL, 0x2E09A5306B1E7E6AULL, 
            0xBA15D457672114EAULL, 0x957611C975B7818FULL, 0x598AFB3ACE7E8800ULL, 0x869EE5FDF645014EULL, 
            0xA4176422B84EAA46ULL, 0xBCF4C67B1326409FULL, 0xD4891D54AD788F97ULL, 0x16ADE6B252726EE4ULL, 
            0xD04E169A2ADC44A3ULL, 0xFE7F45B72459A4B5ULL, 0xDB9A07C35F42B578ULL, 0x4219DAEA0AD8CCB1ULL
        },
        {
            0x85FBF94EDE4D1B89ULL, 0xD75C32BAEEF23ED8ULL, 0x6898A76914B10378ULL, 0x3FC39F98BA47C4B8ULL, 
            0x192F94C868F1C119ULL, 0x6B8A1A97428A2CE9ULL, 0xB38C32FD94449E66ULL, 0xB95960F1CFE3F10FULL, 
            0x15E6C9742F60C901ULL, 0xE847A3B484BF3327ULL, 0x1240A9A8F89782D0ULL, 0x78162BE370918CA5ULL, 
            0xD25D1DC7FA466C03ULL, 0xE7F32C2C9800AB52ULL, 0x1748B9E1666D4896ULL, 0x9326F93EAC8AB94FULL, 
            0xC58BD2E60ED32364ULL, 0x1CDF4B00BB81963FULL, 0xC236410761005E97ULL, 0xB3DBE2C60A71D8F4ULL, 
            0x469FD2282A1F64F0ULL, 0x112E26BEA23AFAC1ULL, 0x27D068CEC975C88BULL, 0x48DD46DC1D30BDA8ULL, 
            0x19A28B223BA7FB77ULL, 0x24C8FBD138ABCA89ULL, 0x50B5289F26F35463ULL, 0x480891015F2571E7ULL, 
            0xD7201D0D4CE2969EULL, 0xF872AA713C75EF70ULL, 0xF80F8E61FF1D15C6ULL, 0x74D6B3B8D5CDB487ULL
        }
    },
    {
        {
            0x65E10AA798AC2951ULL, 0xE6268E7850A22497ULL, 0x7579877F56F03394ULL, 0x49457B5DADF7F95FULL, 
            0x7B23D7DE46AD0F89ULL, 0xED4EB826F773AA47ULL, 0x22CB893FBC7C9CC9ULL, 0x5406F88613225796ULL, 
            0xC4F9F2A982EB6FE9ULL, 0xC6F4BD0B6937C994ULL, 0x1D6AEAA6C0906A61ULL, 0x9EB8B374C3FB9182ULL, 
            0x0680922CBEA917B5ULL, 0xA1B027CF03CD6DCFULL, 0xEC54C51AE3CF1829ULL, 0x34169C3D5FFB1113ULL, 
            0x65E70416F1DC451AULL, 0x195AB2D35A47FFCCULL, 0x11D256A376AC9543ULL, 0xED7BF2C9555FD3F4ULL, 
            0x43888DBE55EFD70DULL, 0x3730681EE7520D29ULL, 0x2F3D22AAD56936A1ULL, 0x6BF1F8F8E7C9B18AULL, 
            0x540F788CCD044229ULL, 0x4B7447A4A765AD46ULL, 0xD1CB2BE2209F6E1FULL, 0xA8CFBF5BFA292EC7ULL, 
            0x881E4EE933794DD8ULL, 0x29EDF8CB9E4A42A6ULL, 0xCFA6E87C002B462DULL, 0x0F0F8BD94073B82DULL
        },
        {
            0x5F79654158A8F0DCULL, 0x488FEF7C66BDAF5BULL, 0xF21AB3EB7C94C66DULL, 0x508A09B711244D5AULL, 
            0x65633F90EF497B3EULL, 0x88EDE3E507550F88ULL, 0x3B9E1016471FE364ULL, 0x76BDA66F8D4F7F9EULL, 
            0xC64FE7D07EEC0F7EULL, 0x590B28952B98A1B4ULL, 0xB261E02E35857DFFULL, 0xE7C06F811BF42757ULL, 
            0x227CF8E1BC3A925FULL, 0xE44AE57DFD0A64FEULL, 0xD35F7F986B413D48ULL, 0xBE8EC32F974FA7FCULL, 
            0x8391B30976841ECEULL, 0x56C9BAA519DF73CAULL, 0x177B0BF69C396608ULL, 0x9D2429BBC420E031ULL, 
            0xF72A523A8481908BULL, 0x293C9B191D300DC4ULL, 0x17C76CFC2DEBF8DBULL, 0x98A340B8B378FFCAULL, 
            0xF46D246A3526CE2FULL, 0x147D698C142B10F0ULL, 0x158032E7CE85004AULL, 0x3C558D0D20AC6BCCULL, 
            0xC0F5450D9E241CC0ULL, 0x076075617D5CBDD1ULL, 0xC205A18EC91A0042ULL, 0x992C6D95D15A5731ULL
        },
        {
            0x7686A2351EBFCFBFULL, 0x426C2FB95D47CE05ULL, 0x9A6552560AA3A907ULL, 0x904F567DBBA625E4ULL, 
            0x5A31CE893D254CC9ULL, 0x149D8297195B9052ULL, 0x5C4D5E44A441784CULL, 0xB0392A64D581A9E0ULL, 
            0x960C0F2CA7BDEA23ULL, 0x99F138DC573311A8ULL, 0xFCFF483AAA229BB3ULL, 0x97C975D5933CD558ULL, 
            0x2D072FB6D7B72403ULL, 0x90BB1715E9110F59ULL, 0x2D1FAFADE64548F6ULL, 0xF287A91B1136EABBULL, 
            0xFABD78E51F22F291ULL, 0x6A42CB4C418C0A4DULL, 0x44234952E90CB969ULL, 0x8D371EA1536FBEF9ULL, 
            0x1B4A9B33C26C2505ULL, 0xFC86A0697C9730BDULL, 0x2F7F95EEED7F5D1DULL, 0x8AF9FB9C07355519ULL, 
            0x0A389435F2E21F50ULL, 0xFD520F6C09DADD28ULL, 0x9181FBA4521A8D95ULL, 0xE82C7752D55157DDULL, 
            0x1B0644569DC481A6ULL, 0x9A991E18A7D4EE53ULL, 0x873539A32265A4C6ULL, 0xBC6E7BFAFE2792B4ULL
        },
        {
            0x2971F7B91E114AD3ULL, 0xE9A92D015F31585BULL, 0xBE372526A0754908ULL, 0x16AECE87E272B525ULL, 
            0x3F3BC622CCE83996ULL, 0xC895FDD7E567C767ULL, 0x5C6038B5573B52A2ULL, 0x287A881CFE627F8AULL, 
            0x7C749A036DB26518ULL, 0x5424DF645045C26FULL, 0x4D240B461E367283ULL, 0x92462549A364D39CULL, 
            0xF74269FE47929DD3ULL, 0x1EFE720C901BFA44ULL, 0xEDA01014AEF6A58BULL, 0x61313F102A8145A8ULL, 
            0x93DA553C0EBEB4F1ULL, 0xFC6580031CA36120ULL, 0xEB67062412B26946ULL, 0x26C0C1E5E570701AULL, 
            0x23FCF31F92AC2AF4ULL, 0x202DAAA18E67262DULL, 0xFE22CD84CFAB5B96ULL, 0x0B18F533139F6DB5ULL, 
            0x073F63933B1141ACULL, 0xC553CAEC1D4B4E51ULL, 0x6AE7F4C281871F0DULL, 0x5DE4FA146AF5F4F6ULL, 
            0x74FC6AA2926F3476ULL, 0x81A2225D7146B7E8ULL, 0x105B976589B5751CULL, 0x916E0A200910D0B4ULL
        },
        {
            0xF7355DFD26B8FBE9ULL, 0xDD119D76F2C492CAULL, 0xE890DAC53669B1DFULL, 0xF655F149BC58F524ULL, 
            0xE28B99CF824DF2CDULL, 0x975A885E691CCC68ULL, 0xAC26499A34FE20A1ULL, 0x545A380AEED3050FULL, 
            0xCA8F25EAE04CD52CULL, 0x5C9DA4D61BEF9061ULL, 0x6C77D185035B004DULL, 0xB781C3AB415001AEULL, 
            0xEFD1C124AF74EDA4ULL, 0xBDDBA277F1D83882ULL, 0x23C9451EF12F3F63ULL, 0xAA3E4B222EE82C5EULL, 
            0x3AB87544B755FD71ULL, 0x37D155543DBA5E0CULL, 0xA67E00428C48376CULL, 0x92324D6D044B97DAULL, 
            0x5E7342112B0FB0D2ULL, 0xDFCCE6E9AFDC64B2ULL, 0x82358968F54B4E53ULL, 0x23899EDCBDF6FAADULL, 
            0xB88CE76F60155E09ULL, 0x4B2BC3F981FDAAE3ULL, 0x4911F89C0EB8EC54ULL, 0xC58745C9776A26BAULL, 
            0x4ECD00D2028846A5ULL, 0x24F6FF450F53952EULL, 0xB530D4621E21E0DEULL, 0xD9F1461D7FA613C8ULL
        },
        {
            0x2CC87F3100D0AC6BULL, 0xD112B86CBD1FE24FULL, 0x27B60D4B268FC5B4ULL, 0x64BE33A493B75A2DULL, 
            0x0AC7A8F547B5AB04ULL, 0x0E832701CBC76DCAULL, 0xA576767AEBCCCEABULL, 0xDBBA1E2077913514ULL, 
            0x96F2B24944F7F266ULL, 0xC1E675DB03D00161ULL, 0x415B94B70E6F2B11ULL, 0x090AD3B0425D2BC1ULL, 
            0xE9C6395EE8DCDF9EULL, 0x1F43E763572716BEULL, 0x7AEAD95D58392B10ULL, 0x98CD83BE2E18551CULL, 
            0x0E0D889E5A70215FULL, 0x965C7ABBB25942DCULL, 0x85C8B8A6EAB3B93FULL, 0xA6972A02C6DDF869ULL, 
            0x11DDF3088516BFE7ULL, 0x036659E7E3C4C47FULL, 0x6FDDF38E94EC8BD4ULL, 0x8268DAE94E5C4906ULL, 
            0xF86A85BE2EEF49A0ULL, 0xB881A3095EEA420DULL, 0x8BB0EE0CA38DC0C9ULL, 0x7C192504A21E3311ULL, 
            0x0ECE34331257DC00ULL, 0x050BEF22295F6940ULL, 0x026ECADF3FD40360ULL, 0x7569E874D8B5AEF2ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Canopus::kPhaseCConstants = {
    0xBA30DBAFAC2EB001ULL,
    0x3E4A10F70316167FULL,
    0x8A9A8E4F5E4ED798ULL,
    0xBA30DBAFAC2EB001ULL,
    0x3E4A10F70316167FULL,
    0x8A9A8E4F5E4ED798ULL,
    0xA0B4B9A3A76BC22CULL,
    0x95B7025FEA5F78AEULL,
    0x9A,
    0xDF,
    0x13,
    0x5C,
    0xD1,
    0xB1,
    0xBD,
    0x04
};

const TwistDomainSaltSet TwistExpander_Canopus::kPhaseDSalts = {
    {
        {
            0xD1CD4BB7D720518CULL, 0x19297D3B3216C03AULL, 0x0974DAEE2762DF74ULL, 0xCBDBA7E71F03EDD2ULL, 
            0xD53B45C1AFDA0D0FULL, 0x003E21269908C1AAULL, 0xF17DEDFCD434C962ULL, 0xCCE10132ED102F58ULL, 
            0xEE97C0D51FF33601ULL, 0x165C9605A87BB786ULL, 0x8257F042F3F3D4A3ULL, 0x2AFD8F2CED452F8BULL, 
            0xBEAEB0CC49A16FB5ULL, 0x472676AB32F6FE39ULL, 0xE5C3762189341F8AULL, 0x6330CF88FE7FBBF2ULL, 
            0x8BD218F48F05379AULL, 0xD30D8568BCAE0590ULL, 0xCBB668AE3D28881DULL, 0x34083D9948586519ULL, 
            0x303DA9E3F7BECAD2ULL, 0xDA08D16911E57DB4ULL, 0xDBE34BDF81446DA6ULL, 0xF7D9C062739230FFULL, 
            0x6A21BA21132E3CEFULL, 0x29FBD0F8581459BBULL, 0x3BF88AD8CC5D2D3BULL, 0xED2BA96140E58921ULL, 
            0xB2814930DC6D0E43ULL, 0xD2AD3D2E186C2353ULL, 0xE711BD9FC91DA01FULL, 0xA34D67D2BEB6E6FBULL
        },
        {
            0x7A874646B07F8576ULL, 0x6A633F47700978D9ULL, 0x0629A11755D740FBULL, 0xB9A787B9ADB66E67ULL, 
            0xAB772CAA560A70A2ULL, 0xB4EA146FF7BC0505ULL, 0xA9DECC751F67BA87ULL, 0x4F4C23E9047EB900ULL, 
            0x98BDAF9945D77D6AULL, 0xBA13D0AE147B2523ULL, 0x0018D7D4FD698585ULL, 0xE0005660EABDB5ABULL, 
            0x174ADAB9F7E0DD33ULL, 0xA25F6AA1674686CBULL, 0x2A4BC0060D2F2830ULL, 0xF85C1BECDC315698ULL, 
            0x5B30C0E1D767833EULL, 0x5251F37AEEB2785AULL, 0x5E221D0F6CB65E60ULL, 0x518A4A7FCCF1A666ULL, 
            0x28675ECE9A000007ULL, 0x6DAF251D5DC0FA46ULL, 0x534C85E55C23A209ULL, 0xFA6C4C828A82EBDBULL, 
            0x0771D2BBD1A53C11ULL, 0x690196F6F6EFCC43ULL, 0x04C8FDF3FFA7232AULL, 0x5E357EF07BD0E04CULL, 
            0x095E8478B24FBE9DULL, 0x89A74CD5F18B3A3FULL, 0x2D8E6D2EF047AF05ULL, 0x0CC3CF8E8E08515DULL
        },
        {
            0xA0B3CAEB941D0259ULL, 0x204C195E144CDFB3ULL, 0xC14F56AA07B52464ULL, 0xF7D99C6FB381375EULL, 
            0xD007F34A84253EADULL, 0x9AAA17C4F8C71291ULL, 0x2D8FE79925ADB5A8ULL, 0x72AF7E206E1F0502ULL, 
            0x6A2B9894D877BFA8ULL, 0x0F96AFC9D625904AULL, 0x7E68BD48FFBC32EFULL, 0x03CFB8E2E316396BULL, 
            0x17431D5E28C1A299ULL, 0x1A39420E7EBC0FA3ULL, 0xE8023C84D7A30317ULL, 0x03F6135410BAA4B4ULL, 
            0xBD34211B4F8F67FEULL, 0x7BDFFE40E0A3ECC1ULL, 0x98BACDA56C879AB0ULL, 0x9E8502D94880D9A7ULL, 
            0x9A3C72A6D5038CDEULL, 0x137A265F71D3470FULL, 0x1B4226D7829C8D7AULL, 0xBF255F3C119B4645ULL, 
            0x1611CCD71C4D759EULL, 0x9A502D3C731E3E92ULL, 0x2A323251B99C9DD8ULL, 0x9BE39FAF773D1181ULL, 
            0x3FE59F367D95B7A0ULL, 0x6F186D75D9323088ULL, 0x6ED126E4920806F7ULL, 0x178F0018D5C5D201ULL
        },
        {
            0x60D94F0C1A6125B4ULL, 0xC43846409F9C8CC2ULL, 0x16270AADB100F578ULL, 0x7036DB26F24E40A2ULL, 
            0xE901CBE45B5C4C4CULL, 0x93DB472BC06706B0ULL, 0x269D667E5ACB7C44ULL, 0x6B6AEAA0A59857FFULL, 
            0x2FAD297E6E7FBF22ULL, 0x27DFBFE2AEF05BEEULL, 0x4C43570E4430129CULL, 0x528135B764A056A1ULL, 
            0x192B5A43DB42DDA8ULL, 0x749DFC6636CB6D77ULL, 0x41C17F7323ED37F8ULL, 0x2FCFC5B9F04EE354ULL, 
            0x05CB0960A8589367ULL, 0x81E2AC8587C1DC49ULL, 0xB5698F062AF1BEFDULL, 0x59118B794630A368ULL, 
            0xAC3EB06BF5564FADULL, 0xFB02467EF31AC265ULL, 0xC9FDF754462D0D62ULL, 0xF7E9A0906470E339ULL, 
            0x7158662618A85BF3ULL, 0x7F67BE11D9DF3912ULL, 0xE462BA4B5D98C8D8ULL, 0xDDAA00E221B39983ULL, 
            0x753176645CE71737ULL, 0xD7580810B0AA9353ULL, 0x3B0D22A144AC4E17ULL, 0x6241DB480E682BA2ULL
        },
        {
            0xD71750E0A70F2A80ULL, 0x9F9A253AA4EECA03ULL, 0xA2A6560DF43E65B5ULL, 0x5B981A35FA407905ULL, 
            0x3E36447E926AB814ULL, 0x5CD575EBC219A2FEULL, 0xB310C04C2EE1BCB4ULL, 0x9F6140BD1CB7527AULL, 
            0x06B0187FE00B8C7CULL, 0x618FFFE374BCF931ULL, 0xCCF201254BD4F97DULL, 0x910338E9A917DA93ULL, 
            0x56EDB163EEBA3570ULL, 0x52D4F53336BB0E48ULL, 0x444790D8DEA01C93ULL, 0xC457045A15153FE3ULL, 
            0x3C4B30E35696163FULL, 0x4D24EF9E0BBE6B8FULL, 0xA0D0377F12562A68ULL, 0x2D9C12B2298B4771ULL, 
            0x2485FFD3907B1EA7ULL, 0x92DA2D2BC896FD01ULL, 0x51BC7F2824118ED8ULL, 0x3D70942BE3D69447ULL, 
            0x0140159BE17249AEULL, 0x1364C03EF28369BFULL, 0xBE60207759496EBDULL, 0xB14ED8362066B18FULL, 
            0x89BC3541B552086DULL, 0x8DB8CE8955D19424ULL, 0x8A06602BFCDF2FAFULL, 0xDC5A896D1B936A1CULL
        },
        {
            0x14922904D87D76DAULL, 0x9E2FD8ED99FDCFB0ULL, 0xF26A3ABA4041529EULL, 0x9349071EE2679062ULL, 
            0x292E726E93E1C68BULL, 0x6E1E7A88778839B7ULL, 0x7BA5B9927F6CA7AAULL, 0x19D3C7496498BD48ULL, 
            0x5D921810D3F1A3AAULL, 0x0DACB37803DD7B56ULL, 0x3847017B71F92A82ULL, 0xF6D6D7324B1AB51BULL, 
            0xD6C02985D569CA1FULL, 0x9EC374AA6EA4E01EULL, 0x36E95516ACA6BE1DULL, 0xF6E7E37542905897ULL, 
            0xE6620E85040BE0A8ULL, 0x682CAE33A5774B7DULL, 0x955BCEB9A14BB6F3ULL, 0x3541AFDB2986B557ULL, 
            0x71CA520C163EDAF6ULL, 0x31EAB6BB6E66474AULL, 0xA830CE13D78751C5ULL, 0x76595780A9DA7C08ULL, 
            0x2E6BB786A88D327EULL, 0xC8F55F19E52970C0ULL, 0xFE7E54D97ECD04E1ULL, 0x5C15E042476D7C4AULL, 
            0xF974502D1DF8F9E2ULL, 0x8ADFD5759FDAC5AEULL, 0xFBE1D64F56C3152FULL, 0x910705FB821A1C40ULL
        }
    },
    {
        {
            0x45AD050D0711BF4CULL, 0xC21FB1059F7D344DULL, 0x10A48B1C534A552EULL, 0x5C52C09D4AE2C841ULL, 
            0xC6B8E43FC6DAC064ULL, 0x35824CB9901755AFULL, 0x1DF42547BD77F390ULL, 0xB38DF46C7435319EULL, 
            0xB584905247DA7414ULL, 0xFD6C342CF8A2F8DDULL, 0xA92933C06F58369BULL, 0x97507E94C89E225AULL, 
            0xD8052947F49635CEULL, 0xDA001DE6E717A0E0ULL, 0x0389989FF4E0FBE5ULL, 0xCB7E57FBD1DFB27CULL, 
            0x5725EF67A32E821FULL, 0x83D480E387D47C06ULL, 0xF86CB81387431E0CULL, 0x2DB0CB43E6B85B95ULL, 
            0x0C42DB3BF6CA52F3ULL, 0x1484ADDAE4065774ULL, 0x187B2E288ED5A29BULL, 0x22F5A9D7E456DD18ULL, 
            0xE6FF145AF6E1B5F4ULL, 0x75DB3A562C28D484ULL, 0x1974661E813149E5ULL, 0x62B09BDA5B676ECAULL, 
            0x7289D65DC7A6A44BULL, 0x6B76192F77C1B395ULL, 0xE499955751141164ULL, 0xBFAEAE113FAEE3F7ULL
        },
        {
            0x0D811CF432EC4DE3ULL, 0xBFFF5BCEACD3BA48ULL, 0x77FF784E66618DB5ULL, 0x75CDF22C14B0EA44ULL, 
            0x8EBD17DCD93AB99EULL, 0x7F7E7B18707B23E8ULL, 0x168EB510D7B4369AULL, 0x0D1351837ADED6C8ULL, 
            0x8FE46F6EEBC485ADULL, 0x8669B45A1B30FD05ULL, 0xBE5F3ED11E214226ULL, 0xE959CA1338D3D999ULL, 
            0xE279B44B6066AACCULL, 0x2B790543BF224ACCULL, 0xDF44489D2D72A427ULL, 0xCF29ABCAE3178A4FULL, 
            0xBDFF302DE68EDF14ULL, 0xF614AB330FFB9009ULL, 0x630806B8B75976E0ULL, 0x10017B5C6E20B84EULL, 
            0x2B2735AC7E92A121ULL, 0x4A00741A6250786BULL, 0xB843069BB56FBEAEULL, 0x034DFD9D1A2519AFULL, 
            0x1B25285B476BF6C8ULL, 0x023962E9990F7E88ULL, 0x2BA3EC003302CCB5ULL, 0x80C875E80B35E20EULL, 
            0xE5E7FF71B02441E4ULL, 0xCADA3D7C4F629A91ULL, 0x0194135108508597ULL, 0x8A11293EB3BF420EULL
        },
        {
            0xB598E2613A8ECCE7ULL, 0x61195E31E083507FULL, 0x06808955D3EAAF2FULL, 0xB239C3EEF30F5846ULL, 
            0x5E96B9BB98311E1BULL, 0x5250E4EE2640EFDBULL, 0x62A0E44FB05D1303ULL, 0xB352853F4EF4080AULL, 
            0x54E073B8C3051574ULL, 0x06E9796AC65EB7ECULL, 0x6D163C6C81FFDF15ULL, 0xD8B5BCD99482C646ULL, 
            0xA2EBBF46CEEC0688ULL, 0x91291B56F525A887ULL, 0x9B6F0750939F1B27ULL, 0xBB99582CB661229AULL, 
            0x5C32F351DD1BF710ULL, 0xBADF247A9B55810EULL, 0xAFD1BF14E2365CCFULL, 0xC1F07D755A082397ULL, 
            0x950FA20A2F7AADF9ULL, 0xF89E3ED2DF5F9DB8ULL, 0x001752DA2F9A4AAAULL, 0x965A3B407F9B2132ULL, 
            0x6CDD2D696516F538ULL, 0xA9ED259BB911E386ULL, 0xBC023BAB75CE436BULL, 0x5E2F366E8383C6E0ULL, 
            0x689921C7BD37012BULL, 0x8AD98FFAD5383795ULL, 0x991B34AEE2BE7182ULL, 0xF8349FEB45AC68FEULL
        },
        {
            0x4E46197606A33EDBULL, 0x552B7D703925049AULL, 0x9EF7F3C9607370ECULL, 0xEEDA49BDE4FCC4ADULL, 
            0x707AF367F0102CD7ULL, 0x3024702A6BD01BB0ULL, 0x6B7E16C7E26CD02EULL, 0xDA75E397B3ACA4A2ULL, 
            0x965C53C7C8C20EA3ULL, 0xE9035E223D038E5FULL, 0x89296D10A82674A1ULL, 0x23045EB73B5D42BBULL, 
            0x2467ACACAE98BA60ULL, 0xF7DA3A268DB07C65ULL, 0x8504EFE014D9BC8CULL, 0x8A0FA5F9E4568079ULL, 
            0xA1122234E90E7912ULL, 0x3D3967F321003F30ULL, 0xD5306FD386B8B02BULL, 0xBA6B8EFC59B82B25ULL, 
            0xF29F1C0C0C55792AULL, 0x15AD36F1F6F01B14ULL, 0xECCEFA5C9BF59925ULL, 0x55EC0B49A715ED6AULL, 
            0x9503199DF662E327ULL, 0x846DC0F11BAB28EBULL, 0xBFC71A2E87732252ULL, 0x8851BB466346464FULL, 
            0xEF2C2F9EB506E50FULL, 0xB2275398CC1ECF2EULL, 0x1897495F5C4D34E7ULL, 0xE67DD501DC3806ABULL
        },
        {
            0x0BDD2C4524039611ULL, 0xD072E53ABD154B94ULL, 0x4BA1F47B02586DA3ULL, 0x9F21755BF31980D4ULL, 
            0x4F25D306BE2EC478ULL, 0x2DD065B40C1CC870ULL, 0x70807C89EA356A07ULL, 0x1015DC4BB6576823ULL, 
            0x70952B2D13230DCCULL, 0x69F48346F3E0611EULL, 0x700AAAA49D1E456AULL, 0x5C2E6AB2359DEDB8ULL, 
            0x9EF3D073CF5173FCULL, 0x53F0D294E024FBFDULL, 0x47F02DF0F8AD7A8DULL, 0xC0105948FF01CB0EULL, 
            0xCF45B42DFF184FD1ULL, 0xB9F5B00566325E9FULL, 0x16802833BB9B56E0ULL, 0xE4A719443613A588ULL, 
            0x9F02DB9B486D31C7ULL, 0xA339F44C0C3EAB00ULL, 0x48EA983381A16972ULL, 0x43E529B30EE1EEF3ULL, 
            0xC05555810F8A14B5ULL, 0xC730B08BF8B3C7ECULL, 0xAC584F023B89DD97ULL, 0xE850410506AEC7F5ULL, 
            0x9954A01BDF2AFFD4ULL, 0x58B8430343B44056ULL, 0x6EFFEDA2631C6F3AULL, 0xD952C96216D87404ULL
        },
        {
            0xB1FDF5AD5CCD4E38ULL, 0xE0866D3B5E2416ECULL, 0xAC7ADC21B82D8396ULL, 0x138C8CDEFD0B3684ULL, 
            0x7B7CF7F873438600ULL, 0x95FEB263871984DFULL, 0xB897572B9F07D0D5ULL, 0x22D749201A644A32ULL, 
            0x5962C4716270F3B7ULL, 0xF929646DC49671F7ULL, 0x669086507510C35BULL, 0xBD21410D28E04BADULL, 
            0xD45907802A67CDD6ULL, 0xDF55EA4210743DF4ULL, 0x35E5F5BB5CAEB057ULL, 0x315BB629B2889B7FULL, 
            0xC703E7D9D29589CBULL, 0xB78B91BDC0A30E82ULL, 0x84CBBA5EF35E8F6EULL, 0x364CC04402D5A43DULL, 
            0x999B986D63394422ULL, 0xC4092FB36BEF73BDULL, 0x2368D23A95406CC0ULL, 0x44E167A0D24F7C4BULL, 
            0xC3D9BA74833E4425ULL, 0x2B350791EB9AA70BULL, 0x6E27FD7AEEDFC083ULL, 0xA889410827A9FB48ULL, 
            0x054C16CB3B405801ULL, 0x5537BED48AA34BCDULL, 0x37C0DD4150F5B934ULL, 0x81F0839851521C34ULL
        }
    },
    {
        {
            0x2A5ECA5400E7915CULL, 0x907974879CACEA82ULL, 0x33D2BC19DAC7A7D0ULL, 0xFF4F9A40962687C1ULL, 
            0xCA43C6B7FF576066ULL, 0x30F0EB547190278DULL, 0x6030AFB9F5B74BADULL, 0x7FDCF64A61B97BA2ULL, 
            0xF6D5233A111B9C23ULL, 0x3805C78A46523EDEULL, 0x163CD3DBDDF050B7ULL, 0xA6DCB0221819EE30ULL, 
            0xA4BDE7BA1423B993ULL, 0x820F81AA4877634BULL, 0xF95BE6EF90A7AFC9ULL, 0x742EFDDAAD6FE803ULL, 
            0x93994FF79545E4EFULL, 0x8D648C385D05D51EULL, 0x259F9511A9D01041ULL, 0x7C70C76E603B28E3ULL, 
            0x61F600BE392B14D2ULL, 0xA9048484C9E65C2CULL, 0xD09C0A0652ABDF9EULL, 0x52932C59350CDAA1ULL, 
            0xDF954069CCCF2BCBULL, 0x6D00CA8575AA2D56ULL, 0x4DEBE491408662D9ULL, 0x021BB4332341FADFULL, 
            0x5367BBDFDC272519ULL, 0x97991697325B9FC0ULL, 0xAE51CA2FEBA9FCE0ULL, 0x42F4D79802E71662ULL
        },
        {
            0xD435765BDF2B2FB7ULL, 0x5BBE3652403D271CULL, 0x58AD2A79F8B5789DULL, 0xC577E8F8077A4618ULL, 
            0x563F91F98CD7709EULL, 0x62F212187E52A0ACULL, 0x7B3D229380C6685EULL, 0xFABE233AB95A67BDULL, 
            0x1635289B14A8D3B2ULL, 0xEA9606893FAD64A5ULL, 0xE213873A31DADD54ULL, 0xB6CCF0257EB20D18ULL, 
            0xC5AEDC3D65F1FC19ULL, 0x833F07336913FA5CULL, 0xABB2135A87A54A22ULL, 0x4A1E3483F7FD87F4ULL, 
            0x63E337AD1B24CE5DULL, 0x701D59E41A54E153ULL, 0xBCCB23A05085DCFEULL, 0x9589C10DB6E59928ULL, 
            0x9685680006A50322ULL, 0x1F1788BE50CCC247ULL, 0xDA6811BE2307CA47ULL, 0xED614A5C290131F9ULL, 
            0x3302D75FFE800E12ULL, 0x6DE4E5487AD0985CULL, 0x81BB85B34FB1FA1EULL, 0xEE335CA83651DDB5ULL, 
            0xF67CAB829764A538ULL, 0x4F8EBECC6DBFB48DULL, 0xAACA2C45EC9F20EDULL, 0xDD2EE6596201B028ULL
        },
        {
            0x3BBF7D37852EC5D7ULL, 0xE84B28F548527F0EULL, 0xB5FFB27422B9535EULL, 0x84B6CB95590EE361ULL, 
            0xDD3A77C97247199BULL, 0xFF9A990F7430A1F9ULL, 0x996928CF8DC857F5ULL, 0xA7FCB4CEB7565300ULL, 
            0x639D98B8B5A789DBULL, 0x64D89549EA7B3E0DULL, 0x6367678436E2FB4BULL, 0x516A1F52B34C10CCULL, 
            0x98BC90CC233928A2ULL, 0xEF6108B61D947721ULL, 0xA7B43DB29472AE8BULL, 0x8D821CA998627CC2ULL, 
            0xF8793737203F3C21ULL, 0x9EA955329914F014ULL, 0xB44AC163F79589A2ULL, 0xC9925E3EBEF171BBULL, 
            0x6D159879DA3845DAULL, 0x881F2A551066524AULL, 0x882E17D6189DBD82ULL, 0xE956C5509B68A6CEULL, 
            0x96CADC3BBD759A11ULL, 0x25388FF3A359A03FULL, 0xF7D7865690A662FEULL, 0x87CAC492D9953B4BULL, 
            0xDB97FD60F57C8F96ULL, 0xC4BB77D584FBDB11ULL, 0x87B8FB732FC56B48ULL, 0x482B9521560A8E5AULL
        },
        {
            0xAE7DF21AD191C647ULL, 0x176ED179BF4748B0ULL, 0x59AF2E6CD8FBFB02ULL, 0x8CB1C722ECA720A3ULL, 
            0x7766CA5ABA7F9474ULL, 0x4931DF38EFC7DB19ULL, 0x29ED99C8750B5179ULL, 0x79E7B093D2B9EE55ULL, 
            0x26B848A97EBB6AB3ULL, 0x4C935263450774BBULL, 0x8C0FD40750CE15A6ULL, 0xFC02F98B7ACB3AFEULL, 
            0xD2EC549F0CCA4B4BULL, 0xE1D81594176B58D6ULL, 0x8143F912269EFC95ULL, 0xD4A020815CD2FB99ULL, 
            0xF04189D127899FCDULL, 0x20D741E63EBF2547ULL, 0x8174A04E691EA558ULL, 0xD186656FD27BB5BAULL, 
            0x997471411752EFEBULL, 0xEDE53D2DC5FE109BULL, 0xE9EA467D3B7F2725ULL, 0x0C8168DDBECD5643ULL, 
            0x90AFF4D0BE6C4F2AULL, 0x3C3D3AC3E08D000FULL, 0x23C88F8437A0E998ULL, 0xA8DFAD4E94E0A56BULL, 
            0xC05036E3270EE4DBULL, 0x7519AFBF7AA68ACAULL, 0xA76AAB670F64F8FAULL, 0x82DE0177C0BD4E37ULL
        },
        {
            0x2D31055CACEA3EDBULL, 0x5BB0EB21392DF086ULL, 0x15E1DD65275F23A7ULL, 0x92F50F0A23A2721BULL, 
            0x86B3E5CC91BD2F9DULL, 0x27285520905EF8F4ULL, 0x7EEE06F026D6A9D6ULL, 0x24594C6719D7188FULL, 
            0xD9FBD506F0B9913FULL, 0x0A93952E787C170EULL, 0x9CC7153B0CAF9022ULL, 0x87513F0D8DB90C2DULL, 
            0xE8E522F296374306ULL, 0x25A2A5F934ECEA5AULL, 0xA5CEFFCA83E14032ULL, 0x4D47B3D0251C35D5ULL, 
            0xF1B928DE18C6388CULL, 0x5A5976640CDBEE18ULL, 0xB5AF4C7403A60C6CULL, 0xCBF15FD51341913FULL, 
            0x1BEEFD007F503DD3ULL, 0x183F4DF1D131B234ULL, 0x8CDFE9B13192CC5CULL, 0xB251D9A9E4A5A71EULL, 
            0x50DF79E38097CF93ULL, 0xE9069A7FA2EBF66DULL, 0x786C780D9C012148ULL, 0x335F7AB4BBA8FDECULL, 
            0x5D027745407E58B5ULL, 0x73EAC984C46D657FULL, 0x5D393E2494987B95ULL, 0xCE828599F051E646ULL
        },
        {
            0x358AA498D63006CDULL, 0xE762F1553063B09BULL, 0xE40A80486016089AULL, 0x56697D8DCF996590ULL, 
            0x34C0D49B021A08E5ULL, 0x03D5545D9B4AF6ABULL, 0x884CC3CC24515450ULL, 0x2274E9B393F9FD6EULL, 
            0x04D07F0469A70088ULL, 0x88652478D3C45F98ULL, 0xAE8F66093D246AFFULL, 0x46469F3EB5CE6048ULL, 
            0xDAEFE0148874D61AULL, 0x50F747E2FBB615DAULL, 0x8BFCC9A2B1385149ULL, 0xAE66CA6EA39C1961ULL, 
            0x5B980D4900073E0AULL, 0x5D6C412B45B56A47ULL, 0xB54A7071362A9AC6ULL, 0xFF89CFBE370074A0ULL, 
            0x9C9A626A92E63973ULL, 0x109B1E3FDA96F99CULL, 0x6023573B70CB3FC6ULL, 0xCDB7A75152B268A2ULL, 
            0x054C0AD347E5D28BULL, 0x5E523061EE4D86B6ULL, 0x3D6DCA91BDD0C58AULL, 0x225A13F0532312D1ULL, 
            0xBEF7F6709D810D68ULL, 0xBF396CFFAAD05081ULL, 0xD45298EF16A14B61ULL, 0xEC72AC814AAF32C8ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Canopus::kPhaseDConstants = {
    0xB50BA8352F6DAF3EULL,
    0x6D78352A0637C84BULL,
    0x2E15F32E629262F4ULL,
    0xB50BA8352F6DAF3EULL,
    0x6D78352A0637C84BULL,
    0x2E15F32E629262F4ULL,
    0x6FFF3D76C8911896ULL,
    0x75A423E3CF18ABC8ULL,
    0x3C,
    0xA7,
    0xB3,
    0x94,
    0xA1,
    0xFF,
    0xAB,
    0x32
};

const TwistDomainSaltSet TwistExpander_Canopus::kPhaseESalts = {
    {
        {
            0x9D7D5B6669F361B2ULL, 0xD6999286F5F2CA7AULL, 0x0698E8166E10E2B3ULL, 0x4EB42F2DF9F0CE00ULL, 
            0x68DC5601E2FD9B95ULL, 0xB2AEF54480E0708AULL, 0xC63B87AF32D3993FULL, 0x85D65FA754EA2F83ULL, 
            0xD4FE746799E95F2AULL, 0x0FFC7460AB76A923ULL, 0xD392012008A433D7ULL, 0xBC18B79516294893ULL, 
            0x13086B6AC4B36738ULL, 0xCA5E0495E3C34F9AULL, 0x9D6A337E4037081AULL, 0x70C8FFEEEF45F621ULL, 
            0x024533285A63F549ULL, 0x8388515BDB6F9E00ULL, 0x1495F729C58D4A9AULL, 0x27BB59FF01920FC9ULL, 
            0xC82D8217A4B96E3DULL, 0x0E291EAE342B6B7FULL, 0x9A9573FA22ADF4B0ULL, 0x8C2F2650859E8A3BULL, 
            0xA1AF9C76FFA7C6D8ULL, 0x46EB0748A303D5B3ULL, 0x66BF3CE7D1DA55D7ULL, 0x5A2627B9A9C68DFDULL, 
            0x6AC34409C9187E5DULL, 0x5CB7C2658B7B4BFCULL, 0x434D41A29E7C62F8ULL, 0xA4083E2BC498AAB3ULL
        },
        {
            0xE87CEC19773774D2ULL, 0x98F7C87D5982E01BULL, 0x9786373D766C5298ULL, 0x98FB625623792D05ULL, 
            0x991B3AFB916F64DCULL, 0x14B2BA1FA3AE6B48ULL, 0x341C61E21CE5AA25ULL, 0xAF157F69E5BE2709ULL, 
            0x2E6412267E00F3EBULL, 0xFD64DAFAA7B65AE5ULL, 0xC3EFAB418186FF6BULL, 0x8A5DEE5270DBE797ULL, 
            0x9B1011A83DAD0711ULL, 0xB677FADD5D7DAF2BULL, 0x43BD7EC9ADA44EE4ULL, 0x9C3CB101BB15089EULL, 
            0xF0F628838BFCDA37ULL, 0x075180BBA2F1B707ULL, 0xA2351E0ED87FF842ULL, 0xB67E8A6556186E1AULL, 
            0x523ABC504ACC446AULL, 0xA1907B2238C89535ULL, 0xB75487E4C27F5C94ULL, 0x473264C5D8F38E30ULL, 
            0xB5065C17077906ABULL, 0x3ACC9BEDF1550080ULL, 0x1ED4536A1437D3D6ULL, 0xF304CB8CECE3B763ULL, 
            0x6A111172D7D0B7F5ULL, 0xF2FB224E13D22F89ULL, 0x34BF2E59F9E30F51ULL, 0xF24AFB5B8E32F718ULL
        },
        {
            0x187AFA808093E187ULL, 0x0B487ABD2F189557ULL, 0xD8D0AF70BDF9D5CAULL, 0x66CB21ACAECB628FULL, 
            0xADE5F947564CE080ULL, 0x32A0726CFD56CC34ULL, 0x6312861CDF7C5015ULL, 0x7F5E29942584E7DCULL, 
            0x87FA1029F7D11E65ULL, 0x5F573C2B6E773849ULL, 0xEA8A05C93007ED0DULL, 0xCFA0431EB162FE8AULL, 
            0xFDAAA4D2C5D1582DULL, 0xB2FD24F59E1F4CE5ULL, 0x6117E6F337500829ULL, 0x1F5CA0776CFCCD54ULL, 
            0xA210D2768D28014FULL, 0xDD3E03CD35018C42ULL, 0xB5B03224827C275CULL, 0x7751CB1775159A32ULL, 
            0xF5234D469A237EDFULL, 0xFF0E291A5BE4B703ULL, 0x70EABBA6ABF6224BULL, 0xB7A561B6C8812F6BULL, 
            0x1239CB429050271DULL, 0xAC28FE768B36136AULL, 0x2B8BDECB8BCC6988ULL, 0x868623CAC8A91259ULL, 
            0xED231D15713F41ACULL, 0x3B222F3BC6B0275FULL, 0x88673E9AF3F7C952ULL, 0xF51629B0EA5D9220ULL
        },
        {
            0x281536F2EF581FB2ULL, 0xBB577DA4CFFE1E76ULL, 0x38C0203EBCB52E08ULL, 0x3EAD3FA5BF6F2A8FULL, 
            0x016FED4D173E043CULL, 0x4C8030FABFA9CEBEULL, 0x93FF933E8B2A20FCULL, 0x2C1A8CDAEFAC7AD0ULL, 
            0xBEAF43D8171CE466ULL, 0xDB0E557CF7CA0977ULL, 0x1AD771420AF08F4CULL, 0x7D13D698F9977A0FULL, 
            0x9C76E0CB174400F1ULL, 0xC0A00FE0ADECF3BAULL, 0xC5ABCB07699AA1B3ULL, 0xB8771671445553B6ULL, 
            0x482065D5CEAD0A0FULL, 0xB80E4FF3EAEC44A1ULL, 0x86ECAC8456B9721AULL, 0xB30A5BFB670145AEULL, 
            0x5A9DBFA4E80B3C60ULL, 0x16E2FE0315231E9BULL, 0x49072B10FA6D69C5ULL, 0x330FE232CE165AB7ULL, 
            0x6C7A597152A29E59ULL, 0xE5C9A548AA287657ULL, 0xEBDCB10B087555DDULL, 0x2718DC097378C127ULL, 
            0xB73E872F5EAA2746ULL, 0x275A80C19593DE1CULL, 0xD2D32BD9717946ECULL, 0x46969F0C2BBA743AULL
        },
        {
            0x1CEAAA916140E0A8ULL, 0x0CDF7F647783AFDDULL, 0x9D4E155CE04FDFE9ULL, 0x793FD75FBB0EAFEEULL, 
            0x328DD450D256D708ULL, 0xA8FE40EB5A3D1D86ULL, 0x6358E8DEAFB74246ULL, 0x60830741804D0EA3ULL, 
            0xFB4DAA6D17451FB8ULL, 0x9D63A3C0B792D197ULL, 0x45280665A4D9270BULL, 0x4FF10376533BF418ULL, 
            0x8451D154276AD76DULL, 0xD1BC712BDDA1214EULL, 0xBD63C90BE1CED746ULL, 0xD5C319DCF8957CD7ULL, 
            0xCF2C2F7C9C8BDF60ULL, 0xF7DD98520EECD069ULL, 0x0526795EC9FFDD66ULL, 0xF300ACA15FEE915CULL, 
            0x6C9E09DBCFFE3C79ULL, 0xE9B843B8A439AD90ULL, 0x7AF58A09FDCA088EULL, 0xC89D740430206B6CULL, 
            0x66771C7428972CF2ULL, 0xFFD106F3204A54FDULL, 0xDB00DCD9404259C8ULL, 0xD21BE4730E3B5074ULL, 
            0xB6D804EC1AF56B41ULL, 0x694DF4821D2772BAULL, 0xAAF3F475B4532EF3ULL, 0x110E3B2EC704E667ULL
        },
        {
            0x545F2E8E4286900FULL, 0x59DE04FF6E08CECCULL, 0xF2E909FD05E64B67ULL, 0x65EEC3F57E7E54CCULL, 
            0x57629D7FEBDF795DULL, 0xBCA951AE8E90A01DULL, 0xEDB500968F91C416ULL, 0x7BD189539BEC865CULL, 
            0x23DAA975616A61D0ULL, 0x4F7A18934CC67497ULL, 0xB01D4EF42A8078CAULL, 0xFA3703AA6CBC8F00ULL, 
            0x281EA8972B26F339ULL, 0xD8CBD8A3BC69F9B3ULL, 0x880B4D1D567CC9A8ULL, 0x2B59B6BC55A7E9A1ULL, 
            0xB06064D4B7C2558BULL, 0x0CFD85F64513C0ECULL, 0xD24116E941EC9207ULL, 0x93D77890CB9C9C6AULL, 
            0x0E53930A83A2BAE2ULL, 0xEEDAC6C27C556E75ULL, 0xEDBCFB3B4E567D6EULL, 0x93E993F56A41C1C2ULL, 
            0xAD6FC1330A8FD3A1ULL, 0x1EE29274D48444F8ULL, 0xEB1979A8C13FE61AULL, 0x0928FA58AD5AE249ULL, 
            0x44C876786A6812E7ULL, 0x6389BE90AF328228ULL, 0xCA9ABD671BFFBE8AULL, 0x4F5E55E50D1855C6ULL
        }
    },
    {
        {
            0x1C0C6311220F7CBFULL, 0x8245E28F8E05C84AULL, 0x1F0FC4A80F3D3B5AULL, 0x36ECBEA0BD644EF6ULL, 
            0x99F05B75718DF815ULL, 0xB65B57C2B6ED3925ULL, 0xE09CD98E16F50F2AULL, 0xB61D228036FB7DC5ULL, 
            0x68880ADBCED8D4DEULL, 0x3C0B02751C56777EULL, 0xE948FBB1C7975D35ULL, 0x7B6CC6830DA71253ULL, 
            0xC12C4F6462FAD29BULL, 0x8E75DC3FCC15AEB3ULL, 0xBB8C47F125C31C40ULL, 0x2ADA39A3B75AE346ULL, 
            0x66BDFAC4BDC068CBULL, 0x85AF4FC08B62131AULL, 0xCDC7792E27C0B5DEULL, 0x39ACEE14422CA10DULL, 
            0x80EF1AF297A69F83ULL, 0x338E0DBE5E519B43ULL, 0x3635470DE2F171DAULL, 0xA1C56206492D7771ULL, 
            0xAED9AC9248B5CB25ULL, 0xBF8028DE837CA10BULL, 0x0BACE60060BB180DULL, 0x438B8754DFD0DF4DULL, 
            0x6205B57EDEED5295ULL, 0xF1B087C9DBCA62ECULL, 0x25E75BCB0B28323CULL, 0xD31D828ABF8CC6CCULL
        },
        {
            0xB96DD9DD78EA3BF8ULL, 0xA79E2B00C9ACE9A3ULL, 0x9B482464E772776CULL, 0x3A9CDEDB6E4AB3E3ULL, 
            0xC209F873D3912EA1ULL, 0x17319B338A7EBEB3ULL, 0x6DA7E325F66323B6ULL, 0x0EEFC9B14C89985DULL, 
            0xA33C443F1C053395ULL, 0x3D0794CED390A48DULL, 0x86AD20175B2744B3ULL, 0x671F09262994DE1CULL, 
            0xC7CCD5F73FE51CD3ULL, 0x173F879BFCDF7A7DULL, 0xC00A9283EEE79DA9ULL, 0x9740A854393EE472ULL, 
            0x5B64CA8D2EF97F17ULL, 0xF723C7B57090B501ULL, 0x825545E2D1000354ULL, 0x1ED6E2EE375355C1ULL, 
            0x2FCFE2F025758F36ULL, 0x39280B704E971A4CULL, 0xF57C8AAA13BCA296ULL, 0x0231AE143FD0E9E1ULL, 
            0x0A1E381DFA829A17ULL, 0x666F1B5FB7545D2DULL, 0x988F32B6C609DE28ULL, 0xA0236FCBCDCD4B52ULL, 
            0xE0D8B69D904FCDA2ULL, 0x9E5D457D764246AFULL, 0xE35971CB1DD93E3DULL, 0xDCCAFFFF9D331A0EULL
        },
        {
            0xCA4582DFB2049549ULL, 0xB34497F22C7A0CA9ULL, 0xABC39EF0F44EA433ULL, 0xB6CC0B62AA77144BULL, 
            0x4E7E54022313CCCFULL, 0x3C9AB42DF2FF84EBULL, 0x0C79F4F3AF1AA29CULL, 0x710B9531A3CD31B6ULL, 
            0xC80117A471DFF6DDULL, 0xD55739DE9364C0CDULL, 0x51264D6CD69FBFDEULL, 0xCD14B4A7772509AAULL, 
            0x6E7FB95EF0FE2313ULL, 0xFF3DE0D7BD6A65B8ULL, 0xF5FBC47E4A7ACC0AULL, 0x324AA36B93D1A4D3ULL, 
            0x35F3F2C3237BC1C4ULL, 0x8DAC044CE31EA0F1ULL, 0x1EDE993084D8EDC1ULL, 0x9E0435BDF3E677DFULL, 
            0x6589C8A25B2DEF2BULL, 0x50C0939F264C3BA3ULL, 0x9138C026DF1B06E2ULL, 0xC81BD054159E2C7CULL, 
            0x0C34F94728201F55ULL, 0xCF1D372A1F73AFE4ULL, 0xD2DFDA6A9D6939F8ULL, 0xB61D5D7C530B6A56ULL, 
            0x260733526335CEE9ULL, 0xE91AE988EBA485EFULL, 0xF117DA013A1C8C99ULL, 0x3F80E9323072028BULL
        },
        {
            0xBD82485A0B037729ULL, 0x57FC04B7425CB325ULL, 0x6E575BFC809F8D3DULL, 0x18FEEE14A8AF123EULL, 
            0x5A1A288C058B3A60ULL, 0xBCE8BADA4F0B15BDULL, 0xF13E4F6462A34A16ULL, 0x8AA79CAAAD560337ULL, 
            0xBD2AB77E162BBC8FULL, 0xF38711C47FB53281ULL, 0x290D4949FF5CB89DULL, 0x9C53A063292323CDULL, 
            0x3C001265C8703B74ULL, 0xB5CF394BC152C756ULL, 0xCFB38723DFF486F6ULL, 0x5FE57DE203DE4D4DULL, 
            0x3087181D5FCEA1B1ULL, 0x0718BDB1F702EB5BULL, 0x7816853F6C8927EEULL, 0x293F336D2AAE9D00ULL, 
            0x0B879843CE21581EULL, 0xD8CD7C4171F880DFULL, 0x272438655E313851ULL, 0x1397B014E2D5D36DULL, 
            0x47D31EADE0F549CEULL, 0xD5FACF92BCD8DDB5ULL, 0xED2068BBFF58E479ULL, 0x120D75F27047BDA3ULL, 
            0x41CFEC37CECE149BULL, 0x7B8DBD64BE036791ULL, 0xD10F3C65302FF9C6ULL, 0x986FBF8D57F94AD8ULL
        },
        {
            0x4EA6799F58113BD8ULL, 0xA38E4D5AB69BC401ULL, 0x808C50C9192DCB17ULL, 0x4E6274D0AB49FCB5ULL, 
            0x880B88BC4389A412ULL, 0xB3BD4FDB3B50317FULL, 0x38C3F9BC1CABDEAAULL, 0xAE286E7E79F814A4ULL, 
            0x0788D59A5A5E6CD6ULL, 0x7184E15D0DD575C4ULL, 0x38AF21F255D9BA0FULL, 0xA700160F757B68A4ULL, 
            0x293AED9FE352AA63ULL, 0xB02806396FC5BF08ULL, 0xA9DDFB314A318D5AULL, 0x1AE8A2A1F1C4A11FULL, 
            0x47AA1F27B6046243ULL, 0xD276882860A5D67DULL, 0xCF09DE649891054BULL, 0x0D5BCC3D59EB31B0ULL, 
            0x8FDCB424848BC4AAULL, 0x8206BBD8C03826EEULL, 0x73A36C5E8A3A4094ULL, 0xD18B677F56D2C855ULL, 
            0x1720597FE906B6A8ULL, 0x3DFE1DF1CCBAF6B7ULL, 0xA6E2F223121B4EC0ULL, 0x942A4887283C79B2ULL, 
            0x17EC4ED2AFDBE922ULL, 0x8EAD0E3A6FE708D4ULL, 0xD29B75C389A51649ULL, 0x61E22FE14A220B3CULL
        },
        {
            0x16459B040744B3DFULL, 0x97CBE09D70E43D89ULL, 0xAB9ABC0B52DFB987ULL, 0xCCB50965FCB90C64ULL, 
            0x5DB9426D22FDEDB3ULL, 0x1455C00EFB97F2D7ULL, 0x3A2D9D29FA1EB1CDULL, 0x476E41FB1570C9A9ULL, 
            0xF6A736506D47645EULL, 0xBB289A3EB8E518ADULL, 0x86F4247DC7FDE982ULL, 0xACD44DAAC33D964EULL, 
            0x9CF7CAB5D97BE3B2ULL, 0xF4E5C32056DFDC2CULL, 0xAD340B4BCDAA970DULL, 0x141F5D88D1C6EB90ULL, 
            0xB7694AAD1A27B3C3ULL, 0xE8605E8C45B228CDULL, 0x774A7E243270CD41ULL, 0xBB426BC010EDF9D5ULL, 
            0x89E2428E9D2E3BB6ULL, 0x969E6E033AC7F843ULL, 0xF48805AF81AA7C25ULL, 0x70CC567280D30C0BULL, 
            0xECE5E125F5E63053ULL, 0xC2E7E4EB6BC4BC0DULL, 0x219276CD548A00CBULL, 0x6071A04201669EB8ULL, 
            0x4E52F150DE16FA93ULL, 0x04EA5E2FEFEE6531ULL, 0xAB375B437342E107ULL, 0x8BCDEBF6A4710E6CULL
        }
    },
    {
        {
            0x9489632AD745AE32ULL, 0xF4AA7BA7F87C2B61ULL, 0x152C94D79CC4328DULL, 0x7567DBC2ABBD6B19ULL, 
            0xF2B55F6D61B8FF11ULL, 0x62B7C7CE482FB71BULL, 0x9FE7CC9DBE5BD2D2ULL, 0x6B19FD1C71A49A11ULL, 
            0x4FF1AB6954F95DB9ULL, 0x3126AE42699ED3D6ULL, 0x5EE1AE311B9BAFFCULL, 0x99A739D4C50788FDULL, 
            0xD01B5472735DFCDEULL, 0x9D649A5033DB5ED7ULL, 0xEBAA25739A6BDE07ULL, 0xFF7E6EC49298E554ULL, 
            0x56664F6E63AE488EULL, 0x1E9984777BAE70C0ULL, 0x7A40C2E00216EF5FULL, 0xE11984DA58C3F82BULL, 
            0x5CA4D7B9DE81AF89ULL, 0xDC29A9CB12606F15ULL, 0x159AACD7FCFCE7BCULL, 0x02CA9FCFD4AAC641ULL, 
            0xDE0910A0E42E686FULL, 0xE124FA504109857CULL, 0xE607504EAD06A0D4ULL, 0x4686C504D2830ADDULL, 
            0xAEB6073F27EF6CFEULL, 0x0F1BC3E45EDCA64EULL, 0x4672DC706D803F9DULL, 0x379ABB611D3A26B7ULL
        },
        {
            0xEE486C3D1F73A7C0ULL, 0xFB1914290397BF66ULL, 0x545A511E583A6780ULL, 0x215AD02B914FD880ULL, 
            0x934F3268B745A192ULL, 0xC49A6C92D70E3BABULL, 0xE2F544A92D2DB9DBULL, 0x94E0F253F979181EULL, 
            0x30DB9EAB97653106ULL, 0xFF6B3E683E93471EULL, 0xFCB9E1909129FD6FULL, 0x8462B4928A2A07BDULL, 
            0x76CB52F33717FA1DULL, 0x1738840EF21D464CULL, 0xB5FCD8246001BA28ULL, 0x4B20127695B98FCCULL, 
            0xC6C7CF6A47602534ULL, 0x3B33F9782972B06EULL, 0x026463E9A2FCF2F0ULL, 0x91632FEBAB0A8828ULL, 
            0x9E5540ABE7F6D053ULL, 0x8ED8D90417FAE834ULL, 0xD2BEC49BD2D03F5CULL, 0x5CA5287F1DE5109CULL, 
            0x03815B449D229B5BULL, 0x6689EA557811A072ULL, 0x712CB5D1133416A9ULL, 0xF5E402BB1F12C7E9ULL, 
            0x8574C991000150FDULL, 0x38C4B5D1068981EEULL, 0x0D96F9EA194D3F6AULL, 0x522C67A5680243B1ULL
        },
        {
            0x2175BA26628CA209ULL, 0xBCA9513837422E85ULL, 0x9A98DB08A9EAFEECULL, 0xEFD5157D6D74B6BCULL, 
            0x3D34D2F7CFBB0799ULL, 0x3E6C229EFF43F641ULL, 0x186DA2602625DB77ULL, 0xFF7C0DEF55F56F6DULL, 
            0xFDC3602178265733ULL, 0xD2381E2429ADC1DBULL, 0xB9E6F3706BBC25BFULL, 0xC090D9CFB2B7D3B2ULL, 
            0x25E2E388C6460CF9ULL, 0x5D76473D7528291EULL, 0x108A59A2E4983052ULL, 0xE54F1EA1E63E2D7FULL, 
            0xBFE185F51F1B80F6ULL, 0xC7FAFA50ECA2A4A3ULL, 0xD95B5352ECD49417ULL, 0x5892106788686C95ULL, 
            0x747E51613BE35A34ULL, 0x444B3B0E4A50DEE9ULL, 0x29CE41CD257303F7ULL, 0x8EA57D0AEB93B14FULL, 
            0xFFF4B023FF41AE0DULL, 0x5F6900E2410E6227ULL, 0x9BDBD4ABB47DEE20ULL, 0x8BE984464571387BULL, 
            0xDB14680E9ADC9970ULL, 0x7D645B2078E24B43ULL, 0x6CF70FAC0EE1778CULL, 0xF34362D9CC8975D3ULL
        },
        {
            0x174E466BCC31D1B5ULL, 0xC3E79A39B3EF0062ULL, 0x2F74C280B3740AA5ULL, 0x1F0FA43E8E3C9EEBULL, 
            0xE84C9B05720F93CAULL, 0x64A7D626E66E6357ULL, 0x21D06B8645677DB2ULL, 0x0509A8FB37CCA38CULL, 
            0xF46A1E2976C56D96ULL, 0x440886DFB0254F40ULL, 0xFB3EB34D02A41649ULL, 0x537A17F19CDAA41CULL, 
            0xE0D103EFBF60666EULL, 0xE3A2D8055F336FF6ULL, 0xC2D9158F6C327F53ULL, 0xF34013BFC699E898ULL, 
            0xEA0BDA8DEF10F2D9ULL, 0x1F015A1F2A8673CEULL, 0xD31DAB09E159487FULL, 0x1EED9B86843F651EULL, 
            0xDAEA0A51910741A8ULL, 0x87C050B68F476D45ULL, 0xD6C2D1C96A4736A3ULL, 0xBCF2629D6051752DULL, 
            0xC53A42457AA934D6ULL, 0x71760463833E79DBULL, 0x2B1304C73D406F80ULL, 0x1C74FCB8A086A2F9ULL, 
            0x05C9B9C9DF984374ULL, 0xF9374E1FBF5BB69AULL, 0xA24DBC4B20342C3BULL, 0x2E31B62C7DFFAC55ULL
        },
        {
            0x3FB3A6CE513B679DULL, 0xE595CDAAA64D25A6ULL, 0x4698C1C01F906F9AULL, 0x2CAC950647250679ULL, 
            0x6CCE46BD4D4E658FULL, 0x9FB7B8507503D98DULL, 0xAF9EAE4580EAB554ULL, 0x96B3BC5BD05D2E28ULL, 
            0x73809AD9D7DF6820ULL, 0x75062917D5118EFDULL, 0x7FD90FFB21E05235ULL, 0x94A043A5ED93BBF2ULL, 
            0x7A84A5CFF917AA94ULL, 0x56D02587042C2BB4ULL, 0xE33B963DA2D92DA4ULL, 0xEA947D1C11BB0EAAULL, 
            0xC2F58BEE362405B6ULL, 0x98D0E493C02C153FULL, 0x64DC7956DECC62A0ULL, 0x3A5CE9EDFF063525ULL, 
            0x0A2449E483E463D2ULL, 0x39E950166D8F53E1ULL, 0x59C9616E884DC01AULL, 0x498389B275E96838ULL, 
            0x59B272C62CDA3009ULL, 0x93A5C6FB533B893AULL, 0xC3EC3EBEB1297B22ULL, 0x37E55FDDAE463F3AULL, 
            0x19A791C73BFC5EDDULL, 0x12420B386B41CC80ULL, 0x9DC5494EFB868817ULL, 0x9E5FF371C3AD1E45ULL
        },
        {
            0xEBD711EF32C21B21ULL, 0xBA1664131FF16282ULL, 0xBBA7CA26C3664E16ULL, 0xBE34BC92A068CFFAULL, 
            0x4B4CE9139C0127CAULL, 0x091FDA7C3E7FC52BULL, 0x543C01FAC272703BULL, 0x087A4E1D02090F14ULL, 
            0xC8A307668C555B4AULL, 0x22A39C4014D6D687ULL, 0x436603BE7A7411EFULL, 0xC2F9594A87CBAD9DULL, 
            0x8EE2ADCECF0A3CD2ULL, 0x846CECEE7F191AD5ULL, 0x470E10DC7375AB88ULL, 0x5721F9F3D3112509ULL, 
            0x32CE3EB217464C1BULL, 0x5A9DD18726E65028ULL, 0x2CE3EBCB80F31BD1ULL, 0x5FD99E7DDBA306B7ULL, 
            0x39A0038E51C88FCBULL, 0x5DE6CEC60FE4AC83ULL, 0x4E6DDFB6D658B938ULL, 0xB70DA83211F7AF4FULL, 
            0xA5D4088374A8C433ULL, 0xFE371AE42399A6F7ULL, 0xAFE4BBE52731C1C3ULL, 0x2868A74F960B6B05ULL, 
            0x4FE79FD9F90C2269ULL, 0xA18883CAFD00CDA5ULL, 0x917EE3257EFB7FB8ULL, 0x3690C972AE0BA201ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Canopus::kPhaseEConstants = {
    0x85169560E9083572ULL,
    0xD20957124058E782ULL,
    0x690FC9C9C9D73500ULL,
    0x85169560E9083572ULL,
    0xD20957124058E782ULL,
    0x690FC9C9C9D73500ULL,
    0xC8355DFB179F13DAULL,
    0x476C3837C45402C1ULL,
    0x99,
    0xE9,
    0x58,
    0x4F,
    0xBF,
    0x50,
    0x5E,
    0x30
};

const TwistDomainSaltSet TwistExpander_Canopus::kPhaseFSalts = {
    {
        {
            0x89611D1E485DB9AEULL, 0x984A7A3C639C2EA3ULL, 0x75DC460ECF7FE495ULL, 0xC4A063A76CDB3AFBULL, 
            0x337014C3435EDCADULL, 0xC337B854785616C3ULL, 0xF6A43B02A61935E0ULL, 0x2E21C3E96D2F3A74ULL, 
            0x1D546E652C6C2558ULL, 0x862D0E3CDC553760ULL, 0x58F8E7FDC9790AE1ULL, 0x72FD616C2059DCADULL, 
            0xCE660C070C8B47E8ULL, 0xD5807793E641ED22ULL, 0xB297F45A5722BCB1ULL, 0xBDCEB452253CCE32ULL, 
            0xC035E45DC29D33AEULL, 0xCAE2582D45FBC93EULL, 0x245D71DA619604A5ULL, 0xE961CEE23FF02C19ULL, 
            0x7971998C000AC1A6ULL, 0xCB51404BE3E557C1ULL, 0x89B7C0B11BB02870ULL, 0xD8974B90757E30F4ULL, 
            0x4171E31EAAC68F77ULL, 0xA0FD6603E01F57C5ULL, 0x6B28AF9697B75F6FULL, 0x2A26CE9ABC70011EULL, 
            0x1322F8A077845178ULL, 0x79D51FEC3EFC7AB6ULL, 0xA33B21ED1F7143D2ULL, 0xB2554BBF07D0D2B8ULL
        },
        {
            0x4280ED7480E4AE2BULL, 0x919BC7FCB2C9FFC0ULL, 0x52F1C1810957C15AULL, 0x77F6DBF3E52F0BD5ULL, 
            0x46A3D186FA253C0FULL, 0x7925EC21D7A2B867ULL, 0xEA7682AF9C4677DAULL, 0x414642FAB47FBAC7ULL, 
            0x8A302FD43504C959ULL, 0xEEA298DAF7F54995ULL, 0x165A55CBB6BD1B8BULL, 0xB58DE60C23A70354ULL, 
            0x26364B116FF865D0ULL, 0x32A10AEB515B3B2EULL, 0x9B7A87257477907FULL, 0x3601114DEA73507CULL, 
            0xA03A1BD541D8037AULL, 0x141358DBAF88FAD7ULL, 0xC85B1A5CA01FD29EULL, 0xCCF483980010F134ULL, 
            0x38076741469BCCE5ULL, 0xB6726AABFB172A2FULL, 0xCB431794237C2FB1ULL, 0x1D18A9370EA35787ULL, 
            0xD2A2C3FA3EF3988AULL, 0x7A0FFDB35EB3AD24ULL, 0x2DC28B1BBDD356F0ULL, 0xE2E5AE2AC3E93A9CULL, 
            0x689AF2FEC710B3AAULL, 0x38A2523219C472C5ULL, 0x1AB89181EF58426AULL, 0xFB8F9353CE2C362CULL
        },
        {
            0xB1AE5E12B33A2BC9ULL, 0xFA6B29522A7C9DFEULL, 0x2534601AEF56AB45ULL, 0xEA25F4A899D0F930ULL, 
            0x3E8AA6A54833C101ULL, 0x241C26D66920F122ULL, 0x657A40F269596A50ULL, 0xAEDB538B4D356ABAULL, 
            0x5E11E7BF4A31F58CULL, 0xEABA26D51E74FC6AULL, 0x23E2C16E694473F6ULL, 0x982202DB4FE7BB8BULL, 
            0xA0089DEFFC9B8538ULL, 0x74C4CAD4EFD48EC2ULL, 0x3A9108622C91051EULL, 0x8873D7DDD27A2A68ULL, 
            0x9EE99ED620362030ULL, 0x90B62B39995C80D7ULL, 0x0845C956A7FF016FULL, 0xB1ABBD25109FC795ULL, 
            0x6D10A4E4F5B0EF7EULL, 0xFC15075A91E3AE34ULL, 0x0CDF95D95F352668ULL, 0x3EE6DBF43F09FA39ULL, 
            0x72DD042F61175843ULL, 0x28F3728EC8FF57C5ULL, 0xC0AEA1F784395469ULL, 0x1228A5FF5F1D48C4ULL, 
            0xA816DF1C98023056ULL, 0x25BD7B454A37A44FULL, 0xA9A266071EEDF344ULL, 0x77D5B6F30A1D5B04ULL
        },
        {
            0x41F7531036028797ULL, 0x8EA949D46282117EULL, 0x27BB0BF747584536ULL, 0x7E0C6900688D7E46ULL, 
            0x52FC635FCA75D7BAULL, 0x1AF9689C0FAD689CULL, 0xE9707CDC4D61B74CULL, 0x333B4143E179245DULL, 
            0xF975CE7DB0C53402ULL, 0x7FF12A2CC7DF6324ULL, 0x5CDCCB7574FF63C7ULL, 0x1B942BD7A5639C8CULL, 
            0xCDA5D9D72423FF81ULL, 0xB286605FE5C20723ULL, 0x5EE81D146B70C8ECULL, 0x217CDA46896B085AULL, 
            0x53638C8AB49DACE2ULL, 0x285D83FD05063994ULL, 0xE7D274671FE9C3ECULL, 0x0A08ACCC6F24CB88ULL, 
            0x0D0E221FE2945B57ULL, 0x227E2DD64CCA1FC5ULL, 0xF82C5D28033FE0C6ULL, 0x03C2EE985E74501AULL, 
            0xFC970FB1CAB4A3DEULL, 0x3BD8532FB73AA343ULL, 0x0A611548C9F5A060ULL, 0xA4B8332DB98149A4ULL, 
            0xD849C8547A3D5D52ULL, 0xB856A17815B2D913ULL, 0x1443F1A7B0A1139EULL, 0x3013AE555073D705ULL
        },
        {
            0x5CDF5C76E1BAEC6BULL, 0xD86E90497BEE89C4ULL, 0xF1393F426A7AE218ULL, 0xA98A8548F4AC7801ULL, 
            0x3BD4636234ACFE8CULL, 0x0A7F63573628B55FULL, 0xA1944A3BE1F3C7D9ULL, 0x59802D42C5AAD45BULL, 
            0x69330B8C4A7BA741ULL, 0x6071A382DC00FE55ULL, 0xE9108A3A628E317AULL, 0x5A96B03DAB1D2E39ULL, 
            0x43F8B846E20BE2DAULL, 0x8BBC76FA13FB81CDULL, 0x6E8E4D9F5485F813ULL, 0xE87AA6A7B634C7DCULL, 
            0x54BC9F39A6B39100ULL, 0xB1ABA17B9CD66FB2ULL, 0xB7069BEE7979CF68ULL, 0xB1974863259E6434ULL, 
            0x03430E2B80E47C83ULL, 0xB88F85B3A314D141ULL, 0x59486D39CB567B65ULL, 0x60278F60C65E9B27ULL, 
            0x6181AD7C22E547D6ULL, 0x314932F295E8A417ULL, 0xF099709DF1801544ULL, 0x1D81CC2BF13EBF76ULL, 
            0x4ACECE69D2759E99ULL, 0xE6AAC1DE594CE8D6ULL, 0xDD9423DD04D9AF25ULL, 0x21CB44ED9BD6F5E5ULL
        },
        {
            0xFC908FE968354D6DULL, 0x4E6881856F3AAF1FULL, 0x37E772AB54F4987DULL, 0x05E13AA5E0C50955ULL, 
            0x245D6ACFB726FE48ULL, 0xAABFB0D5EAE73108ULL, 0x1E5179EEE5EB78A4ULL, 0xA30B5239378FE342ULL, 
            0xAA4E6165557005E4ULL, 0x40C6CCAFFA631BA3ULL, 0x3643CB871806DD79ULL, 0x51466BF736AD7ABFULL, 
            0xFB1B3BDF5BDFECBEULL, 0xD06C53057EF17D89ULL, 0x908FE56EE04D2D87ULL, 0x6ED5048149E86B38ULL, 
            0xAB33589DDEF1F11CULL, 0x0C42C6F9388D0049ULL, 0xC46BA7799CF0C6D6ULL, 0x2FE21EFEFE1552C8ULL, 
            0x032AE86072426653ULL, 0x0B0F5C2E3A0D9FAFULL, 0xF79BE2D7D32EA5B5ULL, 0x3373C5FD7518D18FULL, 
            0x5785297B7906C8C3ULL, 0x3D953337E975AACEULL, 0xBB308D4ABD373434ULL, 0x00BF9819035D1544ULL, 
            0xF3D2DE82ED1E42E8ULL, 0x74934C9C4A55D568ULL, 0x55FBB3253B8D7F54ULL, 0xC357A875AC3435EEULL
        }
    },
    {
        {
            0xCDF5052407C38B15ULL, 0xE92D29A284C3E4C7ULL, 0xE20C944AD0371440ULL, 0x9A77196D510E1BEDULL, 
            0x0B24895D93133BA8ULL, 0x91B4EF262B8D52BCULL, 0x4A52CC66C4A5BF57ULL, 0xDF7362181E757D72ULL, 
            0x79E5A1B673D5D70BULL, 0x8B0CB789902051DBULL, 0x0D929598BA747F2CULL, 0x5194FF96B8291175ULL, 
            0xED3A7E3C30CC2DE7ULL, 0xF8665F23FF2EB8AEULL, 0x524B9AA4DB5D2889ULL, 0xCEDA5EAEEB9B98D8ULL, 
            0xEBE6807F95383650ULL, 0x2A696040D65D88ECULL, 0x1388B5AF9F2A0405ULL, 0x54C96BC8C8316A70ULL, 
            0xD467BDA1A7844A23ULL, 0x8FD284A400AC3F35ULL, 0x1D92349B8FE3997FULL, 0x0866CF13985C04C1ULL, 
            0x6E2A124E3B1D7060ULL, 0xADB9BE9017FB1D97ULL, 0x9B9DEAB0F712925DULL, 0xDB3600B69C94837CULL, 
            0x2EFEBF847ED0A0E4ULL, 0xCFA41D93E2442466ULL, 0x4F70BEA6A4C4EEB6ULL, 0x431BD673C34CC669ULL
        },
        {
            0x140E68A8DF32D755ULL, 0xDF541ED8B3F5D8DFULL, 0x4A1E0EE59FC4209FULL, 0xF2B4186F6A99D678ULL, 
            0x93FC2AFDE0E1C080ULL, 0x272358830E11D983ULL, 0x627E18F84CB0EDE9ULL, 0x526BD4E30D37F7F3ULL, 
            0xAB9C8DAD847885C3ULL, 0x8C92126F45159DAFULL, 0x072F20D8A4683100ULL, 0x5D64C790DFF54925ULL, 
            0x7E688925E9333579ULL, 0x6BFA69C2AAA2DE11ULL, 0x4877C63CD762AE87ULL, 0xC942CB5F697E3B5FULL, 
            0x64C1ABB624664AAAULL, 0xCC35B80E8ABC27B2ULL, 0x88FD4D731ED44DB9ULL, 0x00BAD14E70894125ULL, 
            0x06770FD6E37EC86BULL, 0x1F9FFA8642D9567DULL, 0x7F1B3449A1A2E174ULL, 0x9756361EA339E86CULL, 
            0x7F513BF3326D609FULL, 0x96A2DD67443EF593ULL, 0x60328780164137EDULL, 0x57C871E27AA76A94ULL, 
            0x929FB12001B93941ULL, 0xBD0E0868E4EDD89AULL, 0x284EC968794D28A8ULL, 0x1479D4E1EC3A8321ULL
        },
        {
            0x6ABE42E9D9D098B3ULL, 0x77A4DD1C728FCF9BULL, 0x656B1B7565C90A74ULL, 0x8FA13A90F3448920ULL, 
            0x323315DFE93070DDULL, 0x213E54D2939C0C8BULL, 0x2C681B5EA3B210F6ULL, 0xFF7523012D4BA5CDULL, 
            0xA21074DB71FBC90EULL, 0x26721989F97E7FB8ULL, 0xEB0979E49BB19B27ULL, 0x2A3A71F95F290A8FULL, 
            0xA37C88EBF0195118ULL, 0x0E2B37B6F012A293ULL, 0x7E1EC80C4051FE48ULL, 0x4706BEDC50E23EBCULL, 
            0x18199E5704206479ULL, 0xDF0799CA6F82DFCFULL, 0x15CE318FDB2DFDA2ULL, 0x3287556BE62603F2ULL, 
            0xEDD76D80000EF781ULL, 0x8C6EC43A84CA17CEULL, 0x747E3E40B2519E81ULL, 0x581546DA57E47FBEULL, 
            0xFA1747FA4A5E6355ULL, 0xF9EBF08EF47D2040ULL, 0xF2009B678562BEE9ULL, 0x5A156AF82738EBAFULL, 
            0x82A7158AA3AD38A0ULL, 0x78AFBABA2937549AULL, 0xD05F41DD2EB1618FULL, 0xBB6D45C58F37B500ULL
        },
        {
            0x6C45CD1B2138E2C9ULL, 0x37BD52F208E8CD6AULL, 0x8D6D039EEF3E2B24ULL, 0xE748D10303641EB1ULL, 
            0xB34676C4A03B08E1ULL, 0x2200D7F1A3BBAF14ULL, 0xB58BD4B04031C500ULL, 0x6C9673775D434E75ULL, 
            0xDCA254A1ADBB6779ULL, 0x1CD28F6892F6DA36ULL, 0x4E56C7FF638B0449ULL, 0x6FCBAB1407AEB0E3ULL, 
            0x3ACB90916857D48DULL, 0x9D42C17D77D1E493ULL, 0x9A8A50AC763F8762ULL, 0x347D14BBC50BA54CULL, 
            0x2C96838963A3A448ULL, 0xB8A64A8092B9BE28ULL, 0xA16742ACF89C4ED6ULL, 0x9881D496491DFBC4ULL, 
            0xCD9B0D127E1FE22FULL, 0x8E42D68DA5E55E5FULL, 0x6D8E268ED0F4A986ULL, 0xE7DC9B241CC00B98ULL, 
            0xA15684A566996DBBULL, 0x1DE0343CCC21575DULL, 0x18AF2196DCF3973DULL, 0x76B8423D4BD9306FULL, 
            0xDC7C56E563841438ULL, 0xDE203FD68F08913BULL, 0x3B8D57E3BCC385F1ULL, 0xDB4E1DBE6B173C25ULL
        },
        {
            0xE290C12926C9C9D7ULL, 0xE8B34C0753780315ULL, 0xC7D784B3DCE6377EULL, 0xEB95D0355ED5EDE2ULL, 
            0x5942AAA3ACF132AFULL, 0x72620EB069F559C7ULL, 0x7B19F5199BB26269ULL, 0xAC160F0605AB6B1DULL, 
            0xAA5A8B951476EA14ULL, 0x244D9F3C9493CB85ULL, 0xF910278B0BFA7F4EULL, 0x31DAA48469891B17ULL, 
            0x512FBBB03ADD7987ULL, 0x8168F598CCCF6BB1ULL, 0xFF975B1EE3071A39ULL, 0xD3935DC95CA9D2B4ULL, 
            0xAC41A5A0103F9617ULL, 0x5590FACB5A5AE87EULL, 0x8C31D4059CB4F703ULL, 0x29832C9313A3DB7EULL, 
            0xF8E44651E834C8CDULL, 0xE46EC19D853A9F84ULL, 0xF5AD56E1B10FD858ULL, 0x92895FDC8FACD1D7ULL, 
            0x5C6AFC55587B1622ULL, 0x8C1AF1D35E27F527ULL, 0xAEFE08FFBBD4B249ULL, 0x7DE05A0F924B33EDULL, 
            0xCA73F4D0945B3886ULL, 0x1CDF73F11F6D942DULL, 0x034EE07AE711F01CULL, 0x5871D8556ACFC2F3ULL
        },
        {
            0x77F777CC1EEBE0F9ULL, 0xE4F880A6D86A2A38ULL, 0x918E1AA8400127B5ULL, 0xA2E86A6CC8D717ABULL, 
            0x06A517B59EB93334ULL, 0x12CA87D55C3CCFF4ULL, 0x2AC3271934BD8F72ULL, 0x0B7A41350774CC86ULL, 
            0x426CD94CC883A624ULL, 0xA2967ABFEDD23630ULL, 0xE2BA0C4FE964518FULL, 0xEFCDFC8F070FB366ULL, 
            0x2A88B26599D9103CULL, 0x377D5C70C7E31153ULL, 0x4BDBA6802A4EBBD0ULL, 0x0110C5D27031C494ULL, 
            0x1D6688F3412B41EFULL, 0xBA848AD5EBA0CA2BULL, 0xB4E3FDD16C641939ULL, 0xD0513E68EC2A8C14ULL, 
            0xA4DAF70D33AB676FULL, 0xB5F762ACB6A99D03ULL, 0x5F2E06DB241B6B42ULL, 0x66D35DA376719FCDULL, 
            0x997B3FC51B695419ULL, 0xF2E02270CFDBCF9BULL, 0x1CBBA4E9BDB02A18ULL, 0x55C38FE6871C2A94ULL, 
            0x7398380B5BB9AE75ULL, 0xAAFEDFEFC8B6B015ULL, 0x2CDB41708F97C639ULL, 0x93308D7C404146C4ULL
        }
    },
    {
        {
            0xB7595B261D8DE4FDULL, 0x3FD186A70A1166E7ULL, 0xE7BFC7CA2BFB334FULL, 0x28FD98B73D703B08ULL, 
            0xA22C74065714EB7AULL, 0x3F7A7BFEBD099063ULL, 0x2B680DF32B40A9F0ULL, 0xC384E7DCACE14877ULL, 
            0x3F95403DC0AB907CULL, 0x9C223547FCC6E260ULL, 0xCC83DE01FE9C429EULL, 0xF0EA0E577BAC53BFULL, 
            0xF338301969EB6B01ULL, 0x278DB6C400688607ULL, 0x06380D4392817ABAULL, 0x6FFAE2A5B93A40ABULL, 
            0x6A09439287CF6FD9ULL, 0xE56EDE1BA3A70112ULL, 0xA88DB005103DC873ULL, 0x1188266FD2201E86ULL, 
            0x9556D0EE84BF2200ULL, 0x29F166B0D04255ADULL, 0x0CE6B7E9E037FEF9ULL, 0x635B983799036931ULL, 
            0xB70CE37C902FF4EBULL, 0x1584CB0DBB26D8CAULL, 0x01D936E38AF90BE6ULL, 0x4ED29738DED8CE63ULL, 
            0x82C5978D6060D044ULL, 0x41A470D241D2F423ULL, 0x0BD2A6480C894A20ULL, 0x6EEC65271DCE393EULL
        },
        {
            0xB4D947EF1A736755ULL, 0xDC4DC5F31C72A606ULL, 0xF1BFEFCC5D68CC65ULL, 0xBF6EE4F3B76078E5ULL, 
            0x02B3E94AAEEBC21EULL, 0x2DDAFB5EF0CF5287ULL, 0x0CDFECCCEB929250ULL, 0x1C32484E525E26D3ULL, 
            0xC9DA31EBFD99F5F4ULL, 0x05A0B11553A11111ULL, 0xDF6DF0C5037A51AAULL, 0x21901CBCDB2B4BA6ULL, 
            0x3F6B7F373753FC64ULL, 0xC72E03B64AB47FECULL, 0x77CEA2754B908E96ULL, 0xBC7981E1BD897322ULL, 
            0x46613F4715074924ULL, 0x154A6EBA928D599AULL, 0x086F67DE0F12F4DFULL, 0x5AF75718C48CCCABULL, 
            0x6883FAFB8E807880ULL, 0x54049D0A3D4A2361ULL, 0x5DE493E3A97979CCULL, 0x79898A7E913B75E9ULL, 
            0x8D536F9DEC923D29ULL, 0x019C320AD8B718D0ULL, 0xA8E8AC9D9A9ECB6EULL, 0x251EFCB121BEA836ULL, 
            0xBBE6490BA5668917ULL, 0x4485A42AECBC4C38ULL, 0xBDAB774592A4D33DULL, 0xE4D405780F2FEFE9ULL
        },
        {
            0xD9ABEC225D1EC3C1ULL, 0x85F0FE6473781C9DULL, 0x0DB0A8D7D6EA4D11ULL, 0x5FD42611A26B337BULL, 
            0x6404A9435ECEFE79ULL, 0xE3B0B5CBA02A2F92ULL, 0x565116171AE3FBF9ULL, 0x31979E9B1E38A3C4ULL, 
            0xD59A8C5AC69D45A2ULL, 0x747D6FE5C7FC612BULL, 0x05945DFEFD433755ULL, 0xE89F44182E4F7C74ULL, 
            0x606600B3C699AE39ULL, 0xD0163A8A24E3C7CFULL, 0xD5EEA13AD81FCF56ULL, 0x184A00846F02F66EULL, 
            0x16AD99E5EBF6DE1CULL, 0xF419173F7B44E6D3ULL, 0x4CF39AA1524BC025ULL, 0x25C3E61472DAE22FULL, 
            0x0AADA00E0043528EULL, 0x64E77A5E6FEDDCA6ULL, 0xD74FFE5E80E081B6ULL, 0xA4B18FC5432E430DULL, 
            0xB7EFCFD1C8C43A32ULL, 0x2AFAC60C7B7355B4ULL, 0x0B6942ADAB7B0F06ULL, 0x9552DCCBFAB29A70ULL, 
            0xE8572C15BB4A1C3BULL, 0xD3561F592392C3A0ULL, 0xAB207CD94EF3550EULL, 0x243E7EA36A9C170CULL
        },
        {
            0x0DDEEF9DEEAEE2B8ULL, 0x76FE05AFCA58B1ADULL, 0xF2B5A8A0DA4D6F79ULL, 0xB58C69FD8CEE6E4CULL, 
            0x43D5443724294260ULL, 0xF94CFF0DC4CD9BE5ULL, 0x474045BCC00C7C62ULL, 0x3DBD7D8C9EF4B031ULL, 
            0xA40CC7895B09E1C2ULL, 0x992194857475B29CULL, 0x11734FA44E67E444ULL, 0x1C2976214034F8A6ULL, 
            0x2D1B187B63A88C8EULL, 0xA95E98F888E71BC5ULL, 0x73FCF02FD8EEBE2AULL, 0xCAC206EE7DBBF795ULL, 
            0x1002DB21F03B1683ULL, 0xE4ADEE9ECCB00F15ULL, 0x32E244B45E0B99E6ULL, 0x418DDD8079CDC3C2ULL, 
            0x3D0A0A00642E222AULL, 0x1A3DF9B3D90E08A1ULL, 0x973489B8435CFC23ULL, 0x85A08E2F1F358244ULL, 
            0x47594A450D9AB98FULL, 0xE70630B519224946ULL, 0x7FF44BB9E12EFE78ULL, 0x2B3CD7B440EA9CCFULL, 
            0x812F9881DFBAD32DULL, 0xEC7BDF9DA5E34240ULL, 0xB57F56FE9754B59EULL, 0x38B328AEDC5EDC9EULL
        },
        {
            0x8A2C6551AB89B533ULL, 0x0895BB03E9A3FED1ULL, 0xF45B76EBEE409648ULL, 0x63B674C2B149316BULL, 
            0x43DF676BB87557ABULL, 0xF16E9DBF32038D14ULL, 0x8F3D03D7486CEAA4ULL, 0xC4E30C479EC3623BULL, 
            0xCC24AE0431695DDAULL, 0x9B4F787A4D2C1D6FULL, 0xCE163C39E1AC8EADULL, 0x95B3C65B4A839CFBULL, 
            0x6535162DE97FAA55ULL, 0x8DDFD71C55D9123AULL, 0x4A80F04ED6F16924ULL, 0x94CE840000D9DC0FULL, 
            0x0FFEF00C24EA7495ULL, 0x6BE4CB20B8020116ULL, 0x7106A185D191E5DAULL, 0xB0777F6A5081544EULL, 
            0x0117417F3ED45A2AULL, 0x51FC57215F664324ULL, 0x16ECDF1AA19D6DADULL, 0x0A56ED5ED3E2BBAAULL, 
            0x553E0535EEDFE998ULL, 0xAA3B744CDDAEDD75ULL, 0xB38B8C8292A9FF85ULL, 0x275D63FABC7019A4ULL, 
            0x00EED31C4C24D0BDULL, 0x664E4EE4E83F35B2ULL, 0xF74915FC7C34FC45ULL, 0x510CDA027031C158ULL
        },
        {
            0xED0BB17C1E886425ULL, 0x158EC84A43ECC1D0ULL, 0xEB9E56165E6E2EF6ULL, 0xFE8818C12DFCE930ULL, 
            0xABFC983BF9EC38C7ULL, 0x260E52B2A4D8EA59ULL, 0xBC4BC8299D97F983ULL, 0x82E975D0AF74B8B0ULL, 
            0xB6EDC1EA96134B0BULL, 0x0B05A01EAE76946DULL, 0x6F6A7E60F196E225ULL, 0xF1EFD6C029B264C7ULL, 
            0xDDF4DC2B3A37993BULL, 0x3A2243A7DB973096ULL, 0xB1EFD0BF1210E1B2ULL, 0xCF5AEF0E57F3B5BBULL, 
            0x34EA1DE751FCE3BAULL, 0xE71A09BEEEB706A5ULL, 0xE57318E509C5A4EDULL, 0xFF323B104564F959ULL, 
            0x01079868B56F4DCAULL, 0x1D3F2D241D89A8BFULL, 0xE936781088622817ULL, 0x6EF33887FFF410A9ULL, 
            0x76CD3379DB5C5F1FULL, 0x3DCBB1F0C28005BDULL, 0x2AF4CC2E3147620FULL, 0x90CA3750D820EBA9ULL, 
            0x7548EE90000F3212ULL, 0xBE4C7A90B93B5022ULL, 0x367619543E3F8093ULL, 0x2DE8A95F7DF359B8ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Canopus::kPhaseFConstants = {
    0xE7161964E601FC69ULL,
    0xAF3939DB7F954B79ULL,
    0x1920757E60255D5AULL,
    0xE7161964E601FC69ULL,
    0xAF3939DB7F954B79ULL,
    0x1920757E60255D5AULL,
    0x06084A31EB664F0BULL,
    0x307BFBD89302E89AULL,
    0xC6,
    0x9E,
    0xC2,
    0x3E,
    0x41,
    0x96,
    0x48,
    0x40
};

const TwistDomainSaltSet TwistExpander_Canopus::kPhaseGSalts = {
    {
        {
            0xA32A73ACDAAA59B1ULL, 0x5B99FA0FFFA6789FULL, 0x19BA3EEF9DA03A5CULL, 0xF8934378960F9D86ULL, 
            0x9966333924BFC812ULL, 0xB71BFB86394F1ADAULL, 0x360790B7015CC5D3ULL, 0x830F3DDACCF7F096ULL, 
            0x750A75A9CAE9B80AULL, 0x0AC2239B98FDBD2BULL, 0x0F6DDF4D836CE504ULL, 0xDD9C612BE984F870ULL, 
            0x171CD9EC1BAAF459ULL, 0x2827B6B8E18F547FULL, 0xEE3D595A22B4CFD4ULL, 0x01EE0CDC5D4DB60CULL, 
            0xD50D3746DEB607B2ULL, 0xCDB3CA572BC2B667ULL, 0x61867645DAA978B6ULL, 0x515D1ED7487AFF84ULL, 
            0x9C070E4AF6D81236ULL, 0xC37865E3F5E1102DULL, 0x8FC3BECF9636135CULL, 0x01DAAA90EC44BC07ULL, 
            0x41EE3BB372A34863ULL, 0x715208ECAE6FB3EBULL, 0x102602C88F14F658ULL, 0xC65C60FE99BC6BCBULL, 
            0x55FC4F59F1D840B8ULL, 0xB28D38863C42283DULL, 0xA3BAA08B6357B366ULL, 0x13FA858F4CB4C576ULL
        },
        {
            0x73DC7B2D36685A52ULL, 0x0B92DBE7C1E31D92ULL, 0xCF60316D349D2F77ULL, 0xFBCAA2292CF7B13EULL, 
            0xBB197D461C2F050CULL, 0xEF30C393D762283FULL, 0x5C5DF4C2EB5ADCA7ULL, 0xDB21DEE3519809DDULL, 
            0x32CFA6585848D931ULL, 0x44FD44D53CF25482ULL, 0xECC9FC8D33B935E7ULL, 0xE2E88F5978998E52ULL, 
            0x4061F049D7F37BD7ULL, 0x790D74D7E9DAFA04ULL, 0x995DFBC6E2734507ULL, 0x1E472346F7D053F0ULL, 
            0x4C1D97E9886EA66EULL, 0x3210FCEEB842E4D0ULL, 0xB9157CE4A433F0F0ULL, 0x55DF46F7658EDA0BULL, 
            0x9DEA60E816587B86ULL, 0xD0004B73C593C2F0ULL, 0x8E590332865537FBULL, 0x5171D2D3C0222924ULL, 
            0xE53DBE94AD6F19DFULL, 0x5D1EB2FA7AED30BCULL, 0xB85F23EBF1697D9BULL, 0x037692CF0E67D08AULL, 
            0xE282743CCF186EDEULL, 0xBB02FEE0CC7A4400ULL, 0xAA601763296321A7ULL, 0x6D0A087D2FD7BD99ULL
        },
        {
            0x90840A352ED0B915ULL, 0x32203BDB44220866ULL, 0x44D67AAF38CF45F3ULL, 0xD38591F855EF321DULL, 
            0x61F4D2893BB22B22ULL, 0x5D43F5EC726DC42BULL, 0x63D22B3BF578BD4DULL, 0x31488FB7EA31FBF6ULL, 
            0x80DF33534B4B5758ULL, 0xAA87464E7BCFE7EAULL, 0x13A4A09229D21568ULL, 0x74EF55E6DBF87569ULL, 
            0x51A99E851CC2D555ULL, 0xB6D52C8B120D344FULL, 0x93BC6D6B973293A6ULL, 0x3FEF1CEDD96B2C31ULL, 
            0xE0F69329AC220790ULL, 0x71D244CF14D7C7C6ULL, 0x358133ABD8FA9B7CULL, 0x46ACE66BB967B838ULL, 
            0x0AAF80038EDEFA11ULL, 0x9C6A85B98954E792ULL, 0xEF870D22C1654409ULL, 0x115350C098128EE6ULL, 
            0x76E943B0D27742C5ULL, 0x579927DF6813ED00ULL, 0x50C1C069C93D7013ULL, 0xB0A7D888718A2C5AULL, 
            0xAACCB6E702DB1B39ULL, 0x89669B037CA2D315ULL, 0x68DCE03E647A3B39ULL, 0x8A9CE3E2A0AA4042ULL
        },
        {
            0x050694A207F98632ULL, 0x4F45B81459A9C960ULL, 0x3FF477C20409CEF5ULL, 0xDF69F44E9D7B61C0ULL, 
            0x1BE26013DAF70C89ULL, 0x2728C11334B64A56ULL, 0x47D412F52FD18F84ULL, 0xE4C313694173F062ULL, 
            0x2EDC8C50E4161A63ULL, 0x2FF49D792E3A9BCCULL, 0x39C1B0CED746CD10ULL, 0x84BAF4B3ACB6AC36ULL, 
            0xD6D2574F8F0BB095ULL, 0x9DF55FD143C1D3F2ULL, 0x599FA464F07C5E63ULL, 0xEEFC136C1A7E85CCULL, 
            0x2C8CE5D00A61DC84ULL, 0xC39AD48D620A12BEULL, 0x55EF914E6F66DC59ULL, 0xC529B25B41063635ULL, 
            0x41E172238CB8A174ULL, 0xD7D8CA9DE394C6B1ULL, 0xE75A82D0EA6D6357ULL, 0xF5E8B121AA6A46B0ULL, 
            0x400BF3DA99C0CFE7ULL, 0xA0AE3649931D9105ULL, 0x36D9F3DD27E2C2CEULL, 0x5004A8FC81987886ULL, 
            0xB76D35D32A7ADA76ULL, 0xADE12DBA67CD801EULL, 0x77A799C60A0DD9B9ULL, 0x9C14365A2E877199ULL
        },
        {
            0x2C14E9729A8C5507ULL, 0xFA472456E670D857ULL, 0x38D8B0AAECC37C2CULL, 0x52F21C2A2D7D880FULL, 
            0x85BCB20972B3C92EULL, 0x7763EBF48E3BF83EULL, 0x6F1E9A99EAB6B5F8ULL, 0x2ED97A4380C83481ULL, 
            0xB68E2FD5DC827990ULL, 0x2138F10D9DC2BB51ULL, 0x1C57EED49BE14228ULL, 0xDE42ABAD408BE67DULL, 
            0x76D6905B3703340CULL, 0x2165AD41006FCDAAULL, 0x8690E76CF3005242ULL, 0xBE8965037708EE35ULL, 
            0x2560CE35E5F428EEULL, 0x4D75A3C96CC023E7ULL, 0xFCA45E3CAA0DF9D4ULL, 0x426BB349F6B465BBULL, 
            0x79119B1A73117F4EULL, 0x7F641BBAA36DD9D2ULL, 0x674A0D8541E2A38CULL, 0xE8CB2BB51D3E5FCBULL, 
            0x67B7487F07E66699ULL, 0xB558D967EC90EEAFULL, 0x86C92D826A599DFEULL, 0x9B8698600B21F06CULL, 
            0xB6825447928C6A2EULL, 0x37A9CC11E36BB24EULL, 0x6C10DCAF14501A74ULL, 0x41481413220693B0ULL
        },
        {
            0x899147E480AC700AULL, 0x32FC572C4A452AFCULL, 0x0A81F069A47FDD4FULL, 0x521F795F7A3938A5ULL, 
            0x83D0F3732652BBCDULL, 0x64193CB8B6013491ULL, 0x12D3A897D41D25B9ULL, 0xF61F82B53DC2B7CBULL, 
            0xE9BDEE786831CAA1ULL, 0xAE6B82DA19084B48ULL, 0x9841A13A5AC727BFULL, 0x5E7A235B6E5FD316ULL, 
            0x8D7D9C6055A79097ULL, 0x8C99D78FEB8C4371ULL, 0xFB2A67E6FDF06298ULL, 0x90F213C41CD46186ULL, 
            0x047CB5046777FD40ULL, 0x863163AA5A19E851ULL, 0x3AE769C065E3B821ULL, 0x44946DE9BE66B175ULL, 
            0xCDF9B9051AB6C56CULL, 0x062AB488E4205AE0ULL, 0xE51C30DA7091B396ULL, 0x1C2392C8AD711FA6ULL, 
            0x0EA558B2906601A5ULL, 0x13C2565D83A074A9ULL, 0xB0F74686E77320B7ULL, 0xC3099AEBDF28372FULL, 
            0xFA7F3B5373ABA19BULL, 0xF313DEBB953910B9ULL, 0xED0DDED1C7F6DC28ULL, 0xEF6CF031F58FFC75ULL
        }
    },
    {
        {
            0x7D99ED8CE7F642DBULL, 0x926D2D056770600DULL, 0xB940DF0AFA0CDEE8ULL, 0x24F9620B76B4B29CULL, 
            0x843EA791C9155DA7ULL, 0x0A688A124602A41BULL, 0x3D541081A96E5AB6ULL, 0x52FF06DB05EB6912ULL, 
            0xD435BB420FA02B0EULL, 0x7E082DECF36258D2ULL, 0xDCAE2910AA1FDCBAULL, 0xE78D918C161DE7EAULL, 
            0x0C5A35CFE48177E5ULL, 0xCE90B37859FEDCFDULL, 0x83FD9505E2449BDFULL, 0x64AB9A474FD127CEULL, 
            0x1CD4B5BA97545CDEULL, 0xEC821EB80DAFAD5FULL, 0xDD35E650908120ADULL, 0x505DF6ACD1C18931ULL, 
            0x0D561D035EE8E1D5ULL, 0x4D65699B92D11805ULL, 0x17003CE865E0D948ULL, 0x2DCDB65DC910BAFEULL, 
            0xC9F8DAEF9FC9AA0EULL, 0xAAFB1A62492DEF96ULL, 0x96A189A205C6EC19ULL, 0xADAB2902648137B1ULL, 
            0x738E32F6CAA1F442ULL, 0xAD49BE3B9511435FULL, 0xFE79EE87CBF49EBDULL, 0x61E79226E870379AULL
        },
        {
            0x4398C56DF3E0A7DEULL, 0x4D9FE76B0078AF5EULL, 0xC844C0F3E6118813ULL, 0xAEC0E192CA35043CULL, 
            0xB78502DDFECF2011ULL, 0x08DB662BC796FDC0ULL, 0x474E3F2BBFFDBDC7ULL, 0x562D834F0A4A779DULL, 
            0xF106CD8CAC67CA76ULL, 0xCF58B9046E43690EULL, 0x7B9F87BA987B4DE5ULL, 0x8AE2C206A477CB92ULL, 
            0x82B42331308AA6FBULL, 0x87CD7095CE0C5494ULL, 0x41A99816F2336F7AULL, 0xD6FFB295CE241284ULL, 
            0x2D7B7F3D129C2456ULL, 0x7F7810BB2DA179ECULL, 0x6C9B1760246942A5ULL, 0x05B6448A26DC25D4ULL, 
            0x6672654D3A1ECFC3ULL, 0x988A58072355FEF8ULL, 0x74D77668EB7CEBD4ULL, 0x0C7DE20DD2A8FF22ULL, 
            0x3AD08197F81DAF48ULL, 0x407AB587ED9DEEBAULL, 0x8C46CC2350DD4A5CULL, 0x6402E77C2BBA14F9ULL, 
            0xA27EA4B9C702D2C3ULL, 0x2DF783753CDAC778ULL, 0x57029DED3A919A69ULL, 0x753396BD255EA596ULL
        },
        {
            0xC0DE358AAAB87362ULL, 0xE25AD67E4A307EF7ULL, 0xB726B4A3E28FB327ULL, 0x8E8135F44D9CC9EBULL, 
            0x7838C198CE0D5C97ULL, 0xD385EFE02441D53CULL, 0x3A8FBF5F9AF57451ULL, 0x125066CDEFEA1DA0ULL, 
            0x44F98F22FEAF188AULL, 0xDBAEC887DAD23F62ULL, 0x485DAC14E654B9A3ULL, 0x1787B53239B9230CULL, 
            0x786E266F0D40B81DULL, 0x9558845416E3D064ULL, 0x8F4069813255DD6DULL, 0xD03D28C4F1DFE377ULL, 
            0x81C51B85B852C460ULL, 0xAEF08EC0575FA93CULL, 0x95D48548C7648EC6ULL, 0x920D420E03D1BC1FULL, 
            0x15D2BD33063252E5ULL, 0x8D485D149232A916ULL, 0x5F1C2E903B2C81B2ULL, 0x6248604E7C7225F9ULL, 
            0x1823CBFA51BDB956ULL, 0xC40FEC7EC2030DF4ULL, 0xC9BEE5BCBF51B3A4ULL, 0x62509382E97B9C63ULL, 
            0x7E78D1F0C5BC6BDBULL, 0x08879CD84836604BULL, 0xB85770124F0AFA95ULL, 0xAA553758DF5F6DF8ULL
        },
        {
            0x2922BAAC3F44B35DULL, 0xCC3D6A09DAFC1D75ULL, 0xE5851B50339CD287ULL, 0x5FB60B3ADE915A12ULL, 
            0x0607BC87B80982D7ULL, 0x67AD93BD6168B002ULL, 0xB18EDCF2D94FBE00ULL, 0x4DD78D536510C92AULL, 
            0xDF7271F0E0D83E5EULL, 0xA662B83AB3FBB441ULL, 0xE92EC160172E372DULL, 0xBEB2BC5672B729A3ULL, 
            0x6ECCA2116C22C4A1ULL, 0x9E229CDDEF429C3CULL, 0x6A274136514D8065ULL, 0x7B9CE80365D723A1ULL, 
            0xFA0AAB3F2775AF81ULL, 0x692063164E311601ULL, 0x99319D7DE8217232ULL, 0x819ACE2628CB783FULL, 
            0x9D73FE554306AFCDULL, 0x8AC21C5E2767033CULL, 0x374EEC4B2775D107ULL, 0xCCA281BFAD9FB4EFULL, 
            0x19EF22B7E75CA589ULL, 0xA4D3BEF5F6C55552ULL, 0x30343B45E1CC6896ULL, 0xA78B7E48B4127386ULL, 
            0x35E8A3A32F65E0CBULL, 0xE2C685C0567AB4AEULL, 0x2A15705E3322CC19ULL, 0x61EA8850ECD7EC54ULL
        },
        {
            0x49D015AC2EDF9288ULL, 0xBA24A7FF774DEB28ULL, 0x0BEDC855AF2DD82FULL, 0xD95FC85043F7529DULL, 
            0x78D88CCAA49188B2ULL, 0xF9EA7DDC933856D7ULL, 0xDF05E4E6AE164FF9ULL, 0x355DAA9DEF1FAB96ULL, 
            0x7E27A666007FEEB0ULL, 0x7B0BCAD6B4A4A1A1ULL, 0x4BC26E853F167739ULL, 0xCFDA811FA5E6AF91ULL, 
            0x2CE07468E5BA287BULL, 0xB15C1F03D69AE48EULL, 0x74EA02344EE29DD9ULL, 0x04BF83F0A98A4A58ULL, 
            0x829F4EB8EB386E02ULL, 0x197104E8F5F80BBEULL, 0x765AA6E8E4D44BFCULL, 0x67380DD8EEBD78D5ULL, 
            0x74D0CC97AAA837C7ULL, 0xB77AE94D37A593FAULL, 0x38292012A47B83F4ULL, 0x8D6B66C3B70AE1BCULL, 
            0xCDAA3B9FCEB57D52ULL, 0x590E355DF94CFD6AULL, 0x2532A2EBED5F6328ULL, 0xDF8C22991C8F21AEULL, 
            0x3991D090EB2CEFDCULL, 0x1AB1C05CED868AC5ULL, 0x016306EC7009FFCEULL, 0x475F628415DCB05EULL
        },
        {
            0xE2F1F70D795983E6ULL, 0x07F45B0BA930AB40ULL, 0xA64ADA46F67F849DULL, 0xE7D41AA407C5A3B0ULL, 
            0xBF7DCB172D94C139ULL, 0xD87222A0E10C6F47ULL, 0x78BD6F9C9CFF7CC7ULL, 0xD577806DACA4E964ULL, 
            0x211C978700CF1DCCULL, 0x52EB874E65437538ULL, 0x356D78ABBF88556BULL, 0x55A0230FE2A995F9ULL, 
            0xBF89FD00C30916E1ULL, 0xCD64AA4057C7755EULL, 0xC6B705AF405D4E43ULL, 0xF10C76813959052FULL, 
            0x42623BBFA594E171ULL, 0xE27F9B4A46688052ULL, 0xDA59F855F60D1EA6ULL, 0x153C7DAFD3718475ULL, 
            0x0867A9920A74A1D2ULL, 0x7F148B8D43323BF2ULL, 0xA9011AAA125D2B17ULL, 0x75FD28C06CC860DEULL, 
            0x320EABE0D8D0B54BULL, 0x19A4E22C8885FDD4ULL, 0x46EE562F9D82D4A8ULL, 0x428549C148D00A3AULL, 
            0xCCF9D5398CA5E730ULL, 0x8BC3FAA12899C29FULL, 0x848385DCEAB83979ULL, 0xBC848DD188DC02F2ULL
        }
    },
    {
        {
            0x8230E4C9EE29E216ULL, 0x970E47B6147BF1C4ULL, 0xCE47FB4891BA0858ULL, 0xA1CC1641D2A531E1ULL, 
            0xCC166BDCA2B0236EULL, 0xBAAEB814CF3A9AD8ULL, 0xEE023AA5210245ABULL, 0x776C67601CF5C24DULL, 
            0xA9F2AFB0109AE033ULL, 0x1616BA726112E17EULL, 0xA762F76B660E0ACBULL, 0x3E73D2E9107A41B9ULL, 
            0xA70AE6C45389F753ULL, 0x9D3FB46F10F42688ULL, 0x38AE5A6B25AA72BCULL, 0xFE30E1CA84D55C02ULL, 
            0x7DD3BB599DD49AD6ULL, 0x307C7F69B5D76035ULL, 0x7404D20C79504C68ULL, 0x2A205C9538ED1D1CULL, 
            0x629CF804B09FEBE9ULL, 0xCA1C55FD75294705ULL, 0xB8625FAB2C203060ULL, 0xD0AE31836D71DDB0ULL, 
            0xF7403B6EBD446909ULL, 0x4684CA939BC6338AULL, 0xAA4943A2D00F1EBEULL, 0x7B4AC9D856D13FFBULL, 
            0xCD7492A75DB1A4BDULL, 0x67E664423200B022ULL, 0x568762F3BC2BF0B4ULL, 0xA09EA15EB8BB1031ULL
        },
        {
            0x39718697F14C82CAULL, 0x63AEBDE9B15F0491ULL, 0x66999028B767661BULL, 0xF7E9C25CAF42A0E4ULL, 
            0x580933006809C5DAULL, 0xA36B96F75ED72FD6ULL, 0xA1D3E9E6DB9173AEULL, 0x271C570D65A550D0ULL, 
            0xF035964F562D747DULL, 0x9A8E9612C2990528ULL, 0xD8320541B8289679ULL, 0xE5CB4FDB50C8CDE3ULL, 
            0x55453E0B94331F36ULL, 0xC79A6D359547BE7FULL, 0x7A7F9F83E4C1EFE2ULL, 0xAA8A003C8A4829CAULL, 
            0x13D5B9F2AFE30901ULL, 0xFBFFF7E24B45A2A5ULL, 0x8D61BFA9102FFA40ULL, 0x3CDE99EC1FF575A3ULL, 
            0x2AD92BE31CFC828DULL, 0x0431C02A970E4555ULL, 0x485094118CA23DECULL, 0xC6518B87CA22B1D2ULL, 
            0x2A91912B24B4889DULL, 0xD28C3873656645EFULL, 0xE45900034A60AFE4ULL, 0x56BBBD102A9172B8ULL, 
            0x2C3BDA5BCBAC861EULL, 0x802425382DEF72A7ULL, 0xCE97A884E86EB3C3ULL, 0x45278891BCDBFF84ULL
        },
        {
            0x822613CBF1331F75ULL, 0x23842B97F9E5A1B4ULL, 0x3B73D859FBFFA538ULL, 0xA46F75F3C99D0E18ULL, 
            0x67163CCF1F6D3FA2ULL, 0xD7C70A7CB2BFC541ULL, 0x18FE65D7CFE46D3FULL, 0x51C7C459D0269512ULL, 
            0x5A9362712044440EULL, 0xEB9DBB1273B1BE24ULL, 0x9BA3D19446B6CBAAULL, 0xD080E2DB2088B180ULL, 
            0x6E3308A82B7FB8A2ULL, 0x9BDEA648C087A5D4ULL, 0x447EAB34FA882150ULL, 0x7D1F23D360D532FCULL, 
            0x849C40C0B3D13CADULL, 0xF6691F167861D1BFULL, 0x3FC233BD0BD5286EULL, 0xB2F8CFC356A71BAFULL, 
            0xD0B36C92F0925ED5ULL, 0xD1D946B0E88DBA71ULL, 0x92AE4C270CDB978CULL, 0x80BCDE23577A26B8ULL, 
            0x6B5A9634024AAFC6ULL, 0x0ED22AC1968C818DULL, 0x94CB108A6DC43129ULL, 0x26D47F1D7F736CC5ULL, 
            0x6F6111BB6A956FF5ULL, 0x396ACD94272BF9C1ULL, 0xEE09080AAB85E1ECULL, 0xED91B1F19E8D3AF2ULL
        },
        {
            0x4ED87BEDA36E29EDULL, 0xC552421650008D55ULL, 0x96260EFC85C43F87ULL, 0x7463466A6DCC968CULL, 
            0xF2ECEC0A25FB052AULL, 0xFB1A6B81561FB97BULL, 0x75B382E7FA00BCBFULL, 0x2C7D5BAB797A4318ULL, 
            0xCEB23F6FEFC5EB83ULL, 0x4EECA622D54E788AULL, 0xB210B692C7BF1A78ULL, 0x16294F5FD4E0C7C3ULL, 
            0x980E2A462E5F9714ULL, 0x7ABEE7604775CA1FULL, 0x639E7DF6EF06DD99ULL, 0x61A572F72DECA1A8ULL, 
            0x904BEF2AC428A7AAULL, 0xFADE6144F15B8F9EULL, 0xA4948C3DBD030A07ULL, 0x9BDA7CB90979D4C3ULL, 
            0x9A8870B6EDE39201ULL, 0x48ABEF12AE7A8730ULL, 0x52FBDB0B76BDEF22ULL, 0xA5F11CAE721574E3ULL, 
            0x53145F0053F36C0FULL, 0x637313A2575FD823ULL, 0xA619D80FAD68AF2CULL, 0xA05BCA39C04B26D9ULL, 
            0x4200B804E5E12EE5ULL, 0xE941F450DFA791DFULL, 0xD8FF56B0BCB2B469ULL, 0xE2958E51EDA24DE2ULL
        },
        {
            0x1545A26C222B23BFULL, 0x133294C1569C5140ULL, 0x476517C0BF4AD87FULL, 0x7CBE66D952D83379ULL, 
            0x537D7D1B208B861EULL, 0x72FA632A820483C3ULL, 0xE2DA58EB895D06DDULL, 0x01D49C7EA51DC946ULL, 
            0x53AD927A2C8D7BF4ULL, 0xD63FA60FCF06709DULL, 0x98902CBCB39E91BAULL, 0x7FF681B01D25DB85ULL, 
            0x36928E7AE8EED582ULL, 0x230D3B96A5266E14ULL, 0x31CCF8579ED6733AULL, 0xF365B8464B07CA5CULL, 
            0x367C1CE5C16386D2ULL, 0xB1E716A177D6199AULL, 0x1C2EE46705EF8321ULL, 0x5E27103B9E36E61EULL, 
            0xE076591B55033F87ULL, 0x0B30387D9E3F15C4ULL, 0x49159BDECCCE7A28ULL, 0xD0FB395D3C5F66D5ULL, 
            0xF54E3473F8A7D99FULL, 0xF31FB6733F850A54ULL, 0x08C109BFE940E07CULL, 0xEA7DB68EDA5605A1ULL, 
            0x1CD96FAF0A06D95DULL, 0xAEDAA78ED9828B30ULL, 0x2F2A5083A919A732ULL, 0x9896010E3031F1FBULL
        },
        {
            0x58140D4B3D2703ADULL, 0xCC0A979AE3CBBB3CULL, 0x8F307B16D61D3BBFULL, 0x839BCED29253FA29ULL, 
            0x8A875BD5F5A1CD64ULL, 0xB606DBCA432F6276ULL, 0xD0C61ED792D7A05FULL, 0xE44947B10000BD23ULL, 
            0x3BAF7D3A73E8EA99ULL, 0x7405BF9A2CEBF614ULL, 0x918E30CCC232729CULL, 0xB7BB0D01978635E2ULL, 
            0xC83A8C9849EC5495ULL, 0x187845F959678BAAULL, 0xADB806DF02621B5DULL, 0x179C330AD68E18F4ULL, 
            0x196EEE67E09802F2ULL, 0x2523EB9DF3DECB08ULL, 0x8EBA80533C1D519DULL, 0xD794A0C1909C8456ULL, 
            0x127F34FE1CB82246ULL, 0xDE8BF60FFD6B9D02ULL, 0x3768FC6313B9AA7BULL, 0xA15F8CBB7AC3EEECULL, 
            0xB55F2DCAE6935597ULL, 0x1CF1649C96C746A9ULL, 0xA410A4961C842595ULL, 0x29F0C0A0DDBB2A0EULL, 
            0x1D372D506BC5834FULL, 0xE6CC509490CFE901ULL, 0xAD76FD57710363CAULL, 0xD08F330D513CB4B1ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Canopus::kPhaseGConstants = {
    0x4B1535F2D93036C0ULL,
    0xC5D5F3B2D0BC44C6ULL,
    0xD5A728156503623FULL,
    0x4B1535F2D93036C0ULL,
    0xC5D5F3B2D0BC44C6ULL,
    0xD5A728156503623FULL,
    0x58CF15790C88D990ULL,
    0xDEE79C5BDB5019BAULL,
    0x60,
    0x6A,
    0x70,
    0xBF,
    0x7C,
    0x9C,
    0x8F,
    0x70
};

const TwistDomainSaltSet TwistExpander_Canopus::kPhaseHSalts = {
    {
        {
            0x55C46DE47868E0ECULL, 0x1AA350F21C57D7AFULL, 0x08DD58DD98217B25ULL, 0x36D6AFE8A9540DCCULL, 
            0xB833BB010AE479A5ULL, 0xF41B5FA9B8AE308DULL, 0xED61E5819047303AULL, 0x3CFD90B045C7A38DULL, 
            0x93E66108151CCB27ULL, 0x3649A31D83D82109ULL, 0x4798FF693ED0F389ULL, 0x7649C4057BE97282ULL, 
            0xB622758547416A23ULL, 0x1253C12D2FE9DB5FULL, 0x277F35626EDD642CULL, 0x84CA4F6920D65E38ULL, 
            0x902F0942F5A78D55ULL, 0x652129B70A38CA36ULL, 0xA86CABCB02199B29ULL, 0x941758C6E8042D5AULL, 
            0x9EE3DD83AB5CFD53ULL, 0xF4B198C86DDBBB2EULL, 0xE86A0FAEBE42F13FULL, 0x49F9BC84F1F6C0EDULL, 
            0x44A174C25A2A95EBULL, 0x85B62A7147118F56ULL, 0x1BB2F0B6FBF68537ULL, 0x8885A80AE721BABDULL, 
            0x99FEEFF6F47F1E71ULL, 0x52E6B9CAB5698EB2ULL, 0x58A3F00FA393A92CULL, 0x7BC819187C749A67ULL
        },
        {
            0x4E2C55ABE786124FULL, 0xCA6F441FD40856A3ULL, 0xCAAC1591D7D4D49AULL, 0x323BCF11CFE75586ULL, 
            0xDB9F701754F951E2ULL, 0x0A29E29929D35E3BULL, 0xF1FDE1F70F9360E7ULL, 0xF9D11C630FEAE149ULL, 
            0x46E2AFB4796C1178ULL, 0x2E0EE499076DA5B7ULL, 0x9A6675835ABFC474ULL, 0xA9C5944197894960ULL, 
            0x60EBBDEAA65AEC22ULL, 0x453D6C1D3D46776BULL, 0xC0F75A49DE6CD100ULL, 0x828806CBF09D6BA8ULL, 
            0x29C8A80B047DFD2CULL, 0xA69CDBFB3377935DULL, 0xB224A754C42B5821ULL, 0x36116A4368CEFDF4ULL, 
            0x9A12B15AABD3FFF8ULL, 0xD00C0D7D7AFF2393ULL, 0x0757FA062D987856ULL, 0xDFC454994A67CB9FULL, 
            0xD9660E4A02FFE06AULL, 0x72A5D457E55B6397ULL, 0xFB617A097DAB2F8BULL, 0x23AA0C887C05A5EFULL, 
            0xE7335EA54CAC65D3ULL, 0x39350B4A29A7AC0AULL, 0x2157E288553D3087ULL, 0x6173C1220A255BFCULL
        },
        {
            0xE64F7ED48BD4D827ULL, 0x4B6823187A30F064ULL, 0x1F9889890A58FA87ULL, 0xA277F166C608EB0DULL, 
            0xC3EF72ABF849FD7AULL, 0x74C86A206EB0765BULL, 0x75083DB1EB34E4FAULL, 0xB98269F5FCBF4532ULL, 
            0xDB03434CAD3BABF9ULL, 0xFBEB0F07E6331223ULL, 0xD725BCD165D067BAULL, 0xD644A51162F8624FULL, 
            0xDD68FFC514FBAB81ULL, 0x02D677E579CCE7AAULL, 0x3F93A67A77E4984AULL, 0x3D1B4C3A3C731DE2ULL, 
            0x0AFF705C88FC46BFULL, 0xEE271EB972ACB0E0ULL, 0xCA154581A3E62F27ULL, 0xBD81EB1F5B47ACD9ULL, 
            0x252C3C03A8DEC9B9ULL, 0xFCC72BCD15E82208ULL, 0xBD81F7A7B1740A37ULL, 0x76C0721FD5696172ULL, 
            0x9F12CAA5BD43C2A9ULL, 0xBC4A71C20626468AULL, 0x027AF479CBFFF198ULL, 0x97510FC106BB44D3ULL, 
            0xD452B612BCB5FE97ULL, 0xE978D9FEE439B24AULL, 0x8D0241C6C1F62AE4ULL, 0x153B99F29B27A3E1ULL
        },
        {
            0xBE1C9EDC3886497FULL, 0x1EA25A2D956A2390ULL, 0x14A348C94F98139DULL, 0xAB270D4C5D75FA24ULL, 
            0x593531E8AA749D51ULL, 0xCE3F13594A23B00BULL, 0x150EF74062B23371ULL, 0x4E0ED73939F5185EULL, 
            0x2C593022B892DDACULL, 0xE65854881A220859ULL, 0x7D4E28D1638DA753ULL, 0x2FC56D62C4752663ULL, 
            0x638CBBA957DB4806ULL, 0x4CE414133DEDF559ULL, 0xA75B17635A10DCF1ULL, 0xFC93FEFD4A460A8FULL, 
            0x7F388FC857D7D418ULL, 0x4D8B7C5B3EF31B94ULL, 0x92C19C56E7F087E2ULL, 0x51A3CB3324C5A98FULL, 
            0x35E984F6ED238A91ULL, 0x063591E387A8E9E9ULL, 0xF3CE0F2B4FAD1FDBULL, 0xD70600AB321AA25EULL, 
            0x9B4EAFDBD0DCF602ULL, 0xDF3BF41F75655B22ULL, 0xDD593750BCAE5F94ULL, 0x27F31790B229A72DULL, 
            0x14112322B451CFA1ULL, 0xD7319D0398CB9BA1ULL, 0xDAF2D891FC51BC55ULL, 0xD62530178A0D6650ULL
        },
        {
            0x028759B4D972E8C2ULL, 0xF78FF45FC2592926ULL, 0xDEDB0E6BF1F30F79ULL, 0xEADFC93B2A8D82CDULL, 
            0xFEB72B98FF36D242ULL, 0x35E7FB7D99E22EA6ULL, 0xE1245ACCF0D2C43EULL, 0x14B79AF3A2F7D25CULL, 
            0x3F0F930CC5E64A88ULL, 0x5A805D24013C48ECULL, 0x1304D2AA61EDB40FULL, 0x44B7038090306CE1ULL, 
            0xDD6A74BE9D60E922ULL, 0x8290BDB714A6545CULL, 0xA8A7171D69627806ULL, 0xF6436EE54E18D31AULL, 
            0x4C4FA67712564EA2ULL, 0x389AE8CBEF518E86ULL, 0x78BB8B3152DAD9C8ULL, 0x33E8C216C6B07C74ULL, 
            0x9B4CE2CEAB9A8AE3ULL, 0x433DFFDA5C43568AULL, 0x4738281B59098BCCULL, 0x54B1071B7FF2C47CULL, 
            0xDA97B6D523B76077ULL, 0x5E40FAC049AEB29CULL, 0x0EB8163A7DA5681AULL, 0xA1D1EE7A851ACFE0ULL, 
            0x8A9223F896CA62E7ULL, 0xC996D490725EE978ULL, 0x4AE02FA60B6275BFULL, 0x050C218409535BC8ULL
        },
        {
            0x9722A1CC37448128ULL, 0x8ADAE6E18C9D2938ULL, 0xAF6C4C2FF911AE90ULL, 0xE508B6C4EB6CD470ULL, 
            0xADD548F7586463FBULL, 0xC4AF69B41A85C390ULL, 0x9A631579E3912B5DULL, 0xFCF106A970F24B8CULL, 
            0x25145603269DE727ULL, 0xD834E19D5CC9501FULL, 0x4650DF8A09FC5012ULL, 0x8E93DC7E80BB35E1ULL, 
            0x7FD6C22EF337D5A4ULL, 0xE3703CB5D66D379BULL, 0x337597C34B96D9B9ULL, 0xDF9B803934703252ULL, 
            0xE409B360FB03E7A8ULL, 0xDEEC1E28479EC0A7ULL, 0xE31282327448CE5CULL, 0x8B5E9CFD7B534BFBULL, 
            0x8FAD003E8EC0D124ULL, 0xAE165BCEB29A5EDDULL, 0x8AA6BCA4B65E428AULL, 0xA4BDF91EF996F0D0ULL, 
            0x5FE97055299BC899ULL, 0xD9C3033AE2E51C1EULL, 0x6083551F5BE587B2ULL, 0x64D4814B69239867ULL, 
            0x4B5D06EB4635D022ULL, 0x57EB26BA86C9838BULL, 0x91DCF548758FBA74ULL, 0x221635565EDFA219ULL
        }
    },
    {
        {
            0x56470910CEB744BAULL, 0x6A28A8FF868F8D99ULL, 0x1B6C21C2BFF1FC99ULL, 0x962ED172CAD38B7AULL, 
            0x54AAA281D6D7B51DULL, 0xC3D195FCBB3964D0ULL, 0x1411011B9A55494AULL, 0x5FC0F78324289368ULL, 
            0x955B744CE76354DFULL, 0xB2F25148F2933051ULL, 0x3D724A137AB57886ULL, 0xF353F0EA55B99A6DULL, 
            0x614A952135E079A6ULL, 0xEB5B671E3CEB5925ULL, 0xE553A4CD7C3FEB67ULL, 0x37F2617F45D473F0ULL, 
            0xDBE517B385D38319ULL, 0xEF443EEF9A47B90EULL, 0x54D3AD13E561B259ULL, 0x1065AA0F96DB68EFULL, 
            0x790E65D444A6F4ABULL, 0x207D1ABD8CC644ABULL, 0xF043463B81C5EA3AULL, 0x60D7B0F69FB0DE96ULL, 
            0xB256EAFD8E50D3C8ULL, 0xD51850B7ADCD2A42ULL, 0xEADFDE297781A75FULL, 0x1B2B500153366550ULL, 
            0x1B8EA91C818B1391ULL, 0xDF539EA1D4828608ULL, 0x6D900A710127A300ULL, 0x8BF6D49AFDCF4A83ULL
        },
        {
            0x709810B1B0F3D114ULL, 0xEB50801295B7A30FULL, 0xB68F878AFB8D1925ULL, 0x3D97004FAAD21E9FULL, 
            0xB924917E30CC14BBULL, 0xB3310143BA0461D6ULL, 0x2E5F3FB368BBA584ULL, 0xBA62F5477B2E6E0FULL, 
            0x5A630CC9937EB83CULL, 0x49CAB35CCBDCCBEBULL, 0xC340A564B805CDF3ULL, 0x6D58E1929F961683ULL, 
            0xDDCD42F0B8E41D6AULL, 0x9BCABE9D8CAAE75DULL, 0x7B07FAD85F8E1676ULL, 0xB510ACC7915C361CULL, 
            0xC63D5B9D7F19F315ULL, 0x84EF1075C952BD73ULL, 0x87ECB162204CCE81ULL, 0x1FDE2B72FD75BDC1ULL, 
            0xC3BF6D4E54A8F96CULL, 0x1DD629A05A4B7673ULL, 0xEACC90199BC2162CULL, 0xAB2B7D536BD1F918ULL, 
            0xDA3FBE7782B34B51ULL, 0x2FD7863A902B6C51ULL, 0x2C62D4BD074FDD35ULL, 0xDCDB28AC763D2B67ULL, 
            0xB86E4652FA57CFC9ULL, 0x30574FE24F4B4BA7ULL, 0xCDB5AE9471B6ADDCULL, 0xA164B56022C8DA44ULL
        },
        {
            0xF54A1AC6E5E5033DULL, 0x736B62B2FFC77BA7ULL, 0xCDBB59B004B407D9ULL, 0x820743E4092FE028ULL, 
            0x4149A2079016D58FULL, 0xE7C56D10B8C311D0ULL, 0xE6382863F5738F3FULL, 0xBB0EBCAB63020F88ULL, 
            0x0DB41EDD529BB767ULL, 0xF219B9011784E801ULL, 0x696000320565C311ULL, 0x08E07316A3074B10ULL, 
            0x1DB3009972AFABBBULL, 0xAE43F600B4550D56ULL, 0x43DEBAD4D3F4314BULL, 0x46C9F46E1E8C7256ULL, 
            0x0D3699C4E22DC099ULL, 0x5FF2CEB5C71D1615ULL, 0xB48B803F1157FD79ULL, 0x027BD9568AAC2B3FULL, 
            0x555BA6A8B27670DEULL, 0xA1F5FBA26079FB9CULL, 0xBE8A7CC01A4AB3B8ULL, 0xBD825894D4D0AFD3ULL, 
            0xA2824661B0EE210BULL, 0x41A9C715F12AC5C7ULL, 0xBFDB00EB74025BC4ULL, 0x92B42D9705C7C09AULL, 
            0x8A5C1B77F58D93C5ULL, 0x06C22D1D0B0EDECFULL, 0x039B0DC3DD7CE43EULL, 0x46D228F9462AF475ULL
        },
        {
            0x5A2E5F12ACB7710FULL, 0x32138D31D99154CEULL, 0xB04E88480AAC0949ULL, 0x736E084733F3110EULL, 
            0xD14C2B53565FF9AAULL, 0xEC46B75045B00193ULL, 0xA8584C4D57FD8BC2ULL, 0xDEE4B4A3399B9F7DULL, 
            0xBEF6E27AF14E26ECULL, 0xB41DBEE9798DBA60ULL, 0x4CFF1F570C677631ULL, 0x20D43F05B7B4B30CULL, 
            0x263F9F9120085BC1ULL, 0xB53BCC859F9C296DULL, 0x9F3C8A8F99BEC78DULL, 0x2F9FF7B8019F5C3EULL, 
            0x0C72DE03F2CEA6EFULL, 0x20F3BDBEF62331C2ULL, 0x52BF1C259602DED6ULL, 0x4156D284F3DEFEE4ULL, 
            0x1A1FD9BE2449DB85ULL, 0x49FCBB1336019A0CULL, 0xAEC4094E1AF1909DULL, 0x5FC31B824C1262C8ULL, 
            0x6FF9E192AE7C15ACULL, 0xF8BB0BA6F8E059C8ULL, 0x22D9BA172764612FULL, 0x4F8F11904995C603ULL, 
            0xFE659C178C26BBB7ULL, 0x3E654A699044D499ULL, 0x7539C66B9ADB5F2EULL, 0x30F7CE8EA4A5FDD9ULL
        },
        {
            0x4BA896FD05F4D938ULL, 0xDCE525F326EA85B2ULL, 0x7A92EACACAD123BAULL, 0x8C1D68C963396E19ULL, 
            0x4F85C9A364438737ULL, 0xA8FCD201D3807538ULL, 0xC8112F045CCFE33BULL, 0x03E70DC936114A42ULL, 
            0xD7075DC81136A424ULL, 0x613C7E9D2D18E0A0ULL, 0x8F07DC79717AD626ULL, 0x5C89B78B38D64222ULL, 
            0x92241D105D489922ULL, 0x76D6AFCCA376E18BULL, 0xC355DA4087C3A944ULL, 0xE08AA58FCF7EF31DULL, 
            0x9A9E9825A0C41EF5ULL, 0xE3C44C13809C7DE0ULL, 0x171C42E13D23590BULL, 0x0522CA09356C8143ULL, 
            0xB94E9656EC437B28ULL, 0x7D3013F6746B124AULL, 0x36C888A51C4E3D4FULL, 0xFAC006CFE84777FDULL, 
            0x70B30B9B1444FB94ULL, 0xF1C2381E0C1F717CULL, 0xE343495AFB3750D7ULL, 0x5395C9D3750B37CCULL, 
            0xC654EEF7AF52ABF5ULL, 0x7668D4FC7367803CULL, 0x5D45E4F677AC108EULL, 0x22EEAB2C878D2FE2ULL
        },
        {
            0xDE4FD3E623B58EB0ULL, 0x58BFC6C1B4E97563ULL, 0x7C0CE1EC30DB7DE8ULL, 0x21CCC04D703F4D3BULL, 
            0x8CDF0B2E631B64D5ULL, 0xE57D3CEBB47E175EULL, 0x88834B94CFD4FFBAULL, 0x510CC51BFD63CA48ULL, 
            0xF855C5684D338AE7ULL, 0x4A6900D0F2446528ULL, 0x0B80B98EFD8295E6ULL, 0x4926CDC104AF3CCFULL, 
            0xF96B4CED35599086ULL, 0xBF9FF10E2451333EULL, 0xFD495DC3A189D60CULL, 0xBB13B14E3BD5453AULL, 
            0xEF6072E01CFE9BB7ULL, 0x5D7BE0D7BD170D81ULL, 0x144B91C841B2FC39ULL, 0x374C2F19CE68B855ULL, 
            0x4F00E3E763C33BCCULL, 0x03340FEB04B9E70CULL, 0xAE690AB4F3830176ULL, 0x43784714AE8476FDULL, 
            0x330B8B7013BD6303ULL, 0x9EACCA0FFA793C9EULL, 0x51EAAA63D83D2E91ULL, 0x35820D16DB8029B7ULL, 
            0xCB88BE6794827ABBULL, 0x14A561A8DED91567ULL, 0x17536EE714254D81ULL, 0xB387C0F171C372C3ULL
        }
    },
    {
        {
            0x7FC8522BFDAF71B9ULL, 0xA3B2ED243A1CF232ULL, 0x718440C47B3727CBULL, 0x19CBAE78634ECA09ULL, 
            0xC09B0271C0DA0989ULL, 0xC05A6C430AA3B943ULL, 0xE4CA662F77C6BDCAULL, 0x01AAE8F4D3648EF0ULL, 
            0x3B867869E6BEF939ULL, 0xB9C60C0C0D7A0986ULL, 0x7A9152062F98F1D2ULL, 0xC402DF2A40B39236ULL, 
            0xE57EDDCE8E0A2052ULL, 0x8AADF0FC5327907EULL, 0x5FF62C1E57297441ULL, 0xC9EEE23B70B759EBULL, 
            0x55956AB32A35A9A7ULL, 0xA6EB9567D4158BDCULL, 0xF9364F2A0B7C5E5EULL, 0x763EB43FEFBE3CF3ULL, 
            0x27C5A54E16C9C5CBULL, 0x47D1DBEEFB11FA4AULL, 0xEF962D85B62255FEULL, 0x94C85FC47BC744D8ULL, 
            0x01A0FFD6047C5500ULL, 0xC287D9C0C5B291C2ULL, 0x5FF5972290A61FB8ULL, 0xDF39BF9BB1D63290ULL, 
            0x868A1C06E9100495ULL, 0x018510F23D6CC092ULL, 0x638E9EACD202A3ADULL, 0x5BFE484995825E68ULL
        },
        {
            0xD7F3A5F3A9FCAA16ULL, 0xDFC75FE7C949FFBCULL, 0x0E138A3D26D0B338ULL, 0xEC5957A8C10A3F50ULL, 
            0xB22AAE769AB774E7ULL, 0x6DFE5BC6B48F533CULL, 0xDB09A1834B9E34E4ULL, 0x83060CDE18F6F2A3ULL, 
            0x32426B0703CEB373ULL, 0xD69929BED3C23E5EULL, 0x728CD9FE707EB171ULL, 0xCBA4B6249CDD58E7ULL, 
            0x4C6121D368C03B14ULL, 0xFFF945EBC09284A6ULL, 0xA354BC3A765BF679ULL, 0x3976D42B0D279E03ULL, 
            0x244F226C5A062B1CULL, 0x89F3667CAF319D4FULL, 0x2B6593EFC72CF8E5ULL, 0x10A6943F7CB1B279ULL, 
            0x7C32D9C3F0605F70ULL, 0xD301A490604DBA80ULL, 0xF0F7A80C6A21A0C5ULL, 0x36F852B7DEFF60ECULL, 
            0x408449939583C54FULL, 0xF3BE2FDB1713AE8EULL, 0x4C529E05F05C9FEBULL, 0x27A68F18A355FBD0ULL, 
            0xE0DAD659BD4F19A4ULL, 0x074D5B356644EA22ULL, 0x6D4495B8A8B04B40ULL, 0x151E023272006C90ULL
        },
        {
            0x1DDFEFEAE914B5CFULL, 0xA545B2CC6F32A66BULL, 0x6163A43688AFDAD6ULL, 0xBD7B699D9920DE04ULL, 
            0xE217020375DD77B3ULL, 0x9AE7E5F1ECCD84EBULL, 0x2E33F0DD53F9A99CULL, 0xF05AB026330D4CD5ULL, 
            0xF04410DD00770521ULL, 0xC7109B2E9DA29716ULL, 0x1AE22C4D289F07A5ULL, 0xD33C1BE274456DE1ULL, 
            0x79721D6C75883E5DULL, 0xBFABFD2C3CB2798AULL, 0xD6F9E9AF8A9E77ACULL, 0xCDABDBEC16D72BDAULL, 
            0xE24D2F44F0DFF79FULL, 0x4F9DCC23590316B4ULL, 0x59B47635C15E4FE6ULL, 0x63601F636E915071ULL, 
            0x822D582F54B05D6CULL, 0x353904A86D1D3BEDULL, 0x6C4D5F51BC6B4C3FULL, 0x9BCF115BDB574098ULL, 
            0x7479CC0482E122CCULL, 0xA3964E75EDC28C9FULL, 0x8BE7ABD36F1EB141ULL, 0x74418C1331845AA0ULL, 
            0x94EF2E871DA03110ULL, 0x6B3736185A309656ULL, 0xD184BB0B2A4E3D41ULL, 0x2456E4AD44EA720EULL
        },
        {
            0xE6B108191F0CF30BULL, 0xB2AB746FF78A8E12ULL, 0x70B6E348A7A84F12ULL, 0x3F07B4512668FE34ULL, 
            0x47247AA950A84E72ULL, 0x7BA286AC2C914F4EULL, 0x2A3E2B5651ABBB61ULL, 0x4658531108A10AEAULL, 
            0xA1FCA8774B9636D2ULL, 0x2DC162DEAE98B0FAULL, 0xE62E45F875DB083DULL, 0x434D4A06E98DEC80ULL, 
            0x1AF7B7F300A3FC72ULL, 0xA28CF6C0D4C0B368ULL, 0x78BBEC0E8BA1EB25ULL, 0x9EEF7C4F820135D5ULL, 
            0x130F516F4B917CE8ULL, 0x6973D575750FC41FULL, 0xB35A3F288B91949BULL, 0xFCC7A47A07C68ACAULL, 
            0x9E7BBFE1607302ECULL, 0x8C78DD508A72C696ULL, 0xD3685FC853DC0C0CULL, 0x4A64DC50838B053EULL, 
            0x1AFDC725ECF19E61ULL, 0x3EB5419D60EEA678ULL, 0xA859FF2A4053F0F3ULL, 0xDF57DFC833F62E74ULL, 
            0xE584975756673F9BULL, 0x3A9A81A2B1D551CFULL, 0xAFC011CAF177288FULL, 0x0D31A7FF4D4DEEAEULL
        },
        {
            0xFA279962A04C2EFFULL, 0xAA1A35470EB58F0EULL, 0x36F994D02800800BULL, 0x0EEA45592846FA43ULL, 
            0xD3C4B8BC474975B8ULL, 0x6B98BF0E0137ACF0ULL, 0x4A85284565B42F4EULL, 0x3BA7FE81E53EF515ULL, 
            0xB8B80277BE519F48ULL, 0xC47513701056B841ULL, 0x2069E7CB010723F4ULL, 0x9032C228BD9C0961ULL, 
            0x6D2C822407931926ULL, 0xBCBED9E27D8597D3ULL, 0x86BFAB216DE9649BULL, 0x3BFCCE556F5E5728ULL, 
            0x348EC0F8D0B2326EULL, 0x3AE61A5C715DB1F6ULL, 0x1F81B1655337735FULL, 0x129BEE9E33EAD3B9ULL, 
            0x6AD39FF56A79F772ULL, 0x40DE440104140068ULL, 0x50FF1DF674786BAAULL, 0x817803F85F06657CULL, 
            0x5559CA742128398CULL, 0xF1130C15972C1147ULL, 0x709FD9F6AA129262ULL, 0x2CB14B312ADDEB89ULL, 
            0x96E0BEF137AECA80ULL, 0x32928E2DF8CC6759ULL, 0x67C63E1CB11C8B07ULL, 0x134BC6D76FDCFA4CULL
        },
        {
            0xDF439C5613C31F85ULL, 0x3820A62C7332C907ULL, 0xB07DE155DB2DDC0DULL, 0x54FD6E8F5E4B280BULL, 
            0x6607371AC2E282F3ULL, 0x7507CDACC6C38008ULL, 0x0C75C917F75339EAULL, 0x7D62049ACBC9ACA6ULL, 
            0x8CDD2E13EC9CAAEAULL, 0x6798567C3072E3B6ULL, 0xE6892FFF162C08B7ULL, 0x00CE1489FF4C4035ULL, 
            0xDBF1BF649FCF365EULL, 0x5AB8A1CA81B528F3ULL, 0x2C1C911B2627F0E2ULL, 0xEF2F9E859AC33B7CULL, 
            0x74E45C197A678741ULL, 0x564996D2F5853B98ULL, 0x0B444D106D3BBEA5ULL, 0xA3A518EAB57B74ACULL, 
            0x61DD6DF277276555ULL, 0xBF8AA22AB26D7FC6ULL, 0x293838F1466040C5ULL, 0x55904EABA853C198ULL, 
            0x8377D08364B1EBDDULL, 0x2FCE6EAEB4CFA553ULL, 0x5F7C46D9E7AF3DD2ULL, 0x4EF8D4723D23C956ULL, 
            0x216060688224CC39ULL, 0xE2798740ED0041D9ULL, 0xD9C3A61DA9839E42ULL, 0x17365CA12170B418ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Canopus::kPhaseHConstants = {
    0xE78B2C6E2E095306ULL,
    0x4A8F527BC54305C4ULL,
    0x575C601D66F0C092ULL,
    0xE78B2C6E2E095306ULL,
    0x4A8F527BC54305C4ULL,
    0x575C601D66F0C092ULL,
    0x6BC7F23B5DEF8A06ULL,
    0xD03F7FBDE72A663CULL,
    0xB2,
    0x6D,
    0x81,
    0xF8,
    0xF4,
    0x72,
    0x42,
    0x29
};

