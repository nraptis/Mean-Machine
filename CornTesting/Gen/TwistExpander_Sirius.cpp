#include "TwistExpander_Sirius.hpp"
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

TwistExpander_Sirius::TwistExpander_Sirius()
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

void TwistExpander_Sirius::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0x86C6C574E5F65550ULL; std::uint64_t aIngress = 0xE9A79858038F7DABULL; std::uint64_t aCarry = 0x9147713C2DB8B429ULL;

    std::uint64_t aWandererA = 0xAAEB6621B8C4E8CCULL; std::uint64_t aWandererB = 0x877517E040516A6AULL; std::uint64_t aWandererC = 0xA7D28BADE803671BULL; std::uint64_t aWandererD = 0xB36FFA8B8CD403CDULL;
    std::uint64_t aWandererE = 0xB14ABC3C7411A72FULL; std::uint64_t aWandererF = 0x9FB7DDB7D1D274C0ULL; std::uint64_t aWandererG = 0xA7E7733EDCBFFFA7ULL; std::uint64_t aWandererH = 0xDE60DF16E6F86049ULL;
    std::uint64_t aWandererI = 0xD1A0B45F2C300204ULL; std::uint64_t aWandererJ = 0xEF22591ABCBE6787ULL; std::uint64_t aWandererK = 0xF061E0F019D71A08ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 17218358996201144004U;
        aCarry = 16592469443584854596U;
        aWandererA = 15951788567860584008U;
        aWandererB = 13849986930305333892U;
        aWandererC = 9615042549338484841U;
        aWandererD = 9495393829266774928U;
        aWandererE = 14697151427601115128U;
        aWandererF = 12838547888904586171U;
        aWandererG = 12420897825266581760U;
        aWandererH = 17126920694599929514U;
        aWandererI = 11257461489409778612U;
        aWandererJ = 10308295131384154231U;
        aWandererK = 14208368091658407380U;
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
    TwistExpander_Sirius_Arx::KDF_A_A(pWorkSpace,
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
    TwistExpander_Sirius_Arx::KDF_A_B(pWorkSpace,
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
    TwistExpander_Sirius_Arx::KDF_A_C(pWorkSpace,
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
    TwistExpander_Sirius_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Sirius_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Sirius::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xA009B6F8762FB85BULL; std::uint64_t aIngress = 0xB7B853628362F951ULL; std::uint64_t aCarry = 0xE3F00CF0481C2E94ULL;

    std::uint64_t aWandererA = 0x8577C8FBCA5C0B95ULL; std::uint64_t aWandererB = 0xC291438F519AA622ULL; std::uint64_t aWandererC = 0xD87610D4EBD851B0ULL; std::uint64_t aWandererD = 0x8ECD504A354CE2ADULL;
    std::uint64_t aWandererE = 0xEC95FF927B1DFB47ULL; std::uint64_t aWandererF = 0xCC23965874AFBDA7ULL; std::uint64_t aWandererG = 0xF66485519255C5A4ULL; std::uint64_t aWandererH = 0xD1C57100F7B18FE3ULL;
    std::uint64_t aWandererI = 0xE8E2C69E48CE1566ULL; std::uint64_t aWandererJ = 0xC343A12D68F07C3FULL; std::uint64_t aWandererK = 0xBEB7E685131CF5C0ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 14220210076998594256U;
        aCarry = 9352230801142269960U;
        aWandererA = 17664532958431194533U;
        aWandererB = 11945645930821449170U;
        aWandererC = 12648610251999949656U;
        aWandererD = 11587327547401558458U;
        aWandererE = 16320821426355672076U;
        aWandererF = 14564773538723206453U;
        aWandererG = 13235645194620581183U;
        aWandererH = 18093908365465022559U;
        aWandererI = 17620506524067405120U;
        aWandererJ = 9673926230386120015U;
        aWandererK = 12037016802424315068U;
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
    TwistExpander_Sirius_Arx::KDF_B_A(pWorkSpace,
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
    TwistExpander_Sirius_Arx::KDF_B_B(pWorkSpace,
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
    TwistExpander_Sirius_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Sirius_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Sirius::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xA46FBED63489D7C6ULL;
    std::uint64_t aIngress = 0xB2A7F19BD3361B89ULL;
    std::uint64_t aCarry = 0xECFADB7437B770B6ULL;

    std::uint64_t aWandererA = 0xF188E6C3A1B09958ULL;
    std::uint64_t aWandererB = 0xC674C2991FDDEAF1ULL;
    std::uint64_t aWandererC = 0xB730A43D1EC3873EULL;
    std::uint64_t aWandererD = 0xB1D43C01F84A089DULL;
    std::uint64_t aWandererE = 0xD2048E3F94189D19ULL;
    std::uint64_t aWandererF = 0xEBE985BE82B6B5DBULL;
    std::uint64_t aWandererG = 0xA888A05420DDA8ACULL;
    std::uint64_t aWandererH = 0xD842699E62AFF12EULL;
    std::uint64_t aWandererI = 0xDD161691B6B1BE19ULL;
    std::uint64_t aWandererJ = 0xEB082B32EEDC1A25ULL;
    std::uint64_t aWandererK = 0xC3F40D18BB44257DULL;

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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneG);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneF);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseCConstants), &(mDomainBundleInbuilt.mPhaseCSalts), aSnowLaneC, 2);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneE);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneA);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseGConstants), &(mDomainBundleInbuilt.mPhaseGSalts), aSnowLaneC, 6);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneH);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneC);
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
    TwistExpander_Sirius_Arx::Seed_A(pWorkSpace,
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
    TwistExpander_Sirius_Arx::Seed_B(pWorkSpace,
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
    TwistExpander_Sirius_Arx::Seed_C(pWorkSpace,
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
    TwistExpander_Sirius_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Sirius_Arx::Seed_E(pWorkSpace,
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
    TwistExpander_Sirius_Arx::Seed_F(pWorkSpace,
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
    TwistExpander_Sirius_Arx::Seed_G(pWorkSpace,
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
    TwistExpander_Sirius_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Sirius_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Sirius_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Sirius_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 31 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1788 / 1984 (90.12%)
// Total distance from earlier candidates: 54375
void TwistExpander_Sirius::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 940U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 2U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1950U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 400U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1186U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 792U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 315U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1313U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1271U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1726U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 547U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 191U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1829U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 148U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 440U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1574U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1437U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1402U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 161U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1123U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1352U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 621U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1078U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 686U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1364U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1468U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 216U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 166U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1309U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 561U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1331U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1441U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 885U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 141U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1945U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 108U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1371U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 336U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 2039U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 394U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1363U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1976U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1396U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1918U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 578U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1530U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 466U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1385U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 580U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 912U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1543U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 691U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1062U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 46U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 374U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1392U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1677U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1242U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 746U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1061U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 599U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1097U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1339U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1117U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1467U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1265U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1567U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 271U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1337U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1220U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1096U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1814U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1120U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1386U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1946U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1557U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1728U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 569U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 598U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 564U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 78U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1338U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1303U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 719U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1378U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1151U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1561U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1895U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1665U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1769U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 977U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1649U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1840U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 87U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 341U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1306U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 860U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1592U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 902U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1746U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 889U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 224U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1940U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 563U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 577U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1610U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 493U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1568U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1176U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 834U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1538U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 665U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 263U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 949U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 71U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1334U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1547U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1140U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1824U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 482U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 975U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1571U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 206U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 296U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 120U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1050U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1230U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1148U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }
}

void TwistExpander_Sirius::TwistBlock(TwistWorkSpace *pWorkSpace,
                                       std::uint8_t *pSource,
                                       std::uint8_t *pDestination) {
    TwistExpander::TwistBlock(pWorkSpace, pSource, pDestination);
    if ((pWorkSpace == nullptr) || (pDestination == nullptr)) { return; }
    std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    std::uint64_t aPrevious = 0xD6529F0E2A640B4AULL; std::uint64_t aIngress = 0xC3AAC8AA56750ADEULL; std::uint64_t aCarry = 0xD1B8CEBD9F0A7779ULL;

    std::uint64_t aWandererA = 0xCC9EBFDC576B53CFULL; std::uint64_t aWandererB = 0x997C4CC1D89E4E60ULL; std::uint64_t aWandererC = 0xE7788353647EF235ULL; std::uint64_t aWandererD = 0xF8139D8051C5D7CEULL;
    std::uint64_t aWandererE = 0x8C6BF7BE99F69329ULL; std::uint64_t aWandererF = 0xC2895AAB073A24E6ULL; std::uint64_t aWandererG = 0xE8CCAFD9C1E6CC11ULL; std::uint64_t aWandererH = 0x95FFCA4A1351E562ULL;
    std::uint64_t aWandererI = 0xADBBE496BEE9B735ULL; std::uint64_t aWandererJ = 0xAB99C3DF05248A63ULL; std::uint64_t aWandererK = 0xEE6E2BEE2B07B60AULL;

    // [seed]
        aPrevious = 9995257683236475600U;
        aCarry = 13754012556229610859U;
        aWandererA = 13198507074298226640U;
        aWandererB = 18381892015709896420U;
        aWandererC = 10978257350611248288U;
        aWandererD = 16763851873799895140U;
        aWandererE = 17059799936601550627U;
        aWandererF = 11458911410174982341U;
        aWandererG = 10207719083867499116U;
        aWandererH = 15657572644827645065U;
        aWandererI = 12284560802906527835U;
        aWandererJ = 12102926688654759399U;
        aWandererK = 11108039337685171953U;
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
    TwistExpander_Sirius_Arx::Twist_A(pWorkSpace,
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
    TwistExpander_Sirius_Arx::Twist_B(pWorkSpace,
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
    TwistExpander_Sirius_Arx::Twist_C(pWorkSpace,
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
    TwistExpander_Sirius_Arx::Twist_D(pWorkSpace,
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
    TwistExpander_Sirius_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Sirius_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Sirius_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 31 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 16224; nearest pair: 459 / 674
void TwistExpander_Sirius::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1308U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7188U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5508U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6067U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6150U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 8140U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3288U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 195U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 909U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7032U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5710U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3818U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
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
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1075U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1522U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7943U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3813U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 821U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 313U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 530U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 622U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 933U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 178U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1236U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 854U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1483U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1415U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1591U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1435U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1652U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1678U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1757U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1463U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 349U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1361U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1685U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1422U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 31 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 16201; nearest pair: 450 / 674
void TwistExpander_Sirius::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6770U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3607U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6630U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1913U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4992U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 8104U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3480U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5501U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6094U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3726U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1541U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4790U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4380U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3469U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4966U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 338U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1628U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 941U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1202U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 498U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1593U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 469U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 958U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 180U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 714U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1351U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 322U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 278U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1763U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1582U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 619U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1324U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 371U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 539U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1112U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1178U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Sirius::kPhaseASalts = {
    {
        {
            0xB87D9B0B0F285E92ULL, 0xF02B6329BCCFA57CULL, 0xCA9AD245181350E6ULL, 0x2756F95ADD2FE5DAULL, 
            0x5741D2D40B0EC0A4ULL, 0x0EA7C893625517C4ULL, 0x421842315C856F96ULL, 0x630DE866CECFB8CCULL, 
            0xFE6D541D0792BBD3ULL, 0x7797DEC0868891BAULL, 0xA41C3FCD7A31393AULL, 0x237C24B64D934705ULL, 
            0xCD86A8BCBE06B8FDULL, 0xCE6D52D4080A459DULL, 0x92AF6D44DCD12F03ULL, 0x52D75A39DE0F601DULL, 
            0xCC5215E643E6137CULL, 0xEC8AD0A8E522B8C6ULL, 0xCF3D741ABB7A752DULL, 0x675B667300455EACULL, 
            0x23341D90C5797B0EULL, 0x362FADB4D9C3C61DULL, 0x31B11B9EFBD44DDBULL, 0x7AA2263D216E61B1ULL, 
            0xC8BD7EF27E6C2225ULL, 0xF0E4577DB159D37BULL, 0x8BAEF177E3CD6C66ULL, 0x1D24F83DD2070A82ULL, 
            0x1C4B7188A315B76FULL, 0x3B57FE6C83457CD6ULL, 0x4931B79BC25F335DULL, 0x568DF1F4C5CCAF81ULL
        },
        {
            0x76E05F9151581A43ULL, 0xACCDE7969B73D3B1ULL, 0xC7275957F0DD5A8FULL, 0xC3755B5E77CBA1A3ULL, 
            0x66A6CFABA03EF6CCULL, 0xD2DF9E8C2707E618ULL, 0x02D44E63194E9533ULL, 0x457D280357F3E669ULL, 
            0xE53A1A6CD4D1DA1BULL, 0x1DD28C970F0C9F7EULL, 0xDD01F4C0BD28D1B7ULL, 0x6BAAC12E51EAA415ULL, 
            0x3D52996F35A0B312ULL, 0xF1BC7AAAC1249F54ULL, 0x276E990D0F67220EULL, 0xF4193CBEE0088632ULL, 
            0xC7BF9E79089CDA49ULL, 0xFA1FB977B9B82262ULL, 0x6FF4CC51DC77302DULL, 0xFA063A32D9F014F6ULL, 
            0x4DC594CDA6D4A62FULL, 0x5886BB58348A5CF4ULL, 0x3AA43EFEFB1EEE22ULL, 0x4ADC07C5C49EDDBEULL, 
            0x6B1897F3C521CA31ULL, 0x955D2DED451403D6ULL, 0x5591B5CA75F251EDULL, 0xF8AD9812257B1EAAULL, 
            0x7F356AD2F0B8A53FULL, 0x24823CEB67EE7D02ULL, 0x563271388C14E12FULL, 0x5E94C7C56CDE00F9ULL
        },
        {
            0x5C1447F86AE6CF45ULL, 0xFBD6617B25B130E1ULL, 0x7C7CFF30F4F0E17FULL, 0x5F1963565020B56EULL, 
            0x6681FE75146E0667ULL, 0x343DDDFC6A4193ACULL, 0x2BFF67A29398DB8AULL, 0x0F778A6065354661ULL, 
            0xA35E96D5ADC93577ULL, 0x6D0A03D2DA015B09ULL, 0x1277CDAA2A0829D0ULL, 0x7BBF7B3166E926D2ULL, 
            0x1ED9CAF5F549096BULL, 0xF7FE26BEFCE63516ULL, 0x2C693293AF673EF0ULL, 0x41B65CEA1F9553A6ULL, 
            0x650822E5007BE7BEULL, 0xEEF9EE12812B99F2ULL, 0x340890FE290BC37FULL, 0x34740BE7AAAE3C07ULL, 
            0x3AA063E176A79A10ULL, 0x97D0029D4F78CC6EULL, 0xEED3AD4F6519BB9DULL, 0x84F8A37D023DEBDEULL, 
            0xCD3AA86A639BBC59ULL, 0x871A86C5291D2DB1ULL, 0xE1375CE1FFD6B0CCULL, 0xE1B82CCBECD22D3DULL, 
            0xC157AE6C708FAEA5ULL, 0x3588F57933847271ULL, 0x413CA78AB28CAB2EULL, 0xC1DCDC56ED5F9D36ULL
        },
        {
            0x914E90EF556CD9DEULL, 0xB93B4FE25C1D298AULL, 0xC245C8F3B40057E3ULL, 0x9A3EEA43EAA25F4EULL, 
            0x91750901DDA2EEBEULL, 0xE3A37F129A67918EULL, 0x625E9F6F908BDF31ULL, 0xC67CB27F68BEC895ULL, 
            0x48D43C63E2A7B644ULL, 0x493D2EB509D8517AULL, 0x4A32A3F8123FB193ULL, 0x36226A33E68A41A6ULL, 
            0xDD2D1E49065C8293ULL, 0x35E8C1B01ED9D4F1ULL, 0x1B158F097F5DFBA4ULL, 0x61AD2C3A5241D529ULL, 
            0x14C0721D58B2D77BULL, 0xC25BFFB5CC2DE758ULL, 0x9332B197F24E022CULL, 0x3C0EFA8F88DD88F5ULL, 
            0xAB1EF5A374CA086CULL, 0xCF7B31AD609D2AB4ULL, 0x44385522419D4C0BULL, 0xE2FFD5DDD259A751ULL, 
            0x7C700BFE5D3C54BFULL, 0xE0AB28AAA03BCD6BULL, 0x9FEA0AA3E99E4749ULL, 0xA8F92F14F110B801ULL, 
            0x51C6897F9F714044ULL, 0x5064F22B38EB73F1ULL, 0x8F266E301647C1C9ULL, 0xB6D81907616D7B01ULL
        },
        {
            0xAE566F8777D1A8FEULL, 0x6EBDC904EE2DDA62ULL, 0x0CBEEFC5184B203BULL, 0xA3F85B3168AD420BULL, 
            0x9C9304A590B6A9B7ULL, 0xDBC4D04B64223933ULL, 0xFF56DBC7E228918FULL, 0xB8E6AAEA119BE4F9ULL, 
            0xC4A12169E932769AULL, 0x70F872ED8DDD4132ULL, 0x70546FB65FB0C95BULL, 0x1BFFBF4907984CC5ULL, 
            0x60459A6C3A82E045ULL, 0x077417B0F03DE530ULL, 0x387F96CBCCF238BFULL, 0xD0BA4D8895F2AF16ULL, 
            0x566B03253FDD17EEULL, 0xAFE8FF9DC819A2D3ULL, 0x9FB18C24753A739BULL, 0x1EF2DDF077952CEAULL, 
            0x6FF5CAED22351D49ULL, 0xC1049850E46E69A5ULL, 0x3A386A7AB17DCE82ULL, 0xFDC1C5FF6C296C0EULL, 
            0x8C075A8EE0628310ULL, 0x087F45578B98043EULL, 0x63DC25BE0A37A680ULL, 0x4FA7D295B81CC2B6ULL, 
            0xBD5BEB04F4C74FA4ULL, 0x82F52883D5044F41ULL, 0x5A262CF4D3984A0DULL, 0xCE3DFC7BD5BF7B7EULL
        },
        {
            0x9AD0A474CEA2098EULL, 0x7ACE4DBA3B531647ULL, 0x51E16E36EC8879DBULL, 0x745E509A4574AD86ULL, 
            0x057B807B32C8A759ULL, 0xF732F9989025D4C9ULL, 0x55E68FA40BD731FDULL, 0xACCBED74A93D1879ULL, 
            0xB9B7C6E71ADAE0CBULL, 0xFF7150A1378DB37BULL, 0xC6466D85273DDFD3ULL, 0xEBD32148568AC50DULL, 
            0x971FFEB29313345AULL, 0x7C2DC85E073DFDD5ULL, 0x1EB0B611D6A38823ULL, 0x385FA8A8B7B246D8ULL, 
            0xD34EEBF84CB902BAULL, 0x1E029AE436089B32ULL, 0x8D957B9F0DD69FA3ULL, 0xFF58AFF5372580E6ULL, 
            0x238A9579A6AE7004ULL, 0xCC8272498612E6D2ULL, 0x8585B0F97DEB0AF3ULL, 0x168EB935182B03A9ULL, 
            0x3F6E52C664528087ULL, 0x35402D3F9EE74A7DULL, 0x0DAF733D0393530CULL, 0x9CDF57FE3F8653E9ULL, 
            0x3763ADB57F995BC6ULL, 0xABD8BC4F077B5A7AULL, 0x2C2DDDDBA2646DC3ULL, 0x4DF72A5E91E1D399ULL
        }
    },
    {
        {
            0x393F59D6CD359F3BULL, 0x154C65776F1D728BULL, 0x4F74997CBDA15524ULL, 0x97017EFE289C8C1CULL, 
            0x461DCE47781B45D9ULL, 0xFD76006AED70F27AULL, 0x61EDF4F9383E7AEEULL, 0x93A83857A8AD77F0ULL, 
            0x18496A9D0E955414ULL, 0x9CC1B5780A580618ULL, 0x0B4167B5723901FAULL, 0x41FF115955DA4C64ULL, 
            0x7E172674875038D8ULL, 0x44F2101874F60C97ULL, 0xA501704839F07888ULL, 0xCEAC4A3F29B321E5ULL, 
            0xF4B648911CDF0137ULL, 0x5C79278C61A89545ULL, 0x3BA78FBA28670676ULL, 0xE4524B15A2F9A2DAULL, 
            0x133C18353A20AA5FULL, 0x91076296F8CD2976ULL, 0xB76EC3B92DA39942ULL, 0x3278B8AEDD099A8BULL, 
            0xA4C4E3929CD58F7EULL, 0xF1047D4311F58BA4ULL, 0xD1AAA3F538EDD597ULL, 0x9034D5DEB235E375ULL, 
            0x934F9745361CF0E2ULL, 0x00F0AE018540BF83ULL, 0xEF40B2FC6D28A3CDULL, 0x999ADD4C2FCF8219ULL
        },
        {
            0x92F95BF0EFA92394ULL, 0x18616BD500CF6DA2ULL, 0xC0BB68C0CDE46F77ULL, 0xE5210BC6475C5DAEULL, 
            0x2CFE61323BE928C6ULL, 0x2386C1C9EE92D442ULL, 0x9A383F62A5DA3BFDULL, 0x3DAA0E7BF38130BDULL, 
            0x86261030836BCA80ULL, 0x9080BD4D0E844D34ULL, 0x90F76D9B2DDC6133ULL, 0x96C4BE9651F41B6CULL, 
            0x35F1678FBDE11CBCULL, 0xF840A8923AF9071EULL, 0x7FCD869594C83335ULL, 0xFA9ABBF173AA8162ULL, 
            0xADFF7CB85B51C961ULL, 0x4C3591DCD3D28756ULL, 0x09B504B7EDCA256CULL, 0xAA85D135F56F1B2EULL, 
            0x4D837315E8924434ULL, 0x52C6DEEF30A50D35ULL, 0x2EA5C6B17B8075B4ULL, 0xD31EA0ABAF37F1F7ULL, 
            0x1159304DCDFA8C89ULL, 0x7A341B28451764C1ULL, 0xD9B3459C64892A3DULL, 0xFF9B7D035D1D70B3ULL, 
            0xECCECCA8902BDA97ULL, 0xD4040FAF8FD8B30AULL, 0xF90269825066C257ULL, 0x8E51507A0843BFA8ULL
        },
        {
            0x498935D2419F3052ULL, 0xD4E64A84E89419C4ULL, 0xD72E2B4C23E9791CULL, 0x60011BE35EEDDE66ULL, 
            0xF4A1A0FB8B0368CBULL, 0xEC19CFE43D11DA4AULL, 0xA8EF8086C8DC7185ULL, 0x4D7FF8AC9AF58CCAULL, 
            0x07046018DB1A0A82ULL, 0xAC067E82AA40E3B3ULL, 0x63A72711A77F302BULL, 0xB62491D3683C0FB2ULL, 
            0x5F1FED71834F15EFULL, 0xF411EBAF793E83EBULL, 0x5AE0A6B0A3311F1CULL, 0x761E4A7343F570CDULL, 
            0x8DE55ED4D62C124FULL, 0x1CD2E546D28926E7ULL, 0x3BE174B07330A25FULL, 0x507A577CA941C7B5ULL, 
            0xC9391C7BD5AFA7ACULL, 0x4840DB9663135D9CULL, 0x2C3194C5989391E6ULL, 0x1D288D6A9018C19AULL, 
            0xB09531509B65C669ULL, 0x8140ABD29F31537CULL, 0xE31C6A8820479831ULL, 0x2E98AD3E38FBC402ULL, 
            0xF7B52FA43EFFF695ULL, 0xB44E15E5D335FA1CULL, 0xC5A6F4B45CE8FF5CULL, 0xE7245DD41B312FE9ULL
        },
        {
            0x37D74EA5C967E35DULL, 0xCEAAC3A0C70D9B74ULL, 0x3721CDEF7AA9C32FULL, 0x04C1AEA26AE3D25EULL, 
            0x74499C7431449C1CULL, 0x8FDC9965F4EF9F1AULL, 0x9AD9172789E51445ULL, 0x92F65AD7ABD0B42DULL, 
            0xBB8A6304EBEC0DF0ULL, 0xE6049EB6DE606035ULL, 0x69434DA121A7F386ULL, 0x6C98CD98F8E3F2EAULL, 
            0x3B9054E2865D8A19ULL, 0x99D7051B255F663DULL, 0x76803D2441ECEF5DULL, 0x127F812AD16EB5D9ULL, 
            0x02C2FD4D650488ABULL, 0xBEF5B4B59CD23B41ULL, 0x971CFFDEC8FAE12AULL, 0x4128370C2684314BULL, 
            0xB5334FE9D4A5E113ULL, 0x1DEB6352B6793541ULL, 0xF561C8298C4E6752ULL, 0xA879EE40B21AD497ULL, 
            0x65A4B399E6BFEADFULL, 0x6B9AB812F6773C18ULL, 0x76E52853941FA6FBULL, 0x16185FEFD22CA711ULL, 
            0xF5ECC8087602DC22ULL, 0x4B6505CC51915A5DULL, 0x1BE7F7450568F9CFULL, 0x4E0BBAFFD8342C51ULL
        },
        {
            0x0188483EBE6D82F2ULL, 0xB6C74E13BBAA14E0ULL, 0x019B0E33760E6024ULL, 0x2BC7091DC3FAAC1AULL, 
            0x4BF8CD1DA7C0337BULL, 0x44958953876151AAULL, 0x3BC3A782D4E7591AULL, 0xA9A892E59B7689DAULL, 
            0x4E376E889C2228B1ULL, 0x5E861C55898E4BCCULL, 0xD338E659BFC3F4ADULL, 0x2B4FD3FC67538480ULL, 
            0xAE44A041868120DEULL, 0x1D2D456CE8F1BEB7ULL, 0x145A041821ADF06FULL, 0x68847BB40685E985ULL, 
            0x0DDAB2FE06618A19ULL, 0x7119BC2BD705BD22ULL, 0xC2DEE04A944BFF8CULL, 0x3DFD4C30FB093F5FULL, 
            0x7A65525696A79284ULL, 0x1C71ACA8635C8858ULL, 0x36347A53AF0348A4ULL, 0x4D9175194E06BAD7ULL, 
            0xBE4F7AAC0338550DULL, 0xFD0DD38CC336C5C1ULL, 0x9C6A2B158FEDC5F8ULL, 0x8356C1384C4EFB4BULL, 
            0x04A546163F1E60A0ULL, 0xC609720D2C0892A2ULL, 0x57426080D1CFA938ULL, 0xB0F98383C917E68CULL
        },
        {
            0xC3419C9C94D19568ULL, 0x63B7A8577E1EC6C6ULL, 0x33D18BE1C09B854AULL, 0x92E65DADA2A3AE97ULL, 
            0x601C4DD449144BE2ULL, 0xE8CB6637DF342F64ULL, 0x2943B2093DB28A9FULL, 0xCEB9179B36AC9E6DULL, 
            0xB2BA2E94F9BBD742ULL, 0x0EE154C0B22472F7ULL, 0x22DBD3A4E5BF262CULL, 0x7F8699DC3A5C8E75ULL, 
            0xC20DD264EBA10D7BULL, 0xCBEAAE10EA1D5E28ULL, 0xAC5EE6A4D2E066ABULL, 0x21998068AAED4025ULL, 
            0xC64BFB06584FE4FCULL, 0x1FAE3ADD6334EE54ULL, 0x8C25A57CCC7501CAULL, 0x4A3C5A8BD41DDAD1ULL, 
            0x24E188978BC5693DULL, 0xAB349A7D4511BED2ULL, 0x21CCAA437D06958BULL, 0x9B43D2FD8CD5EDBBULL, 
            0x83FF79B6BC6B538CULL, 0x10999385B04F25ADULL, 0x31134A5DC7D45BE2ULL, 0xAE5B494A0651B244ULL, 
            0xA84A1CD9ABE259DAULL, 0x3BF1520C121BB5F9ULL, 0x87CEE7D9A563616AULL, 0x11C42E8FA7F7BABCULL
        }
    },
    {
        {
            0xB8ABBC049D8E5F8DULL, 0x2ECC392C229500BFULL, 0x6204317006A5045FULL, 0x117F4BF1B552DD11ULL, 
            0x1C2A495922EA476FULL, 0x94D1E1C1CED99987ULL, 0xD6141BF2D6FFEC47ULL, 0x343533A0125C57BCULL, 
            0xC401EA49BC5B1CB4ULL, 0x24B65732B0390384ULL, 0x869BA5D65BFC30D1ULL, 0x2F1D36CB73803D96ULL, 
            0x83F9786FB8B2234DULL, 0xD0256EBD8FB1671EULL, 0xE8BE4476FDF8ECCAULL, 0x7A65D5E25FDAB42BULL, 
            0x3A09DC13077B7CBAULL, 0x70FA141362D77A93ULL, 0xAF385E62A431CB8DULL, 0xAB4CDBFDB834655DULL, 
            0x77A4AD414D6F8842ULL, 0x5B28D17D04A8C766ULL, 0x09E91FCE0E4BF477ULL, 0x3832625E96956130ULL, 
            0xDCAEE2795CEC0F64ULL, 0x3313561F3A5622A8ULL, 0x40C668234CE54FC7ULL, 0x986CA32D1F7D4C0DULL, 
            0x098B3F222C006A63ULL, 0x29B5F7FADAE7DB8CULL, 0xC26E47FFBB3663CFULL, 0x34B0D5126ECC08C1ULL
        },
        {
            0x8ED4535E74A12314ULL, 0x7386169DC1276819ULL, 0x610FA8C9BCFB8E1BULL, 0x0805F8EC93B56BC7ULL, 
            0x7D258C679D9B1840ULL, 0x5A057E0A2F07AEABULL, 0xAED8D633E52F24EDULL, 0xE5A1B85A08199A33ULL, 
            0x9B17619627B4DE96ULL, 0x6855A30899E8F2FAULL, 0x809C5BFF576F7F11ULL, 0x07324A3F80F55A91ULL, 
            0xF8318AEC31ABD680ULL, 0xA111F729F15F88B7ULL, 0x03A27196D389D826ULL, 0xEF042970503ED8EEULL, 
            0xB743BAFD97558CAFULL, 0x5B7A23EF0C7BBF7FULL, 0x1C49EB5D854A209EULL, 0x5D1DE1EA9ADF5584ULL, 
            0xB75CE52524FEDA6FULL, 0x6CB9053651283365ULL, 0xF7C4F305298F79A5ULL, 0x334D3F16800C09E1ULL, 
            0x239BFA42ED09D7E4ULL, 0x10151618D8D1BAE3ULL, 0x79C616F6096CDE6AULL, 0xD4CBBA2AFA3B971BULL, 
            0x8626928BD10EC657ULL, 0x347B8C4519B0F8BCULL, 0x8B4613B293CB20A2ULL, 0x61E5D9ABD6775EDAULL
        },
        {
            0x3450EF65DFE048D1ULL, 0x567E3CA1FC28BB57ULL, 0xB399ADF170F82A37ULL, 0xB6A37D86B2239280ULL, 
            0x4AC2ED8E349908C0ULL, 0xD6CE6236DCF7D251ULL, 0x118B961560197B81ULL, 0x4FB7001CBE9652C1ULL, 
            0x752A4E36CAA137BCULL, 0x2D07D831F8F0C029ULL, 0xE3F2AE0C3F4DFA09ULL, 0x32295CA056DF4CB2ULL, 
            0xFC7E22AB795663EBULL, 0x41856197840FB503ULL, 0x766DAC00F8381567ULL, 0x9A270ED4FB41A0EFULL, 
            0xD86BE9E3E1374334ULL, 0x75DBCF2A3D63CF29ULL, 0xE1C51E9A4B8D7C50ULL, 0xACEB8ED2FC8758F4ULL, 
            0x61A61AEE8364FEA3ULL, 0x640A60E1D06F5174ULL, 0xA779E6C6F722D3CEULL, 0xF8A5CF9205672056ULL, 
            0x726AA013F6C9FC49ULL, 0x8CE544B91C50A79AULL, 0x81873D356F16320CULL, 0x2718C638AF3DFEB8ULL, 
            0x813BA5ED7F03807AULL, 0xA94F3181B475910FULL, 0x6B019E99AE0EC336ULL, 0x9401EF9DAF92D4BAULL
        },
        {
            0x646764E974DDAE42ULL, 0xF10B9415225E50F8ULL, 0xF3091721E3F91F0CULL, 0x2B795D783BEEC46FULL, 
            0x19884D855FC2EE60ULL, 0x44D1B341E88B449FULL, 0xD4C9081CD9F38A49ULL, 0x36267EE773F38960ULL, 
            0x926AE6B4BE5B85D4ULL, 0x0574732E2B30C076ULL, 0x33AC5D974C29F942ULL, 0x7A086D68BBD4DC4CULL, 
            0xBE4DAA5F9F51C2F4ULL, 0x74197703B4F60C50ULL, 0x5D174016177B6650ULL, 0xBFACB8B328AA64F9ULL, 
            0x772FACB3DA8A3740ULL, 0x71FCFC53822C8CD5ULL, 0xA4BAFA613E8D1145ULL, 0xFD4229C41CD89D96ULL, 
            0x1D238396534F38D1ULL, 0x9EE312E45DC3A357ULL, 0x53BF7B3C0A877716ULL, 0xC5F98AD739E8F42FULL, 
            0xDEAB13DF52DB424DULL, 0xE19188FFF85CEE5EULL, 0x215510D290CD3317ULL, 0x7446F52611AA923DULL, 
            0xC4A6E2CB3FA19097ULL, 0x3EAC88663D34A380ULL, 0x9DFF899D9C3CBCFDULL, 0x72C5EB46410D1F0FULL
        },
        {
            0xC36158300B0FED02ULL, 0xAF705A77B95E8AFCULL, 0x60426C9F70B95962ULL, 0xC52A03C99571B5B8ULL, 
            0x935E49C936046160ULL, 0xBB89FBD2514AB4E5ULL, 0xFF1798A3C341CA2FULL, 0x0BE08574DFC235CFULL, 
            0xF30C2E0638242961ULL, 0xCAC198B038AD6A2EULL, 0xA43408537EEA85BEULL, 0xC90AD69090603A23ULL, 
            0x2D6821F12B52625FULL, 0x5381E1E380D3E094ULL, 0xC7D90B6C28DA8B8DULL, 0x6DC0BE4184C89DA5ULL, 
            0x19909A93E2F8AE94ULL, 0xDA28855A7815F32EULL, 0xEA70C8CAFCACD8C9ULL, 0xB61DCEB0103C1899ULL, 
            0xFE6CF13E41C8D2D5ULL, 0xB7C2B53373BE9EB2ULL, 0x4F80FB7CF674D327ULL, 0x129CFFBB13DE4608ULL, 
            0x9542C2C1F6892A2BULL, 0x3E88BF0E70F5550DULL, 0x7A6968BFF084E276ULL, 0xF0DB45FD3CEE18E0ULL, 
            0x0C5A63533FFADAD5ULL, 0x2A9D0933BBB2B0B0ULL, 0x9B135920CD2E725DULL, 0x4B7DC1EA07314C21ULL
        },
        {
            0x6CF3F47521B0544AULL, 0xE9C71A288BBCF853ULL, 0x7D114C1D863B57B4ULL, 0x6664B9F434688F62ULL, 
            0x05F633847A6C7801ULL, 0xAB1EFB0393E005A2ULL, 0xAFB70237FE45D622ULL, 0xEF7D805B46B68B6EULL, 
            0x14584B050374AB54ULL, 0x61FC2C410126D08BULL, 0x622D6EE436B6CD3AULL, 0x4BCD4DFD858DBC75ULL, 
            0x14C409B04035A957ULL, 0x42CE01EB1E8BE966ULL, 0xE57BD2F474DE6459ULL, 0x86C83B575C536C4FULL, 
            0x1ECD630E468B5D50ULL, 0x322D482809952C80ULL, 0xA82F11A499C9B2CAULL, 0x52C706959A4090EFULL, 
            0x4B4FC35A2A97F2A5ULL, 0xA214007B1B964B6DULL, 0xAE5171FDABFDDA35ULL, 0xA1C88559F302F0BDULL, 
            0x208D683C1FCBFEB7ULL, 0xBBA5F09621192F5DULL, 0xAB6C112020DE9B49ULL, 0x480121929D790F22ULL, 
            0x2008FD1D856DFEC6ULL, 0xB58920598997B171ULL, 0x2E9FB64C05D4C9C0ULL, 0xFE8D6D4614E2EA97ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Sirius::kPhaseAConstants = {
    0xBF4F086039F0DBE6ULL,
    0xC14DAE95B0A0F9D0ULL,
    0xE51D04C6BF70D3A6ULL,
    0xBF4F086039F0DBE6ULL,
    0xC14DAE95B0A0F9D0ULL,
    0xE51D04C6BF70D3A6ULL,
    0x1935ABFADBED3DD5ULL,
    0xD43C7BFC0E2AFEA0ULL,
    0xAE,
    0x25,
    0x6A,
    0x5A,
    0xA5,
    0xCA,
    0x73,
    0xA3
};

const TwistDomainSaltSet TwistExpander_Sirius::kPhaseBSalts = {
    {
        {
            0xA4A85F9E869BCD37ULL, 0x4BF8A78274D25C31ULL, 0x7D2F0730AA9D25B3ULL, 0xEC9945B8B07A74ACULL, 
            0xD9DCF5D77E599DB1ULL, 0x423ACAC63776FACCULL, 0x5FFACEC9DC25D403ULL, 0x8531D4BB98277075ULL, 
            0xF40D965A3910C485ULL, 0x11A18518205D186DULL, 0x583F3AC113444230ULL, 0x1AFD88C6F90B8F83ULL, 
            0x57D64FA7982850EFULL, 0x3509830BA7F78722ULL, 0x2E0F4567E2195059ULL, 0x30F9B64882F5B38FULL, 
            0x981FA0EBBD14D117ULL, 0xB0CA4B0A61C31AF4ULL, 0x3FB79974D158C69CULL, 0x7B3CB8D0986ADBC1ULL, 
            0xA116058C7DF00E6CULL, 0x0CB9DB1D5E6E4387ULL, 0x0CE393F73CF6914FULL, 0x4BBED9D9AED2F346ULL, 
            0xFAB2B1746EAD2A3EULL, 0x1F014D61A7202CB5ULL, 0xAF8EDFE9F7743876ULL, 0xCA25F94135FD8242ULL, 
            0xEBFDDA8169D0C8BCULL, 0xF5BD0B23091A2996ULL, 0xB48EFE3A0A8548BEULL, 0xAA1180CA65A3E535ULL
        },
        {
            0x49DDAF675A02B69BULL, 0x62C04ED2F4D03FABULL, 0x32839030026D9820ULL, 0x9215A3437C8EDEC9ULL, 
            0x25570F643C841E2FULL, 0xB6C4F36C4199E21EULL, 0x10196DF03E71F4A9ULL, 0xAA5B1B46F248D534ULL, 
            0x1240B8782D5CB8D8ULL, 0x66B821ABCAF0518FULL, 0x7BBB0B33CCEC53F9ULL, 0x78BE1C3C4B705CFBULL, 
            0xCCB10CB9520A0127ULL, 0xA96072D0E9CBECFAULL, 0x2CAA187FDC2E2FBCULL, 0xFF0FFF7EA79E024EULL, 
            0xE30122E9CBA8B508ULL, 0x3520959218EEB86AULL, 0x1C9CB5DE7EE4EB4AULL, 0x77AE42149FD01BF6ULL, 
            0x1161DC132FCC7FB6ULL, 0x8B35C2F88E5EBDB0ULL, 0x968FCA54B0F875DAULL, 0x2A73077B61AD09ACULL, 
            0xF2071F4888F4865DULL, 0x28DEDCC0067DF44AULL, 0xE787BC2133046044ULL, 0x9E13F64A7FB72D73ULL, 
            0x694094F1D8376626ULL, 0x5A26247C02E28E96ULL, 0xE94F52AA81FDFEEAULL, 0x88EDE49C78D5F7B0ULL
        },
        {
            0x4E49303A17FBC187ULL, 0x65FF16F8A4D996B9ULL, 0x289F28F37F625B42ULL, 0x1FBBF5BA8CA4AB03ULL, 
            0x2D24B9C1C35CB1ACULL, 0x688B916D81DC6CC7ULL, 0x25669E9635F99030ULL, 0xB3631E6692935650ULL, 
            0x6F144DFC1DE9A3DCULL, 0xA4461F105A91A7FDULL, 0x367BCD4913505DEEULL, 0xDD8FCC443972CC54ULL, 
            0x247A6ED04BD7E9EAULL, 0xF852A02A8105DE30ULL, 0x93BC156D7A48588EULL, 0xF5CE515116EE05EBULL, 
            0xBE8E9E1FA4A58D5EULL, 0x24C839D98740F43FULL, 0x825ADA706AA82573ULL, 0x8D505DB9BD60E562ULL, 
            0xF04EC84F2C8035BCULL, 0xCC6C6E1D59F3B192ULL, 0x3804C3A2352ABBF0ULL, 0x061BB68AC91479F6ULL, 
            0xB8E91E81677BF0C1ULL, 0xF231BFE55BBDBD51ULL, 0x6C6EE42074F87EE2ULL, 0xA6CCB118F7BA53CDULL, 
            0x9DF510B9471213F2ULL, 0x22BDC719A88FC009ULL, 0xE9F80FFAAC13DFE5ULL, 0xC0F373EA9542BDF7ULL
        },
        {
            0xF8E7C126B27BB9BBULL, 0x03769322F463ED56ULL, 0x787EA0EDB67547EFULL, 0xCDC467E61AC4935CULL, 
            0x0A873EF6FB84F8E2ULL, 0x3905B74D2A18348CULL, 0x97C20F8FA40AB294ULL, 0x5A197C61D1DAFC79ULL, 
            0xA2719C2559B7C410ULL, 0xBB9F056CC5FA254FULL, 0xB6BEB253E094C9ACULL, 0xCFC1DAFD8C4F5157ULL, 
            0xFDB93D7585A356FAULL, 0x8FEA43DBA1030490ULL, 0xEC6CAC71BD510580ULL, 0x29A14970842EAF56ULL, 
            0x72002588BB322CEAULL, 0xE83F370147185CC9ULL, 0x655CB4ED8452C319ULL, 0x2B767B3759DE8257ULL, 
            0xC983028A9711C8D5ULL, 0x0B10E54088306896ULL, 0x4C2EB7D5D18458D9ULL, 0x5EA204D2A95ABB91ULL, 
            0xA6D6CECA2F5C6C73ULL, 0x0F24AD91D132EEA2ULL, 0xF0CB4CC82CB26A2AULL, 0x85CF7FE4C6B0AB30ULL, 
            0x3C2C6FB3F8BFAEC9ULL, 0x8DCE8A66A67DBAA7ULL, 0x496C893914E65987ULL, 0xE9B144E13FBDA439ULL
        },
        {
            0xDAE55637CB743C96ULL, 0x92D264C9848018EAULL, 0xCCACBDE2BB94F28DULL, 0x6FB1D24CE2DC59B5ULL, 
            0xFA06E538C6FC9F5BULL, 0x1E440426BBAF7421ULL, 0x6C8C3690F4E29B31ULL, 0xA6DB4D541204F07FULL, 
            0x226C08BA1FC475A3ULL, 0xAFFD3298475AC316ULL, 0x6D41CF7F52B60F0DULL, 0xFCF142CB4131C080ULL, 
            0x8C3BF78F36C2DB8BULL, 0x82DA800BFDEB39CDULL, 0xF85338142BFB987CULL, 0x24D2961636ECA853ULL, 
            0xF0F12B7384946B09ULL, 0xC69A40F8CACD192FULL, 0x8A2684636532CE32ULL, 0x24F1C3FCC304FD6FULL, 
            0x01306BDDB2692EDFULL, 0x9775791552017AE8ULL, 0xC362AF9DF860B0B3ULL, 0xB096A32EAE582B46ULL, 
            0xD13F4CD0B88139E0ULL, 0xDCE14A2288B9245CULL, 0x34AD4CF586D97857ULL, 0x9E18C20F6B7F5A46ULL, 
            0x4D65AF6AA581054FULL, 0xE0EDA0B4DA398FE3ULL, 0x6D7125554805A3D4ULL, 0xC9487366C1329FB5ULL
        },
        {
            0xFC6AE3292F7955FCULL, 0xCB951A59DEA01DADULL, 0xBE72A9A2164643B8ULL, 0x57B65F1D5811FEBBULL, 
            0x17509F5461CEBEF7ULL, 0x3CB35F5FB7590884ULL, 0x03DAA5A07D03D24BULL, 0xD150FB8B9051EDB7ULL, 
            0xF94B898EA637905AULL, 0xAD212F58F929B703ULL, 0xCC857A4AD1D1FB2FULL, 0xE28B122E06C94BBFULL, 
            0x4D784C3AB65CB44DULL, 0x4D5CB45705FA0D90ULL, 0xE7BB8DE4957E4596ULL, 0x755FBE81F96D05A3ULL, 
            0xC3E6E7A8DEE77914ULL, 0x61FAE0B022E78E65ULL, 0xD7CE58F5DD823884ULL, 0x0D558CD10B6496F0ULL, 
            0x00C5F46B9555B63AULL, 0xABF3F4B787ADB3A5ULL, 0xC3DBC0A987D50DBDULL, 0x50EF317904851BA7ULL, 
            0x8F885012A58A7043ULL, 0xA1B8C9288915F035ULL, 0x0747745825619509ULL, 0xA2749FF38CB433D0ULL, 
            0xD34D0D066EF210D3ULL, 0xFC7C89F6F95A6DD9ULL, 0x318E5825EC86E92EULL, 0x88CA5E56119D7626ULL
        }
    },
    {
        {
            0x63F3F8A534C89C5CULL, 0xE03827742EDF6DC2ULL, 0x9836667C6BF9772EULL, 0xE3395E07B3BE89F5ULL, 
            0xC9456787878992E8ULL, 0x8F566E2936460E62ULL, 0x776C6BB83B959096ULL, 0x519FC96D0E110637ULL, 
            0x7676E0AAA525C1E1ULL, 0x1DE8E2A5DE4323ABULL, 0x8A54BCA916A4518EULL, 0x455FDBDDDC01BA9EULL, 
            0x8603EA710D48B67CULL, 0x93DCE5B01C27AC78ULL, 0x136205E40AC7BA48ULL, 0x24963047EBDFBAF6ULL, 
            0x6E3E6CEEEBD828E9ULL, 0x2595CDEAB3EC718AULL, 0xC2802AC7F467B0FDULL, 0x40B4558722290212ULL, 
            0x492332C83B031553ULL, 0x7FF0116A327F41D1ULL, 0xDF830E267C6123ECULL, 0xE4105C08C20BDACCULL, 
            0x17B632E42A1388B7ULL, 0xC6CCEC15C6C5E78CULL, 0x358BD4CABBC16CF4ULL, 0xE32144B575DE45ACULL, 
            0x410E382F309E42E8ULL, 0x2966D6BB66CBF855ULL, 0x87BD16ECA207F9E7ULL, 0xD798C6BDD2F40416ULL
        },
        {
            0x65E73A9896A44432ULL, 0xCAF64B0C8B404B5DULL, 0xFF679EBEA093E036ULL, 0x0A1ED757BA8CE6ACULL, 
            0x2D10EDB2B3B3A17CULL, 0x79874B8FFC4ECAF7ULL, 0xFBF52754D350B48CULL, 0x4E627756D4B35007ULL, 
            0xE6B3D61C3A91722CULL, 0x1FD97E73F00485D2ULL, 0x84D2C6BDAE61C1D1ULL, 0xDD7C3AB9783C9A2CULL, 
            0xE23FFBE8B728DAF2ULL, 0x9216993B1418915FULL, 0x282CD72604D966E4ULL, 0xC2B7BBFA939D6DFEULL, 
            0xC44F70D987177623ULL, 0x295CECED77407F5DULL, 0x7E807BAD16F9EBFEULL, 0x97F6ECD184B97776ULL, 
            0xC2315D7E44BA4667ULL, 0xAA3A3F01BE9B9B51ULL, 0x5BDC84DA2DD905E5ULL, 0x7DDB5569F71B201BULL, 
            0xD55DF36C531201DEULL, 0x914BE32F6AE33ED8ULL, 0x7202A09DA04995E7ULL, 0xFEDBADB3311AC2D5ULL, 
            0x48FCCB69C3D2448BULL, 0xF9E152B9CEAFC37EULL, 0x82965416F6FF9933ULL, 0x2349F15482B81959ULL
        },
        {
            0xF9DFF5B3695F797BULL, 0xE37A34F20C21E474ULL, 0xBED28F43816BC28AULL, 0x02988818529ECB70ULL, 
            0x78A5A7445685BAC9ULL, 0xE12020C24CD6BC52ULL, 0xC2DBBBF82E5E790FULL, 0x2BAC04E528A03F22ULL, 
            0x29EA2E6033337D86ULL, 0xD8C5E88732EC784AULL, 0xFE5B87D63C7EA05FULL, 0xFFDD90A0D4ED82C3ULL, 
            0xA741806990E0309AULL, 0xCB7DACFFEF42107DULL, 0x2DF4E4D52C90CB41ULL, 0x300AA08FA0C3EE64ULL, 
            0xBA5E6E86C938C541ULL, 0x68C0A8DE0004B716ULL, 0xE65EBD785D179E89ULL, 0xA42F161098F2E98CULL, 
            0x7A87E823E4544F3DULL, 0x395195A8413485A2ULL, 0x85512DD7FD629F11ULL, 0x2EB406ED6C1E7A46ULL, 
            0x3225CB37247FB983ULL, 0x363C88AA084B9CBEULL, 0xBA8933FC981FD84CULL, 0x0E709B07E1A7A813ULL, 
            0xD44C2162AE65CB07ULL, 0xDEF99FBE3FDD9AC0ULL, 0x330319BE599F6071ULL, 0x95987F7F85D18C2EULL
        },
        {
            0x2F6E66B9148C9171ULL, 0xF1088B15CAD74E16ULL, 0xB0F3456CF28D8447ULL, 0x155C28F00C9D0CF7ULL, 
            0xD823DE4C6E45A170ULL, 0xFB68497A8A4FD34BULL, 0x151BD90B96A72169ULL, 0x8E95F2DB12BE7370ULL, 
            0xBD74197DC69BAF35ULL, 0x68EB1C5FE267C564ULL, 0xC657FFE7DD042DF6ULL, 0x0745A294C9F4E83EULL, 
            0xC26D327F494B5D34ULL, 0x4615EDE9EBEE4C27ULL, 0x92CD017369DE21F1ULL, 0x86E07C39291E02B3ULL, 
            0xA8EC35EBF39470E3ULL, 0x2F492DD59C2380E5ULL, 0x17001C5FD5E3FB12ULL, 0xC23B84A11B0F4781ULL, 
            0x2AA790562230E887ULL, 0xD8C596B51859A8C3ULL, 0xF20DB1EE8CF49029ULL, 0x63ECE1FFF2FC252CULL, 
            0xF915CDFF074E2783ULL, 0x5D57EDF11D9853D8ULL, 0x2D0E1D1D96195928ULL, 0xCF59368BE5E2667CULL, 
            0xE7C2CC0544A4D16CULL, 0xBA39AA81E9BDE69CULL, 0xEC7E6C364FB43141ULL, 0x4A185AEDA4103D7AULL
        },
        {
            0x512F0AC067E928ECULL, 0x56D6F5EA91D5D492ULL, 0x7BDA88426DCE2239ULL, 0x028D9F685D74DC2AULL, 
            0xD551D6766F776676ULL, 0x11794EA8257EF854ULL, 0x353DFE14C99882DDULL, 0x84D50F7193EE3195ULL, 
            0xD3184DA3578CBD38ULL, 0x88B9198951AC2C1DULL, 0xBEF0A9C7E06ABAB2ULL, 0x8F20B30784BE8090ULL, 
            0x6C4915A2F9AF9666ULL, 0x6687AE72804199A1ULL, 0xE5BF9EE03DE04328ULL, 0xDEBF8730DB546A79ULL, 
            0x2DE793772C9D0D7AULL, 0xE54E369EF7B1FC27ULL, 0xA46539B1728190EEULL, 0x51665E3AD58781FDULL, 
            0x34AD146A04057034ULL, 0x85BD2442CEAAD4FEULL, 0x3822CD208C268C8CULL, 0xCC02F70E7C5DFF56ULL, 
            0x9F28359FA96E5033ULL, 0xA804025DD6B8D5A7ULL, 0xD31232D5CFFE00C4ULL, 0x98CEA41E905ED245ULL, 
            0xF54A0F8637ADAC62ULL, 0xB30F89E4A541EAE3ULL, 0x6D925E4B93141D92ULL, 0x23F9F06FE81CE03CULL
        },
        {
            0xE2D719C978D19113ULL, 0x48B47489B4CFAC65ULL, 0xBD31F87119122844ULL, 0xE80A1099EF1D351CULL, 
            0xE3F7272C0C40BAC7ULL, 0xB7379311157876D7ULL, 0x4B4830489AD520B6ULL, 0x60F014947BA79459ULL, 
            0x3400A6F30D6AADABULL, 0x616805799B0A275DULL, 0x0AD3EBE2DDFA0403ULL, 0x45C0915CCF646B25ULL, 
            0xCB29ABB34A0968FCULL, 0xD50030D4A2F2ADE3ULL, 0x1983A68751DF8C6DULL, 0x864AFBCBE7853295ULL, 
            0xC42FD410D4DC7CE6ULL, 0x574B7B352BB02575ULL, 0xE0C08D6534D50BBCULL, 0x8EFD9E34F55BC9FCULL, 
            0x5DB2BC09F690AD2CULL, 0xD93FD3513506008CULL, 0x70BE625E32CD3DDAULL, 0xCA4C7619A6EC9D53ULL, 
            0x0A7C65F32A26CA12ULL, 0x8DCF217C3EB209B5ULL, 0x7F6F6605B2BB574AULL, 0x8704FF2C00909F7FULL, 
            0x53DEDC7842FADC17ULL, 0x8EF172051403E0D3ULL, 0xE0465F45F1B5CBC6ULL, 0x6DE741A737B87B20ULL
        }
    },
    {
        {
            0x59519558B5EC4ACAULL, 0x02961A20FF1D6DDEULL, 0x208DBDB27283F1D6ULL, 0x67725FE6F1228F6CULL, 
            0x39254E816323B099ULL, 0xCA4878C418D2563DULL, 0xD76F099FA843AE44ULL, 0x8A1CE20E8A11C1C0ULL, 
            0x3B26C0BD69EBCC93ULL, 0xF9F4E3E8AACA1E51ULL, 0xB8BF69CBEE1B1A34ULL, 0x42AE8CE08FB12B8CULL, 
            0x603FE9123828381AULL, 0x7A10D9385F539C16ULL, 0x7CCE0208FD2D7895ULL, 0x847F80042E3E7529ULL, 
            0x89A5C06A7229D5B3ULL, 0x9FE4B8D414E503BBULL, 0x828B6410D21BD089ULL, 0x970F609E1B2FD758ULL, 
            0x4F1BDE1E7B6A059EULL, 0xF60D19CA9F9ED5A9ULL, 0xA2623D8C32BB6E7AULL, 0x0A91FA4D797A39CDULL, 
            0x5FB2C7C3ED5A2656ULL, 0xB970BDFC0E5581DCULL, 0xD110BA645C90B67FULL, 0x1A8BD78B725342C5ULL, 
            0x48214AF9D8E05272ULL, 0xA2293E778D195F03ULL, 0x7889949214DFA52EULL, 0x99987CF1352C8C9AULL
        },
        {
            0x9016503F61874601ULL, 0xC27182BB764AFED0ULL, 0xD5FB8B11FD3ED715ULL, 0xF04155A45D282D7DULL, 
            0xE5FC1EE02B975017ULL, 0xAE599012BF5D681FULL, 0x24F9BFF71D18D735ULL, 0x9A92871C169122EBULL, 
            0xE21414C4EBA1233EULL, 0x137F8E890EF5E312ULL, 0x7AC8A7177C43A51DULL, 0xFE499B0190FC4E83ULL, 
            0xB65230BB53FC0464ULL, 0x260B4971E827F46EULL, 0xB2E0F1904B764B06ULL, 0xDB4FFC971679A1F7ULL, 
            0x2CB4F2F4AC6B39AFULL, 0x45A3545CE105CBBDULL, 0x441F115F7D0EB655ULL, 0xD7473DECD5BA1B6EULL, 
            0xBD4F14FB4F9F1618ULL, 0xEF2AC465D3C6010AULL, 0x3B843EC15B9F7104ULL, 0x94449865133B1621ULL, 
            0x8F93800F2983D496ULL, 0x0F922ED40BDC71B5ULL, 0xC9C11FCE88A6D7DBULL, 0x8DF3448D3DA4C9B6ULL, 
            0xB77163F562F7B47BULL, 0xF42A63065E1E8AE0ULL, 0x6FB5DB5E7F90087AULL, 0x49AE6892E06322A5ULL
        },
        {
            0x3D55A8816763A174ULL, 0xEED0B20F9FD13822ULL, 0xE09184D20AD90DCBULL, 0x5C89AB558C8E0B6CULL, 
            0x081CC59462AA2439ULL, 0xD04E94781EDF9F73ULL, 0x6A6D61B58CD4D0FBULL, 0xAE4338F7C9E47703ULL, 
            0x75A99E0B1032FA12ULL, 0x6068761FC634D292ULL, 0xCA0CDFD24C30D183ULL, 0x5082172D4D62D362ULL, 
            0x3B503CF8B07D9DA4ULL, 0x3081635E09D9A4CCULL, 0x2F8CFEC0D07DCC0EULL, 0x7AFA28631B87E820ULL, 
            0x05A511A9E8349291ULL, 0x251F9606B09677CBULL, 0x90BD892DD763CDB6ULL, 0xC3B694E043BBD147ULL, 
            0x41FE043282D37CB3ULL, 0xD113ACFA114F7D87ULL, 0x3059BCDC60BEB17FULL, 0xBD3B1A7F5BCD4390ULL, 
            0x072532215709D86CULL, 0x96FB2685BFB06C14ULL, 0x34750AA8DDC6BA88ULL, 0x6E8478155EDE84E8ULL, 
            0x545B2D04764BC4C6ULL, 0xAC5B11FADAB82D54ULL, 0xEFA1FAEBF0D3E9E7ULL, 0x6F0EB93AEDD99F40ULL
        },
        {
            0xB4037299EA3E4976ULL, 0x785A74522A32ADA7ULL, 0xC8E460D181AB0699ULL, 0xC7A1454C064CEB5CULL, 
            0x838AF6A1E1715588ULL, 0xD2A6F9BD39C45216ULL, 0x82DBB6DC0878B222ULL, 0xFEA457E322BEFDC0ULL, 
            0xA34AF010286906FBULL, 0x0EE06F6DBA63672EULL, 0x80D7AE330706CEE2ULL, 0x7019E44E7EC3489AULL, 
            0x3E669A7583792B29ULL, 0xA865BF5C70D865F2ULL, 0xC0BFE74EE67B7E34ULL, 0x798288933B09C46DULL, 
            0xFCBE01B17F5C8D08ULL, 0xB085A3C06A5D23BAULL, 0xF9D8094F7BE786DBULL, 0x185656239A48E0AAULL, 
            0x1450BA7723FF02D6ULL, 0xA306DEC5D79C0562ULL, 0x3CE2AFB5734A0948ULL, 0x18AB38D3193F2E94ULL, 
            0xFC89F19D018A5742ULL, 0x1504AB36B58F66FFULL, 0x970190F0A1AD657DULL, 0xB07F2C44276AFF6FULL, 
            0x73DA96C80D8FE8AAULL, 0xB677B811DB4BDB98ULL, 0xD9D250D710300ACFULL, 0x47108B2E39802A55ULL
        },
        {
            0x3810D04D5B807933ULL, 0xA416A7F00D945D9BULL, 0x70CE6833D240A4C8ULL, 0xE9603A97FEC75E7DULL, 
            0x2DC7EE1A93239B80ULL, 0x9B6AAB632E4928DBULL, 0x44E98FAA627CCFFEULL, 0x037D3E7680B1441CULL, 
            0x5FFEEF1A1A8D8194ULL, 0x74BA5F36A16D7237ULL, 0xEA55AFD82645E437ULL, 0x6219DF3A22876D36ULL, 
            0x966DB3C7D05B6B3EULL, 0x5DF005EAE18F26CEULL, 0x95D8481056D041D1ULL, 0xA8FE1B70E7A80BC0ULL, 
            0x13BF4B0F3BC9E0C9ULL, 0x342789D55C7B7B20ULL, 0x579391FCFA498C53ULL, 0x9C02D2FEABD816D1ULL, 
            0xAA259DF12D599536ULL, 0xD2AD2D7AB1701902ULL, 0x6C39B0BA4BAAE951ULL, 0x5B4A6E04844D82E4ULL, 
            0xD05F6AA63204387BULL, 0xDDA9C5EEB9E8E87FULL, 0xBBC08B5FA076A400ULL, 0xDE8C8FCD26C7C085ULL, 
            0x1928533989DB4F4CULL, 0xAF8069F6E9DCF3A6ULL, 0xC47C5E70C4ACD698ULL, 0x447F0E802ECA1B58ULL
        },
        {
            0x0A068AFECAA1882FULL, 0x22E9617EC776B06FULL, 0x72DCB62370623CBEULL, 0x138F4209D8B4813FULL, 
            0xF229CC7784CE4F6EULL, 0x9735C38D0DD848C7ULL, 0x57A72991999738A6ULL, 0x68A9B0AC2BF0D2A0ULL, 
            0x7159FDADB101EEE3ULL, 0x5A0E1B8D3E271B5AULL, 0xDB2F0CDD60200293ULL, 0x84D796406D975F74ULL, 
            0xA269E5D505F39AFFULL, 0x6369BEEF174834EDULL, 0x414802D39ACC84D7ULL, 0x79F979CAFF292945ULL, 
            0x8E180ECAE3C08261ULL, 0xA40045E6415DFCE4ULL, 0x525A4F2DEAB38D3EULL, 0xBC7D3FE8601310A9ULL, 
            0x00BC25C193C82655ULL, 0x7787F4E58012A809ULL, 0xB4C9AEE607484C5FULL, 0x2FA012081E0A9840ULL, 
            0x42521EA41E6E0401ULL, 0x7957D300FB2CFC39ULL, 0xFAE10C21C63DE924ULL, 0xBD199BF97FEF269AULL, 
            0x817068F955F19775ULL, 0xDA919632EB05CD86ULL, 0x9E6C392645D599B4ULL, 0x1AC28A2C4B14A348ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Sirius::kPhaseBConstants = {
    0xC61D3FD8C15A90C2ULL,
    0x8B5D45E86E058469ULL,
    0x637D14C1826D5946ULL,
    0xC61D3FD8C15A90C2ULL,
    0x8B5D45E86E058469ULL,
    0x637D14C1826D5946ULL,
    0x550FF5B21805A294ULL,
    0x06A270D6B22E9E99ULL,
    0x75,
    0x63,
    0x1A,
    0xBF,
    0xAB,
    0xDC,
    0x67,
    0x29
};

const TwistDomainSaltSet TwistExpander_Sirius::kPhaseCSalts = {
    {
        {
            0x5A408CA986F6620FULL, 0x7AB479800611303BULL, 0xDAABFF9AC3F05A82ULL, 0x0CEFDC3D4B8C2150ULL, 
            0x87BD00BF6246E42DULL, 0xF9EEFF665241622DULL, 0x1C6F4825BFC7D17EULL, 0x039DF59C2FE12098ULL, 
            0x827E6036E07B618CULL, 0xDE179574404B9549ULL, 0xC392B90DAF1C8AD1ULL, 0xAC0775D90DFB8657ULL, 
            0xE52AC0DC8161F35FULL, 0x71B2351F6A1B5A4EULL, 0x71CB066AD4811B91ULL, 0x1124383AC37FD1E8ULL, 
            0xC1BF8FEEE766F271ULL, 0xAFB32FF3EB83F87EULL, 0x99FD1FF6088F3CD0ULL, 0xFEC4CFD8383D476EULL, 
            0x8555CDFC4C57F6FAULL, 0x542925D84CAFAEBEULL, 0x11CA5C933EE9E510ULL, 0x5E49345583B1F7B3ULL, 
            0x30C6C93A1B11DA95ULL, 0x2DA38A21D987A61BULL, 0x5B7CDE2897717DFDULL, 0x9EDCB2E4D489D1C8ULL, 
            0x0031AA92EB8529D4ULL, 0xA0E41F004753C6C9ULL, 0x49FD4D5F548F0AFCULL, 0x36D021FAEF06EE84ULL
        },
        {
            0xC922F97CB94DF6E5ULL, 0x315CC54BC23D2956ULL, 0x7FFCF2721D4A3858ULL, 0x6DB67FB357F59F49ULL, 
            0xBC6F939A487B0B3CULL, 0xC80BB54E7A6AAF13ULL, 0x0C72DDAA57334989ULL, 0xC9530013D43CB568ULL, 
            0x26A654ADA5EB499FULL, 0xD84326C11EB66EB4ULL, 0x95F6F2A62E1D7BD3ULL, 0x0CBCF3AE3DB31020ULL, 
            0x5A5E50B165460FFEULL, 0xF78889FA48DA7BBBULL, 0xBE34438F75D4333DULL, 0x48A37A154AD3824BULL, 
            0x20D6C0D0F74B620AULL, 0xC20CA089AD262875ULL, 0x6C1AFB521501808FULL, 0x932E8160E0C712FEULL, 
            0x51131DC0262010C4ULL, 0x02AD26533E148EA1ULL, 0xC3AA5732421A4802ULL, 0xF2EB40783E5E5368ULL, 
            0x24331D1529354BEEULL, 0x1F827747EF8C692FULL, 0x34901BF725B1E191ULL, 0x20B749171AE73D0EULL, 
            0x6254CCEC92FAB16EULL, 0x742CBDF257538D76ULL, 0x24A2F9B0D1CE6E8EULL, 0x467EA04F33FFAC36ULL
        },
        {
            0xD6650A0FBE146F80ULL, 0x9671D0548A87029FULL, 0x0707CA432889AF11ULL, 0xFE8017BEA9C62738ULL, 
            0x2A8E25AC895DA96CULL, 0xB8E43EC6BD9CEC56ULL, 0x95A83838AE9B64A1ULL, 0x914BC30F1A5DD89CULL, 
            0xB0D8B194F76302ABULL, 0x852F2627E47F887CULL, 0x74A91118F697B3F2ULL, 0x38F41E67A391634EULL, 
            0x5C8F7F90A91632C6ULL, 0x0B27D50642DC4CD7ULL, 0x2C3348861782FE92ULL, 0x9CFC5A7C13147688ULL, 
            0x9F0BCB28F01EF33FULL, 0x0C8EFD3ADA3AB060ULL, 0xE8C721D02F33275AULL, 0x4461AD977400EB89ULL, 
            0x8ED087D59220148AULL, 0x56ABA7BAE4FD17E6ULL, 0x48BB7D1662FE516CULL, 0x442A7AA382B38A2CULL, 
            0x45A4145A360002BBULL, 0x6BAB3B3A2C56CE3CULL, 0xE2BC3C5F5B337FA7ULL, 0x558012D40C8CD196ULL, 
            0xD393E2077CE5873CULL, 0x451A5B6B88B90DA0ULL, 0x87B08C4C130B1AA9ULL, 0x7C1A23613ADF6C84ULL
        },
        {
            0x5953CE1E9E08241CULL, 0xC6721DB436EED87CULL, 0x888ACF9A30C711FCULL, 0x491FBCDC6870C0C0ULL, 
            0xC38D695816045072ULL, 0x7B4761C353E206BBULL, 0x51314AA37B86834FULL, 0xFE5D835BE563BF6FULL, 
            0xC36EFE23D8CEF5B3ULL, 0x5B3ADD9B0D45CC5EULL, 0xEE95805FBA2B49E9ULL, 0xFEF1C119E030A7BFULL, 
            0xE5135E92F4C27ABBULL, 0x328C785E8B8F584EULL, 0x083511ED5C8A2813ULL, 0x15B97BD567E5664EULL, 
            0xCF41CDD0773BD227ULL, 0xBE8169244B83F602ULL, 0xAE24E7CDCCA641F4ULL, 0xD0473F98C7AA5F62ULL, 
            0x14FFDF3A6395E90EULL, 0x8113E51B418C783FULL, 0x9FCDD5F2ABD91670ULL, 0x82BF57A6D6EBD088ULL, 
            0xB84A22CEB75F3D00ULL, 0x0E32DBEB5BB9E701ULL, 0xCB4927A656BB0FE5ULL, 0xDC436FEF5056D6DAULL, 
            0x0B370A356BAEAEABULL, 0x27247AA43C14FCF5ULL, 0xC7BB348258D17D3CULL, 0xC67790249C4B0246ULL
        },
        {
            0xEC15D1CA6317DEF3ULL, 0xBF2EAC30FC764331ULL, 0x22043CE05DFE5BE9ULL, 0x580C1CFA4B8CFD3FULL, 
            0x34B0280694CE7B2AULL, 0xDEB287EECA5E4D3BULL, 0x78385C787470D7B9ULL, 0x7D5D4A8CC00E4AA4ULL, 
            0x40492C15C98EB492ULL, 0x429117584425E10DULL, 0xD94D9D61A38B3646ULL, 0xD3DDF688F5CACF57ULL, 
            0x33A46FA165A53517ULL, 0xB5D9C9FEDC79175FULL, 0xF6A6CFD8E134B396ULL, 0xEC11442FF0DA16D1ULL, 
            0x5886F91CCB28A35FULL, 0x532AD1B93EB57B0AULL, 0x4F34B05839148636ULL, 0xCCFD2B647350C1D3ULL, 
            0x716AD10DAF6B5978ULL, 0x25E73D025A853FDDULL, 0xC3AB4AF1663E05DDULL, 0x85CC2A46EAE9C1D4ULL, 
            0x0DDA04DF4B3BE30BULL, 0xE40232FFA916E081ULL, 0xBEB035BE78396213ULL, 0xDCCB21CB976D0FB5ULL, 
            0xC22F6B1BF7F176AEULL, 0x6256B7FE1E19E8B6ULL, 0xAE6F0E9E55A50E85ULL, 0x8114BF33EC244D85ULL
        },
        {
            0xED451C6949D2F4E6ULL, 0x2096D955D7AB66DDULL, 0x7A15D070F3EC86E4ULL, 0x369038C29DFD3790ULL, 
            0x113A8285EF78CAC2ULL, 0xE334F98565FA6EC2ULL, 0xEC46A87767AD972CULL, 0x6D30F1ADFCF32BD4ULL, 
            0x64860E099807739CULL, 0x0AAF16ED94342862ULL, 0x82D657A30D3F556AULL, 0x664908432F035F8EULL, 
            0x00F9ED4782ECBD38ULL, 0xA8CA22A701F90A47ULL, 0xF26BB41C22CAA5CFULL, 0x10E3AEBD1075BF70ULL, 
            0x0AE3FE929E65092EULL, 0xF5C29874223C2AA5ULL, 0x6D666AB007183496ULL, 0xE6BF888639692304ULL, 
            0x5D93C7AE4DD436A4ULL, 0x552CD187E666473DULL, 0x3E298EF4E592DA5BULL, 0xC4FFA3BDFCF93E17ULL, 
            0x8FEAC3FA947FA740ULL, 0xE4343CA776775D7DULL, 0xC5DD292E7FC0F24CULL, 0xF9FE9AF2DA147195ULL, 
            0xF4D83CB42A64E2FAULL, 0xEA47B395649D5A34ULL, 0xBDA33FE3CBCB671FULL, 0xDE351468D163E9A1ULL
        }
    },
    {
        {
            0xB23E4E5484AA7FE1ULL, 0xD4BD085E24A5F735ULL, 0x5A7A613F30568FF3ULL, 0x15B229F74483BFD8ULL, 
            0xCCA9657F330A92E3ULL, 0xE46D2175988490ECULL, 0x84961EA78738A1D3ULL, 0xB7D12DBC14A78892ULL, 
            0xF6199C84F47B4473ULL, 0xA7F196998EFC5165ULL, 0x590F11367AAF8E8EULL, 0xB1133C92D7D99670ULL, 
            0x471322FD1B8817F3ULL, 0x4E7E0701B85DCEDEULL, 0x490EC71984658B98ULL, 0x6DC30CC30C3B126AULL, 
            0x20DF2FC7104E2343ULL, 0x13B7BD4E8D05EEB7ULL, 0xD471D776150F1F9EULL, 0x24E0E4C3F3EDC5CCULL, 
            0x205E1A868F610D7EULL, 0xB72CBA0AA3C85FDDULL, 0xE2DFE60D1F0A1BC2ULL, 0x52630D2DC58BDF07ULL, 
            0x2915452CB94870D3ULL, 0xF93E19E4D46A5156ULL, 0x66AC8C9557FDCCAFULL, 0x9A22E0D5529F2ABBULL, 
            0xADF38F49FC337C0EULL, 0x023C64C7931DF1A3ULL, 0x8770453D8657666FULL, 0xB6FD6549845EC072ULL
        },
        {
            0xF6A1DCD63FEBABF2ULL, 0xE5A2424CB33322A6ULL, 0xF787082ECF16E46AULL, 0x25F711CE962F4181ULL, 
            0xE927E486A76D6D61ULL, 0x17E7A5E57BE1DBA3ULL, 0xD084D087B6E7F298ULL, 0xF3CDA3A98A0D4601ULL, 
            0x2241A2ADA12901C9ULL, 0xDF6F9118C98E584CULL, 0x771E311CD49A2E33ULL, 0x3DEE8CCDD6C3E84CULL, 
            0x55297D31595277E3ULL, 0xD03CCF0F0E819A4CULL, 0x67B1C819CFFA3C04ULL, 0x4DA1865D93FED26CULL, 
            0x633C85080DF49CBAULL, 0x39363027C876C547ULL, 0xD00D379430E8E4B6ULL, 0x2AA313341AF995B2ULL, 
            0xE0F87419FE5BCCC4ULL, 0xF5936DFE9978FBF7ULL, 0x58C432BF7E97273BULL, 0x626A52A0E7DCE950ULL, 
            0x56BBFA5A50298F3EULL, 0x335FD5074DD05906ULL, 0x24E4BEACE6372E60ULL, 0x7E36A0359F570127ULL, 
            0x652ABF9963191CA0ULL, 0x8BDED7DDF7F30D28ULL, 0xBD5C79EBD9EE87EAULL, 0x95D35AE443846123ULL
        },
        {
            0x1DC2706C25ED998CULL, 0xC252FBD6C4133977ULL, 0x056D1DF059E85013ULL, 0x9415D9EE0AC52B0DULL, 
            0x0F1D42712009991FULL, 0xAA8E200B4C8A896CULL, 0xC5402AF1908FCA0EULL, 0xC8E75BA64E5F645EULL, 
            0xE86FA37C12DD9601ULL, 0xEB63F0A7A947409FULL, 0xD88D02E161994F82ULL, 0x7FD010D2A6302835ULL, 
            0xBD5C762FE790A3F1ULL, 0xB0878693545FC442ULL, 0x1EDBD64461C791E1ULL, 0xDEF2A78906C4BF53ULL, 
            0xAA6835957B249D72ULL, 0xFCAD1EE5A510BC1AULL, 0x34CE57AAD40DA9C3ULL, 0x25D425021535EEA8ULL, 
            0x6BA4C4921BC71120ULL, 0x386742DC257F5A16ULL, 0xFA288FD771895444ULL, 0xDBF3C31B91F72D73ULL, 
            0xD87A7C8642B2051CULL, 0xDBB72D830BC51000ULL, 0x004622326C2EA2ABULL, 0x3EE19B8475C41387ULL, 
            0xF236F63BAF4E0C56ULL, 0x1D0375CC34AA5AA6ULL, 0x3594AF212FECC5A5ULL, 0xB12CF73DFCA67725ULL
        },
        {
            0x0F44E3B9658D76F9ULL, 0x308EB9C0B83323FEULL, 0x63FF4639F1470858ULL, 0xD30CBC89CC3354B3ULL, 
            0x0619E41CEE7E54E9ULL, 0xA3428172EFF499F9ULL, 0x0B7DB37E40EF0C6BULL, 0xE0637B40B4558663ULL, 
            0x84FB617B96D89732ULL, 0xF6D6C6633E1716A9ULL, 0x9776C49D659E2CDEULL, 0x1787587DC37375DBULL, 
            0xAC685477D262DBEFULL, 0x6631E9BC6BC6E083ULL, 0x5049928A1EC0582BULL, 0xEE25D87616085A99ULL, 
            0xB415FA48E87AC6D2ULL, 0x37DFB48FC9E3F351ULL, 0x5C201068235C5B9EULL, 0x09E5BE08EA53D6C1ULL, 
            0x27963FD7952B79F7ULL, 0xB2687292A3B58D35ULL, 0xDAD4E7E06533F0EEULL, 0x374BA363F7B9E5A1ULL, 
            0xB1C36D5F3E715C91ULL, 0x6217F6F0C926316AULL, 0x0364E138E155A041ULL, 0x49525EB64C757612ULL, 
            0x47D735AFD95CBFB6ULL, 0x268A57AECCE0F94FULL, 0x3A3B557081A32E74ULL, 0x7783E0B8683F7543ULL
        },
        {
            0x7B0425F6C04D5F8AULL, 0xAF1F495F77B37335ULL, 0xE6ECF678356962FFULL, 0x4698FABAF5D07C37ULL, 
            0xB1B52C9FC530D50CULL, 0xD34C2EF1B4427CC9ULL, 0x95AA909A71B321CFULL, 0xF92357E4060D649CULL, 
            0xCEF0C8687B5D4D65ULL, 0x39FFF104BBB0B6D2ULL, 0x66EBCDD75D0EB905ULL, 0x4A9AF649B18894EBULL, 
            0xA9CACC8985EA2909ULL, 0x91BEB851C2D54E3DULL, 0xC7122D7A7C792179ULL, 0xC1240933054CA50BULL, 
            0xDD12A1914A047DEEULL, 0x6BFCEFD4BA18820DULL, 0x550C40143F46EE66ULL, 0x582BCF17D48F45BFULL, 
            0x4EE13EEA5FD7D871ULL, 0x18001683A7250739ULL, 0xA9C4E22647768D32ULL, 0x2F6472A0855A83CBULL, 
            0xB4EA9EFA0B8FD95BULL, 0x01930D10B33D357CULL, 0x0ECFF377919911DDULL, 0x0E59B07821DBC51BULL, 
            0x8755E7BDBA758BF9ULL, 0xF4BF389B22DBCC12ULL, 0xE1B470F023557EC2ULL, 0x690C362151E5C16FULL
        },
        {
            0x45462BDFCCF6C663ULL, 0x92280BD6ADE2B665ULL, 0x963948BBF89BD83FULL, 0x0272ACCE3B0FF1AAULL, 
            0xFABB4DC17385C9CCULL, 0xB6F00133824FD991ULL, 0x704CDF4EAA89BDF6ULL, 0x7F5FEDAC955CD9EDULL, 
            0x9C92B848D390B5EAULL, 0xB598411A8C34D788ULL, 0x9B3166650B138B9AULL, 0xC8C2C62E6404118CULL, 
            0xC2F2EB2D89930471ULL, 0x040B8A88E3518267ULL, 0xCB0B749BA86564F8ULL, 0xC16C9247B2426F73ULL, 
            0xAEF579CD6671D268ULL, 0x8C3E17FE046DD56BULL, 0x3BF3EBA12B6B6B9EULL, 0xA7F38BF0FA243FE8ULL, 
            0x97840A26983C7733ULL, 0xBBC936CDC03156B2ULL, 0xC9D766EBBC9E412CULL, 0x80D876C18FFEEF2DULL, 
            0x1AC5852B81326DEBULL, 0xE4751772666960A9ULL, 0x962183A9EAA8C4EDULL, 0xE30E437027D97C2EULL, 
            0x698ED880CCEB1B78ULL, 0x131E320E02D9375FULL, 0x3ACEE94304676871ULL, 0x51AF33154054C0D6ULL
        }
    },
    {
        {
            0x9AD47E7968B1D291ULL, 0xB932050CAAB37C3BULL, 0xCD3ACD805C79E476ULL, 0x379D5647A79BC78EULL, 
            0x4E949E9509B05C1AULL, 0x58C4CBA79A71FDA4ULL, 0x5E7FD27064C86107ULL, 0x1A4322BC0A0793DBULL, 
            0xADF16613354431D3ULL, 0xF6F7C6D85665CB42ULL, 0x5985612DAD2FAE7CULL, 0x8BA65D200EF6F1EBULL, 
            0x4A5CA5595505551CULL, 0xCEE0BA7905D698EDULL, 0x370E7CA7961C89A0ULL, 0x0F53A2EF8127CD7CULL, 
            0x26683BF712958E88ULL, 0xA1B300345B8AABE7ULL, 0xA1CF5E69212C4665ULL, 0x4865F158AD946A56ULL, 
            0x3A15F43BF3F535F6ULL, 0xE031FC1461FE5835ULL, 0xCDF882731E53549FULL, 0x94BC7EA5BDCA8CD7ULL, 
            0xB5491A25DD695416ULL, 0x77750F6555D71DE5ULL, 0x191F148EA5862B2DULL, 0x1C6613957F9ABAAAULL, 
            0x790BDF41C46985D6ULL, 0x0AA615062860F116ULL, 0x5783321620CAE177ULL, 0x3595D4689555B1CAULL
        },
        {
            0xB47833BA113A3640ULL, 0xD37044E228B4E775ULL, 0x117BADCBBE6BD42BULL, 0xCBAD4C5807E4BA8EULL, 
            0x1170F5F81787D278ULL, 0xB4FAB2E45DDB5ABAULL, 0x634BA1EC5F427BDAULL, 0xAA46B2419420F83DULL, 
            0xAA1934C7AA506DC8ULL, 0x254798E4486436F1ULL, 0x9182A5FF2E08166BULL, 0x7B5CE64B71995CABULL, 
            0xB0A77126831C36FCULL, 0x9F4B3B362C7006C2ULL, 0x9CA6D58788A35D71ULL, 0xAD2ED9A03AB791BEULL, 
            0x9D54207400430DFBULL, 0x3E3319F93E877D49ULL, 0xFA12310CD68AC1F4ULL, 0xDE56454F1472BC97ULL, 
            0xD546C8007283A8B0ULL, 0x2EDC830F8BE72DDDULL, 0x605AEAEA9D2E7836ULL, 0x11C59ABAFF842971ULL, 
            0xA4E02486BFC6EAE5ULL, 0xFAA2B19DFB12115DULL, 0x14CB7DDC70AF90F2ULL, 0x5A991E087BC1CB41ULL, 
            0x20D1A52D18E349A8ULL, 0xA2ECC6900A3F29CFULL, 0xA8E62E173BF728BCULL, 0x0E28031F8C1B06D3ULL
        },
        {
            0x4FA2E28E4D9EF0A0ULL, 0x1A72429ADC4ACF58ULL, 0x1EE696C8951A01FBULL, 0xB3606C64B50008BAULL, 
            0x7289579EB4F99342ULL, 0x106D25752BBF1975ULL, 0xB037D61741635488ULL, 0xEA614B4B71B98BB5ULL, 
            0xE031DF548409960FULL, 0x6BFB8B7B49FB598DULL, 0xF09C5B71F83D9C9CULL, 0x8460D5FCECE73A23ULL, 
            0x82B5499E5485C8B9ULL, 0xD5384B38AA801C4DULL, 0xCF44715A96D185D5ULL, 0x05EFFC09B1FD11A0ULL, 
            0x832998A4941E24CCULL, 0x60D8C221ED20371CULL, 0x75E40EC14AA453E0ULL, 0x42F7CB21B78F3EBAULL, 
            0x7D5F7C096AE7A61BULL, 0xF8E324AD9C6A9E00ULL, 0x38649B0F10731507ULL, 0x38D5ACF2EDF26802ULL, 
            0xF2632D455EF90DEAULL, 0xED0D5BCB085D2E66ULL, 0xF1E224FFEB02FF59ULL, 0xFF4E79F65A76C866ULL, 
            0x1976ED228E68D910ULL, 0x8C3821FE1D99C0E2ULL, 0x43AEF49224EB2165ULL, 0x0129F88B72434D3CULL
        },
        {
            0x6E66457BDE899294ULL, 0x0B5613F797CD6C52ULL, 0x14670D9321B9BA3AULL, 0x24B7769E4ACEFAD6ULL, 
            0x2968344C09C03393ULL, 0xCFC52DA22BDC1F5EULL, 0x15BAB086B20BD612ULL, 0x57A143B62C860886ULL, 
            0xA4111ED2461D20A4ULL, 0x35C617B44947E212ULL, 0xC2A5EC4C94A1A4CAULL, 0x12C5DDC5973597AEULL, 
            0x32C66DADFDC043D1ULL, 0x79488F108E3E18BCULL, 0x584CA07A24B41BD6ULL, 0x371C29F17DC56A48ULL, 
            0x9299D47229A37616ULL, 0x44F87B0799E6708AULL, 0xDFEC471B2CBCCAFDULL, 0x908AD830D3F6A277ULL, 
            0xE769EE61B142E628ULL, 0x4465A1EDAEA452A6ULL, 0xA9BA763F572BE187ULL, 0x54DD6094466EE9D6ULL, 
            0x1257101990844A79ULL, 0xFB2EE89D1EF40259ULL, 0x87E7A9A7300C16E5ULL, 0x92C486DB6A0DFC4EULL, 
            0xF9902B6632A6250EULL, 0xB89689C02CDB1E07ULL, 0x1F2B7C6F4DE6C5B4ULL, 0x1E64FC5C48ED1E23ULL
        },
        {
            0x1F8E34CFB5072C91ULL, 0xB6A72CA6BAB215E8ULL, 0x8FE54915A0D01EF5ULL, 0xB7F7A00C73759C6BULL, 
            0xAEC0A09C87C381ABULL, 0x9F87E0A6EA2D7E05ULL, 0x8152C1994497F2CDULL, 0xA4A7F77FE857A5BBULL, 
            0xDB3CFAF1604FC2ECULL, 0x08D8172FC4294570ULL, 0xEA154C159F9D7669ULL, 0x1CAB1BB5A20D62D2ULL, 
            0x7B7DE6B0DA324E6EULL, 0xBE0D4449EEED9701ULL, 0x98E6F7EE2C3F6436ULL, 0xFBAE9AE680A31225ULL, 
            0xC17F7255037E2A1EULL, 0xB9F908B2422E2B42ULL, 0x26C883783B7EF899ULL, 0x48F233A22991CE5CULL, 
            0xEB31A945B97B8DCEULL, 0x176E3ACA2825478FULL, 0xA5FAC823E88C6B1EULL, 0xA246779B007AF642ULL, 
            0x99A699CA4A40C05DULL, 0xE49000AF161C85E2ULL, 0x07DCD9C611633910ULL, 0x73F14F9700A50069ULL, 
            0x33768C8D3F666020ULL, 0x84D230F75046D8D6ULL, 0x72F2D59F8EDC9B1BULL, 0x59E7025B79730390ULL
        },
        {
            0x3D0CE02456B5CB33ULL, 0x47AD79DCF6DB143FULL, 0x2AB81C5F544918E4ULL, 0x625B8EE0B81FB921ULL, 
            0xCF422D0E87687DFDULL, 0x8EBE325AF9746114ULL, 0x5177E7C32FD28CBFULL, 0xF5F015821418ADC2ULL, 
            0xC4663A1991944435ULL, 0x3C5E65686422C9B2ULL, 0x2233D2321A2764D6ULL, 0xEA3F518677F0CD05ULL, 
            0x6A0525AD6432DFD4ULL, 0xF3ECEC21759E57DFULL, 0x654699BEE3552999ULL, 0x3DF427333ACCBCC6ULL, 
            0x2DD9C870405A3B02ULL, 0x91791AD6E20C3C72ULL, 0x25D11FD11FA09AD9ULL, 0x64B7C92E2696BB2EULL, 
            0x932088E579BDE124ULL, 0x09A358BB43587130ULL, 0xA62C114EE7DA8186ULL, 0x3A531A500ED17905ULL, 
            0x19971F6FB395DA03ULL, 0x8C1E4A147D3AA208ULL, 0xCF7BCCC3EA1D9DB1ULL, 0x2881F64E749C54E7ULL, 
            0x31B3B6BFE8668AE3ULL, 0xFB84A908EFFD7C7EULL, 0xD77399D3EB82A63DULL, 0xA22CFD1CADE60A23ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Sirius::kPhaseCConstants = {
    0xF4861B74211A201FULL,
    0xCA0C65A49E635B0BULL,
    0x8429DB5B95500E80ULL,
    0xF4861B74211A201FULL,
    0xCA0C65A49E635B0BULL,
    0x8429DB5B95500E80ULL,
    0x59A1A606469A0B0AULL,
    0x874E71FF779BF6EBULL,
    0x26,
    0x2F,
    0xFE,
    0x38,
    0x85,
    0x2F,
    0xED,
    0xCD
};

const TwistDomainSaltSet TwistExpander_Sirius::kPhaseDSalts = {
    {
        {
            0xD564A68CCBFCCA92ULL, 0x98141E028258D289ULL, 0xEF69B2639D69BAEAULL, 0x27C333A96432EAFDULL, 
            0x1F53135E9B8B1AD8ULL, 0x6BC8FB567CD9929DULL, 0x2BF975DA372A969CULL, 0xD4CEC3146BC2734AULL, 
            0x167F6630F62F35BEULL, 0x3F7D998D25BD2325ULL, 0x8EE79C8E0E34AD29ULL, 0x5A9B0F7F15E6EE36ULL, 
            0x562B6E6CF310B657ULL, 0x5B38D301185579C0ULL, 0x74AF718C937E6378ULL, 0x71EFA4FD8523CEE7ULL, 
            0x4BD2C7C09C652C89ULL, 0x819182861F697B08ULL, 0x728E29EDF66CFEE8ULL, 0x2C40951512F22904ULL, 
            0x3C83661C7650B61BULL, 0xD4B6BE3186BD620CULL, 0x9498B50183BF585CULL, 0x914C0E01C33E6961ULL, 
            0x278D26B45EFF9553ULL, 0xB378269A17EDF0ADULL, 0x505E7472DBF72EBCULL, 0xE3659022F4B3BB10ULL, 
            0x12423EB0D8B249A2ULL, 0x5B7655CA9A2FDCE8ULL, 0x6BE2074B8B97BF79ULL, 0x9CB3B4858657B118ULL
        },
        {
            0x5E70AC333B07837AULL, 0x21565DFF1490E876ULL, 0xA4E31F5304F155DFULL, 0x1E357D1A2D3A2AD0ULL, 
            0x72808277707ED5C7ULL, 0x8D14559461006275ULL, 0x97FBCD365871EAFEULL, 0x2A3B140C59A66E71ULL, 
            0xB225F249ED6990C0ULL, 0x8F72A2A8CAA82AFBULL, 0xA7BAA95B2D0C5604ULL, 0x11BDC3FF46EB7C95ULL, 
            0x2D9C19C1E5E266E1ULL, 0x45A7ECA065F396CAULL, 0x61047516C69AB1DAULL, 0xAFB273AE7305AFA1ULL, 
            0x187DAC31AADC8E22ULL, 0x0CF1AECAC5E86D92ULL, 0x63C5BCBDA7F3945CULL, 0x94C76F2267038910ULL, 
            0xF61026FD8F0E7238ULL, 0x3701794D56FCFCECULL, 0x670E7D260DC9B8D0ULL, 0x54FE27826AB04D70ULL, 
            0x77D357DFD3BBCBBFULL, 0x535BC6F0E894189AULL, 0xEF60B0D46BED0C02ULL, 0xF0E16284C0032946ULL, 
            0xCD0A9118BB9179B8ULL, 0xAECA84B0D469AB01ULL, 0xC4DC65775903683FULL, 0xD79CB323F64B051EULL
        },
        {
            0x1BB6682C61F1036DULL, 0x78914CB17C677FD1ULL, 0x3C60380023C1351DULL, 0xBB7FF9DBEFB9C0F0ULL, 
            0x9550D5F250724023ULL, 0x3D4E9C6BC5032412ULL, 0x2ED9EB599E944539ULL, 0x0E13A2038276170CULL, 
            0xF3C07C6AB3EFC34FULL, 0xC19A85FB5FE93B21ULL, 0x18371A7FE63BC6D2ULL, 0x40B5F8B48471B20DULL, 
            0xB80EF09956C0E842ULL, 0x6DD00E591B3C70BCULL, 0x0D81A2FD011473FDULL, 0x5A9C7BBEB2044F3DULL, 
            0x46AF37C1A6281AD4ULL, 0x1E90C22C7B4E7EEFULL, 0xD9D9A2D0A37CA3EAULL, 0x4AF3187C240DC107ULL, 
            0x09B0398AD85CA59BULL, 0xCA9A0434AF861B0AULL, 0x8F686B0A163444FBULL, 0x32DA37C6FF3727E1ULL, 
            0x81FD080D5ECAA038ULL, 0xBA7D4C1EFC9177B1ULL, 0x7ADA4F70C3F519E7ULL, 0x652A85857709EE58ULL, 
            0x9DF7C10C3985821DULL, 0x8CF9895CE5E34740ULL, 0xA4B6D4E3E143B230ULL, 0x8E265B0591E6A0A0ULL
        },
        {
            0xA2CF2417F76FF6A7ULL, 0x40A5FA13C305D9D0ULL, 0xFB7BFD42DE251E48ULL, 0x024DC45E46DA1D84ULL, 
            0xAAACC09BC91C56ECULL, 0x8F96A1E6B56724DEULL, 0xAFCE4D2FBE63FA27ULL, 0x8AA22CBBB4BCCAF9ULL, 
            0x624CA3D239B2D9ABULL, 0x771506484AA06525ULL, 0xB1C2C7B0992757FBULL, 0x79FD5FC7849C546AULL, 
            0x4A97370B3C0919C4ULL, 0x903354D0608D3E58ULL, 0x8665F7FE0E10415FULL, 0x9CE56D14A4AB51A1ULL, 
            0x2677BE866892AA80ULL, 0x1B670112F145BEA7ULL, 0x53B53EFEADC72D10ULL, 0xAE238CD32FE58739ULL, 
            0x26B0071C9F3B9284ULL, 0xCD1B1B1ABB248D1EULL, 0x8D396A83A87BA8B7ULL, 0x610D07EB33EFD62DULL, 
            0xFC8026055B935B89ULL, 0x9F710DC4F2F50555ULL, 0x021220F1A7B63B34ULL, 0xE216FA03CEA83685ULL, 
            0xF1B5C0D248BE19E9ULL, 0x0CBEF60A812EA571ULL, 0xC4BC7C5D02655500ULL, 0x86BCC7ED121221C4ULL
        },
        {
            0x7DA7418DB6C19F0DULL, 0x8E3FAFFB962A7D0CULL, 0x14DD8C643569E7BCULL, 0x1333C8E8997145E3ULL, 
            0x9D8CCAD225D76E55ULL, 0x112877EC5E301205ULL, 0xE0A67D2592C0CD1CULL, 0x111F1497D9AE02FFULL, 
            0xC7C3A7A581A09284ULL, 0xDC5E0343CD347A75ULL, 0x8C991086609538A4ULL, 0xAD84BB00E6BE43E8ULL, 
            0x448D0B584B94A215ULL, 0x370BCDAB6E46F09EULL, 0x9494DB1FE3981A38ULL, 0x90AE8035F12AF5EFULL, 
            0xA8D6BE1581B4255AULL, 0xE2611F78A1BDBA6EULL, 0x21C12B3CF96DFE90ULL, 0xF9F61F9E0A5EC1A9ULL, 
            0x21FA31E1A00BE8BAULL, 0xD743502E4D5557AFULL, 0x218F8688FD67C6F8ULL, 0xC9AF9D330E1C369AULL, 
            0x1FA44730ED3DD3C6ULL, 0x64E917EEF103B6C2ULL, 0x8A48D701BC52ACD4ULL, 0x89C9D63CADE27C19ULL, 
            0x3945EA7E544F6041ULL, 0xA1C73F9325F8B18EULL, 0x89603D599CDED651ULL, 0x0D11EDF79DDBA1AFULL
        },
        {
            0x11419232D0E25FBFULL, 0xEA083DF38DE30306ULL, 0x73B9D6F14E7AA4EEULL, 0x744529FE27B61B0BULL, 
            0xAA20D62C48A48B83ULL, 0x87D1260B53D823D3ULL, 0xAC3ECD43E34BD40CULL, 0x099112A6ACA7735AULL, 
            0x667E7B246E1C5B25ULL, 0x5289815D04CE0B36ULL, 0x1525D59ED09D8002ULL, 0xB5A80D59CF3AE65CULL, 
            0xEEC79623C68840DFULL, 0xF1D9928942EEA273ULL, 0x6F622DA9E79BEE6EULL, 0x1368B6FC2E1C9F80ULL, 
            0xEF13CFAF8945E24DULL, 0xBCCE83798FF267F3ULL, 0xBB0DE44896966008ULL, 0xD1E1CA4057C9AC66ULL, 
            0x7F88E87AC32269F0ULL, 0x9F5593FC24A0A63AULL, 0x9CD3D0B488FA8143ULL, 0x4A0FD34F4A2705EFULL, 
            0x12E2A76CCAD8D0EBULL, 0xB4B52E3F5CE51D7AULL, 0xC1B094E79AE6B786ULL, 0x4C940F2A86D39EFBULL, 
            0x81B83DA6957DF5FEULL, 0x12D9F4743307B4F7ULL, 0x5DDF165129BC8CDEULL, 0x161609D05ED9FC29ULL
        }
    },
    {
        {
            0xB36C99E6F0A908B4ULL, 0xAC577C007CF1F006ULL, 0x2A16CB44E6581A85ULL, 0x025D8E9ADC2226FBULL, 
            0xC5E8C635AE4C6E2EULL, 0xC700A7D4BC798903ULL, 0xBB2FC09A7D594C1BULL, 0x50038C380F69AF62ULL, 
            0x5BFD1EECED339F03ULL, 0x1D9B43B8CF649497ULL, 0x7E25E567F471498BULL, 0x452FD6B2750B74C9ULL, 
            0x839DC7F3571141BFULL, 0xC384C4B44B98DF1DULL, 0xEAFDCF8B81A3A554ULL, 0xB5FFEDDFC59FBC45ULL, 
            0xA237D7074DFBF337ULL, 0x6ABDAEC1552F8F98ULL, 0x0928BFFE16D7CF63ULL, 0xB29BC15BAFC666B1ULL, 
            0xC3D60DB6012BCED7ULL, 0x291ABE4247C1CC18ULL, 0xB40662D8ABEAB823ULL, 0xD2A7189F68374CFDULL, 
            0xE527B0F5E658F9B0ULL, 0x89A85A7BEB1F358FULL, 0x222D7A260442CD2DULL, 0x87D91B4D1AF7FE42ULL, 
            0xE65DECDFD9E09721ULL, 0x2855D0B4EBFC58A5ULL, 0x8410D389005C2E6CULL, 0x042D777F3D653411ULL
        },
        {
            0x33F6466E4A691999ULL, 0xDB313E5076CA31DCULL, 0x87BDCB716BED2FEAULL, 0xAF248DEDFA523787ULL, 
            0x77837D93802BEF5DULL, 0xF55B58F14AB0F20FULL, 0x7C8B2E5F7B4DE6FDULL, 0x1A620FFDE2DA8665ULL, 
            0xDB7C85FBA58085E9ULL, 0xBF6D71D9657B2934ULL, 0x3069E68C2148AD83ULL, 0xEE3FD459C08A20A2ULL, 
            0xCA85F71617255504ULL, 0x6C212A7A4776E8E2ULL, 0xAF294AC84BFB82BBULL, 0xFD4F7283EE4E373DULL, 
            0x8607FF6C1D364639ULL, 0x40559C9864A20AE3ULL, 0x062A8BE7DC2B6BDCULL, 0x792DAE7F6B417C53ULL, 
            0x38BD5BFAD31D96D9ULL, 0xF1F454DE457077CAULL, 0x5EC9A9D649396A6AULL, 0x7EB1BF2E7B13754DULL, 
            0x2EBA50C9FB4381E9ULL, 0xC037ED7487DAF281ULL, 0x4518BE8B06F15D27ULL, 0xD09A696830757B67ULL, 
            0x2E09AB0E174936DEULL, 0x353DB63B3268318AULL, 0x9ACC1A47A524224CULL, 0xE1CA1F57ACC3E23EULL
        },
        {
            0xFBEA464AE45B7B2FULL, 0xFA3179482B8A6DC8ULL, 0x209B55D1C11DCDBDULL, 0x49FF8DCD0ECBC1D0ULL, 
            0x14CB34A17AF0DE64ULL, 0x8ED186332D8C9237ULL, 0x0650D8CA8B1FDAB8ULL, 0x1A90648CDC38D6FFULL, 
            0xA30FB7C7833E61D9ULL, 0x3687BF0EE298A634ULL, 0x304B1AE132794CF3ULL, 0xA3526F805186055AULL, 
            0xDE34CDC998080846ULL, 0xF61703DBB50E7F24ULL, 0x28DFEA138B448213ULL, 0x87C7F9A768F29D66ULL, 
            0xCCCB87402C482365ULL, 0xB1A7ADB59A4237B2ULL, 0xB2348E481BC3EE27ULL, 0x349E7F4241FA9579ULL, 
            0x94AAC212F7ABF314ULL, 0xDA30AE7431D2A580ULL, 0xFF5C17F06350DA5DULL, 0xF236011309123D01ULL, 
            0x62BDFDAC0F945DA3ULL, 0x2016D35EE5552B43ULL, 0x45EE93E7A6392E5BULL, 0xDE6D1C83E09F30F3ULL, 
            0xC52FA27E8BCF5DFDULL, 0xB9976B42F56A5294ULL, 0x59EC771740A1D99AULL, 0x1DFD48954AC4A67DULL
        },
        {
            0x1EA9322EB073FDE9ULL, 0x8D8EDB9106D431FFULL, 0x61B883CB0AC7B401ULL, 0x2213D1AD7AFC1F21ULL, 
            0xFFB0CFBFEADBB16DULL, 0x3109938D337B47F7ULL, 0xF7736DA048AD0385ULL, 0x38E48B247A054D99ULL, 
            0x3DD4F4789B64128CULL, 0xA3B2610774F2C4AEULL, 0x8A269104482C8187ULL, 0x7091ED57D051D711ULL, 
            0x138B8AB1043F972EULL, 0x90C83D99030AE11EULL, 0x5BB2CB8B99080ABBULL, 0x08980CC391F88F15ULL, 
            0x6B4B1C2F34E01447ULL, 0xF67EDCA515886394ULL, 0x5748482B4ACC8E8BULL, 0x51132EC53F05DED8ULL, 
            0xD4751C237A434898ULL, 0x28B7871F09A8E8DAULL, 0xDD1E6D6BEC44A471ULL, 0xA93E7764152F4DE1ULL, 
            0x3EBCF297C3DAD371ULL, 0x0533866A01D35471ULL, 0x5B2C573E20184C57ULL, 0x0487E3FB3D1B84E0ULL, 
            0xCE5E1C79C09F414AULL, 0xE37A6EEC6DC90997ULL, 0xB7C86CA5A8A2EC66ULL, 0x72ECFA1243280E30ULL
        },
        {
            0x1C53DC85E202D9E1ULL, 0x0F19819C51903F92ULL, 0x8FB312C34A8C79B0ULL, 0x8BECB0F8F43D884AULL, 
            0x568AFEAB8D36FF29ULL, 0x6C5EEB38EA060D60ULL, 0x3004082B2FD913A1ULL, 0x81F363593A2FE6D8ULL, 
            0x58A79A24F88B5C61ULL, 0x90E2F76EFD8A93AAULL, 0xF06378C31A76114CULL, 0x1335A50965ED28B4ULL, 
            0x3D8A5909D869A476ULL, 0x24DF3C20C743620AULL, 0x61319542E41BBD73ULL, 0xABBAEAAD8BA6246AULL, 
            0x6D4C857DC91358A1ULL, 0xA540660C2B654D0BULL, 0x313ED0600A5AFAD6ULL, 0x78D513C716D01437ULL, 
            0x86F8DD9BD9F061CFULL, 0x304E35A8CE636CC7ULL, 0xB19185AD70F3E94AULL, 0x3082DE9D3039AF69ULL, 
            0xD1D7BB5AEFB1B0E6ULL, 0x00A5A8A1B7C29E6CULL, 0x8668536E336E2BA9ULL, 0xB7A049FCEE4468D2ULL, 
            0xAA76120A87C8B9C9ULL, 0x30E27A5E5451E080ULL, 0x988591C6194FBFA4ULL, 0xBA214A865DE0FEA5ULL
        },
        {
            0x661F992F8036F3D8ULL, 0x779161B6CE571681ULL, 0x53151DB0F4AED862ULL, 0x78E444BC8C44BB84ULL, 
            0x998C890E1F85043FULL, 0xBE7A20ABC30A05FEULL, 0x1F945B23628A0219ULL, 0x95C71767060E4E78ULL, 
            0x98E8B5ECD4A251C0ULL, 0xD6B924EC5DDB13CBULL, 0x3A755F0A16F1506CULL, 0xBFD48ADCFDD7855BULL, 
            0xB8CA9222EF622794ULL, 0xA599FC013A09776DULL, 0x7F3375BA8AF8B8CCULL, 0x67833B3814354F61ULL, 
            0x079B1754873E6BE2ULL, 0xAC86DA1C673A4065ULL, 0x6F1BA20BC9E2F99EULL, 0xD6F5825B5E3DCF8DULL, 
            0x5469006BE5A0173EULL, 0x994B926E73CE61EFULL, 0x1C8F8800FBFFCE1CULL, 0x7C29A2661AEB18E2ULL, 
            0x6D40D267D88E49C4ULL, 0x6F6EA1437A269D5BULL, 0xFDBD56DD366CF231ULL, 0x61AAB65E3AABB70AULL, 
            0x825687AC8C376E03ULL, 0x14B1853FCA463724ULL, 0x93C594153127DAA5ULL, 0x1B5A17E7BEB7D078ULL
        }
    },
    {
        {
            0x63693C966BDD7A55ULL, 0x919B7E0FFCCA548EULL, 0x6A54E177B19E0406ULL, 0xF7140A46B0133FB6ULL, 
            0x876ADDD394F8B19DULL, 0x6F0FCB193EE4E72FULL, 0x1EFAA339E1B78576ULL, 0x0527DCDE5C9F9B0AULL, 
            0x4C23FA1A072BC033ULL, 0x42FF6949B271414FULL, 0x67F50699496CED45ULL, 0xF3BE92E02A87318CULL, 
            0x1D791B53AE8449BEULL, 0xE094FE3A1D3B0B73ULL, 0xDC64CEBAB9AC26ECULL, 0xC78DA352D593568DULL, 
            0x202F09BEE295D153ULL, 0x6DB1383795B67E8FULL, 0x9F3CFA2B0BFA234EULL, 0x427FD442EF3244E1ULL, 
            0xB3801BC30E7B7BECULL, 0x795A6B9D0A4AD0E0ULL, 0x03640298B50E23A8ULL, 0x601A685466001947ULL, 
            0xF6249609A4B0956DULL, 0xA204998A54C6C064ULL, 0x962E585DCCB961E2ULL, 0x97CA69718B61D487ULL, 
            0x286BDF4A0984B59BULL, 0xC479D7355DA66B59ULL, 0x3F434D0B8E4B360DULL, 0x3FC4322D047F4DF8ULL
        },
        {
            0x287567EBE32A3494ULL, 0xF9A89AEF2CF5DCB6ULL, 0x69A259F810B3F2D9ULL, 0x8600D43F42291429ULL, 
            0x385244EE5D1A2C85ULL, 0x221E4E1136795E17ULL, 0xF1237C2FBFC103F6ULL, 0x9E7713818EF6EE07ULL, 
            0x41A4B8551EA00D54ULL, 0xDFE80A869A1D7674ULL, 0x4F64B103D1BB4E3CULL, 0xCF34BE33D36AE039ULL, 
            0xFD53AF83CE0C61BBULL, 0xEFAB3B4C10C1D769ULL, 0x2854C27977775E8BULL, 0x6E0ECDFF66D80252ULL, 
            0x08570B365B570905ULL, 0x47EE04E9783C74ACULL, 0x553DDA242A5F676AULL, 0x6A113194F074A291ULL, 
            0xB9BFB644F57C68E2ULL, 0x7EE90536213B7733ULL, 0xB4779051C9C9FE57ULL, 0x5A219C9C871975EFULL, 
            0xE4B6DADB9093BA43ULL, 0x4427354586678837ULL, 0xF8442CB1343D5E80ULL, 0x5848F92F3C71CCE1ULL, 
            0x0B2892B2897695E7ULL, 0xDE15A25B1A38E76CULL, 0x9F1437602FDA0123ULL, 0x1AE32ACD98978FA1ULL
        },
        {
            0x07605654DDBF0167ULL, 0x4D6F5ECD1F5E9B89ULL, 0x103DCE9CBDCDF318ULL, 0x6FFC21DEBE5B6917ULL, 
            0x5524D326BA659A46ULL, 0x93563EA858E4245DULL, 0x53CA9EE23881305BULL, 0x3EC3AC6E3A2702DEULL, 
            0xDBDC53B7A17ADBA6ULL, 0x72F85AAD8603A236ULL, 0x2286CF7CF04C6694ULL, 0xFE760433ED9602F4ULL, 
            0x8CAA30DA7DEE9D37ULL, 0xD6B72DDB990024E1ULL, 0xE1037027662D1EF3ULL, 0x5E8CA099429448FCULL, 
            0xD86AE9234D45058AULL, 0x4766730D71E26468ULL, 0xEB4E0E6843D842A5ULL, 0x95812FB10DC29F83ULL, 
            0xFDF5F764B38042C8ULL, 0x0E8A306194A599BFULL, 0x97BD8589F70F3E7EULL, 0x7F6C69E91D4E6F79ULL, 
            0x0883E0F46AD8E2E9ULL, 0x377CACE189E4012CULL, 0xE5F09FB7FA7BEEB2ULL, 0x84AE25E0298F0F1AULL, 
            0xEA9C2FD600B14AFDULL, 0xE7B17C1F17EDA1D5ULL, 0x166AEC898465175FULL, 0x090280DDDD3C39F0ULL
        },
        {
            0xD56D605207EE4925ULL, 0xDEA7B59B4ACB87CAULL, 0xFA15749AECADAA53ULL, 0x5DE6F18F317CD856ULL, 
            0x016CD1D04C014927ULL, 0xC87E41E96B2A9B79ULL, 0xA578DDB580DB342AULL, 0x34F6DDAAAE3AC20DULL, 
            0x5DBCE6B84D0523F4ULL, 0x21D1516CC4897EF9ULL, 0xEC807AB2756183F0ULL, 0xA22A18EB46E8E943ULL, 
            0x24A3FC0ED812AED9ULL, 0x52889DF117C048E2ULL, 0x6011F7FFB123320AULL, 0x41083672FE6E5E31ULL, 
            0x44325D671FD9F181ULL, 0xCF8758A282D36CB8ULL, 0x6E5182786DF1A5EBULL, 0x406FB9C29CEA4CF2ULL, 
            0x806BB686F92324F3ULL, 0x6083963D17706AECULL, 0x4C60A3718538224FULL, 0x6AA4D06C8E15AE23ULL, 
            0x4D25F9161DA125A7ULL, 0x2767D0C75B6F8EE4ULL, 0x2964392709AAB997ULL, 0xDEC1CBA31E62497FULL, 
            0xD18612AB5D67FDDDULL, 0xEA87158CA2B26D34ULL, 0x133AE2B4FBA67841ULL, 0xA14506A77F64636EULL
        },
        {
            0x3C944AAE6F29EBD0ULL, 0x1674BDD7AEDBC129ULL, 0x60A0A8BB8C7A8791ULL, 0xCDE61EE6BC13549DULL, 
            0xD95788AEEF7FB10FULL, 0x3CF9587105D62AF3ULL, 0x503FFE503416C53AULL, 0x8BBBA243F60C13ADULL, 
            0x4B775F72E98B28BBULL, 0xE4F4FEABF37E8A55ULL, 0xBD4A639DED9A2CFDULL, 0x0CFAE70BB9B4982FULL, 
            0x5DC9D2D5E9EF0AD9ULL, 0x0609280B3E604C38ULL, 0xF53E8CA5B42ECBA6ULL, 0xF3C91CCB392ACA16ULL, 
            0x23EA120AA7509714ULL, 0xB36E7B67E8CCDCF4ULL, 0x25F21699E12E354AULL, 0xF0D62B12C10A29DFULL, 
            0xFA2AF1E3CB7A1F90ULL, 0xDBA3DC72BA2940CEULL, 0xE0B4E0152D1EA437ULL, 0xA59A298DA229E516ULL, 
            0x19641D6F001AEB60ULL, 0x593737C5A05AE5ECULL, 0xA2DAC049D5B6B660ULL, 0xF933CAA013087235ULL, 
            0x64FEB7D8744382F1ULL, 0x99699A820A09515FULL, 0x8683A9AA31627BA3ULL, 0xBF03B3C9751CC6F6ULL
        },
        {
            0xFE083D1B74E17F57ULL, 0x44D2880C152AD97EULL, 0xF4E54D4D75167942ULL, 0x4465D43BDBD2F349ULL, 
            0xC8BDE53DA002225EULL, 0x2DDCF14389B92876ULL, 0xA9F39B4E2A23ADB1ULL, 0x3975BF63F96973DBULL, 
            0xB320DEAC07E39A8CULL, 0x232B064ED6C47F34ULL, 0xE3FDFC99C1ECDA7BULL, 0x38A43E3AB672D455ULL, 
            0x326E0BDE9308A584ULL, 0x2A8AB15EA02451D2ULL, 0x2793287DE9E4046DULL, 0xF3A65A9E2573951DULL, 
            0x14CCF75D152EF3FBULL, 0xBB419FD6BC789FF7ULL, 0x52406B012C3DA94EULL, 0xAB8897BAE5F05F24ULL, 
            0xD71F937B74A1504BULL, 0xC0B7BB5FEAF4475DULL, 0x2BB31BB76D782F47ULL, 0xEE2A99180B456778ULL, 
            0xDDDDBC273C1FA9E6ULL, 0xC84C718136A169DEULL, 0xCEC4CFE1FDD44B3CULL, 0x7BF406A391903C9EULL, 
            0x419BCB631D6B8C13ULL, 0xD6790F7E81E60015ULL, 0x494E46EFE951D91DULL, 0x4A1FD82AD2670738ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Sirius::kPhaseDConstants = {
    0xEA2D421DA5316347ULL,
    0xD259E69CD22EB3AFULL,
    0x2057DC9B4B5A5C1AULL,
    0xEA2D421DA5316347ULL,
    0xD259E69CD22EB3AFULL,
    0x2057DC9B4B5A5C1AULL,
    0x70CFF5A34534B9CFULL,
    0xAFDAC997AADFD69AULL,
    0x62,
    0x64,
    0x05,
    0xCE,
    0x9F,
    0x20,
    0x5A,
    0xB9
};

const TwistDomainSaltSet TwistExpander_Sirius::kPhaseESalts = {
    {
        {
            0xC48A0BEA7A1E9228ULL, 0x19030C73FFD986F7ULL, 0x10E9EDC8D1817074ULL, 0x515A981C02B77838ULL, 
            0xD3059937029DF813ULL, 0x5B75CF77098530A2ULL, 0x597E3AF2EA63B861ULL, 0xB742EB7FAE9ED817ULL, 
            0x8A1E4934DA814444ULL, 0x4CB9B37E327BC057ULL, 0x1EAE2426D940D2FAULL, 0xD3212604487B7DAFULL, 
            0xD1E3F97AFFDD3B18ULL, 0x3E02B21E9E69B676ULL, 0xCBAD76324B9CA5CEULL, 0xA9C21A113C0A416EULL, 
            0x71FC72031E347907ULL, 0x21934F5381ABB697ULL, 0xBD614FECA50E0535ULL, 0x9D7058869ED2D6A4ULL, 
            0xFA8EB84BAECEE420ULL, 0x9AF8E359E553BC82ULL, 0x0E6AC8CB4CBEA4E9ULL, 0xF3118E30D32199A6ULL, 
            0x981009666A861EBDULL, 0xDF94AADE4FE85A2EULL, 0x7A4BBF1F31FBBC93ULL, 0xA22EE4DC8C6952C6ULL, 
            0x33E44069A3FB07D7ULL, 0x46B5E374D4B60362ULL, 0x54C28D279035832EULL, 0x1AD3E30348925A06ULL
        },
        {
            0x52F9B159B5B135F2ULL, 0xCB29A2A45DB3420AULL, 0x09F1498B0B9BF09BULL, 0x3792FB2E417F82E7ULL, 
            0x46C8D10DCB4A03EAULL, 0x46209D089BDC2156ULL, 0x7C4D0C85D44E98D3ULL, 0x5FFAF98389C222A0ULL, 
            0x780C166879F7FFDCULL, 0xAE4842160DD2EE21ULL, 0x6C7AABD5D7967579ULL, 0xD420AE2AFB615F0FULL, 
            0xD00C0799AE6988B9ULL, 0xD4644EC01F86B6D6ULL, 0x80E1115DEB22670AULL, 0x3E39BED74E60CDE2ULL, 
            0xF7462A9BE913BEB4ULL, 0x64DC73F0AB96C2A4ULL, 0x86263D2D19B347B4ULL, 0xCD6117DBAE974DBEULL, 
            0x322971B4436A2156ULL, 0x886BD0534E8A6FD7ULL, 0x683ADFA1DB8AB70AULL, 0xB468B5DAA819C392ULL, 
            0x83301C6E68BE1FD8ULL, 0xA20B3118EDBFD38CULL, 0x4CF82BFBEB023B12ULL, 0x7243A551B2F99079ULL, 
            0x771ABB6DE5393B3DULL, 0x9560832FF5F2CB91ULL, 0x580288833CC6DE3EULL, 0x16DA30E42A48F7EEULL
        },
        {
            0x9FBE5194687EF664ULL, 0x8534085A5416A037ULL, 0xC7347CCB5537B606ULL, 0x08B3E56524C8125BULL, 
            0xF8CBF79AA7A11E7DULL, 0x0865A6A83B8C7A71ULL, 0x80705814BE857000ULL, 0x3771B65D04C42D99ULL, 
            0x3FBB3F291ECD07CFULL, 0x8C4CB1E06D13466AULL, 0x5AC43D94AEE8CFF5ULL, 0x8E6EFDCD97F59F95ULL, 
            0xABA41ECE36A66932ULL, 0xA8E039C9278AC384ULL, 0x272EC9469D20A9A1ULL, 0x1192F03E01571691ULL, 
            0x4D059B652F241299ULL, 0xF23A824D47C8685BULL, 0x427A8C2CE1B1648BULL, 0x6D5023D241C35F06ULL, 
            0xAF8904AF0D4E3B0AULL, 0x6842918F2B2EC4F8ULL, 0xAE5E223C6D76F399ULL, 0x78D1C7C920E96C72ULL, 
            0x45F7A2815BA616F9ULL, 0x9697120D6EC83A05ULL, 0xC992A8E9BCB211CFULL, 0x6DD49896483B4A29ULL, 
            0xDE990AEB33A3D138ULL, 0xAD6368059601BDFAULL, 0x703DB8ABC782B215ULL, 0xF6283F7F18598F92ULL
        },
        {
            0x6082FAC4BD674B66ULL, 0x6A110BA98F275C8EULL, 0x284890ABFD94950BULL, 0x7E3638F40F332CBCULL, 
            0xEB1D10097C30EAF1ULL, 0xA9F885BF004B46D8ULL, 0xB24E890D6F2D6F6EULL, 0x0B88FB827637C73BULL, 
            0x31FDA37D55DB224FULL, 0xF227D0603090862AULL, 0x87BEDD7748FCF07DULL, 0x94B8E28FB441CF54ULL, 
            0xB21A292F0665DEBCULL, 0x27695F79CB864A7BULL, 0xA31BDFF2F2B109AFULL, 0x486FFA95C60966FAULL, 
            0x6A9E2A590DD82AA9ULL, 0x0265F111B47A1EB7ULL, 0x3EEABC2A68BE16BAULL, 0x7C91311C05F9E4ADULL, 
            0xF046A8D88AD070E0ULL, 0x7EC90E6174DE5BFCULL, 0x1B513F7D10F38458ULL, 0x4F1A91EA670B7058ULL, 
            0x5BC1F6CC2909C8E9ULL, 0x8DA60D80700D2A58ULL, 0x500BFC72926D77EEULL, 0x2AE390268357D193ULL, 
            0xC611DCACE33E6266ULL, 0x51107165EF2FC676ULL, 0x2F9A653B0D95CAA0ULL, 0x7D7F91DCA83B7C00ULL
        },
        {
            0x62686818D7BB0EAAULL, 0xDD58CABD289873EFULL, 0xC9D5CFC16737882DULL, 0xFBD9FE4B32A0B413ULL, 
            0xF24D08D92156D0CDULL, 0x164C4B3A63387E84ULL, 0x16576DB8DCA9C440ULL, 0x043E9D503426C7BBULL, 
            0xB55EA8A5F3B9AADCULL, 0x30ACECB346F2B615ULL, 0x89031ED961126241ULL, 0xEF211CBC10986961ULL, 
            0x252A783D88B00A34ULL, 0xE5952F6DDACFBDC0ULL, 0x059AC471EB8C0C88ULL, 0xFB49796D4BEA5024ULL, 
            0x4AE5F3F011256B4FULL, 0xFB9F119BB9C36F95ULL, 0x1D29D31F1C547948ULL, 0x0C7CEA7FD65ECBB7ULL, 
            0x11E7588176BB7FA1ULL, 0x0B2D3A211A350F0AULL, 0x6098AB56E22ED9EBULL, 0x77D2790AE8AFBB16ULL, 
            0xEAEAF1D2D3A53F44ULL, 0x9F42CF016208F15AULL, 0x4B4C8BEBB5D94162ULL, 0x2730023B688E9978ULL, 
            0xEE941D9C32CA29D1ULL, 0x39B9E05F5B2538E2ULL, 0xC52271839DE84691ULL, 0xC4B160F6EF21C370ULL
        },
        {
            0x6792157BC978DC3DULL, 0xACAE6C1FEA53E261ULL, 0x5C07C6FA4C86BF21ULL, 0xDBF44A00AC312DFBULL, 
            0x0B201D267C815BF1ULL, 0x99D1EF82185B859FULL, 0xF17B5A473A71E890ULL, 0xEE0A283024F742E8ULL, 
            0xA78AE0D30FFA1150ULL, 0xC0CA6BBB7BE3113CULL, 0x2955BB89ED3E67ACULL, 0xB4454BAEFD05BF38ULL, 
            0xD91C0FA45E00EE97ULL, 0xCC429B94B686DC01ULL, 0x12D0C2BC165A5500ULL, 0x6BDBE3E931CD4726ULL, 
            0xE4632D07E497170CULL, 0xC917060AB5CD00DFULL, 0x07A9CA11FE0D8457ULL, 0x173EE7B4D6E827C2ULL, 
            0xBDDCB40B6F99961CULL, 0xD58DA2F1E8124DE5ULL, 0xEBA4F30CECA8E752ULL, 0x9CBD13EF0BA40151ULL, 
            0xBB1F8DC44DFF0B45ULL, 0x56EBB52863BD81C6ULL, 0xAC16933D93B0A472ULL, 0x18DC3EA03EB6E6E3ULL, 
            0x4C23C67207C3418FULL, 0xBE864367EDF13CE3ULL, 0xDAA7561EE152D230ULL, 0xFC0E88411891C245ULL
        }
    },
    {
        {
            0x1E2EE4EF7C5759A4ULL, 0x73ACDAB2787B0767ULL, 0xFEB122415CFEDF8DULL, 0x5CC7DC829B20ABCEULL, 
            0xCCB15D96EF0AABDFULL, 0x4074FC28C7ACA8A9ULL, 0x54A120AB2D124699ULL, 0x8EFF86D849B7DEFEULL, 
            0xAE058E5870BD9096ULL, 0x6090D763CB3B9796ULL, 0xEBE23AD163DE9636ULL, 0x3BF46C908E36C774ULL, 
            0xDAF7472954CBCB37ULL, 0x7A546FF629056876ULL, 0xE558217F441E8DD4ULL, 0x1157714A033FEC04ULL, 
            0x78EA4D3A7001F738ULL, 0xB60CC84F4F9FCEF6ULL, 0x46AC21C13312D05AULL, 0x7330B2A843CB6011ULL, 
            0xE5CEACD8FDC22EE8ULL, 0x64548D4E6960E1F7ULL, 0xF2220DC2202C75C0ULL, 0xEE7C158C68AB99E3ULL, 
            0x33CF68934102A761ULL, 0x0E295F16263A5984ULL, 0x33C5934A5504CA2AULL, 0x425F8E067E4C7595ULL, 
            0x519B44A7E3C5CB3DULL, 0xA83ED469EC66F4AAULL, 0xAC819C9718AEA860ULL, 0x6A82A29D97C910CEULL
        },
        {
            0x11A493EE17351AABULL, 0x69E60D21FED5FFC7ULL, 0xB1959D88960D8EFCULL, 0x3C1FE49AABD555A7ULL, 
            0x4DB8777859F393B9ULL, 0x177B42B70977B4BAULL, 0x0EC9A9F0EDD7736DULL, 0xC1AD6197CE0DC161ULL, 
            0x11955F6E6E613A8DULL, 0x6B11124390C114EEULL, 0xA69397530AB26424ULL, 0xAE37F8E014D85EB1ULL, 
            0x67E0187FAA1EB9B8ULL, 0xC36CAF36501C2C5DULL, 0x0181B904EE9ADA59ULL, 0x2D6E2E3886D559F6ULL, 
            0xCCEF5606CE087D98ULL, 0xF1C7F60EEB88BE40ULL, 0xF121230D204EE7F7ULL, 0x8C7D637D1190906FULL, 
            0x5B685F0F384F0E6EULL, 0x80188D663CA32166ULL, 0xFE0A946F16DE5390ULL, 0x8D15EAAB6DC2FD45ULL, 
            0x066CEC3379963072ULL, 0x8CABAD4D3CCDBDEDULL, 0x5D87A4A814F42377ULL, 0x613ABCE365135C08ULL, 
            0xBB61C4937C287E05ULL, 0x155076BBE53D2C2EULL, 0x40839B1603336231ULL, 0x19199FB6F5F34D65ULL
        },
        {
            0x841830FD23A08FD1ULL, 0x0F77606289C4BED8ULL, 0x486CA86096A4122AULL, 0xB206A9434239BAACULL, 
            0xE0F5BE561FB1B656ULL, 0xC59BED0FC8A424D8ULL, 0xACD0736C17F7D69DULL, 0x642A3943F8218FEDULL, 
            0xF71B56AA3B9223B5ULL, 0x11BA7D199C38B9F0ULL, 0x0C091E5B20C290A2ULL, 0x8AD29212F64B4CFFULL, 
            0x6B3DC451EE778911ULL, 0x28D19B8CEE63D7D6ULL, 0x76299C4BDEAF648CULL, 0xF6B99F1BB5C2A95AULL, 
            0x79CB4B687AFDC3DFULL, 0xB09D0D1F305C8EC6ULL, 0xB3C79806852645DDULL, 0xCED8CC343857B6CAULL, 
            0xA31F2AA04957096CULL, 0xA2C7297D96D56B5FULL, 0x955C8682EE37389BULL, 0x08ED5FD1727AB927ULL, 
            0x5A179C9733201324ULL, 0x869E2CFFE9704FA3ULL, 0x5C624D3C64F76348ULL, 0x12567B616D5D2D2BULL, 
            0xE7CF49116FC68DEBULL, 0xD8B59862DBB663AEULL, 0x407445CB2FD28962ULL, 0x6E238E3D76BC35D4ULL
        },
        {
            0x19F63F2D8364D408ULL, 0x9652CC87A66FE084ULL, 0xA87D0D6AB2982A98ULL, 0x35A6DF51914AD3CAULL, 
            0x11D263B0B4B14846ULL, 0x286E6CE8163B5057ULL, 0x84934AF782112401ULL, 0x900D9B3CCDC03952ULL, 
            0xAFB473EC0AA3F01CULL, 0x4FC371EAACBBA939ULL, 0xD6907C990244662DULL, 0x4BE9A3EDAE2C3F47ULL, 
            0xD66776178C5DD914ULL, 0x1AD9D1104E1F5FC0ULL, 0xDE7CA02291FD6B08ULL, 0x4F03A6AD6BF08FB6ULL, 
            0x4864521C5812EAE8ULL, 0xC8A18D06D455E347ULL, 0xF6D9E8AAF0BB819BULL, 0xD57A1118F403FEAEULL, 
            0x1792A068B0271770ULL, 0x042E2D9825F1AE42ULL, 0xAB4C5D1D97084023ULL, 0x3D7F101876E0B0E2ULL, 
            0x978A967E5A364B08ULL, 0xC32153B4685F58D2ULL, 0x94C01FEF78D0B89AULL, 0x7AFA815EF8F2BD11ULL, 
            0x6BC89198F83EC528ULL, 0x0AEC57F3465C998FULL, 0xDDEBD403B658C8A5ULL, 0x78E95B31EC670088ULL
        },
        {
            0xA75C4BF00AAAE469ULL, 0xC7513C644E0F0B78ULL, 0x0942CF41A9D1E780ULL, 0x18C7CEE6DF265C19ULL, 
            0xA91587FAC1E6E3FBULL, 0x23EB3793FA013391ULL, 0x3F097653259AEA7AULL, 0xA70884AE7E4DB459ULL, 
            0x14DA3188BA4740A3ULL, 0xBDCBC0270D93556CULL, 0x3041602B30B7FB68ULL, 0xA56153B1DAADDFE7ULL, 
            0x0B9DF4DDF49E0702ULL, 0x81126D3C44F928AAULL, 0xE71B1EE8ACAF2B61ULL, 0x2494523E11E03B27ULL, 
            0x5812CE03887DC435ULL, 0xF84CCED2E5EC01C9ULL, 0x27408BFC811F14B0ULL, 0x1AE08973A03143E0ULL, 
            0x64A3C1935779F7BCULL, 0xF55A5F10083E8946ULL, 0x7C679D7B6E856A9BULL, 0x0E654680CB5B84D5ULL, 
            0xF2EF102F04A66879ULL, 0x5AD9885AA06FF40EULL, 0x27E9DDE14C2157DEULL, 0xF24B5924B57E9220ULL, 
            0x983FA463B6B3E379ULL, 0x45413DFC0EAA984BULL, 0x838464BA0BCEB585ULL, 0xD078A96A920C5F88ULL
        },
        {
            0x0C554922F1504C43ULL, 0xB08333E6A35EAE45ULL, 0x9403CF10DDF22B80ULL, 0xDD74C0656080A978ULL, 
            0x8DD4EF631403E5D9ULL, 0x0ED0532125A7D0E7ULL, 0x0B199BAEA252B588ULL, 0x4CA75D9F3B452FB6ULL, 
            0x77E95EE92741DEC9ULL, 0x5475021A73263368ULL, 0x37E87FA484333447ULL, 0xBF285A8776FDF7BAULL, 
            0x0A104DC7286CECB9ULL, 0xFA0E58D5F77F6DC8ULL, 0x48A8CA7C9B02E193ULL, 0x5A6F57A6F8D4C34CULL, 
            0x2595BD6C5946F88DULL, 0x6DA3D6825635D85CULL, 0x85C5BBFF70A055D5ULL, 0x4E03D94ED1739B49ULL, 
            0x8580B4A8D105BBFCULL, 0x572F284DBFC9A64AULL, 0xE41BE669D432BC61ULL, 0x477C7AE938ACA659ULL, 
            0xA054E8F726B955CEULL, 0x022508283CFF0736ULL, 0x6AC8CA4D96752C1EULL, 0xD8AE9E06654DB967ULL, 
            0xD6C80D4407A07F4AULL, 0x3E36C1781C177432ULL, 0x8F8E444C38337C1CULL, 0x1DD32E3B6DF7A4F7ULL
        }
    },
    {
        {
            0x4E29B6C2B8E811B9ULL, 0x718D554EB93F0281ULL, 0xC6C45CACBDE64DA4ULL, 0x74306BF6268DF400ULL, 
            0x605FA2B4EB15CB88ULL, 0x9569603700A2CF7CULL, 0x2BEAD023B6D69650ULL, 0x1BBEB3754DB4E8B1ULL, 
            0x3B7DDE050CB8A51FULL, 0xF508B5BE47992FF3ULL, 0x496B8D1CDE453478ULL, 0x913B946C2E4059A4ULL, 
            0x4FC4F1F351BB6EBDULL, 0x86562C91F464C856ULL, 0x712AEBF1F73E024FULL, 0xEC72DDA12C2BA3DEULL, 
            0x0E14358CF45CC47BULL, 0xD23B2A9884F83285ULL, 0xA0F17A11C0E0C939ULL, 0xF011CB292378A0E6ULL, 
            0xE62E013CAD5626B0ULL, 0xF51F33BB99DD84B0ULL, 0x9220CD4C66D82341ULL, 0xC20C4D0795DCD452ULL, 
            0x01AFCCAAF60AB0D1ULL, 0xD5CA02904D583246ULL, 0xE26E0A0678D966BBULL, 0x53DCFD46D91B3E60ULL, 
            0x51B4484747A02B11ULL, 0xA4739824CC7B62E2ULL, 0x5100FFC7EA43066BULL, 0x3F1393E66DC50216ULL
        },
        {
            0xDA3901996EB80C80ULL, 0xEDC60593041C9C47ULL, 0x35FC69F283EAA01DULL, 0x9E1560C2DF5FD854ULL, 
            0xDB927B1A9D09DD87ULL, 0xAAD6AD053EDB1F71ULL, 0xB12598C68DC51167ULL, 0x29FAA9D0BF3B1D45ULL, 
            0xB1C88BA0D1B83C57ULL, 0x282B5BFBF5209FD3ULL, 0xE6AF040DB889B94AULL, 0xB75A21FFD6302EDEULL, 
            0xE9AC0BC981D739BCULL, 0x52BBE70BAD91BDC4ULL, 0x8E71E097451328C5ULL, 0xE1DC40073ACCFF57ULL, 
            0x0F9FB2628590D1DAULL, 0x2BAD6913EF9C48C8ULL, 0xF15917172AE6A2C9ULL, 0xC5B5F0DB891E44BFULL, 
            0x4FC0F188C2D6617EULL, 0x4F861AAFA14A8368ULL, 0xCECB932EDE9D776FULL, 0xB84E4148583D474FULL, 
            0xB2EA2A525E8EF721ULL, 0x6169E507A5813CC2ULL, 0xE60BF65B0F1984DBULL, 0x028D267FC97A9B11ULL, 
            0x2EE928B50D079333ULL, 0x4F40B2B572EA1215ULL, 0xA80D25B26C11B698ULL, 0xF55894695BD158D4ULL
        },
        {
            0x284CFFAC31DBEEDDULL, 0x1F929E19A800BA05ULL, 0x91804578853D8991ULL, 0x13D92B1F0ECE91D8ULL, 
            0x6BFCF35437A87905ULL, 0x73B77AEA026BA725ULL, 0x32AE7304A68FE05AULL, 0x14CA85A5D0A94B3FULL, 
            0x5A7210490BA642CBULL, 0x5B9BE4963D61517FULL, 0xE87E252BF243E5C5ULL, 0xC554BBD2FB315F19ULL, 
            0x6959F90A7C2469F7ULL, 0x097916A4E3053708ULL, 0x58EF9FBEF6DF383CULL, 0x2B97E607FA691723ULL, 
            0x9F91E4772BC94F90ULL, 0x7E8E9DF6B3F4BC6EULL, 0xA6D95DE680E06F74ULL, 0x55441F5C6DDDA387ULL, 
            0x202BF8B82F38CE4DULL, 0x40346168BADB4E40ULL, 0xB492AC44F1D1972EULL, 0xDDECA209BD3DC3C4ULL, 
            0x6C1EDAA60B7807D5ULL, 0xC1E126B10AB7E0E0ULL, 0xF2BC71EC16E4C203ULL, 0x7F836AB3625D146FULL, 
            0x418D4969693BEE0AULL, 0x0AD00ECA1D229BC7ULL, 0xA2AD4277A12E5652ULL, 0xC86F87F1A5A7F543ULL
        },
        {
            0x14CD502D416BD05DULL, 0xE4439E9D7658B9B8ULL, 0x9DC2D055B925E0F6ULL, 0x65F2E37E81B09849ULL, 
            0x45D5E0FC094BA26BULL, 0x8DE133BF270F0138ULL, 0xC76729C35F4CDDB0ULL, 0x8595EF48F2AE760DULL, 
            0x91E130D0FD27003BULL, 0x5FA8C7FF12F0D67BULL, 0x8CBDDCB5339BEA84ULL, 0x83C48B155EE6D9D5ULL, 
            0x86D4E586BD58E167ULL, 0xFA14F233A60D890DULL, 0xE589D7F241FC13CCULL, 0x4B4DC44EC07437C6ULL, 
            0x2A4ECE8BE7157839ULL, 0x110736AD3D422B2CULL, 0x2ED3326B1A9F12B8ULL, 0x6ED13AD8E3088867ULL, 
            0x5B392D71FB6F13F2ULL, 0x77071E401E66C55BULL, 0x69162B7F5EA54003ULL, 0x048D5141C7FCE173ULL, 
            0xE77EDB965270C82BULL, 0xCC658543D5D1F14EULL, 0x92E17A38266DE430ULL, 0x58315A31B7EF0A2FULL, 
            0xA31DCC80EE457727ULL, 0x427F5FC993E74005ULL, 0x7DDFBAAA882979ADULL, 0x80CCEF8F17CA3615ULL
        },
        {
            0x4C2CB4E00F012820ULL, 0x34F8A6276085E324ULL, 0x16D235703F52EDACULL, 0xB98D84B455F1D279ULL, 
            0xF809F210B627E092ULL, 0x2C35DE7A473DE0FCULL, 0xF7CDBBB66D47E281ULL, 0x7FD3D1B5B22A8EBFULL, 
            0xEBC57AAE619FA0BBULL, 0x07031D85AE546407ULL, 0x4F53C39C00731949ULL, 0x1A12441A5746BE88ULL, 
            0x9FE890778D7F55ADULL, 0x0FBFFB6736DD2812ULL, 0x87A8CE3512C8B042ULL, 0x4A8FD02A7C3D1F87ULL, 
            0xD945DB82D766B98CULL, 0xFFDF740FFEFEC88FULL, 0x163676866A3DC389ULL, 0xC359ED3A00594FCBULL, 
            0x10625FDC6FE20064ULL, 0x04D53DFE17330E2BULL, 0x2EE2173F3F6CE4E1ULL, 0x706DE3386DF83880ULL, 
            0x2DAF802C87C086F4ULL, 0x292DA93ABCA0AC9CULL, 0x50126DE13EBCEC62ULL, 0x00689564878AFABBULL, 
            0x6E516962A089396FULL, 0xBC61362C7D82465BULL, 0x9B16A6A74DAAB6E1ULL, 0x56F36507B9D70720ULL
        },
        {
            0x930FBB36A38BB31AULL, 0xBB1ACACA3097F5AFULL, 0xBA56E42065D78B95ULL, 0xD2D07A6EEDA4D7F2ULL, 
            0x94EA3C306076D17AULL, 0xEAECFAD7155948A1ULL, 0x8DE3D243850EF517ULL, 0xEBFDF02D9D36233CULL, 
            0x86DE6EF4628A6437ULL, 0xC34A504F7DAFCF52ULL, 0x23B7EEE95EAA4813ULL, 0x95DC38F445239394ULL, 
            0xF45857CD1B6B3A8BULL, 0x9FF3EE660FAF117AULL, 0x5BB7B65865EEFAECULL, 0x4A44C4204554809DULL, 
            0x8DC78AF1BB26093FULL, 0xAA3607905361F18DULL, 0x09FD66E44F59D067ULL, 0xB4F4946C2DACA694ULL, 
            0x42630ADFFC3DFC1AULL, 0x9B9CF6751F5221C9ULL, 0x68732660BEC5B36BULL, 0x0EEAF82ED9356CEFULL, 
            0x177943C60799FE26ULL, 0xB4E10AA82748E7E0ULL, 0x52EB78EB72595FACULL, 0x603046B95EBF08EFULL, 
            0x46CA4D2743022B05ULL, 0x38482602DA4E4E7BULL, 0x7A8D5D84C5FF47E7ULL, 0x7DA30558E46BE61FULL
        }
    }
};

const TwistDomainConstants TwistExpander_Sirius::kPhaseEConstants = {
    0x1F6C60F35ACB0EF9ULL,
    0x4D5B262002D26D5EULL,
    0x86B8528F17950993ULL,
    0x1F6C60F35ACB0EF9ULL,
    0x4D5B262002D26D5EULL,
    0x86B8528F17950993ULL,
    0xC445182238D7F863ULL,
    0x5FA8B559E031780DULL,
    0x18,
    0xD8,
    0x7F,
    0x78,
    0x05,
    0x38,
    0x96,
    0x76
};

const TwistDomainSaltSet TwistExpander_Sirius::kPhaseFSalts = {
    {
        {
            0x93C1A64935B1F6B2ULL, 0x468736E7E7A949A6ULL, 0x36EED5BD8D98D58AULL, 0x6A073BAEDCA345C9ULL, 
            0x27A909DDD347773CULL, 0xE7F669AFF0208AD6ULL, 0x59D7711388B50EABULL, 0x0904D3A7A9BCDA26ULL, 
            0x42B51073229677E2ULL, 0xB0DA4702EEF1B735ULL, 0x62230D30B1A7055DULL, 0x4B9E56E2AB09EBCBULL, 
            0x52695A58F01DFC58ULL, 0x70389816EA2E69AEULL, 0x8E0F0D5791B50661ULL, 0xD700783A86F8AD03ULL, 
            0x01213009BF4950ACULL, 0x883F42DC07B82D2EULL, 0x32FAF050B3AF0D30ULL, 0x12FBDAD0DF00AACEULL, 
            0xFB29F37663E2F99CULL, 0x26238336C1662111ULL, 0x4D54DBAFA2AA4DA6ULL, 0xD3E4F0C18F39EE07ULL, 
            0x2E3CA70128D1AEEAULL, 0xE7E620A302707797ULL, 0xDD98BABF27B69B60ULL, 0x00F1E7EE3B26CD6BULL, 
            0x5EFEB88D3EFD7F17ULL, 0x8AC57B0B40E8733DULL, 0x6583471D47710D2FULL, 0x20509CE44A66C24BULL
        },
        {
            0xF0EA7BC3FA9081FFULL, 0x05C5ACCB8C2AA182ULL, 0x553C035904392C64ULL, 0x96AA101BAF6D56BAULL, 
            0x239A6110CBC03DF4ULL, 0xD1D531BB7F10A404ULL, 0xCE46B6AA9E9CAE66ULL, 0x9D1959D4BFA3ECC5ULL, 
            0xC5B5F6F4800C7E87ULL, 0x82231C8E85E2BB5EULL, 0x5E626F31C250E0B3ULL, 0x84AF7DB833582A2AULL, 
            0xFB09BCBFA050E134ULL, 0xD7789149B6D6C4FEULL, 0x17BE3094C64A6B56ULL, 0x20E99770B143658FULL, 
            0xBD515C0003557D32ULL, 0xFEE6A1244E1E5B84ULL, 0x353E683FC330249AULL, 0x2AF275B4812EA0A2ULL, 
            0x7B0061042483FA22ULL, 0x0E8B6D18B005B0D9ULL, 0x66B11DDA40558154ULL, 0xA9D995C0A62F931CULL, 
            0x71CDB228DAD7A8E6ULL, 0x370193057980AAA0ULL, 0x1A7C3346F9057748ULL, 0xA4B40944A990482FULL, 
            0x7BCB65799DFA75A0ULL, 0x0B5965D0B2BD7B76ULL, 0x8A577D0E3B9BEBF8ULL, 0xC89BEC53E2B99F4AULL
        },
        {
            0xDB14B3616BDF065AULL, 0xE7B2FF9637101CBDULL, 0xC5719FD4A4552B73ULL, 0xA3FC85ABC9B017FCULL, 
            0x42426F913BAC77D1ULL, 0xADB33243CBF9C5D4ULL, 0x02FF6F8EB4774695ULL, 0x9AB19AFFAAD77602ULL, 
            0xC85E5B8B1A3D384BULL, 0xEF7E7C692FCB2EE2ULL, 0xEA6F92B7F126C049ULL, 0x8C015A2325834919ULL, 
            0x3C77FA9A3D09D87FULL, 0x7F547C9DBAED6586ULL, 0x94BC6C58E9B1910FULL, 0xD69AF5D5FAA55929ULL, 
            0x30F11F7300B28FE4ULL, 0x2587794D8F32DF50ULL, 0x162D8814D9906B0AULL, 0xC4628A0EAE1CAEEFULL, 
            0xAEB53633D581D522ULL, 0xE1F7855C76AB901DULL, 0xB3284CF44E9849FAULL, 0x6A0221F143C0D41FULL, 
            0x1F3D3E05E4662D38ULL, 0x5FAB292BEE42D46CULL, 0xA794835024E806E9ULL, 0x45B4ED8F920C1A65ULL, 
            0x4FBB954938F72084ULL, 0xBC4AC801529C5D95ULL, 0xAA4F68BE8C114AECULL, 0xFF78365EE1FC1A99ULL
        },
        {
            0x8C43C72DDF64E435ULL, 0x095F36B06E31A37DULL, 0xB03369C529B78FA4ULL, 0x0A9C96ED3F704ACCULL, 
            0x2B534A899D8D2140ULL, 0x4481BB100C7FF7A9ULL, 0xACEF7F1A6E681CBFULL, 0x0100A0D31A631D97ULL, 
            0x81006C05155416C8ULL, 0x4E1CEDBDFBFEF0C5ULL, 0x392CDE70370D4823ULL, 0xC7F02B3DCFB9C92EULL, 
            0x17B118C784388614ULL, 0xAB0BA33C335DD9F4ULL, 0x99A9807237DA6AC1ULL, 0x1A98734663D83553ULL, 
            0x501AFEBBB56162EBULL, 0xA91B6B9C9877E570ULL, 0xF409FB7A3F377AD4ULL, 0xAA02C19B22D6589EULL, 
            0xDECC95B30F308B7BULL, 0xE92D927DE80CFEBDULL, 0x75D11D3CEED8E75DULL, 0xF47B7170AA1E11D3ULL, 
            0xFB7F039D468B8DEDULL, 0x52F3A62903186272ULL, 0xD14D23EB3699F87CULL, 0x8774B6235F8BE6CAULL, 
            0x9148DD59B7C2D2DFULL, 0x05C89841B1B64F93ULL, 0xC8AD144EC4685C38ULL, 0x31452FE4FB50A9BEULL
        },
        {
            0x1C4BE8A399BFD8EBULL, 0x3006B7AF0AB84B99ULL, 0x8D0E53DAF8FD2254ULL, 0x1B94C0FD02F00823ULL, 
            0xCA4F5B6ACB6A68D3ULL, 0x842220D4BFB3F509ULL, 0x8ECA043CEC6807A3ULL, 0xC2BADC408C972353ULL, 
            0x25936B65A64687DFULL, 0x71F35D98EA8E12D3ULL, 0x110C22760B482A5EULL, 0xA5AF64A58E38D16EULL, 
            0xC7C80B9DECC79514ULL, 0x4209BAF93935C2B7ULL, 0x6A1D70252D4049A2ULL, 0xFED2D6964147DEC4ULL, 
            0xAE4AF55B983AD715ULL, 0x56284BD3840F95E5ULL, 0x76A48FA07628AD40ULL, 0x232D4D4B12C3241AULL, 
            0x6AD857C126D74D4AULL, 0x48E1031956FC5694ULL, 0x31679B21FB237646ULL, 0x9FBEB699C0259132ULL, 
            0xD6D9C7C84A24068FULL, 0xFB9F46D819D863B3ULL, 0xC307B4AE38C19DF4ULL, 0x035E85AB9D9E7912ULL, 
            0x36B04F092031C64AULL, 0x8AA1B54A4775BC39ULL, 0x96AB7C098C9A881AULL, 0xB6D323CD9FBF742DULL
        },
        {
            0xA54F70295766C835ULL, 0xF2178BB55282885DULL, 0xBB4CB937F5459C59ULL, 0x2C142CA5B79E0EEDULL, 
            0x32548EA28EE39495ULL, 0x66905CBC2B75CB03ULL, 0x4F7DE169D6B0E916ULL, 0x83B2CF580EFC604AULL, 
            0xD72B54FAA73AD00DULL, 0xF2DB9DBA741AA353ULL, 0xF281443B01A1F5D5ULL, 0x5FD4BF63694E7696ULL, 
            0x762CC0418966969AULL, 0xA1234829DFDB7BF0ULL, 0xCA729D5BB4147D76ULL, 0x31AD476FC31E5042ULL, 
            0x7BAA2EE7FB6C9FE8ULL, 0xF5260B1AD3CB3F7BULL, 0x0DF94599B1C57DE8ULL, 0x68FD75D61BE96B75ULL, 
            0x1777E476A9630788ULL, 0xD54D7AE03ED2A9BFULL, 0xF1FB0912C73D05F5ULL, 0xCF4CC1D0D4A5DE32ULL, 
            0xC7C3984A7FE5C9CCULL, 0xC75274A020DD2478ULL, 0x096900B7BA830829ULL, 0x63D2E7995A2E5322ULL, 
            0x3F210D8374B86FB9ULL, 0xC5D4871EF365268BULL, 0x454323DE796CE277ULL, 0x091C136D9D5D7007ULL
        }
    },
    {
        {
            0x91FE0B09EB200FD4ULL, 0x23AF7A356F65C166ULL, 0x78B39F27B2368129ULL, 0xEEA40E9E4CEA163CULL, 
            0x871949330C762A4AULL, 0x574DB5A0EC5FE72CULL, 0x22146E9DB17E12AFULL, 0x93A0D04095A79C19ULL, 
            0xF19F401ABA475772ULL, 0xAD4FCD2FB4BC4B90ULL, 0x2A5DA5C6EABD86BBULL, 0x297949ADC8FC90B4ULL, 
            0xB267052B8EBFD0C6ULL, 0xB398FA1C3D2B7A51ULL, 0xD5F13AA5FAD78919ULL, 0xE0C0B186D9C8765BULL, 
            0x32A6EFA94E5EB3EBULL, 0xEAD5C1BF4750CEF4ULL, 0x5B3705A6CFE4575CULL, 0xF2004468614CD23AULL, 
            0xB3FDFBFA78CD3807ULL, 0xCBDC57A6FBB44203ULL, 0x200B11F9CB0F2B62ULL, 0x975ABD9AEE14759AULL, 
            0xD5B0CB2AA118864FULL, 0x1C0C6234E4C1EE85ULL, 0x95E191028434C764ULL, 0x856B43BA208FD940ULL, 
            0x564E707F899038EAULL, 0xCEA2D5BE8023E5D4ULL, 0xC08D43D1EFBE8EB2ULL, 0xF55EF1D9EA0534A3ULL
        },
        {
            0xEC5170670586B89BULL, 0x434A3B4A0DD4F7B3ULL, 0x274C079086E6EF7DULL, 0xAF71FD56B1E41AB8ULL, 
            0x70B73948A04EF273ULL, 0x1BCCBE0D116ADF73ULL, 0x0BE4662897F38A95ULL, 0xA58468796D561A71ULL, 
            0xBDDD3C15977742FAULL, 0xB201595A5129A007ULL, 0xB6FBB0255EDAAE60ULL, 0x8B463C9EC345033BULL, 
            0x917F47D12E379B56ULL, 0x17869DA9CF047F74ULL, 0x79BBA44BEB009AB1ULL, 0x79C47D7C071F4E26ULL, 
            0x45D3BE8E609794DAULL, 0x07E6D1E3A4B4A831ULL, 0xD5A61E684B5C1064ULL, 0x885B9101664DE395ULL, 
            0x302E6E3C60983867ULL, 0x1BD12063DCD41D5FULL, 0x84F57492C7EA8290ULL, 0x2FCBFBA733326EF0ULL, 
            0x0DA9DF449FD9C3EAULL, 0x7CD66DB4DC51BBA0ULL, 0xD18804D9AE933F58ULL, 0x8A28907BF078493DULL, 
            0xABE9D8F33D57CF95ULL, 0x664BDE28882203A4ULL, 0xF2B9092C6FC21D79ULL, 0xFF4D7F9DD8D812E5ULL
        },
        {
            0x94906C0F15D43C51ULL, 0x8E04A4DBBD5A37D0ULL, 0x192D73F35F22A8FFULL, 0x948202C175345D76ULL, 
            0x56765673F80626FAULL, 0xD8A685056CBF7DEBULL, 0x41308AD490BEB841ULL, 0x4FA80BBD5B503AA0ULL, 
            0xD423BA77E73FFBCBULL, 0xFC416678F63072C0ULL, 0x758BEDD23E7EC292ULL, 0x9D163827189B9EBBULL, 
            0xF9DA2FA73B04F653ULL, 0xF90E3D12A5030515ULL, 0xEB3B7085B2CE187FULL, 0x88183285C5BCC197ULL, 
            0x55875D14D60C5174ULL, 0x9FDFE46630F5FF11ULL, 0x45550DB4BA2A3B30ULL, 0x4F8474BAF91F63D7ULL, 
            0xE76AC615AB2ECD6FULL, 0x7E5DE64A044C3C60ULL, 0x61475E58AE039238ULL, 0x41A17608A16F3B07ULL, 
            0x8745B0ABB352D6B9ULL, 0x3819FC1FD8B509CEULL, 0x11D167A312D1A2B6ULL, 0xDFF019931A227759ULL, 
            0xAD1B345F72EB9A6DULL, 0x33C4F17B12FD7652ULL, 0x1E087BC96FCB8616ULL, 0x6E617E45E076EC32ULL
        },
        {
            0xC01ADDFCD0F83477ULL, 0xE050B91EB66C7E0CULL, 0xC386C09A1FA15DDFULL, 0xBC3B45E84BAAB552ULL, 
            0x51EC5636F45BFB32ULL, 0xC2D28AA5F919E8D7ULL, 0xFD69ACA421DE03BCULL, 0x3B3F42BB3797F609ULL, 
            0x42B9D57591487A8FULL, 0x69E08C89C95E410BULL, 0x9E0763FAA7EBE694ULL, 0xD9FD23E3F79B24DBULL, 
            0x17700B5E314D7475ULL, 0x1481B4E001798BD7ULL, 0xC679CC4353724504ULL, 0x40FA117AB08E2D60ULL, 
            0xEB5E52FCB23D882BULL, 0x7C3BB61051070A27ULL, 0x785098CBBEB78D15ULL, 0x182B1937D5E413A9ULL, 
            0xF438DD38FA960F70ULL, 0x289F205B3B4C0CB8ULL, 0xCC5E1150A5158EC9ULL, 0xE252C45A399CCB27ULL, 
            0xC8C313EF0DC8FD06ULL, 0x2F8EEA74CB7A96F0ULL, 0xD0D888E58D91A7B3ULL, 0x3005972F8E14119DULL, 
            0xDCE1E9737948E73FULL, 0x3C8B63B8840CE874ULL, 0xE2FF865203482B7BULL, 0x9BB1BCB2F2726D63ULL
        },
        {
            0xAF51A1EBF5A19048ULL, 0x54B559261703AF9FULL, 0xCDEEE2459783FBF2ULL, 0x2D8C484A70CC822EULL, 
            0xF3BED88A16B2B026ULL, 0x4E5B95AD9D03555EULL, 0x0657AD0544103DD5ULL, 0xBB91A3E6E863466AULL, 
            0x32F6AAC59752A757ULL, 0xCC386E2F699F5DD0ULL, 0x8F4CFD53EE0AB70EULL, 0x6C1DC7B52AF2078FULL, 
            0xCC42195A5D979E4DULL, 0x40F35AB369A26758ULL, 0xC22C6E7EE73848ABULL, 0x27AAE6E5AAFEF58DULL, 
            0xB3F8B4FCE7794138ULL, 0x8FAE8ADF7801F891ULL, 0x3DC448A64E5FAEAFULL, 0xDCEF76EF014B6DC6ULL, 
            0x753496EF6D06A483ULL, 0x055CD44AD683FB5CULL, 0xF3C7223C37102FB9ULL, 0x43F790C56701F058ULL, 
            0xA57BAA03EFCA9543ULL, 0x0D38B839F2D7C1E4ULL, 0x06F8BE9A2EAD7112ULL, 0x0C97CA1907AB7A88ULL, 
            0xDDB6DE6C7A83E9D5ULL, 0x0CB46BD9887FA41AULL, 0x156BF5898942CBDBULL, 0x6A7A2DA73DAB1519ULL
        },
        {
            0xD271D982857434C4ULL, 0xDA49F1C9E577A98DULL, 0xAE8129EA17798A29ULL, 0xA5E5BAB77A1BA87FULL, 
            0x8E13234699CA27C7ULL, 0xDBBF12E2F4C64B69ULL, 0xD21BDE8816684A11ULL, 0xAFFCF98F3FF1F76EULL, 
            0x0694AA0BF1783EA9ULL, 0xDEF1240C9E1FF383ULL, 0x67F9AE05EB433F16ULL, 0x1FF232BE0CE2BC17ULL, 
            0x7598F3FD288FC5E4ULL, 0x27C692C1F375D2AAULL, 0x77C587617EB5BF2DULL, 0x751B1A4531C0D711ULL, 
            0x9F03A8BFAD5CD980ULL, 0xAB00A6EC13025E20ULL, 0xAC5AF6B0941BF902ULL, 0x8F1207F372C1F5ABULL, 
            0x815A42FEE25ACD9DULL, 0x4AD0E77A68844DF1ULL, 0x6FD39D1D67E3BBFAULL, 0x35303966FB750A78ULL, 
            0xF97B101E12930277ULL, 0xA60AA126C07A8653ULL, 0x6581E5C862B0C1E0ULL, 0x4623099310CAE84DULL, 
            0xB07DEE1431AB33CBULL, 0x742FB48E68A914C7ULL, 0xD5981E806A192756ULL, 0xE4CBC667DBE8E5D2ULL
        }
    },
    {
        {
            0x069BA24D8230A023ULL, 0xFE29A16A4B70A046ULL, 0x5C3EA5D887277BADULL, 0x4C7B3D9B885DCEE4ULL, 
            0xC766562F7FD9A991ULL, 0xBC5BE494D247234AULL, 0x074BE27F4C3D3CB2ULL, 0x886A3941113DADA5ULL, 
            0x6DF893439D26ADD6ULL, 0xA63C945F11D5C051ULL, 0x028A0A83C391BD70ULL, 0x673941DE91440FCDULL, 
            0xBF4CB058E8504179ULL, 0x1EC71794C532BB4AULL, 0xCA61FCF43B65A612ULL, 0x69074EEB23179ED1ULL, 
            0x9030E21398F1188AULL, 0x5F1BA040849ECD89ULL, 0xD6708471FB87662CULL, 0x6B0F1B941F988DA9ULL, 
            0xAC25449837C7FE9EULL, 0xC2C20754B1E12CD3ULL, 0x2B5E5FAC40A8E95FULL, 0x9883C0D8DBCFA68EULL, 
            0x0D282C0B1BBC988EULL, 0x800C8FCC6E109600ULL, 0xC3322E23B25977C3ULL, 0x63B400E9D727E8D3ULL, 
            0xB8F54602387AE7E1ULL, 0x541F0DD86900B087ULL, 0x45E5A35B9CB405D6ULL, 0xD6E491F4467D17D6ULL
        },
        {
            0x8AD3C72557C3B637ULL, 0x791CB23F92ABDAF2ULL, 0x4BE40224B29ADB97ULL, 0x096ED219671F7396ULL, 
            0x075B84D2DF06887BULL, 0x1D66B5961438A881ULL, 0x617FE91BBB97CAD1ULL, 0x55EBE30E372ACF98ULL, 
            0xF4986DF7701E104BULL, 0x0B8895C98D20B6B9ULL, 0x0692EC1AADB0A4DFULL, 0x0D8BEBACB2943AF1ULL, 
            0x9C5119C7AB7CB02FULL, 0x4A77D1F247B13845ULL, 0x6AFD109010697AABULL, 0xEA0FE0611D258787ULL, 
            0x3969C253EC7B6922ULL, 0xB5AD8F687A6C81C4ULL, 0x627512D944409B44ULL, 0xC442AD663E89FFCBULL, 
            0xFEDB4339FF52887BULL, 0xFCB1142904FC9FF1ULL, 0x821B42A2D18A0721ULL, 0xA030898B34973CDFULL, 
            0x182364291A0A64B9ULL, 0xBFF1405298FC5158ULL, 0x5F59D1E80AE89B03ULL, 0xABC47709D335264CULL, 
            0x157EDB5BB29F26CDULL, 0x35043D2E19B113D8ULL, 0x3D8B81439EFB9E44ULL, 0x6A30797D9D180A0DULL
        },
        {
            0xB95E18E6DF7F92AEULL, 0x981B909169EBFA38ULL, 0xD78150B55271073BULL, 0xF6AD9BFA6E26E258ULL, 
            0x896308FE3CD58D5DULL, 0x03F23607D87E1610ULL, 0x7FA6DD3BA472B215ULL, 0x1C76681F35F18806ULL, 
            0xD06C42B1A02BD5C6ULL, 0x3D8B9452C967F1AEULL, 0xC60CCE900015F9C6ULL, 0x5F65063F13A4AA6AULL, 
            0x23D9F75A6CCC6CD0ULL, 0x4B5881302104FB18ULL, 0x2F89BA2667D4E4BDULL, 0x58C2D1A7E3AFDA76ULL, 
            0x73F8250312B24F5EULL, 0x080426B326184C97ULL, 0xB16F2A9FA4D27BCDULL, 0x6542E47F06D21388ULL, 
            0x8284250DA366A025ULL, 0x457535702E7A96A5ULL, 0xC553DD04AB2E31DBULL, 0xD5B8B8B1CDBB2950ULL, 
            0x04B3532C37702C27ULL, 0x0579A547BC8F7A15ULL, 0x257135A0AD80C4F4ULL, 0xA6F34866AD699CE4ULL, 
            0xCDF582CAB719AF97ULL, 0xF975C6C29FF96A64ULL, 0x5E92662B91F320FEULL, 0x0E06BEFBACBF8E28ULL
        },
        {
            0x80F3BC6A43612EE3ULL, 0xA0447DE14752728AULL, 0x6C1B0262D9D1CCF7ULL, 0x8E5C408E0ACC1739ULL, 
            0xBDE5F791CA3528E2ULL, 0xE95E1E9EA3E6277FULL, 0x68E98D7E386D966BULL, 0x6D84A82D3162FF04ULL, 
            0xC73353548B2165C0ULL, 0x6C13BB19076EE469ULL, 0xC0C97FF22FFEA143ULL, 0xCFBC4513CF751B72ULL, 
            0x707D1B112CE9397CULL, 0x820725650DA54DBEULL, 0xF3697785162AA453ULL, 0x8439C750975E135FULL, 
            0xE22B1DE8E6F12224ULL, 0x47D5DA8B08469883ULL, 0x3DC26E6275DE3F1DULL, 0x60B143EB6D0E183AULL, 
            0x62A4FD773EDF8AFDULL, 0xCBC3C233E1584099ULL, 0x2E7EF22CB01118BFULL, 0x105FCC68EB8B5DF4ULL, 
            0x475ADFD615EE1CF7ULL, 0xCB2470FDC36E7D21ULL, 0x535B4A3B243AC0B2ULL, 0x5A0FABAF0F647F28ULL, 
            0x36698DF1C1F523E3ULL, 0xD0620535E5A6274DULL, 0x669A2F3FD69C2127ULL, 0x7D0F216BB1D6723FULL
        },
        {
            0x7ED236E6BAA02C5AULL, 0x80732321B874433BULL, 0x068D68ECF57F46F3ULL, 0x11FB40F007819C83ULL, 
            0x642A56D9C90DD502ULL, 0x344D76B8BA50C050ULL, 0x42D65A53F67C165BULL, 0x44791D21A710B9FEULL, 
            0x009F3D11B255CC4AULL, 0x148E2256EF71E347ULL, 0xCA444972EE10DC93ULL, 0x8FB21AC87A066AEAULL, 
            0x5F2F32EFABF3E9CAULL, 0x93BBB99F1FA91A15ULL, 0x6A5068E55C64C893ULL, 0xEA09CB80BFEC6FA8ULL, 
            0x02DDB257A6F5CA4DULL, 0x1D83183E74A70FD4ULL, 0x163827C16A5AC033ULL, 0xB716C7423C325D26ULL, 
            0xF274F47E4D3CACFBULL, 0x95AAB79F8E879905ULL, 0x0513883BC8F2CD47ULL, 0xCB624B7DA8F7C3D0ULL, 
            0x58DC3FEB91D37A89ULL, 0xCB2B38282F6F94BAULL, 0xA9B850F181A4562EULL, 0x7E758D18D76FDAE6ULL, 
            0x5CD07BB518CB6DB9ULL, 0xB12F7AC33517B24DULL, 0x0D21250679266E90ULL, 0x7479AE2B2871DF10ULL
        },
        {
            0x9B8436B4A2AB40A6ULL, 0x6C234B6BA4F22856ULL, 0x5B617B4C39DFA8A2ULL, 0x75A2F4ED89AA9016ULL, 
            0x5A4479D379B05878ULL, 0xBBFF9B8D4F8995E1ULL, 0x9F97461363FA9FE8ULL, 0x2D73AF05C1BE94AEULL, 
            0x64749B7F481A6CA0ULL, 0x0EA220AED165F2F3ULL, 0x50A3634E532D2E52ULL, 0x101FA96E3CE7F780ULL, 
            0x39566C592082BEFDULL, 0x8F82428A991C68AEULL, 0xFF6D9DA77F99628CULL, 0x26014DAF3BC855F5ULL, 
            0x5824265A6890D52AULL, 0x3685FF8088086664ULL, 0x19FBDB4517F1D929ULL, 0xA301CD943FA8F3D6ULL, 
            0x564A4AF05A4D747DULL, 0xC005E676F438C78BULL, 0x0CFD3416E9713422ULL, 0xB881EAD82558361BULL, 
            0x7C7DEA2CE0E61A9BULL, 0x662EA779FACA6C9EULL, 0x15F0F404C7D3C644ULL, 0xB3BFCBBC570A25E7ULL, 
            0x6285C8BB744127ABULL, 0x117C001F134EF3B2ULL, 0x49DCCC9586EDF0ADULL, 0xB99B78C9FE3FE730ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Sirius::kPhaseFConstants = {
    0x76C4859BF87CA761ULL,
    0xE4CEDEA21D1D5FB6ULL,
    0xA367A7B54FC1773AULL,
    0x76C4859BF87CA761ULL,
    0xE4CEDEA21D1D5FB6ULL,
    0xA367A7B54FC1773AULL,
    0x8DE2DC3A1CEE2A94ULL,
    0x0CB01DD4529A2812ULL,
    0x47,
    0xED,
    0x31,
    0x32,
    0xF3,
    0x62,
    0x58,
    0x81
};

const TwistDomainSaltSet TwistExpander_Sirius::kPhaseGSalts = {
    {
        {
            0x389A35586C9C66D1ULL, 0x58793FA027779D48ULL, 0xF7599734F5C8E405ULL, 0x423F4A56D9A3E08BULL, 
            0x1F24E2CD660CE516ULL, 0x0986865A895D4465ULL, 0x4652B7167E2D4121ULL, 0xF8232D833A213DE4ULL, 
            0x65876FE5B2C3E90DULL, 0x5807ED4083E13382ULL, 0x45B8A338D4A5DE03ULL, 0xB4E06318218D18FDULL, 
            0x2A1916BB5FD62C3FULL, 0x4362125CF48F70D6ULL, 0x7055B1CC145F62BBULL, 0x9B465A8E2EC1A7D1ULL, 
            0xA8C5BE77EC9CD2E7ULL, 0x8D3352B900279B12ULL, 0xD54DA3CC7CDBA6C8ULL, 0x104BBCAC33E89C7BULL, 
            0xEB2C236710E6A396ULL, 0x64F3DA75E52B28AEULL, 0xE228777EA9E09585ULL, 0x75C2A7E4C0CA4AB9ULL, 
            0x15FB03716A817B1AULL, 0x7AEBFC64D58799D2ULL, 0xF34EBAFFF92747D3ULL, 0xF71DBEF24EE9CBAAULL, 
            0xE88A2A06A17AABD3ULL, 0xAAC07CC5BACB8A0DULL, 0x4E6AB2D5E0F24A03ULL, 0x7EB08F9938016F33ULL
        },
        {
            0xEE9CE3B9BC90D4A6ULL, 0x8A12FC09E1634C04ULL, 0xB2551728E4C7E9E9ULL, 0xB9D8DBCED271EDFEULL, 
            0xDFBD720F4200C6E5ULL, 0xEFA3697950667490ULL, 0x2B39E3B3465EDCAAULL, 0xC86986C2E95B57A9ULL, 
            0x26CCAAC06EE1DE3FULL, 0xCCACB152AF6BDD56ULL, 0xF3B20ABC2840D967ULL, 0x29ECBF706E879F1CULL, 
            0x5143CF78A7844875ULL, 0xEE1B8E2AD62C02E7ULL, 0x9DFF95DE51C90874ULL, 0x8BCE1C1B66A49B37ULL, 
            0x34B679EECEC363F8ULL, 0x067F417B34A61BE5ULL, 0xB71A56A92BE329F4ULL, 0x61C74BB83BE031A8ULL, 
            0x451E9510AA76580FULL, 0xE8316E0BFDD04678ULL, 0x7B7F03EB3EDED902ULL, 0x7765C93B25EA17ECULL, 
            0xDEA72105E882A575ULL, 0x0890D850F6D76953ULL, 0x2857D0D9156455E9ULL, 0x4AB105903E640E9EULL, 
            0x8FE7024C17F803C1ULL, 0x8E53CB56E1D189B9ULL, 0x647C84BA13754138ULL, 0x6A098E7ADEE0CB7FULL
        },
        {
            0x8DCEC83E0AFB9611ULL, 0x8873CD9866B4E398ULL, 0xA76D5A4089958C94ULL, 0x2CA2A6ADC5C2CD49ULL, 
            0x7C024E96C883188EULL, 0x04CE6FB7ECB58A22ULL, 0x7690E5108C14084CULL, 0x0D7AEB95F2815CA6ULL, 
            0xF7A3736C6E23B8C5ULL, 0x3AE702240155C05CULL, 0x598A49D957607C6CULL, 0x8BC95E98B6919C52ULL, 
            0x847D0B32E2A164B7ULL, 0x902552BA799A2D6AULL, 0x18E3D2309D8ACD57ULL, 0xC207DF39F84B3765ULL, 
            0x396868F18A8E8EC4ULL, 0x428C695A9E2282EEULL, 0x425701FD8C8BF9C3ULL, 0x33F137BBA69528F3ULL, 
            0x9E1BD9D5D2009F96ULL, 0xBA20364C85E43194ULL, 0xF5D1F34C357FC13DULL, 0x2BF1F03202CC9FFDULL, 
            0x337A03238A093862ULL, 0x5896DF4BCE9950B7ULL, 0x9E8F2EC5A16D7C4AULL, 0x00B437E6CD0FED24ULL, 
            0x7940A01D6FFE0EA1ULL, 0xE243B23EF6646BA3ULL, 0x10C3A9DF6BF00AD7ULL, 0x61BCC638CDD8C7BCULL
        },
        {
            0x5474960532451F5BULL, 0xF2E6A9C4E53B62D8ULL, 0xAFE61FFA0A6B2580ULL, 0xB07816414615BC7CULL, 
            0x518F643624523593ULL, 0x7E0032F869519613ULL, 0x04621C34D392B768ULL, 0x94AAB64A373600C4ULL, 
            0x2EBFA5DBD8EC9155ULL, 0x2C01D15989A804A6ULL, 0x0DD5BBA78D318A44ULL, 0x2A605B79CC74D405ULL, 
            0xA12C6DC35DCCD7B8ULL, 0xF959379975BF6653ULL, 0x15885D4B4CAC81BDULL, 0x39FC03BA2EFA5EA6ULL, 
            0x39CB455B4C353B63ULL, 0x8B2AB824D8049DDFULL, 0x0F4CB25BB06C1E59ULL, 0x0F141CD542B75978ULL, 
            0x7800A99088DB1F1EULL, 0x424603AD45F30EFDULL, 0x24451E4B51620904ULL, 0xDF2DA109B604B609ULL, 
            0xBE63ED8E61FA95D6ULL, 0x4B2017F238F77974ULL, 0x2FB5EAA2B350C749ULL, 0xD773EDF6B0BFB4EDULL, 
            0x9CCC74D6AD392EECULL, 0xD39F7E3BF3826A4EULL, 0xD7AD8E0C82C7DE05ULL, 0x3E63E7CFC49AFE47ULL
        },
        {
            0xCB3565590ADD0490ULL, 0x8CE02B2250D83EBCULL, 0x3146A3B50CB4EB29ULL, 0x823BBCC607A211BCULL, 
            0xF1245A0F9CEE3D6EULL, 0xEF3003DEECAF2907ULL, 0x02CF1D89501F4197ULL, 0xC8F3C0662E64C4F7ULL, 
            0xEE145CE938E48A05ULL, 0x94CE75657F66DD44ULL, 0x2B970B8B894A53DAULL, 0xCED7B7915964D857ULL, 
            0x2CD60963D0C454D9ULL, 0x8FE470779089A50CULL, 0x8917BB147352E969ULL, 0x9E1013CDA171C834ULL, 
            0x10B2EA80E0991587ULL, 0x77DE15B28A693873ULL, 0xF4F3A20D1F2F73AEULL, 0x0FBD2F43A7B90B14ULL, 
            0xF19A594C6E0F7882ULL, 0xF906A1B0E926FE47ULL, 0x1B1F1043ECDA2DF1ULL, 0x30592DD4A26DA4E7ULL, 
            0xB35DF6D7C59EB5E0ULL, 0xF6EDE804D565A6EAULL, 0x49C6B36589F75F1EULL, 0x8289AF553027EF3FULL, 
            0xC8F86DC342DB4C04ULL, 0xA99398821C47FD76ULL, 0x10F688B131888298ULL, 0x5429E4CDEF6E5A75ULL
        },
        {
            0x6E1C14C13DC6D8D4ULL, 0x9E35A02CC510B162ULL, 0x254DE13BEE13659AULL, 0x5197BDE51F9ED986ULL, 
            0xA7403266343D3202ULL, 0x1D6024B658A3AEACULL, 0x588E528A11F22E64ULL, 0x62DC8FF2B1221B09ULL, 
            0xF9A0E00051BF97C5ULL, 0xEDE77902B7CD63E6ULL, 0xC740F5011A608BE5ULL, 0x5A63AE0C54EDD137ULL, 
            0x94E27C522093658BULL, 0xD410F227866B107FULL, 0xC08A6276181626EDULL, 0x07CD4CEFBA4E31F5ULL, 
            0x52BE211D76C0D00DULL, 0x30B432706BBCF2C7ULL, 0x97CAAD4C38A242EDULL, 0xB84EC680A207F5B0ULL, 
            0xB2302B0543FC72ECULL, 0x9EBA0B80F6A41F24ULL, 0x38139DEDB5DD3AD1ULL, 0xB03262E0DECDDC59ULL, 
            0x07CE43FE1E7CE08EULL, 0xBD2F04F97B248DBCULL, 0xEFDFADE9ECDCDE3EULL, 0xB99A1A464E9B7167ULL, 
            0xA296C6408F067F24ULL, 0xA1036392E3CA20FAULL, 0x6C55649337773754ULL, 0xC08D94CBBE688C16ULL
        }
    },
    {
        {
            0x4CD58E9255CEA58AULL, 0xB8F9A4BA786C5B32ULL, 0x1068B0F05EA0D4DFULL, 0x1AA7865C05CB5906ULL, 
            0x00ACCEFDC6841005ULL, 0x68F87174BD96DDFFULL, 0xCBBD48D476146E8CULL, 0xC9C4B27210B9FFE0ULL, 
            0xD3D1D08A6F1CBD52ULL, 0x4ACCC7530359240AULL, 0x1D574AEA3604E4FCULL, 0x590A502D6F0CE356ULL, 
            0x2043307C738B322FULL, 0x1B51D7F0FFF6B337ULL, 0x4189F770B12CBFA7ULL, 0x23CC6491712EC0DDULL, 
            0x10D63DA0AA78CE9BULL, 0x522CF1FEB37CB6FDULL, 0xBC7852EDE5FB8716ULL, 0x7E49B0894DACB563ULL, 
            0xDBC15AB4114AB543ULL, 0x1BFB7E4B7652B868ULL, 0x16E3DC7D2E3A1381ULL, 0xC4BEFC6BC6709EAFULL, 
            0xC060A280B54F5699ULL, 0x406607D637DDFFE2ULL, 0x2A0007A4A98BDD55ULL, 0x527B4EB423AB95EAULL, 
            0xF07DCB15907AD786ULL, 0x4A1059FAA7405BCAULL, 0x4659CDCE3E937747ULL, 0x539E966628FB0ADEULL
        },
        {
            0x19045AB9EFBA2234ULL, 0x202093AC85CE0095ULL, 0x0005B9BA5E395E2EULL, 0x70E8BE5C387DF05FULL, 
            0xF841E473C1011F95ULL, 0xC03A385F794449E3ULL, 0xDE8AAB273927B7BBULL, 0x31C1CAE78EC8D151ULL, 
            0x5EE936F81CB09A8BULL, 0xD5D9DA4E673178F5ULL, 0x5027798B41D1CA6FULL, 0x11B3AB2B5E1E6679ULL, 
            0xE38B192D83DB34D4ULL, 0x9AF55D6760D6E6C1ULL, 0x8FE6377D6937D98BULL, 0x5699A464BBB9CA1DULL, 
            0xA4ED58439EDCD89FULL, 0x93D8276942BBD445ULL, 0x54C32C19C148CD28ULL, 0xEBE34815970692D6ULL, 
            0x9D4F4474051318CFULL, 0xAC2CB9FE548AB465ULL, 0xDE3625805C7AC3A9ULL, 0xA6C936F6A94F84E2ULL, 
            0x87261B8179B535FCULL, 0xDAC988A345A5C0C0ULL, 0x047440689BCC335DULL, 0x9A92863A4F6A6B16ULL, 
            0xFCB175B0F93F261CULL, 0xF1DCA2894155E0C7ULL, 0xFA77B14759CD15F1ULL, 0x5D47789110E600BCULL
        },
        {
            0x72D30419FF9A5D73ULL, 0xBFAAF4F24413CB38ULL, 0x25B83866C20ADCDAULL, 0x8DE5F0A578DDBD0CULL, 
            0x914C6E50DFC21F19ULL, 0xAC3E380E45E6418BULL, 0xC99153D255E26317ULL, 0x73058420FBD16267ULL, 
            0x8DAB718BDB28D8A4ULL, 0xD56A8EAC29C84DB9ULL, 0x5EDBC145EFC9283FULL, 0xCD40071574CE097EULL, 
            0x9BF112F69A8BADD3ULL, 0xA757945C23557207ULL, 0xCC5A283602FCDC3BULL, 0x68C191EA12660A8CULL, 
            0xD8F018608561889FULL, 0xA97ED4C2B1312357ULL, 0x32884F27B50ACEB6ULL, 0x7CEA97997ECC4235ULL, 
            0x5D90C96DAE69113EULL, 0xF8615DEFD9C98DD9ULL, 0x62C482D5DBCE7522ULL, 0x62D0CE44F534FA80ULL, 
            0x4E90633B6F1360EAULL, 0x2EED15C7472013CCULL, 0x7A87296AD58A7CB3ULL, 0x1268B49D23E4288DULL, 
            0x8247D0E8DC097A8FULL, 0xB74383193DA6A696ULL, 0xDF16626C6B462D16ULL, 0x72CAC3734D2E4619ULL
        },
        {
            0x7722DA4B83107CF4ULL, 0xC67C6EB8AE8DE2DFULL, 0xD25D4201B5B05AB0ULL, 0x34A5337CF7C7D54BULL, 
            0x9A5C4483EFB6AC55ULL, 0x9F4FBEEFC58BDEFCULL, 0xA6F34CE48ED1DC93ULL, 0x4639A12EB96E6262ULL, 
            0xA6ED80B1CD85DDF4ULL, 0x46FA3F60A96B3EADULL, 0x3D0E1C2A3B3A277DULL, 0xC22DA1F7096DF20AULL, 
            0x0DB614024E24445DULL, 0xD6DEC865766034BAULL, 0x9F9F42E717894BE9ULL, 0xA22A997908BCF552ULL, 
            0x7F8FBDB166D111A2ULL, 0xD10F4C8A57D1E8CEULL, 0xDF9B8D289B9DD932ULL, 0xDBAC090CCB3B7C30ULL, 
            0x33B9AE8263F9DFBCULL, 0x15EBDBC045495C4AULL, 0xDFB0789D2E489DE0ULL, 0xFA2DFA7DF0E1570FULL, 
            0x8D60C79D40E9216CULL, 0x46573A37A3B1BF40ULL, 0xDB1B581DFD398F72ULL, 0x670658C613C8E479ULL, 
            0xEAAD2953D98CF65FULL, 0x101E3C93DF70C936ULL, 0xCFC312C5C793A191ULL, 0x31D629F9451F84B2ULL
        },
        {
            0x3D59F406D6BAF36FULL, 0x3D3846DAFDE5955BULL, 0x0D677E59C008FD28ULL, 0xD3040D1794DA82B2ULL, 
            0x02DCEB18713BE253ULL, 0xAF6B85B6B04210CDULL, 0xD73BA86F2423D920ULL, 0xC8947401528A1150ULL, 
            0x7309436ED1B4B582ULL, 0x693C9C4B10BB2648ULL, 0xA9CD2D7ECE4DFD54ULL, 0xFC611E514DD0CBFFULL, 
            0xE9B5E252ECE7CD5AULL, 0x6F7512E3E3499461ULL, 0x7DB97E7D58BAEA75ULL, 0xE5591DB74573AA9AULL, 
            0x7331F82B305F2E5DULL, 0xD43614B012D366B5ULL, 0xB45F8255912FB66FULL, 0x4236AA129CEC0752ULL, 
            0x999D43DBD081894DULL, 0xBC01C8FD55EF9D52ULL, 0x05E8BA346E8BCE72ULL, 0xAEE8BB90DCA0C8D3ULL, 
            0x7246BEC9DB307425ULL, 0x6EBBED973405DCBAULL, 0xF474306A8EBA7CDDULL, 0x6A9C2503F4A84CF4ULL, 
            0x32C36919B39072C4ULL, 0x0411EC4F5C37D6EEULL, 0x150F77343C6CE97AULL, 0x00401758439950FBULL
        },
        {
            0x2612B5748DB09667ULL, 0xE7DE81E93362FDFCULL, 0x5A9310DA5DBB6539ULL, 0xD68D97B73194FEFBULL, 
            0xD2A5D1CE2E4B0F50ULL, 0x59DEB03D85C58FEBULL, 0xD310E517F5876D6CULL, 0xD612C4AA2896AE56ULL, 
            0x67560AB3774AC7CAULL, 0x4B97493ED1949DE5ULL, 0x7DF21B93E7EC26CDULL, 0x9A9CE0E5FB526388ULL, 
            0xBF76AC6699D18835ULL, 0xB2BFE4976C65051BULL, 0x02A0F70FA9984ED3ULL, 0x55CB771A2AD61BD9ULL, 
            0x43F767551733CF6AULL, 0x9DD3B68AB1679566ULL, 0x57443957C6CCACFFULL, 0x024F655B7C8C5707ULL, 
            0x5A78174D2A8BA9B1ULL, 0x418F1F1908CD0B99ULL, 0xE44DFB71087C222FULL, 0x872F2A767E4A3CC0ULL, 
            0x5F0C2075B19770B6ULL, 0xF02B6658D6828154ULL, 0xD300EDC4A9C03A98ULL, 0x4A34EBE07878C6F1ULL, 
            0x67BF129BB9301E98ULL, 0x4A58E1B16BAA9D83ULL, 0x210E3BCBFD5275E5ULL, 0x709BADAD6A09AAC4ULL
        }
    },
    {
        {
            0x7DF1A0EF9F1EAD51ULL, 0x1753835214FA8601ULL, 0x86F686AF9B10B18CULL, 0xE9F49201B677E569ULL, 
            0xB2EBFD8ADB463DA3ULL, 0x21B66A62CEB7AFBAULL, 0xFD0043941372B4C1ULL, 0x5CBF8810CBDD194BULL, 
            0xBD8916B0973C7720ULL, 0xCAB8A42E5697E0FEULL, 0x42461C5006C7E91AULL, 0xD5CA87416D575761ULL, 
            0x10CF6124A90F64EFULL, 0xFE510354D6E20ACEULL, 0x2531F47967DED69AULL, 0x7BB8EE1E60F5E277ULL, 
            0x959C0155C1040147ULL, 0x2F7D20023791BD48ULL, 0x44943F4A1EEBFAD0ULL, 0x05A54B2287B6092BULL, 
            0xC390E5BA39C88459ULL, 0x07260B045F987E67ULL, 0x346F69E9DCB9776EULL, 0xC840BE345E3106D8ULL, 
            0x3B5C5531F72D057BULL, 0x92CE6189A9CA3B36ULL, 0x023686325C762EBFULL, 0x388E97242FE5DF58ULL, 
            0x670235BA864679F9ULL, 0x348DEAD76CE6D0E0ULL, 0xD2C6F7B6113774FEULL, 0xCC0654D9D1DC2D47ULL
        },
        {
            0x39904A5A37FF1F14ULL, 0xFE622D992299CCB7ULL, 0x8566180B2E95CB0FULL, 0xF1CFC68FC6D4604CULL, 
            0x2BA4F1664CDF67CFULL, 0x0F09CFCB49EF9512ULL, 0x1766E3A7981CA655ULL, 0x026DB607439ED6F5ULL, 
            0xC7C308AF0E7EBBD0ULL, 0x64B6E22928A0B30AULL, 0x1EF00CDF77FC2438ULL, 0x6A49EF6770B8AFD1ULL, 
            0x018B16EFCC6BE985ULL, 0xA1522E1B83CEC773ULL, 0xB1309B60D42A5AA4ULL, 0x1AD2ED6726A64959ULL, 
            0xDBEF9D898A0F278FULL, 0x95F0E80F5FD2B3D8ULL, 0x6485CBAE13A1D108ULL, 0x9D557B9D24558509ULL, 
            0xD2C617D13F0D4163ULL, 0x2B339134A73B06F2ULL, 0xD49F3E61CD39FD1EULL, 0x7FE70B77A778A704ULL, 
            0xF519A26240042532ULL, 0xDCC60D92A651860AULL, 0xC607CA5EE59FBCC9ULL, 0x1F9B16D1CF645477ULL, 
            0xB36C5958E5025A3FULL, 0xDFF48C6F07000C4BULL, 0xC35E46139CC30F5CULL, 0xF59AF0E91077D314ULL
        },
        {
            0x62A432DE869B431BULL, 0x305F587F27DC27EDULL, 0xF417D33967F09D83ULL, 0x79C8C061CBE27F4AULL, 
            0x51DEFB24D5488DCDULL, 0x169257D95066FF2EULL, 0xD2270F9187B9BA9BULL, 0x10B26997E41E226AULL, 
            0x7DDFCA8BF989986EULL, 0x46E29BC97BDA0A21ULL, 0x3978C6263830451CULL, 0xBF62241A211B30E7ULL, 
            0x1B4A568944E2B3ADULL, 0xA7D2769A04DDEEBBULL, 0xB86019CCCD9F0804ULL, 0xC456F7B5013C0578ULL, 
            0xD9AF03116BDE1D2AULL, 0x2A790ABA67E2CEB7ULL, 0xDB1F2B0E56C63B22ULL, 0x04F1A5494EA7DFE6ULL, 
            0xF2E2110CDC10F1E5ULL, 0x423CB1BBFB58DC10ULL, 0xCF22D969608F9DA4ULL, 0xFBB4AC155E4A68ACULL, 
            0x4CB98DB1A7B77566ULL, 0x68984841E05B3797ULL, 0xBFF03A2988451D09ULL, 0x23E47E392FD002FEULL, 
            0x4804E8F813FEA1A7ULL, 0x19FAD08E2E65A5FEULL, 0x07346D4A791F5B1AULL, 0xED62C1FA5ED83AF8ULL
        },
        {
            0x2EB7B3AEF49AA931ULL, 0x146BBFB5938139DEULL, 0xA3459B896FE4E61CULL, 0x1EC8F87DC6EAE402ULL, 
            0xCAE5AB2A6A84C090ULL, 0xC11B2F3CA285AE64ULL, 0x91A8A4528D912E6FULL, 0x523685D3B360C4C6ULL, 
            0x297ACF094BE3C376ULL, 0x745F830E656E9E92ULL, 0x66417D4E3CACD599ULL, 0xB65B1348ECF55049ULL, 
            0xDBFEC06411B2BDE0ULL, 0xBE16100D55A6C7FAULL, 0xD86D9D36EAAE1B64ULL, 0x98B24A1CDE47D1BAULL, 
            0x0835EF6F3F463BEFULL, 0x27E02DA85F6F0ECBULL, 0x38508057A0DD20E0ULL, 0x7499083EFE380DD9ULL, 
            0xD27786CB1D4327D5ULL, 0x36062C024A35F999ULL, 0xE2C0BC8E6C151E67ULL, 0x0FC0DFADCCC44941ULL, 
            0xFC38EE91EE07FBA3ULL, 0x84747523E30E6386ULL, 0xF443CA62BDC160E7ULL, 0x23512012D368CD52ULL, 
            0x7F6BC49C4B4D1A35ULL, 0x32DBF68DE7BF7989ULL, 0x68C3CE57C67DB58AULL, 0xB3744E31885AD0A2ULL
        },
        {
            0x109F8A6D59286670ULL, 0xBF2DEFA6D1BC1B26ULL, 0x1810A7D95576FB07ULL, 0xB022CB460AE1169FULL, 
            0x5B17D5648C4B2275ULL, 0x64613D1F9CA9ACE2ULL, 0x198C5EA93A265C55ULL, 0xDE575ECCDE6CB1D2ULL, 
            0x90B09D41C2DC65D1ULL, 0x81D578E19E56F526ULL, 0xDC078099CD4A80D6ULL, 0xBED37B308B440F56ULL, 
            0x0EC5F99207861B8FULL, 0x8761ED886E5D9154ULL, 0x9A51275831A7719BULL, 0x1310538CF82F35B3ULL, 
            0xCFC311E5B19BE372ULL, 0xBE6824D5C07AF5BBULL, 0xD8B50F7563416295ULL, 0x94E6721AB2DF44B8ULL, 
            0xE95A8A6D82AC2C02ULL, 0x36E3C10ED69E9E01ULL, 0xFFD3BEB656A558A5ULL, 0xB7EC1507FBED6D3AULL, 
            0x092CD44D9E521B4EULL, 0xB134D14504DD3105ULL, 0x17045867FDEC0BDFULL, 0xE735DDBC0161DF57ULL, 
            0xA27254F7C246C515ULL, 0xD31EAA5533F60FF6ULL, 0x2996F8C02D9CF4CAULL, 0x386C37FF10F43B43ULL
        },
        {
            0x4FF1AD15D9ED63DFULL, 0x6A5FE1D1E9D845EAULL, 0xDC631D2B6CFFFE3DULL, 0x7C28BF3EED5CE590ULL, 
            0xAF3AE30E01006B94ULL, 0x18B004F898866CDCULL, 0x1DF9361D26282297ULL, 0x38B66BD31C485249ULL, 
            0x68771C027083E27BULL, 0x92B88747973889E3ULL, 0x973102C8FA2917FBULL, 0xF48E37DDC5172ADAULL, 
            0x18D231075E9A2617ULL, 0x9C5C82E1D650194FULL, 0x90B38C80CF151E25ULL, 0x07508676302BD02BULL, 
            0xCFA74EC0BD3B4974ULL, 0xB5074FBC21D774A3ULL, 0xA9E2B0F9BE9F1C3FULL, 0xA15DDD85CE659145ULL, 
            0x057EBB7A0378565DULL, 0x3C2AF8F43F36C74CULL, 0x5ADA870386D7A23AULL, 0x7515E9C5B3C2CB7CULL, 
            0xAC4FC4E88B8D92D2ULL, 0xED915191C827C5B9ULL, 0x0532D0A7ED5EDBF5ULL, 0xDA548973E634D8B6ULL, 
            0x4B4779DB0BA5C27CULL, 0x7ED6F03B455D145BULL, 0x3B9F272555C0D3B6ULL, 0x2FC8567FF87DE83AULL
        }
    }
};

const TwistDomainConstants TwistExpander_Sirius::kPhaseGConstants = {
    0xCC72F81A0E893AD8ULL,
    0x5ECB1D67571D1BD1ULL,
    0x4FCB601E9A971820ULL,
    0xCC72F81A0E893AD8ULL,
    0x5ECB1D67571D1BD1ULL,
    0x4FCB601E9A971820ULL,
    0xC2AE4B086D2981D2ULL,
    0xB7CA0E68F67624C1ULL,
    0x30,
    0x69,
    0xF8,
    0xF8,
    0x86,
    0x4D,
    0xA3,
    0xDF
};

const TwistDomainSaltSet TwistExpander_Sirius::kPhaseHSalts = {
    {
        {
            0x2448A53ADA5ED349ULL, 0xC1C1F153A52A6223ULL, 0xA041E48C78168CCAULL, 0xABC81669A2AF2566ULL, 
            0x9A7645E4F2FE012CULL, 0xD88CD210328B2CA3ULL, 0x2CF2DC64E2455E0EULL, 0x366B6C8B8C414142ULL, 
            0xA756C0E932388714ULL, 0x267255A12EB4A2F6ULL, 0x1FA0A245532C6321ULL, 0xA108CC84C78D17CAULL, 
            0x4D74D71FF6C0F986ULL, 0x00D7D800C88F871DULL, 0x579F26F69D7260F8ULL, 0xE75302203D95880AULL, 
            0xED8B30F1301BF10BULL, 0x4429A49EEB2F8E32ULL, 0x879C46BA25086B4EULL, 0x11BC195205A82B1DULL, 
            0xED9F94E9029F3543ULL, 0xEA26C92C0EB5B13DULL, 0xC2397E0234AA6C62ULL, 0xB9D3C7867231784EULL, 
            0xA8D3344A5AF9369DULL, 0xD6BA44E3F950A0DFULL, 0xE57166BE8F5B8EDCULL, 0xB2271C29569C142BULL, 
            0x31D29EBB88AC578BULL, 0xFAE54CE914C3927CULL, 0xFFE43668D4EFEF7DULL, 0xA9D4FA458F39CC8CULL
        },
        {
            0xD6DD9DF2C2C77B98ULL, 0xC31CA8695D433D54ULL, 0x1EA5BA978590ECF6ULL, 0xD834E04E82B44288ULL, 
            0xA1FCAB6C0B2B4934ULL, 0x60A27DCA09EEEF02ULL, 0x3E88F09448E7AEC9ULL, 0x1BC1AF76B70841EBULL, 
            0x2C3AF93EFBECC6E4ULL, 0x592E8F887DB5EB58ULL, 0xEC5AFF5D16D647B1ULL, 0xCDFF422829873969ULL, 
            0x6D68656B588F02E8ULL, 0x0619764DB4BB5D9EULL, 0x944A96509E15AB68ULL, 0x73AD970FF8CE22A9ULL, 
            0xB8CD94C5AA47AB40ULL, 0x0830D4E874AB2CA2ULL, 0xF7CEDAF275E6DEE7ULL, 0xC04075AF85C09960ULL, 
            0x2991C53416938AC1ULL, 0x4C6CDBB6893B1C1CULL, 0x97DC46885149EF41ULL, 0xB6E10E5711F8ED66ULL, 
            0xB61F8922164E85D8ULL, 0xA021A691840C1C63ULL, 0x36F1D80CDD45371EULL, 0x08D05B931739B6F8ULL, 
            0x7D9E40FEB5BF00F3ULL, 0x335D0A42040B440FULL, 0xE4F5B7E3D8B9A0E7ULL, 0x4504A87178A7EC24ULL
        },
        {
            0xDDD5C8ACD6104696ULL, 0x4F3D2B082E44056BULL, 0x251D4D721C46BFC4ULL, 0x1327460C0042CC66ULL, 
            0x9BE1213A93377113ULL, 0xCBC27B6196397DD0ULL, 0xBF245336FD4D6579ULL, 0x52DAC70E0D14A4FEULL, 
            0x1FD4ECF9DA2BB0E7ULL, 0xFEAB688713AD31CDULL, 0x8040D7AD4FA2631DULL, 0x3A80F5325548A6CDULL, 
            0x72665ECD5BB4806DULL, 0x8DE85BB53E44DD83ULL, 0x50FC95F9930A8A73ULL, 0x1D0421D575D44CF2ULL, 
            0x067FA65F6941237EULL, 0xDF23922EDCE65504ULL, 0x35F49E97FE9B667EULL, 0x50E5ABC7AA7AC2D7ULL, 
            0x57F02763FC7AA26DULL, 0xD15E13CA2D17106DULL, 0x725648C4C06931C9ULL, 0x258E488EED30D2E3ULL, 
            0x1FDCCB05E2F1D917ULL, 0x531365E55F3B4280ULL, 0x8089426C9E84EA48ULL, 0x6110A38A193C485CULL, 
            0x2F16A01C97C1A3B6ULL, 0xA62B804131AE910AULL, 0x144ED98969BF35B7ULL, 0xE141B499FA8F12ACULL
        },
        {
            0xFF73B35532E03D94ULL, 0x1D837C8226FCC276ULL, 0x10F659A2EFA49B4CULL, 0x78F20F75A5291DE6ULL, 
            0x8E5313A7A4C442C2ULL, 0x9071C6AA7513D4A8ULL, 0xCEBD8C5F49355E59ULL, 0xAD4E4E0EBDC6498CULL, 
            0xE604DC3BDB3963D4ULL, 0xE19CACB9A29CF21CULL, 0x2D49AD7397318DD8ULL, 0x2A65C6B8D9C2B301ULL, 
            0xE8842F9AD44DF3ABULL, 0xCD67F7513C517D70ULL, 0x600E743EA04176AFULL, 0xDA421A5E8D37412CULL, 
            0xFE93FF43B4CB4BCEULL, 0xDE42177C0F1527DFULL, 0x8FE1675292218467ULL, 0x4422BE9260532850ULL, 
            0x16A5257CFFCB86ECULL, 0x898521D3B5CE3250ULL, 0xA23587ABA07C7693ULL, 0xB762511E3FEF5F69ULL, 
            0x6B76E37138DF540BULL, 0x066A54669AEAF6E1ULL, 0xE45B0271B084CD16ULL, 0x29A42A1B49DCB66BULL, 
            0x66C6E80A49CC3062ULL, 0x97AB808317B66806ULL, 0xE7867FEE442AF8F3ULL, 0x19D1934A5652498FULL
        },
        {
            0xD3C2B0B94C7A3637ULL, 0x5C6EB28706C97774ULL, 0xFD091FB10B1FFC5CULL, 0xD657CA79B615B19BULL, 
            0x6BCE8B33B940655CULL, 0x48011865411F9628ULL, 0xB0F6C15E9840D9F9ULL, 0x1BB3222DFEC63038ULL, 
            0xA8C3EE0CE0AF6B2DULL, 0x289FA14F8D4B1CD0ULL, 0x4E09374F7ABB9A28ULL, 0x6F59A9BBB80051BEULL, 
            0x799C90B4150799B1ULL, 0xD2C63ADA315C000CULL, 0xBAAFFBB5B062C7FCULL, 0x86C267972CF9B6AFULL, 
            0xB158BE7AC875E9B9ULL, 0x3A2A26E50E991F50ULL, 0xD39305977AEEA614ULL, 0xA7FC4D96804C166AULL, 
            0x8C9AD66D776E546FULL, 0x03A31710E6CB46A7ULL, 0x9BF7AAD2A075743CULL, 0x37E9919775C0BF53ULL, 
            0xDC9EF11FE45DA760ULL, 0x7AB48EC7C6B939BDULL, 0x65EF5415BB8C2D0EULL, 0xB9F919D2712879D2ULL, 
            0x6585FAC102A5F43EULL, 0x06820A8AC9975546ULL, 0x49E183CE37218F58ULL, 0x42E148030B1B2576ULL
        },
        {
            0x73BFA9411435FF8BULL, 0xA683D2FDDEBB33C4ULL, 0x5E5B2C4E48F20178ULL, 0x367A0227C1CD9A01ULL, 
            0x7957A2B4A16E4717ULL, 0x2A633BC29AAFFE95ULL, 0x385360331FEA962AULL, 0x8BF7A0CE3FCC3711ULL, 
            0x61D7684DF59FAEB8ULL, 0x8B401EED1E12A1E9ULL, 0xD5354AB7442AC35CULL, 0x4E11C963BBB58460ULL, 
            0x23C3D2E4A17406CBULL, 0xB86E1C46B04C35BDULL, 0xABDF2CF61805BFE5ULL, 0xC7307BD91A7B3384ULL, 
            0x7B5430A24A8A9621ULL, 0xCE2B9BF361ECDCBCULL, 0x35743F740DFD7EF8ULL, 0x6FF56D680D5200FDULL, 
            0xB3E129326FC0CA23ULL, 0xECE0E9D5AC667024ULL, 0x79CDE169BA7245DCULL, 0xFDF9035BEA48D6E6ULL, 
            0x67DBC2C30104A188ULL, 0x81D47A6F110DEB41ULL, 0x5264C7BB8FFF83EBULL, 0x12D4B597664DD43CULL, 
            0x35705D68FDA1D8B5ULL, 0xED1DD185E65CEA3DULL, 0x85F3790176650651ULL, 0x1AC9457323E1ED46ULL
        }
    },
    {
        {
            0x564CA1186DABB6B5ULL, 0x34C29AADAB55F88EULL, 0xFA816DD95CC7900BULL, 0x883F98D92267ADF1ULL, 
            0x4EE39EACD1E4E3EAULL, 0xB4C9EC7E75E83BC9ULL, 0xCA98DBA20E3EC1EBULL, 0xB24ECA74FCB87BD0ULL, 
            0xADF64B7829CC2EF5ULL, 0x1FF118CDF73F850FULL, 0x1A3EBF844C0721FFULL, 0x2F52E6BDD82E0E25ULL, 
            0xE9D6D072070E5778ULL, 0xD1344AFA18D592FDULL, 0xB8AC555676F7A13EULL, 0x4587E26C1882D648ULL, 
            0x4D3D0302ECEC8778ULL, 0xD5ACA65EEDC8C96FULL, 0x8478923F46BF3BE5ULL, 0x6DB5B29E4FC9F45CULL, 
            0x3E7720D04B5429E5ULL, 0xF457DF17FA78654DULL, 0x0F6B9B4ACC1ECA89ULL, 0x8FE76DF2F392408EULL, 
            0x47189448AA132BD0ULL, 0x6D3A4ACF832E44B1ULL, 0xBCA84798AA1A5F77ULL, 0x74FC5152607E6B85ULL, 
            0x9571689E5357120BULL, 0xAAD72E17FB0A9F67ULL, 0xDB12FC2A024AF3ABULL, 0xC739F012FA612E7BULL
        },
        {
            0x6ACAFC3D4893D2D3ULL, 0xD949BEB7CB97E642ULL, 0x8595C5E5C0138A34ULL, 0x2E1758831887752FULL, 
            0xB0CA727043C3BFDBULL, 0xAD9CA4CBE6185A26ULL, 0x8668457C79D76638ULL, 0x08B9AD7DF2C9FAEEULL, 
            0xD7F2CD538D3B85EDULL, 0x740CD7D2FF3C6C05ULL, 0x378610C5B7E76C1FULL, 0x9E74734D6811E3C9ULL, 
            0xBC177D846D8ADC34ULL, 0x12330E4F2E1B8414ULL, 0x134A61DDB124E883ULL, 0x46C389E842ACBF55ULL, 
            0xA96E7982D64A189FULL, 0x1B24894792D19630ULL, 0xD2EEE4E1DC30474AULL, 0xDDD10F8393EDDE11ULL, 
            0x8C0DD512699773F8ULL, 0x65966673E4873605ULL, 0xE66B4241A2C4ACCBULL, 0x943B69EE07B6FF9FULL, 
            0x165DC3C4071436F3ULL, 0xC756A39E5FC400E1ULL, 0xC8789E81E7BC7C2AULL, 0x5CF390D5A0B5E50BULL, 
            0x7118D1D318B4E2FAULL, 0xD38A1D9C966CE9EDULL, 0xB81CDB84DD8EC0D0ULL, 0x6F1C42BB0764F69BULL
        },
        {
            0x5AA6231EA9B2D527ULL, 0xB55E1E8A128978EFULL, 0x6DB1F8C4AC304F1BULL, 0x07BAC76C530811C8ULL, 
            0xAAFEA7F325DB3DB9ULL, 0xEE53F593094D1A99ULL, 0xC12BA425288D9232ULL, 0x6C12EF3EDAE7F86BULL, 
            0xF1D6A887CB2FB0ACULL, 0xBCB6AD4C2BD28E53ULL, 0x645086618FBE5953ULL, 0xCD268CD06D195453ULL, 
            0xF172B77855B39A83ULL, 0x6BB2B687ACC04832ULL, 0x8DBCAF992818A907ULL, 0xE401162800546554ULL, 
            0xF900E1A7DCD89A08ULL, 0x5F7BB0EC3D1982DAULL, 0xDD82242EDA937150ULL, 0xA9B5B87EE3556D24ULL, 
            0xDE0C683C04D95460ULL, 0x8B079F2848ECCB93ULL, 0x3E6747682D623301ULL, 0x1ACA7E44B619C10CULL, 
            0xEC16A7AC87394729ULL, 0x85183D645A474983ULL, 0xADA31EC6847513B2ULL, 0xC57468100F8AF6F6ULL, 
            0x8A1472F58B65BD2EULL, 0xF004D9570AC7B8F2ULL, 0x0F4F365DB82E587AULL, 0x01127CA9BBFA9BC0ULL
        },
        {
            0x1DBCA2F2F08F6CDEULL, 0x7F7CCAEB3C8C5737ULL, 0x3A551F7AEFC37B51ULL, 0x9188C3950FDC94DDULL, 
            0xAB7DF7078264D5E5ULL, 0xA3807DD9109A2F55ULL, 0x6DC6767F5CDB526AULL, 0xE600A385A2D4FB19ULL, 
            0x1A31B9605B3CED9DULL, 0x47D702EBAE7FA50CULL, 0xC3C4B48D685A5566ULL, 0xF2C1780C4C69494BULL, 
            0xCBB590C4A0EBAE47ULL, 0x0F64213804D92EB7ULL, 0x69B37AA61BA18E4CULL, 0x5135F88C0DE42B89ULL, 
            0xFDA9A2582ECD7874ULL, 0xB2197D57A98340B4ULL, 0x98B7F644CDFF8638ULL, 0x533CD7D80DB314D1ULL, 
            0xCFD512DCAF94E617ULL, 0xE2BA9F3FAF8BD43EULL, 0x0544A044E6A56922ULL, 0x06DA03EC69C2D0D2ULL, 
            0xDEE6E7F009FEC2E8ULL, 0xA9B59E8F0EB22A55ULL, 0x804B01EEA15AEC62ULL, 0xB96EC9FD0D604AEEULL, 
            0xDFDF079A7CF81D08ULL, 0xF5D2A9D9317999CAULL, 0xEF7206CC93DFCD76ULL, 0x1016BCB0FD936EABULL
        },
        {
            0xEA0A949BC620AA51ULL, 0xD25A3233547CF2CAULL, 0xD766CB0B8D909CF9ULL, 0x78C0C0BA7373D4CFULL, 
            0x6E98B9864AFEB42CULL, 0x9C73B2972FBE7518ULL, 0x8A7FCEB7C62D79E3ULL, 0x583B05375AD2E530ULL, 
            0xEF1256BFCFABF0C2ULL, 0xEF8F3294EE308698ULL, 0x23A613A23386BD3CULL, 0xC995F4FFE04870CEULL, 
            0x736B1E04095D1019ULL, 0xDDBF954C3F12DE78ULL, 0x3EE83C2B2E191222ULL, 0x8F6097DE0AD9CC8CULL, 
            0xB9C7ACCEDE820F5BULL, 0x44E74DDFA9525E91ULL, 0x94FFDA9E47817636ULL, 0xD3603D28E7E405D7ULL, 
            0x5287CA7A7B8DE4CBULL, 0x6909341CC5245039ULL, 0x9DF200B3B44A9571ULL, 0x9FF8FFF8CA03C3FEULL, 
            0x42B7048504BAA10FULL, 0x58E4D1770E776EF3ULL, 0xAAD0B9AA045C5F74ULL, 0xF4E3667AF9E1280CULL, 
            0x6BFC6C35AB64A369ULL, 0x40341A4123154EBBULL, 0x60B2A298C71E8113ULL, 0xD1DBC2D0144EE398ULL
        },
        {
            0x025249711B8AB450ULL, 0xCD5215AC12B547FCULL, 0x211657B158D0C977ULL, 0x8A1AC16F6271ECCDULL, 
            0x6147B2116B791AB7ULL, 0x0201BEE9ECEB8FC9ULL, 0x0CAFE09DDC95B6CCULL, 0xBFC5EF996EC2D5D2ULL, 
            0xE485B87D8A3EDADAULL, 0xE3ADC624CDC765E7ULL, 0x301F9829A58D927FULL, 0x524109C8DE772EDAULL, 
            0x82ABB9E41544A496ULL, 0xB8A8EFA5FEB82AFCULL, 0x6921638D9606EDCDULL, 0x411CDF49C46D9A23ULL, 
            0x15EE76155F024582ULL, 0x70103652FF11C5E9ULL, 0xFE89F5A77BC5A242ULL, 0x2D4D6B7B223C273EULL, 
            0xD8BC5A159CBDD330ULL, 0xFF6320019D3FAE4CULL, 0xBA52C9DCC12ADB30ULL, 0x0D5079B3CD6BDA14ULL, 
            0x41FAD22607A89B14ULL, 0x935BFA12141050BEULL, 0xEF05D61A899673CAULL, 0x5F31224C2994C2CCULL, 
            0x6B318625C158D31BULL, 0xF452B14C8CB1F9A8ULL, 0xCD35FE7FAB7EB018ULL, 0x2BA2427166B7F20FULL
        }
    },
    {
        {
            0x73E069FF90026B5FULL, 0x88A922613E44D683ULL, 0x57A1459AEC09B37EULL, 0xB61EEA405E3AFCFFULL, 
            0x81CB934871561E7CULL, 0xA62E75B7EDDEAD0EULL, 0xBDF62AE7F3648F35ULL, 0xD148D15010AE0A6AULL, 
            0x2A86080ACE0FB35CULL, 0xA2344DF5C48AD514ULL, 0xCE613C8E57F8BE24ULL, 0x70EB4ED50C404271ULL, 
            0x3F6BA7C3227DDDF7ULL, 0x35458FBD877D5175ULL, 0xC817D6DCB98F20B2ULL, 0x0BB3F5F0C1123BD7ULL, 
            0x15598A9CDC69DE7FULL, 0x1A5E4F5D0FF0024CULL, 0xEE8DEF7823DB4D4BULL, 0xDBD134FC0421CA3CULL, 
            0x7FA4F0FB1DF8B507ULL, 0xEC6C6D4CCA989A56ULL, 0x6C71574F5B6799CFULL, 0xC9CE42943E35BD92ULL, 
            0x005AE6D3AD0CE211ULL, 0x71AC3FF3A1021EBBULL, 0x7DD87FDB9847EC2BULL, 0xE322A35EAAB86CBCULL, 
            0x621B8A0F76684AE8ULL, 0x59A29654A75E72A6ULL, 0xB9F1F4C916BA86EFULL, 0xA9565A985F178822ULL
        },
        {
            0x38F4E9FDF5574E7CULL, 0x9B6D1152A5E1A117ULL, 0x8C0E1CADF4A82169ULL, 0x28F496D113C4EEC4ULL, 
            0xBF257622C47BF806ULL, 0x715758876F702362ULL, 0x6DA51D2778ECB3BCULL, 0x132A830732AACC85ULL, 
            0xD7D1C366F85B6547ULL, 0xE47B483C7C1B9B14ULL, 0xD1A71C166B52E1F3ULL, 0xBA54AAC9D095816EULL, 
            0xF51636FA981A39C1ULL, 0x83A0E1F3034F8D16ULL, 0xD87C97953F9E518BULL, 0x67D4A585210EC75AULL, 
            0x9AE47A7D390164FEULL, 0x60A4D93B0926373DULL, 0xC61741937A912494ULL, 0x5824EC6C9E5CA805ULL, 
            0x42402A8BD11AF995ULL, 0xF14ED22CF031274BULL, 0xFE53D821B2A74A57ULL, 0x937FC7253AFAB0FDULL, 
            0x8AC84741322B6B93ULL, 0x7CC0C989C85E17E1ULL, 0x7BB18A609C6A58F6ULL, 0x7841109D6B5AC72AULL, 
            0xE8AB0EB906E2BD07ULL, 0x3D73191CD44764F0ULL, 0x7C73EE30059FE2DEULL, 0x4D87EC89086A6C83ULL
        },
        {
            0x9A2E89B193F84A0CULL, 0x1AE40796EFE8EBA5ULL, 0x683FFE8917DFD7B7ULL, 0x0633F39CE08149FDULL, 
            0x2421CF561D8C50A4ULL, 0x7F0AC37E400FE2D0ULL, 0x68B9B128B677E1FBULL, 0x1DF8C9208153D471ULL, 
            0x3F09C2AF1B0FAA15ULL, 0x2C727388463D48F5ULL, 0x09ABE1578332291FULL, 0x6A95CCF84DA2C39DULL, 
            0xBABD6085A6CA97F3ULL, 0x5C7B3BEC55EE72C3ULL, 0x338A4CAEFA9A63B0ULL, 0xEBA99C32D1DE01F4ULL, 
            0x9AF14D4CEB597DD8ULL, 0x6CC96D2EDFC43D0EULL, 0x10CCCE11476E7F80ULL, 0xADB9152873BA114EULL, 
            0xD7D4386DD1B57B19ULL, 0xE16B1BA50FB22584ULL, 0xFC5EDA5967583098ULL, 0x7955235F66D5CD4CULL, 
            0xF678C50F53C4A4DDULL, 0xC8571D31B8542B5CULL, 0x0E334818D323F39DULL, 0x61C9CAEEF34A0253ULL, 
            0x71E103608B469572ULL, 0x973F4AEEA12D4175ULL, 0x5CE9AAB89CD0EF55ULL, 0x821E5464ACB7E539ULL
        },
        {
            0x185803C8B40AFB6FULL, 0x364FF6927B5282B4ULL, 0x96EDEA2BC7D3DDD1ULL, 0xC2A61B3BCD6AC185ULL, 
            0x5673CC27D3D6D6EAULL, 0xE810CF0ACB4A4B54ULL, 0xFCC7E1AD22D9FC65ULL, 0x5FD7840C9DE10403ULL, 
            0xBDACAC60AB6EE363ULL, 0x169214A1806D829CULL, 0x625CFBC8E26C5BFAULL, 0x02682953FD7CD089ULL, 
            0x109172FA567C9F26ULL, 0x767F72113D7D7281ULL, 0xB7D08D743AD93A18ULL, 0x5E6738E84C147767ULL, 
            0x18DA10CD23E39FBCULL, 0x3FE78CEECE353B9CULL, 0xEC49350CE877C13AULL, 0xA710530DCC2A35C7ULL, 
            0xC00147286F29F5E5ULL, 0xE0ED42BD6D7701C0ULL, 0xB6A5F340C84100D2ULL, 0x5FCB6E78D026A9D6ULL, 
            0x96C32BC85EECBF81ULL, 0x16817DAAD1DFD8CDULL, 0x5AB60D2910FC9C94ULL, 0x02BBF7839783C39EULL, 
            0x97B8A6EBB625E302ULL, 0x2D3F0BB3EE51D41EULL, 0xABE2DA713C365191ULL, 0xAE42BA28377191F4ULL
        },
        {
            0x7766CB3B20F39849ULL, 0xEB435558E41AFA86ULL, 0x3056A459376AFD47ULL, 0x54C9EC8AAE8EEACBULL, 
            0x45F74321468FEFB6ULL, 0x9E92F4B49F8F6C77ULL, 0x6AE211E791B0CD2FULL, 0xC83FAE0C5CBC2B9CULL, 
            0xF7E4DE91B486CC0EULL, 0x0F8DD2157DF71480ULL, 0xB5F795D12111FB00ULL, 0xEC8DEF031E8BAB7DULL, 
            0xD81B72AA19E6A663ULL, 0x1B8722CC73888656ULL, 0x7CB89CE2B5E71493ULL, 0x241ADD049A2DAEC3ULL, 
            0x30B9B63332E5E037ULL, 0x8D60A29490D590E7ULL, 0x5DE969547267B1B1ULL, 0xE203CE3C707F8863ULL, 
            0xB8EC0D7FDBF81D34ULL, 0x1156F680D05ABC1EULL, 0x5E5CB3839AF83B0FULL, 0xEC071F40A8993D7CULL, 
            0xD021C8FC34308F42ULL, 0x3513791FA61D9BF1ULL, 0xC44ECB4DB1B95EC0ULL, 0x2A736DEBE360AF20ULL, 
            0xA44DC56632EF26D3ULL, 0x54E507128594A0C2ULL, 0xF12AF741C3DD0597ULL, 0x2FD074D7284B36B8ULL
        },
        {
            0x1CD720DAD96439F9ULL, 0xAACE41A5362E6543ULL, 0x40C4C53EB5D2195BULL, 0x684242D12C6A5060ULL, 
            0x414C52404422A146ULL, 0x5A462AC3A03D1923ULL, 0x895E18AFA76FB8B7ULL, 0xCBEA7E9AAB1C8702ULL, 
            0x42D9793946623B3AULL, 0x747C23CD4E6D97E3ULL, 0x7761ECC1EA8150EFULL, 0x6D877E8A6327ED5EULL, 
            0x4E8D8D22DE7314EFULL, 0x90E206E4018111D9ULL, 0x39B8F3011FF3F872ULL, 0xF2CC409B2B2C21A4ULL, 
            0xCECDF17A3AE3AD27ULL, 0x22B93D7346C63AF6ULL, 0x48F4C29EE5640490ULL, 0x4037AA86C5CA7DF6ULL, 
            0x92A0B95BF772A77EULL, 0x9F6FF7B7354FAFF8ULL, 0x0CFDF72C25AAE66FULL, 0x87B65A2330DD66C7ULL, 
            0xB8E189B43076F879ULL, 0x470E73AA4A3CA87FULL, 0xFAFFAB114B3F07F2ULL, 0xD84FFC7541FB8E5EULL, 
            0x471D644DF9A142F0ULL, 0x532BC5EA98C9D0C3ULL, 0x8966232DFF050AC9ULL, 0x5F626C210F1C49D4ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Sirius::kPhaseHConstants = {
    0xF966D28805A2B457ULL,
    0x1E27AB474E76F011ULL,
    0x2E73D762DCE7C221ULL,
    0xF966D28805A2B457ULL,
    0x1E27AB474E76F011ULL,
    0x2E73D762DCE7C221ULL,
    0x42A7FC37CCB5E832ULL,
    0x9602765E60CBB8E1ULL,
    0x1D,
    0x83,
    0x78,
    0xCA,
    0x2D,
    0x8B,
    0x88,
    0x04
};

