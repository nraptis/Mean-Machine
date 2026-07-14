#include "TwistExpander_Castor.hpp"
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

TwistExpander_Castor::TwistExpander_Castor()
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

void TwistExpander_Castor::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0x89E45E1C3862EC09ULL; std::uint64_t aIngress = 0xCEB862F8FC2F3541ULL; std::uint64_t aCarry = 0xB2DEACD621F0B29EULL;

    std::uint64_t aWandererA = 0xC891AE041F0715A3ULL; std::uint64_t aWandererB = 0xDDEAB704E3937E7DULL; std::uint64_t aWandererC = 0xBAC05072B8BE4C91ULL; std::uint64_t aWandererD = 0xF529963A72CF4734ULL;
    std::uint64_t aWandererE = 0xD997C8CC34828CE5ULL; std::uint64_t aWandererF = 0xA3A4CEDD7D5B18E4ULL; std::uint64_t aWandererG = 0xFBB62F4752247809ULL; std::uint64_t aWandererH = 0xBE5B28CF3A48A9B9ULL;
    std::uint64_t aWandererI = 0xB2BBD5E49227E980ULL; std::uint64_t aWandererJ = 0xE451B8B1C9AE49B4ULL; std::uint64_t aWandererK = 0xC862A20DA97BE39BULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 9453733418241339719U;
        aCarry = 10331373898457674585U;
        aWandererA = 12800708513289378848U;
        aWandererB = 10118221266626954290U;
        aWandererC = 14922366275308794591U;
        aWandererD = 15650068619139373738U;
        aWandererE = 12464978673078312881U;
        aWandererF = 13283524130672243949U;
        aWandererG = 16006444743600085756U;
        aWandererH = 16443245017525386372U;
        aWandererI = 15134391379462683598U;
        aWandererJ = 10009719981249940835U;
        aWandererK = 11212940182618972160U;
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
    TwistExpander_Castor_Arx::KDF_A_A(pWorkSpace,
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
    TwistExpander_Castor_Arx::KDF_A_B(pWorkSpace,
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
    TwistExpander_Castor_Arx::KDF_A_C(pWorkSpace,
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
    TwistExpander_Castor_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Castor_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Castor::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0x8D0E27FFA91443A1ULL; std::uint64_t aIngress = 0xE87DB61F58537F38ULL; std::uint64_t aCarry = 0xF4A0975E5FC8B6A2ULL;

    std::uint64_t aWandererA = 0xD8DE0726AD6BE5BEULL; std::uint64_t aWandererB = 0xFE3CE278DBC78FDBULL; std::uint64_t aWandererC = 0xF0EB0F5B97D626BAULL; std::uint64_t aWandererD = 0x94F63354B055555FULL;
    std::uint64_t aWandererE = 0xA5A9AF15A41C3C1FULL; std::uint64_t aWandererF = 0x8756396F36662DC5ULL; std::uint64_t aWandererG = 0x8B99C05E13B02583ULL; std::uint64_t aWandererH = 0xD1A82D54C26BAE0CULL;
    std::uint64_t aWandererI = 0xFC0651F144068797ULL; std::uint64_t aWandererJ = 0xDFB85062CF861391ULL; std::uint64_t aWandererK = 0xB82CCC1E52488F4BULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 12383566653141683715U;
        aCarry = 17017359640622654957U;
        aWandererA = 9309260462512800880U;
        aWandererB = 16007509508182219169U;
        aWandererC = 18390406796875071447U;
        aWandererD = 13308661568013622292U;
        aWandererE = 17898210189910984649U;
        aWandererF = 9832949651584594098U;
        aWandererG = 15653883093913957549U;
        aWandererH = 12152470120341533847U;
        aWandererI = 14683963919419136482U;
        aWandererJ = 17181485745490241307U;
        aWandererK = 15583404200857609442U;
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
    TwistExpander_Castor_Arx::KDF_B_A(pWorkSpace,
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
    TwistExpander_Castor_Arx::KDF_B_B(pWorkSpace,
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
    TwistExpander_Castor_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Castor_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Castor::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xA8756513F241251DULL;
    std::uint64_t aIngress = 0xB23E8CB9EB4B105EULL;
    std::uint64_t aCarry = 0xC91CE98D113234DFULL;

    std::uint64_t aWandererA = 0x9060FA63E6CE052CULL;
    std::uint64_t aWandererB = 0xD5F8C471E0B4BEB6ULL;
    std::uint64_t aWandererC = 0xA5A8DE291FE7CDBCULL;
    std::uint64_t aWandererD = 0xA03E2A94FD49EF70ULL;
    std::uint64_t aWandererE = 0x8FD24F94975E0A0BULL;
    std::uint64_t aWandererF = 0x8330D9E44251AE77ULL;
    std::uint64_t aWandererG = 0x9A8C88C6D3F1EED9ULL;
    std::uint64_t aWandererH = 0xF8180101CE974195ULL;
    std::uint64_t aWandererI = 0xD17D276BE35338C5ULL;
    std::uint64_t aWandererJ = 0xCE18AE550B182D1AULL;
    std::uint64_t aWandererK = 0xCD23F31EBCBF24B1ULL;

    // [seed]
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneA);
        TwistSnow::AES256Counter(aSource, aSnowLaneB);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneE);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneH);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneD);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneB);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneC);
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
    TwistExpander_Castor_Arx::Seed_A(pWorkSpace,
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
    TwistExpander_Castor_Arx::Seed_B(pWorkSpace,
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
    TwistExpander_Castor_Arx::Seed_C(pWorkSpace,
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
    TwistExpander_Castor_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Castor_Arx::Seed_E(pWorkSpace,
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
    TwistExpander_Castor_Arx::Seed_F(pWorkSpace,
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
    TwistExpander_Castor_Arx::Seed_G(pWorkSpace,
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
    TwistExpander_Castor_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Castor_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Castor_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Castor_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 16 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1827 / 1984 (92.09%)
// Total distance from earlier candidates: 27815
void TwistExpander_Castor::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 744U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 2014U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1430U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 52U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1227U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1137U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 685U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 398U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1084U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 64U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 739U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1176U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1820U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 343U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 18U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 387U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 140U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 670U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 24U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1693U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 295U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1624U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 257U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1981U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 274U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 291U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1055U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1608U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1818U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1988U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 864U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 657U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1556U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1462U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 230U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1643U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 304U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 424U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 933U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1726U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1734U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1740U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 60U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 589U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1319U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1962U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1286U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 336U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 5U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1135U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 828U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1272U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1910U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1035U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 2011U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 796U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1500U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 773U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 44U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 2007U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1400U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1331U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1931U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1082U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1574U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 197U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1252U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1377U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 2024U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 706U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 3U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 158U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1772U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 188U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 972U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 603U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 233U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 982U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1906U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 477U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1148U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 472U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 338U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 651U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1954U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 640U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 2032U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1410U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 789U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1143U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 783U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 812U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 593U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 754U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1600U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 2029U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1194U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 379U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1122U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 36U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1898U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 193U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 652U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1957U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 169U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 27U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 199U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1229U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 725U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 204U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1315U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1423U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 702U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 767U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1506U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1317U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1239U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 831U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 2027U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 134U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 751U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1944U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1953U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 786U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1975U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 770U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1948U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1815U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }
}

void TwistExpander_Castor::TwistBlock(TwistWorkSpace *pWorkSpace,
                                       std::uint8_t *pSource,
                                       std::uint8_t *pDestination) {
    TwistExpander::TwistBlock(pWorkSpace, pSource, pDestination);
    if ((pWorkSpace == nullptr) || (pDestination == nullptr)) { return; }
    std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    std::uint64_t aPrevious = 0xC2EB1B439D0ED33AULL; std::uint64_t aIngress = 0xC0D4F4DEBD2724E5ULL; std::uint64_t aCarry = 0xE2365BA265316832ULL;

    std::uint64_t aWandererA = 0x878881967D92822EULL; std::uint64_t aWandererB = 0x8480AE7B6661597AULL; std::uint64_t aWandererC = 0xFDC1D0C602E3F1FDULL; std::uint64_t aWandererD = 0xB5A4915D96920AD9ULL;
    std::uint64_t aWandererE = 0xADCEA0A366B7E135ULL; std::uint64_t aWandererF = 0xCE5DD57FCAE48772ULL; std::uint64_t aWandererG = 0x85F972EE936CB13AULL; std::uint64_t aWandererH = 0xFC9172AA40AE860CULL;
    std::uint64_t aWandererI = 0xA136ED19D636D976ULL; std::uint64_t aWandererJ = 0xA0FC7BC3B6C33A6BULL; std::uint64_t aWandererK = 0xB6C05A4C7672975CULL;

    // [seed]
        aPrevious = 12171922789975262508U;
        aCarry = 11016605263497172334U;
        aWandererA = 13365185376606318243U;
        aWandererB = 16304789485702254844U;
        aWandererC = 16585094196973794117U;
        aWandererD = 11553472519268941637U;
        aWandererE = 12576119076708166363U;
        aWandererF = 9834068355280817700U;
        aWandererG = 16703879339818526287U;
        aWandererH = 17184838616798310570U;
        aWandererI = 16651353419745914633U;
        aWandererJ = 13387608267341686465U;
        aWandererK = 15365207407995365425U;
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
    TwistExpander_Castor_Arx::Twist_A(pWorkSpace,
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
    TwistExpander_Castor_Arx::Twist_B(pWorkSpace,
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
    TwistExpander_Castor_Arx::Twist_C(pWorkSpace,
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
    TwistExpander_Castor_Arx::Twist_D(pWorkSpace,
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
    TwistExpander_Castor_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Castor_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Castor_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 16 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 8207; nearest pair: 515 / 674
void TwistExpander_Castor::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4733U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6947U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2120U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 8143U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6712U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6603U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7473U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6962U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4735U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6160U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6172U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3086U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2965U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7724U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7709U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5628U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1653U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 513U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1835U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 820U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
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
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 339U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 22U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 485U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1839U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 200U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1679U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 73U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1178U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
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
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1884U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1347U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1060U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 746U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1284U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 163U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 947U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 702U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 16 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 8225; nearest pair: 502 / 674
void TwistExpander_Castor::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4990U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1232U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7442U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4652U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5630U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6760U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5025U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2783U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 543U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5470U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6611U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7289U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3268U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1416U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4107U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 269U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 281U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1696U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 185U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1964U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1756U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1580U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1745U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 568U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 837U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1181U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1363U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1958U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1091U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1647U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1987U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1872U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 315U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 513U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1490U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 903U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Castor::kPhaseASalts = {
    {
        {
            0xF8A82520FA9EEA49ULL, 0x8BA2598C072A3193ULL, 0x2124326908450778ULL, 0x85E8CB2ECB59D95FULL, 
            0xD42B55D62C81244BULL, 0x1053BE93385ADBF5ULL, 0xE77C9ABCF31DE53BULL, 0x2539FA25261F6595ULL, 
            0x27BE5D0AB0CC3703ULL, 0x01B868C81DB6F751ULL, 0xF43015C8EF311BDFULL, 0xFB40C9D0FDD83102ULL, 
            0xD0234BE10E405252ULL, 0x4EE8500302E4C612ULL, 0xFF4A3EC0E028C420ULL, 0x0721774DD9FC875FULL, 
            0x57052D4B398E2736ULL, 0x93FB187DA44B6F40ULL, 0x3ED0B4F972542123ULL, 0xD913533A93DDA7D1ULL, 
            0x52BFA6F536B1C23CULL, 0x335D128026672C3AULL, 0xB10B2B0E067E1895ULL, 0x6213BBC8861925BCULL, 
            0x9E4C37397407BF37ULL, 0xDB8A7D198001A1BFULL, 0x98436851710862DFULL, 0xEB5BFDCDEA7F0EB2ULL, 
            0x3AC6A3893A3B75B9ULL, 0xF891640017D03BEDULL, 0xAB7AB1545DFCE08CULL, 0x96A7FD433254C2FBULL
        },
        {
            0x42310FD80E881891ULL, 0xD745BC10156D67E5ULL, 0xB5D36941A3711963ULL, 0x8DDB7BC9518D615CULL, 
            0x5ED3F7B41A273302ULL, 0xD4A2D0B2FD78E0C4ULL, 0xA562F24874A73447ULL, 0x4FC848E63221F690ULL, 
            0x4E42F75A2D4EFF11ULL, 0xD09BAD0471EC0D79ULL, 0x7F43F31AA5734795ULL, 0xDA3464E58058D4E6ULL, 
            0xB27D4CB8FEBE371FULL, 0x51EC797DC625D110ULL, 0xBDFD20F752A998CCULL, 0xA811C289A6698856ULL, 
            0xF1E7A099687ED48DULL, 0x1B5293CCFCD15CE0ULL, 0x12F76D1B0A616EF5ULL, 0x1161012EF5D3A2C4ULL, 
            0x97381DEDE601BDD9ULL, 0x506D2AE069B5EDE4ULL, 0xC6CB00EA87EB9C34ULL, 0xBCD17315A4C083B8ULL, 
            0x38589316F61FAF24ULL, 0xAF4041E4F4A36C3FULL, 0x9DE6A26E857AC201ULL, 0xD221E34248DB90D3ULL, 
            0x7EC69B8E32F320D4ULL, 0x118F1A1FBB6EF13FULL, 0x19DED6FB2E77F8C0ULL, 0x2B941C6753CDE269ULL
        },
        {
            0x59403EC64BF9B616ULL, 0x483289BD9B2D112AULL, 0x4256E8C27B5304CAULL, 0xDD83D5518FC04C1CULL, 
            0xCAE3157DC91034E8ULL, 0xC98031C44615E779ULL, 0x66F68A7AF34FA87EULL, 0xD6AC6365D4AF25C8ULL, 
            0x542E3D946A0D0E9BULL, 0x5121296DE8EB7AC2ULL, 0x5EE26A21A17B52A7ULL, 0x04C1E238746488DFULL, 
            0xD9F329FAF150C3E6ULL, 0x6F79377D29046407ULL, 0x7B0F0E5CC9F260FBULL, 0xCDBBE8BDF39F22D7ULL, 
            0xA10354A27091AE39ULL, 0x7EB766771842E02DULL, 0x789730E50F927916ULL, 0x07C0CDA841E2C7DFULL, 
            0xBDBB2F01134DB027ULL, 0x34936C563B74C40CULL, 0x0AD4111CF9C3EAC1ULL, 0x827826489E5A75AEULL, 
            0x4FFA8833F1E3F725ULL, 0xE9B05956D5B33FFEULL, 0xF997C0C12CFBE774ULL, 0x01E918068A7828ACULL, 
            0x64360FF4549B045EULL, 0x7C2B9B49E0250785ULL, 0x6D465E4D74DE6E30ULL, 0x808C3FF4BAF9B2C5ULL
        },
        {
            0x30FD4B691662BF1DULL, 0x425D47AE450AAA34ULL, 0x61931DE31980D129ULL, 0xF55EB37169B58ABDULL, 
            0x95F73B941F9DD92DULL, 0xB720E9ABC801A835ULL, 0x6DE102C01619C083ULL, 0x0A4553AC8C10417BULL, 
            0x83C00CC3C3D368DBULL, 0x355FC52E18C7718BULL, 0x19CF6E5857CC8520ULL, 0xED2356FBE6451E46ULL, 
            0xAC79BD3FE543B39BULL, 0x9FED3FB416008AEAULL, 0x5D4580AF2297FB43ULL, 0x8F92599F422B55B6ULL, 
            0xB9F8AC7CE04A9E5EULL, 0xF17A2C2663C3FCDDULL, 0x11BA7422C7034E9EULL, 0x2E6333A1C7EA49F2ULL, 
            0x410DBD391C87AF27ULL, 0x24DD6281D64A1C58ULL, 0x35509A43FA45A767ULL, 0x6ECE16521183878EULL, 
            0xB51639375F8E671AULL, 0xB53965A4E8BEC02BULL, 0xFFC8919856D6EC3FULL, 0x23FD568F55EBD117ULL, 
            0x61190FC67272AC85ULL, 0x072B8D8071A51BC5ULL, 0xCAC2D79DF89B86D1ULL, 0xC83CED608DBF7CFBULL
        },
        {
            0xAAA1099E8CF42E27ULL, 0x5D27CB817D2EC711ULL, 0xD9C194E1130CCE25ULL, 0x91FB062D6AEF1B02ULL, 
            0x8E16A1E5A8380657ULL, 0xEFC48877C12F814DULL, 0x9ED9BB9B6D55CD7FULL, 0xE2C75172A3702299ULL, 
            0x50E334ADE51966C0ULL, 0x687ABB5AB0A028ABULL, 0x680866DA6CD09A95ULL, 0x6DEF1A634C312787ULL, 
            0x73DBE4CA35370219ULL, 0x6F5E78370B3291C2ULL, 0x46FD78DEDA66FD47ULL, 0x0F645BC57ED9BFFFULL, 
            0xC9F5DE9F5629978DULL, 0xA338F8C0F1A3BB81ULL, 0xB650905C9208999CULL, 0x62DFA81460EB6B8AULL, 
            0x9FDE098FFA6691DDULL, 0x525B3EC43BF0F729ULL, 0xDEC1FEC8389649B2ULL, 0x2E94E7A658E46F82ULL, 
            0xA92091E4E48F26A0ULL, 0x4AC6ABAFC4615194ULL, 0xC71313FA497E7ED4ULL, 0xF7E2D875B2FBF836ULL, 
            0x252DB61DBBF29BDBULL, 0x3A12EDE77E0F28FFULL, 0x06CAA4018CCD6FB2ULL, 0x3C3E5C9185346C3EULL
        },
        {
            0xC6E784F3CD166FD6ULL, 0x48AC51DB983B1AFCULL, 0x80A30EE528472140ULL, 0xF427DA7099D7DA44ULL, 
            0xC809BAAC7DFB62E7ULL, 0x98B0596975564E85ULL, 0x7B7E46A6F56222EAULL, 0xCDA462D2C5E78613ULL, 
            0x1EFAAB129D607EB5ULL, 0x0DC2C9EA50FB62FFULL, 0x37B706AFAE856C1BULL, 0xED3F0AE2A7E27436ULL, 
            0x9F1EA3FE4CF21681ULL, 0xDA398AFBB18D572AULL, 0x935F733F69145C3AULL, 0x0EC4D39FC437F352ULL, 
            0x36C9A71AFA68FDAEULL, 0x060416AC3E1A53E0ULL, 0xE41167A451FB5282ULL, 0xFE2FBE92F004553AULL, 
            0x6AE9344E0A7BFAA5ULL, 0xB63387EFFAEF6BEEULL, 0x7FB4486E3EA1353FULL, 0x3C9A4BB47E0A875CULL, 
            0xA45A0B45BC1182B0ULL, 0x41ECD28021E8BE29ULL, 0xED1EDF4185DA82F7ULL, 0xDE1060F11FE2D937ULL, 
            0x617FB899185C9C06ULL, 0x1184D8CDFBAF689BULL, 0x565EA73FED0ADC12ULL, 0x439FE563C983C829ULL
        }
    },
    {
        {
            0xB7688599628AD6D5ULL, 0x8C5EA4534D78E8C2ULL, 0x6AF0DC5151D60A64ULL, 0x3340E6CE8CD29A97ULL, 
            0x78ADDD9A68D32753ULL, 0x6AA050D4FD5A0EFDULL, 0xE571301BC9EDD74BULL, 0x20C29D36BA829CD3ULL, 
            0x6FCAF39A5D5611A2ULL, 0xCBEF2DD3CAF7D244ULL, 0x695AF71AD2579228ULL, 0x0F1EED6035F04122ULL, 
            0xDBBCA82BDDC8015FULL, 0xDDE30512F7034BCCULL, 0xC0A4A46E530057B1ULL, 0xC0DF4C18970186CBULL, 
            0x439D0BAEFE38BD26ULL, 0x8604304C9E3B565DULL, 0x20DE40E77CC2F37EULL, 0x4FC8E86A296A888FULL, 
            0xFFA47A20164A921EULL, 0x07F30A2AFF354C56ULL, 0xD5B8C6D759B4FCDDULL, 0xE28B11F3AE7A961FULL, 
            0xB9DE0D8C18AD2533ULL, 0x6E9089516173AB24ULL, 0x681E0F07EC139F0DULL, 0xCCB6E7F704FF516AULL, 
            0x3F8B28635388D394ULL, 0x9D66B2530C555D15ULL, 0x5248D4FD0F575B6DULL, 0x716B6F662ABF5403ULL
        },
        {
            0x9E843BDC29128615ULL, 0x7A1D2ABBF6DCCCC1ULL, 0x508F8D72106B6E3CULL, 0x0332522975F13296ULL, 
            0x17B92AEA895D49D1ULL, 0x09811DCD0565C644ULL, 0x608B30813EC71B13ULL, 0xAE7ED13E247BE43AULL, 
            0x6A0A4795472E47BFULL, 0x00D0599D5AF4AE48ULL, 0x8A7595E9AE9E878CULL, 0xE5CF98808B7E00E3ULL, 
            0x9D50524997BCEF23ULL, 0x788EEE621682B6F9ULL, 0xD961CE9B7562A8EBULL, 0xF44558784D0873D5ULL, 
            0x1AA464464C0A0442ULL, 0xFF83C58A16DFC3FBULL, 0x8B634E92794BB2BCULL, 0xD664027227436F11ULL, 
            0x6135749DBA97E924ULL, 0x976A5383F76A9DAAULL, 0xDFC26A8214719C57ULL, 0xFE758E9464557B94ULL, 
            0xE536576A60E6F8A8ULL, 0x4C43C8E26EE31E93ULL, 0x835F472F72B56225ULL, 0x6161D6FAE6157F64ULL, 
            0xC08CC67FEF5634DAULL, 0xF774C253DC75A19BULL, 0x5E6EFEC0092D5E33ULL, 0xF4DE7C2B9A62A011ULL
        },
        {
            0x16A8974905F9716BULL, 0xBBBA1B170B8ED227ULL, 0x9F9F54B2B9D5DC6BULL, 0x81DC62E5D5292CA8ULL, 
            0x2A16F581E8DF34C2ULL, 0x04DEE6AC83EFB685ULL, 0xBBE1541067D5E5CEULL, 0x0A31BC120CCF7707ULL, 
            0x178E99D9F8A83F4BULL, 0x78FCEAD989A23843ULL, 0x256A58619FAEB613ULL, 0x906E03DC1209BEBEULL, 
            0x6B8417855074DF6FULL, 0x0DB2E8F2CA39CB29ULL, 0xD47B20AA37E977E5ULL, 0x6CCD002623451C22ULL, 
            0xD35D69E90170E232ULL, 0xE98F02ADD65F6141ULL, 0x4D81CDAD6F106AFBULL, 0x2BE410B431775394ULL, 
            0x3A1343F99F539F7AULL, 0xC4B4EC1AA214BDD9ULL, 0x9845D0C8799E0DBCULL, 0x40ED379178C2694FULL, 
            0xD8F8103915F34047ULL, 0x25979AE17B0CEDA0ULL, 0xEF78D7B262FFBFEEULL, 0x839B9578BF780683ULL, 
            0x3D960A7473402E54ULL, 0xBF34F10F0E773639ULL, 0x3BCB8085363501A2ULL, 0xCA770CD43759C0A3ULL
        },
        {
            0x8AD3EB9CB52BDAF9ULL, 0x091F81A7EC98A811ULL, 0x1D0E5F2BBAB16F0DULL, 0xFC1DB3E585AF36D7ULL, 
            0x26725EDC67C74A60ULL, 0x549C7CA79E7C3A93ULL, 0x6A60D3715C6F102EULL, 0xA2F8EA20CE7C790AULL, 
            0xA13D146D2A065A21ULL, 0xE996E9E156A52BB2ULL, 0x4268A995860786F9ULL, 0x8C77B9629E4DDD7BULL, 
            0xD7E83921D6299539ULL, 0x0CF174758D0909DEULL, 0x341F008B9D480E59ULL, 0x85E6462664B6B597ULL, 
            0xA9A3D6280C1C31A8ULL, 0x9512B11022DDB7C2ULL, 0x93AB9373AE5A85E2ULL, 0x6961305F1AB8367CULL, 
            0xD4A85D03A4DB0F1FULL, 0xBF0252135396681BULL, 0x1ABFA1205E9404CCULL, 0xC17F4DFEF5A52D01ULL, 
            0x4FD670304248BBD0ULL, 0xAFFFA734B47FC6FEULL, 0x1DCC73F7D3EA3636ULL, 0xA6822E69688B1044ULL, 
            0x0007116936C77F07ULL, 0x61510B85FD44417DULL, 0x28383285A0551932ULL, 0xCCAF79EC3C3863D3ULL
        },
        {
            0x9184DC9E734CDB3BULL, 0x71CB4789032F1D5CULL, 0x98AB95BB2F57753FULL, 0x65B9E0B18C053CCAULL, 
            0xD371E624237DE3D3ULL, 0x1C4FC4D00E290853ULL, 0x97AD61B1AF65E720ULL, 0xA9202F63EBC587AEULL, 
            0x1765BD502BAF1CC7ULL, 0x6A32C492B3CD378CULL, 0x4958AFF4E1C5B459ULL, 0x0EF3DE40315601E9ULL, 
            0xCD17A62F4BFC3773ULL, 0x0EF4B328F40CEF7AULL, 0x62DCAAE69E014962ULL, 0xD738A4CBB95E12B6ULL, 
            0xCBA0CA985CC28B70ULL, 0x249CADD7C0344A9DULL, 0x2B1FF9AA6DA84397ULL, 0x933FC78CCD071DA9ULL, 
            0xF357ED2C90BFB612ULL, 0xA2CA05A1D2ABC8C4ULL, 0xD0C9199B3E0CB2FFULL, 0x42E90A4779AA5E62ULL, 
            0x6C0526307785E07BULL, 0x95C0476DD2AF4B57ULL, 0x89CD9B53AD1C6C67ULL, 0xAFB33C5F41B9DBDAULL, 
            0x10C33B9AA3B1BC11ULL, 0xD2108F8DC8C5498FULL, 0xA352C26B6213EFACULL, 0x9B93D5703556229AULL
        },
        {
            0x49F9F9B95C1F5C5FULL, 0xF447593938E256C0ULL, 0xBD63C560253793DAULL, 0x5D77A8EA03500B27ULL, 
            0xD1891C09A631BE9AULL, 0x799591A38319CBB7ULL, 0x6A0637A59B37ABFCULL, 0x71EC5841AB2DCFE4ULL, 
            0xECAF783629C73AD1ULL, 0x20C3494510812E1DULL, 0x8CD842C73ECFE3B5ULL, 0x57F005C6B25557E6ULL, 
            0xDAB838A6867709DBULL, 0xD63A266C4198B423ULL, 0xA9943CEB79DFD1CAULL, 0x6DE017CCB1E082A5ULL, 
            0x289C4C2150D610C4ULL, 0x2D09A10BC50985B5ULL, 0x823DA6A21949BF0EULL, 0x1153BC0D25468E58ULL, 
            0x76D8774B110756CCULL, 0x9AEC1C10BF6AE2E6ULL, 0xC15D27355E8A6E32ULL, 0xA2B5CF0DAC6B26C3ULL, 
            0xB2D77C27FB650D9AULL, 0x542AE1DEE21EB9DFULL, 0x251B98DC5ACDE673ULL, 0x3F0E88D878F189CCULL, 
            0xC3BF61B3E88F6E51ULL, 0xD3A2E8E3CF1CA5E4ULL, 0xA1201705F0F9DC9BULL, 0x82CA86A0B1C23E71ULL
        }
    },
    {
        {
            0xE03EDA0D1CEB89D5ULL, 0x26BEAEE6AD4CACEFULL, 0x76EB51F6931DBE68ULL, 0x85997CF6191FD5B2ULL, 
            0xF795D67883D0C99EULL, 0xC11B71B71C1ECC1FULL, 0xBB5BC205118F8C62ULL, 0x7EB6F4C6FAF0CDE8ULL, 
            0xABF769F6249084ECULL, 0xBC4D0C2C4C425849ULL, 0x9671D13C3203C38DULL, 0x454F2ABD0FA3EDFFULL, 
            0xBCACFAD82129D9F7ULL, 0x76C7611F7DA586EDULL, 0xCC73461979AB59DEULL, 0x6E2F42890F36B4ABULL, 
            0x0ADBF3F8289D588BULL, 0x39E9AF2043D356DFULL, 0x63FEC2236F4D53D5ULL, 0x44829C81500E6C00ULL, 
            0x0D9543F2EF3EE480ULL, 0x4D18E45D1ACFB282ULL, 0x95DA9BF22B3F4803ULL, 0xA6D7632AB0FCFEA0ULL, 
            0xDC4D90FF1C047D4AULL, 0xC2851A230AA6583EULL, 0x8535404DB4EBD516ULL, 0x7654AB77EFCCBDC9ULL, 
            0x0160ED572B834D6EULL, 0x6B9251A5BC084661ULL, 0x7B72C3658A40BAFAULL, 0x7300B45D2AF5DE42ULL
        },
        {
            0xDA18D6A81697AAF6ULL, 0x8BF91A617ADBDAEBULL, 0xCC4296E3E85877E0ULL, 0x4BF8EB19EBC1753EULL, 
            0x7A86649FFE72B1D8ULL, 0x671B5F598077ACCAULL, 0x97578700040B420FULL, 0xF2033D5EF2CEEE65ULL, 
            0x421BED0871845136ULL, 0x4E3DC0D2A1151494ULL, 0xCCD0ACDE22756B69ULL, 0xAD1CDA34AC97AEEAULL, 
            0x2CCDEA48599EEEDEULL, 0x41CE11740BEA0549ULL, 0xF8DCE06B9AB1E836ULL, 0x93B172AD03CC2A00ULL, 
            0xD71AE07DED04EBC2ULL, 0x57854F9277CFA77DULL, 0x3B317CD46FB2098BULL, 0x7C528807EAA57A37ULL, 
            0xBAC50C74A5F16648ULL, 0xCA71192FDF5DDC94ULL, 0x0FE1A0437F07EDD0ULL, 0x6414A6AAAB42561AULL, 
            0x7F0F7CABD33032F2ULL, 0xC4A5448CB9CBD58EULL, 0x81574BDEB97AA34EULL, 0xE53D9D85F6FF531EULL, 
            0xEA05577A3DA41549ULL, 0x8B55DF4623FB93F0ULL, 0x886F6ACBD00F97A2ULL, 0x33061B3F6A3DF8DDULL
        },
        {
            0xC7EB1C7DE55E3170ULL, 0x5772DC6BC480B133ULL, 0x052FB3688E9F8C10ULL, 0x1F1A5DD41EB9F31FULL, 
            0xECC3C41F37E14031ULL, 0xA2ACA9E0C5458764ULL, 0x72E7272F4A3E5E16ULL, 0x28CF816C7C939118ULL, 
            0x0A6C8443924CC3B1ULL, 0xB4111D162F0B2BE4ULL, 0xA372DA8595ADE625ULL, 0x1BC4D6CA215CA417ULL, 
            0xEACD6D98A8FDF429ULL, 0x9E60A4EAFF74C4AEULL, 0xF79C022AF8B098AFULL, 0x2083D9DDE8D7A831ULL, 
            0x8037F031E7B6DF17ULL, 0xC818998019CF6A64ULL, 0xFF169FB2AEA0F264ULL, 0x0C35AD302EA653BFULL, 
            0xDEAFD71621FA8D51ULL, 0xD622BE5CAFCA2DC5ULL, 0xD3F929A938807F1FULL, 0x425FAEFAA0E5BE4DULL, 
            0x2C5B614BBD0B4E1EULL, 0xDDFCFD25C5211575ULL, 0x803D5076A75C3F79ULL, 0x07D0FBDE36B0713BULL, 
            0xFD13F6148D23AB5FULL, 0x4FFF9A9947B1853BULL, 0x5E09F63ACE0B163CULL, 0x5AC16E4D63A980E3ULL
        },
        {
            0x8B01D80ED36BF1A1ULL, 0xACEEDF99AFA2C15DULL, 0xC74D62D71BBFEADEULL, 0xCBCC102AEF87B3EAULL, 
            0xE0CF7EBAD5318B6DULL, 0x184D1152F9E9CD32ULL, 0x9FE6D97E93F1F080ULL, 0x249A3D3D257E767CULL, 
            0xAE889B79615328F9ULL, 0xD5B581FD0BBD874DULL, 0xD3BD1710A5B29621ULL, 0xCC342A38B90EA039ULL, 
            0x1A0B6FF2FB9DEE3EULL, 0x62A682BB4754C09CULL, 0xE1ECDB3313755D75ULL, 0x5CB1161E4FD11CD7ULL, 
            0x5885DA78F7EC9A88ULL, 0xF37BA50B98D75809ULL, 0x568A25388832687AULL, 0xBE75C2E6BBD1047DULL, 
            0xAD3E9DBD5508FD14ULL, 0xC7C045055421D514ULL, 0x73E66FBB828697CDULL, 0x35B9555ACCECAE6CULL, 
            0xF65A48B46190ABCEULL, 0x39D17982BB227260ULL, 0x05A77F489667B28DULL, 0x8B6A3CE7726B4382ULL, 
            0x58358B93B1346586ULL, 0x4DFB510E7E9B52E9ULL, 0x23F21631FB02B965ULL, 0x0647CFF52CEABB50ULL
        },
        {
            0xC540955DF839690AULL, 0x5D37F860F172D9CFULL, 0x79ED42F6367BA213ULL, 0x355E88F1078F3CF3ULL, 
            0x21201A69DB3716C8ULL, 0xE873CBF8CE51DFEFULL, 0x6EB7AC161CC2CAA2ULL, 0xF2122D91FCF66FA9ULL, 
            0x8CDFB71E9F972A5BULL, 0x9CF635462E24D9BBULL, 0x1A7E6B8F33B21D9DULL, 0x4659959C5900324CULL, 
            0x9D3BAF6C63862BF7ULL, 0xB98F3B6B286DC8E6ULL, 0xEF60EFD6AA83B45CULL, 0x78CB46B2082CCA2BULL, 
            0xD4D591B592AA183CULL, 0x2DA8FB1069EB5161ULL, 0x26F9AB179B0E4F70ULL, 0xD061999FF0999BBBULL, 
            0x56CC2C53976FEEAAULL, 0x276D135272C5ED5AULL, 0x5669FDE234CC637EULL, 0xE0CAA0621CE9C4CEULL, 
            0xAB8919267F7AC6FCULL, 0x4C09B15ADF4F83E3ULL, 0x77AE7D4DFE4977E6ULL, 0xA610044DBD30340DULL, 
            0x9A0A09E0B897979BULL, 0x70D26F8C430E709EULL, 0xBA283533C48E74C5ULL, 0x03058500E4D4DB25ULL
        },
        {
            0x21539E27961213ECULL, 0x7FC62933B515933FULL, 0x41769345F950B381ULL, 0x2B0714B6F5E5932BULL, 
            0x5862F8CB18A15AD2ULL, 0x8BB34635B79605BCULL, 0x93A7ECD78AE96193ULL, 0x789DF38915B76B14ULL, 
            0xFA7A722B90FB6A5CULL, 0x7FC244643974E18EULL, 0xBD846EB826C08605ULL, 0xCFA4D2607C0EF344ULL, 
            0x5741A151ACF69DEDULL, 0xDFB95D51B8355409ULL, 0xF2264F0A88FBBCBCULL, 0xBD00B83889A4877BULL, 
            0x82594BC66A7A3FFDULL, 0xFF6961E5564800CAULL, 0x01FEDC4E6A861599ULL, 0xBF9E4B879A77F5D6ULL, 
            0xBC4F853828D6C05AULL, 0x26DC4A9B549A4855ULL, 0x39B987089C857BD8ULL, 0x23BF969453174D63ULL, 
            0x6A2842DA13256511ULL, 0x8D7E310ADC41A4FBULL, 0x25D3FB726B05DC28ULL, 0xB9ECC854EFDE2788ULL, 
            0xEA390E7C53B3A494ULL, 0x15760DC347A772FDULL, 0xFE667804BE880B6AULL, 0x3829CB7186D95BE1ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Castor::kPhaseAConstants = {
    0xACFB1350CD66F8AAULL,
    0x896603FDE062A590ULL,
    0x7B9311E83F356704ULL,
    0xACFB1350CD66F8AAULL,
    0x896603FDE062A590ULL,
    0x7B9311E83F356704ULL,
    0x2A8BBF969D65C860ULL,
    0x34976608DFE0322AULL,
    0xB0,
    0x07,
    0xB5,
    0x3D,
    0x3A,
    0x76,
    0xC5,
    0x47
};

const TwistDomainSaltSet TwistExpander_Castor::kPhaseBSalts = {
    {
        {
            0xD3CC78EEA403E69BULL, 0xA0613BB32CDC2B1DULL, 0xE4C2DA37CA1787B2ULL, 0xC5CE93C0F7C4E651ULL, 
            0x11BD2DE6F9A74366ULL, 0x5807E1E4FADC0926ULL, 0x248ED245149FE5B2ULL, 0x14A19B7D72736FD7ULL, 
            0xA4D7BB2AAACB5698ULL, 0xDB2BFE443426B16BULL, 0x5601C56ABDB43A15ULL, 0x38818D733AE288EDULL, 
            0xD3E6037623331CDBULL, 0x9D21D21393B03A3EULL, 0xF58DDD2B94C3B294ULL, 0x3FCA54EE907ECD06ULL, 
            0x488DF1D62D15890AULL, 0x53A41CD98C8E3032ULL, 0x3F6B6860D522A589ULL, 0x099397181A721609ULL, 
            0xA4DF69873952F877ULL, 0xBB6A37B5E733171CULL, 0xA4935122871574C6ULL, 0x622E9DE4034F2ACAULL, 
            0x2D44491965456403ULL, 0xAAC7DBB33BB6DCCEULL, 0x9EC0784DFD6BC587ULL, 0xEB2960A94F0BC20AULL, 
            0x5F3DACFD578C7CDCULL, 0xCB8D854FA2AD4710ULL, 0x7F7FD3DB368BC486ULL, 0x0F6A0DB02B3C9EAFULL
        },
        {
            0x68C727E46CF34307ULL, 0x54371FE36D5E012FULL, 0x71B8076A4AE58589ULL, 0xA6C55E12990B0EFAULL, 
            0x6E7DA0C27D36A370ULL, 0x0928797420C0FDC8ULL, 0xB6CC3C470894143BULL, 0xBC4D1096A14223BBULL, 
            0x489C8A92AD53D661ULL, 0x2BD3905CA6987C5FULL, 0x960EFB0A11233EAFULL, 0x0CB414EA6CBE4DCAULL, 
            0xAC06EC1B73B160AEULL, 0x7EAC5C70B8E1BC45ULL, 0xB2AC6FAE555F09F0ULL, 0x290D4C16F9612366ULL, 
            0x44C709062384E9A6ULL, 0x05443D3FD11A4558ULL, 0x4AC2FD97DC9D6C4AULL, 0x2AF724ACFF195009ULL, 
            0xB0E6F72E7D993023ULL, 0x400620D48B75FF85ULL, 0xF4FC3F60E79670EBULL, 0x5A3E25313C1E33EDULL, 
            0xBAD3DDB879B46C2EULL, 0xF19277FA3112DAC8ULL, 0x070044341505D410ULL, 0xF7815ADFC3121F8EULL, 
            0x2314B2E4F5A52DDBULL, 0x7D37AFE4A27FCD24ULL, 0x1DAA78CBAB105CBAULL, 0x2C96F20882BD8D06ULL
        },
        {
            0xFEABA50912C2D143ULL, 0x08A43E4B807AB7B1ULL, 0x9031B2116EF38BAEULL, 0xD2FEAC6D61B95B18ULL, 
            0x7C0655CB9E8058DEULL, 0xE17ADF4824F34355ULL, 0xABF841B83D93AAB5ULL, 0x874C7495A2952241ULL, 
            0x6FE6D29AF115064AULL, 0xCA03FA5B5944C717ULL, 0x517B8B8D826F83CFULL, 0x2B03060CE01E9ADCULL, 
            0xD679FB9F3B56321CULL, 0x6DA212756C623E14ULL, 0xFE7F22E48D839B7DULL, 0x32858A4DB50EE5D3ULL, 
            0xA0C8E40A76AFEC02ULL, 0xAB35CFDFBBFC2A8AULL, 0x003CFE6C8F4025C8ULL, 0xE0D2CE2C454F7974ULL, 
            0x78A406CCC063C01FULL, 0xCB96D2854136DE4BULL, 0xDA8969AF57EE0712ULL, 0x043CF1C082E82578ULL, 
            0xB4230908A19A4E74ULL, 0xE149EA4C40C5AEF7ULL, 0x2EEDB49ECAA91F3FULL, 0x5785DB0E04823E67ULL, 
            0x6B4EF81F95FDC953ULL, 0x2D9EA8C5A1BB576FULL, 0x8C2FD5D303C5C69EULL, 0x3BE6DD3560E392A4ULL
        },
        {
            0x0E366F980A845B23ULL, 0x03C491DCBE2CE9DDULL, 0xE73970E4F1718EB5ULL, 0xA87AD90099A022E4ULL, 
            0xC918BF90D989776FULL, 0x1F87F65C58B71806ULL, 0xBAE4BBCCA4082988ULL, 0x2236E12405CC94D2ULL, 
            0x35617FCA2802D133ULL, 0xFE3C5916FC8F056AULL, 0x4D07CF5F7EABDABBULL, 0xF473971CD058F0E5ULL, 
            0x4BF040A003564AD2ULL, 0x4493623E4823F0DEULL, 0x3E48BB730417A740ULL, 0xB4CF5652213DC25AULL, 
            0x61044B94172165F2ULL, 0xE076FBA1FEEC9ABEULL, 0xEF77BE3A27A84775ULL, 0xDFF8188BB9CE2B34ULL, 
            0x8961EFB1EE962BDAULL, 0xD6F9CB5F4265FBD7ULL, 0x0AAFBF371877D7FDULL, 0x2593EB23D3CAB3D4ULL, 
            0xFA86633DA383AF3AULL, 0x5CB5AEE6BF4DB60DULL, 0xD1F5D7B7E312C184ULL, 0x510B0CBA88D95672ULL, 
            0x3795D21C9D9151E7ULL, 0x9EC3E5198FFD41B8ULL, 0x52B478EB39B871CBULL, 0xEDD1FEDCB2E2605EULL
        },
        {
            0x458EA4242B0CB92EULL, 0x13A3400873B3C7A5ULL, 0x5591EDB974E15918ULL, 0x4D789FAF807CCF7EULL, 
            0xE37C678BCEB2B4A5ULL, 0xF6A198A16996AB67ULL, 0xE9F871ED2CCD1EA0ULL, 0xB533633C68C6213AULL, 
            0x605320D63D103B46ULL, 0x384AE7B88B6A8F2CULL, 0xA0CDE417963836BAULL, 0xE2F5463E514F89F5ULL, 
            0x00E3C6F8BA3E018BULL, 0xB8B0CBF130CFE40FULL, 0x10FE0B7036AF0C28ULL, 0x242D94C8A6464610ULL, 
            0x4C252392158CCB1CULL, 0x30828C9EA9CAA00FULL, 0xDED7322859F5E524ULL, 0x5E69F167C98D628AULL, 
            0x100D0F8B5DB6CF94ULL, 0xE4F55FB0F05A9BC9ULL, 0xBB0542C18E75D21FULL, 0xF0120ADCF4356548ULL, 
            0x01EDFF6B5169ABBBULL, 0xEB1769EB4EBD3818ULL, 0xE7E4A7AFD6F11485ULL, 0x2FE4EC4162FC08ABULL, 
            0xE9EFF59032330FDFULL, 0x126E2EB5BF36C656ULL, 0x2831B38A50DC7A6EULL, 0xBD15B61EA460D1C6ULL
        },
        {
            0xE90032CAD0FBCCCAULL, 0x5221F30DB15C7E67ULL, 0x01152A692C8C80BFULL, 0x1ECBFFB9293B3539ULL, 
            0x591727BE9FF92600ULL, 0xDB824A7CB1429C7BULL, 0x0E85E34480B0B131ULL, 0xF9F25C3C306E5543ULL, 
            0xA0B7C0C0C67F4738ULL, 0xBC62094ED90A95BBULL, 0x565D0FA97184DE9BULL, 0x52EB40720D498E74ULL, 
            0x48E187F74D6C46ADULL, 0x1B6DA5C5523757B7ULL, 0x543C384B007BFB92ULL, 0xABDF3B080169DDB6ULL, 
            0x07C885DBE9E00DFDULL, 0xE65633D89348363AULL, 0x8AE575C2DA1E7B00ULL, 0x6E4EF425616FDA2DULL, 
            0x7018E3520C255F00ULL, 0x414ABB5FE113AE1FULL, 0x688CAE2DB0FECAEFULL, 0xA8645BD144FCFE70ULL, 
            0xC6135F1A48EDF74EULL, 0xD1AB45453287A477ULL, 0x6AD697D9A34F5823ULL, 0x45125CE2F2A4EB2AULL, 
            0x1F5B9DB3A03F2123ULL, 0xB82E015110E2E903ULL, 0xF3FFD3A0BBD608FFULL, 0x4F1CE5A33961D8ADULL
        }
    },
    {
        {
            0x49744DF7C867FB7CULL, 0xD9A25D384328E2CFULL, 0xB6071E33A9E1D5B6ULL, 0x0C6485853D26DC5DULL, 
            0x012C79E60BEA6B1CULL, 0x11E312382F2452D1ULL, 0x7CF936CAF1C2CBCAULL, 0x09FF074D03DFC5B8ULL, 
            0x117BBB11686521E3ULL, 0x5C8F3A5B50258FFAULL, 0x00D1EAD6B5BEBB6BULL, 0x635EA2523BEAE5FDULL, 
            0x7AABB5203740AB2FULL, 0x8B0C558FAB38805DULL, 0x58A7EB485A230837ULL, 0x7FA960807BE2AFA2ULL, 
            0x9A7C805C7A72692EULL, 0x338556F589829134ULL, 0x4463E813E7F5082EULL, 0xEE5FC769C9F89FF1ULL, 
            0xD510360072E7B1FEULL, 0x2DDC3445B2C599DAULL, 0xD39EFDDE890369A6ULL, 0x68F0F7FEFA80146FULL, 
            0x2AE89B5349B63A9CULL, 0xEC9B36DA150380B0ULL, 0xD6BACCEC53027194ULL, 0x92BF0339538664C9ULL, 
            0x84F5981E4300501FULL, 0x4CD1AE9A0EFE7958ULL, 0x9AEB82F80649F2A3ULL, 0x4E4ADEB62AA8F2CBULL
        },
        {
            0x6C02A0CF532E0CB2ULL, 0xB14C85C3A35AC77AULL, 0xF794AF801267A2B8ULL, 0x6BB27CEBD40A9A8FULL, 
            0x3C55BCE48C199873ULL, 0xA6E19CD2B2B85B56ULL, 0xD65918CC597FC83EULL, 0xAB2C4907F37A518FULL, 
            0x54E6D5C87DDBE744ULL, 0x9FA04769B1580346ULL, 0x89177A11621ABD2CULL, 0x4F2A775901DFBB4BULL, 
            0x74F3A029FE143678ULL, 0x5B51C0FE7099702DULL, 0x7796E279FBBBED45ULL, 0xD5666D83AB07AD73ULL, 
            0x49014A2D391DEBB0ULL, 0xAF3D307163DD6855ULL, 0x00DAE024A7313CC6ULL, 0xF452AEBB26DC50F0ULL, 
            0xCBBF23918DCBFBF5ULL, 0x654AD94CCCEAEBD6ULL, 0xF557F15FC9E9009FULL, 0x6A054F8191FD9921ULL, 
            0x5AFD4C75AC039D5EULL, 0x3498F18A2352BD57ULL, 0x2E0D6FDFD5949AC7ULL, 0xAF2FC176754E052AULL, 
            0xDA5B992A41EE0DC7ULL, 0x21C84314F9C5E99CULL, 0xE8C8585C1E539A79ULL, 0xDE3C670272D0EE18ULL
        },
        {
            0x63F6800CB4EB8A44ULL, 0x49F06F90A80E8D1DULL, 0xC57F91D51C4DCE66ULL, 0xFF9D567D0C1B0F13ULL, 
            0x8235965871730B9EULL, 0x07EEAA8D44832666ULL, 0x3F876451714C1D85ULL, 0x6ACFE7D0BE616866ULL, 
            0x3343C02F0290A1BAULL, 0x99C88847EB8C4632ULL, 0xE6552E135B713493ULL, 0x3A7F1D2025384BCDULL, 
            0xDC1EC02B7B0E28F4ULL, 0x1A4FA62C8206BD3BULL, 0x07A171515A40B9B1ULL, 0x4A33481962BC1238ULL, 
            0x3902C0F673EED48EULL, 0x2CF46D183EF46803ULL, 0x4258B97F8D0AF8DBULL, 0xC1E40850756E756BULL, 
            0x03D2C03D80899F44ULL, 0x08038EA1A8462437ULL, 0xCCEA4B7C11D33207ULL, 0x8ABD21D6209D90F2ULL, 
            0x242F5D3697D01C29ULL, 0x21E82F4E833E26C8ULL, 0x5A383DF53999D1F3ULL, 0xF506C4D0644CF757ULL, 
            0x0B60DF1CFACD8DECULL, 0xDB0FC1323716EDB2ULL, 0x35FAE737877050CFULL, 0x09990B038DBCE68EULL
        },
        {
            0xC41ED89B9002F5A7ULL, 0x1C74E300761677AAULL, 0x85F9E37446137AB9ULL, 0x3F3CC677B8D508B5ULL, 
            0x89177636350F6422ULL, 0xE73BEDA1DA3B0657ULL, 0x581429FB3BD4A916ULL, 0x97924B92A8801904ULL, 
            0xB4C1CFAA95DE3203ULL, 0x1E086C522ACF4C78ULL, 0x6E1D4B60F0FD1EFBULL, 0xF10B204C63E60137ULL, 
            0x78D58117737CC363ULL, 0x5289557453C96C30ULL, 0xF2B60D96F6530934ULL, 0xF7F367127B37B8C0ULL, 
            0xC18C8A9BC0F2DBE6ULL, 0x5CCABB8D32CD6256ULL, 0xA35930CC2621DEFBULL, 0xE8BAE63A3AB4A0EBULL, 
            0x73CB47ADA140D846ULL, 0x496E9EF57D260807ULL, 0xE66EA837C76D2D7DULL, 0xE8A46B7E9A7DFA1DULL, 
            0xC044DA270DE07DB3ULL, 0x827B51A5C48EC864ULL, 0x4D59CA360411C48AULL, 0xC69EDD0281931972ULL, 
            0xEB9B5F0FB0CA5747ULL, 0xB7160A3A029401C4ULL, 0xAB959EBE398336EDULL, 0xF68C4308030A1C56ULL
        },
        {
            0x9F5B55CC38CE8D9EULL, 0xF42534948705979BULL, 0xDA3A3210AF60C730ULL, 0x994547C6E0D11AB6ULL, 
            0xE980D95EE17CE3BDULL, 0x9B16D08589687B12ULL, 0xF0A05B509A1CD0A5ULL, 0x562D745C3D2182FDULL, 
            0x8B9E879A0DB32D4AULL, 0xDAC1B6BA62E8108EULL, 0x725763210FEE437DULL, 0xC3BEFB1DD3E0389DULL, 
            0xF9BD5996D28BE6C0ULL, 0xDEAB5FE1751814A7ULL, 0x17E2A2B9ED1E2253ULL, 0x3EE7F50827832C3EULL, 
            0x348AF5359D9F356DULL, 0x4AEEE09E0DBC6F8EULL, 0x10B78836E80C605AULL, 0x4CDE587726FA2776ULL, 
            0xACF98822A1DF8640ULL, 0x6BC3E6C23B1B32C8ULL, 0x89DF74CB84E4E96DULL, 0xB6425052D61FC58EULL, 
            0xE3691EBD414E1D3BULL, 0xB79AC05AF42696B0ULL, 0xCEAF7ECF6E3AE34CULL, 0x50DEE7A5A783AD46ULL, 
            0xDCC3D2620642FFC4ULL, 0x44ADF94E5CEE354FULL, 0xCB36661E596A3490ULL, 0xFADBDC841B2BED12ULL
        },
        {
            0x14D6FFBB59EF4D9BULL, 0x4C6F9A8E87B68C89ULL, 0x5F0DC93FBE3A49C1ULL, 0x84EB2BAD9577591DULL, 
            0xF77E64293DDD1C26ULL, 0xE883A29D3CDDBDD8ULL, 0x2BA7E94E31ADCD13ULL, 0x95486E890F6BF91FULL, 
            0x1C9245B1D1B0E6F0ULL, 0x131E7F3424864F4CULL, 0xEDD19E25DEFF951BULL, 0xD56630F4D468DE9BULL, 
            0x33898DE5ECBFF871ULL, 0x6CDAFEB405661B7CULL, 0xFDFD62D848419CACULL, 0xFB770BE98B403691ULL, 
            0x714A796ED2BA1AF6ULL, 0xCDE38097794A6C10ULL, 0xB9DDB81ADA98EC25ULL, 0x44C1D4A24F90B263ULL, 
            0xC55D23B246508D9CULL, 0xC9A2BEE492109AB0ULL, 0xF171C7950FF81587ULL, 0x38BFF08AFB48FA26ULL, 
            0xB043A24D334153CCULL, 0x9B5FC958CD8FC873ULL, 0x1E5F66DEEE03A472ULL, 0x8993B4CF32ED4E8AULL, 
            0xCB9157D7A938151DULL, 0x5127538224535BB4ULL, 0x614C9C6CB6364096ULL, 0xDDF55F46A5DD4CE2ULL
        }
    },
    {
        {
            0x9B2CDAF3B1B53DC6ULL, 0x83D6D2636C0845BDULL, 0xE7B1431A9D76D852ULL, 0xD47E9D732170DD87ULL, 
            0xF44AA48D11099CFBULL, 0x55F90D2824500FC7ULL, 0x9FFBB0FEACE26963ULL, 0xE73BF5322671F672ULL, 
            0x2DDD436235B083B3ULL, 0x23A6754383B1AC62ULL, 0x4C84E6A414E47319ULL, 0x9F7A13CA0599DEF5ULL, 
            0x8205B004BB8616C7ULL, 0x30095AB46508A0F3ULL, 0x30B675892C84C350ULL, 0x48ECB2D9A5528C49ULL, 
            0x090B3608C4FDCDAAULL, 0x5E79F06EC75989EBULL, 0xB9DE35E3BEDB4362ULL, 0x60E7C6DD2E43C35CULL, 
            0x4A49DCD9DBC39AC5ULL, 0xE6AE7975CED9028BULL, 0x6B51DC5138C21AD0ULL, 0x9A955083566EBCEAULL, 
            0xBFA7515999F045FEULL, 0x6DB8DAF6D4E78238ULL, 0x83BE9C6C0604771CULL, 0xAB3ED6C8DAD26F64ULL, 
            0x490BC59C8FC49522ULL, 0xDE214DC5CF7906FFULL, 0x23FC3E31D85D2D24ULL, 0x00C8183F8819F266ULL
        },
        {
            0x80F416E38F5E8F23ULL, 0xADA9ABF4CED8F09EULL, 0x27608BC9293AD4DEULL, 0x950A4AB4E458D5C2ULL, 
            0xF0769637F4946D94ULL, 0x53253D8EFC16908DULL, 0x21B99E40D9B1F887ULL, 0x721A8ED12D09666CULL, 
            0x18512AE1F4FBAE62ULL, 0xA574B1CD0F29B6D4ULL, 0xD393E8E6FEFE31D6ULL, 0x9DCA5F0645CDEF79ULL, 
            0x44F276EDC230030FULL, 0x66F47E5C8964102FULL, 0x9BD7876D4E18F090ULL, 0xF807BB03D00A5D47ULL, 
            0x50D608ED86E3909FULL, 0x73190DDAA13D2B0EULL, 0x45D22741390002F3ULL, 0x66F7D5349842612EULL, 
            0xAF8DF424DF9FF11CULL, 0x1CF04015C1219175ULL, 0xA4512082A7BA2E11ULL, 0xAF90278C59717B6FULL, 
            0x7C8715427BD3BBE5ULL, 0x9457715AEAB4EE64ULL, 0x82924EDB76A26324ULL, 0xAEA66427B8CB3C58ULL, 
            0x065DD16799658D9DULL, 0xA9D71DF2AA91D49BULL, 0x3178042466964519ULL, 0xE7564D3A201CAAFCULL
        },
        {
            0xCE3D6257E6807DB8ULL, 0x7821785F5A134226ULL, 0x90004DE529FED6F7ULL, 0x384F963BBBA49496ULL, 
            0x416987A60CBA81B2ULL, 0x3B09730AED22A318ULL, 0xA15C00434A0780EAULL, 0x38E25176AD4EC58EULL, 
            0xE59D28F0B1D6CB49ULL, 0x8DF5E40117EC5B28ULL, 0xF6784C1B81331F6FULL, 0x78152CE751BA3D22ULL, 
            0x19830C9F1BA024C3ULL, 0x2CA0BD3B78F3E271ULL, 0x01F2F6DD18BFB08AULL, 0xA3075D7BB46CE192ULL, 
            0x0550C07C49A2FA9CULL, 0xEBFEDF09DA490803ULL, 0x5A643DABCA246713ULL, 0x539454787A7CE0D7ULL, 
            0x44FE2C9305650DFBULL, 0x88447CEBB19F5CA9ULL, 0x0649CF763452E415ULL, 0x8360CF8D74FB82EEULL, 
            0x38063D02BBAC07C8ULL, 0xC156936738F33C2FULL, 0x17ED0604985795B3ULL, 0x256887DD1B8ACE3DULL, 
            0x383F0EEC7C101249ULL, 0xC2B934E0DAD13704ULL, 0xD6938944B2B86BD8ULL, 0xF0DAD992DD802B11ULL
        },
        {
            0x4B6A3B4D0E269B9AULL, 0x5C47ABF7407E2B4BULL, 0x9B56BFBD07542D67ULL, 0x2DBB0BE41F23448DULL, 
            0x2704725686E245CDULL, 0x37233711CB9F4457ULL, 0xE1A9E0D69E222728ULL, 0xE66A40C0E712AE25ULL, 
            0xCE1C495F24DB0F1BULL, 0x5BA5C9CA99633FA6ULL, 0x0831F1FC6C459374ULL, 0x8128291ACF31B773ULL, 
            0x5BEF1A427B5592FAULL, 0xD7C06F900B1D84C0ULL, 0x5201B812B7C6D484ULL, 0xBC72A9A22E9FAD0AULL, 
            0xF12DFE93DB23B16CULL, 0x15B948A5CAA2E055ULL, 0x13849A07A681050BULL, 0xEB66E85734536C47ULL, 
            0xDD030B20293EA120ULL, 0x83092D89836F85C3ULL, 0x348573D29E2C6B4BULL, 0x2969E63AE5A0524BULL, 
            0xD745CAF5CCD7732CULL, 0x853DED072D3C25AEULL, 0xE4D0B72635E7595AULL, 0x20050491F5084840ULL, 
            0x1FC0D40D1CCD1F03ULL, 0x189CAB0A4337A47FULL, 0xB3307BEEDEA8E7C1ULL, 0x5305A1EED4F3A161ULL
        },
        {
            0x3E1F2F9D1C77D54CULL, 0x94499073F4815933ULL, 0x2F2C8B359DFA746FULL, 0xD1EE51AC87C3A51CULL, 
            0xB3324C3BB390FBE0ULL, 0x9A10A4545FDDB732ULL, 0x073A3F6160723703ULL, 0xCB10EB913F5C6649ULL, 
            0x58266A8746719E2EULL, 0x07F9C7169121099BULL, 0x0FA44214EAEBCC38ULL, 0x59A0AEC27997BDF0ULL, 
            0xE0096AE955831603ULL, 0x3C72598822593513ULL, 0x66B3254F197326D6ULL, 0xA6C1D86541E6B9A0ULL, 
            0x12A009FCAB558283ULL, 0x84F35C8B9891BCA0ULL, 0xC80EDF5624CEFA10ULL, 0xC8094879A089D176ULL, 
            0x9DFDCA27691EBD80ULL, 0xFD5AAD8AEDC85CB8ULL, 0x393055259A69A72EULL, 0x2B86C0B339CED039ULL, 
            0x82A979FDF949F74BULL, 0x12E1C246E5249C18ULL, 0x3D00A904751A6EA7ULL, 0x551449E115584870ULL, 
            0x477C3B321C060A9CULL, 0x13A608CA04808D5AULL, 0x1350989AB2783E0AULL, 0x375F2FF571E7DFF4ULL
        },
        {
            0x54EEF6A6CD8261F1ULL, 0xB72B1774D88857EEULL, 0xA2788396F844CE0EULL, 0x073D0D5E7C0F3DB1ULL, 
            0x255FB0C5F89582EBULL, 0x44D4CF61E256C86BULL, 0xE6E09BF268E61D77ULL, 0xE38F9CF1A62D7AB4ULL, 
            0x48E24FADAD84B9DDULL, 0x63E6F71B8DD95169ULL, 0xAA9146A06BA7CEBCULL, 0x2A956721B2B61AF6ULL, 
            0x495B666984E0E479ULL, 0x32AA5687FFB1B946ULL, 0x541CEB9C23434E15ULL, 0xBA075893DF492E67ULL, 
            0x0D1D40B59D6A9E9DULL, 0x291BFB44B2C90644ULL, 0xE0C2509281E38CE7ULL, 0x75B3EF7A09B9B8BDULL, 
            0x0B7535B36810C282ULL, 0x38B0D864673A5883ULL, 0x3CD759F0E0539E87ULL, 0x044DD2F700843D13ULL, 
            0x61196320C33C3A73ULL, 0x9BD32C5B04705837ULL, 0x94431F24535756CEULL, 0xB859811367EF9FE7ULL, 
            0x6305F8FC68449D84ULL, 0x0C96D704694B2CEAULL, 0xF3FE4DDAEF87B714ULL, 0xA434F2DC68562B34ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Castor::kPhaseBConstants = {
    0x2638236A1702285FULL,
    0x25072A3450191DF4ULL,
    0x5CD7038642CE2C87ULL,
    0x2638236A1702285FULL,
    0x25072A3450191DF4ULL,
    0x5CD7038642CE2C87ULL,
    0x18A06718E4918640ULL,
    0x70F404A31F6F4822ULL,
    0xEA,
    0x37,
    0x41,
    0xA9,
    0xDE,
    0x83,
    0xA9,
    0x04
};

const TwistDomainSaltSet TwistExpander_Castor::kPhaseCSalts = {
    {
        {
            0x01141077297A5899ULL, 0x2B63697279E7BD61ULL, 0x9AE266730008EE0DULL, 0xE11699F61E61384AULL, 
            0xB184EE009BE741A9ULL, 0x8A505B4FEE165C28ULL, 0x9EBD5C9C553F7AD1ULL, 0x7FA9A8100C9350E1ULL, 
            0xD54210C22D02EFAFULL, 0x7D79C5AD58810119ULL, 0x86239F23AE73BD98ULL, 0xB76CC3089F9129A2ULL, 
            0xC1B54574B74B5979ULL, 0xB334A97413AB66CCULL, 0xD6BE60F1A2555F24ULL, 0x43953C81E4C5BA8CULL, 
            0xFFF55D2C88F584DFULL, 0x5DB658585F40A1B9ULL, 0x1C382D91BED5ED2FULL, 0x88CC414D16DC64FBULL, 
            0x872A70152BEE7D55ULL, 0xC1C31EC4D23FA6C1ULL, 0x12105C4CE99FB568ULL, 0xCDC676B3D0A31907ULL, 
            0x5C775875AAECC57DULL, 0x8B62E0CF3490B37BULL, 0xFA4BD31FBF83E4ECULL, 0x3F1CC0B02F56BAE3ULL, 
            0xCCBF518502225B2CULL, 0xAC4010C1126B5945ULL, 0x88B3963E3A1B2E11ULL, 0xA0F579D5C0296756ULL
        },
        {
            0xDE73FFC6EC464872ULL, 0xE50279904EAE6E50ULL, 0xC07F8D36279CAF6BULL, 0x4E99A6956E8D60EDULL, 
            0xB093C18A8FECE725ULL, 0xF979A2E4D240A886ULL, 0x2E61C027B6387A0CULL, 0xA6901D56F6A3F386ULL, 
            0x9D3400D0873A2518ULL, 0x1200B6B7B7E6436EULL, 0xF12CC7D59AEE4D40ULL, 0x6ACCBEE7802960FEULL, 
            0xB4D899EED6314775ULL, 0x80E29EDB4BD3A3D1ULL, 0x1BC409ABB0E5F8A3ULL, 0xFC3CDA0D37ECEBD8ULL, 
            0xB41654CDB0E48952ULL, 0x4F9B0686DB1F9779ULL, 0x45B7BBCA685A9AF3ULL, 0xB89B778A7436B4CFULL, 
            0x9584CF2DF27B2456ULL, 0xDBE8E9DBDBD02991ULL, 0xF888BBF826BCAE35ULL, 0x8C35BFF8A54C75EEULL, 
            0x2D5EB940F12B769DULL, 0x570EDC17CEB41F68ULL, 0x4B6643F59B792593ULL, 0xF3716E862BC95239ULL, 
            0xE5678E38EE44BA6AULL, 0xE671C62EBE2061A1ULL, 0xC8012665942D2275ULL, 0xF5D0CDB9FA472C79ULL
        },
        {
            0xADCA1088568ED5E3ULL, 0xC66F61BF70BC0AA3ULL, 0x13C54DC458969056ULL, 0xE5D04724B5470619ULL, 
            0xB795E89221267C33ULL, 0x8E76BAC1ED715C27ULL, 0x01CE67F3B517742DULL, 0x534AB0043C63B96AULL, 
            0xDF0CE149121F43E7ULL, 0xF5A6E031ABE75299ULL, 0x1AF06C0DA81BB15FULL, 0xE169A7E40CC4AD0EULL, 
            0x32BC23A95C928E5AULL, 0xD82C9BDF948DC36AULL, 0x4491FDA2D18EDA5CULL, 0xAEEC59524CA1DC39ULL, 
            0x9A63DADFEDE87AD3ULL, 0x82CE27F10F01648CULL, 0xC706563F19445918ULL, 0x99C0C4188093D1FDULL, 
            0x44C96F8169D94D31ULL, 0x2AF6254D75A27C4BULL, 0x8029154BDF9E790BULL, 0x8101C99528C11259ULL, 
            0xCCBF57D94BF5A409ULL, 0x0EB9E0CC99993563ULL, 0xAB0B9B82AFE2BBAFULL, 0x7D7F59DDBABBB6E7ULL, 
            0xC5DE1918371D63F6ULL, 0xA62D6F2E54D88914ULL, 0x251AF273013C0D2EULL, 0x6ED325F5DFD0E82AULL
        },
        {
            0x7369714062770FA5ULL, 0x67812C8E4C7934E8ULL, 0x85733B991599393CULL, 0x130221118E2BB8F7ULL, 
            0x9DDAE76E49C98E1BULL, 0x0643779D49F58CB8ULL, 0x43ED1A4E92431A6AULL, 0x98045AD82BF26099ULL, 
            0x63302A2D0EB9DCAEULL, 0x2FC2F8B5047E653CULL, 0xB6D0B9B5D1B521E4ULL, 0x144C0BC97A655707ULL, 
            0x949E7F620FFE33F5ULL, 0x62EB56947DBEB8F8ULL, 0xBB319738C394529AULL, 0x24D518788F119C54ULL, 
            0x5748D9CDFBAB1C0EULL, 0x69664352AB8B1552ULL, 0xB91AAC9B8B312C47ULL, 0x9F08A5AAC481E891ULL, 
            0x51D54A66FFBFA4D5ULL, 0xAB81DAED40765779ULL, 0xB53B14C18FEC3BC0ULL, 0x7CEB778075B34900ULL, 
            0x99CF88D7BFB227A9ULL, 0x07B7EB319D9BC121ULL, 0x6D0C2FDD31317653ULL, 0x59A5785281ED1A71ULL, 
            0x49084E2D0EC945C6ULL, 0x382CAE1BC1D84E7EULL, 0xA606F084CE73C641ULL, 0x1477E60515DA90E4ULL
        },
        {
            0x3616967B83AA5501ULL, 0x19DAFB400042A84AULL, 0x13E64AD42037D27BULL, 0xFF631D63AE8DB483ULL, 
            0xFB1283DDF94FB2E5ULL, 0x8D442156CE008193ULL, 0x62FCA1409F6A7CEEULL, 0xEE0CDAF4A98C11D1ULL, 
            0xE12E88FD5E3B83B9ULL, 0xF4327375F19C38E0ULL, 0xC868CF2484F760CDULL, 0xE82541A9402A737AULL, 
            0xF26EDC03B57DBC35ULL, 0x8F8EB90403235453ULL, 0xD118DF6B318D09DDULL, 0x2CD2360DE304F883ULL, 
            0xC685696C630A21E4ULL, 0x3BF1B07ADB20AAA9ULL, 0x039BB8855A1526E0ULL, 0xE8831353480F0764ULL, 
            0x29937130EA51F8FBULL, 0x6D193FDCA42F15C7ULL, 0x878F47A7D37CA778ULL, 0x71956266CDF72EFEULL, 
            0x0779F7E6711966E7ULL, 0x7F65F226AFC53346ULL, 0x51A8CB0CB86777C4ULL, 0x87AA552ED257D490ULL, 
            0x56B875441EC387A8ULL, 0xF50D592DA513DBC1ULL, 0x8A7B42841A2AB482ULL, 0x1040E25C017BFCD8ULL
        },
        {
            0x086FAC1C72B7EC20ULL, 0x790F8A9F09BB8472ULL, 0x70178A98496F117DULL, 0xD5AB95DA97E55163ULL, 
            0x9805A5DAC342E3A5ULL, 0xB14677A50796057EULL, 0xBB14D74E7F0D1308ULL, 0xB1809908F0291252ULL, 
            0xF67387E5D2CAB8B1ULL, 0xBA64BAF3953742FDULL, 0x1EAC3D0DFFDB3F3DULL, 0xC3AA45F57984ACC5ULL, 
            0x09A24BE01AE1FFF4ULL, 0xEFDD395F0A680BB3ULL, 0x18A68D14B1223373ULL, 0x4CB40AACD5CEA80BULL, 
            0x261D74BD3772F217ULL, 0x4096FF117C3C2094ULL, 0x45F499962345E6E7ULL, 0x02CC38EDDEA6CDAFULL, 
            0xC0BEF105FBC67CA8ULL, 0x0D87D4F80880E50FULL, 0x5B6437DB0271573DULL, 0x36700F232E9FFCF1ULL, 
            0x7B6AEA02B54CF57FULL, 0xCE301BC5882DAF1FULL, 0xCF52478CA62A26F0ULL, 0x7E64013825129C0DULL, 
            0xC04DA2B3C8C4542EULL, 0xB8C2CF254882D58AULL, 0x2E3D6043E8DCF57CULL, 0x4999E22B34B9C205ULL
        }
    },
    {
        {
            0x07BF36655939DAC3ULL, 0x9F85ABD9AB3FCA5DULL, 0x49FF85CE2FA5281CULL, 0x64086AEE951DAED0ULL, 
            0xD54D76B3F63CCBC9ULL, 0x1783252F88EF7D0BULL, 0xA249E886DABBFC2BULL, 0xC545AD5AF6339DD0ULL, 
            0x79856EDC7C789E2BULL, 0x4471841213BB6E46ULL, 0x5907B770EA8778D2ULL, 0x73B1A8615C20965EULL, 
            0x3A23FEAB24CB4115ULL, 0xFE8B8128642EC3D2ULL, 0xC6536CF8581F20F0ULL, 0x0954C8C847673644ULL, 
            0x68A22EA0CE460DCFULL, 0xA33DB5D6902B63A0ULL, 0xB93B5A948DD12154ULL, 0x5BA7DD2793A10231ULL, 
            0x6D14987A7541468CULL, 0xB43F847312EEEE71ULL, 0x7FF3BDC6C0F2CAEEULL, 0x63CB83ECD5812D45ULL, 
            0x11585393275147E6ULL, 0xE8FBCDE68749C27BULL, 0x71D0861CB6AC31E2ULL, 0xE894ED9A9398ECD7ULL, 
            0x9D1F987B099ACAF1ULL, 0x646B70F5A3B1676AULL, 0x2623F126CFB6B57EULL, 0x7B19EBEBB45194F4ULL
        },
        {
            0x2BFB4DB0BC7749E7ULL, 0xB623E60170094ABBULL, 0x81106251AA386A7AULL, 0x885BE6539A4547B7ULL, 
            0x28B2016971567E1DULL, 0x6BC17B5AB04D17B0ULL, 0xFFC39049289DCC9CULL, 0xBBF2EC4F3F0873EDULL, 
            0x5203AE330AB8AAA4ULL, 0x84C63534F0CCFCAFULL, 0x0CF87653BF6C150EULL, 0x4050A498D22309F8ULL, 
            0x89BD5AC8369E6E39ULL, 0x8526D10F70E94DDCULL, 0x359A7CCC634FF008ULL, 0x06A4403954AF85D3ULL, 
            0x9A13C5452C28886EULL, 0x0453F4F7C43CE532ULL, 0xF6EFC9F73A688063ULL, 0x89C217285AC7969CULL, 
            0xC596D606D26E25C8ULL, 0xF056C900D5C52964ULL, 0x79132CBA3D63688EULL, 0x3183906577641783ULL, 
            0x7276EEC6F8D56D7AULL, 0x92B9DBD609BE5E78ULL, 0x65303C4305C3C65DULL, 0xA9A2F97A34A5BB6EULL, 
            0xF62EA09B07A0094CULL, 0x6438E0E4B6250F71ULL, 0x8B6916BFB6448479ULL, 0x14274F5E008D5896ULL
        },
        {
            0x3B10214F137A6A41ULL, 0x44C47EC2283D7E02ULL, 0xB2533F7E412FA155ULL, 0x83B9A39B9DBB333DULL, 
            0x260D392FE74136A3ULL, 0x2D4EF85A7CFE0486ULL, 0x47A58F07A426D49EULL, 0x962A770497E30F72ULL, 
            0x097D5DF1DE98DDF6ULL, 0x1CB926ACE7B85BD1ULL, 0xECE062F0A77A0A3DULL, 0x3D729C3E5DA2FD27ULL, 
            0xC73B742564CB24F9ULL, 0x329C5885F5B46096ULL, 0x1E9D196234B3E091ULL, 0xC7F920A26E7EE27AULL, 
            0xEBDBA69568AEB960ULL, 0xA6001629109D943EULL, 0xC809967B9FD44AA8ULL, 0xC935948AE1589AA0ULL, 
            0x36E9F737FFED8594ULL, 0xC1512B4D143F113AULL, 0x9CACAA8A36B07818ULL, 0x71A1F6CDDAE2F431ULL, 
            0x2C5842130CBCE5C8ULL, 0xD8FC91260D7F6761ULL, 0x503DC7EED473601FULL, 0x414D222B67D579D9ULL, 
            0x9F45CFE094C43C75ULL, 0x4FF0A0E041D07D90ULL, 0x41E4BA4B6A39DF4AULL, 0xC1D9A07F462ED224ULL
        },
        {
            0x713708D997B2FDACULL, 0xC931821D345512BEULL, 0x5809640A5FA916CCULL, 0x727F0FC44F23594DULL, 
            0x380FB06A216FC7EBULL, 0x9EE62570563A2E72ULL, 0xE1573BF2EE901AF6ULL, 0x16AD1FCCD4FFBA9FULL, 
            0x785E5489790701F1ULL, 0x33207D68D2B7817DULL, 0x9FE68BB9906B3B27ULL, 0x5F241CE27845E463ULL, 
            0xD91EC5F7DDC96B62ULL, 0x5E50F79F61972E47ULL, 0x43813C1F9B6176E3ULL, 0xC5FD351F7175C239ULL, 
            0xFA5CC03077E25C1AULL, 0xC31FA0170D181046ULL, 0xFEF88778C9CEFAACULL, 0xD2CC14FD1D0F513CULL, 
            0xAC17DF2B6D07B1B3ULL, 0xC0018A5421BC1321ULL, 0x883847FB5DA1A061ULL, 0x5D8E15128EE0AC9EULL, 
            0xD0F97AE140582698ULL, 0x6604B57DE3BBB745ULL, 0x69D96CD3FC1C3B48ULL, 0xDC45670CD92B68F2ULL, 
            0xBBF00BFB199960BCULL, 0x7C6043799E9C4AC2ULL, 0x4EC5F061B90DEEC4ULL, 0x2ACC207A21210A71ULL
        },
        {
            0xB31868E6C1A67117ULL, 0x5B5D83320377A054ULL, 0x7A443C5EA6C8F194ULL, 0x263F8C278AF1F223ULL, 
            0x143B1AA61A66C1D3ULL, 0x5B04E08869496EF3ULL, 0x285EFD6B0BF16B8BULL, 0x708805D1A8A12408ULL, 
            0x0DDB94F20F65817BULL, 0x9D5BEF7B136735E1ULL, 0x8FC981DB918715F4ULL, 0x29DC8A2138B2354FULL, 
            0xCA319F2755AE0813ULL, 0x5A107DD12BBC4B10ULL, 0xEB6FE5DCEA9CC58DULL, 0x0CD1B8BAF44F8FD2ULL, 
            0x6EB028509D34AE70ULL, 0x535BEEAF7A61E9F7ULL, 0xF5101109B34F348EULL, 0x0132A2BD324FE197ULL, 
            0x16AAE8FF45546292ULL, 0xD09291B78DC219B7ULL, 0xF9160BB88ACAF9A5ULL, 0xE7952EA4CB5DB2DEULL, 
            0xAE8DA1203343E8A7ULL, 0x94D8C0851D430F7EULL, 0x9C0C77486E4B4BA6ULL, 0x045F604246417E24ULL, 
            0x304F5D0D75A280E1ULL, 0x206867CEF359950FULL, 0x0B1F9363ED76B055ULL, 0x80A4C2DDFE68673AULL
        },
        {
            0x08F2B8B843D6331DULL, 0xD1D5CFE3B6BF1653ULL, 0x6E3842CC6C6A43CCULL, 0x2FFEE5F3742A1320ULL, 
            0x299F995E6FC67F6AULL, 0xD5D6A3B6444750C2ULL, 0xEB53837848B844FAULL, 0x20285EDDBA6A6C9AULL, 
            0x361D323DDBC56BAEULL, 0xEA2E6A6D14D4952AULL, 0xF7924F79CB270668ULL, 0x440005F5BB493F21ULL, 
            0x8A70CDE94052FDD6ULL, 0xD50B49DFFDCAD0ABULL, 0x2D3708738E85D15DULL, 0x6C3F39334D0E067DULL, 
            0xF2B69889086D473BULL, 0xEDAEDC67DC57D9E2ULL, 0xF0600612B55B4C4FULL, 0x1D9CAC10DE53A2B1ULL, 
            0x59F8502A7764FAC6ULL, 0xF4A1C406C704253BULL, 0xDC86D2C074975EEEULL, 0x7CB520442B4C793DULL, 
            0xDDE9241B0D044595ULL, 0x1E833035B3199C04ULL, 0x55FF2647BA1646DFULL, 0x9A35B9DFABEDE67BULL, 
            0x8DA471A75D552459ULL, 0x52318C9A0F555E14ULL, 0xC9233A4579BE3B23ULL, 0xEDD8432A112FD15EULL
        }
    },
    {
        {
            0x910662664E968F4FULL, 0xE4D46B9EFD53236DULL, 0x69608910767EF587ULL, 0x58F2F370AB859BA1ULL, 
            0x86DEF4E256925C6AULL, 0xAF3E5499AF628CF1ULL, 0x46B7D8D6A30FC7F1ULL, 0x05B36FE618A87A05ULL, 
            0xE46A5E1577E950E3ULL, 0x102F0CCD16413219ULL, 0x4648D68790034B3BULL, 0xA1009D665B2C4BA0ULL, 
            0x96D821A0EDEE1EBBULL, 0xF76C4699D545F857ULL, 0xF298DED70C172321ULL, 0x842F55D70589362EULL, 
            0x3CB8FA6B738D4794ULL, 0x42740F413C10E164ULL, 0x954CB8E5A079517DULL, 0x2823F845AC7E383DULL, 
            0xF93A01BEF85A9FA8ULL, 0x379FB8C9089EEAC6ULL, 0x8B2F2A32998C3157ULL, 0xDBC1FA7B172A8BBAULL, 
            0x4945584C32353085ULL, 0x48CC3D386EDCF55AULL, 0xD198E809E944F0FCULL, 0x950477949C061765ULL, 
            0x5B51C9B50D68F3A4ULL, 0x13409CD65F7826D1ULL, 0xFCE0D4FA727FA0F8ULL, 0x2D5BE61A1C989FDAULL
        },
        {
            0xA0FB9C2A040E027CULL, 0x19D75A6EA9A70483ULL, 0x723210C91D694B36ULL, 0xD55030ADBCAEE225ULL, 
            0x354A9965A8362DFAULL, 0x5CF3FFE785A9ACEFULL, 0x11F1780A42D6763FULL, 0x83A644DE44BC35E8ULL, 
            0x9D2B85960251F3ECULL, 0x2061363807640301ULL, 0x3ABE496647C65DCDULL, 0x43D5CEE6EA7D687AULL, 
            0xC134F4EC7183C08FULL, 0x1D30565E942A5A81ULL, 0xF0EE44D5964C73EAULL, 0xEC25C54566CAFEF7ULL, 
            0x70FA6EDBCD0E9DC4ULL, 0xBB14C4176A9FA162ULL, 0xCAEF2E0C69D259D7ULL, 0x822F486AE1FEAF73ULL, 
            0x33725E57ED10E572ULL, 0x4C0AB4A25AA4BEB1ULL, 0x89B63A9868CF1AC1ULL, 0x9E05B11B9B945E4BULL, 
            0x1E1585A18640A2DEULL, 0x2F92DCED8C141D76ULL, 0x3E9737726C0DDE81ULL, 0x86B4CD35247C5FAEULL, 
            0x274FC7A84A563FFEULL, 0x71A83720731A662EULL, 0x145ADE6224E1F314ULL, 0x7DEAC4E258D7A57FULL
        },
        {
            0xE860EC84ED8490A8ULL, 0x9E21D59492BEEA0EULL, 0x17404D2358F32211ULL, 0x3DC5AACAC829BA70ULL, 
            0x53A6E7FAA8A6F5FAULL, 0xE65B4787625B9455ULL, 0xED0BFA2D8774DB49ULL, 0x4187B1323FD222C5ULL, 
            0x2D66EF9C4985D6DAULL, 0x068BABB3BAB9A761ULL, 0x896AF76861C50786ULL, 0x4C8A40F4872A6359ULL, 
            0xDD933E60CAD15139ULL, 0x63CCA0FF9634C27FULL, 0x7949C5343A38D646ULL, 0x298C202FA9F0B911ULL, 
            0xDDC5330A83ABE242ULL, 0x202FD8E94BADB6F9ULL, 0x6722FA25AB05482AULL, 0xCBEC29EB7C4DAC57ULL, 
            0x31CFFE0603C815D1ULL, 0x879648F6093879CBULL, 0x4331358A5890E4C5ULL, 0x692527DA3A7E201EULL, 
            0x984BA19ED50A9697ULL, 0xCCDC27F75EADB0EAULL, 0x1310097C6A59B0F4ULL, 0x2773441C6F11C621ULL, 
            0x66526EAB9C8BE3DFULL, 0x58BE78ADC39B68C4ULL, 0x0D52829D9B0B8DB0ULL, 0xF91DC4E10C844806ULL
        },
        {
            0x22887D2E7D35EDC2ULL, 0x3294EB133A250F72ULL, 0x87070DBFE5CA07EAULL, 0x27873B401FCFEF84ULL, 
            0x5D33590B0B96B6EDULL, 0xBF7B48F96CCEADD4ULL, 0x0CC3D7613ACC6AF1ULL, 0x008EF4BC7DAEFD4FULL, 
            0x0A36E48EC09F8702ULL, 0x6C252CD66F8390F1ULL, 0x2B3C5378B6872D7DULL, 0xAD6833718A950D5EULL, 
            0x41DD33D237142C70ULL, 0x1118A8888072692CULL, 0xC95BC61ADD0648F9ULL, 0xC54D268F008C2BBCULL, 
            0xDF36FD64CD41C13EULL, 0xB8E341E249431F91ULL, 0x7CD42E1C420B4505ULL, 0x0AF608668FFE5307ULL, 
            0x20E026F220123C38ULL, 0x69F70BAA633772D0ULL, 0x4517BF76057F3A70ULL, 0x46C77ED8C9AC5286ULL, 
            0xB560601F32F91126ULL, 0x7232CEA68429461CULL, 0xE97F4C91FC8EF753ULL, 0xAE3396A4C60E1178ULL, 
            0x84FB16CA9C267397ULL, 0xD6CE2AA163F2DF20ULL, 0xE4C380E7C49D6CF7ULL, 0xE23CE42C6AB4F473ULL
        },
        {
            0x15F5E12AA23BD054ULL, 0x7898960242A4E588ULL, 0xBC8798C1A408075DULL, 0x23749AA36F7A47DFULL, 
            0x5826F306CB74AC47ULL, 0x8BD423826320118CULL, 0x1E604186CDBC1027ULL, 0x636D0651A5F21977ULL, 
            0xF1A96390D05191B1ULL, 0x42A6377D2E6E2ACFULL, 0xF1482D6DDE770E68ULL, 0x137BB9BEADE73847ULL, 
            0x529B84D3549288D3ULL, 0xFE76387634BBAECCULL, 0x1106A9089D137E44ULL, 0x65E39CA5E0FA1D79ULL, 
            0xDF717B1975308739ULL, 0x71A9AF42E9DF6D4CULL, 0x20ED639180609E50ULL, 0xA545A7EB6A03715CULL, 
            0xE7C9957CBCC4F660ULL, 0xCF9DDE6AAFEEF79BULL, 0x20101453925518BEULL, 0x6A3103F48376D22CULL, 
            0x176A535C6AF585B8ULL, 0x77093AE1718FF6AAULL, 0x11FC363897FC3D35ULL, 0xCF37E1D902028407ULL, 
            0x1DAED9A16EBB50B0ULL, 0x7A0C51F01A5D08E8ULL, 0xF4934D844404612BULL, 0x608FE887A17638EDULL
        },
        {
            0x113BEFF0BB38CE28ULL, 0x6BC90FDA1D4EAF64ULL, 0xA328D38D68C563C3ULL, 0x23986032D56526F7ULL, 
            0x654A77D47C1ADFFAULL, 0x8933FEB4D68D252DULL, 0x12494D0535A378ECULL, 0x8E0275635AA476B4ULL, 
            0x9F3D5207A7559D0BULL, 0xEDDDDEFEC31B1F98ULL, 0x2D48B59EB35BF4B2ULL, 0x5C3DC1BF19A75C7EULL, 
            0xEA537C5F0B93F93FULL, 0x884B9A9D6EE212C3ULL, 0x838E77C7A5F644F2ULL, 0x9A04C54309624D4DULL, 
            0x541CA71835365B0BULL, 0x088A54F482F11F5DULL, 0x096D08430B1355D5ULL, 0x8A833D1684E08498ULL, 
            0x23B0639FA4993556ULL, 0x3C31A3D37D5105E6ULL, 0x409FBA5BD83DA825ULL, 0x59C518FDFC3810EDULL, 
            0x39F458C22E7A013CULL, 0x35062857CE5A14B2ULL, 0x32A5616E335C417FULL, 0x67EE362277D833E0ULL, 
            0x53CCD79458494962ULL, 0x9394D2ECF2C3D8F3ULL, 0x5C72A4BC7811C264ULL, 0xAA90F98FFCF524FCULL
        }
    }
};

const TwistDomainConstants TwistExpander_Castor::kPhaseCConstants = {
    0xB4DF1C7FCDD0B3FBULL,
    0x4D9516D054947CE9ULL,
    0x5BA6717F8FDEC6F3ULL,
    0xB4DF1C7FCDD0B3FBULL,
    0x4D9516D054947CE9ULL,
    0x5BA6717F8FDEC6F3ULL,
    0x1F270E5512F7D408ULL,
    0xA8BFCE52406CB2D8ULL,
    0x4C,
    0x60,
    0xEA,
    0x73,
    0x26,
    0x3B,
    0xAD,
    0xEE
};

const TwistDomainSaltSet TwistExpander_Castor::kPhaseDSalts = {
    {
        {
            0xA8CB772AB4F41306ULL, 0xE94AD8CEC0CD1CA2ULL, 0xF79798EAF9626D01ULL, 0x8D9CBAD38E36007EULL, 
            0x2E83AECB6F026F9CULL, 0x9EF583F9CA6D8AD8ULL, 0x6A5F4E0136A77BF6ULL, 0x18B582308A0DBA9BULL, 
            0xE0BC39FFC874ED8BULL, 0x29CF79E39167693EULL, 0x4006F943E77D342BULL, 0x8BBBDB8384DCC17CULL, 
            0x4E2E402D9A527608ULL, 0xBF7EFC7C40EE7B12ULL, 0x106CCC6F2C1602ACULL, 0xE3173EC30C6D95B8ULL, 
            0xB41354211CE3B215ULL, 0xF5B4CBDD094BD595ULL, 0x6402752CF4C7A422ULL, 0x5EC7B2E6B461B162ULL, 
            0xA284CC18CD94B841ULL, 0xEB1826DF01CCEB0FULL, 0x5D3E5F5FBC870655ULL, 0xC9666E69C495A115ULL, 
            0xDCD52C0B841BDAA8ULL, 0x41BD4B66BF2B6B14ULL, 0x01A5A4C7ECD652FEULL, 0x3E149ACF2412558AULL, 
            0xE4A39C15613FA2F8ULL, 0xA75ADCD77B1F108CULL, 0xC8A83CD25C559FA5ULL, 0x73A4C47267E158D1ULL
        },
        {
            0xAEDC150ECC404383ULL, 0x5014F13E2901971DULL, 0xD04B141D2E83FEA5ULL, 0x5FACEC7A9C5FF99CULL, 
            0x0613BD1059A9E205ULL, 0xDF2B48EE33005188ULL, 0xA966A837BCBBD28FULL, 0xDADE4D1FC9890684ULL, 
            0x10E61C1B4AD13946ULL, 0xD31B84481CDE4A32ULL, 0xB5B78B7BDE7AB1C0ULL, 0x8A3927FCE076BB40ULL, 
            0xCC7F7E06D6EDA96DULL, 0x30249220D9F288FBULL, 0x7E26403A56216820ULL, 0xAD4A1834E04AA683ULL, 
            0xE92AD3FD266805AAULL, 0x5771BBBA3C11C3E3ULL, 0x6193D3F51DBD1768ULL, 0x91756EB6FE21768CULL, 
            0x7720AEE625F96686ULL, 0x79E24466CFEF2AE6ULL, 0x318043BAEA92679DULL, 0xCBBCAA96B3E8E02DULL, 
            0x99B5F45302DE4C69ULL, 0x33E4E5B3D88906F9ULL, 0xC947366A99B78F45ULL, 0x336766B14EF1A479ULL, 
            0x1377637BFAD2DB81ULL, 0x3B956D834502CEB4ULL, 0x43AD59AC84BD8EA3ULL, 0xE7B7722765A9A3B2ULL
        },
        {
            0x8F0EDC051A903EAEULL, 0xF84C12778CF932BDULL, 0x87464E2B39A18737ULL, 0x9E44624104BCF46DULL, 
            0x13CFE6AC70906A36ULL, 0x7DB4C387E58B2DBBULL, 0x5BDEEE4B3AC664BCULL, 0x97A7689D9CBBD911ULL, 
            0xB126DADCAC9BD978ULL, 0x3F25664290031CF2ULL, 0xCB02722EF6F286FAULL, 0x4FBF8336E175423FULL, 
            0x322E6F1962F897CCULL, 0xF8028E42657751AEULL, 0x6CA10F3C42DBA844ULL, 0xF9575E353257502FULL, 
            0x13C96BAB3D9D07DBULL, 0x4E0D6A3DC628D534ULL, 0xACA05426BDE175DAULL, 0x46E21C931BD50B69ULL, 
            0x6F68664B7D5E1700ULL, 0x059015A939DB6775ULL, 0x4BE1CB40EF30149DULL, 0xA1492B160F31DB78ULL, 
            0xDE9FE43EECCD7329ULL, 0xB912C639A2A31DDAULL, 0xCC5F642071FB5BA8ULL, 0x98560C0153C606D1ULL, 
            0xAB229D116008075BULL, 0x5FE9334502ACF077ULL, 0x86077E009EE61061ULL, 0xB0DC07C76897C090ULL
        },
        {
            0xF852524371FE6A65ULL, 0x62742C440705BAB2ULL, 0xF60B24DA0C6052A8ULL, 0xF974D38FF63EAE64ULL, 
            0x1FC76DC28956B5F0ULL, 0xD0EA7165BE909EBAULL, 0xE8A60941D103524DULL, 0x66F591FA60B51F77ULL, 
            0x50D15963CA88CC22ULL, 0x9B4EB655D3BE1F27ULL, 0xBDB5FD74621FAD87ULL, 0xCC941041B2730749ULL, 
            0xDA30217F82155421ULL, 0xC7F20946F7CC14FCULL, 0xA58500201DD9BAD5ULL, 0xB026D012691D7AABULL, 
            0x161D4A7E9455BD34ULL, 0xA5FDC7A3C63DE74BULL, 0xAAE0C2ED1AB25DCDULL, 0x2760A7C5FF099388ULL, 
            0xFECD480B758C56D7ULL, 0xB74F0D4D00F4A0F5ULL, 0x3BC29BAE502ADD15ULL, 0xFB0D5D6030D07947ULL, 
            0x05844A4AF556449EULL, 0x6AA69E7A4036D233ULL, 0x08B23B7A9CB6AFB1ULL, 0xF402A4D6D3C18B1BULL, 
            0x1911A08DDDB987C4ULL, 0x7DA2E54E0AD86A53ULL, 0xD4EF16265F753D05ULL, 0xB7716F808C819DB1ULL
        },
        {
            0x38248EBE0BAB80ABULL, 0xCA0D5328695B05B6ULL, 0x2C2EEC3ED95E8EF0ULL, 0x197008B0DD335170ULL, 
            0x251C590F3D8A0653ULL, 0xBDDCC5A5DB0BEEEBULL, 0xB6D1B783E30D08B5ULL, 0x2D42002351D3B279ULL, 
            0xAB123E381E5A6EDAULL, 0xFB973D6D9AE50043ULL, 0xDCE2F8445181D013ULL, 0x3EF000FD6AC8CFEEULL, 
            0xF1B8B542A42168C6ULL, 0xCE14CB0743D3E726ULL, 0x0B327FBEB333409DULL, 0x95AF51E6C52D5155ULL, 
            0x75E7138F6E054CA0ULL, 0x9F7AAB5B39CB685CULL, 0x1D42A168EA7C39A7ULL, 0x8CAE7A5D8001BED0ULL, 
            0x9C1DE4276AB5F40DULL, 0x69C93B1E9C54A032ULL, 0xE0EA1E9C485839F0ULL, 0x4E794103FD607449ULL, 
            0xF8B56FDAE291E0E2ULL, 0xA1A21CBD6DF33330ULL, 0x594F4C1A2B89889EULL, 0x9C2387F9F2F9FAF0ULL, 
            0x1627C58CE9128141ULL, 0x69A751245E56E9F4ULL, 0x07C582915000503DULL, 0x209BABFEF279CCA7ULL
        },
        {
            0x0011E105AB8C632EULL, 0x4BBFD76378E93C49ULL, 0xFA79CD5449B0D05AULL, 0xC596F6DEBAEB9AB4ULL, 
            0xEB735F953729B838ULL, 0x3E481364840DE2B2ULL, 0xFA153C5353D8483CULL, 0xB6ED35343FA7B94FULL, 
            0x2C8BA5DD124AD1AAULL, 0xD18FCCE0C3C88AF3ULL, 0x1D104B6119FF15A4ULL, 0x6988990F66989703ULL, 
            0x019B9DE2F8E2FB69ULL, 0x4ECB6881C1DD977CULL, 0x3F8AB9469225C368ULL, 0xE7A887CCEED0101AULL, 
            0xF846543C01CA9A84ULL, 0x25481FC339A6781CULL, 0xD8C6B3642B85AC56ULL, 0x5D8E64C16B79EADCULL, 
            0x3FDA2F48B35F6388ULL, 0x6CA4006D85F417C2ULL, 0x7C581E356AB6C21FULL, 0x2256423BEF8752A9ULL, 
            0x4EA407469F77E9B8ULL, 0xAE862F3C353A3D58ULL, 0xA74DAD5B0D9857C4ULL, 0xEE0F07F5BBDC6C3BULL, 
            0xC95055B2127B5613ULL, 0x59AA7F094BB2B3D1ULL, 0xAAD3C0ABFA9B0AA4ULL, 0x801D67B3BFEC1903ULL
        }
    },
    {
        {
            0x4455439731A2E252ULL, 0x1707FFC93318318BULL, 0xB18A0A39A321A5DDULL, 0x9DF4B58FB7683F89ULL, 
            0x14E6D48A2C2534B7ULL, 0x36A5361348FD3C40ULL, 0xE5AAB51B6E49597BULL, 0xD24BC934763A2F81ULL, 
            0xAAF5157C9C32C57BULL, 0x39F6FE9C6EBE1465ULL, 0x86B9D5AB962D805BULL, 0xC3110A3BDE1773B3ULL, 
            0x5A335112C60A2433ULL, 0xC3623E7215096042ULL, 0xF97A9A7A50F6FABCULL, 0xC9078D908D0789F8ULL, 
            0xC1697D00FB84FD00ULL, 0xD3C168A79F3C4648ULL, 0xB93FB51DBD41EE02ULL, 0xCF853AEA5EF2EEDFULL, 
            0x4FDB3789731C468DULL, 0x566A31538092A249ULL, 0x61EC6DDFE04CA63DULL, 0x3B47C997864DDEBAULL, 
            0x47708CBA90544178ULL, 0xDFE1B0537A513074ULL, 0x9F66D0C51330C536ULL, 0xCF63DC2B537F1B78ULL, 
            0xA514ED81E98B9641ULL, 0x8757B5ECC4D0E532ULL, 0xCE697ABB3C6EE4A0ULL, 0xDD77C1B21CA0F57DULL
        },
        {
            0xEF2E7C38CE0A93F1ULL, 0x240D2AD6B5697630ULL, 0x4091343D1DAC2CE8ULL, 0xDFCA39E64909E17FULL, 
            0x6A7D748CCAA9D881ULL, 0xD19453717A58308DULL, 0x7CE3C117663CAB7DULL, 0x4A7F3DE691E1B8E5ULL, 
            0x542A24554FACCBF6ULL, 0xC9174F5A5FBD235DULL, 0x36DDC3827D0A80F1ULL, 0x971C713FCEA65F8DULL, 
            0x4B7CA68D8BB9B970ULL, 0x831F87E63F2BDA29ULL, 0xB1DFB080A79CA2BEULL, 0x6BF19B29F0361CC4ULL, 
            0x6BC3E48019E104FEULL, 0x9053EB354FA67856ULL, 0x3BFED7DCBB8D726DULL, 0xAAEFA08D0B89E886ULL, 
            0x8E6E5DBCD70D7493ULL, 0xBC731C0B60A9CCEDULL, 0x04B7969CC4630A6AULL, 0xA8621E33053D8D1BULL, 
            0x6F3B6494AFC80FCFULL, 0x39D3272B0C8D8BD8ULL, 0x9EA4769399D47791ULL, 0x93A45BA82F28169BULL, 
            0x3106FF08F1757993ULL, 0xD345A4B58D40B86AULL, 0xE3E8CD59E2E79486ULL, 0x01B5FD8E8B722F90ULL
        },
        {
            0xCDD02718122460BAULL, 0x2687C39368BB5417ULL, 0x0AC046D587299D6CULL, 0x73B78EB18F8DD472ULL, 
            0xA1FA4330B88C7CD5ULL, 0x2D91CCC8DFBF5FC2ULL, 0x8C795EC763349A9AULL, 0x1138C86B62B78CFEULL, 
            0xE869922D613F49D9ULL, 0xDCB10B05477FD17FULL, 0xA9B141E67164ECFCULL, 0x7E59260E859EEC63ULL, 
            0xAF6C288F43B6BF95ULL, 0x7F92776ECF1730B7ULL, 0x4DA1C94ED14EA6B2ULL, 0xD2667963285F0048ULL, 
            0xFA89B9B0B404C3ADULL, 0x5C5CB84E4FFCC119ULL, 0x200E29276908B595ULL, 0xFE3B2782B47BAF48ULL, 
            0xF021C1613700BB72ULL, 0x1CF947944A5D2AD9ULL, 0x2E899438509CA315ULL, 0x771090FA9C33CC2BULL, 
            0xA4737F44F0020753ULL, 0xD57DEBE0B2070ED7ULL, 0x5071CA8171A0B0BCULL, 0x465906175C0C696FULL, 
            0xA4C9677A51E3F31AULL, 0x3F8ED106614C0494ULL, 0xE353E110E5577713ULL, 0xA42A0A8011E52FDAULL
        },
        {
            0x58A3E2FAD77A79EDULL, 0xA8EF896A5EB405C2ULL, 0x975AB3AB13EC362AULL, 0x0D786A04179E343EULL, 
            0x799DB1C919A792E7ULL, 0x69EFC14810F462FDULL, 0xBB8177271A51AA13ULL, 0x1C8EFB19C89E074BULL, 
            0x227628CE173D374EULL, 0x75FB833282D01D28ULL, 0x63F43E828E0809ADULL, 0xE5F2653AD930849DULL, 
            0x0647C58601163141ULL, 0xBAFFFC541B0BEF1BULL, 0x29A474EEBBF81A40ULL, 0xB0C538FBB087F984ULL, 
            0xE800EDB92720B555ULL, 0x511871AB228EE277ULL, 0xB977269F00F675FDULL, 0xB95621515BCDC2F5ULL, 
            0x5F4836F8013DAAE2ULL, 0xC9BDCFA3E8E3703EULL, 0xE066C2BCFD7DB0C1ULL, 0xDC422A522C44FD70ULL, 
            0x00ECCBA2264A49A3ULL, 0x7A9BE126677F78CAULL, 0xB34B02296E7DD6B3ULL, 0x3172026585F00048ULL, 
            0x245CD4888698C103ULL, 0xA4EC8170B38546FBULL, 0x327DD87A68CED320ULL, 0x2A45FA51ACCB7640ULL
        },
        {
            0x12A29507358E9CC9ULL, 0x6CD19F257A770E0AULL, 0xF5DC9C08DA06039BULL, 0xB12038CD75514008ULL, 
            0xC7F284760965F89EULL, 0x18D6818C1635721AULL, 0x364A378F5E1474DDULL, 0xA242F19554757C0AULL, 
            0x76242E9BADF8EFBCULL, 0x7750DD08E822FDF1ULL, 0xC812491BD1D7406CULL, 0x847FD7C328971183ULL, 
            0xCF53274B747C0C56ULL, 0x328CA23A672A05F6ULL, 0xB8053897B26A0FE2ULL, 0xED3A8D1AE1DCA6D5ULL, 
            0x75E0DB2666E88CF6ULL, 0xAEE32AE54613831AULL, 0x13E99780CD26C091ULL, 0x5A560A5041283BDFULL, 
            0xCB3F9F5491CA9D95ULL, 0x1CD14D3D378B888FULL, 0xBB767D26A03F8107ULL, 0xA8C30C99CF8C491EULL, 
            0xBE7FA2184C4B070BULL, 0x82AE509B71E4882CULL, 0xF0B4342E4368EFC1ULL, 0xC0E0F88839B20D83ULL, 
            0x5BFC54283CE8269FULL, 0x2C62C8BEEF0244FAULL, 0x7348E0CEEE0F9622ULL, 0x25948CE1C431036EULL
        },
        {
            0x0B7CAD3C725A5361ULL, 0x69C05241144D07FFULL, 0xEA4B2ED7FBD9D950ULL, 0x0FDF8DBF8252ABD6ULL, 
            0x34525D30333B2AD3ULL, 0x8BA4D6D3E310D3D7ULL, 0xE4022A57E08F7421ULL, 0x2782DB8FC8B4CB88ULL, 
            0xE4A4BFBBF0FF1C47ULL, 0x1C32970C55EA191DULL, 0xD57EA1A3BA0F03ADULL, 0xB13EF4F25ACCD040ULL, 
            0x7E465AC358A17BCBULL, 0xD635B43171660178ULL, 0x2AB6F1EE826FA875ULL, 0x1844DB0AA9EF0D59ULL, 
            0xB0F1F8144455D447ULL, 0xD4BD8E5DAC10F71BULL, 0x11F93CE27A4E01B4ULL, 0x9347445D26775612ULL, 
            0xEBCA4A4E6A28222FULL, 0x863D0469C6D4E2D5ULL, 0xBFAC87EB55A42946ULL, 0x9BEC6678AC745505ULL, 
            0xA18084D0B88BDF68ULL, 0xCA9833398950FF26ULL, 0x7754C3448FA7DEE4ULL, 0x4C17E600B60784F3ULL, 
            0xBF7187A3104CC3CBULL, 0x68795F12B55BD655ULL, 0x3346BA02282625E6ULL, 0x3B6563C6F8FF5EB9ULL
        }
    },
    {
        {
            0xB39A60019E6905E0ULL, 0x5CC70AC02C8D2DF7ULL, 0xE4F33677220D68D0ULL, 0x7B9A274FAAB6B0F6ULL, 
            0x3C56BA5A972FA3D3ULL, 0x656AA151FD4D6D87ULL, 0x0B44EB2C5245E05BULL, 0x788D040EF6EF6FA4ULL, 
            0x941180709EB0318AULL, 0xC802F727E62A2F6AULL, 0x24160D6FFA6BE6ABULL, 0x02F677B4F84E7E86ULL, 
            0xEC895D330F5B1026ULL, 0x09C06BD6E509BE0DULL, 0x1AFE90DE6AEA1BECULL, 0x674BC091786AFCBCULL, 
            0x4FE3615D30614D8FULL, 0xE9835844D62019DFULL, 0x3B5D47E19E67FC07ULL, 0xADFD9292B8BEBE38ULL, 
            0x8F7691C15DE38C44ULL, 0xDD40D0C28893600BULL, 0xDB2702AA2250C3D6ULL, 0xC124CA33E0F949E8ULL, 
            0xFB255D63952A45F5ULL, 0x13036F97D28A4924ULL, 0xAEBEB754F629A160ULL, 0xBFF868EC124879E9ULL, 
            0x98344290D513FFCAULL, 0x256F52CB516C3F0EULL, 0x908D09745CB25DE0ULL, 0xD931F6F202D69D43ULL
        },
        {
            0x3B50905AC8E96023ULL, 0x31EE2E5A6951E9E3ULL, 0x44275D96EEF3A71BULL, 0x4DCDFF0BC64F070DULL, 
            0x4AA6F70460E7D8DAULL, 0xC3587C9B7B3A269AULL, 0xE43CB657DD48C9E4ULL, 0x99E3456A6335015EULL, 
            0x981AF343CFF1CE24ULL, 0x80ECBF29C835187FULL, 0x9CA98344B27E92A8ULL, 0x5D14CA1478460988ULL, 
            0x92CD5E6D0EF45FD1ULL, 0x6B3741327B8B87A5ULL, 0x3DE2997F0B52D234ULL, 0xC35248237435271AULL, 
            0x2BCFB06FD3BAE096ULL, 0x53427D60A82FBDF2ULL, 0x52152A93D8A86673ULL, 0xDDC6B32F3E33ECCCULL, 
            0x3117548E6F539A07ULL, 0x634631B5684F1E49ULL, 0x20136B031344C1E1ULL, 0xD18DC5104BC71554ULL, 
            0x6167FC1B4A45C67EULL, 0xC1C243713384A6F1ULL, 0x55B08CEDDDD647D1ULL, 0x749769F28BD98336ULL, 
            0x9068439860827020ULL, 0x77AD236E9A713830ULL, 0x51D78C66ADB5BF98ULL, 0xE6E7E8FD3AC88BCAULL
        },
        {
            0xF8319D34DF53B9A9ULL, 0x7B5CAF66D5AC342DULL, 0x6837B7D671B3E67BULL, 0xE7C564B37F2F17CCULL, 
            0x97500D24471F964AULL, 0xCFBE45DF7743BB5DULL, 0x60A6991AB6C49835ULL, 0x497DBE4FEF639D14ULL, 
            0x846C328FF5255B65ULL, 0x7EECCB32872C1C6FULL, 0x98466CF0D3E68F75ULL, 0x619FECF52AADCEAFULL, 
            0xC0CCD673FD061640ULL, 0x6DB2258EEF9E8C1EULL, 0x9B5D7B5B111269AFULL, 0x4576CBE8DF6DAC74ULL, 
            0x65D67FBFEE247F76ULL, 0xD3DDEFEE6B5E52BAULL, 0xE17C8DA097F5033DULL, 0x0EC21C649C155AF2ULL, 
            0xD2480A2CCAB8F8DFULL, 0x633C8D3A66B78F0EULL, 0xE3DF4773CE69C6A0ULL, 0x858800F81D759C96ULL, 
            0x2670AEEFB48844B8ULL, 0x02FC4EAA48609D06ULL, 0x57A049B22551865DULL, 0xD1B09C91BF45BE29ULL, 
            0x9C3FDB5964F951E4ULL, 0xB051954B3A59CA87ULL, 0xE1DD2A3D1D0B9854ULL, 0x7FD592B137A9F58CULL
        },
        {
            0x70D45E619A0CBBC4ULL, 0x5289F78334179387ULL, 0xB1B4EB2DFD783224ULL, 0x9A13903D97A190A8ULL, 
            0xB4C1D71D569D5090ULL, 0x90531C3123113DBBULL, 0xC3E17E906C42DE65ULL, 0x5A740589B3887580ULL, 
            0x664F74FE03B11889ULL, 0x161D27013E74E5B7ULL, 0xC7E3D007A7E61819ULL, 0xFFEC119C4FE59F4FULL, 
            0xDAAA6E6A69E253EBULL, 0x9A7E069DDE042220ULL, 0x33DB4BA4C405B6C4ULL, 0x6DD50B8E3A7DBDD5ULL, 
            0x096674DCF102565AULL, 0x0ADCE0494C8D7B88ULL, 0x3067E7934E9C0FE6ULL, 0xD43B973D28D323DCULL, 
            0x2D16F724C7A08630ULL, 0xBB21475B3C7D10FDULL, 0x6C6EFCFF814D369FULL, 0xF54D3B2BFB14B8D6ULL, 
            0x741D42EFF6F01CCBULL, 0xDF67B256D82F0A9BULL, 0x1511FC40B653ECFFULL, 0xA92741F73F273E0EULL, 
            0x3F8E071F7AA99C2AULL, 0xB066393F0EA47B64ULL, 0x9E317FE5FE8625A7ULL, 0x267EB3E704B55914ULL
        },
        {
            0x61C29D7774E86168ULL, 0x8E3EC52A04683478ULL, 0xC209EE65B5FD4351ULL, 0xA488D0F11CA4D2D6ULL, 
            0x0578F672E0DF5E6DULL, 0x79B527E1D8D5AF64ULL, 0xE2AB0ECC4D2382C9ULL, 0x380D44AB44F6A82FULL, 
            0x800D71F17DFAF005ULL, 0x2CE1ED00C8C88CACULL, 0x534D92C4EC38F123ULL, 0xB5A91FBE393B9173ULL, 
            0x1557E40FB81783C8ULL, 0x8F32AC76BBC60751ULL, 0x6BE8A17E94CB0AB3ULL, 0xE8213D6798CA151BULL, 
            0xD98450F6E856D4BDULL, 0x293647D037AC9CE0ULL, 0x58AAD1DE96E34A62ULL, 0x0732DDAC861D5DB4ULL, 
            0x2AFD7A6F3700F004ULL, 0x0F410100E7957823ULL, 0xD8E72FAE25465B16ULL, 0x5DB5C53EA9117EB8ULL, 
            0xF64CCE761BE7C26CULL, 0x263359966EA6E437ULL, 0x51AF652431B6C597ULL, 0xAD00725F116FD3D8ULL, 
            0xAF10FAB6E07D5445ULL, 0xFBCDA3CB25AAB8D1ULL, 0xEBAE4A0237732683ULL, 0xE7450B11430D4CD9ULL
        },
        {
            0xB8C5095E1575FD29ULL, 0x4198B252636676C7ULL, 0xAB4F01D1BFD0FB08ULL, 0x219226F3A170EAC8ULL, 
            0x1211315CB0DDFABBULL, 0x46CB7A007C326E15ULL, 0x03A0F69A26AD6BDCULL, 0xA8D88D5D21553029ULL, 
            0x2FB81DEAF2573F5DULL, 0xD176EB757834C29DULL, 0xDBBB7574B154C538ULL, 0x2B818F9F3C57E6CDULL, 
            0xD159DE165DA7240FULL, 0xBF616B94D2CEC20EULL, 0x1C6390B6D898122EULL, 0x60CB1DB64EE43F17ULL, 
            0x61555DB1D0D513C8ULL, 0x59A6126596B5CD98ULL, 0x0E3BF0E859055450ULL, 0xB8CB4053099A51E4ULL, 
            0x1E4D014E07B7FC31ULL, 0x31556C2859AF567EULL, 0x6454B3B0A9495B79ULL, 0xA9EE962697C9877FULL, 
            0x68D35D55A7344825ULL, 0xCF96A16C9B81DF8DULL, 0x02C5600E266E3EDAULL, 0x7EC2A8EABB79EFFCULL, 
            0x7BFFC4F57F6261A6ULL, 0xFF5D5A7062DDB419ULL, 0xBA09156D704A8884ULL, 0x69902C5FCD9E2D70ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Castor::kPhaseDConstants = {
    0x453BEEC0367B3E87ULL,
    0xC49EC9F206BA3857ULL,
    0x977EB605149C3761ULL,
    0x453BEEC0367B3E87ULL,
    0xC49EC9F206BA3857ULL,
    0x977EB605149C3761ULL,
    0x13874C69B8420C32ULL,
    0x2DD7DADE582B11A2ULL,
    0x23,
    0x02,
    0xAD,
    0xE5,
    0x65,
    0x02,
    0xAD,
    0x77
};

const TwistDomainSaltSet TwistExpander_Castor::kPhaseESalts = {
    {
        {
            0x9CFB32175E264DC8ULL, 0x436B18735BABF046ULL, 0xA55AE93561253C76ULL, 0x497BD54C412642CEULL, 
            0xC82EA5C407A61535ULL, 0x0B4FA72212727281ULL, 0xBA540DBD4BF0CDDAULL, 0x256E5BE03BB74CC5ULL, 
            0xC40EC2922AD6EF22ULL, 0xA0913617FCB0031DULL, 0xEFBB27F046F88552ULL, 0x8ABB002550982A02ULL, 
            0x6618F0F6542261E6ULL, 0x37DBC5F17430606EULL, 0x0116D17670086438ULL, 0x19F4214D296D1FB2ULL, 
            0x8877619DD5725D60ULL, 0x8400DA5B7E2DB17AULL, 0xEB9F460109FDEAE5ULL, 0x29A5472FF1970461ULL, 
            0x4BF9439073B5613FULL, 0xBD6FDB5BD7AD8659ULL, 0xE9DD0BBD6EE82023ULL, 0x1C6656EA0D1A1AC8ULL, 
            0xB6DF203A66CC4D3CULL, 0xD6408D6D8A9A1916ULL, 0x99A14C14D31EA22AULL, 0x9CEA9F9C23C87D25ULL, 
            0x8657D98F3C11EBF8ULL, 0x82F0A24CBD6083E6ULL, 0x3A5CECB70FC8EFFFULL, 0xDF385F890BE8054AULL
        },
        {
            0x03D6FFBFFB6BF808ULL, 0x0174DD0FDE142CF7ULL, 0xC56431F6B88BC5E7ULL, 0xAB19CB031F675441ULL, 
            0x2B4175EEFACCE885ULL, 0xF3D494D8E6D1A9CCULL, 0x5371EA0D445C4C37ULL, 0x6C9D74CB48BCE3ACULL, 
            0xC63FC854E0D6F52CULL, 0xF39FB8FBEDFF7CDDULL, 0xCA5621CCAC5C046CULL, 0xF96868B20C9F3DE4ULL, 
            0x818FD6F5A43BE10EULL, 0xA0D1AB7700072973ULL, 0xEC999D5A860C6884ULL, 0xD9FA92B38AB81644ULL, 
            0xD4BE1CD5B649D896ULL, 0x09E75F2445D69008ULL, 0x1344D8AE0BCE9FEBULL, 0x843976FE48C258D6ULL, 
            0x9E1393A63568D838ULL, 0x6832D07B7C6D4E71ULL, 0x65AFF05C5415488FULL, 0x549D62B93C189B67ULL, 
            0x7E519C44EEFEA660ULL, 0x821E91C7E059E148ULL, 0xA365FC2AD1538C29ULL, 0x537B9F82BB2C8A89ULL, 
            0xB88C0881E654B50BULL, 0xE7D4604C481A7DEEULL, 0x56D3EC6835BB1747ULL, 0xF62EEFB5F0D350E8ULL
        },
        {
            0xBA15C5AFBDDE1E2CULL, 0x9133ECF3AFF8F41EULL, 0x1F9043C191C7A51DULL, 0xF44E71921E31E082ULL, 
            0x60825A496E40DB26ULL, 0x7F834A7B476A43E8ULL, 0x95D3F0A2D30B495BULL, 0xBBDC453BB3AC0C6EULL, 
            0x115731BD88423440ULL, 0x50649FC655589521ULL, 0x40DB624A95D96DACULL, 0x29A1C0A819A2C3E0ULL, 
            0x1B5D5C7EE5F10EC4ULL, 0x92DE7F5CEE2F2103ULL, 0xC8AC9D0F473D8F6CULL, 0xC01DB7DEC3AFA402ULL, 
            0xD7C3F7C64794E01DULL, 0x9D0FC3B38E7D2883ULL, 0xB9F5EE88F89F55E8ULL, 0x6E70FA7902A64737ULL, 
            0x2B5DA52C62B3866AULL, 0x66D17381C5DB3E2BULL, 0x96A96CA9CFAB6EB1ULL, 0x74166E9D6CE77606ULL, 
            0x3C555E285C0ADEAFULL, 0x1FBCB3C6E13543C3ULL, 0x9AE8B935E2B9511DULL, 0x3CE8335056883365ULL, 
            0x9DD0FF9F20F02681ULL, 0x9C1995922D1A8820ULL, 0xB16D3D55E42C32E4ULL, 0x7D07B63B5F7B2E18ULL
        },
        {
            0xCBB3E8A513ADE2F4ULL, 0x7D63F388D9737057ULL, 0x5F909D240801BE81ULL, 0xB6386F4828E13DCCULL, 
            0x30304D8B780B6D0DULL, 0xB6E935E2F2D1F70DULL, 0x898B4122FAD10D32ULL, 0xF099C959C61B8FFCULL, 
            0x85DA32FE6AB67FD4ULL, 0xE68D07CDA4BA7391ULL, 0xAC4D2193246FAD06ULL, 0x34396BCF5274D0B8ULL, 
            0x1CB5883E59F08C50ULL, 0x51A21F986EFCDA17ULL, 0x9D610BC2FAF11BFAULL, 0x6712C53123805D57ULL, 
            0xC598B9773B874E63ULL, 0xA56F1D71FE2BE1B2ULL, 0xB76C5A73694B35D8ULL, 0xB92DDD159243E010ULL, 
            0xD25150472F850179ULL, 0xD8ED626D196FE4A1ULL, 0xF525E460AE3B40CCULL, 0xD585239AA18497AFULL, 
            0x07A1BE9F8F562AEBULL, 0xC786701E51AAB26AULL, 0x1B76E68F902F4863ULL, 0x5D658F920D0427BFULL, 
            0x630430201BDB66BDULL, 0x9BB286DB758F811CULL, 0x25D088132A0D1FE9ULL, 0x81D9FB5007567496ULL
        },
        {
            0xB9061F0E80C52C17ULL, 0xE121013880793420ULL, 0x671401D304A5744FULL, 0xCB2B6CD783E38C46ULL, 
            0x8DAEF43BE2443B30ULL, 0x303E8109ED5D5315ULL, 0x09D015DC049FEC8EULL, 0x8B243515F713290EULL, 
            0x6C36D7F3FD022D3CULL, 0x6FE633EFDA098BDCULL, 0xC244CEA67B32B000ULL, 0xAED1B28BB27A0278ULL, 
            0x35886573DCEEB06EULL, 0x77CE818DC64FE8AAULL, 0x44282C8E32F5625DULL, 0xCDD7BEE5C4C10A83ULL, 
            0xE70CD22A4AB1D2D7ULL, 0xEC038848561B570DULL, 0xEE1446803A309C9AULL, 0x64B9E99BBA23ED83ULL, 
            0xFBE883FD0CCFD50DULL, 0x55CC03C1CB434E53ULL, 0xA1B28256D68F1C65ULL, 0xA789341F8582796FULL, 
            0x6F7DF92305CACDE6ULL, 0x5A249B8B01322048ULL, 0x51BAEBD096E06728ULL, 0x3E49A93E60AA7375ULL, 
            0x8E1F02889C096ABDULL, 0x6D2EC61E51E40F66ULL, 0x00A2F677F057E2DBULL, 0x613D0D45EE9B8820ULL
        },
        {
            0x9BB1FD0D57D265CAULL, 0x8B423FE7A4D05501ULL, 0xD9ED804EEFB7B34FULL, 0x6B6E0F0E74CEA3C8ULL, 
            0x643CFEFEF5AC5D0BULL, 0xE9ECB985B753CEDEULL, 0x26D57BEEB21B53AEULL, 0x3EFDE0A8DE334C54ULL, 
            0x9041E1E7B20CCFC0ULL, 0x62CF88FFA3B32F7AULL, 0x6656C4194BC87ED4ULL, 0xCD2EC0E8AB8166FFULL, 
            0x7DB164112B069F90ULL, 0x2B18A7D478BFBD48ULL, 0x8B0309DC045C09DDULL, 0x4C2FB9EDC34DE485ULL, 
            0x294AAA63B7E5D27FULL, 0x08D231FF27845B97ULL, 0xA73B2D2114BEE87CULL, 0xF26D766F5EAE3279ULL, 
            0xA591CD8C61322809ULL, 0xDEB300A6DAAD2DD2ULL, 0x8C5ACD71DDEBEE6FULL, 0xD71C95058FD661DDULL, 
            0x4C034A22B82F529FULL, 0x9EC501659674B5B9ULL, 0xE8FE6387B3C1D2B3ULL, 0x05E2C1236FBE087DULL, 
            0x4E40B4633A86F744ULL, 0x85CC1C7B2D5093F3ULL, 0x64D1F4A35D14905EULL, 0xF56BEE0A224CFA11ULL
        }
    },
    {
        {
            0x5FDC1D26E7C146EFULL, 0x5E1D2E83F8B185FCULL, 0x1399B0B1B83FC5E2ULL, 0x212C97F40C008F3EULL, 
            0x01954E87298B1100ULL, 0x105537239CE32D94ULL, 0x33596F9AFBC804C9ULL, 0xD35B29B0FE1B6EADULL, 
            0xEABFCFD69A462F8DULL, 0xD2FED0B4458BF6D1ULL, 0xD44137BB2F15ADB8ULL, 0xEF3DA7EB9A9274AAULL, 
            0xFB6BF3894DCBBAFBULL, 0x5E2AAF49E318CEC1ULL, 0x6B47DD7D675344ABULL, 0x9437F247CE226768ULL, 
            0xB26893B0401B0EE6ULL, 0x8BE24ABCA090E6A8ULL, 0x08560E9691C7C25EULL, 0xC13790094E1F3832ULL, 
            0xE5F4C0421B0F9075ULL, 0x52C7052E8BE1E048ULL, 0xBE1F90DCA4086367ULL, 0x3D729E44C7E56FD2ULL, 
            0xE8F42E6F3BFDA22BULL, 0x33EA28945070CC5EULL, 0xF7899F009238BDBEULL, 0x387C691A052232FCULL, 
            0xAED23DE5F09581C3ULL, 0xCD4615658B84585EULL, 0x92AEDBFDB1519B68ULL, 0xA7A0DEB3951EDEF1ULL
        },
        {
            0x6469A19C2FAAC527ULL, 0x8CB9ECD0968CE73CULL, 0xC9FB48DC351D9763ULL, 0x2D017CA7972C2C20ULL, 
            0xBE5D6C25DF293148ULL, 0xFACCB3FA31C3B0D7ULL, 0xC1E1F5C22B17838EULL, 0x0306963491E7750EULL, 
            0x83D671EFAA96A6C6ULL, 0xBA4FB53C9C0D29EBULL, 0xB78B8D23B0F43DE7ULL, 0x979AE3A9575F9EF4ULL, 
            0xBE9804237054C60DULL, 0x9544BDE7CFF92C3AULL, 0x6D37233BF493CC2BULL, 0xF29FA986684ADF45ULL, 
            0x4B486407885104A2ULL, 0xD782BD093C4CC595ULL, 0x63DFECF90EA22CDBULL, 0xD38D0FA3781379ABULL, 
            0x8AE4871D5A322BDFULL, 0x2F785C80971F619DULL, 0x1B75ED2495B0D7E1ULL, 0xCE79F834F675767EULL, 
            0x0157B42DDF47A637ULL, 0x7A41F36732747A0CULL, 0x52B6F5910EA7A3A2ULL, 0xBC421965BCFC04CEULL, 
            0x84C8B83333D7A4BEULL, 0xA4B4621B5C04010BULL, 0x9EC228CAEE741B0EULL, 0xDEA31785B2C2AA4FULL
        },
        {
            0xF62C403EF0680FB2ULL, 0x5064514C92E3EB59ULL, 0x8C544A13D393194AULL, 0xD00ABD196A88F6E5ULL, 
            0x9B6E4E28EA20CD3BULL, 0x10D2095BEDF0D732ULL, 0xE297535504CD3D00ULL, 0x79CDB053E3FB9E6CULL, 
            0x63C9C2A120EB2E23ULL, 0xC8F0858477CF2A81ULL, 0x447EA142D8684CAAULL, 0xF7F35B3472EC5949ULL, 
            0xB011B403FC629C62ULL, 0x2CEE7FD5771342F0ULL, 0x42D11F01308173E5ULL, 0x57CEBFCCE8DCD4CFULL, 
            0xFE518F19ED15C9B9ULL, 0x5ECACBBC265A1F6FULL, 0x7EBE6B6D964F409EULL, 0xE4BAFE7CD23E9A32ULL, 
            0xB3FB28B828E2652DULL, 0x4B88556B989409DAULL, 0x08A17B78381D492AULL, 0xFB5B19582EA88E9AULL, 
            0x687EE6FB56BE2A13ULL, 0x3804FA9EB5BABFCEULL, 0x0654AF937527AC95ULL, 0x324AC2B31DC458FEULL, 
            0x844C708C4DC62E2FULL, 0x7FDBE1658B07ABFBULL, 0xE311899A3AE0CCDBULL, 0xB46C6FE46E2BC4C0ULL
        },
        {
            0xBD82F0762112950BULL, 0x1D88536E52CEC531ULL, 0x4DD49EEB307C590CULL, 0xC3D5AD24C825C7D4ULL, 
            0x3381DC57E669BE45ULL, 0xACF65D083F28FB64ULL, 0x8A40F7F846E8EC85ULL, 0xF613FCAB5741A8A1ULL, 
            0x5230E829D1D4A79CULL, 0x0617E52936BF00F0ULL, 0xB0B8C58BF826EA1FULL, 0xC39BADE0964FB162ULL, 
            0xD0A03C09FEC1E790ULL, 0x260CEBA901072A39ULL, 0x1D7090A12E5D0499ULL, 0x19F5B451CFE96E66ULL, 
            0xAA7F01378CEBD2E4ULL, 0x45A77B5360F062C3ULL, 0x6D89A3059A322158ULL, 0xF29C5D1B123FA666ULL, 
            0x402E9A3747801980ULL, 0x03D41D19A04F32AAULL, 0xF5F732F73BE44C73ULL, 0xA1EA13E7E532AE60ULL, 
            0xD02CADC1FD8CA1A4ULL, 0xA922BFC15FAF1651ULL, 0xDDD88F0DADAA6FBBULL, 0x7B5A9D468B6EAF03ULL, 
            0xB3E77A75BAE83CB3ULL, 0x1F61A57D48CE5687ULL, 0x1286B9523FBA28DAULL, 0xF43C7BE46A8549D9ULL
        },
        {
            0xA65E9F57107A75BBULL, 0xCA77A83E023876B5ULL, 0xCF4ACBA262BF55A2ULL, 0x459E89F073015976ULL, 
            0x4C0E38CCAFB0E52AULL, 0x98AF37CFA0D6023CULL, 0x218F61E43242B2DBULL, 0x548F6D63FAD6A647ULL, 
            0x2C1898C5A784D139ULL, 0x2E6E4EA8AFF3A793ULL, 0xFC994050127D3071ULL, 0x83EF6FD7083FC5A7ULL, 
            0x915D5749C43576B2ULL, 0x48F2688560AA7477ULL, 0xB47CA6E9D0B4FC2AULL, 0x2DFDCB0D7A512312ULL, 
            0x8C310C01FC182224ULL, 0x0F31F3E3E069CDA6ULL, 0xDA5B4F4AC848ABA3ULL, 0xDCEBF0D4FF19D659ULL, 
            0x5450FCA37DE5F3BCULL, 0x98F536660903A27AULL, 0xA2D27B42EEFED96BULL, 0x94531420C4B91303ULL, 
            0xCC5573059A59D03DULL, 0x46D3AAF3E764BF96ULL, 0xDCFCA20EB7E07547ULL, 0x1A6C690CC18BB35AULL, 
            0xE7A95A0036E43F74ULL, 0xC22324406A680C4FULL, 0x1F2D214BD16190F5ULL, 0x6C3C9530EB9F5BC8ULL
        },
        {
            0x9207BC711A96F3A5ULL, 0x656722C45B2BAC38ULL, 0x81A9556F79F99B3DULL, 0xB9423E0E44DE1A21ULL, 
            0x6558C989BFF25C2DULL, 0x95E778414BBF1B11ULL, 0xF2765A3E6C49AAECULL, 0xFA83D162A8E8ADDBULL, 
            0x3868F453A85988B6ULL, 0x9438B6055D224380ULL, 0x206264E20212635BULL, 0xA4A81AB6BA1DE400ULL, 
            0x081FF1C768B2C3DFULL, 0x23104DA65DD95B34ULL, 0xAC42488E665BCFD4ULL, 0x5324323789CCC725ULL, 
            0xD707F0F99AE1426FULL, 0x5F2BF5F6FB0E3EE3ULL, 0x3197938682884321ULL, 0xDE466D2FF68226BDULL, 
            0x658D382A6E0B21E3ULL, 0x47726AB282859A9BULL, 0xBE7765385ABD985BULL, 0xA84279D81AC423F4ULL, 
            0x09CEF418268865D6ULL, 0xED07B97AF4C84D46ULL, 0x7F2424A8F436E7C5ULL, 0xA042017933BFA2CEULL, 
            0x45DA50D1ADFC5BD9ULL, 0x3591420BC891D26EULL, 0x34DAC0BD02268F35ULL, 0xA5C09EF5D1A0C562ULL
        }
    },
    {
        {
            0x458950868D3901B6ULL, 0x4EB97F8D52675E5FULL, 0x31DA412D1528489DULL, 0xF85FF2066C2F63AFULL, 
            0x8607C580620AB7C5ULL, 0x3358655240C3B2D8ULL, 0xE724D90E9E452076ULL, 0x7F158B9BB280882EULL, 
            0xFE3E711BC0A6B697ULL, 0x82AE28F52EEDBA0CULL, 0xE26E5115D19AE9AEULL, 0x529863F117052286ULL, 
            0x498793D25947784EULL, 0x0645872B5C91EA19ULL, 0x69C3C689B48F39A3ULL, 0x3826D5E6C9458F46ULL, 
            0x98484EFDA3037085ULL, 0x029726A96DBDA845ULL, 0x927BD37F0D41EDA4ULL, 0xA2A1D7D4A99AFE8EULL, 
            0x9B1F92AB044465CEULL, 0x5C52CA8AB5DE1084ULL, 0x43E2BFF28A688A67ULL, 0xA2A92187E6603403ULL, 
            0xE06211A9FC34B00FULL, 0xC15B9A113185E00FULL, 0xB8C38C3FF533BEDBULL, 0xC5D58E9363DEA370ULL, 
            0x988A7A7483808607ULL, 0x9E1577D998312AE3ULL, 0x70CEEEFF8AC3C9E2ULL, 0x157D0DD0A6560FACULL
        },
        {
            0xA47F31CACCF07508ULL, 0xC62CC4D6977CA8B9ULL, 0xD41E2F46A3BB21A1ULL, 0xD0CAE6D1C9E0D0D1ULL, 
            0x8D51FEE9B7247838ULL, 0x2CCE7B3A5B4B59F0ULL, 0xF21D7685BA0DC992ULL, 0xB7F288084F9F08F4ULL, 
            0x93F10394D78E3905ULL, 0x8CCBB3688C9C9C59ULL, 0x776DC9B49A6EB692ULL, 0xFAECC28ABEFB2058ULL, 
            0x4F860E0FACDE9330ULL, 0x51A9C4828D7A1725ULL, 0xE84DFF6595CCB451ULL, 0xEE012EA13E26899CULL, 
            0xB68BF1FA5665DFF3ULL, 0x542AD6DF661A7165ULL, 0x7089D42C2C4ACA1CULL, 0xD69EE9C3E807ABB3ULL, 
            0xB6F96309210D5A7AULL, 0x14EF05D47B9A591CULL, 0x02F1ECBA72180045ULL, 0x800B47B186AADCC3ULL, 
            0x021D9D5AD95F1051ULL, 0x0E71AA6CE93EF4E9ULL, 0xA8AED32328313381ULL, 0x5F18713A5185C062ULL, 
            0x2CB42FD88152D3D5ULL, 0x771AEB53D08B42E6ULL, 0x271CC39546856402ULL, 0xD513B8C08CA8630CULL
        },
        {
            0x48B217F43B6366C2ULL, 0x6E6A47563DB7979AULL, 0x2D0A0CE99F06FE5CULL, 0x91207108526607C2ULL, 
            0x1BF5518971793F47ULL, 0xEB2FC8E8974993DDULL, 0x0C53E4FC36B24996ULL, 0x854EB43B35ECD9FFULL, 
            0x6784B6DB0BC0F6D2ULL, 0x57700BF48D27B70CULL, 0x2434F47DC7221C61ULL, 0xB6D66FDFB80A778AULL, 
            0x1B6A1DC4DCEC8C0BULL, 0x8E6C66AC41EFB7E0ULL, 0x288BD1FF8F441CAEULL, 0x3AD564080A144B13ULL, 
            0x9CE89E034BA90BC1ULL, 0xD9529BE38EC31473ULL, 0x97A2CA5DF4BC8988ULL, 0x7057A289C529686DULL, 
            0x94D97599FCD50162ULL, 0x46C423038E66891AULL, 0xDD9E14A2DCB6B10BULL, 0xFD9A7EC9A45FFA38ULL, 
            0xFEF0DED0E5F9BA94ULL, 0xA915811CAC42A668ULL, 0x3EE123B12A87C8FEULL, 0x4840AB034046CE7EULL, 
            0xE07349D19483D4F2ULL, 0x4D36241FF0C10030ULL, 0xE14A9733C6C03DE5ULL, 0xA9A98ABEA4982F74ULL
        },
        {
            0x4BBD4D5FA4B6039FULL, 0x7F3D503F8ECDD550ULL, 0xF3E006ADB5D751D6ULL, 0x09A0B96E72B4D03DULL, 
            0x10CA96738973AF97ULL, 0x845534867EA79BF5ULL, 0x62A5781619C680E4ULL, 0x01A1BB53C6517352ULL, 
            0x2242C85A47A0DEFAULL, 0xA0A288A629932D17ULL, 0x98BE694EE9E0D151ULL, 0x5DBE46458D3F4339ULL, 
            0xFE6917007D23F73BULL, 0xCCD445C14463E71FULL, 0xBEFBCEB3984DEB59ULL, 0x3285694B7AA7461FULL, 
            0xE61A49E97970E5F5ULL, 0xA18440D168D78FEDULL, 0xBB1B2CD2A09E6544ULL, 0x82FD4254CEBEA0DCULL, 
            0x96D8073614871D4DULL, 0xAF436D2829C33F9EULL, 0x4BE16367AB4398DFULL, 0xEC5947AFBACF1175ULL, 
            0xEDC33B18E63503F4ULL, 0xF2D1428572A5CB94ULL, 0x1DDAAD0031D75E8DULL, 0xF6B8E67708F374D9ULL, 
            0xFC5713CCF838DD8EULL, 0x3682301166186647ULL, 0x7D1FBD5C5DF162CCULL, 0xF0D4713255516E9AULL
        },
        {
            0x591B09B62CD2A0ACULL, 0xECC49E618C84CCDDULL, 0x885E452BFCC00EE9ULL, 0xC33E0B2B5841DB2FULL, 
            0xC1757FC27C3C7EEDULL, 0x3A17F31F917147C2ULL, 0xC226BDE4B9258645ULL, 0x1539F29301369EFCULL, 
            0xA6068C19475BFC71ULL, 0xEB55B788A5C0164EULL, 0xDF5F107938EFA384ULL, 0xE6CFC20FE026D308ULL, 
            0xE56EF207CA28648BULL, 0xBF41D97759047EFDULL, 0x5D5D9A0FAF8699BAULL, 0x634A402784D91945ULL, 
            0x138EE4D831925395ULL, 0x0967A13D02BE6642ULL, 0x38DEF98781CB5C6AULL, 0xE5547F27E72B5CBDULL, 
            0x807A1018195A2079ULL, 0x7FA4A78FA1D7FC16ULL, 0xCECE6EFE0DF73143ULL, 0x4DF99195E9EEE445ULL, 
            0xFDA7D9E65703AF21ULL, 0x4DC0F2D31ACCE7BAULL, 0xB446D1E32632122DULL, 0x1E7251EE1DE0428CULL, 
            0x28E0E3BA069946B4ULL, 0x42DAEA6FBF6D389EULL, 0x593EDB497E363766ULL, 0xEAFF9852143E2FBEULL
        },
        {
            0x5E39FE059230FD6FULL, 0x4F613BD99F78A94FULL, 0x300A00412CF7BF1AULL, 0x844F29F64BCE50A5ULL, 
            0x9C13E17439A0C528ULL, 0x9761D301CAED2FC6ULL, 0x6B48B3C2409B8F27ULL, 0x7AC3C2D2807A3B70ULL, 
            0x411AC95D31220232ULL, 0x74189B0B955DCD45ULL, 0x2E5B870420A9D70EULL, 0xDC7B7640B295EE49ULL, 
            0xF927E46FBA3FD773ULL, 0x34AE7D3E31B59DC3ULL, 0x52759F1D3F02594EULL, 0x5AFDF74DC07134E8ULL, 
            0x89E847A438C7C1C6ULL, 0xA5274EC364C35492ULL, 0x65420919E6A70D57ULL, 0xEA105115A00B0D23ULL, 
            0xDE03EF4B4FBA594BULL, 0xA7267F401EB2F445ULL, 0x6764D78B88204FDDULL, 0x34E9DBA8552C4EC2ULL, 
            0x60209D2A0B6E7E16ULL, 0xB2C4167C10C0BE7CULL, 0x78FD2A16E8772167ULL, 0x2D0837465521ECD9ULL, 
            0x388E1B60454EA94EULL, 0x96848BC1F6977318ULL, 0x397885E5494C594FULL, 0x80E981A48E98D8CDULL
        }
    }
};

const TwistDomainConstants TwistExpander_Castor::kPhaseEConstants = {
    0x06F203585AA6DF8AULL,
    0x3208902F794ECD01ULL,
    0x17CE5D46BD8C4ADEULL,
    0x06F203585AA6DF8AULL,
    0x3208902F794ECD01ULL,
    0x17CE5D46BD8C4ADEULL,
    0x3D80F496D214F87FULL,
    0x7EFA436CFEBA0496ULL,
    0xB6,
    0x2B,
    0x3C,
    0x6F,
    0xB6,
    0xE2,
    0x60,
    0x21
};

const TwistDomainSaltSet TwistExpander_Castor::kPhaseFSalts = {
    {
        {
            0x34881A604B1B131EULL, 0x113AF4CCB38C6B9FULL, 0xE8701A44FFAF0C1FULL, 0x060949381709B4A4ULL, 
            0xA9420E7CE867E596ULL, 0xE6ED936EDFFF052EULL, 0xA7C0BB4FB8CFC296ULL, 0x31E0AFEBD59EF777ULL, 
            0xFAA35C301B777A8AULL, 0x6FC3A36DFF5F4850ULL, 0xEB128CCBA5EB3238ULL, 0xF034B6A9DFFC2B53ULL, 
            0x797F30741F42A396ULL, 0x7D4B5EA1B95D7DD8ULL, 0x384A21B1B6E2572BULL, 0x24FD62A6DA77F603ULL, 
            0xA51491A6EEA5A27FULL, 0x6BD4AF4DC2E9FCE0ULL, 0x06E34A27CBA40A5EULL, 0x6953C3D691BBC177ULL, 
            0xE4B1C952ADE67D1BULL, 0xF67A297F568BF1B9ULL, 0xB64546E9E1F31C5CULL, 0x031BCE3210B8E2CAULL, 
            0x5B0646102FF6805AULL, 0x1000730D1B56FCABULL, 0x4739A5024F9EC290ULL, 0x9F446E47B353D055ULL, 
            0x249C36AE7F65123DULL, 0xB1E4B7D235C61E01ULL, 0xA0CE24781775D4E9ULL, 0xE2DEF223FF32C9BBULL
        },
        {
            0x39746FBAD16E7F32ULL, 0x328B76D173B20502ULL, 0xA68EFF483FD30539ULL, 0x1CE3F406F2836CBFULL, 
            0x46C8928C1EEC4C36ULL, 0x57348FAF9CE0986EULL, 0x97CDE4CF324BF69EULL, 0x522C41D47BF1EF7FULL, 
            0x676FEC51677FFCFAULL, 0xF60EF1262C06B2F0ULL, 0x34DBC5FCD964A099ULL, 0x57BEBC71107FADFDULL, 
            0x88A779A7095EEC9FULL, 0x68380446385F678CULL, 0xE5CD805237AD41C7ULL, 0x43C6A267758A7F16ULL, 
            0x53A271D502875FEBULL, 0xF3D065AD0C379458ULL, 0x36B2D934B6C7B30FULL, 0x0CF8A38C44373E16ULL, 
            0x9037B5DA2AA065A6ULL, 0x0E221874F4736B3DULL, 0x3A76C8F258A8CA13ULL, 0x22AF420BC78C7FE5ULL, 
            0xE99AF492CE4BDF20ULL, 0x69253019BE5D0C49ULL, 0x21830B43B9534C21ULL, 0xEA5C4F42F043D985ULL, 
            0x16AD673D3868CDC2ULL, 0x12429BA55D3E740FULL, 0x6726FF5E07F544D8ULL, 0x18D403BFF5F56D27ULL
        },
        {
            0x420A4D26D2DD74AEULL, 0x6EC6AB3A18242949ULL, 0x0E72593355D1B394ULL, 0xEA2F6A1D1AAFAC46ULL, 
            0x1710D44D8CDF22E3ULL, 0xC7D92E87EAE9E037ULL, 0x2C8340288781FF1EULL, 0x5001582D47CB52C8ULL, 
            0x034F561499A82129ULL, 0x5F595390A35632EDULL, 0xA4E7782C1EEA580CULL, 0xEE118E09F2E99360ULL, 
            0x74760B19131A7F1FULL, 0xD67660738DD2D97FULL, 0x84079DCC86306B5BULL, 0x36675768959C357AULL, 
            0x6C111C21465BE1F9ULL, 0x618921660D763782ULL, 0x854AA129B242C1E2ULL, 0xC663FAB5EB5997E3ULL, 
            0x0061C13D5B080123ULL, 0x568A6D3CE56AB13FULL, 0xD2F7CD87D39FD373ULL, 0x043F37A265413ADCULL, 
            0xC67E2E5346D9318CULL, 0x5AE786A7FAAC7024ULL, 0x92123029DF3A18B9ULL, 0x6CBD884A84D9C184ULL, 
            0x8C7295A7B9078DEFULL, 0x5A001B4D2C399988ULL, 0xCA5C3264531013FBULL, 0xCCCF193553835FB0ULL
        },
        {
            0xAF02CB75C86FD855ULL, 0x782B41FA00D4C415ULL, 0x36C6C414A5C96DEFULL, 0xB56F9FA772C075A7ULL, 
            0xC959C0AE9E342E69ULL, 0xC267AF0B97242BD0ULL, 0x4A754AD5265C42B0ULL, 0x21E2DEC5CCFDF756ULL, 
            0x277A33C225BAE245ULL, 0xCA65CCEB62BA7C34ULL, 0xCB7E5C863496019FULL, 0x8C9205214EC659E4ULL, 
            0x882A7300E8C5AFB6ULL, 0x41E5F9559034E3E5ULL, 0x8390251C36BAD39BULL, 0x0AFAC71EDEDBCB04ULL, 
            0x5F5A26DBC7841ECDULL, 0x4E03D5BE96DED4DFULL, 0x7FEF73CAFCD8CD6CULL, 0x1DA957E83D78BEE6ULL, 
            0x782EE7A5AB154EE2ULL, 0x054655D6C93B9CC0ULL, 0x577B167965F5F9E5ULL, 0x4A75F7B054A764C1ULL, 
            0x4003573EBDA9A739ULL, 0x8A69F6458F4FB16DULL, 0xFDDB3C8BBBE8A624ULL, 0x4CF0FB9E1F07ABEAULL, 
            0xBECDDCFB58F05561ULL, 0x9970F3D7FEEC706CULL, 0x5D2323A694CD36BBULL, 0x7071DC1B375CAB36ULL
        },
        {
            0x0FD1F37A9F219C0FULL, 0xBA43626FA1268DDBULL, 0xCF237C14EC95C52FULL, 0x8A979DABBE722B71ULL, 
            0x1367F58C8A1957F2ULL, 0x588DAB301012A054ULL, 0x9697766FFA49ED62ULL, 0xBDD12DFB41C170BCULL, 
            0xD4ADC8F305FDB90EULL, 0x9A89D2A5FB47269AULL, 0xCCCFA8E9744E9D5EULL, 0x638DBD825CDAC600ULL, 
            0x844DCD03DAC2B765ULL, 0xA623CA537DE19098ULL, 0x536A63F7BFCD909AULL, 0x75ED65A42AF774E1ULL, 
            0xBFC38A348C7BF3C7ULL, 0x6E1A9C7635F5BF13ULL, 0x4F8333B29969121DULL, 0x588AD119BDB19D19ULL, 
            0xC55D78C1B99D8774ULL, 0xB87165C40CE67CC4ULL, 0xB943E68579C0BF3BULL, 0x14C3EB8E37538835ULL, 
            0xFADBFC2FE50D6CBFULL, 0x63E8570BB6DE3985ULL, 0xC033439FFD45883BULL, 0x4572AC108A210D90ULL, 
            0xE8F7308CDDC11EA8ULL, 0x0C91A7C364EA24B7ULL, 0x8B2397E95ADAD72DULL, 0xD29E912C79F56CFAULL
        },
        {
            0xF42FDF4EA742B589ULL, 0x74684FF896DF0CD9ULL, 0xCCF43C843818D86DULL, 0xDC9FC355016DF187ULL, 
            0x2CCCB24C524E9560ULL, 0x6E71EEBAC10CC151ULL, 0x2F11DB769114A79BULL, 0x7DEC8F542E1A982EULL, 
            0xEAFEDE1B6EE96394ULL, 0x88D4135FB5B27F97ULL, 0x7DF50AD64653B745ULL, 0xB7617B2CF3623257ULL, 
            0x879692AFE3990F5EULL, 0x55EF429BCE187E0AULL, 0x9945A65707088F11ULL, 0x7DEEF4B76BAF9873ULL, 
            0xD4EBBEC21D8EB189ULL, 0xAC2D8C91CA087522ULL, 0xB818A61433A3397DULL, 0x58008E59D912A8AEULL, 
            0x81AAA0D481A30834ULL, 0x53EA98C51F6F119BULL, 0x8D95EEDF386F2F79ULL, 0xAD86378263185DC3ULL, 
            0xC35B986993ADAA61ULL, 0x8C2696D5D2B067C3ULL, 0x004DBBCCB8174707ULL, 0xC53F55D6C7F23749ULL, 
            0xC8FF497D9F395352ULL, 0x2351E95C63123E1FULL, 0x241465C5E7A8D491ULL, 0x5EDF4C915A898D1DULL
        }
    },
    {
        {
            0xE2F64B65A2774172ULL, 0x3581FE5A7549F805ULL, 0xA8F55BF2F6867366ULL, 0x3C937F5B9C17B95DULL, 
            0xF02A8D36F4D6F52EULL, 0xB8D13D05BF4C92BBULL, 0xB80C2C5B3329E88CULL, 0x6FF6915BD3CC65F3ULL, 
            0x647A1D9F2397D11AULL, 0x4EF063F5BF63B2CCULL, 0x23A025BEDEADDBCDULL, 0x85584569FC7B16C0ULL, 
            0xE685D2BA620AC233ULL, 0xC8A6814F7577D598ULL, 0x1567D843876CA043ULL, 0x3BED5BEB3755EBF4ULL, 
            0x2D66D277496CC200ULL, 0xF7A4FD563823BA50ULL, 0x657E32EDC73B1123ULL, 0x9F24C8732A4D66F4ULL, 
            0x0C9C11256433637EULL, 0xE52B322A1EA4A47DULL, 0x1AA63226688B1CE7ULL, 0x84DDCA2725145B1BULL, 
            0x0D07503E0452EF56ULL, 0xF2297BD06E420BCEULL, 0xC0ACE4FB0F426A1EULL, 0x398A9E8E50A3A13DULL, 
            0x4638AAA132BDF508ULL, 0xA08AFF6E48B1965FULL, 0xD57C2662E51BC6C1ULL, 0x354C8369BF0DF6F2ULL
        },
        {
            0x28BFF20B267F2A8DULL, 0x00B49EA1225C5405ULL, 0x377A4B0D07EDBD2DULL, 0x61EFF5C0EF834484ULL, 
            0x40398D620C2CAA09ULL, 0xBEBD92490B6DFF30ULL, 0x1A8BC938B102A7CFULL, 0xBA539521DA6ACF0EULL, 
            0xF43FF904720C689EULL, 0x6E7782534A8F67B9ULL, 0xD158607EF0AD2973ULL, 0xA9F01D4BBC3C9EC2ULL, 
            0x75AC94CE3973D219ULL, 0x1C17D07B3D3EEF9DULL, 0xF42D6336959D78D1ULL, 0x1E8B38237815E29FULL, 
            0x34EA0AB053C444CAULL, 0xBA5514136FE8D55CULL, 0x24DAC69E6DF84C31ULL, 0x5291BD384195F052ULL, 
            0xA0D152DBEC257C61ULL, 0x8BCCA3549E74C82AULL, 0x72D970AB7C7C7D47ULL, 0xFD8C662E55F4A531ULL, 
            0xE5AC692210CA5546ULL, 0x27608E08976A6BAAULL, 0x16B5F67CBDE1E168ULL, 0xE1851600B3583E93ULL, 
            0x9A932710582A1B43ULL, 0xF05D1334971B5076ULL, 0x0FE66B47ABF58FD2ULL, 0x2E521C4E5DF4692CULL
        },
        {
            0x17E80E08017ED634ULL, 0x498730403DBF90CEULL, 0x3873F934AFA1FA41ULL, 0x33891BB2B49D0148ULL, 
            0xFA19C5569BC0A2CCULL, 0xE1031A22FF8F60D6ULL, 0xCA6ECF42B2C5320FULL, 0x9F30EC9AE24024FDULL, 
            0xAA730080DFE2F1B3ULL, 0x583BBF5ED05D082FULL, 0x21232B23E83FAB9BULL, 0x03020303D3C43928ULL, 
            0x5D4C902DB9EACFB0ULL, 0xDF545A865FCDE5E1ULL, 0xE7B7AB43B6F95019ULL, 0x2E976121B56AF716ULL, 
            0x7479B6B230B466DCULL, 0xE09A82304C8F3D1BULL, 0x8484686F4013D9A1ULL, 0x504192396E297019ULL, 
            0xBBF6FF47E11086DFULL, 0xE8B642300F751D96ULL, 0xFE9911B7967EA50FULL, 0x069E9E1DAED3C71FULL, 
            0xF4BDFE6A336B11E0ULL, 0xB1B2B44F00B209F1ULL, 0x37E29BC279BA5A6DULL, 0x8C6197DA5528CD57ULL, 
            0x8EEF67B34423D985ULL, 0x58619858A32E2CD2ULL, 0x4650C0294299CD22ULL, 0x4A3071AFD196AEB3ULL
        },
        {
            0xEC6D5AC91D123C55ULL, 0x21277900F669ED79ULL, 0xC74719CEE42A9D1DULL, 0x2B6A4CE8172C761CULL, 
            0x91FAE0430704E4EEULL, 0x03EA0B545C2F3C30ULL, 0x7BE89D59E107D866ULL, 0xC430F5E6FFEEBA65ULL, 
            0xE900D5677F158025ULL, 0xF2008397345507D6ULL, 0x858EA6CD38FED434ULL, 0x488C661DCFC996D2ULL, 
            0x59146684EF4769A9ULL, 0xB51170E7784DCEF9ULL, 0xF2F5375C14D070D2ULL, 0x09039F1D92A1FE22ULL, 
            0x169E01F991350628ULL, 0x9FF4B9FBEDF22E3EULL, 0xB689D0A432B86627ULL, 0xB8559E5BC77697B9ULL, 
            0x4E9B178B33E6E69CULL, 0xE5C7D8D18CC1991BULL, 0xD698DBAFC7C5B40FULL, 0xD21267EF6FA278A4ULL, 
            0xA76315EABDAD85DEULL, 0xCCC2CC4D0554B135ULL, 0xC51A5B7EF4E7E051ULL, 0xE9D3AACD3C23D839ULL, 
            0x69F278DBF2AB6FEEULL, 0xC34D440A40FBC422ULL, 0x607841C7E7485EAFULL, 0x3F1563FCEA87C5CFULL
        },
        {
            0xB767BEBD531D6C27ULL, 0x4F328935F507E525ULL, 0x827CA7C40C937BDDULL, 0x7147FBFD6605EE3FULL, 
            0x2F972799EA8ACE1EULL, 0x38D3D2F964287596ULL, 0x265EB53279C528DEULL, 0x2A2DAFFDEFBA6E47ULL, 
            0x61511B81C703FA0CULL, 0x7B66DE9E3185E59AULL, 0x3D0C43E814BD1E89ULL, 0xBB0D627247FA3A35ULL, 
            0xCBB14C835D130012ULL, 0xCE69232E75E0A84AULL, 0x745D99BB262F66D6ULL, 0xFEABD140F101D83EULL, 
            0xB8C95E89B9447C79ULL, 0x776CB4249FF97622ULL, 0x85BDFCA83DB60DDDULL, 0xEFE047EFA9A283CEULL, 
            0x342C0491CD1C9E3DULL, 0x29C805B712030C8BULL, 0x9DFBFE85F30EBE02ULL, 0x1B33EC89D33FCA72ULL, 
            0xD39C7374649A5B59ULL, 0x426E32232E820152ULL, 0xCC40B6F721A2C422ULL, 0x9F3B4A1DB74EA594ULL, 
            0xFAFBFC0E58E9346AULL, 0x99C14EBA9AAE27C3ULL, 0xC7B38DB185FD3758ULL, 0xE69D3B88800C870BULL
        },
        {
            0x10820E4072115488ULL, 0x80C22FF48D2AA1DEULL, 0xED57996CF43E91FEULL, 0xAC1C3E26AEC06CFEULL, 
            0x685263EB91CBC43AULL, 0x13DAEE4226F1227FULL, 0x9226B5A86F7668F6ULL, 0x44FD14ECF4486367ULL, 
            0x68DE94818D61CF98ULL, 0xE6BF789060BCECA8ULL, 0xBCB7F1643ACC7010ULL, 0x8E5BDCA752E8B103ULL, 
            0xFAAB42A5F6CA3A09ULL, 0xDA9F29F453431AB8ULL, 0x66308A47B440F79AULL, 0xF8D5F7827A6E2BE4ULL, 
            0x1D65699E44158991ULL, 0x222D60D533B348E5ULL, 0xE8A8738ABC791149ULL, 0xAF8467A6A75A59ECULL, 
            0x7DE8DB45AA99D7F0ULL, 0xA245E6B0AF748ED9ULL, 0x268054BA4BBD1957ULL, 0x98F2447B86B9BC6CULL, 
            0x475B25DF47D452CCULL, 0xBA3F78A2FF8BE1A7ULL, 0x698D5CAB2E9436B7ULL, 0x220FFD4A5268D425ULL, 
            0x9A2F1A81C5C11052ULL, 0x5BBD900844245BDBULL, 0x6EBFDE6D5D173A8AULL, 0x4A5D2ED5C46358EDULL
        }
    },
    {
        {
            0x453D43F41585ADF4ULL, 0x99559FBA90BFE8F3ULL, 0xB2A317DA832423E1ULL, 0x61A08BAB8D50D0A6ULL, 
            0x88A5EC04211F11F7ULL, 0xCBEF1B9960D049F3ULL, 0x647084C7637F5C18ULL, 0x0F9CF00D0EC3B3D8ULL, 
            0x155732779250D15EULL, 0x56BF670D966359AAULL, 0x32FA7AB4E0ED49ECULL, 0x9073B90CDEB08295ULL, 
            0x6E8C466D8BBF4ADBULL, 0xA0828A5A5F761D8AULL, 0xB927B2CE9C598791ULL, 0x52B39EB7F8E0E8B8ULL, 
            0x25BF4F5B535E6044ULL, 0xCE6F29B5893236C2ULL, 0xD4EAC32A97BF0E4BULL, 0x6337CA0ACEF01366ULL, 
            0x2D7359A83D8797FBULL, 0x24CAE8A3758A3239ULL, 0x9A4B3C52DB81FD56ULL, 0x4801A3157EE4B279ULL, 
            0x810959091950FE3BULL, 0x53B99D1ECA0767A1ULL, 0xCACA079E7F4F9E45ULL, 0x2FCE07A21C952617ULL, 
            0xF777256ACF5ACB08ULL, 0xED609E050C0557C7ULL, 0xE8DF7F886F32DA41ULL, 0xC6D78B81CC0EDE1FULL
        },
        {
            0x62F0E884166626F7ULL, 0xF6330E482A6E395BULL, 0x6A3B0CADE308F9D9ULL, 0xFB58E5B576AB122FULL, 
            0x12C160F1E2CD259DULL, 0x765FDB43B6AEDF0EULL, 0x89D05164FE7F4CFEULL, 0xBBDFEB007D394995ULL, 
            0x2476F8EF29174D19ULL, 0x9BD78923D8A563B2ULL, 0x6D3570EF917A568AULL, 0x0C5FAAFDEA41759EULL, 
            0x65623F9139880D55ULL, 0x726B8CC9090353DFULL, 0x7F10A765FC108EF9ULL, 0xA1E5A69D8F2B5473ULL, 
            0x53CBE5344060E1DBULL, 0x6C408843EDB28EA6ULL, 0x5CFC583B6CCFFA6AULL, 0x02C587C9BA1F3A63ULL, 
            0x3BBF82FE861D725BULL, 0x62AFDAFE79E9CE54ULL, 0x5C7F25178410AC38ULL, 0x6EA42520B25712E8ULL, 
            0xFC7A7828EA03AE48ULL, 0x4DDA3741C1E81D90ULL, 0x250495CCF6A35DA7ULL, 0x37B427F128798F04ULL, 
            0xE646C246CB0718A7ULL, 0x4980AB8A94DC3555ULL, 0x40742055ED8C2B11ULL, 0x623872518C149928ULL
        },
        {
            0x269F773B66F27C8FULL, 0x5243EB8F0139112DULL, 0xBF3EDD03FBD96474ULL, 0x948626EC70DFFFBAULL, 
            0x51AE3152ADB891D5ULL, 0x011EA457C9C82F08ULL, 0xACA6B767C8A07465ULL, 0x8CA9026BA33CC7D4ULL, 
            0x4F6FB1A4E6599F00ULL, 0xD8456F549F97FC9BULL, 0x46A1344FC59919F1ULL, 0xF038D0B2530C7988ULL, 
            0x6324D487EE35436EULL, 0xE1E1CFF8C583EAF4ULL, 0x06D52670CEB4ADB4ULL, 0x2ABFEBFEBF36A41EULL, 
            0x207AE8780BF38BB4ULL, 0xDE2A64EB832B3952ULL, 0x6C51D1508B5B5E72ULL, 0x3CCFE2C5287F2C1EULL, 
            0xDDCED5B962B86CCEULL, 0xA5F1784EFA49D05AULL, 0x28F51E607842CFE6ULL, 0xC1B73D8560F08B7FULL, 
            0xB29090CDCBD6B523ULL, 0x47942E49964EBE8AULL, 0xEC2241CF91082697ULL, 0x7ACF51D6FD606BE3ULL, 
            0x72509C6A7E82C150ULL, 0xBC46F3A05216E1CAULL, 0x616853099D4C22F6ULL, 0xCBA9F0A738D4F30AULL
        },
        {
            0xC1129E6EB2346C3EULL, 0x48181A327D58A002ULL, 0x18414E8FA84AC825ULL, 0xDB5F86F8F10C4B74ULL, 
            0x206243EA8F505197ULL, 0x295715865A56DC4EULL, 0x2CBBE3C00B166B44ULL, 0x3831A3DD83C66694ULL, 
            0x1D9CAADB2A130DE9ULL, 0xE0B31E55F9F42707ULL, 0x360C42D732EEFA09ULL, 0xE05577A9B913D50FULL, 
            0x1FACB0655E222952ULL, 0x39AF1AB5A74A7C83ULL, 0xABC5072072A6750CULL, 0x302EB36D9BB254E2ULL, 
            0x2A54F6DEB4575B9FULL, 0xBCB6DADAD8EAEF34ULL, 0x9FE7CA03C8DFB909ULL, 0x0C750FFAD4BADE71ULL, 
            0x156FD4576E6D176EULL, 0xD0B2779068F06B1DULL, 0x5BA61D829BA32883ULL, 0x93D654B54EF4E1F9ULL, 
            0xD3FD29C05CFEA0C9ULL, 0x04AD859EE0C107D2ULL, 0xEC5059E4C973CDD0ULL, 0x617CF3AA191E6C93ULL, 
            0x698FB4EE91835312ULL, 0xD5114F8C1EED72A5ULL, 0xC0738BD1C2351F55ULL, 0x95CDE2A940A831F6ULL
        },
        {
            0x3FE7A358FDAFE451ULL, 0xED893BF36B472CF7ULL, 0x4893373870ADB579ULL, 0x69786AB79DEACB07ULL, 
            0xD8FC76270EA29CA3ULL, 0x94712107E7A846FDULL, 0xCBBBE4F215E0D935ULL, 0xE53276EFFDF15AF4ULL, 
            0x0258EE6D2828FA30ULL, 0x1F67E332A2A89DEDULL, 0xF2D592B91DA12551ULL, 0xE452AE1B63D03809ULL, 
            0xD9F2BF96C41B32C1ULL, 0x220573A29BEBA2ECULL, 0xA310377FA2DA5C90ULL, 0x0812F1B5A22D70CBULL, 
            0xB1E25ED44EED3AFEULL, 0xBB44898ECAABE22BULL, 0xA42A0998F3473EFCULL, 0xBF2F9F3025BE0DF4ULL, 
            0x917873DC8A1F9C64ULL, 0x8647B7E9689083B8ULL, 0x5EF480910E9D6E5AULL, 0x84CBE6C94D1A82B9ULL, 
            0x202EBF8F4869ABB5ULL, 0x15603802CEC96FF8ULL, 0xEA69ADD1D8B56482ULL, 0x569CC9B9C68BCC89ULL, 
            0x37B3862D82E4DEF0ULL, 0xFC4F6037C2DF896EULL, 0x4603C48686C21C10ULL, 0x396E443201FC5A5BULL
        },
        {
            0xDD341F551DE8B92CULL, 0xC1DBD15DB9922089ULL, 0x92F81C387676F0E1ULL, 0xC3E1CF4C6E70F5DFULL, 
            0xB13DD68DB1DB196EULL, 0x72B8EBBF089EC51AULL, 0xF92AF949587B809BULL, 0x86DB1BE48B591775ULL, 
            0xC439F8C0EA5EA66DULL, 0x28D81C7E86EE559FULL, 0x5E08ACE390308683ULL, 0x332A912D380A2DEAULL, 
            0xD368B611E2A41DF7ULL, 0xA65EC41F61097542ULL, 0x0D288417D8D710BEULL, 0x2CDE3AA8E8509855ULL, 
            0xF8CAE5B3D6226E58ULL, 0x27CF8AA450E471EAULL, 0x3C8BE042CF91907AULL, 0xFB8B4F539388D5DBULL, 
            0x44D0E59AA1C9AEF3ULL, 0xA4A01B6E8712B5ACULL, 0x8DECA040ABAFC25BULL, 0xFE85CE0CFC23C170ULL, 
            0x45F1FF0216CDD72EULL, 0xA02D44A24E65D603ULL, 0x2DE6B4A914793CE1ULL, 0xF7937287D1FD38A5ULL, 
            0x24A8A4A7FC2D5629ULL, 0x408D3C933A9B3835ULL, 0xFA5308ACC2FF2869ULL, 0x2BF55B9475912E98ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Castor::kPhaseFConstants = {
    0x9E481B729DCA04DBULL,
    0xEA9DFC8CA8D6C5FCULL,
    0x4014F9B18177115BULL,
    0x9E481B729DCA04DBULL,
    0xEA9DFC8CA8D6C5FCULL,
    0x4014F9B18177115BULL,
    0x16882AE02A22B51BULL,
    0x1754175C66BC7532ULL,
    0x18,
    0x43,
    0x85,
    0xDE,
    0x83,
    0x66,
    0x74,
    0x0D
};

const TwistDomainSaltSet TwistExpander_Castor::kPhaseGSalts = {
    {
        {
            0x16AFEE09FE2EE652ULL, 0x2CA67869A4A5E085ULL, 0x94F3283BE75666B7ULL, 0x38A15688426EB277ULL, 
            0xA02111428356FA02ULL, 0x196C2FF27E89F497ULL, 0xEFEB4D1E824B45D4ULL, 0x1942F1A9FDB05D74ULL, 
            0x3C3EBD1ACB5AF1D3ULL, 0xDEFB2A7520C4ADD9ULL, 0x9A2A9D7C6387A1DBULL, 0xA47390D31FBC0A0BULL, 
            0xA837933A6FD09FBCULL, 0x9D05B9813C580874ULL, 0x807F1454F7171DF6ULL, 0x029EC293350A621AULL, 
            0x9690A1E1C536B6EDULL, 0xE665B4282EC0254DULL, 0xEBCD38954F907384ULL, 0x093B79B370A2AFE4ULL, 
            0x47B0C1CED0A12A66ULL, 0x41953000A8FD1139ULL, 0xE26F4B97395C97EAULL, 0x6141F645ED0CF884ULL, 
            0x62AC710B8F8EE853ULL, 0x80649E436C528CE0ULL, 0x6AA6BE823F433B55ULL, 0x4157EA815DECC877ULL, 
            0x01883E45664356BBULL, 0x59AD07ABEB4BD5DDULL, 0xCB33B4D05B257994ULL, 0x4034B093B6BFDACBULL
        },
        {
            0xE08B1B07A8B38716ULL, 0x0D519C9A64FBA261ULL, 0x353A2E662B0C52C2ULL, 0x46A5B42F8CEE7EB7ULL, 
            0xF92DBD190B05FA8DULL, 0x285B201EA4EC9474ULL, 0xFE599A13F73E1739ULL, 0x5A0AC3DF4FE85A37ULL, 
            0x63A6BE1AB2599849ULL, 0x83DABBBCC48E688EULL, 0xC47A5780C6306727ULL, 0xA2C6868AD8209F9AULL, 
            0x032312642D09C18DULL, 0x8A47C97136E62330ULL, 0x42AD98DD436687F8ULL, 0x12260EA726A7ED03ULL, 
            0x84EBABD1F77FADC6ULL, 0x35E469AFB721C60CULL, 0xA7AFB3572D267798ULL, 0xFF55C5B3B52346F0ULL, 
            0x27FE32250002747AULL, 0xD9D82A4A122E6689ULL, 0xD0AC9977C7540771ULL, 0x3F628592DD766920ULL, 
            0x52A67F259962C47DULL, 0x5770694DF4B6394AULL, 0xD688456BD5E722C8ULL, 0x477EEE9B6EF12B42ULL, 
            0xE5B3E1A032CE3319ULL, 0x4A290A349C3A72DEULL, 0xAA51055F73A032D9ULL, 0x0753F26E0FF9AFD2ULL
        },
        {
            0x96FC66ACF024E9EFULL, 0xBF0A219DD44C90F5ULL, 0x3F2A5C24E998ADCDULL, 0x4F42E48E9B2C4541ULL, 
            0x94F42614CBE41EDBULL, 0xD39AA1E185035CF3ULL, 0x4E990CC20B93A3FAULL, 0x509F7E02E6DC5142ULL, 
            0xA776D58B11D61D5FULL, 0x47464758A0CB57B8ULL, 0xC0831D21E03A269BULL, 0xFC8D8064F816CACDULL, 
            0xFF233885EE31AEABULL, 0xA05CBF9080EDBEADULL, 0x1FECA4126D549753ULL, 0x78B1A0912877FB67ULL, 
            0x651E229B6B111FE8ULL, 0x5BA90BE660372CA7ULL, 0x541D6D832BADC09DULL, 0xCEFFFF7DEFD7F0AEULL, 
            0x881DF27CABF96990ULL, 0xA9B1BF560500FA5AULL, 0x2F98F5A9F6F4724DULL, 0x05DBFCA295AF580DULL, 
            0x9EC1DDF6B9E29D6EULL, 0xBDA6CC49003AD488ULL, 0x40E87E5AA6B40239ULL, 0x2155D60AB2D69A8AULL, 
            0x5218E3A81075A5EDULL, 0x897BECEEC71980BFULL, 0x17FF59333FD7A41AULL, 0xEA955E5D23049048ULL
        },
        {
            0x06E35C11FC68329AULL, 0x6E85C9A0BD0A2F29ULL, 0x32F0BC110845C09EULL, 0x4FF1A1DCD3084D77ULL, 
            0x5D1EA058134807B7ULL, 0xD23EFE3A56811106ULL, 0xFF7C14EFF1083A38ULL, 0xE1CADDC09B2D6B62ULL, 
            0xDE6B021C45007956ULL, 0x191E0F576385686BULL, 0x0968654C80CCBA70ULL, 0x6E24549A4D2D7682ULL, 
            0x6E318A54165FF99BULL, 0xE14C60FC61A09C86ULL, 0x4C8852CC2F111913ULL, 0x68B85C78BDCA9E7BULL, 
            0x976546AC8CA0F3E8ULL, 0x08764210635C0EB9ULL, 0xB27C72FC380F305CULL, 0x633BE4DD11EBBCBEULL, 
            0xB38312DB17F4075EULL, 0xED3353BAC08EE8FAULL, 0xAC41A66FD1605565ULL, 0x9727D5972695E29CULL, 
            0x74ED01F3D7191AEFULL, 0x572A40CD753ACEABULL, 0x55E5EA9E62BB8FA6ULL, 0x50E623C110717C25ULL, 
            0xC29BCF261F93C5DBULL, 0x81F02D731C1015B5ULL, 0x12F312E10B1F494EULL, 0x35ECF33E3E3C51D0ULL
        },
        {
            0x681206D420310447ULL, 0x0B38C193BA0BFDBFULL, 0xE5E03F46AD073E6CULL, 0xCBDF5313AC8F530AULL, 
            0x5494942A7D861A28ULL, 0x38809FEACC98196BULL, 0xB0024F4284BC79AEULL, 0xF70DAF4C658DB823ULL, 
            0xFFF8332DD660EDF5ULL, 0xBE4005B5E4EDF3A8ULL, 0xEAC87F77BDF7BFE6ULL, 0x5EB08C0B2F20E4F3ULL, 
            0x134444F31A851670ULL, 0x36D88A861C1FCFF5ULL, 0xD73846A5212C0CCDULL, 0x99429A1D6FA1C6FBULL, 
            0xF15D1031D3381CAAULL, 0xC31D4D96D8F7C15EULL, 0x752E2939D9EE07F7ULL, 0x67E711E389090C0FULL, 
            0x9137E662F78A32D6ULL, 0xE23E43C6E660257FULL, 0x2A2589964C956D91ULL, 0x7F5B6F510AC6ECB9ULL, 
            0x3BF470CC46E254FAULL, 0x89AD61C7B87B816AULL, 0x78A0BA9730DBEF83ULL, 0x9CD314011BA861A6ULL, 
            0xE08A29A565090182ULL, 0x7F4D37BFF7AB0013ULL, 0x35632C3352E25C96ULL, 0x5BD8A85AD12D4B9CULL
        },
        {
            0x7D50E09C4DF8D7CAULL, 0xC9DC226D139D1FF3ULL, 0xAE231273BE160574ULL, 0x77158E78A21C173EULL, 
            0xA7E08CEC2C9D02A5ULL, 0x48BAC524DB20C86AULL, 0x86049CF047F3B652ULL, 0x942BBDE2A3A0BBFEULL, 
            0xF85E797403F6C943ULL, 0x69EEAFEE5E300A80ULL, 0xA580074353963CF5ULL, 0xE3C187477C9114E1ULL, 
            0x6E2C102EA23041AEULL, 0x453F67C249C526B2ULL, 0xF8001195298945C7ULL, 0x5CA6E600FB87A128ULL, 
            0x357016E8C013174BULL, 0xEA564CA676C6CCBEULL, 0x78F34F410536F9E7ULL, 0xF069B61A4ADE1629ULL, 
            0xA1D91643684A1402ULL, 0x8EC9F8112273A908ULL, 0x471BADC24070EF47ULL, 0x28956F30C49ED4C8ULL, 
            0x79E3FFA0AA35B87EULL, 0x1EE0A9FA80658AA9ULL, 0x558AFACD315142F0ULL, 0xA97BF00831D552EAULL, 
            0x09ABD489E5D70458ULL, 0xF362A0E80260C6ABULL, 0x08ED8C6D44B2EC6AULL, 0x6C8E45423767581FULL
        }
    },
    {
        {
            0xA4A676F497859078ULL, 0x8BD5FDC6C13C797AULL, 0x90D81E657BE39496ULL, 0x0D196E691916ACAFULL, 
            0x7AADB2D507EE27FCULL, 0xFADA8C01E95964C5ULL, 0x8CFF991FE595E470ULL, 0x64FB480F7E19569CULL, 
            0x5BA70B6718E4E937ULL, 0x488BCFC04370692DULL, 0x14106AFAD4984966ULL, 0x64C76ADBF02F1A1EULL, 
            0xC29BB6B62BA6E062ULL, 0x8B2A9567686A9C5BULL, 0x94EC0D6CB2109134ULL, 0xAAC9A99ECC57838AULL, 
            0x578051F30834A325ULL, 0xEDE0B5EE5B9DCAC1ULL, 0x9D8526293846251DULL, 0x4F7A8632BEA8DC17ULL, 
            0xB1773AB7C003C1F2ULL, 0x64841CD72F230E03ULL, 0x5E76B83B617870C7ULL, 0x58412FA57E3321ADULL, 
            0x9B26AD784AD92BF0ULL, 0x1E0B4E5C83CCED1EULL, 0x7F9B70BAF7ADAE6CULL, 0xB956C44642FEBE17ULL, 
            0xB560DB5CE905B812ULL, 0x7F2DF9A0BE8E76F8ULL, 0x8266065B29189599ULL, 0x47DCC2552BCEF2F1ULL
        },
        {
            0x48C52B71F7E875BBULL, 0x93A0E763A3C2D9F1ULL, 0x92438FFE6E031E52ULL, 0x156C0735F07704D0ULL, 
            0x0E0A80B422E10083ULL, 0x1E0A193DE9F2FBA5ULL, 0xE350F3898C3BC553ULL, 0x4144BACB5086E401ULL, 
            0xECB162F71D14BC38ULL, 0x6A8C2E0859C3587AULL, 0x0463AE273F74D3CDULL, 0xEF78CBDD629022B9ULL, 
            0x55259351E437B0A5ULL, 0xAAC0EE32260F9E80ULL, 0xD7E5098B228B151CULL, 0x2D9F7EA8D6F893B8ULL, 
            0x5211F0B000F2471FULL, 0xDF44F75C2FEC03F0ULL, 0x02CC15C1DE907F3BULL, 0x7181220F536FB0E0ULL, 
            0x1B142AC1FF8BDE96ULL, 0x82E27EA543DBC7F0ULL, 0x79250DA0B61A4D69ULL, 0x925C3AA8DD1B5449ULL, 
            0xC244D88F407CAB8BULL, 0xE1E27050B2401913ULL, 0xD5ADD03F11A4A0CCULL, 0x40EA9DE509C740B1ULL, 
            0x1AA4E862F06E15B1ULL, 0x7D064182CB492160ULL, 0xF1E3A9551D25ACF5ULL, 0x32AFC3FA5E2898CAULL
        },
        {
            0x3BB9C194F887686DULL, 0x99E0505F3B28D370ULL, 0x22AD7A15B71FF163ULL, 0x46DC4976C606DE78ULL, 
            0x91488429576BF60CULL, 0x8CF16DC5E6E1275BULL, 0x55332FA35B17CEFBULL, 0x806FFF3477F5353FULL, 
            0x20BA5CC2C78A6113ULL, 0x13A185E797CA1C85ULL, 0x3215CE9FF64C6ABCULL, 0x02556B083FEDD52DULL, 
            0x0E9B1BD48E447AF0ULL, 0x924903135F4241FFULL, 0xDEE604D6BA25809BULL, 0x74418084D691FF79ULL, 
            0xC8FD0B9A1C374ED0ULL, 0x3A59637FB7AF9E58ULL, 0x6F26499B75FF6BD6ULL, 0x1BFAFCFDB4C12C59ULL, 
            0x92F8555F5DE801ABULL, 0x217C2893EFAFD60DULL, 0x31CA21E86130CCE4ULL, 0xEB3729BFDEA8080BULL, 
            0xB8633D2F9F6EF7BBULL, 0xA4EF997DD41FC079ULL, 0xB7B465621AED58F6ULL, 0xD16CFFE85CE39B97ULL, 
            0xBE5722BF6FE29C1BULL, 0x55858B18C3DC7713ULL, 0x0B3BA6A7852A8D9BULL, 0x67713AD126563293ULL
        },
        {
            0x2A346BD680918BFAULL, 0xAB28656E28440A62ULL, 0xAEC9EEFAD6BB42D4ULL, 0xEA3E27023D8D6403ULL, 
            0x0BB6570594E156F7ULL, 0x9C16E11D62DDB4D1ULL, 0x778C189A931FA36AULL, 0x6030F7012387E83BULL, 
            0x30F7AAA3767435ACULL, 0x92461DA965CDB6FBULL, 0xC6A4F2998F5DDE54ULL, 0x59E0615B6024423AULL, 
            0x6BAD177A0C0E9A03ULL, 0xE6B30419D573A136ULL, 0x78EB03FFCEC6847EULL, 0x9501DDDC90B56604ULL, 
            0xB0C98B62C56EA817ULL, 0x24618031E4F8A632ULL, 0x090F39765078BCB4ULL, 0xB0CE641D1BFA081FULL, 
            0xD55BA51AA4B2AA55ULL, 0x5343CE9369AC7E46ULL, 0x1E4911ACDB888547ULL, 0x071CA044DB548F9FULL, 
            0x8DC31BA7B995DACBULL, 0x198E1FE430218A1EULL, 0xEC37FE00743AA23AULL, 0x2E2EE0ABF49101E9ULL, 
            0x4D42F580C58BEA69ULL, 0x930F599183DB06A3ULL, 0x8F0A2A1E5610956CULL, 0xC18B02A9730490A0ULL
        },
        {
            0x2A2B24CE7BD45F01ULL, 0x37FD320CCC78CB95ULL, 0x1EE662A5341B0C49ULL, 0x6AD7863C7660D289ULL, 
            0xED3CC6AB1F38DE68ULL, 0x3FA88F228AB097A0ULL, 0xB3E0B19CB0D507ADULL, 0x9360166C30E4320BULL, 
            0x3A47E264B35C2343ULL, 0x64D08A5F61135C4AULL, 0xEECAF9CCB9D8FDC4ULL, 0xACBAA694A90159F6ULL, 
            0x4DC38331D7FEC28DULL, 0x5222EFB40B4020B3ULL, 0x496159BEFBACCD2AULL, 0x91921717C64540D0ULL, 
            0x873BD78FC3C357BDULL, 0x1CD5EEF496760DB9ULL, 0x5FE5D2EF2408C582ULL, 0xB4EAE3D962C5CB41ULL, 
            0xFA656C7D30B89530ULL, 0x91CA8B989781D585ULL, 0x1283608098F77B14ULL, 0x79FE78E16132D410ULL, 
            0xDBE92BED8F52426CULL, 0xFAF330A2EEED848EULL, 0xD7973D42740035DBULL, 0x69E93CB2B4BECD29ULL, 
            0x05306ACB332C43C4ULL, 0x8765479378E8B6D9ULL, 0x6E56EC14BF2FD207ULL, 0xF1254A2642C55AA9ULL
        },
        {
            0x92E1667A9CAD5775ULL, 0x32A6EF96EACDCB9DULL, 0xC005AA70D61F60BDULL, 0x4959AB2A2AE80D00ULL, 
            0xEAF6242317D47558ULL, 0xE3AEEDDF1B511D41ULL, 0x21C1B2FC5EF14998ULL, 0x766DAC9BD3D38B19ULL, 
            0x1DF6315AEB0818FAULL, 0xCF617FF375D89308ULL, 0xA5E34A73336C21D2ULL, 0x16B45D0E814059CAULL, 
            0x40D29AB9A9A3CD87ULL, 0x7EC4CB98FE64B291ULL, 0xA2EC8D58D22F1425ULL, 0xEBDFD97EBFE88B2CULL, 
            0xFF91F10BF09AA44CULL, 0xB7204059A200F350ULL, 0x7C7F5902A83703FDULL, 0xB86A86C7DB674606ULL, 
            0xBB7DD82B00925900ULL, 0xD84C9FDF85087135ULL, 0x0FB1D24B4A48B6B5ULL, 0xDCD552CABA15AF88ULL, 
            0xBCA85DD908472F92ULL, 0xDB4E515D3A0D30EFULL, 0x1C681E6FB9D51080ULL, 0xC0FD0C005878FC02ULL, 
            0xC7A7F6439691397CULL, 0x21669C9DBDBDB1C5ULL, 0x177EFB450B6F883BULL, 0x92C52312055CEB1AULL
        }
    },
    {
        {
            0x2F1933E80F52FAABULL, 0xD6A27BB6292E24A7ULL, 0xBA9D07D4A43DED3BULL, 0xFEC6C3EFC4FC6450ULL, 
            0x52C2007C75AA2E45ULL, 0xCBDCE828FF4E052DULL, 0x5C15312AFC2A6AE6ULL, 0xCDB3B4BEBA301A18ULL, 
            0x76CCFA2D1F850112ULL, 0x8631D131FC138B15ULL, 0x6EB353F6D65D6C93ULL, 0x29213088175E2F3DULL, 
            0x7350B7E08B3D729FULL, 0x83BE44169F82D254ULL, 0x83369D9E5DF9F9C0ULL, 0xBFAB6AF73C944D9AULL, 
            0xD6BA4B5FFEEC798FULL, 0x98E2EFC3C5A8A368ULL, 0x4AA45F59A5053D58ULL, 0x2A87B6DD17404E49ULL, 
            0x95ABBC766A20DDCAULL, 0x9E1DD3B6B431E217ULL, 0x915F26D3E8A3275FULL, 0x099162D192327EF3ULL, 
            0x61055A1D1CF481D3ULL, 0x8262364DCB8DA83BULL, 0x6D33E417812D8DC8ULL, 0x72C60F2671FA13BEULL, 
            0x05ED4C70E796318FULL, 0x1F99A4969D206AEEULL, 0xE3AA5DAB4FED5282ULL, 0x59B1944A8DA78FF3ULL
        },
        {
            0xC7A9764A43EEF3C4ULL, 0x1CC0D095B3466B28ULL, 0xCF7A4A4499387BFCULL, 0x828106A32D2C6D45ULL, 
            0x0D6F685DA67084CCULL, 0xE24AE2954CCCEF7DULL, 0xF28142EDE2FD5F61ULL, 0x57A8E4AC51C5006FULL, 
            0x208AB9CA8A13F35EULL, 0x08F505A63529D316ULL, 0xE951CB6D51BDE032ULL, 0xD481CC5B8D3028D1ULL, 
            0x00CCD44976B7565BULL, 0xEFD5C31E39305ABAULL, 0xE1EADB8EC4B3027BULL, 0xD14829DB52FC3EBDULL, 
            0xC0A5D2E60A27F842ULL, 0xEF8FDCFD5014B14BULL, 0xE3269E3C3BAF4DB5ULL, 0x414FA3C90B2F565DULL, 
            0x82F01804CE28B0C9ULL, 0x3BC5B955F8BA4567ULL, 0x9980D2243C97DAB0ULL, 0xE3BEF737AD205342ULL, 
            0xDA4F927C052AB28DULL, 0x8107BA229E598D07ULL, 0x446BC100DB421D12ULL, 0xC51476C5EC06AF99ULL, 
            0x474CF0087AAD278BULL, 0x4D5F266BCBA6B6D2ULL, 0x124475C5E64C7A9EULL, 0x88F42B1DFE50B7AFULL
        },
        {
            0xE8BEBEDFF349A3CEULL, 0xAE6F7EC182F9C842ULL, 0x3BCD144DE497F058ULL, 0x01BF7B5D25B076C2ULL, 
            0xD996B263F05D0CDBULL, 0xD6C7C175973EBC85ULL, 0xF65D820A243F1727ULL, 0x11BD97DAEF580D92ULL, 
            0xBCA699FD666D62E6ULL, 0x871F81EBDA3BBCF6ULL, 0xE9721B7379475026ULL, 0x08CD91B4FA72E8DCULL, 
            0xA183279A5EB5F456ULL, 0x52731C83F101DEECULL, 0x798B8F852B994B84ULL, 0x57A106E67065E540ULL, 
            0x6BD7BDDF3DDC7F04ULL, 0x9EE294929E26EDEEULL, 0xEBB468ADDB8A0669ULL, 0x56E1709A505113F6ULL, 
            0x4D006C247B2DD788ULL, 0x51B5B9DC4084A952ULL, 0x70FEDA055070B878ULL, 0xD9FFFFD1C74FE23AULL, 
            0x99EEC77D56C16A61ULL, 0x2AC9CC2AC46E2752ULL, 0x4932AC769D38205FULL, 0x3D71E6706A9AAC9AULL, 
            0x6D5CEF68D5031FCEULL, 0x731F287683CD1093ULL, 0xF0885D2D6CA63274ULL, 0xC967E47BC3FC8890ULL
        },
        {
            0x92564C8E174B4EA9ULL, 0xC445F4C67F75ECFFULL, 0x1F4CA7446592AEFDULL, 0xD081F17C98E59D51ULL, 
            0x9C020BC4FAE9634DULL, 0x6B58A0ED6CCA80EEULL, 0x36349251F9E6AF5EULL, 0x21BD90A383B7301DULL, 
            0xC3048CEEBAA80949ULL, 0x466DE0B5B1E6F6F4ULL, 0xD8B1A8951DB24C92ULL, 0x82A2F4A344384EC2ULL, 
            0x9C9C5CC20AE50F93ULL, 0x1F80968E5C1DED75ULL, 0x06762C1C3741A628ULL, 0xF5A4E48DA864EDDFULL, 
            0x7CB2CBB4FDAC2FB6ULL, 0x3B29F9CE01E1D032ULL, 0x6B2C6CC002393EAAULL, 0x3BE5756D6FFD77A6ULL, 
            0x7000E68D016F703DULL, 0xAB5118FA51880D51ULL, 0x67FF98656479C8A1ULL, 0x9DA3996992E90DC4ULL, 
            0x4D9C1E2C77B8D91DULL, 0x8255E15960202B89ULL, 0x67F20CF573B535A7ULL, 0x9B46BCFBA2FD1759ULL, 
            0x6874744AB954B18AULL, 0x813AD85DB829E1CBULL, 0x28EE8EE785332F57ULL, 0xF73AA8955D7D58E0ULL
        },
        {
            0xBDE3482A1E110F96ULL, 0xE400BA75111BA525ULL, 0x50672800A731B975ULL, 0xEABF5E4BABC37994ULL, 
            0x228587435B25CF60ULL, 0x200509407177EF37ULL, 0x675241EE0EF07DCBULL, 0x23849229591F645FULL, 
            0x3C51F40F68DE0CB7ULL, 0x23EEA6CBBD6AFB20ULL, 0x6E059570244939B8ULL, 0x7E0BB4FAEB08E5ABULL, 
            0xC88E8D7108310C7FULL, 0xCCCEF42C19854B89ULL, 0x5B6AECE8806EAB1DULL, 0x3A74BE2A816FECF2ULL, 
            0xCB4010381097A27EULL, 0x4B34D46A686EB0B1ULL, 0x959F3FDFB51FD4F9ULL, 0x1660BF2B6001D6ECULL, 
            0x4088031F77C2E91BULL, 0xD0612C6DFE87D4ABULL, 0x7902309FBCE4FF45ULL, 0x37DDC3D74BBCF1EBULL, 
            0x7A7E872EE885C511ULL, 0x834A531406B7B861ULL, 0xD6ADCFCA3ADE155BULL, 0x06F17B598BEC07A9ULL, 
            0x21C06F720D0132DEULL, 0x01BE6382694C63ADULL, 0x2C6801DCD49E824EULL, 0xBE75030E3A9EBBBAULL
        },
        {
            0xF84CFCB69BA88415ULL, 0xC3D915E1CCDD2386ULL, 0x5BD92FB78810A8FDULL, 0xFF2A053421FC9823ULL, 
            0x5DA1EDA8AE413417ULL, 0x2C24E05C2ED5F553ULL, 0x9ADE91B65F81D9D5ULL, 0x07F74056EC098E22ULL, 
            0x8B299895F0EC7E58ULL, 0xEBCBD245AA737AC4ULL, 0x82890679F158C699ULL, 0xE54E28B51BEF8A47ULL, 
            0x6C861DE7D4816AB0ULL, 0x9C099CB63587C032ULL, 0x819D2440A9CF559EULL, 0xA806C3E3E0B2A6DCULL, 
            0xD83B5CB44FD0966CULL, 0x0B143873087A8450ULL, 0xDB0FDFADE12C4F56ULL, 0x9AC0E8D9691CFFFFULL, 
            0x792F98BB8250C7BFULL, 0x8F6CD646E7EDC8D3ULL, 0x5070C0D6A677A058ULL, 0x53AB9183FABB1D69ULL, 
            0x8A983A5E0D8A3B1DULL, 0xA22BA1B488496BB9ULL, 0xBBC347557E2F6803ULL, 0x513AB397BA20BB99ULL, 
            0xF902C8F93182F2BFULL, 0xA86B0B4016E68761ULL, 0xCC8C643C859F3CD0ULL, 0x965C9DDD45FB9D75ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Castor::kPhaseGConstants = {
    0xD9B6EADA78830FDEULL,
    0xF7ADE8C374FD333FULL,
    0x55C05074D4A9E9F6ULL,
    0xD9B6EADA78830FDEULL,
    0xF7ADE8C374FD333FULL,
    0x55C05074D4A9E9F6ULL,
    0xFBAF9C1E9D4541DBULL,
    0x919D4592821FDA45ULL,
    0x77,
    0x6D,
    0xD0,
    0x2D,
    0xEC,
    0xC3,
    0x8B,
    0x61
};

const TwistDomainSaltSet TwistExpander_Castor::kPhaseHSalts = {
    {
        {
            0xD65C64A1C98B210DULL, 0x5AE5FE5756E9121BULL, 0x08F8E3F0EED54430ULL, 0xFD96ED3075D88A66ULL, 
            0x64A8B1B4E9DAB633ULL, 0x9A2A1408F3173DE9ULL, 0xC7906494A8D2869BULL, 0x104CAF99E0AC7F03ULL, 
            0x25F80583FC9216D6ULL, 0x1D810F94CDAB2347ULL, 0x20D6E7ED28FD0E19ULL, 0x99C5AF2C88DFA1F9ULL, 
            0xD390869B0CDA5583ULL, 0x0501BEF93CD884E3ULL, 0x403D703B2C7F6D67ULL, 0xF88E7500A86B6E36ULL, 
            0xB2A7A36F1507A13CULL, 0xF5BD9D53837CD1CFULL, 0xD43B1B07496F102BULL, 0xE36CDCD5CF007A0CULL, 
            0x4296C952B2CAA1E1ULL, 0x18E13449D2C53D8CULL, 0x6253F7D7AC34A034ULL, 0xE8024BB0C6F93FF1ULL, 
            0x914D626DE845CE8CULL, 0xAEC79E236262ACEFULL, 0x2BC23D62067D836DULL, 0x66A4087F023ABACDULL, 
            0x2EFB1C16F7734010ULL, 0x324396DD049A0E0BULL, 0x0A1735C51C9A079CULL, 0x5DD089F4C20B91FEULL
        },
        {
            0xD53BF05EF7A30C24ULL, 0x9FBC8EE644ED1578ULL, 0x5C78A44EE5E8CBF1ULL, 0x1C55E79326F29016ULL, 
            0xF8C88A0CC30118CDULL, 0x0D3D80B1605C52ADULL, 0x5C58FC49C25C28C6ULL, 0x60DAD8DE8B9F4AC6ULL, 
            0x372E7C50A9C2FE70ULL, 0x18A98B1757814AE3ULL, 0xC3DEDCD141EAB241ULL, 0xF4C766045574157EULL, 
            0xAD4473315ADD46F2ULL, 0xDE94F427028052F8ULL, 0x287B3BACCA49206FULL, 0x2A7F1FFD92025216ULL, 
            0xEA6A2F2E83568E64ULL, 0x1F72B1504BD948EEULL, 0x950E652852095DF5ULL, 0x5C2EA8562BA3AA2BULL, 
            0x336EAA94519A447FULL, 0x64A110F814BDF9B9ULL, 0x9B749CE7155A280AULL, 0x619CDEA421CA90EDULL, 
            0x51726899635E7E63ULL, 0x2A53497C27D902EBULL, 0x28419D4020A62F02ULL, 0x0944C194964A93D8ULL, 
            0xB96BDAD9F479DEE8ULL, 0x04BDB01E50B79FD9ULL, 0xE2CD32C465CE5CE8ULL, 0x05F7D9401D2B9D47ULL
        },
        {
            0x87C87E9BD141DD58ULL, 0xFDD9354BC6F9EDAAULL, 0x6E7DD5A7DA2BAAC7ULL, 0xDCBB78B5826CED1EULL, 
            0x15FAA7CE07413522ULL, 0x9044970EDC47729CULL, 0x8E732EEDBCBC522DULL, 0xD446F9CD6EC86FB5ULL, 
            0x6D153409E7B04BC1ULL, 0x6727C91ACA4AB4AFULL, 0xC43F64E7C3599899ULL, 0xE0D290FC365D6A3AULL, 
            0x4D83ADD34A5BE7EAULL, 0x4F1D979AF47763F1ULL, 0x94F32299E85789C5ULL, 0x3B96BFD6312E3C20ULL, 
            0xA0955ABEE0D5E7BFULL, 0xA7ADD952DB4758CFULL, 0x63244BE2CCB197A0ULL, 0x80D556A54968D9B3ULL, 
            0x5003A107086C8F7DULL, 0x234C5402F553FEC6ULL, 0x7FA3CD5CC68D3BCBULL, 0xA585BE0A04D061A3ULL, 
            0x0321AC36E5CE0E07ULL, 0x473B825080390F95ULL, 0x7CBDC5D975FF2106ULL, 0xA5AA9976C5510F80ULL, 
            0xBF48EA62A6E1B9AEULL, 0x64E16809E80315C4ULL, 0x983B798A878874B0ULL, 0xFF29B151267200E0ULL
        },
        {
            0x8F3127958E4AFEBEULL, 0x5E467598343518FAULL, 0x5A148748DE458BAAULL, 0x39CAB9C417B76D62ULL, 
            0x42AA78D4B8E8E156ULL, 0x2D2A80A4BBC97E81ULL, 0xD2549BD0158CD8B7ULL, 0xBAC25E590D91259EULL, 
            0x5DEF0F95D7AA0B24ULL, 0xC3F8F57C10F5FBDEULL, 0x9798D5CA1B032577ULL, 0x8CC009A331F18534ULL, 
            0xCE610CF01C02DE99ULL, 0xC960ECB03AFF395BULL, 0x75BF8932C9D6F6E1ULL, 0xDBB50DC6AC8539D8ULL, 
            0x6B25B6E2DAA13F29ULL, 0xBC55071EE9142B05ULL, 0x40D608285318678CULL, 0x2E5C9BFCDDC61F74ULL, 
            0x89154BD89D76A0E1ULL, 0xA7A1597022DE3EBFULL, 0x58B7AED4A8BC342BULL, 0x27FF8F92C5250126ULL, 
            0x43E8E84FA451F726ULL, 0x3AF48EDDE7619F11ULL, 0x378B517019D03A7CULL, 0x5E673887040E94A9ULL, 
            0x9F5C74D0934ED032ULL, 0xD3A7991662CFE598ULL, 0x70B2AB4AAEFB5FA8ULL, 0xE6ABD8C8EA94E081ULL
        },
        {
            0xA9DF6274C170227EULL, 0xE990E5F892228C9FULL, 0x543B5E561F6B8536ULL, 0x86B824CD8E1C16F1ULL, 
            0xB9DD873917A798B4ULL, 0x1AEB0C766903F501ULL, 0x872DEBC17B135AB3ULL, 0xD09DDAF6A4B31B9DULL, 
            0x334EC4CA7D97B634ULL, 0x7EF8EEC1B480DA68ULL, 0x3C3E3AC20119878EULL, 0xDFA5E1518CD58C03ULL, 
            0xAA44326648A0959FULL, 0xA84789CB6610C92EULL, 0xF3E62B55231AA397ULL, 0x8A8A4A8F05211E98ULL, 
            0xE507A6CE7567B993ULL, 0x60C1C37CBDBB56F6ULL, 0xC4C3092A29072626ULL, 0x1E235476F134326FULL, 
            0xCDC850079C1A064DULL, 0x7D8E4D6278C0CCFDULL, 0x94F43E3D16E0B76AULL, 0x0EA9549C97B4B4EFULL, 
            0xC1DABD039F9BB45CULL, 0xB869FAA98833C1D5ULL, 0xDB8766A0FEA3B9FBULL, 0xC3530648592B242BULL, 
            0x8C9EE35231F81346ULL, 0x0C72FC2FF80A3DFBULL, 0x85A27D78DEACF4FEULL, 0x12719A7DE5022650ULL
        },
        {
            0xE27D119E408721CFULL, 0xDE121C71AA6400EEULL, 0xB01F4BCD1DEA79B5ULL, 0x9389685F56B67C85ULL, 
            0x6D1869BE16146117ULL, 0x9AFBFD4C8711D957ULL, 0x1BFED199335803F4ULL, 0x236B70CCB1B43915ULL, 
            0xC840DD952D094D67ULL, 0x206EE43EE65B0BC1ULL, 0x03171F6C8A22C5C3ULL, 0x0131394E1463BDE7ULL, 
            0x84DA330C23C62F7BULL, 0x6F4B45251C0C8084ULL, 0x3EF34242D18D6FE7ULL, 0x650E54DB11948F56ULL, 
            0x22F45C7C7837EA84ULL, 0x4396756DB6B508F6ULL, 0xD61B3A1AF2643925ULL, 0xD55A0C57E8A8EAA8ULL, 
            0xB765A167B231DE09ULL, 0x86E4618B456578B0ULL, 0xCEFB8B2CC6EA4D51ULL, 0x31E0CD4EE8EBCA0EULL, 
            0xD316534E7E3072D5ULL, 0x66ECDF0BD947FB2CULL, 0xF1D99F8AD5646B65ULL, 0xC3F154A6822EE87DULL, 
            0x1865E6CE46E65315ULL, 0x1109F754A779AAD9ULL, 0x614ED06DAC090B74ULL, 0xDA2B99368A0101B8ULL
        }
    },
    {
        {
            0xA69C7BA26910D90DULL, 0xFDCAF5985A31313FULL, 0x8EE2757825A3D0ACULL, 0x0EB5574B41630C83ULL, 
            0x32BFFE4DCD29C3FAULL, 0xFC60339213DDA1D6ULL, 0xE23AA9AA02463E5FULL, 0x1D7344C61F233893ULL, 
            0xC2275E21105E03C2ULL, 0xC86E7855FC5CDF65ULL, 0xF4DADC4418D93048ULL, 0x53E08EC8CF786536ULL, 
            0x35E6FAB3DE14459EULL, 0x3C0B44EE34088AB1ULL, 0xD9F68D3F0F3E92D9ULL, 0x953ED58F69814667ULL, 
            0xFF220E125AAF3640ULL, 0x80AFEA3197C5EB0FULL, 0xF925907EE972B252ULL, 0x6074B7E6167BD829ULL, 
            0x804DD0082DECC0EBULL, 0x45F6E59BDABFC654ULL, 0x2BD16CA2AE54595FULL, 0x3472C465B9DA6016ULL, 
            0x15897FDBB353A300ULL, 0x9C94F137834F4258ULL, 0x7FFE6A19C840A0CEULL, 0x509ABD95090B1989ULL, 
            0x2AF54A813E0044E8ULL, 0xC4E79D46886013ABULL, 0xD8DD00A0B52A31B7ULL, 0x05409E02E98B2925ULL
        },
        {
            0x34AC1A906FF3B05EULL, 0xB566A0DE9F51E3D4ULL, 0x49DB5FF4F7E69D1FULL, 0x46929A237D364AF5ULL, 
            0x3FF41CD9A631C4DDULL, 0xECD89A9AC0757786ULL, 0x05875C731C3BDF93ULL, 0x47A84A182ABA9D5EULL, 
            0x56AB84035DB57388ULL, 0x115DE0B3A4D2833FULL, 0xFA7B3CA5950412FEULL, 0x54BBDF15337F92A0ULL, 
            0x4F502703E9833CBAULL, 0xB50424EA4A60727DULL, 0x917476850D073C43ULL, 0x20339F9C1DB46424ULL, 
            0xB1766735276A41B2ULL, 0x74D317D854331C41ULL, 0x731F967DA8BBD0F2ULL, 0x62553EA467750207ULL, 
            0x2F8C2BAA5754DE56ULL, 0xE2334A67CBD6FE82ULL, 0x72F149AF38A5634DULL, 0x7517BE91052566C7ULL, 
            0x90C1AAD39B5F0CFBULL, 0xAC974B93B78307C7ULL, 0xD0730E60B1F59B13ULL, 0x440C2490EB60BC8BULL, 
            0xEE017DF4606C2F7DULL, 0xF94FA208D3769424ULL, 0x43520D1756C48A01ULL, 0xEC823AFD69A32EB1ULL
        },
        {
            0x28D2135BE33DDE76ULL, 0x250FD0DE1A19F9FDULL, 0x0DB93B3E0AD1835BULL, 0x91210BED56D415FEULL, 
            0xAD86334FA8B09F9FULL, 0x49130A1CECA4B811ULL, 0x4FE5E6422EB475F7ULL, 0x1B845B7908FBD2F5ULL, 
            0x8D6B918A05472891ULL, 0xE700077095B17C35ULL, 0xFCDAD53856356B42ULL, 0xFF3A02F7437D77D2ULL, 
            0x8B0D138E353A6289ULL, 0xC4881B4AA23C5ADFULL, 0x6AF00829DF8BD6FFULL, 0xBE324948746A95CCULL, 
            0x0CB90457E0718831ULL, 0x53BE6775A7A97017ULL, 0x31AF1EB93531E10CULL, 0x64EB32D5F8068737ULL, 
            0xEC010A0C64A0C93DULL, 0x55D770FFA09FFEE5ULL, 0x428A9A808DB0DFB5ULL, 0xDD0E32A74CCBB699ULL, 
            0xD70B1F6254F0F491ULL, 0x9564D1CE1EDD3399ULL, 0x336FDEDF760A924CULL, 0x94362430AD048A2FULL, 
            0xF427C8209E50F16FULL, 0xDF369710AEFCE85BULL, 0xA79E2B54CFD6C872ULL, 0x711E9FBB714392F7ULL
        },
        {
            0x0285488EDECC2569ULL, 0x8801355C0E8FAA1EULL, 0xD71F91B51CBA8E5CULL, 0x2295EB046E0D6EA1ULL, 
            0x265FAF659E53470EULL, 0x7A74A0DBEB4273A7ULL, 0xD66B07B344A60EC4ULL, 0xE3E0C22DB3A8FA63ULL, 
            0x9A654C5CAE13A106ULL, 0xFA639500E0CADE63ULL, 0x86463F67DD69A4C6ULL, 0xBC0441B298B3186EULL, 
            0xC31449C139482607ULL, 0x45A5AD6E9B469AC9ULL, 0x0139EAB33E3FE3ECULL, 0x3D80AE0DECF5E36EULL, 
            0x775B835EE390965DULL, 0x8987962923A965ACULL, 0x08FB64F8AA2BF503ULL, 0xB364248FD8CECCF8ULL, 
            0x246D47B0AF991332ULL, 0x617ACDAF25959064ULL, 0x868B64E15529DB6BULL, 0xF727CF83D582B44FULL, 
            0xECD1930A4D8E0E4FULL, 0xE130575E7F8E5003ULL, 0x10C47C16202BEF5BULL, 0x0368BA0952F20038ULL, 
            0xB248A106B3BCCA7AULL, 0x31D61A7FA4441C9BULL, 0x39B026EFAE263BE4ULL, 0x9AE5628B2D910DFFULL
        },
        {
            0xA2272F799B8F8411ULL, 0xFC7FD9D541FB6EF5ULL, 0xE70F5984C0AAAEE7ULL, 0xF0296C7980C1CC2FULL, 
            0xE9D86CD2F2A1935AULL, 0xA790593C17E96A44ULL, 0xC3D46332624817B0ULL, 0xD9AD545B99567AF8ULL, 
            0xC292D6EA8608215EULL, 0xC2F8D1E84474DC13ULL, 0x8FFDA95380558E6CULL, 0x71A4D7FACBC35900ULL, 
            0x9B0E2713D2F39874ULL, 0xDBD96BD00E851AC8ULL, 0x218FA748D7B41F5EULL, 0x93C7FFB8CEFD8C4CULL, 
            0x267B2A136D499EC6ULL, 0xC05F02654EB04ADBULL, 0xA49F1CA439F7BF30ULL, 0x655C9C5AF7E6D38BULL, 
            0x037D41A8DB2828B1ULL, 0xB5739BE4575ACE0EULL, 0xCCE6EEB76B777461ULL, 0x318CBDD2EF58C681ULL, 
            0xC32027EC73F7BBD6ULL, 0x24177DF8D46ADC97ULL, 0x696E0ABFC421D82AULL, 0xCFE0EA84109D5883ULL, 
            0x48DC62E4DFFF5030ULL, 0xDD942879A48250A8ULL, 0x99C5F757BCEDE6DDULL, 0x146CAE7D122DB371ULL
        },
        {
            0x53276D1FD47E5932ULL, 0xDC0A54DE54200CCCULL, 0x1F0B81AA3EA66285ULL, 0x8B1496E575746240ULL, 
            0xCAF9ACF31C4681D3ULL, 0x02CA7F0835AB0CE5ULL, 0x408439BB567606F5ULL, 0x26E78CD90442090EULL, 
            0x5E9D4FA248CE9FBDULL, 0x74A9C7AB96E1C15EULL, 0xE8A159ED83D2EE3AULL, 0x777AE63E51915027ULL, 
            0x5A42BD37D0FDEAB0ULL, 0x1234A6D0276567ACULL, 0xCE4211033658A639ULL, 0xA54E6B0C7FA23A13ULL, 
            0xDA8378E8A2B29D72ULL, 0xA05DDC2B027A0260ULL, 0x376815B19E17626BULL, 0x110E62EED5930572ULL, 
            0x7653CEC4DC14C139ULL, 0xD5F73E3C6B809BC9ULL, 0xBAD46507D4037C79ULL, 0xD67655DB0BB4E978ULL, 
            0xA71C854D7662CC5DULL, 0x5C933E406FB9D03EULL, 0x37DE07CA4F3FCF63ULL, 0x9E1CB63B22C89FE6ULL, 
            0x6BA33A89F88B6A08ULL, 0x86B0E339ACDDE70EULL, 0x1C038EDF8E9357D1ULL, 0xDFB51454C1B2042CULL
        }
    },
    {
        {
            0xDDCFE3DD97FAA5FFULL, 0x2A268200C295D35EULL, 0xC165EFAC79755FC5ULL, 0x1F994D6257EEC16FULL, 
            0x1B7F33EA55F0437CULL, 0xC394609621B00977ULL, 0x359D89122AAD7CEFULL, 0x35D3E1B1EF41EDE8ULL, 
            0x2B7548951067998CULL, 0xF29816188819EB06ULL, 0x6148059F04A5903BULL, 0x76AE0AF7BF8F2555ULL, 
            0xC2014A1BC9A1C499ULL, 0x6EB1011A914BC438ULL, 0x68A38BE6DFA1A2AAULL, 0x3E093A710BBC6EF5ULL, 
            0xECA05AEB837B9D92ULL, 0x89E37BEAD9C11A61ULL, 0x3024847ECE9F8FC1ULL, 0x7730901055591BFCULL, 
            0x98C7B710E58B6957ULL, 0x6AE43D78001123A8ULL, 0x87E56D8743C9891EULL, 0xC01B6F6F5E21D1DDULL, 
            0xCB880F0EE5DE3A1CULL, 0xC0CECD69B38C3948ULL, 0x43BA3CE2F3723ED5ULL, 0x0639D82AA0D91EC1ULL, 
            0x5C4ED98FD3F7179BULL, 0x565E6785AF9D8A29ULL, 0xD67D0D92ECDC83E2ULL, 0x7260CA5A58A7CB95ULL
        },
        {
            0xF81928CC0E6A5BF5ULL, 0xE4546A8A1BF89F6FULL, 0x8108F0FB14FD0B33ULL, 0xEBD7DBB57867EA13ULL, 
            0x9765CE70B8378CEDULL, 0xC0E29C04FD4C386FULL, 0xC63DDE2A7A8BBE1EULL, 0x1811E24F0BE5DA4DULL, 
            0xD520FEA11C221C4CULL, 0x85363A2C1AE88B4BULL, 0x19AF413496483487ULL, 0x40D22A972A12A4D0ULL, 
            0x96F4B0127A151235ULL, 0x2B2F957EFDA90103ULL, 0x9837A396390BD7D5ULL, 0xEA698B1F2CAC9B47ULL, 
            0xB0888C6C6BF2C695ULL, 0xC3FB05C8DED09331ULL, 0xDBF14F2D80838DAEULL, 0xBC5D4BBDC9916802ULL, 
            0x95E7CB42E0E33240ULL, 0xF8D5BABE4FC0B1D9ULL, 0xBDB7CC33BA0902BEULL, 0xDE610324345E7B66ULL, 
            0x0723FAE8ECE9900DULL, 0x2C58349EBD73C013ULL, 0xBBB961339B0C9B79ULL, 0xCB4E16DD6644B22BULL, 
            0x04A2A3D794DAEC08ULL, 0x5849EA5912B429B7ULL, 0x740F874739F4D958ULL, 0xECFC65E850CAF62AULL
        },
        {
            0xD6E8B0D17727D999ULL, 0xA62ADBECCEC43D97ULL, 0x395F77B55692E50EULL, 0x2E344C11494F3929ULL, 
            0xEF6A0F5DE833C6F1ULL, 0x0A15CA9E9F69B4DFULL, 0xF018B8823D8262B3ULL, 0x41098AE75AB2B86DULL, 
            0x69EE0E78444FEC04ULL, 0x7B63AC50DBC00A4FULL, 0xB81EF84AB190A3EAULL, 0x178B4CDA36B2EABDULL, 
            0x55D1BC592FB59C3FULL, 0x934D9666C639CBAAULL, 0x9A90E5FB88A3A83DULL, 0x98F42D0B3C682C32ULL, 
            0x30D557E653701E81ULL, 0x69DC706F44AFB1A8ULL, 0xFA3416555AFC8D2BULL, 0x5E13BE6D402177E1ULL, 
            0xF5CEE45700FDE470ULL, 0xF56A765BDAB5E3E5ULL, 0x1E7E9904B2377A73ULL, 0x0F049BFCCF9C824CULL, 
            0xA59FC0E7DCB3F9D3ULL, 0x151A7F984086695AULL, 0x6A6DA702329E0CAEULL, 0x1B612CF6C17175B1ULL, 
            0x98092F92D9A1D03DULL, 0x77912E59604128DCULL, 0xE266E6B50A36C77FULL, 0x38373B9980E4CA61ULL
        },
        {
            0xF642DAE8D5BB2ABAULL, 0x8A861E5F64ADAFA2ULL, 0x2A61830D8C7171C8ULL, 0x27259135FB12EAD6ULL, 
            0x3F21A4EF29E37990ULL, 0xA968A926439DE9B8ULL, 0xBD2D0158C5CB7744ULL, 0x52879D532E725C2BULL, 
            0xDDDD993AACF580DFULL, 0x51EE34F18FF53531ULL, 0xD66EBB1AE6DEBC19ULL, 0xE166A1B78593899CULL, 
            0xFFF7D65A0119033DULL, 0x1B64BE1B740F27CDULL, 0x28D12AE66D5E91DCULL, 0x307424A5EF21929EULL, 
            0xA064056382489D36ULL, 0xEA95F74BAB208CCCULL, 0x01A9EEAE76F001CEULL, 0x00251A338F8E8442ULL, 
            0x013625278AD8F5F9ULL, 0xD7DA64B74A3B2900ULL, 0xF64467B32D879C15ULL, 0xBECC3B905E0ACD50ULL, 
            0x33EE8C82A09B8098ULL, 0xEFAD15EB8C7F5C18ULL, 0xA054996CA1350A55ULL, 0x7C47FDA161B0787FULL, 
            0x238DF44E77555F75ULL, 0x77C86AAD41BF66ACULL, 0x3261A4C225B15D6DULL, 0xE46D06CA00D08C53ULL
        },
        {
            0x8B1CA15D659FA622ULL, 0x4F9517A0BF4A4D07ULL, 0xC6B0546902237F30ULL, 0x6CAEDE342E16AA38ULL, 
            0xFCF7215382265F65ULL, 0x1EAE3EF585B3ECB6ULL, 0xAC16FBF27A970222ULL, 0x412C825D6D0C8EECULL, 
            0x8A95D642C4D254D6ULL, 0x29631DDA9B1B277BULL, 0x204D88D40076A5B2ULL, 0xF0D028FCF97ADBF4ULL, 
            0x612BE840C661E9D1ULL, 0xD4938F614B50714AULL, 0xC1920BD822ED3FCCULL, 0x90A6229FF55CD228ULL, 
            0x844A7E572030CAF9ULL, 0x473DD7B91F922760ULL, 0x60DB2C0533A418B7ULL, 0x0B5289A7DAD8378EULL, 
            0x2581E64AC7C0B9BAULL, 0x38797DE2EC6B3381ULL, 0x8DBCF0DE0022BE5CULL, 0xC1C6D7B59E590A0AULL, 
            0xB84C46564DB2C2DCULL, 0x2D0585E2B56780DDULL, 0xE5680A016C7086D4ULL, 0x89C14075816969FFULL, 
            0xBE667A62C0F97A93ULL, 0xC63947F73630582FULL, 0x7EB6AA81B1CFA45CULL, 0x4D3D5F349E7B6752ULL
        },
        {
            0xA9FE867A03DDAFFBULL, 0x96C298FE5A50F96BULL, 0x0B48CA4DA38B14D5ULL, 0x9671E76884738808ULL, 
            0x079B1C980763F583ULL, 0xAE1C957598A9EA13ULL, 0x4A0FDC224C6CB26BULL, 0x060A079767BD28CFULL, 
            0xB4C25E755D8E2117ULL, 0x2E89E95ECB37E59DULL, 0x50D4C5B37479B92CULL, 0xF8B4F95EC2F83CF4ULL, 
            0x31A9C2725C93B2D9ULL, 0x789E0FE06E49B316ULL, 0xFFD0D8BE3C20B48AULL, 0x4B8D8B8CFFD97AB1ULL, 
            0x78E4255D7F851EB3ULL, 0xCAA20E86A1C9C32FULL, 0x9A0BB6F6EE76E927ULL, 0x5691CC3F4F55CD8EULL, 
            0x4D9AE3C52CA7A62AULL, 0x5FEA921D83DFB9F1ULL, 0x43C4B2C0EADBFB80ULL, 0x04BB3EA1A1B8DFCAULL, 
            0x564D5B5086068810ULL, 0x6B250E857915E764ULL, 0xFB496CEF03C811AAULL, 0x3944EDC8AE68572AULL, 
            0x11C426EC720FD308ULL, 0xA5A397B4E497C65AULL, 0xFF58C05F97497975ULL, 0x841E278DDE68F381ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Castor::kPhaseHConstants = {
    0x1F73A87451A085C8ULL,
    0xB2D8E06CF19035CEULL,
    0xD396B39DA95E444EULL,
    0x1F73A87451A085C8ULL,
    0xB2D8E06CF19035CEULL,
    0xD396B39DA95E444EULL,
    0xE75AA45AC6A8308FULL,
    0x5AE9CBBFBD19AA8EULL,
    0x44,
    0x1C,
    0x62,
    0x75,
    0x46,
    0x6B,
    0x83,
    0xCD
};

