#include "TwistExpander_Altair.hpp"
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

TwistExpander_Altair::TwistExpander_Altair()
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

void TwistExpander_Altair::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xD8AFE2AD88ADFBADULL; std::uint64_t aIngress = 0xA6FFCCBC3021512EULL; std::uint64_t aCarry = 0xBC2568EC3EF89511ULL;

    std::uint64_t aWandererA = 0xDEB4BA669022618DULL; std::uint64_t aWandererB = 0xA72CEB11B87AE187ULL; std::uint64_t aWandererC = 0xC01ABCF9865E4F94ULL; std::uint64_t aWandererD = 0xD67C4FAB73FE156AULL;
    std::uint64_t aWandererE = 0xDB3A7E9F3CA19C16ULL; std::uint64_t aWandererF = 0xEC11FE0A9F0E013DULL; std::uint64_t aWandererG = 0xEDA81E1845196E4AULL; std::uint64_t aWandererH = 0xA534A5C65795CEB1ULL;
    std::uint64_t aWandererI = 0xD177198E511B0164ULL; std::uint64_t aWandererJ = 0xD13AB7168B985616ULL; std::uint64_t aWandererK = 0xB011379A80340AD7ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 15356375459826739133U;
        aCarry = 15482196185447765311U;
        aWandererA = 15808278536383454192U;
        aWandererB = 14151722374183462873U;
        aWandererC = 11811398777492650988U;
        aWandererD = 12577719999718154277U;
        aWandererE = 14737891098196832264U;
        aWandererF = 9409660129509457334U;
        aWandererG = 12881878435592869865U;
        aWandererH = 11248159777313176055U;
        aWandererI = 18380649690054515266U;
        aWandererJ = 12129630363065065544U;
        aWandererK = 11043133040457914964U;
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
    TwistExpander_Altair_Arx::KDF_A_A(pWorkSpace,
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
    TwistExpander_Altair_Arx::KDF_A_B(pWorkSpace,
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
    TwistExpander_Altair_Arx::KDF_A_C(pWorkSpace,
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
    TwistExpander_Altair_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Altair_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Altair::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0x9E0C785F98EEE24BULL; std::uint64_t aIngress = 0xECF2C345508F703CULL; std::uint64_t aCarry = 0x89F438BAE1674842ULL;

    std::uint64_t aWandererA = 0xFF398B9AC503784AULL; std::uint64_t aWandererB = 0xDE6DD3BC8AD398BBULL; std::uint64_t aWandererC = 0xAAEA313769303EEDULL; std::uint64_t aWandererD = 0xF2FCB93403760963ULL;
    std::uint64_t aWandererE = 0xCD680A33F07CB960ULL; std::uint64_t aWandererF = 0xD6D8FC2EA3BE8FF7ULL; std::uint64_t aWandererG = 0x9F0443F1E8C8C710ULL; std::uint64_t aWandererH = 0xB1E016A3429B5E7EULL;
    std::uint64_t aWandererI = 0x8A2587EEF3D41914ULL; std::uint64_t aWandererJ = 0x801650FC075299F6ULL; std::uint64_t aWandererK = 0xA912948EEEF43986ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 14902185737518028997U;
        aCarry = 12704974979523849183U;
        aWandererA = 10027987590530801707U;
        aWandererB = 12090412634576995983U;
        aWandererC = 15372153750271584509U;
        aWandererD = 11309276421029127996U;
        aWandererE = 13790807440522551351U;
        aWandererF = 13182766266637811314U;
        aWandererG = 12540988427120049333U;
        aWandererH = 16441824748440474015U;
        aWandererI = 9424546822149774689U;
        aWandererJ = 12263019450533952399U;
        aWandererK = 17512389004513595363U;
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
    TwistExpander_Altair_Arx::KDF_B_A(pWorkSpace,
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
    TwistExpander_Altair_Arx::KDF_B_B(pWorkSpace,
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
    TwistExpander_Altair_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Altair_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Altair::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0x81F2CD2D429BF7A1ULL;
    std::uint64_t aIngress = 0x82B160CA43E90D38ULL;
    std::uint64_t aCarry = 0xCD1268D3AB5CA6DDULL;

    std::uint64_t aWandererA = 0x8471A34B3912C593ULL;
    std::uint64_t aWandererB = 0xB87900042F1D90EDULL;
    std::uint64_t aWandererC = 0xAE564DF51868527AULL;
    std::uint64_t aWandererD = 0x9D20239F65F7BC9AULL;
    std::uint64_t aWandererE = 0xF0C29C344E67C0E0ULL;
    std::uint64_t aWandererF = 0x8E9DF6D7EDC90251ULL;
    std::uint64_t aWandererG = 0xF3759CEE5BAAEFF5ULL;
    std::uint64_t aWandererH = 0xA5494C295F53D8CAULL;
    std::uint64_t aWandererI = 0xD551E80FA68A8084ULL;
    std::uint64_t aWandererJ = 0xED8DB8E6D0E4A9B6ULL;
    std::uint64_t aWandererK = 0x81CFEEE4CDCCD288ULL;

    // [seed]
        TwistSnow::AES256Counter(aSource, aSnowLaneA);
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneB);
        TwistSnow::Aria256Counter(aSource, aSnowLaneC);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneF);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneE);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneC);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneG);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneB);
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
    TwistExpander_Altair_Arx::Seed_A(pWorkSpace,
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
    TwistExpander_Altair_Arx::Seed_B(pWorkSpace,
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
    TwistExpander_Altair_Arx::Seed_C(pWorkSpace,
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
    TwistExpander_Altair_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Altair_Arx::Seed_E(pWorkSpace,
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
    TwistExpander_Altair_Arx::Seed_F(pWorkSpace,
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
    TwistExpander_Altair_Arx::Seed_G(pWorkSpace,
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
    TwistExpander_Altair_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Altair_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Altair_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Altair_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 7 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1907 / 1984 (96.12%)
// Total distance from earlier candidates: 11500
void TwistExpander_Altair::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 774U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1152U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 6U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 214U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 22U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 815U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 946U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 348U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 152U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1799U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1905U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1537U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1950U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 61U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 903U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 294U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 659U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1149U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 458U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1209U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1859U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1841U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1512U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 344U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1349U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1806U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 427U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1960U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 870U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 75U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1882U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 582U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1378U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1729U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1921U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1891U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 830U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1395U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 573U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 844U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1666U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1901U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 2004U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 2021U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1610U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1320U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1480U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 856U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 179U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1375U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1500U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1791U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 324U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 491U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1504U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1444U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1890U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1619U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1774U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1103U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 772U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 163U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1290U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1548U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1056U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1064U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 861U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 103U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 77U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1226U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1095U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 528U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1834U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1802U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 418U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 100U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1182U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1853U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 829U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1586U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 476U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 223U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1098U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 594U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1592U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1337U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1959U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1354U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 2017U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1223U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1762U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1838U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 920U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 667U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1380U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1297U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1926U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1957U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 259U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 828U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1085U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 153U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1401U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1481U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 229U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 518U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 392U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 10U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 149U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1626U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 320U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1598U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 59U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 788U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1331U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 743U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 700U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1302U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 675U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1516U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1125U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1584U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 524U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 766U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 511U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1162U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 181U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1596U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }
}

void TwistExpander_Altair::TwistBlock(TwistWorkSpace *pWorkSpace,
                                       std::uint8_t *pSource,
                                       std::uint8_t *pDestination) {
    TwistExpander::TwistBlock(pWorkSpace, pSource, pDestination);
    if ((pWorkSpace == nullptr) || (pDestination == nullptr)) { return; }
    std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    std::uint64_t aPrevious = 0xFC34A6C3C6122BC0ULL; std::uint64_t aIngress = 0xC87B2E7B678C6068ULL; std::uint64_t aCarry = 0xA0129440F4710343ULL;

    std::uint64_t aWandererA = 0xDF6F8831258EF1DCULL; std::uint64_t aWandererB = 0xC4940B1237451BDBULL; std::uint64_t aWandererC = 0xA2BC76E5BCF0FBD0ULL; std::uint64_t aWandererD = 0x9290B15E5BE82F4FULL;
    std::uint64_t aWandererE = 0xE924F6FF99BA8711ULL; std::uint64_t aWandererF = 0xB59F2F7A16FA545FULL; std::uint64_t aWandererG = 0xE5B48E40FAD87B30ULL; std::uint64_t aWandererH = 0xFD90775BA098EDBCULL;
    std::uint64_t aWandererI = 0xE72845FF6C5DDDE7ULL; std::uint64_t aWandererJ = 0x9AA1513AE1A258F7ULL; std::uint64_t aWandererK = 0xB8C8F4A7433A39D2ULL;

    // [seed]
        aPrevious = 16086039283658061136U;
        aCarry = 18431957047825012810U;
        aWandererA = 16131011980450423762U;
        aWandererB = 13372737873648649919U;
        aWandererC = 15811639399349093818U;
        aWandererD = 14388380752658260371U;
        aWandererE = 14832340000048296464U;
        aWandererF = 14722489628831936690U;
        aWandererG = 15933171295697916933U;
        aWandererH = 12508065313779720638U;
        aWandererI = 12893787336766798426U;
        aWandererJ = 14809176698294877127U;
        aWandererK = 12320222181384835828U;
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
    TwistExpander_Altair_Arx::Twist_A(pWorkSpace,
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
    TwistExpander_Altair_Arx::Twist_B(pWorkSpace,
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
    TwistExpander_Altair_Arx::Twist_C(pWorkSpace,
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
    TwistExpander_Altair_Arx::Twist_D(pWorkSpace,
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
    TwistExpander_Altair_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Altair_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Altair_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 7 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 3392; nearest pair: 494 / 674
void TwistExpander_Altair::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 570U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4651U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3096U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2468U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6679U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2344U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7514U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 888U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 166U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3361U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 392U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6730U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6144U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4854U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3513U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2916U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 261U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 249U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1926U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1625U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 300U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1004U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1636U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 824U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 972U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1898U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 923U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 595U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 932U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1079U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 791U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 413U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 95U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 634U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 926U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1901U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 7 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 3387; nearest pair: 514 / 674
void TwistExpander_Altair::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6189U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4912U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2313U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5001U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3421U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4157U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6697U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3355U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 747U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 927U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5560U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3126U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7403U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3680U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4311U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6723U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 924U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 600U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1369U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1934U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 669U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 959U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 147U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1632U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1857U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 584U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 937U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 853U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 904U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 710U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 157U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 960U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 80U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1992U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1851U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 136U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Altair::kPhaseASalts = {
    {
        {
            0xEE32EEE4D63EA656ULL, 0x4C73B30912603A06ULL, 0x521FB9A6E6033810ULL, 0xAE1533085B487F42ULL, 
            0xA692029BEAC02739ULL, 0x9E33148C0C849D68ULL, 0x3DEE7B142D5276FCULL, 0x69F02F9AABC391D7ULL, 
            0xA5D15B5BDF72FCCFULL, 0xBF340DDD6ECA60A7ULL, 0x5A1EBE6AD00C75AEULL, 0x6BA04B857A1FC2E5ULL, 
            0xACD854FFD17093D3ULL, 0x1ABCC52929F0F8DBULL, 0xC80D20590A5D41F0ULL, 0x76B50C70FA3CA8FBULL, 
            0xDEC54CD24D9BA6FEULL, 0x1E8D94A69F8EC45DULL, 0xF142625987D5058BULL, 0x338BBD2B23CFE8B1ULL, 
            0x17CCC4F5A70BED35ULL, 0x81C406F5A42E430BULL, 0x388E3D7870921CBDULL, 0x95A36EF710F671B5ULL, 
            0xE1520F64DB6A7AC8ULL, 0x90C2AE6224D48B76ULL, 0xD9D0C7A9B4A7C913ULL, 0x32F5FDCCAC4864EAULL, 
            0xAE216AAF472E71E5ULL, 0xEDB42307655CFA78ULL, 0x7B0A7AFD0095171DULL, 0x84CADC16943ED305ULL
        },
        {
            0x4C6842BC60A42383ULL, 0xBA004655160C3AC4ULL, 0x344825A9BD0B071FULL, 0x38D368C9B0B75BEFULL, 
            0x3236F0BD3365D211ULL, 0x00CBEBAD1B36F97DULL, 0x5EE0635BF019E69BULL, 0x7D18320AE2A9CAA1ULL, 
            0x19D25110E98EDB64ULL, 0xD53F66BB05106F63ULL, 0xD339622D513D3D2AULL, 0x6EB0C24D6BFC0080ULL, 
            0x03257BA0466BFB9EULL, 0x17DCCAE31A3704C2ULL, 0x172134655F6127C2ULL, 0x3F86FC1E02B2C5E2ULL, 
            0x4ACC65D7A489267FULL, 0x37B7E5F2BF1046B8ULL, 0x58FC49D05972EE83ULL, 0xC6C1E74B4BD339DCULL, 
            0x3543E650E0ECF0E0ULL, 0xC29EABD4C15C8840ULL, 0x1343E9F233DA3C5AULL, 0xAB35CDE9F2187EDFULL, 
            0x8192B66A08CE55C9ULL, 0xADF3D0D5DE37251EULL, 0x6578F8B74FD0A4BBULL, 0x8303591116643F45ULL, 
            0x6C7F8C7AA31B37C0ULL, 0x6A07FF5A2623D88EULL, 0xC0051938383DBCABULL, 0x8C336B24CD735B92ULL
        },
        {
            0x62798A56B72F95D2ULL, 0x21B768047330FBB8ULL, 0x00DB3EC5311EB78EULL, 0x84760975B29F40D9ULL, 
            0xF4C7FA8835585049ULL, 0xA0C1A908B7638045ULL, 0x8806621FAE995D73ULL, 0xD9F27A23B8E508B0ULL, 
            0x5D2E2BDB52A85D0CULL, 0x7D903037F6FA49BEULL, 0x4FA1207E9FDBBFF6ULL, 0x37C31EC872DCE1B2ULL, 
            0x92A09D60991EE211ULL, 0x68CDD6A75C5E6C50ULL, 0xA8E5D9D5153CD652ULL, 0xCE76309B617CDD40ULL, 
            0xD73E6CAFAD29CDEAULL, 0xD19FE95F0CBC8326ULL, 0x45DA616C60D2C397ULL, 0xA31A6B5A96E809D2ULL, 
            0x4D6AE10213FF28B2ULL, 0xA72BEC57975BC53BULL, 0x14E8FE274153C313ULL, 0xE3299A51B5ED68EEULL, 
            0x7FA636BDEDA2D831ULL, 0x5BCD0A26675F62F8ULL, 0xEF09E7F33AF8CDDBULL, 0x658E04EDB571B7C5ULL, 
            0x5266C3CF7062578AULL, 0x2923C827B2CF3496ULL, 0xAE4F73AAF17AFFF6ULL, 0xEB703EE33E5DE449ULL
        },
        {
            0x3904635EA45B179CULL, 0x4C591E67786B5F2EULL, 0xA5FAE6C6F28E1149ULL, 0x56014EDB3A6E3F4FULL, 
            0x9003A6A2140A3C5BULL, 0x91901FFC44D5AC4EULL, 0xA36DE18A2971B2EDULL, 0x0746486441F12243ULL, 
            0x17BB19D0A9218D9FULL, 0xCE77092EEC330CE1ULL, 0x471BCFAB210C60D9ULL, 0x6E5D6669E161B40FULL, 
            0xF587E47FE64D4371ULL, 0x9535076D0E95C1DFULL, 0x5F41481695F1E85FULL, 0x354CF33C17FEA763ULL, 
            0x37E064B43FE63350ULL, 0x9B25C98DC5F888E4ULL, 0xAD5FE2419B497A94ULL, 0x6BE758CD0D6BCCF8ULL, 
            0x81969C8B5EA49F5AULL, 0xB4CC88E364FD6159ULL, 0xDBCC41616C1727E4ULL, 0x85E6C1D107B8C04EULL, 
            0x02A9E6400B2EF23BULL, 0xA8D994C548837559ULL, 0x778A3BE6569F9C40ULL, 0x984D80E5755A62FDULL, 
            0xE7EF382F58F93471ULL, 0x55C4B2D913AEBB07ULL, 0xB793E86C5436A3E1ULL, 0x3FED3ED5B65483D6ULL
        },
        {
            0xCF4A5888A8B0E7F3ULL, 0xA662265447B00959ULL, 0xA2B4F3ED6B546D6EULL, 0x9D7118DE77B6E5A6ULL, 
            0x8A1877BDC04FFA82ULL, 0x654EF67CE1459FFBULL, 0x9C5B08D2DBC6B11DULL, 0x7D763830871A4699ULL, 
            0x4323F88E35CAFC7AULL, 0xC208AF946341C77AULL, 0x5DD2F0AA31D75E77ULL, 0x448DD3F08E6A7AEFULL, 
            0x62E664111C922E7FULL, 0xF18DEDA7FEBF2ED3ULL, 0xDFF7E86ED1A09571ULL, 0x87A69F871FA37384ULL, 
            0x1CD8C9D7138D5440ULL, 0x385198C0B53846C8ULL, 0x7EA6055616AF8636ULL, 0x31DDB6072C05FBB6ULL, 
            0x323A53990B78CB6CULL, 0x381223EB60266380ULL, 0xA778EBBDC5A30411ULL, 0x5B0F41708FBF5D28ULL, 
            0xC0F703DDB4C4AA8BULL, 0x19443BA99A141122ULL, 0x7E21EBB37BFFB9F9ULL, 0x6C108FEBD91A7499ULL, 
            0xC262329C7288F550ULL, 0x6C5AE80B19B94AB2ULL, 0xC9472972F41C7B01ULL, 0x2284E5A963C33689ULL
        },
        {
            0x9B203D1EFFDD136BULL, 0x3E949AA29A7FD959ULL, 0x014D18D1F3B4B959ULL, 0x4BB3286D48FFDBBAULL, 
            0xF4DE4FF575CD0C61ULL, 0x0D94BD23B3EEB4EBULL, 0x3117FF40E47A5CB0ULL, 0x3E2D0B08EE0ABBBAULL, 
            0x65AB40579329F018ULL, 0x261BAF46B36D0194ULL, 0x0E955FDFF96CB6E5ULL, 0xD279F31ED8CA6176ULL, 
            0x368C919C90FE2265ULL, 0x0180D95468E10E98ULL, 0x5D941B52AC48B467ULL, 0x8D6F28A42DFD7565ULL, 
            0xA8ACDC0A2EDCD6AFULL, 0xF58B5F965C3D4873ULL, 0x9C256B0FB657E765ULL, 0x624BA9C7AA7ED886ULL, 
            0x7B13FEAC0A4ABDA0ULL, 0x6C10AF50712056F0ULL, 0x5B82C908A577BB3DULL, 0xA07392CAF173B02CULL, 
            0x8F1ADF8BC1BC21C5ULL, 0x2D70822F0C2051C1ULL, 0x3D241319289A1E82ULL, 0x8716FDB71113CB81ULL, 
            0x4ED9A798D05FEAF9ULL, 0x1C85BED39A3AC9F2ULL, 0x6CEC8D41E9E301F3ULL, 0x915A5CAB581B16CCULL
        }
    },
    {
        {
            0x8FFF4060E71D19DAULL, 0xCEC5172F1945B223ULL, 0x75EB2390FCEC854DULL, 0xFA1F4BE60D11F3B0ULL, 
            0x4276D1C096267660ULL, 0x8AC936CBD813A641ULL, 0xF25862AE2E599917ULL, 0xBD481EF7F069B3EBULL, 
            0xD5BC0E3C22226CF4ULL, 0xD42F017068D44D7CULL, 0x23D92C588495934DULL, 0xF6F5024FFAE3A3E0ULL, 
            0x7419035789AE2A93ULL, 0x38C8E87BEB41B183ULL, 0xF4ABF33708214AB5ULL, 0x368C67126D4E4362ULL, 
            0xE28417E4E7163726ULL, 0x33B1FED779EED8ACULL, 0x97E15651ED60C153ULL, 0xB7207C815CFC49FCULL, 
            0xD636DE3BCDF77667ULL, 0xBDDD037D87F0ACD7ULL, 0xFCDA19CF68B01AC5ULL, 0xC8EA9ECE9C886D09ULL, 
            0xDD453A0FE477F23FULL, 0x9691E2D55A48A497ULL, 0x7F5B3AEF54603F91ULL, 0x5D7CF99145E1EC97ULL, 
            0x7ACD057C3B850880ULL, 0x815DC4D071D0E038ULL, 0x11A23F784400DB08ULL, 0xB7B451E7C0D6847CULL
        },
        {
            0x5E46E4B7A6F11722ULL, 0xFD676DC041491616ULL, 0x9C0FC65CBC4C8CCEULL, 0x2595496AD34B26A2ULL, 
            0x7D5173631A880632ULL, 0x57F826261CDE5969ULL, 0x0E124D618D82AA1CULL, 0x3922042F8479F991ULL, 
            0x4496DB7F823C9DEDULL, 0xFB4F179F6C460D10ULL, 0xB21C7931730FEB27ULL, 0x5327CD358FDA5CAFULL, 
            0xDFDB8C8FD26614EEULL, 0x4C255532DB2B0ABBULL, 0xAE1646907C3C172EULL, 0x1A3ADF51C98C6ED7ULL, 
            0xA05D9B57478017EBULL, 0x73B19EE30E1BD1DAULL, 0x9ED2704E3B161EDAULL, 0xF909C093B254EB8AULL, 
            0xC21FA907445CDE7EULL, 0xADCC599D9B185F12ULL, 0xD687CCC00440CEECULL, 0x138E2B61211F242CULL, 
            0x7416ACC4B6BCDCA9ULL, 0x7CEE06B39D497216ULL, 0x28DDD46427D4FF98ULL, 0x27F597461AD4E088ULL, 
            0x2BD9252213194FD2ULL, 0x947EF193D6449CF2ULL, 0x3D15C70FA78ED7FAULL, 0xEED024FCC38836FDULL
        },
        {
            0x775AF4EE1BB9DCFAULL, 0x800310BEEE4DA674ULL, 0x5E4ACA0804039205ULL, 0x47652FA15F76FC80ULL, 
            0x2544818F58433811ULL, 0x16F6FBE99554B75BULL, 0x7C62FC11F5D0672CULL, 0xBD579150CF612A54ULL, 
            0x221899AEF20A7BB6ULL, 0x1A71C7C1569B3071ULL, 0x78385B5F2DE00F07ULL, 0x4470CBBF1DFD1321ULL, 
            0x91DCEB6F6DB80C5FULL, 0x89244F6C14FA6818ULL, 0x41281FE01BA2B106ULL, 0xDAC7D086C6042C5CULL, 
            0x346705DC24077222ULL, 0x439C01143114760AULL, 0x71FDD666C3A48309ULL, 0x56B79E9509A48E08ULL, 
            0x7549F00C804DB161ULL, 0xED506AFE7B65FF7EULL, 0x345E5E2C57560A35ULL, 0x7629EB264AC12752ULL, 
            0x4DD1A3B6F7511FC9ULL, 0x6D4DEEC8010FB407ULL, 0x627C8232E03B46A2ULL, 0x5B75C299648E2D6FULL, 
            0xDD0D91A38EF539C3ULL, 0x81889F8E63344972ULL, 0x57A61F40958DDD61ULL, 0x4915D4A7D536BF71ULL
        },
        {
            0xF29828F549A79FD5ULL, 0xAB4FF4BCEDCB6D3AULL, 0xEE5957215BA86971ULL, 0x3393426B778A4837ULL, 
            0x51C6DD60C3B44CCAULL, 0xA41B03601602A624ULL, 0xC8DC0FFB8FFE72ECULL, 0x7E0224543409C5EDULL, 
            0xDFF4A2D32E2EABB5ULL, 0xDAF514352415607DULL, 0x37BAE68A33E5983FULL, 0xAEA808249E4D3134ULL, 
            0xA1BC0E5757F8B4C5ULL, 0x407B5822AB455678ULL, 0xF26908177B510F2FULL, 0x5ADED42A3787A8D8ULL, 
            0x12F64170D55C1A45ULL, 0xDC5EFC9ADEACA676ULL, 0xD84EA242841775D5ULL, 0xC38447A027AF948FULL, 
            0x6DA45FD13D9F5289ULL, 0xA35180B649810143ULL, 0x97751C342B4496A1ULL, 0xDEF4633E0D4D3EEBULL, 
            0x4C03C39E498E2166ULL, 0x4676EA134ACE571AULL, 0xD581E96B84592137ULL, 0x733D475064E0B8FCULL, 
            0x7586888C5877A775ULL, 0x136BE86DDC5EAB55ULL, 0x0CFD94EED97EA797ULL, 0x49658EE16D016B37ULL
        },
        {
            0x2B34DB1F816D3FCBULL, 0xE88EEC72BA21EF1BULL, 0x400DDC6A6AE98C5AULL, 0x641925163C102441ULL, 
            0xAB3CD74923888142ULL, 0xD8067FBEE0BB19ADULL, 0x765DEA458C4C95EAULL, 0xF107E8FB39BCF776ULL, 
            0x30AE28635E4E8B39ULL, 0xA75162ACDEEC863FULL, 0x173DAC5422A0AB17ULL, 0xB52F769D70635D4DULL, 
            0xF0B08D06543D214BULL, 0x5944CB9108F7E43BULL, 0xF58AC6A8A4D91665ULL, 0x2F93934A1B7F2569ULL, 
            0xAFC7D2D74E66C6B9ULL, 0xC50A16846D7EC224ULL, 0x27DCB0E4AC1EDD5FULL, 0xE0E3B76ABE0FA3BEULL, 
            0xA88100C14CA701E2ULL, 0xD927805EAC6AA882ULL, 0x5254CAD39A68CC06ULL, 0x5AD522D1ADD0CB8EULL, 
            0xC85078F4EB2BA423ULL, 0xE6BB397DF314A69AULL, 0x1784AEF1793E795BULL, 0xCF46D8E59C3ACD88ULL, 
            0x7B4385579CEE9BF1ULL, 0x328CAD7F98796AF5ULL, 0x82D75A19A85CE077ULL, 0x93A7C5AAFFD63111ULL
        },
        {
            0x75A2AE76A698515FULL, 0xF13F3BA2CB637B66ULL, 0x072C1A956DDE9CF9ULL, 0x519E62C569748F23ULL, 
            0xBE5EAAE67B2B0DB6ULL, 0xFB86207B8D8A2A46ULL, 0x1EDB148F5DE11A06ULL, 0xD8BCE5C702B04766ULL, 
            0x14E26A19A21C6B1CULL, 0x5F4A352B0309D153ULL, 0x007D5C7AA923AE5BULL, 0x3D63BFEC0851B9C2ULL, 
            0x4B9B3CC24BFD7E5AULL, 0x57E093B2C1583333ULL, 0x867F2E623BFA3D52ULL, 0x741596DF6D8E9962ULL, 
            0xAC041FEC9B37E10AULL, 0xE77B458230E6B08DULL, 0xBE5B687E79F8BDCCULL, 0x267A91949FA395D9ULL, 
            0xC31B6082E5F93F85ULL, 0x1E6C1BE1A587D5BAULL, 0xEAD602642B97F903ULL, 0xD60C5A269AE56D80ULL, 
            0x3B3636CF78F10E6EULL, 0x79119CBFEBE57CA5ULL, 0xD14A814648F43C68ULL, 0x8C143BBEAFFBB349ULL, 
            0x3DD787AA523FB6AEULL, 0xB02EA6FA9B7B55FEULL, 0x12E6AB2FE16C034AULL, 0x71023994CFCADC58ULL
        }
    },
    {
        {
            0xF2418C2873A03929ULL, 0x8992E6A3777C0D6BULL, 0x3A9B3F1CA5052B28ULL, 0xB0BB6E6C783E9860ULL, 
            0x2AD775335CF4D230ULL, 0xB3FE5D6CF85CB821ULL, 0x9AB5EF4FF5AB8915ULL, 0xE175A4BCA72EB938ULL, 
            0xEA4B91BB7C2AE2B4ULL, 0x4B18FEBFE07600F0ULL, 0x5FE69ADD3C315E45ULL, 0xA04CA2BAF2B38EF0ULL, 
            0x2CDFA5FC966F3F35ULL, 0xFCE2F1B203FEFB32ULL, 0x4F105ABA0767BEBDULL, 0xF58A29F61C26CF9DULL, 
            0xACCDDE412D71C458ULL, 0x930F7BA8FE6B218BULL, 0x0ED9CEB046C713B3ULL, 0x7216359FD16E9C20ULL, 
            0x5B50F19B5CEBFC0DULL, 0xBD8A0499822ED35AULL, 0x17EFBAFBBEC3847EULL, 0xD4E912F300FE50EFULL, 
            0x4A3F46E2B434A518ULL, 0xAFCE61F68E3D6661ULL, 0x475B6F3C47BEFA50ULL, 0x02CE33DC33262DF1ULL, 
            0x43B78A0854D43C37ULL, 0xD46743B322C313C8ULL, 0x608C5B9A1776067FULL, 0xFF6B6DA198929BBFULL
        },
        {
            0xEEECA205882AABF3ULL, 0x18876BF0E5E550B0ULL, 0x8DA5605575F97CFAULL, 0x363F7F6C10C8D493ULL, 
            0xDF7F7B89D4AA6ED3ULL, 0x7EACCDC4CB3F69E6ULL, 0xBF6304E8CFEBF46AULL, 0xB501FE25308E4AB9ULL, 
            0x127833124F33F2C6ULL, 0x7AE98F0983F27AD9ULL, 0xD48B10BA049F5A2EULL, 0x7AB5BCB69B4BA0D2ULL, 
            0x33D3B15FA76C9DD8ULL, 0xEAA335405C075D16ULL, 0xCFC93FB5BD37F51CULL, 0x9E4814816A961AE7ULL, 
            0x073C2B85C0813490ULL, 0xC5D2A7C3F84007C9ULL, 0xA3024F42B1FE56D8ULL, 0x2EFEB175D4BE6275ULL, 
            0xFE0F1418FE95FC3CULL, 0x3E5B63A29624AFA8ULL, 0xDFD052B949261C0FULL, 0x1D589FAF1B7BC7B3ULL, 
            0x6A729A95AB70DC00ULL, 0x881BB264A052D83FULL, 0x8C90B510CFE286E6ULL, 0x7AF36C1D3AB7907CULL, 
            0x0656D935C36BB304ULL, 0xF47F52CDFA0CC671ULL, 0xED60961CBFBED696ULL, 0xDB04CAEA2D9A5A66ULL
        },
        {
            0xE2F52F6BEF3C8CC9ULL, 0x0CA0033DEEBA87C3ULL, 0xAF6E2FE36800ACF6ULL, 0x73F92FDD441F96D6ULL, 
            0xD36DED8E30F2C608ULL, 0xCFE6C8B8279F7AA5ULL, 0x4B39BABF2305F38DULL, 0x1FBDC9334BF0B0B9ULL, 
            0x1117C6E30F1ADCD8ULL, 0xBBDC31B36B86A044ULL, 0x72DC6B1312398659ULL, 0x9A8911EB5F74B925ULL, 
            0x0CDF2FD2E56D8093ULL, 0x5A162641F12E3C9DULL, 0x80B3A21667901996ULL, 0x6CA0ECC7D1BB3F83ULL, 
            0x021AB290FC57F9E6ULL, 0x1F3D6A3EF32896FFULL, 0x125D62224E9EB07DULL, 0x27111F60500F7D87ULL, 
            0xA72A6FEC8CE986E6ULL, 0x4D021479A602FAE1ULL, 0x3193F3AA79FD380BULL, 0xAD608ED57A6700A3ULL, 
            0x1F670F7CC501F51BULL, 0xDBC32EE736CFB4D8ULL, 0x55DE37C998B84699ULL, 0xF5C3EA5041863A18ULL, 
            0x228D389DF5BF943FULL, 0xF731CB07B4DA9EE8ULL, 0xFE0703A8F4EC283AULL, 0xA04C0B47B64F9135ULL
        },
        {
            0x222620DE1CC4211CULL, 0x34CF0226C1DF276DULL, 0xE707672CADAEC194ULL, 0x1E91A49DA6BAB33CULL, 
            0x292FCB8A610AF336ULL, 0xCF60520F5F72DC40ULL, 0x663727A3CFB3F512ULL, 0x918F55A484542B8BULL, 
            0xD8D3DB2403F4CC84ULL, 0x8625ED54DB2824B6ULL, 0xC91A2DC66BF4EC7AULL, 0xA038CD80EF3C7808ULL, 
            0x3FEC5EFCAF3EBD0BULL, 0x980BE837BF1E10CBULL, 0x390A4F2797E06A5EULL, 0x956225724FD6C933ULL, 
            0xB48C422764165C4DULL, 0x57D3267EF40413BAULL, 0x85DA478AF788ECB4ULL, 0xEEA32F8F68692DB3ULL, 
            0xFF846A7BD1524139ULL, 0xBD0D10A7B0B9C67EULL, 0x44C753E4A0EAED22ULL, 0x687D03A07F9AF7A8ULL, 
            0x19F9AFA8C0189EF0ULL, 0x1AF1B5B8ADE0AB6FULL, 0xFD3CB8816FC66F5BULL, 0xB43320B9A9E84A2EULL, 
            0x7806F4036F9CB2A7ULL, 0x2C7D7ADB036FE1F8ULL, 0xD1DD07538B02C77AULL, 0x3894366E5D9FF9F4ULL
        },
        {
            0xD65EA0BA7AB6C4BCULL, 0x3D974498568B29B4ULL, 0x31DEE337AB6EA4E0ULL, 0xCA52ACF21F14A9A9ULL, 
            0x4F794C8E58289242ULL, 0xED7947E8F53B98C6ULL, 0xF1C9E50F1D2C87A4ULL, 0xB83AE6A378D27AD2ULL, 
            0x4CFE2D871FFAE045ULL, 0x7A9727FB1BB6DD43ULL, 0x0CA80FFE20C55E4AULL, 0xAA8060243C753BAFULL, 
            0x855446264FC31A2BULL, 0xE6545CA2981391E5ULL, 0x8E0AA2F610CB30CFULL, 0xFFB3691EA7A106A3ULL, 
            0xEB536FBC92352497ULL, 0x1D2086724B3C7DCEULL, 0x4151742E22B92C60ULL, 0xF0A503AB4EC8009EULL, 
            0x8ED738967B6C7619ULL, 0x50A8042EEB1AA16EULL, 0xE9D44929FEBDBEDCULL, 0x089B5D9617CA1126ULL, 
            0x001FD18573BF7093ULL, 0x0179AED772D300F2ULL, 0x867DA089B175CC86ULL, 0xD2E5B7BA88348F49ULL, 
            0x561BFF2D9F0192F3ULL, 0x9E9D0F43C25D89D5ULL, 0xEE51F99CF5FDED29ULL, 0x35C57509CD0F58C7ULL
        },
        {
            0xBB5604808537A881ULL, 0x3A50EE3DBD9478B7ULL, 0xC77446D28179890FULL, 0x5AC18C182F39C6C4ULL, 
            0xBD0F35586C760072ULL, 0x1C6CE0E634DDF330ULL, 0x0E9BFD4A8FBA1653ULL, 0x67DD995D5D00D42DULL, 
            0x7895B9989DCF23DEULL, 0x95871A224931F091ULL, 0xCF383F6B01E51566ULL, 0x3F874F078AAF7741ULL, 
            0x2B3316D9D59FF958ULL, 0xAFFA9FD84FDB8EFAULL, 0x9C32BDB7EE22B21FULL, 0xC2D5D3BB22E459DFULL, 
            0xAECF5355D59BE7B0ULL, 0x6EF9843A1CFB2060ULL, 0x99879006B2C01672ULL, 0x988A27ED221217A9ULL, 
            0xC0DABA25095769BEULL, 0x8A8CD478C9F6BDDCULL, 0xFB4F9850A784772BULL, 0xF8A52DB3406FEE41ULL, 
            0x4B7B897869AC8767ULL, 0x431E2067CC6DC892ULL, 0x9B334F9C074DF7E8ULL, 0x17A06BBB423AF5D4ULL, 
            0xA11DF5744B1992BAULL, 0x77BFF95C2C8D523FULL, 0xC29D7283E6D048ABULL, 0x652D69993815C59DULL
        }
    }
};

const TwistDomainConstants TwistExpander_Altair::kPhaseAConstants = {
    0x5249F81F5D66750AULL,
    0x946DB6E86D7468DDULL,
    0xDBDE5736FA9530DBULL,
    0x5249F81F5D66750AULL,
    0x946DB6E86D7468DDULL,
    0xDBDE5736FA9530DBULL,
    0xBF16646C6528EBDEULL,
    0xC982A9D6E018826BULL,
    0xE3,
    0x89,
    0x88,
    0x0B,
    0x48,
    0xFD,
    0x84,
    0x25
};

const TwistDomainSaltSet TwistExpander_Altair::kPhaseBSalts = {
    {
        {
            0xA6BBE00655F088A1ULL, 0xB2DE485A773BE43CULL, 0x34876BDBC99E7191ULL, 0xE741C68287D3B1F3ULL, 
            0x6F73087F07534D96ULL, 0x944DACA8BDAF3BD5ULL, 0x2123FFF13F2A75B2ULL, 0x506BBD0E7BDCE09DULL, 
            0x79B95E186651260DULL, 0xE9E77D2C4BF2BB17ULL, 0x128A0CB0F21DF29AULL, 0x644DA644B906A262ULL, 
            0x07CC5869BD9DDC22ULL, 0x47F4C159C4A8257AULL, 0x9476D1803E5A564EULL, 0x49E2D645E0538F5BULL, 
            0xEE4CD08005BB4196ULL, 0x9204F46D0572D318ULL, 0xADB878E2AB28A9E4ULL, 0x96BC03308AE7AC0DULL, 
            0xF3A147FFFEEFCE9AULL, 0x40EA7A1F08DD9FA5ULL, 0xC070B36CBF09F70CULL, 0x07EDCD3039D54048ULL, 
            0x2017FF2AED0DA4FCULL, 0x5C8C37F8952A35D0ULL, 0xF697ED628B1F793BULL, 0xA4F13F05F35EC21EULL, 
            0x50716448D2C5D5E9ULL, 0x6A2EC6E814A22B63ULL, 0xA0579B8B9EA5C7B3ULL, 0x5605771E386842C7ULL
        },
        {
            0xD48DAF80090D8A31ULL, 0xB6769D467BEC1B24ULL, 0x12D7BB74F6E3662BULL, 0x3259375C2EFB650EULL, 
            0xB14463EB51CEA017ULL, 0x5FF3424B82C810ADULL, 0x79D074F29A77E439ULL, 0xEB318832926D6D13ULL, 
            0xCA23129C32691A61ULL, 0x39852527C997E1A5ULL, 0xC4A7FC5846CD939CULL, 0x7E5630509E2F0536ULL, 
            0x31A23B59C7DFE8FCULL, 0xD879F8631FA5E7F2ULL, 0x71AB5BCE4E5DE0E0ULL, 0xC7F19E03CBBD63A1ULL, 
            0xA93B3D77267F1EC5ULL, 0x120E65A7E9110922ULL, 0xFC5E957347E0AB7FULL, 0xE6801823F398F896ULL, 
            0xE11EF0517666B2EFULL, 0x9DB52A273288A27EULL, 0xEDB1527444CB8209ULL, 0x081D472914AE121DULL, 
            0x275FB1D9493F19E9ULL, 0x118CA0BE9E4ED1EFULL, 0x715C3A2CBCCCC96DULL, 0x0359FF9CD9280EA2ULL, 
            0xBAA0607C2CD25390ULL, 0x2B7D4FB2CC56BC63ULL, 0xCFDB5EC742E4409DULL, 0x8890434A13609237ULL
        },
        {
            0xC1678910A58195F7ULL, 0x028BBC59669DC420ULL, 0xBE02AA2E867FE229ULL, 0x248DF731C57A9D7AULL, 
            0x892477AF4008179EULL, 0xA0280DCC97D14523ULL, 0xA16CE339C9BD70F6ULL, 0x03FF958606CDC697ULL, 
            0x3E6C28562100D50DULL, 0x6337EB8F36A203A6ULL, 0x336E761C805D5068ULL, 0xDC17F5C57871970EULL, 
            0xF2D335FC2854FBBDULL, 0x06619E922538EFD6ULL, 0x8B315ABD5960BFF6ULL, 0xE9BA8A4057BB03FBULL, 
            0x7DBD29AEBFA80756ULL, 0x85C2F6AAA701C3B7ULL, 0x140DD8014B9AFA54ULL, 0x7459722BA44FA0E8ULL, 
            0x9D363D73B824A75DULL, 0x0FE3CA2B9507232BULL, 0x0CB45E1025BB47D4ULL, 0x73C0CC328F917D7DULL, 
            0x6ED27489C99B8CDFULL, 0x21C91022405B03DAULL, 0xC61E43FE7537E5D9ULL, 0x5EA6ADF9A5B1BE13ULL, 
            0x7C576B2AA77A3DF6ULL, 0xBC4A663AAAA3F857ULL, 0xABE9CBB4C77D68F4ULL, 0x3062E281B95FAE15ULL
        },
        {
            0xA74101163DD854B2ULL, 0x2D7C0C387C7447D3ULL, 0xAECFE01593BEBCBAULL, 0xC9B45718D5A0AC6CULL, 
            0x90FD5FB887F0B283ULL, 0xDEF12E9F3040F65AULL, 0xF0F33095F71D5BE2ULL, 0x8D0972AFAB1D6345ULL, 
            0xD66A478502122C69ULL, 0xE2F80EFFEB412D3BULL, 0xB27B2E98F126E027ULL, 0x3C9117249E57E319ULL, 
            0x80A258F32E50EE28ULL, 0x2093AA3A8946DA69ULL, 0x2BDEBDC47BCF9715ULL, 0x29F876C67D9304F9ULL, 
            0x365E893F7A96892CULL, 0x36102AD3D14783A0ULL, 0x6AC638513482BE22ULL, 0xB47C80AEBFF8E2F0ULL, 
            0xDEDED0CC8B552683ULL, 0x5B81F134962329D4ULL, 0x4BDD87E5EF050F4AULL, 0x3227F128941C77C1ULL, 
            0xC6704696D62AA3B6ULL, 0x7542597857742FACULL, 0x603BD0131E61EA91ULL, 0xB35BA7D6ECB1E3AEULL, 
            0x9DE7F2E481841EE7ULL, 0x1B10C68A716F78F1ULL, 0xDB7006C9012E2B6EULL, 0xBA9B97D85E8A29B9ULL
        },
        {
            0x5611581526C10F02ULL, 0xE527F8762E0B24F0ULL, 0x36966DD5EC3EB066ULL, 0xBEF705F4B1F88C08ULL, 
            0xB87870C8D3DFD85EULL, 0xAB0742B5AB2C90D0ULL, 0x633E7AA5B600F801ULL, 0xB4E9032D8201F6C2ULL, 
            0x8554FB3661428E35ULL, 0xF22AE434AAE40F26ULL, 0x8C5C998B9DDC380BULL, 0x9F642E6EAE3D393DULL, 
            0x1106C27C028B32EFULL, 0xD607DAD6A0DB0616ULL, 0xCE1260A1251FF4E5ULL, 0x787737CA4AD14B3DULL, 
            0x2C1AD746D12688C3ULL, 0x9ECD322035540EE1ULL, 0x407D19A4EEAEE78FULL, 0x4B3355D17D89634AULL, 
            0xC06F2990538F39C0ULL, 0xBDDA194A7C4030EAULL, 0x60A0A8B81E3F0D71ULL, 0xC2FBCD5E5B2CE367ULL, 
            0xCF53193088C76664ULL, 0x581F67A059E3CDECULL, 0xFDBAB67DD0C26D9EULL, 0x7E06D56872C0E9D7ULL, 
            0xBBCEFC6C6852BC70ULL, 0x0126691722020F67ULL, 0xDC2F4B9A57F19CDEULL, 0x5D0F1D1CFC5B2969ULL
        },
        {
            0x3589AC247DF2C3DBULL, 0x27F122031815A733ULL, 0x9A4F082D662497D4ULL, 0x5AB91B89EA6BC678ULL, 
            0xFCE8F7EE12EE580EULL, 0x27ACE35DBC1A44B1ULL, 0xA77240B4AA047E3DULL, 0x24CDEC8CAC99897CULL, 
            0x6176930E31BCB012ULL, 0xCE9626EA18FF4281ULL, 0xDBD8A7AA013BA4F2ULL, 0x82FF3C11F3102654ULL, 
            0x3600FB41A88DD22BULL, 0x6031DBC51E839E04ULL, 0xB9F27E528DE611BCULL, 0x0CC455180465EBECULL, 
            0xD4F3AA4AB296A6F2ULL, 0xAD4B17807717B95AULL, 0x2145E1E86C8903B2ULL, 0xA915904262CB1642ULL, 
            0xE1F49942FFB64837ULL, 0xAA7F437A12E4247EULL, 0x1FF6BF08652AA61CULL, 0x67FB86DEB2019C79ULL, 
            0xF36ED4E81E73A507ULL, 0x18D44070E01F34B0ULL, 0x8D986E0E085E3735ULL, 0xF90B31A215573AEDULL, 
            0x7ED8F679EE036D27ULL, 0x2F9C831970F87B87ULL, 0x9D49A4FA193ED0A8ULL, 0x630962A31B0E9355ULL
        }
    },
    {
        {
            0xBEF36014E137DD2EULL, 0x1CCCC321B9767FEEULL, 0xB957763F44AAB80BULL, 0xCC1278B27AD12D28ULL, 
            0xA6191D238971CB50ULL, 0xDCFAE5613636BFC1ULL, 0x18C155B4BD379CB7ULL, 0x118D1E4032AB5CA9ULL, 
            0x70A8BC663C7F413DULL, 0x2C710ACFCCE0C2EBULL, 0x5CB8DB89710D05FDULL, 0xC2B191A63F15E476ULL, 
            0xC8D1DBBDA3E52A3BULL, 0x6DC49ADA08B595D6ULL, 0x37BF188A97261840ULL, 0x3EFC14E9AC208CE9ULL, 
            0xEB7B1B51DAAA9A91ULL, 0x8AF079155A7B83E0ULL, 0x722FE317FAEA4847ULL, 0x230A1661E3EE904DULL, 
            0x5D970A606C9C8526ULL, 0xB969D3C74629D685ULL, 0xC461A8A1B1A18B2EULL, 0x1C35DEEE12CC7948ULL, 
            0xB0BDD549ED8808D5ULL, 0x41F29E6895077AEEULL, 0xAD9DB7ED3B12C990ULL, 0x7EE7E0EF86A7721EULL, 
            0x74B41A87BBA133CDULL, 0x77012CDEFB0197FDULL, 0x76E8087AD00BB5BCULL, 0xB9A37AFC0E580D0AULL
        },
        {
            0x005CEDDBC26BC0B6ULL, 0x817C89FBF0A2E5C4ULL, 0xFC1B9AB685A452F7ULL, 0xB9BEF2E4C26ABC1AULL, 
            0xC443D888920A447CULL, 0x2ECDACB909599ED9ULL, 0x6B0B56712E759E71ULL, 0x23004CACD479CF77ULL, 
            0x931308E83A3C2120ULL, 0x0BFB31760489108BULL, 0xB1F228F5385B934AULL, 0xA979097B2F4D2C70ULL, 
            0xA9A1B2016775B49EULL, 0x044207120D488EB9ULL, 0xED69B690AADB63F8ULL, 0x8E4349E909FB5E2EULL, 
            0x1CAD1774B88838DAULL, 0x79ADC6995655B707ULL, 0x679CEC9CE18CD45CULL, 0x1B456A10865B35D7ULL, 
            0x713795E0201186D1ULL, 0xCDE51BC1419E8B39ULL, 0x0348E2C05E990A25ULL, 0xAD2BE08A61A8AE54ULL, 
            0x84693021F0642C99ULL, 0xE6FDA8A8061D7070ULL, 0xE01A10BA9566F84FULL, 0x8746BF3E40DF3786ULL, 
            0xE7406B1D6E889C82ULL, 0x1CE3CF4FF8E3603AULL, 0x1F875CACB8F447A8ULL, 0xC5F32CF5AA6160FDULL
        },
        {
            0x43E54CCF090D52E6ULL, 0xA50D3CCC66E4874BULL, 0x5EDD5C0F3B711D0EULL, 0x51F76CA010FFEDA0ULL, 
            0x56E95A6693524200ULL, 0xE793CA1E8F29375DULL, 0x0576581FAFD880D3ULL, 0x4AF9EDABEE6B6FE3ULL, 
            0xCB4A31DFDE192379ULL, 0xEA24D3FBFE3083A9ULL, 0x69C9EA5C3DCDCF86ULL, 0x14F83C82F470BF42ULL, 
            0xE53C07A4C0A52C65ULL, 0x73FB173DC58538ECULL, 0x8E085F708C40DE48ULL, 0x70EB4961783D79DBULL, 
            0x11D112805248AD59ULL, 0xC80AC58D6DF82231ULL, 0xB0A6118364890EE2ULL, 0x47250975F5939FA5ULL, 
            0xCC1B6D02FF73886CULL, 0x7808241DE08EC393ULL, 0xEC3ED59F95CA503AULL, 0x61746A26A305B262ULL, 
            0x0BA89BA5D13F4B25ULL, 0xC6A2AAD12F7EA922ULL, 0xBF941E5029932865ULL, 0x1EFC0F91317FB208ULL, 
            0xC48E92C896EFD330ULL, 0x9530FEAFA0FD7702ULL, 0xFA8EEBCF7C8F0415ULL, 0x66F2D621E81817B3ULL
        },
        {
            0xEEACB1B7F66B660BULL, 0x7E78AF49FEB7DBB5ULL, 0xA1A724AB70C78FC3ULL, 0x827B389A5BB31285ULL, 
            0xA74861C511FD4097ULL, 0xCF927ADECCA885A7ULL, 0x7E3FFF7F37F8E906ULL, 0xE47D2D4A648C0559ULL, 
            0xF8D8A88A8C1530BCULL, 0x04C8293C235D81D9ULL, 0x13E7713C73C9F8EDULL, 0xA807157840C58FCAULL, 
            0x872133D85624F4E6ULL, 0x72F902AE110055C5ULL, 0x3EB11C6ED1A31C37ULL, 0x8C22F1E0F456EA36ULL, 
            0x2726C881ABC5A8AAULL, 0x18F658C729A4DD11ULL, 0x9812EACBEFAFD1FFULL, 0xEB79E51B7C40189FULL, 
            0x8AF987F9126517B4ULL, 0xDAA7F0CB4DDF7C03ULL, 0xB5608F527EC7D4B1ULL, 0x219A6CFC91306390ULL, 
            0x33452D5C066DEB74ULL, 0xF73FAC1496A3D4CAULL, 0xD2324A4A50B3FAD9ULL, 0x66FCF7E2D8B795ABULL, 
            0x932402C3E2F261C6ULL, 0xD00A3DFBF520FF54ULL, 0x484A2F323AAA4D19ULL, 0xFE72D013B1EF8A69ULL
        },
        {
            0x2DD6199C94A04E62ULL, 0x69DF12DBD62A833AULL, 0x038782563BA7CA3FULL, 0xAA2F6ECCBB94F55CULL, 
            0x5C4374EF26625094ULL, 0x8CE497EC31C6CE5FULL, 0xE0B2D81A51ED9FF0ULL, 0x7F7C9A0FA7B2B883ULL, 
            0x740A67B531D2E45AULL, 0x7D47792D348455E9ULL, 0xE42056A39609C22FULL, 0x8D07C1C1B140285BULL, 
            0x14C6B6546FC5D476ULL, 0xA86E5AA57FB7236BULL, 0xD9539A4995B96343ULL, 0x3A87DC958D2A8C44ULL, 
            0x088427FC42CEBE4BULL, 0xA81773B3BE6CDC75ULL, 0x37FD89864C3F4758ULL, 0x01EB479F6863ECD7ULL, 
            0x04429C9017773632ULL, 0x80E405A4B86AF780ULL, 0x0C944A49C8DA61A7ULL, 0x0B789BF6509AAD97ULL, 
            0x7FE4292A4A77CB98ULL, 0x627993314AD760B4ULL, 0x709BE5E184F3A35AULL, 0x0F2CA9C9FA7E1A12ULL, 
            0xCF7EBCB3E7615AD9ULL, 0x3C521C0D74F710A8ULL, 0x7C09243FFAA965EEULL, 0xC819AC9232E13E76ULL
        },
        {
            0xC33EE7E6315D451FULL, 0xDE4A48D889B03D8FULL, 0x0D62750A11AF2F6DULL, 0x24AD394296BBFF87ULL, 
            0xE537FE2D88F72000ULL, 0xE65B993A62BB7FFEULL, 0xF9CC98FE359E3AEAULL, 0xA6ED3B639EEF5B73ULL, 
            0xAB4BE14CD2995E29ULL, 0x667FE0106A2E2ECCULL, 0xF90DC6D62F48D459ULL, 0xE1389E3DA051D6AAULL, 
            0xFE74957146CAE648ULL, 0x308A91F1E8937D2DULL, 0xAF678FC8E5D24FC3ULL, 0x2134551783CB3695ULL, 
            0xEA238747E75CF41CULL, 0xD3E52593296A2FD6ULL, 0xED3DE98EFAB9837EULL, 0x3358B77F6A010F58ULL, 
            0x15028353C5DAFE31ULL, 0xB8EF8045C4352D6AULL, 0x9696197A8EDC346AULL, 0x1AB8C29B263E98FAULL, 
            0xE79F755B61CB52BEULL, 0x1CCCF39FD0B1EE1FULL, 0x61F30F066937272BULL, 0xDA1C2B9BAD5E8D0CULL, 
            0x0728D650EF8DCFBEULL, 0x3DA9C6972B04BA53ULL, 0x0BF5743718D8DC28ULL, 0x6A27701398DD223EULL
        }
    },
    {
        {
            0x7E496F60F3931EA4ULL, 0xFF8CED01984C37E5ULL, 0xBE4B92263B352068ULL, 0x3A9EBB6761ADCEA6ULL, 
            0x18F6441A7520D976ULL, 0xE7E77B0F4EEDA0AEULL, 0xFC8C8DFEF28EDBF8ULL, 0xA0C98D18C20BA9C5ULL, 
            0x53F867DA5210A129ULL, 0xB09521D56B3E2177ULL, 0xC7B9EE96D02465CAULL, 0x2F11C98150605DD9ULL, 
            0x7F81B24F4AC6F5BDULL, 0xDDDBB1C6DB8EB501ULL, 0x511AA9FCD621D0AEULL, 0x890BED021B65FC92ULL, 
            0x52957641AC9BA31BULL, 0x02A2DB19198AA8C5ULL, 0x18A8337DA338D117ULL, 0x717EC4781042868FULL, 
            0x3E665434822F582AULL, 0xF90D445B769C2334ULL, 0x5BD02E0B6267378AULL, 0x14A607FF7800519CULL, 
            0x66E14B444385AE1CULL, 0x72F4493D2C928860ULL, 0x8F72C77EDA72B89DULL, 0x214C59B568F00EFDULL, 
            0x983B2A580A1A6D3CULL, 0x78ED0B5926799279ULL, 0x1F90100ACD5133E1ULL, 0xDEB5FF3952D66E85ULL
        },
        {
            0xFEBAA7B49736C79BULL, 0xC9238615F5526EBFULL, 0x21C5F49166C9FDEFULL, 0xC5836B34986ADFA6ULL, 
            0xBFEC6EEE2CA04C46ULL, 0xAB4ACACC22DB3AD7ULL, 0x2E40E01B36DA5421ULL, 0xBD0735276D9F9153ULL, 
            0x6F654D998E8629A0ULL, 0xF4AC5E0BE2251AA0ULL, 0xB6B170B0A9B46F29ULL, 0xB33867761C0BD5E9ULL, 
            0x6E4CE5A0B455CFEBULL, 0x2D58C1D75EBE908CULL, 0x5B811877BEECD0FFULL, 0xFAFC1520E0F6FD9EULL, 
            0x0AF8B38A4C45544AULL, 0x7B45D4DB6F0307D6ULL, 0x7D1D9B5DC645136BULL, 0xB0E16ED1FC70555AULL, 
            0xCB901FF67AEDFECDULL, 0x0DE32A058DA8A2A4ULL, 0xD452163CE6EE0906ULL, 0xBE70193BD078BA18ULL, 
            0x4A2AE1AA3E90F95FULL, 0x1FC9A21ED324BB6BULL, 0xB14299A02CDA71DBULL, 0x2C4CC694A550B5A9ULL, 
            0xB253D33217966A8FULL, 0xA0FCE38870A92D54ULL, 0x1A60A85135E8D416ULL, 0x86844B40D6A9C20EULL
        },
        {
            0xF5B715FDEA979DEEULL, 0x7C7395F8E3915CD6ULL, 0x17F1C347D0472EFBULL, 0xF4D013CEEF829533ULL, 
            0x7C00E40A5EE8C98DULL, 0xE26142D5B46B988EULL, 0x8C9FB7FFE6DF5478ULL, 0x86A225699A4C0F6BULL, 
            0x4E2376F7F65EDA15ULL, 0x07658B84D80CCCCCULL, 0x19F7A23555F28D9EULL, 0x99F76E0EDD676A9FULL, 
            0x29FC905B66A251C9ULL, 0xD5954CEB8AD5786AULL, 0xDDD060086CFAF1DFULL, 0x5FC388611F035BA9ULL, 
            0x57B4CD03FF419945ULL, 0x724E290A686A70C4ULL, 0x752D91E8A3766D48ULL, 0x329E04AF916B601BULL, 
            0x45EE63811EFD0D3DULL, 0x444A890A7CF71D24ULL, 0x041D969637F14C12ULL, 0xE4C71E2CA1AFD1BCULL, 
            0xF10157A39DD66B5CULL, 0x4521BABD9AC54D50ULL, 0x7842E147E1892E97ULL, 0x91F283C4213FD9D2ULL, 
            0x2B86A901AFFFB2F5ULL, 0x82C3F4E556FAD61AULL, 0xB7DFE4497E55BAE1ULL, 0x4320741020763ED5ULL
        },
        {
            0xBE8007FB21E0C7A8ULL, 0xDEB6D74FBC4DCE8CULL, 0x21FF4253426553C8ULL, 0x49F63233BF9DB420ULL, 
            0x1A34C8A5862F99D2ULL, 0x1995DB2384D23CE7ULL, 0x4CA28C827A7DFE21ULL, 0x17759A7AAB65D545ULL, 
            0x2C117BB68B0B3BB7ULL, 0x63511537F92D2D6DULL, 0xF1F3063173A38F36ULL, 0xF0D38B0BB7F903A0ULL, 
            0x0E0D6E7C98DCDE1BULL, 0xCD98EDC508634541ULL, 0xBD56F20863FF1466ULL, 0xBD425B09B87F1414ULL, 
            0xBA80BDE63C0AE9BAULL, 0x08F0F510D0573E7CULL, 0xE43281014DCE74D7ULL, 0xF6C3A16B4C46D2C0ULL, 
            0x67E5C9BD99003221ULL, 0x7F075AFCCE0EAAE1ULL, 0xB9533AB494D66E9AULL, 0x00CE09483F8DD027ULL, 
            0xAA309CAD68A2A30DULL, 0xD19028F944FBF8F5ULL, 0x909CB19A1A53A405ULL, 0x0F9711724D55DF17ULL, 
            0xE3306CC29E908ABEULL, 0x1DFBE9D33D11AB18ULL, 0x597D3C1AC9593453ULL, 0x2C951F826C0CF210ULL
        },
        {
            0x77A328E8A3E595F2ULL, 0x84395581EDE9EDFFULL, 0x9DAE6A73DAE6E11CULL, 0xA1E41E474E7F4C2DULL, 
            0x7D1D3E585C2DAC52ULL, 0x09DF927A143DD3DDULL, 0xF4C7A33AFD6486A7ULL, 0x89FC41AE16B0D78FULL, 
            0xDC29D045322E49A6ULL, 0x3C724C59874BD0BEULL, 0xB8B2FFE465223099ULL, 0xA83BE3C42FCE9E2BULL, 
            0x4FC23FA3028DD42CULL, 0x9C7D8C65B0CD49BAULL, 0xD12F5A918FE40A19ULL, 0xA438651B8D24A6FDULL, 
            0x48BD7C0F92190955ULL, 0x3CB3B8FE055F3F2EULL, 0x6F01DD471E59D44DULL, 0xDA67324A2EBCBFDBULL, 
            0xD74207547F89B486ULL, 0x9BFC0188A0ACB3B0ULL, 0x8A0063783A28989FULL, 0x6163E1498DD74CDEULL, 
            0x93F2C9C93572CAAFULL, 0xD49DDCA3417CF56CULL, 0x5DFF03195A7FA73CULL, 0x89995CC7A6066F5DULL, 
            0x806BE5B13C7D461CULL, 0x7BB34BE0AF7B3C1DULL, 0xB29B6A910980F6CFULL, 0x05773DF55C2B2380ULL
        },
        {
            0x90AC12F568BDBFD5ULL, 0x187A87949EF90671ULL, 0x8932DD9C91BE3F45ULL, 0x8263466397D44D09ULL, 
            0xD47DEF06017EE568ULL, 0xC44A01BBDEC7024CULL, 0x20042E2A3514ACD4ULL, 0x2245548CFF60EB50ULL, 
            0xF406138868A51C3AULL, 0x542118BFE6D0BDCEULL, 0x544AE310B3EF96F8ULL, 0x694249E74A9EB066ULL, 
            0x98B4250073EC324CULL, 0x9576F74D2064F8DAULL, 0xB7A398D4984133A7ULL, 0x8848285FA01A2E0EULL, 
            0x28D9594EF021F941ULL, 0xEAEE8A0D21C3DE3FULL, 0xC194044063B6BDA1ULL, 0x0D3CC4031C3931E1ULL, 
            0x5CAB1F21C647678CULL, 0x4BFD088CBC97F43CULL, 0xD61FDFE3B7EF39EDULL, 0x35231D99E5B622E0ULL, 
            0x1E9672C77AA95A86ULL, 0xE6F5535DCC7144ECULL, 0x0BC56020E243F4EBULL, 0x24B94120C041B8C1ULL, 
            0x06B32826364C27CEULL, 0x2C50E8C92CDD92E1ULL, 0x905F135016D6EDE7ULL, 0x94F62D220FA6D22DULL
        }
    }
};

const TwistDomainConstants TwistExpander_Altair::kPhaseBConstants = {
    0xE4B7006457CEB0A0ULL,
    0xF83938E12072858CULL,
    0xA7F02BDAC7DACA17ULL,
    0xE4B7006457CEB0A0ULL,
    0xF83938E12072858CULL,
    0xA7F02BDAC7DACA17ULL,
    0xCCB5381F0FD58421ULL,
    0xE58F49DD7D18D90CULL,
    0x0D,
    0x84,
    0x24,
    0xBB,
    0x8C,
    0x65,
    0x6B,
    0x4F
};

const TwistDomainSaltSet TwistExpander_Altair::kPhaseCSalts = {
    {
        {
            0xDCD66155FDD8120BULL, 0x1F81618760B48F7DULL, 0x7FA8A8AFCEF63B2CULL, 0xF5FB33D0F96207D1ULL, 
            0x172635ACE5DF7FE3ULL, 0x940F0F4B6B9EB2FCULL, 0xAB1FB3676F4F209BULL, 0x973BE9F893047ED2ULL, 
            0x7FBEAB599D418BAEULL, 0xF69E073846119457ULL, 0x5C05C3FEEFFB349AULL, 0x856EFD4A52C20F51ULL, 
            0x2FC300BE0678363BULL, 0xE5037F7C8DA97B15ULL, 0x9955EC812532F522ULL, 0x703AF701966231DFULL, 
            0x3FF80E59BC2114F4ULL, 0xCED2AB45DF602B8EULL, 0xF92BFC6101DF3E71ULL, 0x21E629AF01041BF1ULL, 
            0xEABD372BAB0BE85DULL, 0x5708DB46507F1277ULL, 0xE0E91E3960FB1074ULL, 0x2B672015AEEF8FB7ULL, 
            0x6B0A52253F5007FAULL, 0xA133E7E11C999EB9ULL, 0x5AE94FEF72737C8DULL, 0x6EEB9A2B1C2B35AAULL, 
            0xDDC4AEB6CA8E1190ULL, 0xEAC4540ECA9AEC93ULL, 0x25C63A5236CF240EULL, 0x1C34C3E94F8A0BB3ULL
        },
        {
            0xA7CBBD77AD3FF15AULL, 0x6A560D8644450FCAULL, 0x9B5CFE95F80F2114ULL, 0xB617265E0A4A5498ULL, 
            0xEEA61A4E21142C5EULL, 0x377FDDAE91D658BAULL, 0x1FDD6BEBA7CCA052ULL, 0x6110CE2DBA90F3A0ULL, 
            0xAAEAD677B4BD3D73ULL, 0xE726365077F9D146ULL, 0x175D55D8AC345D0DULL, 0x3AB36043C202126BULL, 
            0x8A37E94D49736845ULL, 0x7F6235CEF2062262ULL, 0xED3A4E61EB36AE75ULL, 0x86CBE1E9D6CA224CULL, 
            0x47C153CF1FC062D2ULL, 0x601EFDDD04C8F275ULL, 0x21C3E2E3F7619018ULL, 0x62F55549CD4F595DULL, 
            0xB8C2B3D6D00A92CCULL, 0xE1204F609B301D9CULL, 0x9B87AC975F07619DULL, 0x2F1569B67EF0D68CULL, 
            0x98D1583BD95207D8ULL, 0x02CC9182134CFAFFULL, 0xF0FF596A77683650ULL, 0x4C52F0C97859B7C5ULL, 
            0x0E4EB8E9814B5821ULL, 0x475E44E2C7D3A2F9ULL, 0x3A08F53CA367AF75ULL, 0x09EE4B5EB96583E6ULL
        },
        {
            0x520FD9CB2E771A87ULL, 0xED0D63D09FFF99B0ULL, 0xDAE670732C477B56ULL, 0x852EDE6D7FC4DBD4ULL, 
            0x6E444E3163296FC2ULL, 0xE9FC3CBF758766CDULL, 0x002BD145F0840431ULL, 0x3E92146F8E4C8344ULL, 
            0x04046A6FFE6A8799ULL, 0x71122BD9023C716BULL, 0x345A174F9249FF39ULL, 0x9821CE94F2877203ULL, 
            0xB36E8560A9AA520EULL, 0x72382EE9C3B12BC6ULL, 0xF7A754E874AB0726ULL, 0xD59B4136E00CDA43ULL, 
            0x252B299D744F9640ULL, 0x24DC9071A13C9AB0ULL, 0x8DDEBD49EFE93BE6ULL, 0xE00526C9EED1E007ULL, 
            0xFAF68EA7B2AAB53DULL, 0xF89461532BCC5390ULL, 0x91B1C5A3E3ADE296ULL, 0x251016769EA4CE6FULL, 
            0x1DAE60C3064BE3A2ULL, 0xD9D67F3BCED0842CULL, 0xD9C2D0CCDB77BA05ULL, 0x35D15C7AD46BA2E0ULL, 
            0x922AAAD0498A5FF1ULL, 0x9C6CA4B9B018F8DCULL, 0x042EE59E8EEBE84CULL, 0x7D0E335696C9AE57ULL
        },
        {
            0x4415825F86A4ED23ULL, 0xED6B7872905299BEULL, 0x8045AA1589A93B1AULL, 0x727885CDA425D3C1ULL, 
            0x7FCF4B5F84B93AC3ULL, 0xCE93B8C8A686A8B3ULL, 0x992D22FCBD38E589ULL, 0xB7E8DFAD6C5DBF94ULL, 
            0x55DB68CDEDD16E79ULL, 0x926B083C76A19A5AULL, 0x728B8D08907B93B0ULL, 0xD2178BD877379B3EULL, 
            0xFA059E795B57F5BAULL, 0x58D4702502722A23ULL, 0x8857DFB863636846ULL, 0xF6B29A33831031CDULL, 
            0x40FBB77BD81B2989ULL, 0x062CD36B0DDB8141ULL, 0x7FB06B2B0B634EB1ULL, 0xC7DA6E533AABF674ULL, 
            0x7DB92C181676BD0AULL, 0xC4806999084CB38BULL, 0xA0B39716AD554BF9ULL, 0x3BFD797F47C1B6E3ULL, 
            0x5E4AB8328667BA88ULL, 0x812E900F6A5187D8ULL, 0xC2D91D1A112A6847ULL, 0xE11059320BB4FDB8ULL, 
            0x4C38B3BFE22EB8C4ULL, 0xB0A497AB6EB92EC9ULL, 0x9F3B43A4A6EA0C88ULL, 0x4E1DCAA370E71913ULL
        },
        {
            0x3FD388CA9E0587B5ULL, 0x7AB797BE2467AC9BULL, 0x0F0ABB13A4DEAAD8ULL, 0x31348F8752D46E87ULL, 
            0xE553C1A07B156320ULL, 0x9912AEE08BB60A1DULL, 0x534ED8676069603AULL, 0x3DF05E59D16DC09EULL, 
            0x294F5062B4B90E17ULL, 0x4F18CEC57D797D00ULL, 0x67EB425705FB2586ULL, 0xFD56CD5F78621642ULL, 
            0x5171AE0CF0CB7B02ULL, 0x9985E772E1FB88C8ULL, 0x66EA7D2E897B6B7EULL, 0xB2A797A92DC187F5ULL, 
            0xBC081E826FDC9F30ULL, 0xF1A6F03A7AD76E12ULL, 0x34C797B12919C341ULL, 0x3E1F050AA5E8A0D3ULL, 
            0x61A196CCE69AFA81ULL, 0xAB5B06027611B9F7ULL, 0x9A8BE8AA3E31CA0FULL, 0x7D9F2047D6F4BAABULL, 
            0xC7F2D2A44E8A2405ULL, 0xFA67FE223921650EULL, 0x288B34BDC0CB40A2ULL, 0x4F17C1C90008B9E4ULL, 
            0x99A8E8F0E3E32CD6ULL, 0xE474F407201F95FCULL, 0xB7B3C1698D894308ULL, 0xAE8D6293D6C90365ULL
        },
        {
            0x1A4DDA5661A80529ULL, 0xFC09308824803CF7ULL, 0x41485A4AB2FDCFC5ULL, 0x66E1BB3C474D484CULL, 
            0x4203AA092C4CBD9FULL, 0x85D67CA45CA0B510ULL, 0xB775933AC2AF2623ULL, 0xBCE3CD8C12BAE418ULL, 
            0x5BA418C6105909DAULL, 0x4B4AAE9FF588B3F0ULL, 0xDB610A14DEFA4A81ULL, 0xE8F0892164F6A934ULL, 
            0xA11B9BD1117DACCCULL, 0x991B87E586737BDFULL, 0x82B53FDDB6F398F0ULL, 0x97133C1519269B3FULL, 
            0xE89B47529B4575B0ULL, 0xE75ACB9D96251C04ULL, 0xAA733F9F70A507FCULL, 0x5C023DC18AF7E78DULL, 
            0x47A3A1556AE1B7EBULL, 0xA6EA8B9A4FED2FC2ULL, 0x62DCE3C65801819FULL, 0x867B40766CD509FEULL, 
            0x6F6C6F08DAEF7060ULL, 0x0DFED73B3B55AB19ULL, 0x12FCD855ADFD2144ULL, 0x0F84ABC338090353ULL, 
            0x54AC4AC170365059ULL, 0xC38FF2C3D002AA48ULL, 0x886C51D6A7709F0EULL, 0x69436A32FA4FA5DFULL
        }
    },
    {
        {
            0x90725B1EBE63FD31ULL, 0x2CF19CD9F5DC35BAULL, 0x13B205394578D829ULL, 0x3628638FED230A99ULL, 
            0x2D69E5C9E835C6D1ULL, 0x433EB5FC2D7586ADULL, 0x9F4FD7FEC6FE4DF7ULL, 0xE70BB91E9A8CDC12ULL, 
            0x71403F2C508065C9ULL, 0x20C14107A94DC57CULL, 0x4CA1A31766284D4DULL, 0x001B40587411756FULL, 
            0x935A81B04EDD1AC4ULL, 0x8EBD6CA386B287DCULL, 0x3EBDC9A7401E8BC0ULL, 0x09368DF4B5EB327AULL, 
            0x44A93DD688480A09ULL, 0x3A2CE82B0B676695ULL, 0x67CC7F1A6D82829CULL, 0x035FA1D620E3DD74ULL, 
            0xCE0D25BA3D60C045ULL, 0x59C71D75F3D29316ULL, 0x684BA565E02BE57BULL, 0x2A21A16B9FE05B9BULL, 
            0xE1185AE63138091EULL, 0x55EB405A29F78287ULL, 0xACD14E896AC3F592ULL, 0x3D49C66FC9135F16ULL, 
            0xE2958A2AC0BB8A88ULL, 0x644A7786B68AA627ULL, 0x708E51DE1AFFE9FCULL, 0xF690B2AC7AB55D8AULL
        },
        {
            0x1D8C9AD740F59E1DULL, 0x6564AE906B28C9D7ULL, 0x52EB76775895AA65ULL, 0x0E93AEB872B984C2ULL, 
            0xE4449D3AA293A890ULL, 0xD71FEEEFBAD42CD5ULL, 0xDD1991FADDCF20B8ULL, 0x4F1887AF556EA17EULL, 
            0xD9F9CC176D5C726CULL, 0xA471AB950F50D055ULL, 0x188C60E292161B48ULL, 0xBD5AFA26F8FDDE8DULL, 
            0x178EA7ADD58FD995ULL, 0x635F9C4707CE204BULL, 0x22A989CC494C647DULL, 0xB4A9A63B8455659CULL, 
            0xAE66EDCE11697594ULL, 0x7CF1507071F8B66BULL, 0x610FAF3ED529AEECULL, 0x4F37B6498B5F545BULL, 
            0x5F94D2B0319BAE2BULL, 0x3614A9D6D9D7EA07ULL, 0x4EABCA69B86F9FFAULL, 0x8EB24AF4E9B7B25CULL, 
            0x3231B8139F6CFBD7ULL, 0x0FF2C826024BB8A0ULL, 0xC766CA8F60AF6FDFULL, 0xC032B0BB0416174BULL, 
            0x64DD548C1595F0CDULL, 0xD2E868A3575F19DAULL, 0xEA015424393118CEULL, 0x8F2D23E4257C2937ULL
        },
        {
            0x767274AC1B3A9651ULL, 0x1061715B6AADF8A8ULL, 0xB4B6418424DF1EA7ULL, 0x4AC4604915482104ULL, 
            0x2BBD63C1164FE63CULL, 0xE243EA3D019679B6ULL, 0xB105BB7315146232ULL, 0xAD383E62AE6EDB8FULL, 
            0x0A250FA30B2E9861ULL, 0xC9FF57DB979C38DAULL, 0xCFDDA0541E36C8F9ULL, 0x9B10E38862942935ULL, 
            0x9D00A3A7ACF6006BULL, 0x116685B3E8D26AB4ULL, 0x73420B82D9E3A389ULL, 0x87493FAEAD7A55E0ULL, 
            0xEF060860E29C7EACULL, 0x4E7E93023D677D3FULL, 0x86D1254757CF1061ULL, 0x70BE1C77E3C929D3ULL, 
            0x6F102903634E54B8ULL, 0xCD1E38C1147E1EBCULL, 0x69A92A7123D88286ULL, 0x43D694ACD6B54B38ULL, 
            0x7F6FFD18CCE40112ULL, 0x9E0FCD420C2D63A9ULL, 0xF8BBCDEA9AD62C68ULL, 0x79783C7BAC19F139ULL, 
            0xAF54EFD22DBA975EULL, 0x09C821424C1BF817ULL, 0xB7966761FC69DBBAULL, 0xA36DFA5468469C17ULL
        },
        {
            0x6C8BD48ACF4D124CULL, 0x74DD1A1DA3B4B119ULL, 0x6DD553D85CBAA2EDULL, 0x3307FC5AE1C8E221ULL, 
            0xB862ED5E001D4CE0ULL, 0x8FE91DDC4D4A9A8BULL, 0x22C1490A07CA6A57ULL, 0x068A67288543034AULL, 
            0x10627C5A40EC25D0ULL, 0xF35C55B20931E17AULL, 0x3EA23B0B788D4AC9ULL, 0xADB66E9E7FBA9F03ULL, 
            0x02EE4E3A6754BEE9ULL, 0x4609E38A4CEA9139ULL, 0x702CC6EF8040B878ULL, 0x05D112B3F9AB58D0ULL, 
            0x61CE8273363C6EC9ULL, 0xD16288370FC50438ULL, 0x97B5F33106A9A6F8ULL, 0x79CB73363320E044ULL, 
            0x70B2480A9B72E559ULL, 0x9A849D32911F0DEBULL, 0xE1CCE9E004DBF5D3ULL, 0x16856EFA87D8BB5BULL, 
            0x8618AF358F12BCECULL, 0xDC4AA5CDBF9F6C64ULL, 0x2998E6BBAEC8E758ULL, 0xB4C33F9926FBFC4BULL, 
            0x7E9B03BE393F5DBEULL, 0x7BFF4C19A59076F5ULL, 0xFF6CB1E309F6AA9FULL, 0x2773DD613119E12BULL
        },
        {
            0xE0BE8E2E621F242EULL, 0xCEC6B475F29B3FB2ULL, 0x9CF1843B5D201E05ULL, 0xF25C12E5866B758DULL, 
            0xBD66C8A070D2F774ULL, 0x84EBDEF34FD094DBULL, 0x54E369FD826A31B7ULL, 0x790B2683901E0B8BULL, 
            0x2434C3290CA1418DULL, 0x49F8B85C7ADF0F78ULL, 0x3FAC125CA38FBA9EULL, 0xB54217B1568C7DE3ULL, 
            0x410B9E8370218F23ULL, 0xECEACC4063BC7D0AULL, 0xA5134AC08017C064ULL, 0x92899A74F69F1062ULL, 
            0x8B7326E4A93BBCB6ULL, 0x142FA3B248692A5BULL, 0x4D681F2D47F3E442ULL, 0x43891ADDD9B1B32AULL, 
            0xAD2651BBFF242BAEULL, 0xBEA728049C1D4DDDULL, 0x4E71A0946AC3419EULL, 0xCE40BB2AA7D626BDULL, 
            0xF55CE5C3C4AEB3B5ULL, 0x20BDCA74E0C851F5ULL, 0xD230BD2ACA864805ULL, 0xA2E253BAE596282CULL, 
            0x4C1A06F82516F1D4ULL, 0xA50B1403E1FE2184ULL, 0x63A4E44CB23DC249ULL, 0x1460828E3B6B7059ULL
        },
        {
            0x15DDE2AEA2187634ULL, 0xB712DFE60BFCF38FULL, 0x40939D303D82431EULL, 0xE5544872FA928F5CULL, 
            0x6333865C2C987351ULL, 0xFA93022FB0A3E350ULL, 0x23D05D0399B88A86ULL, 0x3FC1E0D3B92440BAULL, 
            0xE6B2E947ADD9DE2BULL, 0x3FD2961A7F85050FULL, 0xEE552426E9A98A80ULL, 0x22536A7FA287FED1ULL, 
            0x032773AD81C8493EULL, 0xAD24E478226AF977ULL, 0x1546CF30AC00D39EULL, 0xB5921E8C2588FFB4ULL, 
            0x513A49B0E833C7E5ULL, 0x06D63B5CA9CC647DULL, 0xD24519709A8A230FULL, 0x7DAAAC41DBE7C69EULL, 
            0xD747C62A5286CD32ULL, 0xA68DDDF09381EAFEULL, 0x8A91C49DD60CC8E8ULL, 0xB38E667721FA5949ULL, 
            0xA2F03871911B0699ULL, 0x00C1BE1ED6DD2AAAULL, 0xAAD3EF8157FC4BB2ULL, 0xA23D966C8CF0C98CULL, 
            0xC9D5252F63071BA2ULL, 0x339682CDB58F5580ULL, 0xBF1BC30501BE2CC6ULL, 0x1F344043905C7380ULL
        }
    },
    {
        {
            0x863FA9E6A1B1EAF5ULL, 0x6D48724B9971A576ULL, 0xED670C15E16A2963ULL, 0xF7AD34A5D8167EACULL, 
            0xC092DE646CA9E4A2ULL, 0xAC4D6E7DEADF1FC9ULL, 0x16E73C3651E81F7DULL, 0x5B7BC4B8D5F14C51ULL, 
            0xCC9CAA8481BDA5A0ULL, 0x8BF01C92AB482C0DULL, 0x036A2CC90C53E80DULL, 0x62D62881C038DAC2ULL, 
            0xD0AFE6D89DF8DED8ULL, 0x6530D4D8A9C8BB4FULL, 0xDD0B8E5A857D93BBULL, 0xB6263126B483CBEEULL, 
            0x8E73BF1DCDC254A7ULL, 0xACAD25902CC02D24ULL, 0x3CB46EBB5C1F5464ULL, 0x3E4D1731809C3D5AULL, 
            0x6F558A1C00C3F4F2ULL, 0x049FA07173D2B81BULL, 0xB0CCA12526FAE3E4ULL, 0xD7892F8844390C19ULL, 
            0xFBB754E03EA68012ULL, 0xCD4ADFC09B920191ULL, 0x1E87C3B032BDF712ULL, 0xA1AD8F63631E2BD0ULL, 
            0xDE0F515A89599CA3ULL, 0xBC5030F63CB75010ULL, 0x9E557DCAE5D5D5BDULL, 0x33158DFA3EFAD44CULL
        },
        {
            0x851DA18B6600885CULL, 0xCC15C99466AFF078ULL, 0xBA77BA84D7C985BCULL, 0x9B06AD7413FC1DA5ULL, 
            0xA23C8DCCE1A2DDC9ULL, 0x02E0094A99840360ULL, 0xEA94C4A3CBEBF43FULL, 0x779EF0745B135B9FULL, 
            0xE4FBFF37B25C828AULL, 0xF3E57A035639E288ULL, 0xAD189CF68449107EULL, 0x26BE182F108DA4C1ULL, 
            0x314634BECCD029CDULL, 0x07E0478F39B4E935ULL, 0xA841ABAD6F916335ULL, 0x2CF3A7202CA4098BULL, 
            0xF474E48CF4686E91ULL, 0x7F9A7EE284395489ULL, 0x787B26FEB51F44E6ULL, 0x474DE1180EA6219EULL, 
            0x301912209222131EULL, 0x471862CC0C0505B7ULL, 0x78FB5E85770B2BD7ULL, 0x39B3B048D1EAF9E5ULL, 
            0xBF78948C087B1051ULL, 0x63FD05989DCF46C6ULL, 0xBEBD998936F6A727ULL, 0x7A913E22517DC30CULL, 
            0xB124136976EBF00CULL, 0xA516915AE86AEF0BULL, 0x4B1742C88A751852ULL, 0x27B05175E1AE8667ULL
        },
        {
            0xBA0F598FEDEB9EB8ULL, 0xD3F0171855487398ULL, 0x2947114EF562FEBEULL, 0xC2632F5F0D624D9EULL, 
            0xDE5DCB2F6D3CADB5ULL, 0xCB05FDE0C80FB5FEULL, 0x5EEB4C64407BA9C0ULL, 0xB5898CC0560942C9ULL, 
            0xCCC625EBBA292E37ULL, 0x5B97EE131A16127DULL, 0xFD55C9B7176E182BULL, 0x49CFDC74F5502CADULL, 
            0x022FAB842D75E251ULL, 0xB69197C0406F0595ULL, 0x6D8C2C4331E0821EULL, 0x1338728DE544D83DULL, 
            0x48A05B0F3D25FA55ULL, 0x11F2C636B4BC09CFULL, 0x7D1008119DF29BE3ULL, 0x63D3068A31650E8BULL, 
            0xEDC0AFA0DF348A9EULL, 0xBC566BC258060371ULL, 0x389A12F859C24804ULL, 0xF5AB7397C626FC96ULL, 
            0x9855F38AA2723C73ULL, 0x349FF543DD82E828ULL, 0x37D3D5E3C2EF1F2DULL, 0x57BB65EA360DCBD7ULL, 
            0x919E9D6BE50140B4ULL, 0x22E2D3054F48DADEULL, 0x7F7D4D1E286E6E82ULL, 0xD9B591E506450118ULL
        },
        {
            0xB2C717D0C98017BAULL, 0x2C031361AF174A95ULL, 0x7736C893381690B7ULL, 0xDA6643308A5E34DEULL, 
            0xB22E9D3BE0FDD36BULL, 0xD28E3652E65DE1F7ULL, 0xDD6D17C8F32CF5A4ULL, 0x99A18375EBD9A124ULL, 
            0xDD856E9F09814943ULL, 0x674786973920B67EULL, 0x224CFB7F07B262A3ULL, 0x93581B191E6800D7ULL, 
            0xCFA4DC42659F5118ULL, 0xB1599DD72319DCACULL, 0xDF4A0848B6DC9692ULL, 0x31528493BA4F727AULL, 
            0xE182B7E5E4A7D70FULL, 0x161EAB52BE055ACFULL, 0x775C1DCA33E60B3EULL, 0xAABE79B9AA9F8000ULL, 
            0x87492C666AEAD41FULL, 0x9CECA22EBE8E0363ULL, 0xFAE6BC9D6F4C5160ULL, 0xE2AE8BC1C4E322C6ULL, 
            0x5AA26AFA4AD6EC91ULL, 0xE8C1CA8A9A74100CULL, 0x5B32ABE1C0398356ULL, 0x484A413331D462DFULL, 
            0x42E00C435ADE5D2DULL, 0x8D12B87DA85A7514ULL, 0x40F40FF2768E96D0ULL, 0xF27630335F9A3942ULL
        },
        {
            0xD41B443C27BEF04DULL, 0xB6A751D393084C2CULL, 0xE62BE600F3B3F0A4ULL, 0x7BD53DFEC6B43E83ULL, 
            0xABDB41CCD7EEE7C2ULL, 0x842CD9E9829E41EAULL, 0xBF7D784B6A15FE46ULL, 0xA32BE25931BC2A33ULL, 
            0x9792D60786282756ULL, 0x24097CCDDBECB6F2ULL, 0x028693423BC4849AULL, 0x7E7D3FCDCB9E3201ULL, 
            0x334D114A3D1E93E9ULL, 0xA08B2C5F4AC70D37ULL, 0xD57060C81C4A843EULL, 0xFF635F93F96EA760ULL, 
            0x3651F92A1B6A912FULL, 0xDCE01867D80CA6B5ULL, 0x90CCDEA3BF884923ULL, 0x3208CBC4A3A196FBULL, 
            0x716F18423B059DCDULL, 0x0C5C0F9482C72E77ULL, 0x65475BBA0B1865A6ULL, 0xF3C7A05A97F91CC5ULL, 
            0x794C6D2C71CB7D28ULL, 0x7E600B14544FDA62ULL, 0xE30DBDBE2F1460FDULL, 0xD448483A619927FEULL, 
            0x02666B50D965D25EULL, 0x36317B28BC0B154CULL, 0x3350926F49595682ULL, 0x762469DBEFB73AA7ULL
        },
        {
            0x50F993B5001A1D0CULL, 0xC4872E149EFD5D74ULL, 0x3120C16ACA5C90E4ULL, 0xF385881981FAC8B1ULL, 
            0xEB2EA0F0072EC7DFULL, 0x5BF849965060CF4DULL, 0x872F17ABFA08C5EEULL, 0x86F8BA51E7B2D518ULL, 
            0xFF6133752F5037DEULL, 0xB689B0F9D6378B72ULL, 0x2ED81C24AF0A8537ULL, 0xF116751B542684EFULL, 
            0x0D283B0E0B892AE4ULL, 0x1E0C51160E45E7EFULL, 0x91E411338D7BAAFAULL, 0x2FF3EFEDB4EB07BAULL, 
            0x35429B7E9B3FFC49ULL, 0xB4371F507D637D36ULL, 0xC168AEA0FF50A332ULL, 0xC385C44761DB067EULL, 
            0xFB1B32BF8382B916ULL, 0x90D10865374A933BULL, 0xFBE9F73E685BADAFULL, 0xBC00E97BC9450BF7ULL, 
            0x07021D6169A4CE27ULL, 0xD72D98BCE07DEF12ULL, 0x2A06174DB7D1A53BULL, 0xFC16F14E42542FDDULL, 
            0x1A5965AD0F7642BEULL, 0x655F3501D174C62DULL, 0xCF63EB8198FAA1E7ULL, 0x6CFCF77775BEC460ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Altair::kPhaseCConstants = {
    0xF9AA5C179E30077CULL,
    0x52A6983F6A0073E3ULL,
    0x9665B2BB6E4679A3ULL,
    0xF9AA5C179E30077CULL,
    0x52A6983F6A0073E3ULL,
    0x9665B2BB6E4679A3ULL,
    0xAC2DCB28C9107E65ULL,
    0xE4945F70F3B12A1AULL,
    0xF8,
    0xDB,
    0x01,
    0x86,
    0x38,
    0x81,
    0x08,
    0xC4
};

const TwistDomainSaltSet TwistExpander_Altair::kPhaseDSalts = {
    {
        {
            0xA945A9F5571AB3DFULL, 0x1CDCB286D36C30F3ULL, 0x0B2B43DF7C47258BULL, 0x81F00D50E7D63304ULL, 
            0x346471A41CC95D67ULL, 0xE4244D49C11EF5AEULL, 0x5B93A2C2E04EC247ULL, 0x31B96822937B4393ULL, 
            0xF56A96E40CF52577ULL, 0x5BDF3D47605AFE7CULL, 0x8EB7C7F3BE327561ULL, 0x953C22B67158BC91ULL, 
            0xB97B3D24C57F3A8BULL, 0x066B76FB2B584A5CULL, 0x9C0FB5E0A9165FA4ULL, 0x7519C5726759BC9BULL, 
            0x797A9AE5BBCD56B1ULL, 0x15F2114CA7C42491ULL, 0x2CDAB80AAEB66E06ULL, 0xB557A6CC6C8AFFCFULL, 
            0x131252ABD1339567ULL, 0xB3CABC3C232A6EEDULL, 0xFDB6B0C925C40074ULL, 0x2B399AEC4A2AAAE5ULL, 
            0xBC9571E845217C78ULL, 0x244D586BC6E25147ULL, 0x498DD4F1CC9DE1A3ULL, 0x508D6AD8C69D964EULL, 
            0x34C22EA343A2EC88ULL, 0x791449B97703B709ULL, 0xDFD1F5DCFBABC7F3ULL, 0x34C42628C440B475ULL
        },
        {
            0xF0CDAE2338480937ULL, 0x017D192508F27B94ULL, 0x13C55E92B050F242ULL, 0xCF8196CDAE288FC9ULL, 
            0x3D7747B97D14DDCCULL, 0xE5F89DDB62649861ULL, 0x71654D3769D4CC1FULL, 0x0DC84565B62E36E9ULL, 
            0xE79FEACBE8C25146ULL, 0x86DB88C83D773F5AULL, 0x3B66EB132C9FD025ULL, 0x957A59A8BADAFBEEULL, 
            0x007C0BCC16C03E59ULL, 0xC9F49860CB2F6CD5ULL, 0xD801C6A604393D49ULL, 0xAC65B91B03F65096ULL, 
            0x7F884ADD3369692FULL, 0xB4833B4B93144B34ULL, 0x89A6B6E5BC887A46ULL, 0xD3D940BF5F7541A9ULL, 
            0x62D80944D5C02463ULL, 0x3434BF6290AF4852ULL, 0x0B11CB9172636521ULL, 0x59815E498C238D6AULL, 
            0xFF149C4243F2CF3EULL, 0x35E18C0D08AACFEEULL, 0xC038C62C4B7BB3A0ULL, 0x69A7DF41184F4145ULL, 
            0x427040C7A843B604ULL, 0x588C87B8380CDA06ULL, 0x758C5E7A505F968CULL, 0xB95EB7DBE3911A0CULL
        },
        {
            0x65AC05F5327E91C4ULL, 0xAF4706545867EA31ULL, 0xA0AEEE501003ADF7ULL, 0x22B044828610045CULL, 
            0x0652789256B96B72ULL, 0x007247C072F672E5ULL, 0xAD7E8B9833F5739EULL, 0x91D8C30D56215EEDULL, 
            0xFB5C5B22E7B9DB69ULL, 0xDB36035360111295ULL, 0x9A417752B02372ACULL, 0xFF44098827932E36ULL, 
            0x3CFDB934C922978CULL, 0x14136224AFEDA8CDULL, 0x53C01B43D89D76E9ULL, 0x38993C4F2EE5A1D4ULL, 
            0xE23C90315C16160CULL, 0x4C03B2EA24222D09ULL, 0x3A599C35C4CACD7DULL, 0x733B75596093E508ULL, 
            0xA8A48CEDD49BEE53ULL, 0x51FBD98F5B0E5E43ULL, 0x20D0EF3C1A83A5E1ULL, 0x7D7B3A6919033CD4ULL, 
            0x908A1A67C9B982AEULL, 0x943449413E734AD9ULL, 0x29BCD8A1AB9D434BULL, 0x18F418F4D5997C81ULL, 
            0x1E81C8D36E62A299ULL, 0x8A86989EE83A362AULL, 0x572709A6CC3BA206ULL, 0x7FEC8C6930DA5D7EULL
        },
        {
            0x81C7FE6DD4ADDC1AULL, 0x7E3E578DB3D957A4ULL, 0x5CDECDB94B24CE91ULL, 0x73AED24FFB791709ULL, 
            0xB7CC4AE2F40E5B58ULL, 0xDAD911E66D5DCE4AULL, 0x4D810384E5A800B8ULL, 0x0D564EC41633C3D2ULL, 
            0xC517CDD9EDA8AFEDULL, 0x6E2E83F46BC82B01ULL, 0xF6CE046FD2D00C07ULL, 0x07A5AD96415D94ACULL, 
            0x2A5BE8799E67973EULL, 0xA22F84AEDA90ED02ULL, 0xF601A280DE579DCFULL, 0x6C27A4613E142AE2ULL, 
            0x186B421FC1FC17CCULL, 0xDA8BD63AC96ECE6FULL, 0xE13DD76EE6E390A1ULL, 0xE2678702DBEA2696ULL, 
            0x3444D1EB17F78096ULL, 0x32E968079BC451B4ULL, 0x9049706F846AB428ULL, 0x6D1052FD2B68C89EULL, 
            0x913CCA3ECACF490CULL, 0xB56334868C9279D6ULL, 0x58DC7C7961B60A01ULL, 0x4E783B963D848EA4ULL, 
            0x9FA4DE4C64D18AE8ULL, 0x9A97D91599CC5A1BULL, 0x0811B1DE0507FFB4ULL, 0xD9193C19FA9DE304ULL
        },
        {
            0x1CEBE216F1CA0EF9ULL, 0x3F2A5120E5C782A6ULL, 0x4092E387FFFFE21DULL, 0xEDA5618DB9182C22ULL, 
            0xED2555006FF9A616ULL, 0xEBA2943F8556C6EBULL, 0xF2DD093F9E5C7750ULL, 0x5AE4F22BEB6B6C28ULL, 
            0xD9F8BA9C729BB448ULL, 0xD13B8E3866DB5843ULL, 0xEF85C3669F95C80BULL, 0x6BC01BD46C42CBFCULL, 
            0x9A9F6091BA0AA68DULL, 0x5F6221926DD8D08EULL, 0x81E8FCF5861F5B73ULL, 0x350750E2B1AF402CULL, 
            0xF33E24C2FB51FCEAULL, 0x52E8F400332E6852ULL, 0xEA9A53C068C2A378ULL, 0x7155087B52FDA10BULL, 
            0xD1030AC681EDA388ULL, 0xA101CAEA7E1165C0ULL, 0xDF1BA455FDCBE991ULL, 0x7B345C4A9A8BB64BULL, 
            0x6B429DD3F5D0035EULL, 0x6102DB596F25D605ULL, 0x24C1231AA7A2F9B5ULL, 0x0CAD63F6C6E0EC79ULL, 
            0xC4357ACDA8EC7BE9ULL, 0xDEB3305AD2CB3EDBULL, 0xE40F6E11AA3C3FF1ULL, 0xA960725A34F65E27ULL
        },
        {
            0x51FCA733EB3E5E70ULL, 0xC99BE235514F62C7ULL, 0xDB33AC21B1B8B1E2ULL, 0xBE9D01E0C2F5D48AULL, 
            0x1DCC7C64DD1DA8BFULL, 0x125D06CE25FCDACEULL, 0xED99A8B7623F31ECULL, 0xAB5A2976401D9F77ULL, 
            0x434960E6F9B63000ULL, 0x07E894A32189D6A2ULL, 0x31DC870BE1BABE35ULL, 0xE1DBAA9655FE76D6ULL, 
            0xE134D17B8A6BE5BBULL, 0x94A2F56EC6115248ULL, 0x34DFCA85C2E11AA5ULL, 0x24FFB822DF6C0DD9ULL, 
            0x50E72739AE3691C6ULL, 0xC9AFB1FEFD7D8FACULL, 0xFDA3EDE9921A59AAULL, 0xC2B4B9B6C441AD08ULL, 
            0xBF64156806F4AC52ULL, 0x02FE9C34C35191ECULL, 0x41A2478CBDA1CF32ULL, 0x1615D88A20C96C13ULL, 
            0x3DC59E32F3F252F5ULL, 0x966BB2D65721AF25ULL, 0x0640BC28E2A72106ULL, 0xC4CF378933A1645BULL, 
            0x71A2E07B0179D717ULL, 0xF61EC4C6E3F7775DULL, 0xAFB36C0ABE498C60ULL, 0x0280FFCB37AEFA92ULL
        }
    },
    {
        {
            0xDC8134B58709C5CEULL, 0xC47E19DA94BC51D4ULL, 0xCE27E98BE23E9035ULL, 0x4F43F6B6729AE8DBULL, 
            0x49B777746DDC61D6ULL, 0x15333279CF55B88FULL, 0x142E1DA627B6CCCBULL, 0xE8ED26471F76CBBCULL, 
            0x5BAAD0300C406776ULL, 0xF9A2C05E657BFE6AULL, 0xB433E66C84E7B4E5ULL, 0x827D5AF025C46A63ULL, 
            0x9B89192DD4497781ULL, 0xC3D5B1C5149316FBULL, 0xEE90A1EB6E1B9FB0ULL, 0x81DCC0AD57F0B56DULL, 
            0x2531C40149690DECULL, 0x4F895B2FE48A4931ULL, 0x5BB6732BE52642D3ULL, 0x0B93AAFD58F15387ULL, 
            0xD659728E1E1607BEULL, 0x7ECDAF96B7F48CDCULL, 0xF010B66BCEAB9D02ULL, 0x173FE5B5D34CC459ULL, 
            0xBE83726E6A15F02AULL, 0xAF05BF5EEF556C74ULL, 0xA10BB8D52BEA6409ULL, 0xCFB28F3003A3E803ULL, 
            0x54D3F808B8AB1890ULL, 0x800FA599AF3598A2ULL, 0xCFCE0011962712DAULL, 0x4018D73A3B213399ULL
        },
        {
            0x93B9850A55D48962ULL, 0xC014D53BC0E38141ULL, 0x9980D924770D156EULL, 0xE36B37CF19371E24ULL, 
            0x9454664E5429CACDULL, 0x5586B2480B8A431CULL, 0xC5EA54F1565BB125ULL, 0x8DA3F15246538950ULL, 
            0x747D83953246C4E5ULL, 0x6C6A83A4E82E1A47ULL, 0xEB1258CD11C018CBULL, 0xF5D8C13A13516539ULL, 
            0xDE0EE651DC2CFA98ULL, 0x07C32506BB308FBEULL, 0x1479113B36AD4411ULL, 0x2C180F9DA5D9345CULL, 
            0x15E2D9D187DB1EA5ULL, 0xE685CEE33314BEECULL, 0x2ECAE68538BFAC3DULL, 0xC4BF395274C89FA6ULL, 
            0x2DAAA28ABC09F34BULL, 0xC1BC85894B0CB878ULL, 0xC4A1E8080A2EB1DFULL, 0xE67FF2AC73CD065CULL, 
            0xCDCF552A94ACBA24ULL, 0xA587C3596A6BCAC3ULL, 0x2DE0A62DBFEBA65CULL, 0x41BCB5BE19052EA4ULL, 
            0xD0191FF4C1CB048CULL, 0x43A0B3AC310BCCFFULL, 0xCC9E6703518768C4ULL, 0x68268A40AB2A910CULL
        },
        {
            0xC3023E063D38C06BULL, 0x3B33DCFAC163EAFAULL, 0x32F20DE2C33B04B8ULL, 0x07EE3B5CF8E2762DULL, 
            0xD07028B18FC2324CULL, 0x47699A34399DF2B2ULL, 0x2B207148ED47E30AULL, 0xF827CCDAC49EAB92ULL, 
            0x02C37518174252A5ULL, 0xFEA051F7B765E093ULL, 0xF119C792618D5D08ULL, 0xE93A511802E41325ULL, 
            0x92338324BABFFB23ULL, 0xC65E39B6B955464BULL, 0x1B9936B34B7EA1E8ULL, 0x00D4DB72930CCD10ULL, 
            0xC4F6D0783EF64ACDULL, 0x78C5BDE03FABFB75ULL, 0xE0F06E84665BE2A7ULL, 0xDA3158229A1CEBB9ULL, 
            0x0588DCB03A9631F7ULL, 0xC7ED2DBB5B37B542ULL, 0x1374E49B05181466ULL, 0xC3EC04AE57DF07FDULL, 
            0x34CC724FBAB592EAULL, 0x63F6588F59C8B6ECULL, 0xC607381EF40C5004ULL, 0x0E496C87813CE32DULL, 
            0xCBEF5B80BB46EEEFULL, 0xE6F10E99FD1F5C4AULL, 0xBB10A03AE5C4DE64ULL, 0x5521BCD786E2DBDBULL
        },
        {
            0xD2B285D67A825F85ULL, 0x711D4DDB0FDFF159ULL, 0xF240FB376EDFFE9EULL, 0xCAA923336B9E4398ULL, 
            0x854B7DC29F76E082ULL, 0x537ADC809D5163BCULL, 0x54D7723A8D18BAAFULL, 0x0814E01253E4CFABULL, 
            0x6A0C83CD6C6226CCULL, 0x6889FD12C8978A35ULL, 0x3383AE3F53EAAD86ULL, 0x4AA24CC1F5844DF3ULL, 
            0x7859D5E453646CBEULL, 0xA59B869507C7AB6CULL, 0xF101515701C7C92DULL, 0x3F47E2D92B3C0A65ULL, 
            0xBF4069CDDCF5D5BDULL, 0x7D628D4A27AC8768ULL, 0x5BBE1D19408648FEULL, 0xCF46C24EDF7A2EA9ULL, 
            0x7FB983BAF09325FDULL, 0xBEA0255FB5639F18ULL, 0x007B424A49C94522ULL, 0x118091E9E558CC44ULL, 
            0x5DA22173511910CFULL, 0xCF3031F93C03C24BULL, 0x121E962B9BF24ADCULL, 0xA2BC3A1B6B6B3B48ULL, 
            0xEBDF850BFF4D1104ULL, 0x9F80DDE3799A76BAULL, 0x1A2FBF433F695157ULL, 0xEF533EB13EA3559DULL
        },
        {
            0x47D5101763467CA7ULL, 0x5062C090B48842D5ULL, 0x0A43CA2EC39B80E8ULL, 0xE24AF3A302C1A9F0ULL, 
            0x8004F8CA7413C4ACULL, 0xE8F41D31ADDE660BULL, 0x129890617CEB55F7ULL, 0xE767580BCBBE5C5FULL, 
            0xA4F986C1497B5453ULL, 0xE7C8A2FA6A050973ULL, 0x64200EB0E95B3E64ULL, 0xF0E409F8337DCE54ULL, 
            0xFC6BC49518CDA27CULL, 0x116313B2A53F6222ULL, 0x503167D44A162855ULL, 0x0BCD004AFF46E68EULL, 
            0xF3DBBE87BD293A06ULL, 0x144249A25E730153ULL, 0xD70A729A003B5F36ULL, 0x8FA606E387ED261EULL, 
            0x49C7CE5C041E9DF5ULL, 0xA1113D61C6C198EBULL, 0xB8ED3E09E32B056AULL, 0xAEB0E8716382C67EULL, 
            0x41DB83C4E2060264ULL, 0x45153C9BB340270CULL, 0x9692BEBC139EB03AULL, 0xAE822C216FC77E07ULL, 
            0x918369D08F9656CAULL, 0x397E5C4A48B8B378ULL, 0xE513FAA92D35B40EULL, 0x3569C5EE04C05E02ULL
        },
        {
            0x4E9F14578C8E2903ULL, 0xB156578820778DE9ULL, 0x17263D322566F61DULL, 0xC011CEB7CB994230ULL, 
            0xC768DEA45E78BA54ULL, 0x5C6812F41C5EFD13ULL, 0x72A453D2BEF2C54EULL, 0x3952A2FF44669C34ULL, 
            0x536484DBD98FAE24ULL, 0x852815721A6B8BA8ULL, 0x369D865413FCF01EULL, 0x492EBB84D27770AAULL, 
            0x310683C11B649DC1ULL, 0xDC89B51AD5ACF9B2ULL, 0x3225B3105B0F33C5ULL, 0xC7D1E18531835331ULL, 
            0x1C4E36E71AFD08BAULL, 0xF3BF5ECFF5F45097ULL, 0xDF7505A8D131942DULL, 0x9F81D7E164E8DAADULL, 
            0x1B1B0DBBED9795A1ULL, 0x3EB4C6D3C65BEC0DULL, 0xC178AFBBD73543D4ULL, 0x956BD60C3D36A8B1ULL, 
            0x8DAC959E7FE97AB8ULL, 0x3390E9C9B801A40CULL, 0x116B5681F3158231ULL, 0x10F6015E8C1AED32ULL, 
            0xF17D64CB30BD4248ULL, 0x8F4610176E0632FEULL, 0xAC07D3FFFBD9DBA4ULL, 0xB3CD28A6C13C8610ULL
        }
    },
    {
        {
            0xE9303B47D4F47FAFULL, 0x63DF34683BE8D221ULL, 0xED4220B21668D0DDULL, 0xF9FFA3C049B666B3ULL, 
            0x7943905177278A24ULL, 0xBF0B4E0A0029B26EULL, 0xD0C0D41E62132086ULL, 0x82F111A0D0FEF19CULL, 
            0xDFC8B4285064297DULL, 0xCEDEEDBD1C478029ULL, 0x3FD117825AB5366EULL, 0x6F24FCF6D65FAF29ULL, 
            0x0F85D5590B513588ULL, 0xB9903C5D4FCEE0DBULL, 0xA04266BFF2FD4CC4ULL, 0xE2C2F91E6A414C57ULL, 
            0x988A612AF6904F2BULL, 0xAF0138C98040F386ULL, 0xBBE279D785BBCF5BULL, 0x17E00F17CC7BF272ULL, 
            0xDB93FE53925A49B9ULL, 0xEF04AFD32CAEED1EULL, 0x558EE356F59A59B0ULL, 0x5931F6EB106AA2FFULL, 
            0xB777250EA42A29C5ULL, 0x593A88A85A32F3B2ULL, 0x51BC9B153FB507C2ULL, 0x682BB2943D9F62F7ULL, 
            0x50E9A28A8C44A153ULL, 0x695D3BF659B00361ULL, 0x75631A424973BAA5ULL, 0x58E34B35E3BBA85EULL
        },
        {
            0xDDA6A8585F4C1717ULL, 0x58549A4DF3779856ULL, 0x75E903D9645BC800ULL, 0x557662FCFD10459DULL, 
            0xF3CABF4993F49C1DULL, 0x0A8385A470A04473ULL, 0x978DBEC7B7D2B143ULL, 0xF4FBDE5BCA0370E3ULL, 
            0x5804C018F36E3965ULL, 0x7396393672EE7C28ULL, 0xFEE91A98117DE847ULL, 0x1F2A2954E619C341ULL, 
            0x12524B2BD7AD3371ULL, 0xABFA1F6BA659A8F4ULL, 0x97CC443A8E28AD36ULL, 0xD6792B4E93D657F8ULL, 
            0xA7BE83B5BEF1A636ULL, 0xDAB0BBA49C3B59DFULL, 0xE198BFB6933A3B2AULL, 0xE7690C3E10D0DB73ULL, 
            0x4A3318EDBA495E69ULL, 0x86B1529D105B91ECULL, 0xD442A7B877949853ULL, 0x78FAE47F8D01BCA9ULL, 
            0xC9409DC901CAE142ULL, 0x6E270043F4952F00ULL, 0x992D70222B656725ULL, 0x15C29131C731C8E3ULL, 
            0xF7CACFCF15B54D17ULL, 0xEF243FB39B3895E4ULL, 0xF9F8C82479AE8969ULL, 0xC8BBBA23E9344CFFULL
        },
        {
            0x50F11EFC819DC695ULL, 0x917C5AF11F20685BULL, 0x015E5259A121F7B0ULL, 0xE8E25CBDC187DD0AULL, 
            0x9131857D2EF5B25BULL, 0xE7CA7B97F0039EB1ULL, 0x6B10D86324FC0B06ULL, 0x2D75785328246CFDULL, 
            0x38B7DEB771ECD320ULL, 0x418EA05043005472ULL, 0xD054BEA8B0ADE610ULL, 0xA277CFCEF507BBDCULL, 
            0xDACEC6E6611EEF9CULL, 0x5E41455618F70F3FULL, 0xA0D25608BC244AABULL, 0xBF5C5D6FF3AB9D1BULL, 
            0xCB3EFD3B8124D29CULL, 0x2961430F0967EE81ULL, 0x6CA5DFB02911266FULL, 0xC683037051585DB3ULL, 
            0x97A7BF5170F2E83AULL, 0xF733DA05C837FD73ULL, 0x0075E8257F865931ULL, 0x402466DC2247F948ULL, 
            0x39FC83BD0D2500A0ULL, 0xBBF1DF5AC67D0C2EULL, 0x4E10759601EAE3DFULL, 0xED2BEA5671D88F98ULL, 
            0x038AE1E841A4B080ULL, 0x1E2E5750164F0ED8ULL, 0x24CDA50615098ABFULL, 0xE42AEF8B65C86953ULL
        },
        {
            0xF7755F9A5978520AULL, 0x2103AB632091EF75ULL, 0xE1FF1FFD8E2029BDULL, 0x4454C1C840549DA7ULL, 
            0x6022F54A11744741ULL, 0x64A7994A16936CC4ULL, 0x20ACA0391DA6D5AAULL, 0x0F4143120F7186C1ULL, 
            0x84F5DDD4DF6DE682ULL, 0xE0F5B65286629687ULL, 0x8C1D351D4621F283ULL, 0xF97D01F435DB3957ULL, 
            0x7F60536B8B3C0638ULL, 0x1D080EEEB9DA75D6ULL, 0x90ACC2187763CFB9ULL, 0xDF7ECE51866C27BDULL, 
            0x9585363B09BE7D48ULL, 0xF4E2B4D521AB8871ULL, 0xCCD0F704CF41163BULL, 0x6C7D02B0D60CF253ULL, 
            0x5540077171C6DAEDULL, 0x534AFADCBB99BD66ULL, 0x350469DDE40D90BDULL, 0x6ECF8BBB504BA387ULL, 
            0x2308C4573260F1FBULL, 0x9BC5C336FB9D0879ULL, 0x155F07B0943EB1E1ULL, 0x35150F06FAD1C354ULL, 
            0x5C40C2DD543C1ADEULL, 0x3D0874C49D8F1916ULL, 0x18BF0465FB36A842ULL, 0x35A69BA1B162EEA2ULL
        },
        {
            0xA20A73521C7B4AE6ULL, 0xE20D837DFDF25E4BULL, 0xF87C0022EF870060ULL, 0x4A7E99AC21C5FD8AULL, 
            0x98EA354BB871E524ULL, 0x5F97113D35F3B74AULL, 0x613570B05759B52EULL, 0x3ED0766E15E25797ULL, 
            0xC133CAD50A2C9F1CULL, 0x5BF56CFF896D0017ULL, 0x56B52F2FDC9847CDULL, 0x456BBEB6F6D660EFULL, 
            0x2EFB37917089C6E6ULL, 0xD3B73E7DE8362E40ULL, 0x7338309C6D61632AULL, 0x59E04707A53A4F05ULL, 
            0x6B5BB13A4B2DEC68ULL, 0x1C6C0CDE2C8CD6E6ULL, 0xB4FF7739DE365963ULL, 0xAF4B53CCA5F48566ULL, 
            0xEF599D9A9859681AULL, 0x341CA7F0666B09BDULL, 0x936D949065F420A0ULL, 0x6D79E753E30D9E93ULL, 
            0x6DE868B2227B7C9CULL, 0x4B059CC8173E4E4DULL, 0xA53748E0500ED4ADULL, 0x70632802BDFB5829ULL, 
            0x019D980D256E5B7DULL, 0x8F7247D26731073AULL, 0xA2E567FB1F4FFE9FULL, 0x084F0F7B7CFA6342ULL
        },
        {
            0xFA59D7EBBABE131FULL, 0x6AB09C4EA24C8FD8ULL, 0x3384B13928F7F271ULL, 0x2426CC9A3DA4BB3CULL, 
            0xF8D1A2334FB7660EULL, 0xBDE3D1E90B3D2EF2ULL, 0x9E4A4488A589E358ULL, 0xC1CEE2E9F0ADBD51ULL, 
            0xF7C618F039B9D2A8ULL, 0xF0678A8576528DAFULL, 0x3733BA0EFCE78FD1ULL, 0x9A64C2570792862FULL, 
            0x91C71CBE90ABDFAFULL, 0x7D8D7E1BBD06F8AFULL, 0xCA1B342A91953537ULL, 0x2C136DAE2DD04F62ULL, 
            0xA9E620BA49FA466EULL, 0x3BDDFDEB6055C360ULL, 0x5BFC131F884A6A54ULL, 0xBD76123A48DE412CULL, 
            0x32CAB9B10164650FULL, 0x28E5240ACDCBA852ULL, 0x400F5F6DD949D8E2ULL, 0x0A77DC9BDA2F16FDULL, 
            0x9E7542CA3FE70CD9ULL, 0x30EC57C57E1B1F5FULL, 0x75A1216F0559D319ULL, 0xA45C91C23729D5BBULL, 
            0x4588E0F3C9C6DD25ULL, 0xC4CCCB4DE449B661ULL, 0x7D1D5EED712E9E87ULL, 0xD07A8C30670F46C7ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Altair::kPhaseDConstants = {
    0x451D85926121BA75ULL,
    0x066F64BAC1227953ULL,
    0x61A825769E7F5E9FULL,
    0x451D85926121BA75ULL,
    0x066F64BAC1227953ULL,
    0x61A825769E7F5E9FULL,
    0xAC6F2826F07B871DULL,
    0x151C910DD373ACEAULL,
    0x6C,
    0x28,
    0xEF,
    0x3C,
    0xE3,
    0x59,
    0x30,
    0xAD
};

const TwistDomainSaltSet TwistExpander_Altair::kPhaseESalts = {
    {
        {
            0x32F6D5A8F8E421A8ULL, 0x4F1E5361F5D31033ULL, 0x1EF5B1C4F3E0F410ULL, 0x0BFBE5C4011E5988ULL, 
            0x0209EF02C50FA5DBULL, 0xC7CC90C6E4EB7C16ULL, 0x5EB3D8646260188AULL, 0x6620F6D5C4549878ULL, 
            0x4B5D04844D25F254ULL, 0x51C23CFD46F33262ULL, 0xCF910A4ACFC8A6D8ULL, 0xEAB2503774F1F586ULL, 
            0x443D619AE451E761ULL, 0x039E5F9AE23348EDULL, 0x30AC712C7CB3DE11ULL, 0x33EBA15F1EB0996DULL, 
            0x627507E23BC4100BULL, 0xFD2C2AAFCB96B84DULL, 0x4414E1AE89F8AA55ULL, 0x52E3B2D24B3E86A8ULL, 
            0x7C01D8AFF042AE15ULL, 0xB05D4DBA82079610ULL, 0x709E547E66C3787FULL, 0x87883351CC588553ULL, 
            0x6FA5F16709490C29ULL, 0x1334DF878DFFEE5BULL, 0x7C7ACC6685B246FDULL, 0x26944A1AFF1DFADDULL, 
            0x5B52BB69A129AD33ULL, 0x091917EE1D8DFEDEULL, 0x7BE46A8070797403ULL, 0x9B8A5D84768B8BAAULL
        },
        {
            0x38C5CD49968ABF77ULL, 0x8EA9E0AACF047E1BULL, 0x8E5AEE912F0A6E20ULL, 0xDC499D159948B3A6ULL, 
            0x5E010AF96EBC56B7ULL, 0xE4A128253F14537DULL, 0x3BD9F2AC03304CA7ULL, 0x4BDC5582EDE74D37ULL, 
            0x9EA35024F2ECBF6DULL, 0x80DAB1DCDDCC7D32ULL, 0x12FD69AF001B6542ULL, 0xD7F7A32A5CCC2372ULL, 
            0x22083C2A63B8C9DDULL, 0x18C4BB6B97EDA973ULL, 0x9B1652E6BF2D8B6DULL, 0xCF21176965C66703ULL, 
            0x2972D8168B056370ULL, 0x3A499742B74F4056ULL, 0x8261B4AC473C83EEULL, 0x2192664D7DD925CDULL, 
            0xC16D5D2DDAA3EA1DULL, 0x5E634DB9BE13B238ULL, 0xB53AE04ABA70D563ULL, 0x64F1012FED8CE684ULL, 
            0xB1B43561604CDD1AULL, 0x517BD00D2A28556EULL, 0x08F699867ED54283ULL, 0x163257B367F1880BULL, 
            0xD11C814900FBF942ULL, 0xC7F46FBF7345D331ULL, 0xB949EE4E96D5A6E4ULL, 0xB0FC8815BEFE17DAULL
        },
        {
            0x84759A393B3FA952ULL, 0x05DCF7F3CC27001EULL, 0xFEBA61F40710BA1CULL, 0xD1D2897BCBE5A8A7ULL, 
            0x9D341A1163CF3021ULL, 0xB60771BF0B21572FULL, 0x8079AEDBC0F7709BULL, 0xD22B6D2B03D61305ULL, 
            0xA71357420E2B790FULL, 0x9CE6A8A51186F478ULL, 0x83F3EC3A05DB0F88ULL, 0x4401EDDE4BDBA5BAULL, 
            0x987CF0D6CC23DEC9ULL, 0xD7202A1611584980ULL, 0xDF29016C864774EDULL, 0xE1447C63CD70A1D7ULL, 
            0x998ACFFC8D6E1CD2ULL, 0xBEA114C1008E6863ULL, 0x72EEAD0BF6307EC3ULL, 0x27EB0D76CDE33A0EULL, 
            0x01D596128D2E9BF7ULL, 0xEC7A9CCF56103630ULL, 0x2896D1CC857DB782ULL, 0x64015BD3A99EE847ULL, 
            0x49756C3C9D4683ECULL, 0x79DB3DCF3D0C36DFULL, 0xF56A9FFE39912273ULL, 0xFC86B14A96CD6B4EULL, 
            0xAC41F3180D58D06CULL, 0xC2C5386728E7CADDULL, 0xD5BE3C2E09D152D7ULL, 0xAEDAC06597A0B84BULL
        },
        {
            0x4BD4878919D5A679ULL, 0xFCD3ED0A4D8164F6ULL, 0xDA32FF9A14F4F5BFULL, 0x75046A15A7878AA1ULL, 
            0x9B7A81525C87AEDFULL, 0xF9368717C724E9F6ULL, 0xC70A56983778B1B4ULL, 0xC0D11359C5B117B6ULL, 
            0xD1D124ACF8B0F38EULL, 0x72B3A4705912D270ULL, 0x988E86EB6FDE25F4ULL, 0x22D73A4CD7FC45AEULL, 
            0xDB10A23F90A2E49DULL, 0x011C51D4444F4834ULL, 0xDC9163FED021778BULL, 0xD69EB2F6D26CFE1CULL, 
            0xA28BD6090BCE562AULL, 0x277421406EDF1C49ULL, 0xA560129AE2C179BDULL, 0xC7E60341868A5195ULL, 
            0x631BBCD58904ADA2ULL, 0x96654F0D9FEBF72FULL, 0xAA1544FB8CAD82C7ULL, 0xDAC69ED2924F843CULL, 
            0x97AEA93DEDF934F3ULL, 0x392C0B8036734592ULL, 0x20187719451503E4ULL, 0xE5B5B286CE9D295FULL, 
            0xC4D3C4B53E47B6EEULL, 0x0B3445F7D2261E0DULL, 0xF0E446B6F3136F88ULL, 0xF6AB7ABEBD867CC1ULL
        },
        {
            0x0290F46CF282B64CULL, 0x4A5FE860DD4850A3ULL, 0x409DA473222BBC4BULL, 0x43D7D9CF7886B410ULL, 
            0x4E0D347B60748517ULL, 0x5F909BEF78EC8897ULL, 0xD989D57B9ED3B3F4ULL, 0x7BDA5E8831CE9362ULL, 
            0x65FF5B61E3097B86ULL, 0x13969981CDCF79EFULL, 0xE21DF3E3B6D1EC34ULL, 0x7DDA8B58F50990E1ULL, 
            0x15F5E02C8C5967CAULL, 0x0DD52D2E5A0FFCDEULL, 0x00B17BE244FE05D3ULL, 0xCC341E24C2111CECULL, 
            0xFA24771DFC86FFD1ULL, 0x792C578D613CD503ULL, 0x7D27C5DE4D1F4474ULL, 0x42A6F4E4B6A0B565ULL, 
            0x49E46A3DDBDA2A65ULL, 0x0FF74B92C9A16051ULL, 0x60B9720B2B2DB56DULL, 0x4DF595B7B22D139DULL, 
            0xDC21AD062FC27D23ULL, 0x637C816AA1001E11ULL, 0x33FBCEC3F27B1CC3ULL, 0xBF45DAFEC992C67EULL, 
            0x46FF397D1E1BA788ULL, 0xE5EE15D822C06BBBULL, 0x6DD5363F335AFCF2ULL, 0x1FAE34B09289F1F0ULL
        },
        {
            0xC4379353EF2AE4FCULL, 0xDDF86923FEE8786DULL, 0x7A5A2951EA3647ECULL, 0xE98CD433EED8CF76ULL, 
            0x450090F7672C0B7BULL, 0x61028B24046015E9ULL, 0xF7B034F4873141A5ULL, 0xEA75BBA5D0CB4474ULL, 
            0x0EC5CB395692BCD4ULL, 0x335C4EF804CB8DB4ULL, 0x7EDEAD41825E849AULL, 0x5799DB5B22935089ULL, 
            0xE975E7D0BD915E25ULL, 0x67B3C10F3AADF906ULL, 0xF08FD9B1108C9C5CULL, 0xAC71F220330B5A8CULL, 
            0x9887587F83F50C9BULL, 0xB85EFCF7088D209DULL, 0x61148B9E19AE8C9EULL, 0xF44FA682E0E5100BULL, 
            0x7F00D0523E3FFCDBULL, 0xF261C1BE5312CE9EULL, 0x3437B95D51D1DFBBULL, 0x6FE17BE3B13A3D8CULL, 
            0x920D194F609B3DD9ULL, 0x7DA3A2FAE3DE7542ULL, 0x2285B6F8BBD8C313ULL, 0x38AFFA6FD7E64573ULL, 
            0xC1480B9C3B6A8E16ULL, 0x6E53B9135B4C5B98ULL, 0xCD003852A2F194B7ULL, 0x4684E7BD798C0C4DULL
        }
    },
    {
        {
            0x649BCA07BED787CBULL, 0xD721A9B20CD18B9DULL, 0xF41D2CB91201AD12ULL, 0xC508711B89F6BAE8ULL, 
            0xFF8FCB5F6A4072EBULL, 0xD940C33BF2E6AFC2ULL, 0x05DB205CF17FFCB8ULL, 0x132CF1DEA06D2E22ULL, 
            0xEC7F7CA280A6BDDCULL, 0xCFA6C2DE924A5991ULL, 0x9DF26940404E88DAULL, 0x0656C72B434697DCULL, 
            0x2E46BC1955723AE1ULL, 0x319E03320A42ADD6ULL, 0x44E1125DEC2B33A4ULL, 0x5FCC9D736882E55FULL, 
            0xDA04E189250F2B06ULL, 0x35BC60F0108B20C5ULL, 0x248241062449DC10ULL, 0xE8118183D2684F20ULL, 
            0xB989DC1D885637E0ULL, 0xD2C5B326EEB64D7BULL, 0x506570F77CDF32AFULL, 0x94B93B76353EC14DULL, 
            0x02BEDCC667135AB2ULL, 0x76FF4D93038ED4ECULL, 0x1D34357AA3BFC266ULL, 0xA8532DF6619BD8FBULL, 
            0xB11A016A5FD4B2F5ULL, 0xC4BDDD45CC017228ULL, 0xC2DD07526711F437ULL, 0xFF6B1F673AA2CC87ULL
        },
        {
            0xDCA428545866A245ULL, 0xE8029768C9FAE6F0ULL, 0x0303DA31B4080E71ULL, 0x414EF23E85C6F28CULL, 
            0x8D859B59323A9231ULL, 0xC7AC8AB1CDA0DCE1ULL, 0x7497DC0D0B7A0B60ULL, 0xC1AA224B294BB747ULL, 
            0xC58A28CC2BB8E553ULL, 0x3D29579E0DCCBBC2ULL, 0x902A64D71CBA8CA8ULL, 0x004E6257B33B97E1ULL, 
            0x78C2DF421169BAC7ULL, 0x4E6555DC5695EC91ULL, 0x0DC0E5F785C755A2ULL, 0x1B5D1D8669938554ULL, 
            0x6D6899EA5ACF414EULL, 0x10FD6EFAA2E7255CULL, 0xA547E99DAE559BCBULL, 0xD894D38BC3D82264ULL, 
            0x4376AF3ACCA95E5CULL, 0x75539F96067FD19EULL, 0xCE1B499D4C31CDE7ULL, 0x2972276EE3784F05ULL, 
            0x9A4B5D6BE2A56038ULL, 0x791456426D851657ULL, 0xD959FA0A103D32F1ULL, 0x11DD1C78271DAE74ULL, 
            0xA6756D2E20A64515ULL, 0xE2A2FA769A47B3DAULL, 0x2C86D90BF2491738ULL, 0xB8ED3E3343407728ULL
        },
        {
            0x256C0670A78AEB40ULL, 0xBE576C502DBEA2BDULL, 0x84BDD0BD38FDABF6ULL, 0x6A7A0B31CE238969ULL, 
            0xE7D66B9FAFB231D1ULL, 0xBCE0291FDC36358FULL, 0x75A9DAC207EA23EFULL, 0x5533C72910F62AD0ULL, 
            0x492CCAEBCB899AD6ULL, 0xFCD8A8879B8AD3B3ULL, 0x672624ABBECEAE86ULL, 0x04FB52009A972F7BULL, 
            0xA33F0F170D0DF60AULL, 0xB3688A5AB0EC08B6ULL, 0x84F985E8FA00580EULL, 0xB890C02F5A74823CULL, 
            0x0EF97009612513C3ULL, 0x9D52620CA1DA9AB5ULL, 0xC6F68631E3122EEFULL, 0x7D0DF330858D1A38ULL, 
            0xEC755B2AB7C25424ULL, 0xCEA59E8B6AA44D27ULL, 0x091B36328905379AULL, 0xA1EB700DA91069E0ULL, 
            0xC90FB74CB2637EEDULL, 0xE39AF4D74B05C22DULL, 0xC2831666829AD184ULL, 0x68FFD09FADDC75B8ULL, 
            0x64102EC9CDD059EEULL, 0x584CDF9488BCA758ULL, 0x58ABF9AD7D376DAAULL, 0xCDDA99FF128E1EF7ULL
        },
        {
            0x7DF5419BE65E9F3EULL, 0xCAEF34C85BB4C056ULL, 0x657B88C25BB8FD47ULL, 0x656F93563C100587ULL, 
            0xBE278B634680E9E9ULL, 0x615E6C42410F5900ULL, 0xBE3675E4326EC624ULL, 0x7330FD457AD95E72ULL, 
            0x042C14408E7CBB97ULL, 0x3E5D5798DFE4F69AULL, 0xA33FA48E4DAF4EE7ULL, 0xB875AD231743DE78ULL, 
            0x3C4A13514C54E620ULL, 0xBA437D33385831F0ULL, 0x29BA77ED9A352EB3ULL, 0x0091A2ED81740E88ULL, 
            0xBAA1D33D2A4AF544ULL, 0xDB2B9F2F85B2880FULL, 0xE1FE73E76135840EULL, 0x82A14990C65DAD2CULL, 
            0x2C2D59D7E359901FULL, 0xC82B8C232766FB5DULL, 0xB9DBC9CA4836CAF1ULL, 0x6C27757F62E9AE9DULL, 
            0xA2D5070BC873EAB8ULL, 0x3863D2DF54B21F4DULL, 0x8A5A89AAC685569BULL, 0xB5DB998C44E2D695ULL, 
            0x17E7D21803ACC8BAULL, 0x82EA04CE7523CA07ULL, 0xE8BB791BA0C45303ULL, 0x19FC935771710B23ULL
        },
        {
            0xAB751E9FFF631C90ULL, 0xAB6B31F80838E648ULL, 0x29C1402C92C01C65ULL, 0x495B1FF8ACF1B638ULL, 
            0x0CBAD9FC0C891EFFULL, 0xB94B00C174AC0BFEULL, 0x30239B8531A81458ULL, 0xFEC983432581D2D6ULL, 
            0x193290AFD960EBD5ULL, 0x67C3BA200CEAFC87ULL, 0x4DD1CFC365DBEC07ULL, 0x4394D9DC5E3E639DULL, 
            0x0D834A84DECF8AF2ULL, 0xB3E71E9B973AC944ULL, 0x55D26CD207B816DDULL, 0xA2D1C689CE25B304ULL, 
            0x70EF47C93E17E6EEULL, 0xBFFE46E291025D6DULL, 0x882FA35AD5F0AE60ULL, 0xF5EE8AC3842A6994ULL, 
            0xF10BCFFE7A563AD0ULL, 0x8C112C14615624F8ULL, 0xB1429F0E3C9D8099ULL, 0xC088EC005E1904F7ULL, 
            0x7855AB898908900BULL, 0x9A992F3BB027087AULL, 0x4024E5CC57D87A94ULL, 0x55093DDB342C5805ULL, 
            0x26342BC0AB4747D4ULL, 0xA783136FED1EBF58ULL, 0x76666CE09E9A4FCEULL, 0x7C496DF5B7C89AA2ULL
        },
        {
            0xF59A06F98B29718AULL, 0x2EFB1432F822E242ULL, 0x4F0A97D4500456AFULL, 0x6676863BD68E354BULL, 
            0xA2F2E6F0B92F300DULL, 0x32CAA6F80BE6DF27ULL, 0xE0364C780240D488ULL, 0xCA90F34237EFAB75ULL, 
            0x4E4C5CFEF4968B57ULL, 0x65BA5AB0C140E144ULL, 0x3FE74A1B91E7E6FDULL, 0xA5870D0E11767A9BULL, 
            0x33B0B3587D4856CCULL, 0xED6CAA1B5C84EDADULL, 0xFB0FADA394415AEEULL, 0xF4FC01591F17DD79ULL, 
            0x242C33294359B38BULL, 0x1D17802AC51D15BDULL, 0xE641CFD24C48EAE1ULL, 0x443B87EE234E4427ULL, 
            0x9C16605A6C21DD83ULL, 0x428090C2D0C83F3FULL, 0xF33DE6E876D12968ULL, 0x697863DFEE49C3D8ULL, 
            0xDF9017F874F5F785ULL, 0xA5F22753B0F54006ULL, 0x3A6477564026A8F2ULL, 0xB2628A27C2EEAD75ULL, 
            0xCC44C7EBDAEBD18CULL, 0x7E32A7A88D8E316AULL, 0x1906FFF96AA883D1ULL, 0xC82CCE448E302EDAULL
        }
    },
    {
        {
            0xF611C9B648FF3D3FULL, 0xEE7DF1825E787856ULL, 0x7807E06B76F85572ULL, 0x31A67249A1CCC33DULL, 
            0x2542DCB097C3637DULL, 0x91B0173922A91966ULL, 0xCB63994F63190A2FULL, 0xB4F9A0A300A844A1ULL, 
            0x90B6C955993714FFULL, 0xF2C1FDFB3469BC72ULL, 0x8EC558769530E8FAULL, 0xA5B84E3F7BF05985ULL, 
            0x3E18C54B6476F301ULL, 0x6F6CB055B180C090ULL, 0xA7194D2372B3B3AAULL, 0xAFC792CD3E0C6C97ULL, 
            0xBE9F5CE92D656698ULL, 0xD94A9B93CBCF4463ULL, 0x41E19039358BC400ULL, 0x9A37228F6DD3F206ULL, 
            0x001EF19CA90528F5ULL, 0x5506705D14C09414ULL, 0xCC1E875ADCF1A0A0ULL, 0xC75E3068F894C142ULL, 
            0x3EEFBA21B6EC96C4ULL, 0x4CB70DD1FFCA2096ULL, 0xB7CAD2E55E3DE98AULL, 0xFFB6E851D914B238ULL, 
            0x60E02BE63CDC7020ULL, 0x35C9B2B5C63C51FCULL, 0x2C151B73E65973F2ULL, 0x68F0C46BDE8FB148ULL
        },
        {
            0xDD9DB96416496196ULL, 0xE5B140A166DE77D3ULL, 0xD0A6DD30E2ABECBCULL, 0x6A557744EFC1721CULL, 
            0xCA5E82A1F7CE5F23ULL, 0xAF14F88AEC2F4C3FULL, 0x85B291774AFD08B2ULL, 0x464DACD04E8F3424ULL, 
            0x6537916B9469F22CULL, 0x5ADD29F1882B8331ULL, 0x29A7DCC72A072D0DULL, 0x84D046B989353584ULL, 
            0x766AF2B5C44226BAULL, 0xD53C467053FA7AB0ULL, 0xE376888C8EAF68E5ULL, 0xF92AC2C561ACF33BULL, 
            0x02356EF00F876ED5ULL, 0x753B0FFCCF4B0FBCULL, 0xAB6B2586CFFB76EFULL, 0x504D6CF201C4ADFFULL, 
            0x06D8CA913A5CEE57ULL, 0xD6AE90A8E9BAA3E7ULL, 0xE5BE421A598CC97AULL, 0x1EFAFB8A889F0125ULL, 
            0x0A1E9E05D685DFDFULL, 0xB9720C41DE4F3962ULL, 0x50D34C163272E081ULL, 0xDD4982F2CE3C81E7ULL, 
            0x95CA541E4DC2A0F0ULL, 0xE7A7DB55A3A4ADA8ULL, 0x0F7386D93B32673EULL, 0x0C6137EAF66457BCULL
        },
        {
            0x833DAE2C61055835ULL, 0xDA6F1A23A31D5739ULL, 0xCB8F268396C0903EULL, 0xA963F09700D4745EULL, 
            0xC59DB5E21E9D1253ULL, 0x50B6561A523F61F2ULL, 0x5A683E19CBA0FEE7ULL, 0x807B535B11494844ULL, 
            0x2196ABA5EF64FD6BULL, 0xD25AF469EE13860CULL, 0x4234A63EA635CEFDULL, 0xB4D6CA78DEFBCD5BULL, 
            0x6C8A781F0CCA513DULL, 0xEF154F44E3E255DCULL, 0x163F8A0EF52FE663ULL, 0xA4EBD794A5ADFF27ULL, 
            0x79B8FC92C89646BBULL, 0x4769741B00EE286AULL, 0x371F307072D4573EULL, 0x1D72B948049AE1A4ULL, 
            0x183AFD76A1628F7BULL, 0xF87FA1E11AEED233ULL, 0xB1E96CD43EE60F87ULL, 0xE4CB2F3E635F6DB5ULL, 
            0x05A1561F06C6CDCCULL, 0xEBAE562E0B87DDE0ULL, 0xA387FF337A123FAAULL, 0xAF3F11E900640EECULL, 
            0x2AE56FF038689504ULL, 0x9015AA1E208A72AFULL, 0xA24F24AD6E6E3F9BULL, 0xBFAE7D5B4739A155ULL
        },
        {
            0xAF7E103C6D411193ULL, 0xA9B561C2E514E08EULL, 0x3B4EF41B6D99C9D6ULL, 0xF258F47B4A37F087ULL, 
            0x76EB3EC2DE8B6752ULL, 0xC37B585CE0F362DAULL, 0x04EDDFECF386ED4FULL, 0x4BEBF6B2938E2E8AULL, 
            0xEA69DD71F6851B11ULL, 0x5E2C320E741CEE64ULL, 0x52FAFAFA12C9836DULL, 0x21328C6F525B4623ULL, 
            0x588C88F85AF83C28ULL, 0xAF33754C0C965D5CULL, 0x5071DF11A4929759ULL, 0x52ECF262ACE5D2F2ULL, 
            0x12761BE859F6E0EAULL, 0xFA8CEAFAE40B1DA4ULL, 0x0388AB994E1003A3ULL, 0xF23978849E6AAF34ULL, 
            0x76257A627E49DA28ULL, 0xA648B1A543A5A154ULL, 0x7D267AD242AEC80EULL, 0x308FBEB12CDAC659ULL, 
            0x72FB94FCE78C7BB3ULL, 0x06BED3FED5BB2D46ULL, 0x39A0F67CAAE94485ULL, 0xFC204C49C6B3A0E4ULL, 
            0x6E2093B4643C89CBULL, 0xF37B19AEE8E4FEBEULL, 0xDB64EF77B43BFE4AULL, 0xE2DF4414A26D52D5ULL
        },
        {
            0xCD7F61BCD71A58FEULL, 0xD250F83D282AD292ULL, 0xA7D8D6C4C7ABED0AULL, 0x9FEDABCCF2DB1097ULL, 
            0x5E3A0E23733F91C0ULL, 0xB328B96031CB0A64ULL, 0x33BA5F0988CC3DA1ULL, 0x8F2EC53F05AD4278ULL, 
            0x146B1FF156C4627EULL, 0xF1AB8FF428B69064ULL, 0xAA423D2785C1ACD5ULL, 0xD248F3DC871AD5DAULL, 
            0xE155068609A5D6A4ULL, 0xE2D31B8F26A19407ULL, 0xA815EAADF71B626FULL, 0x73E1F31B033CE53DULL, 
            0x78951AB47031CCDBULL, 0xFB82AB86B8B2DEBBULL, 0xAF3ABE80D9455F7FULL, 0xC9823356B0D790AEULL, 
            0x74EBE9ADC8E0DBCAULL, 0xC71C4DDEFCE722C1ULL, 0xF66EBB72C22812D4ULL, 0x7DB70237BB5AC5ECULL, 
            0xE6B014E30EDD22D0ULL, 0x605FD1C4C19953EDULL, 0xF39159EEA2CA86D0ULL, 0xD95030A61D617B11ULL, 
            0x9E946B260416185DULL, 0x1B26853D3D5D6B81ULL, 0xD938480E5EA5F825ULL, 0x027A62DF0B820F1AULL
        },
        {
            0x67F2206E26C07A4FULL, 0xC36B469745E10CB6ULL, 0x1BA16CDD5C420CA7ULL, 0xEB76D64430A30007ULL, 
            0x0A061C3BED3E953AULL, 0xF56F1116CB84A5EAULL, 0x84A8654DA8C0D97CULL, 0x4E756B3CB98839C0ULL, 
            0xC615A07FDA79C241ULL, 0x36CEE7F8C61D5C48ULL, 0x58A094CB27640EBCULL, 0xAB5B6CC8D69C05ECULL, 
            0x5F9A5676FC2E5651ULL, 0x708F74DCA49B2398ULL, 0x7CEAA54ACCD3BB18ULL, 0xFCA20C4ECC16F423ULL, 
            0x4EA261C9F6E76A18ULL, 0x8FD9512412B2B2ADULL, 0x7EC1BEC852D299B4ULL, 0x08DB5176FC57A419ULL, 
            0x1CD3300377A28E52ULL, 0x4A690BEE2DB62111ULL, 0x25094C383EFEE121ULL, 0xE72C53C66C37F2FDULL, 
            0x1394735DC25420D9ULL, 0x7DBAC1E777AFE573ULL, 0x20EF39F13DE74CBDULL, 0x66CC6DBAD9382678ULL, 
            0xB875989F7263D379ULL, 0x4AAB5FFB31578669ULL, 0x0037CE9B6E003B42ULL, 0xD9190F82AEF2C6F1ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Altair::kPhaseEConstants = {
    0xBE8EEC5F9CC552B3ULL,
    0xFAEF1219A089DA58ULL,
    0x401D8799E7115023ULL,
    0xBE8EEC5F9CC552B3ULL,
    0xFAEF1219A089DA58ULL,
    0x401D8799E7115023ULL,
    0xBF604681D29C867CULL,
    0x8FF57AAD9421AEFCULL,
    0x1C,
    0xEC,
    0x1D,
    0x64,
    0x5A,
    0xF0,
    0x40,
    0x90
};

const TwistDomainSaltSet TwistExpander_Altair::kPhaseFSalts = {
    {
        {
            0x9204D00CE867320AULL, 0x6B398F94E970E216ULL, 0x2E776C133535917BULL, 0x486C96887F0A14F2ULL, 
            0x7688C547863F13AAULL, 0x84E4E162472BDD53ULL, 0xE7F76F071DC4C482ULL, 0x3D1943D7B17618CFULL, 
            0x0FA633A1B141AFA9ULL, 0xCF1B183AF1F2A97AULL, 0x616C9F7500E0325BULL, 0xA3E3E37CD3185653ULL, 
            0xEEAC7017299915D8ULL, 0x82C9164B04649E36ULL, 0xB05EC1938AEC8EFFULL, 0x4E82A2B7822137EDULL, 
            0xDEB2ECA060045021ULL, 0xEBCD8D85B76143CDULL, 0xD329D19BB987C211ULL, 0xCF8C162CB001A2FFULL, 
            0x471CEA5A9AFDE008ULL, 0x076104D366D1270EULL, 0xABAA36982CAE997CULL, 0xD409463A08E51161ULL, 
            0x244B81196A25193FULL, 0x6012CE934D0F6483ULL, 0x3D25670AB1675353ULL, 0xCFC000F8D25C1B7FULL, 
            0x2A0D5C2209A6CDAAULL, 0xACFA2A6C30BD1C0BULL, 0x082156971D0F733CULL, 0xD2A6C32FD2BDC7CDULL
        },
        {
            0x6745189ABC037116ULL, 0xBB9F62661D441072ULL, 0x3DB759660D55AD72ULL, 0x1E174C6984CCE0A2ULL, 
            0xA811D607BFB1A626ULL, 0xC02CCF80F5338B38ULL, 0xBD837C984F75BDE5ULL, 0x24A04A0AA6003A8DULL, 
            0xF5E54C4F62EA0411ULL, 0x4C80CC4A22554A1EULL, 0x7867715DC4AFEE22ULL, 0x3D350AD0B4074D22ULL, 
            0x3FB587E76D44C0D7ULL, 0x1FA04639E2BDA8A4ULL, 0x698DCA2582B35FC6ULL, 0x1E6ECD405B58723CULL, 
            0x0698468ECE84D749ULL, 0x00DFD42B2FA9CD6EULL, 0x1A935B437F33E90DULL, 0x61CACAA209490DAAULL, 
            0xEA4368B7F41D4DC8ULL, 0xFACB9FF3C960D756ULL, 0x5FE4A1CE206F4BC0ULL, 0xF00F52E20A62C1ABULL, 
            0x8E3393E8C08838B2ULL, 0x2332278BC453B56EULL, 0x63EC0131B7A34D9FULL, 0xA564488200C55E93ULL, 
            0xD4E397798AADE88BULL, 0xA7670D224F4D33CEULL, 0xFB1BF55A258315FFULL, 0xAEE5BF6849380888ULL
        },
        {
            0x126596C84D844BABULL, 0xF576F2294C416420ULL, 0x63A091FA89D81CE4ULL, 0xFDD2A2B9F1713300ULL, 
            0x6B13655BEC495460ULL, 0x3DF4739FC632CA2EULL, 0x742D92C1EE5409B3ULL, 0xF71256F8B8F125EDULL, 
            0x6F30BF1F01FE70EFULL, 0x42FD79F9FF34E30DULL, 0x92F97D305D32EEAFULL, 0x66D6643822C87136ULL, 
            0x35B7EF5B81E04F1EULL, 0x5F45636F4A9D8EEBULL, 0x47AF5E561A4A586AULL, 0xE9CB4A548C355A19ULL, 
            0xF0DDAF69A6945BECULL, 0xD447C0DA079DDC73ULL, 0x281561C75A0E5087ULL, 0xBC8444D979D8373CULL, 
            0xB8C8D42FE033D017ULL, 0xCE1C422EC3831FC6ULL, 0x40D9C945A34A54D1ULL, 0x03C1509440440584ULL, 
            0x70769C5D3CF15092ULL, 0x5D18D07BAF82A9DDULL, 0x6C1F647C747B6DACULL, 0x844A15BFBA0EC509ULL, 
            0x35FA068EFEF601E7ULL, 0x3372D3D97E92B3D4ULL, 0x90FBE4B3E88E4E54ULL, 0x8305A61D98F9C7B0ULL
        },
        {
            0x47F64C71CA61C67CULL, 0x9E190289827A8A34ULL, 0x26443E4A2EEA81B1ULL, 0x6EAA3EE0C8E17678ULL, 
            0x7263602D902A0FA3ULL, 0xCB9D0FD455FD90CAULL, 0x7B8CF6380DE0D2B9ULL, 0x963D2D59F61471F8ULL, 
            0x6F2101BC2754FD92ULL, 0x8A46B51E470B8348ULL, 0xA72BF5E485F4AFF9ULL, 0x4C207B1FD8A91EBBULL, 
            0xA249ACED71776C83ULL, 0x58F3740748E6C501ULL, 0xF03455E9B6F20001ULL, 0x7706F26A5F255B13ULL, 
            0x70F44E036A1B7D81ULL, 0x0FEE62E9C7393E23ULL, 0xEE7E7CD18584D671ULL, 0x99CE98903D6FE204ULL, 
            0x3D0F5EE192065A50ULL, 0xC0D8703D3D7C2264ULL, 0x76B9E5571B56FCFDULL, 0x489534075ECF6C22ULL, 
            0x219484443750D3C6ULL, 0xEA4A4D9469A47386ULL, 0x24148336EF08F993ULL, 0xFCD12FDC6645F790ULL, 
            0x87CBD0D3B611D9C3ULL, 0x79EFECE5E5A173ACULL, 0xB3C94DC092411379ULL, 0x476BDC6D2C3437A2ULL
        },
        {
            0x923945D603994179ULL, 0x44A72D7BC6C8BE50ULL, 0x34DBC5C92838DBF1ULL, 0x47ADD59349757A34ULL, 
            0x9CDA536D93A542DDULL, 0x6934451A4D00E99BULL, 0x30E26BB95988D868ULL, 0xE26C94BD796BA719ULL, 
            0x7036DF7BF446FD44ULL, 0xC56202B2F5127915ULL, 0x38C725A9766EFDBCULL, 0x04549EA513767F35ULL, 
            0x8C55BB0817143A78ULL, 0xD004BCF48D00AAC5ULL, 0x4103713FFB6A98C6ULL, 0x37477784E823F6BEULL, 
            0x0BE49CFBC7F996E9ULL, 0xAF9BEC883E82BEFAULL, 0xF9594517E11CD99BULL, 0x5ED78CC76DF585D7ULL, 
            0x68B0CCD20EBA344AULL, 0xFEDC08B325CC7AF7ULL, 0xE7328C2C0058FE55ULL, 0x4AAB6494C4D49765ULL, 
            0xC8FACA12B3EF5696ULL, 0xE946B3BB1CA5B96AULL, 0xD6F58DFE05C646A0ULL, 0x4D2A2A5A88B90F40ULL, 
            0x0756909022B4AB55ULL, 0xED1A5A212F3F6D63ULL, 0x6982465109BB59FBULL, 0x8D7904107DCCA1ACULL
        },
        {
            0x1232119EE7C29A7BULL, 0x8504ED05B07418ECULL, 0x020FAFB66A9D581CULL, 0xA3CF174FCB2BDA15ULL, 
            0x87B508D585B4336BULL, 0x9A9B265C1D5241AFULL, 0x496295A386C867EAULL, 0xEC60C65C4C69BAFDULL, 
            0x2B2377128294A7E0ULL, 0xDAD324486978884BULL, 0x47F302AE1B6E86EFULL, 0xD2391D901B9E1BD9ULL, 
            0xF1F9858A2D2C5E89ULL, 0x23A6766BB41DFEEFULL, 0x762D54ED9EA4FD0FULL, 0xCE57EA187E11D66FULL, 
            0x455C63B417EEC960ULL, 0x2F26DC40D1BE385BULL, 0x9467B72DB6AC1405ULL, 0x877CF0EA868B55FFULL, 
            0xE15E339B972CF1BCULL, 0x500FD6D05177641BULL, 0x766D36231400F4F9ULL, 0x9FDF17B294BAB807ULL, 
            0x7DAB65C8C0DBD29DULL, 0xCD3D1E6E5AFFFEA3ULL, 0x9D42EE8CD4DD0B80ULL, 0x12608A50A577CC62ULL, 
            0x3F39A6BA25399693ULL, 0x74A0E9E7203882EBULL, 0x9E498197B7AE934BULL, 0x4420C1623B9287B2ULL
        }
    },
    {
        {
            0x7D6691C8DE1360D6ULL, 0x7DA66CACC794E927ULL, 0xC6F02344875A78C2ULL, 0x9B92C4CC61EA2BF0ULL, 
            0xD3D5E2B52A78FF99ULL, 0xB0B3381A0DE8D6AFULL, 0xEE670E7E93B29307ULL, 0x62B4D2FA089A6341ULL, 
            0x8D11DFC55AF0E204ULL, 0xAA3E5945DA2ED9EFULL, 0x76AB305E1EA8E0D1ULL, 0xD6594C6204473C76ULL, 
            0x2CFA2B08C97CF54EULL, 0x08BE750F1DC13D01ULL, 0xF31ECAB8F698FB60ULL, 0x26639F08C3211434ULL, 
            0x55DE71F94384AA54ULL, 0xBB55AB1D1A967E59ULL, 0xA8108174D771BB96ULL, 0xC874BB4E7327BC93ULL, 
            0x8E893408C7D65A4AULL, 0xFAFF53FDE4C9045CULL, 0xB6B75F07725FC325ULL, 0xB1EE1C1F044D3CF2ULL, 
            0x79D97541E0DCE9A6ULL, 0x2F64881472A87A96ULL, 0xE5B28346EB78E6ECULL, 0x871371742E5D7B6CULL, 
            0x243AE1D7A0A7673AULL, 0x04BF4EF4D0090DB0ULL, 0x16A482DA8D154790ULL, 0xD2A452CCABC0AA32ULL
        },
        {
            0x0F263AFEFF3B4B24ULL, 0x2FD377042DB67D62ULL, 0x50F9C7F797892479ULL, 0xB5F06090FFCA487EULL, 
            0xA5E5D7944629999CULL, 0xC347129D54B8204AULL, 0xA0DDDF6CB7036EF3ULL, 0x6ADE6EF88B396221ULL, 
            0xE6E3F223DEC9CEB7ULL, 0xEAC1845CDA95E001ULL, 0x9B80E94B73B808AEULL, 0xB867277B0552CD9AULL, 
            0x229E345EC7880C9FULL, 0x1880133E7DC7A1D9ULL, 0xB72C885FFC32D864ULL, 0xC4C1BACE36B601E2ULL, 
            0x4AABBE78F3E5A8F9ULL, 0x820D3E5A6F12E97DULL, 0xACD6496418B6793AULL, 0x3A74A34CEF0329B5ULL, 
            0x76D3F62D2B8B662AULL, 0x673B44F751588FA9ULL, 0x0A152250F3A2457CULL, 0x53E2472F8E92718FULL, 
            0x49520214A83567D9ULL, 0x8B6C00A3314260FDULL, 0x7C792C0366E6F5F0ULL, 0xE2355833579B020BULL, 
            0xCFEF63EDBD2B9EA0ULL, 0x79A07C00A084F252ULL, 0xDAD46136B529A5B4ULL, 0xA3BABDB57C80DCD4ULL
        },
        {
            0x50B3979F046E143FULL, 0x0EA02B121F690F1DULL, 0xA4A9E31B4BDEDF24ULL, 0xCDE9F33F60450E4FULL, 
            0x34BC8EF452AC0E68ULL, 0x0CABBEA036296B66ULL, 0x13D521DA39D0E5EDULL, 0x881C5C70F94CE5E6ULL, 
            0x73C5A3C04C4C90F7ULL, 0x07DB9479B1F9BF1EULL, 0xA211724BFDBDC7FBULL, 0x7E72BA4156237320ULL, 
            0x28DA6E3ADB504C85ULL, 0x9650439F559E3657ULL, 0x9E22D103BFA03943ULL, 0x3C7F431FC157FBD5ULL, 
            0x9F15EFAF1818FD46ULL, 0x99CDB754133E6691ULL, 0xD39EAABDDFB8F06CULL, 0xDE830467E922BABCULL, 
            0xD87497F3F7923B28ULL, 0xFA1F1CC295BE3F02ULL, 0x0B4B9A61208A9D84ULL, 0x9464AD37BDC56129ULL, 
            0xDDD99F0511F6C387ULL, 0xBF0E047E1305FBB8ULL, 0xD7ACD8418D110930ULL, 0x00F1A25A8E936DDEULL, 
            0x7A7E7FAF9CB3D2C9ULL, 0x8DE896E6A01C936BULL, 0x10A15FCE0828A916ULL, 0x1FFC5A125642C72BULL
        },
        {
            0xE83D73C7A08BD99AULL, 0xF96C3B569063E96AULL, 0xB9B35C607A3C5891ULL, 0x313D7AAB08CB092AULL, 
            0xCCB4F70666D63D9CULL, 0xD26D7B86BF839A9AULL, 0x905F1204579D7FFFULL, 0x3E6FF5F40222778AULL, 
            0x84C126C46A4A8E8CULL, 0xA91D73BCA473F850ULL, 0x7FB7A4F710C759CFULL, 0xDCD8C812BF821270ULL, 
            0xAAC501351773FA01ULL, 0x1FE28D981F15A90EULL, 0xF96ABAFB28A76B24ULL, 0xBE1378E73380C3F2ULL, 
            0x4670C99D96690A4CULL, 0x6B8C3FD5CA97DB17ULL, 0x634987E25C29E743ULL, 0xFD3CFB67D51CC160ULL, 
            0xDE7802C82625285FULL, 0xF592D81D24B11F65ULL, 0x769398637A3DDDE1ULL, 0x43371D9B05A0F7F6ULL, 
            0x4EA843C5F6EA17D1ULL, 0x288DFC63A7138FB9ULL, 0x22B8F83EF9EBB208ULL, 0x909FC8BD394C002CULL, 
            0xD84DDB977126137EULL, 0x7099483624EC8EE6ULL, 0x9295888AF7D43460ULL, 0x5B50506F042EBD0FULL
        },
        {
            0x45E938E14239EFE3ULL, 0x895483E657ED3D54ULL, 0xE7A43B647F41BDA0ULL, 0x93BCA98F4F2ADA94ULL, 
            0xF076FDC7BA83C8F1ULL, 0xA896EAF724F38704ULL, 0xE9740ED84BA48422ULL, 0xC2E700F5D52D2943ULL, 
            0x60326865E4371557ULL, 0x36233122FFF19974ULL, 0x528AA5FB22FFFB93ULL, 0xDF2957C04103D67AULL, 
            0x34D277F4D404E643ULL, 0xE0E5F37DF84231AAULL, 0x4EE78DBB076DD69EULL, 0x28A6E4F289AB4F48ULL, 
            0xD6B7ED2CDE73E291ULL, 0xA32BDA4349836BB9ULL, 0x4A90523DA1C41BC0ULL, 0xA858BE7743569AEAULL, 
            0x16B84C3217344CA6ULL, 0xD768A0F65D02146FULL, 0x16ECF6927D09E47CULL, 0xC0E540A518A162EAULL, 
            0xC30EE1042EA2FE90ULL, 0x6CAB1E92A59B94A7ULL, 0xEA8E7A2F73F35E8CULL, 0x947F36034A188F50ULL, 
            0x79C271F5ECC521B4ULL, 0x90EAB2716AFA241EULL, 0xB0C5CBAA1405752AULL, 0x5681B36DA3C0CF5DULL
        },
        {
            0x5CBDE6E400DBCD7FULL, 0xC771DBECF7BDA210ULL, 0x72E4D5ED229E2FA5ULL, 0x793C52407DCDB28BULL, 
            0x17F5F24C4C796FF6ULL, 0xF543E96E8273E53FULL, 0x57AEDE429F0C3A7FULL, 0x8E62EFC4ABEBA839ULL, 
            0x06101A70263DF2A1ULL, 0x461B1BF75407B937ULL, 0xF69B736D3CC27EB1ULL, 0x9B6767A9ACCEAEB0ULL, 
            0x3AC8B07CDB62661DULL, 0x37F3E5BB000DDB7FULL, 0x117063BF7ED36475ULL, 0xF28EBBA31063DD65ULL, 
            0x82070E6B32448AE6ULL, 0xFE4FD42A163EF90DULL, 0x1B4F80B68E464AEEULL, 0x37EB9957E0240E3BULL, 
            0xBE0757A3C8677E6DULL, 0x6CD952F224197834ULL, 0x73A97A8A59AABF9AULL, 0xC479794992D3AE93ULL, 
            0xEEFF9AFEF337B8B8ULL, 0x13F91F316AA8D4DDULL, 0x5A2C3AABEFB3EB06ULL, 0xF9F7B7D65DB1104DULL, 
            0x6C3E714BFA2AB5EEULL, 0x675AC997D16C8C68ULL, 0xFA2A6DC25F633620ULL, 0x537E6D51172E87D3ULL
        }
    },
    {
        {
            0xBF9D02456A7AEAFBULL, 0x0539FECC6774C27FULL, 0x91EB0480B7D71483ULL, 0x0C6037F3A49C753DULL, 
            0x655E7AEF488CB947ULL, 0xB53EB363AB547F8FULL, 0xDDA7F14916CE2916ULL, 0x8A3791DA4F68334DULL, 
            0x9C4DD27B88090103ULL, 0x6B74CE211B02C63EULL, 0x26F362C1E3873CE9ULL, 0x33B6CCD145C26D5EULL, 
            0x1E054DE714DB39D3ULL, 0xF1FEABCCF249ABA6ULL, 0xA09B997704604800ULL, 0x8EF581F5FBC8DD59ULL, 
            0xE081C48C7203B88FULL, 0xE8C0BC6112A545FDULL, 0xE65DFC24B24A35FCULL, 0x27C3BC7B5869CF07ULL, 
            0xF9945024849A00D5ULL, 0xEFEEE5DC578854BFULL, 0x68268AF4410D4B7EULL, 0x5972860F45F9E734ULL, 
            0x324EAC33B32DCA81ULL, 0x2A4187370BC6832BULL, 0x360928A01AF98B94ULL, 0xA8D61C3655E500D2ULL, 
            0x0D48C9700CE7CB3FULL, 0x265565A9D3B6E3C4ULL, 0xCE6FE8C2B30FDC50ULL, 0x3212F96EFE7A2AA8ULL
        },
        {
            0x60D021E62D8EF719ULL, 0x3C493207D49D0575ULL, 0x50076BD1AD33860DULL, 0xE0EF4C477A19510DULL, 
            0xC769FE9980FB9B23ULL, 0x58EB855EA33736FAULL, 0x6DE708342D4CD91FULL, 0xC9EDFB066399B400ULL, 
            0x05581F0311FEA1F2ULL, 0xC59B8082B87D92C5ULL, 0x44AED8DE30BF0122ULL, 0x3289A007DC749425ULL, 
            0x5CC08C3753142327ULL, 0x3C335B6D453A02BCULL, 0x3BDE8D3872CC9099ULL, 0x0E935E0867AC8296ULL, 
            0x30D512C1811067C5ULL, 0x0180E6887C8C7620ULL, 0x431E40C8962D6C87ULL, 0x7F8B56848FC691FCULL, 
            0x28A83FE4A572F4C8ULL, 0x8A6FC2F54AC42C78ULL, 0x82010A4CD5011954ULL, 0xEBAAA7B21F404FFFULL, 
            0xB6AADB7D0BABE582ULL, 0x06CE1857163662E7ULL, 0xAC7A35D36C5A9EB4ULL, 0xF8370C33F6079705ULL, 
            0xBACEFACD91C4D3A8ULL, 0x5147456F659590BCULL, 0x507C92039D1F0E84ULL, 0xD8ADF51C647D1CB2ULL
        },
        {
            0x128D728507BA5DE5ULL, 0x98D3FBFD680DFFF6ULL, 0x2CE5851F0746D35CULL, 0x68CABC50E188B871ULL, 
            0x23F0EC3510A94809ULL, 0x734F1F793279C5F7ULL, 0x528D5A0E7E932392ULL, 0x10FBB7C9CAE0BDFFULL, 
            0x3245AB8B09534833ULL, 0x0A72D0630A49EA5DULL, 0xB64CFCA83263EF1EULL, 0x4796A23C70CB95D8ULL, 
            0xC41C21ABCFF2946FULL, 0xB7DAC602D2B36BDAULL, 0x53B8072E28CF78F4ULL, 0x0B5B4FB2496E1658ULL, 
            0xDC63CDE7E13AAE52ULL, 0xC7F6D9CD4E4BA3CDULL, 0x4972BFA060F9A129ULL, 0x5EE05574E9B3D08FULL, 
            0xE7CD750ECEC01FFDULL, 0xF6BF061C4BD7644EULL, 0xE6C0AE2CBA15EDE3ULL, 0xE50C517B2D1D564BULL, 
            0xBF7CDD612CFBC6D9ULL, 0x9EAA1FDB1F2B3064ULL, 0xD3884473677FD733ULL, 0x93A2E3C1F4D10036ULL, 
            0x6FABF28CB20BEB5EULL, 0x78470ABA4CA56F7DULL, 0x9C1CF8458E8E0FD1ULL, 0x16D7792E5822C900ULL
        },
        {
            0xD520C4FCB9AA2D77ULL, 0x17748AE1A97A2490ULL, 0x23B3225FC103A827ULL, 0x608CB9D9F82028E6ULL, 
            0xD945AA31336C90A4ULL, 0x33387D8E58B7B5ECULL, 0x65B9A1D1EF842B7EULL, 0x03F7C6B361C5657EULL, 
            0xE25034FC5996E2D3ULL, 0x8A1AEAC839F07B2BULL, 0x294F5D0B352580C3ULL, 0xE2C54E3CB3CDB729ULL, 
            0xB6E63FB2DCE5B513ULL, 0xE910A4F04B313B4FULL, 0x203BBD0B906EC2C7ULL, 0x24133174C7BE146AULL, 
            0xDF037E5BF63507E6ULL, 0x61D880AC38EFCC48ULL, 0x9AFE76BD73AE5048ULL, 0xF0DF611AA9B6ED97ULL, 
            0x3309A8B5F4875501ULL, 0xE32DF97519C9E9A4ULL, 0x9A4E6378FA9685E2ULL, 0x1AFFA7856715D883ULL, 
            0xA6AA921B3B4024FCULL, 0x33982C390FE256B9ULL, 0x2FEB2DE8F3D4740DULL, 0x18D318097EBF643FULL, 
            0x1C4D945108B9EA81ULL, 0x69BAC0102FE4B306ULL, 0x1AF5C041CFB14E4DULL, 0x2839A0959B9C92DEULL
        },
        {
            0x767191AA4C3FC313ULL, 0xBBDC65F0F23450B4ULL, 0x336ED1CBB9097E0EULL, 0xDD42E681261D24E3ULL, 
            0x3406DF2647A05D2DULL, 0xA46835FFBB317849ULL, 0x7D3899951F5DBFF7ULL, 0xA00242978DF9D557ULL, 
            0x904C950C13041368ULL, 0x5031E50EAACC7392ULL, 0x55655DBCA66D9E06ULL, 0xD39D5E96E9348B60ULL, 
            0xD2138971253F72A7ULL, 0xF87CE74CC7228312ULL, 0x1AB9DC0D20190FB4ULL, 0xF3595AB7CF6709D2ULL, 
            0x3918426EAD0B1046ULL, 0xAF0EBB15E2C98052ULL, 0xAC90A75CCE6F9917ULL, 0x8FBD46E61FA5844CULL, 
            0xEE34B391867D13BEULL, 0x9E87A9A0C007C512ULL, 0x658405FD2DA9DDFCULL, 0xFF9DE7D2BA417807ULL, 
            0xC99C4DD9F54809D9ULL, 0xFAB46CBA125F249BULL, 0x617FE5E1C293FFAEULL, 0xD943B9741FF95173ULL, 
            0x1D6682A4C38DD461ULL, 0xEBF2D700898B8D3FULL, 0xFF6407D4E77FE718ULL, 0xBC45457A73E994DFULL
        },
        {
            0x376BFC7DB7A15E2FULL, 0xE1EFA7294E2B3FBEULL, 0xEB44B74AEED2A0B5ULL, 0xC2D20E9681F22299ULL, 
            0xC9C64CF103897B5FULL, 0x550144DEEFC2BF7AULL, 0xB0C429895C522331ULL, 0x6751882D46B17849ULL, 
            0xEB78DAD71CE67BB3ULL, 0xA27AB2990A28ADD9ULL, 0x5864D5026CB6BC4AULL, 0xE814C29806662D40ULL, 
            0x457AD8653C56D8D6ULL, 0xB24689AAC470161FULL, 0x8B0604A2DD1A79CEULL, 0x3EA224B1B27102EAULL, 
            0x607E69BB23821A40ULL, 0xEA075057C97E0AAFULL, 0x0C5B78FEF1A9D8D0ULL, 0x6093FFED3997236DULL, 
            0xAFC70F648633D834ULL, 0xA7EA477875CD17B7ULL, 0xEFECAD945A38D768ULL, 0x1C50D26118D0F128ULL, 
            0x775A1436CBF0631EULL, 0x5702734BA7E0A366ULL, 0x9D26875EAF5CC700ULL, 0x9F0EE7E87CE18576ULL, 
            0x2546E367D0BBBAE9ULL, 0xECB188E570D17350ULL, 0x44383B7C8DD6508DULL, 0x823D0F3E758414FBULL
        }
    }
};

const TwistDomainConstants TwistExpander_Altair::kPhaseFConstants = {
    0x1641C0A334F74821ULL,
    0x7148D180B84364E5ULL,
    0x96D91CDAE34E9926ULL,
    0x1641C0A334F74821ULL,
    0x7148D180B84364E5ULL,
    0x96D91CDAE34E9926ULL,
    0xC45E0F69724D6141ULL,
    0xE7DC53FAA52A43D1ULL,
    0xE1,
    0x26,
    0x43,
    0x8B,
    0xBF,
    0x64,
    0xA9,
    0x88
};

const TwistDomainSaltSet TwistExpander_Altair::kPhaseGSalts = {
    {
        {
            0xD9E10D100D425FB4ULL, 0xA02B98762BBC8E01ULL, 0xAF327383E9AEE626ULL, 0xD249EEDD930F7D32ULL, 
            0xBE7885A4AD7E7A71ULL, 0x5F453036EB6D5780ULL, 0xB2E6FFE23A73CDD2ULL, 0x37ABFE23EDAB66C9ULL, 
            0x22EF4ED698999377ULL, 0x838EEDA958F94623ULL, 0xB43F1B7E9E6897FFULL, 0xFD0BE2B1324BD07EULL, 
            0x23FC8CAC6732FDADULL, 0xD598167A3D61367BULL, 0xF143CDD9FB0A579BULL, 0x7F727302F0CA1109ULL, 
            0x8518E106E55D0A2CULL, 0x8B1465FEE6A4EA78ULL, 0x7719D8534B64FB72ULL, 0x47FBE64837E698A8ULL, 
            0x208463D6597571EFULL, 0x40085B620AE5B5A3ULL, 0xAD6A19A77EDEAD1CULL, 0x0D58E8ADBA3E8814ULL, 
            0x43CEE1CA19036653ULL, 0x437928DE948C0861ULL, 0xA467880D850CB155ULL, 0x0B3882461F4727DFULL, 
            0x133140E8B6873180ULL, 0x0841877CFB4CEA9FULL, 0xDBC64ED1EE097233ULL, 0x80FE6B3A5FAF246BULL
        },
        {
            0x6BDF8963F1CF1ADFULL, 0x4F7FF3FBE8AABF71ULL, 0xC613B23FAFF294B2ULL, 0xE8DCC11D70504606ULL, 
            0x935FBF02986AD327ULL, 0x918BC2FA3151F4B2ULL, 0xA8A2DAD4E36C20BBULL, 0xE07B60E5B95733C0ULL, 
            0xD42EB8BB6F6A4750ULL, 0xBE9BC707B67B17E8ULL, 0x7988D7202113A0EAULL, 0x4FAE98B35BCD4C34ULL, 
            0xBBEB317388AE6B73ULL, 0x63060538482D34B8ULL, 0x4E6DEC8BC5BA7CB4ULL, 0xF04EB43382EDE537ULL, 
            0xC70693A61A23CD9CULL, 0x68A1D49B31F8DA4EULL, 0xF6DB6EA7EE5F3898ULL, 0xB0A6FABB01C771B8ULL, 
            0xC6262BB594E3430BULL, 0x5FF4F43AAEA6E95BULL, 0xC007832E21A616EEULL, 0xE2E849DB3A249AAFULL, 
            0x70F5879F5CFAE7FAULL, 0x484208B55209157DULL, 0x44872687DF1D1314ULL, 0x02C698397561AE63ULL, 
            0xB679548A44E4CFBCULL, 0x40FC5573E1AD4747ULL, 0x610DDB1DC5D2563BULL, 0x238D611BC8D3E98FULL
        },
        {
            0x89A59F323A0EF302ULL, 0x9D9E0C6942F74AE1ULL, 0x3EAECEDF7DF7AE73ULL, 0x0B981E653EBC1E27ULL, 
            0x5E1AD1D8C0DA62FAULL, 0x402949AB9E9F8723ULL, 0x64C4BEB60CFF407CULL, 0xE786B9F14AFBE050ULL, 
            0x361CE4AB3B5772D1ULL, 0x9CF0B0CEFCEE6AE3ULL, 0xE34692BAC708E907ULL, 0xFB1A0C67B3259304ULL, 
            0x42E387CB8294AE62ULL, 0xD4502975F58DB5B7ULL, 0x20DB3790EDE87281ULL, 0xF911650D40C6A245ULL, 
            0xC9944E6E509C6D0EULL, 0x096EBD3E6F0BED0BULL, 0x80A55ECC0B4F2604ULL, 0x73AE9C8960B8F57BULL, 
            0x16F028A6A49DA024ULL, 0xF62F62B891863E92ULL, 0x6D484550BF68D5F2ULL, 0xFEEECCF319C3ACE0ULL, 
            0x75AEF8D1DDC8050CULL, 0xA79AEB88BDB8E168ULL, 0x83C28C1A9DFEFE90ULL, 0x4CC01CBF964BB94BULL, 
            0x9D2E4B709CF42383ULL, 0xC58F6BB4105C220DULL, 0x2515028E49903E56ULL, 0x7BC567F6F0E00EF3ULL
        },
        {
            0xECAE50F27979D56BULL, 0x739AD5C6F7D097DBULL, 0xD5CC4811BF94DFA1ULL, 0x4D0B5D9A0ADE72C6ULL, 
            0x185A9622F44D8EE7ULL, 0x1FAC1D2557AD258CULL, 0xF56C1295F3859EEBULL, 0xBD3C0B6F395A8996ULL, 
            0x7B6153133346441FULL, 0xEC12A429841B47F4ULL, 0xEDCAB6A447400EE9ULL, 0x2F11F9FF57A155BDULL, 
            0x8D28703D2B027C23ULL, 0x61F03D1860880A5DULL, 0x5BDDD38186F22659ULL, 0x2DD78619C0C52289ULL, 
            0xA4F80316CD521BA5ULL, 0x69CBD14AB12F664BULL, 0x718ADCFF9D542EBCULL, 0xCD51573F4EC29CDAULL, 
            0xDFEDF9039AC526C9ULL, 0xBEFDF3AEF945A3A2ULL, 0xB88E93FEEA850863ULL, 0xBBA97FD3B8D7AE03ULL, 
            0x85597DEE3E58DCEEULL, 0x52E8E03ED766BDA2ULL, 0xA34443973EEB2770ULL, 0x14E7C5E0E5225047ULL, 
            0x4CD631430C2FB6FAULL, 0x50557D2ABE4E2ADDULL, 0x01E281961CBAD25EULL, 0x700E573EB55A2362ULL
        },
        {
            0xFF9550D9F935BDF5ULL, 0x4A74BC8E3D572CA6ULL, 0x641106172A0911E5ULL, 0xD5E81CB56F49B2A1ULL, 
            0xB96EFA9B0222661BULL, 0x526C7959E6E86A7FULL, 0x3FAD8582EE0BFD77ULL, 0xFA018D27E5FDE995ULL, 
            0xF98CC1D53A126C85ULL, 0xE02CD617F1078E42ULL, 0x77F26521653A9827ULL, 0x41093A835D8FA204ULL, 
            0xF35DAA7AA742A87FULL, 0xA499109B321EF9ADULL, 0x226504AB46862747ULL, 0xE0125CAA7A904CA3ULL, 
            0x820F7019852B3612ULL, 0x199F575DB823B7C6ULL, 0x12D8784E57DFCB45ULL, 0xDE4CE2298BDE5A4FULL, 
            0xABAD5B684E5D8D33ULL, 0x19C39736D13F907BULL, 0x0B6576A763E29942ULL, 0x04E2E0152F75BF08ULL, 
            0xD883A167B4D7977FULL, 0xD974BE141CFC8E3DULL, 0x9AFA367A11E83D77ULL, 0xFCB41D9A052B0E2BULL, 
            0x56E6332E96F44BE9ULL, 0x11427C8F64C10782ULL, 0x8816B1EB81883C18ULL, 0x2878D2AA3E492FCEULL
        },
        {
            0x3114D9C766B0DEBDULL, 0x43965C3E939124F8ULL, 0x21DD59D06A761805ULL, 0x992FD1DFB7CD67C0ULL, 
            0x36278949FBDAF941ULL, 0x9F21EF2B66307EA6ULL, 0x83F2FE5EE5DAE589ULL, 0x6C0E4A87DCCB9854ULL, 
            0x16ED761191DF1694ULL, 0xEAAEE9F40782AAD9ULL, 0x268A8B678AE250F7ULL, 0x76A8271F25D4FAE1ULL, 
            0x6B15C30616564DA7ULL, 0xCF7BD0A4C9985CD1ULL, 0x4BD38F267D290DE3ULL, 0x5FF4A67EE15D1BE5ULL, 
            0xD1EEF582A4565721ULL, 0x7A5FB4CFF0F88C9DULL, 0x85D7DC2F313AEC57ULL, 0x231E2E2899B24066ULL, 
            0x7A666D5407AD541AULL, 0xDEDF3E9390FCF31FULL, 0x67A6BA4300F08360ULL, 0xE8AA30D7C45BB445ULL, 
            0x5CCBF5BF2D98E260ULL, 0xFDC24619B0314035ULL, 0xA093331796C5C9D8ULL, 0x4003FB20757F050CULL, 
            0x035381FAB891C0E6ULL, 0x5A46AF66B59E8C15ULL, 0xACED5EC09D174049ULL, 0x56E10CAB5B7C7F80ULL
        }
    },
    {
        {
            0x922F003B257CECF7ULL, 0xEC11E8BB59EE670CULL, 0x2D1AF792C3C7480AULL, 0x4CC84EFCBD28692AULL, 
            0x54AF233E932E1E58ULL, 0xB6704FC26CE911ADULL, 0x6F84A131CF5D00E0ULL, 0xE456F824CF6FF57EULL, 
            0x5F44526F18EB9997ULL, 0xDACE59D43F23C467ULL, 0xABE9827F31A1C8A0ULL, 0xDB8C495F05E86559ULL, 
            0xDADBC7B93A2B905FULL, 0xD432E77E0BAF5B8BULL, 0xAC557F88E1215918ULL, 0xC20C08F340C4DB1CULL, 
            0xBB595AE7CA1303F9ULL, 0xEF795041BDCCE34DULL, 0x11684838131D73FEULL, 0x197ADA6C6CD93D3BULL, 
            0x1C0F479647872F86ULL, 0x799E818614C40540ULL, 0xB060D8896B8A0EA0ULL, 0x91AB4ABE5490A5EAULL, 
            0x9C59FC0FDB276526ULL, 0xDB4BCAB7CF416538ULL, 0xBBDF3FAD9FEDD5D3ULL, 0x471EAAD29619D36EULL, 
            0x032B84A2C478297EULL, 0xC40128F0E9279164ULL, 0x232AD3845C7ED071ULL, 0xB9A4D6B692C191D1ULL
        },
        {
            0x2E74CECA482D34DEULL, 0xD4699F068ADC4679ULL, 0x3F7BDEAAEC0C7C44ULL, 0xCF8F556596060DC9ULL, 
            0xBCA85E98EEA3F836ULL, 0xD5E56BBF910B0F32ULL, 0xA0B2B93916CBCD20ULL, 0x66EB548390AEC573ULL, 
            0x2372537537EC3D5BULL, 0xDB4A97FD506E07BAULL, 0xC885D32835495499ULL, 0xC2F46BE76EFF707BULL, 
            0xEAC2914F8DF9D19CULL, 0x5BDAF992DABBDE20ULL, 0x65052F9048F7E393ULL, 0x51A2DBBE5FB629D9ULL, 
            0x6E26AFAAC54BE812ULL, 0xDE8A6F2AF082807CULL, 0x89A0C8E570009BCAULL, 0xDD76BC0C21C01AB4ULL, 
            0x3AFEA9CAEBE5E1D2ULL, 0xAC1A1EC937B23F96ULL, 0x9996B269E0988D50ULL, 0xB01CF3AAFB9584A9ULL, 
            0x7374F114CAA368A0ULL, 0x2DD646FCCB0F494DULL, 0xEA4C2A30D544D335ULL, 0x37500F8649FA2DDBULL, 
            0xAF5B5AABC1816709ULL, 0x3985758DCA47A901ULL, 0xBD629BD598FDEC71ULL, 0x7B76F00750CD0F7DULL
        },
        {
            0x80FA536D5985C4A7ULL, 0xE27C54EC41E614B3ULL, 0xFB2F4670CAA7B502ULL, 0x9FD162D6ED1EE02AULL, 
            0x640DEFFC6DD8D96FULL, 0x67485227A41008C1ULL, 0x10C84FED396EB711ULL, 0x478A81946DBF96DFULL, 
            0x3EBDF04B4908748EULL, 0xF4BA9E2C2A722C87ULL, 0x54F162EEBB5A5CCBULL, 0xAA38D617569304BCULL, 
            0x267C31AA80CBB24AULL, 0xE3B9612CC5165FB2ULL, 0xEFA4EA54896CCBB0ULL, 0xD8D50D81714ED8E3ULL, 
            0x9A48E3EE7EFFDE91ULL, 0x53BE6D1ED346A8E5ULL, 0x28213C24B39C6029ULL, 0x17CD866C3CEE07EDULL, 
            0xB73BDCB09B0D42F3ULL, 0x73DA94A19E2E5FD5ULL, 0x0DF6E98CA18AB7FEULL, 0x96C50DCDD049E1A2ULL, 
            0xBFAD8D5D00E81B9EULL, 0x384393A2EDDF4D58ULL, 0x736C182A371A81BEULL, 0x732BF2CA7857DE39ULL, 
            0xCDBB1ADF5C0CCA83ULL, 0x30373C102956F7D5ULL, 0x2B05AF7C917FC0B5ULL, 0x065BAEF3A34AB12EULL
        },
        {
            0x25D04C0B9A54652CULL, 0xD931B74A4AC68E98ULL, 0xAFAD3800B8D4CA73ULL, 0xF80E60B723B98CFCULL, 
            0xBE9DA93E54EC5E5FULL, 0x8983F676552AE528ULL, 0x2D599E84830997A1ULL, 0x3B841C63F601FE65ULL, 
            0xDF63E79BC9EEC229ULL, 0x880086A12950B49FULL, 0x77533C86D5AB5806ULL, 0x1B2670523B165760ULL, 
            0x593AA7BC7B4A76EDULL, 0x0B014924AF703A28ULL, 0xFF30997B4BDBC6A8ULL, 0x3B2776AE9D91B1C4ULL, 
            0x5772E614DB464F09ULL, 0x4C38A8A67EBA3E56ULL, 0x44E8073ADECCDBD2ULL, 0xBE8C3FD4D103BB83ULL, 
            0xFB369E308DF90474ULL, 0xCAD95212A655AAE4ULL, 0xF367D159B786EE8EULL, 0x4EB03C2FE264AD8FULL, 
            0x522E57D7595FB802ULL, 0x2E3A15A767B4205FULL, 0x534C1855F15A4EB8ULL, 0x78D763F5FABC71F8ULL, 
            0xF5D5384735782FAEULL, 0x1AA8EE8AE95E7352ULL, 0xA4EC35F312A99284ULL, 0xB868058DA2B9AE73ULL
        },
        {
            0xED949B1EDDA40BD3ULL, 0xC94DBCA6AE1B8F9AULL, 0xC8EB08644F6CB284ULL, 0x29E9F27330AA59C6ULL, 
            0x93870852945585FBULL, 0x2CB35F78DA69757CULL, 0x81A3FF36043EF281ULL, 0x407E1D506DA4FFE9ULL, 
            0x11CB79C311552AC3ULL, 0x06B29CDDBF10D93BULL, 0x55FB38291503B880ULL, 0x1C67AC4CC101A97DULL, 
            0xF3927863EE87B3D4ULL, 0xDEFDA2E9241495B1ULL, 0x49CF8B15D259283FULL, 0x99270C44A5288DE7ULL, 
            0x0523CFE8F8DAE8C2ULL, 0x7393D052F40639E6ULL, 0x2D0DEB990EF51820ULL, 0xA91063FA79278CFDULL, 
            0xEE3B0A500790B652ULL, 0x21C2C7299E941673ULL, 0xD28F29A6B4F1BFDAULL, 0x607726CFA5C3CAF7ULL, 
            0xC3CE4D3CC9D776DEULL, 0x90E7705BEFD6ADD3ULL, 0x06958B4428B84C5CULL, 0x4D449A9437C840BCULL, 
            0x1C6B387C9B246736ULL, 0xB69A2C91168BB1DEULL, 0xF40F5BACD4E30AF7ULL, 0x82696C9E3C8F74C9ULL
        },
        {
            0xF3A67509294F945CULL, 0xB57E5F3D2E0F280BULL, 0x89549CB7F169A12EULL, 0x2F432B44F27A62F7ULL, 
            0x12715204E0F0462DULL, 0x8E4EB2468A66578FULL, 0x3B09AF0FCAE9DA23ULL, 0x7398600B588F00F4ULL, 
            0x7B678670332B8C49ULL, 0x15FE65F222E1B088ULL, 0xD77D7A78466915C6ULL, 0xFA364784D7A4F2F6ULL, 
            0xEA95338FE3414BABULL, 0x01E58109BDC3F41CULL, 0xF122D80FDAA052D5ULL, 0x8880D630B34C183FULL, 
            0x26A56CB23C3EED75ULL, 0x7A1ED7E92F20F1C2ULL, 0x6B6A482727CC433FULL, 0x8AC0ACB35214F2BEULL, 
            0x88E0E558D6C8E8AEULL, 0x9FE15E4B7E2664FBULL, 0xCD96699F5FBDF410ULL, 0x5343C32A7A850B43ULL, 
            0xD639C6F128EB3E1BULL, 0x3CB005D52D281147ULL, 0x0D53C127876817C6ULL, 0x60B97FEAEA9923ACULL, 
            0x7D131D51F8C3E724ULL, 0x94D3CE040A9D05CBULL, 0x47B1AF961C5B0DE1ULL, 0x4CE691D7BAE367DAULL
        }
    },
    {
        {
            0xE82FFEBDBBB36350ULL, 0x0A363F2F3EE39DCBULL, 0xB6EE31EF7BCE3DDDULL, 0x0ED27F5AE0AEF80AULL, 
            0x1901BCCFC1900E34ULL, 0x023D7BCF2AF41D1EULL, 0xAA138F6D0CF7B5A3ULL, 0x2FCB0B5EE6FF25AEULL, 
            0x0EC8515D451456F3ULL, 0x0D53AAED974CF366ULL, 0x9F11C4D6E84DBD2EULL, 0xDDC589C3340F079EULL, 
            0xD31FD2519AE5543BULL, 0x7867579F5FB2CF01ULL, 0x081345BA1F831481ULL, 0x939BBDD4287BC1F9ULL, 
            0x22852D9CEBD5CE85ULL, 0x83FB075B596D4DBCULL, 0x03363648B11CE25AULL, 0x90097DC0374274F4ULL, 
            0x9E67DFA32FA75991ULL, 0x465BA81596C1371DULL, 0x197F4EE0CF0710C2ULL, 0x2A90D2751FB53109ULL, 
            0x1934B3924E197BB5ULL, 0xDE7622D6707F4E99ULL, 0x46BD40D769BD1683ULL, 0xA5B4D8A886EF74BCULL, 
            0x499C6155166A326CULL, 0xB683C005ECA0B60BULL, 0x2D686174247D5CB3ULL, 0x3CA121F7D056C8EFULL
        },
        {
            0x6856C66452125536ULL, 0xE627F8D8825695B4ULL, 0x3F3E94F3654129D0ULL, 0xF549C5EAB422F7ACULL, 
            0xE8F25922C04B07EBULL, 0x2EEE6C88410F8D27ULL, 0xFDA2C245EC140327ULL, 0x756D8C8AD4F550FDULL, 
            0x80293CB50C17FB3DULL, 0x37EBC0A0832310C7ULL, 0x89533509674D01E5ULL, 0xA841E28214EB42C0ULL, 
            0x0D29A156FC160B07ULL, 0xE6D048128B968D91ULL, 0x3FF906CB3F4541ACULL, 0xD14A748E1E7CE3F2ULL, 
            0x2E6F2FB0BEA4E948ULL, 0x04956FA8739BBE18ULL, 0x216C1A2058436EF8ULL, 0x162F7CBE684EE0B5ULL, 
            0x4D3F74C39EC95782ULL, 0xCD0C610BEFD5DD38ULL, 0x81BE1CB8A9D69398ULL, 0x386BFBE970F41AC1ULL, 
            0xDD7F3CECBED7634EULL, 0x692597D463AC6140ULL, 0x9238C5AF1E7D8171ULL, 0xA06B9213E44A947EULL, 
            0x6DFB2B0FE48AC76EULL, 0xB71FD634A2860E16ULL, 0x25D2F8C936AA1D86ULL, 0x05CC0700C9491A3EULL
        },
        {
            0x34455178024B8B0DULL, 0x6897A885E5C6B327ULL, 0x93B9ACACDC3CF231ULL, 0x0A62DF57F9494AE3ULL, 
            0x30DE40DA2E4DB87BULL, 0x2E83208FF440D950ULL, 0x53E97D38C6D01C61ULL, 0x3F607AD7DEE6690BULL, 
            0x21D24F5D7525506BULL, 0x7B62CF2805DB9C27ULL, 0xE37C9C0835BF1DF2ULL, 0xC7D4A3D026F465D1ULL, 
            0x52985FAA4AE16AE7ULL, 0xDE36D03F56E36BAEULL, 0xB9FA7C9675A9F50EULL, 0x6E675D4D24481B27ULL, 
            0x6567BB3137347711ULL, 0xF95D2C601B2CAF42ULL, 0xAE64C15C8E7C86DEULL, 0x971DA450CE5489BEULL, 
            0x63BC822886BE03DAULL, 0x2B47A0FB7984ABA4ULL, 0xD6D76C1D2C44D98BULL, 0x413AC7A5E6E54823ULL, 
            0x49409269CD26574AULL, 0x853E825BC659FD51ULL, 0xF5A80001B79AE02FULL, 0xB2B1E6D0DA79544CULL, 
            0x9F07EECFDF1F1571ULL, 0x29680DE812E5F013ULL, 0x1E711B6EF4752724ULL, 0x6175030B9979B80EULL
        },
        {
            0x9A13DC6A88FC4545ULL, 0x15807DB25D11531BULL, 0x9D9BA288FFF9C64FULL, 0x1AA41D983CCD7077ULL, 
            0xF10D5A3501A32B62ULL, 0x769CC2FC049A2C27ULL, 0x87CA786E815DD0F1ULL, 0x5A4E5ECA34B68C6BULL, 
            0x2EA0FE5074BA8EF8ULL, 0x33B9737C51069892ULL, 0xD04DF1C8B053C802ULL, 0x3A258A7B086061FEULL, 
            0xAC76F7BA23CE0BC6ULL, 0x0D77F552AF3BEFDDULL, 0xC0A1CAB6FB6B8441ULL, 0x46C11C77AEF1006EULL, 
            0x9B960CC2F616C48FULL, 0x13E5F8418D75D68FULL, 0x623F40F747700321ULL, 0xC9D113891DDA9434ULL, 
            0x301CA5AB1B54C402ULL, 0x02F1AD699915D568ULL, 0x35C1184B260AB42AULL, 0x919E0E72D335CC3DULL, 
            0xB03DF96F0EDFB4C9ULL, 0x9C17C55D2DF0ACAAULL, 0xAF5EF6B436D65294ULL, 0x5F857B6EC3E8ACFDULL, 
            0x1EA6BDAD2B5D483FULL, 0xFA1A72351748BCDBULL, 0x8A86A44A85A48438ULL, 0xDB54787691DD9C77ULL
        },
        {
            0x3BA0149F7ADEE9D0ULL, 0xA79C0F4AD95D35ABULL, 0xD79B1539F8542610ULL, 0xD5A52F4486662F00ULL, 
            0xFB0277AFC0B38660ULL, 0x3A4296D33CA0CCDAULL, 0xD54D35C8F4026EEEULL, 0x329A19B781BD0C78ULL, 
            0x571F3F98274D97DCULL, 0xAC339D35049AB6E5ULL, 0x56371328D1BFB121ULL, 0x7B6D036C1CB6A7EFULL, 
            0x14EA6B2D4C17840AULL, 0xC7AF6675F6CCC394ULL, 0x9320796089E9457AULL, 0xA426FFB6B7480349ULL, 
            0x804DCD163AD441FAULL, 0x5A2A7DA29CD8A385ULL, 0xCF88F6D0FA49B4E4ULL, 0xACA56ACEF694B699ULL, 
            0x30445E6BA854A72EULL, 0x8B3F67301ACD295CULL, 0xE96BE7C3D2C3B990ULL, 0xC0C9526D503036DFULL, 
            0x3DFCEFA1575EDDFBULL, 0xABB3532484649A9FULL, 0x77592FA4758E9091ULL, 0x0597880BDA8CF50CULL, 
            0xA58A72F403BCDE10ULL, 0x9100765D7C29C88DULL, 0xB2550BF9538C2F09ULL, 0xA616A3E2DC0CE445ULL
        },
        {
            0x7BD7AB86CB71F823ULL, 0xDD7A7F8BDF462C4FULL, 0xEFEBD49B32522A03ULL, 0x314F6184391C01FCULL, 
            0xDC8D30EC5D014ED7ULL, 0xBDFB464E8408492EULL, 0xD2B8B686689F1F18ULL, 0xC0C85000C9003796ULL, 
            0x498D65C8F97E8A7DULL, 0x4287BDB47DBF0364ULL, 0x42216607D3670D83ULL, 0x0DFFAAF68D26BF08ULL, 
            0xE4C26E4223D745FBULL, 0x9502463D3B457B5BULL, 0x05E4512A7FCA2659ULL, 0xDD34680EEF4C6504ULL, 
            0xF9FD8AA9747E6AB2ULL, 0xEF7A5F071C899434ULL, 0xA872122FFE726835ULL, 0x3EA224F8A274A481ULL, 
            0x690DC1E30C44E1AFULL, 0x6E3F617D835D40F1ULL, 0xD88BCDE7EE5521AFULL, 0x19035F79DD083AE2ULL, 
            0x6C5FD790F4CC5825ULL, 0x6DFF7E25D1057D41ULL, 0x92EC56EAED2FC298ULL, 0x850DF6739FD8F643ULL, 
            0xD1BC15B3888242E8ULL, 0xB64AF309AFB8498FULL, 0x129EB4F82CBEC48CULL, 0xC634948A07834339ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Altair::kPhaseGConstants = {
    0xCC617A9790127E85ULL,
    0xA71A8F01A086D337ULL,
    0x3818505E5FE30CBEULL,
    0xCC617A9790127E85ULL,
    0xA71A8F01A086D337ULL,
    0x3818505E5FE30CBEULL,
    0xDA8D63BF2A6419A1ULL,
    0xEEC43238E0B46D8AULL,
    0xD2,
    0xFE,
    0x65,
    0x59,
    0xE7,
    0x1F,
    0x26,
    0x5B
};

const TwistDomainSaltSet TwistExpander_Altair::kPhaseHSalts = {
    {
        {
            0x261EAAC994D94552ULL, 0x35BF2AEC264CDF15ULL, 0x13770C907EC3ED72ULL, 0x86B960A6BDB02D8AULL, 
            0x402CC21D6BF8B777ULL, 0xC628F5E92A619078ULL, 0x28BBF15B31D2FCAAULL, 0xD03AEA0D38A5D777ULL, 
            0x92BD5DBEFC9E5B98ULL, 0xD51938A68F92A30BULL, 0xF664A8BAA8C4A56FULL, 0x27A8CEEBC4574DA9ULL, 
            0x6906F633436E0D3AULL, 0xA34C949BAD4ECFB7ULL, 0xBBF69B94237B47F1ULL, 0x5CC03FC7D0127337ULL, 
            0x898AEDD82EDA13A5ULL, 0xC77DFA122AEE143FULL, 0x5055EBAD48F8F1CAULL, 0xF8DA657B15285DFBULL, 
            0xAE8AA05C1E3A65C1ULL, 0x0815E73803EDD666ULL, 0x36D1B94A385DE02FULL, 0x962055D8859ADCDFULL, 
            0x0EE262C81D5C38B4ULL, 0xDEDEE21202BD9C6FULL, 0x2F836AD02D684B17ULL, 0x0815935665241DFFULL, 
            0x4C9C11C217D332E9ULL, 0x79724EBF761E09DDULL, 0xA82D8621F0A8BBBFULL, 0x2B8963F76D57C7F6ULL
        },
        {
            0xD295919CA54EC2A4ULL, 0x3DA4A1F3F8CE95A7ULL, 0x2DA86BBA4E5E663CULL, 0x1A3400FB358907D6ULL, 
            0x3AA67ED37E06ED89ULL, 0x9A9939402900895CULL, 0x594821F62133B2A6ULL, 0x60B54A89AD524D9CULL, 
            0x38958B7D37A2DF5CULL, 0x77DC3095A80B30B2ULL, 0xE6FA56481E3C55F2ULL, 0xA245DB861A723B2EULL, 
            0x7F14CAE4346355FCULL, 0x44A5F645EA9128D7ULL, 0xE99CAAC7CEB15A68ULL, 0x8E4E8ADB15840807ULL, 
            0x7FE996058CF8FEFEULL, 0x0DA0E8672B22E329ULL, 0x1D25621C6B52B7CEULL, 0x3CA7BA0C6A66D746ULL, 
            0x225CABD15A0AC9D8ULL, 0x0EA1CC9965DC4AA5ULL, 0x48BF33D94C7DA3EAULL, 0xBF5C68614B3A5541ULL, 
            0xD46813048A5BC14AULL, 0xD825F6C305644DDEULL, 0x5055AD953C3A64DBULL, 0x507EF2A521749FB8ULL, 
            0xB87A96CF467D18E5ULL, 0xD27812E2B283A7E6ULL, 0x22BF69518A45E1CAULL, 0x565C14810ADCF6DEULL
        },
        {
            0xE4479AA6C4A73CFBULL, 0x6B4C2822A6ED2C57ULL, 0x1525854CEF8C9B8BULL, 0x229A858EB8A4A30FULL, 
            0x5AFB2985E8201FFAULL, 0x1DB2D9F75F88C6D1ULL, 0x3919DE9AAA945431ULL, 0xB0A04B7CD9F50164ULL, 
            0xC101026995DE9519ULL, 0xBD9FC1C80DAD29DEULL, 0xA8B28E664E6A3D4DULL, 0x0D4DE794FDEF5F1DULL, 
            0x0D2B6CFAF6F9CB67ULL, 0x795493F9938B87B0ULL, 0x4C4B83A31C10B119ULL, 0xC3551946B71A2101ULL, 
            0x134F546CE24B5D9DULL, 0xE80CE5F0ED2568B3ULL, 0x963F54068974134DULL, 0x8D3AA27528729344ULL, 
            0x92F0416D50A193F1ULL, 0xAB34F0863C919C56ULL, 0x3F11888C53EE35C4ULL, 0x7854C31DBF3A661DULL, 
            0x1E6EDD4F17A08CD5ULL, 0xDDBED5965D0CC1D7ULL, 0x90D04DB800189432ULL, 0xB8AC417D04FFFF3FULL, 
            0xE5D4EF39EEDF730EULL, 0xED73BB3FA1738617ULL, 0x5FFC6115DD85540AULL, 0x091AFD407538ECE6ULL
        },
        {
            0x002B270B3810EE56ULL, 0x221AF092F6DB002AULL, 0x7156D4018D202EF3ULL, 0x2739E78C28FC14DFULL, 
            0x1A34B982B78F3F1EULL, 0xF306F25A7E5604AAULL, 0xDC11ECEE51B06AA4ULL, 0x5685E04BC8943073ULL, 
            0xCEEA7D9585FE8B3FULL, 0x2D8BD6BAF9B22083ULL, 0x62DFADE202594C53ULL, 0xC3526861DBD2290CULL, 
            0x90AA2E9E35C21752ULL, 0x76B49D9349028408ULL, 0x7161E8F535260917ULL, 0x61D070A080D7E87AULL, 
            0xDD67720D0344F997ULL, 0xB4B84CA4D55D905EULL, 0xDA26F5E6C185E48FULL, 0x4A60239C2E40BD3AULL, 
            0x0D9DFD4F428CCA82ULL, 0x82E19A9520643F40ULL, 0x80874422134C415AULL, 0xA01349D7E1BBC2C4ULL, 
            0x0223025D72459D92ULL, 0x5A925A32E710DB99ULL, 0xDAB4FD20402D32F9ULL, 0x91DB94F2F24C7287ULL, 
            0xCBCEFCB1DEA767BAULL, 0x1CA89865C6DD1A7FULL, 0x5ED2E3ACB6F16A14ULL, 0x494F54795BEC9599ULL
        },
        {
            0x63C7993C51994C2DULL, 0x2665CB094543D1FCULL, 0x288131F6434F0CDDULL, 0xC47351D2F5EDF954ULL, 
            0x957A5CD4B6D9A557ULL, 0xAFD9BA43B718173DULL, 0xD8FA74B8D2F9042AULL, 0x426988F44B19883EULL, 
            0x255E811E4E109D1BULL, 0x89E230642ECD96B8ULL, 0x74CF08DF5421574EULL, 0xB72DB11B94E8496AULL, 
            0xCB42EAE1D754229BULL, 0xE8377EDB349328E1ULL, 0x98A5B8F1991A31A3ULL, 0x59CAFD2CF4DDD94FULL, 
            0x75C2D1A2C89660B3ULL, 0xAA1B0BAC8CCBCFADULL, 0xFA0B039795561F36ULL, 0x81414E07A7B439FCULL, 
            0x3B47F6CAE5718C43ULL, 0x44D649D84CDD6A28ULL, 0xFFCBD34D1FC9057EULL, 0x5BFA0B1D56B8E742ULL, 
            0x46877ED21BEE80DCULL, 0x0499CFF896CEDFA3ULL, 0x18C38DE66E5C13E3ULL, 0xFAAC9998D4165A17ULL, 
            0x9B25EE204D0B3F7FULL, 0xEA6681E834D62375ULL, 0x6DE2E3DC20E93F98ULL, 0x67BC180F9EA443F3ULL
        },
        {
            0xBB1BA6A771FE4568ULL, 0xDC4F08511AA95BB1ULL, 0xD4703C49BDC5EE67ULL, 0xCC2C495A9C4933B0ULL, 
            0x7DB3FB3F3BCD64C2ULL, 0xD680891415B90636ULL, 0x4C6A580F150D9DF4ULL, 0x7C68EC8BF89D55EAULL, 
            0xA2185FA6DA1D6FA2ULL, 0x446B9BAC549BE9AEULL, 0x1B114BA8A571CC37ULL, 0x73A834F792FD43ECULL, 
            0x787389E19814C0B4ULL, 0xD633A74285578591ULL, 0xBEC21E504B2DC3E9ULL, 0x1EFD2E2918DF188AULL, 
            0x65B68E573DAA4FD5ULL, 0xEC7393C66F5D0748ULL, 0x49FABC5A703BA6AEULL, 0xB1A9426FDD22CE18ULL, 
            0x280DB5843D3E2E9EULL, 0x313C4EED7BA93045ULL, 0xA521A76A4F9C1AADULL, 0xFA613830429778E1ULL, 
            0xC7A684348A0930CEULL, 0x818D91E09C4A419AULL, 0x5CCFD2668DA84703ULL, 0x5AA0040106F2DE0FULL, 
            0x90517E95F6FD96E1ULL, 0x060F93F62831248AULL, 0xED78DD75BDCCCEDAULL, 0x679E0DA9FC9E7058ULL
        }
    },
    {
        {
            0x16BB8B37B827906EULL, 0x3739CA0F3400A309ULL, 0x9A36BEA5E4DB1A31ULL, 0x5E9D2FE5C6E2C308ULL, 
            0x4E32571A6BB43B58ULL, 0x08E57CD4C935736AULL, 0x54D6A5BB8A00C089ULL, 0x7D39F6BD7F70456FULL, 
            0xE0538F57EC087F3EULL, 0x2A7D929466C0EDADULL, 0xA6CC5E31E4495552ULL, 0xBA3DFB0CD3023085ULL, 
            0xE8E8DEF7475D790FULL, 0xC5C78EDE6EC5BD08ULL, 0xE9E7BD620B7C9BDEULL, 0x9E8839FF54CAC5B8ULL, 
            0xBFA2BB77BECB5A85ULL, 0x2F28F6DC2AC0C2BAULL, 0xF24F7392016C8881ULL, 0x380F34EB703C98BEULL, 
            0xD7631C1F1DC6AE62ULL, 0xAC18755DD0C2AEB9ULL, 0x45A3BA477012546FULL, 0xD7DAFB37DE4D3AB7ULL, 
            0xB7A455A1FE2AC586ULL, 0x091DDA308E8135DCULL, 0x8EAC8A0100E8EE22ULL, 0x117E09B2924A5FF2ULL, 
            0xD5660643DE402571ULL, 0x1EE44A116A823A66ULL, 0x969022667FDB1731ULL, 0xB65A2EF228A2A698ULL
        },
        {
            0x8FA00A5D8F97D679ULL, 0xCD163B2DECA31F29ULL, 0xEF3583CD20AAD511ULL, 0x0B0E15B5341C9DB5ULL, 
            0x34A991DBA5277F54ULL, 0x9B37F36EFD13B580ULL, 0x3610092A6A807FBBULL, 0x532F8043908B2898ULL, 
            0x12900BCFBAB8239BULL, 0xD098608A13562F67ULL, 0x65A7228C2D7FFC32ULL, 0x241080ECE3906BE7ULL, 
            0x00D4E343890F8E9CULL, 0x7E5C605D6E5F2F86ULL, 0xE8628CF245C8DE1EULL, 0xD85B1955D70D57A4ULL, 
            0x5D467B64CD574319ULL, 0x716CD47B936F27F2ULL, 0x20B9A481DC4BED60ULL, 0xFBA839081CD09379ULL, 
            0x7136B34367FB4EC0ULL, 0x200838D7001D770FULL, 0xACBFE432B0626569ULL, 0xD85E9B475BE8E5A2ULL, 
            0xDA22852D06E6604BULL, 0x24442544179595F2ULL, 0x8E36E80031B610AFULL, 0xFAA245787301C3CCULL, 
            0x2B3490930F86CAF0ULL, 0xBDEE85EC31849CD0ULL, 0x187D2959D91F920EULL, 0x1319B9D3EA49D9CEULL
        },
        {
            0x1AE77E21EA72E439ULL, 0x1AD9C665EE4CF4D7ULL, 0x1D5E1EE905ED4DF2ULL, 0x730CD16EFAA7A4DDULL, 
            0x2686CA872121978FULL, 0xCC29A0ACEDED511DULL, 0xAE2AC6A0252A5A96ULL, 0x4D016196E0948B66ULL, 
            0x21E219546DF71893ULL, 0x06D932BDDCA2F750ULL, 0x88C2481B7C5398C0ULL, 0x6015973B074A8666ULL, 
            0x511479A9B8F25494ULL, 0x1E2E2B73783DB2CAULL, 0x33A17D4D8BE58EF8ULL, 0x0BE9A2ECD074113FULL, 
            0xC678AA05D9F4AFFAULL, 0xB5ED5EEBB5B79087ULL, 0xF16DF245E0480506ULL, 0x6DA7B62CCE997644ULL, 
            0x35070ED3583EDCEDULL, 0x7F3048BB4808B9B5ULL, 0x2F89DB1F218B0479ULL, 0x4BEF597B7B76E5B9ULL, 
            0xE739440A2F7A61FDULL, 0xC2726E0220CC1076ULL, 0x155B492019E9EC49ULL, 0xD553962175AF7711ULL, 
            0x15086A80538530CEULL, 0x0D533D652F7D2D83ULL, 0xED6290E5286C89E7ULL, 0xC6C052A1668A6DFBULL
        },
        {
            0x6C43EBD1491CC381ULL, 0x98D636C1E1E579FCULL, 0xF325014D6C7B497CULL, 0xEC308E6F1FB68A18ULL, 
            0x2C8E7D79AB80F026ULL, 0xE6FD5EA501B0CCE9ULL, 0x76BFA88D6BEA7B36ULL, 0x54BDA761C745A910ULL, 
            0x4B31089DE8748E18ULL, 0x4C698D3216885CDDULL, 0xA6B07D8D372A5AFAULL, 0x980A779DE8975F57ULL, 
            0xE8D147C1AC6EF0B6ULL, 0x3FD9BCE39AE5EADDULL, 0x84763630905627C7ULL, 0xD3FEEAB03BD36D17ULL, 
            0x6DFB822E9E1ED48AULL, 0x526FEBE2BE4738D3ULL, 0x989B7D3FBF593730ULL, 0x8ADE54BF62F32FF2ULL, 
            0xC4B0D1B3133549D4ULL, 0xCE8C0B4409A1DDCDULL, 0x0BB8573296CB7F5FULL, 0xE173C978041ABBB7ULL, 
            0x1625CA58BBC32369ULL, 0x835308691D64037AULL, 0x271741421BBFE00EULL, 0xAC5214E901842C52ULL, 
            0xC00BC8017AC066AAULL, 0x3296EC629D43E155ULL, 0xA6A888BFAB91C719ULL, 0x394E790B13AF6ECAULL
        },
        {
            0x65099DC545896432ULL, 0x0FC0B34D82D7B327ULL, 0xE5F0BA086191A7D2ULL, 0xD10EBC8B04822A45ULL, 
            0x2B41E23F727E7EE5ULL, 0x359B2690B81850D5ULL, 0x7D56AA4C7B542D3BULL, 0xC706C0F3767F0DBDULL, 
            0x70A76C31848B3627ULL, 0x72AEBF39B919D528ULL, 0x101B74AF2BCDF3BBULL, 0x86B50EF3BC4AEBE6ULL, 
            0xB330007FC04727CDULL, 0x1CA4A4B086D8EDD4ULL, 0x4005C6AE7050D181ULL, 0x68FC4CB9EF7F7BC2ULL, 
            0x380538B0B596E8C6ULL, 0x1C8ED577483E59E3ULL, 0xA28EC759E71896F6ULL, 0xBED13F2A221173B9ULL, 
            0xDF1B2362E1698479ULL, 0x3A93903A91408C63ULL, 0xA630985E582C1FC4ULL, 0xAF98CCD7EFFB5D64ULL, 
            0x629BADDB29099D08ULL, 0x5A4193828E70A2AAULL, 0x3B98712690ADC20DULL, 0xA90882EFBADD8A88ULL, 
            0xDB64AB1C9C1933C0ULL, 0xDC0EBACD653929A9ULL, 0xE66F018C0F553830ULL, 0x0DAE64EFF33185A8ULL
        },
        {
            0xC429CC95D577E5B6ULL, 0xCD839E71FCBA70B1ULL, 0x4B3DE3E719F56C84ULL, 0xFA8CC7122DE754A8ULL, 
            0xF9E5E4198D66E14FULL, 0x4182E407253FBF43ULL, 0xDE7F61117AD73CACULL, 0x968AE95137B42CD3ULL, 
            0xBE0F02312AE6CA04ULL, 0x566E5FD038ED0185ULL, 0x2064847CFF848DF1ULL, 0x3248FB5A7F80AF78ULL, 
            0x12C0C480095CBCE6ULL, 0x2E06E30CC3EA9FC7ULL, 0x5619D3D198B67905ULL, 0x219D3F0A8639FCCBULL, 
            0x067AD5B9D4A8AD16ULL, 0x3968468E936CF7E1ULL, 0xB6D147EEED5DE304ULL, 0x7617BE4A00268516ULL, 
            0x9D92FE47C2DBB767ULL, 0x59F97BD4D2E8BC63ULL, 0x7566B0D86585EA01ULL, 0x9FF7124EBB444144ULL, 
            0x54CBF0366F1901E8ULL, 0x24D9AB94AE17AAC3ULL, 0xC0724A0030A13095ULL, 0xF56F0A078428EC5DULL, 
            0x147D4C646A2324C9ULL, 0xBA711419E4C297F2ULL, 0xC962CDE34DCF3B8BULL, 0xA910EF7BFA5EF185ULL
        }
    },
    {
        {
            0xED889B637E43A733ULL, 0xC2A3FD61A9567E23ULL, 0x3013E41BF8976597ULL, 0x83B7D4BD4703CF28ULL, 
            0xB5BA1F7FEC3D3D53ULL, 0xF65A182DE4762FDFULL, 0xEF360FCF4D248592ULL, 0x957538B123C23894ULL, 
            0xC2B98CB6B5EA305FULL, 0x79144100F3BD4642ULL, 0x63E4134A8F610BADULL, 0x2AA5D97496A5E809ULL, 
            0x70824A84A1E7F266ULL, 0x3289589B48C31FE9ULL, 0xEAEE5669E58C61CFULL, 0xF3669B16C43A3912ULL, 
            0x5ACB58F7B31D769FULL, 0xB373D0B1D173273BULL, 0x1C9D3638A9FE900AULL, 0x661FC20CB2D1AA46ULL, 
            0x567AC4C4D4FA23CEULL, 0x7CCD72CDFA1CFC79ULL, 0x2CD9E40B6FF779E0ULL, 0x01B2C5EE9A65DAEFULL, 
            0x5DEE21BB2CF26C05ULL, 0x3E9FE63FF4128E7AULL, 0xF24AAFE72E05086BULL, 0x6AECD87EED4B2664ULL, 
            0x951FF64D445ADB44ULL, 0x3F7269C24897443EULL, 0xD8FE66344FBA8EBFULL, 0x035DB7104A071488ULL
        },
        {
            0x4A24A67B23E91D19ULL, 0x29D20101B63C6B6FULL, 0x966529E97F2405DFULL, 0xBCBFC20D182A2FFFULL, 
            0x7BA246E7CF9D0705ULL, 0x344707C884BF162BULL, 0x9C0C706C90395A4DULL, 0x2577EC5669DB5355ULL, 
            0xFD77FAFDF77F6F08ULL, 0xB5BD5993BDDA4418ULL, 0x7B8927F93B1DF398ULL, 0xE42D514962D56DE4ULL, 
            0x81B82C126ED06B5CULL, 0x521C204B34484D94ULL, 0x128EB08209BD9033ULL, 0x7357E9C7B666442EULL, 
            0x0759ADDACFD3CA98ULL, 0x7DB8AAB6BD260636ULL, 0xAAAFFAB1735A0B30ULL, 0xC60158A295E27C9EULL, 
            0x6D221DC55D07D42CULL, 0x65B5B5D27CFBD867ULL, 0x89D0C39F9A777498ULL, 0x3CA5D29D9DD6EA94ULL, 
            0x5DC8E5ABCC2DBD20ULL, 0xDD65DA1B1912E2E6ULL, 0x160970D8102EC4B8ULL, 0x7EB58542F836236FULL, 
            0x60BE2AD383BF31F5ULL, 0x7A692164167D77C2ULL, 0x8002565C4731E441ULL, 0xFB6C0DFC5D028C0DULL
        },
        {
            0xE287F0142D5B7819ULL, 0x1182E3FB5FDFC93EULL, 0xEFC777504EE3CED4ULL, 0x9D9A68C9AF7A8925ULL, 
            0xB4D6C7C967F86CE2ULL, 0x88300FF84FEB734AULL, 0xE685EA382E2C9382ULL, 0x8EB130AEA351FD37ULL, 
            0xE1FD7338C1FC58F3ULL, 0x16E3BECB606EE305ULL, 0x8E83DBD1F064AAD8ULL, 0x4B8BA81C655ED1A2ULL, 
            0x446CD4045517A28CULL, 0x7FB562971DC9E6DFULL, 0xA6BF4F7C6318FDFDULL, 0xA6D2D9F34E0DC4F3ULL, 
            0x2235177D4FB9692CULL, 0x47079CD340B392E5ULL, 0x812BE72B2E91643AULL, 0x263651E3C7E4BDE4ULL, 
            0xFF108D10EB319121ULL, 0x5A19A6721A8EC39FULL, 0x20EDA7B0793E7204ULL, 0xBB171B9CF2F24684ULL, 
            0xA5BFF13F6A4BA6ABULL, 0x09C4A6F5EF5F1B5BULL, 0xCA83B78276290467ULL, 0xC039E29E4A0F9EA6ULL, 
            0xF4BFC2B40E681AE6ULL, 0x9BF261DAA8F4EC11ULL, 0x223129ED839CDF0CULL, 0x78A7200EE66777BEULL
        },
        {
            0x955391AA7710AF0DULL, 0xCFF4602AAFBA7AB6ULL, 0xCD7AD2244C6F1E58ULL, 0x4D6205A9549B96BDULL, 
            0x81E009A20B17C1A4ULL, 0x7B3387C18BCFE715ULL, 0x4D5867DF8D7BE968ULL, 0x9AF32016FDC41C33ULL, 
            0x65E7E5079EC41A8EULL, 0x32054FD11EF2B842ULL, 0xEBF928BAA36F11A0ULL, 0x6F205916D7F506B5ULL, 
            0x1D438B992976D6B2ULL, 0x78EB66A9AABA1F0AULL, 0xD4C9773897A1B784ULL, 0x7CD4DDDBA8DF42FCULL, 
            0x5CC5D9DBAB52CE50ULL, 0x4DD3B6FEAE4D5CDFULL, 0x60F53C9FC06FCD59ULL, 0x88378A42720C4E47ULL, 
            0x02116902C324ED1CULL, 0xFC9BDAF3028BB48CULL, 0xE5A02D8D04CF96DAULL, 0x6771BC610F642D4AULL, 
            0x58A7BDE73020323EULL, 0x2B59BB0F51DA7AD0ULL, 0x5B801F0642A844EEULL, 0xB85F477236F2E834ULL, 
            0x6CB7A1346E69FBE7ULL, 0xFC7C4801AB82FEE4ULL, 0x4A6370B4CC3D9F19ULL, 0x72AADDBA370F2FE8ULL
        },
        {
            0x4F92441E1DAD3366ULL, 0x46BC06BD89B81EE8ULL, 0xBC7F339F21181AADULL, 0x421D8CEC47B006D0ULL, 
            0xB7F840DBEE84C65FULL, 0x668665AD771854FEULL, 0x4F33938AC70583ECULL, 0x0B68FD61907B02EEULL, 
            0xAB4784F0391025C2ULL, 0xF2A2547014FB0F2EULL, 0x2B5C7790705784EFULL, 0xE9A32D9949499868ULL, 
            0xC23FF7C738AEC28EULL, 0x9FCCD589F30E5270ULL, 0xD231BDAF355BC89BULL, 0xBA72DD8806F741DDULL, 
            0x53D79942EF1DF540ULL, 0x13DCDA6C4165D626ULL, 0xA6570573583C0DA9ULL, 0xCEA7159037FC8EF5ULL, 
            0xA2080884E000338EULL, 0x4434F93667011DDEULL, 0x9FC17E35B4EADADDULL, 0x69227AABD35910B3ULL, 
            0x55BD2843588FCAA4ULL, 0x2C6B072895836BE2ULL, 0xDD3B8C6D4F6E97DBULL, 0xBDA8536E24F5968EULL, 
            0x7104581F302CAB1DULL, 0x58496C56AC31871EULL, 0x62FDFB409AFD9C52ULL, 0x5A3BDF794913B290ULL
        },
        {
            0xD6694212C7F98B3DULL, 0x5F55A58CB643A224ULL, 0xBE49BD8AFFC8218EULL, 0xD34C7ED53E638C7CULL, 
            0xFF187504B7DA15E7ULL, 0x9E62BC9C21743C69ULL, 0xC75330E9B54BC231ULL, 0xA73DD2D68AD5BDF2ULL, 
            0x038D6F0442EF8209ULL, 0xCEB5D0B833C1F301ULL, 0x12937D24E90CFA09ULL, 0xE238A9FABD3EC075ULL, 
            0x9825718A589214C8ULL, 0xC3C30ED5D4C0A575ULL, 0x3B24DC87D0CEA8A9ULL, 0xA18254CD783F2387ULL, 
            0xE50DD0688276E7C3ULL, 0x306D794CCAF93B43ULL, 0x35C31A6064DC518CULL, 0xC4B2F07A85AF68AFULL, 
            0xBD0260F08A2E58B5ULL, 0x7BA7EB2265EB0219ULL, 0x98DEC08FC44A7169ULL, 0x3C0EB85989C2B30FULL, 
            0x6F658679B10B7362ULL, 0xA189D774B318722EULL, 0x17CB1425A3728E30ULL, 0x132436A570CE4E5FULL, 
            0xE4BB90F155C43612ULL, 0xD4922931F4DB45D0ULL, 0x215A9C0A87DBCB60ULL, 0x42C3E228AC5127D3ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Altair::kPhaseHConstants = {
    0xFA10A6CA9BF30D0BULL,
    0x6AE7410BF363BB4CULL,
    0xEA086BD1996963F3ULL,
    0xFA10A6CA9BF30D0BULL,
    0x6AE7410BF363BB4CULL,
    0xEA086BD1996963F3ULL,
    0x358259E4CC287BB1ULL,
    0x5F1FD0203CF9B5F2ULL,
    0x52,
    0x1A,
    0x4D,
    0x5B,
    0x18,
    0xBD,
    0x3B,
    0xE5
};

