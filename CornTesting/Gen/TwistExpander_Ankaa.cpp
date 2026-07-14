#include "TwistExpander_Ankaa.hpp"
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

TwistExpander_Ankaa::TwistExpander_Ankaa()
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

void TwistExpander_Ankaa::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xDE7F0DAE57C437AAULL; std::uint64_t aIngress = 0xD4AAD835EC762A54ULL; std::uint64_t aCarry = 0xB1CABDE52B6ADD24ULL;

    std::uint64_t aWandererA = 0xF1A580B7A54402CCULL; std::uint64_t aWandererB = 0x85825D0329B653FEULL; std::uint64_t aWandererC = 0xA5E314D65B67CA68ULL; std::uint64_t aWandererD = 0xD3C60E68C071BC97ULL;
    std::uint64_t aWandererE = 0xAB8AC5BA0615A060ULL; std::uint64_t aWandererF = 0xEB2A82CB1282A7DEULL; std::uint64_t aWandererG = 0xD370D5219973037AULL; std::uint64_t aWandererH = 0xE51C61EB18F79FD3ULL;
    std::uint64_t aWandererI = 0xF79B2C8D53BEB0EDULL; std::uint64_t aWandererJ = 0xD59ED188761CF22DULL; std::uint64_t aWandererK = 0xE75AD1F6EEDFEB1EULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 9245075669486675688U;
        aCarry = 16240364217934247587U;
        aWandererA = 16826741162886275214U;
        aWandererB = 16896734737169798191U;
        aWandererC = 10554811691241342341U;
        aWandererD = 14426274585002560798U;
        aWandererE = 15858906160449455840U;
        aWandererF = 10152693910471068493U;
        aWandererG = 14049030934736876946U;
        aWandererH = 17680026678177267734U;
        aWandererI = 9471273992968668745U;
        aWandererJ = 18245003114120239741U;
        aWandererK = 11402830747192227821U;
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
    TwistExpander_Ankaa_Arx::KDF_A_A(pWorkSpace,
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
    TwistExpander_Ankaa_Arx::KDF_A_B(pWorkSpace,
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
    TwistExpander_Ankaa_Arx::KDF_A_C(pWorkSpace,
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
    TwistExpander_Ankaa_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Ankaa_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Ankaa::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xB0EF6D2107F089FAULL; std::uint64_t aIngress = 0x908785D9F5E007EDULL; std::uint64_t aCarry = 0xC8B1093FBBBAE0DDULL;

    std::uint64_t aWandererA = 0xF525F50EFD9D56A0ULL; std::uint64_t aWandererB = 0xE9356D9F863B98E2ULL; std::uint64_t aWandererC = 0x8A516DEE96AFDF63ULL; std::uint64_t aWandererD = 0xA18D52170C7A6F4FULL;
    std::uint64_t aWandererE = 0xC5186D6F4F06ACC8ULL; std::uint64_t aWandererF = 0xC8D4959BBE6DF751ULL; std::uint64_t aWandererG = 0xC9D6A0B1F15D7ADCULL; std::uint64_t aWandererH = 0xD396303FF196B9C5ULL;
    std::uint64_t aWandererI = 0xF8F3993C60EAF8EFULL; std::uint64_t aWandererJ = 0xE1D120D93DEFB5B4ULL; std::uint64_t aWandererK = 0x98183A1357E8A03CULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 17494206871412710772U;
        aCarry = 17666998739659092008U;
        aWandererA = 10714467690385056619U;
        aWandererB = 15101446007321449380U;
        aWandererC = 11090171977209001252U;
        aWandererD = 18381281471738506266U;
        aWandererE = 15127349665118580577U;
        aWandererF = 10767360578979489944U;
        aWandererG = 11421094663150453018U;
        aWandererH = 10506580096625001383U;
        aWandererI = 9683825252237542645U;
        aWandererJ = 13181450998415155344U;
        aWandererK = 11925850796483938148U;
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
    TwistExpander_Ankaa_Arx::KDF_B_A(pWorkSpace,
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
    TwistExpander_Ankaa_Arx::KDF_B_B(pWorkSpace,
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
    TwistExpander_Ankaa_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Ankaa_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Ankaa::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xFEA8572F2A762440ULL;
    std::uint64_t aIngress = 0x993279E6BE4FD388ULL;
    std::uint64_t aCarry = 0x9EE51BD7757BCBD0ULL;

    std::uint64_t aWandererA = 0x85ACD31FFC1AFD54ULL;
    std::uint64_t aWandererB = 0x846264FA5B89B274ULL;
    std::uint64_t aWandererC = 0xB0C723CD45F81D18ULL;
    std::uint64_t aWandererD = 0xF75053B6B78E465CULL;
    std::uint64_t aWandererE = 0xB7C1F5E1464CEBB4ULL;
    std::uint64_t aWandererF = 0xB8AD76A637141FB6ULL;
    std::uint64_t aWandererG = 0xA7AEE02C38089D07ULL;
    std::uint64_t aWandererH = 0x8751A935C4DFB9CDULL;
    std::uint64_t aWandererI = 0x92F8A94BA3B8FB55ULL;
    std::uint64_t aWandererJ = 0xC10E112A54E6DF5AULL;
    std::uint64_t aWandererK = 0xD3962710EAE4D136ULL;

    // [seed]
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneA);
        TwistSnow::AES256Counter(aSource, aSnowLaneB);
        TwistSnow::Aria256Counter(aSource, aSnowLaneC);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneD);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseBConstants), &(mDomainBundleInbuilt.mPhaseBSalts), aSnowLaneD, 1);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneH);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneG);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneA);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseFConstants), &(mDomainBundleInbuilt.mPhaseFSalts), aSnowLaneD, 5);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneE);
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
    TwistExpander_Ankaa_Arx::Seed_A(pWorkSpace,
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
    TwistExpander_Ankaa_Arx::Seed_B(pWorkSpace,
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
    TwistExpander_Ankaa_Arx::Seed_C(pWorkSpace,
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
    TwistExpander_Ankaa_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Ankaa_Arx::Seed_E(pWorkSpace,
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
    TwistExpander_Ankaa_Arx::Seed_F(pWorkSpace,
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
    TwistExpander_Ankaa_Arx::Seed_G(pWorkSpace,
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
    TwistExpander_Ankaa_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Ankaa_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Ankaa_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Ankaa_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 8 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1902 / 1984 (95.87%)
// Total distance from earlier candidates: 13355
void TwistExpander_Ankaa::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 964U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 2042U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 669U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 242U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 643U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1565U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1413U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1727U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 284U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1154U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1303U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 345U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 325U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 449U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1582U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1831U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 206U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 804U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1069U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1860U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1332U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 705U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1502U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 129U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 47U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 996U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 214U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1364U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 730U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1776U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1244U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1430U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 295U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 906U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1163U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1017U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1640U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 637U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 797U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 416U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 580U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1487U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1737U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 772U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 64U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1236U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 313U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1726U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 511U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 469U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1898U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1558U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1590U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1873U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1428U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1427U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 594U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1477U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1323U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 2015U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1319U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1047U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1187U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1223U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 504U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1104U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 725U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1805U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 755U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1093U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 279U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 285U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 766U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1023U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1815U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 649U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 609U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 310U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1416U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1725U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1853U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 558U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1120U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 347U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 542U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1930U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1952U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1728U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1090U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1598U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 846U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1712U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 155U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1296U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 917U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 250U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 211U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 714U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1628U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1283U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1456U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1229U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 968U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 323U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 539U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1224U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 780U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1457U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 287U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1857U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 945U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1480U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1207U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1143U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 108U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 849U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1434U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1182U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1965U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1114U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1820U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 561U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 252U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 36U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1170U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 403U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1933U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 394U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }
}

void TwistExpander_Ankaa::TwistBlock(TwistWorkSpace *pWorkSpace,
                                       std::uint8_t *pSource,
                                       std::uint8_t *pDestination) {
    TwistExpander::TwistBlock(pWorkSpace, pSource, pDestination);
    if ((pWorkSpace == nullptr) || (pDestination == nullptr)) { return; }
    std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    std::uint64_t aPrevious = 0xDCD357F02D5486F1ULL; std::uint64_t aIngress = 0xD7CF357D7ACBCDADULL; std::uint64_t aCarry = 0xF2BB42725D9D35E9ULL;

    std::uint64_t aWandererA = 0x9DD7CA1A5A2B0BF7ULL; std::uint64_t aWandererB = 0xDE4294DD2770DCCDULL; std::uint64_t aWandererC = 0xE1A98D54FF7ADA9FULL; std::uint64_t aWandererD = 0xCE7CFC07934DA649ULL;
    std::uint64_t aWandererE = 0xF91A72FC3BD0C809ULL; std::uint64_t aWandererF = 0xEE78FCE6485C1281ULL; std::uint64_t aWandererG = 0xD3A54E246C625DBDULL; std::uint64_t aWandererH = 0x974E60F14DC9C058ULL;
    std::uint64_t aWandererI = 0xC9FCA45CD11D7DD6ULL; std::uint64_t aWandererJ = 0x8C3971B4B36D951AULL; std::uint64_t aWandererK = 0xF06BC7B4BD26F087ULL;

    // [seed]
        aPrevious = 14513757172884363886U;
        aCarry = 16256154892427592425U;
        aWandererA = 12030569695084799266U;
        aWandererB = 13522999117628561906U;
        aWandererC = 16743605433468334885U;
        aWandererD = 13984085444774355636U;
        aWandererE = 15948757820716710306U;
        aWandererF = 10622020124004120756U;
        aWandererG = 17245358593701822526U;
        aWandererH = 13103623579630932897U;
        aWandererI = 15825580776394505814U;
        aWandererJ = 10821330873833180387U;
        aWandererK = 11889885728540250652U;
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
    TwistExpander_Ankaa_Arx::Twist_A(pWorkSpace,
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
    TwistExpander_Ankaa_Arx::Twist_B(pWorkSpace,
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
    TwistExpander_Ankaa_Arx::Twist_C(pWorkSpace,
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
    TwistExpander_Ankaa_Arx::Twist_D(pWorkSpace,
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
    TwistExpander_Ankaa_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Ankaa_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Ankaa_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 8 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 3943; nearest pair: 528 / 674
void TwistExpander_Ankaa::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3339U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7691U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 659U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1355U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2010U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4670U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 685U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 941U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3256U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1480U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 163U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7520U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7329U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7857U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4922U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7777U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1789U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1674U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2004U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1889U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 428U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 108U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1804U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1259U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 277U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1715U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 73U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2019U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 501U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1634U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1438U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1249U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 102U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 380U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1840U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 835U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 8 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 3950; nearest pair: 533 / 674
void TwistExpander_Ankaa::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7162U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6438U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 907U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7289U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
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
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4042U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4307U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1620U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4415U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6137U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3117U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2194U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3345U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3776U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6513U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6439U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2429U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 129U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 776U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1929U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 38U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 850U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1370U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 691U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 455U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
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
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1553U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1722U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 797U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 8U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1895U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 417U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 631U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1578U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 361U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 973U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1928U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1138U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Ankaa::kPhaseASalts = {
    {
        {
            0x27F4673F27ADF597ULL, 0x53B0A697CC97729FULL, 0x7241E8AF3D6883E8ULL, 0xA6D17707196088E8ULL, 
            0xBD880591529C3C55ULL, 0xEF195DA648B856E4ULL, 0xF839D9D0719E2541ULL, 0x62CC881CECC66EFBULL, 
            0x7A550611EFDA3E72ULL, 0x2264673A8BD567CAULL, 0x732E4EDDDE499F38ULL, 0xFF8DF787013A3278ULL, 
            0xD7E4D1B594694DAEULL, 0xE5073A02D31048A7ULL, 0x9E190D9023E62905ULL, 0xE52DFCFB6835BCEEULL, 
            0xD5ACEC044A98896CULL, 0x7895785F6F577F31ULL, 0x37BA8711C8777E78ULL, 0x270F4C7641FE40A4ULL, 
            0xAEFE42F48FDCC0EEULL, 0x8C335A60033A530BULL, 0x51EDFDB8FF6A0298ULL, 0xC2BDA5BA303C1EB5ULL, 
            0xCF35FBFB80855B16ULL, 0xAD1D852354915096ULL, 0x73CC6A87EC0AB8C1ULL, 0x9E307E9752F2321DULL, 
            0xDDC44275F67D200CULL, 0x55EED4B7E891CB84ULL, 0xD04E11F268CD1E32ULL, 0xB33B7A73256F8272ULL
        },
        {
            0x44FAF8686BD81588ULL, 0xCF6E1E005527F684ULL, 0x27845033450CAD09ULL, 0x53D3BD93A835CF0CULL, 
            0xE388C904F8BB8F0BULL, 0x7253E07E3126A00AULL, 0xFBFE367D5283695AULL, 0x84933BAC0E9F1D02ULL, 
            0x3B05E4098D703097ULL, 0xFD96917DA56389BBULL, 0xA25EB6B16BD9B636ULL, 0x0BCE470B9579B42AULL, 
            0x3CF2039CF3D2DB93ULL, 0x5854DD3835327633ULL, 0xD2D292E518175936ULL, 0x9BC39A515C82FD07ULL, 
            0x2AF76D24D833DD6FULL, 0x8F7694FA8AB0B6FEULL, 0x76A245783E1CC395ULL, 0x79CB47710B2B5F6FULL, 
            0xBA317EE2A4358BD0ULL, 0xBFACB6503EEB2E2BULL, 0xE8FD8AF41B26562FULL, 0xA15318FD4670895DULL, 
            0xCAF634D2DB21F7ABULL, 0x199CA45359DC7AF9ULL, 0xE3F93507D7667CF7ULL, 0xC7C704970D5FBE59ULL, 
            0xB2ECFE2B02A9660AULL, 0x5CFD7C1048EA6C1CULL, 0x6E3CD8DCC8DF6513ULL, 0xEEC88B63AC6DA8B8ULL
        },
        {
            0x2E42CAFDACFFB701ULL, 0x70DB23169F186591ULL, 0x6D653DA01E5A6537ULL, 0x7AC282B95F5D8740ULL, 
            0xA30223C89F8A6B89ULL, 0xFE3C4AE6343F3E39ULL, 0x7780F7E2257D94C8ULL, 0xD0CA5F2D4D1B57EEULL, 
            0x1BAE2F4E5286A6CCULL, 0xE4017B8FD549EEDAULL, 0x6B0F17DABF2348C6ULL, 0x301C63D35DA12842ULL, 
            0x68F38A08C2939972ULL, 0x7CB35848315A2A9DULL, 0xA2C580C680649D27ULL, 0xD7A4F3508FF84BA0ULL, 
            0x32C2096D0991E70EULL, 0xC00CA5344E5D1E29ULL, 0xD8F67FC6997DA3C9ULL, 0x2BAD2CF421340F5EULL, 
            0xDAF47092E6DB9311ULL, 0x79DECBE258EF29CDULL, 0xADA846B34183A245ULL, 0x4F3EDBBDD5E1009FULL, 
            0x144EA985B7BF3B97ULL, 0x3118A74725B0DD22ULL, 0x72A087918A5E53DAULL, 0x2933E3712EC75221ULL, 
            0xCDFF009FB9963E6DULL, 0x8E1D0E99AE0A471BULL, 0xC342E6E5E2BE5CF4ULL, 0xDAAAA6AE991C4FF0ULL
        },
        {
            0xA7259CD588681C71ULL, 0x3A5650ABA6FB568AULL, 0xDD7055C793CD2912ULL, 0x79DA5374FB1E6712ULL, 
            0x0564E0A8FE6EA68BULL, 0xF7D5B7E38FCFA305ULL, 0xE39DC556CD93AB37ULL, 0x93E349A64CEA1036ULL, 
            0xD0A2ECF0DD8D5CA1ULL, 0xFC1C7E3BAF1660A2ULL, 0x8CECCBAE0229CC7EULL, 0xB65D439BC3C29429ULL, 
            0x577E3D72A3ED4BBAULL, 0x1DF89D96BCC8AB95ULL, 0x00667C562B0FD4F9ULL, 0xD800731AB3FC7D3AULL, 
            0x0E0D35767A96DB21ULL, 0xE1B9955D248618E6ULL, 0x05C0ED4D84F7356CULL, 0x51C21E57E2D10505ULL, 
            0xCD2F86A4FC5DE9A4ULL, 0x28534C15EF35B6CCULL, 0xB2EF7985F61FAF16ULL, 0x1A582A308A6F47B3ULL, 
            0xAAB7B981F20F3EB7ULL, 0x81B94977AB37E44DULL, 0xC9745E5A62D0C394ULL, 0x9188A589CDCF2DB3ULL, 
            0xB1603D1667D341D2ULL, 0xA732E43796191F50ULL, 0x2747B91B84DA69F1ULL, 0x4EF06476667FD5BDULL
        },
        {
            0x94F3A718882948F4ULL, 0xB7DCEE7ACA0B97B4ULL, 0xCE885DBFBA0F2541ULL, 0x95CFBC718B84016EULL, 
            0x6C1C4974F5AAFBFBULL, 0x6C53EC30A744F5C9ULL, 0x77BE5C721B7D9E14ULL, 0x6DF8E344B5DF3462ULL, 
            0xECD33BE8887728C8ULL, 0xF2FBC9A48366A64AULL, 0x52A3C6399EFD34FBULL, 0x35E9809954DA09CCULL, 
            0x61882ED0F13F0F7CULL, 0x56653441333627E5ULL, 0xE2A71BB032D13C9EULL, 0x6D4E3374E4DE79EBULL, 
            0x28CB16C6C0EAB110ULL, 0x07C0199E25D93C0FULL, 0xF3A7416EDA056E42ULL, 0x8E1954FBB41E2E55ULL, 
            0xAE503F7459F8C93FULL, 0x1C5428E3F339336CULL, 0x49D8F449BE0B56A9ULL, 0x1511E378BF55C131ULL, 
            0x97B08BA95395DC31ULL, 0xFACB07F1DF1ABC2CULL, 0x0600D5652F39D1ABULL, 0x46A52E482114D40DULL, 
            0x4F689E6AADEB04FFULL, 0xA7F7519A142EB068ULL, 0xC4CF5A802F43B611ULL, 0x1B1AD79AD52527BAULL
        },
        {
            0xB37F0662D1ACAD4FULL, 0xDD84A2DAD0E23F86ULL, 0x6976BAD01B1C8B6DULL, 0x7D824436D2884BAFULL, 
            0x270D9B824B374ACDULL, 0x32391F97F3F5EFB8ULL, 0xB7C91A0E5EA8A57FULL, 0x89E72A2520515D5EULL, 
            0x8875EC0F4A43D35FULL, 0xE4E6F26BAABBFBCAULL, 0x28D8D88A291B985AULL, 0xDA51319E59D3F133ULL, 
            0x0E1592145F0A5DA4ULL, 0x1B1E12B6A5A3FA9AULL, 0x5FF2AB647EBDE41BULL, 0x358A34818E0916ACULL, 
            0x317765B12F340FDEULL, 0x0611697CFAAAC356ULL, 0xC2EBE981646259B5ULL, 0xAB54540B3530C24EULL, 
            0x7CDC5F15E3D31532ULL, 0x917E9F227D4847BBULL, 0xE432CE893AC6A467ULL, 0x3A185E2372400934ULL, 
            0x46FF38514F81EFDAULL, 0xC21ADDE9765300FDULL, 0xF68FB6B130720219ULL, 0xFCA3E1E090BE8D7DULL, 
            0x744B27B18E16E77CULL, 0x954795F055C63E9CULL, 0xC46AC3D554069C19ULL, 0x3ADEE0314D9756EFULL
        }
    },
    {
        {
            0x8452ABECF4E2D49CULL, 0x9DC4C4E56B9060D8ULL, 0x013ECC5F326A9C15ULL, 0x0CCA6B21BB2DD8BEULL, 
            0x4120B0FE8CD36BD0ULL, 0x82B8516E4386E05DULL, 0xAAEE2DD265C5D366ULL, 0xF6C6AFD18AE1BA17ULL, 
            0xE54BA67AD156D3D1ULL, 0x632B095CF19FFE19ULL, 0xD70AE840C679C015ULL, 0x494FA6476D3D15D8ULL, 
            0x7248D1768DBF2AFCULL, 0xF038A4F6FBB6525FULL, 0x8B668A46A8903AB9ULL, 0x48BAE1B840B6B59CULL, 
            0xDE6D12D5C583EF58ULL, 0xA76006E70D776C3FULL, 0x03D3F0E1452C63A6ULL, 0x7F25CCFE9EB2CD2DULL, 
            0xC132B7CD094F9FA3ULL, 0x4EF96AB58D59B181ULL, 0xEA20E341E6D013E0ULL, 0xC8584525EA9FD196ULL, 
            0x61A2CC805F2640CFULL, 0x0150F677F8440992ULL, 0x41BC5C4A733C5859ULL, 0x232B1838EF151CEAULL, 
            0x721A993DB2F6911EULL, 0x6B922600B62785A4ULL, 0x0D5478A3FB830AB9ULL, 0xBD70BBD0577C3166ULL
        },
        {
            0xC217270DD6D15933ULL, 0x29E397EF6BC8F97AULL, 0xCCFB8B425466AC68ULL, 0x6D461DD04E785A58ULL, 
            0x0590D45659DD2F3EULL, 0x6E0B05C5466AC934ULL, 0xCD2AD676BD2BDB93ULL, 0x3D7C45A4235B3907ULL, 
            0x1A434A191FDD3A16ULL, 0xCC8DE8E7478E5C60ULL, 0xDA87E1695A7828F2ULL, 0x43A03814DC5C22A1ULL, 
            0x3C51318A809F41F6ULL, 0x04E296A4C01A31BFULL, 0xF799E132B204DF06ULL, 0x3F4D77115DE57610ULL, 
            0x29F8E43B3037BB2EULL, 0xEAEFD56B163EF039ULL, 0x029C5B4AFBB1F62EULL, 0x22FCAC495C66DB55ULL, 
            0x7782898A9E979D1CULL, 0x00EB17E0CED3F07AULL, 0xAA0D90140520C458ULL, 0x0ECB7C2C82FECBE3ULL, 
            0x78B70F1C72A1E39CULL, 0x0E0C02AD6D87E646ULL, 0x7FCBC3745B843188ULL, 0x0D3E6D27A3B8133EULL, 
            0x0BB742BBFFE37E9FULL, 0xA586DC19D448AB2BULL, 0x5DBF8B29DE9F2FFAULL, 0xA35B94ADDFFA1123ULL
        },
        {
            0xE61B894B2D4A1C50ULL, 0xDB5669D26F1FEDC1ULL, 0xA17B8D3BC25290C1ULL, 0x5C5118B0BCA75E9CULL, 
            0x81E4F1ECEE3F44F0ULL, 0x8D9C36A29FF85641ULL, 0xF3B7E546590C679AULL, 0x28D1D60F4A70F775ULL, 
            0x243711BD8AA85AA9ULL, 0xDC933999927431F6ULL, 0x637A07BF05CAAB49ULL, 0xA91DA843E26B44AEULL, 
            0x407261C172F47944ULL, 0x551B3F3F59CAB8CBULL, 0x8A5D3840734BB130ULL, 0xC7DA73904B42169EULL, 
            0x14B360633C8AC8A1ULL, 0xA4BE26E2BBA16BA2ULL, 0x155D98731B0927DFULL, 0x3F05E67B63662501ULL, 
            0xF7EA865D7A5D9E9BULL, 0x5B212D18FB08F581ULL, 0x3381F861EFFE7F50ULL, 0x9CDCB2EDB2E4D42AULL, 
            0x96EA8BFEB290B522ULL, 0x4819A48F77B1B58DULL, 0x773AB721533B6F7FULL, 0xAA328BA25E5D68CCULL, 
            0xCCC93F3B49FC71ABULL, 0x354263F832D8E8E1ULL, 0x5B20CAF286C18E82ULL, 0x10962E2E48B2D0CCULL
        },
        {
            0x000065979CD774DBULL, 0x8A593C4C59A9FD48ULL, 0x6AA753ECB272764CULL, 0x7C541D48369BACF8ULL, 
            0x60B89646D0B2D55EULL, 0xDF70BFE533017124ULL, 0xDBDD11E32B74CDE6ULL, 0x588E38A43DF17A5FULL, 
            0x1D5BAFC139F55C4BULL, 0x4ED0930718DB06DAULL, 0x7B062696D164DB7CULL, 0xE27D0ABFF95FD5E5ULL, 
            0xAC9E6449DD112F31ULL, 0xF616E6B2EA243803ULL, 0xCAFD0B71C684F370ULL, 0x81E63B7AAB00B55DULL, 
            0xF461862ADB8E8C72ULL, 0x9CB385D4D0A0C382ULL, 0xEB91C44ADB39D62CULL, 0x6108FC3DB1192DD1ULL, 
            0x3A96539B184EA73CULL, 0x1B5408C262AFD6CAULL, 0xEF33EA0F1EBE054BULL, 0xCC1C84235EBD9771ULL, 
            0x0337942573C27875ULL, 0x0AEA3CB74ECA1995ULL, 0xD3AA92076B3588ADULL, 0xE33D031830A622A0ULL, 
            0x66CB6CFE251A09B7ULL, 0xEBC57F417A0D3710ULL, 0x08354A05D2ACD54CULL, 0x346562F514E9076DULL
        },
        {
            0xF520CBBAE59538D1ULL, 0x54DA611A4BA20359ULL, 0x21F9BDCF49E59DA4ULL, 0x31C3BA3EC88DBBD2ULL, 
            0x4CCD59FBC5B10EFEULL, 0x0C62E3D8406D8F02ULL, 0xE3D13A06F0A3113FULL, 0xC2AAFB7FC39CC2B0ULL, 
            0xC4D32E273B9A18EEULL, 0x1B17391F7DF6B009ULL, 0x7F11212EC9BC2DD7ULL, 0x4A58265A143D09DAULL, 
            0xCE5CDE6F0CA38AA1ULL, 0x9DE42210F2D67881ULL, 0x54AE9E2D2B0B0C07ULL, 0xA0D27C98FE49486EULL, 
            0x52896113A6973A60ULL, 0xB358F1886BF4F26DULL, 0xB35A81CDEEA06D39ULL, 0x1DFAC145C9FDDEE8ULL, 
            0x3AD1182FEED9E424ULL, 0x2D96F92D674A6909ULL, 0x711E7672DE0108F5ULL, 0x30D8C0665A8ACE57ULL, 
            0x7E5A027E9C7E6345ULL, 0x30F84B51EF613CECULL, 0xA419D73BD86C9F42ULL, 0x1ACDB3D232F9E7C6ULL, 
            0xD9B8ADFB33A13F8AULL, 0x325F4E1BBD28132FULL, 0x7B570DAB234AA74BULL, 0x2FBFB26F9BD6F188ULL
        },
        {
            0x1967BDBD70F1B42DULL, 0xC5F7006AFC5D7268ULL, 0x06E76569AB5D8ED4ULL, 0xF364A0C2EFCB5E67ULL, 
            0xDD8C0E3B996DF530ULL, 0x86D7C41F8F7DD4EFULL, 0xBFA0B1009728C146ULL, 0xAA66A4A899E61C47ULL, 
            0x9124CCFE8EAEEEDDULL, 0xDC9DAC62AD58AE1EULL, 0xD171C838110C558FULL, 0x24C18CCB2871CFF4ULL, 
            0x6675CD12A0CD9034ULL, 0xA23972AFF3F625C5ULL, 0x955663EBA2E1B70FULL, 0x203218B5E6400141ULL, 
            0xCC15133664504798ULL, 0x1D3F80E839A3B13EULL, 0x638751CF57CC3675ULL, 0x8C5936C74F93D79EULL, 
            0x25C3B285301B2037ULL, 0xDD9DEC6FF3027E6FULL, 0xBF91A9B55BEE1186ULL, 0xCCD9F32785DC4368ULL, 
            0x53207F4E7CC951C4ULL, 0x55C9E14003D6D2BFULL, 0x757FD8D11958F213ULL, 0x2A29C1C61E9C0AC6ULL, 
            0x6669BA3AEEDB2990ULL, 0x3FE1529A5ED96511ULL, 0xD9CD8740800E1EEAULL, 0xA365AB196509780DULL
        }
    },
    {
        {
            0xAF2C609B137A6EC1ULL, 0x89EEA7E63DFA1A3EULL, 0x90C6E1FB80E203B8ULL, 0x5A14A799D48C5A30ULL, 
            0x2550F3D1C8FE8EE2ULL, 0xE3A1E3C3A11D79D9ULL, 0x7377F1B37472A58BULL, 0xA1FC10C29754B028ULL, 
            0x2CF5A5E3240BDF0EULL, 0x858AA19CC515D679ULL, 0xBD26C6DB49FF10A5ULL, 0xA74BB840DEB17AE2ULL, 
            0xA49141DC11A1F4A5ULL, 0x80D2ABB3C132656AULL, 0x3013A675E56BD4E8ULL, 0x41A2F440C20E739EULL, 
            0x605D29F9B4F377A7ULL, 0x5C2D201DC3B96211ULL, 0xBB9A62DA3D64F503ULL, 0x0F2A3B9CBD9A7C88ULL, 
            0x367E52FEA07ACA16ULL, 0x5E0C1D89BF15D427ULL, 0xE108B816A5EF4DF9ULL, 0x2D68695B55A50149ULL, 
            0x6B64E3959989582CULL, 0xA9A5D75A1D61FB58ULL, 0xEE2E4E1E5C9435DDULL, 0x88A4618089D97F1FULL, 
            0xBF4688A58F45A3F6ULL, 0x6AD21DC290129649ULL, 0x61BD01130F5966D8ULL, 0x607D3C5F49707DF3ULL
        },
        {
            0x0FADABA11AAA5ABAULL, 0x1B48189CCF2C1A17ULL, 0xCB7C31105B7B36A6ULL, 0x2939AE42A6254841ULL, 
            0xC93F110B5BF4759DULL, 0x40961EFF636002A5ULL, 0xD69297F4DC60AF73ULL, 0x9CDBAF1C6A44B5F5ULL, 
            0xCBCB25DA2A7F0342ULL, 0x7823A92DD18683ACULL, 0x58AEFDD331AC58D3ULL, 0x3497DA025D674413ULL, 
            0x3D12D122F1AE3E77ULL, 0x9324B6DF122A9EFBULL, 0xA0A1BCDFA3CCAE4AULL, 0x889DCE0B38D17BD3ULL, 
            0xFDFD28635BFED87CULL, 0x71D3BE5EBC96F8ADULL, 0xE3E4B338D5AF055FULL, 0x0859A8CD93A8100EULL, 
            0xF6D2A0A798789475ULL, 0x4B99DE3ECB1EFD21ULL, 0x755D0BBA48C90B93ULL, 0x90FF74BA98CEC0F9ULL, 
            0xA9870603C462EC2FULL, 0xD17630A093E139F5ULL, 0x12C75EAAD177A71CULL, 0x74EABDE1D34F73BEULL, 
            0xB0644203BCB70500ULL, 0x6F2EC56F9B1FAB91ULL, 0x4AB05C9450A0A94CULL, 0x219ECF6980B8FDD1ULL
        },
        {
            0x3088B712F20F0680ULL, 0x0508047A0ADEA601ULL, 0xAE8EAC12CCA5C314ULL, 0x7A74C79912EDBD0AULL, 
            0xF6F652515C26CED6ULL, 0xD4DF7BA26CC37F0BULL, 0x9156DD6509D671EFULL, 0x9099A9656598472CULL, 
            0x9DAEB86C1AC74438ULL, 0x4877F060D7FA8B68ULL, 0x2B8A3ABC6404B15FULL, 0xD56FA25B4EF3916DULL, 
            0x233E6C00FB02A6BBULL, 0x7D8259AAA7434142ULL, 0x75A34E5901D9C37CULL, 0x24896A80359DC7B2ULL, 
            0x853B54F14EB244D6ULL, 0xEF1C4488A16CA435ULL, 0xBED636439453BC57ULL, 0xC886236E3AC65C49ULL, 
            0x8D5EC9DAD6E29BD3ULL, 0xCAD1F24FA77BC718ULL, 0x632341D176CD5350ULL, 0x3ADB936D9CCAE228ULL, 
            0xA2333AD69669D625ULL, 0x4B2DA63CA77FA1E3ULL, 0x5EE717B09373FE84ULL, 0x9F95A7BEB1732DC8ULL, 
            0xD70E238611952D3EULL, 0x663ABD5D3F8CDC61ULL, 0x2BEB7AE290ED82FFULL, 0x316F238AAECD3995ULL
        },
        {
            0x5209C3FE9BAD0B8BULL, 0xFF225A8A1D98DC1FULL, 0xA59B5B259D87D895ULL, 0x89B75D28F2CB8593ULL, 
            0x7B9E5A814920EFD6ULL, 0x53B6899BB7FD926EULL, 0x9FAC7409E96D4509ULL, 0x74DB65A87DBAD09CULL, 
            0xF0537BCF49BDE834ULL, 0x7D31C5E6B1E2C251ULL, 0x064B8B2938088748ULL, 0xA684E45F560EF129ULL, 
            0xFE83B60A3D72814BULL, 0x89540B108762B1B4ULL, 0x24034B470780C577ULL, 0xC16E554BBCE0F9B0ULL, 
            0xA0ADCA297A9295DCULL, 0xDF868699D04FEFFAULL, 0xD49E5BA4FC93E2EDULL, 0x15B8CD11DB72BC5CULL, 
            0x4FFC162F4E2DA514ULL, 0xAEFE81B9510C2470ULL, 0x83628B15770EDE0BULL, 0x631D684505C47438ULL, 
            0xE891256BA2B66785ULL, 0xDE3DD0B807EF7C6FULL, 0x272E5D11D8FC7127ULL, 0x2D3D38CE3BB29020ULL, 
            0x3F328B5C2246BEBFULL, 0x3D5EFE97D86063B8ULL, 0xC6EB043875FF9639ULL, 0xCDE43BF28DBA493DULL
        },
        {
            0x036A41DE4C7B0ED9ULL, 0xDF28F5BF72EFF92BULL, 0xAB0D6C485F5BCE80ULL, 0x4EC876B73903D733ULL, 
            0xB50E11D1A5FE6E91ULL, 0xD53D67F6D2861684ULL, 0xADDEB8B22ED77392ULL, 0x5FB74735D422C787ULL, 
            0xAC895BEDC79FD328ULL, 0x6EE52A91E0C99825ULL, 0x8C3BF76B7B25172AULL, 0x5A07C7C96E335DB0ULL, 
            0x79590CAEFD3E5799ULL, 0x3212EB8B1DC8D8E5ULL, 0xD9C565C92BF677DDULL, 0xE3F159D8BEEA362BULL, 
            0xCDE67F975883E2D8ULL, 0x051F86B700A4F3A5ULL, 0xE2377D9594C6A5EAULL, 0xF20F227CE56DA5DBULL, 
            0xEC8D01117968E4F4ULL, 0x89672A7B4AED0378ULL, 0x14B541478ED183DEULL, 0xBCF9CEB3CCD0C46BULL, 
            0x54A7D24A4155C19FULL, 0x534BF34F41E4F2B1ULL, 0x1E0E3ED50D2A7576ULL, 0xC5F2CB3ADDBFE50AULL, 
            0xCFB7392276B5D08CULL, 0x59BE3564F1247E80ULL, 0xE9F67623908872D1ULL, 0x356F4E5EDBE588D9ULL
        },
        {
            0x5590AFE1FA863069ULL, 0x90AB23DA659ECCE2ULL, 0x19A772A2FF4D6A36ULL, 0xA636E33A954D1F85ULL, 
            0x52AF9698A4AA9922ULL, 0x8049614E76D1CB71ULL, 0x8A268FEDF71BC2A8ULL, 0x4DD039BE932AC4A9ULL, 
            0x2AFCEB6FDC8B7865ULL, 0x2B31E7B26191094DULL, 0xD2825AFFCF87F680ULL, 0x7190BA484F81A505ULL, 
            0x02EA782A5A420757ULL, 0xDDD614AA1212E098ULL, 0x40E38E0DA7177740ULL, 0x0968A9DB9E2DAB7CULL, 
            0x4A48C333264EE136ULL, 0xCDD4DEC24403FCA5ULL, 0x477450A9E87BCC71ULL, 0xE1FFEF9FAB541DE7ULL, 
            0x02AD4CC5CA370CCBULL, 0xE08904F63A1ABF07ULL, 0x3C9260D1A5AD7CD6ULL, 0xB753FCB4D0422AEBULL, 
            0x417095A6C30CBFC4ULL, 0xCFB0A5507BAC1137ULL, 0xFB9F1ECFF472F203ULL, 0x5E19691109ED67A5ULL, 
            0x2E16338139FE05FCULL, 0x3F444F4ED73CF50CULL, 0x22BD013DCAF74B5BULL, 0xBC09FBDF8A0ECD39ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Ankaa::kPhaseAConstants = {
    0xA25E0C1D51C98E26ULL,
    0x9C5103987B045001ULL,
    0x8CCA0A28C4ED2196ULL,
    0xA25E0C1D51C98E26ULL,
    0x9C5103987B045001ULL,
    0x8CCA0A28C4ED2196ULL,
    0xEB8FA7B56BAF362DULL,
    0xE7D12D9E0C4C109BULL,
    0x53,
    0xDB,
    0x99,
    0xE8,
    0x9E,
    0x59,
    0x4A,
    0x65
};

const TwistDomainSaltSet TwistExpander_Ankaa::kPhaseBSalts = {
    {
        {
            0xACA77D6904EECBFEULL, 0xC931410FF8F9AA42ULL, 0x4EAA8DCD83E6056BULL, 0x2D8DBD7F5F4383CFULL, 
            0xBECA08BEC5A5299BULL, 0xD3DBC9329C0E8BAAULL, 0x78540226DC4632A6ULL, 0x671BE9A16E41D009ULL, 
            0xB28EEC4E591743D4ULL, 0x16F13285B8CE95E1ULL, 0x7818D4A611EB9ACEULL, 0x368FC4117E5F2B7BULL, 
            0xC26DDAEAACFFB1C4ULL, 0x82DA42063C373E05ULL, 0xB817D1D2FB5BA290ULL, 0xFD168B041C302834ULL, 
            0x87D7CF25C7E32F08ULL, 0x5DA1F740FD5DA77CULL, 0x8619F788C6A37DD2ULL, 0xF55EE5B431DEEA54ULL, 
            0x853868CACD1E66E9ULL, 0x408BA48C640721BAULL, 0x0079EB823B2B128CULL, 0xF12A0F9EFB66426CULL, 
            0xDCBBCB83AF78BE93ULL, 0x2B86CD518A06BCD3ULL, 0x91BC823F4FCE7262ULL, 0xBCD93E0789FEE29BULL, 
            0x0224785AA7E6A983ULL, 0x7B1AA24FC2C66150ULL, 0x32EBB69387A5DBD3ULL, 0x5F4E04D3E3C4400BULL
        },
        {
            0x5AB0E7614EDD8878ULL, 0xD0BBAA8EB519402DULL, 0xF89677E0BF692DC0ULL, 0xDF8608E58F6CCB46ULL, 
            0x08C08F64373B2CF4ULL, 0x1684010D52E7471FULL, 0x6CC524D7D14600FAULL, 0x49CB79846EC512BBULL, 
            0x99BC919643B3D984ULL, 0xE4F1F98F2314AB5BULL, 0xE3F667FCC0EC7455ULL, 0x3FFD14BB729073B4ULL, 
            0x3C51A82E32E8CFCEULL, 0x891AA66E5271947CULL, 0x9003571D01D2A61AULL, 0x0EF3BB71A946D267ULL, 
            0x50D241CCF5328820ULL, 0x0839327B810DFE2EULL, 0x25701E1E8AA30486ULL, 0x27C9EBFF39495647ULL, 
            0x571CCD143F0F50FEULL, 0xAF49ADBA090F33C0ULL, 0xBBEE9415CEBA70C9ULL, 0xF13E5B5F1533E677ULL, 
            0x55A9FC3F20302157ULL, 0xE2F760F94F96D9FCULL, 0xEAE1767852AB99F1ULL, 0x7EEBD0AC0E391507ULL, 
            0x66FD5C4D10D7F0ECULL, 0xD9A6AAFF9294540FULL, 0x8B21327EEE841662ULL, 0x290BD592AF3F91BEULL
        },
        {
            0x573A2078323028F8ULL, 0x18E153E0876B19A5ULL, 0x8B79CD60EF5D81C1ULL, 0x575782A4A867B25DULL, 
            0x0967E4D6E58CC50DULL, 0x8565EA20C0699A5DULL, 0x541BDFA7C0082DD5ULL, 0xEE6D8D4244602478ULL, 
            0x177FA3C9A8FC526CULL, 0x3254C4AF0D3298D2ULL, 0x2CC26078D8E1B265ULL, 0x5CF61BC67E1091ACULL, 
            0x2BA51811EE6824DCULL, 0xCE00D120DAA7590DULL, 0x6A4D521AF8BE32EFULL, 0xD3894562C1FB5AE8ULL, 
            0xE479F24E1309DDDEULL, 0x17F50F4BEAA53A88ULL, 0xF463D262D77D8AAFULL, 0xC68A28A1F9D63632ULL, 
            0xDE721EE2EB9AC50BULL, 0x63AA2E135D5FA61CULL, 0x60EFE863E180650EULL, 0xF3BF9CBCC57BA5DAULL, 
            0x410A4E2F1541946CULL, 0xCAFE2BC83FE6E519ULL, 0x105FF33FA7F33B0BULL, 0xB4C3A931F82F4DADULL, 
            0x8B7EE6D8CD696A95ULL, 0xD27942B897265FE0ULL, 0x3C6AA9273F7CE733ULL, 0x4C9B171B0A2F33FAULL
        },
        {
            0xD60329997042956FULL, 0xF86D2CE679E283FBULL, 0xE5BCD297AA4BE2FCULL, 0x39D3B34F269C0E3DULL, 
            0x8ACC030C1CD26CFCULL, 0x3B7BED486FFA61C9ULL, 0x6CDE6FE68F3296D8ULL, 0xAC310084F7071B69ULL, 
            0x6971522EC6AE729EULL, 0x93CBF81834731BD9ULL, 0x04937196EB6A6474ULL, 0x4E47C1BFF1A72507ULL, 
            0x60770B89B8DDB280ULL, 0xD7ABAD8DDFD1FF55ULL, 0xEFACC884844D9DE6ULL, 0xD876F48045C678A9ULL, 
            0xE33EAB3E51A4F292ULL, 0x20B967B09B37F287ULL, 0xE49D4241A19A2F3BULL, 0x14BA074C2B7DE56AULL, 
            0xB43C2F942BA0AA21ULL, 0xAEBCB5DF5EEA0291ULL, 0xB4E99E04821C72BEULL, 0xC440978C35BC42C9ULL, 
            0x90E3C02C8769AE03ULL, 0x06E5110452E0FCAFULL, 0x0185697497FB3577ULL, 0x1639DB00F323282FULL, 
            0xA0808A12CE0E22E4ULL, 0x9112DA4B134B909DULL, 0x2D398FE124EA2E3EULL, 0xA91305ECD4B22F6BULL
        },
        {
            0xE53A37E8B175DC71ULL, 0x788DDB71D3F58962ULL, 0x3036FC278DFCA155ULL, 0xAB4B6295060717D5ULL, 
            0x79AA85AC60EAA26EULL, 0xE0D0CC03EAEBC598ULL, 0x568751AE2AB93CE6ULL, 0xC8D2BEE90847EAEDULL, 
            0xBD7C6F926C1418D6ULL, 0xF5CF1B87CF037BEAULL, 0x5149E48A5464EC3BULL, 0x3963510A33011806ULL, 
            0xD85343ED4A88BE9EULL, 0x5A946EB38696CF45ULL, 0x805BAD75AC572BD2ULL, 0x41C86AB19EBF0C91ULL, 
            0x05ED58CCFB6C9069ULL, 0x366CB39F6B8B2FA0ULL, 0xBCEE1BC5C21A9494ULL, 0xAA409D611B23633BULL, 
            0x443BB0ED73CDD6BDULL, 0x7968A6D7D759A092ULL, 0x86A5237DB7AAA0A4ULL, 0xB48FD9660FC146DCULL, 
            0xCA20E26B43518C13ULL, 0x737E6F937CF9741AULL, 0xB77351B3D19A682BULL, 0x195422B2D45EC65AULL, 
            0x2ED45DAE0EE163A2ULL, 0x052CC9C40AFC79C3ULL, 0x31ED9603E17ADF41ULL, 0xB89D3FA858B4EC42ULL
        },
        {
            0x66F4EA106769FCA2ULL, 0xD30FB38F3A877BECULL, 0x267263C28FC87560ULL, 0x15D22748255FF354ULL, 
            0xD41658F52329896CULL, 0x62DD9BCAA7C7E879ULL, 0x4EEF4FA263570D70ULL, 0xBE4E091046106D94ULL, 
            0xDE3F3A49BA0EA584ULL, 0x680F97334D7C1E66ULL, 0x1E9861C160021B54ULL, 0xA514EDBBAFAC967FULL, 
            0x4098D866623015BCULL, 0xA8B0568E6FB48D34ULL, 0x9199801AB62C5E63ULL, 0x5C30D44814D6F880ULL, 
            0xFBB6824268AA7287ULL, 0x4582EE05F679DB1FULL, 0x9741063D1B21E738ULL, 0xF0D616050485B857ULL, 
            0x8DB81D85E319925CULL, 0x3499D93BD69F1B07ULL, 0xB8347B7544983928ULL, 0x7C36D86C3039D4B5ULL, 
            0xB1C24AC28C0F31D1ULL, 0x596E73DA2A89A627ULL, 0x36E9C22F2B10F2AAULL, 0x4A8BC23A61484AE8ULL, 
            0x55EE211CA2164B3BULL, 0xB8F8A258C20434A9ULL, 0x8E2A40BE5EF4ED0AULL, 0xB42FF65970B72796ULL
        }
    },
    {
        {
            0x7571F1AA753E618FULL, 0x99A318C5D46F165DULL, 0xB0EF2FE32D0E9F59ULL, 0x4A23784022C6EA00ULL, 
            0xBE7C467C7FD2FCD7ULL, 0x0E5C2E8E690B5C6AULL, 0x24E02F4BF992E9F0ULL, 0xD02E09EA7AD8D85EULL, 
            0xB0D18567EACAFB05ULL, 0xA7325F7725EA8FCDULL, 0x7304819CBE25FF38ULL, 0x7C60438517AF2041ULL, 
            0x90950449A7933448ULL, 0x37FB72CE1AE61DE9ULL, 0xA2D0346428C63EDAULL, 0x57AC54CEEC834A89ULL, 
            0x695B3E20372C8AE2ULL, 0xD0A1ED0E84EF39A8ULL, 0x0AAD2FBEFDFDD6EBULL, 0x224CD2B3EF47961AULL, 
            0xC9BFE03DDD51C50AULL, 0x99AAD0F85EECFF8CULL, 0xE2788CB69D32D4FAULL, 0x723583738C5A8A86ULL, 
            0x0DD4F498D20C3ACBULL, 0x36776C8703D19D78ULL, 0x916AFE80741BD0C8ULL, 0x9EF661C729AF4B1FULL, 
            0x839A2684C52A12A0ULL, 0x2FCC8CFF13F10465ULL, 0x10F202C61ADD1876ULL, 0xF80958ED8475831AULL
        },
        {
            0xA302494A9425C186ULL, 0x7DBC934935713E77ULL, 0x88241D5F02F66E09ULL, 0xBFCFAC187A2707A6ULL, 
            0xA7DDD832A79B810BULL, 0x4BF5C4A23612C636ULL, 0x8C85B19B9E109A03ULL, 0xC18BE47FB9551E7EULL, 
            0x968847229045D368ULL, 0x50E10BD8708E3AC4ULL, 0x3A9DD9000BDE7EC8ULL, 0x3D9F9C972B847BC8ULL, 
            0x0F153333F40B7BB4ULL, 0xDFF5826421AC972AULL, 0x0D0546926DA43D11ULL, 0x700EA5185AE78EFDULL, 
            0xE7FD8FDAEEBCCFBBULL, 0x75CCB038275F3BACULL, 0x14815F78D208ED14ULL, 0x7627E1F63DB9335FULL, 
            0x570CEEB81D6E7310ULL, 0xD3B11F63E154B6F6ULL, 0xE65384FD544A9BB7ULL, 0x74E4BAA3DCEC47A6ULL, 
            0xBD9939BA7BA5CC24ULL, 0xBBDE446848B0D844ULL, 0x6B5AF3DC6D2B524EULL, 0x0E18ACC565FBF917ULL, 
            0x1F286E1A2521C113ULL, 0xC171BAB0DCCDBA95ULL, 0x0EC03E8992147FB6ULL, 0x67CA5C1DD2CE8E06ULL
        },
        {
            0xF8D3755A474E6E90ULL, 0xA086D9AE97B0B758ULL, 0x044EFF55E754726EULL, 0x9FCA9D0289306DE5ULL, 
            0xF429CF9AC80D8CE9ULL, 0x8CAC7B197DED05F1ULL, 0x3A914DE88F88D621ULL, 0x6E8E12D62F425233ULL, 
            0xF6FE0A3073F9ED4EULL, 0x3058D6DCA1B06875ULL, 0xB7985AE15EFE64B2ULL, 0x5F752989BE0C1700ULL, 
            0x2B9C0A0FE23DFCE6ULL, 0x7017086BCE1F8FB6ULL, 0xA9356F0671770ABDULL, 0x920FAD9AFDAA5661ULL, 
            0xF1279ACEB6574EA3ULL, 0x22DD608A6D82C7E0ULL, 0xF79D37089DE970E1ULL, 0x77F21CD1250CD4C0ULL, 
            0x59AD4B7E99B4C0F6ULL, 0xDA37FA9C345A4687ULL, 0x99DDCBEA9434E2D1ULL, 0x34B9B90646543ADFULL, 
            0x9D56E600B016B906ULL, 0x21909DD4A38CA1EEULL, 0xA147BFC0D2D05C69ULL, 0xA64C47972CE098BDULL, 
            0x1EF3DF20E443118AULL, 0x39D2886BC568EF62ULL, 0xBAFB69A727A38490ULL, 0x3C8FA7C63224D8E1ULL
        },
        {
            0x35D4B9A6D7E6D4B5ULL, 0x20D56C8D4538F593ULL, 0x9FAF9C66EA6A203AULL, 0xA60CAF75A089202CULL, 
            0x6D862443ED1327D5ULL, 0x67016B0E84AC0309ULL, 0xDC71832D8488903CULL, 0x8F95FD6CF3B798DAULL, 
            0xCE249758BBCA19E8ULL, 0xB7B29A618F20DE4BULL, 0x5B9E9ED7EABECF6EULL, 0xF1C244F69D05B533ULL, 
            0xBCB5BD4F2DD541D2ULL, 0x466B24C0858D541DULL, 0xCAF4DC6BEBF16CFBULL, 0xDDFA3B6C2C581A6BULL, 
            0x6F544B3620D702F3ULL, 0x5A615369DA50A8A9ULL, 0xA81E76DDEAE6F0FAULL, 0x9A068D7AFB667E02ULL, 
            0x124F68031A1D76A1ULL, 0xAAE81E95F8385B2CULL, 0xDBECD4F01D5B04CBULL, 0x44D040B34D28779BULL, 
            0x755E6D36B2F9970FULL, 0x1E6A2E2D5BE66A3DULL, 0x45848A10B8AECDBEULL, 0xE518B45262C1F8AEULL, 
            0x0030C916A8217AC4ULL, 0x2ECCB7AC50DA1A98ULL, 0x3D745393B3E3FB77ULL, 0x6B38F7123C8376B2ULL
        },
        {
            0x58755FE07D512FB7ULL, 0xB1512CF4D67F6462ULL, 0x752BF9B964483EADULL, 0x76088BB828DCC2F4ULL, 
            0x1802E4F58A6F7AD0ULL, 0x654F89E1EB0C7556ULL, 0x54785901D41AE06AULL, 0xB2288B37C47B7A71ULL, 
            0x104F4F639272F1ECULL, 0x3BDC51BFB6777DD3ULL, 0x7A9FC0A32F37FAABULL, 0xEC3DFE10D1A47E80ULL, 
            0x2D590785ABDB3AB6ULL, 0x21FF9C0FDA2D31C0ULL, 0x6E4151AB1C32C80FULL, 0xC24783B269B31B4DULL, 
            0x24C07A2B88C73524ULL, 0xFB494579CF7EDD2DULL, 0x640CA9653F17C3E3ULL, 0xD8222E51AB3DE216ULL, 
            0xFA821BD7300862AFULL, 0x2ED59FCA88B293ECULL, 0x2516FB0522DB94FAULL, 0x30AF3600E9361612ULL, 
            0x8C035F091319FAC3ULL, 0xC216AC1532CE97BAULL, 0xADACCA0D8E5A1C48ULL, 0x07C51912E5CE57E5ULL, 
            0x1A454BA06439DD0AULL, 0x68EFB4278D6B764BULL, 0x9019E7E9DF39B9F2ULL, 0x765101F06F81D8ACULL
        },
        {
            0x9645AC52ECF40362ULL, 0x717FAD1FE2D47EBFULL, 0x37726C93E1CA53F0ULL, 0x588AAE03C6CE8E2DULL, 
            0xACFE902B75C10219ULL, 0x7F80ECE2B36F4AE1ULL, 0x34B1C64960A45945ULL, 0x07380132B954105DULL, 
            0x7D6E5A2EA15BA501ULL, 0x18C4CE880E12CB8CULL, 0x6A5394A742CD17A5ULL, 0x15B21C4912E71ED9ULL, 
            0x20D50EE5D686A5FAULL, 0x70837CAC56F61B54ULL, 0x4C3783FCA19E0801ULL, 0xF8E9D7E8E1FB4E21ULL, 
            0xB9A30013F952299BULL, 0x16D06BF87DA11CCBULL, 0x9696412668CD0A92ULL, 0x7177B03C7DB97B44ULL, 
            0x49886AD2F88F5AF8ULL, 0x8A233FC62684DC76ULL, 0x699E3BEB27E03AF0ULL, 0x822D018E29A6CA16ULL, 
            0x4EA5F81AD83612BBULL, 0xB66F8F2D78F0E9DAULL, 0xBFF17C1BFA1723EFULL, 0x64899A7F52C79A75ULL, 
            0x0BBEAB0F3CACFCDBULL, 0x0A26D9219B4ED19DULL, 0x0C821FDE9AC7D04AULL, 0xE472113CEB3E558DULL
        }
    },
    {
        {
            0x6D96D15E8DE6023AULL, 0x3AB8E791350F460DULL, 0x398638F7C60117ECULL, 0x2E81B1BBE5BBC35EULL, 
            0x1675FD53C2127BBFULL, 0xFFC1AB2CB11A524CULL, 0x21AC606C8F7F7A19ULL, 0x5FD5065A93AA95BAULL, 
            0xF2BC707D579E8FD0ULL, 0x3C46AFB1CD9AF923ULL, 0xAC7FBD1D7283F2F0ULL, 0xB2B9047A6D59EED0ULL, 
            0x140A702ED224868EULL, 0x9F4A63FD2D383D58ULL, 0x439AAF961CBEDD72ULL, 0x8E9B59C3B52515D3ULL, 
            0xC34F1CAADCCCB551ULL, 0x1677BCBA126608B9ULL, 0x8D84C722F254D195ULL, 0x90560879BB838EF7ULL, 
            0x64C65D26337918C5ULL, 0x80D70550382D33A7ULL, 0xE8BFDAB4D305F741ULL, 0x64DE5366C63EBD6EULL, 
            0x75ED045A7B1B1447ULL, 0x374A49B7AD5AFE2DULL, 0xD0E0D00FF26CCD03ULL, 0x9DA02EA5471CB06CULL, 
            0x7C05A1C2CF236340ULL, 0x6C4C4201586EF76FULL, 0x369B4DCF87ED6DA9ULL, 0x56BAC2EFC6E4FF0FULL
        },
        {
            0x80B5E20CDF9E0D7CULL, 0x5EC9BCECE31E7ABCULL, 0xB3351506B5095F4EULL, 0x73DA5A80D6271245ULL, 
            0xBB1982BE8F38C20DULL, 0xDB6F3AFD49F8DD6EULL, 0x64C6F87C56237C74ULL, 0x0D9E42E4B4B49A2AULL, 
            0x6C07A55D0C79CA81ULL, 0xD0AA56FEBE576B53ULL, 0x80EB66F7B7983F6DULL, 0xC013DAE28C0C0C48ULL, 
            0xF324ABA50904F405ULL, 0xDE0B8B5B4F4B978DULL, 0x2556B0712EB6E787ULL, 0xD01E8A405DF09C54ULL, 
            0x433995F50C7D3C54ULL, 0x1C99245AC9EDAB1BULL, 0xF4DA7CCB919202C5ULL, 0x04020881833DBEE8ULL, 
            0x92AD7B989A902438ULL, 0x0038155EE12FA6ADULL, 0xAD55BC5501F2C3BDULL, 0x9DACACF28F98935FULL, 
            0xAE57F575E78737E1ULL, 0x97826837F75E0415ULL, 0x0971EA7951D55115ULL, 0x71A6A995A8D596A5ULL, 
            0x2FF4BCB55D5A33B3ULL, 0xE825335720D2FFBDULL, 0x0FBE219BE216A1DFULL, 0xDC2CF8E388684E2DULL
        },
        {
            0x2710995B34F9AD30ULL, 0xED8A773CEA5C196FULL, 0xE01B7C7825B24828ULL, 0xAD3BABE38675B36CULL, 
            0x5AEB06F6EA2C2AF2ULL, 0xDF7776FCE41CCFBCULL, 0xAD9F212EEA3A1B19ULL, 0xD5A1ED4039C1F523ULL, 
            0x7D435F9892AC7427ULL, 0x1D6C2855088EF03DULL, 0xE0175CC39DD2EBE5ULL, 0xAF16542DE4FCDC80ULL, 
            0x6159DD795552154CULL, 0x2266F11D20E6312DULL, 0x19324AE5FE15EC05ULL, 0xDA59329A8992393BULL, 
            0xB3FCA24FC9673A9FULL, 0xBF7F83A96AD0FE1FULL, 0x78747A7F56174591ULL, 0x2209C692E5D81EE0ULL, 
            0x7D1CF47555AFA190ULL, 0xACD4C0CE9AACAE9EULL, 0xE0CA4A587DAAA25DULL, 0xC77ADDAF844036CFULL, 
            0xF38A26945A9DED9BULL, 0xA25E25AEBBEF89BBULL, 0xFF6B585AE72F6A9DULL, 0x283CA0E298C7A2F1ULL, 
            0x1AF6B490CEEB2A2DULL, 0x19B5058ABEAF66D9ULL, 0x658D544765D82BD1ULL, 0xDD46D88B7DCDD910ULL
        },
        {
            0xF32DF0238C9D13F9ULL, 0x0D3CA88796E10A94ULL, 0x5D34632BA9577C89ULL, 0x4D185359330362F5ULL, 
            0x8152540F6F7511AAULL, 0x7E2A8B28D8038DEDULL, 0xF2908FC25C6500EDULL, 0xDF3F82E82DBC9FCCULL, 
            0x650F342A78F823FCULL, 0xB90160248E25BFA0ULL, 0xE48F47907E197AACULL, 0xADF394F4B6069C71ULL, 
            0xCB4DCE91DC48BB73ULL, 0xAECEF52F45898EEAULL, 0x695C808CF98AF779ULL, 0x830DA237EBE25396ULL, 
            0x2BC123573FA3F089ULL, 0xCB71BA696F6E7268ULL, 0x06F3D43577AA0ADFULL, 0x34599ED8B52640E2ULL, 
            0x46EFCA0174EF202BULL, 0x878063F7CA90AB9AULL, 0xF457CF6FAC311A75ULL, 0x519247EEB82F3F35ULL, 
            0x38EDF205969B6B75ULL, 0x6612B34B2A07C75EULL, 0xE10221E1E20FAE8DULL, 0xF19C36D6786BA6EEULL, 
            0x47C82782D71EBDF3ULL, 0xCD149437F832B242ULL, 0x89DBFEED6D69CFB9ULL, 0x9C070639257C9604ULL
        },
        {
            0x10B0E0B414D19E3AULL, 0xD0190262A8172EFAULL, 0x529C141E400DFC99ULL, 0x14FAC93ADBF012A2ULL, 
            0xD00479D7680EA270ULL, 0xB5088475D8C94003ULL, 0x43B9A8A8BA51C9E0ULL, 0x808AA21851C0B9C2ULL, 
            0x259C56CDBCFBB756ULL, 0x086A4B37BDFFCA54ULL, 0x3758F89B34E41F54ULL, 0xEF58E1F0651D88A7ULL, 
            0xEDC1831EE160E70DULL, 0x8624D93B45AAFCFFULL, 0x0DF0C52B1F6F007EULL, 0x5D7D1C3D38C1BA69ULL, 
            0x188E4D7F5F9ECDACULL, 0x6F6AA9C0CF3DC700ULL, 0x95C039250A972331ULL, 0x84BFB061866726F1ULL, 
            0xA0C3FD0900342828ULL, 0x3961D3970A2DB613ULL, 0x4ABA5BE467D5580CULL, 0xEF598C20079AA4E5ULL, 
            0x2A3E770479D9D1ABULL, 0xBCD50253F9648DDFULL, 0x5FA1CAF2E989816BULL, 0x880522DE9E855AF2ULL, 
            0xE1D16FAF8773EE76ULL, 0x79999A808B9A11FDULL, 0xFCDCD8DC20AAAABEULL, 0xFE4E409B8DF6AC92ULL
        },
        {
            0x81AFA7C1228652B2ULL, 0x1BC828B7BA7E95CAULL, 0x90A9A073B8CAB737ULL, 0xE481006282223E5EULL, 
            0x4C68182133FC0522ULL, 0x672779E5AE94DF22ULL, 0x335E359EB0F3097FULL, 0x45DF53D490C24934ULL, 
            0x7E035C927C7A93CDULL, 0x87F5B5142DB038B4ULL, 0x5426ACDAA84741E7ULL, 0x9EA324881B805795ULL, 
            0x7AC37C34DBD9829FULL, 0x659EB0C76DA5B16CULL, 0x93A9CFE5BDFC8D25ULL, 0x1C5431EDDFC7A3F0ULL, 
            0x3931427A8A3EB9CCULL, 0x9FD75793AB32D2A5ULL, 0x848CE55DE9B81E94ULL, 0x54B1F219ED90F404ULL, 
            0x30BC95FAA39A87CDULL, 0xDE15FE69E824D5F7ULL, 0x4B7AF3E5E9119EFBULL, 0x97B52F8C17B665B8ULL, 
            0x03285D60E45C235BULL, 0xBB6CA30D4375A65EULL, 0x94D1764809DF98A8ULL, 0xB80A0919DDCF8F5EULL, 
            0x59299353F01A93B4ULL, 0xC9E603A5F8F1DAA2ULL, 0x85BC65313212AF40ULL, 0xFC81D998C05FEEF5ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Ankaa::kPhaseBConstants = {
    0xAE2B17F40CC2CBE4ULL,
    0x742E8C6AD98493F7ULL,
    0x1D98C4375570DA70ULL,
    0xAE2B17F40CC2CBE4ULL,
    0x742E8C6AD98493F7ULL,
    0x1D98C4375570DA70ULL,
    0x2E891CDA13C6CCC7ULL,
    0x25AD539D66C97A02ULL,
    0x4E,
    0x97,
    0x14,
    0xAB,
    0x90,
    0x90,
    0xAD,
    0xA2
};

const TwistDomainSaltSet TwistExpander_Ankaa::kPhaseCSalts = {
    {
        {
            0xF8614B4DBCB25F3DULL, 0x16FDBAA1570961D6ULL, 0x445B0E25EF44F164ULL, 0x2A1B09A1A9C36FD8ULL, 
            0x09E4092D6CA5638CULL, 0x9B148C461ABA4571ULL, 0xB93ECF40EEB5DFF5ULL, 0x5FCD899EC6329585ULL, 
            0x7F5E5C729A0158D1ULL, 0x8454C950FD37B899ULL, 0x4D492123BDA2268BULL, 0xAC33BED2AD190EDCULL, 
            0xA2C17C45B23CC63FULL, 0x4C79FE720BE7FD6DULL, 0xE288586DAAB6FE40ULL, 0x0DB5DCE6E408B0FEULL, 
            0x0F1F7E2E0C0EB55AULL, 0xDA83D0AFDE582285ULL, 0xC938EA7F892FFC87ULL, 0x2B6B1482BC3B394FULL, 
            0x08105C8AB79811A4ULL, 0xA361882C38200142ULL, 0x2DF8B4F638ADF735ULL, 0x811F8324B74A3A8DULL, 
            0x78613B230F1BE975ULL, 0x312716906304559CULL, 0xE7EF1E61DB13A814ULL, 0x82C94DFD4C7C4F03ULL, 
            0x6C0674D158E12268ULL, 0x320AAF66F94AF7C1ULL, 0xB0944D8FF5F916B1ULL, 0xC5A9A5B155B95786ULL
        },
        {
            0x4E5EC4C9498656CBULL, 0x64E0F388166B4111ULL, 0xF9059C2CA4FD5702ULL, 0x4BAA6BF0CDF904B6ULL, 
            0xE264594D295290BFULL, 0x4A69F6D2EA1F6873ULL, 0x870DA6E76675A321ULL, 0x9B87ECA7B485C8D5ULL, 
            0xB4941B8023C0467CULL, 0xE673FC014B3CF647ULL, 0x9080C26D0096BBFCULL, 0x06A008400AB7B32BULL, 
            0xB3AE39C18B58D2D6ULL, 0x252018BB96B1AD08ULL, 0x334F8D528F0E2E7EULL, 0x7CA77C685D3AC1BBULL, 
            0x9D5F5EC828D97D5BULL, 0x9B52E7AC57B8B6C1ULL, 0x0CEDA65E33138122ULL, 0xFF3C22FBAEB7982FULL, 
            0xC855DF0E5E40FBEEULL, 0x193935F5C42BA6EDULL, 0xC2A0FFADA60E722CULL, 0xE3606378759C2F73ULL, 
            0xE28F011B1AE9A57BULL, 0x8992DD730B8E4504ULL, 0x47B0DD79376302BEULL, 0x2FB2930007D1DFD4ULL, 
            0x1528C5EA1EAEF50FULL, 0x3CA8F1B6E9CB8483ULL, 0xAA7E8E77913A1BA5ULL, 0x7B118894AE4AE56DULL
        },
        {
            0x082DA8A070B2E0B2ULL, 0x21BD9EB041C490ECULL, 0xF3CAD2DAA061EE20ULL, 0x1F7ED35D8A44749DULL, 
            0x9C4DD090483B3B92ULL, 0x84A80B37B6951845ULL, 0x9D8806C493591829ULL, 0xC1C232327C8E3926ULL, 
            0x2C08295184E58FDBULL, 0x1BB77FC2FC744EFDULL, 0x873395BB64E00DBCULL, 0x73BCE5854271F3C4ULL, 
            0x858452A07FF6D466ULL, 0xAAD5EF81EE29273AULL, 0x4478BAB6C529CB0DULL, 0x28EDDB744201F0CFULL, 
            0xCF488AAAA11BF91CULL, 0x0C48218618C8378AULL, 0x699D60A8658A1FECULL, 0x6CC4452F8EE37E27ULL, 
            0x4861E26231F61363ULL, 0x51B29A6B28B45904ULL, 0x796D51086B4CE2B3ULL, 0xD6EDD4B23795168FULL, 
            0x908E1A69D60A44DBULL, 0xC85956CDA27C5314ULL, 0x183A99F1236A57FCULL, 0x755E9B97DA808B8EULL, 
            0xA0CF1D266249581BULL, 0xD374C5633AF333ABULL, 0x00A32018CD138F6FULL, 0x41B58316B73598FEULL
        },
        {
            0xC026FA83AC2B85ABULL, 0x951A3DA2E0AD2794ULL, 0xA5DE34D90513D72EULL, 0xF382DCB8B90933AFULL, 
            0x54020D22AF20C886ULL, 0xA00DC2E4B9C15348ULL, 0x6A72D488AAEA3CDEULL, 0x936FDFE7D0593315ULL, 
            0x47608665080B00DCULL, 0xE300279FD72B01B9ULL, 0x5C4B87EBB38B17B0ULL, 0x38C84A7649041C1DULL, 
            0xFE7079CFC7B48581ULL, 0x2670520157228DD4ULL, 0x0669F339604ABDD0ULL, 0xEF066938E8CFD720ULL, 
            0xA98FA6B845F34ED5ULL, 0x29C0477C4E483EE0ULL, 0x910969DC2EF48A0AULL, 0x1D020302D4B07BE3ULL, 
            0x016ABA9A7E7EF43DULL, 0xF47DCECBF431F1B2ULL, 0x7685B03E45542FA6ULL, 0xE49504195B3102BFULL, 
            0xD205CEF2A6546704ULL, 0x95D5EAEF6F92AE02ULL, 0x542ECAAF913FB2F6ULL, 0xA7606FA1E4537064ULL, 
            0x89DEBBB0AB381C0FULL, 0x7D06D40DAD2439C6ULL, 0x400699967CA0B213ULL, 0x2348E3138ADF412EULL
        },
        {
            0x4F0C75F410304344ULL, 0xA0E29F0AA64B7A46ULL, 0xD230569A667BEA17ULL, 0x6ADEEAB5BB973D57ULL, 
            0x4D18C570F2708C30ULL, 0xE5AAAAC2970D1889ULL, 0xB661A65E969AC8B4ULL, 0x5DA4971482228AD7ULL, 
            0xEFA199DFDDD5BDD6ULL, 0x6E39CBC9F8FC08C5ULL, 0xEA26AF65EEEA3ADEULL, 0x22E12B8FEA2057A8ULL, 
            0x3E0382CA7FD2CE28ULL, 0x4833F00F8ACD91EBULL, 0xD0392CED6CFEE2C1ULL, 0x53DF19E571D5924BULL, 
            0xF95BE72261EE09C9ULL, 0x1864A3D35EBFE373ULL, 0x7341DED16E850607ULL, 0xB103B21CA04C29A8ULL, 
            0x928B7CE21C8AE7F9ULL, 0xE1C4B8790C3FA1F0ULL, 0x704AE8B516D4AB9DULL, 0xBD348576E3129E57ULL, 
            0xE41169C6027BDE8BULL, 0xA921B108489CC4C5ULL, 0xB92482BA8909E1ABULL, 0x1F7003CD96C3DF05ULL, 
            0x1FE01C0FBBC7216FULL, 0x3134D33EA239B9F3ULL, 0xA2DC69DE6800C4E5ULL, 0x96533E04BEEF0A8CULL
        },
        {
            0x3F690A7E15087DA1ULL, 0x64062B3BC73EC48AULL, 0x33F8611909EAC5A6ULL, 0xEE3495893408D2D8ULL, 
            0x6AD5E49DECE0AB70ULL, 0x42B9E6229458AFA0ULL, 0xE16222DFC7C6D03FULL, 0x23177910B83BB412ULL, 
            0x6C3033EB815A0D65ULL, 0xF4FBF4487A83A248ULL, 0xA40EAE695CEFB6F3ULL, 0xD3695E2930A9A022ULL, 
            0x6CC9D743C5FEBDD7ULL, 0x484918CE5C5DDA4EULL, 0x0133FC7C04A96838ULL, 0xE183B818AD13FD1BULL, 
            0x411169BDFF29A6CDULL, 0xA1E796EC8BB2594DULL, 0x9400947B2F239879ULL, 0x1142AAB6B9059311ULL, 
            0x0AFEB1DD6D3B58A8ULL, 0x8E4B2B9CB1B37D91ULL, 0x57A33349A27EB41EULL, 0xA0C68614F3F69F3DULL, 
            0x9A7FB7D9B84B11F4ULL, 0xE042DDAF07C36413ULL, 0x4A966A12A333E29DULL, 0x2D0EF6DA54BD7DE7ULL, 
            0x2F8DCDE2D373D2BBULL, 0x01ADBE3699046CBCULL, 0xE2C3C96D115B6186ULL, 0x6D1E57647455AEB0ULL
        }
    },
    {
        {
            0x33A2E68B47AFB533ULL, 0xA726D9A7C65CE9B7ULL, 0xE6B62F03FEBB3D20ULL, 0xC477DDEDC46E3805ULL, 
            0x3EDBAEC9E975CAD8ULL, 0x4AF4976E0076A8EDULL, 0x549310A402A67E7CULL, 0x509625A53F337694ULL, 
            0x265FF1DE07F56C50ULL, 0x4C5142793B57D38BULL, 0x676F1E0E5C1D8CB0ULL, 0x2B0820AC578B4FF4ULL, 
            0xA37164517E6F3394ULL, 0xC5C70E3D720FE390ULL, 0x903661D71709B3F3ULL, 0xE4C3D760C433E0C8ULL, 
            0x4DACFE30CE13C0E0ULL, 0x122E035522539DE4ULL, 0x110C233AFE1AB5CEULL, 0x16C36C5307ED16E7ULL, 
            0x2D60E87BABD0223FULL, 0x2EC39B84A3E28BA3ULL, 0xAE500E9C050B20FFULL, 0xBD3D4E2264C70F26ULL, 
            0x15FB756DF9FAE111ULL, 0x4A024507D3492CE7ULL, 0x7EE0E9C77F539C75ULL, 0xD27F6E8AD8F51E1BULL, 
            0x6B2023D84B892B7BULL, 0x9263C2DF9A05DBA6ULL, 0xD3B5DE201FE5629DULL, 0xE1AE3446F12D7219ULL
        },
        {
            0x28D928B9BDF07868ULL, 0xF831F93C70D5CEE8ULL, 0xE3D1400D5427BE4FULL, 0x07B7ABAE5234A911ULL, 
            0x516F06BFB13190F4ULL, 0xCE25F1FA8D784AB6ULL, 0x61C268DABC0A7748ULL, 0x5E844C559A4248A4ULL, 
            0x05EDCDAAB5EC8C02ULL, 0x25EDE8140FD37873ULL, 0x348184657F8C9E15ULL, 0x4094E8A12DBF87F4ULL, 
            0x31A0CE88CAA7E895ULL, 0x98A9C6102250701FULL, 0x71D3997B2B0B98AFULL, 0xB509B14BAF9B77F1ULL, 
            0xF60B148D70025A28ULL, 0xFAFAFA3297B88CC7ULL, 0x9512FA4982D7CD14ULL, 0xF1D7E3CD356E0210ULL, 
            0x3AAC9CDC590756AFULL, 0x1D95B26B6DCCD927ULL, 0xA7BEE3FB843709C0ULL, 0x62CC87EABB038563ULL, 
            0xB9D9A94D1D306591ULL, 0x8B5AE6D33E55C5B8ULL, 0xD4B704F67868B3ECULL, 0x0134AFFAF90A6228ULL, 
            0x1B45343E59D0EC02ULL, 0x5332C242C9012353ULL, 0xFDE5A87A2A3C7121ULL, 0x92C077852EB58140ULL
        },
        {
            0x7680371208D04565ULL, 0xA37EA4815B5D14BDULL, 0x8D67E3F378EE6370ULL, 0xC89130A7B1EABD71ULL, 
            0xF0C3CD5BCF5AA7B5ULL, 0x10EDD6EEEF6B60A3ULL, 0x156F267B2A87A16DULL, 0x32AC59F1D4361F4DULL, 
            0x7A5FB921F3E41D12ULL, 0xF210912B0BBD388DULL, 0xBF403401ED3CF982ULL, 0xB36A685B64339C21ULL, 
            0x90483AAB445F9140ULL, 0x80ED34F688CBA9D6ULL, 0xDC6BCF8C585AF293ULL, 0xECBE10987F7F9EC1ULL, 
            0xA367CD1DBB320FB9ULL, 0xBCACE78F9736165FULL, 0x4825E0668EB50D94ULL, 0x52E1B530B484BEE4ULL, 
            0x08A9C7E44108AEBEULL, 0x3A250950780EC6F8ULL, 0x6BB3E4C211F69E0AULL, 0xAC1AA25241EEEBDBULL, 
            0xD17BC0EEBBDBA60FULL, 0xEFDF6E12B2A081A1ULL, 0xB15E92A797719645ULL, 0x6C2CE66AD9509D97ULL, 
            0x5321097A86BF6C8BULL, 0x37EA3A2DE2DF8E47ULL, 0x479DBAD5B4CD16ACULL, 0xD3809C0C28A2A024ULL
        },
        {
            0xCAC8D5FC6E873B73ULL, 0x12537F88096D94F7ULL, 0xCD16ED375A5604E5ULL, 0xDC297C4C95995329ULL, 
            0xB8E994E2EA47F918ULL, 0xF7CE57612C52757BULL, 0x41C5D0B6FB27CB6EULL, 0x5CB502D4CF830765ULL, 
            0x70A4DCCEB1537F0EULL, 0x31AED42753860E72ULL, 0x98A1B94C64870B17ULL, 0xC835F63CF57ACA8EULL, 
            0x8A4AEAC7A7AF5336ULL, 0x1465BD1029C588E5ULL, 0x26C11EDB26C1BA35ULL, 0xBEF6F63C1104A95EULL, 
            0x349F62863601FAE6ULL, 0xE8D302506354D030ULL, 0xF105DFEDC07D7B75ULL, 0x1968856A8C0D94F0ULL, 
            0x706D8B0CC13388CEULL, 0x1A9FF606F496C829ULL, 0x0A69FF3AB1DFBF6EULL, 0x6DF43C21DB1FCD97ULL, 
            0xA0FA1421AAF1723EULL, 0xC22D08C8CAE8762FULL, 0x7EC830DF2BDAA7ACULL, 0x269722A3B5CC4855ULL, 
            0x913DB44764BED901ULL, 0x451BB68ABC324BA5ULL, 0x30C000F47BCE08B9ULL, 0x514137B93EDF95ECULL
        },
        {
            0xD6505CBDB8F6DDB2ULL, 0xC097B9613ACCF910ULL, 0x4033219D6E06CE0FULL, 0xE180CD1AABBB6A8BULL, 
            0x8E8A60262AE871DCULL, 0xC7F8F372B9403EF7ULL, 0xE1C97A2E2EDF233DULL, 0xB912BCCD5819332CULL, 
            0x0852908AC9A8B65EULL, 0x3320D88446FC63DDULL, 0x82F397CB01252621ULL, 0xB0E2A4A2E53BB0ACULL, 
            0x68C5BE1802ECCE22ULL, 0x2E07242B22B3A908ULL, 0x9CCB1316F8956F30ULL, 0xA7E02D2A23EB41C1ULL, 
            0x027EB28172D49852ULL, 0x6056AEA7C34CBC91ULL, 0x3D624BE1EA18259EULL, 0xF58A153D3ACD80FDULL, 
            0x00C5B5C68AD268CFULL, 0x1CD531D7BD944450ULL, 0x11C32B5241C2BE54ULL, 0xCB4C20DF5C691847ULL, 
            0x523F542D2250E0ADULL, 0xA204A609F262BB1EULL, 0x86549FB5E4B38C1FULL, 0xA6ED72E0D5747880ULL, 
            0x58746F64B50818F1ULL, 0x6B89BB995866265FULL, 0xB4740B95379C06E3ULL, 0x94AEAAD8381E932CULL
        },
        {
            0x13A68AAF4256ABCBULL, 0x861DE14153CE27FFULL, 0x806E4715D27F97E9ULL, 0x850A2242542B0505ULL, 
            0x42DF2A3FC932AD98ULL, 0xC7413477B1985E66ULL, 0xF1D4FABA6F2EF6E3ULL, 0xDB9F82D7B6F94CC1ULL, 
            0x61838C4814E28BA3ULL, 0x42698289810D2CAFULL, 0x6C440A12147C8E25ULL, 0x500D69DD08E541A5ULL, 
            0x1C1AA00A0C26EAEEULL, 0x89B411606A807FD9ULL, 0x001DC0E80AADAE6EULL, 0xA56FF1816549F281ULL, 
            0xB36EB4AB38FC9F08ULL, 0x76370A9492585CEFULL, 0xC3A8AE0EAD3B521BULL, 0x19B005304671ED0CULL, 
            0x0E6818724ECA2649ULL, 0x2825CC74A9DD9127ULL, 0x1488AC44F5B6E87BULL, 0x39EA1E06A8C31B9CULL, 
            0xEBC77B2FB1E15974ULL, 0x970C90FD5E600406ULL, 0xD1DEAB3D68899233ULL, 0x50B484CE2D9A4D8BULL, 
            0x6B0B432716FB2A35ULL, 0x94C6397C2BA20277ULL, 0x38C5B17111AA10A1ULL, 0x8EAB02E7AFE0841DULL
        }
    },
    {
        {
            0x2ABBB34C697C0B58ULL, 0x6DDDE8EB2E9A2B1EULL, 0xEEDA0D21547A3172ULL, 0x32A1CB1BE60107CDULL, 
            0xB8309272441702F5ULL, 0x38556F454A7FDF75ULL, 0x48FF7B36665BE22BULL, 0x4639E443CFBD4534ULL, 
            0x696A7F5675925675ULL, 0xA84A2C4F4E568826ULL, 0x9C90085980CB198BULL, 0x5B81926B7B9D2A56ULL, 
            0x154ADCCE1EC24E06ULL, 0x9632066E7E59A6E4ULL, 0xD804FBC796866E07ULL, 0x0170A2114E94177CULL, 
            0x57D737272B5F4AEBULL, 0xD6A2EE09E0259D2FULL, 0x32F55CCF0458E0C5ULL, 0x3A9B4A7ACCB38F2AULL, 
            0xC147F9139E333E9BULL, 0xB4AF49883ACE69F6ULL, 0x68A73E62C3F4F38BULL, 0x10A04D9174C64AE4ULL, 
            0xDDC9F64B0217D559ULL, 0x4046C1D5B01A25ACULL, 0xAABEA1F453562300ULL, 0xB4A33A86446B914BULL, 
            0x7E39901BFE6B37D0ULL, 0xB718637D37D980A4ULL, 0x8648E455D91A1F2FULL, 0x6D00B03E38741D03ULL
        },
        {
            0xBF3F90B8E1075A6CULL, 0x61E8C6CDED4A1890ULL, 0xB96EEDE0397E162BULL, 0x4ABD09438FB2FD90ULL, 
            0x7A9352C1BE6898BDULL, 0x2F5417DC6B5CBB5DULL, 0x97CFA10479BBA696ULL, 0x0C87866567FFB1E2ULL, 
            0x7D2740F21918A529ULL, 0xD194F638C680B0F1ULL, 0xE62514C2EACC1635ULL, 0x0B58B9389A0D09E5ULL, 
            0x371DE610D39CDE6BULL, 0x75ADA78C4192AE22ULL, 0xBA10CB626F3792D0ULL, 0x3AF3E5CD16FD114CULL, 
            0x588C7A3833908064ULL, 0xC2CA70D3ECE46202ULL, 0x36F3A7A41786BA6AULL, 0xE4B2F4124F5DB217ULL, 
            0xDE79C972ABF763A8ULL, 0x4616C124D636FF07ULL, 0xE58D18B3FBF2CAC4ULL, 0x23D2244EA258BC8AULL, 
            0x778516A4629C4780ULL, 0xB35BB786E61980B4ULL, 0xE5F4E63DF1C930C8ULL, 0x67B424162D792DF8ULL, 
            0x2C071B0690B1163DULL, 0x79BE106B9A419DAAULL, 0x770F128B7BCD47D5ULL, 0x32EFCE658016EB53ULL
        },
        {
            0x4F2B11FDAD1C10B0ULL, 0x2873460D214ABC92ULL, 0x52FE4D6A0BAA6FBBULL, 0x5128C81B67E218C6ULL, 
            0x0142BE6CF1C13F2DULL, 0x540746B3CC5F02D9ULL, 0xEE6FA23BA8A37468ULL, 0x699AEE6757EC48AEULL, 
            0x8152D5AB33814BD7ULL, 0x9C0171BC1B2122C1ULL, 0xBC555155B8E35E58ULL, 0xA72AAF78DE7A5004ULL, 
            0x125C415384E8AC31ULL, 0xFAF02FBD2BD28D10ULL, 0x069405DA1144FD4FULL, 0xED596CB21396D0AFULL, 
            0x1D05925A09A7FA46ULL, 0xD874212383860F3BULL, 0xA8CD0EF5E4C5BAA0ULL, 0x603DC552E89D0C72ULL, 
            0xEB785E39E8AA4C86ULL, 0x40C364ACDCB54112ULL, 0x75F0E12B09AB4E55ULL, 0x48A01E48B56AC1ECULL, 
            0x2CC72A159595839BULL, 0x425A3ED525289045ULL, 0xDF51F8410ECCF6C4ULL, 0x8D5E3129EF6659E2ULL, 
            0xAC1DC6323F8B49A6ULL, 0xCAE3F566F2602C31ULL, 0xF0EB74A17C5A673BULL, 0x11EB587BCE3CD2F7ULL
        },
        {
            0xBB9FAF30B2FBA8A0ULL, 0x2472B7AB0AF2EDD1ULL, 0x757443DBB3B1E3D1ULL, 0xEB74F3C67F251F77ULL, 
            0xB3C65DBFBB1C126CULL, 0x4B560D65C25AE4C8ULL, 0xF0F2C04D3AC2170AULL, 0x1E6BAE859F22E42DULL, 
            0xC5C35A99E0CFB67BULL, 0x17C2099B894861A8ULL, 0xE55839458E9212D1ULL, 0xFB79432816D5C133ULL, 
            0x474E1C0DCAB8E8B8ULL, 0x1F215003B607EFF6ULL, 0xDEB2090B8BBE99E7ULL, 0x1578F54B52655D08ULL, 
            0x53FB88C34EC045FDULL, 0x8AD8131B82F54B8CULL, 0xC554711DFEDF8030ULL, 0x25EC96A1ACE3081CULL, 
            0x3FD1B5121484F912ULL, 0x800699CD362A76EAULL, 0x8253A6C17369C11BULL, 0xEF6D284485B3A7E0ULL, 
            0x4DFA3E3837FB499DULL, 0x90F23298365167FDULL, 0xA7754BFA99CC4204ULL, 0xB72AC1D9CD5FC53DULL, 
            0x9E3F6336C34D7243ULL, 0x5CCE14BF08F31780ULL, 0x103A037452D99245ULL, 0x79A7F7AB74923A74ULL
        },
        {
            0x1406BEA2AA198366ULL, 0x587968EBD41FAAA5ULL, 0xB9BC841BC81D8DB9ULL, 0xF71434927FDEEB75ULL, 
            0x4A7C300F105581E7ULL, 0x6582D54385E0D049ULL, 0x23DD5E262C733F25ULL, 0x23C28D8084769372ULL, 
            0xE76A3161DE30EFCBULL, 0x4074D8584C8DB6E3ULL, 0x65A7435DAA7A9CD1ULL, 0x398FC68293A5EB69ULL, 
            0xF54E37209B7DEBA4ULL, 0xD2BA494EA81C0E3FULL, 0xBA6491F251BFF6FAULL, 0xE6D753836E15DAB5ULL, 
            0x0D3BEC5B677BBBCDULL, 0xD2D06E716628848AULL, 0xDE1F968544512307ULL, 0x7C0FD3F2A8C18D9DULL, 
            0x2EA99E8DC39880C0ULL, 0xB5563003BCE28DDFULL, 0x9CAC001AABCC994FULL, 0x429134BB3ED87246ULL, 
            0xA77985E5421C8CBEULL, 0x4EC77125264A033CULL, 0x53BDEF150082B5F2ULL, 0xFEE80FA60A66B5C8ULL, 
            0x3B2984BDBEE6D02EULL, 0x0FFFD0364AA98E5AULL, 0x7BBE98D10DF8F070ULL, 0x2DEA7AA495245EB5ULL
        },
        {
            0x3EAEDA7A030F7026ULL, 0x9CC8E74544A9FF68ULL, 0x5CD87FACF1C58BB3ULL, 0x1955F44528A436DCULL, 
            0xC8CDDD7AD9E90D34ULL, 0xA13EEC3FE3249676ULL, 0xA26A6AD4CBD0D4D2ULL, 0x49AB575D5924682BULL, 
            0x50E8ABAC2B85B1CFULL, 0xED56A31959620058ULL, 0xFDB2FC3CE65F5B1CULL, 0xC5C8D0D51BC35EE9ULL, 
            0xD02DA405BB16A890ULL, 0xC537F302866520F6ULL, 0xEE1AC2BD5CCCE89FULL, 0x067209AAA75FA1D0ULL, 
            0x825EDB5667907F2EULL, 0x478575089346BED8ULL, 0xF08FACDD07B5E11BULL, 0xCB5745AD52895BC2ULL, 
            0x5CB6840E1F07A621ULL, 0xA91516E0AB62CA14ULL, 0x2CFB24D5CBFF23B5ULL, 0x31B5B432931C4767ULL, 
            0xA2E82EEB8CA30028ULL, 0xD12ADD5C3B557819ULL, 0x847ED92396061A18ULL, 0xECCED9EA8363BC0FULL, 
            0x21516F1AFEE8D303ULL, 0x7F8EB810B903FA25ULL, 0xFC4C09E3C5922D19ULL, 0x0FAF92E6866135EEULL
        }
    }
};

const TwistDomainConstants TwistExpander_Ankaa::kPhaseCConstants = {
    0x3AB94BC09C3623A5ULL,
    0x9F4E023F8196C9BCULL,
    0x56C30A5CECF6F732ULL,
    0x3AB94BC09C3623A5ULL,
    0x9F4E023F8196C9BCULL,
    0x56C30A5CECF6F732ULL,
    0x7B26349347675452ULL,
    0x4B44856F350BBD07ULL,
    0xE8,
    0x50,
    0x62,
    0x9A,
    0x9D,
    0x81,
    0x1E,
    0x21
};

const TwistDomainSaltSet TwistExpander_Ankaa::kPhaseDSalts = {
    {
        {
            0xAE90A47816821451ULL, 0xDAF0B20158AE8FA1ULL, 0xB4E220AC977074AEULL, 0xD9EA074D9C73330BULL, 
            0x66E6742AF777C68EULL, 0x50A1F4AA7D2139E6ULL, 0x395BBFA08CFC2D91ULL, 0x359779ADE0BAF747ULL, 
            0x37CA5B19D7E59884ULL, 0xCF10A2363A28D62DULL, 0x768C2FA3D6C3CF3BULL, 0xC3D0156516DC0FA1ULL, 
            0x04949F4FC7678A7CULL, 0x59262CE9C7D48294ULL, 0x6C665B840EBFAEC9ULL, 0xC5A1EF9C3EAF3539ULL, 
            0xD5AF036E3F752F2DULL, 0x67C49F4A5EB61E4BULL, 0xCF7A0B11BD6CE894ULL, 0xC9D935FAE196C87EULL, 
            0x36474AA699C47CDAULL, 0xFE3C10D339B791F7ULL, 0xA34A6C8BB3A970F9ULL, 0xFDDBA57448EB2A1DULL, 
            0x6AB4ECB4AC9EFEC6ULL, 0x8F31D1731C8C5545ULL, 0x06013D174ABD14F4ULL, 0x1894880F8D4933B3ULL, 
            0xFFDA5FDEFD044D6EULL, 0xC03BB29BFA3A5985ULL, 0x6BF755F93D68C3A7ULL, 0x5F9E3183EE851721ULL
        },
        {
            0x495374E42BE8A018ULL, 0xD71DE3FE1674F729ULL, 0x47571BA35CF6AA01ULL, 0x2219A667F911625EULL, 
            0x3EB631340176014EULL, 0xD05676999453FDB0ULL, 0x417F1C1FBA6915B0ULL, 0x8909431330BF2BBDULL, 
            0x7E9CA8F2176792EEULL, 0xFC3BE7F2DDE2B39BULL, 0x588476A9214AD8BBULL, 0xB32919EFDB4443D2ULL, 
            0x2AF58EE10C5E2DA0ULL, 0x80CE1FB73C05CFFBULL, 0x26E9C28EE6B99D04ULL, 0xDB3667156E5F8DF9ULL, 
            0xBC502F436D92E745ULL, 0x4DDE86C1E55DB95EULL, 0xDA332FE564B6DBDBULL, 0x962DCFE578DC067BULL, 
            0xA49875B4B20AD459ULL, 0xE55CBBA99E405524ULL, 0x8DDE2123FBC4BAF3ULL, 0xD35E128D3E9EBFF5ULL, 
            0x717E3C27793007D9ULL, 0x39AE34FEFB366C7DULL, 0xD4602EE24BEC5AC0ULL, 0x4ED12B00293DB6AFULL, 
            0x02175A6DC58313A1ULL, 0x1707C2EE37F11C23ULL, 0xA67A47B60B72F401ULL, 0x9BEA8C461CE94C22ULL
        },
        {
            0xF586B6766941A216ULL, 0x5EE6B41EFBDD2C20ULL, 0x90D46515E98A0323ULL, 0x19D39808EAE28AA5ULL, 
            0xB6F62F401FBA00E3ULL, 0xAAF6DE672D512224ULL, 0x8A8A19949B156185ULL, 0x7D2DE40B9FB78FBDULL, 
            0x47191EEE78224A6FULL, 0x3B415E371A7886BBULL, 0x6FDFCC5545E5E17AULL, 0x4EF1FC64B1EB5FE2ULL, 
            0xD991F098ABA842E0ULL, 0xFA3AF0D88F4BE616ULL, 0xA75DB4E824286340ULL, 0x533A9B34C71A2D75ULL, 
            0xD8B32D6EB12BE0EAULL, 0x6C491CC92CE2B99AULL, 0x03DC04C311ADB770ULL, 0xF121B6DC195B21E8ULL, 
            0x241A7457C8EE32DAULL, 0x94FE94BD11FFD6F5ULL, 0xAC7F0AB57E82BD6EULL, 0x4DD0CC99E9AAFCE1ULL, 
            0xEFF7810948F0D285ULL, 0x2B4AEADC34872340ULL, 0x6E4241C87B3EC5B3ULL, 0x862CB2330074B9A2ULL, 
            0x5B569B329B0A79DDULL, 0x82F5BF60E42A87D6ULL, 0x84ED15A1A723B331ULL, 0x9360A29AD9D8E98AULL
        },
        {
            0x60E7DDCBA593E99AULL, 0x042672C66B9360D5ULL, 0x00E128078A483C14ULL, 0x61482AF69CACCE8DULL, 
            0x3F58F86DEA28B014ULL, 0x699D88EA07C9B6D0ULL, 0xA1EB47A797CDBC10ULL, 0x8D4B303A38740F6BULL, 
            0x911E78CDA3C451CDULL, 0x62A7503490ECA4E5ULL, 0x1CFDEB95DA832722ULL, 0xE72013670FF3434AULL, 
            0x75D49F4375C49F40ULL, 0x5DD6E0D1D109BB22ULL, 0xA0F311361FAA797EULL, 0x0440CFD001C5660AULL, 
            0xD8D4DB639116C7A9ULL, 0x794CB9BF1A268116ULL, 0x44F19355947405F4ULL, 0xBA53048DC39E62D1ULL, 
            0x804658CC1AF71549ULL, 0xC40AAFA888C58777ULL, 0xE186C0B8F0FB3926ULL, 0x44502D10A9CEEC24ULL, 
            0x32CC8E7E518811B0ULL, 0x9026142383EA090CULL, 0x717AC905FB2997A1ULL, 0x358BCE5E9D8244B9ULL, 
            0xADCBA5AB95A11628ULL, 0xDEB812DD5703B4D9ULL, 0x295AE07383923D78ULL, 0x95642503D64E19A1ULL
        },
        {
            0xF52AF0A9CCE4CDEAULL, 0xC60A37CCE79C29C6ULL, 0x1A0D50C3D52EB147ULL, 0x89822A23351AA781ULL, 
            0x483A755A8FB8EF3DULL, 0x0B0692CD551ED00DULL, 0x704EFF3A4203D486ULL, 0x783B6D02E55ECF26ULL, 
            0xE048252B9E37EF45ULL, 0x98A4AB58B6A040EDULL, 0xD3850DD963CF36D7ULL, 0x3B13AC2523740F9FULL, 
            0x7631505C43E36C8CULL, 0x471EA5385947ACB8ULL, 0x6312C4F1C6B36674ULL, 0x7503BCBFC8B5613AULL, 
            0x2B73D68BF4A9A2C5ULL, 0xBD3C30EB95BBA12EULL, 0xDE9EB55F20F690C3ULL, 0xACF4F2C0B1D2F0F8ULL, 
            0xF1B8E53C8E81316EULL, 0x733F0F8AE866C8B9ULL, 0x36BAF2DE76D2CB84ULL, 0x7B9F78DD5D2D68BEULL, 
            0xC493ED14B33FF502ULL, 0x8DF6090AA34C6CF1ULL, 0xC19BA2FD9A62DE47ULL, 0x416E4BA12380E664ULL, 
            0x45192BACA9283763ULL, 0x6C9594C8B897AEE9ULL, 0xCAFBB86C667A54ADULL, 0x35E8CF2012B1592FULL
        },
        {
            0xD759BAB16BF2A1E4ULL, 0x933A9D99D5F1D484ULL, 0xEEE28598EA29F802ULL, 0x03DD2D2975D6F7ACULL, 
            0xC2C9EA6BFA418025ULL, 0x07A84D4638B305EFULL, 0xF1AF58809AD9FCCFULL, 0xFADBF2B02F5F7CF1ULL, 
            0x6EDCE428D65AE827ULL, 0x39E44AD1686E3F62ULL, 0xECB40CAF60C1241FULL, 0xFCA771F04F947A64ULL, 
            0xC17C80F54FBD355BULL, 0x007FC692E3FBCB04ULL, 0x6C5D205086F42AF2ULL, 0x398DB233E05D9A51ULL, 
            0x2F481AFDAB86AFBAULL, 0xE60FC2091A2F3993ULL, 0x0CF3CCE2388E1CFEULL, 0x35BC7EFCDE3430E8ULL, 
            0xC1F72C5D67F7F170ULL, 0x12FA8F018FB19AD9ULL, 0x38A098F4E16F3BF6ULL, 0x4A05D84F59EFE9FCULL, 
            0x86F3D6D146C591FBULL, 0xB6A85BE7B52D3396ULL, 0x7DA95574400DD15BULL, 0x13D33C1E74CFF281ULL, 
            0xB66F5A3648809901ULL, 0x1C11A7BB016EE1B4ULL, 0x90130B3CD7285486ULL, 0xABC68BE2E4612E02ULL
        }
    },
    {
        {
            0x85E25A34622B3895ULL, 0x94ACAE659BA6F5E1ULL, 0x083173C84ED9BB46ULL, 0xACFCD97B5BAAFA66ULL, 
            0xA7A1D4F1C0BACCC4ULL, 0x6E580B8968FB5CC4ULL, 0xD1BC997CEB21D299ULL, 0x41950C2CF27CB0ECULL, 
            0xEC9A89169B2892DCULL, 0xBD0B1FB7C16A8832ULL, 0x09CD1E9929EADE8BULL, 0x3E003AD75E888699ULL, 
            0xE01F227038320F8EULL, 0x50227605D3E32893ULL, 0x22FCE8FDC4609B47ULL, 0x5AF63540EFD0175FULL, 
            0xA7DC26D0709D7A7AULL, 0x174FB4B197250ADDULL, 0x27424EB8BEAC21A3ULL, 0xE1832758B1CFC04BULL, 
            0x0BF8FF8E6188E338ULL, 0x2C3A1EEBE69EC666ULL, 0x5DFC55A7320C01C5ULL, 0xCC0690C6913F229BULL, 
            0x3C569A1BEED77177ULL, 0xD1F459D9815AF1D5ULL, 0x96A05DEFD27BB536ULL, 0xB5375F10ACDE3F6FULL, 
            0xFB2F78396F84CE31ULL, 0x9A4ED4FC12884125ULL, 0x3E436193673367C6ULL, 0x99DE3704ED660CF9ULL
        },
        {
            0x5DE6E1CB884CCE1DULL, 0x2F5EC1150BFB1579ULL, 0xB0EF9D2C82F35AC3ULL, 0x2ADB69A12EA7534BULL, 
            0x951619EA25AB4253ULL, 0x2D82BAAABC91A2B7ULL, 0x2AFB592D4D4F9446ULL, 0x80DD23A0CB3D3D9CULL, 
            0x300EB7FC71BD4124ULL, 0xBC3444317D738D70ULL, 0xB40B54374C3129EAULL, 0x41FD0F69FC5A18BAULL, 
            0x250638FF09FF1D8AULL, 0x9A388BCE9055A5ECULL, 0x8825324000ED1AC2ULL, 0x33A43CC54429C2C9ULL, 
            0x2DD3CF070B358AC7ULL, 0xCCB85C5EB3340A73ULL, 0xDBE3CD13C3B50CC7ULL, 0x562D2C4421B7764EULL, 
            0x4B09DB64DB12F715ULL, 0x4A4D070DF1D34D85ULL, 0x3AD21C0E41AFA905ULL, 0x8A6C9D486A732BB2ULL, 
            0x775AA58896F0430FULL, 0x9C322D685A72FB57ULL, 0x51807E21674EB7AEULL, 0xF4A04C82D3EC7CAAULL, 
            0xC754C1FB60DB8A19ULL, 0xA1B3552E92FA4057ULL, 0x8A0C55D5C578BC66ULL, 0xAA84C3FB3D7062A7ULL
        },
        {
            0xC1905A49B984879AULL, 0x9FE21DBD46B69C0DULL, 0xB30B04F605A99EECULL, 0xB8F00B66F2A2A345ULL, 
            0x30DE54F4FE94FE24ULL, 0xF71DB11BAAE1A3CFULL, 0x2AB9F1445CBF32E9ULL, 0x40B542BEA49FF264ULL, 
            0x4FFE56D2B3FB47A2ULL, 0xF7FC6C44828F02BAULL, 0x70DFBAE80614F572ULL, 0x072E0171DE3EF2E6ULL, 
            0xD657168C7832B3DBULL, 0x98C1FE18A6E55DB3ULL, 0x655AA40CE6839C7EULL, 0xF2751E61F0602CF5ULL, 
            0x146B47AC995DA809ULL, 0x1639F5EB0DCAAF82ULL, 0x00FD552B8EB36F10ULL, 0xB73C96862BCA5022ULL, 
            0x23F771F0CAD3B65BULL, 0xD63BFDD855BEA2D9ULL, 0x90B3D612DB00C51AULL, 0xBDA7AB6528132710ULL, 
            0xEBEBA7601C1A41EFULL, 0x7BA26A0E9EA9B11FULL, 0x8679F852957B50FBULL, 0xBF53015B6081398CULL, 
            0xA7678242F19BB7E8ULL, 0x40231F3AB127E97EULL, 0x0AA9361C3B71804EULL, 0x604C08A187C02F69ULL
        },
        {
            0xAD31B07A24FF1529ULL, 0xEF8106023BBB64E6ULL, 0xF832B4B2B7B7B3B3ULL, 0xED88E39D2148F197ULL, 
            0x3D7C6F4C34064EDBULL, 0x7FCBD143C33F82CCULL, 0xEB8DB31922EE7BD3ULL, 0x744F684CBF5D0EAFULL, 
            0x2E2925A3A923E545ULL, 0xFA8F560205EFDD98ULL, 0x928210A76C980612ULL, 0x85C2BAFC0E9FA482ULL, 
            0x1FAD7E3986E64D2EULL, 0x624678684700849BULL, 0xA1707CF93CE6C7F7ULL, 0x456D16AADBF916D7ULL, 
            0x31112299D2495CB5ULL, 0x4D46131BBE88ED4EULL, 0x7F79A80711BC5A46ULL, 0x10F85165E13E11E5ULL, 
            0x6060E27034F11726ULL, 0x37391B75A6004BF9ULL, 0xCE3A0A61CAD9D9D6ULL, 0x10F8721AB91A2C28ULL, 
            0x7E1DFA194C570CC2ULL, 0x73C51C48EED9B8C0ULL, 0xC0688CF1C23B8D61ULL, 0xD3ABC222F3CCF964ULL, 
            0xF173D5C3B4059EEAULL, 0xD03AB0ED19CFAED0ULL, 0x39FD8645B561C600ULL, 0x0E8C0C8B3421F231ULL
        },
        {
            0xC35E371E7436369CULL, 0xEB5D74AB4D8D3BB7ULL, 0xB48DD87528659341ULL, 0xEDC82B6057CB2217ULL, 
            0x8C0CBE2FFA697BFCULL, 0x31A90EB47E406C59ULL, 0x01D01E40833F3BFCULL, 0xA4C5FD54E70CF97AULL, 
            0xB4E3837FDF38B480ULL, 0x540EB8420398094BULL, 0x125DE95B42AEE572ULL, 0xCCD8A3F2E7A75CEEULL, 
            0x6FEE5C60838DC3D5ULL, 0xC7229582AFE361C7ULL, 0xD099F05733A268FAULL, 0x0A59A1AF863E7E81ULL, 
            0xC5CCB0DFB0BA5456ULL, 0xBF952258FB1C1C2CULL, 0xFA67A8E407283210ULL, 0xBDA8B8684FD30C28ULL, 
            0xD7B078081CF5EB13ULL, 0x9E1D47889FFFEA7AULL, 0x5E9AB0EC95A69E8BULL, 0xD2831E26449C9759ULL, 
            0xAC718DFA5C4C5DBCULL, 0x1D29E02FE143D1A0ULL, 0xA2C6348D61A91A67ULL, 0x687A232827890101ULL, 
            0x511796D4C9515040ULL, 0x8CCF0670889B2953ULL, 0xD2066BDA1264A434ULL, 0xFB8225B9139EED9DULL
        },
        {
            0x33DE162F20FF8D25ULL, 0x26146CF0FB3A2156ULL, 0xA78A7F03500E29C5ULL, 0xA7E6AE2220052EA8ULL, 
            0x41A80EC092B5BD5EULL, 0x86B7F88DA9DE049DULL, 0x649DEB83E20F682DULL, 0x530CC1DF9D9F150EULL, 
            0x9523F972C4CBDF0DULL, 0x37EDD2FECCACFA46ULL, 0x04D3614B82FB8FA8ULL, 0x6AF5723F5F96A746ULL, 
            0x7793141447BBBED4ULL, 0x917DCEFF50E97C5CULL, 0x1148F736CF6B5C4BULL, 0x0B3DC0F79C10C2ECULL, 
            0x55A6479789FEB3ADULL, 0x850216AFF6F5A9AAULL, 0x997B4F89066129CCULL, 0x78A62A425E9560F2ULL, 
            0xF70EE546E96CF633ULL, 0x46EA0E77B72A57E2ULL, 0x97588B403046B961ULL, 0x6C3D2D8DB678DACDULL, 
            0x510A9BF92F95C2B3ULL, 0x800329E9E3377798ULL, 0x86D787659DDE7DEAULL, 0x23C1039AC7B95480ULL, 
            0xC6B57DA67105F278ULL, 0x5B9C60C8B1E83FABULL, 0xE09E23DC3813F856ULL, 0xB4981306631D3D54ULL
        }
    },
    {
        {
            0x88729F1CC299FEAAULL, 0x6A0A26E8535473EDULL, 0x267507BF25A13D26ULL, 0x0D3E2FE82028906CULL, 
            0x0D38FB77811B7827ULL, 0xDCAE4E2F93B46B77ULL, 0x1DE20A45E39FD28DULL, 0x17ACC0E106C947BEULL, 
            0x3240700FD32598ACULL, 0xE0A4D7B1D0A19647ULL, 0x856EDA156C35A37AULL, 0xC76F97C6C65310DEULL, 
            0xB8F64104DDD43992ULL, 0xD76152F68B93925CULL, 0x76739823E02C5004ULL, 0x712A3736569C86BCULL, 
            0xFE8FC9045346D286ULL, 0x7C75E839B3D4A4B6ULL, 0x62FF03FC64E5B2F4ULL, 0x0833E69AC3B3AF23ULL, 
            0x5783FEF0A894272DULL, 0xB8B07ADCA2575487ULL, 0x74CCDA983DE7E24BULL, 0x8F0774D503802040ULL, 
            0xA419B51252D215BDULL, 0xB5DA7B223559371BULL, 0x126D6E9D9CA7C9A5ULL, 0xDC8E9372FDB3F1CAULL, 
            0x263EC07CF4EFDAC1ULL, 0x1BBAF137C656075EULL, 0x8FC249B1954E933EULL, 0x7D2AD43DD4971DF1ULL
        },
        {
            0xBEAE3C09A832C22BULL, 0x0B6FDE68A145218EULL, 0xAAEDD5B13725C579ULL, 0x56D89B10C848E45DULL, 
            0x0491BD353C49538BULL, 0xC30841DAB3AED4B4ULL, 0x241B48E63AC364ACULL, 0xD64809775E9ECBA7ULL, 
            0x463B07E8D78A5893ULL, 0x1A19506ADF695E2FULL, 0x138675E4AE6CCBE1ULL, 0x51E16DFAED00081AULL, 
            0x055332B12AC4761BULL, 0x2DF972B291931E2DULL, 0x9FF6A07CF2AF8D44ULL, 0x47B311655A39D064ULL, 
            0x65677F92D29598A9ULL, 0x4219DC6C745634C7ULL, 0xEC0B5DEAA3EA907FULL, 0xFC053E6BDE331523ULL, 
            0x3540426AD01FCE75ULL, 0xAA9485B7FB95DBEAULL, 0x578EF5A64508B02DULL, 0x13F32A4031D4F7DFULL, 
            0xF71395510CB8DE1FULL, 0x751443D7CEA271BAULL, 0x9FB1F67387445F28ULL, 0xAF8303CC67BC4C17ULL, 
            0x1E53D84DD96B8095ULL, 0x85F7BEAF01B16C58ULL, 0x55E9876759AD9ED0ULL, 0x29FB652A703A8212ULL
        },
        {
            0x2922978CDB13CEABULL, 0xD9D5036A11E16377ULL, 0xFCD558CFAF82A67FULL, 0x9AB195F54AEE8839ULL, 
            0xBCEF3D1C7EF667E4ULL, 0x91823EBC1D1B5903ULL, 0x8DA0E67F72505B16ULL, 0xEAFF71C9333418C1ULL, 
            0x105BAFA939104808ULL, 0x4F974D7DC50A975DULL, 0x51B7206D36BFA694ULL, 0xDD19935451979BBFULL, 
            0x2FC10F3D87DCD0E2ULL, 0x69DBED9B335DE258ULL, 0xFCE0ADC4930520B8ULL, 0xA955398801C5D8A1ULL, 
            0x11776D12406B77F6ULL, 0x028FEC22A572D0E9ULL, 0xBC511B93D9FBA04DULL, 0x95E883A8337D806FULL, 
            0xBEF625A69C95827BULL, 0x38E9E2F439240ACBULL, 0x7EC217AE0D404D08ULL, 0xF9E29E841629F974ULL, 
            0x06F80DCBC5F83E3AULL, 0x1A9135EE8C26E00CULL, 0xFFDB944218ADBD40ULL, 0x2873750C5012E235ULL, 
            0xA766A3F14CD2A9CDULL, 0x5D661F292C7D9295ULL, 0xD915F6FB6101043EULL, 0xFB7E14D5CC23223CULL
        },
        {
            0xA2AF8B46BCB49C65ULL, 0x652AED7CCC356542ULL, 0xE0C296E6CB85BF8CULL, 0x58860EA50FA80C13ULL, 
            0xD58BB0AC5D759440ULL, 0x0918501AF3D57867ULL, 0xE89C5193F4C1DD0BULL, 0x73D79176FF464100ULL, 
            0x402500E831D2063FULL, 0x105297322A6A712FULL, 0xA4A8E1802449EA68ULL, 0xA33A093134B2EFF0ULL, 
            0x95AB5491604DE428ULL, 0x6B077D53D7CD99CBULL, 0x54D267B2A3609663ULL, 0x2376DFDB1C0C543DULL, 
            0xBEE83DAD7AA78367ULL, 0x3B2E42665EBEBFD2ULL, 0x85B1A9D07DB4416DULL, 0xB5F73936E4F71A1DULL, 
            0x37343C929500FC29ULL, 0xCB7969C624015A63ULL, 0x3B468783A8C3996CULL, 0x27E2387AC6B5313FULL, 
            0xBCC516C2C17C771EULL, 0xD1723B39842992E5ULL, 0x65CDB5705ECEFD84ULL, 0xAF5FF6C020017F71ULL, 
            0x830539FE5B1E05BBULL, 0xB16210C4076BD066ULL, 0x9C67F9CF97FBD598ULL, 0x5C001DABEC688F2AULL
        },
        {
            0xA779F0705C8F47FDULL, 0xFB8BC569C11AF8D7ULL, 0xEE07CCE029985D1FULL, 0x7DE73D4994BE88FDULL, 
            0x468099984290F6B9ULL, 0xE843C32781112D6EULL, 0x4B85565605C598FAULL, 0x43FFE44B73A25CDBULL, 
            0x5E7CCBCC4582158CULL, 0x2F4F3A5C19C7EFD1ULL, 0x772084E7354323F5ULL, 0x621C66ACBF7FF016ULL, 
            0x670419F0D9DE1EE1ULL, 0x8380834654F7DA42ULL, 0x062CD1260DDB7D14ULL, 0x5A8A8A2CD5C60B25ULL, 
            0x1583B7C42FD111DDULL, 0xB8DA5077A7A10E83ULL, 0xD404C7E5FD1AC17AULL, 0x35EFF1B03D96FEABULL, 
            0xF3FDE5B1BBD529DAULL, 0xBCE411775BA2BCC3ULL, 0x2F4E908160247ADCULL, 0x913CBA56E5212C30ULL, 
            0x6A4ECEFC079E9883ULL, 0x8690ADD6CAE3012CULL, 0x0E8840824C14DB5EULL, 0xE12BA4CDDB5E3973ULL, 
            0x1FA4B01AE3A9027FULL, 0x518EBB3BB990E63EULL, 0x11CF27419650798DULL, 0x2076A651F78432E4ULL
        },
        {
            0x4E93A681141C08D6ULL, 0x192C65AA30E93038ULL, 0x8CCDBE6C2CF14442ULL, 0xDAB05481D6524B69ULL, 
            0xDCE183C889B57179ULL, 0xDC7493C806043B30ULL, 0x0FAD0BDD9CF2D622ULL, 0xEA9ADA3D2722C55BULL, 
            0xD97A526106BA1F25ULL, 0xBD7EEF42531CB487ULL, 0xBE9ACD5CEB4F19DEULL, 0x1CEB9CCADE94D461ULL, 
            0xCE37E2DE9E847952ULL, 0x45ECF056FFA01294ULL, 0x12D4A783C6EBDF5FULL, 0x593838F536A9989CULL, 
            0x7E0154F73DF324DEULL, 0xE3A6E7108A782882ULL, 0x66D315BEEC7A539CULL, 0xA58940CD1AB6706DULL, 
            0x3B447969C8711459ULL, 0x58356E669869E2BDULL, 0xCCC2295C409140D8ULL, 0x650F69AD5616DEB3ULL, 
            0x6102AE479E029B60ULL, 0x608E77F2A5AF5A50ULL, 0x4E58DA5BF8B6D039ULL, 0x2D041836D0EAFB68ULL, 
            0x72BC60FE649AFF02ULL, 0xF9C00A0684C97B04ULL, 0xB6D09BA34A8220DCULL, 0x72ECB04301FC772DULL
        }
    }
};

const TwistDomainConstants TwistExpander_Ankaa::kPhaseDConstants = {
    0xE60EDA64BE0C04FFULL,
    0xBDA4EC56A7EE6DBBULL,
    0x3CC5EB0AC25CDBE8ULL,
    0xE60EDA64BE0C04FFULL,
    0xBDA4EC56A7EE6DBBULL,
    0x3CC5EB0AC25CDBE8ULL,
    0xD3BEF9A04D69AF56ULL,
    0xB5E8C6FE9EAF98E0ULL,
    0x2D,
    0x59,
    0x70,
    0x3E,
    0xD1,
    0x07,
    0x0F,
    0x40
};

const TwistDomainSaltSet TwistExpander_Ankaa::kPhaseESalts = {
    {
        {
            0xB9CAAA1B438E0390ULL, 0xAF974FB2A79932D3ULL, 0xB311776ADF5947D1ULL, 0xBA73C03318D27A49ULL, 
            0x085CE020D3412B59ULL, 0xCF302D4349D5418DULL, 0x706B39B44F7C1ED6ULL, 0x4B3B1DABC0F81AE3ULL, 
            0x698820B082AACBD1ULL, 0x2159F815292B3319ULL, 0xD58836482594FD2CULL, 0x8BB94D3C6275D52CULL, 
            0xDAAA00F2116A72BFULL, 0xD855E3701C18D666ULL, 0x414799716EBF66B7ULL, 0xE99B58364329DD5DULL, 
            0x591BCCCFEA29A680ULL, 0x70D7B95E57F612A4ULL, 0x10D071187B389202ULL, 0x4D1BCC2CA0FA80B2ULL, 
            0x048B5D36E761D2E4ULL, 0xB817BD28D1D683ADULL, 0x01E49B677A8A9ACAULL, 0x7C430ACF1FC7F608ULL, 
            0xD83CA97F640B0639ULL, 0xC5D7F7BC9E8CE2CDULL, 0xA9ECB42BF04A298DULL, 0x59363642425FCCE2ULL, 
            0x1F9F280F4F50E575ULL, 0x2636039FA2A022ABULL, 0x90417F14DFBBE041ULL, 0xE6610DB8E3A00F26ULL
        },
        {
            0xB04F42AD4BE51F03ULL, 0xCF98FCD107A2DC69ULL, 0x643DAB667805218BULL, 0x763B4033FBAEC843ULL, 
            0x22D08254D4B4E66EULL, 0xB3E006D0E027EA43ULL, 0x76DE3170121EF6D7ULL, 0x4CC9A60F9897518AULL, 
            0x24452047BAC66DC9ULL, 0xB392C8C8FD75F9FAULL, 0x0979C308E452F62EULL, 0xAD567A159E210D9DULL, 
            0x7DA39850EF75B747ULL, 0xCABF02050901C015ULL, 0x2CBD80B953A83D5BULL, 0x8A98D1709B69659AULL, 
            0xEA38AF335F7DC1FEULL, 0x3A74DA5AFB3EEB2EULL, 0xD11BCDDF8A9B160DULL, 0xD4563A477A05D5B3ULL, 
            0xEDEDCACEF88D226EULL, 0x79E0282BF2636EECULL, 0x1B8BFB01078A078EULL, 0x8A4FCB08E0767A49ULL, 
            0xBC6F248C30362CFBULL, 0x959322887B219692ULL, 0x7A70A3147761C8C0ULL, 0xB1CDE0B6834C375FULL, 
            0xE0DB6DF4FD149AACULL, 0x4C1439F750B41345ULL, 0x5568224D163699A3ULL, 0x77EED896344C7B6DULL
        },
        {
            0xE6E66F14DF21EBB6ULL, 0xFB1E5C05D853EF5CULL, 0xCD4D766ADCCF8D9EULL, 0x1EDC321DC4F98479ULL, 
            0x3C6AF3940D75490EULL, 0xD20E409BB3CA3E8BULL, 0xBA22C3619A80EA25ULL, 0xFAA284F867036785ULL, 
            0xB05140492C3BD92FULL, 0x720510F28A39700EULL, 0xB677C2D053F5F3D4ULL, 0x4D6626658BE37E4BULL, 
            0xF5FFF9587A3E515AULL, 0xD5DB6AE8CBE915CEULL, 0xE7FCB75D99DDA33BULL, 0x8892F55D42ADCA84ULL, 
            0x17BDBFF59A5B525FULL, 0xF29FC6A2A200CA87ULL, 0x98EACDFE815BC32DULL, 0xEEBCB9BF7844D45CULL, 
            0x4A84B7D45C9CF9B3ULL, 0xCA37B8BE317DB65AULL, 0x10E7BE2448E5C82BULL, 0xAB47FC74A92EABA0ULL, 
            0x7895EE54E4F79771ULL, 0x8DCF9B529DE8DDEEULL, 0x07EA43CFBBC82768ULL, 0x080002EC11D4AB64ULL, 
            0xC658906D12CB69A2ULL, 0x3D1BD84F6589149AULL, 0x776E5523AC477D1CULL, 0xE6E91888748F5E86ULL
        },
        {
            0xEDEDFE0EF98157D2ULL, 0xB0133018C24306CBULL, 0x15237F5576C11D14ULL, 0xD8F8589F9195405FULL, 
            0x4414D0C4D2036142ULL, 0x468A5F4311E98079ULL, 0x0F0E6EC0B2B3E4F2ULL, 0x2B2B4555F3C6E907ULL, 
            0x81827D2564E7B986ULL, 0xCCACD2FC2EA3B5C8ULL, 0x0DD615837BE55529ULL, 0x9EE951B62734E232ULL, 
            0x7F84C200488FEF1AULL, 0x504B1EA88952B9D6ULL, 0x64B1F5870C30C9BBULL, 0x953E65CD31B7BF83ULL, 
            0xBE4A8177925942D6ULL, 0x37311567BD819961ULL, 0xF54562476C13B4DCULL, 0x5B1D588E3F4E62B9ULL, 
            0xE964FD4E2C6E1613ULL, 0xE2FF1138C3777751ULL, 0x1F8D1B0D3D86BC23ULL, 0xC9485D96577AA52CULL, 
            0xA70E07F7105172CAULL, 0x2F7C6A73B36BC114ULL, 0xF11277D7E5F7FFFAULL, 0x2848AA8FBA7E13B1ULL, 
            0x70F16CD61BCB674DULL, 0x0250903DFBBA9639ULL, 0xC738CCCC0D1712D4ULL, 0xEC0FBE100A458725ULL
        },
        {
            0xC935DF60AD95DEB8ULL, 0xA142B6687CBC86DBULL, 0x2A9925E1553DEE95ULL, 0xC97F6F61C26731C8ULL, 
            0x0A3418A8E685B1D0ULL, 0x8D7DE5BCA7A9F9D4ULL, 0x5EC65366D25F9A4FULL, 0x2689C78646913B24ULL, 
            0xAF14033B4811FF35ULL, 0xD01108AF89041182ULL, 0x117C9553FC190D18ULL, 0xB1572593247F533AULL, 
            0xCC52A626BAA28563ULL, 0x4B4D4521AEEDBCAFULL, 0x74CE494E53297887ULL, 0xA5EA5D46838925CAULL, 
            0x79DB564D87FA99D4ULL, 0xA53229A68F29489DULL, 0xF1C380C2BECA0C09ULL, 0xA2C4EB94E619D861ULL, 
            0xB87E1C5908F5F4A0ULL, 0x9299C712EBFBFEF9ULL, 0x48479E5AD32C2D54ULL, 0x023BF7EAB35C0E15ULL, 
            0x5E5EAFE2339BF502ULL, 0xD8E5FE720E45166EULL, 0x3621269D9ECA3281ULL, 0x15C0132896898FEAULL, 
            0xE8A87E1EFB8E8D91ULL, 0x78753AE30C873C09ULL, 0xF1DEAFCE9BD0F960ULL, 0xA31FFA7E0EC4004CULL
        },
        {
            0xD466ED68E833FFDFULL, 0x60555DD987DD6255ULL, 0x3800E2482EE32739ULL, 0xF097344299DF89FCULL, 
            0x715482D3E6EF7761ULL, 0xF9913F1215C9EAAFULL, 0x90911E867139E777ULL, 0x75A63F5E13DB75D6ULL, 
            0xEDC563A075414B44ULL, 0xF66BB26EB0A64F13ULL, 0x574B63397D127499ULL, 0x8FDC338D6E80CD8DULL, 
            0xD933BE012FBA484EULL, 0xBBC087B9E50D20F4ULL, 0xD58554350A50C38FULL, 0x46314090CEBF72F5ULL, 
            0xF58EA7D54786DDB4ULL, 0x43C802D733298D69ULL, 0x2A332381483E5139ULL, 0xE5213AE4FE6C3578ULL, 
            0x0913F89D55197614ULL, 0xA0309ACAAA70B8C7ULL, 0x17FCFFD6A5C5E2B0ULL, 0x9394E107A571527EULL, 
            0x2AB9E43798333367ULL, 0x200FB07CD2BEAB27ULL, 0xAB002C96556BE476ULL, 0x310F5ACC5385D4C6ULL, 
            0x6F4FFDC980737788ULL, 0x212E6C4EAE7B2B4CULL, 0x445036E2596CAA2BULL, 0x4B0600E63EB5F8BDULL
        }
    },
    {
        {
            0x49E3D4480C5CA07CULL, 0x375007E326D07C72ULL, 0xA190BE9578ACCD8DULL, 0x32E1EFA540D395CCULL, 
            0x9CDD4E97BBF29EEFULL, 0x267E177568AEBD54ULL, 0xFC4BD03921FE913CULL, 0x1E1D05184FAEBE93ULL, 
            0x16169EFCFFEB86D5ULL, 0x84EBE1554458B35BULL, 0x439989EDB5304653ULL, 0x3CFCFD4945D6CEF9ULL, 
            0xD24877627BFF6512ULL, 0xBDB7E3EE0CEB6E6DULL, 0xCC15E49B5F0EDC7EULL, 0xCC30071FA3629E96ULL, 
            0x38F33F98A4DBDE1CULL, 0x44A9E4B00FF90274ULL, 0x7602FCBF80C58245ULL, 0xBCF67EEEE29256F5ULL, 
            0x046D5F0269317B29ULL, 0x8E2E53C9F8B48A5FULL, 0x3650B1F16BD82AE9ULL, 0xF6599E22268E143DULL, 
            0x9D12ED0523AC95AAULL, 0xD54A10B2AC78230DULL, 0x2A67752A67F46D2BULL, 0x2E6AAD2DC6B7E4C3ULL, 
            0x7BE405979D59DB6DULL, 0xDB0563A6244EDA03ULL, 0xA35F8BE7C85F3E5EULL, 0xCD5C8195A2ABD08FULL
        },
        {
            0x616C38435C1E138EULL, 0x5D7FA3F48DAAEDBFULL, 0x017A10A18830BDC3ULL, 0xDB2624CF39420641ULL, 
            0xBEDD3EDBDF7B86D6ULL, 0xC7F75D4C10E1B4FEULL, 0xE6B827616C9DA904ULL, 0xE2190E821A26D9CDULL, 
            0x15282B2FF1615464ULL, 0x72D0DEF5FF35E385ULL, 0x96D2856F46DB58DCULL, 0x014EB1710B406185ULL, 
            0xD03B7347FC887DBEULL, 0x7D4ADA0468137AFCULL, 0x2A31768D46D84268ULL, 0xDCABAC7950C493CEULL, 
            0xC6B152D5C776F549ULL, 0xACF8BCCCDF36D2B0ULL, 0x1E4BC5F5E9D08C18ULL, 0xA986BED3A80B225FULL, 
            0xD7B658E887DAD09EULL, 0x925CF2A76A337828ULL, 0x95BA79E5416988CCULL, 0xC370177EEABC7B7DULL, 
            0x4ADF8E72EA5E6BE8ULL, 0xFB2B96C98974F15CULL, 0xC9F871709EEA6F16ULL, 0xDE137788C24B0032ULL, 
            0x071EE63964BE8784ULL, 0x32C1DB6D812D01B8ULL, 0x4E2C2D1916843DE5ULL, 0xF85FBFD5A78FF68EULL
        },
        {
            0x79652FC285A77AD5ULL, 0x38608BB48BC528AAULL, 0x2CA626ED05B0D053ULL, 0xA997181FFBA13965ULL, 
            0x44C6E6E7DA246FE6ULL, 0x237EB307567A353CULL, 0x2366525FE7DEA05EULL, 0x41BEA973DB039D29ULL, 
            0x3AFC381CE26BD5E6ULL, 0x83FE1C86A489989EULL, 0x9F45F8DC4EE88DC3ULL, 0x507188DA94092FF5ULL, 
            0xB45F16552625F482ULL, 0xBB0AD85FFBA3E6D7ULL, 0x97A9CB5E8FA72189ULL, 0x0B052E00D965A894ULL, 
            0xF41B9E8B945C0286ULL, 0xFDC07116B6805FC4ULL, 0x04B856552E7D55DCULL, 0xC75AB33105538478ULL, 
            0x54B890FF55BAB42BULL, 0x11BBD4100F63530AULL, 0xC0CFC1D93CAC2318ULL, 0x2AE1AA9AF56A7E33ULL, 
            0xE5B377DA34E4B493ULL, 0x2DF697DB12D5B5CDULL, 0x1C52E6AEBBE8BDC8ULL, 0xB0449A7BA741C99AULL, 
            0xE5361AC4BBE27309ULL, 0x609C68AF133EA967ULL, 0xE591788C7354AA2DULL, 0x1DB57077E151DEE6ULL
        },
        {
            0xCC59BE7D6EED5982ULL, 0xD571261BA68B2784ULL, 0x41DB045E1569544FULL, 0x6FF6ABCBFE44B914ULL, 
            0xB0D351A1F45BC482ULL, 0x80F0B309776CB8AFULL, 0x51F418E9A33F63FFULL, 0xDAC9F1EF12DF7B05ULL, 
            0x482E0D03BDCE191FULL, 0x9F6CC60677D07DD3ULL, 0xA4885FE415E0BD56ULL, 0x54DE085075792C71ULL, 
            0x7C6884FCB4A6185CULL, 0xF9896AE24C32904FULL, 0x2F6CC02882466789ULL, 0x2F697D3A69EACAB0ULL, 
            0xC49459C9BF112EF2ULL, 0x6E049C545A71EFD6ULL, 0x37094B294C34592EULL, 0x2086FE83E8112467ULL, 
            0x001A0F6525E0F1C1ULL, 0x5F5B2C7B9BA1C93EULL, 0x1F778F2A1127DEDDULL, 0x2331F9EEB75F70B1ULL, 
            0xDC5F2D47B698ADB1ULL, 0xA1703402A098A307ULL, 0x0DC46B2D63529927ULL, 0x2A4851C829764C48ULL, 
            0x6FF511F440417BD2ULL, 0x4B61C9AFA29FC46AULL, 0x4A79E5905FED3204ULL, 0xA65ED5C6F16E4D3AULL
        },
        {
            0xEEDE820B206C2A0EULL, 0xA3AEC85FEE2BA106ULL, 0x8D36D11531934E08ULL, 0xDB7E71447091CB7FULL, 
            0xCB2AA1707F4CD4CAULL, 0x5F3E1398D9C69E8AULL, 0x24E0C2D693FAC210ULL, 0x4E6C8279970CEC80ULL, 
            0xE26D8633A7A786D9ULL, 0xFDA18AACCAE63CE1ULL, 0x6C166357502BF6CBULL, 0x6A07B5F281927FA8ULL, 
            0x7B91B3D706ED1AC2ULL, 0x851785EEA3446275ULL, 0x2929258FB221EE05ULL, 0x7BB2C13F0B72EA22ULL, 
            0x9A3160136BFC4D03ULL, 0x7B337FA39DD562D1ULL, 0x751E5846146FDF2DULL, 0xE7DFB046C06DF089ULL, 
            0xF9ABF69B60DAD66FULL, 0xA3642FB835E1DA94ULL, 0x692447AAF71193FBULL, 0xAEB5C088296708BBULL, 
            0x3020928F9E0F5DB9ULL, 0x3922ACC96F45352BULL, 0x6C640A781C399F7AULL, 0x57A885477919F9F7ULL, 
            0x9C0FE4D9C574B7B1ULL, 0x34107F515F6B72BDULL, 0xBCFF65EB9361CCFDULL, 0x07F1614D7A35640AULL
        },
        {
            0x297C32AE850EE89EULL, 0x5225A470C27DD57CULL, 0x6EC532902E75AF87ULL, 0x538AE599426D98C4ULL, 
            0x93244869A6A924FEULL, 0x0EBCC364765A2E3BULL, 0x728E6D78AD0A24B7ULL, 0x17EBBF297CDD8EBFULL, 
            0x01C20F3DB77723F6ULL, 0xAE1606D6780476CDULL, 0x2FC9331DF7CC8F92ULL, 0xFD069F43524F9FDEULL, 
            0x389992C8E71BE14BULL, 0x8B7EEEC07D7C0490ULL, 0xEB3CEEF70348D839ULL, 0xFA7EC9BB4766ABCAULL, 
            0xBCB2F9AB2C78886CULL, 0xBAE492837DEFED95ULL, 0x82A11BE073F072DAULL, 0xE1DE11B72F30E0C6ULL, 
            0xC5AE78BE1EA649F9ULL, 0xC0388CF5C295D4F7ULL, 0xAF2110A7C5EF6B70ULL, 0xF39924827B055FD4ULL, 
            0xD7D95F7850C49D5DULL, 0x2A05E2C9F2ABDE86ULL, 0x004F11D9A9895E0EULL, 0x7100D9B87E9C831DULL, 
            0x11602AA37181FEF8ULL, 0x2F7876234FBCB82CULL, 0x245B39BF4BEE00F3ULL, 0x30223637897D1EFCULL
        }
    },
    {
        {
            0x773715223A25F4B5ULL, 0xAEABEF50910272E6ULL, 0x1417F4AF59B35E17ULL, 0xD35414E24B25E78AULL, 
            0x6F03C0869239BDA2ULL, 0x2674C3E59E11C9BBULL, 0x824BEECF6B5C6421ULL, 0xA8084A243393884AULL, 
            0xC1765F0D4C3B37B3ULL, 0x9BA46ECD2F232807ULL, 0xC4BFDF95C3AB6B38ULL, 0xDC59CF51BE8C6D4AULL, 
            0xF0E83740BF2B5244ULL, 0x8F915D012B70B570ULL, 0x578A957250D31F1AULL, 0x1770CD789FB3B473ULL, 
            0x75B294FF103D07C6ULL, 0x19AF0F369238C54FULL, 0xB7D3D0E02BDDBC2EULL, 0x3894D7B246A0E95DULL, 
            0xEE557966DD846560ULL, 0x7B2C291F5D820F46ULL, 0xEFD61E28943037F5ULL, 0x5582C8CD118EB76BULL, 
            0xB749BD4F12661D78ULL, 0x0EEEB5D65B666E0AULL, 0xC7AF2F79A3D34322ULL, 0xE9FCF343B8FA18CDULL, 
            0x543273E5DF091903ULL, 0x5E8A306A5B7C3521ULL, 0x79FE4425F4BAC3F7ULL, 0xE20360CA2DA7CDEEULL
        },
        {
            0x05FF409963F72694ULL, 0xB42A93032BA07445ULL, 0x2C4597194F93889EULL, 0xB6EAF08B9DC4F46EULL, 
            0x4F1C5008277AC5FCULL, 0x484423DE1520B739ULL, 0x7D7D5F4D2D5BB9ECULL, 0x4F426B8903147E29ULL, 
            0xF5895DBF89744388ULL, 0x659DB238CEE6A719ULL, 0xFA934F8789DAF39AULL, 0x61F4B67BBBE1D7B1ULL, 
            0x4BD860FE1835B5A0ULL, 0x7EE4C285F407DD0BULL, 0x04C1E968DD5EDBB7ULL, 0xC8186BF0AF1730DDULL, 
            0x2429859025E2A835ULL, 0x1B50994356B50140ULL, 0xA969B3380986162EULL, 0x3F18F0CF057D5D1BULL, 
            0xB7B4057A9E74D772ULL, 0xD85727A04C56B0F3ULL, 0xDC8507F75ADB48C7ULL, 0x6B84009E98109DFCULL, 
            0xDAF6E4DB21BA282EULL, 0x227641711205F73DULL, 0xBCD6281C9183F339ULL, 0x317CC31854FE9FA6ULL, 
            0xCC0BA7F15ADBFF3BULL, 0x6CA1F2675A02CE82ULL, 0x53A847390F50BE6DULL, 0xD0579FAFA8AC2619ULL
        },
        {
            0x7F0C0096873B0FCDULL, 0x9847CC083650CE7CULL, 0xBE2F52256FF5146BULL, 0x1C7555D03BCA2433ULL, 
            0xAC5EA764637367FAULL, 0xCE178C62373B9F28ULL, 0x687444AB645BC776ULL, 0x93AAC63409FB52EBULL, 
            0x5D1708A19E50AC80ULL, 0x2EB7B6531AC5B5FEULL, 0xC4ECC7915FFA0B9FULL, 0xE2AF51257B9552AFULL, 
            0xC93A11C702455300ULL, 0x8F32618478E75007ULL, 0x8B4AF1F23AFF2A78ULL, 0x6FBE1A045EA32A21ULL, 
            0x70F1C98FCCA1CFCAULL, 0x4DC44EBE03891666ULL, 0x1AF6F49F96175CA7ULL, 0x693D0AC7C2240EA6ULL, 
            0x99A8A11F4C2DD05DULL, 0xD69DB27EF6EE1B99ULL, 0xA5FEA8F911350568ULL, 0xB18F5CA0B4523E6DULL, 
            0x7406B7CB9B1ADFC1ULL, 0xB2B0BDACFFC0334FULL, 0xAEF7FA6EFCE97E02ULL, 0x3A63B4EF3BF8DC5BULL, 
            0x5E608742514BDF1AULL, 0xD240C3B6E2D50C96ULL, 0xF11061A135B84196ULL, 0x73120E30188F7120ULL
        },
        {
            0xCF4D6399626276EEULL, 0xFB7958B1175DAD5CULL, 0x28BCC574F106106FULL, 0xEEF137F8208E3BBBULL, 
            0x7133A06E3172F28AULL, 0x17DC81E3C775926CULL, 0x5694D35C8592B5B4ULL, 0x495CC088CD22EE3CULL, 
            0xD384229515DBBD69ULL, 0x638DD265A8FBECD8ULL, 0x12451EF517B83FACULL, 0x4F863D80BEC0DCE1ULL, 
            0x60CF8DF507D9B0ADULL, 0x782E67349532C9B1ULL, 0x20C260E00F07A60EULL, 0x57D516D56B1913A4ULL, 
            0xE1B0A5A9A8ACE2BAULL, 0xAB0DB6E4E8BE8119ULL, 0xC196C37E7CB62347ULL, 0x9D53238EC9CD7B84ULL, 
            0x729240910515521CULL, 0x25489ED5A85EE45CULL, 0x8FB63D600097BC06ULL, 0x5B8A66D35CBE9F38ULL, 
            0xCEE411F88D4248C4ULL, 0x061F20EDE942BD2EULL, 0xBCD3D685E2302B85ULL, 0xC404AF5D4AC9C8E3ULL, 
            0xD09BBFB5A2EE9018ULL, 0x5F5FBD8369860D2AULL, 0x931B01E1547C535CULL, 0x27C570CB925A5297ULL
        },
        {
            0xB261E97B7D91600BULL, 0x1B8C5B3A3E0DFE54ULL, 0x7F76864886DCC681ULL, 0x585DDA6C578B2926ULL, 
            0x30288F2CFF3F34ADULL, 0x4AD213FA56DB25A4ULL, 0x4C99B07E183D1C9FULL, 0x274C11347A6B4893ULL, 
            0x8AFC2A2BB82D9120ULL, 0xE6953E171E54F57EULL, 0x6DBD0D9C4E41A576ULL, 0x5AB97D5EB1D2A7E0ULL, 
            0x25E197F90606776DULL, 0x2B946B460344DF9FULL, 0x4C6D33BB73EEC71EULL, 0x1A6EA830FEFFA6BBULL, 
            0xD9E4E499A880A251ULL, 0x5B02211C0CE056D7ULL, 0x1FC58455AC5DC1D3ULL, 0x9C3C42C1EB8DC6EFULL, 
            0xA3C7D05D23FF97B0ULL, 0x39AB2F4EF5D5FB3EULL, 0xF5664CC2B5F74680ULL, 0x059E0CF0EA324076ULL, 
            0x9DFA3300B0D638A9ULL, 0xA94B9AF28D8B1BB6ULL, 0xC18D0C67FB339BBEULL, 0x80992D4B82718B29ULL, 
            0x70039C98FD051AEAULL, 0xA0B2E89FD2491138ULL, 0x4577CD6B6DFEC92AULL, 0xA6AAFDCBBB046CE9ULL
        },
        {
            0x5BDA6D4F78A950E7ULL, 0x9B43DCC6DB0DFB31ULL, 0x2BA64957A900EA47ULL, 0x2EA0661403073BA0ULL, 
            0xE023071B8B77AF67ULL, 0x50183D01DA7DF660ULL, 0x2D91D22B9287A832ULL, 0x2DDD3B980BD69826ULL, 
            0x5EC6B933F759F822ULL, 0xB60238E03086D85FULL, 0x6E595079F8E00799ULL, 0xA4CE011160886EA3ULL, 
            0x5878C5584246FCC4ULL, 0x429C6ECF0A424A7EULL, 0xE610C7D5D9AB7E3BULL, 0x6C6A756CB2AB5417ULL, 
            0x34B813F738D06C8BULL, 0x187A726DA1ED69A1ULL, 0xE0A28E14A6B456F3ULL, 0x7ABEBE500F030206ULL, 
            0xE1EB9747F946585DULL, 0x68200785F2EE77E4ULL, 0x88E9946B33761A50ULL, 0xB5F45F7B70BE42BAULL, 
            0x8459B62587F3746EULL, 0xC51B7C2D8A4003EFULL, 0xB3ECE372CFF9DF1EULL, 0x40A5BF6EA39BF492ULL, 
            0xD2AEF6C48138CE99ULL, 0xDBD35107994604D2ULL, 0x878CE205DCE566B2ULL, 0x4E7F25345AD71BB5ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Ankaa::kPhaseEConstants = {
    0x8D74192020EC93A7ULL,
    0xD7E8DB060DC74C8DULL,
    0x23F6B1C2AEBCD628ULL,
    0x8D74192020EC93A7ULL,
    0xD7E8DB060DC74C8DULL,
    0x23F6B1C2AEBCD628ULL,
    0xBD184D33A3EDF6CBULL,
    0xAF04EB7C1743A654ULL,
    0x14,
    0xF0,
    0x63,
    0xC7,
    0xBE,
    0xEF,
    0x3C,
    0xCC
};

const TwistDomainSaltSet TwistExpander_Ankaa::kPhaseFSalts = {
    {
        {
            0x7DE84AE5F6656A4EULL, 0xCD74E78791715125ULL, 0x3CACDB6ABB2CDCE1ULL, 0x958724B7CF4210C4ULL, 
            0x9F70ADF32DA2918BULL, 0xAAE83EFFF8A20E7CULL, 0x2A5551FFC9E2A3A3ULL, 0x357BC5FDE5EE23E7ULL, 
            0x418F62FC708E7F31ULL, 0x6D1BD36867FE5ADEULL, 0x2FC9077A5E93B62EULL, 0xD50E6E9D19A7627DULL, 
            0x9022F57CE3009E40ULL, 0xE256222170875423ULL, 0xBD16D403F96E15D0ULL, 0xF1BB181B68FF1134ULL, 
            0x8482284B37D469F2ULL, 0xBF64163051631ADEULL, 0x9BD375CC9C0107EDULL, 0x4E8130BE5EF7C7ABULL, 
            0xF90B37D50DD927ECULL, 0x5478A15DE89A452EULL, 0xB648BE44B69A8B3DULL, 0x586CEA230507E856ULL, 
            0xA0528300B2CB6E5CULL, 0x79A141F1388655BCULL, 0xDEE972831CFBFD55ULL, 0x62C149D500E0301EULL, 
            0x1B9EDE3EB62D5FFCULL, 0xA87F4247EEF41EDDULL, 0x6F8685F0FCDC3657ULL, 0xF8288B9C4BB8945EULL
        },
        {
            0x81C680692A38E0D6ULL, 0x17CD213B493CA861ULL, 0xEDA93D7E642CBE0DULL, 0x4283836E688999DFULL, 
            0x4F7247BAA168DAA8ULL, 0x782F485E1C82F6CCULL, 0xCDDCBC3E33E5F340ULL, 0xDC6817B70D239FA6ULL, 
            0x784173490C4F6437ULL, 0xA80434DA986A0C83ULL, 0x7B4A522D0958AB94ULL, 0x8E285214A55D5781ULL, 
            0x0E4416CB025A7E1EULL, 0x478D358356E601D6ULL, 0x66A1DD65333BB8D3ULL, 0x3277DA9B8A234E23ULL, 
            0x1F152EF97F06D975ULL, 0x51B6FC3BB538FDDEULL, 0x2E03177366BBD3BFULL, 0xAA3C8AA57858084FULL, 
            0x04051B79FF5F0E2CULL, 0xD3BD7F37D07AECD5ULL, 0x2BC70799C8FF4F2BULL, 0x4B2DB2C807927EFEULL, 
            0xC0C4AEE0AC52120AULL, 0x54060BB350AC7611ULL, 0x5A33BF4EB9B0BA87ULL, 0xD484C385B590D552ULL, 
            0xF8E1CD46AFC1C97FULL, 0x7C6253DD7428FD39ULL, 0x1F0595525CCB8A87ULL, 0xA80718852793BA12ULL
        },
        {
            0xCEC5674DA27CFE6EULL, 0xB59EFE970D77CFADULL, 0x79EFFF42BCD99031ULL, 0xF97CB6947780BE17ULL, 
            0x4F1F0B40AFAF68FFULL, 0x8D820DBA3CE7AD88ULL, 0x4BC46A21446E700FULL, 0xEDFA8931FDFED2E3ULL, 
            0xF3123DA17497012BULL, 0xCB6989793481C1E3ULL, 0xC1284182D2E7CE6DULL, 0x1BD919A7E3D4254FULL, 
            0x07D76196F998ADBDULL, 0x080A16C52557A2ACULL, 0x99799A1785C32DB3ULL, 0x3918483A3FBC0AD2ULL, 
            0xA296233E32E46045ULL, 0xDF448E7057050CC0ULL, 0xA11D10A9F4E3138DULL, 0x7BE54A76CBA3C036ULL, 
            0x4F9D12A6434C8A90ULL, 0x59884BFE96FE1A51ULL, 0x5DE2711B00999741ULL, 0x611A9DBA458A9B41ULL, 
            0xB2B234E7E9FC0EC4ULL, 0x0000C99376E65B3DULL, 0x27186E33A8E004DBULL, 0x817492746A2EB554ULL, 
            0x0D7FE9BA2905F632ULL, 0xD41FED5464164B98ULL, 0x686B4D4A5D68D7DBULL, 0x11102E261FE2E77DULL
        },
        {
            0xF9F7076BE90E7078ULL, 0x93990858B8BF9528ULL, 0x9365AEA52BF94A23ULL, 0x115C1B4A6DB2D940ULL, 
            0x8B8D57F1862C31CFULL, 0xAB66A98F9C9705E2ULL, 0xBD9E071E964BD209ULL, 0x0958D8BFE3A827B5ULL, 
            0xA22F72F1CE985B64ULL, 0xADEEC6CCC65B4A34ULL, 0xABF6FC73EBC606BCULL, 0x1FD1DD7A547B7E2FULL, 
            0x2D4CE5529F8AADE7ULL, 0x58863614594E3BBFULL, 0x7180DF512E9BD79DULL, 0xE52B9FF6FEC3722FULL, 
            0xABE7B13333FF695AULL, 0x3C96B43A41A3801BULL, 0xBF25248FBFF8B282ULL, 0x85E97105BF3A3E26ULL, 
            0x5747C7BACC08994AULL, 0x41B15B533DFBDAF6ULL, 0xCC080332D6D4483DULL, 0x8821F87B7D316C94ULL, 
            0xEB89C52737DFB020ULL, 0xEC0ED28BC455BD81ULL, 0x5D93BF360B05DA33ULL, 0x2E903E5DE31D53E6ULL, 
            0x97472D18380C97A0ULL, 0x7B75C1806DAEE359ULL, 0x21BF383C982248F8ULL, 0xB4E7B29CA518FCADULL
        },
        {
            0x09C9C4817C6949BBULL, 0x8634DEE1B09B308BULL, 0x6CC4AA352A1D6561ULL, 0x633C464391FE64A4ULL, 
            0xE8DEEAFC95DF1A56ULL, 0x47BF7A0E5900B3C3ULL, 0x57A4C8F63C311FB4ULL, 0xBD690FDA8DDD409AULL, 
            0x40B6D267580ADE2DULL, 0xEAC995BCE351AEA9ULL, 0x15564226B2EE15C8ULL, 0x4D89C6931BB737B1ULL, 
            0x62E113D19BB6461BULL, 0xAD84603490E15DC1ULL, 0x7CE740370023AE4FULL, 0x8F9502E6CAAFA597ULL, 
            0x167F4CDE6B01F6A9ULL, 0xD80B364F38D3E136ULL, 0x7CB3264B13AAC54EULL, 0x3C9DB1C67BBCBEE4ULL, 
            0x4C1D74970875C9F8ULL, 0x0269417AB9A54A5CULL, 0xB4546F01F2254892ULL, 0x74F8BAA3DD03B3AAULL, 
            0x005A4FF4C4C9F928ULL, 0x777E7E1A3B3FFDEFULL, 0xBC6A3F886A28B97EULL, 0x59A981CC6EC15CC5ULL, 
            0xC57F8F8E13D73C18ULL, 0x3BF07E8FD5993BBDULL, 0xC42CAD2EF43333C2ULL, 0x7926B2D04E2AE9CDULL
        },
        {
            0xD8115CB7D92EFB56ULL, 0xC8939B1E4ECF9A26ULL, 0xEF67F922C07CE8BAULL, 0x94637150A639C125ULL, 
            0x246D6BD8B4A546DCULL, 0x1D2093EA75D36D8FULL, 0xDA6C0EB9A66C7109ULL, 0xC02B63A7D6CCD377ULL, 
            0x0443F54CB888CFA0ULL, 0x12CBA034EC795D9CULL, 0xC103EB9AD0087F60ULL, 0x59CADDC4E820611FULL, 
            0xCF26CDC9FFE7F42CULL, 0x3458A5F13362A301ULL, 0x758A0E7783273F69ULL, 0x01827BB7E61E0CB0ULL, 
            0x6BED8914E2BD8182ULL, 0x260E9035384B6365ULL, 0xE64A8D43D00513E5ULL, 0x93F79FD4B45EF8BEULL, 
            0xAC26B4DF553FEBA1ULL, 0x39153A16AC9DA99FULL, 0x88D9D8DF7771BB71ULL, 0xE993CBF12370B92AULL, 
            0xA3A30BD49517DE58ULL, 0x637A4D91724C8BBFULL, 0x5471FCA17590A6E2ULL, 0x857E491EA85DA233ULL, 
            0xC7CB1906E2C7327DULL, 0xF8F6AD2E30F647E3ULL, 0xCDF552FDB292876EULL, 0x7ABFB1431F24CEA1ULL
        }
    },
    {
        {
            0x5E003204A513E134ULL, 0x05698FAAE018825EULL, 0x050BFB4ABCDA7184ULL, 0x5FAB9FA71EEA32A6ULL, 
            0x88B658B4BE0D790BULL, 0x0B47B8DC00378223ULL, 0xF8BC7424CDDF963FULL, 0x2C6EAFB07234A06BULL, 
            0x5ECFA6B096BAFABBULL, 0x47A5306E106264A3ULL, 0xA8BA9729E778A8BBULL, 0xFD449367A824EC56ULL, 
            0xB162EA0E81C74886ULL, 0x2717B79124C65395ULL, 0x9B75875B601CD623ULL, 0x2108600D435C1CEEULL, 
            0x8C2207A7387A0C3FULL, 0xA1760E46206642AAULL, 0x581C4B4E31D8178AULL, 0xAA63F51B49E2419BULL, 
            0x88E373009BDBC59BULL, 0x04196994F8382061ULL, 0xFA285EF537044EFDULL, 0x0A4E8ACE30893B44ULL, 
            0x987BE812717D168CULL, 0x66F107F13999B455ULL, 0x3F8B7464265CA649ULL, 0xE2F29E1CF4D2FE1AULL, 
            0xEE4CD791E1AE3F90ULL, 0xDB8F802897D18F6CULL, 0x9D64B6D7E58DE12AULL, 0x0A393F6898537435ULL
        },
        {
            0xA55724FA97182D83ULL, 0xCB283C668BF7AC7DULL, 0xAEA5D57074F4654EULL, 0x4FF0CC2BCC2E4000ULL, 
            0xA1757B60D31192CDULL, 0x5076585C664E5663ULL, 0xDE6940B301598F77ULL, 0x8E9951BE50AAB059ULL, 
            0xB88509C5E3F6A303ULL, 0x62FCD720E89EC9BEULL, 0x856D1F881359574EULL, 0x5674B79B91ADB893ULL, 
            0xD3FF8620C4825F91ULL, 0x108AB2D94231677CULL, 0xDE50BAF5E0540AE2ULL, 0x357BF9533C0C184CULL, 
            0x5B4CC43FB87414D4ULL, 0xA8C372260BB91729ULL, 0x0EB734829BA8E376ULL, 0xC9F11C3666CD018FULL, 
            0x836C0F4A8A1E7D31ULL, 0x1F49AE583C97E8F4ULL, 0xA7D595BDD125AE2DULL, 0x823B1299E68FE42EULL, 
            0x36A1FEDC0D6E9A65ULL, 0xC3F8F90CA333825AULL, 0xE9B21968C702EC86ULL, 0xA5998DFB404405AEULL, 
            0x36BDAA7A319DACC4ULL, 0x444509329B03A6A3ULL, 0x9D83799FE4CB8965ULL, 0x2042DA1A2EA4C231ULL
        },
        {
            0xB32E47054B3B75F4ULL, 0xD7237300F08B8EE8ULL, 0x22C3159458175472ULL, 0xA115DF62ACBE73F3ULL, 
            0x2A90D814118A4CC1ULL, 0x7D2A3B35924650F4ULL, 0xC948AE352A010267ULL, 0x225402AA7FCD7682ULL, 
            0xD5819567BE0B25DEULL, 0xB005E3261FBF9C54ULL, 0xE9B974186CBD4AC7ULL, 0x713BDFAC4C44FF2EULL, 
            0xAE71AC89BF5ED260ULL, 0x97E4BAD0862B2CCEULL, 0xA759AAC517454572ULL, 0x7396D67AB1ECA16EULL, 
            0x0BC9F6352D286642ULL, 0x1E682D06FE2AB302ULL, 0x120F6E86FF542596ULL, 0x4F79198EC848A864ULL, 
            0x99A97A73968C7230ULL, 0xA408F6745DC8EDD4ULL, 0x29DC6DC2CB2B90DFULL, 0x5CC0318446FCC42DULL, 
            0x15C4CAF0EEB91B85ULL, 0x4AA77C01577A9C3CULL, 0x2E5E17931A9813E1ULL, 0x12A568CA522A5136ULL, 
            0x736CC07DFD27EFDEULL, 0xE4628F0E22F985D7ULL, 0x1FCAD185D00466DAULL, 0x8EBD29D0612811E8ULL
        },
        {
            0x462CBCD1A5C2BF9AULL, 0xD8AA0B28AEB5A363ULL, 0x632A2FB65FA9BFC2ULL, 0xB99192F9FD9E98FAULL, 
            0x83189C66DF5264E4ULL, 0x5C16E935FE6A8C4CULL, 0xC6626CDD3350747FULL, 0xCA9C395BB5A598D1ULL, 
            0xABAEF4DF6B338DFBULL, 0x295F91837A5792A1ULL, 0x0431A6882D663CFDULL, 0x4021F88E2C0209ECULL, 
            0xAED988DDB99D44CEULL, 0x4AD22F92820DCAB0ULL, 0x4B2D25642AD2C072ULL, 0x880CF5536452F0BDULL, 
            0x5F50D6BD6B762CBAULL, 0x7C2F6C12B0F779B9ULL, 0xEAADCF028AFA2ED1ULL, 0x92C399116060E44BULL, 
            0xD827019B2A706F94ULL, 0x211A5D41587DD1DEULL, 0xCCFB278C73F6FA00ULL, 0xBF962134D2B4F39BULL, 
            0x8AC7E0108E7C2A3CULL, 0x666CC34C433A0E99ULL, 0x3207DF6F98977D1CULL, 0x1BD32AE0C031A663ULL, 
            0xF2C1776CFA87623FULL, 0x7CFDF2C3E384D228ULL, 0x38C233720EF3097DULL, 0x2BA6C64C1997F1BAULL
        },
        {
            0x93538B36BCCA2B26ULL, 0x3ADBD4553E5F9BC4ULL, 0xC8B298BF26ACA0CCULL, 0x1219A68CF81D1183ULL, 
            0xAAD677B6F9585C1DULL, 0x5478B817E6FA4C5FULL, 0x76A5E91DF846CF28ULL, 0x498BEC47AC2BDA2CULL, 
            0xF3A3E3E4E7EBD3B6ULL, 0x9DA1E7E9F72029C8ULL, 0x9AA64C6558617AF0ULL, 0xE33590B2900FD1C8ULL, 
            0xD96CDEBC4FC1230BULL, 0x2CB1B585BE9074C4ULL, 0xFA4D95BE8A20DFD8ULL, 0xBA5D6C1651D2F83BULL, 
            0xEFAAE5743186E63BULL, 0x31232D5A74D722ABULL, 0x59828DCBE255AEEAULL, 0x3EEE25CB40E4CD6EULL, 
            0x28910170502EA009ULL, 0xA2D97F40EF3D147FULL, 0xF61CB5AEB657FEAAULL, 0xDB5321D6C255318EULL, 
            0xBB02AC5FAE46406BULL, 0x9571E0697E58668BULL, 0x545DDA46856E6CC9ULL, 0x3DC4971E7E001534ULL, 
            0x296C549CABB34122ULL, 0x9498693E60BC58C8ULL, 0x34FFE3557CFB7395ULL, 0xED48289213627588ULL
        },
        {
            0x30D94BECD8C6F05AULL, 0x6B550FCD6136B610ULL, 0xB15A548175C44943ULL, 0x15C2CB839375B39BULL, 
            0x25C4CD19D2028110ULL, 0xB32F1972049E6ABCULL, 0x5D46C5075BD962CBULL, 0x6E6EC5628C011611ULL, 
            0x51B4F24B8054B80DULL, 0x0853685E30BD471EULL, 0xF6140979946C28EAULL, 0xFEFE99D7E9D46141ULL, 
            0x1FC0811240CF4F79ULL, 0x0C95A354A9AFD086ULL, 0xD76C4E620947314CULL, 0xF2FA100111367190ULL, 
            0x6E72EADE41260B12ULL, 0x0DAD2F9AFCA0960EULL, 0x525EA457A73BBBB1ULL, 0xFE0CADBC4E252AB4ULL, 
            0xBB0ED1785CA1C083ULL, 0x8DD6108AA4E219C2ULL, 0x4BE5CA56F41BAEF4ULL, 0x0E9B2F371CBA0BFEULL, 
            0xBB4D476C56F75968ULL, 0xB4CD166EAD3D7A2BULL, 0x4780D0A331F1F169ULL, 0xD7AF8CBFAB41C8E2ULL, 
            0xCA93BB364624C19BULL, 0x69F8744A1FE1A824ULL, 0x16C03B5B6D8B4EF3ULL, 0x7183DE16116B1799ULL
        }
    },
    {
        {
            0x9F299953EBF79DA4ULL, 0x4FC33941499F6A1EULL, 0x32252B52D06421B7ULL, 0xA75EBF2271E0516CULL, 
            0x74B6F2A17B2F7C03ULL, 0x22FFFB99F0EB20A4ULL, 0x6E06B22494BC9A68ULL, 0x40D5CFC719AD5DF3ULL, 
            0x5DA9D23E90F8E6ABULL, 0x03017C12102B6051ULL, 0x86083B92C9867307ULL, 0x6D7D55A8E56A2894ULL, 
            0x229EF80E871321F4ULL, 0x5AF3205976E66FA4ULL, 0x5D56DEBB346D02F2ULL, 0x33D387FCF70BC5FFULL, 
            0xE527D4BDF0C44A82ULL, 0x386C5245EA2EE2B3ULL, 0x11F88FBA69E2789DULL, 0xF5F11F6E3F1E99F7ULL, 
            0x92A821D19F0E1231ULL, 0xF00582F9108999C7ULL, 0x8E29633C128E4CA5ULL, 0xE5A9E2ECC57188DDULL, 
            0x59CE111A5E550A1AULL, 0xDE0B86A99BBFED0CULL, 0xBCA1668129CDCB96ULL, 0x2EE9C043612DBA40ULL, 
            0x6FBAAC8DA60BF808ULL, 0x0946813BEA237A64ULL, 0x94274D180EE8151AULL, 0x8C15CAEE990E5113ULL
        },
        {
            0xF2FFE93FE056A2B7ULL, 0xD5C79BF36A1E5547ULL, 0xC6F9DCD6DA5E1840ULL, 0x1765F6B8230AE787ULL, 
            0x2C6046F5E58F7A29ULL, 0x08378D8AF5C0B9BAULL, 0x818D814D3163D85EULL, 0x3691725CB9E517F5ULL, 
            0xFF2A2E122F0150F7ULL, 0xCFC4372E09160220ULL, 0x262E8B834DC879CDULL, 0x4CB437EDA7097C70ULL, 
            0xE36427B1DA5A1919ULL, 0xFFA9D54BD383749EULL, 0x416B6DD790A9344AULL, 0xD24C76767D9F6CB0ULL, 
            0xC9FDB705C3FB2896ULL, 0xC93663AD835B0A97ULL, 0x0C40FC45CB0BDB06ULL, 0xB2EDDB9C56B3C6F4ULL, 
            0x7A753C51606E8426ULL, 0x8EB0D11871D9C09BULL, 0xE82D5D1550465506ULL, 0x4328956B7A85BA37ULL, 
            0xAF7863FA1C2ECFC0ULL, 0x1A0C3D82226BCB23ULL, 0xB639897975E1B319ULL, 0x15236A71F86E3B55ULL, 
            0xE12A47129069CDA4ULL, 0x08E433052A8CDE29ULL, 0x2BB974CC23E0E468ULL, 0x341377D5B1CA6738ULL
        },
        {
            0xF7B466197DD877BEULL, 0xEB346FAD3CCC88EBULL, 0x91A35B38A03956E9ULL, 0xC67DE43A3D0A5B7EULL, 
            0xABD19F689AAE0261ULL, 0xDDDD1A359A7B6FF3ULL, 0x5358B2882AFD8923ULL, 0x84179EB8998F810BULL, 
            0x08549153C84ACA5FULL, 0x3D5232F9DD6D0AE9ULL, 0x958672BDD5E9202BULL, 0xB2EC31CB89A370A5ULL, 
            0x79CE0BF83F5F4EA4ULL, 0x35422A450360A87CULL, 0x9B689F765B4605E8ULL, 0x8F8DAAC68EC4090EULL, 
            0x535D569ADB1BFB70ULL, 0x110C4BF5E7E74CC9ULL, 0x1DA1EA7163F9B44BULL, 0x6133712BDC7D8CC9ULL, 
            0x800431C093556B5EULL, 0x9EE8B4C2B714EBB6ULL, 0x3F7DF23530FF255BULL, 0x43B61DADB4532532ULL, 
            0x97C048CFEBEADC19ULL, 0x827774E387EFA5FCULL, 0x57D0F4CE997F8866ULL, 0x9904F4854B920920ULL, 
            0xA09C9C0348DE0344ULL, 0x5140D19FCEE40603ULL, 0x06CEA3E221DB354FULL, 0x9BAEA42CF434C5EDULL
        },
        {
            0x271E7C83927E4EDBULL, 0x33DE5D719D1B70FAULL, 0xC4D8694C8907AFCBULL, 0x4168F3205B528211ULL, 
            0x0541745B0D2B9195ULL, 0xF530957DDC6DA06BULL, 0x9DB838A725194313ULL, 0xF6EC272EA58B154DULL, 
            0x5A51FA9F4FF41A6FULL, 0xF7AA9A346C3E4FB3ULL, 0x04404DFE060BFD78ULL, 0xC4178C587D3A34C9ULL, 
            0x2F948F71192BC982ULL, 0xD5D12E7313282108ULL, 0xCEB6FF5EC21C4FC2ULL, 0x1870FFE37BCB8929ULL, 
            0x6C4B61218671DDDBULL, 0x3182CAE9F07537DEULL, 0xF8D6F66949FFC67CULL, 0x5B309FB94345AFF1ULL, 
            0x0FA7C3E62E4EE04FULL, 0xD14B90E061DFBE51ULL, 0x1B9D32714A9BEAC9ULL, 0xCEF1961D2E8289EEULL, 
            0xC2A910724AA4B2A7ULL, 0x23439B10BC848208ULL, 0xDB270A6FCD8F7554ULL, 0x34AB7780D587A899ULL, 
            0xCC10AFC9AD6A9546ULL, 0x986A93783BDFB440ULL, 0xB4CA51058190A6FDULL, 0xA438EF12003B4A93ULL
        },
        {
            0x21FD7F58596D60F8ULL, 0x4E7DB7EF25B6BF69ULL, 0xD1DDC3283BC4C3CAULL, 0x7D0E2324D6989610ULL, 
            0x300ADD86215691C1ULL, 0xA007E42C29F9C97CULL, 0x278CF0AD2739FA1EULL, 0x275CA1AAEC1B732DULL, 
            0x5A86F5CAF1FC309BULL, 0x7322DB3044B5AA86ULL, 0xB229F02E133B865DULL, 0xEA7E860932607412ULL, 
            0x8FE49D97D8F5C299ULL, 0xA97ED045E0D424B0ULL, 0x9C94B7F136AE95F5ULL, 0x4586BB7E04700A6FULL, 
            0x5C6309F33ED0FF49ULL, 0x33C0585B7465E0A3ULL, 0xBAED849630812D8EULL, 0x5CBD315E16775033ULL, 
            0x0937B6C47E32A3A8ULL, 0x29C969B672F93F35ULL, 0x19C206F113431A2CULL, 0xABACE7667F80F25CULL, 
            0xC139903078FBFBCBULL, 0x5D8443DFB6AAD134ULL, 0x082DDE76F62DAEF4ULL, 0x4696BA5506A9FD16ULL, 
            0x5602832B1CE337E7ULL, 0x81B1819E3F8FE7B2ULL, 0x1BDBD9A8C3E5AC18ULL, 0x2DC1A17BE01B6083ULL
        },
        {
            0xA00D425D77FE5450ULL, 0x913715162C8EFEDCULL, 0x0390B58992A6FC70ULL, 0x7D7C41D913921384ULL, 
            0xD21EA4423299F9F9ULL, 0xEE63FB4579A38917ULL, 0xE54D50E0F71F1214ULL, 0xA69A5E601EAA387BULL, 
            0xD8C535C26442D665ULL, 0x7FF77242E5A5B3A1ULL, 0x1364B090F92F137AULL, 0xCC1481C746939788ULL, 
            0x3228603E90A21B50ULL, 0xB3C525251F4E5A63ULL, 0xB7F6EE6638D817D2ULL, 0x5D1632B9D5C10DF1ULL, 
            0xCD76333030AC8E84ULL, 0x3135BF2AAF14EBD1ULL, 0x3313D84C52020B8EULL, 0xB69E330B245D2D7CULL, 
            0xF8E6037FCDD84862ULL, 0x21B52C39C25CAC0DULL, 0x62954160B6E1347CULL, 0xFFE5C661AF37C4A4ULL, 
            0x825CC2B946715301ULL, 0xF0DC2C08CC580563ULL, 0xE941707BA6840135ULL, 0x025356A659CA4BFAULL, 
            0x2EE23C18557B20E8ULL, 0x2DC2D3893905B5FBULL, 0xB33B640A2AA20D4AULL, 0x9EC51575603D5FC3ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Ankaa::kPhaseFConstants = {
    0x97D39DD64C8DDA3CULL,
    0x62A7335CD8821EC1ULL,
    0xCE416F5BCE2745FCULL,
    0x97D39DD64C8DDA3CULL,
    0x62A7335CD8821EC1ULL,
    0xCE416F5BCE2745FCULL,
    0xE2FA29EBCB989C7CULL,
    0xE2AE43030F64274AULL,
    0xAA,
    0x50,
    0x14,
    0x89,
    0x1E,
    0x0E,
    0xF9,
    0xDD
};

const TwistDomainSaltSet TwistExpander_Ankaa::kPhaseGSalts = {
    {
        {
            0x44113B94E116D96EULL, 0x57D7E27828F45289ULL, 0xD98E1A041C529E4BULL, 0x145B91756F3DC9FBULL, 
            0xE4BDFF4B372D1B0AULL, 0x7903F5C183B8DCFDULL, 0xE3F56DEB03083C86ULL, 0x000D8CC8F608245BULL, 
            0xFD197CD053ADA287ULL, 0x23E5F2B903A45132ULL, 0x775895067055533DULL, 0xDB3422C99646E7F5ULL, 
            0x55DDAA3AE4B0A045ULL, 0x4F475B250087343CULL, 0xE2B11CDDB3F6519DULL, 0xB8001A875B1EE60BULL, 
            0xA2DA2A7C8688C47BULL, 0x27252B381F5BE439ULL, 0x2E04DA67B0B0B50BULL, 0xEBC0B1B3FDD1B5E4ULL, 
            0x52D7E26C4E05340EULL, 0x6C62641BB2AB1960ULL, 0x8D444FD4CD613576ULL, 0x107E9C1A7C2DFCD8ULL, 
            0x37F806BEDD0EF2C3ULL, 0x254AA40CF938B744ULL, 0x17C54DBE411DC1DBULL, 0xFE0ECE20A602CA7FULL, 
            0xCD8F7800C67015C1ULL, 0x82185DF55F04329EULL, 0x12E0656985478255ULL, 0x7AEA3D5D4AC3DB1FULL
        },
        {
            0x2603F69FF56EECFFULL, 0x03F01B18C776C8ECULL, 0x79F464D3CAB3064CULL, 0x1F36C1A03D744BEBULL, 
            0xA7CAC1C305F6C485ULL, 0x7FC449BA46344608ULL, 0xE2A03E1EFADBEF63ULL, 0x85E5DD38024686FFULL, 
            0xFB1486F576A254E2ULL, 0x2C881E41155332C8ULL, 0x927A7549D4C9CA52ULL, 0x247DABD31EAEF67DULL, 
            0x1ADEAC9BCA20E358ULL, 0xB897EE11F4C5B890ULL, 0x219DBDD423CA5182ULL, 0xA3218F95F3BA8465ULL, 
            0x8866B813285A9E76ULL, 0x7234EF1D00D171BAULL, 0xE51793294A53ADC4ULL, 0x7C8CC7CDF9C67B9FULL, 
            0xE371731045AA858DULL, 0xC2771AD0DF2CE00AULL, 0x2B889F6D8B989C39ULL, 0x25A3786280F26BE2ULL, 
            0xE136A8AD5B56EECDULL, 0x0E6BB3A22A616877ULL, 0x39561C0818B37441ULL, 0x1F0BB76E1B0633B2ULL, 
            0x92C7A5D9704D244AULL, 0xD3BD8C3FD3767A36ULL, 0x5B680C18C7DF7918ULL, 0xE664F5CDEA23B2CEULL
        },
        {
            0xFC87008C9A12F3F5ULL, 0x58ACE0A21DA40B18ULL, 0x5C1ACD4F46CA811AULL, 0x1286FE159E4CC581ULL, 
            0x26C91FC9B5D58146ULL, 0x2475C2E83F7C4B8FULL, 0xDAD00209E09EF9E7ULL, 0xA22B1A0C8187A9B7ULL, 
            0xC33D9115AE964C27ULL, 0xC0A9A555DED98635ULL, 0x166674B8E9975104ULL, 0xD76A9441B9FA807FULL, 
            0x70350631B6E0C6BBULL, 0x68024E29CBABFD75ULL, 0xEE73822EEE14FAA3ULL, 0xB5E12335FBE2EC18ULL, 
            0x5F9EB5F317DCCF39ULL, 0x4C1C63B021278353ULL, 0x17569602B512CDC2ULL, 0x2401664A02863158ULL, 
            0x50D72B88AA85DC65ULL, 0x3B145CE6DB35E01EULL, 0xB9C7F1643EF620D4ULL, 0xCAC0B566F622354FULL, 
            0x3879BB1A00E2E837ULL, 0xC25B8BB0C8C7F21FULL, 0x4BA48659786E0DA2ULL, 0xD710277F5256D237ULL, 
            0x7C71E0FA666DA99EULL, 0xE1693189165236AAULL, 0x3D53778B6302C6FCULL, 0x1550A788683328FFULL
        },
        {
            0x225FA658BC16E7E0ULL, 0xAEFD64911DFE3DE0ULL, 0x92118253F41A8AB2ULL, 0x219786BFD40D6086ULL, 
            0xC3F422D347E92E22ULL, 0x4F961DD7F9CF5EAFULL, 0xD1FCCC0672CB45BEULL, 0x81CEA732E774B976ULL, 
            0xA3590FA81E2E720FULL, 0xC34787E20A2DBA85ULL, 0xD0B9F50A6627D19EULL, 0x23F1BC84D1544984ULL, 
            0xDE028367FC76870DULL, 0xE2319B540031FEB0ULL, 0x9160E733BDE0EB65ULL, 0x7EF57331405F94A4ULL, 
            0x3D03CC7FF6477769ULL, 0x2D3E422FE8586248ULL, 0x3F72D22C878764D1ULL, 0x40EECD10A6931594ULL, 
            0xCABAB30A8708F28DULL, 0xA913AC79DA271876ULL, 0x5CD1C009DA34CB31ULL, 0x91BE6C2135B99AB1ULL, 
            0x387386EADE8C701DULL, 0x51ADB6F43485EBF7ULL, 0xA5139A685ACF44C2ULL, 0x93738956DAA6898BULL, 
            0xCC8B9E61981BB127ULL, 0x8E94B65AF133EA2FULL, 0x3D6DDE2D4A97D300ULL, 0x8CC20AE65DBB7FDEULL
        },
        {
            0x23FF7CB3E0945CB3ULL, 0xD6B126A318E99B61ULL, 0xA2A50455DA47CAE4ULL, 0x83FCA8A721CA9EFAULL, 
            0x08F54043A65D1FFDULL, 0x3E32B94197434777ULL, 0x3A5DECA6DCAF47ADULL, 0xF7240FBB6EE5CA42ULL, 
            0x644CAA62E5883BF1ULL, 0x21484158AB7A14BAULL, 0x673BBD02E22DB227ULL, 0x74EE82D69071E06CULL, 
            0xDE3469E4F935D888ULL, 0xFF1281DBD12B438EULL, 0x6063A613D04D0C6CULL, 0x77FD92EECECFE876ULL, 
            0x5147FC100374E9D0ULL, 0x210B4EF5A281898BULL, 0x900F9742A90F2578ULL, 0x235C6BFF37871AF4ULL, 
            0x09693FF5F609F9BDULL, 0xBE4BC872B605889DULL, 0xD91EF92055117617ULL, 0x9181A3F946C99FE7ULL, 
            0x744DBB6A04BF4C41ULL, 0x0ED1574548487D47ULL, 0xE6C541327287F0CCULL, 0x90196FDD9B9ECABBULL, 
            0x83FD53EB27D3B1E2ULL, 0xEC317F0DD45B4145ULL, 0xE4D618188F3AC267ULL, 0x860681D5094500F7ULL
        },
        {
            0x3592A99D548377B5ULL, 0x03DE7237487D2EBFULL, 0x706C8DACAFEC4932ULL, 0x1AD894293CDFD078ULL, 
            0x8E491D886CA02507ULL, 0xDADD3039D9ED7174ULL, 0x5CA8F7B9A0765311ULL, 0xA38F492BD23F656DULL, 
            0x3432B90670FB3F7BULL, 0x65E89CA8B74F66C5ULL, 0xEA362CF9A55B8805ULL, 0x5D35C7493D1D85D5ULL, 
            0xB0A0E4370881177EULL, 0x133BF9D821E990FDULL, 0x57202DF85D44730BULL, 0x75F35FF0F4E0F1FAULL, 
            0xA78860CCB526A167ULL, 0xBF7DC9923D63D3E9ULL, 0x9D942610EE728ABDULL, 0xE51F5AF36E52EA43ULL, 
            0x2684C6CA2EA7983AULL, 0xF790EC910225727FULL, 0x1975B7BDDF38A6C5ULL, 0xCCC0FA258A45F87BULL, 
            0xC8313AF05FF5E5D4ULL, 0x8BFB971B603FEF21ULL, 0xFEF9BD0DA37C2150ULL, 0xADB360AFB8D12DD8ULL, 
            0xE09A6D319EB2865BULL, 0xA10B3700A4A8B31CULL, 0xAA34D0254965E45FULL, 0x622260FFC0D46B55ULL
        }
    },
    {
        {
            0x2C64759441F689EBULL, 0xFF435FBC044D5EE2ULL, 0x22EC44095D05D893ULL, 0x19F0D8E84C92B077ULL, 
            0x620D6A38472BC71EULL, 0xE14F9CF72145535EULL, 0x56D7EA481E97AD88ULL, 0xB64828CF6AFF351BULL, 
            0x78F57501E505DAB6ULL, 0x852E27148E163628ULL, 0x1F27C258AFAB9DF7ULL, 0x4985D984CEED148AULL, 
            0x58CBBCC1EC7CAC1DULL, 0x788ECF9F02FC38E9ULL, 0xB4C72ABD26642554ULL, 0x36FEEF858E15B99EULL, 
            0xF4118C929AA30A7FULL, 0x0958FC238D92F265ULL, 0x23703274563462EFULL, 0xDF19B99C86D2EBD4ULL, 
            0xAAD814621FA34B48ULL, 0x1C05771702BE9460ULL, 0xF4F4A39D6E36C047ULL, 0x8033368A756B6AE2ULL, 
            0xA361573E58C9FDD1ULL, 0x4BB067A65BA40014ULL, 0x79557AC7F16C2621ULL, 0x623EDFE33693E2C0ULL, 
            0xCFF176DD405C0867ULL, 0xA9D22A2519FDE9AFULL, 0x788A0553A9044726ULL, 0xE615E44E98BB4184ULL
        },
        {
            0xA33D9B0770360403ULL, 0x680F92ACD592985BULL, 0x6D5132FDA40BB56FULL, 0xE3E08DA87F5ADDF7ULL, 
            0x6993FFFDB537EFC2ULL, 0xED8DC9AD2C7B1589ULL, 0x509797CAC83E8228ULL, 0x46EAE6260FEE5719ULL, 
            0x0FCFCB4A02DB3174ULL, 0xF5392C4D01E58372ULL, 0xB2E422991F2D28B6ULL, 0xFD7DCD7F1F14B045ULL, 
            0xDC6ED7B81D8ABF2FULL, 0xCCAA9B4EAAA0B105ULL, 0x135621E4CB176442ULL, 0x8F6001803A1CCE2BULL, 
            0x9D15D2952D459C2FULL, 0x4AFEBC55A3BF3635ULL, 0x09FB279B8645778CULL, 0x3C1DA30FB355ECD3ULL, 
            0xB323B04619623AD0ULL, 0x975489FBBF4F2C0AULL, 0x81C0C267B5ED3F15ULL, 0xE937182240214613ULL, 
            0x0F33277C0082BE18ULL, 0x862E85AEB39E5F36ULL, 0xCA03BE42DA4393BDULL, 0xE0AA329F912D650CULL, 
            0x4DAC490F92F1F470ULL, 0x4D2B2D2709D2CF28ULL, 0xD9B55824B7E36ED5ULL, 0x82BCCD24A6327564ULL
        },
        {
            0x6FCCD820B1612B77ULL, 0xEDCD764BB263DD64ULL, 0xBE133E8A3EA5D53CULL, 0x3E9AC65E3FA46609ULL, 
            0x7736E327CAC72942ULL, 0xA3F3D0946EE02DA9ULL, 0x7E87515ABE7F40E9ULL, 0xF87A713C8B764E1CULL, 
            0x16B288D1CAC3F4A5ULL, 0xFCA237235F5A879CULL, 0xDF6D7A6FE06BA9C6ULL, 0x873ABA1D1D45F060ULL, 
            0xDC292697F7373F0DULL, 0x0841E84EAE583CD4ULL, 0xF898BDE5103FD3D8ULL, 0x56696CB113B3B40AULL, 
            0x97FEA41614113833ULL, 0x63C1AA799E0397E6ULL, 0x49E0C6BB14531A5AULL, 0x319212B73B5AA663ULL, 
            0x21F80F29B506BCC2ULL, 0x002A5780E4FA6DA0ULL, 0xF066638AC310E340ULL, 0x7D570C5890B09414ULL, 
            0x9D62FF3B6641AEEAULL, 0xE1CF1F20F55E18D0ULL, 0xDB6E2CF0EE6108E4ULL, 0xD865F6F576B8FFE6ULL, 
            0x6ADA89FDB3591C2AULL, 0x3837A9A2D22369B8ULL, 0x30ABF9B96E27C809ULL, 0x8A8492959CE2AC83ULL
        },
        {
            0x79CA4E9D9C0E252EULL, 0x7070BEE375140AEAULL, 0x67F8838112A2042EULL, 0x61987E1AF5233D4BULL, 
            0x97448AAF3B387B65ULL, 0xE000C45305B619D3ULL, 0x4998C84DF3599A0AULL, 0x0BE2587427D5ACC5ULL, 
            0x39D4633E21CF2DD3ULL, 0xF2F06DDE188F24AEULL, 0x0AAB2436CFEF21BDULL, 0xC0E49BD84CE62A5BULL, 
            0xEDB2FBBF70BD3E2AULL, 0x7F39A55B4DBAA657ULL, 0xBE7EB7751C118CFFULL, 0xE4166E2F903FBF60ULL, 
            0x17737E510956D8C1ULL, 0xECD401D6DB026856ULL, 0xB07A4D4605AF97D2ULL, 0x7E48CBEA625A48A9ULL, 
            0x44A7B0BF49092A3AULL, 0x09548A87D605F445ULL, 0xFC69C78C84B47A9BULL, 0xB0B413655C5C6D5EULL, 
            0x78A63F104D51AAB7ULL, 0xA9A62FA4E409603DULL, 0x32E8B8A5300CC3B0ULL, 0xD00C45AF4633BC21ULL, 
            0xCB33368538DCFE1FULL, 0x2E22CF7F0B855A16ULL, 0xABA7E5194EB47BECULL, 0x1CD3767E25CD2B2BULL
        },
        {
            0x8CF18250937EBAA9ULL, 0x2A7F317E3FA37353ULL, 0xBB45BCEDED8624E4ULL, 0x2E3FC90127D9C5BCULL, 
            0x354B0C09C5579C9BULL, 0xCB05C5A70A31B22AULL, 0x0B77D925D6A0CB00ULL, 0x09701255D2CAA0AFULL, 
            0xDCA37FA0C2F23338ULL, 0xE5CC2D11D701EA6BULL, 0x872BE9D0E933370EULL, 0x71BCAA0F702C0F04ULL, 
            0x5DDD2B02C8295B11ULL, 0x68BB6A7263D26202ULL, 0x4711067D678B5E27ULL, 0x02DDF9106F7F03D3ULL, 
            0xB7A15E03742FE051ULL, 0x2A377001145726DAULL, 0xABE4958CD7122384ULL, 0x678F640E16AB896BULL, 
            0xFE55465260C17DA6ULL, 0x09F96F57452B7CD2ULL, 0xA86B0FAE184F77A5ULL, 0xD7CEF186BFDF97E6ULL, 
            0x9F6A3E54EE2EEB28ULL, 0xD1DC53FE4B2B4F50ULL, 0x93B43112BC5D6745ULL, 0xAA721D11F7EFB76FULL, 
            0xC268D5AA858B797DULL, 0x43839FE5C849D7DEULL, 0x273604B22719529AULL, 0xEE2DE888DF2B294FULL
        },
        {
            0x036CC157E07F92AAULL, 0xB3870FF0D7E70C01ULL, 0xC606A07134FB809BULL, 0x4EE3D1883B184CA8ULL, 
            0x5551CA0DB0B01D65ULL, 0xE43CDFDCDAD91AF2ULL, 0x358C30DEB7D04BB7ULL, 0x03625CCBB6679BE8ULL, 
            0x289F2C924BFC8327ULL, 0x5A4576BFCA2EE000ULL, 0xA12567F50F7DD80AULL, 0x1DB9BB0C9A45F7A1ULL, 
            0x0A9260CF6DAFD5E6ULL, 0x1488B5558E04A386ULL, 0xC25AD09649E1A94DULL, 0x8458774B475C5EAAULL, 
            0x5FA29A9A236F8B68ULL, 0x65F2711F1BB3A6D8ULL, 0xC7FD2CCE7798A5AAULL, 0x17FDF4EDB173FB70ULL, 
            0xF9B41AFBCEB8DF47ULL, 0xA032A694020D133AULL, 0x13694BADDE35CB48ULL, 0xA09FF6A920B292B8ULL, 
            0x6530AE3702194C4DULL, 0xF2D4CE6EF8354142ULL, 0x4444B72831E334D4ULL, 0x59884C13152AEC0DULL, 
            0x360E081BB3976277ULL, 0xBFD5EA96172383E9ULL, 0xBBDD2C387A7BE416ULL, 0x1C9657ECACDA37E6ULL
        }
    },
    {
        {
            0x87CDD017FDBB4080ULL, 0x57A141A799460CA2ULL, 0x3E5D824A333A171BULL, 0x392F15ADF912BEC4ULL, 
            0xC78C09806818D133ULL, 0x2FE178A884A2E658ULL, 0xDA960477FFD4CEBEULL, 0x336700CF84B0B181ULL, 
            0x88186921EF008BDDULL, 0xE5C11B06BF2A2CEEULL, 0xA96AF5746ADA5C67ULL, 0x5CBE0BC821D44CBAULL, 
            0x57D54153A8C738E8ULL, 0x9E16178A1293878CULL, 0x189ACC9D425009DAULL, 0xDFBB572541FD78FDULL, 
            0x7DA82BB64B16C186ULL, 0x3D67C4F08D13BF5EULL, 0x82887053E7455591ULL, 0x0BB9B098D1800EA9ULL, 
            0x8A1F6513AA723972ULL, 0x842449C2E7515A42ULL, 0xA91869167623BE2BULL, 0x9A6CD5A15988060DULL, 
            0x713676A6B4114538ULL, 0x01B50DF0CD048BC4ULL, 0x69B7AECC8DA9EFC1ULL, 0xEE0D705BD5BAC5FCULL, 
            0xAE9E2F2F95B6589CULL, 0xC3405E40BE0B1922ULL, 0x8F8AC039739AD49DULL, 0x63C36F0DC835DBF5ULL
        },
        {
            0x7787387F4F7B8FDEULL, 0x18B5CAC31805B8EDULL, 0xE6BAE1DD401F09BEULL, 0x8477AD0E83BAFF87ULL, 
            0x259084CC8D21F163ULL, 0xA3E070C459A3460CULL, 0x3DD6083372D22937ULL, 0x02E32B38480283E6ULL, 
            0x685B407899083B9EULL, 0xEC4A6E2C6BD31C00ULL, 0x4F71DA208ADBE098ULL, 0x191EB088DE06D3E1ULL, 
            0xFB525E40EC03B395ULL, 0x2541D06F378DA6F5ULL, 0x177455088EB7ACD7ULL, 0xD426EF3569E1A432ULL, 
            0xD50B4DECB1D80EE7ULL, 0x3B92F1D61EB71641ULL, 0x53D53028661BC323ULL, 0x24BC6346722AEF6EULL, 
            0xE9ED0162BB3F2E7AULL, 0x9ED3C4A09EAFB355ULL, 0xE7DD27B3128FBAF8ULL, 0x3CFD9293D81AB641ULL, 
            0xC486A9A062599DC0ULL, 0x87A841A54BD4C0C1ULL, 0x17932755B7D84523ULL, 0x5D6F62786FFBB97EULL, 
            0xDF39BDC5A1BE363EULL, 0x3B40FE587ECBD8ADULL, 0xD18D4BAA68D1D709ULL, 0x446B09ED094D1BF6ULL
        },
        {
            0x34108E71E9E8ADB5ULL, 0xFA8DA731AACB6B03ULL, 0x1D22CB329E7CDA54ULL, 0x177EA056DFC00F04ULL, 
            0x2AF24167880E378AULL, 0x5327EA383AF25435ULL, 0x6984378F52097EE2ULL, 0xE47FE9B8EB172023ULL, 
            0xA7CDAF806CF54C93ULL, 0x4F3218BF6CDFAFABULL, 0xFB70C994423D7421ULL, 0x7BF7E693AE2AB8FCULL, 
            0xCB3601E4AAA43795ULL, 0x20E48EAF0CA68F60ULL, 0x9E664EA6224BE421ULL, 0x6F49844A6FA89964ULL, 
            0xC5DD5C88645C9439ULL, 0x0C918CC66B1DC15BULL, 0xB9E6B08020C518C5ULL, 0x7BC22E2451FF4629ULL, 
            0xAF80D9783401E218ULL, 0x70000F4B64D6087CULL, 0x3DA0F039AB5E55A7ULL, 0x4120F7FE68D76189ULL, 
            0x2E9BA6BBE9B224F7ULL, 0xC1F9376CDD8C8AEAULL, 0x02839F454F67F77BULL, 0x2FFB805E92B20B98ULL, 
            0xB09D34BFF8E3E691ULL, 0x13C7B402B28F01A4ULL, 0x676EC778FB5EDD00ULL, 0x77633990264EC4BDULL
        },
        {
            0xDE5A93A2068EAD01ULL, 0x5C19AE40356220F6ULL, 0x396413F080BAB8F8ULL, 0x248630392B91293FULL, 
            0x9C874AAD8BAE9814ULL, 0xE3103716D55E2419ULL, 0x725AE533B5316058ULL, 0x21AC118979342D4DULL, 
            0x0F75E182043BBED1ULL, 0x4FDBB3ECB70DE8B7ULL, 0xEDB22D50C463A324ULL, 0xFD42D59AE97855F5ULL, 
            0xE03CD36DBC0F8618ULL, 0x6B16E3E7EDDA9AF5ULL, 0x715DBCD3F4475F57ULL, 0xFD635B548B1E64AEULL, 
            0xB29217926995CBABULL, 0x0204A1D439705C7FULL, 0x558068574FE8AC20ULL, 0x7FF95EA5486EC002ULL, 
            0x129D70EBEAF7EDBBULL, 0x5EBCB76FCDD35F78ULL, 0x9108135EB302AC24ULL, 0xFD4E767CD1034785ULL, 
            0xC55B72689C7F4B25ULL, 0xB5755CC2683CF6EBULL, 0x2588CAFFCDA307C2ULL, 0x956FE25186C2CE3DULL, 
            0x9C7F18A5330932CCULL, 0xDBD0CF5572F1BC73ULL, 0xFCAAEC3845A625CDULL, 0x1AA49BB5F0F4EF22ULL
        },
        {
            0xC8277DE1E496D96BULL, 0x079452A2B4423182ULL, 0xFFEC37447B3D520EULL, 0xA6A3163132C24D48ULL, 
            0x17A6275CF2654061ULL, 0x5D263BFB25F1A902ULL, 0xF843CEA666F1CB72ULL, 0x2F961CD232AE0C8BULL, 
            0xB52536D722A3DF61ULL, 0x0E98668F34042F4FULL, 0xB42D77EE82655D10ULL, 0x5DD636CF15DEA64EULL, 
            0xF5A80ED3217B45DEULL, 0xC2CCEE49FCA8433BULL, 0x4319DCD4FECC6BE7ULL, 0xA32BB1D95D492CE0ULL, 
            0x26FA8FA362EE68A2ULL, 0xABD32EC3F25682AFULL, 0xCD405DE47162D5A9ULL, 0xF380E932A95E792BULL, 
            0xF27925DF3456AE44ULL, 0x071EB60036F473B3ULL, 0xBCBAA48CBDD2B165ULL, 0x185A397FF21413CDULL, 
            0xE116AF5094C5026AULL, 0xD123B3D20C367D6EULL, 0x7318C750CA15A8B1ULL, 0x1F52CDBB6C6E022EULL, 
            0x89CB0F2D18D77E13ULL, 0xAAE8762559C6A119ULL, 0x499B8699BF1388F5ULL, 0x167E4FAC1A15B911ULL
        },
        {
            0xCD3B15EB0E50D46DULL, 0x65032463DE8AFDE3ULL, 0xAC7945C9FB3EA57BULL, 0x429C292301E40136ULL, 
            0xDF50720F5B3AC2CAULL, 0x86EBD0AB7D4618D0ULL, 0x566784E954FF173CULL, 0x94CEFAB2E2FCDE75ULL, 
            0x10316576598BDC33ULL, 0xA8A744A4F7A5C33EULL, 0x00B997C0EED4E614ULL, 0x9D6D069B5E1E7502ULL, 
            0xADBEF51AAC646FBCULL, 0x434DFD52743E8475ULL, 0xDD0010C29C3B8B96ULL, 0x34080D9226107FA6ULL, 
            0x8A844E81AD7B3FEDULL, 0xC18434AF8800BEBEULL, 0x9F07B2374C4F0160ULL, 0x763B0C195C0E32C8ULL, 
            0x9F135F14FAEB9C8AULL, 0xF9AD3BF31412DF41ULL, 0x56D1BC87ACBE92DFULL, 0x835B403412F28940ULL, 
            0x700019A9083C4107ULL, 0x223F26694968976EULL, 0xF104BE27AF967A3BULL, 0x309EAF7AF84F4B46ULL, 
            0x3961D5B85D6F62F7ULL, 0x0E562E4F9231DAABULL, 0xEAA5441084B786B1ULL, 0x7676CD5EB7E54E7BULL
        }
    }
};

const TwistDomainConstants TwistExpander_Ankaa::kPhaseGConstants = {
    0xEB32C3D6297D6A43ULL,
    0xE45D94D38EEED57AULL,
    0x8D24AC6ABBB72E70ULL,
    0xEB32C3D6297D6A43ULL,
    0xE45D94D38EEED57AULL,
    0x8D24AC6ABBB72E70ULL,
    0x6B080FE920D8F556ULL,
    0xD2646958D5199237ULL,
    0x96,
    0x4E,
    0x59,
    0x50,
    0xEE,
    0xBB,
    0x3B,
    0x97
};

const TwistDomainSaltSet TwistExpander_Ankaa::kPhaseHSalts = {
    {
        {
            0x311A85DFB4DCDE56ULL, 0x9861C6F97E8DD136ULL, 0x12368D63D539CCB9ULL, 0xAE8170C990699244ULL, 
            0x128B1FD976742A4CULL, 0x4501C84B7705063EULL, 0xA232DBB5C966E280ULL, 0x3F0BDD0365EE1D5FULL, 
            0x3E0A35B4730E7E51ULL, 0xF1D54C258C3D5918ULL, 0x9D2996D6F8254CFAULL, 0xE7FDCB61590B4353ULL, 
            0x2E89F3B05FD805A7ULL, 0x374962E573CC635DULL, 0x76299CC25CF0ABE5ULL, 0x30F692B6F8C35F2CULL, 
            0xE2E9044D6CBF8D39ULL, 0x2FB68795C1619C59ULL, 0xF562731A77A3F5CFULL, 0x8C0D098A04595068ULL, 
            0x3974A196849756C6ULL, 0x7DA05A760D3DF3BFULL, 0xA4E411865BE753B2ULL, 0x457DC9665A0D15A9ULL, 
            0x0436FB71C8DF087AULL, 0xB28E3DC2F20F45E9ULL, 0x6DB1F49142BB3C34ULL, 0x4B3223199A5B6F8AULL, 
            0xA522441045EB15D7ULL, 0xD1F71D52906B2081ULL, 0xE8E1DD16E424E74EULL, 0xE7ED116D9DAA353BULL
        },
        {
            0x1E711B2DB2543A6BULL, 0x6B66E88894731E63ULL, 0x84E147C3B6CE706CULL, 0x639A6CB7040FD4CBULL, 
            0xF8EEBA4DD064C92BULL, 0x763F809884662718ULL, 0x853F53FC5FEAA67DULL, 0x8E973B14484AAAA7ULL, 
            0x8B79C4809CDB6130ULL, 0x0A911E0FFCBCB24BULL, 0x018044E68C976C2CULL, 0x09D972ACC79B8E85ULL, 
            0xA0CD7CDA3AB5EE1BULL, 0xF748A07AA04EDFE7ULL, 0x3106625AB269E7FAULL, 0x0B4F5E69B9156E83ULL, 
            0xC690438AD6BD55C1ULL, 0x5B36F7AC6D614DBAULL, 0x8ABB8AB9F97FAF6BULL, 0xA9B5E61299E0A4FAULL, 
            0x07C62354E1F4C909ULL, 0xE4A7161838FA5ECDULL, 0xDDE4824EE8291120ULL, 0x1850E3406B9D0008ULL, 
            0x2BEC7290AFE972D9ULL, 0xAB6201E7F16C2C7CULL, 0x45D03D3365020FD8ULL, 0x26AB3EDDF859A90AULL, 
            0x625E1EDF14E422E9ULL, 0x7D1BAEB0A147330FULL, 0x284AA618B0AA7F68ULL, 0x859F36DC2942DF35ULL
        },
        {
            0x4C8CB83A4393FA05ULL, 0x42AD172CE84DAF2BULL, 0x902D26D9AA18856CULL, 0x969FFBAE4E8877B0ULL, 
            0x0465FA5DD473DED8ULL, 0x0AC8B10ADFF94AE2ULL, 0xF2A660F00FF4F4CCULL, 0x8BE5ECEDA136909CULL, 
            0x0BC373D801EE3921ULL, 0x8EF79F4B4799599EULL, 0xE21310362C617D01ULL, 0x10262189BE294057ULL, 
            0xE604AF831491F538ULL, 0x0F418CC4BADE7E6AULL, 0x5371DED1CC8802C0ULL, 0x8F621764330CA923ULL, 
            0xF5A830F7DB085CF4ULL, 0x1AF50F842F818395ULL, 0xC09DFE0AB5BD8F2EULL, 0x0E8CB1AB4E84D07DULL, 
            0xF2FA6B5C24F5D3EEULL, 0xDB9704344D4FA21BULL, 0xCBD5FE32E3D40C3BULL, 0x641D804E533E2A9AULL, 
            0x6CF107465F92024CULL, 0x4301831D5E1586D0ULL, 0x9928B807C6C6A1ACULL, 0x767069080D1C6DF7ULL, 
            0x53E7152AA18E8390ULL, 0xDC0038D8DD7C1221ULL, 0x1F4F6F78A6B616F7ULL, 0xBC32F4CF726FE301ULL
        },
        {
            0x3F1D49EEA5A01EDDULL, 0xC70B66D0E7A6E720ULL, 0xAA634F63BFA65672ULL, 0xE6EB3E7E28292867ULL, 
            0xB1D865A6FB1746CCULL, 0xB2001D6836E86EFBULL, 0x22B339C4371AD6FEULL, 0x64AEB768E9D7DD76ULL, 
            0x1CC0A9B9F4710513ULL, 0x2BC625B774B50F35ULL, 0x7A91CB8B4863DBDAULL, 0x636BA3F812668BC5ULL, 
            0xD34173BA72D862BBULL, 0xBB0A076A4EA65779ULL, 0x38A2A78C905BD5C2ULL, 0xE0E6DCBACB98B4FBULL, 
            0xE9958ABA7A85B533ULL, 0x31B5D385FE83C4BFULL, 0x9886CCB0E7B73790ULL, 0x59476820555FD841ULL, 
            0xED9B723D0C248C93ULL, 0xFA2880FBC9AE9B2DULL, 0x072F3CC27B180D12ULL, 0x0816DA3D2BE51F84ULL, 
            0x0314F4B60CCE34D1ULL, 0xB466DBE18A6B9BC7ULL, 0x29687F362B63D607ULL, 0x4F8DFACCFFF63703ULL, 
            0x7C3621483BEA782AULL, 0xB581839AE84D5FC0ULL, 0xD4E3BBA9D8989CBAULL, 0x7E8F5270ED36D0E1ULL
        },
        {
            0xEB184D4E7597B680ULL, 0xE663CE836A816CECULL, 0xDF95989519A5A867ULL, 0x724D565550E336CCULL, 
            0x2C6E773DE797AFD3ULL, 0x95108037C01D4AC7ULL, 0x563B9FAA3C1B7876ULL, 0x65F0E6C5ED293D91ULL, 
            0x94D0FCC9D10C482FULL, 0x6CCA587A33A6D263ULL, 0x43710B97D73ECCC6ULL, 0x6708A196E4E8E0C3ULL, 
            0x9E3DEFD0205FCBBCULL, 0x78F54E2AA3570222ULL, 0xBB647CCA58A26B32ULL, 0x72B7B8E4576F1574ULL, 
            0xD3C2728254D17D7BULL, 0x86F27C2EE67E5EECULL, 0x13BB1BE059B146DFULL, 0x878AB0E1E4C39E14ULL, 
            0xC2CD5A31CBD7C92AULL, 0x466C1DC8C9BBACEBULL, 0xB5A03C48D48C5FB8ULL, 0xDA652F46C7CEAFF2ULL, 
            0x52C4E67093545A6AULL, 0x13F805A7B3C57FD6ULL, 0xBC0B4EB35059F041ULL, 0xE84A8E683638D9CCULL, 
            0xD316D6638BDFFC11ULL, 0x5B27DC4150B609A4ULL, 0x57B7218DD30C34D6ULL, 0x711E09C408533051ULL
        },
        {
            0x0DE07BD84C587329ULL, 0xFB80652506FF440AULL, 0x8FC902D6E126C20CULL, 0x7E24B742428DCC75ULL, 
            0x6D7CF814D28FF9E7ULL, 0xBCE7018303D83B3DULL, 0xB9121EBBB768B467ULL, 0xDB84E38EC732ED6BULL, 
            0x3C3CC90363B1B42FULL, 0xC0C77FF0E1B9C539ULL, 0x7E98079676F581E0ULL, 0x6800F67C25625BAEULL, 
            0xC09A3A37CB1FCCB6ULL, 0x1D6C5AFDF52C5CD2ULL, 0xC586C5EFCEC87E09ULL, 0x9550AA87CAEEF478ULL, 
            0x0E4A784FC4EF50CBULL, 0x95DA78F0626B7E10ULL, 0x441BF423BDEF80B6ULL, 0xDF0B01C87B315403ULL, 
            0x847220A856D95521ULL, 0x5AFD5EAEC401053FULL, 0x7C3CCF98B6955AF6ULL, 0x5F45C4A2919521DFULL, 
            0xE053B9A913F4D80AULL, 0x451BD8BA2E8D4045ULL, 0x13F8D6E6C847D8ABULL, 0xE1365BAF9418235EULL, 
            0xCD37ADBE39A7E693ULL, 0x9E1A760A7420A4A4ULL, 0x731535B48D700573ULL, 0x3F9D7CD17454D790ULL
        }
    },
    {
        {
            0xF307297557B9CF5EULL, 0xED39B2B11C92C3F3ULL, 0xC31186166EC3AFFBULL, 0x96EC7F811A3F655CULL, 
            0x6D482516D77D63DCULL, 0x1F1ADA877C7EAD8BULL, 0x0D0541DACA036C22ULL, 0xF72FBB7693FE2E8DULL, 
            0x293EE15AEFF8EEF2ULL, 0xBE69F672BAAE2CB5ULL, 0xADC323E6349ADC2EULL, 0xA09136775FE589D5ULL, 
            0xA286F92F8AD3C293ULL, 0x9B23484F0F62A1A0ULL, 0x2962D73E67D049EBULL, 0x36E95D9743859B41ULL, 
            0x32D6907A439C6387ULL, 0x399C2C94705FECB6ULL, 0x54C14D83F9573170ULL, 0xFF9FA194BD95A195ULL, 
            0xA46A1DD5469597D2ULL, 0x30624B7F395C3035ULL, 0xA0625682101559FEULL, 0x10401944AD62EC1EULL, 
            0x953A363F8562310FULL, 0x3BC4A5504DBDA4F4ULL, 0xDD23547F035FE3B2ULL, 0xA51A7F1223E7C7DDULL, 
            0x850E6F1D865D9080ULL, 0xEEBB765A83772EB1ULL, 0x044993BE1AE247CCULL, 0xD83C7A3A4167D6B5ULL
        },
        {
            0x8690A33331A93041ULL, 0xC315E6CE2A4D10BBULL, 0x565F753617509583ULL, 0xDFA15C61BE873F72ULL, 
            0x4295B8DC165FE4FDULL, 0x7EB9C98255FE8C98ULL, 0xA2579A0532FF89CCULL, 0x8B453CF55729E3D2ULL, 
            0xD1F8A51905850D8CULL, 0x22CE279C335DDC02ULL, 0x120A9717E098E589ULL, 0x89DEB60711844458ULL, 
            0xAF8BC4C44FED6CCDULL, 0xE939F7FEC03DA499ULL, 0xF82D4F925F63834CULL, 0x9BB5AFCA54DFA9F7ULL, 
            0x0E60877927575D02ULL, 0x99427B1272D77FB8ULL, 0x00ECB5E8FF06D73FULL, 0x84B93C03D6F70B13ULL, 
            0x203561F18F877F06ULL, 0x17BC39BF671D16B2ULL, 0xA36369749216E8EDULL, 0xA0C30C34FD1A0177ULL, 
            0xEA07DC5E12D7D90FULL, 0x98FC2D025D4EF454ULL, 0x9746EA6F67BDA73CULL, 0x9176B0F82652E568ULL, 
            0x4CE4FFF59459B8B9ULL, 0x57D33CB52CB89DACULL, 0x03374F838D50CB42ULL, 0x82083AD4D401A11AULL
        },
        {
            0x78C4C1DA6F9A4C42ULL, 0x1DC7C1B2ACB824BEULL, 0x3914C3A00FF538F0ULL, 0x245CA5B674490147ULL, 
            0x4C5CA6B64D465474ULL, 0x9BADFCFE34674C68ULL, 0x9E6A14CC20AD6CE7ULL, 0x6F0F2161C89EDEE7ULL, 
            0x2A332098AC3D0A11ULL, 0x07F02AE867C6BAD7ULL, 0xDB2DA386ACDC0E3AULL, 0xB5F4ABFEC316D362ULL, 
            0x79283DC59E5521FBULL, 0xD6183B81045941DCULL, 0xE96E6CB15945D987ULL, 0x6DC598EB05DAB089ULL, 
            0xCE017B2B93A45571ULL, 0x10BCB5994A25E090ULL, 0xA9E8683310D8EF85ULL, 0x6FE6103938671A70ULL, 
            0x433EA31D2E6B438EULL, 0x9D748ACBC12D6F6BULL, 0xF8050E4A063E3688ULL, 0xA993BEA92BE5400BULL, 
            0xA85AF87DF3D95790ULL, 0xC784D357916F60BBULL, 0x2C67CF9057482D98ULL, 0xF9498D0EE8041D39ULL, 
            0xF575B20788493E70ULL, 0xC54FA4FB47B0E881ULL, 0x024BA2D13F23992FULL, 0x45A30898B14DCCC7ULL
        },
        {
            0x9C971874A7460AF4ULL, 0x3AD750825D48FC23ULL, 0xB5A5B229A504E9E7ULL, 0x1B1A49012F2411E4ULL, 
            0xC1A4538D68DA126DULL, 0x8FF8C4F10FFD1A03ULL, 0x16C061B8CE3058DFULL, 0x2F8CBFD394A6E454ULL, 
            0x83B4A1C8DCC4436CULL, 0xA8C9EBEC518F6926ULL, 0x85DFA75B4CBA780DULL, 0xD154F8E42E202AEEULL, 
            0x9333BCFB90343F9CULL, 0xC4AE01F5BD29869CULL, 0x7D521DC4B66E5382ULL, 0xEC4660680209B828ULL, 
            0xF453C77792229F58ULL, 0x5EFD5F746102B815ULL, 0xAC50E82F23AD5B3CULL, 0xDBBA92474B788D59ULL, 
            0xB37E75BE3C64812BULL, 0xD274A666CDD54F02ULL, 0x06A5B552383E4206ULL, 0x68028B2EC779DD0FULL, 
            0xC6263C306A5F9D0EULL, 0xE1711E629C3E73F6ULL, 0xFD6712C61A4368FCULL, 0xEDD97E56C0780A47ULL, 
            0xF7889F1DB49ADB6CULL, 0x7F279FCFC15086A0ULL, 0x4627CC23DB1E7541ULL, 0xBF987228B997C77EULL
        },
        {
            0xC261ED81AAAA467AULL, 0x776477C3882A171AULL, 0x152ED9A8F82DF4D2ULL, 0x27F703B9E912422CULL, 
            0xB0634B6E011C6E32ULL, 0xCDD0A01E5DA56266ULL, 0x39EF435828A1C9D8ULL, 0xD2C91FB83DF0E29EULL, 
            0x45357060BCA75FEDULL, 0x4AEB46E895D79B8DULL, 0x095AB20E71281ACEULL, 0xFCCEF0B99EDBDDB0ULL, 
            0x7F3A6C6FB1FA04CCULL, 0xD17BA0EA64257EBAULL, 0xE1F26278352A7FA7ULL, 0x3DBAFC4C5AD78ED7ULL, 
            0x0A4F1BC7C728B67BULL, 0xB5618F2B2A97B97BULL, 0xA6160BC215D2CC48ULL, 0xB41F7EEF992ECD38ULL, 
            0x0F17C4C34E446DD2ULL, 0xA99E46BDB62FBFB1ULL, 0xC2371AF190850CD6ULL, 0xFCBCBCF8C21FEE96ULL, 
            0x851EE0451BBE1C5BULL, 0xB9F7A741901BAE2CULL, 0x47D03B762B71B25EULL, 0xB4A2659A0770DDF6ULL, 
            0x8CB73A762979718FULL, 0x8255F1824609F8DDULL, 0xE482537ECAC286E7ULL, 0x3F038C0402A80DC8ULL
        },
        {
            0x7BB2722E63626AFBULL, 0x64BCCCD48BB8B01FULL, 0xC1C1059BF213EE54ULL, 0xC67752D227CA2AC5ULL, 
            0x6B6FB7FD6B83FF09ULL, 0x7AF53D70D0FE20D0ULL, 0x8B349C06430E384EULL, 0x5831D32C41C16173ULL, 
            0xBEAC76A5B9D627AFULL, 0x6C803703AED459B2ULL, 0x86D20064C01D16A4ULL, 0x64DD9C268E690E31ULL, 
            0x235E7C823AC2C2DCULL, 0x178B65AB2049390FULL, 0x351EE90B4149309BULL, 0x83F32ECEDB3922D0ULL, 
            0x72330329EFACD9DEULL, 0xE1B36004FB719D5CULL, 0x36723901C88008A7ULL, 0x559A9B160508FD89ULL, 
            0x73CBEBDB9D059C7FULL, 0xA56717D38762131CULL, 0x4A08A655283941CCULL, 0x927A15862C662A32ULL, 
            0x7266E2558274172BULL, 0x2202CDA7291510BAULL, 0xE36415F191D2EB05ULL, 0x0A2A0560A111D2FFULL, 
            0x170D29ECD167064DULL, 0xD2C53CEB144BF733ULL, 0x0487846C33CD5603ULL, 0x16FA60F6F3FF3847ULL
        }
    },
    {
        {
            0x151B38ACB22F1D9FULL, 0x3272D7F4DF1997BCULL, 0xCEC654BCFD02D78FULL, 0x8C9C8F3CA61F7A86ULL, 
            0x7D9D59BF0850C238ULL, 0xDA4DD1C9200A549EULL, 0x2EF42EC0739E49D6ULL, 0x7D513D474F8A3E3CULL, 
            0x6E3900CEC906D134ULL, 0xFE10683459526EEEULL, 0xEBFF6D10A0D0DC44ULL, 0x1F403AB1AF618852ULL, 
            0x4AB37B6A8FD99C4FULL, 0x431B7249022C9BDBULL, 0x70A2C9586EF7F472ULL, 0x64068EEB5B1F2597ULL, 
            0x9D388C8E17665018ULL, 0x93FCF11DCE7CAF1FULL, 0xD7B3F09A6AF21C2EULL, 0x2AAB6505E027B26AULL, 
            0x9B166E8417AFB053ULL, 0x638D48C7DFB7BC57ULL, 0x72FEC2D507FB7B80ULL, 0x93BAC483A65C56F6ULL, 
            0xBFAD4C90C3558D91ULL, 0x2D8710DD517E59D6ULL, 0xF37FE073DE36C36CULL, 0x850DD944EE924C6FULL, 
            0x601005E84244EC28ULL, 0xB88CDB95A93F1B56ULL, 0x412D65AEB619D031ULL, 0xA5A03860189E7FB6ULL
        },
        {
            0x337ABE9BEBAC35FFULL, 0x11BCCE99D58CD124ULL, 0xEB5FCB6C57C52DE6ULL, 0x2EB0E3C2F9F44D2CULL, 
            0x9CA00FB4CE48A5ADULL, 0x338F634DC48F55C3ULL, 0xDC1A61511D47FFCCULL, 0x221175D92BF2FBACULL, 
            0x190E9242DA23A4E9ULL, 0x8B23F1BA8BA41EA2ULL, 0xA4B609F45B8E14CDULL, 0xC1388E440A3AFEC7ULL, 
            0xB9FABEF072F676B1ULL, 0x570BD85EBF272D08ULL, 0xF23045855FDB12E9ULL, 0xC2609F9CA625EBE8ULL, 
            0x57659B6040FBB115ULL, 0x7CFEF3F16BBDCB1FULL, 0x249F13B781DD3D39ULL, 0x1E89B14E00456D37ULL, 
            0x5F6FF24185A6CF38ULL, 0xEE4EBD126DE3982DULL, 0x8CFD82133E2FE5FAULL, 0xCAF06F6473322E5DULL, 
            0x5CD93E38E08F52A8ULL, 0x35CDEC303B1160F7ULL, 0x4828257981550080ULL, 0x5ED8F713308669D7ULL, 
            0xA3A92516431F2A7EULL, 0xBE9601D9F899C06FULL, 0x0409D5FBED9119A3ULL, 0xA7C5CB9BFA220B5EULL
        },
        {
            0x6A56563478A6BC91ULL, 0x160011DA44F628E6ULL, 0x9144E02D144210B1ULL, 0xA11556C50DF655FFULL, 
            0x833E0FB29BC89DA9ULL, 0xC341EB6F8DF39E5AULL, 0xA8630B9C8EF50737ULL, 0xE833EE2277139558ULL, 
            0x5C4D64CD81E489A2ULL, 0xEC2E91F561810B57ULL, 0x821ED82FD2495BBAULL, 0x0C0E07EF89DDC39FULL, 
            0xB1817342DA56B09AULL, 0x9E2DF13739605229ULL, 0x3A1294B55B2382F8ULL, 0x3469C8D6A9A01750ULL, 
            0xDCEB38F342E4D4E8ULL, 0xA41A43017A1B2525ULL, 0x957A87412B63D927ULL, 0xD427F27AF3943DA7ULL, 
            0x78C050BC9F234A60ULL, 0x812344DAC599F008ULL, 0x8B5B4649EB5A8D4AULL, 0xB3BC181700EED0A4ULL, 
            0x6688BEB6D7A14D9CULL, 0xACA88A2AC091739CULL, 0xACE6D8F14CCAD2DCULL, 0xE95E729E45FD22E7ULL, 
            0x7D27BED661C2366FULL, 0x4E8A60029B6550D3ULL, 0x56BE372093721049ULL, 0x7D06B01248DE5A38ULL
        },
        {
            0xAE242DA7E1625850ULL, 0x28CA4A3E7646117EULL, 0xC18B7A134D5B317FULL, 0xAB33D88AC08D70D4ULL, 
            0xDBD14697DC298D02ULL, 0x93D5A3F8E46FCE16ULL, 0x68FFB80CAFE0D76BULL, 0xBE0B4A95A72DF17DULL, 
            0x74DD85CA5DEAA199ULL, 0xAA7FC7520A9B6E9EULL, 0xB394355F589EDDDDULL, 0x4D0938646BB60BF9ULL, 
            0x65B42F6F4EA3AC74ULL, 0x667C4506C54E5C1DULL, 0x93A3B1DD31ABB3E0ULL, 0xE65EF3037FC68C29ULL, 
            0xA96EE84F7BBFE529ULL, 0x7F6B2C7A6CA92D56ULL, 0x074C3D3B2E5B26AAULL, 0x357B0A01659501D0ULL, 
            0xE0B304AA7C6E0664ULL, 0x55F38377C4D3316DULL, 0xA515EA030964FFBFULL, 0xC580F30D037C81CEULL, 
            0x7EC54AE8707A536BULL, 0x100A76DEF6B00673ULL, 0x0F4118B9BC09B959ULL, 0x0F561FE7E34FD513ULL, 
            0xE619C81B158E399DULL, 0xA90413B1C26A8EFFULL, 0xA232DD7C313029AFULL, 0x611B243CF77AF784ULL
        },
        {
            0x07444E67DE0171E7ULL, 0x4A1C42ED683929DEULL, 0xF3C7087FB384F7DFULL, 0xCEE14666D67C0E27ULL, 
            0xA45F34EDAF68C41EULL, 0xD7445993F0AC05D7ULL, 0xE79B92DFFE21A589ULL, 0x38DA51BEFCA39B82ULL, 
            0x0038B04C90701A52ULL, 0x7258D6F4618676AFULL, 0x24DD3E6865F976B8ULL, 0x878AFEEAD6D1CAB9ULL, 
            0x1335A49AEF12C851ULL, 0x4603AA1A1AA06004ULL, 0x2BEF1C06EA0E1466ULL, 0x0E1AD73117979D6BULL, 
            0xC7475F6C33FC8AF0ULL, 0x386F28F70ED0F6A3ULL, 0x950B358BEB31C2A7ULL, 0x95103980B64A00F7ULL, 
            0x0EED24CE0CDDC9C2ULL, 0x1C9918AE4E6567BAULL, 0xF7C6BA535C6FBFAAULL, 0x4C8C709F988A3677ULL, 
            0x876C1441C9BDDA30ULL, 0x661E8A8DBD88C5DDULL, 0x550F6A6CE5F537C1ULL, 0x98F206874D5F9015ULL, 
            0x72F7AB9212A35881ULL, 0x04C01B6BC6820C72ULL, 0x8044399709835B36ULL, 0x8B19FC16978B4071ULL
        },
        {
            0xB0D0B7CF6BCEEBC9ULL, 0xC79735C55A350C1EULL, 0x84566FA8590AEB42ULL, 0xB8B813B9315A0534ULL, 
            0x0520EFA2C0DD2E53ULL, 0x0FA4D78B77B335DDULL, 0xFA349D67849028F7ULL, 0x1C6E0463723DD973ULL, 
            0xF583A40EE33D79ADULL, 0x3C441172EEB75E5CULL, 0x353F55CA1281239DULL, 0x301679513FF79DD8ULL, 
            0xF8A0FC3F9B051229ULL, 0x784A7B8D60D84D01ULL, 0xBBD4804A8C119CACULL, 0xDF5964A793DAAB26ULL, 
            0x1E0EABDF0C350EA8ULL, 0x7AFB8C4F957F878FULL, 0x5FD72BAAC0EA561FULL, 0xF70AC4AD92EEC68FULL, 
            0x856976B448C87975ULL, 0x7AFC4F398C883662ULL, 0xAC81E0B79460F157ULL, 0x8CC5E46651367DF9ULL, 
            0x2562E7FA49017DACULL, 0x82255C1FBCD0C67AULL, 0xB0FEA77669E7AB4BULL, 0x0258D412E7370A56ULL, 
            0x3A80B3D57CC65A64ULL, 0x37463AE674642BADULL, 0x0E2F3448AE4FC338ULL, 0xBDF8DEC2286CB7F7ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Ankaa::kPhaseHConstants = {
    0x757D5811D9D669D7ULL,
    0x115BD75DF56FA1F1ULL,
    0x389F9D9EE63C23E0ULL,
    0x757D5811D9D669D7ULL,
    0x115BD75DF56FA1F1ULL,
    0x389F9D9EE63C23E0ULL,
    0xFB5DD5B3F6CF4337ULL,
    0x487109784887EC3EULL,
    0xC9,
    0xCF,
    0x9D,
    0x9A,
    0x74,
    0x12,
    0xE3,
    0x52
};

