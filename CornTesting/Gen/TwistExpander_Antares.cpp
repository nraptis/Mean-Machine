#include "TwistExpander_Antares.hpp"
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

TwistExpander_Antares::TwistExpander_Antares()
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

void TwistExpander_Antares::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xDFB104F9CEA55888ULL; std::uint64_t aIngress = 0xDD8925E0D33F4A64ULL; std::uint64_t aCarry = 0xE2F2F67566004228ULL;

    std::uint64_t aWandererA = 0xC45292097133E023ULL; std::uint64_t aWandererB = 0x850CB3679DE5617DULL; std::uint64_t aWandererC = 0x9DBA8B290EDC224EULL; std::uint64_t aWandererD = 0xA2D10841F65D2CDCULL;
    std::uint64_t aWandererE = 0xA18DEE8477660B76ULL; std::uint64_t aWandererF = 0x94B4FA9C31BE625EULL; std::uint64_t aWandererG = 0xB2BDB431887ED448ULL; std::uint64_t aWandererH = 0xDF2DA1529E13E4C5ULL;
    std::uint64_t aWandererI = 0xC894F96770A85DA0ULL; std::uint64_t aWandererJ = 0xAE7FC06E5EC92109ULL; std::uint64_t aWandererK = 0xCECF866F48EE312DULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 17183895421256064551U;
        aCarry = 9314116401075529645U;
        aWandererA = 15199632925329993585U;
        aWandererB = 15387067842525679564U;
        aWandererC = 10504436454906743788U;
        aWandererD = 13326616636399726033U;
        aWandererE = 17601404939721544991U;
        aWandererF = 12711259941261461631U;
        aWandererG = 15419904835671396672U;
        aWandererH = 14153783513768294876U;
        aWandererI = 13810563526965630020U;
        aWandererJ = 15723522835413418852U;
        aWandererK = 12149312781149177728U;
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
    TwistExpander_Antares_Arx::KDF_A_A(pWorkSpace,
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
    TwistExpander_Antares_Arx::KDF_A_B(pWorkSpace,
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
    TwistExpander_Antares_Arx::KDF_A_C(pWorkSpace,
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
    TwistExpander_Antares_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Antares_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Antares::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xC0461D49AB21A85AULL; std::uint64_t aIngress = 0x9A68EF2FB3525D01ULL; std::uint64_t aCarry = 0xE0B698116FB9E670ULL;

    std::uint64_t aWandererA = 0xBFEF38CA55A27BC4ULL; std::uint64_t aWandererB = 0xC011B75E7289B838ULL; std::uint64_t aWandererC = 0xFEEEB6F62664CC66ULL; std::uint64_t aWandererD = 0xB0F6EB82F94D41E2ULL;
    std::uint64_t aWandererE = 0x927D6682CC8B8700ULL; std::uint64_t aWandererF = 0xF6DDF86B1356A906ULL; std::uint64_t aWandererG = 0xDAFCBC428D56146AULL; std::uint64_t aWandererH = 0x982884AD83314FB0ULL;
    std::uint64_t aWandererI = 0xF647CBA272C9B653ULL; std::uint64_t aWandererJ = 0xFEE8FC36C6C0BB00ULL; std::uint64_t aWandererK = 0xD2AE317FF262A59FULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 16167845722423006299U;
        aCarry = 15027448756298752946U;
        aWandererA = 14501927022065884491U;
        aWandererB = 11879939719052927502U;
        aWandererC = 16985579193119282310U;
        aWandererD = 11641259516825034673U;
        aWandererE = 13265146433261890999U;
        aWandererF = 12495853101153835938U;
        aWandererG = 11759051279595569391U;
        aWandererH = 9255265191713464611U;
        aWandererI = 14557668150669322144U;
        aWandererJ = 9410086736182720963U;
        aWandererK = 18358374763229247578U;
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
    TwistExpander_Antares_Arx::KDF_B_A(pWorkSpace,
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
    TwistExpander_Antares_Arx::KDF_B_B(pWorkSpace,
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
    TwistExpander_Antares_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Antares_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Antares::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0x8E9C2C35FE124841ULL;
    std::uint64_t aIngress = 0xEE0F0DA261EF413BULL;
    std::uint64_t aCarry = 0x8DE7DC25CF6C81D7ULL;

    std::uint64_t aWandererA = 0x8BE6609C685279C8ULL;
    std::uint64_t aWandererB = 0xD8A65404526D46D0ULL;
    std::uint64_t aWandererC = 0xB876902A9FE37C63ULL;
    std::uint64_t aWandererD = 0x9380A5060E9B2C93ULL;
    std::uint64_t aWandererE = 0xDA5C36FF46A6F4F9ULL;
    std::uint64_t aWandererF = 0xB4022610A7AE732CULL;
    std::uint64_t aWandererG = 0xE60E76CB096684ABULL;
    std::uint64_t aWandererH = 0xFE584913122226B0ULL;
    std::uint64_t aWandererI = 0xC066AEB827A3E510ULL;
    std::uint64_t aWandererJ = 0xD906C673A7CEC01BULL;
    std::uint64_t aWandererK = 0xD601D6091E39725DULL;

    // [seed]
        TwistSnow::AES256Counter(aSource, aSnowLaneA);
        TwistSnow::Aria256Counter(aSource, aSnowLaneB);
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneC);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneD);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneH);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneB);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneC);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneE);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneG);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneF);
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
    TwistExpander_Antares_Arx::Seed_A(pWorkSpace,
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
    TwistExpander_Antares_Arx::Seed_B(pWorkSpace,
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
    TwistExpander_Antares_Arx::Seed_C(pWorkSpace,
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
    TwistExpander_Antares_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Antares_Arx::Seed_E(pWorkSpace,
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
    TwistExpander_Antares_Arx::Seed_F(pWorkSpace,
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
    TwistExpander_Antares_Arx::Seed_G(pWorkSpace,
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
    TwistExpander_Antares_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Antares_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Antares_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Antares_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 9 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1861 / 1984 (93.80%)
// Total distance from earlier candidates: 14924
void TwistExpander_Antares::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1107U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1450U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 485U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 723U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1440U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 960U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 493U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1071U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 605U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 434U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 116U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1438U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 721U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 672U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 78U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1875U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 100U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1346U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1259U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 349U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 748U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1218U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1201U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1881U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1360U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1640U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 283U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 647U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1124U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 179U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1235U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 483U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 518U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 71U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 949U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1399U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1604U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1163U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1619U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 21U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 301U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1437U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1101U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 77U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1700U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1194U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1095U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 938U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 2039U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1712U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 35U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1947U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1920U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1885U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 274U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 124U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 41U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 449U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1096U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 844U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1652U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 335U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1584U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1621U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 691U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1565U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1705U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 3U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 205U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1033U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 989U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1314U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 104U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 635U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 311U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1635U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 717U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 88U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1337U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 61U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 160U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 749U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 558U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1672U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 384U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1097U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 360U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 625U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 122U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 391U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1871U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 744U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 210U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 848U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1421U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1293U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1374U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1427U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 109U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 920U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 324U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1532U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 372U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 649U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 700U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 628U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 32U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1027U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1210U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1452U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 968U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 826U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1549U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 261U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 2032U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 440U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1511U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1994U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 803U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1479U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1643U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 868U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1467U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 251U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 299U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 581U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 641U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }
}

void TwistExpander_Antares::TwistBlock(TwistWorkSpace *pWorkSpace,
                                       std::uint8_t *pSource,
                                       std::uint8_t *pDestination) {
    TwistExpander::TwistBlock(pWorkSpace, pSource, pDestination);
    if ((pWorkSpace == nullptr) || (pDestination == nullptr)) { return; }
    std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    std::uint64_t aPrevious = 0xFE21A538E535825DULL; std::uint64_t aIngress = 0xBF1A4453E84312B6ULL; std::uint64_t aCarry = 0xDA6815EE99BAC57EULL;

    std::uint64_t aWandererA = 0xD00D28087696BDEFULL; std::uint64_t aWandererB = 0x8A317CA9A0EC52FBULL; std::uint64_t aWandererC = 0x9DB3EDC171E1D312ULL; std::uint64_t aWandererD = 0xA85C21E66747689BULL;
    std::uint64_t aWandererE = 0xF290CC4FDC5717E3ULL; std::uint64_t aWandererF = 0x9016ED23468EAE73ULL; std::uint64_t aWandererG = 0xA0B4D0DD43C094EEULL; std::uint64_t aWandererH = 0xC6264A9A007263A7ULL;
    std::uint64_t aWandererI = 0xD6F4D3E235B1A06CULL; std::uint64_t aWandererJ = 0x97C223C9B0C5EB18ULL; std::uint64_t aWandererK = 0xDC92D9BEE66DFCA9ULL;

    // [seed]
        aPrevious = 14094570144728332384U;
        aCarry = 10811146742864654177U;
        aWandererA = 15800945291570350689U;
        aWandererB = 9459312112955538095U;
        aWandererC = 16031066550495406827U;
        aWandererD = 14466741180847049810U;
        aWandererE = 16285964115416644963U;
        aWandererF = 10127197104016580001U;
        aWandererG = 10022336401147941386U;
        aWandererH = 12403356937036482131U;
        aWandererI = 9457330005031924333U;
        aWandererJ = 15497785283904643005U;
        aWandererK = 11259003424176800094U;
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
    TwistExpander_Antares_Arx::Twist_A(pWorkSpace,
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
    TwistExpander_Antares_Arx::Twist_B(pWorkSpace,
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
    TwistExpander_Antares_Arx::Twist_C(pWorkSpace,
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
    TwistExpander_Antares_Arx::Twist_D(pWorkSpace,
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
    TwistExpander_Antares_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Antares_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Antares_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 9 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 4469; nearest pair: 496 / 674
void TwistExpander_Antares::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6817U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1612U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3335U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4953U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1049U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4993U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6968U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7085U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3192U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 8037U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2750U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2893U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3999U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7792U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7178U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1989U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1477U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1832U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 523U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 38U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 264U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1672U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1240U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 228U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1157U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1511U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 863U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 72U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 401U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1210U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 375U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1580U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1664U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 617U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 801U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1108U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 9 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 4456; nearest pair: 498 / 674
void TwistExpander_Antares::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7442U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4329U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2730U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5871U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5433U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2726U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5116U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4631U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7424U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3156U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1587U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4194U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5712U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6377U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7097U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2948U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1760U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1847U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1464U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1622U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1167U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1873U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 544U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 581U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 686U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 75U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2035U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 165U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1177U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1188U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1112U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 986U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 2015U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1127U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1008U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 435U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Antares::kPhaseASalts = {
    {
        {
            0x147A43A8990EA9EDULL, 0x9A63F8E3ED8C1B5EULL, 0x770CC71279ED8252ULL, 0x2E66440B336AF968ULL, 
            0x2CACB07BA5A38FA7ULL, 0xE9C315B24EF31246ULL, 0xBBE5316FDF6D589CULL, 0x74481DA6E0EE1703ULL, 
            0xE8590A320E009826ULL, 0x2F8244360D302123ULL, 0x13D86C5797858D29ULL, 0xC44E5700F3DE4966ULL, 
            0xAE9EC4DA9D7BD5D0ULL, 0xB751945A9663B0EFULL, 0x68C5584FBC9218ECULL, 0x3DB5C9269DB6D84DULL, 
            0x4C79B93E195D94E2ULL, 0xE8CFEB0146516FBFULL, 0xF4D1A700A4039EC2ULL, 0xFC9A536F106DCD21ULL, 
            0x67DE54B8313001BCULL, 0x6DDF2AD98BD2D689ULL, 0xFA95D22AFD8C64DBULL, 0xF83D3B0E23E649CCULL, 
            0xF15B6A2344DF623EULL, 0xC7E7881613796B0BULL, 0xFCB4CBDC6F73E328ULL, 0xA5735A1CD3ED6C9FULL, 
            0x1AEFF9331711FC5CULL, 0x2786A93E025C53F0ULL, 0xF25473A5F2BFB179ULL, 0xE576372776F43C9DULL
        },
        {
            0xCBE23C113CADB772ULL, 0xA8A0473A3908D44AULL, 0x0BFD4948A01B83A7ULL, 0xFA69DE021B3DAB34ULL, 
            0x02B1ACE11D74103FULL, 0x2FCEDA45C7529C81ULL, 0x7CC898F91AA7B7F4ULL, 0x170701C8A0DB11D7ULL, 
            0xCA40DD789A9CE426ULL, 0x1536A50E8179C13EULL, 0x03A89A2D6D56DFD4ULL, 0x79DE11735FBA266DULL, 
            0x00A4BB52E76FF3EDULL, 0xFD6A09E1E6F64330ULL, 0xC8CEF5BF5824ED30ULL, 0x27EDE083F65A6122ULL, 
            0x025D21BE11DD7D59ULL, 0x828D72E9F7EFBFC0ULL, 0x1E412B1ADA2E75EAULL, 0x17578A214FBAD247ULL, 
            0x52DD4DC3AB3DFAD3ULL, 0x3FCB5193767D0AD8ULL, 0x4DCA61420799E254ULL, 0x0367E042FAD107C2ULL, 
            0xE6D8C2AD142E279DULL, 0x4C31A163F4659E0FULL, 0xD2DB25F8C31F87E3ULL, 0xCA1D42AB25B64FDBULL, 
            0xB411EB5F0357DF4DULL, 0xFA6FFB368665ED1FULL, 0x36BD48F9F8BE76E6ULL, 0x619F13B8F2B6027FULL
        },
        {
            0x63C14D3AEE71BD16ULL, 0x55D6223B41E729BDULL, 0xB6DC72F52F889265ULL, 0xB0F74DADA3C2F771ULL, 
            0xDC2E72B928424FB3ULL, 0x5F927C9747F216FDULL, 0xEB5926155E308B19ULL, 0x47FD07F4A18C4DC2ULL, 
            0xEF9AFCF6A1371A54ULL, 0x109D331F6D7C24E4ULL, 0x74DFFEB597DAEBD5ULL, 0x96F8C60A05AE37B0ULL, 
            0x2AD4B2F254C73BAAULL, 0x1F217F1569CC5766ULL, 0x2AE0C045ACF82A23ULL, 0xAF16D7EA1BDC9891ULL, 
            0xE87EA8AB17D7A596ULL, 0xD07F043B09F7C5F7ULL, 0x05B36DFF00E78EEBULL, 0x0531D0E1044A1E0BULL, 
            0x311819F8E09A1804ULL, 0xD5981CFF1FFECDB8ULL, 0xB7A567756A841AA7ULL, 0xC1A956205A85C96BULL, 
            0xFCC2ED9EB64F000EULL, 0xEDDB63C7772726F1ULL, 0x9A82317EB3DF5710ULL, 0x545A698276A89DCCULL, 
            0x50BEB8FBBB46BD97ULL, 0xF3651A1587861B08ULL, 0x404F9743EABECD04ULL, 0xD827330A36E376AFULL
        },
        {
            0x3395D16582F776E3ULL, 0x6FD9EB05A6EFED16ULL, 0xF3BF12198C87878DULL, 0xE3D50C74B9DFAF4CULL, 
            0x1EB66C0ACC51BC18ULL, 0xCB7D97AE9F8763B8ULL, 0x97716D8FFA7B687DULL, 0x3772C652061FF9F8ULL, 
            0x6130F72375FDDA6AULL, 0x10ED914CE184DBA0ULL, 0x8430FD2A27AAFBFFULL, 0xCA675229214C77E8ULL, 
            0xFE774EF98C68C4C5ULL, 0xF8F5922E538EB2DBULL, 0xF7E25F07614ED6A8ULL, 0xF294403C435B98F2ULL, 
            0xD6A1EED607632CDCULL, 0x6943E55519C7AEF1ULL, 0x80EC372B7A8ADD49ULL, 0xBE2E4A23332B8A8AULL, 
            0xD9CE87FE50D452F7ULL, 0xE774A00378801518ULL, 0x7B6B4911F6E302E6ULL, 0x74E281873637B19CULL, 
            0xD8674445BD8D2832ULL, 0x7F2D3F90B251F960ULL, 0x35897562A582494FULL, 0xFC7B811D4333975BULL, 
            0x2414E43B0865902FULL, 0x3FC96337B1D37D34ULL, 0x13449AEB7EA16B6CULL, 0x672F0CF7AC059BD1ULL
        },
        {
            0xD077FBC55DF8FCD7ULL, 0x535107B33B336C24ULL, 0x1D153B3A83B40C81ULL, 0xEFDE7292A4B5005EULL, 
            0xF732279566BCEB5FULL, 0x8270C32E6655C5ADULL, 0xAB246BB627AFEB05ULL, 0xF573EA6C828C9D77ULL, 
            0xDEDDC58ECFBA72FEULL, 0x64A2F02273A598DEULL, 0xF01F31F2DF0A614DULL, 0xA3AA36F0BE54E4A5ULL, 
            0xA1D34ED0C6191097ULL, 0xB04259CD8545804AULL, 0xA32481BAE2B9B745ULL, 0x2196C223349C912BULL, 
            0x0DFE0E018C8E0696ULL, 0x8875A394CDB83D87ULL, 0x8AF6C601C890E2F2ULL, 0x08814D463467A828ULL, 
            0xB5B1BEF4C4CDB06FULL, 0xA3C328E5FE472277ULL, 0xDB4644E7C3AAE78CULL, 0xE507948870F48978ULL, 
            0xAAB082CCA96B6E26ULL, 0xE9CDC0616B650EC1ULL, 0x2D45755EDE8B655AULL, 0xA0C773D86A23F58BULL, 
            0x8DDDECD605A28B7EULL, 0x73F1F5E0F47AE457ULL, 0x9EB020ABA1F9A1C8ULL, 0xD0A0CC207D444792ULL
        },
        {
            0x836E77920B362187ULL, 0x6E5A4F89EE84022AULL, 0x9163A9D3816CE941ULL, 0xDE6BF6DEB978A215ULL, 
            0x1EAB5828FD04BE6DULL, 0x73790B139D3B85EBULL, 0x1E4535DE9BF63CA8ULL, 0xCB67FFDBA9FBBC2EULL, 
            0xCFEBDC9BDA5ECC3EULL, 0x83A901FE6097DEC8ULL, 0x8AB29B71D2E01E7EULL, 0x0E9E493FEDF0F2E1ULL, 
            0x97D061021A5D48F7ULL, 0xA96DE12BC39B1530ULL, 0x35EF7C264E3FC7E8ULL, 0x106E691229D2FDCCULL, 
            0x691F5557E2EC3272ULL, 0xCEA57EFFE7628095ULL, 0xB114AAF0DAD140EDULL, 0xC0A46D77BB4D22E7ULL, 
            0x1433DF17EA0EEA76ULL, 0x8B5EF0FB8B6C1250ULL, 0xCA29E1F8687F443AULL, 0x771C4340C440F5B2ULL, 
            0x87808F393FF2CF22ULL, 0xE1621CFCC1DD06D5ULL, 0x4369D9FC0395DCE8ULL, 0xBC91BC47338A28C0ULL, 
            0x2A4E21066785A145ULL, 0xD1B0077AD2D92148ULL, 0xC0721C8EAAC8082EULL, 0xAA3BC5F4888FABFFULL
        }
    },
    {
        {
            0x7073ABD95F521E16ULL, 0x978005D98F0125ADULL, 0x2CD27792CF966691ULL, 0x6A02EBB822E7507AULL, 
            0xFD2408D70ED59501ULL, 0xA4D8EDF22EBCD0A0ULL, 0x7336DA813619AEA2ULL, 0x4545B35975810B07ULL, 
            0xFD00E510E17668C0ULL, 0x2C8755B716E8EDF1ULL, 0xB210EC5BE6AFF798ULL, 0xB43B7E87A3973779ULL, 
            0xC3784FB3AF398726ULL, 0x2340EA6D2F3E79B4ULL, 0x197BFF92B154CD23ULL, 0xCE010E58FAD141A3ULL, 
            0x62BF121972116027ULL, 0x54CDBD13895F84E1ULL, 0x23B88B26BDDFE218ULL, 0xA8498D2FCF5B5312ULL, 
            0x7D25B294FCA227A3ULL, 0x12B0905C309F5FA8ULL, 0x63639E343AE3F543ULL, 0xA5843963209C5B5DULL, 
            0x5B7A5F2E7AD22385ULL, 0x9A6152487E493571ULL, 0x9AB639D8E00189A2ULL, 0x4E67C4BDC628A6EBULL, 
            0x29425DF6B47203EFULL, 0x22206293F511164FULL, 0x9A13BE37E669CAF4ULL, 0x2D75A6E8C83C4C4FULL
        },
        {
            0x378FB6EB89D725CCULL, 0x1E4732B4001BBC5BULL, 0x3A945905923F28CEULL, 0x2B7200C86FEE8390ULL, 
            0x64AAC053E191BB7CULL, 0x8A69AEC000FE2C9FULL, 0x323503C1B71EBCB7ULL, 0x807CAA24EE5D778AULL, 
            0x3562CA078E478EA1ULL, 0x104DEA8ED7902E53ULL, 0x7E9ACD2BDD0F34D5ULL, 0xD4842A22089006FCULL, 
            0x35D08BB7DF06A894ULL, 0x85B6B01E8AEAAB4DULL, 0xA7048CABBEC025EEULL, 0x768ECB3DE57378B6ULL, 
            0x58C2E3AEEE4E5EF4ULL, 0xA2BE520873E9E78DULL, 0x1B1078C6EAFEFC2DULL, 0x626A6C33BD6A8698ULL, 
            0x2C9ED3A17AE0AC37ULL, 0xF0BD416742336D9EULL, 0xAB131B03B0836B79ULL, 0x65C4A32A80DC120EULL, 
            0x47EC2424707900A4ULL, 0xC8196F1E008E38E7ULL, 0xD383966CAC823AD5ULL, 0x92DC0E68ABBEFB66ULL, 
            0x4A37C31070784CF6ULL, 0x42780C7C47B4D105ULL, 0x43F067CF45B383BBULL, 0x40D2AAADE59A52D8ULL
        },
        {
            0xCB995CF6FC5DB8D5ULL, 0x3BF016A6464B793EULL, 0xBF82F349CC2481AAULL, 0x8984D27A8D96C4EBULL, 
            0xBC2032642B250786ULL, 0x99F5F7459F97778DULL, 0xCC331A5BAACCB0D1ULL, 0x5DDEFD64D4606BCFULL, 
            0xF88ABE2FD462CBA4ULL, 0x26C6822C06173561ULL, 0x884CEAD3CCF051ACULL, 0x0B7D89B819F0AC93ULL, 
            0x1091C31517B05C88ULL, 0xC81ED7113A14A20AULL, 0xBA1B5032CBE944A1ULL, 0x5764FE2686D6D79BULL, 
            0xCC31FA15ADE33702ULL, 0x8ECB6A5D7D8503D2ULL, 0xB102F5D031D3BE84ULL, 0x3CCB0F9982B1ED3BULL, 
            0xAFC84B9C829734B0ULL, 0xF4077F8B0223644FULL, 0x017BF11395FAB3CEULL, 0x0AD654CF0B8A9C02ULL, 
            0xB38A9C9633C771E8ULL, 0x5BA83CB335CEDBBBULL, 0x1A9B382DE1906865ULL, 0xFFA76E6E9A021D27ULL, 
            0x68E6FC765F5F44EBULL, 0xC4C7F5C49038094CULL, 0x721903F2059C69D8ULL, 0x323CE186B20A2A09ULL
        },
        {
            0xBB08F6B217A91523ULL, 0xDC75289AE4FABCFFULL, 0x25C310014C073114ULL, 0xE67E8AFD0FE1792AULL, 
            0x9B7C16E71913F2F5ULL, 0xF466F31D2C4C9D1CULL, 0xCF1689CAADAD1DF2ULL, 0x4058B1182AD39885ULL, 
            0x0DE8668796B26B68ULL, 0xB385B5A23160F0C0ULL, 0x7EEEFE70400338E7ULL, 0xC0EA1E9302E50605ULL, 
            0x15D7C9D17037E6D8ULL, 0xD29236DF9E5E634EULL, 0x4991641237D35BE7ULL, 0x33C64E94B4703141ULL, 
            0x75D6C06E1CA9A039ULL, 0xFB943A82F04F2620ULL, 0x6091721C65C066EBULL, 0x42D41A024E07A96BULL, 
            0x1684C3A91B54E061ULL, 0xEA5648A71F965CDAULL, 0x0508F750625EC021ULL, 0xB683098BC9CD8A03ULL, 
            0xA020A77AFCFA5548ULL, 0xBC8BF92BEEC23F33ULL, 0x59AD0084B01768F0ULL, 0x4C8C3CB43BA4AA04ULL, 
            0x033FB61DF7135989ULL, 0xB5FC2AD06A9B90C7ULL, 0x2A230E4D4F6FFD23ULL, 0xE9929AD29F8C4D71ULL
        },
        {
            0xF4D4511D9A7660C3ULL, 0xBD7A4E3122A71BD8ULL, 0xDE896C1FC63169F4ULL, 0x515DFF8B464D7BC1ULL, 
            0x8FED990ED6F8B28EULL, 0xD014D17FA157010BULL, 0x79221EEF415AC213ULL, 0x4380B6AA4EFD27F2ULL, 
            0xE9FB74BB59EAE088ULL, 0x4323E6279F3B57DCULL, 0x9A0A5DF7BF187BD5ULL, 0x620E6A488A36BE9CULL, 
            0xDB22700B9FF03B2BULL, 0xFA227DE7166E6662ULL, 0x24B92DB0CF06AAB2ULL, 0x2FEA4B8C93153436ULL, 
            0xFBC2BE2A317289E7ULL, 0x9124D89479CCFC75ULL, 0x82F84071F714A146ULL, 0x8E50D5E539D048A9ULL, 
            0x11FB4F837B97B83FULL, 0x1FF61EB41B9323ABULL, 0xCE057CA51A518B60ULL, 0x338B68FBDD543B4AULL, 
            0x2ABBFF8C55681F80ULL, 0xAB2060CBE79C147AULL, 0xCFB984EE19D7EAF2ULL, 0xD41CFC847A1F3BB4ULL, 
            0xED08A451A1921523ULL, 0xEC8D9EBBCB79336BULL, 0x41E591E988C2525BULL, 0x25D7FAB27052A7DDULL
        },
        {
            0x022EC899E112540FULL, 0xD0CF23F8839B1D23ULL, 0x5D10E4E93FEB6DC8ULL, 0x2AAED7838BBB24C3ULL, 
            0x97498357C5B9AF34ULL, 0x6E426B2DA1569D8FULL, 0x9A0B0857C25257EFULL, 0xAA750D9CBE2225D4ULL, 
            0x02F74C8A3F4AB13CULL, 0x3684B9EF5523B60BULL, 0x5E16A92F8224E2EBULL, 0xEFBED2B670C31723ULL, 
            0x09EDA0C9A06DD31AULL, 0xFB5B92DC3F1780F5ULL, 0xBD21B339CABE3A24ULL, 0x236C2FAFC2333E30ULL, 
            0xE1C0F91500B1B35CULL, 0xBA7FFF768485467EULL, 0xF25362B0202098F6ULL, 0x6919924392C78E52ULL, 
            0xA2A301005239D2AAULL, 0xF268643B76C1BC3FULL, 0x0AF4C7A7476CA513ULL, 0xA7B6AFED25668416ULL, 
            0xFCA9C2E3D43D3739ULL, 0x69E744EBC49FB70CULL, 0x31AF47DCEB1FF29FULL, 0x832CBEC59BA693D4ULL, 
            0xD82563957C519922ULL, 0x0B59C4D205B54075ULL, 0x21CB5B75926DD430ULL, 0x1BAEC78CE36D147DULL
        }
    },
    {
        {
            0x23BA75BAB83AA145ULL, 0x310F87F176D3A59BULL, 0x755B04EFFF7DACA4ULL, 0x117D6FA9C70049EBULL, 
            0xEA34BAC1F9D7150CULL, 0x8C46D9A079367D0DULL, 0xB53A372070C76390ULL, 0xDA9F8D7E61150638ULL, 
            0x42349437C03DF462ULL, 0x2CD6F1B67CE7065DULL, 0x7B10818A3F0B1B58ULL, 0x09356A873AD435EDULL, 
            0xC2D0EAE295310004ULL, 0x9E97BBDEBB7B4458ULL, 0xFD363121793B7CF2ULL, 0x03FEF6CA3F8ACB10ULL, 
            0x5BE090E1CABE15ECULL, 0x43D97E0A8BA97BA4ULL, 0xD41994C711492D11ULL, 0x652F79EBC3CDA333ULL, 
            0xC512047D5AEC3857ULL, 0xED034DF3353DF2BAULL, 0xBD774201BA839E1AULL, 0xF05A36BB9092E04FULL, 
            0x27839A5EBC00C25AULL, 0x99BCAC2FDA0213C2ULL, 0xFDFFE4D17B799648ULL, 0x84056353D99CA6A9ULL, 
            0x3679E6B66E9BFA52ULL, 0x283DD1E2AC053DC9ULL, 0x0577383DE06E0F55ULL, 0x456CACF1558D101EULL
        },
        {
            0x049365EF5925357BULL, 0x8B2A96F7077B6331ULL, 0x7FDAF3DE5DE4EF5DULL, 0xF2AAE89409CFAB68ULL, 
            0xF3236CA9D82085B9ULL, 0x7E7282FC98611C1CULL, 0x8BBDA84EA2880EDAULL, 0x90D02B613E1D0EDDULL, 
            0x86839BDB73DD1205ULL, 0xC13D384611A6F055ULL, 0xC89351504CA18DFFULL, 0x921955BE3497F554ULL, 
            0x0DF9003F5FB66464ULL, 0x0167FA51E7F39EE1ULL, 0x4D2E733A4A43AF9FULL, 0x3AD54DA2F54BBC49ULL, 
            0x54814C7DE141BF12ULL, 0x1C9A12C95B838E0BULL, 0x80821113CC01D871ULL, 0x0EDDBFE9A1C6FEA7ULL, 
            0xFC1A86ECEA763A68ULL, 0x536B54F9A35C3D00ULL, 0x21A9A3417E1C8F07ULL, 0xA4B7972DA3C7A2A2ULL, 
            0x6EF8074D232C077CULL, 0x4C3E960472DE345AULL, 0xA172C2B35DFE2FE7ULL, 0xE56458A83B10EF7DULL, 
            0x7C63DF2103A8E55BULL, 0x6A0CDD748603110DULL, 0x80068DB7C95C349AULL, 0xEBA8A61F74596954ULL
        },
        {
            0x4A77640CE7E48570ULL, 0x1804EAEC1932EB74ULL, 0x15B047651F0CE0ADULL, 0x52AD77632A5C70DEULL, 
            0xE0BF29BD4879C398ULL, 0x8FC719887E214B96ULL, 0x4E4669B4177B3EB6ULL, 0xCE6D8E6A0DEBDB11ULL, 
            0xB3D29E559C3021ADULL, 0xC90BA889F3F5B670ULL, 0x94264A7297742927ULL, 0xC1D93B0A124D9AFCULL, 
            0xD68B98A014FE62A5ULL, 0x01C94E566F7C13A7ULL, 0x4837843E8106E0F8ULL, 0x3A03C025DE9BA5BBULL, 
            0x8C51832732343984ULL, 0x408D4B041EADFEACULL, 0xE32D14990ABCAB02ULL, 0xEE0D50E8AF7D330DULL, 
            0xCB57E5FD55AC8E87ULL, 0xEBBC2B7C381F96FEULL, 0xE63D8E3D221909F3ULL, 0x391CBB3E6CFD97E1ULL, 
            0x8EDFC94652892CD6ULL, 0x0E732D75FB06BE73ULL, 0x9DA216B564B9E550ULL, 0x0CE28E9E664C32A2ULL, 
            0xAFBB584C4C2AA0A3ULL, 0x0238FB6265EFEEEFULL, 0xD2E7C3C2AB23123EULL, 0x1D93A9391E7E2F4EULL
        },
        {
            0x4EA4DE07C5C11DF1ULL, 0xF68A346DE233D9F4ULL, 0x452F77193D148730ULL, 0x6D033A51EB9961E8ULL, 
            0x37382761F5202254ULL, 0x9A1F62CE385B73E7ULL, 0x9EA3EA5964B4FFBBULL, 0x1F988B979025EA55ULL, 
            0xE3C904235437D4CCULL, 0x485B9F74D1BC1F31ULL, 0x3BF4AEFF5B252D54ULL, 0x2174D230EEA91A58ULL, 
            0xB516A786126A601DULL, 0x503C45903B07E52CULL, 0xE5755989DAD7FE9BULL, 0xF011A1033629221EULL, 
            0x8DE0B22DEA45CDD6ULL, 0x84AA0875C757D431ULL, 0x116360537379AF53ULL, 0x5284E3F1945FA4FCULL, 
            0x7F0C417D3D1DA5FAULL, 0xC9F0EC8024DE906FULL, 0x575C4FD026BDA573ULL, 0x6ED800BC20F7ACFBULL, 
            0x11CF89AFF14E3F85ULL, 0xCA8E824817C460BCULL, 0x346250A458957CC9ULL, 0x8DB479C063BB883EULL, 
            0xE55FE158FB98D6E0ULL, 0xF0E31A71DFA7273FULL, 0x31EB378E5CE33E01ULL, 0xAF939AB944A272CEULL
        },
        {
            0xE8C08C977986772CULL, 0x39088419A022B820ULL, 0x8F5814D4E6084801ULL, 0xA5DCA11DA7668E22ULL, 
            0x63E09FAA3393D269ULL, 0x0A96AA821AFA69F8ULL, 0x8B42729B90E58A11ULL, 0xD58DBA88F26ED77BULL, 
            0xBCB88BE30001C688ULL, 0xAACE9707F613EFB9ULL, 0x530DE48B447E471EULL, 0x73C3BA882717EC3DULL, 
            0xDD128DA6472E034DULL, 0x05C2BE9E1219A3AFULL, 0x98D093D7B6038DA7ULL, 0xAC656F68E0FD983EULL, 
            0xE4CA033A42C6F66DULL, 0x1D8BFE427CE99122ULL, 0x95A6B6C8E3943E86ULL, 0x2DAB9DE7EAE7084FULL, 
            0xA6081432EDE72CD2ULL, 0xCAB3C32A80371FEEULL, 0xCB7B899EA22F7F25ULL, 0xA20410368EEF3E39ULL, 
            0x2382CD5848478726ULL, 0x70F0089FBA377905ULL, 0x84D557F5E11BDE75ULL, 0x12C898A3CF7A7FEEULL, 
            0xF6C47950F4AC5AD7ULL, 0xCF729C608D73B512ULL, 0x4796358C61488F3BULL, 0x7CCC92D396AEB14CULL
        },
        {
            0xC92A583AE5FEB731ULL, 0x3AE8C86DE6D578CEULL, 0x42882448A327CDDEULL, 0x449D8591DD5DD634ULL, 
            0x856D9DDB5F8B4574ULL, 0x7FE656A7C8D64321ULL, 0xAC9997E3484B8AA1ULL, 0x70DF65FC091D1F11ULL, 
            0xFEF2D8C331C197E4ULL, 0xCE48B5E60A50C01AULL, 0x9000AD7D77189ABCULL, 0x790154BE8DF66379ULL, 
            0xE0276B347B87D283ULL, 0xA5ACDF53DD6F116EULL, 0x8A8034ABB5A4262DULL, 0x98F060C2CAD5D7EFULL, 
            0x3B457A146A9C3FA9ULL, 0xB85A08BEA8484B3FULL, 0x6BCD3E813274E1BEULL, 0x5709D816AEC1017CULL, 
            0x5DF50D3BC3BF881CULL, 0xAD98D17F3A3DC545ULL, 0x8193EBF347501B6EULL, 0xEA1D5011E717C200ULL, 
            0xD9002FA971C970A2ULL, 0xE89AE7F81525DF78ULL, 0x1E298C5CE1275A36ULL, 0xA61ADA50BF37672EULL, 
            0xDFF761805C52FC08ULL, 0x3D1535B0CD56CA8CULL, 0x93717A315AB27D7CULL, 0x1A77B4F671F86ED9ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Antares::kPhaseAConstants = {
    0xD903375092288EA3ULL,
    0xC1326B29D876CE08ULL,
    0x47E34EC4F8A74E49ULL,
    0xD903375092288EA3ULL,
    0xC1326B29D876CE08ULL,
    0x47E34EC4F8A74E49ULL,
    0x58E9263CA77E2684ULL,
    0xE38B0549ED550E46ULL,
    0x60,
    0x44,
    0x62,
    0xC9,
    0xEA,
    0x15,
    0x69,
    0x6B
};

const TwistDomainSaltSet TwistExpander_Antares::kPhaseBSalts = {
    {
        {
            0x6D24F3347A44CE23ULL, 0x81099BC9387C79C6ULL, 0xF0F68748F0E5AB7BULL, 0x146D2734CAC0D2B8ULL, 
            0x04B693EA1A4B45D8ULL, 0xD5F53971C0175EE3ULL, 0x701D7433B4BB49E8ULL, 0x8E2B27DC68CA7FBCULL, 
            0x2C6201633691CADDULL, 0x4E5F3689C29E7A15ULL, 0x551890DA379E0BC4ULL, 0x2CDAEB6C917C3072ULL, 
            0xE22CE09B73977D94ULL, 0x23918FE3D3333395ULL, 0x9EF6BCB6B126446EULL, 0xF16E9620ED3309C4ULL, 
            0xB58E2BC95BEEE886ULL, 0xD19DADEC380908D2ULL, 0x3530C1DEDDDD9A39ULL, 0x9D20B6A2DBA788E8ULL, 
            0xF89D6DD5A90CCC2BULL, 0x76E135A15E996D10ULL, 0x104B1353F5EEBE9DULL, 0x5430A682978E68DAULL, 
            0x90DADE134C3E9BF9ULL, 0x9E9347B0C0FCFC80ULL, 0x314A20AF749D3069ULL, 0x860916ED1FDEEC09ULL, 
            0x2377148CDF2C1E52ULL, 0x725E3DC1622AA321ULL, 0xC206E5CDE4F4D2C7ULL, 0xCE1022336C36D99EULL
        },
        {
            0x4CFD19F7C2F1A8F8ULL, 0xFB41562F040D03BEULL, 0x0A96F2E6E01BAA08ULL, 0x51FFDC57B9CC486DULL, 
            0xA2420435E00A43F4ULL, 0xB5BC31C26E4B7DC2ULL, 0x223CF85C6CDDF840ULL, 0x89B85683A9237D20ULL, 
            0xDF95256199AC414EULL, 0x3FF7B67DA1F86402ULL, 0x419FB6BA7E383E4EULL, 0xF13D07F0CF6D04FBULL, 
            0xFDD126063CF9A3C4ULL, 0x2BA2FAF4E9031CEDULL, 0x27CD3343E616A302ULL, 0x2DCEDA0B4B9C1253ULL, 
            0x3CF3DE8FAEEA4411ULL, 0xFB75187EA49E46F6ULL, 0x2F5E67A358C1B8EFULL, 0x832E93DD23E85906ULL, 
            0xFF63604004CA3FEEULL, 0x4B54306348926481ULL, 0xB56B3D25AFF770FAULL, 0xC441562939FC05F6ULL, 
            0x453EC8698B4AE22AULL, 0x9C1234630C071B03ULL, 0x71B7E944DBD417C4ULL, 0x6D5CAB6DD75197A7ULL, 
            0xF56E91C6B0F57A7AULL, 0x515DC28958E13A60ULL, 0xCDA180512590D713ULL, 0xB0C570D7A30C4CF8ULL
        },
        {
            0x56A10FFAFC3089B5ULL, 0x24F91D73EC998388ULL, 0x70CE91C45B616456ULL, 0xC8A8F230CB1B7C5BULL, 
            0xAE0E63D76CFE9548ULL, 0x583D01C6E34ED7A6ULL, 0xB6C74D5977E053D4ULL, 0x1FEAC72F3B40AC64ULL, 
            0x5AD29ADC09B2364AULL, 0xECABD25E17893E67ULL, 0x7B5413B66FC3862DULL, 0x5FCCBF237E65CE8DULL, 
            0x85739F08AAB04190ULL, 0xD6AC3683AF4F2CA8ULL, 0x13D361E6A6BF062EULL, 0xFCD16613A2CDCA29ULL, 
            0x47D2F44F1D2597BAULL, 0x081E740217D7DDAFULL, 0x9F5CE5E8223B821AULL, 0x5642984A0AE9F53AULL, 
            0xB3537ECB731958B7ULL, 0x5B41D56F07006B02ULL, 0x26D6FD69828FAD52ULL, 0xC2FA7B82B982E660ULL, 
            0x782BF46942AACB44ULL, 0xBC84598541D173BCULL, 0xD0576D12FED79D56ULL, 0x2D985E879F55F427ULL, 
            0x7F02DC4C37B92D21ULL, 0x44BA08E540CEC82BULL, 0xB71FED0BD5189FC5ULL, 0x3D0AA5EC41B9771BULL
        },
        {
            0xD9D2B122076B7502ULL, 0x1D0844C8E8308F1AULL, 0xD39713CD209E124AULL, 0xFB4FB1CE64733FBFULL, 
            0x0FD4D0C8BC8C3D3DULL, 0x265CBE67BD94B53FULL, 0x7C2E18D9B638D156ULL, 0xA3053B2EE194607AULL, 
            0xCAAB4F27E58C9B5DULL, 0x406AF287474A4898ULL, 0x449EA70357949550ULL, 0x9782A9342A9770ECULL, 
            0x38B402BD3CA67D5AULL, 0xF160F8B5B3D0E3D0ULL, 0x1C916359BFDA4299ULL, 0xE32DF17AC60EC75BULL, 
            0x7BDFC418864A0243ULL, 0x73956C7A7400916CULL, 0x0977D51E2371116CULL, 0x38B3B0FEC07B74D5ULL, 
            0xBFAF21920EB5ABEDULL, 0x41D1BF0923DFD27FULL, 0x70BF936A553CF6F7ULL, 0x72AF3797C9599024ULL, 
            0xDFCCC3CF217A4F5AULL, 0xE24AD08B0131471FULL, 0x56607770369F045CULL, 0xE907D8F3E0A37DD7ULL, 
            0x30D2FD5969D17AFCULL, 0xCD87F7D47E09EC77ULL, 0xDA57ADDADD4476F6ULL, 0x210308E2F7A7C327ULL
        },
        {
            0x7EE88C093A6E4786ULL, 0xA1BFC1A8799E3E2CULL, 0x3ACF5CA4BEE7ED13ULL, 0x62E3204576564154ULL, 
            0xDC9F88EF85987EA2ULL, 0x6681676B4D84C5A8ULL, 0xE6908B48DE9844C2ULL, 0x90835FE6856C5C37ULL, 
            0x45C1DB25AC22AE75ULL, 0x917961AD95647D72ULL, 0xE9F6A60C0E9EA770ULL, 0xAF5B93C86409B18FULL, 
            0xA70CC62871F891D1ULL, 0x5EDDE3F6C8F20E36ULL, 0x89691FDF7688BA2EULL, 0xF039EEFC7791385EULL, 
            0xEE2C49079B1B67D2ULL, 0x257DEB3B44EAEA7FULL, 0x49E839B7A1120027ULL, 0x36395F0B3D0BB9C1ULL, 
            0x655E29CBEACF5DC1ULL, 0x4CF5D84EB24276FFULL, 0xB5CDF82386DB70F8ULL, 0xFEEA46A11F8630A6ULL, 
            0xEB15B3FC72F504F3ULL, 0x15F05049AD3BF886ULL, 0x0E5D49D7892D68BDULL, 0xA6E0D78ED903A612ULL, 
            0x0AEAE17A19E27334ULL, 0x6364BBB8DED24637ULL, 0xA16724F3DF0B04FFULL, 0xA982518FD1D550AFULL
        },
        {
            0x0F7B450EB5A5011BULL, 0x4FE19F2A1CB9B091ULL, 0xD244E12844F9D1ECULL, 0xED743D3019D526A5ULL, 
            0xF94FDDD63E5339ACULL, 0x11E3C6002C2CDDC3ULL, 0xC7BFB7F7C7172BF8ULL, 0xFB5F5828E5228916ULL, 
            0xAC2FD13E571C7FDDULL, 0x3580238885E60ED9ULL, 0x75B2734382239A5FULL, 0x8398AC55FF5BC957ULL, 
            0x1661782C377C4B43ULL, 0x57063EB2AFFD5EB3ULL, 0xE3A07E0AB90C551DULL, 0x2C3C67FE30B82B32ULL, 
            0x2FC6E5464299EF79ULL, 0x7E930FF42EA0F907ULL, 0x74D0DBA9707EF182ULL, 0xB3FEB5846174EAAAULL, 
            0x34393FB789D57072ULL, 0xD7A1B96EF5BD14FAULL, 0x1ADB8AE3D12A3CAFULL, 0xB5ECBEE01C0FA8F7ULL, 
            0xA84F8AD2E2D72B9BULL, 0x5E6C7A7C92040E9DULL, 0x0B67E25D34F83A68ULL, 0x6FCC4A28EBE4A616ULL, 
            0x65C78F2385E44FA0ULL, 0x03B84B7DCD79447BULL, 0x92B9A17145CAC6B4ULL, 0x3C4FD1EFDE418470ULL
        }
    },
    {
        {
            0xF3D8224B0E475027ULL, 0xBDE18DDDFC53FF92ULL, 0xA742E1277E6757B5ULL, 0xFD58FEF5538E8F8FULL, 
            0x36349BA1B3FC11E1ULL, 0xEDFB6A147A384E69ULL, 0xE520120ACA15087CULL, 0xEA6ED5B5EC98F69AULL, 
            0x29117F66E049B45CULL, 0x2E43AC8E3DFE7827ULL, 0xE52ED611CF2A34B0ULL, 0x2A87C2F5B26AA7F7ULL, 
            0x5D277B8C81DC49B1ULL, 0x5415435F1D20C567ULL, 0x18D4BB07560CEB68ULL, 0x0D3DAB038291D907ULL, 
            0x6C208335AB4F4FC1ULL, 0x6B090940E00AF3ADULL, 0xC9EC54D54B8EC38AULL, 0xDA9E2B4ADFAB62E1ULL, 
            0x301D3FE7076D9A0EULL, 0xCBE00AE0CC72C8A3ULL, 0x9EE8D767039A0E39ULL, 0xDEF4CEC15426B7A3ULL, 
            0xC8F7F98B0428201AULL, 0xB0E66649DC5C501CULL, 0x7469E61A4D115D36ULL, 0xE8C40A931F2D8FA0ULL, 
            0xE7822FF41E7403ADULL, 0x4F350551C5B0C799ULL, 0x6CE2A9883F2A9E35ULL, 0x85D695A6C7F510D3ULL
        },
        {
            0x5A8A6EB55F487A18ULL, 0xF88FA5D775612EF8ULL, 0xADD6EB55ABD3BFDEULL, 0x33BBB0D75A9E16A4ULL, 
            0xB6BFE8C9CE576112ULL, 0x91DDA131FE422C88ULL, 0x589DD39590B58EDDULL, 0xF6CAEF67124F8810ULL, 
            0x68020FEB11F854EAULL, 0x79FC87C76955485CULL, 0x51F16B06950882E6ULL, 0xB24410A12E669B40ULL, 
            0x8791FED752E682C6ULL, 0xCA7EE2879AADF00FULL, 0x42D1B969F54610C9ULL, 0xC8E3B2BF3C4CAFC2ULL, 
            0xBA4899B074001795ULL, 0x9130D5D2347B4441ULL, 0x8AA6AE32A53E7C07ULL, 0x6988C3FF5E7C6773ULL, 
            0xBA99EC0FDDAB5A0BULL, 0x32E776D8EAD4A700ULL, 0x2647EB7E2D8FE6F4ULL, 0x649767F646A80B88ULL, 
            0x7D6C22CDA2E69998ULL, 0xACCD86E3658F99DCULL, 0x42620BD6EA7D4A95ULL, 0x475ABC714D390B38ULL, 
            0xB20FA0CC8A439076ULL, 0xB40C4A37537CC411ULL, 0x8844FEF88D9931B5ULL, 0xC4451ECCC79F1FAAULL
        },
        {
            0xD0EEDCC75EE9292DULL, 0xA1A76F6C6A163E05ULL, 0x3507289BCDD67C36ULL, 0x37B2E4C48E7DE7F5ULL, 
            0xE3A37148E567BFFFULL, 0x8D631BD004F48D3CULL, 0x8A97DF0B6D82CF7BULL, 0xF77C43554303742FULL, 
            0x3BCCD22E8F9DFDEAULL, 0xB2C935FFFFAB7CF1ULL, 0x771A01825D5E09F7ULL, 0x867B2CF52275CD7EULL, 
            0xA0CAF13129253442ULL, 0x4E649C3EE2335224ULL, 0xCCA1EE8F261E5611ULL, 0x03C8E78C90C15287ULL, 
            0xCEB6B6228B3AC41AULL, 0x2E0C08A133B9A992ULL, 0x23325370E53AEF62ULL, 0x19A396CD52707043ULL, 
            0x0D0C6E77005F95BAULL, 0x572BA5064F053C91ULL, 0x814374B335798783ULL, 0x4310E140A2E5F15DULL, 
            0x3A3DB978E5F648C9ULL, 0xDBBB3AFBDB75E4BAULL, 0x24110E57515FEB96ULL, 0x539B71BC5D2739B8ULL, 
            0xB1186B8C1AAEE7C0ULL, 0x9EF28660FD69CBA8ULL, 0x3BF46D83F4BC709BULL, 0xEA715EAE07D5EA0BULL
        },
        {
            0x216770D66392254DULL, 0x1B577B5EF7BF6067ULL, 0xBA88C8DE8E578379ULL, 0xE1C22F5A0935802CULL, 
            0x9152387548F970D0ULL, 0x4776390F8951B6C2ULL, 0x8EDCD687AAAED265ULL, 0xC9889F2192D931E0ULL, 
            0x7FF67A5B250D96F3ULL, 0xA0522A38385A7853ULL, 0x153B850D3E55F2A8ULL, 0x4B5DCA3AE97F405CULL, 
            0x5009ADD9AE81BCEBULL, 0x0B6878A2392959AAULL, 0x834B8E9E8F1951E3ULL, 0x9B70E051CF18ADE4ULL, 
            0x515815F04402F09FULL, 0xE4A07832F3907964ULL, 0x90D632932F630930ULL, 0xCFF222E3C97231B2ULL, 
            0x272EFE3F56670E25ULL, 0xFD272B98516389CCULL, 0xF67F2A8FCF3BA0A2ULL, 0xBEAF2B191AEE2164ULL, 
            0xEE8CE7F44079E9E6ULL, 0xADEABBB343CEE1A3ULL, 0x3EEBF740456FFB3DULL, 0x2E3F155D97B4E3FBULL, 
            0x50BA160A81C602FDULL, 0xB7665F5811915F39ULL, 0xE890A4566E85BE5AULL, 0x43EC7D5C8C0D01ABULL
        },
        {
            0x47264D2147367716ULL, 0x3BDC557501926B9AULL, 0x6ABE391CBB1CC8B0ULL, 0x5AD25D0D0FE5201FULL, 
            0x19D798B6B582E4B7ULL, 0x58B0E6117282419CULL, 0xCC5D717B4D04903DULL, 0xF531364FCD99809AULL, 
            0x7215845AC733638AULL, 0x781CD9509ED396DDULL, 0x007F850CD1C81AEEULL, 0x4C012E7109F293EDULL, 
            0x132CA292C920D123ULL, 0x9540ED45E771224CULL, 0xAEFA559055426C76ULL, 0xAE4B319B7B8C4855ULL, 
            0x38E2376C8FFA6CE6ULL, 0xA3A7FA38F7D4DEFAULL, 0x82DB9DE93C0A3C86ULL, 0xF131486396ECB880ULL, 
            0xBBB7095E2A91C1BBULL, 0xF7E6ADF48727D9A5ULL, 0x251AADE969EB5CEDULL, 0x125B53F97640666DULL, 
            0x5069BC0A0E745054ULL, 0xCA9FFA19A9EABAF2ULL, 0xA3B2001E421B610FULL, 0xDB945EE7EE3081C2ULL, 
            0x9B408348D74FF5B7ULL, 0x9DF46FB3A98DECABULL, 0xF396B6ACFD7F2DB3ULL, 0x665006E94AD69D13ULL
        },
        {
            0xA102FB02A2D6E2ACULL, 0x60644B00EEF200D8ULL, 0xA9A09630EBDD9426ULL, 0x50AFEA983FDC5EE0ULL, 
            0x083C881B146D1C2CULL, 0xB4D9280813DD2EC1ULL, 0xA2201DA15FF48166ULL, 0xFDB9E532361C0A0FULL, 
            0x0C9F76B606F29A9DULL, 0xA7E60A8E37ABCD28ULL, 0x5F3F28C088A0763FULL, 0xD405D84C2A45B37FULL, 
            0xC4C27AA96E7DB6AAULL, 0x5EF0B7BEDDABE63BULL, 0x333B8CB847B81719ULL, 0xF6309E7F16FD3063ULL, 
            0x94BD4415B0A35704ULL, 0x46BD696C53AE4A7BULL, 0x283D4951B65A7E78ULL, 0x6C12207FAF666323ULL, 
            0x5E0EC6A9384733A3ULL, 0xD9311C5B3C16DB16ULL, 0x80CB06EBE5CB5232ULL, 0x98ED30084738F3A5ULL, 
            0xD8E947D787FE875CULL, 0x0E0DCB66A1B95AEDULL, 0x6819F9591AB51DD7ULL, 0x0F6AC469B58B8363ULL, 
            0x6F0F29FF867AD2EFULL, 0x8619FCF9C63742A8ULL, 0x2FFF29DC271B0357ULL, 0xB6951BDF411DDCCDULL
        }
    },
    {
        {
            0x349E534E74094D37ULL, 0xB89B1915B7997387ULL, 0x4D4FC35C4736DC99ULL, 0xF2BCE860E05F28FEULL, 
            0x5E3AC049A2EEBB44ULL, 0x5CED2F3A57F9EC32ULL, 0xE6C5D696F6FD8271ULL, 0x9D70F9CE5043759BULL, 
            0xBD9BD66E7C2FC41DULL, 0xFA56C16AA6428482ULL, 0xA9553923757438F3ULL, 0x636B20414267289DULL, 
            0x847332344652CFA3ULL, 0xAA1548DABF64EACEULL, 0xEE5A0C514EE3D2B3ULL, 0x28EC1699B59D1F37ULL, 
            0x2AA524CD75D0A097ULL, 0x112152C60016A778ULL, 0x122819C070CFC516ULL, 0x79DA10C039B38F46ULL, 
            0x6EE0DD85CF09DDCCULL, 0xA916BE95436DBFECULL, 0x35D298F2AE92A054ULL, 0x5ED9188165890E59ULL, 
            0xE76FDBA0D0020C45ULL, 0x1C5BA11DF1183721ULL, 0x5CD857369945CAA4ULL, 0xE8C14E1CDD39B69CULL, 
            0x95EDF4A603A1AED6ULL, 0x3787B968E3F52071ULL, 0x93C893EBC4DE251EULL, 0x9CB1FFF7CC10A16FULL
        },
        {
            0x1C837F6C7C5ED4CFULL, 0x49FDAD325D979FBDULL, 0xCC920D004C34527FULL, 0x069EF9263A73E201ULL, 
            0x16E08A876414CF4DULL, 0x507F5C1FCF75E161ULL, 0x9778E4B9F17A1C70ULL, 0x1C290E96973E046DULL, 
            0x4DFB45A540F08054ULL, 0x57B345024F1321FEULL, 0xECED063BB3AA14FDULL, 0x208D904BEECE8A8DULL, 
            0xEF70DF34562571F9ULL, 0x06A26B2D4ECFEA93ULL, 0xF68C3E05270E37BBULL, 0x9036A47B49BEFFF8ULL, 
            0x673CB40F40241A9EULL, 0xE69A944D042EB63DULL, 0x8340FB81441ED91EULL, 0x90746D7B0C4FDF0DULL, 
            0x6F1B491D80F6230EULL, 0xD100EB1B199932CDULL, 0xA3EE5DA82A2F6EA9ULL, 0x88797055695D82BBULL, 
            0x1334D6124EC83B46ULL, 0x1A496BEC3428B5B9ULL, 0x5FBF99E6F0A3A64FULL, 0x81C9C599D788AC6EULL, 
            0xBF8C960ADE41D6DCULL, 0xB6E9D422003B7194ULL, 0xFBE46E96E708C3FAULL, 0x822CFE53C7A5E09DULL
        },
        {
            0x8C103E0D487D8562ULL, 0x1BA20E7C23AD3221ULL, 0xF2A9F1644EBF584DULL, 0xCF45CEA8C87B5D54ULL, 
            0x1B57107094762254ULL, 0x5FFAC7267EDC4DB1ULL, 0xB0ED58BEED5055DCULL, 0x8FA65289B72ECDD6ULL, 
            0xC1D9354A7A5EBA5FULL, 0x58C8B8E75D125A0BULL, 0x77CEA6F480B3DB88ULL, 0x8023ADB1CF763A6DULL, 
            0x4BF18E2D144E14B5ULL, 0x2BDE2B97151A674AULL, 0xAC3DE76928C2E769ULL, 0x5FA4B44CA5DF3E16ULL, 
            0x03D8605726DA2A45ULL, 0x746F9EFEFF3824A1ULL, 0xA45DAE99E2E5288AULL, 0x444C5738F19637E0ULL, 
            0x43B3EF27A5322402ULL, 0x93334B08E4328353ULL, 0xA556DBF9AF68D6AEULL, 0xAD531A3375445626ULL, 
            0x47D54E9AAB21EEB7ULL, 0x9C2E2D724C383CEEULL, 0xAEA45406278A4E76ULL, 0x25DACDDBD6402240ULL, 
            0xCC4EFE73B38907E8ULL, 0xF69803FF32899774ULL, 0x527065CD7BA2F1BFULL, 0x357C14E66B66F604ULL
        },
        {
            0x9906F97BE5EC35BBULL, 0xBB8C6A788DEBA91CULL, 0x528AAA1DC0D7F40CULL, 0x35FBC90042FC5393ULL, 
            0xAD099D980032C37BULL, 0xA9C67988F82CCFDEULL, 0x05A90DE47BDD1289ULL, 0xB6B0305DDE05FC06ULL, 
            0x98266571D32D567EULL, 0x7C59F93F6B04987FULL, 0x5714F52F2DA0FDC0ULL, 0x37C0A1F2F8D663B5ULL, 
            0x926109D303557D8EULL, 0x2CB7A217DD64A47EULL, 0xB0CA64F61FAED0B6ULL, 0x474FEBCB12EA8A56ULL, 
            0x54971BB2700E8DB7ULL, 0x86F1D41C55265B80ULL, 0x04E4AC03EC69EDEFULL, 0x02C86CEFF8B256DBULL, 
            0xAF19F78F71AD1325ULL, 0x7B25AB54427F15EAULL, 0xDBAAE78991BF18C2ULL, 0x336C67201CFF8182ULL, 
            0xCDAD4FCF8EA10092ULL, 0x5583FF1F25D73DE3ULL, 0x97A82F8C2C14385BULL, 0x402421FD6EDC84CEULL, 
            0xD6AA30C36670AC0FULL, 0x468BA68D2D413B42ULL, 0x1E14FDD073091020ULL, 0xF69AC7664A9B9639ULL
        },
        {
            0xDD49E96C4DF4AFE0ULL, 0x14CCFCE5B5B55FC5ULL, 0x43A880571DAA5A37ULL, 0x029B7961A8BB3018ULL, 
            0xA68AE7A616ABD13EULL, 0x072F86FCC9C064F9ULL, 0x2B30810BCDC563E1ULL, 0x72139957EF18C942ULL, 
            0x4F22A866F7D1FD8CULL, 0xBCD341AED1A6F077ULL, 0x18B7CE469655AC73ULL, 0x565773424A4DF393ULL, 
            0xB2B35EC30AEE477FULL, 0x8C17BADF74040CDBULL, 0x16746672489FA0ACULL, 0xCF8E153BF7D26851ULL, 
            0xE5FA8BC4FC07A8F5ULL, 0xDB799EA373AD5791ULL, 0x8ED68DC2B1B846CCULL, 0xCD16FBE8BE393EF2ULL, 
            0x7FB0CEADD0E0926EULL, 0xBE008257C27CFF88ULL, 0x28022D08675CB304ULL, 0x05741BAA3FB1FD08ULL, 
            0x0008DFD0505008C9ULL, 0xB9F923D2DF33127DULL, 0x54E7B2C646000EBEULL, 0xC32253400D311F03ULL, 
            0x84257471BF29411EULL, 0xFEC0EB34A1575253ULL, 0x6373C25E96336DD5ULL, 0x69F61DF1C61BE852ULL
        },
        {
            0x32F2AD5FA1ABCE66ULL, 0xB4DA0B01C7E89D4CULL, 0xA6378879DD06707EULL, 0xC3ED358918357C1FULL, 
            0xF82E3D50CDF2B76DULL, 0x5BE65DCC26E229EDULL, 0x38D22C3831E7D8DEULL, 0x677D726AC1498989ULL, 
            0x405B4E4F2EEC2603ULL, 0x24F7893C69588697ULL, 0x8027FEB10DB6B1BCULL, 0x956C7B06C8027E96ULL, 
            0xBAEFB52546948906ULL, 0xBFE29B7F1E57DB02ULL, 0x36BEE0378D197274ULL, 0x05240533BAE4A21EULL, 
            0xE7390E7FBC2DC242ULL, 0x64E185BF114C4A24ULL, 0x417541D7B028BCF7ULL, 0x1F920146CB7734F4ULL, 
            0x25E1539CB3C32DB7ULL, 0x92C9E4A2D544CBAFULL, 0xF2DB2EE73F3CD92DULL, 0xA3274FB22667D4CAULL, 
            0xD64FAFA025E0A49DULL, 0x102F7BC76B4DF8BEULL, 0x6FC310AF5EE6D7D6ULL, 0xF38D3A688E2A8EC6ULL, 
            0x00EE25EF6742DB13ULL, 0xF74A3DD5BCE502E6ULL, 0x22082C2BDD33551BULL, 0x0CE0409B4AB7D97AULL
        }
    }
};

const TwistDomainConstants TwistExpander_Antares::kPhaseBConstants = {
    0xEA204AA200BB338FULL,
    0xD34A26C4FAFA9DD9ULL,
    0xCC1D4615E8A28E3CULL,
    0xEA204AA200BB338FULL,
    0xD34A26C4FAFA9DD9ULL,
    0xCC1D4615E8A28E3CULL,
    0xE34B6F74D93A9F13ULL,
    0x97A4A1B67AC98C0CULL,
    0x22,
    0x64,
    0xC2,
    0x9F,
    0x8E,
    0xC7,
    0x62,
    0xBE
};

const TwistDomainSaltSet TwistExpander_Antares::kPhaseCSalts = {
    {
        {
            0x224EE31671A10C2CULL, 0xED0C97DFFABC1446ULL, 0x381EFD06219A0D19ULL, 0x60EF81ADB1848872ULL, 
            0x49A8F540ABC63FFDULL, 0xC8A07EB8AC61003EULL, 0x7451A647D45996A0ULL, 0x23C87789D20B21E9ULL, 
            0x7EC2B06D217580C6ULL, 0xABCB8BF9325A3E57ULL, 0xAF7DF396B0750C33ULL, 0x70B16E563CE46E77ULL, 
            0x656B3752CF9F7F33ULL, 0x824D79653EE22161ULL, 0x98FD4F5CBD8509B4ULL, 0x257FCD1A7205010DULL, 
            0x68A7D3DEC24DB91EULL, 0xD0752A7A691A85D5ULL, 0x0B153F291749B5B5ULL, 0xB3AE8748EE5ECBB3ULL, 
            0x18DEE5FD1C8F711AULL, 0x143876086A3B2587ULL, 0x684439FEFB595491ULL, 0x2CDE4304FA1707DCULL, 
            0x0F48057C2264E7CEULL, 0x3629D30CEB8A2372ULL, 0xA5D7B00E39CA1C8AULL, 0xBD275C3BD7FC9EC2ULL, 
            0xAFD71D3D12704AEBULL, 0x89CEAE3D9D2C11C4ULL, 0x1F7A0B2804213755ULL, 0x046709B6593BF959ULL
        },
        {
            0x64FC7CAAD8C99E50ULL, 0x9FED1C2BDDF1919AULL, 0x8619DF48BDF72787ULL, 0x9F1A3D6CF79C3260ULL, 
            0x525643FA057AC35AULL, 0x249933EF8F7904E9ULL, 0x1CC9081115EF422BULL, 0xEB148DF35B660371ULL, 
            0xC7B93867176C5D19ULL, 0x396E3718EF982DB6ULL, 0x5C2393719C069869ULL, 0x3F976336AE506E6AULL, 
            0x327B009B07A7F030ULL, 0x6672ED4FE5A59F5FULL, 0x60E462138D2D0339ULL, 0x22EA008A6064D5BBULL, 
            0x8779CE2CEC90F7D0ULL, 0x519EFA7E4B759E62ULL, 0x58EC76A3D83C9403ULL, 0xF30A5DEFA18AD994ULL, 
            0x3821AE612032CBCEULL, 0x7D7E69F1853A12EAULL, 0x328498BFEDEC2AA6ULL, 0x78B4041EBABD8A7CULL, 
            0x0500303D81D1D351ULL, 0xEDF41EC071B87E97ULL, 0x8D34837888194A55ULL, 0x9DF8AE5E1C9CE980ULL, 
            0xA748CD8B0166D892ULL, 0x6B9A4E505A9DA541ULL, 0x16A04866AD849238ULL, 0xC3F34F54C9ED954FULL
        },
        {
            0x33342620199541D0ULL, 0x1E7FD3C059BB95FBULL, 0x50B8E6700D3069FBULL, 0x73F0B196B5D8754FULL, 
            0xCDB9596C0963711FULL, 0x6E5F1B9D2EFE0444ULL, 0xD505406064793F2EULL, 0xF91AD60219A038FAULL, 
            0x6E242D94173CE013ULL, 0x97294F0146C90C88ULL, 0xD84FC65137554EDDULL, 0xF3706C1A06E31578ULL, 
            0x7D23152871C65FFBULL, 0x7DC72946E3BC9937ULL, 0x0065E794BEE08128ULL, 0xC330F692DEF34C61ULL, 
            0xB9766DB5E4858C8DULL, 0x8F5D91E24960256AULL, 0x33300B2423AA5B65ULL, 0xA242E305169B1B03ULL, 
            0x0AEE6E03E2F37924ULL, 0x1EAC5D61312BA55CULL, 0x35D7F4144398DF23ULL, 0xDD5D05C6B028EE81ULL, 
            0x474D5E8430D5A789ULL, 0xD8E30D09A60767B1ULL, 0x59318747DB43A84CULL, 0xA137693C65D66039ULL, 
            0xCA0BA8DD80F88E27ULL, 0x91634638E3EEBF19ULL, 0xD6628B046C804AE7ULL, 0x52BDF4EB581CEEA9ULL
        },
        {
            0xF5ED192186E6A12EULL, 0xB3A2BC8E9A73D118ULL, 0x554513CF6E4C9534ULL, 0x2910841098AF6936ULL, 
            0x827EFD92F0DF527AULL, 0x322037498F0BE0D2ULL, 0x315000ED64E8197AULL, 0x47833B5F8E341913ULL, 
            0x8DBCF29B52B7D775ULL, 0xE6877F883777765DULL, 0xBF8796D72CBB341AULL, 0xCF1D5D3CEF8BE209ULL, 
            0x62D604642E7723C4ULL, 0x4A2EEBBE43A906D9ULL, 0xFD26F4B230031692ULL, 0x0C04AC354485683DULL, 
            0x17387C71FD2766B4ULL, 0x6CA89806E787829CULL, 0x51286E4B09E8BEFDULL, 0x931A444C869ACEADULL, 
            0x46D60626B0DF4A0CULL, 0x0CF4778CA81C241CULL, 0xF250ED0E4870018FULL, 0x87EB770580FAEFD8ULL, 
            0xDFF52D20631B30BBULL, 0xB94C8332224502DBULL, 0xD73A47AB7B17EE0DULL, 0x87DDC05EDD0ECCF3ULL, 
            0xB1D151E8A5013961ULL, 0xC00EBFBADF5E93A6ULL, 0x9E71C060A9AD43DDULL, 0x009743ECE0434267ULL
        },
        {
            0x01DDCF75BC9F9EAEULL, 0x80EE60E2D597CFF1ULL, 0x99F420261EE13384ULL, 0xA5BA29556AB25295ULL, 
            0x2DAA8EF16CA2B0C8ULL, 0x050B9FC67D86239DULL, 0x8E4230B0ADF71E86ULL, 0xB7AC250DFF7DFE2FULL, 
            0x2F357B7B996852DDULL, 0xC593FE7272DE6FF7ULL, 0x8CDE624A739FBCF6ULL, 0xF92673348EE160E0ULL, 
            0x43DDFC393AB3D952ULL, 0x8582822EED0BA32FULL, 0xBC356C0F43922510ULL, 0xC2BF7D25444BE7E4ULL, 
            0x6F136D630E23F901ULL, 0xBAFE41B991A4EE0BULL, 0xCB35FAEC826E9CF8ULL, 0xB763BC4A230EBC39ULL, 
            0x6E11C1EBE2610587ULL, 0xF540FF7EBD5430E7ULL, 0x2272853593E20017ULL, 0x9744FA565FCBF4BDULL, 
            0x1FCE4C79C4FA6880ULL, 0x31E54E306BADE676ULL, 0xADEC22B754A19F5BULL, 0xB14CFF4A5BD359CCULL, 
            0xD7D94FB499DEBF2CULL, 0x477399CD5A834160ULL, 0x0364FA6B200746EBULL, 0xA7C1B856F3BF8D49ULL
        },
        {
            0xEF5AD27C5EED00C7ULL, 0xFCFCA9F1D743D140ULL, 0x8571135518D76CFEULL, 0xD275EAB6446D2C90ULL, 
            0x8F931BC3AFA0A7F0ULL, 0xBF46891ECE8B2A84ULL, 0x7EB5C8F22DEC5EEDULL, 0xC4167ADE0624E4E3ULL, 
            0x51E0FDEBFD6E9F4FULL, 0xBD4A0F1C0C2056BFULL, 0x150A2289B980F004ULL, 0x78BAD1AE14450674ULL, 
            0x46B3872543083E51ULL, 0xDBFACDE5EA42E67FULL, 0x42EB96FAFD4CDC59ULL, 0xA3BD72CCC155C5FDULL, 
            0x61641A3206B0708CULL, 0xF4F5F1836C35E4ECULL, 0x72453B05B93FC7E0ULL, 0x773496F32257825CULL, 
            0xF56D69BEC711C697ULL, 0x12E8405578C8AE64ULL, 0xF37564942A0F54B5ULL, 0x8C8B8E0B84B644A6ULL, 
            0xB4E907CDB4E83844ULL, 0x6C1822D6258DCDACULL, 0x684A01EC512F1AA4ULL, 0x4396963B5EA6B40FULL, 
            0x3B7504F376A1EFA7ULL, 0xF25516B880C6A302ULL, 0x5AA63F7674BF6DC3ULL, 0xD8352728C12D80A1ULL
        }
    },
    {
        {
            0x1773F39E2EF10329ULL, 0x532AC88A938EB1F5ULL, 0x4924F7EF3BF7C935ULL, 0x294F7291CDD2316CULL, 
            0x8B596DC9B694DC89ULL, 0xD0329CC076F25668ULL, 0x6595123E4E6D9817ULL, 0x57536C84D3F5F12BULL, 
            0x1F6D2471FF5FCFB6ULL, 0xE6213490C60EAB98ULL, 0x8B0EE52067F18E19ULL, 0x267FCA69206FFF05ULL, 
            0x2B35B51F5C168256ULL, 0x5E60AB9F030BF636ULL, 0x7E9944844F49A042ULL, 0xC0E366DB3E15BCD9ULL, 
            0xACFB8BAA7367DB8BULL, 0x65A7CC94C98C2AE4ULL, 0x572375CEA85B67E6ULL, 0x0270C08210006342ULL, 
            0x4812469897C098EDULL, 0x6D5B733DDD2385A6ULL, 0x545FD4FDB8917670ULL, 0x6585E476BB52330EULL, 
            0x2E35A6C37649C831ULL, 0x49EC76931937A9F9ULL, 0xBF54A3348DEAB3BFULL, 0xC91BD3D0E03F344BULL, 
            0x871F848B8BA55895ULL, 0x09C7017CD500F076ULL, 0x503A7BBF9EA1465FULL, 0x672B45D96B437AF1ULL
        },
        {
            0x1DF366873D5FF3D8ULL, 0xBA2CEC7A472DA448ULL, 0x26FFA60C29A453CBULL, 0xB307929024D28555ULL, 
            0xDCDAB83174F3E706ULL, 0x8D0B6AEA57568809ULL, 0x3941CECC8DF028A7ULL, 0x37AFF59B7510C59FULL, 
            0x087114CB3D5ADE1DULL, 0x2CAED877E5B1923AULL, 0x9FA2ECED082A14A9ULL, 0xB49A280A60B5FB57ULL, 
            0x2FCCDC18DC6D4627ULL, 0x53B9BDF1233DB029ULL, 0x16F445CE882173DBULL, 0xAAA9A0FA0F35B9B8ULL, 
            0xB1CE31F7FE08EDC9ULL, 0xD712889D1982DE6DULL, 0x07239FA9A110CE79ULL, 0x055EFBA19E5264CEULL, 
            0x7BFC84CD2D3AD58AULL, 0x81321ADE7758B34CULL, 0x079A43DE0CECC83AULL, 0xAD744FBE6033400EULL, 
            0xF6B3B511AE815702ULL, 0xDABF376ED94442D0ULL, 0xB282AE3C554ABF90ULL, 0x4C7B835F12698E57ULL, 
            0xCACB7BD247929C78ULL, 0x0BE1CADD14E2A639ULL, 0xBA969C24E9D47877ULL, 0xF2E64D44F8FB30CBULL
        },
        {
            0x42A5FEFC8CCCFDA1ULL, 0xADCC8C02812D6FD4ULL, 0x915828AA697A55C2ULL, 0xC66090176EE8C53EULL, 
            0x74F1E2CCEC547118ULL, 0xCD67BD99E7260075ULL, 0x00D80EB071B55035ULL, 0x64595A2119E8DA37ULL, 
            0x0ADE449EDE0DCEA0ULL, 0x947AABDC37588E1DULL, 0x0801A8D2173AAE16ULL, 0xFFB1824A40FBFC1DULL, 
            0xB8EE82AE5248011DULL, 0x767EB72EA4AA95DCULL, 0xCDD55C7D69E86842ULL, 0x7FE690D8B42BDBFEULL, 
            0x8D2FD4ADA0B9F0F0ULL, 0x9285FD6C6744B54DULL, 0x38CC7F57989C660EULL, 0x22D12840CEFAB61DULL, 
            0x93861CCE06884292ULL, 0x92CC37FAE35F9F1CULL, 0x37061175C2E6C34FULL, 0xDB623893E04E173AULL, 
            0x43F2659B07B21E75ULL, 0x6606A26E65DA6DA1ULL, 0x9FB5FE711E4FEB93ULL, 0xBAABA2F0D8315F4FULL, 
            0xC006BD0B7982FBE9ULL, 0x46451D9FDD194B9AULL, 0x7744E7E27A8B94FBULL, 0x00BB15D82320AC20ULL
        },
        {
            0x00A7A77014E5CAC9ULL, 0xE87BB2830172887DULL, 0x7104B2C963C476C3ULL, 0x3D7D0DF3758A01CAULL, 
            0xFEC5197CE9B88D42ULL, 0xDD331B6CCEF4D1E6ULL, 0xF203DD2DE2F34D82ULL, 0x960E17AD3C55C63FULL, 
            0x4592CF4AF7EB328EULL, 0xF684CCA5CAC7835EULL, 0x84283E7B4F23EE09ULL, 0xFCEB6F0870064641ULL, 
            0xD0BFC4A6170DB5D3ULL, 0xF686631F1DC65048ULL, 0xBAA0C3AF80B8E9D2ULL, 0x307A745C4F546B00ULL, 
            0x795373D5B37BB04DULL, 0x0C42DF3C5159EFB0ULL, 0x9BA68B4FE6759A47ULL, 0xFE5395F0061FA567ULL, 
            0xD3537D4C21DFD22DULL, 0x566CC2239B5C047DULL, 0x128CE114F6627AE8ULL, 0x51C092F6C58543D5ULL, 
            0x334F9820463710B1ULL, 0xEFA3023EDEA754B7ULL, 0xBA91AC997914E8D1ULL, 0xC8153532374400A3ULL, 
            0x76850190F5AF8D82ULL, 0xDD745B3AF7616307ULL, 0x304938B4DB54E159ULL, 0x4311E23194D5ED2BULL
        },
        {
            0x16BBF39F80ECABD7ULL, 0x12571DCB60DCB9B3ULL, 0xEA428B656003329DULL, 0x882113A469EA1F47ULL, 
            0x666FE1CB7A1CA45DULL, 0x234EA5E1AFB836D4ULL, 0x91C396B68430D218ULL, 0x45EDBF439D2C4914ULL, 
            0x46D60DC591655A21ULL, 0xA211B40087E043E8ULL, 0xD6E9E7919041BB43ULL, 0x5CDA2BD8F5B40214ULL, 
            0x8A8AF6EB7D7CB209ULL, 0x8BD69DACB384A5F1ULL, 0x73B6ACE11F537FFEULL, 0x48546466C038B1E3ULL, 
            0xD3EB2FC8CE72E3B3ULL, 0x7859C3E672A8F0FCULL, 0x1471778B7C22829AULL, 0x00AE03A585CF41AAULL, 
            0xC7449EBD63F53D5CULL, 0xDD7405E3530096C2ULL, 0x791870DFAB5C9727ULL, 0xF772168E36D07D37ULL, 
            0x2FFB84BE1C688C55ULL, 0xA363F586B07636E0ULL, 0xF5E2C5BC0642CD54ULL, 0x2D0C07C09BD2239AULL, 
            0x2ED3794C672C14AEULL, 0x97C64944386AE512ULL, 0x8A62114F45419650ULL, 0x979621624C969ED0ULL
        },
        {
            0xC89155A55355CFB9ULL, 0x0EB92A4F1E6B95C1ULL, 0xAA2D4E5AF09737ABULL, 0xA0AE97CFA83DA1C1ULL, 
            0x68B1167C677177F2ULL, 0x66789590152F7284ULL, 0x88B87A95F8CA89C4ULL, 0x194206AB3E3BD41DULL, 
            0x6E9E25430F4710C3ULL, 0x58AA6B36DA98E282ULL, 0x7898A4B1ACBFEB7DULL, 0xB624B47E21CD0788ULL, 
            0x38EC6890E39F9276ULL, 0xD27917A8CBB3CB22ULL, 0x979AF81836C3C3F0ULL, 0xAD8A9497292FE067ULL, 
            0xF9DE595CB92E9AAEULL, 0xC2E0DF79409FBD9CULL, 0x4E3AF6A5CDE9FDBFULL, 0xA6925196AA5D70B0ULL, 
            0xF3CB2920DDEF66BBULL, 0x85861439F13B892BULL, 0x2A17AABA6CCF75D2ULL, 0x33DB6FF7E346FAF7ULL, 
            0xD7E72FB0180847B2ULL, 0x7E85BFC6D292C3BAULL, 0x10CAA7242F408B4BULL, 0x133E7587083911E9ULL, 
            0xDC8A41837F913672ULL, 0x0889590112D2A2BFULL, 0x81BC9CA5DEC734E8ULL, 0xBA39F919ACE3D463ULL
        }
    },
    {
        {
            0x0A6749A74ECFD7D3ULL, 0x19C73A9D409C23AFULL, 0xC96C5ED69F86AC4CULL, 0xE24F0A834F967A53ULL, 
            0x2E6720E768693B87ULL, 0x3DB09F0A581001DFULL, 0x0769BEC5B7449879ULL, 0xF30EF05E9C09CC09ULL, 
            0x52D4495516150D91ULL, 0x207FE911EDD90191ULL, 0x4F8C07104CCB34BCULL, 0x08D14BE8042A8CDEULL, 
            0x25CEA7E599066739ULL, 0xE5A2565B4BB1E652ULL, 0x0086985BECD12626ULL, 0xC43FB44AC0AED57DULL, 
            0x04E121F3DF1A444EULL, 0xB2BA3042C35CAB61ULL, 0xCC9565B550271F9CULL, 0x3977D711B824DFD2ULL, 
            0xD1496D941DD2AB5FULL, 0x5B7688516E6E92A0ULL, 0x1A9E0E1B2FEE86FBULL, 0xD54D56F5EA3DE25DULL, 
            0x1066D943E4FCCE4AULL, 0x28D31CDD0AF160C2ULL, 0xE5F8AB886B039BD3ULL, 0x3B7BCEEC7D8A0D00ULL, 
            0x845CD763DB1D26DCULL, 0x562C9CFFD28CCBCDULL, 0x06C42A8176413283ULL, 0xCA680D47487F3CFAULL
        },
        {
            0x08013FE040429319ULL, 0xCE8F6E031BB81ABAULL, 0x90EF24F15515B982ULL, 0xB6014A76D8EB5BFBULL, 
            0xA3C5DC7F1C0720D7ULL, 0x7A981EF536885055ULL, 0x3EA4BC367FE7F99AULL, 0x74D641E41CBAEDBFULL, 
            0x520C6D5638F3CB8FULL, 0x0D781954321BF191ULL, 0x5C534F5B835CF700ULL, 0x6E047906268CD4E9ULL, 
            0x503C1E2F90F300DFULL, 0xEBAF7948613C90F1ULL, 0x5AED390E60C44C28ULL, 0x78566AD03C12D8F9ULL, 
            0x6049BB987A366219ULL, 0xBCFDD1A7359B7A7AULL, 0x41845F062F2AB5E2ULL, 0xD456218CCEDD7844ULL, 
            0xCAD89E3C46D9DCAFULL, 0xABE7AAFEC87A5658ULL, 0x85ED37C18D7DFDFFULL, 0x3B16BBA250F823D6ULL, 
            0x4466E2B23F4A19FCULL, 0xB2B4988981DE53ABULL, 0xB86FE40D9A7D5817ULL, 0x8AB8AA15FCAC3E1EULL, 
            0x3DDB8FD198B6D6E8ULL, 0x1A214D9B573DE318ULL, 0x2EB0FEBA773A537EULL, 0xF39BD09AC59098E0ULL
        },
        {
            0x8F39FF04395B15BFULL, 0x8A3E750AAE6D4D56ULL, 0xCA3FAA39B8DB8C9AULL, 0x2211AC1596F22230ULL, 
            0x46D313B0DC43596AULL, 0x4FF2363C51ABE0ADULL, 0x880D839685F272A7ULL, 0x31CFD7059CF6663EULL, 
            0x0134BB4856BEDAD7ULL, 0x04FD7C88298C4554ULL, 0x903C6476BC691513ULL, 0x9F818E5647FF85D1ULL, 
            0xE858BA2A7E1523D3ULL, 0x2EDA2943D7F3AFD7ULL, 0xAB6D6FA017C95615ULL, 0x57708DC7B90918B6ULL, 
            0xF1B59810C80EFE5EULL, 0x34E9B88FC0AF87A9ULL, 0xC3E10C0374B28E55ULL, 0xFE53AB24AD4F49B4ULL, 
            0xCD0E7CBBF81EE326ULL, 0xC7EC2C08C8974AE3ULL, 0xE6CBCEFB9873E30DULL, 0xC9BA28FE59BF4B40ULL, 
            0xB5AA0976772B855EULL, 0x958A5C4407F4EBD8ULL, 0x9FD38A4BA90F1326ULL, 0xA9BA5381924C0131ULL, 
            0x8A051790299A53AEULL, 0x498C45CA712A4F92ULL, 0xA67447B0AD50B116ULL, 0x3D1EB100FCB1239DULL
        },
        {
            0xA1FF2CBD1D05666AULL, 0x24B88FDB35987396ULL, 0x167D3DC72C4352CBULL, 0xFC5C151F6A0FA49AULL, 
            0x99818BD19CF5E8F7ULL, 0xD1DDA69DF221ACA6ULL, 0x880D6EB724527F2FULL, 0xA1C120ECCE8CCBE4ULL, 
            0x74334E034DCF96DFULL, 0x2A669DA0AAF24A25ULL, 0xE492B54004125CC3ULL, 0x3FC9A5E89E3A1489ULL, 
            0x18171FEBAA7D94DBULL, 0xCF9B65CC04B65B0FULL, 0x91C4A722A4C1A33DULL, 0x7D0E51EDAF483E57ULL, 
            0x2FDE3E2B842911AFULL, 0x7716639712A95E4DULL, 0x6B861E8D9B127B6FULL, 0x5BE6E4BE2C208CFFULL, 
            0x8F12E228C7966F0EULL, 0x47C95AC5622FDA01ULL, 0x061CAA240444C9A9ULL, 0xE2E56DA7B8D61A20ULL, 
            0x84EB292BCBEA97A3ULL, 0x87FAE015B2EEF732ULL, 0xBB7FB365F20BF4DBULL, 0xA092005C283F3309ULL, 
            0xCC98FCFB2703A9F6ULL, 0xFD8B78FC8E914E33ULL, 0xD7E787DDBF94EE29ULL, 0xDABAEDF66F0FD527ULL
        },
        {
            0x9841B65E27EAD64EULL, 0xD41C4983E58D1BC5ULL, 0xB4DDE65FAE46FBACULL, 0xF9A00082D170085DULL, 
            0x2978A1B16EFB1172ULL, 0x8F71176939F482F8ULL, 0x88F53E776AC28313ULL, 0x55A5CDFC255A067CULL, 
            0xC87CC72071FE4F1EULL, 0x2C04B3FCA8BF3987ULL, 0x8BF9C7D2DC0BA566ULL, 0x0AD0813CA2114E50ULL, 
            0x539EFDC8B814D643ULL, 0xB3B1E82AC1C8E96BULL, 0xD7469929DD0DEACFULL, 0xDDBB6E3060B0DA85ULL, 
            0xF5168FF79428D89AULL, 0x5E8E1210A3F6B0B1ULL, 0x5ED2268321658B4DULL, 0x0BC2D4DA819AC2BFULL, 
            0xB54A4AB9BEDB41BBULL, 0xF00013A97FBDE2D4ULL, 0x728D6A05488F86A1ULL, 0x1FC3C4989A87D887ULL, 
            0x23D7EECDF70576BEULL, 0xFCD34019F7C372B5ULL, 0x41366DDDB8333089ULL, 0xD13A5BAF2D218A7DULL, 
            0x4303B725F9D4A6FEULL, 0xBBDA253464C7B18DULL, 0x40A5E0701DA3DC4DULL, 0xDBF847CC58F36D3DULL
        },
        {
            0xCF9991CBA6F71CDCULL, 0xD482D25C03CF9EEAULL, 0x5ADCA6AD6D6B9D44ULL, 0x317F5A7460BE971DULL, 
            0x35E6F9F3A476B49DULL, 0xCDC93C149163DFABULL, 0x69F2A6E6882A2729ULL, 0x85147533157332A4ULL, 
            0xF09B0C7B88BA531EULL, 0xED1EE8A7E30AEEFDULL, 0xC79CB7CC9E026722ULL, 0x67CC51C55925CB1BULL, 
            0xA468E9F96A350DF8ULL, 0xB7D15F6D931375ADULL, 0xD3A3F915CC8B1524ULL, 0x3250E1133611900DULL, 
            0x0A94F9AF06D7D817ULL, 0x7E63A6686D88DA14ULL, 0x90241371ECFCB5C8ULL, 0x23DA0CD89C029B99ULL, 
            0xD4E3F1A749CC10B8ULL, 0x2AFBD50A54A33BE4ULL, 0xFA5B7EB076847994ULL, 0x0001879D0BCD5FCAULL, 
            0x493AD055E5C6DDB1ULL, 0x369914A260B0BC89ULL, 0xFC4EDA7B615BBFA1ULL, 0x5739C53F2B8511F1ULL, 
            0x67D032F413A265E9ULL, 0x769FFD686DB0184BULL, 0x4D8460E32C3829A5ULL, 0x42FB279D891469D8ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Antares::kPhaseCConstants = {
    0xA865D956C3EF48CEULL,
    0x51849B333249A1CAULL,
    0xEC7CA17F2B87D20DULL,
    0xA865D956C3EF48CEULL,
    0x51849B333249A1CAULL,
    0xEC7CA17F2B87D20DULL,
    0x87FAA5986628CAB9ULL,
    0x96C919D53D29BF9FULL,
    0x48,
    0x7E,
    0xD0,
    0x83,
    0x51,
    0x7C,
    0x3A,
    0xDF
};

const TwistDomainSaltSet TwistExpander_Antares::kPhaseDSalts = {
    {
        {
            0x6AA436CD13CA5C0AULL, 0xAF749A0BCB1C55BBULL, 0x58F8C925475023F2ULL, 0x1D2BCD30FA202FB7ULL, 
            0x0790D8BFC03A48C5ULL, 0x16D755FA82843EBEULL, 0x5F0533497CDC4B44ULL, 0xB368CAFA3E8E353AULL, 
            0x258707F2EFC3434EULL, 0xEF5C3D21478EE869ULL, 0x0CEE9749F076278CULL, 0x29497C1592E4AB30ULL, 
            0x350A2883C834DFDEULL, 0xE97419BD105B5039ULL, 0xB95B30DCCDA97EBAULL, 0xC3DB0EBD250D1A4AULL, 
            0x0D47505C8ADAEF50ULL, 0x44C20A280272786BULL, 0xF79272B8FB15DC14ULL, 0xF92CD9D68395F5BEULL, 
            0x089CC68C8739F293ULL, 0xD9534AEFEF313D43ULL, 0x06E8C7C106F1C7FCULL, 0x21C46FE70083623AULL, 
            0x1380C215F65A4407ULL, 0xB3A2DBF08A3BE0B3ULL, 0xDE7E3C2277019016ULL, 0x4797CC1C4FDB6937ULL, 
            0xB21DFBFC7F1BFBE7ULL, 0xE23EC3BF9C1C68E7ULL, 0xE1E63554FF16374FULL, 0xD69654B18C6A714FULL
        },
        {
            0x3F458FEBC65EFA74ULL, 0xE9C45263CD08C25EULL, 0x35761963BC9316B5ULL, 0x8265A18C0B0F06C9ULL, 
            0x52E870DF6A2F977DULL, 0x662A308758945AE7ULL, 0x8839DA8858C6C8CCULL, 0xCBB97E28CD36D7AFULL, 
            0x61486A68FC6F781DULL, 0x30810C3562F29C57ULL, 0x5D88BF2CC172153FULL, 0xB93079BDAC3FB385ULL, 
            0xF53BCF6DA1468340ULL, 0x0E668DCA565568EFULL, 0xC3310C6E705C3E54ULL, 0xA40FF6435724B115ULL, 
            0x47F80187804DB737ULL, 0xBE5D23CCC9641472ULL, 0xB7649AA0CB59A491ULL, 0x6023A488ECE08740ULL, 
            0x1CA89E20829DCA42ULL, 0x5458F01A04C7ABC3ULL, 0x69369A33C090637DULL, 0x2D840B3F592AD6A5ULL, 
            0xB2CD366406B897C3ULL, 0x1F1DAE8F4A19CE16ULL, 0x94C59A6D9B210B0AULL, 0x07B099F48291F89FULL, 
            0xE8126ECEF8B19454ULL, 0x1928453C6832A18EULL, 0x05E1661C2352F5AEULL, 0x9F7095EE89D2496EULL
        },
        {
            0x14BA96EBB2781F00ULL, 0xB8BFA74C326C9412ULL, 0x88A7D4F746813C55ULL, 0x5147686DE4E0C5DBULL, 
            0x8F1A4E4E97BED0A5ULL, 0xB8EB8CFB740DD553ULL, 0x8E71D3EE16E769E0ULL, 0x6EB3646A93E3D11DULL, 
            0xA42E98B25282C0C3ULL, 0x525AF6421A86E6FFULL, 0x1BA838B1BDF28687ULL, 0x9BFA170340093598ULL, 
            0xC80A1E36C843B555ULL, 0x38C0C8CD083E3DA8ULL, 0x9ABDBDE2403A91B4ULL, 0x56C6FCDE1D2C7050ULL, 
            0xB7E1E955EEB383E0ULL, 0xEE1EE332E6877813ULL, 0x90794CDBCD42713CULL, 0x0A5488FD62654526ULL, 
            0x622CE47A7E2F62D8ULL, 0x8C095D9E96C08821ULL, 0xA0C50A3A067FAB21ULL, 0x4F3BFCD14230ED14ULL, 
            0xF31137377DB2DBEAULL, 0x2F661FC6D5CC7A2CULL, 0x795B5F6A3C200606ULL, 0x4FC86D4899DBC1C3ULL, 
            0x7B500B4CAA31CB0BULL, 0x990D2F418D642D10ULL, 0x20F4F51B4FC8ABD2ULL, 0x3F0011765F7E6945ULL
        },
        {
            0xC2BE8D11CF42D87BULL, 0x3F3F454CE0FCF141ULL, 0x84D212CA2FD00B0FULL, 0xEF37572E49A2A3D7ULL, 
            0xFC335215FE4A6319ULL, 0xB48540A11F807A63ULL, 0xA24289B414DE52D6ULL, 0xFBBB4F3D9E62A560ULL, 
            0xD3013AEEF5EEB4CAULL, 0xAD682940FE0B5F1FULL, 0x47CA868043DA1619ULL, 0x5B842A2A64970615ULL, 
            0x192532659B4DCB7FULL, 0xAC0EFAD6382A0286ULL, 0xCB8F0D5474C97F76ULL, 0xE97B9D54E90A591FULL, 
            0x12D9B2CCDA1733BFULL, 0x4AD97FEC5C7AC9CBULL, 0x7D7EBFB5E88E36BDULL, 0x474907A0CD4BA8E2ULL, 
            0x0AD9BD1EC0937633ULL, 0x612F39CB03AA2921ULL, 0xB0992F35EF6F4913ULL, 0x2479E44A79A369ACULL, 
            0x42DDA0E87134647EULL, 0x6CF772814BAEF600ULL, 0x54DFD8B24816D217ULL, 0x4387924B67F4E1A3ULL, 
            0x47F75003AD79D8BCULL, 0x366A08DB29B56868ULL, 0x997E4CD2419939F1ULL, 0x632E096F4282D6DAULL
        },
        {
            0x2BEAB9D4A4A7379DULL, 0x8ACAC732241DA6B2ULL, 0x244273E9BD50440EULL, 0x4F23CD42412603B6ULL, 
            0x7A28B6E7CB5DF86FULL, 0xFCE83263A1222600ULL, 0x166030BFF7C6573DULL, 0x1027AF7F23D2E339ULL, 
            0x846654808C720E16ULL, 0x86F490D2811D6126ULL, 0x59D40DFEB8ED81EFULL, 0x63D16252B9649F46ULL, 
            0x86CA5622F8585D84ULL, 0x035713FBE75EE98FULL, 0xD9EA97F4E8C48FF4ULL, 0xFF4C7CCFB6F7E9F2ULL, 
            0x6AA6D7E1BA5F7236ULL, 0x42D475B39BC1BC26ULL, 0xA3B6C118367EC876ULL, 0x926943CD35DD6F13ULL, 
            0xF7EF98B8CFA52A8EULL, 0x94F30C08984F7BFBULL, 0x40AA218B82F78A66ULL, 0xF1A679E219E90D96ULL, 
            0x954677534A072AD1ULL, 0x40860C664BF7943BULL, 0xE413DFD485820B46ULL, 0xEE255BBEB29BABF0ULL, 
            0x2357A9F2C7205A56ULL, 0xDB7D038D899B3DE2ULL, 0x014653E816FF9899ULL, 0x6607D16BD11D964AULL
        },
        {
            0x15D2DEB4D0B10C57ULL, 0xE44A3DE09EDC254BULL, 0x04D41CEF07FFCAB0ULL, 0xF60A6C2D4B84EF54ULL, 
            0x3DFE32CE9C5F8EE7ULL, 0x84DAE9015540F4EAULL, 0x8641DB72FF16D748ULL, 0xD1586D8BB32005ECULL, 
            0xF8CAAD8FF4B6206BULL, 0xF62A4DC63A7F82AAULL, 0xAE5141FC9E9ED192ULL, 0x569A684815410D2BULL, 
            0x437FC1B1AFB00C1DULL, 0xE895728492608593ULL, 0x325B39B5E9995D6AULL, 0xFCBA7AF7DC9990B0ULL, 
            0xF1941CCF742712C6ULL, 0x9510FB70B84C5FD2ULL, 0xD452C7F9E5071EEEULL, 0x39A081C153E93974ULL, 
            0x537448B6157C852BULL, 0x6E571A5BE5113415ULL, 0xB0D5DDCAFC9421B2ULL, 0xD8D2F0C3A18020A1ULL, 
            0xA2422B0E78D4C386ULL, 0x6ACCAEA5302C4BE5ULL, 0xD0F8B5848F779A05ULL, 0xA8E31E44ED64F1BAULL, 
            0x4484DB42525197EAULL, 0xDA3D50FA202D447DULL, 0x94A829C0BFBF2507ULL, 0xB228EE7706ED7A0DULL
        }
    },
    {
        {
            0x6EEC7C469454502EULL, 0x3BA6D0063462550DULL, 0x29CD9C3FFAE312DCULL, 0xA5144CD6C2739FF0ULL, 
            0x6441322F05F31111ULL, 0x9967D754CE35178DULL, 0x9D8E203363E45864ULL, 0xD5C348EF4D349D21ULL, 
            0x5E678D88A6BAFEB2ULL, 0xD91FD0BC276E07D3ULL, 0xCDCF0DF6DC577783ULL, 0xC3624113CBA108B9ULL, 
            0xEEA33D50F9382721ULL, 0x44E352049DEA1FF7ULL, 0xB11BB7E01EF2058CULL, 0xF704963BACC55152ULL, 
            0x3619AC75B083E1A7ULL, 0x8E1A36E0F0C24C91ULL, 0xA446AB49D60FC7D6ULL, 0xB81B6FCAD5DDECDDULL, 
            0x1E491C65D7DCE901ULL, 0x0767729ECA57F3B3ULL, 0x3B8397BE0A76AE64ULL, 0x898C7A9C4BAE3653ULL, 
            0x52C0B5560F257AE2ULL, 0xE59E9CD436641772ULL, 0x6E169A1E6C288E13ULL, 0x461B6F8EC8C7FD6AULL, 
            0xD11031D0103DE8F7ULL, 0x2FBAA696E3526E68ULL, 0x9FFBD0F6E561DFDEULL, 0x0A29A4BFB844B41BULL
        },
        {
            0x0D423CC99F23BA00ULL, 0x1DE2F7FC1EDA37B5ULL, 0x0E27EF62612D4886ULL, 0xE216DCDF365CA6B1ULL, 
            0xC4B486FA642789DAULL, 0x4DA5D61EED7AAB80ULL, 0xBEC011CE155BB377ULL, 0xB6F6C4BC9B373169ULL, 
            0x6D197D79F85C09AFULL, 0x27885CCAF291107FULL, 0xD5A71CED2859C0E5ULL, 0x718068946B85E723ULL, 
            0x939D71945542C0C3ULL, 0xDA9F9167DEA5CFF3ULL, 0xA99FCC40101A8F9BULL, 0xF0AA9F56735243B8ULL, 
            0x97348B3D91B7B0D9ULL, 0x160008D8176E2EF9ULL, 0x7BA26DFA0F14150BULL, 0xE74C0A5C10915AABULL, 
            0xBF945FF7FDB26C58ULL, 0xA7A178C6213F70A9ULL, 0x41B05517FC81ADC7ULL, 0xAE29B68E8A3F745FULL, 
            0x2E78BCC90924C9FFULL, 0x3373E08F048C0A5BULL, 0x324F77638BA3915DULL, 0x2C64DEB03BDEEF86ULL, 
            0xC1A5F9039CD03882ULL, 0x92A31CD130335067ULL, 0xC46978AD235CE35AULL, 0xDA80DB3F53339661ULL
        },
        {
            0xA7542008195B8B0CULL, 0xA0FC8A68520D54FBULL, 0xB3211A45FD0FDC07ULL, 0x23291086D951F6B0ULL, 
            0x0F58A822DCF6B28DULL, 0x8823BD8582671867ULL, 0x37F079C044BAF262ULL, 0xDB5D2044DD83F168ULL, 
            0xE8956317AEA82409ULL, 0x85EDDBCE43E581CDULL, 0x0E13CE0EF35DE01AULL, 0x5F1B7FDCC446D917ULL, 
            0x8515DADD62512FA1ULL, 0xF4321172359B3552ULL, 0x7A254C1640B02696ULL, 0xB554544F0634E3B5ULL, 
            0x89881B1C2F2F0CEDULL, 0x51863AB9DA4D008DULL, 0xC0FF72047A5679EBULL, 0x0660960B6281DAD0ULL, 
            0xA5C235C99D3448ADULL, 0x6335B9646D67D1B3ULL, 0x65314DFC960257F3ULL, 0x4C7222060FB3EBE7ULL, 
            0x75DEBB7B0A00D879ULL, 0x8C8A0426D0BE1EF8ULL, 0x50FC10C12613D336ULL, 0xECB6E90AF3C82084ULL, 
            0x5A940B28C5F07CEBULL, 0xD6E8A5E4B713C5C1ULL, 0xF2BA040FE4224ACAULL, 0x5384A6EF5BEBB873ULL
        },
        {
            0xEEC3DE5A44D80126ULL, 0xFCBB6C1B60692B2EULL, 0x7B6EFA789071259BULL, 0x9F066005459AC25CULL, 
            0x566E2C0C7E318763ULL, 0xD8D283FB11EB77A0ULL, 0x8AD5583164766434ULL, 0x91D15B1A5E7A9271ULL, 
            0x0FE393304E82DD69ULL, 0x59F5D49E3720C191ULL, 0x81C65B9AE4C00656ULL, 0xADFF65A30878D6C8ULL, 
            0xB9830D72331C7487ULL, 0x1C71344806B055D5ULL, 0x066AAA3068525A4BULL, 0x72A9B1CB30E5DE8BULL, 
            0xAB4CD94561C3D0B6ULL, 0x5AAC09A2972D1BCEULL, 0xBB49C91609AF06EEULL, 0x5D36C803D1C59A60ULL, 
            0xE02C9BB6DB07514AULL, 0x1D3B79249C92C5F5ULL, 0x3274BD4AD78C82E7ULL, 0x70BDAE98FE5A6ACFULL, 
            0x812FEC5CF4E7FD57ULL, 0x55B82D27DA5247D5ULL, 0xDAF24C41E7DA1AB5ULL, 0x6D965B720F75159DULL, 
            0xF58387C881AEBB50ULL, 0x989B9BD6F463DD5AULL, 0x7E7570680CE0F4B0ULL, 0x1F680D6F4ABD0D7CULL
        },
        {
            0xFDEC7D423AD1CF6BULL, 0x3D34D872962919C4ULL, 0xD6FC5CD7CD0A8AB1ULL, 0xDC731FE4939ECA9FULL, 
            0xCE2121AFDD4D4583ULL, 0x4C6AB5DFBD386F1FULL, 0xC2636865CAEFCF62ULL, 0x19BF4D067727FB39ULL, 
            0x21997BE24264F534ULL, 0xDFE023CEC452EB09ULL, 0x3593753B189094F2ULL, 0x7A86557144670E5CULL, 
            0x05C4FC0F9AE954CBULL, 0xD5447502C8AC0427ULL, 0x15B41E746ED560C4ULL, 0x6CF968BD92EBCBA9ULL, 
            0xFC53506A9D82C073ULL, 0x976D28C36445C111ULL, 0xB9D7E11E6E279C9EULL, 0x91B1D6DE19BF5C46ULL, 
            0x49ABA0963B658115ULL, 0x07C05D984B606DCDULL, 0x9A2BC3088B33EFF8ULL, 0xA428866D866A4CF2ULL, 
            0xC451669670B7019BULL, 0xF3A1FFA0904B31A5ULL, 0x6B483CDDF3DCB25CULL, 0xFE92E9352D971F90ULL, 
            0x397DB6B11630F7E0ULL, 0x812695F4E5C89AFAULL, 0x3846A42D45E7C2C7ULL, 0x8E6DC81D9093BD4CULL
        },
        {
            0x152351437BC64088ULL, 0x54111387E476BC5DULL, 0x0A01574CDB0487AFULL, 0x871F90ABE9F59FA5ULL, 
            0x3F5E5E3BDC815AD4ULL, 0x19A8D9B266A19130ULL, 0x5F86DB4F55F3A972ULL, 0x369D1C70359CCD93ULL, 
            0x5F72DB3D3CE05143ULL, 0x3F1BCE73B9C69807ULL, 0x8DF0B86909CBA798ULL, 0x0DC2E518CF84C9F7ULL, 
            0xF9A4CB51FE5FDB7FULL, 0xF03BB1CDC9548C10ULL, 0x6DB3B091ED13DC9AULL, 0x3F42C877C1413716ULL, 
            0x5D70F83EB4D2DE6CULL, 0xF74F64550EB12A7EULL, 0x2A7870ECDFAFB9CFULL, 0xC333B4DF366BB26CULL, 
            0x8A16EF9D0546DB4BULL, 0x55586C8074C0755DULL, 0xD0F2E08A5199917DULL, 0xA7503EA949A070A9ULL, 
            0xB145131BFDF6EF1CULL, 0x9929C63E89C346B0ULL, 0x40972E532E6CBF7AULL, 0xD05FC0ABD19D4B65ULL, 
            0x46CE8D76C60BFCBAULL, 0x6808522AD585E2CAULL, 0x374053860B8629B3ULL, 0x0784CD7FD3946F27ULL
        }
    },
    {
        {
            0x036EDFF1C328450EULL, 0x8570D2F4667BEA1FULL, 0x0CFAAC52CEC8A686ULL, 0x30E0A2968E6A8F1CULL, 
            0x8761567C37AE57E4ULL, 0xB29357EBD0032BC8ULL, 0x46121BB0E7C891A6ULL, 0xE34D7308741759D8ULL, 
            0xBBC769862C4310A7ULL, 0xFB6BDF6BB3E473ABULL, 0x3214364C1A9CA5E5ULL, 0xF3F694CE9EE27E51ULL, 
            0x34621B487ABD7B2BULL, 0x90DFE873A7D0744AULL, 0x712B81CCB2D72AB4ULL, 0xC86A3099EE65DFD3ULL, 
            0x2F7C4C7418934088ULL, 0x0A3D08DABBA8924AULL, 0x38B8B60701A46D1DULL, 0xF0B52ADB0328D9F0ULL, 
            0xEC6F7BE47E1216D3ULL, 0xA569A99CF969DE38ULL, 0x3F5AE4D50D2597FEULL, 0x0E7EBE90D54D59D2ULL, 
            0x59D5EBE3B1251EC9ULL, 0x00C1563CD4D543BEULL, 0x62B2734DDE72A535ULL, 0xD17A5B395CD87FC2ULL, 
            0xE9875FBBF67F13DBULL, 0x90A2B24136154DDCULL, 0xC848A1FE82C5AECDULL, 0x7196FB30CA4093B5ULL
        },
        {
            0x7C9A11E28C5E7480ULL, 0x18469BD740D60AA6ULL, 0x6BD8FBD00824ECB5ULL, 0x8ECCF571B72A3B11ULL, 
            0x6028D2C25D87C4BBULL, 0x42877ED24A60C33DULL, 0x4924BD8B24B0F841ULL, 0x0A32F4C032C310BDULL, 
            0x5A7C3583390D03C0ULL, 0xFEB74CA167A32EBCULL, 0xD15F3D20F35FC2E2ULL, 0x00F382B4F360F925ULL, 
            0x98E77A95E21A0045ULL, 0x811F2B2861AC7D66ULL, 0x189496B63316D2B0ULL, 0x616CBEA5A2C2EF7DULL, 
            0x05FA466952271B72ULL, 0x61ECFD0069937DEDULL, 0x67365F6F1BD6B8AFULL, 0x584C85256C50FDACULL, 
            0x44569E7F7C92A17EULL, 0xC5E7C2DBCB864FF8ULL, 0x3B7D991B472F04B9ULL, 0xD4A4FCE0687920E6ULL, 
            0x474DFE998D175B63ULL, 0xB65A4CB0AFD8206DULL, 0xC46C21C35FB8B5C2ULL, 0x178B0DC25D1C523AULL, 
            0x0987CEC9990B8EBBULL, 0xC64E6C3B5FA53722ULL, 0xB9FDEBF92A647C15ULL, 0xBF89ADCFA680AA71ULL
        },
        {
            0x22C70C6FE26AF1AAULL, 0x665BB38E2B14BAACULL, 0x6766EC918C45A3A3ULL, 0xD06A6EE00050FF1AULL, 
            0x8C27DDD590E81340ULL, 0x4A0541093BDE51C2ULL, 0x428F19578D3E4211ULL, 0x7EE9F2CEB8251827ULL, 
            0x76D2C8A1B74C41E3ULL, 0x8413ACB393858AA6ULL, 0x45CB5B0DB3425936ULL, 0xE2AA066EEDFE9651ULL, 
            0x69D9D5B71D1A506FULL, 0xDDDC7FCC7B2B51B8ULL, 0x94924244043E8BBBULL, 0x0AB554AFE0CC40CFULL, 
            0xB2FA3D8699CFE2C8ULL, 0x801A9A027DB41D92ULL, 0x6F1FB9512084B166ULL, 0xB83B4017638AA0ACULL, 
            0xF8F6DBFAF4313B95ULL, 0x4A4524A660D3A0D5ULL, 0x463A0C8D93C1D7D2ULL, 0xF1A765228452ACE3ULL, 
            0xC964CD082E60DE7FULL, 0xBB0AD329CA1678F5ULL, 0x89A0501029CAA57DULL, 0xB8CBF1BF8DBCAED2ULL, 
            0xF2EC94ACE69E3D0CULL, 0xFB345994E6978D34ULL, 0x9411315A3A78BC8AULL, 0xE6AD9B52427E36A5ULL
        },
        {
            0x70E393F856F98FDDULL, 0x715F58FB71FAE0D7ULL, 0x6E9740B4A946E8EAULL, 0xAEA09D784259535FULL, 
            0x4566B3A27E7924EEULL, 0x62F5E677A13C390BULL, 0xFBA8B27C861F4F14ULL, 0x51224B97C76484A8ULL, 
            0x36982855EAB2413DULL, 0x11FBBEF520E8E85FULL, 0x336E49FCDE8FB833ULL, 0x59155E0DA10C4C5CULL, 
            0xB580942861B02F8BULL, 0x221E50D39A7AEC06ULL, 0x4AE7B34D8B79BD85ULL, 0x1C339A3A0D9E749BULL, 
            0x28F20D9EEC58F749ULL, 0x17855FA84201AEA3ULL, 0xD95DFD9C6FD83C47ULL, 0x022F9DBDC2BB8E70ULL, 
            0xD871912F295854DFULL, 0xF136F3B71EA220F5ULL, 0x44503E6780968538ULL, 0x2575572DE92DABE6ULL, 
            0x5EC6AD6ACEE2464CULL, 0xE9FDA3C4117A0591ULL, 0xA9ED433AF029363FULL, 0x4C9C5F87680EDAD1ULL, 
            0xE7459D294D432A2AULL, 0x84A6F769B232F2AFULL, 0x223A56157979DD83ULL, 0x59190CE56E1A01C5ULL
        },
        {
            0x6153B7325C4D4BB7ULL, 0x5AEDBF5C0E3CEC5CULL, 0x32B6E985BC51416AULL, 0xD012058780D64A23ULL, 
            0xC2897EB3499D8836ULL, 0x9814FA24474555A6ULL, 0xC5AE4A23B9BB358BULL, 0x6C4FC2F76CFD5982ULL, 
            0x5A3D6E4DE0E903D6ULL, 0xBB9F731322399E9FULL, 0x13D2B88B5E0E4713ULL, 0x5BE5682025038DDFULL, 
            0xC9C8145C08F940DAULL, 0x7CA5C0CF43DFD8C0ULL, 0x00334A2E09288D6BULL, 0xC036AEDF9E6173F4ULL, 
            0x5F06416888B51DE4ULL, 0x6B69F3EC60A8F67DULL, 0x74BC45DC24BA8B0BULL, 0x66DC98DCDC0E871FULL, 
            0x9D97ADF21E70E944ULL, 0xD4C9DF51864DFAF9ULL, 0x63E19F35804C1A6AULL, 0xF911C7285E23B3FEULL, 
            0x4F94CD427608A953ULL, 0xCED2D453CA3614EBULL, 0x360AC4CAC258EBA9ULL, 0x5D9D3EC2D86CD7A2ULL, 
            0x7482C5A88FE6737DULL, 0x30DA9AB87718E69EULL, 0x8F1FC2D559570107ULL, 0x99937660DEE0D479ULL
        },
        {
            0x17725B380FE1D4BEULL, 0x199EBFA2B6C69659ULL, 0xCDABABF6590626E2ULL, 0x2765E4B4165E0756ULL, 
            0x32D9EED2F3C94220ULL, 0x6FBAD98C4231092EULL, 0xDE2B4DBCD6117B72ULL, 0x24CE1FC57F5A55C5ULL, 
            0xB44505BB49A0915CULL, 0x91AC168A49298565ULL, 0x9084EB4AD772D966ULL, 0x75E1CAC62DF6A7FCULL, 
            0x88A10DE461707F4AULL, 0xD64F9C54720D7BA0ULL, 0xF05BEA5F30783E26ULL, 0x844A55197513F95DULL, 
            0x3F5DC9423517FF2EULL, 0xC3EDC9DF9C973069ULL, 0xC1DE90A4C2D8BBB5ULL, 0xCC9DBD206E952678ULL, 
            0x8E930CB776D74A82ULL, 0xB0A19FBB41A95C8AULL, 0xAA930A16AC86F08AULL, 0x3A39FE97F631FA10ULL, 
            0xB9A713E98A47FCF5ULL, 0xA8ADCB96D9DB3F21ULL, 0x9C36B45FAA55FE4EULL, 0x1CF0C0F70150CD93ULL, 
            0xA42179DB2F9494A5ULL, 0xA4874BFEB6BB3192ULL, 0x7ED09E1E18517923ULL, 0x511C7C56C8B01C13ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Antares::kPhaseDConstants = {
    0x33BA8E05EEC77E23ULL,
    0xDA1DDDB6BDFA5523ULL,
    0xD598C90ED68DA2FCULL,
    0x33BA8E05EEC77E23ULL,
    0xDA1DDDB6BDFA5523ULL,
    0xD598C90ED68DA2FCULL,
    0x2E192166A14E9E6BULL,
    0xD76455343C7EED91ULL,
    0x79,
    0x8F,
    0x6A,
    0xD2,
    0xAE,
    0x3C,
    0x7D,
    0x87
};

const TwistDomainSaltSet TwistExpander_Antares::kPhaseESalts = {
    {
        {
            0x9EB5CE6286A60298ULL, 0x1A6035CFA770F6EAULL, 0xF58BD01D49C4BA9AULL, 0xCB22C8C6C30477FFULL, 
            0xA5C90997C3F66287ULL, 0x45738F1E067C2899ULL, 0xFE88E803BFD2E623ULL, 0xCF78445226904686ULL, 
            0xD76F2A0036445B89ULL, 0x5F5A6C876A67B2A2ULL, 0x7637CBD5447E10F7ULL, 0x5E24B7B7C636F9DAULL, 
            0x723A7221FFED0620ULL, 0xBB090E511E6053DCULL, 0x79E1204B690D5C2DULL, 0x130707ABA595D4F0ULL, 
            0x830E7EC97EFAC1A0ULL, 0xB3AB0825C1F8F939ULL, 0xB246AD44E5BE1E43ULL, 0x176C9B812703F5D1ULL, 
            0xF3326B7029B9F03DULL, 0xA30A9D2F6DDB5AF6ULL, 0x24096276AE438756ULL, 0x049CC4580F5208ECULL, 
            0xE95BFF7F524761C5ULL, 0x5E769D045C2A72ABULL, 0x27F40F44B96A0C19ULL, 0xFB00FA7DF87F5BB7ULL, 
            0xF7450E332D67D87FULL, 0x89C14B6B7949BB70ULL, 0x561F5FE8CC260C82ULL, 0x124C943CEE0CF129ULL
        },
        {
            0x5F778C77AC029433ULL, 0x1A26EAF7D7EE06ECULL, 0x0EB00E5F54672738ULL, 0x352DF1870F2C6BCEULL, 
            0xDD2113FCF3FC6E45ULL, 0xBF156764EA9656C2ULL, 0xEE8DB0F488E2AF5FULL, 0xED24BAEF82D0A0F2ULL, 
            0xA0770BD1232EEE2BULL, 0x4319919BCD6901C2ULL, 0x843C7B92AA83A998ULL, 0xC83DAF8D3E67E6E3ULL, 
            0x17F2FF7755C35BC4ULL, 0x47848515B25002ADULL, 0xC748559AC1544C8AULL, 0xD5D888F246C99EB4ULL, 
            0x9D69C3C1428B19B5ULL, 0x26B75C8817162020ULL, 0x2B53BD939C590602ULL, 0x06FBFBD6A81593DAULL, 
            0xBB84E7884D389358ULL, 0x7C54217293D677D7ULL, 0xA2459D24C5771F87ULL, 0x98CA3147242ECDA4ULL, 
            0x339B703DFA411FCDULL, 0xDD8AFCE89A0FD480ULL, 0xEB398062C48AF2FFULL, 0x00B6A2ADD406361CULL, 
            0xC289071A3F96F4D1ULL, 0xA584B591FD5914FBULL, 0x5C2B1B87342FDA62ULL, 0x1308DFFDBD3D37DAULL
        },
        {
            0x348B4F7DEA317AF4ULL, 0x54C149CB106DB21BULL, 0xDD5D31C85459AEC7ULL, 0x764DC67E5433AFCFULL, 
            0xDCCA3EB13DB70E44ULL, 0x0B8F88C822AA6167ULL, 0x219BB0B049657045ULL, 0xB4644BE28F7EDDFCULL, 
            0xF50D4C597C2FA6DCULL, 0x375448A054B3A06CULL, 0x60FD5D1F7697004EULL, 0xB40112263764BFD8ULL, 
            0x082C7DA390CE4C75ULL, 0x331D3D30E266DAD8ULL, 0x47F6D72B71BC557AULL, 0xF80FDD31D1217E35ULL, 
            0x0118DDD03FFDD99EULL, 0xEF725038CA3C5D10ULL, 0x3583AB00D7D23997ULL, 0x2B938D563FC21454ULL, 
            0x8F9170F77E137911ULL, 0xCF6F7E97DD5895DFULL, 0xF2E6ACA3C691DDB4ULL, 0x0246C22291F3EC75ULL, 
            0x90031EB466EE861CULL, 0xE817BE765A214867ULL, 0x6739ED48027E1264ULL, 0x9F867E439244F061ULL, 
            0x2040484580C89F7CULL, 0x9F2BD336B6BAC1BEULL, 0x72BCDD116F8A7F7CULL, 0xF4DF167BF404DEB2ULL
        },
        {
            0x684DCAB8A16A4E34ULL, 0x34F7459B3A6A4107ULL, 0xA3DC824C9BC9A41FULL, 0x0E10543ED5993E33ULL, 
            0xDCA1F94B5F1113D1ULL, 0x639AD1D5E666E9F3ULL, 0xFE04E237E8E956CCULL, 0x8D9888CFC264D051ULL, 
            0x7B1AE6C643E787DBULL, 0x6837848044C29A09ULL, 0x479667667D51E308ULL, 0x942A62F7BC9F33A4ULL, 
            0x430C39169B06AF03ULL, 0x402FFC31C56E3B4CULL, 0x7D569AE1600ACB61ULL, 0x5D0BF4C9A24C01AAULL, 
            0x918EE851FAB4525AULL, 0xE12626B234682545ULL, 0x26A43E2722E344CEULL, 0xA5D31C1178901599ULL, 
            0x87D2CA033837D072ULL, 0xA47D9F68A8F1963BULL, 0xB73B0FF34D478E05ULL, 0xEE853021FBFA7546ULL, 
            0x8B153A0390463BBEULL, 0x361D1035509BFECBULL, 0xB0729B153DDE9073ULL, 0xBA39A7F999645A9CULL, 
            0xBA70DB8E579EADB3ULL, 0x5E353127E13D756DULL, 0x549BF0F7FD3C4FD0ULL, 0x83F82C762CCA0BC5ULL
        },
        {
            0xE154216DD0AEC1D4ULL, 0x3FF07B8C265E61ABULL, 0x454BA0A6A19BF770ULL, 0x4A230378883F08BAULL, 
            0x811F5CB80D132C7AULL, 0x07DF2437804A8443ULL, 0x04F5AFE27FACD2EBULL, 0x675A15BB6AC682DDULL, 
            0x846571115B747875ULL, 0x161261A5B85C46D5ULL, 0x1B526AED1CFBDB11ULL, 0x91E37C8E3A843ECCULL, 
            0x52B72FFFD4CCA3EFULL, 0x38A64397E58153F8ULL, 0xF89220C25CD34BE3ULL, 0x93D4DD925BCBC20FULL, 
            0x796D098FD3D789C6ULL, 0x206AB73290C35182ULL, 0x29A665910803715BULL, 0x91CF190E4CF2C110ULL, 
            0xE11A1F356089FA83ULL, 0x5A4579DD25BBB19CULL, 0x592BCC8428F4CFE1ULL, 0xD20DD5A3ECA70CF1ULL, 
            0x0B4B04CDE69A3F94ULL, 0xB16318A9EDAA8827ULL, 0xD8A04DAD9211F406ULL, 0x49E5AE2FD818B0B2ULL, 
            0x2D65237381142F8FULL, 0x03DE6523873EC111ULL, 0x8BC319B39295621DULL, 0x2F094255811964A1ULL
        },
        {
            0xEE8789693911D25BULL, 0xDD4435BC830C0ABBULL, 0xD7A12571DFF2C555ULL, 0xC3AFCCB07FE9130BULL, 
            0xACA8DA99CB4BA005ULL, 0x6144330616CFC5E0ULL, 0x85559BEC11269E23ULL, 0x70B31729FF2EA595ULL, 
            0x30C32A4A3D30CC77ULL, 0xD1DE2F9BD3C8CF8CULL, 0x0A2B6ABF9F42CBA3ULL, 0xA4CF927428FF5CD1ULL, 
            0x6804B0F50277CDB3ULL, 0x247F23AFF2ECB595ULL, 0x559E3EECC40E2230ULL, 0x20C7CDF39DB530BAULL, 
            0x88254C741E42A309ULL, 0x9EE95ACC3AF0B73CULL, 0xBFBEC30AA89C809DULL, 0xDDF7D1BBA54E12BAULL, 
            0xF8E7B92504BB3122ULL, 0x4B553438C179DCCEULL, 0x7C53493F625ED9ADULL, 0x0730E9DB04F6FE96ULL, 
            0x1AAFD96F652BE044ULL, 0x429549C749A65307ULL, 0xA04CDAC2023A0B6BULL, 0x0C1E7725A115E8EFULL, 
            0x881F914D01FBBEC0ULL, 0xD2D18F4E22D6FE75ULL, 0xC6F1BF788DC318A7ULL, 0x40D7B75713F8C802ULL
        }
    },
    {
        {
            0xC030C58FC28F2FA5ULL, 0xF7A2A36ACE72AB8DULL, 0x726839FF26D7618FULL, 0x352ADF3A64486F66ULL, 
            0xDDEC3234D2108EF3ULL, 0x156E0A697C84A83BULL, 0xEA9A7BA07AC119BDULL, 0xF5C3B114E9A751CCULL, 
            0xBF7FA64C699E64AAULL, 0x9F03D4049F2E4E43ULL, 0xE73B9E88F5E142BFULL, 0xAAD9CCC5A91624D4ULL, 
            0x56CFC9B97F8BB3F6ULL, 0xD18F1FEBC2A61FD9ULL, 0x58E29689C1E5B1FBULL, 0x8DB3861B8D090D08ULL, 
            0xAB983FDFADBFC6D4ULL, 0xF04208523C2D48E8ULL, 0x997727F5FFDA2D9CULL, 0x65D3CA7273EB671DULL, 
            0x5879AC83DADE29D7ULL, 0x6B61AA6937281AF0ULL, 0x854E25A2911CE97FULL, 0x5DBBCFD8D00DB315ULL, 
            0x243A61DEDA45E9EAULL, 0x312B9CAF1E3B925FULL, 0x49E0A1451EF33B4CULL, 0xDDCABA4101D8E18EULL, 
            0x3248B8141DB96EAEULL, 0xE688B7BF8D80369AULL, 0xD9C48F11911C2013ULL, 0x9972AD764A44B20DULL
        },
        {
            0xCD74D85160F466A7ULL, 0x417EC940B6BAAC0CULL, 0x55BC0BDE247A6BF2ULL, 0xBE08ABE01ADA777CULL, 
            0xEBD34A4D59D11E84ULL, 0x4B88614A1145E231ULL, 0xC3BEE17825C66129ULL, 0xFD29F3EB045A53B1ULL, 
            0x96796387C5E17391ULL, 0x6AAE99549D1A33FDULL, 0xA29D0D026CE73AE8ULL, 0xF22A6D6540C7577EULL, 
            0x4D0AC614088C13B5ULL, 0x811CB1B2733179A9ULL, 0xC17AA6A6E9DF00BBULL, 0x44E6E6F5527C63FBULL, 
            0xD0FF875127F9372EULL, 0xFEC44AFED4DEC32FULL, 0xB1F2EF4E7F2AF092ULL, 0x3155259D253D9B4AULL, 
            0x6AD58BDFA767AFE9ULL, 0x344490216FD5AF63ULL, 0x104B644A92C6A003ULL, 0xDBFE2DEF1A0E1C33ULL, 
            0x199B0FA6FE536DEFULL, 0x73125DFFEF2D1B6AULL, 0x389527B663035DEFULL, 0x0756607761707E50ULL, 
            0x3259A626FEF0AAD9ULL, 0x9C1452A5D532C71EULL, 0xAB73967D1D1DE5D7ULL, 0xA173D640D83C9D27ULL
        },
        {
            0x71BB2CFE8B88C898ULL, 0xD8400B32700C30D9ULL, 0x8A37BD6D6731BE2DULL, 0xDD9D79D80209EE79ULL, 
            0x57B30664D80075CFULL, 0xE9CEADDDF8E27913ULL, 0x1D389F310D351F11ULL, 0x6881267C031C46DEULL, 
            0x34466602D90EC6ECULL, 0x13F6CF6FFA01819FULL, 0xFB3FC8E72BD64551ULL, 0xC79DF1346E3EFFE4ULL, 
            0x4BEBC5D7DB58BEFDULL, 0x7DCEA05F9CAD3A8DULL, 0x8DD8EBA4E82B4C97ULL, 0x4C9789F33FC1788DULL, 
            0xF8DFC8BD745635A3ULL, 0xFD74B24795684352ULL, 0x2B16BF295DDBC664ULL, 0xCC150AEEF6796644ULL, 
            0x537F2E8AFB8B8AC6ULL, 0xA5AF4995A6CD0835ULL, 0x6509AF219C057B6EULL, 0x4AD33A59AA657965ULL, 
            0x7C1C4A313BBBAA8DULL, 0x8FD33996D7B0C62AULL, 0x393F3B289EC7C13FULL, 0x4F7C4D1E840DE10FULL, 
            0x25B7F6AA93DCA7A5ULL, 0xE2013F33A3B111C4ULL, 0x91B89BE7208DD9A9ULL, 0x662F8749F8732CFAULL
        },
        {
            0x5CCC843A146764CBULL, 0x0F94163308708D08ULL, 0x072010672E8B1A9AULL, 0x94CC2F89F7B01870ULL, 
            0x1A1C13205C779981ULL, 0x1C1C5A41F1C715EBULL, 0x1FE0C53463F81946ULL, 0x13BD8649FE3DCAB3ULL, 
            0x51A91F902C91887BULL, 0x1566952CFD87B374ULL, 0x9502EF44116DF1B0ULL, 0x09BCADFC2EC4738CULL, 
            0xD61FBA63D717B535ULL, 0x2BA24C8E6ECCF96AULL, 0x83A9CA25537F4882ULL, 0x998595139D1101F0ULL, 
            0x8D4B7B94D2EB4FCDULL, 0x12B8A3B3083B0A22ULL, 0x5A9BC9A92123F9B4ULL, 0x16AAF7CB90C6A89DULL, 
            0x3CD19FBE2CE61B47ULL, 0xCBC509DA3736783AULL, 0x04944F44E35CCD71ULL, 0x4E34939C22FD205DULL, 
            0xD93B6AEDE3F0FF41ULL, 0xCB0F020B5FA6C989ULL, 0x7EF372414C54DA01ULL, 0x83E0088DB95B5C04ULL, 
            0x10447C42C709A1F3ULL, 0xD371C43B55BC261FULL, 0x9D1911D82A35D132ULL, 0xE0C6F47569F5C4F6ULL
        },
        {
            0xA08B046974268507ULL, 0x182CAEB6CB7516D1ULL, 0x87506D254DBAFBA8ULL, 0xF31C998D1F86F20FULL, 
            0x34253CE02D819E46ULL, 0x0875590FE94B2061ULL, 0x7B498AA959764415ULL, 0x217865A9E9C5D6FBULL, 
            0x4C7A9CEBFA420FF2ULL, 0x088A482D9DF510D0ULL, 0x8E97461642251E3BULL, 0xA9E003356E15809DULL, 
            0x6E4F2AE31713FB9DULL, 0xB361A30D89609E19ULL, 0xF4EBBBF997CD6128ULL, 0xC7CE5C2216D5065FULL, 
            0xB3731715870CABF1ULL, 0x0E1481BB20EC2BD5ULL, 0xDC57D5B6E638B4F0ULL, 0x17EBAAA2DBBF8FEBULL, 
            0x9AF176BDA6F1BB9CULL, 0x92E0403BE77786A6ULL, 0xDFDFB33FC878BA52ULL, 0x4CACB68CA81C44F3ULL, 
            0xD3A387C19F50795EULL, 0x6E3303595FAA2801ULL, 0xB489780A6BDF86D9ULL, 0x99CC0273EF57BF21ULL, 
            0x8532E7AF58490411ULL, 0x5C757643D66D9FE0ULL, 0x6C06E45435DE55A1ULL, 0x43B9C9786EE21C2AULL
        },
        {
            0xFCB6A46D99FD2D01ULL, 0x16B0B8F5147EED3CULL, 0x105AE3588B4ACBB9ULL, 0x5BBCFF0DC5A9B54AULL, 
            0xB698A21B9F38AAE6ULL, 0xD75558DA42B15115ULL, 0x2BD208B45AB45DD7ULL, 0x4A832426603C7315ULL, 
            0xDC0210CEC87A9249ULL, 0x7041824FF9FD9596ULL, 0xD596523424E19615ULL, 0x7D1F39ADD5281545ULL, 
            0x755C07B2114D1FF6ULL, 0xC56D8E0E75712A50ULL, 0xB15B33E1DB22C00FULL, 0x70EFDABA17E2C810ULL, 
            0xC1124A308E042DE2ULL, 0x02DC9D10064151EDULL, 0xFF11BFCD61D2DCA6ULL, 0xF9BF747804DBFECAULL, 
            0x32F50917FBE266AEULL, 0xAA4E36FCD8EF5735ULL, 0xB9D0498C9036955BULL, 0x345EFAB6C69B42C4ULL, 
            0x7C2BC20C95FC4CAEULL, 0xFC922A292A5EAB7FULL, 0x0E0FCF9BDAB1CC1CULL, 0xE2C5BD8786D49F49ULL, 
            0xACC5437FED3140FDULL, 0x0900C21F3D489FB0ULL, 0x59A688D7876E5F8DULL, 0x2AA8E29BE2F323D1ULL
        }
    },
    {
        {
            0xA95EF2ED38F29904ULL, 0xAC9C87407FB5B7D8ULL, 0x8E48744625C5681CULL, 0xFA73343A736EE837ULL, 
            0xE8937BF17280FF0AULL, 0x32B33721CAC2EC3EULL, 0x147E141AFC4B9503ULL, 0x3778DAF02260FC11ULL, 
            0xB9D64A8B9E444AA7ULL, 0xCF62DEF99932FDF6ULL, 0xED6AC62BD87DC18FULL, 0xB8FC4981387A1AF4ULL, 
            0xB7075980D3B22A4DULL, 0xCFBEF3DC02225ADAULL, 0x6701AD820903A6B8ULL, 0xD93F40DFC6CB7EF2ULL, 
            0x8EC7088FED6A1678ULL, 0xC6CAB1EBFD8697E1ULL, 0x6BAC383A273A4B46ULL, 0x9CD757468AD492F3ULL, 
            0x598C6F9C811D69FCULL, 0x4450E1C4F60B5532ULL, 0xCBCC27E646D7B444ULL, 0x09797AD34731AAD6ULL, 
            0x7E67B27F74C3FE8DULL, 0x6B3BA020E8D392BBULL, 0xFF17C5CC01399DFEULL, 0x42AE0102CC8B69CBULL, 
            0x544BDB6CEFCE641CULL, 0xA7D02263D2666951ULL, 0x6DA10636310292ABULL, 0xA822A2FA194E2CC8ULL
        },
        {
            0x49F88DD535CFC13FULL, 0x4C4AB4EE65A191AAULL, 0x2F962DF91ACE07ACULL, 0xAD6A3A7A2AA41673ULL, 
            0x73B116C8DAF7AD4FULL, 0x81A5FB65E0792BDEULL, 0x6699BC8F5C9141CEULL, 0xEA004BF2C60014CFULL, 
            0xF1E58C198FBCC412ULL, 0x6828DA3865EF6602ULL, 0x9EABAFE1A355C999ULL, 0x76D90F2A150943D4ULL, 
            0x2F91FF53DCEB3F26ULL, 0xD4DCCD519FE938B6ULL, 0xC274BCB7F1724317ULL, 0x1916DAA7634B8595ULL, 
            0x90939E51816A6117ULL, 0x7C878736C160B7E4ULL, 0xA6293FFCE391FB60ULL, 0xFC7B8E457665F570ULL, 
            0x2FF7E1F62E9EC11EULL, 0xA7C2440DC4325B1AULL, 0xF40EEE4EE8CED0A7ULL, 0x5790FA3C3AF2D157ULL, 
            0xE4DFFB81E4DE02E4ULL, 0x0BD90DF34F910214ULL, 0x0A0508387E1F1610ULL, 0x51CA98F2EAF78A05ULL, 
            0x5FACEA7AE2DA52AFULL, 0x3B6FD37689914C4EULL, 0x2CA0B6F59A44B8BBULL, 0x2A1321ACB2D59C95ULL
        },
        {
            0x5DDF7915D0E07912ULL, 0x41B956533302CCA1ULL, 0xA33796AE04DAE72DULL, 0xED8933A790C56146ULL, 
            0x9ED8BDF6C9CE6EEFULL, 0x514D40115B38D9D0ULL, 0xBC7E933E9C22F7BCULL, 0x0DFAC40A60869456ULL, 
            0x6B9A0667C2951C29ULL, 0x335BA760F994791FULL, 0x7D9E983281A70747ULL, 0x9B3811DC7DE2397FULL, 
            0x4CFE3E0CB408B326ULL, 0x19D3199B89FC49A7ULL, 0xBEDBEB98EE6AF9BAULL, 0x4705B5699BC856EEULL, 
            0xF8DD6957275FDEC0ULL, 0x711BF603873E3119ULL, 0x778FD016D04559B1ULL, 0x406C52CEBEC1D15EULL, 
            0xCE0A4B53832ED444ULL, 0xD0BE297FD1AE7749ULL, 0xF96F3241BE1B7410ULL, 0x0FC907685B79B152ULL, 
            0xACD98FCEEBACE217ULL, 0x198FFE140EFE801EULL, 0xB1404338022BAE90ULL, 0xDC171F6F9C573B04ULL, 
            0xE4A7F6B420A00561ULL, 0xF926781899963612ULL, 0x25BAC0D02B5F0F4AULL, 0x862787CD34E70B49ULL
        },
        {
            0xAA0731DB601094FDULL, 0x6EA0249E0E8DD713ULL, 0xF9399DAC0EF6A622ULL, 0x73274A42AFD9285BULL, 
            0xFE900CE60DE8F906ULL, 0x39A53A193FDBAB0CULL, 0x6B4BC662099DEB82ULL, 0x70E22BD6046DF4D3ULL, 
            0x956BAC566D3E81A7ULL, 0x4BB302B5E0990DA4ULL, 0x92B0C0F3668026B5ULL, 0xFA76433A626CCF7EULL, 
            0x633F3C9075E5D63DULL, 0xBDEFAB7F239B16B7ULL, 0x9FBF3A7103A166D4ULL, 0xCE608214B65469EBULL, 
            0xA0D33CCC7BF8565BULL, 0xFC6B235E70A667D5ULL, 0x91AB8663553F4EBAULL, 0xFDDDF7A2B08ECBCDULL, 
            0x3D7B79E404F971AFULL, 0xBA302242F933EBF7ULL, 0xDC779DEBA391668EULL, 0x64502CBD9EBC3606ULL, 
            0x5822F65E2D47BE0EULL, 0x073D35DC71A78BF3ULL, 0x8D3979B1A981EF03ULL, 0x7C2280748FD22A12ULL, 
            0x7BAF373F8B1B8BB8ULL, 0xBBD2B11A833B90C3ULL, 0x268F4B8D605E3207ULL, 0x2F06FB25022093E6ULL
        },
        {
            0x774ADF638308B3C4ULL, 0x17C7B9A6582E062CULL, 0xB237163AABD90BAFULL, 0x6AC93903865AEA39ULL, 
            0x5D73C46D80034DB6ULL, 0x67F58681895B31D3ULL, 0x4479C1BC1E181AC6ULL, 0x51815102CDA1BED9ULL, 
            0x3CABA89CD2F4C946ULL, 0xAFAB7DE8B9AA7CA3ULL, 0x1A0A3EEF49CD517BULL, 0x9C3D95F9571E35FAULL, 
            0xB2D3266F227978EEULL, 0xF94296515C08DB8EULL, 0x3322B26366876DC0ULL, 0x970F0F6D42D261C0ULL, 
            0x7DD1C34D1FA0F58FULL, 0x49F69CAC26749E8DULL, 0x037E5B518704C9C5ULL, 0x76A24DF66243FF75ULL, 
            0x540D2487C0872843ULL, 0x0CDA05EC1B0ABCB5ULL, 0x5F12CABF5B444C33ULL, 0xF0A5347BC9094188ULL, 
            0x42A22B1ABECE959CULL, 0xC83AD2A1565C24BDULL, 0xC1A9F6B9B01BAF95ULL, 0x8D5FC9C5291471B9ULL, 
            0xC0DE361E7D318397ULL, 0x21364FEB19590A98ULL, 0x60DD309D27467613ULL, 0xFD882BD76DD99187ULL
        },
        {
            0xF7BC2196B05BAE3FULL, 0xB48236DE14FF7445ULL, 0x5E65FEC099E22363ULL, 0xE53AC89B6F7D79A5ULL, 
            0x401B20D2BCBB5628ULL, 0x901568D234395ADCULL, 0xCE1BA973142F865BULL, 0x29A7BC0E5CA22ED2ULL, 
            0x3A479077A8F9CD15ULL, 0x2BDF6F840AC17C59ULL, 0x8F2C9C5CC8B03B54ULL, 0xF55D8774C75ECB9CULL, 
            0xB64C7EDE179F34B2ULL, 0x42CBCBB3DFEEE707ULL, 0x08596942C72D5398ULL, 0x706EA735F69C4006ULL, 
            0x71188521207B01BFULL, 0xA2CD18C6889CB7F4ULL, 0x1B97237471EF08F8ULL, 0xF56095AE3B07CC3CULL, 
            0x774285DF9A34C580ULL, 0x93EC7D6311FCB2C8ULL, 0x6E2481429C505177ULL, 0x04F25F15B8BD60B4ULL, 
            0x201BD52099E5B046ULL, 0x6D0C96C0151CA49CULL, 0xE656E4D3AB5693ABULL, 0xAE5371AE90698919ULL, 
            0x356FA3AFF0F0F6CDULL, 0x284871B95EFFF7F7ULL, 0x542EB510B9C8B7DCULL, 0xC5B7791D37B02756ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Antares::kPhaseEConstants = {
    0x086824320E584027ULL,
    0x583629477218D9AFULL,
    0xC40C701F7640AD34ULL,
    0x086824320E584027ULL,
    0x583629477218D9AFULL,
    0xC40C701F7640AD34ULL,
    0x81432C0333650A1BULL,
    0xC20A3D8EC86B05E3ULL,
    0x2A,
    0xB4,
    0xED,
    0x2B,
    0x3E,
    0xB4,
    0xB6,
    0xF9
};

const TwistDomainSaltSet TwistExpander_Antares::kPhaseFSalts = {
    {
        {
            0xB1BDEE25C0566A96ULL, 0x28ADD77415FD5549ULL, 0x7C6BADC177740407ULL, 0xE1418BBD8B7ADF1FULL, 
            0x9BCF32B635DBF66EULL, 0x99EADDDAC5CA8D60ULL, 0xF66B5F91EC999942ULL, 0xD13085B77DB762FAULL, 
            0x91B7D905DF5200CEULL, 0x74667E721E5467EBULL, 0xEBBC2E5A0AF8A487ULL, 0xFFC32E3D312192D3ULL, 
            0x3DFD3BB0EC6B8D0DULL, 0xCB3BBA774E23D539ULL, 0x5E60BFF9F28DE732ULL, 0x1190B96500247BA4ULL, 
            0x1BEF80A3F6711762ULL, 0x724862271C61A336ULL, 0x725C279A0104C9E1ULL, 0xCC890E8AE6DFD363ULL, 
            0xB1D179379B60E20AULL, 0xF1D10B394647986BULL, 0xEB0DB89FBB5F6C1DULL, 0xCCD4CE7043E3D93CULL, 
            0xFCA2F22D788CA740ULL, 0xBA674BF01FF39679ULL, 0x8D7852630CC74FEFULL, 0x77CB18B7FE2C87A8ULL, 
            0x5D7BF88999E8CFEAULL, 0x0868DB5406BF6D09ULL, 0xC6E687252F7B730FULL, 0x43A0B691CE898E0CULL
        },
        {
            0x2DFE6F66B4655E71ULL, 0x0EA44E6C8C6C0627ULL, 0x073A9C84AC2EE59CULL, 0x3A2E03CCEE635F55ULL, 
            0x3E7D194B3D16C6F4ULL, 0x170618AC6E656990ULL, 0x6C05D23957DB501EULL, 0x192B0112FDA82B89ULL, 
            0x309E9FF3A57040E7ULL, 0x4C9EFD19282F0658ULL, 0xD61F1F6AEA85BA2EULL, 0xEECADBE93FA104FDULL, 
            0xFFFB96698946F8EBULL, 0x675475A94FE8115EULL, 0xC1CCF747C8BAF024ULL, 0x851C1BC39A08EF57ULL, 
            0x1BB221E8BE7BF224ULL, 0x28FA23576D5988C2ULL, 0x4E87ED7C14E7BD0AULL, 0x376057F9DF63B2CFULL, 
            0xB98977FAC2894C81ULL, 0x9250E5367A3A5A80ULL, 0x2658CEF71C5D6D15ULL, 0xEF26643FCBC23103ULL, 
            0x3B75C2641757487BULL, 0x576408ABCA7771D4ULL, 0xEA7EAB529C0D742FULL, 0x0B1CD756CD8C53B3ULL, 
            0x9B079C460B302357ULL, 0x1BF44FD15CE36A6EULL, 0xCF6EF8C97C551852ULL, 0xF025724F58A3C3C4ULL
        },
        {
            0x909486A2074BCB7AULL, 0x31EE73C38A47CCB2ULL, 0x8265FFE7E682AACCULL, 0xDD0E55B62FB69F0AULL, 
            0x578CC693B44228BAULL, 0x8B79E9E8D0FE0EDBULL, 0x3F96E60B5BD8EA10ULL, 0x8CF68D8879D4F592ULL, 
            0x6E6632D3F2E409B3ULL, 0xBCC2349B7F567EA5ULL, 0x2E0938E6C6596C7CULL, 0x3461977B5AB4BCDDULL, 
            0x2191DE68CF82202DULL, 0x9EBB3B93F6ACC95DULL, 0x8DDCA825C063FCC4ULL, 0x324D7E6615D0ABDFULL, 
            0x615475C3931E7FCAULL, 0x3AEA6C218AA7D20DULL, 0xF6CF166D963CEF9CULL, 0x937B8D9D2BF535BAULL, 
            0xA55C682B437B6574ULL, 0x6CF2927E263E864DULL, 0xA6D5BD80F653A6A0ULL, 0x078DAB1604D85840ULL, 
            0x3D372FB0E884DD71ULL, 0x3C7CA4A6DB2816DCULL, 0x2C0EB5997D58B850ULL, 0x222EF4FF19BDC2F5ULL, 
            0x31E635160613B779ULL, 0x620F99D95EEA4C89ULL, 0xD2B3F740BF263D44ULL, 0x73A79A9B3FDABDA5ULL
        },
        {
            0xD52AFA55DB2AD462ULL, 0x3F1E61FBEFBD8E11ULL, 0x7EC67F6022F8D0FFULL, 0x016F591973EE8185ULL, 
            0xA84F21E699CA297CULL, 0x6BECE6DDDFB2022AULL, 0x0BE14CCFF547E3EBULL, 0x87FBF58237783A9DULL, 
            0x6A944BFD28EE53F2ULL, 0xC3BC8F6A74C22F16ULL, 0x98070EE089B5D2DBULL, 0x6728DB063781DF40ULL, 
            0x312ABB8052DF7D88ULL, 0xDF3216E9095BCF68ULL, 0x76518AB7A117243AULL, 0x4518D411942C4CCBULL, 
            0x5AE6229309A9953AULL, 0x5E4F89B52DB67AC1ULL, 0x15D78DB366E4091BULL, 0x2EAD03B869643A24ULL, 
            0x5B4E4D3095679470ULL, 0x46AE5D4426B0407FULL, 0x26F96CCC65C4A964ULL, 0x89638E18D4513189ULL, 
            0x785B318DCE5153AAULL, 0xFA07548976141BE1ULL, 0xDBE0C16583BE6973ULL, 0xEAB1A3D8411CD5E1ULL, 
            0x09640243E8842658ULL, 0xDBDE9A225225CD17ULL, 0xEEAD34CFE3C67430ULL, 0xA4DE33D6BDFE6214ULL
        },
        {
            0x145DB3AB77F6F164ULL, 0xA4D191357CB1D8F1ULL, 0x6B20FC9CCF87A463ULL, 0x0B03E1A9C931C8BFULL, 
            0x49BCA66C4952DFB1ULL, 0x3C132EED5B0FF642ULL, 0xAC9231C8F289F7A0ULL, 0x186B9B39D2368675ULL, 
            0x59FDD957608F5929ULL, 0xF9FBFAE4041A7543ULL, 0xF9A3B03300939CE2ULL, 0xC19B5CCB489C9D15ULL, 
            0xC5092DF5DB531E89ULL, 0x2DDADBF8A5E55F87ULL, 0x7D9D411543FFB1ACULL, 0x2B96D8EDF9175AA3ULL, 
            0x6F4F2F77CFE6231AULL, 0x3AB6313DE4A2ECC3ULL, 0xD7964085DAF502ABULL, 0x995FBEF62CDAA162ULL, 
            0xB828B2B609677A7CULL, 0xDAEBEDA34C4F5C12ULL, 0x7E524A635AEE292CULL, 0x4F81CBB430025143ULL, 
            0xA4D72F82C06CBC98ULL, 0xEA43E03BB8B50833ULL, 0xED5C208275FDC638ULL, 0xCAB3BE70B06DC01EULL, 
            0x54C1E8071967C0C6ULL, 0x46EE75D196827E65ULL, 0x36016FC097EF0A2DULL, 0xF0A931AB462BD2F6ULL
        },
        {
            0x48C5D5959CC6A3E1ULL, 0x87D03DE88DB2AC14ULL, 0xA41FD1DD7EF3CA23ULL, 0x6B7A20C3BAFAFDD6ULL, 
            0xD07A71F48A6A3A3EULL, 0xDA4FD7064962121CULL, 0x7F2E19EEDB4D9569ULL, 0x712914E337A15C3BULL, 
            0x1EE0670554885BB5ULL, 0xBE44CD4F917C8E66ULL, 0x8A72F461C6EC2B98ULL, 0x8EB8704415E8AAD7ULL, 
            0x6CBDDFF7525BEA9BULL, 0xA4613C254E971A2DULL, 0xD53A4CA2EEA2B128ULL, 0x211ED3E1817FC335ULL, 
            0xF28AE0DE8D24FB2AULL, 0xAF497B694ACD8E2BULL, 0x7EEFB4CED9E644FCULL, 0x25515BD43CFA34BAULL, 
            0x7D309BF934BF272EULL, 0x1960D375E1EF67A9ULL, 0x06400804AAE11DF7ULL, 0xA678A837C08E29EFULL, 
            0x5E19BB6A1612DBE2ULL, 0x422499A588BC5755ULL, 0xF72EFA2249D596B8ULL, 0xE4E86FCEE9689405ULL, 
            0x26E18A669552532EULL, 0x1CA3736D4ECD7AD3ULL, 0x4E06F4E5A9A9B6D3ULL, 0x63F910E08090BBF1ULL
        }
    },
    {
        {
            0x8FAAD7462343C806ULL, 0x27B176248B8E5C7DULL, 0x4CAB68A45AF932E4ULL, 0xAD3B3581AAA60530ULL, 
            0x7B42301229A812C6ULL, 0x1A7996FE084F53EDULL, 0x370FC753B6F100F0ULL, 0x793ED9CD814A58DBULL, 
            0x91C5D75F377B21A0ULL, 0x5160FF28D590A72EULL, 0x8F02F26DF864146BULL, 0x95BA184EE63E0D3EULL, 
            0x1104559695F73DABULL, 0x8A9968AC32351EDEULL, 0x31DDBCE8F009A8E3ULL, 0x3B434115D9DA50A6ULL, 
            0x1D25DC5288E1E7F3ULL, 0x56BB5C1C9E0AFD90ULL, 0x10C10C9DE1B04DAAULL, 0xE8B6E365F8477F8AULL, 
            0x29965BBA82A47E8FULL, 0x4096C78168050097ULL, 0xB374A9D487963DC5ULL, 0x496F2A696CA25BECULL, 
            0x9E3C553BAA0769E0ULL, 0xA78FB5D4E0E92F27ULL, 0xD1D8A4A6768504F7ULL, 0xD0FAC7AD278EA441ULL, 
            0x558FBA2E369DF8B4ULL, 0x3759D7D58DFA4A57ULL, 0x5DEFDADA5D59CB81ULL, 0xF0596E3E8D0DB4C3ULL
        },
        {
            0x0893B58C76B15968ULL, 0xECD753F3BB875283ULL, 0xB229C5A4BD931645ULL, 0x6AB146B01D95BBB7ULL, 
            0x3AF33BE8C0C8906BULL, 0xB9E15118F877F824ULL, 0xF041A864D370BBC8ULL, 0x3FFADE8E09C684F2ULL, 
            0xBD7F88EE586D0C45ULL, 0xCED383AFBE4F68E3ULL, 0x932D6C0BFAAC1148ULL, 0x97EDB7317FA33C50ULL, 
            0x4CCC26AC981CDC31ULL, 0x6756C9F7E609D828ULL, 0xECA860320ECDBDFFULL, 0x4E8AE3B4437DE135ULL, 
            0x639B55D8A0CF52A2ULL, 0x141A0E1D514DB98DULL, 0x978482D144F9FFDDULL, 0xFA20DF10C150598CULL, 
            0xFFD4BB58F451DC89ULL, 0x51BC088F07A06120ULL, 0x2276AB20B0C0BE5FULL, 0xE399ED31511547CFULL, 
            0x2714FBEFC8CE633BULL, 0x193E568F41EF3194ULL, 0x788D1ABAB0E09013ULL, 0x298E498A320E5964ULL, 
            0x83D6DAF9847E7378ULL, 0xCB9A0F618B000CACULL, 0x687440F5228DD689ULL, 0x0A19522BE7595CB6ULL
        },
        {
            0x20DC5DFF3C5E7F0BULL, 0xCB4F2261D66F4156ULL, 0xA9986B7FD3D2FB39ULL, 0x344C204E6490AF93ULL, 
            0x2C8545DC2117D2D2ULL, 0xDE5F0071EF59DF3BULL, 0xA4B5A794C6238C82ULL, 0xA9F08876762C79F0ULL, 
            0x8C1E611ECD6944F2ULL, 0x3AAA35F7BBAD7064ULL, 0x0C899EE9F2BB96ABULL, 0x54B9903BD27C377FULL, 
            0x9DF90C824FCBA026ULL, 0xD47025C875691618ULL, 0x73AA9ED6E337FECAULL, 0x56C12C718FD1EEEBULL, 
            0xB035D977E32401AAULL, 0x4E768E9C97AEBB9BULL, 0x6DD2A3B5FE531707ULL, 0x3459E8307E12A1B7ULL, 
            0x721DF97CB045E64FULL, 0x7E1F5E85D051EFE7ULL, 0x113BF312B9BF2C79ULL, 0x53199B5479C388D4ULL, 
            0x31392A5BEE270DFCULL, 0x14FC24935B3DDD96ULL, 0x11CD5C389ADD241EULL, 0xAC00CCBFF80BDCB7ULL, 
            0x88BC4DA8C3FDAFC0ULL, 0x28EF9CD788FACE51ULL, 0xFEEDC4FB15EAA0DBULL, 0x1E7DA9909A5324FFULL
        },
        {
            0xB6820516E5B59A8FULL, 0x6DA34CCD27CE22ECULL, 0xC496DA2AD5293A64ULL, 0x052DF5B89F3E5092ULL, 
            0x2322512732E03BACULL, 0x7A568041B77AB041ULL, 0x9364B4E91B2EBFFDULL, 0x565E2AC91768B86EULL, 
            0x94E1490EB60B9300ULL, 0x66E1EFE05A26C8A6ULL, 0x214C9A5796064DABULL, 0x05EB142C539E2E0FULL, 
            0x7DA0553342C76F71ULL, 0xB0D958501189CA0CULL, 0xEAEF13BDB10DC570ULL, 0xE346D1EBEB80C788ULL, 
            0x3423FC1CB15D5275ULL, 0x513D1CF2D8CEB88CULL, 0x1D5350C8F76C3384ULL, 0xF828B8BAF7866345ULL, 
            0x0CAF08A3CD233356ULL, 0xE4EC602F90873AE3ULL, 0x20DB6596221DB48AULL, 0xB5DFC43C7345493AULL, 
            0x7426200B4DBEEBDDULL, 0xD1838150FF7D19DBULL, 0xB6E24AF70CDD98DFULL, 0x74B99222F4533C9AULL, 
            0x7CCCC0199C217E53ULL, 0x8E3798BADAD3ADCAULL, 0x7A64EE503994157CULL, 0x2B2675AE3E1F2C47ULL
        },
        {
            0x132ABF8DCEDB3B6BULL, 0x2F4CD89A093190A7ULL, 0xED72C93BA0C3920CULL, 0x5E5794C0408CE159ULL, 
            0xC421B777B95B36DAULL, 0x25C884EAAA132C73ULL, 0x291BF286C613FC7CULL, 0x672580717CD173E6ULL, 
            0x0D9EF8C51F5F2A76ULL, 0x9B3EA715A8B57C51ULL, 0xE18FDDF86B25FC1EULL, 0x5C0984D0EAAEF653ULL, 
            0x8FCB84C1952ACBECULL, 0x601CB41C25221D35ULL, 0x5EBE489360F3BE77ULL, 0xC75969B2891F9F19ULL, 
            0xA102E9828946DE26ULL, 0x6B45115377D2A680ULL, 0x6D95BBF691BDC40BULL, 0xEF9B1DE8B4B23CA7ULL, 
            0x8B3ECED2711F57E1ULL, 0xAC5F9A4BE7BB89C6ULL, 0x202EDE27FE7BBC9DULL, 0x2764932CA1FC3DBAULL, 
            0x4DAA95999DAFD549ULL, 0x6D965481624E6BA7ULL, 0x6374C2601D9D1E23ULL, 0x860968297C476517ULL, 
            0x40D0611BCCC6CF2BULL, 0xFE933CB4818CC37FULL, 0x3BF13242F66A990DULL, 0x74BCED7A7373D4A2ULL
        },
        {
            0x322AC78045EA6C90ULL, 0x79523F2F9ABC78AEULL, 0x922806C358E016DDULL, 0xB5B249158D52495BULL, 
            0x38E47CD0C765C1EAULL, 0xC56BF2671DF1AC10ULL, 0x84D9E956ADE9546EULL, 0xA67FCC163FDF4EBBULL, 
            0x87E1F82F4558C080ULL, 0x3A5659E1A501A4AFULL, 0x66CF8E6149FC88A1ULL, 0xEF0698318B77EECCULL, 
            0x50CC599CD88ADAB3ULL, 0x03295317EEDE90C5ULL, 0xD7AF5975430D73B7ULL, 0xD4C33ECD50902910ULL, 
            0x2BC1929D8DA10ED8ULL, 0xA7C704AB77FA5FB5ULL, 0xE72F992C52852AC3ULL, 0x976B4F7BD0141DE4ULL, 
            0x940AA615390E631CULL, 0x83D16785A2E5ADE8ULL, 0xEAC5B49A51F43DF7ULL, 0x14E9A2E806078940ULL, 
            0x454597AF961C29D8ULL, 0xD19B2A09CE3B7D9AULL, 0x81644134B25883ECULL, 0x6EB82FD4F3AF4F25ULL, 
            0xDBE6DA5650E8353FULL, 0x1E25538EB2461AEEULL, 0x90D6FB7993B2FEBFULL, 0xAEB583F636EA7E02ULL
        }
    },
    {
        {
            0x343DE6ED5389344FULL, 0xEF92B59E3770F078ULL, 0x6A4E5C926E3FFD83ULL, 0xA0C3E137A332AFAEULL, 
            0x0E98B7D6124D920FULL, 0x6D05C41BF13F8E5CULL, 0x10EEE137523E3376ULL, 0xBF76406B7DB5D354ULL, 
            0x40A14015CFEAD749ULL, 0x770EC9A0DA480E44ULL, 0x2E44D53AFE7B6F5CULL, 0x01464886B912286EULL, 
            0xB21FEC099BFF0FDBULL, 0xE254B84DF22B45FDULL, 0xBAB2C6C865177F4DULL, 0xEACF99268B463B26ULL, 
            0xC4AFE861290FDDD4ULL, 0xE0770ADFF6CC4D1BULL, 0x4A3720B2DD2762B7ULL, 0x47A45190AA946D22ULL, 
            0xFB1A9D8131B021B4ULL, 0x3EC440193EDE3CEFULL, 0xD510E12C979CE99EULL, 0xBFD2BB95E47B3ABEULL, 
            0x597C4CE9F538C946ULL, 0xA76D2A8AF154A42BULL, 0x4B8BB8EDCCD88177ULL, 0xD373D757BFBB6409ULL, 
            0x4CFC763B8B46D21AULL, 0x8E58B3529326A92CULL, 0x28F3DB980CE35AA6ULL, 0xF92179EFEBA3D178ULL
        },
        {
            0x98D8F002EB07B161ULL, 0x0D34A06BD0F68BB2ULL, 0x2F8574C49CE3E780ULL, 0x21280F00638B6D4AULL, 
            0x67B05F5E80F8FAB3ULL, 0xF9DF71B16031576CULL, 0x206532182C7029BAULL, 0xD74446FDA4728F64ULL, 
            0xE05010E04FA84030ULL, 0x36CD81B0D024196CULL, 0x65397A7C3E4EDB60ULL, 0xB0EEF6C249EC1670ULL, 
            0xC73FF9CEBBCA8F08ULL, 0x35797E4FE3CB59E0ULL, 0xFD53C4AB253EF2C0ULL, 0xFE81CFA0725B3AABULL, 
            0x432435CABFB06343ULL, 0xFB499368DFAD037BULL, 0xF1F811549B302690ULL, 0x2183565E7C58F9EEULL, 
            0xE70DC01D95FE56E0ULL, 0xD08251F3AA7DA562ULL, 0x7BA60D9A288E5D2CULL, 0x697CBF1EB4FDD7CDULL, 
            0x81072434E7FA8EF8ULL, 0x63B5BFA4298A2A75ULL, 0x740CF7F2C3EF2CE4ULL, 0xC4A135FF475221E9ULL, 
            0xFB9A3076312913D5ULL, 0x0CAF76385BAF1B48ULL, 0x46DC3F4561940ADCULL, 0xA0E13869169D04FEULL
        },
        {
            0xB13D9BB25C46FA4FULL, 0x35136CFED0F54100ULL, 0x5A3A4B32C569E472ULL, 0x3E17A193C1EFABB7ULL, 
            0xCBF615170C977187ULL, 0x8789C094CC47BA39ULL, 0xADAA6FD21A9B617AULL, 0x978CF995D1273D09ULL, 
            0x2ACA9A1E5446F763ULL, 0xD66558C135FEE61CULL, 0x12B93F33E4B86E0AULL, 0x3F659A8B6A8C055DULL, 
            0x657E6CC0FB9F865DULL, 0x5F8E1E7DA0013EA9ULL, 0x554AA09D2F6D3D8BULL, 0x5D5EB13AF72DAD17ULL, 
            0x4282554DDE948185ULL, 0x766ECAC9EE2DEAC6ULL, 0x119F2A7C7429F157ULL, 0x8B5A9A9AA72837D6ULL, 
            0xC13EA76AFEE5AD57ULL, 0x092EB59928117ADDULL, 0xFFB9D5A2B86636C9ULL, 0x7E07059850046E90ULL, 
            0x7101102BE316F395ULL, 0x5C325516F8635B45ULL, 0x68AFA042CDEBF58DULL, 0xA58D7C30B047382DULL, 
            0xD41A5058F3811FEDULL, 0x467216B63E7CDE86ULL, 0x9AB7F6542C8007D1ULL, 0x07ABB9506FABB9C3ULL
        },
        {
            0xCC5A6385DC92F8D0ULL, 0xDDCBA9BB44E6DDF6ULL, 0xFB9A6E3DDB312027ULL, 0x90C8C864946496A7ULL, 
            0x0D628EA1DAECF67DULL, 0x36C013FA820AC124ULL, 0xEF9BEB615600FC53ULL, 0x4A349850164C04BEULL, 
            0x191022AC14C0FAABULL, 0xBB77BBCBBEE7E499ULL, 0xDFA301998B6C2110ULL, 0xC53E55955036EF61ULL, 
            0x486BF354043866F3ULL, 0xCCAAE9FEB809AC46ULL, 0x28A3DC8B8B7877EFULL, 0x41D493F24D2D28BCULL, 
            0x566E872695D77754ULL, 0x55679FA6D5FC5990ULL, 0xD4D5DB739F30B9CEULL, 0x8B9F1686EC418924ULL, 
            0x722955EB872F96FDULL, 0x2571A80420A1681AULL, 0xD17ABC6F35047229ULL, 0xB0E8131B05F68A04ULL, 
            0x3765532BAA51EBB0ULL, 0xC6506307E3C9B1F4ULL, 0xFC0138D0F28F0D9BULL, 0x8723DB0B05A4664AULL, 
            0x4F9843A87AF54BCFULL, 0x09B75D6CE6E47967ULL, 0xB428193E3E8BE46DULL, 0x2159494DF59AE725ULL
        },
        {
            0x556AB02AA18F6775ULL, 0xA0712B109C19EFCEULL, 0x6813A05106FE5D00ULL, 0x5935247ADAB54B7FULL, 
            0x1CAF563E74F4410CULL, 0xEB4D3AE08A3786ACULL, 0x9A7E747C3FC463F7ULL, 0x89FE74A9178E5F4BULL, 
            0xE4625E1137B6814DULL, 0x457D6097B04C90FAULL, 0xC32F223C157D58D0ULL, 0x132BAE765D90B54EULL, 
            0x2ABE7FE6586787C3ULL, 0xC7F57FEE13F2567BULL, 0x12460B1518CB0C9EULL, 0x587226D3322AE3E7ULL, 
            0x671FA2FA270E3AAEULL, 0xAEEBFDAC373227AAULL, 0x9F8E1CB6AA7FFFDCULL, 0x2217B4169A296FA2ULL, 
            0xD5ABBF3B63C8F8CAULL, 0x99DDBFFEC794FE86ULL, 0xB1D09EF6C20D5C75ULL, 0x540300BC5A6D0B89ULL, 
            0x0DE8B3DD27645083ULL, 0x2CF3328D5E04B38CULL, 0x20137EE4AC70D018ULL, 0xA9163F4BAE7C32E2ULL, 
            0xAFB5BF8B9CB02896ULL, 0x42BF00F15942BED6ULL, 0x483ED98504427874ULL, 0x9F7A5268F13AC0BFULL
        },
        {
            0x1EE4550EE57DF8CFULL, 0x4B4D6F8B57522737ULL, 0xBD82093B8B69E2BBULL, 0x5D7476527A3B3E83ULL, 
            0x7BFE9530C8AF36A8ULL, 0x48AFB5A2842148ECULL, 0xE3F08E6895040625ULL, 0x556CABED598D2053ULL, 
            0xBDC8761F19FE6E49ULL, 0xA993731F0F0C9D5EULL, 0x130BBDADA10C91E3ULL, 0x35962D407515CA91ULL, 
            0x45C9AA04B7A4D34CULL, 0xD31FA13331FC6109ULL, 0x3B98B13F797FFFF4ULL, 0xA843E7039A70BBE5ULL, 
            0x78C67237DCB4DD0DULL, 0x361E64112D252BF6ULL, 0x487ACF7398833A62ULL, 0x00137606C327A760ULL, 
            0x01B6031F901303E3ULL, 0x622960628E760094ULL, 0xC62873686FCA6E8AULL, 0x7750D20457A6308CULL, 
            0x54653D298765738BULL, 0x367589F5D35B2E8FULL, 0x88345C7C17A9CD88ULL, 0xFFD5297C2C214A50ULL, 
            0x269EC195F469758EULL, 0xDE19181A7F761157ULL, 0xBC630070D54AEF4BULL, 0x9F370A9EF9288467ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Antares::kPhaseFConstants = {
    0xF9AF165BC6632CD0ULL,
    0xEFB7E95A3C5A03FFULL,
    0x1D4A23AA9AEE9A9BULL,
    0xF9AF165BC6632CD0ULL,
    0xEFB7E95A3C5A03FFULL,
    0x1D4A23AA9AEE9A9BULL,
    0x64E8F82459816870ULL,
    0x52AB9356AEE3C307ULL,
    0xB9,
    0x27,
    0xCF,
    0xDB,
    0xB0,
    0x77,
    0x83,
    0xF8
};

const TwistDomainSaltSet TwistExpander_Antares::kPhaseGSalts = {
    {
        {
            0x8AB4BE1A28B2050AULL, 0xA536DAA979DA7842ULL, 0xEF99C8A71BA95B3FULL, 0xBA6FC99ABA309794ULL, 
            0x1950BDBD5458CE94ULL, 0x3E33A184CAE1F286ULL, 0x67EB3AD3165C6276ULL, 0xC29EB2E7566C134BULL, 
            0x286E297235945B11ULL, 0xEDB5C3211C056325ULL, 0x163C0BA1FC3C0C9DULL, 0xB15C27B0BF55AAC4ULL, 
            0x854351945EB5C6AAULL, 0x18D89A6ECA20944AULL, 0x76AA272853BBB2F1ULL, 0x8A6525199B56D520ULL, 
            0xD132FD6E60D0D2EBULL, 0x46EBD12BB384633FULL, 0x350F18907B51063CULL, 0xA9FE3E50BF71A9A2ULL, 
            0x917E7EC519BB63DBULL, 0xC5EEC7D5078A2432ULL, 0x6B06DFB416FC0032ULL, 0x1411020F6B513391ULL, 
            0xDCBF706E7F007D8EULL, 0x7FF9F4AE1D294889ULL, 0x7EC0852998135839ULL, 0x4EC058DC8F4E89ADULL, 
            0x31B8F0B166AAAAA1ULL, 0xFF7A410A0805C2C4ULL, 0x17DA42A5C5E24A4FULL, 0xFD8CE3AD99323C4EULL
        },
        {
            0x51131CAEACFCDD3AULL, 0x38D05386E60C922DULL, 0x857B58215E7725F8ULL, 0xB215F2F0BE9BB523ULL, 
            0xA7EADC83897494B1ULL, 0xBF9A1D1F93FDFC1EULL, 0x3CC849FCA09A6F24ULL, 0x780D99CB87809C64ULL, 
            0xB9892E10AF9E4EE1ULL, 0x478E11292A9D4AE0ULL, 0x326E6B1034AF107DULL, 0x62B094801E776BC9ULL, 
            0x24F281D434A1E49DULL, 0xA7CB5FA9349D076AULL, 0xDD8861E468D4A371ULL, 0x746029F926E0330FULL, 
            0x54AA3A899ECCE087ULL, 0x05DF5EF70BCE0220ULL, 0xE6B161E7CCF554C6ULL, 0xA52A0D8DEAA4E51FULL, 
            0xEF25B0344FE1B6B4ULL, 0x6AD361F7BB223195ULL, 0xE8FE248A6971E18EULL, 0x10C17B468F314AFFULL, 
            0x53E5CD6B1516B0A0ULL, 0xF7339C455C20A6F1ULL, 0x1A13AF1F504B4E40ULL, 0xB489A2FF1BDB6AE8ULL, 
            0xF1B23142AD198840ULL, 0x18C1BAB1ECE473A2ULL, 0x4EA8C160B28314EBULL, 0x34F2E301485858FBULL
        },
        {
            0x72BF0742942501E4ULL, 0xA6EB36E1AB764CD9ULL, 0x06024D65FE0555AFULL, 0xCBAF6CFB18090417ULL, 
            0xF35F7F31770E4FB4ULL, 0x905102A35F5913FBULL, 0xFBF1C13DE4C78390ULL, 0x1E68C2D12DD7EFC2ULL, 
            0xCA627B0B33F9D1E1ULL, 0x67CEC894087F7072ULL, 0xEB157F9DBA88B90FULL, 0xDB30CBE331F4860EULL, 
            0x5733F2BE5FF5B462ULL, 0x70332F84C9216DE3ULL, 0xA4DDD8CFE49167ABULL, 0xA2F6DFC65B7838D3ULL, 
            0x1882FCC1B274566FULL, 0x641074433707116CULL, 0x199AD04B2BF01F0FULL, 0x01D87C0D0428A4E6ULL, 
            0x4435DB8A6D5B5C06ULL, 0x9EE65D928EB7BE96ULL, 0xF29206AD7B23C9E9ULL, 0x90EE8380031902AFULL, 
            0xD911705F4FD2F7A1ULL, 0x7B662AD846A775DFULL, 0x391E6FCD8DDFB948ULL, 0x8E9F6EE2BBE77A4BULL, 
            0x7BBE9C6681D62A0CULL, 0x2ACE2ABF80046410ULL, 0x28C4D70172DCB680ULL, 0x398486CFFE49B763ULL
        },
        {
            0x5EFBF7C972EE0137ULL, 0xCCDD09C75E4B2CCAULL, 0xE004EDF9D320CD01ULL, 0xBC2CD40CE3625DB1ULL, 
            0x6EECEB83A2480441ULL, 0xE4A143F6B4D20585ULL, 0x78FD1BAF2352C40EULL, 0xAA1445C50B3E5731ULL, 
            0xAEE25BC7D3251BEDULL, 0xF8CCD85D8A3A5465ULL, 0x0E834F09E1FE2476ULL, 0xC8065504BB912781ULL, 
            0x8F226A80F794A540ULL, 0xA6244006D78C5551ULL, 0x9C1FDB156AD7FE25ULL, 0xB5A9874AF5748DDCULL, 
            0xD667AF2BEFC943A7ULL, 0xA0EDF31BC026AC13ULL, 0x4FAD708B43117788ULL, 0xD971762F6EA6D169ULL, 
            0xF1992579D3215EA8ULL, 0x600361A16E58BB1CULL, 0xF7308B1CF43B52A2ULL, 0x4DBE298BFD9A9F59ULL, 
            0x3850B49AE479D108ULL, 0x6E3E0AB09E6D8E3BULL, 0x1BE4192547FEA3D8ULL, 0x59CD6C027436C518ULL, 
            0xF5D2BC8AFB96B40AULL, 0x6447F6E2C505B939ULL, 0xD57D2B6A288655ECULL, 0x3D92BE8C6E7029FFULL
        },
        {
            0x682E442179CA4D19ULL, 0x70EE9525C960B4DFULL, 0xF4625BE43714AB79ULL, 0x4115455BAC61329BULL, 
            0xAD61979ED06D036BULL, 0xBCB8C5BEB5510409ULL, 0xCEBFA460B07FD89EULL, 0x23384D3FE7D417BDULL, 
            0x9921C9EC68587AA3ULL, 0xD005010BA069AF8DULL, 0x86045768CEAECCD8ULL, 0xAE6A44C3B68EC3FFULL, 
            0x1776D4246A9F4C37ULL, 0x615AE48928847001ULL, 0x80FD07D0B3952151ULL, 0x8A98E52099C9E8BFULL, 
            0x06D7FA70D8DF8182ULL, 0x3AC16E46DCB065AEULL, 0x8FF9CFCB99F09390ULL, 0xF8685E88C4617551ULL, 
            0xD2FA5994009AC215ULL, 0xF3289DAD08E629FCULL, 0x907C30C85D561772ULL, 0x2DE3CFEE69066692ULL, 
            0xEE6491524B7D1BCCULL, 0xBFB6E23E429831B6ULL, 0x73ABC06D09FEFADAULL, 0x4866FDA05BB4495BULL, 
            0x690395C8DA0C9AD6ULL, 0xADFC21BA4F08DD04ULL, 0x94DD5155BB0E7E32ULL, 0xD5C28AE3A913CF3BULL
        },
        {
            0x432FF6537DC58E29ULL, 0xBD72949E9416ED8DULL, 0xE7901C906E9DECF6ULL, 0x8E664E5E928A5832ULL, 
            0x326A66CBE085F41DULL, 0xBC7514D4DB43F25EULL, 0x207792427F964644ULL, 0xA344820344A0ED9CULL, 
            0xCBAC0260F08035B6ULL, 0x4C20340E0411E262ULL, 0x60C7A7B2D777FE3CULL, 0x65B3D008BB60ACF5ULL, 
            0x874D0B51E1BCD68FULL, 0x3002B682E3F58F45ULL, 0xECA0B30D6430233BULL, 0x88EC0182A72712BEULL, 
            0x480E0B457155B588ULL, 0xD290483BDB5D5BB2ULL, 0x5F2BFAA6C9B9474EULL, 0x91FB2EADBB9218E2ULL, 
            0xA061CEB274D9D4BBULL, 0xE00886844FE5B60AULL, 0x50E48B1C48C25F12ULL, 0x3A808A4C1776ADFEULL, 
            0x930A7E630638BF67ULL, 0x2F3C4B6B954955ACULL, 0x84FD88685320A8C6ULL, 0x7463D5DD66813FA4ULL, 
            0xECB98B9F6175D9D4ULL, 0x7BBDE0AB7EEB8D7FULL, 0xD4C9A40412791940ULL, 0x093F888164B561E9ULL
        }
    },
    {
        {
            0x63B9D8370C8C0F2BULL, 0x2ED56F659C3F2DDBULL, 0x900B898E1EB07903ULL, 0x260FD5B8D5202901ULL, 
            0x1562909B3DA40231ULL, 0xA642560DF3F06207ULL, 0xE34F32791736A7F3ULL, 0xDFA0D9DD3E3A828EULL, 
            0x0673DECAFB3AC518ULL, 0x24DF7BE4616330D4ULL, 0x9B00D6BBAA66A2C4ULL, 0xF0C3ADB545B64964ULL, 
            0xE9A3659549FA6E92ULL, 0x3166592FB141453AULL, 0x1DA3A66ECEAF733DULL, 0x1139F35C321D3558ULL, 
            0x3CD3E29188DCCF70ULL, 0xA4FB1F937F4F272CULL, 0x239753A912EC7AC1ULL, 0x8F9974C589E783CBULL, 
            0x48074B716ACC107DULL, 0xC935EDFD4FD7A9AEULL, 0xAA097D18D8B2A96DULL, 0x3B9E624DB4470986ULL, 
            0xA3D4639089C55B94ULL, 0x3AD6315AA93CA481ULL, 0x9152E49714498F47ULL, 0x39D689E7DE595584ULL, 
            0x9DED703A85AAE397ULL, 0x041734D217F687DDULL, 0x273969974FDF9EC8ULL, 0x0A565111BCBE7C77ULL
        },
        {
            0xF61766231FD3E650ULL, 0x8123858CC4B36AF9ULL, 0x6C62A2A85D3725DBULL, 0x589F7CB4A1ABB701ULL, 
            0x7377A2D89BEDA813ULL, 0x1D1E5131E16982E2ULL, 0x31B9825DA89EBF82ULL, 0xC3FBD2D4F9413982ULL, 
            0xF9759CBB05CDA496ULL, 0x5ED8D10ECC8E6790ULL, 0xCA0DA44048BC9E4DULL, 0xEA4502096CF0CCC2ULL, 
            0x2D0953E02DE72B31ULL, 0x1A4312EA19980395ULL, 0xBA05A0092B211211ULL, 0xC730B7B3C2AB97D1ULL, 
            0xC43BDBECEEAF9159ULL, 0xD4C8A7FD3EE5B512ULL, 0x0F8C1503DB492D37ULL, 0x0BE369C98229DB85ULL, 
            0x8EB12D949CE8E2A9ULL, 0xB1DDDFC6386436E3ULL, 0xA08578C0990926DCULL, 0xE60153778E5E995FULL, 
            0x685231C18D477700ULL, 0x19E45BB318228752ULL, 0xDF912C130EA76742ULL, 0x43B8C9CF0D16B777ULL, 
            0x799B9F948CE85399ULL, 0x7F2C73332B1B6219ULL, 0x2B9E4A0D7BB1C6EEULL, 0x35B14958675E22A4ULL
        },
        {
            0xE4AECADBA7452655ULL, 0xE737B98240985EA9ULL, 0x433836B4533AF5DEULL, 0x44C09A581202A530ULL, 
            0x052A39FC23089476ULL, 0x027AA71649CAE7A1ULL, 0x1621F00938DE2ED8ULL, 0x62CB63D8ABA42716ULL, 
            0x45150D6CDF70B807ULL, 0x27E2085517FD6438ULL, 0xC1ED83BCBA95F5FAULL, 0x1781A388CA136807ULL, 
            0x36B05C6E4E4C7F61ULL, 0xB1D1BE7EA0D46D16ULL, 0xD39CCE60B8998BADULL, 0x6543AE70EF6091F1ULL, 
            0x0003BC8DA14CEAFAULL, 0x5E81CEAD984A5E7AULL, 0x93AA4E44FBFC74FDULL, 0xEED61F4215F89208ULL, 
            0x1334CCEE4FCAE537ULL, 0x208CD3E97F2190EEULL, 0xF5C03CAD0ABD2033ULL, 0xC2EFBFDA9585CB8CULL, 
            0x75BB997124C310B3ULL, 0x183BB8F9E94146D0ULL, 0x4D1DB4C1B7DDB064ULL, 0xC9C298BD0E2D6976ULL, 
            0xCB1C5C3701DC2BA9ULL, 0x0423F62CC02259FDULL, 0x8653BDCCF7F67381ULL, 0xF3C2FBFF3523B935ULL
        },
        {
            0x8D18F6DED5DD5727ULL, 0x43F68A87E10597F3ULL, 0xF9C4496645D0670CULL, 0xEFF0A06F8864EE07ULL, 
            0x91B2FA4411CAF871ULL, 0x622F06EC4DF77EA9ULL, 0x06B4E08C82AB5BEDULL, 0x04A9FB67D772F0CCULL, 
            0x8366948D86525232ULL, 0xCE943B2A44C622CAULL, 0xBDB9ACB665F12F8EULL, 0x420CD55DA81C0902ULL, 
            0x5CC53EE01CC3BD06ULL, 0x97A0297B07073D39ULL, 0x3DA43E1CAB246D5AULL, 0x0EB6CF8298592C08ULL, 
            0x56A4D44E1840DD7EULL, 0xC094F7AA694C427EULL, 0x419E9A3D97D04DA9ULL, 0x38C69014A03A4EFCULL, 
            0x39853BFBA46AFDF3ULL, 0xCB9591FDD8E51881ULL, 0x56C7625BD90C02EBULL, 0x661F4F9A01527DF3ULL, 
            0xB54CE5EABC0CFEE6ULL, 0x14F3448EED2ECE20ULL, 0xD3ED49D13BD8863EULL, 0x35E3FF3D1918700AULL, 
            0x9920D1E187B13A90ULL, 0x617A4EF99E712E21ULL, 0xD01F11DD4F726E37ULL, 0x954D27743C9D3AF2ULL
        },
        {
            0x3BBF934E474442E7ULL, 0xA936AD6BB584BCF6ULL, 0xB891369117A7404EULL, 0xCBA456E18AA7737FULL, 
            0x044FBC903E43B876ULL, 0xBE59442EB832F3F5ULL, 0x2F9348C2405FB181ULL, 0x52FBF91EAF3BB0CAULL, 
            0xD57118F95F73CABBULL, 0xD093498DC046C7B4ULL, 0xB265BFD123B05270ULL, 0x51413FD6EA02DF07ULL, 
            0x98B5CA72C3518DF9ULL, 0x1782C9F511FBB00CULL, 0x31CA1D0D09273F23ULL, 0x90CDE29E92C7A002ULL, 
            0x219A8412EA6A71B8ULL, 0xCB867F8CEC4DB51EULL, 0x73E6CB2109105D66ULL, 0x691290ADA4315B1AULL, 
            0x1D59D11617426790ULL, 0x42B8D6E18C67903CULL, 0x8AEBB16AB886A7F2ULL, 0x72B332C48885CDD9ULL, 
            0xCE2D8F5FC0C3A99EULL, 0xCAD4748756216C04ULL, 0xE52854EB523A4021ULL, 0x8278009CC305E13CULL, 
            0x6314D026074F3136ULL, 0x85F7CAF920BA0F88ULL, 0xBB17286A9FD72624ULL, 0x5E177295777CBC4EULL
        },
        {
            0xD0030D29D97B9493ULL, 0x4568BE6EC4A059A6ULL, 0x46EA6D9987641204ULL, 0x380D956DD9A18BB1ULL, 
            0xEC0040E8FF003196ULL, 0xD5790C89D6D2F849ULL, 0x523EF88754533256ULL, 0x001C347CA181AB8BULL, 
            0xF3C8745CD45B39EDULL, 0x4413E4E51F126CBAULL, 0x8E321904765943A4ULL, 0xA6D956ABF23A648DULL, 
            0x112C51C7149548C8ULL, 0x002D0EA0F9E63FEDULL, 0x22D6CA6C99FBFB6EULL, 0x761DD2C12290852FULL, 
            0xADEF9D365E7C1729ULL, 0xA761CAEC2DE5890AULL, 0x3E3025F9AB79C252ULL, 0x346A1B2340A08B42ULL, 
            0x469DC911F9566B2FULL, 0xEAD01D9BC8372F61ULL, 0x246435A74E592384ULL, 0x543D8161A25A417BULL, 
            0x73771A88FEADCEA4ULL, 0xDF78961BB30F1F2FULL, 0xB21322E4667CB426ULL, 0x7F3DDF0C1487DE80ULL, 
            0x0ECC69705A5F891EULL, 0x5D135C92B17F8318ULL, 0xE97E177614698FDCULL, 0x9EA3C5E851FEA7D9ULL
        }
    },
    {
        {
            0x867307DA93ABB98DULL, 0x3C80057A73CAB86EULL, 0xCA98AFA31B643EB9ULL, 0xFED7F23C88CC3824ULL, 
            0x040AC4D4949E9EC1ULL, 0xF7FEEAC1F9CB08C2ULL, 0x96DCF57FDE81E62FULL, 0xDF9BFC0D06F0DE1AULL, 
            0x03FB044740D38752ULL, 0x72E26EF64B8D5AFFULL, 0x5245D0B5641CAEFFULL, 0xC3E1B576DDA0CDE2ULL, 
            0xA489CFD7E27A6415ULL, 0x621AAC67F1972F03ULL, 0x4F0754BF266ED2F7ULL, 0x6B7C0FE44A5AD904ULL, 
            0x5534D51BD2597E7BULL, 0xF8360CE67B00E391ULL, 0x787E372512CD5CD6ULL, 0x76C9017ADDB23EFCULL, 
            0x21632B220AD8DA57ULL, 0x348706EF3E711FE9ULL, 0xBD14BB96F815C6FCULL, 0x5A1659FDEFEA6408ULL, 
            0x0B2C80E8330F9D0EULL, 0xAFA5A571B1210DA3ULL, 0x222503D63F61E396ULL, 0x9298DF965804E294ULL, 
            0x2C1E89E9245208B4ULL, 0xE7C2108854A903DAULL, 0x363CD3C1A6329527ULL, 0x0000F8BBC9A1DBB3ULL
        },
        {
            0x7AAE04E0353CA990ULL, 0xCF1483F9ADBC6AF1ULL, 0x653A1BCB3A0C9B78ULL, 0x549CC3DF15525AD0ULL, 
            0xFCF9E13D3AAD96E1ULL, 0xC8CC4669D0AD26D6ULL, 0x1329D552A8409BF0ULL, 0xF7A8408AAB67EC02ULL, 
            0xA77BEDB324F0D0A4ULL, 0x647E97D9C550B3C2ULL, 0xC4514FB001A949E9ULL, 0x667BCA57A23B008CULL, 
            0x78104ECD79FC28C2ULL, 0xC3DB7CD7BBFFE61EULL, 0x0E1886E926B48322ULL, 0x47B76DDCF0782704ULL, 
            0xB122A6F5541BEC9EULL, 0xAAF28F59C7EF4A99ULL, 0x5A4CF1BEFF8A3328ULL, 0x0DFE90A51FFEC22DULL, 
            0xDA7881CF69B48154ULL, 0x0F285C0FA08F67CCULL, 0xC98567E6C3F57D8AULL, 0x66C96549412D5F9FULL, 
            0x85BC090FABABE687ULL, 0x5BB9510E5C68D50CULL, 0xC8CFEE8D850736A4ULL, 0xA6ECB4862F0ACF64ULL, 
            0x2EB8325B914776E3ULL, 0x9CDCD99E9F4B7ACCULL, 0xBB67467F2C73C7A6ULL, 0xF2D6840B880DCCF4ULL
        },
        {
            0xCA284AC0F320DE09ULL, 0xE68BA6E09D56A2DDULL, 0xBAE0E0FF218202F3ULL, 0x89E085133027B29BULL, 
            0x6981D1841F6CBC9CULL, 0x8C10374D855422B5ULL, 0xA4EBD6B13823C8EBULL, 0x833DC48D4AC34981ULL, 
            0xA2254EB6DE041051ULL, 0x52C57EBBC97A6284ULL, 0xB6ACF806EEDBFB2AULL, 0x466FB8AAE2FF696DULL, 
            0x7B8A2B149CD682B8ULL, 0xAAD4F48C23CBA4AEULL, 0xB00A46DBD7D5BFFBULL, 0x8C7CA0DDAA622CC4ULL, 
            0x2637EF6F4FE60C73ULL, 0x2FA3FACE00C10447ULL, 0x0066AB7AC3006163ULL, 0xD66054D917F320B4ULL, 
            0xCA3A1EBC11820E3BULL, 0xCAA6668031D7AF89ULL, 0x186EC471E1224E5EULL, 0x0EA058A8207B4B22ULL, 
            0x491453D67452AEEDULL, 0xDC8971A17BFA00AEULL, 0xE688C1CAFD3C5621ULL, 0xFF3BBCB09821AA47ULL, 
            0x2EC665CC20D2967EULL, 0xFA1CB26CC99F8A6BULL, 0xF3B33A738786D300ULL, 0xC592A0EC38F00BDBULL
        },
        {
            0xCF808BEEE3FFA879ULL, 0xD23D42090442D6EEULL, 0xC6338FF8B6F3FEB2ULL, 0xACE9183D89E34BDEULL, 
            0xB8497FBF038D0074ULL, 0x09B7302651DBC071ULL, 0x548358440A6BD272ULL, 0x2337363F5FE35068ULL, 
            0x080BF61BA4807A8EULL, 0xEDDD90A4F0B955BCULL, 0x3F4355B9D0A54F3EULL, 0xCE6F47E139FE3028ULL, 
            0x59263F354F389990ULL, 0xB2313A44753A057BULL, 0x77B3B2820D53C4A1ULL, 0x4A6597CEE76E8857ULL, 
            0xA03387BAECCAA0F8ULL, 0x2D3FC574BAB5BD00ULL, 0x483EE0A687CEE8FCULL, 0xAC4F7CC6C4BCB481ULL, 
            0x45A401E45D82665BULL, 0xCA1336C496903567ULL, 0x83A0288284873A92ULL, 0xA4A7998FD8C88D2AULL, 
            0xBE76A67C2FAB7B64ULL, 0x0347AB015AC2C8CEULL, 0x68E3E4559DDC7F90ULL, 0xDE57F6AD425C5BECULL, 
            0xFBE21144CB149D9DULL, 0x38337B626CD43AD5ULL, 0x29C167D46ACA6E9EULL, 0x525D77441D10C320ULL
        },
        {
            0x488E4616349C6D04ULL, 0x335A88CA4AA63221ULL, 0x3F04B5138BD0D69AULL, 0xC7B2B016109983B5ULL, 
            0x9F1E2F890B611A97ULL, 0x04B9219263EC132AULL, 0x5689FC4F08C55004ULL, 0xD3D2592F54DA7203ULL, 
            0xAE0774BD2347CDD2ULL, 0x2D7D86A296394F96ULL, 0x2D8DB50F3271C459ULL, 0x9E6DE9C441C24044ULL, 
            0xF1B2C641691B4159ULL, 0xF220F3D93FF760F2ULL, 0x6D1F982760DE9CEEULL, 0xEA85643B514BE3F2ULL, 
            0x102A3176AFC2E9A4ULL, 0x65628E37AF2707C1ULL, 0x91F2E56C994D03BBULL, 0xBA054CCA5C07F900ULL, 
            0x77B260E582CFD1EEULL, 0x7EF2F237FE12813EULL, 0x43F2658CED6A8EC3ULL, 0xE8F26F6EFA2F78F3ULL, 
            0x2E785971B78C5140ULL, 0x293D898413D9C473ULL, 0x937169D1AEF0150AULL, 0x301829FC547E0968ULL, 
            0x8D7471F0DC01EDD1ULL, 0xE6D2643EA4CE82A6ULL, 0x713DBDAA5EBE2A5BULL, 0xEF64D986B252E63EULL
        },
        {
            0xC9E0BB1DF9D700E3ULL, 0x1CCECBAD53839032ULL, 0xA06B5DCE0BDC4A57ULL, 0x48B861997E362A01ULL, 
            0x696AE8314EE87B66ULL, 0x69FA633A46FF1CD2ULL, 0xA6C95935001CD4C2ULL, 0x4709014047C8BFF8ULL, 
            0xADEECF5BA65D0344ULL, 0xB81115F3C463FDFBULL, 0x557BBBA43CF06DDEULL, 0xCB5537C090CF4C60ULL, 
            0xAF3340D17D1E8440ULL, 0x3A1CF717B10D16D2ULL, 0x1330F66C4C024F79ULL, 0x75669D80E73D1DE7ULL, 
            0x8345F3C2C8133494ULL, 0xA766D6D5D5353A8DULL, 0x7730100E29006146ULL, 0xC62A780D5A3D14B3ULL, 
            0xEB6EF0BFC433A609ULL, 0x9FA7A2071EE59B74ULL, 0x8BC56775E5A7CECBULL, 0x91380D427871FBE4ULL, 
            0xBA7F835765C8F65FULL, 0x65892AB3AC0B0F29ULL, 0x5547EB9AFFB703EDULL, 0x4BFE690412FC49AFULL, 
            0xFDBF1E0281775108ULL, 0x59CBDEB23AA25C12ULL, 0xBC8FECF53BB0E32BULL, 0xBA5469B3A328F20BULL
        }
    }
};

const TwistDomainConstants TwistExpander_Antares::kPhaseGConstants = {
    0xB79CEE7B64C930F8ULL,
    0xB316A99354D65FB4ULL,
    0x0ABA0C9A1EC63EA2ULL,
    0xB79CEE7B64C930F8ULL,
    0xB316A99354D65FB4ULL,
    0x0ABA0C9A1EC63EA2ULL,
    0x40228F76E0C2F469ULL,
    0x742D6042553D5FEEULL,
    0xBB,
    0x21,
    0x68,
    0x71,
    0xCE,
    0xAC,
    0x72,
    0xA1
};

const TwistDomainSaltSet TwistExpander_Antares::kPhaseHSalts = {
    {
        {
            0x4552F7B22A6741D8ULL, 0xA6457670631E6ABDULL, 0xC2F68CCC9343F0C7ULL, 0x31759F26434FF0FBULL, 
            0xB728EEFF638C0326ULL, 0xD14F479BEAB2ABC5ULL, 0x13AEC4D2B193E3AAULL, 0x19C97E1AAADF5B87ULL, 
            0x9527191CF17F0102ULL, 0x3C7902FF2C0D6076ULL, 0xAD17D464192A7979ULL, 0x4DE1661D685BADFDULL, 
            0x4F9C5B9FA851A37DULL, 0xACFA2F598B346D90ULL, 0xE3752E9A31C75658ULL, 0x7295BAD1E1C11AE0ULL, 
            0xBDE1EF01E1C51DE3ULL, 0x8370447DB592002EULL, 0x411D18E1C72B6A53ULL, 0x726CCBA2094D780CULL, 
            0x2AECA9098D2267E4ULL, 0xDD88EBD764E528B0ULL, 0x5BF0694E9947E9E6ULL, 0xBA36D2199BBF7B1BULL, 
            0x00F61CC1FC4E40CCULL, 0x280D127BB31F8122ULL, 0x0D1DB96280C77C53ULL, 0x95F23FAFEEE20D9DULL, 
            0xF57E3F0ECED5D892ULL, 0xA5E12828C342EFDCULL, 0x35C38690159B3796ULL, 0xA30BD0D2CB0DE787ULL
        },
        {
            0x66DA6703F7303BD4ULL, 0xB9EEC5727AA3006CULL, 0xBEEAA8953CCAFBA4ULL, 0xE6533CAB550BC45AULL, 
            0xFB60A3EAB4165BA6ULL, 0x54434224D60AAC3BULL, 0x8FB3389F3E5E8058ULL, 0x4EAB58CE0E097257ULL, 
            0x6D7E2D7130F29BB4ULL, 0x28710D4006E2261DULL, 0xD4B33F8B75B122ACULL, 0x7771580200930079ULL, 
            0x1F0A82F2944F4FCEULL, 0xB1C21B89CB26E62FULL, 0x21C8EA9207303FC5ULL, 0xEF8DB7E5426AEC20ULL, 
            0xC49492F63DC5E9ADULL, 0x4E1527A8CCAA7013ULL, 0x942E317A4B6FE19CULL, 0xF1676BF26AF1F8EBULL, 
            0xD109040454165904ULL, 0x6E878C9E201EF30EULL, 0xF4B50909C4E82BF8ULL, 0x577DC160E99DB497ULL, 
            0xD2234232480854EEULL, 0x273C76A80675EE9FULL, 0x1AD10396CC66B8B1ULL, 0xE6FD0552EA283D50ULL, 
            0xE547EE6258E2E7C2ULL, 0x95E7036F3B0EEDFBULL, 0xE08489404F22081FULL, 0x76C7AC2308C46169ULL
        },
        {
            0x3AD1655AEC7B765FULL, 0xA992D3FD8EBDEA0FULL, 0xEAAE74FC78D47187ULL, 0xECF76BEA2844D1E1ULL, 
            0x461AA03DDED69FAAULL, 0x721FFC2E8DD8E78BULL, 0x079798B2C88EB242ULL, 0x29CB3DEFB535C89EULL, 
            0x99499630F57AE217ULL, 0x31CA35BF8EB03A1CULL, 0x7E3FC319833D4BE0ULL, 0x225F1FE8F4D0FBA3ULL, 
            0x6DC03006E7F2B9F5ULL, 0xECED62F8A4416A50ULL, 0x80EB2CAE450603E4ULL, 0x35B5DA33979E005DULL, 
            0x8DB518F0F873A355ULL, 0x6E4C5E597C4D1EC8ULL, 0xD52DE0EE63467C68ULL, 0x7A3156DD46619FF8ULL, 
            0xDB27925E5760D940ULL, 0x7AFAE2AA598E7488ULL, 0x91932D43C982A478ULL, 0x31E1BCF874462012ULL, 
            0x26F701CABD403DFAULL, 0xF2A968B0D39EE881ULL, 0x635D6ADD833C7D0BULL, 0x2A053C9AB710E61DULL, 
            0xBCF58FD787EB4B54ULL, 0xC5D7D06EAE8B1157ULL, 0x7017778ED91018B9ULL, 0x0FE90EFEF70724DBULL
        },
        {
            0x082EC523EE5D61F1ULL, 0xE2B4399B693C00C6ULL, 0xB047555DE8DD5F42ULL, 0x14E20E6B2C14FE5DULL, 
            0x5F2F6DA849912D4BULL, 0xA5FA807E1F793C5CULL, 0x057A4C7629B13884ULL, 0x8DC10E1AEF622A60ULL, 
            0x7F7C0A49DC393A9CULL, 0x19FD66135D6162AAULL, 0xD5FACBB3647541CDULL, 0xDD27809A71934CF3ULL, 
            0x1F652B0B2F07DEDBULL, 0x1EF248D58A42ED7CULL, 0x0AB7103C5F16F3C0ULL, 0x2EA92E343A96C7BFULL, 
            0xE99626BA693D4C8AULL, 0x3CC04167B91B67A2ULL, 0xB5F4991416A9B0EFULL, 0x61510F984E0E5D4DULL, 
            0xF873C461D3616E43ULL, 0x8A697D7194012047ULL, 0x98B66AA237A09920ULL, 0xDC3B63EF13AA05BEULL, 
            0xFFF352C2108D15E5ULL, 0x5EAEC41D51432343ULL, 0x954317FBB0095808ULL, 0x60E24933705A2149ULL, 
            0x500CEC546904D51EULL, 0x0EA4CA427A805D0BULL, 0x8354F6BEEB1F5BD4ULL, 0xAF2997893E615A16ULL
        },
        {
            0xD6C6B0316565539FULL, 0x754E84D578BD3012ULL, 0xF98DA5737418EBE8ULL, 0xF53F5B2484F40251ULL, 
            0xB856C67A7B702A07ULL, 0x2D199469A2B92B5FULL, 0x47B20E8B374A1089ULL, 0x828A4AF473CDD23EULL, 
            0x12200E1D71524E9FULL, 0x2DDB940624136EB1ULL, 0x9B85E7455317D600ULL, 0xE9EAB11A30A175A3ULL, 
            0xF742087414FCD6F4ULL, 0x5B3731D7FAEBDDB1ULL, 0x1616C35CA9432F7AULL, 0xD21DC8744F21E815ULL, 
            0xCC0EF0436BBB274AULL, 0x1C6CED7255CB3820ULL, 0xB5974B6D0495296AULL, 0x12932D92EC9A834EULL, 
            0x35F184F6E936A718ULL, 0xF8F3FAC9B7B5D4C1ULL, 0xDD3CEE16D8F3D390ULL, 0x42F04A9C6C9D5DCDULL, 
            0x04215114B9483380ULL, 0xAF84E39CB3B72D9AULL, 0x40BB1DA455ABE3F2ULL, 0x6FBD2A000533DB72ULL, 
            0xF0EF107A44111C42ULL, 0xC611EDB1173C4A32ULL, 0x49D9FB6E5228E949ULL, 0xD55EE77CFFE0DE62ULL
        },
        {
            0x60F0DD65ECC2F0D9ULL, 0xBAF856603372F8A8ULL, 0x095339768BE76A20ULL, 0x7722FD97C67C806AULL, 
            0x2E067E2844D9CEBFULL, 0xE571DE4CDC3F7A8AULL, 0x9429BB61AFC4401FULL, 0x1E133C1DB29A93C8ULL, 
            0xA6B1A4DAFD2E7DD1ULL, 0x1FF838F3820E41C9ULL, 0x3C4E072D966A3F15ULL, 0xAD1723ED5275B603ULL, 
            0x9C94B7D2A180477BULL, 0x9CA9FE7BA88E1C87ULL, 0x6C51F800549BBA24ULL, 0xE3F8D24D2C22752FULL, 
            0x7D68947108B68305ULL, 0xE8FA2010969866EDULL, 0xF24380AA1631EE9AULL, 0xF0CE775CD0C5C3D0ULL, 
            0x7D26BF3F2B0EA0FFULL, 0xCE56893DF1509ACBULL, 0x6A04FC42BF1C868CULL, 0x0DB0619468A31776ULL, 
            0xE2A1209A4D717A2AULL, 0x99D579334D10DD86ULL, 0x8DA602EF383FA837ULL, 0x2FBAA76621D7D7D5ULL, 
            0xAF845BF660C7CD15ULL, 0x2FA78EF3A78273B0ULL, 0xCA9A10C71B97708DULL, 0x9C45A3AE5E83C085ULL
        }
    },
    {
        {
            0x31A88804408A4C0BULL, 0x262D84BD317F3A4CULL, 0x33A761B890D32CCEULL, 0x8A6A35E508F24F69ULL, 
            0x4DE1A12B189040CEULL, 0xB77D3333A52AC3CBULL, 0x116690ACEBB07E47ULL, 0xF8A420BEBCF0DF9BULL, 
            0x898124A1302BEF3DULL, 0x943ED553E27A0DC9ULL, 0x73A629A4397CD874ULL, 0x6B44FAD90651508CULL, 
            0x5D938E2F0A2508A2ULL, 0x70F14C94000DE1B0ULL, 0xF50EDB6571911853ULL, 0xC5ACF7B2FF39D7AFULL, 
            0xCDB2746DB855E244ULL, 0x61995541E2D8AB24ULL, 0xCD2E7D75B641ACA1ULL, 0x0B4B04D43A26C8E6ULL, 
            0x9B31E320D0A255A1ULL, 0x00D553DC99EF8ADFULL, 0x6E0D5B34FBCFE224ULL, 0xFC3EA4D49021D04DULL, 
            0xD82BF7F26B03B00DULL, 0x4E3DBC3EF7C349AEULL, 0x127590771CD44C77ULL, 0xD8CEA2D0B29D68CDULL, 
            0x1835361E1286386CULL, 0xB2CBDA72FA0ED749ULL, 0x0640E9A6BBDD71AAULL, 0x8E7F4D70EC82FE89ULL
        },
        {
            0x1EF0D09ACC3F1488ULL, 0x99C6D0806E62885BULL, 0xA08336E8AA86120FULL, 0x67D2AB96D8A8FFF3ULL, 
            0x6E3BA2AF148BF823ULL, 0xD4897FD804062B3CULL, 0xBC77D4DC24BA9E3FULL, 0xC37AF72DC7C9976BULL, 
            0xD0599A21340FF43BULL, 0xBD0C4E7DF7638DBCULL, 0x4FB52655330CBB80ULL, 0x54740D9CD765A7ABULL, 
            0xBF2A6D630E2AC32CULL, 0x4BBD82C70E4883D6ULL, 0x1C56CCE656CF9B20ULL, 0xB10EB22E91A24671ULL, 
            0x9DEBFDD81AA71D88ULL, 0x1889C32F845147AAULL, 0xF524F4143AF34E4AULL, 0x8930896493FC067CULL, 
            0x314A3CA8CCA5E6DDULL, 0xE11F87235F69C56DULL, 0xF698D3D52CF769C8ULL, 0x6D1F873292AAE36FULL, 
            0x4DC4D31762BF9E2EULL, 0xA959288603B392C2ULL, 0xEAA15619CBA7E5D4ULL, 0xE9D9D66EA4F1642FULL, 
            0xE070A9F2375C0609ULL, 0xCA137E352221BEBCULL, 0x11A313BACAC7DC79ULL, 0xED275F30E29C9ABFULL
        },
        {
            0x6C0FFC1B5EF1B8A6ULL, 0x211C220C5BCFC598ULL, 0xAA240BFD52FC8797ULL, 0xF26BAD24C41CE1BAULL, 
            0x78E50B27942A9A1EULL, 0x34D12C98A5389ECDULL, 0x72B1AD891C06B103ULL, 0x6D500F8617484A50ULL, 
            0x12A86080C6D924F9ULL, 0x3D5C0602E3554D00ULL, 0x614755E9D9C0C1AEULL, 0xA2D539B7EF4AECE3ULL, 
            0x8C9213582A1EA07FULL, 0xE26CF106FED24AD6ULL, 0x6AB97BF484CB336BULL, 0x3132882BB5D9E511ULL, 
            0xA3C3428B90CBC79FULL, 0xE26B2B7B625EBE57ULL, 0xCCE405C1D96C24D2ULL, 0x84CBB6C1F2E79E33ULL, 
            0x8B9E66EFC5D65C81ULL, 0xC022A18F269D23F5ULL, 0xCB06ED9FDDBA15F4ULL, 0x6A394E4722A3EC39ULL, 
            0x21E86F34EE5B71EEULL, 0x262F4710C51CEF77ULL, 0x35AD86E3A2C2448DULL, 0x3BE2A44EAE4B4E15ULL, 
            0x8765B7831EB0B3C4ULL, 0xBA395261B74F6254ULL, 0x69E71EA2D3857319ULL, 0x0094EAFB5CF8C392ULL
        },
        {
            0x7990FB4E8AB17B7CULL, 0xCDE2CB0243BEBBF7ULL, 0x7F882AAFC218E43AULL, 0xB2375813C88F2A42ULL, 
            0xCE93CF1CC3AB6FACULL, 0xA850E1B2A78E7C5DULL, 0xEB1E53219C917019ULL, 0xDB2AFC0AF14D9D11ULL, 
            0x41EFEAD0A990C4C8ULL, 0x90782EDD769D3347ULL, 0x525976C1E970DB0CULL, 0x62224ACC3F4595C0ULL, 
            0xA3F20A8B9C89D803ULL, 0x0769A2A451F319CBULL, 0x6752E372E7AAD971ULL, 0x522D420DE70D6772ULL, 
            0xFEC51DBCA1E5CBFFULL, 0x8BE7DEC63D06357AULL, 0x8DCBFE3038CED13DULL, 0x4E7C55C5F717B1C5ULL, 
            0xDB62B7A0CD5F2DD2ULL, 0xF981870AAD43458EULL, 0x42CAFA1B7A72FAC2ULL, 0x7752B210F96B3FB6ULL, 
            0xC11A23FCF87BFB06ULL, 0x5F9B7E73D897EA56ULL, 0x6DB12378583F03C6ULL, 0x1700FAC78F6A73CAULL, 
            0x934D7E7AE42971C8ULL, 0x6B9B37A624D45AB0ULL, 0xB6FAFCAB0EE49CFBULL, 0x8D7D963346A6B3E4ULL
        },
        {
            0x0C1A7F22FEF825A9ULL, 0xE902E056E65B9E4DULL, 0xF9F81FD9DDA79F2EULL, 0x485795D4FE832062ULL, 
            0xF44F122B49984DB1ULL, 0xE50686171128555AULL, 0x0F869F234C81D73DULL, 0x03A1D220625A8A0FULL, 
            0x2C76076F92297325ULL, 0xDBFA6B2A502C8BB4ULL, 0x209B9B32C67039CFULL, 0x638ECC3D3A6011ABULL, 
            0x0E5EDD39F4629C6CULL, 0x555EA4A88EC1CA95ULL, 0x291456F2298590C3ULL, 0x0802BDDCC79AECE8ULL, 
            0x5C8742F669A6CCD0ULL, 0x2AB909CF73BD0B96ULL, 0xACD79ABCFA0FE226ULL, 0x0C8052B77A6461E8ULL, 
            0x6062A9A0686E51BCULL, 0xDEF06D68041C87A6ULL, 0x3F7700B04ACF7FF6ULL, 0x8669183030D3D478ULL, 
            0xC8E7D15F06720F57ULL, 0x5CADF0E7BFCA5DB7ULL, 0x066C08390AB8372EULL, 0x5CC65C385BBBB689ULL, 
            0xD01F0AC171E9543FULL, 0x4DF77E5BB8F73245ULL, 0x69B59017A487CB4CULL, 0x0955362D744EE983ULL
        },
        {
            0xB6111146ADCD9006ULL, 0xDC55BC9AC8DAE423ULL, 0xA33F654EAA500B34ULL, 0x8A23AF92C3A9DE21ULL, 
            0xEF4FB86DA9BD1C0AULL, 0xEB32F98AA136974DULL, 0xB7A7161FB911147DULL, 0xE6CF34D85A945B6EULL, 
            0x8B0AF3AE5F50FF5CULL, 0xC92E1F5A32AF2FB7ULL, 0xA5502B9EBD6C8823ULL, 0xFD2D892B8E25FDD3ULL, 
            0x48F299CE4E2F31D3ULL, 0x404F59EFA4FEB4A1ULL, 0x77BDA731C8079E3AULL, 0x27BF7721611FD745ULL, 
            0xD762968620EB161AULL, 0xAA9810C8EEBC7EE1ULL, 0x206D6BE2D02514BCULL, 0x617150FDA89C4143ULL, 
            0xCCACDE07FCAB11D2ULL, 0x1C02E5CE4851CD5AULL, 0xFEFD2DAE8F646F28ULL, 0xBC29EFDF721B100CULL, 
            0x8B20CE4234BCCB7CULL, 0x28B5C345FF480CC9ULL, 0x5C5F545DEE1E7BF6ULL, 0xF17F70F787AF9184ULL, 
            0xAE15D8D725F83321ULL, 0xC8A489392E2F6621ULL, 0xD1226FC47102A621ULL, 0x167581BDFC559EEDULL
        }
    },
    {
        {
            0x140392A024AF0D39ULL, 0xE0F6377FFB81AA66ULL, 0x8B37568CE870FC02ULL, 0xC701CA513DAB9AC5ULL, 
            0xA07D885E0353CEDAULL, 0xD123FAC7B75A1B35ULL, 0x23BA15AE796A7CB9ULL, 0x0CDC0607D57C96B5ULL, 
            0x3058A5F8952AC290ULL, 0xFE4EE8E7B9C0A959ULL, 0xD0E1FD0CED521359ULL, 0x3E7F51B0C9541D5EULL, 
            0x061128F4C0E20ACCULL, 0xC0DE5AA6F987047FULL, 0xFF555ECD46A7E844ULL, 0x851BC07C89847E31ULL, 
            0x55E7F229EDD8A8E1ULL, 0xFD6EE2E427A4A661ULL, 0x29943092586C535CULL, 0x6A6CD710985285E9ULL, 
            0xEA58C31DAB792FF9ULL, 0x70B8F06DFFC52AD4ULL, 0x97EDF607C2A50FDAULL, 0xAEC49CDBD62DDAF8ULL, 
            0xC4DA83935CC002FFULL, 0x938D883EFE10C5AFULL, 0x3A3107F8443E2EE6ULL, 0x7EB26D3B5FD4119DULL, 
            0xE564E1A062CEDC20ULL, 0x37C480575B92B7B0ULL, 0x1743B19BB18CEAE7ULL, 0x962A69E9AEDB0BECULL
        },
        {
            0x5E65F47E78FA5E0BULL, 0x5C5F3402E22B3F74ULL, 0x17F262CE7C933C6CULL, 0x44971AD6E46D9FEBULL, 
            0xD20EB9F6B450DFE9ULL, 0x9D79EAF99CAF4AFFULL, 0x41EF857E225DAF50ULL, 0xB2621BE33F3C8432ULL, 
            0x9CB030157D5B8A88ULL, 0x21EA5BA391B2DF55ULL, 0x76083C6492937D10ULL, 0x5FD1833C16D99BECULL, 
            0xE54987784CC16383ULL, 0xC33BBCF820580C88ULL, 0xD87B20BEA9D259F1ULL, 0x8AE35EAB6536AA11ULL, 
            0x20F6B27D3697F504ULL, 0x97FFD64C1B725B6EULL, 0xD847AADD76C80497ULL, 0x5F996A34C5224378ULL, 
            0xC590BE029D058299ULL, 0xA861ECB1CE12D920ULL, 0x8FEA6DA830AA5D83ULL, 0xB6138889FB065EB7ULL, 
            0x0579525EDA38005FULL, 0x6D33C21F0BE41D36ULL, 0x004F5C632A10766BULL, 0xD31ED1E09A869490ULL, 
            0xFE9E55E9A460FE65ULL, 0xF574C37B6BFB0645ULL, 0xBDAD60288082C559ULL, 0x1FE4FDBF7787DC63ULL
        },
        {
            0xD4F3C1B144C28DF7ULL, 0xBF2EE7C1D0B71D4FULL, 0xD608B806BC30BF96ULL, 0x53D55D8916D5BF87ULL, 
            0xCBA70F66B679BFCBULL, 0xD5A6850A9CA27781ULL, 0x9E04574E14D828EBULL, 0x3A87C202134F55E5ULL, 
            0x7A3DEABCC135FCC2ULL, 0xD48EE4F682C793C6ULL, 0x20D719C040ACFD16ULL, 0x798E7794668E0397ULL, 
            0xB7B6D6EC1B398448ULL, 0xCD38D335B56425FCULL, 0xB1C2D570E69E8C7CULL, 0x31297B3DB2D33815ULL, 
            0x17776AF938E2E839ULL, 0x73D07AB2CCCFAACBULL, 0x43CBE9AB326D7CD4ULL, 0xBC1508F69B2B7386ULL, 
            0x0E38C3C570F3E1A9ULL, 0xDB7D1F9C4AFF2638ULL, 0xFA33B473E2D07958ULL, 0x5C334B3A5CC99D08ULL, 
            0x3347D2EFA4BEED7AULL, 0xC0FCEEF778D1A0D5ULL, 0xDBD6D31F4191EDA9ULL, 0xB9D9622D4640156BULL, 
            0x266F38690E7EE394ULL, 0xE8D217FE0624AF3FULL, 0x698E6FD168C37B0BULL, 0x0B87E01C1C52F371ULL
        },
        {
            0x0D511B6509827009ULL, 0x5448D2723FBEFE55ULL, 0xAD81B5F363879F29ULL, 0x1DC43AC9C6682C66ULL, 
            0x726B29FD0C50F5A1ULL, 0xBA978FB2267D9537ULL, 0x142B23340D87D77DULL, 0x7FD976DAB2B790A9ULL, 
            0xE355A240C800BAE6ULL, 0xAC99D089AF66E067ULL, 0x5696E1196BD37D4BULL, 0x63D17F4DE41A73D5ULL, 
            0x2DAC523A1E73394EULL, 0xA8C96FF6005E8FDAULL, 0x94C7F390A6A40BC3ULL, 0x769EB0FDCAA3F738ULL, 
            0xF06244431EBDFD0EULL, 0x3B862D6968BE5BD7ULL, 0xA4E9FE5070B6B2F5ULL, 0xAB16AA34D34EB336ULL, 
            0x9327DF8056B80FCAULL, 0xAB0229BF6BCBBB01ULL, 0x7827855833A02EF6ULL, 0x75C654A4A5EAB750ULL, 
            0xBF5D1E40766720CDULL, 0xFE3B9EB5DC06E00BULL, 0x105B8191DC0A2B22ULL, 0xB54B73C1EEF2D4C2ULL, 
            0x0B209428E51B0F3EULL, 0x8A08DB1E491CBECEULL, 0xEEEE1490FD8E84D3ULL, 0x5977D57187E3086DULL
        },
        {
            0xDBA87977DD6A601AULL, 0xBAF25E639A63E7E3ULL, 0xE59605FB09D9C6E1ULL, 0x95FE95791FE37F77ULL, 
            0x4C53998C1260BE25ULL, 0x1FFE4C7E0EF7DBE6ULL, 0x0D0CB7FE53CC4EE5ULL, 0xD4321050527BB74FULL, 
            0x26D2943B464E1F65ULL, 0x4E8CFB7E5C5C7954ULL, 0xAA8DE59F2A348FC5ULL, 0x92781249D12046E8ULL, 
            0x53C1AE4222B387CEULL, 0xFB316CEF1B2F8ECCULL, 0xB4E9A8B6014A1940ULL, 0x62A5501D3C5E9775ULL, 
            0x325871717F69A0F5ULL, 0x774BB9E3C6EEBD33ULL, 0x11144552742BD442ULL, 0x3F4EAAFF9005461FULL, 
            0x27A810DA51F2A7B1ULL, 0x42CF102EB6A2544FULL, 0x039DB55AB14C1656ULL, 0xF5AFFD1E8A12362FULL, 
            0x217F9D242E215D13ULL, 0xDC8ADDD725C396E6ULL, 0x287BC94F4D915306ULL, 0x5A24C26B8A234A39ULL, 
            0xEF340BC9AAF4A07EULL, 0xB25EB747F117643DULL, 0xC781551E0186F060ULL, 0xDEDCED096A3C2725ULL
        },
        {
            0x77BEC588C8311777ULL, 0x1033CBF6A1BF5D2BULL, 0xBC2A27BE6A12B024ULL, 0xCE08EABFC692E455ULL, 
            0x85A80253DC5B8441ULL, 0xB65FEFE26ED0F309ULL, 0x8C3C3F13AA62F518ULL, 0x71A6316E1F71D5EFULL, 
            0x27FBF8E96FC5AF36ULL, 0xDBBAF61AE8C126B5ULL, 0x1B926944CC0305D3ULL, 0xBA6F777572CB8106ULL, 
            0xBCB3F28AC563721DULL, 0xA650114714604EC6ULL, 0x4B7C514C2DD5ACB0ULL, 0x68AB1D50EB3CB871ULL, 
            0x1E35AFDB8A83BB30ULL, 0x8D8BCA9B4FA47C5DULL, 0xDCBA392B0C9F0BA0ULL, 0xC1DF1371F26D5C50ULL, 
            0xC09FD0EEC81A62CAULL, 0x4344197A62372593ULL, 0xB2227E995AB374EAULL, 0x39C9EF2024D1A79CULL, 
            0x198F7084A91E7AD1ULL, 0x06E09BF710EC63A5ULL, 0xE6F464E7F73BA229ULL, 0x8A22256CADBB9D2BULL, 
            0x5EFBA8AFBA478EC5ULL, 0x1101057FC95321FAULL, 0x7B32BC1843256E17ULL, 0x0CE5ACA5825BAD34ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Antares::kPhaseHConstants = {
    0x7C3CCE62987476CCULL,
    0x5F36BF69DE6C9216ULL,
    0x8BDFE977EB8CA6EAULL,
    0x7C3CCE62987476CCULL,
    0x5F36BF69DE6C9216ULL,
    0x8BDFE977EB8CA6EAULL,
    0x59F4D4883D313CEFULL,
    0xA6846FB4355AF3ABULL,
    0xBB,
    0x59,
    0xC6,
    0x99,
    0xF8,
    0xE2,
    0x05,
    0x38
};

