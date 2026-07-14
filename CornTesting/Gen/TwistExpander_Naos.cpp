#include "TwistExpander_Naos.hpp"
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

TwistExpander_Naos::TwistExpander_Naos()
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

void TwistExpander_Naos::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xF68E97540CDB5FAEULL; std::uint64_t aIngress = 0xFA861B9105722F9DULL; std::uint64_t aCarry = 0xC0C7DE311ED70509ULL;

    std::uint64_t aWandererA = 0xD7099CD32A2A0743ULL; std::uint64_t aWandererB = 0xB86BE844963624B3ULL; std::uint64_t aWandererC = 0xBAD31B9A7DB5011AULL; std::uint64_t aWandererD = 0xD52610507D77AA89ULL;
    std::uint64_t aWandererE = 0x908343100C31302CULL; std::uint64_t aWandererF = 0xEA98C88A1AB69A6EULL; std::uint64_t aWandererG = 0x8452AD4C75B3ADD1ULL; std::uint64_t aWandererH = 0xAA0A1FAFC83BCDFEULL;
    std::uint64_t aWandererI = 0xC92B16B1862C47CAULL; std::uint64_t aWandererJ = 0x911C743FC51B1342ULL; std::uint64_t aWandererK = 0x83F00AAA0A59E295ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 17162405941606996743U;
        aCarry = 14495006675980887259U;
        aWandererA = 17209928759292829517U;
        aWandererB = 17114831279665988593U;
        aWandererC = 15764417522178723429U;
        aWandererD = 17484487248600028580U;
        aWandererE = 15654904098375152553U;
        aWandererF = 17324971436232269081U;
        aWandererG = 16119479230192827281U;
        aWandererH = 18023567596231877599U;
        aWandererI = 11081143103369393163U;
        aWandererJ = 13049882542871986932U;
        aWandererK = 15250934248741300748U;
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
    TwistExpander_Naos_Arx::KDF_A_A(pWorkSpace,
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
    TwistExpander_Naos_Arx::KDF_A_B(pWorkSpace,
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
    TwistExpander_Naos_Arx::KDF_A_C(pWorkSpace,
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
    TwistExpander_Naos_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Naos_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Naos::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0x8EBFF211E8159F15ULL; std::uint64_t aIngress = 0xE8FE7B86C9D8C59FULL; std::uint64_t aCarry = 0xA27569B2CA683354ULL;

    std::uint64_t aWandererA = 0x84F2B7569BCC81FBULL; std::uint64_t aWandererB = 0xCD8C96839292B29CULL; std::uint64_t aWandererC = 0xECC2D034CA2C3D45ULL; std::uint64_t aWandererD = 0xC0DE020D29E09EB0ULL;
    std::uint64_t aWandererE = 0xBCA3A9799A5B2F3DULL; std::uint64_t aWandererF = 0x90CD69C6EB53EBC1ULL; std::uint64_t aWandererG = 0x9E28DB40AF02F0C2ULL; std::uint64_t aWandererH = 0xC7D1FFB714BB6299ULL;
    std::uint64_t aWandererI = 0xF8C5AC79FBFF04DEULL; std::uint64_t aWandererJ = 0xC4AE557A3029F6EFULL; std::uint64_t aWandererK = 0xFCEF93985B449964ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 9823377248316449310U;
        aCarry = 15294987329218593767U;
        aWandererA = 13222112099530502817U;
        aWandererB = 17120071375607579681U;
        aWandererC = 10654248285939844646U;
        aWandererD = 10043979846960645467U;
        aWandererE = 14632406279738073509U;
        aWandererF = 10996263752693476652U;
        aWandererG = 13772335666759301822U;
        aWandererH = 17621116449007257381U;
        aWandererI = 14311654655188343774U;
        aWandererJ = 14805307584596387564U;
        aWandererK = 10080212372021237447U;
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
    TwistExpander_Naos_Arx::KDF_B_A(pWorkSpace,
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
    TwistExpander_Naos_Arx::KDF_B_B(pWorkSpace,
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
    TwistExpander_Naos_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Naos_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Naos::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0x9FD5010718111006ULL;
    std::uint64_t aIngress = 0x86C9FE64C52DAEB3ULL;
    std::uint64_t aCarry = 0x90880FF3E54D1073ULL;

    std::uint64_t aWandererA = 0x8F1DF72E5C157C95ULL;
    std::uint64_t aWandererB = 0xD39F7ADC7FCCF719ULL;
    std::uint64_t aWandererC = 0xBABA1D3BD56433D2ULL;
    std::uint64_t aWandererD = 0xE029A9944024AED3ULL;
    std::uint64_t aWandererE = 0xE20914DC9250D370ULL;
    std::uint64_t aWandererF = 0xF02FB9865705B2F0ULL;
    std::uint64_t aWandererG = 0xA682EF2316351180ULL;
    std::uint64_t aWandererH = 0x8601D6ACD50C2DA9ULL;
    std::uint64_t aWandererI = 0x87C2B0C1C0E6798DULL;
    std::uint64_t aWandererJ = 0xB1D9EB894F73F75CULL;
    std::uint64_t aWandererK = 0xE5C755E847AB026DULL;

    // [seed]
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneA);
        TwistSnow::Aria256Counter(aSource, aSnowLaneB);
        TwistSnow::AES256Counter(aSource, aSnowLaneC);
        TwistSnow::Sha256Counter(aSource, aSnowLaneD);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneB);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneE);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneC);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneH);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneA);
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
    TwistExpander_Naos_Arx::Seed_A(pWorkSpace,
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
    TwistExpander_Naos_Arx::Seed_B(pWorkSpace,
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
    TwistExpander_Naos_Arx::Seed_C(pWorkSpace,
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
    TwistExpander_Naos_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Naos_Arx::Seed_E(pWorkSpace,
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
    TwistExpander_Naos_Arx::Seed_F(pWorkSpace,
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
    TwistExpander_Naos_Arx::Seed_G(pWorkSpace,
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
    TwistExpander_Naos_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Naos_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Naos_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Naos_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 23 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1796 / 1984 (90.52%)
// Total distance from earlier candidates: 39954
void TwistExpander_Naos::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1899U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 985U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 972U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1190U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1623U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1394U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 291U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1292U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1254U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1680U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1832U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 423U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1085U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1072U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1674U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 989U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 673U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1220U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 889U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 770U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1064U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 689U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 718U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1042U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 705U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 699U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1436U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 446U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 2010U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1499U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1128U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 700U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1922U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1299U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1897U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 411U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1958U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1829U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 2001U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 467U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1008U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1986U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 640U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1491U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 502U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 760U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 955U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 81U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 418U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1106U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1586U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1638U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 246U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 476U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 682U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1721U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 314U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 279U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1328U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 768U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1696U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 149U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 403U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1192U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1628U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1702U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 316U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 469U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1441U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1141U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1661U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1795U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 944U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1593U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 102U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 563U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 232U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 913U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1136U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1507U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 360U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1847U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1789U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1228U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1102U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 244U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 525U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 234U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 968U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 970U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 902U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1401U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1777U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1743U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 849U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 939U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 900U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1854U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 662U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 91U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1455U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 216U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 732U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 36U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1813U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 2043U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 638U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 300U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 2018U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1901U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1234U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 253U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1309U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1914U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1842U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 302U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 911U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 826U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 996U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 143U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 369U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 668U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1184U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1083U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1238U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 559U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 272U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 901U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }
}

void TwistExpander_Naos::TwistBlock(TwistWorkSpace *pWorkSpace,
                                       std::uint8_t *pSource,
                                       std::uint8_t *pDestination) {
    TwistExpander::TwistBlock(pWorkSpace, pSource, pDestination);
    if ((pWorkSpace == nullptr) || (pDestination == nullptr)) { return; }
    std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    std::uint64_t aPrevious = 0xECE066F37008CAD3ULL; std::uint64_t aIngress = 0xDD1EF47BBF2417E4ULL; std::uint64_t aCarry = 0xA7FA559AD03E0DB0ULL;

    std::uint64_t aWandererA = 0xFA6C23B89A286E36ULL; std::uint64_t aWandererB = 0xF7C0AE6716432B87ULL; std::uint64_t aWandererC = 0x8AF24FA3293A984FULL; std::uint64_t aWandererD = 0xF2F6D27FECB4A756ULL;
    std::uint64_t aWandererE = 0x8DF4199C25B6B28FULL; std::uint64_t aWandererF = 0xD13DE4751FFB33BCULL; std::uint64_t aWandererG = 0xD040203671F84120ULL; std::uint64_t aWandererH = 0x9784A6149C7E23D0ULL;
    std::uint64_t aWandererI = 0x9F794655F5694DDEULL; std::uint64_t aWandererJ = 0xD3837219D9A8D31FULL; std::uint64_t aWandererK = 0xA8AF86F39993E511ULL;

    // [seed]
        aPrevious = 12960621179281830165U;
        aCarry = 11959299425286543639U;
        aWandererA = 18400049946592164193U;
        aWandererB = 14698708345763995399U;
        aWandererC = 11075296741641118755U;
        aWandererD = 11583145929890446720U;
        aWandererE = 10330060809515200022U;
        aWandererF = 17439464532059559331U;
        aWandererG = 17979882022398951225U;
        aWandererH = 9271728933532860886U;
        aWandererI = 12014051076082189634U;
        aWandererJ = 15330478745494734498U;
        aWandererK = 12342536732255254901U;
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
    TwistExpander_Naos_Arx::Twist_A(pWorkSpace,
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
    TwistExpander_Naos_Arx::Twist_B(pWorkSpace,
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
    TwistExpander_Naos_Arx::Twist_C(pWorkSpace,
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
    TwistExpander_Naos_Arx::Twist_D(pWorkSpace,
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
    TwistExpander_Naos_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Naos_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Naos_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 23 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 11931; nearest pair: 480 / 674
void TwistExpander_Naos::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 429U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7839U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1116U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 918U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2675U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1703U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5073U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6061U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4016U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3450U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4498U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2458U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7638U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2513U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5772U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3910U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 332U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1491U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 344U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 865U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
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
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 291U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1994U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1605U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 492U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 165U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1343U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1462U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1555U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1074U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 596U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 53U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1855U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1349U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1036U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 222U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 984U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 23 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 11942; nearest pair: 457 / 674
void TwistExpander_Naos::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3746U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 992U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3248U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2475U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6647U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5120U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7773U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 550U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 574U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2269U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5085U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4881U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 301U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2369U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7132U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6121U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1690U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1826U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1752U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1020U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1102U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1506U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1822U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1538U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 660U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1453U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1357U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1475U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1786U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 44U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 922U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1016U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1179U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 180U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1742U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1594U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Naos::kPhaseASalts = {
    {
        {
            0x4B08AB99BFB35AD9ULL, 0xCB345CA395C39BE4ULL, 0x75FC42389BA2A4E3ULL, 0xE4AD896DAD232E72ULL, 
            0xA96FBFF2F3C4B747ULL, 0xC1F04537BBE46597ULL, 0x196C161491645FCBULL, 0xB15EC3749FEC0A54ULL, 
            0x42CC6AF2A4143C05ULL, 0xCC70423D5B6CC9B8ULL, 0x4E2D2D3086ECB856ULL, 0x6E32D93EF79BB792ULL, 
            0x74FF8078E32A0EB1ULL, 0xF1D8E91F24A1E2C5ULL, 0xA12CB3BC7D516093ULL, 0x9ECC9D5ED81D8D09ULL, 
            0xA8EF06D7C090C509ULL, 0x0E55A8FB9942004DULL, 0x4F44B498F6AF856AULL, 0x68D974F8D26A7418ULL, 
            0x515CF2A0C3608BC2ULL, 0x270E7DA14DB03032ULL, 0x6E52339696E02B26ULL, 0xF85F3FDA9A27EB92ULL, 
            0xC1502193576EE397ULL, 0x95C37A2E6BC42014ULL, 0xBE4473E420897F87ULL, 0x5EA3B8D5F2ADF1F0ULL, 
            0xF701A0E2BA98B3B0ULL, 0x75E0CCF2E6BC77B0ULL, 0xC7E8BB246F44CA23ULL, 0x80721AAF69556682ULL
        },
        {
            0x2D34F4E9B1AAEC4EULL, 0xD8B957B79436A1E5ULL, 0x9FC15303A1AD334EULL, 0xBD5E17AE1F0EBCDCULL, 
            0x338C5873C20E9FEEULL, 0x44D3A019B566CCEBULL, 0x0ACA05E1628A4338ULL, 0xA393A35C09EFAE16ULL, 
            0xCE64C7505327A3A1ULL, 0xACA1CC6DB5A384B3ULL, 0xBBB5FD8268A2BF83ULL, 0x3E8D3071B375A93AULL, 
            0x38CBD53F03745C54ULL, 0x2ECAEB895A37B000ULL, 0x738DA575F7940CCDULL, 0xABBC4F340086E098ULL, 
            0x6E175883A15EF7CFULL, 0xA2016BF5773E2539ULL, 0x0558B8084C458523ULL, 0x0CA729AA48E9B4A7ULL, 
            0xC0F8AA083FF95121ULL, 0x6DDC8CC8543B9AA4ULL, 0x1AFC442435FA2092ULL, 0x3255EDB437B47FC3ULL, 
            0xAF0E2384546CCA43ULL, 0x1A4C0B5FAA702E85ULL, 0x2AB328CC9FFD7482ULL, 0xF28725DC5644FF83ULL, 
            0x8F8C207829A175BDULL, 0x4D00A24FD9D647BCULL, 0x331132642865E8ECULL, 0xC2883FC82E503C20ULL
        },
        {
            0xAF74E211E8322EDAULL, 0x4F139508D33EE4C3ULL, 0xB8DD4F2C200BB9FBULL, 0xD1D90467C5F90941ULL, 
            0x78174D1A7E767F4BULL, 0x7DF485F2ED31A42AULL, 0x11801EEBAE6374A4ULL, 0x5315FDF423885C60ULL, 
            0x27FF7C0DB2719207ULL, 0x6104D64ED56BDC9CULL, 0x3E55AF602AA99854ULL, 0x2D22A3A34A1EC73CULL, 
            0x97E1DBCEF4086388ULL, 0x0E03285F07A16898ULL, 0x51089151CCEEAB92ULL, 0x322785646FAA0122ULL, 
            0x1E04760FF2924F11ULL, 0x2F865BCB3B8868E7ULL, 0x8C46266C44B086EAULL, 0xA28E88D0D3599E11ULL, 
            0x77CA2CCA3DC4D8C8ULL, 0x1F624028C40E9A52ULL, 0x5EA10C2B4220F830ULL, 0xB207D84E7FD62771ULL, 
            0xD30DD2EC6FD55A52ULL, 0x92C2619A66C4A799ULL, 0xFA4929C8A669E634ULL, 0x3E20956C74D403A0ULL, 
            0x2F9469F42F3F1E75ULL, 0xB4CED42CCAF16203ULL, 0x58D1120C482CD2D3ULL, 0xD790BA1340EDBFE6ULL
        },
        {
            0x0253EAF61CC34344ULL, 0x08B422FB4F7D6FEFULL, 0x4957B95E8CE2F985ULL, 0x16732FF38B9986F7ULL, 
            0x7DD24D5F8919F76CULL, 0xA075BBCDB3B06129ULL, 0x07BA36AA1979078EULL, 0xA6CA24247BC2C4DBULL, 
            0x60AF4D4F9CC5027DULL, 0x1A2E17D0DD27829DULL, 0xAD86ACBA89D26DD8ULL, 0xEBB5617890DD0430ULL, 
            0x52703F59AD571D36ULL, 0xD2B74C60E3D887AEULL, 0x535328272835AF5FULL, 0x41FFC230A005F8D8ULL, 
            0x1E01675946C37EDFULL, 0xADA955ACF7B3F58DULL, 0x86CD2E14C95F672EULL, 0xE7E3C3A551687E7CULL, 
            0x87F9677943349D61ULL, 0x4075AF749C85890BULL, 0x0E6F2C4583250C93ULL, 0xEE03901AC8A5D7D6ULL, 
            0x346020C3AB56E7C6ULL, 0xB4FAD69821E45203ULL, 0xD29E454E49FB3295ULL, 0x2CB84F84367BA6C8ULL, 
            0xDE9CD76853C460D7ULL, 0x4DF976164251E3A5ULL, 0x55C5C3BA07629E7BULL, 0x929E96EDFE32D188ULL
        },
        {
            0xED38D42B713DD9BFULL, 0x600AE5C48E24C304ULL, 0x1213F2AF2EDBA68BULL, 0xA120754A60368465ULL, 
            0x64AC9238F00F6905ULL, 0x76D55E1452B0CB35ULL, 0x56C0FC7353C32084ULL, 0x7E8159D15BE14BA9ULL, 
            0x79998350BA4241B3ULL, 0xBBECF82C723340ECULL, 0x705B20BA389F6375ULL, 0xD8752C64436E1B60ULL, 
            0x1FC6F8D26C7744F9ULL, 0x4786D82912C2D5D9ULL, 0x10F8591F6C47B871ULL, 0xF5DB1831AFD86382ULL, 
            0x73A69058719D1594ULL, 0x8676A6705D7B9747ULL, 0x5054D85DA9EDCEA8ULL, 0xEA3BF423B82944BFULL, 
            0x075D1747A7F9EC01ULL, 0x07CDAB2726401B16ULL, 0xA6965BB2BDAB6AACULL, 0xA9A42A4E12400ECAULL, 
            0x32468C8E7973E708ULL, 0x19B5A7941B08B77AULL, 0x92A8F3ED5CC6D900ULL, 0xD9DED0102BA1138BULL, 
            0xA03A887D0C06FAC9ULL, 0x27B78E93513B2B1CULL, 0x2D41684E44439976ULL, 0xB1E3CB5FE7F191C7ULL
        },
        {
            0x027310AF118F381CULL, 0x455B19DD22E1743FULL, 0x9C8E19AE427EBD98ULL, 0x5764C27854BE7716ULL, 
            0xB81A00539C13651FULL, 0x4FB3DF15B3AD6512ULL, 0xCCB1BFEEBF6584E7ULL, 0x54D41D840A604906ULL, 
            0xABB69E8BA2799786ULL, 0xE0C0CD8392B3B5C4ULL, 0xB35A41D1EC0DAFEDULL, 0xDECA04E3E30ED2D5ULL, 
            0xEED8AEBC79313413ULL, 0xACBEFB74E389D55BULL, 0x9837ABF6DB18B1E1ULL, 0xCF4EBF3D2345FBE9ULL, 
            0x1B57BB117B036B17ULL, 0xC673B7657FE4F5B4ULL, 0x6BB64607B5E06AA9ULL, 0x8DEDC83BB6BB9F8EULL, 
            0x27032FEA8FEC281DULL, 0xF2CD7C7DF841A8B8ULL, 0x3C9412F062C620EDULL, 0xF52F03F8D7F94AFBULL, 
            0xD6AFA82E96016A81ULL, 0x8325D621B31F6B16ULL, 0xE95F6702E9DB523DULL, 0x35EDA457D4F954D0ULL, 
            0x6EE892D9564F3AD7ULL, 0xD5F8505E8B0C38F7ULL, 0x5D51258F264ECD0FULL, 0xE3D1C0BFD22FF9B1ULL
        }
    },
    {
        {
            0x74425A4EC27DC09DULL, 0x815AA2F0BE81EE4BULL, 0x5D42A872EDECFA15ULL, 0x7BE2DA0CFEE12415ULL, 
            0x6F9E22D91DEDA202ULL, 0x7FCF589206313DC6ULL, 0x5B3A91AA1C38A6A5ULL, 0xD2CEBD6FB0B4AAA4ULL, 
            0x6F01C820847B0B7FULL, 0x720B84D21FD3219DULL, 0x8688FA877674F62BULL, 0x63DAA4CC4E6CC645ULL, 
            0xE3B15C9E70E844E2ULL, 0x22B8CF7E4169D3F6ULL, 0x3F71FE599EF4EA7AULL, 0xE0EA054D6A0891FDULL, 
            0xDE377F13BA2332B0ULL, 0x459C5174E0BA2173ULL, 0x14FA056ECAAAAE33ULL, 0x00BE96EBA4834225ULL, 
            0x8490316EDC99765EULL, 0x34DD585DC438CED5ULL, 0x8498CC2E64787612ULL, 0xEA4CE07052E7BF4DULL, 
            0x30810127B73FA1D9ULL, 0xF924B0ADBCC61A46ULL, 0x6AE01C29956B9376ULL, 0x5C73BAF078556384ULL, 
            0x37D3C8064E430897ULL, 0x43DD8AD48ACBC6D4ULL, 0xB0A8669BB8BF0CB8ULL, 0xDB234B29893A1335ULL
        },
        {
            0xF27187ABF14FAEFFULL, 0xD88604E2B337646AULL, 0xDC9904F9C4A260CBULL, 0x95B4CDA5AFF8A7CBULL, 
            0xABF6DEA933C4F448ULL, 0x8778CCA0FAFD7444ULL, 0x91CAE628603004C8ULL, 0xD384B563D127A291ULL, 
            0x4AEEB29AB82A1E84ULL, 0x737639949A8F7D05ULL, 0xC4B20D58A3B0902AULL, 0x79A9B67CBB4869ADULL, 
            0xAD63717AF8C43563ULL, 0x4F41B09A5D8EFA46ULL, 0x424F0FCA0B4ECE31ULL, 0xFA835EBF3064E1DEULL, 
            0xD27D7927DA286B0AULL, 0xF0C918A97D096447ULL, 0x3AAB21294EB02F24ULL, 0x5EA545F98478C886ULL, 
            0xE596AA8C93B1FD2DULL, 0x624BB6B850741D85ULL, 0x0C9166020FA2FAE6ULL, 0x3D461D501EC16C5CULL, 
            0x4861255BAB965AE3ULL, 0xD9D0990438E2E8E2ULL, 0x97E46EF7D454E6A7ULL, 0x6B1DA78241DDB260ULL, 
            0x1FE43341C54D9E3DULL, 0xC8878A15561ED5BBULL, 0x624975228EB287E0ULL, 0x6320826CBE4E72BFULL
        },
        {
            0xE5F182299DCB92BEULL, 0x2E954ECA2B3B5655ULL, 0xA2412A4F6294608AULL, 0x788864978C8664C4ULL, 
            0xB22A002FC055E116ULL, 0x7FA492FB024030ABULL, 0x5346DB443F6E8FB3ULL, 0x33C617BF5F7DB7AFULL, 
            0x313CE661E7E9932BULL, 0x3867D249E115EED4ULL, 0x247C7D2E135F6F63ULL, 0xEE877B4543E0237DULL, 
            0xD4C211323F726758ULL, 0x412991B50C34A1ACULL, 0xCA71435785F43605ULL, 0x8E621A0D64D7F700ULL, 
            0x8BCBEE2E7CBF915AULL, 0x8691544B7EB4DA2CULL, 0x0940CB934A5B27E5ULL, 0x8FE341F4D8A19487ULL, 
            0x1716C2C967E73707ULL, 0xBDFC3239448ACEABULL, 0x8B67E192A8E24A12ULL, 0xB9F2D2F00250FB90ULL, 
            0x8FE2A2C03CB37BB3ULL, 0x36F0A576958C65A7ULL, 0xABD05630D72F9378ULL, 0xC61CF381ABEAB45FULL, 
            0xA0D31F708B930235ULL, 0xFC196D7CDDC8FB49ULL, 0x52C6E724B920837EULL, 0xA4FED6EB1CC86B71ULL
        },
        {
            0x7D616DD27F825B76ULL, 0xF275D683CEC4C1CAULL, 0xCDCE06E1D087EE69ULL, 0x427A3281AFF37C99ULL, 
            0xE6C2226D7A2EE2BDULL, 0x42B29115AE56FEFAULL, 0x3977E2C1C2870E47ULL, 0x30FB99B3ECDCE575ULL, 
            0x8D94EC5B300FECF4ULL, 0x42D82519DE58775FULL, 0xE7267971C68C7CB2ULL, 0x0335552CCB903022ULL, 
            0x6819D4225FA803A6ULL, 0x8829C71B475A6BD5ULL, 0x249EBFAA7895479CULL, 0xDEF977074B0CA628ULL, 
            0xF1718A3BC342111BULL, 0xB38E75828056EB9FULL, 0xE85D12B1E6C7B269ULL, 0xF8410BF4FF079A24ULL, 
            0xDD1F0E94F2E09C0CULL, 0x84D2FD5FBBAB7596ULL, 0xB780A38301EB09D8ULL, 0x73A5DD509D1CD701ULL, 
            0x4039F08990E16A0AULL, 0x4DA3887BA97E8625ULL, 0x10A1B77A475619AFULL, 0x7B888404A2837DB7ULL, 
            0x7ED4EDE972814794ULL, 0xF7292A31349B4EE1ULL, 0xCF6B554EBFA8CDC9ULL, 0xED03A30C5475B694ULL
        },
        {
            0xB153D84F8C2908F7ULL, 0xE708E975F3F4485EULL, 0xA7F71315C1FEB0B2ULL, 0xD3A0D905E388BB84ULL, 
            0xAB5E287FA8DD8DE9ULL, 0x9C13566A85A72081ULL, 0x2CE419CE9CA69FD1ULL, 0xA0A232D24B75F36DULL, 
            0xEF7FA627097977DDULL, 0xB40FAD1842955D34ULL, 0xF80DB7669E735B3EULL, 0x114603F3665C147BULL, 
            0x7F0ABF8F91699664ULL, 0x66D07AED42D51E31ULL, 0x05D56415C2BFD5A1ULL, 0x6C1C2FABA1BE113EULL, 
            0xCAD3BBCCE725886BULL, 0x1517545A53BD0268ULL, 0xC81C5F0BC49D3218ULL, 0xDCDE5C3FC551A428ULL, 
            0x10AE879D730299FBULL, 0x99578E4771B7F650ULL, 0x48B073C445BAA7CDULL, 0x9137E9865E9107E8ULL, 
            0x860B22A63BAE1141ULL, 0x5A405C2A2C12F314ULL, 0x0E237DF186ACE729ULL, 0x6EC2B957B0372091ULL, 
            0xB2B210DAB39BFE98ULL, 0x33DF9ED5E44FC384ULL, 0x1392FE6B76DF20FDULL, 0x28AC21C8D8DA9464ULL
        },
        {
            0x190583EF068ECFDDULL, 0x728F0C1EEE4C8E72ULL, 0x3AD9595953F6EDBEULL, 0x65B2C8B0E73E37A9ULL, 
            0xE6D416F2FF7870C1ULL, 0xB6A5A934E72C1566ULL, 0x2D6F87D4C914D3D9ULL, 0xAEE8E1B701B94EBAULL, 
            0xCE9714778C3F161BULL, 0x9D24FF80CDD78E84ULL, 0x3B63EE34B3ED3A10ULL, 0xB143A96148F7BB3FULL, 
            0xB2C8C8FBF4D53ABDULL, 0x9AC0D45690C226D0ULL, 0x1DFFBAF7CA58945CULL, 0x083EB450010F404AULL, 
            0xE6DC3A7D7629D043ULL, 0x3907163AC3E8CA62ULL, 0xE7CB9134992EF991ULL, 0x5473753D8ECEB46DULL, 
            0xC0E4FE0FA7F18592ULL, 0xB4DA1F0D3BC276E5ULL, 0x9B2D8613B1D1EC08ULL, 0x202F45D79CED1D10ULL, 
            0x52B662C37E6EF755ULL, 0x8FEB625C3077DD59ULL, 0xD370628DD0609EBDULL, 0x8417EBBDF9852D5DULL, 
            0x85ED0A0FB4D23F9FULL, 0x641A747292C36726ULL, 0x5535E8DB2920595FULL, 0x2FFA0C615DF85389ULL
        }
    },
    {
        {
            0x2429A0D532F6AFCEULL, 0x45CAD5C56E7616E5ULL, 0xC74890ABB9934C49ULL, 0xB34CECA055AC8613ULL, 
            0xBEDF6EF7AECD7E54ULL, 0xAC1C931C77CE5471ULL, 0x5E8C85EA680F8FE8ULL, 0xD6FD610BA608A2DBULL, 
            0x2CF50D99AF5A94FCULL, 0xA9AF36885200480CULL, 0x5299F41DD212B9BEULL, 0x56F3ED07D7B833CBULL, 
            0x90BD7C7426DA137DULL, 0x33A05D93C846E934ULL, 0xCE1985BFC0B8C374ULL, 0x66F9E85FB31F86ABULL, 
            0xECFBF01888375A4FULL, 0xE5BA4E7994B7F402ULL, 0x5B9105865E25F678ULL, 0x631330E12222952BULL, 
            0x7AB6D13416AB0F5EULL, 0x9E6AD6B481DBFF19ULL, 0x0A1C384094D3AA15ULL, 0x91B6CE7C084596B3ULL, 
            0x68804E0BF8378565ULL, 0xFFD0A0B5014BE5B1ULL, 0xB83C425A22CD0137ULL, 0xC0267FF55A363A11ULL, 
            0xCD91D62DD69C0BE0ULL, 0x0B7E9D5974F582A5ULL, 0x5808A28B472B9915ULL, 0x4DF7FF0513803DC9ULL
        },
        {
            0x6CD9424E6E1EC8A7ULL, 0xF8F9C2F0171F20CEULL, 0xEAB283554E3ED5C0ULL, 0x0F4FB964006037AFULL, 
            0x5C2F4089309F598CULL, 0x8C5C04030AC2AC23ULL, 0x9895A3903F8945ADULL, 0x8290BEFE2DF8A1AEULL, 
            0xECD9DDA21E8C7546ULL, 0x6ED974C8CBB717BBULL, 0xEA9555FDDE577901ULL, 0x8DAD29F77F779C58ULL, 
            0x2AA29F1B34121E8BULL, 0x404449E6A542F532ULL, 0x08CC831CD37B04A8ULL, 0xC67FE411CDCF105BULL, 
            0xE2DF65E148A2DF0DULL, 0x3B755DBDAA785D1DULL, 0xB0281F8999543EA2ULL, 0x85DC5632E28C3A25ULL, 
            0x9C1B648035F5DAF9ULL, 0xE5A213B848C7E3E6ULL, 0x9744B3984CCBAD44ULL, 0x165DDF266357F222ULL, 
            0x33C7EDAE8D2E3EDFULL, 0xE3BEDFEC7B42ED00ULL, 0x2BF8CBF6FC224F6FULL, 0xB8075FB9CF12AA5CULL, 
            0xCB63A491D4BAE7F5ULL, 0xB89BEBAA7DD90D98ULL, 0x315EC45A40D3A610ULL, 0xC8A8FDF15537FD0CULL
        },
        {
            0xAD8379472DDB5BABULL, 0x3C92008707A03C60ULL, 0xBC17AAAB57329F8BULL, 0x858C95ED29B17F47ULL, 
            0x16C4B9437C95B175ULL, 0xAA75124E53F90250ULL, 0x8D7E8424352C8340ULL, 0x540E46EDC321396DULL, 
            0x588A30773BD1D402ULL, 0xF32D7080DAFF5F75ULL, 0xDCD63C10940D1309ULL, 0x032B9643A3F01728ULL, 
            0xD6952D1EB32390A1ULL, 0x2071F5BED61B108EULL, 0x0B1974DCB1A022A0ULL, 0x84C3731B512BB3B3ULL, 
            0x39B46D88455FB0FEULL, 0x3002F9C10A427C3BULL, 0x2E922997BF7E5B3BULL, 0x0EA4691E9B1239B7ULL, 
            0x8113FCE84109B958ULL, 0x8AC7348BCA085383ULL, 0x159A224E7D4CF437ULL, 0xA34A03FEC6794DC2ULL, 
            0x701D41FD41EC6719ULL, 0x4ABEACCF1B2B965BULL, 0x9B0042042A67BE42ULL, 0x1F9E1D5EDCCBF3B6ULL, 
            0x95FCE7B491685200ULL, 0x71008E069D855450ULL, 0xE066F257DA0808E6ULL, 0x6A103EE3F2B0B6D8ULL
        },
        {
            0xC5D1B0FD578F4D36ULL, 0xFCF3B45C9C919663ULL, 0xEA01A8BC23BE6888ULL, 0x2417C6415E8A588AULL, 
            0xBE70AC8F7BF84E65ULL, 0x96FF63E973216839ULL, 0x0DABA24C8158D6FEULL, 0x6498AD916503B9F1ULL, 
            0x25B561C8CF39B074ULL, 0x1D9D8AC879E9DF13ULL, 0xD148006B7999A489ULL, 0xCBD0D3D7D25ECD47ULL, 
            0x10F9611E66A8555CULL, 0xF337135902BCFF4BULL, 0xD2FB19F3DB5C0811ULL, 0xC52B874458674893ULL, 
            0x24A457FE938522AAULL, 0x9A003F054CA69660ULL, 0x949FEB7B531D0DCCULL, 0x27D92AE8F4D39207ULL, 
            0x937267345591ECFBULL, 0x8CBF9A665D203262ULL, 0x993E2A18B7705C62ULL, 0x006292E255BC2BFCULL, 
            0x2EBC5FF4A9E32EF1ULL, 0x7CF17059C5125F4DULL, 0x8A31A3FD484DCF61ULL, 0x4989FFC9BB0EEFA8ULL, 
            0xD33B17D94C1C2E42ULL, 0x35EE9B1E7D056639ULL, 0x784AAFF5574004F1ULL, 0x2449A4911ED65967ULL
        },
        {
            0x30C99A41B5059EBAULL, 0xAC6971B68729678FULL, 0xCDC040CB937678A4ULL, 0x5BBF585588133139ULL, 
            0x9B2CFAEC45773547ULL, 0x591D3F2C46787C1CULL, 0x3F6FDAC2A6BBDDFCULL, 0x07754AE85503B265ULL, 
            0x9686E31A6707E3E2ULL, 0xE68162FC169F2B76ULL, 0x3A9D75AD71762E80ULL, 0x85488FC3C7938ABDULL, 
            0x7134398E76FEBDBBULL, 0xAA3B94522867E752ULL, 0x7EE269D5A40D8C80ULL, 0x65256B5FA336BC8EULL, 
            0x0FD0D085F6F3F6A3ULL, 0xB601E820934FE847ULL, 0x2FED31AFD8FC696FULL, 0xDE9AB782D97F462FULL, 
            0x1876BDDD91CF4DF9ULL, 0x52A146FF4CAB6C67ULL, 0x4B0C23A08B0FA0EBULL, 0xB7CE188A081D81CCULL, 
            0x4061BF8EAD92545BULL, 0xBFC91FD82108252AULL, 0x4872D2B59BAF741AULL, 0x5FAC8D2298B857FAULL, 
            0xB657AAC3C307EF31ULL, 0x0768BF8CB53FAC54ULL, 0x386EF50C849EB61CULL, 0x5D8924EF8BF76C91ULL
        },
        {
            0x428DA784A9FE97ABULL, 0xD1AD0C757E34815FULL, 0xC4DA69BBD6B7DBD0ULL, 0x8A3BBE2474BE3C4EULL, 
            0xA807F8B3B1AD186DULL, 0xC901F29893AB29F5ULL, 0x9619E44EAD8AE999ULL, 0x94440B512BC2C61FULL, 
            0x5C9068F93E35C35BULL, 0x331564375754D0D4ULL, 0x9E3A3B5F053C07FDULL, 0xCEE37120C2BA21AFULL, 
            0xAFBF61ECFBE57BBEULL, 0x877BF939EA23E270ULL, 0x64F253D4E4B79328ULL, 0x74787878AC25F5ABULL, 
            0x4117E02CEDD7262FULL, 0xF607B0AC994C4C8BULL, 0x3C3D5462856C0C33ULL, 0xA549BB6C7608CC66ULL, 
            0x39FB4BB49263F97CULL, 0x55EE7EF1143D5A94ULL, 0x05BE589CAFB91414ULL, 0x467DA47F62CBB17DULL, 
            0x3EFB7ED31ED2B44DULL, 0xAC15A6F91E55FEB5ULL, 0xB1A820F4F76BC1EEULL, 0x5BA7F924EF4FD32CULL, 
            0x928E180BFB324813ULL, 0x331EB2D6A60C8790ULL, 0x4BE1DE86C8C363B6ULL, 0x9D6BF5D605A38309ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Naos::kPhaseAConstants = {
    0x411F5C8083092985ULL,
    0x30AB373A2E3D3EFEULL,
    0x55CA78ABD9D22B49ULL,
    0x411F5C8083092985ULL,
    0x30AB373A2E3D3EFEULL,
    0x55CA78ABD9D22B49ULL,
    0xE06D9B7B556EB15AULL,
    0xD772426849F6D4D6ULL,
    0x37,
    0xBC,
    0x23,
    0xB8,
    0xBD,
    0xE2,
    0x86,
    0x9B
};

const TwistDomainSaltSet TwistExpander_Naos::kPhaseBSalts = {
    {
        {
            0x69DC1E4A0DD865A2ULL, 0x678EB911C0AC4320ULL, 0xA29BD10B0FA0BEB4ULL, 0x642E7D12DAFB1614ULL, 
            0x5B72868746762B3EULL, 0x575FC2CC9BFE243AULL, 0x46D9ECACE7AA2170ULL, 0xACA6D0C7977B5E89ULL, 
            0x3CDD7E65B44A668EULL, 0x83FA087E222D9736ULL, 0xFAA49BC49E387B92ULL, 0x9E7F67BA0FE92038ULL, 
            0x9202260BEDBA9FCEULL, 0x49D0A8DD46A85CFDULL, 0x58C73CC1096B4E36ULL, 0x2FFEC3A3E60B7390ULL, 
            0x0793C088C867FBF0ULL, 0x601CF4FACD89A955ULL, 0xD61EC5399FD2EA81ULL, 0x8038791EAAFA93FFULL, 
            0x4D4FB09F556C6786ULL, 0xAB753F186E4F3B5BULL, 0x78BFC6AC792FCD0FULL, 0xBDCC2A13B36A902EULL, 
            0x074B51C8AA206E6AULL, 0x9656E20E782D8D48ULL, 0xCE38F18D2D1A4B09ULL, 0xE4598A9C9ED5628FULL, 
            0xD01616A4A30D74A7ULL, 0xAC1DF1565D859C4BULL, 0x48F1099D9EE4A757ULL, 0x652C32AB4C8611E2ULL
        },
        {
            0x82E4933F2156BB31ULL, 0x6B87913273094B3FULL, 0xDC6E0C04717E477BULL, 0x96494601D68B1040ULL, 
            0x4B74BDEF65A1B23FULL, 0x28E144CDB3D573B7ULL, 0xF04CB41794184955ULL, 0x958033D6333AAA59ULL, 
            0x09FB8C931D57E907ULL, 0x4F5FDDC1FEE730A8ULL, 0x64B45DED0933F1B7ULL, 0x8AAEE7C1225D88BEULL, 
            0x490A85750B0D3D4AULL, 0xC4F0A4CB6B183661ULL, 0x94D23B467452EFB9ULL, 0x2A86211435DE44A6ULL, 
            0xA835B59C84A36C03ULL, 0x0D8734287B14D36EULL, 0xEDA671ED1BD67C91ULL, 0x1442E658D8604189ULL, 
            0x85BB8417E5C3A865ULL, 0x0A8DCD35F1B351D0ULL, 0x019B09CF4539C64DULL, 0xCF1D2CC1F4A226D7ULL, 
            0x2763CD4F25FB4A8DULL, 0xEEB7F5729EB97A3FULL, 0x0E931663A5701802ULL, 0xD1F10EDD4AC5BBB3ULL, 
            0x2D3F779A202AA948ULL, 0xAB4550BFF3128EC9ULL, 0xFB216E783997C4BFULL, 0x21F99D1C89D106DDULL
        },
        {
            0xFE1404C20C41DFA3ULL, 0x1371597EF061D5B8ULL, 0xF6C82C2DC0797FB4ULL, 0x44B0B3E2EE4CBD37ULL, 
            0x6EF460C14B58932FULL, 0x62D26AAD4403F4F1ULL, 0x5986C072935A113BULL, 0xE2DB3A139300D626ULL, 
            0x77C3FBE1023B5C53ULL, 0xAA7BF7AA75CAF815ULL, 0x5C5BA4B54DE62DA7ULL, 0x7DE48A5F2A9B3C07ULL, 
            0xE3CD898BC831CC7EULL, 0x5FAC68D7F06851D6ULL, 0x93014CC12F856D83ULL, 0xC45D9F9A522371B2ULL, 
            0xF1D3005E52C28019ULL, 0xC8DE7C41D4CD16A8ULL, 0x985F60DE3E4A9143ULL, 0xB4EF2EFFC25D37B7ULL, 
            0x74C99DD83D4F1D6FULL, 0x39498167E7882D76ULL, 0x8175984EBBE39299ULL, 0x6DBDEA5E213E3762ULL, 
            0x4D46DC045F6E9D36ULL, 0x1A93D392DDD967C2ULL, 0xE7C3A679471A1E56ULL, 0xC9A57DC8ABBA6FBBULL, 
            0xC504A1BF2D93C401ULL, 0x0BAB8F4066AB714CULL, 0x945CB16EAB70EC84ULL, 0xA2E235ADA2265265ULL
        },
        {
            0xB18D88C04E844480ULL, 0x8A2CBF8726654B60ULL, 0xFDD8D22ABE1F170EULL, 0x367E83E885694E39ULL, 
            0xECDE3441CCE20222ULL, 0x4FE0A19E79E15404ULL, 0xBB81E4A13222B4D1ULL, 0x9527DB7D09EDAE41ULL, 
            0x12AB6FD98CFCA9ECULL, 0xBBDB3160FC69139AULL, 0x38940BD31636F73BULL, 0x13A58897646AC79DULL, 
            0xDAA888246F67945BULL, 0x4DF7C87305FF1AE0ULL, 0x7220855B664FE5E9ULL, 0x2B5E122A522BF054ULL, 
            0x7C12B392FF1A6F93ULL, 0x28D2D704BF0E859FULL, 0xD3952694ADFB8B2AULL, 0xCDB1EB5ADCBA47F5ULL, 
            0xFD247D194D6FEDE5ULL, 0xAC2F292FD193AE9AULL, 0xEEBB3D530441B230ULL, 0x278BEDCF32595469ULL, 
            0x440A26BAE2B9118DULL, 0xD2DB480361DB3D51ULL, 0x592D855CA9F36AECULL, 0x7076F739F983B124ULL, 
            0x971B63E56D8D5E43ULL, 0xC19D8BD9DC24EFF6ULL, 0x0E9D0845FA7BE6ECULL, 0xEDE5CD7D00285E28ULL
        },
        {
            0xE5F3E8DCF1D694BEULL, 0x2BE0A3504BCFCA58ULL, 0x9E284F9573AAA8C7ULL, 0x7F027DE8113BDF06ULL, 
            0x8EE13ACE8C7B11EFULL, 0x16475801D5B5BDD0ULL, 0x76EFA637659A60FBULL, 0xD743042451CA9EC8ULL, 
            0x9EDDBD629E171CE4ULL, 0xA13E2D4C58DE2364ULL, 0xF73CD6454C9CE645ULL, 0xC73FF199858AC58AULL, 
            0xED459771959FA2D8ULL, 0xC6574288D2299695ULL, 0x9200817568341B45ULL, 0xD2877E9C8539B64BULL, 
            0x22CE3CB3D694E8F0ULL, 0x19E1B8E931F350EEULL, 0x8BEB0D771D1D735EULL, 0x623053674DE1C0A7ULL, 
            0xB5B68B7D7298E695ULL, 0x962D72DE6B043B37ULL, 0x02E6585FE1F93CF3ULL, 0xDBF9C2A8857C2628ULL, 
            0xFC9F9AF4AC4F2F88ULL, 0x82F3B8DE4AE207B9ULL, 0x70227A6E454FCBA5ULL, 0xE52CCE7CC63AB28FULL, 
            0xCD12C1BFB027A009ULL, 0x6DC138A61AE5544FULL, 0xDB0F7EC85CC529D1ULL, 0x5C4D51151D49F9D6ULL
        },
        {
            0xFE68B521347DF42CULL, 0x5B0BBBA1767158AFULL, 0x28FC0BF0C86E5B36ULL, 0x4269E6D340963954ULL, 
            0xDA47A7676DA9F473ULL, 0xF921832B0A1A4C0EULL, 0x205F404D1CA57DF4ULL, 0xC0090FE43FE62726ULL, 
            0x62E17AD04B3FD5A7ULL, 0xAC5BAE0BC7025761ULL, 0xDD87288B939140EDULL, 0xEC103975F3CFD317ULL, 
            0x2F8104DB568E6127ULL, 0x74E8B633DA9C7415ULL, 0x274A8C0DFC109A96ULL, 0x7220041ACFE9B779ULL, 
            0xCD307B078C5AA96DULL, 0x6EECA57FA40A102BULL, 0x9793972E198B9A1FULL, 0x865785520713BFB1ULL, 
            0x7881B36C06A1F498ULL, 0x548B702CAF833F88ULL, 0x501BE73104DFF76EULL, 0x27A4335E02B56DAEULL, 
            0x1331C8F612BC3C5EULL, 0x30A0B26EAC2DCF53ULL, 0xF1AD8CA00C9B50A6ULL, 0x989338FB38846AB4ULL, 
            0x004995695B9FF8B1ULL, 0x5C36278B1CFF78C4ULL, 0xB87C9BD8D3CC92C2ULL, 0xB0EA5647884E0FEDULL
        }
    },
    {
        {
            0x8EC338D935769374ULL, 0xC17B4B16357C73E8ULL, 0xA7548F731D1510ABULL, 0xBDC30AB4FDBC20E3ULL, 
            0xE37CE100DCAA5222ULL, 0xBFD315DEF85E86B1ULL, 0x634EED8E8E528B8CULL, 0x0180C186CABDEDAFULL, 
            0xC198B96756ECAA63ULL, 0xB902D514D8B39C76ULL, 0x1557C2A8E7D0704FULL, 0x15B32BE3F387DF3EULL, 
            0x96FAA7BB2C652D05ULL, 0x13F9D90E228A70CEULL, 0xECBEB096ADA2DB8FULL, 0x134CAA82BC8C88A0ULL, 
            0x578D3786D7191CF3ULL, 0xA1F9AB4ABBF5A01DULL, 0xC78547E796361232ULL, 0x9FEA5B8F284D9EC8ULL, 
            0x11C6761DCF637B4BULL, 0xBB282928870743F5ULL, 0xC1249D2F3CAFC58DULL, 0x8C0A4518F72DE05CULL, 
            0x52A86324D809ED2CULL, 0x3BF0FBC747606F1FULL, 0x89FFC07ABABD6ADFULL, 0xA7C4410CB5B780A5ULL, 
            0x0E0F95D6C542759DULL, 0xE4C0D9C6F0D73143ULL, 0x3BB84BBA31047729ULL, 0x50D1AF137FC05E0EULL
        },
        {
            0x6BFA559978EEC0E6ULL, 0xFE24B64DD8824E0EULL, 0xD9DB3F95B382954DULL, 0x754871283D4EF11EULL, 
            0xFF9C0F478EE6A426ULL, 0x890C4F552DCD1036ULL, 0x88D6725F9A42549DULL, 0x868A19BA446CCEB3ULL, 
            0x89DB3E357F590272ULL, 0xA8B7BFB9AC5DB621ULL, 0xA20A90234226DDA2ULL, 0xF51B0372F0CB1C06ULL, 
            0x2D43670236B0698BULL, 0xB2BC70A03B30F232ULL, 0x3DC9E60F116830E4ULL, 0xC72D80AAEB336DC5ULL, 
            0x2CA2B7947C45F702ULL, 0x100A932F2EC74EB1ULL, 0xFC7ACDDBFF1080A2ULL, 0x9C35CBBA6CD2B02EULL, 
            0xA6E11087D125201CULL, 0xACE429FB96E53D4FULL, 0x17D7DFDC4F971397ULL, 0x5FCD9B7D77631916ULL, 
            0xD0D2F3400BEC878AULL, 0x600717EF3BFE1EE2ULL, 0xEB721C66D0602D32ULL, 0xA3D7E345178C41C8ULL, 
            0x32F5D76CFF4C7E5DULL, 0xAA2490B7A75C7BBDULL, 0xB48A6724450FCB1BULL, 0x0FF66128E2B731D6ULL
        },
        {
            0xB48EC7DDAF01E67CULL, 0xB9E75612717CBA65ULL, 0xF182A9C77E9F4175ULL, 0x895848512979CED6ULL, 
            0x1E8D6476213BA237ULL, 0xDE578A3D30A2DBFDULL, 0x6A00044F915C0EA5ULL, 0xE36BC0E097F4F280ULL, 
            0x725F03B1096759C9ULL, 0xD5729563B7119D47ULL, 0x535980B12A17A466ULL, 0x2130CB733A5AC32FULL, 
            0xF57062B8488B5594ULL, 0xD0F2B855A72C8589ULL, 0x1934E2523662F7D8ULL, 0xF41A414FB47DA885ULL, 
            0x61352D93316DDD52ULL, 0x9FE63113509B335AULL, 0xA82E37DDA1D59C35ULL, 0xE4D06990AB79B21CULL, 
            0xAABBCE00A0CB26C8ULL, 0xB79EED7A17344A26ULL, 0x2DC8A87D4226D42FULL, 0x0B2DA70366D4A7D4ULL, 
            0xD23AD35E93FAB6D7ULL, 0xBE2B0C003DF34553ULL, 0x7EF6D9B0F1D5C143ULL, 0xA4704A9CA38F5070ULL, 
            0x92775AB58773C687ULL, 0x3D3DDF0C18985DBEULL, 0xAB9ED49372EE188AULL, 0x62C94A23F910C671ULL
        },
        {
            0xD72E9A3DC404FC81ULL, 0x42C376EDEDA368B9ULL, 0x4D58DF4BF6F0E6FCULL, 0xBEE1E5936252A9DEULL, 
            0x1D8F5AB746587F90ULL, 0xAD96A8AB0A38A3ABULL, 0x6D6C11EB834BB775ULL, 0xB363760B1DA1D4C0ULL, 
            0x45AABB9DB435E071ULL, 0x07E5F06E0FFC0636ULL, 0xBAD6E6448E809D9EULL, 0x272C215ECE263249ULL, 
            0xE23F99F077DC40E4ULL, 0x371112F22331FD95ULL, 0x34B9995A71225593ULL, 0xBD1FCA46FB4E84DBULL, 
            0x9BC0052F3D31CA8FULL, 0x9A93A1CDD64061C2ULL, 0xADFC040F896249E1ULL, 0xE0137D9FDC79F936ULL, 
            0xB0B56087E14F9045ULL, 0x9900E7CBB8202CA5ULL, 0x6DE1CD1615FDA593ULL, 0x96383C24A0234275ULL, 
            0x6574EBAE5D8F7AF4ULL, 0x9BC0CCC66F9A0207ULL, 0x5174CE0FA426DF18ULL, 0xE1BEB0EFCC0DB8D8ULL, 
            0xCE04828257EF054BULL, 0x03C3360FA2DFB398ULL, 0xB232A5BBEBF0A9B9ULL, 0x0BA1267ACEA8C9ABULL
        },
        {
            0x148EC9722A682B64ULL, 0xB69A5C2BCA686680ULL, 0x410102B0C18A08A8ULL, 0xD79AC3CA01373EADULL, 
            0x30AA15A43490CC54ULL, 0x3E8A3867A8969F29ULL, 0x4F141E066308E0C8ULL, 0x18D17C5424549F71ULL, 
            0xAC187BB193A4533AULL, 0x376F7DD3F710A4D4ULL, 0x4FA511C8E80404BDULL, 0xDEA5A64207505CFDULL, 
            0xA31274AA5E70E1FAULL, 0xB1443AE2FFEB0600ULL, 0xF555AA5F5CAF8E5AULL, 0xDCE1F0537B355B57ULL, 
            0x7C194436EB5624D7ULL, 0x7875BABC9828F677ULL, 0xE0D010F59FF08F89ULL, 0xE51B874EF9C88633ULL, 
            0xB1F9966D9877F8BDULL, 0x7F8377179E21F95FULL, 0x31F92237266DB970ULL, 0x528A959EA834111EULL, 
            0xDA553DAB2B53EDF5ULL, 0xEB70620A61B13C9BULL, 0xA5AE709A9AD1A5AFULL, 0xE1E187ACEA8B7A35ULL, 
            0xB8704593A73DCFCEULL, 0x195535B7E155B943ULL, 0x793EB53F705EBD99ULL, 0xC9AC42704BB1A45BULL
        },
        {
            0xA4F601EB110A93F5ULL, 0x95395983AF1AC302ULL, 0xA673B741268B7B92ULL, 0x220C07D128D7E922ULL, 
            0x30A936086B33967BULL, 0xC8CB2477669114E1ULL, 0x5DB0461A09712FEDULL, 0x30089E85F9903934ULL, 
            0xF369AF0D3C115078ULL, 0x3378E6F38B20261EULL, 0x62562B659FE60F1BULL, 0xB4340A2958ABA1E3ULL, 
            0x05D3E96196001B00ULL, 0xD52E08B550A4CC76ULL, 0x2798506034795461ULL, 0x02E8C7DA9742DD2AULL, 
            0x872EC00AFC87169CULL, 0x7561E4EA7DB986EAULL, 0x31F17AC49AFF8182ULL, 0xCDB8C41A49A5BE8DULL, 
            0x91DCDD5C79EE6247ULL, 0x13AF1B23B6B756D6ULL, 0xA669502A1E8F1260ULL, 0x7966471CC508FA79ULL, 
            0x55D0003AAC0703A8ULL, 0x80DFB4D4B9706451ULL, 0xE3872F6092B9BEA0ULL, 0x256363B7E555EAD2ULL, 
            0xCA00737930F42699ULL, 0xA4735EFEEC283694ULL, 0x8332F90025397C5EULL, 0x469562788CFAC15FULL
        }
    },
    {
        {
            0xBD6BE6094927C952ULL, 0xC2E9F2C125E74599ULL, 0xE89C27E7A6E4D14AULL, 0xD938FFCDD70FFE84ULL, 
            0x4D05090D91065B19ULL, 0x5E3D7F2CF465C2B2ULL, 0x181BE9594DB87BF6ULL, 0x5E363CDB4C386005ULL, 
            0xD5777B3DB54C6FEBULL, 0xFD605FCA3C22717FULL, 0x8EFC3A411634D858ULL, 0x14F9D430BD200A55ULL, 
            0x9FE03CAEC76458C4ULL, 0x66285881FD7ED95AULL, 0xDCA8CA468ACBFC9DULL, 0xE04CC01F739952CEULL, 
            0x83D0F50F69C3FB16ULL, 0x98E756831E0EA1D7ULL, 0xA75F8F026AFDD5C4ULL, 0x7C1E7F16C58BF8ACULL, 
            0xE0D061767AF0FD98ULL, 0x688BC4B2ACF7099EULL, 0x26F766DF381599B0ULL, 0x3E508E104EA2399BULL, 
            0x06D9D8A0F9BEA705ULL, 0x06A59C3D3E073065ULL, 0xC00DA61E6528354BULL, 0x75DE7EDCBEF3D5A6ULL, 
            0x98F4880F4B054398ULL, 0x987D9F26DA59BF70ULL, 0xC9D287455E888E39ULL, 0x6E59F1828889849AULL
        },
        {
            0x40945AEF3753883FULL, 0xC3ACF51DFA47BCC1ULL, 0x07D98232F717D836ULL, 0x3CC16FF430FDD840ULL, 
            0x3FA7D3707DACF087ULL, 0x11B72D6D4AC23922ULL, 0x139B088ECEDFBABAULL, 0xEC74CCE01AA5C00FULL, 
            0xC92D1A19D387826FULL, 0xD90AFECD6EDE9B26ULL, 0x59FD7CB264038E99ULL, 0x5B993FC386A4B91AULL, 
            0xE91B266DABC3D455ULL, 0xFFC36B709802993DULL, 0x9D72D7CC4AF16064ULL, 0x40C400B1EAA91DE2ULL, 
            0xA062170CE12B6B2CULL, 0xEC6DF29F68CB9289ULL, 0x803FF415D6478CC0ULL, 0x71196D46A8B816C2ULL, 
            0xA30DA4C7FECDE452ULL, 0x33F5E650A5A1942FULL, 0xBFD0EDADF8662D01ULL, 0x66A28F8A7179BD49ULL, 
            0x0B9BD1F314C51B5AULL, 0xD0E845FDE4313E9AULL, 0xA45CE9FC4A979A6AULL, 0x80DC2950F5817EE9ULL, 
            0x418988D9D1460875ULL, 0x0A15637A85382C1AULL, 0xC8CEA02583941EA3ULL, 0xBEED66EA90B7D018ULL
        },
        {
            0xC2886BC7FBE4B13CULL, 0xD6652C690DCED3C6ULL, 0x76986EBCFCF9861AULL, 0xE14BB7F06B25CB49ULL, 
            0x393ECF5C844CE7EFULL, 0x5070AB0E6B5EE615ULL, 0x015258BF8B27FB7BULL, 0x331079798D447A6DULL, 
            0xF518314D9A3D3D77ULL, 0x05EF5A96ECDCCD6CULL, 0x2A09256E14A831B1ULL, 0x7781C6502E7E4BA8ULL, 
            0xBB1C9D68D0892136ULL, 0x99F5ED74DD38AA83ULL, 0x71ECC8F3837EBFBDULL, 0x83FCBC33158A1FCEULL, 
            0x3C96C82CA7EF16E4ULL, 0x21CA4B61743F4179ULL, 0xE0CEC7FEA480C9BBULL, 0xCF600746C8EB1EAFULL, 
            0xC6EED6F8025F3D97ULL, 0xDC908B717121B31FULL, 0xAFF8B9E01329BA58ULL, 0xCEE10A268859FE49ULL, 
            0x6C8DE247F326BD43ULL, 0xEA80EC1D6CF255DDULL, 0x998599AE13A64A4CULL, 0x37D2EEF067E66F30ULL, 
            0x30CF62076CE8EFCCULL, 0xA1C3D6C37A9FEAEBULL, 0xF693264FBD714BA1ULL, 0xE1A0B842503F59FBULL
        },
        {
            0x2A5A998115363FD2ULL, 0xA5803E2FD118DBF3ULL, 0x34FE42E82EE1CC97ULL, 0xEB224AE928A1FF8FULL, 
            0x0A583FB1A3A543A4ULL, 0xA94E143F7CBF7BC1ULL, 0x6FFADA652405340FULL, 0x9EFB23629D163F14ULL, 
            0x496F4DBCE933972EULL, 0xF6309DE4C19F7890ULL, 0x44ADEEEE5A09187BULL, 0x6EAFA64154179F5DULL, 
            0xE078AB6672AE5749ULL, 0xE8C7AEF017209EC0ULL, 0x7907E654D2E55DF3ULL, 0x89C9AC1EB2CAA689ULL, 
            0x0542875BB513CF04ULL, 0x088168C48019C92BULL, 0x4B60915709E54BA0ULL, 0xC632E0C8A22E28AAULL, 
            0x643CAA00A2707B7CULL, 0x1D1F989DF5A979B3ULL, 0xE31CC27C1C27829AULL, 0x2410E2EB902FDF81ULL, 
            0xE681F2FF95734608ULL, 0x684667B433C282DBULL, 0xEBB08D3EE4162BD4ULL, 0x753205A2E497FDEEULL, 
            0xA8285430B4F90BA6ULL, 0xF39A783CDDE0C135ULL, 0x31D6604405B05486ULL, 0x1CA17333B51F4208ULL
        },
        {
            0x1479C645216A4AA9ULL, 0x0074FCD7EA999042ULL, 0x8F3A40AEE705CA72ULL, 0x23C0C3ED5BDB8622ULL, 
            0xB55209F577D740E8ULL, 0xC87D761048502A07ULL, 0xCD6ED87DC5B912F4ULL, 0xB5E65EAE5C28E61FULL, 
            0x8A96DF4D2C5FA84BULL, 0x310D53FD17FF5C6AULL, 0x0CBC3BDAF340BB42ULL, 0x22014918A6BB0D74ULL, 
            0xC48E966BA20A8C7EULL, 0x30EEA4F12F6D2AD1ULL, 0x49245D5D5691C22FULL, 0x57F152F17F69EFA6ULL, 
            0xC8762BB2A61BFC9CULL, 0x94C1105D584279C0ULL, 0x816A1B52E90B3FE3ULL, 0x766511C21288C2D7ULL, 
            0x1FCA3DA62D47E714ULL, 0x7E1688233765E919ULL, 0xA158C21A287CB2FBULL, 0xC90DD43D3ACFAAE6ULL, 
            0xB3D36BD8BDD77322ULL, 0x0B4179525D5F4256ULL, 0x952FA00926BF360BULL, 0xF2DEB2143D9311A4ULL, 
            0x7CC192BD765E631FULL, 0x9120216AF312BD4EULL, 0xA90F713CFA357077ULL, 0x92E5742FCB7B2DF5ULL
        },
        {
            0xD77F3E8A316E6E4EULL, 0xD5151B6A6A5ABA27ULL, 0xCA63D547D8FB4C6FULL, 0x2F466003DD2A71FAULL, 
            0x2440DBDC86E245F9ULL, 0x31A239E4660B54BFULL, 0xD360EC801EED7275ULL, 0x9F615B0240E95C44ULL, 
            0xCD7819A00EBBF1A7ULL, 0x017152D2B3B21873ULL, 0x4BD3618E33ACA020ULL, 0xE363A079EABE8954ULL, 
            0x01B21D8245D99F0FULL, 0x57942C90C2BA142CULL, 0xEF9F3223CA0ABDA5ULL, 0xB0871FEA73F77038ULL, 
            0x07863C0AF0339742ULL, 0x95027D85D1BBF7E4ULL, 0x07AD7D74671B1292ULL, 0x19E40F568E20044CULL, 
            0xA103399946A3245AULL, 0xAA7B458FC01E6C9CULL, 0x5A64A1C9081C4D1DULL, 0x1F1BEC5DD8AC4C2BULL, 
            0xCB30C319518D2724ULL, 0x1BC8D64A53405CCFULL, 0xE526B2EE4000ED18ULL, 0xDF5818F5E4368842ULL, 
            0x4CB0D73398500238ULL, 0xCA8A02660A01D534ULL, 0x89A18CA5E5B24DBEULL, 0xA844910B98F98D23ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Naos::kPhaseBConstants = {
    0xEBDA7369CA3357F8ULL,
    0x0569F3941F700D96ULL,
    0x5C616E95434E12E1ULL,
    0xEBDA7369CA3357F8ULL,
    0x0569F3941F700D96ULL,
    0x5C616E95434E12E1ULL,
    0x8FA7CB9BAB56E2ABULL,
    0xAF4FAF3B4CB06839ULL,
    0xFA,
    0x87,
    0x37,
    0xD8,
    0x1A,
    0x29,
    0x28,
    0xD6
};

const TwistDomainSaltSet TwistExpander_Naos::kPhaseCSalts = {
    {
        {
            0x3A52DEECF141A121ULL, 0xEE640B38150A89C0ULL, 0x497642BD3DEEE66BULL, 0xB3761F98DAE23E60ULL, 
            0xA96A704A5BCEACF9ULL, 0xD6773CD9636F26FDULL, 0x0A812D57C9676562ULL, 0x32A7DCBD724FF50DULL, 
            0x91AB73515DEDA113ULL, 0xA9D1DFBFDECF94C9ULL, 0xAAEDD297B6F69A4AULL, 0xCB4D61EB50F9FCFDULL, 
            0xD6559B81A6EF3B60ULL, 0x055D1507864FFBA5ULL, 0xA9DC6024D04D0E32ULL, 0x587909EAF04BC0DEULL, 
            0xEFEA5D47F46B08E8ULL, 0x32334EFF3AAB333EULL, 0x10F6B769ACD32025ULL, 0x9D7CC51F45291E72ULL, 
            0x99E9A7DD6A63FAADULL, 0xAD3949A7123874F8ULL, 0x52595A0E215DB5B4ULL, 0x8DD237D135A1B6D1ULL, 
            0x536C3D941096DC49ULL, 0xCDE6FC93153617DEULL, 0xD2F88CDAE49D695DULL, 0x388DDDD50D605377ULL, 
            0xBAF203FE78CAB8D4ULL, 0xC4EDD593EB73147BULL, 0x8D97FAF6BE73226DULL, 0x1A80F31FC6589F87ULL
        },
        {
            0x8C3BCD7229AB3F2CULL, 0x63E0526669964D2DULL, 0x10A87C1F23B26EC9ULL, 0x09C7FC87E5D3EF52ULL, 
            0x8513DA775AEA394BULL, 0x8E62CEE052F9F7E6ULL, 0xD4845769D6CE7CDFULL, 0xEDDCC9F582298756ULL, 
            0x5F381428992E7B71ULL, 0xC3DFD323983FDC1AULL, 0xBDE55AB68E3ECF8AULL, 0x35686D19D803E8F4ULL, 
            0xE36FC4D9E524DD95ULL, 0x956F99DA1F96C2FEULL, 0xE9894A4CA410F22EULL, 0xCDC8C29EFE8AC747ULL, 
            0x536D3C51CFA2B159ULL, 0x96AA4514C30DD25BULL, 0x217CCFD881085C4FULL, 0x2C826A9F2ACF1E3BULL, 
            0x1F1AA3142D717481ULL, 0x51570B74FD899BEEULL, 0x37FEDB51C85922ADULL, 0xCBBDA5C0EF5EC2FFULL, 
            0x04F09FA9B4C1C8F9ULL, 0xBB994EEB4432862DULL, 0x221F25A60FB453AAULL, 0x06886595BDFFDB42ULL, 
            0xD0DFE24E44DE93F2ULL, 0xAA2C14142895CC27ULL, 0x3C621E28C834E338ULL, 0x3F381FB4325F4022ULL
        },
        {
            0xC5252639F016FF29ULL, 0x7FFDBE4F1820991FULL, 0x7C9D65E9D00A9B23ULL, 0xAF6BCC548471260DULL, 
            0x65EC3CB90CAA8F78ULL, 0xEF95378548179CA6ULL, 0x5ADE378E0287B469ULL, 0x3B1A79D8E923A6A7ULL, 
            0xD42DEA73512D18D7ULL, 0xE7D9113D9F15BF30ULL, 0x3A26EF1222294E38ULL, 0x48D6BB56D7B7CD2FULL, 
            0xDDAE800E7096CBBAULL, 0x0DAA0C91F20A04D1ULL, 0xBFE934DC651883BDULL, 0xDEADAC7876AAD518ULL, 
            0xC26472B71521EC14ULL, 0x8D3F3D69D02CC485ULL, 0x04AF8B876FF894A2ULL, 0x505F293A38FFE5DAULL, 
            0x478AA0E0B1477127ULL, 0x85F139ACEABA19ABULL, 0x2E53680B1BF9F3F8ULL, 0xF7B5642D63DB03FEULL, 
            0x879D24C9C82C1800ULL, 0x0CA4A6563276AB02ULL, 0xDA5DAB36B2797F71ULL, 0x80F01F296AEFCFB9ULL, 
            0x6B69651E3F5FC36BULL, 0xD08ED9049F1887E0ULL, 0x377111F8A10687F0ULL, 0xF195AE50054C3585ULL
        },
        {
            0x2F5A0C8058773E94ULL, 0x4A7049532857D5CCULL, 0x206464AD5C05922FULL, 0x2FC337D257210646ULL, 
            0xF5A1B2B3B0C7F8BBULL, 0x3CB6A18E35068414ULL, 0x9067B1CAD1510F21ULL, 0x44449F44790AAEE4ULL, 
            0x58CEF27BF6CE371CULL, 0xA5AAAD600524DA51ULL, 0xAD63AB40707ADB22ULL, 0x4132BF91CEC99EEBULL, 
            0x581360250A67113FULL, 0x1A6A32FC1EE5259FULL, 0xEED2951E190337D1ULL, 0xDD0F05272C9239AAULL, 
            0x42543CE0BACE75B2ULL, 0xE85DACC0CA04BA08ULL, 0x9CACE1BC97589A42ULL, 0x83D6CB435CF06D7EULL, 
            0x3FFCC1E5E40A5B68ULL, 0x0E4CF1D18EF4D93AULL, 0xF7887EB570E8C011ULL, 0xF888B35C3BAFE7F9ULL, 
            0x580374DDC757B59EULL, 0xBB108754BCD61FCFULL, 0x385109113487D13BULL, 0xE242B1EC99B2E157ULL, 
            0x7F9045D82FA29925ULL, 0x34F7AC9B400A2714ULL, 0x2599BC879BA8DD93ULL, 0x8689AA2E36164CD3ULL
        },
        {
            0xDCE9AB3EC417D9B1ULL, 0xE1DED16A15E88B30ULL, 0xB3829E6358B610B4ULL, 0x1CFE371F880781E7ULL, 
            0x4D2B05E33BCFB5A2ULL, 0xD44E060110D8FEE3ULL, 0x3B60456ECB59AE3AULL, 0x5DA5F0D0ADCB8C17ULL, 
            0x83A4D2125788654EULL, 0x0B6D16E29924161BULL, 0x1492259BD60D8486ULL, 0xE141190F1227F007ULL, 
            0xF5C921DDDBEA878EULL, 0xB0B57E3F61310C4FULL, 0x2C298DD8450C68FDULL, 0x516C05F608B3BF83ULL, 
            0xF45C96F7D008C65DULL, 0x52866824E50F3F38ULL, 0xA56077E2DC6467A5ULL, 0xB8CC2835F7E24958ULL, 
            0x7161C9E504C423B2ULL, 0xAA2E9449FC99CA9AULL, 0x3255038914CAC8FBULL, 0xE5B3320798D738A9ULL, 
            0x1DB45CBA5B5B6FD8ULL, 0x97CC41C9DBC65A9AULL, 0xCBB05C4FB730C720ULL, 0x924EC61A4F7A2806ULL, 
            0xD65ABCFB854037C6ULL, 0xD6DCEAED230142BDULL, 0xC2BA81D4C33DBFE6ULL, 0x6C845838AE6C0BF8ULL
        },
        {
            0x7A616FA8F6D6577AULL, 0xD94AF8FBD6130353ULL, 0xE78D27D02EFAB143ULL, 0x0D610F121DC441ECULL, 
            0xEC6E5C125DBC2382ULL, 0x5F7B6352F0082C26ULL, 0xF51096AB1C9E5717ULL, 0x026A9AFB6F443377ULL, 
            0xF1694DEDDE0D9F1EULL, 0x32208ACF5DEEFAEBULL, 0x3CB5E3EEE7355A62ULL, 0x23AF8BE4B3C69EA4ULL, 
            0x55320D20F51AF4C0ULL, 0x463B4C5C759B9F87ULL, 0xAF629D60D166A615ULL, 0xE272ABF0EC7084E1ULL, 
            0x3EA5053FAE518484ULL, 0x2EBEFF4474D46947ULL, 0xCABD31F305759654ULL, 0x771F92152C68E3F4ULL, 
            0xBDFBF0327BFCEC02ULL, 0xD2EF97F33AEF20EEULL, 0xE6448502ED46FF9AULL, 0x94C67CEED7CCF14DULL, 
            0xF9DA2EF3F1531526ULL, 0x1F40E0CBCE874206ULL, 0x473A908172CBD950ULL, 0x8698B274322EE1F8ULL, 
            0xBAB761114FC375B3ULL, 0xF9B89FF1DB06C5A4ULL, 0x7283D37B8F3A11C6ULL, 0x9A933FD4FC4362D9ULL
        }
    },
    {
        {
            0x23F79D4598AEF6B3ULL, 0xB8E6B3BA35985066ULL, 0x822CAC51A30D1372ULL, 0x386D33769F9F4C6AULL, 
            0x29E08BC640AD1CB4ULL, 0x24BDAFFE0A74903AULL, 0x2BA7DAFCAB531385ULL, 0x9F48C3088EE69F9CULL, 
            0x9D28612DD6E12D2DULL, 0xB2B14AB386D1A55CULL, 0x815B34CF086B0B44ULL, 0x4B8FCE03738C71DFULL, 
            0x40FB4529DE0E43C6ULL, 0x999FC6D844A9EA4DULL, 0x0EAE55E48683A311ULL, 0x2D157B876DF98107ULL, 
            0x2D9F36CAFA61178EULL, 0x84EC572B32860AA6ULL, 0x82347C1481412165ULL, 0x52ADF7C59E1050C5ULL, 
            0x28B7C9B733BF230FULL, 0xE4259914CD390D25ULL, 0xE23AC762F3B615C8ULL, 0xCDEAC53403ADCA21ULL, 
            0xAE3799082DE3D4D0ULL, 0xD2D2B316492BEAEDULL, 0x1CF95B91304DDA08ULL, 0xE703EDD38EBE0C69ULL, 
            0x15B33A2B446287DAULL, 0x1DCD9A14D04FA576ULL, 0xB4B41473B4562C50ULL, 0x664F844265986B1AULL
        },
        {
            0x777944BBAC3C0616ULL, 0x1C84C1834A8526ACULL, 0x6DA7CB254064205DULL, 0xB30D1F2BE6F9A901ULL, 
            0xC2A28491A3AC4AFDULL, 0x219BA730140DB82AULL, 0x6BC8AB46A1402F7EULL, 0xCD0AA5AEB42DFB9BULL, 
            0xD1AD29AF78FEC602ULL, 0xC3B841C1773F756FULL, 0x7864F3E51B1BC28AULL, 0xF4A7B436C9F324D7ULL, 
            0x72D467F6A8DCCB3DULL, 0x0D4147D7645C902FULL, 0x719D9B7FE3D322F4ULL, 0x763E89E16D3571BAULL, 
            0xCD564858D1904DDEULL, 0x57165A5B52837750ULL, 0x586DCD63A8AED59CULL, 0xB449C94231942F17ULL, 
            0x2B0A66958BD39C07ULL, 0x48C2CD5F02B236C8ULL, 0xCDBD297533F1A916ULL, 0xB671BA61475FE1FBULL, 
            0x01D94251DBC5641EULL, 0x2157CD3B606B1E03ULL, 0x7B94F294DE29ECA0ULL, 0xE8EB388C27D55FC4ULL, 
            0xDC5089F8EF1F3002ULL, 0x4DBDE7022D66984DULL, 0x92E4AC0DE4CC3FD2ULL, 0x1A9F1EE9D4BEAEBDULL
        },
        {
            0xD3BE3F873D219372ULL, 0xE929CEE7E1BBD54FULL, 0x1D0984A958E56E47ULL, 0x039438CE600785B2ULL, 
            0xE38D59D7EDEE7C43ULL, 0x7A7871660931E0EDULL, 0xA12E7D9A75E15386ULL, 0xC765599B0FD82055ULL, 
            0x177026348DB9CADBULL, 0x714A2C76D9583CEEULL, 0x0CDE7462637ECAD4ULL, 0xFEA3BED6486931B9ULL, 
            0xB7925A063C78C163ULL, 0x3E0F81847D0BA38EULL, 0xD99320A12E78132FULL, 0xF6D73AC402C757A5ULL, 
            0xCBF8B0CBFBED0DA7ULL, 0x12F1C36AAAE2F739ULL, 0x5BC9739E2582EC20ULL, 0x32CEC6EB642C0EC5ULL, 
            0x163145B6EFC20DA2ULL, 0x227B3BB8B7FE27B5ULL, 0xE03AB2FD1667AB64ULL, 0xF852E4EB93AA86BCULL, 
            0xD87369124D3A5A71ULL, 0x45B3C526DB3A8C41ULL, 0x710E8D97BEC0660BULL, 0x6015F99D6B8917BCULL, 
            0xFE7A7347921FC326ULL, 0x29BC7B96C487C7D8ULL, 0xE572785530CFC9CDULL, 0x8506B6C6222B6E05ULL
        },
        {
            0xD2722B3B4D72D57AULL, 0x09B30F7D980807D7ULL, 0x55C5FB17A25393D6ULL, 0xE91BC7C88573AA59ULL, 
            0x2D8ED9B184A3B7D7ULL, 0xA535BADEEE77C821ULL, 0x8538D61F14611FBFULL, 0x93DD0B1369185063ULL, 
            0x6C1B1999EC4FF640ULL, 0xA85B9275D5DA25D9ULL, 0xFB5FC786666AB567ULL, 0x54AFBDF397751341ULL, 
            0x4224ECC7AC432BE0ULL, 0xAACAC2F873BC6A7AULL, 0x0E2E4D7B7323568FULL, 0xFF144CB00207EDD1ULL, 
            0x6C89E3316F23D221ULL, 0x6CCFD7AFC878AF28ULL, 0xCC048C1C6ABD393FULL, 0xBE9602B2164CAC57ULL, 
            0x43858647131B43CDULL, 0x613F4F97B3D41708ULL, 0x5B7F4921B598C5D7ULL, 0x662F2BC568567D68ULL, 
            0xFEC6E3A362174AFEULL, 0xAF7695CA039D06DFULL, 0xE3ADD2EE862516F4ULL, 0xA7CF9178CA785600ULL, 
            0xBD156D8F7DD008EEULL, 0x0D6F2BD8F89CAADFULL, 0x94219335B5A0BEDAULL, 0x5C8C30EC896C5869ULL
        },
        {
            0xF30098591893C805ULL, 0x22DD9C369CC27D7BULL, 0x9499DB962204C36CULL, 0x6FA792CEB9511E7AULL, 
            0xB0B31A2CF95AEDA5ULL, 0x6BBAEB486F036BD8ULL, 0x9D54217620AEF9DFULL, 0x8CAFD9CEDC6D4D7CULL, 
            0xCE37AAD08613A1FFULL, 0x0AE74508D3141B4AULL, 0x051B3C91B09CD55AULL, 0x6643FA5149AACCBAULL, 
            0xD533D6FB3CF9A960ULL, 0xFA6E4C28EAB17CAEULL, 0x8740E49CBE14DD5EULL, 0xA1D03A736D51CF24ULL, 
            0x67490DAD698F0E35ULL, 0xEEABD0339D97C733ULL, 0xE13D718DD63351C2ULL, 0x3C3FB4F4CF8FF860ULL, 
            0x1D682D684941AF86ULL, 0x8A502A5240FDE729ULL, 0x0844851B2844B101ULL, 0x17ADCF5A596AF7C1ULL, 
            0x128EC169E4CA6D22ULL, 0xE24BADCF3E958C8EULL, 0x89BC55A65882BDAEULL, 0xCA8141C594074B32ULL, 
            0x250BA44B5EE7C6EBULL, 0x8A51469B4C263ADDULL, 0x440CC55EBAC42B28ULL, 0x26532BADFC5CE5A7ULL
        },
        {
            0xB9D32C50E4163D5BULL, 0xC94BEABB92356DD8ULL, 0xBE924E21863711A8ULL, 0x50229C51F9624363ULL, 
            0x2904362A08436565ULL, 0x1485DC747BAF68CFULL, 0x855970BEFEDC8E64ULL, 0x4B8C1FCB1F8EFBADULL, 
            0x8420F876E99A95C6ULL, 0x97704B4A6DBEF6D7ULL, 0xB58300FE6B56311AULL, 0xC0BA329314D1D9F2ULL, 
            0x9AA19D10983C1012ULL, 0xFE6CD7E3D2A098C0ULL, 0xF84F26B38CABB0E5ULL, 0xA5FF7499DF37A566ULL, 
            0x4B7DC80DA217FBF8ULL, 0xEC2B6A8D6EE571FEULL, 0xEDF4F9DECA08BC81ULL, 0x6B23A8EA0D684B00ULL, 
            0x26373622833ECD2DULL, 0xFBDB092F4B1DC68DULL, 0xCBD6B3BB53A64CD7ULL, 0x48AFF4DC1DF15DEFULL, 
            0xCD3EB9FDF3548726ULL, 0x993FE3A524EB3525ULL, 0x6F65B7EE933F333CULL, 0x34B18EAA4A6B9426ULL, 
            0xA0A3945581199328ULL, 0xB870555E03F2C750ULL, 0xCCC7669F9D11642FULL, 0xAB3ABD1F8B894AF7ULL
        }
    },
    {
        {
            0x54889292BF5D7128ULL, 0x955174482A1DE186ULL, 0xCB071DB7057594BEULL, 0x769F49805E4D2F90ULL, 
            0xB581DBAE2293DB0CULL, 0x55901EFE9A8EE1FCULL, 0xCD9BAA1881FA4794ULL, 0x6A570698805F2739ULL, 
            0x0E3355997F3C0B10ULL, 0x0043170D4EB47148ULL, 0x4D3220F9974670FEULL, 0x81F3B9E7868895BEULL, 
            0xAD3A58039B5CB0C5ULL, 0x40B018802C0BDD16ULL, 0x448224CEDD7957F6ULL, 0x2AA6D45FEC3AEB3EULL, 
            0xEC927A2E017FBCA2ULL, 0x219FF88CA12B9678ULL, 0xD8481029990A9F30ULL, 0xAE7877DE4E3D16B8ULL, 
            0x6C5A65E422B6DECAULL, 0x0E6620A78E2CEF8AULL, 0xF94E725F95035952ULL, 0x7117114E98BC760DULL, 
            0x47062874769F2935ULL, 0xE0978F46E24A2C9AULL, 0x740E716E080432CDULL, 0x130923D64F2FCA6AULL, 
            0x079DF343084F19C9ULL, 0x674C1A919491E565ULL, 0x94687BFCBF3A399BULL, 0x72416A5E9B0F54C1ULL
        },
        {
            0x8BA904F0627A3931ULL, 0x73028F7457D4B8E0ULL, 0xF0F184320FEA1E7DULL, 0xB547C2EF9A814EA3ULL, 
            0x6AEC343830711452ULL, 0x6179C6D7E62FDDF2ULL, 0xB264500F840C3812ULL, 0x32A8A3440DDEC791ULL, 
            0x8786493F3F0081CFULL, 0xC38ACF18E840F331ULL, 0xB94A26B9151CE5FFULL, 0x04C5A3CAE7EEB12EULL, 
            0x9DD4C201084DD3A7ULL, 0x7077EB6CBC2E8AC7ULL, 0x64EC5A97549255E0ULL, 0xA707AF2D99D2E8C1ULL, 
            0xDEF8BD39D301E6F1ULL, 0xEA901FBDDA731776ULL, 0xAC5DC4263B028518ULL, 0xA0171FBD2AED8590ULL, 
            0xA5C0B7FFA35073FEULL, 0x895EE2664D082140ULL, 0xA76DCEEE1EE2D4D0ULL, 0x517AEFDC982D2EB9ULL, 
            0x212DEA1C0A0647E1ULL, 0x1C1C6FE1CEF14886ULL, 0x330175951D595FA6ULL, 0xC4CFE9D461DB9F64ULL, 
            0x24CF7F1E1AEE66A7ULL, 0x529F8CE2B7446266ULL, 0xAE588C0E9C5417DFULL, 0xB5AD3527EC01FE10ULL
        },
        {
            0x1D70D3D78BE6E2BAULL, 0x5F34EDC1807DEEB2ULL, 0x940987DE73DFC020ULL, 0x56327FF453ABF32DULL, 
            0x31887FFB2E31805CULL, 0xECDDE69FCCAE2F51ULL, 0xBCE8E7F48E5CA853ULL, 0x5F1754FDA5376F65ULL, 
            0xE02F6A9963092373ULL, 0xE9B85B4810857159ULL, 0x9D5DA4EA09A87BE5ULL, 0x68F16939050DB3C3ULL, 
            0x6C98C36799FBDC10ULL, 0xA4058CC3BA017FBDULL, 0x64E4312C6BA35D87ULL, 0x48992F8C184CEFA5ULL, 
            0x53772B002CAA92B5ULL, 0x24BAFD50DA77E248ULL, 0x25053575AEB975D9ULL, 0xCA6A7C84A6102848ULL, 
            0xD35F58726CFBCD44ULL, 0x5B2BC89D3F28B9B6ULL, 0x5EF2220A1872EFE1ULL, 0xFB695438DC495A8CULL, 
            0x762B0CBCE816F14DULL, 0x6BFD7C7AC1B15747ULL, 0x44BE784F263E2B67ULL, 0xD7AF69F39DB87013ULL, 
            0x1F23B46BF29A2EC3ULL, 0x93EBB3CEEC93601EULL, 0xB63D192AEBF15EC2ULL, 0x005B65E836797B98ULL
        },
        {
            0xC31102087985AD12ULL, 0xD001A478161DD33AULL, 0xCB6C0639DF2905E1ULL, 0xEE5AE11313CE23F5ULL, 
            0xD3BA5F23E02A2350ULL, 0x6580D1B1EF80CAC5ULL, 0x5F996C4AE6167CB2ULL, 0x4A24E12637B7F8E5ULL, 
            0x2513DE37603A1798ULL, 0x56D20FAF596BF48FULL, 0x29887CF6D21D2BD4ULL, 0x28285F5DDA516FF8ULL, 
            0x96670D7A4D5546E6ULL, 0x7E521ABF6F442579ULL, 0xEFCA24FC1230C37EULL, 0x08CBB55D55622C93ULL, 
            0x10346A129D0F1CC0ULL, 0x8995EF830F4D1574ULL, 0x9C3F4FD379B34857ULL, 0xD212C0253D53D3CAULL, 
            0x43C0B13346CDA6DDULL, 0xD587099DA73EBBD1ULL, 0xE20BD1CF3687DB4BULL, 0x4EDFAF6C3D55C269ULL, 
            0x92F387EED7C2AE4FULL, 0x228CDEDF46CEB6E4ULL, 0xE3F641CB4F5FBF78ULL, 0x0E630086F35DF0AFULL, 
            0x30622297AA1E2CD4ULL, 0x3ED369CC93D2C4CCULL, 0xEBABD335BB867E14ULL, 0x3020A22603AFEEAFULL
        },
        {
            0xA7AB8394C72F7611ULL, 0x652B30D12F4CD7D5ULL, 0x29AB2EC295579E2AULL, 0x37F0CBEF19259FA6ULL, 
            0xACDE3E3E10531558ULL, 0xEE9B036AD3347B47ULL, 0x9155B542E7DE13D6ULL, 0xC22ACEBC90E69282ULL, 
            0xCABD3E4472E4A034ULL, 0x167C8B38FED715D3ULL, 0xA95954B0930EEE94ULL, 0x3FB063236DDD1997ULL, 
            0x37EBE9DCD25BA712ULL, 0xDDA6B3C87D84CAEDULL, 0x665F9630A7F04288ULL, 0x42601B4760FBAC5BULL, 
            0x4A0BB39B19A11184ULL, 0xD77BBD1C0D5D13B5ULL, 0x17BC24A226C35770ULL, 0x97806590F1319674ULL, 
            0xB8FFCF7AE6CE27ECULL, 0x2A347D292697E909ULL, 0x6BFF64E58ACEB913ULL, 0x6E5393F2591F2920ULL, 
            0x8D303C88B5B02ADAULL, 0x091544AC90E8B90DULL, 0x74772D76A6830866ULL, 0x8D97BB74E989BF30ULL, 
            0x6E0F30B190EC7849ULL, 0x375C9003958A8770ULL, 0xDF2D93718397CE09ULL, 0x2EF6816D3F183229ULL
        },
        {
            0xE469C752FAB898CEULL, 0xD7C59D38F65A9EFEULL, 0xFE717FAAC044155AULL, 0xEE7FDEC8C060DA79ULL, 
            0x90BD130BDAC52249ULL, 0xA96E81B9BBE1AD18ULL, 0x33D6228A479C4061ULL, 0x831855406A085665ULL, 
            0xE3D7EABBAA6A4FB0ULL, 0x86C97C7E1BA09D72ULL, 0x91A45247F3107F24ULL, 0xA6B2BC68722C38AEULL, 
            0xFF713D93259356ADULL, 0x4ECD80638E3193EDULL, 0x8F2BECF90257D2DEULL, 0xA161567A5119A36BULL, 
            0xBD36C116760A7C91ULL, 0x85A538A69E5B7A94ULL, 0xA0522F7B3C7D2CB4ULL, 0x6B23BA51BA2ED002ULL, 
            0x2C596B3E7771F064ULL, 0xCED3CE65B5F66917ULL, 0x65D3AD74D9B3A0ADULL, 0x645BF8C55936AB08ULL, 
            0x6C6C20B6142E23CEULL, 0x1E07A13EAC6D9C9DULL, 0xB821C6CA02134562ULL, 0x282F82E4A43ACC7AULL, 
            0x04D66A5859B57F4DULL, 0x7E96759B24814503ULL, 0x093666B83E460BAFULL, 0x6A937B5AB2BA14BFULL
        }
    }
};

const TwistDomainConstants TwistExpander_Naos::kPhaseCConstants = {
    0xFDE4CF0E7E842ABFULL,
    0x9ECE17A5C0F1FA36ULL,
    0x7F13D57B4ED2E31FULL,
    0xFDE4CF0E7E842ABFULL,
    0x9ECE17A5C0F1FA36ULL,
    0x7F13D57B4ED2E31FULL,
    0x009432091EC53191ULL,
    0xA5FACDC9AED3C01BULL,
    0x8B,
    0x07,
    0xC7,
    0x49,
    0xC0,
    0xDA,
    0x18,
    0xA3
};

const TwistDomainSaltSet TwistExpander_Naos::kPhaseDSalts = {
    {
        {
            0xCEDEC7D28C88567FULL, 0xFAE12F6C56EAA19AULL, 0xCA9A12D2DD95CDE1ULL, 0xA04E0C569A7CC9DEULL, 
            0x985779EB86360CD9ULL, 0x69966BE8D717B2A0ULL, 0xD1B38FA4BD4CB6C6ULL, 0x43BDB6F9205BC6C0ULL, 
            0x5C83780399BFC50EULL, 0x6D518FA0A555E2B8ULL, 0xB12B8C867E281BB2ULL, 0x45F6B9F5C6A14980ULL, 
            0xA6683BB2E5A714C0ULL, 0x07FFF1E05992DADBULL, 0x2D16646B945F39C3ULL, 0xABE0873393ABECDBULL, 
            0xCDAFFC3494517A99ULL, 0xAD9FFA5537D70FABULL, 0xA3C9AE0B0B94B7B2ULL, 0xFDDBFB7C1076AAD9ULL, 
            0x5F4A5BC5FCE5FB40ULL, 0xD99D48D597DB8852ULL, 0x86B7FFD25161F244ULL, 0x00ACFD878F384AD6ULL, 
            0x30515CBD8D64D48CULL, 0x5BE3516ABE6145C5ULL, 0xD02FA8BA38186BEFULL, 0x81C9C3E249E7550AULL, 
            0x0600D625D369C229ULL, 0x7462C9876D70D20AULL, 0x48606755E9B21AB1ULL, 0xE70ECEB0A825FA82ULL
        },
        {
            0x3B389E61444ABE76ULL, 0x9E8F98178398D6A1ULL, 0xEA77BEE26E089543ULL, 0xB087465E3AAA0D01ULL, 
            0x51969832A8F863DAULL, 0x0E8913165A5652C4ULL, 0xDE15C6CF763D014BULL, 0xD187148B2E73E56EULL, 
            0x619897C9C7D674C1ULL, 0x6BB9EC1CCDE09F58ULL, 0x793F15F510DB0159ULL, 0xEC759F6A23235052ULL, 
            0x1179BF91302194A2ULL, 0x245F0FFF46CC24E9ULL, 0x121E67C2A40A393AULL, 0x2CD7F4CB401F7A03ULL, 
            0x3DC080AE1BB889A7ULL, 0x1D43C699D88203C9ULL, 0x17451F731837077DULL, 0x5F4E93C65A0340F1ULL, 
            0x4A5429102A17C7A5ULL, 0xA7B3343F319A086DULL, 0xCE502416091BC218ULL, 0x23CE6499816B232CULL, 
            0x5C52C2A5CB0E59CEULL, 0x59C3960CA2A037A6ULL, 0x066FD126033AC65DULL, 0x690C4B6CB1339AEFULL, 
            0x6EAA3FFB2A47A858ULL, 0x97608ED2307EC028ULL, 0x2A9FFB08934EEC03ULL, 0x5CEBD315FA35A412ULL
        },
        {
            0xA785F995E4921DD3ULL, 0x50A50E6E32F335B7ULL, 0x39FDB53698B497F7ULL, 0xB9EC76641187560DULL, 
            0x8BCE9E942DDE7067ULL, 0x4C27D7D3DA13FFE8ULL, 0x5DA5A33C38FAC1BFULL, 0x31528F9D5589F92CULL, 
            0xB569D40C55E5B0EAULL, 0x2FD711F1DB6E0953ULL, 0x4D5AFAC86817030DULL, 0xB5EE1F10F2E4EE3BULL, 
            0x3394489FB87C27F9ULL, 0x5C68D74834099723ULL, 0xD4CD9B87546E1B4FULL, 0xA96F00951B0BD517ULL, 
            0x7A374954322FC82CULL, 0x0E37340E1AE5FD8BULL, 0x7B91D6B98A3DC40FULL, 0x3C6E80EFAD9DE296ULL, 
            0x91B611AE4E85852FULL, 0xD7E9703FCF57985AULL, 0xDEEBB84718D236D8ULL, 0xE32C6B6591402CA2ULL, 
            0xA181134F5BEC6123ULL, 0x3F919FEBF886FC65ULL, 0x33C07D3AE0A1E1A4ULL, 0xF1CDE10C6C8C0AF0ULL, 
            0x9A129CF736E7459CULL, 0x0D499A609F613951ULL, 0xA5BB0C079CD0F894ULL, 0xC95168670F56B773ULL
        },
        {
            0x1FD0FBF2BCF6B062ULL, 0xF5B7375DBFACCEA9ULL, 0x9796B9D316009E44ULL, 0x0EBB8CE72D83CE5EULL, 
            0xAC81888591B0BC20ULL, 0x659C2BE43D8EACD7ULL, 0x413D262BF7F5E0AEULL, 0xC5F01D3DCFC5BF43ULL, 
            0xBCE0A21A329D7C2EULL, 0xAA9E052EB8AB16A0ULL, 0x09B3B964BC1C131AULL, 0x71ECA5BFCF670721ULL, 
            0xAB01957EA63F5689ULL, 0x42C3F157E535EFD1ULL, 0x4E06C9209FF1AEFAULL, 0x201C98F684333DA6ULL, 
            0xF9F080AA0D2C1EB8ULL, 0xF31DE96DFD0F72AFULL, 0x48D4BBBDF0D9DD59ULL, 0xD79E9D392536CC68ULL, 
            0xE84EAAF00E5E2ED6ULL, 0x75BCBF3D4A8A37CDULL, 0x45481E40CC911C7BULL, 0x63069807319A53A9ULL, 
            0xC19EA7C1FADFA4D4ULL, 0x566169A1311288C7ULL, 0xBDA9E76CCEABE62FULL, 0x81D89B40FC675258ULL, 
            0x52CF59EACF81B26FULL, 0x4D029A6EC96B8E2AULL, 0xD8C7286C4E6FA86BULL, 0xDE495F65EDF3C966ULL
        },
        {
            0x079080F1C0A1EBAFULL, 0xB04DB0735A173124ULL, 0x7462ED8A0F94A693ULL, 0xD722B0E543CF015DULL, 
            0xACBE6A1A37658C5FULL, 0xBD74804FEBD6F17CULL, 0x395F008F9C9C0130ULL, 0x3EE1DAC7F337161EULL, 
            0xADCD73AC8792F315ULL, 0xDED793D7B06B3C0EULL, 0x6C0B88DE8C00B827ULL, 0xEFE515B2B2FD89ABULL, 
            0xDE3F8A1D738A470CULL, 0x1DF2F3D8AB2793ACULL, 0x8FC31881D1C22FB8ULL, 0x2C336264C6ADB873ULL, 
            0xE6B529A9C7ED33DEULL, 0xABCBD85C1EFF9B39ULL, 0x0CF7CF04E1DF390DULL, 0x8C839DA5A9CC7F15ULL, 
            0x2DC8F9A927C69595ULL, 0xC9CE2CAF6C3726DBULL, 0xDEC8CA74611448CAULL, 0xAFE5D78AB1380D5EULL, 
            0x93144A1EAF6C0BD9ULL, 0x01E1595C79ED4DF4ULL, 0x1CABC6B7028EA808ULL, 0x97555A966855C4B7ULL, 
            0x582194642C980904ULL, 0x3B7E09D998193706ULL, 0x0069C99ACC28AAADULL, 0x2FD01C1F520583ECULL
        },
        {
            0x63D0E78D985B1728ULL, 0x554EEB7E98130B5FULL, 0x1608F30322232AB0ULL, 0x2173A4F5C4F78BC1ULL, 
            0x7BB677AFB1D6A72CULL, 0x51B84610AED96A97ULL, 0x7AC6A758131F5D73ULL, 0xF348EF44B589C2F9ULL, 
            0x84E673EE85233F5BULL, 0xB26EBBDA627F5DA3ULL, 0xD094A3572EA85952ULL, 0xB61770A8AFB8D141ULL, 
            0x27C820038CEB56FAULL, 0x98C57F81CCA585C7ULL, 0x65C4DE59ACD97E1AULL, 0x827F97B6F4A03FB2ULL, 
            0x7CD409D472F91C28ULL, 0xC093D78D72327014ULL, 0x3133179EFF43C1F1ULL, 0xBECD1EF4BB3A0547ULL, 
            0x477C6EBB55F8031BULL, 0xE13884393F7E69B0ULL, 0x03A1A53FB89FB897ULL, 0x30EA5B2D3BCD6D43ULL, 
            0x110180C677783DBDULL, 0x795F17B3E99C22A0ULL, 0x1A7BA6C3B9FE126CULL, 0x011F82913DBAE03EULL, 
            0xA7F79FC9F2AA68DDULL, 0x7B7C3FDD83CA66B4ULL, 0x92C542804FE7F107ULL, 0x7AFAA41F56CC28CCULL
        }
    },
    {
        {
            0xC33714414028DB73ULL, 0xF581D6280EDE666CULL, 0xE0C2AD9ECEEAFD6EULL, 0x89B4525230B4B8B2ULL, 
            0xA091453C3B4D4286ULL, 0x032D44A6C82CAE6EULL, 0x7CC2230EB134C0D4ULL, 0x4FF2F7969E935E5EULL, 
            0xCC346D9EEF7BCC22ULL, 0xD2373384F91D1CBEULL, 0x0050BF15026C95D1ULL, 0x40FFCA2F01D17402ULL, 
            0x55D93562E74F4937ULL, 0xF7DCC9B99755D2F3ULL, 0xB0382C5DB88B7DAFULL, 0xCF83075BE42565DCULL, 
            0xF877D91808976BF6ULL, 0x76C50C66C1A43196ULL, 0x7234706B9F575303ULL, 0x55F1219370BA2030ULL, 
            0x8A727541110F3D4DULL, 0xE30138667AD0526FULL, 0x04FCA91D7D5CCC43ULL, 0xE11E194AA9FDFD64ULL, 
            0xE6E59BA8EFCBC0F7ULL, 0xD2C794D5FD24F598ULL, 0x4B5C07FB512C3714ULL, 0xE78BCA9847065193ULL, 
            0x9D74581C9BDB4BDFULL, 0x5A764B545179C50CULL, 0x60C7A2C7456F2900ULL, 0xB24D70B365E44F29ULL
        },
        {
            0x510853EB8227C06BULL, 0xA88B0EF7B7A3CBF0ULL, 0xC7A7A1B36FF74FE6ULL, 0xC2EC995981B9A9C6ULL, 
            0x7578912327958B65ULL, 0x43F9B1542ECA0131ULL, 0x032E3C7AE43B2037ULL, 0xB5CACF18A1371A10ULL, 
            0xD03728358F5ADA6AULL, 0x3C95BCC14C5A706FULL, 0x3C93D8A0D2E02387ULL, 0xD79DD449472959E9ULL, 
            0x29C2C78C8E695F6EULL, 0x5D82B21992B36A4EULL, 0xE17AC6FABA6B6449ULL, 0x3B9B28D5023FB61DULL, 
            0x6BFBB0D71E9BE121ULL, 0x731E45B453DB4C85ULL, 0xED7E5462FDA050CFULL, 0x1B24CA8F0C94166FULL, 
            0xAE50130EFA15E0F7ULL, 0xE23554AA0003827AULL, 0x51C3D7E845865ACDULL, 0x6D7F44C2202F212EULL, 
            0x6AE8B2F6595BEB71ULL, 0x932FC4EEEB4EE62FULL, 0x96D97741337BEBDAULL, 0xD3DBCE299C0D5D32ULL, 
            0x10C349BCC1DB0501ULL, 0x3CFBCC0864976EAFULL, 0xF50AFC08ECDF87D5ULL, 0x27C23416364BB045ULL
        },
        {
            0x9D92C060EAE27061ULL, 0x031B6EAC2D86BCD2ULL, 0x963ADD4E8A058204ULL, 0x7CA954266898846CULL, 
            0x8D33168E2CFCA779ULL, 0xBA68A791087DA9CFULL, 0xE1126A7E8CD5B5F4ULL, 0x77562A58EBFF7B3BULL, 
            0xAA0B60061828EEB9ULL, 0xB73C365EA4992C68ULL, 0xF09C2BE4C898C872ULL, 0xA3814577F37BEA59ULL, 
            0x4F08945B23CC6B2FULL, 0x8ED2E6C853196079ULL, 0x17463DDEB36B5A97ULL, 0x9BBDE5D556243219ULL, 
            0xEE017B9591FC9387ULL, 0xA0A3C97C45141840ULL, 0x42E4CDB4BD20A48AULL, 0xD95E72A75499F9A8ULL, 
            0xEEF9D83C03A1B8D8ULL, 0xD49455463AE59D45ULL, 0x2AAF40B0EBE88B2CULL, 0xEB9FB1F971A3FA72ULL, 
            0x2B08E60FF1CE47D6ULL, 0x151D5451581EC6BDULL, 0x1634AD7D053FDF2AULL, 0xA7C005871282E09BULL, 
            0x2E933B0D4C41BEDBULL, 0x1D7D03EE298A9F16ULL, 0x29F536A055B72E7DULL, 0x0CB2FA51AC5F796FULL
        },
        {
            0x7BCA9D62760D2E3DULL, 0x4D1BA5F52D5191DFULL, 0x24C7DD74CB645486ULL, 0xE9E2BAC6AADEE02DULL, 
            0xFAD20D8F81B65F71ULL, 0x04EB9C04D8456F08ULL, 0x27A600C80EC47ECCULL, 0xA4369675E444DD90ULL, 
            0x0B45319CCE816B09ULL, 0x09BAE414DDBAFFDFULL, 0x67D667DE09387132ULL, 0x37AD06E19838483AULL, 
            0xAD80A36193810BFAULL, 0xE7952D1A69473FA1ULL, 0x5A707DB99105BA8CULL, 0xA97F49C942E478E9ULL, 
            0xAE39C3CB993BD9C4ULL, 0x535B73E3B718A190ULL, 0x2380A2869E256C2EULL, 0x64B878A1077CEED5ULL, 
            0x32847D697D76A6B1ULL, 0x453C47AC98A8E224ULL, 0x0AB5011103BAFB5DULL, 0x6778F4946C22624CULL, 
            0xBF5C8E6B1F068DDEULL, 0x5B4C7128DD69A022ULL, 0xA7B6015981E8352BULL, 0x3224B73BA3CB6E87ULL, 
            0xC573F1C17A7B2D8EULL, 0xBB457A596DFFD115ULL, 0x044EFE171F79A39DULL, 0xE02BC65D15F5A2E0ULL
        },
        {
            0x521058C2D0EE78F9ULL, 0x473FA9171EEEEA8CULL, 0xF46C755EF7BA5253ULL, 0xBB764EF43E4737D7ULL, 
            0x101910316A49808FULL, 0x9BCE8FCFBA99D7EEULL, 0xAB2EC24749CA2601ULL, 0xF494C15E7D0E6602ULL, 
            0x4352F4FF2AD8BB42ULL, 0xEF02C59E36D3B464ULL, 0xA43103B236E59485ULL, 0xD1C3125CC7C60A31ULL, 
            0x1500B2A82BAD01DBULL, 0xD058B3701E5E85BFULL, 0xA94082CA9F2F386BULL, 0x849BF7CE04DEED37ULL, 
            0xC0882B3AE4400D7EULL, 0x37AF4E853E439149ULL, 0x0CD29984B5BAA437ULL, 0x6E49E6B4373E04EEULL, 
            0x41CCA2542D9E1896ULL, 0xC5FF7BF79BE9E4D7ULL, 0x1B93E637F0AB4D56ULL, 0x4A7C61CBA1A5DD2BULL, 
            0xBAD00D4B9B8A4D61ULL, 0xDA972442B9B2802CULL, 0x8F0C4AA119F0BD8DULL, 0x16D4726645A471B2ULL, 
            0x63BCF85DC936B3B1ULL, 0xF5B4CC18A2DAA0ECULL, 0xFD3BEA96E294A25BULL, 0x0EB938A107BE03A1ULL
        },
        {
            0x97A651617176DC2FULL, 0xF25232648CA4B9E6ULL, 0xEF6E0C8C2CAECFBCULL, 0x7AB8989773E35E72ULL, 
            0x00E056324D92A87FULL, 0xDE997E842EA25A2DULL, 0xB4B8D043FD7134EEULL, 0xF63C3A13790B2759ULL, 
            0x787F55AB71FF88B4ULL, 0x85CDDEA8E3443829ULL, 0x63EDCA7F7C5B29B2ULL, 0x66B4899002D0F6E6ULL, 
            0x77BD23A2A8324517ULL, 0xEF094291D5406B14ULL, 0xBD9391A0BE1A452CULL, 0x852589839774CA91ULL, 
            0xB4C5FADB9D45CA7AULL, 0xCEFC9E3706FFEB7CULL, 0x8679B486D8F849BEULL, 0x20C6F7D033651FCBULL, 
            0xC22408F29E717714ULL, 0xFD3C8A17165D288CULL, 0xC2CBD7449B4F0C3CULL, 0xAD166321C9173FF2ULL, 
            0x12E2042690985463ULL, 0x87F127B5A5FB3329ULL, 0x90BDE2950578D325ULL, 0xB844A45F41D46471ULL, 
            0xE782BB5D3849C74EULL, 0xF1A99D205AD3EBBCULL, 0x79D6A67018D55918ULL, 0x9DAB7E276385AB35ULL
        }
    },
    {
        {
            0x85AD5BAEF8A45326ULL, 0x7ECEFF615E202A7FULL, 0xB9E8E9C41B4828A6ULL, 0x73F53F6C55CFAA75ULL, 
            0xED088DE034089070ULL, 0x4A40DBC4DB2A792AULL, 0x1FD05AE17CC2C7C4ULL, 0x783B65D33F512182ULL, 
            0x1B5D3CA58BF39BE7ULL, 0x3548A37010665BF0ULL, 0x9917B5D03FB7FC80ULL, 0x30969CA08C408A05ULL, 
            0x45936BC4B2D46665ULL, 0xF6D72A79C267D85DULL, 0x82B91D974C1D31D2ULL, 0x5A1717FE8925348DULL, 
            0xE7838D6D2F451522ULL, 0x58AC028A88187AEBULL, 0x3898131FFF3CDECDULL, 0xF0F5557FE0EB7A7EULL, 
            0x75AD06FF00176114ULL, 0x9B44D8743F1A3F27ULL, 0xD43211A32EB6853CULL, 0xFDF6CC5BF4CBA1E8ULL, 
            0x869C25DB4BCD1260ULL, 0xE0FDC1F16A6F9662ULL, 0xFFEC307BECCDE25CULL, 0x8E330592E7FA4DABULL, 
            0x167CE4DFDE2796AFULL, 0xB22BE6B2D8622EB8ULL, 0x23030EE6643AE717ULL, 0x2CC65A9C8AACD82BULL
        },
        {
            0x7DA36C5F1F84920FULL, 0xC87F2209BF1195B9ULL, 0xD65802A21AF2004AULL, 0x7BD8B119011F812BULL, 
            0xA793E544945CF995ULL, 0x1A01C2FD471982C7ULL, 0xDBE5247777DD5B67ULL, 0x9BE4B36028731425ULL, 
            0x08F95C63642364B5ULL, 0x177C48954A272141ULL, 0x87892AA93E2542F9ULL, 0xD1AA6053B2359E4AULL, 
            0xF6042053B1331204ULL, 0x6518A263500D6920ULL, 0xF2E7A5F39EAB1FC2ULL, 0x8C8BD5138D8A6AA6ULL, 
            0x7A34C1A3AF52A969ULL, 0xC53D8A2BB0C1CD60ULL, 0x51347FB470323B36ULL, 0x80C98AD0E3C13443ULL, 
            0xF15FC522812D0F6FULL, 0x7EB5175A79E51FF4ULL, 0xE4FAA07AB97387BAULL, 0xDE8D6E6C2BB95256ULL, 
            0x581A4DDA1D744D52ULL, 0x245A5C7B32EDA395ULL, 0x8297D844D7D91488ULL, 0xE6C43382938082F4ULL, 
            0x7B871A362846CD83ULL, 0x89712EF349F0D549ULL, 0x0C8906910064F53CULL, 0x6F9CE23A9C6C4577ULL
        },
        {
            0x4F540F0B92E0D6E6ULL, 0x12A643531B42C2C5ULL, 0x946AC1F3BA8BE116ULL, 0xF9C7BBAB656E605EULL, 
            0xC34816272F96C104ULL, 0x9F50FF67F2C2BA7CULL, 0x4991CCF660C9DF74ULL, 0x73BFFB3CB439113CULL, 
            0x0E56F47920DBF509ULL, 0xA30D4A32EAA2AC77ULL, 0xEDA7F194F382DF30ULL, 0xD4FEBC266B5606BDULL, 
            0xD9431F84A981496AULL, 0x8D82FDB9F8995A7AULL, 0x27A1467F82DD9197ULL, 0xB7C7580F95DB22DAULL, 
            0x3E57EF6E1D10B9C6ULL, 0xD6A74C895843A6BEULL, 0xDA0EB35F906701D9ULL, 0x8932BD3F955F906AULL, 
            0x91A23F0EE973AA05ULL, 0x213E98F4E5EAC1EEULL, 0x9E064FC2669FE08EULL, 0x8D2C6615DE2FD199ULL, 
            0xEB5367345AC46F26ULL, 0xF8758420D0BD7C25ULL, 0x988481D266D955CEULL, 0x3B2D16F6E1D2CA76ULL, 
            0xE57061A8B68DE5FCULL, 0x654C3C7FCAA46474ULL, 0x4DB3218675A8344BULL, 0x67C0B77D4AE19C2CULL
        },
        {
            0x3A2C1C5EE3211E03ULL, 0xD7D8F62787F61FA3ULL, 0x57F4203CB97CD90EULL, 0x53F2186833848100ULL, 
            0x02B17EEB6C612938ULL, 0xE2435522D5B3E64BULL, 0xE13DF588923C13F6ULL, 0x40D02AF40BE36860ULL, 
            0xC8F6BC5305798C61ULL, 0x680AC1CA4534630FULL, 0x49B5E774C76593B7ULL, 0x96CB3B982F99BF70ULL, 
            0x140EE0A07AB0F999ULL, 0x14E4D75EBCEAC7A5ULL, 0xAD63E91BB08FFE06ULL, 0x7C0B9BB390C79831ULL, 
            0xFE35351CE66B4CA0ULL, 0xC4E2D78ED951CEA2ULL, 0xE38E8E74934830EEULL, 0xC8FE1D021E9822CEULL, 
            0x47E7A45DBFF2B933ULL, 0x73CFE2FCC30F92C3ULL, 0x368F30206E5F3AA4ULL, 0x842CBDD039A0AAF9ULL, 
            0x4E7FFC3BAEBC81B4ULL, 0xA324E5554D937006ULL, 0xD04B05CB414CECF4ULL, 0xA1CA961A72C1A8DDULL, 
            0x471C6854399ABD91ULL, 0x2E98466D91F52E4FULL, 0x819F9F4099F216B8ULL, 0x0D49C0DB7FF5B742ULL
        },
        {
            0x99DFF4DD3560ACC6ULL, 0xE03082BFDCF087B9ULL, 0x2D8CC698A49D6A52ULL, 0x50A7082EB194E71EULL, 
            0x78E12CD52AA1F2A8ULL, 0x28E4CD9A3C8831CBULL, 0x1B223911A3F4E71AULL, 0x446584B327C9B821ULL, 
            0x35E32EDDBD7B00C6ULL, 0xBB6C7348CD3B61E5ULL, 0xEA3A2C1FC7BEE4B8ULL, 0x3750F9EC95DA7A4BULL, 
            0x0C4359BD4C37FDF5ULL, 0x8E36BD2F643E3158ULL, 0xCEB8A5724F577DE5ULL, 0xFE8A84F61148BDF1ULL, 
            0x6F94552DA64B17A3ULL, 0x5EC474C5FC1D2F8CULL, 0xFCA92A099A1E4502ULL, 0x5D8BD7E84E74B78DULL, 
            0x42B3B3BF5EB5C057ULL, 0x2173DBE3649D7AC9ULL, 0x1AC17EE706F2D143ULL, 0x4D192205AB113228ULL, 
            0x1FDA2F863C80A71CULL, 0x9BBC91C877141214ULL, 0xE8AFBB89940EC1AFULL, 0xDEDE77302AFDE41BULL, 
            0x71F7D85530297D45ULL, 0x6DAF62E0DAD8D284ULL, 0x94095845C088C0EBULL, 0x9EA16911BB69239EULL
        },
        {
            0x1F14D64125D9C4FDULL, 0x228B761813289C42ULL, 0xB70EE54E27ACF35FULL, 0xCD7F880ACD59BBC8ULL, 
            0x95D5228E69585987ULL, 0x8AA8FA2D4FD3D848ULL, 0xA03737BBC23A715DULL, 0x1DE9E31BE23A4585ULL, 
            0x77A927DF868DA4A4ULL, 0xD158AF3346A3233BULL, 0xABBB7C941E065C88ULL, 0xDDDBA3E7D17EE66FULL, 
            0x4E4B7BC703E4CF6BULL, 0x682AAAD8415D6E55ULL, 0x33A02C85F4661E23ULL, 0xF14E1E4EED487D21ULL, 
            0xE6F9616CC8308CC4ULL, 0xDB7FBD1822956C6DULL, 0xD25EC7E6EB8FA00DULL, 0xA01DB373726EF376ULL, 
            0x4BCEBC0D901A3B65ULL, 0x6865BE463CF48DF6ULL, 0xF27A22A453B2730CULL, 0xADD6EC334AE613BDULL, 
            0xC9117D5315F5F7E4ULL, 0x02B4B7D92BB96B5CULL, 0x160325E1B399D5A8ULL, 0xB916236A35D194E1ULL, 
            0x94FC02802188DEA5ULL, 0xE6C864CE4E8B65C2ULL, 0x1A74BD46B35F4EEAULL, 0xA5A132D7EE8D81B4ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Naos::kPhaseDConstants = {
    0xB2705994B9084AA5ULL,
    0x22F88F14D84C7B50ULL,
    0x2BB97F30AC296B5BULL,
    0xB2705994B9084AA5ULL,
    0x22F88F14D84C7B50ULL,
    0x2BB97F30AC296B5BULL,
    0x52CAED45BE9F7BA9ULL,
    0x306033ADC9687B27ULL,
    0x14,
    0x73,
    0xD7,
    0x65,
    0x14,
    0x2F,
    0x60,
    0x2C
};

const TwistDomainSaltSet TwistExpander_Naos::kPhaseESalts = {
    {
        {
            0x869A622DF73A06A3ULL, 0x048C77DA5A767D0EULL, 0x71F9924AB53C3D38ULL, 0xBC21DA0E20537B4BULL, 
            0x951711AC88E4E1C6ULL, 0x0F96894DDE313047ULL, 0xB564EFD0F6C206DBULL, 0x0FE63CFC309AE001ULL, 
            0x641658B819119AFDULL, 0x36D862905842DF25ULL, 0xB98903EBDE806267ULL, 0x1BC25E973DC2021CULL, 
            0x59B233F79F8F9A9CULL, 0xA5A344BA38D6EA3CULL, 0x67B19A7AECFBB41DULL, 0xD5D0D77D5405DDE3ULL, 
            0xF391D6AACCDC4012ULL, 0xEEA8108597852E06ULL, 0x2E62686D56F63FAEULL, 0x01991ECA8A514AB7ULL, 
            0x604A88A497419C29ULL, 0x1088CC79AF95D86DULL, 0xAF73BBB32A22104CULL, 0xBAA53B493B22EE58ULL, 
            0xF509C50258AF5BDBULL, 0xEF415E3B589EEA92ULL, 0xFBCC1C2A6D82FDF4ULL, 0x0299009EC46C32D4ULL, 
            0xAD970F8BFD82C0E7ULL, 0x2E6090818AE7C266ULL, 0x047A749CEDEB6B92ULL, 0xD42D9C897D919092ULL
        },
        {
            0x5D3BF12FF7CABE00ULL, 0xDD4CFE4E93D82580ULL, 0x9D2B299CE6F64CB5ULL, 0xF9174391D04CF01BULL, 
            0x210CAD42E939251EULL, 0x229B6FA21BC1CF94ULL, 0xE8C9BC6130AFE7C3ULL, 0x09F17D8F8A03C56FULL, 
            0xBC6702FA24F060ADULL, 0x2BD81BA38E40C4E8ULL, 0x161D524474E0AA8EULL, 0x8F7857360A6EE429ULL, 
            0x3F421BFFF3B3266FULL, 0x96707A2D492CA020ULL, 0x443991C7E4593A79ULL, 0x26FF2A5AA2C3554EULL, 
            0x032FE66BF31BCF8EULL, 0x466250F45D5EF598ULL, 0x013B892849771C07ULL, 0x85AB813783989667ULL, 
            0xE7371280A2631ED9ULL, 0xF525A1A631AA4A56ULL, 0x311B912D7FF97F2CULL, 0x57FE5AC678EFDA2CULL, 
            0xC3453FAC820C9787ULL, 0x395EDD58A6C9A7F0ULL, 0x89460D5A92D537E9ULL, 0x8D234600D5EC6B86ULL, 
            0xD2ADDB19D47D36DFULL, 0xBEAA04715397D11BULL, 0x7353BB4462935505ULL, 0x3918E2B7CA6B3E21ULL
        },
        {
            0x92A9CE8DA716B66CULL, 0x4E9C8280F87B4F67ULL, 0x75C858E1AEA4B650ULL, 0x283980A5997E3865ULL, 
            0x6B240DC86AFB6F86ULL, 0xE15FD997EBFAB777ULL, 0x698B6C565A147AF0ULL, 0x7653B38F7169C6A0ULL, 
            0x502AEA3BA1040E57ULL, 0x671CC012AF1093CFULL, 0xD199626E1A7469AAULL, 0xA4D2C5E08DA15783ULL, 
            0x95D596C655FA1BF7ULL, 0x50601F52ACA4F158ULL, 0x81502C8D794CB845ULL, 0x902A5B8F58DC8DC4ULL, 
            0xA8A688E278A82E85ULL, 0x62F66402D8BADA8CULL, 0xECAA9A00ED69CD96ULL, 0x6B53E0FE3A0E686BULL, 
            0xADDEB263AD10A94DULL, 0x56F39F22339A8348ULL, 0x778681ED3EAD8106ULL, 0xBD1B69DC2B2BF60BULL, 
            0x09F67E40CF672EC7ULL, 0xBADFD9033968DA70ULL, 0x8F3C3847C0993446ULL, 0x1D0A24E559C22EA5ULL, 
            0xFEA57E02FAD3C711ULL, 0x9E3154F98CB617BAULL, 0x60148F95ACFA469AULL, 0x699DC74E13DC50ACULL
        },
        {
            0xCD690ECAD2684056ULL, 0x67B3262CED4F31D0ULL, 0x9544F01FBA509793ULL, 0x77800FF8989032B1ULL, 
            0x41EAEC61B114BFF9ULL, 0xA9B2841E430F6176ULL, 0x74EE84E9DEDDE0C2ULL, 0x1EF1AC404CCAB1DAULL, 
            0x340A422BB8889BA0ULL, 0xE6D31EDE4C2895BAULL, 0xB6263CB8624F5612ULL, 0xF096F4AF9C0BEB66ULL, 
            0xD2A07BFBC0E6458FULL, 0xE9333B4E900F4560ULL, 0xECF566446ED8EE40ULL, 0x630B64A057B66596ULL, 
            0x90D4AFB96637CA89ULL, 0x8005E5594A9985EEULL, 0xD3D026850CDF9BCEULL, 0xF7F1D8C0EBD9A0A1ULL, 
            0x15C08471B00A24DAULL, 0xD7081626EB05A8AEULL, 0x19CE59A61279FA37ULL, 0xC10E1C69300946AAULL, 
            0x0721F1E966BBAF6AULL, 0x9E0000D9AB277C2BULL, 0xE5ACE6177ACA4D2BULL, 0x5AC608F433A522B4ULL, 
            0xAA4627A21629990EULL, 0xC00637E43351C8BFULL, 0x7CD311444A136FBBULL, 0x2E00B31B73FDDFF8ULL
        },
        {
            0x49127479F9337BFCULL, 0xB8BA0C60D953640AULL, 0xBE97EE8BD3025E01ULL, 0x3D3C25FB423A8927ULL, 
            0x8C84FDF77B64850DULL, 0x3ECB5D099AA72614ULL, 0xF44E6B73272E4ABDULL, 0x46602882E2AC7AEAULL, 
            0x4E19C0D5401EC940ULL, 0x1980576311C05268ULL, 0x8FF0CC20743C55D6ULL, 0x7D09036B1313C84CULL, 
            0xC0E3688C0FBA902CULL, 0xDF2D40E19B2C960BULL, 0x277C64A8B8769A44ULL, 0xC50004EE2F49BBF4ULL, 
            0x44C3E50336D245AAULL, 0x4AF3FD908FAAC00EULL, 0xDF1BDA6705EE9A56ULL, 0x9F2E3C353AD4DFC4ULL, 
            0xF3622631800466DDULL, 0xF26EC7CA9B5FA2C3ULL, 0xD38E3EC477A1C3C3ULL, 0x7482EDE21A8E608AULL, 
            0x1B53D5086EB6142FULL, 0x6E09EEC02DD1B674ULL, 0xE6C0CC02A3A8704AULL, 0x053155F5400739ACULL, 
            0x9862788282B12B89ULL, 0xA35273846E765883ULL, 0xE213531045729E38ULL, 0x27C13F2CF2863C6CULL
        },
        {
            0xC087665B48CEBEC4ULL, 0x06849CEB3453396CULL, 0x4E47D45198DFC4ECULL, 0x822DFAFDA8AFAD53ULL, 
            0x20D96A33516AFA6EULL, 0x3E6939544E87C52EULL, 0x3E6EF23830050E2DULL, 0x798D6FF30F71A052ULL, 
            0xAE575FB36880BB33ULL, 0x41F8458F5B3C8F38ULL, 0x270C3C1B78D3A2F1ULL, 0xA1F554FC6A66BE51ULL, 
            0x7376B81E55A615A5ULL, 0x64075DA1652A8CDBULL, 0xE24BF1A380A72283ULL, 0x3F80D65B740633A7ULL, 
            0x8C46094162B59935ULL, 0x9E7B751DC766D205ULL, 0xC49D8F09007F2907ULL, 0x1F6B19B4B8EEEA83ULL, 
            0xCD7126B8EBFAE36FULL, 0x13F4476FA9B972B4ULL, 0xB295969BF1A094DAULL, 0x75408BE9BDAD3697ULL, 
            0xB88B943DCBF98509ULL, 0x7CE363C0A4BADFAAULL, 0x266CDF9E37E9CBD3ULL, 0x620872B7D9D98C9BULL, 
            0x382A7A3F46BEFAC9ULL, 0x78BA22C39364794BULL, 0x942EE1BD7B7B1942ULL, 0x0B4CDE408545C02DULL
        }
    },
    {
        {
            0x13F03C07DCA02451ULL, 0xA579C930718F957FULL, 0x0C1D482453A75882ULL, 0x92525F15ED0E87ACULL, 
            0x2C572ACD9F537595ULL, 0x15FE6D2D3AB63774ULL, 0x9EDE24B4D9D5D1B2ULL, 0xAFE67B1136DD86ADULL, 
            0x243C12ABF377DBB7ULL, 0x5BDD2994C54D1358ULL, 0x03D17F12603C85DFULL, 0x8BE460EAB5C670C7ULL, 
            0x3BA771E9D2C31D48ULL, 0x4B6930AD484F7B84ULL, 0xC88DBDD857F40C42ULL, 0x215C0DBC06874AB5ULL, 
            0xCB305C9A5D25C3C0ULL, 0x35253651E9756C2FULL, 0x8DE0A3DD6F1786C7ULL, 0x78D2941D433E6DB8ULL, 
            0xCEEDB24F84E6D07EULL, 0x7DA25A284A447A39ULL, 0xDA51EE0A1CBF8104ULL, 0xBBE75C59108601FDULL, 
            0x50F0CE252750D393ULL, 0x9CF3A3D5268E03D1ULL, 0x6BBBFE516BB8392DULL, 0x14B89A0CD883B746ULL, 
            0x3DBF0A976A339CA0ULL, 0xD02FD379F9CA1ECAULL, 0xCFF70E8873301024ULL, 0xF358429431B1E35DULL
        },
        {
            0x58B8BBE551BA8486ULL, 0xB4B95CC5A95C3DD0ULL, 0x3A6FC602A8D8AAE2ULL, 0x7C55B8050C58FCCDULL, 
            0xB84F3C80EFEB86A6ULL, 0x151D5671D748EAFAULL, 0xACDCB1E06CE39F82ULL, 0xC54EEE79E474FFA3ULL, 
            0x438324CE1597514FULL, 0x50E880EBD2CB4BF8ULL, 0x6D827DDCF9701C0CULL, 0x3440A3DE775A548BULL, 
            0x0908589F10857E29ULL, 0xD7D2AED614527639ULL, 0xB0B5A10EE8D6D574ULL, 0x315083AC6F324545ULL, 
            0xD7624BDAF56814DCULL, 0x194AD728CCA35CB9ULL, 0x66D363E2A505E099ULL, 0xFBA33BAC153BB978ULL, 
            0xC85990AA1195B68AULL, 0xB6AF5E53C8D80950ULL, 0xD459B4D64BAA9EF2ULL, 0xB628E1A573231055ULL, 
            0x65BF0B073538EF09ULL, 0x54AD8EFEF6614F85ULL, 0xE09B7E9337DDC57CULL, 0x9DF8E4017BDB6AA6ULL, 
            0xA35DCC8474C7CF3AULL, 0x14A9D1FC239692CDULL, 0x5ABECF1E57E911D9ULL, 0x30D2C78D3E65AA0DULL
        },
        {
            0xE3C9C93223E550C8ULL, 0xEACFB42321C5E0A9ULL, 0x3A9FC61F6FF2657AULL, 0xD55CF02D8845CE28ULL, 
            0xAB831207369C8ED8ULL, 0xD6E58FE6056007B6ULL, 0xB555C8D89570926AULL, 0x185CFC8F27EAEE20ULL, 
            0xAC1E249A88FE7D58ULL, 0x1F13A189859D5923ULL, 0x0A21DEEF25779B1AULL, 0x9C655389123E6B2BULL, 
            0x482C267BB2AFA010ULL, 0xC8E5F410CAEA3E32ULL, 0x7935C466679D32B2ULL, 0xAB91762C45E4CC99ULL, 
            0x2C53C8276FDD56C9ULL, 0x0678370CF4C32C50ULL, 0x644B6D0F3187C690ULL, 0x256E989C960487F3ULL, 
            0xC908C2DECA52639DULL, 0xBB3379E3B47CD813ULL, 0x3B391DEF0C89CDA1ULL, 0x0E41B8C439DA04E2ULL, 
            0x0C933D485E5D2FFBULL, 0x26296F27107F3808ULL, 0x92ED8F36F369001AULL, 0xC49C716678B734C2ULL, 
            0xD37BE8558BC2EB09ULL, 0xD0258BA0BE3F5FCDULL, 0xBDA31E842CE38D2BULL, 0x3312021DFBC8DA41ULL
        },
        {
            0x668134628C3374C0ULL, 0xCAAB2AFC74BB90D4ULL, 0xE4A152596F3ACF86ULL, 0x56FB0BD1F70C0E7CULL, 
            0x78BD8CC42F1BADDFULL, 0xA74D052FE02F68E0ULL, 0x86FFC930536E0CA2ULL, 0x6E4659925FA846D8ULL, 
            0x74477E95B62A37BEULL, 0xAD4BA9FCA3B6139AULL, 0xE2F438E8E9495A99ULL, 0xC1EE248C1C3EB28FULL, 
            0x2296C8B6E8263CFEULL, 0x8BB1F9E69C56B1ECULL, 0x24F030B22B3C0245ULL, 0x8B0907B1E3FE84CFULL, 
            0x1FCDEE5CB75392A4ULL, 0xC254E6D20FC9275EULL, 0xD4FCBE552A781030ULL, 0x60D67C37FB5B2629ULL, 
            0xFDA4562A7F9B2238ULL, 0x95B99255CBE8D1DBULL, 0x8912C70C72AF0096ULL, 0x27D0B1E4EC11A158ULL, 
            0x2436A768E9092A2BULL, 0x3978EA22768DB953ULL, 0x68518253130814B8ULL, 0xAB855BDB11114B5DULL, 
            0xEACBEB3CE701EADDULL, 0x3FC79BEBEC2A353BULL, 0x674A460685AD7E5FULL, 0xE85DD842C0AF7838ULL
        },
        {
            0xEE51B0315823BE55ULL, 0x33EF24087E472A3BULL, 0xB92AA12B0130BA50ULL, 0x2C0DBD54A7312B38ULL, 
            0xAC9DEBC5B8AEE65BULL, 0xACC7CB309CAB38C0ULL, 0xC26E74A2DCBE6E17ULL, 0x3CAB08011D5C7F8DULL, 
            0x527475EFB5E528E9ULL, 0x7BD148E1006994DDULL, 0x6504F35A0D65CCFAULL, 0x84D413D7547E1BADULL, 
            0x56ADAAD2117654E6ULL, 0x08366F269F02E360ULL, 0xDD70A87A02BD1E00ULL, 0x4EEE70FE10A4D1D4ULL, 
            0x008C20828624055AULL, 0x4E207F9BAF304A09ULL, 0x0BCCDC5D909465A0ULL, 0xDCD82A83B91B49E1ULL, 
            0x39AF72BBA932CE91ULL, 0x23E1A73497B757B7ULL, 0xD802D9A133B38F51ULL, 0xAE057A09F62E996DULL, 
            0xCB0E61B0AB6C8021ULL, 0x0070A64B0F8356E2ULL, 0x8A77FF87051B5E50ULL, 0x7DF47517224AF861ULL, 
            0x2395BC855B1EC54BULL, 0x9612B91F3927FA59ULL, 0xE7E99598EBF7291CULL, 0x6FE441AF1FCCD434ULL
        },
        {
            0x4B2EC4DCCE569506ULL, 0xCDD5E979E82E6259ULL, 0x87DAFB68E4C2FF5DULL, 0x2BF94768424ABAC3ULL, 
            0xCA4D02753AC88444ULL, 0xAC753BA5921F8713ULL, 0x5A59A118586CBC5CULL, 0x754142BBA8E21BB5ULL, 
            0x9221DBC7DDFC0709ULL, 0xBA94B96EF8BBF03FULL, 0x9FD05533073AEFD2ULL, 0x7200C8FFC3FA8F24ULL, 
            0xDE7F898192E6B4A7ULL, 0xF46BB98EDB14A282ULL, 0x00260C513E8EB186ULL, 0xB725756BA784A7D1ULL, 
            0x8A124DFD64AE995EULL, 0xA009DA786A49CD99ULL, 0x2DBC669A3E351F48ULL, 0x7507AD9FC960474DULL, 
            0x6DBC6506E41B7744ULL, 0x7C85A0F45F947543ULL, 0xCB0469E2AF17C9CAULL, 0x5CECC19324754E82ULL, 
            0xCBE13FA60D84AA47ULL, 0x6EF2D141E86808FDULL, 0x6F7D837BED570F37ULL, 0x959BB7EDC3519741ULL, 
            0xB7F4F06E42735ECDULL, 0x0C7E9FA4F6B7236EULL, 0x6921C3F20D22EECDULL, 0x2E916E0AFEE917FCULL
        }
    },
    {
        {
            0x89DB01BFE580C08CULL, 0x41936A2EBDD3858BULL, 0xBD02BCD2CD189D5DULL, 0x868913872853A36EULL, 
            0xAA79B96EBBA86A3DULL, 0x400696B9FCBB47F0ULL, 0xF63DB3397C76643BULL, 0x64EE205C0364C51AULL, 
            0x886A3C47C26CE2C0ULL, 0xDE8AF485F90B9295ULL, 0x1D129B8B1A768E65ULL, 0x2FDD4C10C2FA2F02ULL, 
            0x09ABC642BE813BB3ULL, 0x92FB3C1EDE348E92ULL, 0xF67539F353FDF367ULL, 0x0CAF38B044082268ULL, 
            0x3C4E338F56548EB5ULL, 0x36022723E89378E3ULL, 0x24EF20015DCA3A30ULL, 0x2ED866A02DF5A19BULL, 
            0x898314D427C0A29CULL, 0xC2E053263D200996ULL, 0x886BB7A7E74D7909ULL, 0x476AA07E687DBD92ULL, 
            0x839BA23924F2C8E4ULL, 0x2DF89B056FD6E8FFULL, 0x35BEF6218AE2BBACULL, 0xB9602EEBB78C8E2BULL, 
            0xC2AE5DBD67C7393DULL, 0x63F5E172129F2086ULL, 0x796036EA01907986ULL, 0x8B5830F49279C557ULL
        },
        {
            0x44A1D3D160BBA838ULL, 0xAE52C23EB911E3DFULL, 0x806007EB39FC4A1DULL, 0xE4682C111C76F9FCULL, 
            0xC680EA69B1FBB761ULL, 0xBF80AD06F930BFE2ULL, 0x25B62873838850C2ULL, 0xE9B07011D368BECCULL, 
            0x53F8CDCD5814103CULL, 0xB9F24C208312DD62ULL, 0xB7F822ED7BFEEAE6ULL, 0xE511A5C80D6E33F7ULL, 
            0xF8FB73592B381A73ULL, 0xDC62E8F07182DE74ULL, 0x1D50EC2542FC9499ULL, 0xE4941844CBFCACF2ULL, 
            0x51FB37C995583778ULL, 0x32D9613796E32C61ULL, 0xD6FDD0A06ACBA7DAULL, 0xEC301EE376E784FFULL, 
            0x58EC44F02D0CAE6BULL, 0xBC4624019C81FF06ULL, 0xD79BE5DA810C6E3FULL, 0xE2DB265ECF8F18C5ULL, 
            0x085B6A1AD89EB407ULL, 0xAF3F6E3BBA30ABEBULL, 0x3BE235F6B39A2443ULL, 0x1A814FDF986308F7ULL, 
            0x3DB337D9288799B2ULL, 0x09B22341A2D35EABULL, 0x05F8AEA94E32552EULL, 0x061DCA8505B2A1C9ULL
        },
        {
            0x153F318FFAB78A68ULL, 0xB3A6122451A21BD6ULL, 0x8D46396C461488A5ULL, 0x6E5F16DF55AA43E9ULL, 
            0x0C13A5B0EF0EAA7AULL, 0xC41C816A12A8174BULL, 0xBA379BF1743838DDULL, 0x50C3AD29D3899045ULL, 
            0x2991E88B2378C13BULL, 0x7280E09BA0112141ULL, 0x57312B0CAFB1AE1FULL, 0xB24C1D82822F1DCFULL, 
            0x6A2A6369792BEA8EULL, 0x9BCF6B14A8D241A5ULL, 0xB1C4DAB559C71A4EULL, 0x1435694372B29A89ULL, 
            0x124B3903D7053B35ULL, 0xD600A89F44715E90ULL, 0x9E32F03A46E71BA0ULL, 0x14983DCBD06F57BDULL, 
            0x87ED781747759D19ULL, 0x28A08A0A22E54983ULL, 0xE45C0133BFF8F7CEULL, 0x3242FF7E0AFF701DULL, 
            0x774F9DC17CE3FDEEULL, 0x9C00FD48C42F26EDULL, 0x8DF63B1AB5E96BB7ULL, 0x429FCFCD0663AA98ULL, 
            0x9469283FA3F32BE3ULL, 0x07964B3CFB6E7898ULL, 0x0B8DA4BCD06D08DFULL, 0xE4FD081CBDF7BCDCULL
        },
        {
            0x2FFC2E0D3F1D6514ULL, 0x1A6A7A196A31DCC1ULL, 0x0618C750CAEE187DULL, 0x19D15B1AA6B342DFULL, 
            0x93812F599BEAAC5BULL, 0xB049362CCEA389CFULL, 0xA224974C41C633C9ULL, 0xF3D9EFDA1A24FC00ULL, 
            0xA4EEC4BEA439F0FAULL, 0xFDC2D892B462C8F8ULL, 0x3550E0BAD8AF80A3ULL, 0xA004D95E4DD8002DULL, 
            0x595AA9A9723715E3ULL, 0xA367DC777B3B562FULL, 0x6B308A954ED2B35EULL, 0xFBC51524F20EBE3AULL, 
            0x38C87E08F059A4E3ULL, 0x7DCBCA4F9BB48758ULL, 0x5A185F3140C0E959ULL, 0x85EE681228BCA7FAULL, 
            0xD26EAB69DB21BD16ULL, 0x646FB385D2495B17ULL, 0x70D0D18135D8B32BULL, 0x7F78598666025FAEULL, 
            0xBA96B21525FF6052ULL, 0xA9AEAC30BA80B6B4ULL, 0xED532FE2F184AC4EULL, 0x0D95C1FF88390430ULL, 
            0x137081901B5CCEA1ULL, 0x2B00A7F269E69884ULL, 0xAFE4D0C21629832EULL, 0x52F124878A42C102ULL
        },
        {
            0xF6BB2BDFCF203F97ULL, 0xBFBEF98A3A248874ULL, 0xD823097C458F90B4ULL, 0x8342004F45C1F74EULL, 
            0x769293D8A8A2A601ULL, 0x4FE243B550719924ULL, 0x17CE3D17754FA62EULL, 0x2CB3DF71D346EAD2ULL, 
            0xDA112D0FA24A48E5ULL, 0xE65AFD9B95A62337ULL, 0x3206071243D79509ULL, 0xF8951CC455156BAFULL, 
            0x633337E1386052D0ULL, 0xA935E4BFD130B26BULL, 0x5C981F52C885B778ULL, 0x19C3C9CD160C2433ULL, 
            0xF36E32EEA851DBF7ULL, 0x91030F6E8643FF21ULL, 0xA0E5C1F5A2E89125ULL, 0x45CE4F48FE4D9E54ULL, 
            0x05E5CF7AA4C2699FULL, 0xB7289EDF42A2CF26ULL, 0xFE1C4C33DA26602FULL, 0xA4BCCA169DE884DAULL, 
            0x85A935CB7C4763D1ULL, 0xF079954E60B93D86ULL, 0xB775CFDDE8F45AAFULL, 0x4D1A99D14A231043ULL, 
            0x246E41DC49483438ULL, 0x36F5B63861F93E5CULL, 0xF8B4FB7D654C16A6ULL, 0x01074EAAC3C9DF41ULL
        },
        {
            0x3EDBB60B99D169BEULL, 0x014BBCABC22B5B1BULL, 0x0B6512C9EFA66881ULL, 0xBB4BBBC389E3DA29ULL, 
            0xE244425D8BA9C456ULL, 0xBCC917AF95F82795ULL, 0x5EAE8723AC4D4349ULL, 0x970F57C743FFCB4FULL, 
            0x262F96A2608DF84CULL, 0x3B25414429E191C7ULL, 0xD7A205FAA230008AULL, 0x6A027EB9BBE3D67CULL, 
            0x713E8DC85D9D81B6ULL, 0x437D2E4262B64469ULL, 0xD558F301A20647DDULL, 0x8C83A61037F08B65ULL, 
            0x93C90C0167C0931DULL, 0x81CDA2A27118EA50ULL, 0xDA044A3D136D0023ULL, 0xFD1AE98AE11391F2ULL, 
            0xC9181E3F4B83FA2EULL, 0x1A7E10F96C179D23ULL, 0xEBDE97D1720EB056ULL, 0x7E43EFC6A35CEF61ULL, 
            0xE5B0AFD3BE9D4A8BULL, 0xBCACDD4D7A4E1B1CULL, 0x149D14CE993607AEULL, 0xE1546AFA1EE08584ULL, 
            0xC0CCD814F40F11E0ULL, 0x0B696C6EA589EF42ULL, 0x7E9FB5943710A4C6ULL, 0xFC1C446A3029B71AULL
        }
    }
};

const TwistDomainConstants TwistExpander_Naos::kPhaseEConstants = {
    0x66CF6302642A0ECAULL,
    0x7C2D770CADA09E08ULL,
    0x2E0CC82CEF8F5154ULL,
    0x66CF6302642A0ECAULL,
    0x7C2D770CADA09E08ULL,
    0x2E0CC82CEF8F5154ULL,
    0x4549E0C7AE19B326ULL,
    0x58B4BEE108601883ULL,
    0x18,
    0x27,
    0x85,
    0xD3,
    0xD7,
    0xEE,
    0x2D,
    0xEE
};

const TwistDomainSaltSet TwistExpander_Naos::kPhaseFSalts = {
    {
        {
            0x58EF079D2C76BDDFULL, 0x1479CE4C24CA280BULL, 0xBC8E7B5114B3942FULL, 0xDD341BF957E1CF77ULL, 
            0x8579295F161C12A5ULL, 0x569C356BC34B1C5FULL, 0xEB60E7E8851438A0ULL, 0x36FA9B8E2DE5BE2CULL, 
            0x2A3353A7206DABA1ULL, 0x5E701F4DB97E4F1DULL, 0xE72F53ECD3BF39EDULL, 0x3278CF73BE36C1C4ULL, 
            0xB05F2A2D64D2FC32ULL, 0x6DE5C3EE6DA42740ULL, 0x7C25C2FEEA3B0C9DULL, 0x1CCEB0E5BF6F416FULL, 
            0x3D2AC0B421CB9D77ULL, 0xC62C2188688ECCFBULL, 0xF8206816D1F73064ULL, 0xFD849C23F0B690FAULL, 
            0x4D968679341CE95CULL, 0x72454C6B1EB12D6BULL, 0x3975030B3E8EB665ULL, 0xAACD2B2364E72F35ULL, 
            0x79860866CFFBBF3BULL, 0x90FEBB0BC1D01E2CULL, 0xA0B4710B300F6D87ULL, 0x1123828EEBBAC5EEULL, 
            0xC85A624B26422F4CULL, 0x29345BF7583A763EULL, 0x71B819FDB04093D5ULL, 0x0129DB15C13A98AAULL
        },
        {
            0x2D4DE95A23DE1CC7ULL, 0x5E43BF9A23C7FBB4ULL, 0x25F3689761B73F7BULL, 0xBA28C22D22B6A4BCULL, 
            0xF85D6549029E1867ULL, 0xC134ADF067C8AA5EULL, 0x5CA8886B8C4A0B69ULL, 0xBB99DA6B7D8FDF2EULL, 
            0x81D023B446EE21D9ULL, 0xC0DD29CDF3281803ULL, 0x3A588D977FE83736ULL, 0xAA55B5F6EA1B00B6ULL, 
            0x1D24F26522F59932ULL, 0x8B166E6241DF6BFFULL, 0x960F61972B0D6CFCULL, 0x8417EFC139B45ACDULL, 
            0xA98B36778E29DBC1ULL, 0x9783522D50DA0CB7ULL, 0x42062335717A7DCBULL, 0x54B127ACDBC715FBULL, 
            0x53A6571ECC3FAC93ULL, 0x705236FDE4F1E4EEULL, 0x18AA7F040718D461ULL, 0xB923CC55AA934551ULL, 
            0x16AA6624FC149886ULL, 0x1E97A6C8E0E99C4AULL, 0x3710464BC730585FULL, 0xB01BBFB3D00E5102ULL, 
            0x20D8878C6871ACB9ULL, 0x6C48E878AD50822AULL, 0x768BF13C579122D7ULL, 0x10510DE7A894A48FULL
        },
        {
            0x5F07563F841A2B1CULL, 0x7E23D33EF9F355EAULL, 0xE1A9E996669EF050ULL, 0xAB8A0A6B95E047E0ULL, 
            0xC8E8AD8110C1434FULL, 0x815CA332FEB59CAEULL, 0x477E83B8C05B1969ULL, 0x40E9A73C172A0767ULL, 
            0xA6E2171EC6B4A9EEULL, 0xDEF71FBEEC9AA86CULL, 0x0F69FCA66309DCE9ULL, 0x6F107346943A9DB7ULL, 
            0xD643007FF8B9F845ULL, 0x765EC98009FBB69BULL, 0xF15D9612F0571C5DULL, 0xC9E016C735A1575AULL, 
            0x236334D181742A6CULL, 0xA24C26DF974D5087ULL, 0x37F81C13B74AFC2DULL, 0x810276F44818426AULL, 
            0x8E79CBD4C8A84446ULL, 0xD945059BD83E8306ULL, 0xDE0670F313503E60ULL, 0x45CDE49D36A5E88DULL, 
            0xEE6CD9652899DE21ULL, 0xA8E35224438AD298ULL, 0x510998C42037ACFFULL, 0xE8EC7B892359DCC7ULL, 
            0x4098446A926F1D67ULL, 0x77951A682F600023ULL, 0xDDD67CE8A661B756ULL, 0xCE9B2E7EA32918CCULL
        },
        {
            0xB69EF76D8CBE1866ULL, 0xD5A0299297211900ULL, 0xC80780238E1E9124ULL, 0x5453519801F9AD2DULL, 
            0x2EA7A6CB4D391D53ULL, 0x601476D142AE3BF1ULL, 0x458E39CEEAFB7D56ULL, 0xF854948E6B4BF6DAULL, 
            0x43C3A4E256EF21D4ULL, 0x74AB3BF937FF85ABULL, 0xA151016D0E9986C3ULL, 0xEF9D7DBA9AE83CC7ULL, 
            0x8D51CB6BA6D268D2ULL, 0x9AB3B1520DF38BAEULL, 0x812FABDDB529CFAFULL, 0xF3C9B715394B6462ULL, 
            0xC6ED596B82B69DA0ULL, 0x8F77B78F52A5EF37ULL, 0x0D42CBCB142EEA0BULL, 0x03F230D3684F85ABULL, 
            0x6ABEE0EE69C7F3A7ULL, 0x6174C1887241579EULL, 0x8C1C6B62884646E6ULL, 0x007815FC9F0892B6ULL, 
            0x314A97F666647C98ULL, 0xEA5024FB71EDFA4CULL, 0xC0D7D3FD91330DEDULL, 0x1F6A58F726245306ULL, 
            0x4720D13AEFC063E8ULL, 0x56866135D261FAE9ULL, 0x732CD02CDED1124CULL, 0x0902F483C382506AULL
        },
        {
            0x0C1F965A1630008DULL, 0xE3E41FD518478C94ULL, 0x3318A18275249B4FULL, 0x95456478F47F7CA7ULL, 
            0x7FB9E65999C941BFULL, 0xCF7DFD57A268C966ULL, 0x36D5FCA75C1FC78BULL, 0xAE7ED62B5880EE1DULL, 
            0xC71D900A3DB3510EULL, 0x54C9E7832049715DULL, 0x5249C9BFF76CEF5EULL, 0xFA035547593BF60BULL, 
            0x59BF799DA0474E0EULL, 0x431CDEF4B1C541A6ULL, 0xD942527E5041D2D8ULL, 0xEC179631978B8A6FULL, 
            0x5CD8FD14013761ACULL, 0x568C8FF38A60B333ULL, 0xC6615171A5E3ED28ULL, 0x6EC9E6FC33A28820ULL, 
            0xF88102736C4AAD3DULL, 0xAE0AD25286AE68BAULL, 0xD3634856887EF753ULL, 0x8305C641645209CFULL, 
            0x2AD17640F806DB7CULL, 0x207389ACBF1243B9ULL, 0x3DD500D8F9136F6FULL, 0x1351D923E8EDA7CEULL, 
            0x803E0FC05E59CE83ULL, 0xDAE5AEAA7C1F432FULL, 0x4D5E02F2B4DC1266ULL, 0xF606ECB125E64C55ULL
        },
        {
            0xAA7C73A7ABA48EA3ULL, 0x9BDCF38245CCA3E6ULL, 0x0364E3CFE29A0545ULL, 0x124638D0D564B9E2ULL, 
            0xBB4AE70C0B91FD8FULL, 0x96A8527052FD1C2BULL, 0x946ADCEF9111E357ULL, 0x699818549F04E41EULL, 
            0x3478DEA0990DAC09ULL, 0x4F103B070254C17AULL, 0xC5DF3ADA11393F86ULL, 0xBF92C75FC95C36F7ULL, 
            0x99D5DAEEBCADCE26ULL, 0x1C56385685E664D6ULL, 0xF317C447456CF9BDULL, 0x7E24029A2EA2689DULL, 
            0x336A82B840A50C23ULL, 0x49F49C58080FE0B9ULL, 0xFFBFADF5E3D86BC5ULL, 0x556007FBE2FCC997ULL, 
            0x8A427ED7FAFD287AULL, 0xD030DAFF87EA4E79ULL, 0xCBAA2C865152B084ULL, 0x3CD8B6BFAF0DCB08ULL, 
            0xF4D4126862BB4B96ULL, 0x6C91985B7C171CF6ULL, 0x46D0E615D144D827ULL, 0xA6A8D3704F355A6AULL, 
            0x96658515BAFC47A4ULL, 0x29BA62B7A5782844ULL, 0xE5E2FD7C5E7F23FCULL, 0x0A222EB47D6A6E52ULL
        }
    },
    {
        {
            0xB4CDF303E927EFD9ULL, 0xB5D3741AEBE29398ULL, 0xF17F59F081659C74ULL, 0x026EFCD2F11C9AF9ULL, 
            0x19E111CE58F51F63ULL, 0xF80B8EEA23131859ULL, 0x73249F323A3CAB4EULL, 0xDFB551909E8B11BFULL, 
            0x3100D0F95B75AB3BULL, 0x96C235E94B34ED8CULL, 0x23CC00DD3298B7B1ULL, 0x98E50E511A687EDDULL, 
            0xA7DCEC0D02D54FCCULL, 0xDC6E068A296665B9ULL, 0x9B113368E272929EULL, 0x62A1559E9707E7FBULL, 
            0x6C8365FEE389C824ULL, 0x86EE936B17C47554ULL, 0x6D1B8862D1AFE827ULL, 0xDC95F1090338FBC3ULL, 
            0x5B7B6537B3978E61ULL, 0x911594393528FC80ULL, 0x7FF5D3D86B3A52ACULL, 0xE00AD54376DA74B8ULL, 
            0x4D395BA77653DF09ULL, 0x713E91AAC0D3E042ULL, 0xCC8460E103016669ULL, 0x9B0BE77C12C6FA23ULL, 
            0x23076534A9424A3AULL, 0xE2148E2DAA2536F5ULL, 0xDA49E29EAA3E029DULL, 0xEC5C9B2D833B2C1EULL
        },
        {
            0xC2F470FD48063103ULL, 0x257BDFBDEC635A84ULL, 0x2C89A155C7782E0FULL, 0x77EE8644B9832D7FULL, 
            0xBE86A390135BC922ULL, 0xB6AD8DBCA096FA23ULL, 0x7BC5014555A7E882ULL, 0xEF39FAD54F2005E3ULL, 
            0x5D61870B0EBEC6FBULL, 0xB29BC849D9D2FAE4ULL, 0x89CB955686404CA1ULL, 0x1C5BE3C092D6C3ECULL, 
            0x46DE1ADBB4F07FB3ULL, 0xBCDB8B5E44A9C8C2ULL, 0x71C49A9C382BA053ULL, 0x8A65014524A735FEULL, 
            0x817EB45B28CA3BAAULL, 0x68CAF2EC18415958ULL, 0x388B04528544F2C4ULL, 0x10B3991C65A40774ULL, 
            0x9E12BFD60F4C5D38ULL, 0xCB476D91F471A988ULL, 0x57292E221C340C90ULL, 0x85143B1F7EF8B8C9ULL, 
            0x24EAAE7E9A1FA39DULL, 0x137605F6BB8B9522ULL, 0xF7C5AFB12F5D61CBULL, 0x1C3ADF9426FD8CBDULL, 
            0xF83720DC93D2C0DFULL, 0x04262A6DC937DCE0ULL, 0x14E86B277F1F1A44ULL, 0x5AB65DBF4B4DF8D3ULL
        },
        {
            0x17117B45EEC4BA83ULL, 0x483ACF22B926B617ULL, 0xBA8EE68D4F4EC7C4ULL, 0x8EA777747BB0CB9FULL, 
            0x75B2705AD596EE5BULL, 0xB65B3CE0C2B8DA34ULL, 0x11D547A279AC9657ULL, 0x5E4058202150A7DBULL, 
            0xC9D8DD5C308B48B4ULL, 0xC29258C39A17A99AULL, 0xF92EF7439EB7F98EULL, 0xDA23F26449E09136ULL, 
            0xAD54EE1FC12D4EA6ULL, 0xBDD088F7AD0320A4ULL, 0xD4B677EB2BCCF7D5ULL, 0xDC59781567758240ULL, 
            0xAE93DB3300010EECULL, 0xC660894637DD7078ULL, 0x5E2B0C31FEC659E6ULL, 0x0CBD41284989AB24ULL, 
            0xDB85BD604D173E03ULL, 0x825BCDF7C802151AULL, 0x0844F87195300A58ULL, 0xA5F621E89DABD6DBULL, 
            0x6ABE01772F6A35B2ULL, 0xA1761D42F8359983ULL, 0xBCF3B51D7D3D788EULL, 0x23F6B211E5474317ULL, 
            0x25ED5943A957F0E0ULL, 0xF564194C0E2A3225ULL, 0xE59F6FBB1449C66BULL, 0x4FF69178264AF5EDULL
        },
        {
            0x7BCBBFF09C5CEE43ULL, 0x38DD18C594760EDFULL, 0x496FEA39936484F2ULL, 0x54713A1AEAB3B4D8ULL, 
            0x7FEA70F2BA5B560DULL, 0xC878D7D8E1CEF41EULL, 0xA1F6668A36C40047ULL, 0x3AC0E625CBB8EF3DULL, 
            0x6C5F46B63C9878FDULL, 0x102532448D13B59BULL, 0x30D6A194E3F82C15ULL, 0x05A74286EB422683ULL, 
            0x4EE016F103C73604ULL, 0xA3E6426AB31F3F07ULL, 0xE945F04BC35BBD69ULL, 0x6033A01D05722CBEULL, 
            0xDD9CB27A350CED75ULL, 0xBBD42BDD2921FA60ULL, 0x32402F3D59C0F575ULL, 0xBBEC8E5E48063DE0ULL, 
            0x6A59003792B12FD1ULL, 0xAFD9C7C79584A761ULL, 0x8858832E72DE62CFULL, 0xF400A47D2C9001A2ULL, 
            0x6B877B26200B3226ULL, 0x2833461A97DF876DULL, 0xA957950C73FFA5A0ULL, 0x34F88B77C482B3F5ULL, 
            0x3CE54578B06E6662ULL, 0x6D23343F79B0FFECULL, 0x07DA4BCAD5F8A6D3ULL, 0xB28C5AAE4004975CULL
        },
        {
            0x34CE6AF2BFA3AB4EULL, 0xB73D4CF667A5F432ULL, 0xA85293F34A62168CULL, 0x892721AAD377E8D1ULL, 
            0xBE4769E157240C90ULL, 0x2B2B06CC09C4F2F4ULL, 0x8E07D760EB91E7EBULL, 0x0C7CC8C41C7D0040ULL, 
            0x798666CDF5E59F82ULL, 0x522610EF79197014ULL, 0x987CCC2167A70A2AULL, 0x00386FE619FF6E8DULL, 
            0x70B347A96AF6BFCBULL, 0x7C29CC52E2BF07E7ULL, 0xB29DA8798128581AULL, 0x1ECDE1A7A1CBC403ULL, 
            0x27C943A30C1ADFCAULL, 0x8DDF17BA2494D972ULL, 0x02E54FAB4C3A4AF3ULL, 0x76C6E9FD8D13DD05ULL, 
            0xD391ACCC081AFA13ULL, 0xB94D5C16B6ADAF08ULL, 0x700AB6A209A611F0ULL, 0xD76F852BBED49F23ULL, 
            0xFEE7970F3C64E160ULL, 0x9FA624E46D0431C3ULL, 0xDDA9A3CEF0DB2D85ULL, 0x1FF59F875B143890ULL, 
            0xEC7D73D3778B4860ULL, 0x9EA68C10FCF9BD84ULL, 0xC703B7EB8EFD98FDULL, 0x0D1B379EDFB7FF89ULL
        },
        {
            0xB06E3C56AB4B6B8EULL, 0xE694A691A0E1273AULL, 0x40381A555BA09316ULL, 0x14950220DAF66C37ULL, 
            0x245A635F5C454577ULL, 0xE18EAED76F1A56CFULL, 0x2473E4676DB1EF4DULL, 0x52B0A52CECF456EDULL, 
            0x505C6FD06FEC1F64ULL, 0x04A490D94AB80310ULL, 0x8C1F9C9BB37BD32CULL, 0x502C72A2753E8C9FULL, 
            0x40EB8A05A541FEF8ULL, 0x03E76AFE3EB7D39DULL, 0x1473C5738B689484ULL, 0x8FBF8C8F3A957C64ULL, 
            0x542BA3098A822F01ULL, 0x68110671C378A2D5ULL, 0xBF28B83BB0E774F3ULL, 0x117D13C50D640CD3ULL, 
            0xDA0010398B8225A8ULL, 0xBD2CDE0C3EE50DA6ULL, 0x926E8C1978BE3504ULL, 0x7E56A0797D9AB7E3ULL, 
            0xBF29675625BE7743ULL, 0x6693611BF40032B9ULL, 0x1C660AB18121FA8CULL, 0x97CA35DE8F775633ULL, 
            0x1C5F7F4B5B63EC8CULL, 0xFAC9737878A7DBD4ULL, 0x8BB8CDAD5F8C4F08ULL, 0x1F444E5FB559E745ULL
        }
    },
    {
        {
            0xE818FBFE06C3A7E9ULL, 0xED48251E257B8E24ULL, 0x86F80937883A96AEULL, 0x0025E5B0C8328D91ULL, 
            0x2E87656108A5AE4DULL, 0xA90D076D3B1A04FCULL, 0xC3E9D0071B5CA163ULL, 0x63D9AC3D6D43D432ULL, 
            0xD195B764BA655ECFULL, 0x5BFA7FD8ADE1CAD5ULL, 0x679BB3D30E97EDE3ULL, 0xB1BDD136720AD4A5ULL, 
            0x491F3F1D8E3D9C94ULL, 0x13F0007321DADA66ULL, 0x07504CCA6BD9D342ULL, 0x95DC28D13D86636FULL, 
            0xB250DF9646B833B5ULL, 0xDFC31169EA6AC940ULL, 0x7E409C24EAB402FCULL, 0xF5107DEEE995C656ULL, 
            0xC7C0187DFCB3035AULL, 0x90A149B876BB0CD1ULL, 0xF7F4DDCC04F39E44ULL, 0x5D9E55C61C04B6F4ULL, 
            0xD2BC3908EAC044BEULL, 0x18BFEBC972A9823BULL, 0x909BCE61E5C40CF4ULL, 0xE290F82D5D2668B2ULL, 
            0x303FE3CDB96F179BULL, 0x80C170D114896F13ULL, 0x16EC423CEBA62274ULL, 0xE29782918CFAE92CULL
        },
        {
            0x2D1DE586058ABC84ULL, 0x11FF16284903E5EFULL, 0x20257F11EB0368F6ULL, 0x9E231BADE31C7261ULL, 
            0x0DF69B5812CECBF7ULL, 0xE59FC093FD0FFEC0ULL, 0x165503DB5D096B9FULL, 0x664276E86BDC454DULL, 
            0x9498252AF5DB43D0ULL, 0xC4D86BD8D7F0D7ABULL, 0x8721E17E7BAF2C24ULL, 0x6A019B4E2DBC5E33ULL, 
            0x5F4DF9E1FC46CCFEULL, 0xCA721966BB464806ULL, 0xECACE950AA38943EULL, 0x53EF299A78D09562ULL, 
            0xDBCE8594FF9542A1ULL, 0x650C1214A392E9AEULL, 0x12D04633C31CF503ULL, 0x9E42F45737B436F2ULL, 
            0xEB6DC8B5469F2634ULL, 0x8EF809351A25EB61ULL, 0x69783C27DEBE8F22ULL, 0xAA68A6EF1CB0CAD3ULL, 
            0xC77501284CFE8E6AULL, 0x7FCD4A2320D6666CULL, 0x4B17ABCF98F9F79DULL, 0x212ABE357F16B04CULL, 
            0xDAE95492299885A7ULL, 0xF063CDA11A6CE194ULL, 0x80AFDB512BEB9A91ULL, 0xAA008DA18BFCADCAULL
        },
        {
            0xAFD140B8ED734E2BULL, 0x126ECE0E60F4A42AULL, 0x762D4131A60EF3FFULL, 0x352293DF94E8DAD3ULL, 
            0x03652AAD5724064AULL, 0xBF91B388096FCE63ULL, 0x929215D013AE16FCULL, 0x06E741A0883BC7F8ULL, 
            0x92F9B54172E021FDULL, 0x6C7991516A0717BCULL, 0x651B99E7B54AA968ULL, 0x9F4FA533191A2A15ULL, 
            0xE57378B6857A0365ULL, 0x9384B04E11902FB5ULL, 0x6352972B5AFA696FULL, 0x7ED30AFE927995A5ULL, 
            0xE0ECBCE94AE4A881ULL, 0xB8108F504C05AAC2ULL, 0xAB7C2A989EBBD6A2ULL, 0x5AA86EED1EEA91E6ULL, 
            0xDCC6CB910AA8AE9CULL, 0xECE585B9E514E4E0ULL, 0x55356064EB08DAD3ULL, 0x383BF34273A23DADULL, 
            0x570E5D5F7B7DD0F9ULL, 0x6745EA6E984EEDCBULL, 0x3A7A1558A34F3624ULL, 0x015A5A8E5A3F7E34ULL, 
            0xE132DE719F609327ULL, 0x9C31B19327471757ULL, 0x69E178E1FDB2918DULL, 0xA5896B87905B8AD2ULL
        },
        {
            0xC66B0C585DA2F4D5ULL, 0x38450FBA3B905DF5ULL, 0x450F713F3744E1CEULL, 0x157F8ED5C7901D08ULL, 
            0x721FF0A963BF5E3DULL, 0xD6118CE4163058A8ULL, 0xA4E873C0BEA743DBULL, 0xC222788A8FDE1E01ULL, 
            0x3A2379237DEEE3AFULL, 0xADCABC34DCFA49D4ULL, 0x8DB23390F39E9906ULL, 0x42C343C20998C906ULL, 
            0x1AA8E8E380CD4158ULL, 0x8D99369C104639F6ULL, 0x9E65D698E33EC163ULL, 0x798125D2CD02E98EULL, 
            0xF7952E6CA561DBF2ULL, 0xDDAD4B756D286E2DULL, 0x9DF1DE6B9B755590ULL, 0xDB05E8F136706B8CULL, 
            0x7F1693C6057427F5ULL, 0x140E8206F2F50FF6ULL, 0x85CE9F711BCEFFB3ULL, 0xCB062A392BB67706ULL, 
            0x2878579380150D41ULL, 0xBDF9ECADF31A2DDAULL, 0x41A7921F6CCB8BD7ULL, 0x48E285E6158500FCULL, 
            0xF40400D4A7CA3AF2ULL, 0xA3BF5CFD95F8C4F3ULL, 0x80DD8A5428FF3079ULL, 0x5B6EC8FC2347858CULL
        },
        {
            0x04974DFDE296686BULL, 0x253490429981C829ULL, 0x74FFAADDCC533907ULL, 0x2C7ABF700B047272ULL, 
            0xA92EDE60989EB1E9ULL, 0x29D43CFF84DE1750ULL, 0xD49CF42790224A22ULL, 0x2868E6B4D14467FAULL, 
            0x15D15AF71715792FULL, 0x941408797A7A1F34ULL, 0xAD983885C6948C4BULL, 0xBD16CA0E969F0C75ULL, 
            0xE7F42416B009A800ULL, 0x9E10A196CB2F0AEDULL, 0xAFC6F98F49F3E927ULL, 0xC045F01C32954817ULL, 
            0x472E880C45BA0CE4ULL, 0x7951538E99591945ULL, 0x72BDDC98955FE8EFULL, 0xA43C22396CC9426BULL, 
            0x6447C558E4E2CB33ULL, 0x21AB1BE1148CAD5FULL, 0x8994DB713A7A1DDAULL, 0xF9FBE67F8A59E7DCULL, 
            0xE8A3C392DAAF6FBAULL, 0xA5157414A34F2A7BULL, 0x1637433520904E0AULL, 0xBB2D5BA5096F798AULL, 
            0x75D48A1E99C5771CULL, 0x37ABBF869B2B6232ULL, 0x5C1413BFB602174EULL, 0xBDEB517226CEC4F1ULL
        },
        {
            0xFFF47F7AE853F3B5ULL, 0xE71E9FC6EA24A07FULL, 0x67F3B8F8EE60BB7BULL, 0x0A56C814E1592F50ULL, 
            0xED17A747A6F338C9ULL, 0xFD5531F4678A9E1FULL, 0xE1CE317ADBE9BD6CULL, 0xF2B7ECCFD25F8FAAULL, 
            0x95F9D9EBB9F72379ULL, 0xC8C99EC501FA699FULL, 0xEB467C776765BC6DULL, 0x34FD2070E3799032ULL, 
            0x8E7DED1E5D9F2C12ULL, 0xC61A5377C82E7C09ULL, 0x4AA8ADAD21FEC8C7ULL, 0x7EF856DAEC6994C4ULL, 
            0x7E9598CE907D7FC4ULL, 0x3DFD367EF0AB07A4ULL, 0xDE2383BBCCC3DBDEULL, 0x75D72B3C521C2AEFULL, 
            0x840B4565736D616BULL, 0xCB121884E39CDDD6ULL, 0x1DFFDDBC14B860F9ULL, 0xA1CA95B2C711EA10ULL, 
            0xFBDDCDE57D589927ULL, 0xCA4F1BFEB9CCAC90ULL, 0xD6D36FC049E918BCULL, 0x3504C4E78C7D3580ULL, 
            0x5D8DE848B90E232CULL, 0x5C45B07CF7CA9DB6ULL, 0x6B5D4BA9D5DB3DACULL, 0xFAC303E7C10F01BEULL
        }
    }
};

const TwistDomainConstants TwistExpander_Naos::kPhaseFConstants = {
    0x062451EE7C490958ULL,
    0x0F0058B59B7A7C04ULL,
    0x08F2BFCBD2711A68ULL,
    0x062451EE7C490958ULL,
    0x0F0058B59B7A7C04ULL,
    0x08F2BFCBD2711A68ULL,
    0x94294ECE4ED9DFCBULL,
    0xBC7DABB6B59C894DULL,
    0x7F,
    0xC7,
    0x58,
    0x9C,
    0x0D,
    0xFB,
    0x05,
    0x5C
};

const TwistDomainSaltSet TwistExpander_Naos::kPhaseGSalts = {
    {
        {
            0x7CEEB31FFF7C8BA1ULL, 0x065421DC8A36F316ULL, 0xD070DD20634E0DD3ULL, 0xFA6631B5979FE85DULL, 
            0xC0B11C675F06754FULL, 0x3F96F904C6B0DC21ULL, 0x4FCB6B8A02D551B6ULL, 0x2081F53F9BF7C118ULL, 
            0xFBA11D82B0E288C7ULL, 0x76E168490F94CA44ULL, 0x36D788DDABF9E1C9ULL, 0xDAE418BCBA265321ULL, 
            0xE07AD1910C4A483DULL, 0x5ED729472482A7ADULL, 0x50E4DF3FAA1A3768ULL, 0xE75E011C9B22764BULL, 
            0x77A9FDF5BD88C2E0ULL, 0xBF4AB0193EE23A5EULL, 0x5243316840B956E5ULL, 0x3912520392584020ULL, 
            0x1EAB724109812D10ULL, 0xFF4F960CE8200D1AULL, 0x9ADB77C8C7A7D581ULL, 0x183FE74C10B84ABEULL, 
            0x8B6BFBC728A3318CULL, 0x5318D3976C56E45AULL, 0x3B325AE19AFC0920ULL, 0x2291C1C59DEB759CULL, 
            0xAF23879C0ADBCACDULL, 0x321B63B8A373427DULL, 0x0F5E6D84FC9400B5ULL, 0xE87476C3D3556703ULL
        },
        {
            0x4A3EF98DEF406112ULL, 0xFD23F5BE9335E27DULL, 0xFBCD4AF864E94636ULL, 0x7E48CDEE34F627DBULL, 
            0x2903528268ED2AEBULL, 0x2537BA2507798CC8ULL, 0x37E48A1E242CCCA2ULL, 0x86904466EDE6FFE4ULL, 
            0xFDBF1A1EAB2ECFF5ULL, 0x551A43A15D3F7776ULL, 0xFD11D4C5B68F0A65ULL, 0x4F13E5454548A31DULL, 
            0x70EF2E192339A4F9ULL, 0xADC4DB5C1C8E9025ULL, 0x79E8F1F59F04B87CULL, 0x1619766B53870ACEULL, 
            0x78F850EB7AEDA49FULL, 0x001D7006DBF135CBULL, 0x50355070BAA4957CULL, 0x895C8387B014979EULL, 
            0x3D5A92F6BF941C25ULL, 0xF90A0F5CD3A17EF7ULL, 0xDDF68C3274C759FCULL, 0xA3CFEEEE89346557ULL, 
            0xA23A9B591234ACC0ULL, 0xC29D313CF06736F4ULL, 0x4229CCA0CDB71147ULL, 0xBA6F8CF462FD81B4ULL, 
            0xFB1D69BA7DB2C40FULL, 0xA6CFB7F1CA4D7CA3ULL, 0x2A145379A2345C2FULL, 0x537E4427F623CFC2ULL
        },
        {
            0xCB8F1112FA0B3823ULL, 0x9F6F8AA0956451D7ULL, 0x21FEC959F4EC86E7ULL, 0x183B8753A18A39A3ULL, 
            0x7068DFA5EF20A29EULL, 0x4943000F4CC8B8BAULL, 0x40FDCE84F80F7A16ULL, 0x74E8052480C0F98BULL, 
            0xDDA89329E4167A2FULL, 0x44A021E25356E0A8ULL, 0x4089761EFA96CA68ULL, 0x49C9142B3B9DFF1BULL, 
            0x797E165877EEAF4BULL, 0x1646257A16BEE01FULL, 0x8E0F72139E626FD5ULL, 0x1CC8563C3695CE9CULL, 
            0x80231304A6FD0078ULL, 0xCA4981F80735FE24ULL, 0x59F1564463FACDD2ULL, 0x2DE170ED1456AE73ULL, 
            0x07C9EF4B49B0E771ULL, 0xFF2D32AC666E356DULL, 0xFA2A14AF162BB38CULL, 0x20F9521FC85BB487ULL, 
            0xF8884CF5CEB4CC29ULL, 0x12CF133D7F56CC85ULL, 0x8FD3E342D6E98E61ULL, 0x324AEAD209ABBB79ULL, 
            0xB980F289A605DD9FULL, 0xF73348040F174A7BULL, 0x69509A78986D371BULL, 0xEB3E63A67A063455ULL
        },
        {
            0x79450067CE3D8934ULL, 0x2E11E518CA6C3D21ULL, 0xA4DDF1957BF9EC01ULL, 0x9D070F20B7CFAB6EULL, 
            0x95440E9CA0F0483DULL, 0x760C4BDA780A75A8ULL, 0x37E4BCFD9ECC1487ULL, 0xAA52540CB651706FULL, 
            0x3341729250646295ULL, 0xD88F24A5E669436EULL, 0x00B0E5DECED96414ULL, 0x8432B91B040DA786ULL, 
            0x5CE84076FBA42B90ULL, 0x37450DBC09B8FD29ULL, 0xAF66A612AACD9F75ULL, 0xF5C44309CBFFC231ULL, 
            0x23DAE0B4B625E148ULL, 0xA52D756B52642137ULL, 0x0CD4CDCE1D1B38BCULL, 0xE013EC613E9B2458ULL, 
            0x06547D738FC4ECBDULL, 0xAE88B85FC3333666ULL, 0x30681463115A2C7EULL, 0x48624B3BD4D29E28ULL, 
            0xCA78B2E47381CE3CULL, 0xA506BFC4CE27686FULL, 0xB9194952DF5AA9AFULL, 0xD3E1C2428BAF7EB5ULL, 
            0x45E8D9CDF04D82BAULL, 0x3AACCFBABC272095ULL, 0x43E2ADCB2E054BB3ULL, 0xA515D90D01B94F38ULL
        },
        {
            0x806900932CA5A767ULL, 0x928E4F54A8788B40ULL, 0xE8165EE834A4373EULL, 0x948EBECCF8E0A005ULL, 
            0xA5377932D773A3C6ULL, 0xEB666C06EAD21440ULL, 0xCDB98CDEBC9AF6C0ULL, 0x61590D843623323AULL, 
            0x1ADFA48723E61B11ULL, 0xFF6B5EA06A8C5FDDULL, 0x8CC656AB4EE3E97AULL, 0x9A208DC56A5F1B21ULL, 
            0x903CCB0CE251EFCFULL, 0x03ED38EA03993FC2ULL, 0xC13CDD7C71475F0EULL, 0xD0CA7D66B6A83C49ULL, 
            0x1595559A42E2E4E3ULL, 0xA19BCD60CCD3A916ULL, 0x4B644D8969B8A8B3ULL, 0x84C40ABC9162F063ULL, 
            0xC269A61F68D069ADULL, 0x7AD5885523A85AF6ULL, 0xB8EAE0962D4662E9ULL, 0xA94091BAFABBE043ULL, 
            0x919D83624F03011BULL, 0x9EE2A002234E4599ULL, 0xC5538B077A356FBDULL, 0x58E3B7B004ED240EULL, 
            0xE528C77BD1F8D3E1ULL, 0x41BAA1DCB03FEE04ULL, 0x268D8712B23A4CA5ULL, 0x51C63983F6ACDB37ULL
        },
        {
            0x8CF4A5F7B9F9CBE8ULL, 0x632CBD8CC928C9ECULL, 0xFC8BD5179297E9B5ULL, 0x574F10EE844D59BAULL, 
            0x9BAF712A477C4681ULL, 0x0A072028A725C3D8ULL, 0xD54DE6680A0F573CULL, 0xB229665D7DFA895EULL, 
            0xE86992FB783EC10BULL, 0xF43643B2FED7149CULL, 0xC3FF0DAFCC357A43ULL, 0xD326D69249C52ADBULL, 
            0x714298B5549731A2ULL, 0x634821BD7BA42C49ULL, 0x0E05E772F1AF2E27ULL, 0x8950A613AF984486ULL, 
            0xDC37ADEE4C80BABAULL, 0x3E82B9C4BCC4A119ULL, 0x29D95C3304477DCCULL, 0x63A48001266160F1ULL, 
            0xB257ABC248C91F59ULL, 0x28F6EBF463594A14ULL, 0x01952E94EC01D755ULL, 0x78B145D138DF955EULL, 
            0x370F4231EC9A92E0ULL, 0x5845BD748F2B6DE0ULL, 0x58AEB59F414A2F0AULL, 0xF24CEFE58B36827DULL, 
            0x4C8438E48D56AE7AULL, 0x3657E0EDAC6BD31CULL, 0xBC3324FB36A935DEULL, 0xBBD38E4898FAA9D2ULL
        }
    },
    {
        {
            0xBB7F9D276A3116B9ULL, 0x1A98295BA5EB191BULL, 0x1681AE71B5819EB6ULL, 0xDCBCED9E7606F988ULL, 
            0xBC949F32FFE4203EULL, 0x72A7206A31099550ULL, 0x85EA80DB517D940DULL, 0x5539CF6080D76C8FULL, 
            0x4507EAE240AE7E9EULL, 0xE0FE5BAD3E07E50BULL, 0xC93DCB98CA9BD4D9ULL, 0xE380E16836459F75ULL, 
            0x95EC1DA8700A731FULL, 0x9AF16B591B54FD05ULL, 0xD3744989A07B5D41ULL, 0x92F3DC954F708682ULL, 
            0xF58D81DF79B4539AULL, 0xBB7521F3BB63DCB9ULL, 0x586E802FEF0C6BF9ULL, 0xE56E3057192EBB9BULL, 
            0xD0EBB4C6FEC80974ULL, 0xCB5CFAAAF9C68571ULL, 0x187B5443661564E1ULL, 0xF183E45161E567B8ULL, 
            0x4AFF8BB1896A5713ULL, 0xA8C66A4F4804CC74ULL, 0x09446654EA1434C5ULL, 0x6660D8557C05D879ULL, 
            0x625C88131C561BF0ULL, 0xE5BCF28DA9844630ULL, 0x87FBF66655D935DAULL, 0x3CB44E2BF0F0E57EULL
        },
        {
            0xCB72D954C738154DULL, 0x47691A0C434C6B2CULL, 0xADC7FA06AB95F543ULL, 0xC3E02E241BDB1D17ULL, 
            0xA047A91734B1FA3BULL, 0xFA351FC559647D83ULL, 0x7A3EF485898E2F24ULL, 0x631A5926753A010AULL, 
            0x7C2B21917FB39BD0ULL, 0xB676A66FA802771EULL, 0xE8BCF664C9C7A564ULL, 0x9B8595E161D40641ULL, 
            0x8534F6AD4DEB77ADULL, 0x307F66DFE9809D02ULL, 0x16C543A1D949FD3DULL, 0x471FF8EC229169FAULL, 
            0xA1F58C8D4C51ED24ULL, 0x91A854AACC86D47AULL, 0x4FFA64CAD1EFFA87ULL, 0x72C62382EA5546DCULL, 
            0x0C85209B70217637ULL, 0x1437C0D5869E3DDEULL, 0x05DCD476507D860DULL, 0x6B086A65C8C79390ULL, 
            0x3BF5BFB330AE09E5ULL, 0x26442D23950982BFULL, 0x7BEA483600F6CD47ULL, 0x8BD36F7A2D88FA22ULL, 
            0xD480F00C48D50DD8ULL, 0x44A283E3A75161CCULL, 0x2D1D95690AA2F2F3ULL, 0x7143B2A78FC9E8D9ULL
        },
        {
            0x0DB757CFC74D43BCULL, 0x738501402CFC33D2ULL, 0xF1B25EE868920111ULL, 0x8FEF3315E7F4FB8DULL, 
            0xA939241F0E785DF3ULL, 0x4AFAC198108FE0B1ULL, 0x5101D1E1885FFD68ULL, 0x57EF381EF594869EULL, 
            0xD1E4D507A29FB804ULL, 0xCEA84D72BC022F72ULL, 0x3F1F21E5A13AD2DCULL, 0xD530ADDDBAE52D57ULL, 
            0xF640B0494376DA3CULL, 0x1E5CBEFC38A7C03AULL, 0xD993532CC6DAA1A8ULL, 0x9A3E47062B2E1DF0ULL, 
            0xE308CBB0E44040B7ULL, 0x56C7341220737B7DULL, 0xDD628EEFEE368EC0ULL, 0x600BDAE9BFAB699EULL, 
            0xAF1CEF3D100F9268ULL, 0x7BDF1D029660140FULL, 0x716BB2E3BC1867DBULL, 0xBBFAC03884B2E84EULL, 
            0x7C10D3E04E6E2D3EULL, 0x109DD52A47CF6863ULL, 0xB2E3EA3A2B9D2505ULL, 0x91BC684B0C27F376ULL, 
            0xDC24277E81CFA41CULL, 0x9A55CE4287992DC8ULL, 0xE977E1A0D9C6E05AULL, 0x90FAA3469C3A2912ULL
        },
        {
            0x6B807361BB91C72CULL, 0x6A356E6F799ABB02ULL, 0x8B4BB04C115BC98AULL, 0xA5EC29D4543D1D9CULL, 
            0x1CBB99E017E4CA5BULL, 0xD28CEF75C036AD30ULL, 0x570963A54BEBFEB2ULL, 0xA4CA89DA0273C86CULL, 
            0x1C90589AB823A2ACULL, 0xE5157C190A8FEC19ULL, 0xC3485DCE1857FD90ULL, 0x9D0D057D0CD91861ULL, 
            0xB2B0C0D4747E191EULL, 0x46DECF9177A4809DULL, 0x568631427D76B1F1ULL, 0x118A25A4A3B0B652ULL, 
            0x01273085B2D03AFAULL, 0xD9FE88FCACDC17B2ULL, 0x6BDAE28AF87BECDAULL, 0x8B05C4EF81C8E97BULL, 
            0x36EDE8678AFF8C32ULL, 0x0003443C31693053ULL, 0xBB53BAC86D80E17DULL, 0x3ACA9FDEB245FFFBULL, 
            0x6E63A85BFB68858AULL, 0x2C2900E71F232060ULL, 0xE63539962C180675ULL, 0xED7B28641224712DULL, 
            0xEF63BD3433034865ULL, 0x3265C582C4C2EEA4ULL, 0x53EC0BC477CAB5FBULL, 0x9CBFC80D6F1D65D7ULL
        },
        {
            0xF753D93C07462F8DULL, 0x4BB7B761DA471E9AULL, 0xEBAD3C7A539AA358ULL, 0xD324CA94F07835E8ULL, 
            0xEC04ADAFD31ED67FULL, 0x997DBEE62BFA1B4AULL, 0x0F96DC5D9D2E1143ULL, 0xD7E739049C4D6A33ULL, 
            0x4BA81749A4DA8998ULL, 0xBF4BD424AA5AD2D8ULL, 0x687D32380FD4040EULL, 0x875FBB5924EB0DC6ULL, 
            0xFF89AC088C407F75ULL, 0x5D7E9BA678F8687BULL, 0xEBC3329EFCD4D2B0ULL, 0x444ABA775C764310ULL, 
            0x045C6B35251D4ABCULL, 0x9C293CE3965F0E05ULL, 0xCC26793907FA98A1ULL, 0xCA0AFE68D6403DA1ULL, 
            0x48B01DB15041B90CULL, 0x46B137CBA6C7B934ULL, 0x58D8F4E9E452DADDULL, 0x43F3DF2E6E6D44D5ULL, 
            0x854739ECF2C5A2C6ULL, 0x2AF384DB286BB301ULL, 0x400132AFDF36BF76ULL, 0xDE72D35AD0EB7832ULL, 
            0x82987A4607413FD1ULL, 0xF809CA0E0E6C90AEULL, 0x328F06490E58B9B8ULL, 0xE543CBD5579422E9ULL
        },
        {
            0x75DD6CCDDE36C137ULL, 0x35FF2BA84083D34DULL, 0x13E105AA77CF6351ULL, 0x6BD01C1400FC2451ULL, 
            0xFACE1D69F32654ADULL, 0x897C42741AA99BA9ULL, 0x96F3B6E9EF7BCB3CULL, 0xCF995924D312EE33ULL, 
            0x9B3705BBAC4F930AULL, 0x7CC792354A80FBD0ULL, 0x3BAD5FA5EE2311D6ULL, 0x131E3CDF60479D92ULL, 
            0x296D7EC4F0D24612ULL, 0x55B1B148C09E924AULL, 0xFF822B0C1A5C4DB4ULL, 0x153DB684994841C9ULL, 
            0xDCB83D493CE6F7F1ULL, 0x9DADB7396A01A3CBULL, 0xE0A3D20707DC6A02ULL, 0x4F69FCBB888D961FULL, 
            0x5B3D66E741D7ECCEULL, 0xC39F7B31EA7C9D27ULL, 0x4884375621711856ULL, 0x3B38F30F2AB9D042ULL, 
            0x751003C0D33ED266ULL, 0x102A2653B0568544ULL, 0xEBB6A8D37462398CULL, 0x481DE475A8C1178BULL, 
            0x9963E5C5CB4C48BBULL, 0x47B615DA3C001655ULL, 0xE3846CBF1C79AF09ULL, 0x314E5259E48F24D9ULL
        }
    },
    {
        {
            0xF82245F39C4BD50EULL, 0x0FF57CF417E5C876ULL, 0x1258B201AE8AC40DULL, 0xDC39A17C77113175ULL, 
            0x8375BDD722C0DFEDULL, 0x54D81FBF5818FB20ULL, 0xA3ED400E70F337EBULL, 0xA683C40ED4BC2130ULL, 
            0x3FDBE0DAC64AF767ULL, 0xB67C92B86B96D13DULL, 0xA4B0726009D937A8ULL, 0x2F979414AED798B6ULL, 
            0x28DC9E62106B96A0ULL, 0x9DDB10AAA1FAE871ULL, 0x5F44B8135FB31693ULL, 0x8268B1F7A2D128DEULL, 
            0xF0714E0CA8E3055BULL, 0xA3B2CC4879F247E5ULL, 0x95CB104A1AEB16C5ULL, 0xD2B589B7CE4428D3ULL, 
            0xB905665F3B645DD4ULL, 0xCDF09503AF51445AULL, 0xA272DBFCEB1262B2ULL, 0xBB99FF51222099FBULL, 
            0x6287F8AAB0A07CEBULL, 0x38F440BAB647232CULL, 0x15906BE2DA916727ULL, 0xB19C86A838ECF723ULL, 
            0xFD1E89F635A62690ULL, 0xD589451E1308497FULL, 0x03ADD741581D37BCULL, 0x66A22278142A5662ULL
        },
        {
            0xEF6E064D72767850ULL, 0xAF4DE24A1D9B2B33ULL, 0x177FBE05DE91705CULL, 0x6F501D64308604EAULL, 
            0x7F381BCF191AD436ULL, 0x65EF1FD6CA5FF890ULL, 0xBEF14F80ED811498ULL, 0xF6DA5ABB7AC398D5ULL, 
            0x2A733026CA41A500ULL, 0xFD5B1408194761B4ULL, 0xA0EFC0DD3C3969EAULL, 0xA57CC29A57392AE2ULL, 
            0x9836EB387CFB8D8DULL, 0xE5DE035EF5B7D0BBULL, 0xA87CD55FB245633CULL, 0xF187E370FAECBD11ULL, 
            0x28141A55E3E3C750ULL, 0xBCCA183358530961ULL, 0x6A145117B9BA7A6BULL, 0xC0CE6E6DCF04B805ULL, 
            0xCCD1924CEE952D9DULL, 0x1EF07165150E1A0FULL, 0x9386DCD22F934520ULL, 0x753364AA79964F5FULL, 
            0x8555037B1C6FB5DCULL, 0x92C0ED1A8A2C8222ULL, 0x335C4858D06EBA7DULL, 0x2226720466517FD0ULL, 
            0x2DBE5C4B093E6738ULL, 0x162B13429068DFAFULL, 0x89914509D2E7002CULL, 0xEC80701FCFDFA54EULL
        },
        {
            0x044C42EB49137538ULL, 0x4A179DF2330AC918ULL, 0xD266BF1FFB8F26ABULL, 0x2E57849E7611CC30ULL, 
            0x4E61608EDEF8DF8BULL, 0x5BC7831CDF7AE6A3ULL, 0x43D3013CCE6EA619ULL, 0x62B0001FEF9C4829ULL, 
            0x52071FF163AC3205ULL, 0x293BBEEDBCC3ED54ULL, 0xA0AFAECFA9F8B1A8ULL, 0xE24D99F330468378ULL, 
            0x45C769059BE4ABA4ULL, 0xDECF364E0FD6630BULL, 0x6BA5213FE2BA04C0ULL, 0xB80D87E1D9661749ULL, 
            0xFEF17F68FBDF15D1ULL, 0x25DBCCA0751E3072ULL, 0xF6667E1D9F0061FFULL, 0x23E8342CA5EE286DULL, 
            0x2601055CC29C6B4BULL, 0xBA8602382097D0D8ULL, 0x5559CED84119C290ULL, 0xBE3439419036B1E5ULL, 
            0xE96B87DFF18718D3ULL, 0xC98A0629FF5715C8ULL, 0xEBA7CF5C9B4077F2ULL, 0x5FC479D863B095FFULL, 
            0xAA3310C5A8014367ULL, 0x64AA379DA8DF1D06ULL, 0x587E9A7495F72CC5ULL, 0x13409264C307E02DULL
        },
        {
            0xDCF7CAEC68DFA534ULL, 0x2F788104E835CD50ULL, 0xA7770A86A252D235ULL, 0xFDC6137292CD8D57ULL, 
            0xD51D6094650E8A6DULL, 0x319E876379F1C49EULL, 0xE75E2079FA203B3CULL, 0x8CD0F8938DD8812FULL, 
            0x012F185E7E5DE2CAULL, 0x87641709ADE7D5AEULL, 0x89465E6E415F2CB1ULL, 0x265B050D496C2B32ULL, 
            0x855B7C7995294E24ULL, 0x4B09A90AF5CCD867ULL, 0x65C68DB5B60C20FAULL, 0x43444DD406DDB062ULL, 
            0x3E475041A6E27109ULL, 0xDF79426F4D820828ULL, 0xC5F2DF6EDB20696EULL, 0x5E428604E2A2562AULL, 
            0x4301DDAA9B4B2B52ULL, 0x4C828BD87590E9FFULL, 0xA9502ADB75092E67ULL, 0xA711D2165F1AC320ULL, 
            0xD0AFFC87D1451B3AULL, 0x71B091B6ADB71D4FULL, 0x00507FB7EE249207ULL, 0xE1963833C58183E9ULL, 
            0xF8B3AFEA2FE29C73ULL, 0x81C3A217D1656D4BULL, 0x0441FC2973321FBEULL, 0xC56DA4F3A222840FULL
        },
        {
            0x34E8234F691371E4ULL, 0x0C93B1118BEB672BULL, 0x2C3FDFE42DA5BFD4ULL, 0xB0E691EC65ACE5B6ULL, 
            0x3BD45C9061E70967ULL, 0xA5EB23D26CCABD87ULL, 0xF4BE8B01451732DBULL, 0x8E54AB1D307A577BULL, 
            0x4985680E82C0D60BULL, 0x1E8F185B77A98266ULL, 0x817144D5D52BF999ULL, 0xAD97E290D118C2EDULL, 
            0x0E4092399C26C6ADULL, 0x73AF41534AC9B7B1ULL, 0xBCC93F1DC1600F63ULL, 0xFC633B5866048C72ULL, 
            0x7E5C50D83A6F1829ULL, 0x1EB5CD7462D90F21ULL, 0xBEBF4CB2E2FC9185ULL, 0x8FD0814B7C9B7E11ULL, 
            0x73BE39735ECE0D39ULL, 0xB95BEB2E163B14F5ULL, 0xC7CD7ABDCD90A3E9ULL, 0x5803ED7C43D0F80EULL, 
            0x633507A6030FB2ABULL, 0xC59C3D64F9CC1257ULL, 0xD15E1FBFB400E688ULL, 0x1891CAF66C73D358ULL, 
            0x4887ED997DD23285ULL, 0xB75ADCF45E58F6B5ULL, 0x44A1F3497202A41FULL, 0x1D814B5BFF7E73C3ULL
        },
        {
            0xC112610E6AF3EACFULL, 0x8445ABD8502C0D38ULL, 0x9FCF14B6C7A942D1ULL, 0xA3E029C9CC9B7CFDULL, 
            0x681A30844AA8B2F2ULL, 0x847B70F7BA2B922CULL, 0x829900C1509DF382ULL, 0x0C9FF4F3EFF62198ULL, 
            0x325F6F957936C8CBULL, 0x880E37BCF3702AB4ULL, 0x3A57D0F57A77600EULL, 0x1F4EAFB528C65B62ULL, 
            0x49B80FC961BE0DA4ULL, 0x7CDAED3B5CDD8A92ULL, 0x81F11EE287180013ULL, 0x22ADEFB299C263ABULL, 
            0xB1B21E86EC55323BULL, 0x2920FAB3DC752923ULL, 0x8EECB083118D6EC5ULL, 0x588DA1FB5B827720ULL, 
            0xDC028710D435A3B9ULL, 0x6D69551558A12786ULL, 0xC42BC6DB579C148EULL, 0x63D411D6A1DDB05EULL, 
            0xEDEEDCC0F2739428ULL, 0x0E251B3451B9EDECULL, 0xF044ECEC45C8ACAFULL, 0xC7917BCBE5B92BDEULL, 
            0x2DC76F8BDE2798B1ULL, 0x334CD6E0878DD537ULL, 0x06DBE23182B18613ULL, 0xD94952B26B2630B4ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Naos::kPhaseGConstants = {
    0x3F870F53909F0B29ULL,
    0x6DD08E8CC82E0E1FULL,
    0xF9231BE15E47C696ULL,
    0x3F870F53909F0B29ULL,
    0x6DD08E8CC82E0E1FULL,
    0xF9231BE15E47C696ULL,
    0x392D768CAC84DA0CULL,
    0x6149C9CDB3090E10ULL,
    0xC4,
    0xA0,
    0xB3,
    0x14,
    0xE4,
    0xD5,
    0xCB,
    0x88
};

const TwistDomainSaltSet TwistExpander_Naos::kPhaseHSalts = {
    {
        {
            0x7D3C8FE74C1CBE74ULL, 0xAAA102DD45834EE9ULL, 0xFF01E90CE2C28601ULL, 0x4B1901B02E624947ULL, 
            0x125C4615C2A2DDA8ULL, 0x1ED4BA64B07ECB81ULL, 0x2605CB7D4BCAC1B3ULL, 0xE42D7C51FB9A131BULL, 
            0xF02A604BB37F5638ULL, 0xE1F8A0B874CD5C37ULL, 0x550293A4DA95F116ULL, 0xA46F8CA16DFE11C5ULL, 
            0xD9352E065CEC3E04ULL, 0x457124B1C303E7CCULL, 0x737E884A2636D01FULL, 0x7E25B1990B036C73ULL, 
            0xBEB741BDFB85F640ULL, 0xA92464086C6673A2ULL, 0xEF49075A850F4FC8ULL, 0x69927A73F22744A4ULL, 
            0xE93BE9EA7C00E53EULL, 0x3845537972026239ULL, 0xF2BA18B7F7943DB3ULL, 0x3E947A2CAD593BC0ULL, 
            0x9995C03C55DD8803ULL, 0xA0002CC8910014FBULL, 0xE1A9D16E16E87884ULL, 0x0C6DCAECDF22BC98ULL, 
            0x828C3E3E80B510D0ULL, 0xD179893422F41D34ULL, 0x8B06C0D172315292ULL, 0xE455E848079BF508ULL
        },
        {
            0x6A2861053C424180ULL, 0xAA72AE4FE7ABBDB9ULL, 0x333CBA93D21996A7ULL, 0xFC1F1719921695ADULL, 
            0xA397F6C21FAD8D04ULL, 0x3A7B86319CA2568FULL, 0xCDAC11DA6CE455C9ULL, 0xD3CCB5C6672ADF58ULL, 
            0xB70993BD9EA1769AULL, 0x68FE43F0C1940BBAULL, 0xF674B965412031B2ULL, 0x315AFF0270BC47E3ULL, 
            0x859A00DECD72061BULL, 0x38FEF54E354F8B92ULL, 0x78875668DA223055ULL, 0xCB2C4AF2B428F0EBULL, 
            0x49A4708BE66EF72EULL, 0x7DD796E5C759C331ULL, 0xEB89737402174BA7ULL, 0xECD9A8F4191C8DACULL, 
            0x1ACF0FB4DC9F880CULL, 0xB5A7B063E966C9EFULL, 0x3D442E0F75CF33B5ULL, 0x0116A71891C72C80ULL, 
            0x6FFB2A640B84975AULL, 0x6676DCFE88DB92D3ULL, 0x4745D8A4EDA5D06FULL, 0x1BD106B6A44B320DULL, 
            0x039636BC7E3487ACULL, 0x0A0C16BB8CC95443ULL, 0x4263FC446C0EDEBEULL, 0x620E2410E929E821ULL
        },
        {
            0xD3BD5EC88E47544FULL, 0xB76958EB86134BD0ULL, 0x8377752AFCC4966DULL, 0x2FB2EDA0A98D06B0ULL, 
            0x6A1EB2C1CF92E1E2ULL, 0x16F3AF58E8F83C7BULL, 0xA102EF138AA4CABCULL, 0xA28DB6D56600DE25ULL, 
            0x23053741726F1FA7ULL, 0xFF931774368FF272ULL, 0xF89B545A4D1A1CD0ULL, 0xB88CBDFBCFDD4ECEULL, 
            0x5D08F90BB147802AULL, 0xA58FC9482D08CC47ULL, 0x5DA4908D7C204C48ULL, 0x4561514CF0B9BC3AULL, 
            0x09E105ADCF1284D0ULL, 0xAC9E60B622F93C3EULL, 0xA8BEE97153E6A2C4ULL, 0xB6D87F01A40C20C8ULL, 
            0x0485C7CA1E0A709AULL, 0x298549B223BA6D9EULL, 0x24734051D4E77D5BULL, 0xD318522BFE6674CAULL, 
            0x5F69F5F8B746B9F0ULL, 0x2CFB2A70A7B49167ULL, 0xFBE11C77E7C52296ULL, 0xF6ED3E2ACA2B372FULL, 
            0x398A47EBE007C756ULL, 0x92AA8FDF9DB10853ULL, 0xEC5368BC5DCCAE11ULL, 0x10EBEE012DD002EDULL
        },
        {
            0x996ACBD56F44D6C5ULL, 0xA51BA26013700EFBULL, 0x6820F8EEA5A926FFULL, 0xE33B8C51FB10F1E2ULL, 
            0x447CE9E4098B5B13ULL, 0x4AD47EE0146098FBULL, 0xF0AE826AA936D296ULL, 0xEE41469127A08750ULL, 
            0x29A25135FE35C664ULL, 0x43ACE2C9A00EE89DULL, 0x994AFAA667F8C9F8ULL, 0x7C1D6B96B36BC425ULL, 
            0x3FF3D5CAF8A58B59ULL, 0x928BCB99D754600DULL, 0x47BE89FB8BC46F42ULL, 0x992CFEC7EFC2CC88ULL, 
            0x9D9414F019B86619ULL, 0x60882E5B74DC9794ULL, 0xEB90C25D17C7479EULL, 0x70D52BEFCB613F76ULL, 
            0x6105C293DC46BC4BULL, 0x5D4F6863CF74F7D2ULL, 0x24AC49A1544460ADULL, 0x71C3C8262652156FULL, 
            0x55AB9642ACB598FFULL, 0x2D13DD738A8839C6ULL, 0x30DDC82C97A09B74ULL, 0xF2F6DA266C19C83EULL, 
            0x6E889B4D7B7E7465ULL, 0x0C93DC48E000891DULL, 0xDEEB46DDBADD3943ULL, 0x804E4EF2F6703750ULL
        },
        {
            0x6A851E070B3F0CDFULL, 0xF62F26F1C4A5C65FULL, 0x9F1B2AAE9C7374E3ULL, 0x4949078C7225C4E1ULL, 
            0xCB8E5144F448527FULL, 0x341944908693DACDULL, 0x90BFAD55AD931CCAULL, 0xDAC1D91E0BB5968BULL, 
            0xFAAA7DD50590B551ULL, 0xE3C2163F44BBA688ULL, 0x8189A0C58223B39DULL, 0x28B190EC8C4EB220ULL, 
            0x69A9515FFCEC3C4BULL, 0x3635A309103E341EULL, 0xBA6C3F947D4EF06AULL, 0x1B4E04598879883FULL, 
            0xC6C3596FD19BD195ULL, 0x4B6C0F81F7D7C8E5ULL, 0xD23F11B915DCE464ULL, 0x6EE31FEA41F62C3FULL, 
            0x1B679506931B6570ULL, 0xC12921F7AD5B3374ULL, 0xC7CB1028E3D497BBULL, 0xE0E1880BC95F34F6ULL, 
            0x9C7263878449080AULL, 0xE49CF9ECA778154EULL, 0xCB764CEF6CFE2283ULL, 0xCE71A432CF1F54B7ULL, 
            0x1AF8B97259D92981ULL, 0xB03CE0E03AEAFD20ULL, 0x1289848A1EF622CAULL, 0xBFE8BA97D558B43BULL
        },
        {
            0xC9AB2CF101FC42ADULL, 0x1E9A9AFD31351EF5ULL, 0x57D900FF7C410F6EULL, 0x28A4DA0C794AECE5ULL, 
            0x0A53997850E24D9BULL, 0xD7E5F4C654DB4F90ULL, 0x869A8819A225B1FCULL, 0x38B4CB0C3F783E8FULL, 
            0x3FC8E4F1FB1DB425ULL, 0x95E13F6D68128C43ULL, 0x14DCF00CAF232771ULL, 0x988806BF9C2C579FULL, 
            0x741AA2AD145C569AULL, 0x1D2F782F58D77054ULL, 0x6D325E1D59DB466BULL, 0xE7CE7D043916AFA8ULL, 
            0xCABD86A7C038D120ULL, 0x648F0B70234220FDULL, 0x800459924124015CULL, 0x5D6CB12058DABC69ULL, 
            0xCDAEE84DF0019427ULL, 0x9BBF5C2DBE7C0FA4ULL, 0x9CDB30F80EAD4270ULL, 0x5F3CECBBF3E81AF5ULL, 
            0xAFB4DDD23A1228CFULL, 0xA70C572473F61C55ULL, 0x83977EBAFE957535ULL, 0x51FB1D842C55C8B7ULL, 
            0xA3096BFA03DE93F5ULL, 0x3BE2FBDCA1A04F2BULL, 0x98110C1637834597ULL, 0x2CD4242A75C6913CULL
        }
    },
    {
        {
            0xAC19D8BFCB742F1CULL, 0x92448143EF073771ULL, 0x152559DB286E3A86ULL, 0xFF39004151FCFD98ULL, 
            0xCCE286473E700326ULL, 0x97EA3E0F837DE8BCULL, 0x6D42EE9F0B86BECCULL, 0x993E92E4F866E507ULL, 
            0x358087F7EE09B9A6ULL, 0xD566E123B59898A2ULL, 0x41617CAE58EFFBC8ULL, 0x3001B114947720C0ULL, 
            0xD740E310163430B0ULL, 0x576A3E6A3E8DB39FULL, 0x77E40A6A58B5D8ECULL, 0x83CB80466CEA4D7DULL, 
            0xC6E908F1F831CA08ULL, 0xA1DCFB9484898410ULL, 0x5546CD7EA6543617ULL, 0xC988180D2C710401ULL, 
            0x8ECD3A9B14E8ECD1ULL, 0xAC3D2713F9877189ULL, 0x0B0827CAC4039149ULL, 0x21A44806CEF3F910ULL, 
            0x8014A7351D2F5431ULL, 0xD841692AFF416734ULL, 0x73D4591A62324290ULL, 0x9BF44B9A8E41CC40ULL, 
            0x9D6D287A190F19ACULL, 0x944572463B0705E2ULL, 0xA2D80C89D54B40FCULL, 0xEEEECB30079FB1E9ULL
        },
        {
            0x746F8D0AB0696605ULL, 0x932AA597D16398EFULL, 0x047E073ABA81A1ECULL, 0x00EC66BB17E2DD65ULL, 
            0x96196B9E9D0CC27EULL, 0x0D093FA6D80E7172ULL, 0x3E02FCCCD639CB24ULL, 0x12AF5676F942AA4DULL, 
            0xCDA26B4ADE6EE6BEULL, 0xF6FE52DEFCF6F416ULL, 0x511EEA98290600C8ULL, 0x6A9A402F80827759ULL, 
            0x48912BB4CAD11793ULL, 0xA13E04551C031F14ULL, 0x915BA937E4F549EFULL, 0x5B4D5AE594AED2A0ULL, 
            0xC41751430F22F88AULL, 0xDD7421C82317D8C2ULL, 0xE5CD12610234DAECULL, 0x150B26D292DA43F5ULL, 
            0x2A25C231E37AF60EULL, 0x18F7674CDB037D35ULL, 0x79235E7DD8613CFEULL, 0xBFD92F5EE8795570ULL, 
            0xFFF92DC6EAC51E85ULL, 0xE30A6E41434695D9ULL, 0xE10F66374B6606B7ULL, 0x269C9FF2F3AE4584ULL, 
            0xD3A23971FDEEFF6EULL, 0x2592D666EEC684A6ULL, 0x02F03CD00EAF27F1ULL, 0x1C7C94D77A576F1AULL
        },
        {
            0x71B72F4593915F14ULL, 0x6C877817C5D65A2CULL, 0xA8D227E99E327551ULL, 0x10F0FEA168F86B56ULL, 
            0x677279E72469FE73ULL, 0x69BBDED9F63B1E90ULL, 0x26C3FE130587632BULL, 0x8C0BF4F342680D7EULL, 
            0x401492F941AE50CEULL, 0x7B3433DFAFEF8900ULL, 0x547444CF428E87CAULL, 0x63E73BD7C3A48ED4ULL, 
            0x59A378E581D66A97ULL, 0x8B55F366DBEB4B88ULL, 0xA44A68D503EE949EULL, 0xC635A6E031F5F6E7ULL, 
            0xB404069526110E43ULL, 0xF401EFDC40BD73D4ULL, 0x4B42546D4E895AFBULL, 0xD01A28D680DBB68BULL, 
            0x0853071EF84D0754ULL, 0xBAC139D81D6E7951ULL, 0x6ED3341C8D4612B0ULL, 0xB5FEF925A6D9F8E4ULL, 
            0xFBB2B8F1C0EB4C72ULL, 0xD53499E489777350ULL, 0xC4827A7EB3FFF2E0ULL, 0x7F42676921FCEFF6ULL, 
            0xC917BFFBD8F684A8ULL, 0xF52DD9B7B39738FFULL, 0xD8AA5F02DDEFB2FAULL, 0x34794FC3287F09F2ULL
        },
        {
            0x9B78918052C3571EULL, 0x547F1B0BC7EB889AULL, 0x6CAB17B8CA231317ULL, 0xE91D62F9DA1C7720ULL, 
            0xF26BF84FF9DD6835ULL, 0x0EA07C7DEA490271ULL, 0x5DA69751D6058F85ULL, 0xE61A56966A8D065EULL, 
            0xEAD7BDC94F0E2046ULL, 0xE857F2953D1305C4ULL, 0x4074AA585D8AFC2EULL, 0xF7F96A2F63357EC4ULL, 
            0x650426B176E76A02ULL, 0xB9E31863437239CFULL, 0xA15911065D5033DDULL, 0xEC643AD3DDC0DDCFULL, 
            0x8CEE19AD0FAA6DA7ULL, 0x0DA6028FC7C79302ULL, 0xB745CD9C027575B5ULL, 0x30A8AE7340BD7EADULL, 
            0xC9C47DA10078B204ULL, 0xF41EE05D07A0C94AULL, 0xACBE4FC48A8077C7ULL, 0x75CF404FE2265FB3ULL, 
            0x136BFAAA3D7E44EEULL, 0x751208141CEA9CFAULL, 0xDF78374AE7F883E8ULL, 0xEDA9B3544C174A51ULL, 
            0xBDAD2B713A0F322EULL, 0x3AFF42FB848E6C99ULL, 0xCF61ACD3D25DC33EULL, 0xC30E4696C9C86955ULL
        },
        {
            0xFBED4FAAAFC5E9EFULL, 0xCCBA287E32958F41ULL, 0x03E891C3A9C5CFE9ULL, 0x673D06FE1D3BB6C4ULL, 
            0x8CC19FA76B74DBC7ULL, 0x3F0438E27644A296ULL, 0x97CAAC064A92420FULL, 0x0F07BEFDE3778C3DULL, 
            0xBCE23AEC1F2B90F5ULL, 0xB015527B6D1CE4B2ULL, 0x2F8CB0769B7E9387ULL, 0xAB1B92029E3985C6ULL, 
            0x610828A12B17BFE5ULL, 0x14BF757BA7950827ULL, 0xD5B2B2371E937514ULL, 0xB5BC56C57B2762C2ULL, 
            0x7E263ABBC726987FULL, 0x1C3378A8FB78AA34ULL, 0x7766B672300B37CEULL, 0x435C8EC255A80B9AULL, 
            0xB1A9097DD9686AF0ULL, 0x7BB4A77804C3F6EFULL, 0xA471767C1B39A0FDULL, 0xEB49AAB2A01EF5F5ULL, 
            0x4533785CAD3D90C1ULL, 0x62AAA2C974E61586ULL, 0xEE4D4D9CD90F096AULL, 0x241E46C1DA724942ULL, 
            0xDF31843E9F6F8F34ULL, 0x36C7B74A07032252ULL, 0x95B7505AB7B0B6C7ULL, 0x5822E92FFDD3823BULL
        },
        {
            0x04A9AF73A3AA23C2ULL, 0x7D52CA236B26195EULL, 0x7D967818D637AB25ULL, 0x0654CB99699C741CULL, 
            0x6490E853103A0F19ULL, 0x297D9E8D1F8C8725ULL, 0x92BD8AA6A158A987ULL, 0xC68247A32CA1ED6BULL, 
            0x94B82D68B6D30E53ULL, 0x4BAF2E0BE6C960D8ULL, 0x73C1FAC91DDC58E8ULL, 0xFCF7801926F0CE52ULL, 
            0x481289065431168BULL, 0x09D92864D39C1DB3ULL, 0xA3005EF495565503ULL, 0x4D5CBCCE0D5A7FBCULL, 
            0xEC208A960B0CE533ULL, 0x63500DDC45AAA342ULL, 0x4CF4E559A98BD810ULL, 0x79502212FFBFF8BCULL, 
            0xF394F7C4181E98E0ULL, 0x97521061C03BD6E8ULL, 0x61D6627946C867C3ULL, 0xBC1165AA77D3417CULL, 
            0xA082C959DEEAD599ULL, 0x0438B2CCCF24D2D3ULL, 0x7FD0EB6C0D81FFEFULL, 0x6DC50BE89D60387DULL, 
            0xFEFF9EE086E060E7ULL, 0x0FF109BB2BD216BDULL, 0xEE323518B9B9B206ULL, 0xCEAE4B50D0EB4922ULL
        }
    },
    {
        {
            0x92B1271AE843CE2BULL, 0x9E8896959777722DULL, 0xABCA04E3B93F0DF9ULL, 0xD58E9E81B5D11868ULL, 
            0x3FA8A92225488997ULL, 0xC1AABB248DC9B2D3ULL, 0x190C2EF71846671FULL, 0xB352AAF078841010ULL, 
            0x2E70E6EA35A601BEULL, 0x7385CC233320B75DULL, 0x2987FD8CD943C509ULL, 0xA7BB38CD5FF18332ULL, 
            0xDAB85A4FF3D5BA91ULL, 0xCCDDF2E86BFCDEF1ULL, 0xC450C2369BEE8E65ULL, 0x589DA048591B3314ULL, 
            0xDF9F51BE0F4E55B2ULL, 0x27F65936D65BB685ULL, 0xE84B342F4E8745CDULL, 0x44A4A30F6F757115ULL, 
            0x65C189CD6265F6EFULL, 0x946E9C5F2CE40BABULL, 0x1936C9600178AD62ULL, 0x14FBB2E563E62926ULL, 
            0x98962552FDFCBABFULL, 0x4073DB37D5F2FE42ULL, 0xF718266EAE237E4CULL, 0x1A243CA8AC6EC453ULL, 
            0xDC4E526588968054ULL, 0x3B41A3E2FECE3989ULL, 0xEFFE4C579BAE1B42ULL, 0x7F81E72668E1FBA1ULL
        },
        {
            0xB0C4315DC23BE570ULL, 0x0EE802C738500ED4ULL, 0xF4DC4AB4B8AE1665ULL, 0xBA9C2A50B5E723F2ULL, 
            0xC5FF0893C2435B3EULL, 0x3C3CAAD84F6F1FB0ULL, 0x113AB202335FF1F3ULL, 0xE0194D5E95AC4A2FULL, 
            0xB549DDF676C61A3DULL, 0xB604E6668B6000EBULL, 0x6A2DF7B9133B7421ULL, 0x04B582262F805449ULL, 
            0xBCF4AE9F7838DFC4ULL, 0x320C0FC867CB9A17ULL, 0x90A82AE70DB913D9ULL, 0x51B3D34BD5B57E1DULL, 
            0x17127EC0A7103DD9ULL, 0x3599CD6C167B8301ULL, 0x0037953A3B4B488FULL, 0x11F384A781820EEFULL, 
            0x5928E46391B546A5ULL, 0x5943541329838978ULL, 0x67F40D2B2D20F395ULL, 0x388292FF0589A650ULL, 
            0xAF75DB852581E4D0ULL, 0xE3C659239EA1B83AULL, 0xA139F383EED02401ULL, 0x1DFCA3A48E3475E0ULL, 
            0xB64DA8E6A128441DULL, 0xEC747F9008CB828FULL, 0xFA505216AC47CF5EULL, 0xAD4B7A2DD545E0FCULL
        },
        {
            0x3A6994424387261AULL, 0xE943F1258DD0DFB1ULL, 0x96EA69B52EB0E74CULL, 0x82541BDFA6E167F2ULL, 
            0x89F60320111B2B94ULL, 0x471F5A0114AA7440ULL, 0xAC5002A7ACAA6EC7ULL, 0x34184039606CE956ULL, 
            0xC87465BCEC9D5314ULL, 0xE250040594A654E9ULL, 0xB5A372F51B181EA8ULL, 0xB7ED4055338BCCD2ULL, 
            0x9553525A53E86218ULL, 0x1795F4E38F9C2698ULL, 0xA3B4665D102F3FCEULL, 0x9E8F564EF726C09FULL, 
            0xB1C17E0EF0DB3C9DULL, 0x4FB53E6F11A14C9AULL, 0x7DB1F4143302B26DULL, 0xC1DAE0ED5D7C366DULL, 
            0x3FD3F79A050EB488ULL, 0x34DED1624D891DF2ULL, 0x9EDF6013B4DCDE87ULL, 0xF779FC063768851FULL, 
            0x90B6EB7A7044457DULL, 0x3F162D84B6A60AB4ULL, 0x001839189105E9FAULL, 0x617CB11CF2190B3AULL, 
            0x8BCE8A75D02C1A09ULL, 0xC2DCB29B1742BF21ULL, 0xFA40AEAA711BDC0FULL, 0x8312664652CAF4B7ULL
        },
        {
            0xD1ADCEC5A06F19BCULL, 0x7A2D4D4781A79815ULL, 0xBC08BAB12F5532EFULL, 0x0812071BDD744227ULL, 
            0x4BA5C055F84C7065ULL, 0x2142268881694C55ULL, 0x8AA54FF7B8DFD492ULL, 0x0FFC0697144072C2ULL, 
            0x50B1ABD8D4B173E8ULL, 0x6D3CB1282DA3C14FULL, 0xD435829123AB961FULL, 0xBCC86ADED4A851FAULL, 
            0xCE175838D21DBD92ULL, 0x0374B41AC1A5260CULL, 0x6C32A9C9F61E6EA7ULL, 0x9E55EAD0C52C93C6ULL, 
            0xB58328A881DE00B5ULL, 0x00ECD767E5ECF6A4ULL, 0xB1AA568D728C67CCULL, 0x65CE401A9BF5F1A3ULL, 
            0x75858172FABB9AB8ULL, 0xC4AC295D744A6A86ULL, 0x731B9ADCE808CF6EULL, 0x888EEE646F8E9E53ULL, 
            0x220967AA79160933ULL, 0x41E69AE6143C17CEULL, 0xCFE6C51E881DC585ULL, 0xF76049562FCC0586ULL, 
            0x54C2BCF88DF382E8ULL, 0x401E959E20414F21ULL, 0xCB4024C5B21D7385ULL, 0x144F5DC2F4397CADULL
        },
        {
            0xD71152121226EA24ULL, 0xCC9D7AC826E50BA4ULL, 0x23961DDDE4F3F931ULL, 0x8A87792170103152ULL, 
            0x8364CD5B703062D0ULL, 0x943F5083B5D594D1ULL, 0x06E33EC39B8A9A12ULL, 0x3162C1CA88605E6DULL, 
            0x0FE8774B380BE7DDULL, 0x5303BA96B9A3E556ULL, 0xC98502CD616B40CFULL, 0xA552F1B3704C36BDULL, 
            0x8E0B11D7739BE29BULL, 0x840559AF3B0DA93CULL, 0xB12EEF35CC09E3A0ULL, 0x434C0BD7BCD5B56CULL, 
            0x51DC3573C829A50EULL, 0xE00DA1C657FFC51CULL, 0xCC9B2C9FCCF42CB8ULL, 0xA36D62B4E678E950ULL, 
            0x8433870206D3A235ULL, 0x25336B4A0C571A72ULL, 0x5728E58A74745262ULL, 0xB21364945D070489ULL, 
            0x0ED89EFC604EDEB2ULL, 0xE2D232B0AFF30CC3ULL, 0xAD2B395D58CCE8EBULL, 0x2F9FE86E1B715EFAULL, 
            0x7AF6A4DDDDB4C5E9ULL, 0x1C9D649D403ED4FAULL, 0x42A684F2AA459F1BULL, 0x78CC2C14797427C5ULL
        },
        {
            0xD364322131D3221AULL, 0x311C6AFC64A02014ULL, 0xE5D25350DB190731ULL, 0x7FD46F5FD23B725EULL, 
            0xC69EFC6A93418288ULL, 0x6E738645DAA85BABULL, 0x6D86837D60BF938FULL, 0x685D60BB98C739B7ULL, 
            0x9A9B8E22C42FBA79ULL, 0x209E6AD8B8BFD897ULL, 0x8E74D178B3BDE3A3ULL, 0xEDC1402BD41CF8DEULL, 
            0xB6737F0F9D4D5FBBULL, 0x9AD0FBDD94ADE4E6ULL, 0x3C53C04CE016ABB6ULL, 0x22312F960F6836AEULL, 
            0xBD4E1E2497003305ULL, 0x5EBC1866A64CF857ULL, 0xF868227F88920971ULL, 0x2AD180D3E847A110ULL, 
            0xB03186847F5FA6E5ULL, 0x434D04B871F99940ULL, 0x9C0809A4127F5B3CULL, 0xF657A049770D6D74ULL, 
            0xAB7922D54B341A49ULL, 0x01A0E88E2FEF9814ULL, 0x400E250A49CDCEB1ULL, 0x9CF7BDDE19EA11A7ULL, 
            0xFB7A4AE37CDE2891ULL, 0x8247D8BCE661472BULL, 0xE8F8285CC85EA006ULL, 0x2DE1AB0F748B2E9EULL
        }
    }
};

const TwistDomainConstants TwistExpander_Naos::kPhaseHConstants = {
    0xDDAC6071A8D39206ULL,
    0x17138D06E1B71125ULL,
    0x7C9BA3EB5439B977ULL,
    0xDDAC6071A8D39206ULL,
    0x17138D06E1B71125ULL,
    0x7C9BA3EB5439B977ULL,
    0x274E6C70EB40247CULL,
    0xAE0DC3BF6EFCC4E8ULL,
    0x93,
    0xD9,
    0x84,
    0x6A,
    0x3B,
    0xA2,
    0x35,
    0xB4
};

