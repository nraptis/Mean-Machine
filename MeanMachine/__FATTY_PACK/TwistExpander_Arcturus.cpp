#include "TwistExpander_Arcturus.hpp"
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

TwistExpander_Arcturus::TwistExpander_Arcturus()
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

void TwistExpander_Arcturus::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xEC2D2C9F8DD31F8DULL; std::uint64_t aIngress = 0xCDA4AEECA291AD70ULL; std::uint64_t aCarry = 0xACD705EC9D65161BULL;

    std::uint64_t aWandererA = 0xA437A3CA163E0B7AULL; std::uint64_t aWandererB = 0xD23FE23FBD52EE78ULL; std::uint64_t aWandererC = 0x8E3A9B69A56FF360ULL; std::uint64_t aWandererD = 0xF0E488055AAD7450ULL;
    std::uint64_t aWandererE = 0xB8C51345868D9913ULL; std::uint64_t aWandererF = 0x8FCB9DF951608BCFULL; std::uint64_t aWandererG = 0x838A28A3B4839B73ULL; std::uint64_t aWandererH = 0xB6BCDCF42E121323ULL;
    std::uint64_t aWandererI = 0x8E66D84CD619D711ULL; std::uint64_t aWandererJ = 0xD943AB31C1701A87ULL; std::uint64_t aWandererK = 0xAC4AA302192BECF7ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 17884826965977466227U;
        aCarry = 18235812813767208348U;
        aWandererA = 15718589300025884937U;
        aWandererB = 13561578264835878360U;
        aWandererC = 16604132588735315909U;
        aWandererD = 14016321070562957363U;
        aWandererE = 13726294029174319940U;
        aWandererF = 14831652867932156684U;
        aWandererG = 17264688389337244870U;
        aWandererH = 10883293214241933250U;
        aWandererI = 10272865789284408153U;
        aWandererJ = 16055323604769186859U;
        aWandererK = 13719623552743892367U;
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
    TwistExpander_Arcturus_Arx::KDF_A_A(pWorkSpace,
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
    TwistExpander_Arcturus_Arx::KDF_A_B(pWorkSpace,
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
    TwistExpander_Arcturus_Arx::KDF_A_C(pWorkSpace,
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
    TwistExpander_Arcturus_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Arcturus_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Arcturus::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0x8B29D9A3574214ADULL; std::uint64_t aIngress = 0xA625CEAF43FFD34BULL; std::uint64_t aCarry = 0xD97B8256295AE7B3ULL;

    std::uint64_t aWandererA = 0x9EEAB7D324043F6EULL; std::uint64_t aWandererB = 0xC03EC2E8D13AB050ULL; std::uint64_t aWandererC = 0xA5E11478626BDC7AULL; std::uint64_t aWandererD = 0xBF7AD56DDE9842A7ULL;
    std::uint64_t aWandererE = 0xB43EF07CEE37DA7EULL; std::uint64_t aWandererF = 0xE5F74C908EDAD12AULL; std::uint64_t aWandererG = 0x997768C7DE55FFB0ULL; std::uint64_t aWandererH = 0x92DCBB73DC450CAFULL;
    std::uint64_t aWandererI = 0xD64833006461366EULL; std::uint64_t aWandererJ = 0xF437227A08638A19ULL; std::uint64_t aWandererK = 0xF68DC9513F51A104ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 16525319069212959626U;
        aCarry = 16951468791352236888U;
        aWandererA = 17040106315136528962U;
        aWandererB = 16324016119441929213U;
        aWandererC = 14131259759653271365U;
        aWandererD = 15763359558508829289U;
        aWandererE = 13415272405391232235U;
        aWandererF = 16414453479014048771U;
        aWandererG = 11943291514589037602U;
        aWandererH = 15257233140870751778U;
        aWandererI = 15255015019566265609U;
        aWandererJ = 14022617083581718959U;
        aWandererK = 17973534388322718062U;
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
    TwistExpander_Arcturus_Arx::KDF_B_A(pWorkSpace,
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
    TwistExpander_Arcturus_Arx::KDF_B_B(pWorkSpace,
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
    TwistExpander_Arcturus_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Arcturus_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Arcturus::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xC9740E0C3FB1228EULL;
    std::uint64_t aIngress = 0x9882C5AFE36411B6ULL;
    std::uint64_t aCarry = 0x9D3F3D534FDA511EULL;

    std::uint64_t aWandererA = 0xFC4F4CDEC76A63F1ULL;
    std::uint64_t aWandererB = 0xF57C398566C0154CULL;
    std::uint64_t aWandererC = 0xC09FE7244FF7DD22ULL;
    std::uint64_t aWandererD = 0x81848FDC8A74E9D0ULL;
    std::uint64_t aWandererE = 0x95298352B5DEEE17ULL;
    std::uint64_t aWandererF = 0xCD127FC15773D205ULL;
    std::uint64_t aWandererG = 0x8CCC95E6D84052A7ULL;
    std::uint64_t aWandererH = 0x838FE96461B9379EULL;
    std::uint64_t aWandererI = 0xA06AD94F09DFEFBFULL;
    std::uint64_t aWandererJ = 0xC891A74430BC976CULL;
    std::uint64_t aWandererK = 0x838B475D480E75A1ULL;

    // [seed]
        TwistSnow::Aria256Counter(aSource, aSnowLaneA);
        TwistSnow::Sha256Counter(aSource, aSnowLaneB);
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneC);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneB);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneA);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneH);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneG);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneD);
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
    TwistExpander_Arcturus_Arx::Seed_A(pWorkSpace,
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
    TwistExpander_Arcturus_Arx::Seed_B(pWorkSpace,
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
    TwistExpander_Arcturus_Arx::Seed_C(pWorkSpace,
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
    TwistExpander_Arcturus_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Arcturus_Arx::Seed_E(pWorkSpace,
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
    TwistExpander_Arcturus_Arx::Seed_F(pWorkSpace,
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
    TwistExpander_Arcturus_Arx::Seed_G(pWorkSpace,
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
    TwistExpander_Arcturus_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Arcturus_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Arcturus_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Arcturus_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 10 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1851 / 1984 (93.30%)
// Total distance from earlier candidates: 16701
void TwistExpander_Arcturus::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 101U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 664U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1098U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1968U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 50U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1902U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 639U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1167U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1456U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 684U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1724U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1841U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1885U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1815U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1371U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 620U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 490U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 326U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 256U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 723U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1444U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 891U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1054U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 711U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 2019U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1215U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1786U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 258U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1982U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1850U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 930U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 488U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1123U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1243U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 34U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1637U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 99U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1577U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 2004U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1479U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 51U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1331U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 925U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 154U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1917U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 333U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 748U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1816U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 83U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1734U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1771U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1117U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1903U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 622U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1038U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 743U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1730U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1177U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1498U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 561U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1708U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1415U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 313U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 959U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 648U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 90U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1045U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1195U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1406U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1199U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 973U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 918U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1370U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 788U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 646U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 708U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 296U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 13U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 605U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 540U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1466U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1202U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 645U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 519U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 180U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 678U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1289U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1134U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 654U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 875U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 629U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 425U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1735U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 148U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 737U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 2027U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1431U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 591U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1409U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1183U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 632U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 232U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 124U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1471U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 160U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 963U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1527U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1950U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 282U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1362U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 371U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1428U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 728U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 701U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 933U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 638U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1610U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 150U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1667U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1440U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1325U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 582U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 389U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 894U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1548U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1818U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 426U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 889U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }
}

void TwistExpander_Arcturus::TwistBlock(TwistWorkSpace *pWorkSpace,
                                       std::uint8_t *pSource,
                                       std::uint8_t *pDestination) {
    TwistExpander::TwistBlock(pWorkSpace, pSource, pDestination);
    if ((pWorkSpace == nullptr) || (pDestination == nullptr)) { return; }
    std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    std::uint64_t aPrevious = 0xE31290B6E392F274ULL; std::uint64_t aIngress = 0xD8BA5ADD33A55CE0ULL; std::uint64_t aCarry = 0xA94AE3D003440D8BULL;

    std::uint64_t aWandererA = 0x86CCA48A66C9901FULL; std::uint64_t aWandererB = 0xBF003B575D457EA2ULL; std::uint64_t aWandererC = 0x9EB8742736387A1EULL; std::uint64_t aWandererD = 0x88E1ACB810E2F3F4ULL;
    std::uint64_t aWandererE = 0xDEA67F851BDBF5C3ULL; std::uint64_t aWandererF = 0xEA3F41330715EC59ULL; std::uint64_t aWandererG = 0xB06108EA1255FB9EULL; std::uint64_t aWandererH = 0xB6359932DC72D5E8ULL;
    std::uint64_t aWandererI = 0xB9F5EB7DA2F293A8ULL; std::uint64_t aWandererJ = 0xF6568F783B0EFB36ULL; std::uint64_t aWandererK = 0xABB7C415B56BA34CULL;

    // [seed]
        aPrevious = 15931893714385343814U;
        aCarry = 18323947267008050869U;
        aWandererA = 11875755840079173275U;
        aWandererB = 12327535895694485102U;
        aWandererC = 13860058650023142521U;
        aWandererD = 15513913005016404587U;
        aWandererE = 15744276560583387985U;
        aWandererF = 14006733307827878484U;
        aWandererG = 13101826393006046741U;
        aWandererH = 15079541560629287583U;
        aWandererI = 16378195491233022198U;
        aWandererJ = 13397813901282304737U;
        aWandererK = 11869016982854046645U;
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
    TwistExpander_Arcturus_Arx::Twist_A(pWorkSpace,
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
    TwistExpander_Arcturus_Arx::Twist_B(pWorkSpace,
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
    TwistExpander_Arcturus_Arx::Twist_C(pWorkSpace,
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
    TwistExpander_Arcturus_Arx::Twist_D(pWorkSpace,
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
    TwistExpander_Arcturus_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Arcturus_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Arcturus_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 10 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 5004; nearest pair: 494 / 674
void TwistExpander_Arcturus::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2622U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5147U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 770U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3306U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2483U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 8129U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5086U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5275U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7210U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6553U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7064U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6392U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2207U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2630U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3429U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 985U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 999U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1561U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 250U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 90U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 231U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1972U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 176U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1729U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1991U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1640U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 403U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1216U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1915U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1643U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1577U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 743U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1100U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 842U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 787U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1433U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 10 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 4986; nearest pair: 516 / 674
void TwistExpander_Arcturus::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7563U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4797U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3039U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7810U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7884U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7029U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7628U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6498U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1815U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6970U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2874U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6407U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2321U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1195U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3578U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6044U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 218U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1020U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 830U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 467U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1048U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 27U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 472U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 795U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1240U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1214U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 915U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1627U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 583U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1490U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 82U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1411U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 459U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 29U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 170U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1040U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Arcturus::kPhaseASalts = {
    {
        {
            0x33696CBDA04E003AULL, 0x0D675D6F084094D9ULL, 0xCFFB7DA22EFF853FULL, 0xECBA151BCE247CD1ULL, 
            0x727FA3A0FFA360E4ULL, 0x2E86128612AFF181ULL, 0x33DE5A8B5E1F52E6ULL, 0x9B64B254C00B2A9EULL, 
            0x77D5AB7C217E81DBULL, 0x33919B8F0E682031ULL, 0xFA3EA694BBB7369FULL, 0xFD0CBFDCCE583407ULL, 
            0xA7AA62FDFD9642DBULL, 0x0D56F950D722AC38ULL, 0xBEA25B5117E32D2AULL, 0x289E9B146CF720F4ULL, 
            0xC6409807AC30BC73ULL, 0xE02228EB059F09BDULL, 0xA606C4F55F9A66B4ULL, 0x1A5F737851CB7259ULL, 
            0x31A806D9E986A0DCULL, 0x0AF6BC2AAC4BD9E7ULL, 0x79FD00E3FB49CBE6ULL, 0x568100BB8A94045DULL, 
            0x2FF9C88A3AB24D67ULL, 0xFD67D382C2B3C088ULL, 0xFE39BD6AB9593077ULL, 0x465DE73E25F8516BULL, 
            0x066CC88346BAD51DULL, 0xF72C657D9B40F6A8ULL, 0xB2D32D27B34FAB07ULL, 0x21F06A76AD65603DULL
        },
        {
            0x1750360EB9582B88ULL, 0xF983C64119FA58ECULL, 0x496FC12C572D1464ULL, 0x00A77C8D5C2408EBULL, 
            0x7BB3F937ACE05EA6ULL, 0x2E449C382F23CD20ULL, 0x43F138C8D0EDDD09ULL, 0x0651D38FD6B9D92AULL, 
            0x97FD14457B2409E7ULL, 0x9F36FBD008AC7959ULL, 0xEA77DA6071B5E44DULL, 0x80C2626F9B1A01B0ULL, 
            0xEEC44AB0C83B4CEEULL, 0x660C1D4151298D62ULL, 0x8134BEEA694CF83CULL, 0x23D9DD21EB2BEB73ULL, 
            0x0A7C80CA029B2D1EULL, 0xCF9F7459D3C6270AULL, 0xDB21BDEF5DA5517AULL, 0x3C08972FAB0ABD3DULL, 
            0xEDF929DB37621461ULL, 0x9DD8F19620C52694ULL, 0xE7958ADCC07D5D46ULL, 0x28EEF5F204DEC64AULL, 
            0x8EFE69367B896A66ULL, 0xAB21528B715C5E1FULL, 0x4D868168D2A9B582ULL, 0x521467DA8E695BC5ULL, 
            0xE7F8448AE110E782ULL, 0x6F2FC947CBE81E71ULL, 0xA27302F93726664EULL, 0x2ACAFAFC4D70CB82ULL
        },
        {
            0xB9D3FE486A19FBE1ULL, 0x5922199FCAEB73CDULL, 0xB34BA21CD8462D50ULL, 0x5D86FB7356EF3C9EULL, 
            0x61B5E8976560D575ULL, 0x56EE6A6992017C10ULL, 0xF139F7B462FB2C30ULL, 0x726E46C54AA6D157ULL, 
            0xD1ACBD93BEAE41CEULL, 0xE40B0D2DED1E517EULL, 0xB98070DC0BCAA6EFULL, 0xD953979E0B389A98ULL, 
            0x79A912901732EA21ULL, 0x1E35418277B62D28ULL, 0x5BF88C4CB1EA61CFULL, 0x394CF862E92F6CE1ULL, 
            0xB974C3C0D779065AULL, 0x0DE577E56838E74CULL, 0xB226B3A54E173828ULL, 0x31758BEFE32030B8ULL, 
            0x160BB0376AF3AE37ULL, 0x0F4FF86D1A6D2549ULL, 0xD1D00F21159230FAULL, 0xD099931F720986BBULL, 
            0x6BD733613383F7C4ULL, 0xAD16A9243750EF38ULL, 0xB1372FEF6A858A5DULL, 0xE632E64A08AD9032ULL, 
            0x0A1FCE5D4D9E67C1ULL, 0xD9BA0EDC87E572D0ULL, 0x367E371E17BC1843ULL, 0x82F7E66C5ECF615FULL
        },
        {
            0xE3A4C986D7CC6A8FULL, 0xFBED3AFE88C71189ULL, 0x523EA30F055967C0ULL, 0xE6C9CF53374B5914ULL, 
            0x5D0ABE33DFE6215FULL, 0x1388674727F358C3ULL, 0x44CCD774E6DA2517ULL, 0xAE041749A849C57AULL, 
            0xCED17CE38E6C6E51ULL, 0x7F891910A49D8A78ULL, 0x4A5982D8CAB42C6CULL, 0x723759AC4A06F651ULL, 
            0xD8D4085CB94557C8ULL, 0x8C17907B888B459CULL, 0x7031EEE0312331EAULL, 0x3ADC9F6A53432E57ULL, 
            0xCF7544E1DADA2A04ULL, 0x96DF69C2C94BC6D1ULL, 0xBF84C68C6E6E73D2ULL, 0x48DBF908086E2460ULL, 
            0x12ED605536F7BCE8ULL, 0xCBAA5A71A35E0C27ULL, 0xA31E54ACE8309DEEULL, 0x45A2B92722776AABULL, 
            0x9E331A23A4D9A609ULL, 0xF9DFBABA5FFE274CULL, 0xFFFC257CCCD08BDCULL, 0x12AE8C1477BC3CB2ULL, 
            0x828408DB67DF8C24ULL, 0xB56683C6AE3705FDULL, 0x5A739A1102A09040ULL, 0x655D4D93A23AEE43ULL
        },
        {
            0x4CAAE97C05BE739CULL, 0x51CEEB6ABE22542CULL, 0x82F21D864D28954AULL, 0xF6ADAF2260B1006FULL, 
            0x5D0DDD0E40EB5462ULL, 0x0D87D110B63A9485ULL, 0x04C7FA92B59E8A8AULL, 0xE4202DCE1F7A270FULL, 
            0x5CA328181530C48BULL, 0x5240AFA2B1559F01ULL, 0x55396D4E21BD238AULL, 0x135F3EC202B16A72ULL, 
            0x7FCBF6CB1A4674D4ULL, 0x4D94D2103996AE0EULL, 0x5C3684060BEC0193ULL, 0x265BC230EE320F73ULL, 
            0x7B8F42E0CF5224F5ULL, 0x29B4DE60A63BA525ULL, 0x50A7D172147E36B8ULL, 0x009251E178D7C3BFULL, 
            0x235CC83DF80D38DAULL, 0xB31CFB1B414FAC7FULL, 0xD4FC18A4CA628B52ULL, 0x7D9ED5C2A9E8D2A7ULL, 
            0xF25A8C6A67B0490EULL, 0x06B83813F744EFF7ULL, 0xD2773D26830A8672ULL, 0xFBA9D798A9DBC3E2ULL, 
            0x551F42DDF15F195CULL, 0x87597A7B991D34EEULL, 0xC270DCA4FEB27AE5ULL, 0x7727374B0BA7615DULL
        },
        {
            0xC4091E756FA77185ULL, 0x85A05DBAACBACD69ULL, 0x5C8971A7ABC7CD77ULL, 0x549A0CD7187C8FE1ULL, 
            0xAA6B9C7B26B46DF1ULL, 0x21C1248A5E88AF12ULL, 0x8FF3A6ACF2B50079ULL, 0xAA97C7F57544BC90ULL, 
            0xED471730329F57BCULL, 0xAC1660F234C480BBULL, 0xB5B0D22043E812B0ULL, 0x9384F5ACB51A3C5AULL, 
            0xB655D42C3E76076CULL, 0x4D653AAFC973B207ULL, 0x8836999008E2E5CDULL, 0x5DCD751E16B37ADCULL, 
            0x627D625E25EFD656ULL, 0x1E5B4CFA6CF964C7ULL, 0x2726ACCE70C74D4DULL, 0xEA674E690B0008AFULL, 
            0x22A1FE40CBDBFD1EULL, 0x76D431A5F7F31BBCULL, 0x6D661F6D1ED69D08ULL, 0x46B3F77DCC42022CULL, 
            0x1DEBE12C8B8F0B8AULL, 0x34A4FB25BC1E8333ULL, 0x89B69B98DD5B2C96ULL, 0x1F34CE62C8A1F14AULL, 
            0x321453B3CB28D3ABULL, 0x65B2EB195DEEC519ULL, 0x72B8FF331E9DCF05ULL, 0x272848D901C65D61ULL
        }
    },
    {
        {
            0x8D5CC1B5166DE042ULL, 0xCDF22637CD8AE339ULL, 0x0AA235FC1FB13260ULL, 0x17725D5300386DFDULL, 
            0x7A455E8A9DDFFA22ULL, 0xD5F840D084D8B210ULL, 0x2BEBA675723D0551ULL, 0xF91677A7EA767F98ULL, 
            0xA5C6BD3492664F57ULL, 0xB7EF5E37C4864DA7ULL, 0x1EC763D2C72906C3ULL, 0x61F84D341173CC25ULL, 
            0xCBF6A8DE26B78D5EULL, 0xBA8D4E1ABCA1CAF5ULL, 0xCDDBFF1B6DA25DC8ULL, 0x384F259A5D979232ULL, 
            0xD64A841073C67E1FULL, 0xA55790A0391095DAULL, 0x4A9CFF59DCBD1114ULL, 0x13BD59FAB2E46D85ULL, 
            0xA0A4F178206F85E9ULL, 0xBEE9D2820B30E159ULL, 0x88CF406E2A14176AULL, 0xAF8D4952F0376873ULL, 
            0xA6BA2CD045A6DC92ULL, 0xA60227532349B708ULL, 0x5DD9EECAA963DF95ULL, 0xFFFABD7692DDFAA1ULL, 
            0x299B223F1692F46DULL, 0x8702891C7B6649B0ULL, 0x56E4BADD8301760EULL, 0xFD93CCD2619CDA54ULL
        },
        {
            0xDCF5CE0D1FA3C3F9ULL, 0xD6E6F96FF40CB717ULL, 0xA99871C474AA470AULL, 0x667CD28975B4BCC9ULL, 
            0xB41F48CF0AE08A30ULL, 0x91CC61F6CAF6895FULL, 0x797A15C3CD4FBC5BULL, 0xC375917535C8FD83ULL, 
            0x18E38498D3902F43ULL, 0xDB900D169B69E37EULL, 0x7989244A98F3E920ULL, 0xD87C644DC2027845ULL, 
            0x6EC0ECF6F391FA0DULL, 0xCFCD7BCB56B8C5D1ULL, 0x4497166D062747BFULL, 0xFDD8B643C5D5714CULL, 
            0xF42FFDC68EA31AE9ULL, 0x7CD00FE818E155EBULL, 0xCFABEE99E4A18696ULL, 0x75B943A068673BB1ULL, 
            0x71AE2E8CF936AEF8ULL, 0xAD1B5453E2AA2378ULL, 0xCDD547E9DAF99EE1ULL, 0x2467EB9DAB6FC466ULL, 
            0xABEDF2FBA8798410ULL, 0xEA182DA94864D279ULL, 0x5E9646BCEBE1B0E4ULL, 0x2FD5FE137DE35713ULL, 
            0x67DE8B01A6271805ULL, 0xD7116FFDFF00A8AEULL, 0xB30F77058A563CE2ULL, 0x2E8865FB88D7069DULL
        },
        {
            0xE1980297198649B4ULL, 0xC2790996D3A83434ULL, 0x6EC88D43D329247AULL, 0x82E529E4D988AC54ULL, 
            0x0C14E213164B719BULL, 0x8D3EB87219103623ULL, 0x9C5FD722154D1D7CULL, 0x01478C30D2E95480ULL, 
            0x591E010230D2393BULL, 0x48ED142D38A2D0C1ULL, 0xBEFA40A1159EA0FDULL, 0xD4B9B517C1B9EC24ULL, 
            0x537DC4A5046FD311ULL, 0xB996363B66B1E487ULL, 0xAE59C8C4FA1FFF6AULL, 0x236F5A9DCE309F2CULL, 
            0xF5150EF9E00EEB09ULL, 0x13C64703355DCAD8ULL, 0x3304B48730F3212EULL, 0xE3A95352B42CD630ULL, 
            0x336639E4D2802394ULL, 0xA53AC26311A64CE9ULL, 0x31F6F1FD132C68DAULL, 0x0323B22AB83DAB35ULL, 
            0xC6725709B30482AFULL, 0x5D65437C4BE442DBULL, 0xB0032470D6AE6FF0ULL, 0x00975C90693193C5ULL, 
            0xD8B7A0DA7E024FD2ULL, 0x3F26F575993F6DD9ULL, 0x84639666B5FDDEEEULL, 0x4F539B94187F706AULL
        },
        {
            0x2E64820F4E499946ULL, 0x43ECAAB7CBEAF1CAULL, 0xFBB82B5B939A80A7ULL, 0x034593714785EBE5ULL, 
            0xBFB1F563757F1130ULL, 0xEB0F2E4E954BFF97ULL, 0xCDF31DA33EC358C0ULL, 0xAA3B494C1EE3E484ULL, 
            0xF99F850B39181D6EULL, 0x8858FD31252E688AULL, 0x6E61484642D5BDCEULL, 0x83DC7B03C3FD8B6FULL, 
            0x8BB1F50B34DF4525ULL, 0xC4D827D3D95A78DDULL, 0x0AA35EB8C039F59FULL, 0x8CD06DA07BAA34ACULL, 
            0x3B680AE624F3B4EDULL, 0x96657719279F3FB2ULL, 0x8E50BD7C3AD7A71FULL, 0x3C3D050A1DCD6D19ULL, 
            0x6218E7F997FA3850ULL, 0xF795A4CD3A9335B9ULL, 0xF3F2DA08BC4FA9D9ULL, 0xE601180006E162D8ULL, 
            0xF73CA2465E1511F6ULL, 0x345D6E2709070157ULL, 0x4147B98C3C24771DULL, 0xF6284A4866CAB111ULL, 
            0x83C6A2F0C230DDC3ULL, 0x304D6E2B9AC6FC50ULL, 0xFF99B8C0122EB870ULL, 0x9E9EEA1E8BAD9AAFULL
        },
        {
            0x11575D7717D8CB96ULL, 0xBF06C320EC82BF34ULL, 0x420E5C9AA03B3E7AULL, 0x0955D1B87063A013ULL, 
            0x385AC3417EC3F708ULL, 0xA6112ED4828882DAULL, 0x3F602CE4C656412DULL, 0x497F7C65A95DC881ULL, 
            0x9BA65AB1A794E5EEULL, 0xEA4E65ADD65D11EAULL, 0x17326B7B09ABA178ULL, 0x539A428ECC7B0C34ULL, 
            0xA85F2780CC2169FDULL, 0xCC3EB012526D20EFULL, 0x4B1FDD53B22E7E0BULL, 0x2D29053B9BEF165AULL, 
            0xE9895D7FD557193BULL, 0xF6C7A32F9A76E818ULL, 0xC6F71804EFA490D9ULL, 0x76AB0F44B8B02B8DULL, 
            0x3DFA13273E99A118ULL, 0x931752B6A8586598ULL, 0x1877EE6562683392ULL, 0x2AA11D141EC97683ULL, 
            0x43645F49F50F3A27ULL, 0x8AC6739452C3FBDBULL, 0xC50FFD2706A3A992ULL, 0x334152831AB55EC8ULL, 
            0x6763ED347648585DULL, 0x4CF5D8E02CCD8F83ULL, 0x396F40AFD9145493ULL, 0x39CC2AD3EF29E196ULL
        },
        {
            0x2C03152D3E4B3E01ULL, 0x9AAECD07C5DA0542ULL, 0xCCAC1B0090A3CAD0ULL, 0xF6A4D03A76FE4DD5ULL, 
            0x0BAF9682FDFCD6CBULL, 0x92219B911777BA68ULL, 0xAEDDC9515985CE39ULL, 0x6C91E7D6A08EE0C3ULL, 
            0x48C8C1732CFD1676ULL, 0xC7981D978B47B573ULL, 0xCC4DE1F1AFEAAA73ULL, 0x807CCA581FFCD2E3ULL, 
            0xF54D1120290EDE9CULL, 0xAF26271910D50847ULL, 0xD671A81B274F3E3CULL, 0x1E495F3336FE18A2ULL, 
            0x331FCE709B39A4CBULL, 0xEECEB6F3FB8C49E6ULL, 0x43B7E04B3BD84898ULL, 0x91F187119E20A387ULL, 
            0xF6EB4A2893E42D7EULL, 0x2D28DC0B6B55F6B9ULL, 0xE5EB3B36A223F941ULL, 0x0669003C9FFBD420ULL, 
            0xCCEC29BFF8937158ULL, 0x6F923F04710EAE71ULL, 0x98954536EF92D0E2ULL, 0x00BDBE7AEE8C61A5ULL, 
            0xA776E89C5F65A0CCULL, 0x3F03AA060E1B74FCULL, 0x3F95FA64E080D975ULL, 0x10A7A6EB2291246DULL
        }
    },
    {
        {
            0xC2D68362B46551D9ULL, 0x706570BD59C7D9C3ULL, 0x1080B3160BC65257ULL, 0x2CA1B590895AB4F1ULL, 
            0x0820AF0724BD357CULL, 0x19B8FF111D14B9D1ULL, 0x46B488D0280B9CC6ULL, 0x5DD5DCCC5E2BA378ULL, 
            0x0E4477EDF0F87C3EULL, 0x960FF4F74C4224B7ULL, 0xB358A0602E240488ULL, 0x5FFCAD0438456A05ULL, 
            0x0C8C28483F67A039ULL, 0x94EE8C1BA5F7E270ULL, 0xF838CC8DA8850DF6ULL, 0xC57D3686061F63A0ULL, 
            0xCAA20F50538D05F3ULL, 0xC68A51229FC7F648ULL, 0x6172D97E5D3A2C91ULL, 0xE05ABEF56A0DB94DULL, 
            0xF5C660D31D1DE7DFULL, 0x5ED2528BAB726704ULL, 0x4CEA6F86F9115318ULL, 0x432EC2569C57797BULL, 
            0x7E16D97C1A570E96ULL, 0x14703F77B6ABD7C9ULL, 0x6BCFB766184ECA60ULL, 0xD4FBE27491DC6CBCULL, 
            0x5F13654E48F1ED6EULL, 0x307F1347BEF3E7B3ULL, 0xB349355F4F131B86ULL, 0x494F234424093711ULL
        },
        {
            0x977A6B92A5D4FCA8ULL, 0xA27C09EF4087B050ULL, 0xF850A27EFE2ED661ULL, 0x7FC20DE23AF341D1ULL, 
            0xEB65720FF2A87A7AULL, 0xA205428698F67FA4ULL, 0x901EC3577F408631ULL, 0xFC62CB7BA984B772ULL, 
            0xEF46AE8D21C561D8ULL, 0x5739AEF4427B26BBULL, 0xDE258017EACA5A0FULL, 0xFF37A953A34A1BBDULL, 
            0xCF90074B6CE79F43ULL, 0x245D930FBC79631AULL, 0x42A445200D63C8D6ULL, 0x68FBEF6CF7C1748FULL, 
            0xC81C024E47A08F71ULL, 0x2E24FD46C7EE6614ULL, 0x43E7449A8EC9AE18ULL, 0x92DB44FE9C67CB22ULL, 
            0x1663558552B65780ULL, 0x56E5603644C36AD2ULL, 0x03AA87A3956DFA84ULL, 0xF381318FCE9DD400ULL, 
            0x978DA34D3D7CA187ULL, 0xA69F8997580C14F8ULL, 0x8F0BB4F7D660C593ULL, 0x8C03D88A7464A03FULL, 
            0x49641C3D9E068595ULL, 0xB58AF720DAD49FA4ULL, 0x3C6A83AB9464328FULL, 0x19AC3BD35A99845AULL
        },
        {
            0xD7A738B572056886ULL, 0x3EB017E4598CB76FULL, 0x9626D019E99F476EULL, 0x209F43FD58FB08BEULL, 
            0x8D59EB259AD8053AULL, 0x69E0CDE50FB7D6D3ULL, 0xE0F754D3D1BE9D49ULL, 0xD7FF8EE685B46AE1ULL, 
            0x3A56C1737BDD2D45ULL, 0x6606C4BC7F98069BULL, 0x9A13763158DAC370ULL, 0x071686C6560D8527ULL, 
            0xFF8E3CE6564CC5D1ULL, 0x5C75DDBDB719881DULL, 0x754046FEDB2F21F8ULL, 0x9F4637AE6171E0D9ULL, 
            0x0383D8877D5F6752ULL, 0x7AF12A299D964024ULL, 0x87F1A2FA8C1891CAULL, 0x87B9FF5589AB1A2EULL, 
            0x4D57B64DF5D591D3ULL, 0x4AC23B79F750E24CULL, 0x54D84F2E7E606EFEULL, 0xDCD9B82310ADEEB7ULL, 
            0x5D2935A58F1DC0ACULL, 0x8329F5BA5F19B614ULL, 0x8C8D3DBF299FD933ULL, 0x8E8057A0546C262CULL, 
            0xCEB65393A46030B5ULL, 0x5B46DDA1F6F8633BULL, 0xFBF403FE830F54E0ULL, 0xFF003BE9AFB193FEULL
        },
        {
            0xFDE7FFE8FC062E41ULL, 0x31B3CBFB0989ECEFULL, 0x0A43FB8D46CBDE89ULL, 0x35C55641D8CAB2CBULL, 
            0xF3F292398610F771ULL, 0xDA0D00E8C5A0915AULL, 0xD009C2568BC93168ULL, 0xA229FE2D484D44BAULL, 
            0xF0EF40D82F620831ULL, 0x22DC6C513BEB7DA3ULL, 0x182E8A6174DE3E59ULL, 0xE84DFEDB3DA71D31ULL, 
            0x12BB02301E5A0A14ULL, 0xCD8D0623BD2A8C4AULL, 0x4CA91AD848F0B0EFULL, 0x70555E45FE8E0DF9ULL, 
            0xDD2BCF4B9C5323A2ULL, 0x6F548BACE90B31C7ULL, 0xD61190F1E9FDAD44ULL, 0x7F35186CAFF76A5DULL, 
            0xC20E689B8BC5E033ULL, 0x1F0DAEFC01E39C8CULL, 0xF2249BC97BE96B64ULL, 0xA0A6866BA2E7DF47ULL, 
            0xB1640879905EC6DCULL, 0x1FD69A8A646FF057ULL, 0x949A571736F3AEC3ULL, 0x2ED7ADB78A5F747CULL, 
            0xF503C80CF5821505ULL, 0x16B7CF98F9CBB87FULL, 0x764443F1E8634437ULL, 0xD0D68A2521A4C1DAULL
        },
        {
            0x8CD77E00AB07E2DCULL, 0xD2D13F57EE9D54A0ULL, 0xC0E86FF258C4A903ULL, 0xB0AF2F5F5727CE30ULL, 
            0x8E268C417793EAE1ULL, 0x440DF870FF48FF16ULL, 0xEB67185F5766625EULL, 0x8B650C1F0ADD7748ULL, 
            0x76090A4C380898B9ULL, 0xDF78AC1D9D346B11ULL, 0xCD0C593368A6E7B6ULL, 0x88AC71892B568EDAULL, 
            0x67B719958F584910ULL, 0x431372F93F1AF83BULL, 0x5A9BAB03F61A0E7BULL, 0x882561627FAFA828ULL, 
            0x9A59107CD2CD13A5ULL, 0x05B59FA082984247ULL, 0x126CAAA8F6965845ULL, 0x17F4BCE96FC43A43ULL, 
            0xF400045D9F4FD464ULL, 0xC54DDB3544A481FEULL, 0x7933B2D6F07B686BULL, 0x5F1F37E6A61EB48DULL, 
            0x9C2AE86A848EC2F2ULL, 0x9231FC49553AF2ACULL, 0x115C45A513B54E5DULL, 0xA4EC042D77E04A7EULL, 
            0xBA33D6558170F324ULL, 0xB8A759E72B50778BULL, 0x3D9D3A9BC8BE7B4FULL, 0x85C2E4084E2E9983ULL
        },
        {
            0x4E636616713C18F8ULL, 0x7F57DBFFBE4EA60DULL, 0x7B64B8DA952BF72EULL, 0xA70C6E6347A3462DULL, 
            0x8D1D12EF1962EF44ULL, 0x3E26F5D1027C7268ULL, 0x3D1088FFCE75C8C1ULL, 0xB4B96F64ABC70648ULL, 
            0x0ACBB47C7748F5A0ULL, 0x742C2002EFF14C5AULL, 0x555106676FACAFB3ULL, 0xA937D89045CC4216ULL, 
            0xD7080CC5C03D735DULL, 0x7D3E056B18DE43EDULL, 0x274A0827A337C9E6ULL, 0x2889D1E4ACB289BFULL, 
            0xD7BB78866E21760AULL, 0xF6B3F60C198EE65BULL, 0xDF2572DAD2A23139ULL, 0x541566A3423FDD16ULL, 
            0xB269FF00B0B60D59ULL, 0x72946168A7B7315FULL, 0xB3DAC098BB4C8993ULL, 0x88A2E7062C4B08C9ULL, 
            0x52F80BF5C3BAEDD0ULL, 0xE89D96F8FC968910ULL, 0x5C16FEDFBEE3CA8CULL, 0x27063934368E74A8ULL, 
            0xD6A6003A7FD64F32ULL, 0x0A18FA553538E3D9ULL, 0xACEFF1B39A4A5076ULL, 0xB6EA5BD1414AB6E7ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Arcturus::kPhaseAConstants = {
    0xA64D81DA2CAA8BC6ULL,
    0x2FCBB20708177F53ULL,
    0xF5D2F7B24ADF0EC1ULL,
    0xA64D81DA2CAA8BC6ULL,
    0x2FCBB20708177F53ULL,
    0xF5D2F7B24ADF0EC1ULL,
    0xB89236BE3B960B8AULL,
    0x3FD19244730D5BC3ULL,
    0xB3,
    0x96,
    0xE0,
    0xAE,
    0x45,
    0xF0,
    0x0C,
    0x58
};

const TwistDomainSaltSet TwistExpander_Arcturus::kPhaseBSalts = {
    {
        {
            0x7CE9C0FBA051E25DULL, 0x1783D2B38FC74DA8ULL, 0x875A3FD0C88DA90DULL, 0x42734115F2479CE3ULL, 
            0x87E60F598C96F352ULL, 0x3DB8BE5F3A3FF59EULL, 0xE84E339B1052D9CBULL, 0xA0F2302B4AD11E7AULL, 
            0xBA63C7FEEE7B94ADULL, 0xE9C504C824F3C5B4ULL, 0x6C1231AC4D8F19C7ULL, 0xEB69E2036217ED40ULL, 
            0x9FE074F9855BEF3EULL, 0xC1159D70EEBF1BF7ULL, 0x0DE86E9BCE371538ULL, 0xB88986CCACCA2523ULL, 
            0x690CF2BF4244A22FULL, 0x97945CED0E05680BULL, 0xB121A4285CB41687ULL, 0xF0B8FB6CCB8B2871ULL, 
            0x8E4491DFA6AE0E0BULL, 0xB4B81375087530C0ULL, 0x8A05BBD8811DD0F7ULL, 0xA098CE3BBD07638EULL, 
            0x663A7500D033256CULL, 0x38D56892999C4AF5ULL, 0xA100D4A4E69A2313ULL, 0xE01E9BF5AF81E996ULL, 
            0x9154C76002C68053ULL, 0x552A4188D980AAD0ULL, 0x269472205EFBB93FULL, 0x73D4F64E0CC0139CULL
        },
        {
            0x8616F8C7C29913ABULL, 0x14C8331DE6FA4523ULL, 0xD4832B12EA617E21ULL, 0xF7024EC699C7782BULL, 
            0xB5DC5B5BCBE19BA6ULL, 0x2467936C6CD18C52ULL, 0x1527686834706975ULL, 0xADFF3F06D15D61C3ULL, 
            0x570E79CCC3116CD9ULL, 0xBE34894AA4C205B0ULL, 0x0BAD610C434423B2ULL, 0xFB02856436763BD1ULL, 
            0xE5E742C46DCFFC04ULL, 0xDE064877CBC6888BULL, 0x5596BCCF977D27CEULL, 0x59FAD445783E4247ULL, 
            0x7A0F48AD12769A66ULL, 0x00CD05B128A157D7ULL, 0xC35B180A526F73B3ULL, 0x42AF2E688F1C5EBCULL, 
            0xAB806830EA7C6A40ULL, 0xAF0917EE5BB2FF11ULL, 0x91C6E6AC0D199C03ULL, 0x23CDC82633B58C9DULL, 
            0x30A4ACB7B2A9EBEFULL, 0xDD38168553C25FE5ULL, 0x5AFBACCB0F3A7661ULL, 0x80D103179DD962ACULL, 
            0x06A887C4D29F886AULL, 0x30DB90A34121613FULL, 0xDB9AE7E15E6FF71CULL, 0x927A47EFDE808990ULL
        },
        {
            0x1FC2199F3C551FCBULL, 0xFA2A660985C8AA6FULL, 0x2C80A3035B1CE7B8ULL, 0x23F06CC6BA2D977CULL, 
            0x3E23F3B51AB8CCEDULL, 0xD60227B3792C6A88ULL, 0x182DE1DAC904B5E1ULL, 0x66DB63C715D2E3D8ULL, 
            0xC416BCCB5E8F6C7DULL, 0x4991DF018B9480A0ULL, 0x8A667402890C3B97ULL, 0x8B5F16494D56DE4DULL, 
            0x6809FB419BE88FBBULL, 0xE667BF92052C9E32ULL, 0xF37CA28ABC59823AULL, 0x870C9830CD85805AULL, 
            0x6BAD693D5AE99102ULL, 0xA0D7BBB1B0E05A79ULL, 0x16CE50F95CDE8417ULL, 0x8B9A82BA3B9CA7BCULL, 
            0xAC8326D4958BEC17ULL, 0x63EA253683C341F9ULL, 0x9537D58418AC03FDULL, 0x6B2C046B027A9D9BULL, 
            0x08D1FF941A5F517FULL, 0x93904BC53A87B183ULL, 0x5F7293271DF39662ULL, 0xE4D760115188E10EULL, 
            0xD0E890B66F0705A6ULL, 0xF147C527C8828A83ULL, 0xEBD53B74E0CA2BF5ULL, 0xEF7A8CB4DAC57D24ULL
        },
        {
            0xB0864A5404B61D0DULL, 0x3AE301F8D0F89ED6ULL, 0xA7E054E95DA6C676ULL, 0x30CCC276BBC25EAFULL, 
            0xF3D7AB097616C6CBULL, 0x712C3943B2531702ULL, 0x429885B9C6D8774CULL, 0x778EBA7CDA085C57ULL, 
            0xE8BBA234B9FABA4CULL, 0xFCA464C561FEA55AULL, 0x67C5ED005E40B5B7ULL, 0x57CB31E2F82B9F01ULL, 
            0xEF97AFAB052FFDACULL, 0x13775FC13CFC6B63ULL, 0xA76826823934D3C3ULL, 0x20FCD7CC5F8DAF29ULL, 
            0xDCD7C9BCCA263896ULL, 0x6C32F647722FB489ULL, 0x680E113CC673CC16ULL, 0x77193E7CEA51A62FULL, 
            0x275BBC0744BD3468ULL, 0x340072F5E71950FDULL, 0xBC4EF0AD96FCA0B8ULL, 0xA31B377A5812C59BULL, 
            0x2B0D3FB74082E6F9ULL, 0xDDFEAEE70E9B4F25ULL, 0xC87DBA1616F66865ULL, 0x8C14FF7CD87BC2A5ULL, 
            0x480BA9B6A838D9BAULL, 0x2B3B7B92D5C3DF34ULL, 0x27A57C3F5B782E30ULL, 0xC99144C7EF8FD772ULL
        },
        {
            0xCF4404CBCFB1A819ULL, 0xE901C454F11042DBULL, 0xE36E19F00257F075ULL, 0x3DD231E1490E5133ULL, 
            0xD773ABE7B43D2F79ULL, 0x7647C6AF5DE71DEFULL, 0x0FA9C1D9D42E34EDULL, 0x1B279E028C5C6A70ULL, 
            0x24B1E1DED5D10134ULL, 0x1DF2000E676AFDA6ULL, 0x3B74B2E8DC560C32ULL, 0x1C17AB29DF83CCC5ULL, 
            0x497D57D58D8FC07DULL, 0x862FD6F7A3C3D4CAULL, 0x197B99538AF4AD80ULL, 0x329055275E5C6517ULL, 
            0x3C55549BD7F426D4ULL, 0xFABFCCBDD318D2B0ULL, 0xBC9929515716EBC0ULL, 0x71541577D11948B5ULL, 
            0x0011D3A12D56096EULL, 0xA749E2097815A3D1ULL, 0x419A563A27407696ULL, 0xE2E1CBE4A2A8DB99ULL, 
            0x30264A6EB3B1F1F4ULL, 0xE6BE8C262AC56461ULL, 0x586C1CCA5E749655ULL, 0xF489E81508A0998DULL, 
            0xCBC73F5BCD029C96ULL, 0xA202B37EDBDF7F80ULL, 0x2C6EE43CEEA0919FULL, 0x7795026A70C28A15ULL
        },
        {
            0xA3F316AD34DF3A44ULL, 0x17D7EA3C045B3F62ULL, 0x84D0B19AE4070CACULL, 0xF714DF8E182CA556ULL, 
            0x226B80CD30208D58ULL, 0xA3FC2D1B04190895ULL, 0x4D7F05D3FCA31DD0ULL, 0x6262889CD057A9A0ULL, 
            0xEB7A230C7054E734ULL, 0x659EC60BE60CFC0FULL, 0x62D3CEE6C7FD3193ULL, 0xBCB28DF48B58E5C8ULL, 
            0x6D8D17B93101691EULL, 0x74D6E808141CE782ULL, 0x353269F9278FB3DAULL, 0xD91C2FE9F5A2426CULL, 
            0xA7F8D4CC656A3C36ULL, 0xB23A0DF4CA0D5171ULL, 0xA6B9C43E3D9EAC05ULL, 0x529D1D0C99B0844CULL, 
            0xA356CBEB222B39F3ULL, 0x34A156DF40D0E095ULL, 0xD6F6EB4B375D8251ULL, 0x9C39F73D2CD7E64FULL, 
            0x1DA5064F129B5D03ULL, 0x70878F3B3F25DC74ULL, 0x852B17822CEA7106ULL, 0x9B47E2A4D7839E8EULL, 
            0x1444987F27ED5A7AULL, 0xB62583351745F0EDULL, 0xA1D50CCB7CEFB855ULL, 0x8C07F5C802339EF4ULL
        }
    },
    {
        {
            0x56E124E024DDFC51ULL, 0xBE90CCDB745E3BE1ULL, 0x1E4AAA5C8619A1BAULL, 0x58015948FE6E39A1ULL, 
            0x642EBE34F3E64801ULL, 0x9D40E8798894EA52ULL, 0xFCB226D54806A5CEULL, 0x3565F7708B6DDD37ULL, 
            0xF8E823C26D511024ULL, 0xC17BAA4A48DB87C5ULL, 0xA8D8EF80F0259A79ULL, 0xE9934BA35AAAD654ULL, 
            0x20671D74B6BD9669ULL, 0xD3FEE8B8B2C387A6ULL, 0x9105835A31542368ULL, 0x610D734D426073AAULL, 
            0x51E739E300DAEDB6ULL, 0x79BE313F1819BF8EULL, 0x75F6901B6F7E0F81ULL, 0x46F0968B2044320FULL, 
            0xEB1A68899415E335ULL, 0xCC4F8D4454689976ULL, 0x3C382E9C1F1ED509ULL, 0xB92D17324D8B7518ULL, 
            0x54F43BF8D343E5D2ULL, 0xE2AE6F98BC0ECC29ULL, 0x48BCFB612504093BULL, 0x5D3B4CCE179DEEEDULL, 
            0x5DE07B587EE78A54ULL, 0xCAA5887FF1A940CAULL, 0x56A2DC4F7603C15EULL, 0xAAA072990F0954CFULL
        },
        {
            0x2A0D201EFE4D2179ULL, 0x471BF3D428099C28ULL, 0x6A96B6B361528E07ULL, 0x071143F1FF7E6C01ULL, 
            0xEE7A2A40653D5F92ULL, 0xA05AA820B19F816EULL, 0x73F690750A74D271ULL, 0x6BEA8FD4BAF545ACULL, 
            0xADC7061779DA4F93ULL, 0x3C72E65BBE252992ULL, 0x9581A7F37E8C722EULL, 0xF818654CDEE3B3D3ULL, 
            0x8715F4A941CB9FEDULL, 0x45B4C82249572D77ULL, 0x511766B79E004B9EULL, 0xE558B53B56A0C709ULL, 
            0x2034E16395F64179ULL, 0xF4897377D0B6A9CBULL, 0x4DEB62B57A2D8345ULL, 0xDA30A41A4C6CC3F6ULL, 
            0xFFD0D4C41CA9BCC3ULL, 0x45F1B43A80255591ULL, 0x4DB21945D942EB1DULL, 0x824EC71AE73DBBC9ULL, 
            0x99B51DFDD927F814ULL, 0x4E0A376010791A42ULL, 0x08226181B98646DBULL, 0x8EE944486319F97DULL, 
            0x400B5C4642A8E7FCULL, 0x475B4E1D32B6FD8DULL, 0x45BA673BAF03B52CULL, 0x102161D410AFEE3CULL
        },
        {
            0x27E7335DA5E1CD88ULL, 0x98DE41503483ED25ULL, 0xC6FFE4104AD5B237ULL, 0x8F2DEC1188DB70E4ULL, 
            0x63327F8FA79E2358ULL, 0x05725213B4792195ULL, 0x1E3430B42EFBADE1ULL, 0xD54FF8D21ED352CAULL, 
            0xD562E257E8CEFD5BULL, 0x4B477981EFDE315AULL, 0x9E7EAC0E7493CA35ULL, 0x0E379164C9ADA806ULL, 
            0x3B66FF66138990F0ULL, 0x9889753AB96EF7AAULL, 0xDCB566E6E906D8D0ULL, 0xFFA9EFF3DAB2BEE5ULL, 
            0xE3732E4B6F2ADE3CULL, 0x9331781E8736F4C7ULL, 0x29E9C8B507DAB8B2ULL, 0x4AE5444B78B8CC5EULL, 
            0xF487DC122E5F0F61ULL, 0xA949B398503BD7DEULL, 0x1F9BAE09ABEF3169ULL, 0x9AA5D41C4A2C677EULL, 
            0xBA89F9546446ADDBULL, 0x869BDB1059EB2CE6ULL, 0x85293F18AA8EAAD5ULL, 0xA08C3561075A621CULL, 
            0x686C35918DEDFCD6ULL, 0xD7DC5B3F514A15CDULL, 0x674124D8E4692A76ULL, 0xFC58842DE115C263ULL
        },
        {
            0x6DE924657B76A28AULL, 0x76F3EC4B923637C8ULL, 0xEB0868B8983ED14DULL, 0xBED9991B94A38A83ULL, 
            0x4A14869D63E7EE58ULL, 0x29A20A33A4FB9B2BULL, 0xA09793F70DFBB957ULL, 0x09FB5D0196975FF6ULL, 
            0xC7AC8BE5ADF9B2B6ULL, 0xA97CFF0217E226F3ULL, 0xCE0A65CE2F885DA2ULL, 0x621C09918CCBEFE5ULL, 
            0x6FDAC06600183AB5ULL, 0x85A4E9A323169E0FULL, 0xBE55CCC93D532778ULL, 0xDC54B0A303749154ULL, 
            0xE215F3F56DA6DB43ULL, 0xB6452EC0E31FD495ULL, 0xA8CB360A4E052826ULL, 0x02EBABCB0F77E33EULL, 
            0xD9A474E5D55F1780ULL, 0x574232282003A6F6ULL, 0x7E7B41A70915896AULL, 0xA5110D1FFE68C8C8ULL, 
            0xD26DD311A8137FADULL, 0x76FE74D60A5F4CECULL, 0xC80A6BF8294D63ACULL, 0xEA6BF69F7B0112EDULL, 
            0x695092B7DC015350ULL, 0xC1ABCD1377E5EDB0ULL, 0x4CF357CA0E4C357FULL, 0x6D1E4714B8059E21ULL
        },
        {
            0xF089DC197A9950F5ULL, 0x6B54293360D8487AULL, 0x934C8ED168FDC551ULL, 0xE2B1D514C4F47BE0ULL, 
            0x1F4C8CDB4AAC4B6BULL, 0x42154CF352F4F20BULL, 0xFC18B3A59A9F376FULL, 0xE45A09780FD591EDULL, 
            0xA6B1A4F12E0FCA56ULL, 0x4BC7B96E1E54EF25ULL, 0x460E6ED66BAFFF4BULL, 0xD2CD2440981D5E01ULL, 
            0xA232DA4365DAF8A7ULL, 0xBE28B11BABF3A3D8ULL, 0x31C6AE76A43A3968ULL, 0xA2510DA0F49C202FULL, 
            0x0FA171650E06EA10ULL, 0x74F956AAD15C236AULL, 0x948D7E6155D79801ULL, 0x011B3F4F3C191403ULL, 
            0x89FE55D01A8A5D25ULL, 0x592BCD98A56676C6ULL, 0xA346366BFD3F2F44ULL, 0x70A78172074F9FFAULL, 
            0xEC0C2BD2AF8AB196ULL, 0x6EE3C8E2F2606A76ULL, 0x399048108AD733E5ULL, 0xD0687EB7DBD422C9ULL, 
            0x1CE9C8209C479B0BULL, 0xCE6499F379A0AE77ULL, 0x284C56480E35B696ULL, 0x7963A35B89BDD489ULL
        },
        {
            0x3737D86CE35BC3F5ULL, 0xA553BF1414B6E690ULL, 0x7BF8FA06D1B3EE1FULL, 0xDF7BF931F4EC9E96ULL, 
            0xF79DC15438070221ULL, 0x75CC039CC34946E6ULL, 0x32EB1652F021F92CULL, 0x2AE163FF77658188ULL, 
            0x31A2FEEFBD839F34ULL, 0xC03ECC35C3AE9953ULL, 0x85E9597861526656ULL, 0x2404ED08EEAF42CFULL, 
            0xF4F6C1E39C20CC48ULL, 0xF77AEE12C659F06EULL, 0xBA7A0FA8237A145DULL, 0xB463A31E8428934DULL, 
            0x1E58E29409685E24ULL, 0x298E7B2FF9980B22ULL, 0x17C684EA8C9ED24AULL, 0x857C7FAC7110EFD1ULL, 
            0x01C5A7B6A9295548ULL, 0x503A844F9445E2DEULL, 0x343B4C26487EA3E1ULL, 0x27167A29E8322E63ULL, 
            0x196E8A1CE05F1252ULL, 0xD6B26A98F590F087ULL, 0xC855E58A8A77BF82ULL, 0x8D42911E7EC45F71ULL, 
            0x45B59F3A98B050BAULL, 0x1CDDF7329909F266ULL, 0xB48C8D109EE58DC9ULL, 0xD8080C61D70D0C9DULL
        }
    },
    {
        {
            0x7B345568B24DC693ULL, 0x06373E1356A3B36DULL, 0xF8A4A6040241B75AULL, 0x719820897D45A2BBULL, 
            0x1A69D4EF639EEBF3ULL, 0xA90393E5F7F6F7EDULL, 0x5F455FA70BE036BFULL, 0x3AB162B8777B8689ULL, 
            0x2B1D429ADBB3B4DDULL, 0x1C9AF9CD5FE5CD2FULL, 0x826DA3AA9EB9C5DDULL, 0xC97FE13A1245E707ULL, 
            0xA17F923320F404B0ULL, 0xB6EEC08C758EC4C4ULL, 0x17196BEE8616A662ULL, 0x7704ADD6B4E1AE56ULL, 
            0xD3624DF6631A9192ULL, 0xD8B71B939D1A79F3ULL, 0x20FD0F6A08755597ULL, 0x10B04F4AD0DD3445ULL, 
            0x5F3CCBC49EFEA860ULL, 0xAE80FB3760305686ULL, 0xE8C6EB31E50F0C3DULL, 0xC0BDF857A4F43E98ULL, 
            0xD122E857CB5F69D3ULL, 0xF9A80C11655FB39EULL, 0x369BE064077E8950ULL, 0xD1C409D114DF35BAULL, 
            0x1CB209EE062CCAA8ULL, 0x4FFD9DFF1BEB810BULL, 0xAB38136264366FFAULL, 0x4F443A09F2F439AFULL
        },
        {
            0x0AD26C48FDD7CAC1ULL, 0x8FED883A7C2162C1ULL, 0x7BE547294F25C14CULL, 0x6417970E133FA2FFULL, 
            0x0A32DF573D2C44D9ULL, 0x0827ACAECE9FA556ULL, 0x4D197DB6BD147413ULL, 0x206C4816F88300D7ULL, 
            0x7CA1506DA6913936ULL, 0x7BAB70F977EE7D09ULL, 0x4DD66C2166C02BC8ULL, 0xCEF899F90AAC86F4ULL, 
            0x2E0FE8B6F8F40242ULL, 0x783705064129466EULL, 0x0350DC8E40969221ULL, 0xD281A71E60C33B65ULL, 
            0xD83A1C81C11B3701ULL, 0x9A5DE9090A385BD4ULL, 0xE71AA9947295CBA7ULL, 0x2915B7F161A2FB23ULL, 
            0xB4C994DD3E52D878ULL, 0xD7CF959DEFD96AD6ULL, 0xAFB993C119126C03ULL, 0xBE388ACD1FD92527ULL, 
            0xE7C36535B7890E4DULL, 0x32E19FE19B49ACECULL, 0xE2DE7F312FDB2917ULL, 0x4DFD1D799F270805ULL, 
            0x9B8F73AFA36B4F8DULL, 0x8FDBD962AE7893A6ULL, 0x06DB5B8D9868E7CDULL, 0xC86C6BF34CE2537EULL
        },
        {
            0x34FE8E1D2212D08CULL, 0xD100B98063F54B9DULL, 0x6F9A4DD882848D41ULL, 0x21D41D969A4DEDC4ULL, 
            0x85625F2BADE71FF5ULL, 0xBD29296BBBAB0237ULL, 0x02028A6EF7262394ULL, 0xBEBA480DBE7C486EULL, 
            0x781AA760E97722BEULL, 0x6C3FB9528DD15D36ULL, 0xE416262F14CAE8BCULL, 0x67A06131434B8284ULL, 
            0xEE7D1C6AD92B9BD6ULL, 0x572C32D415BD85B8ULL, 0x8B1618C0E8274837ULL, 0x693EECA41EF5A75BULL, 
            0xFFB64128E922D277ULL, 0xA93FA4452A73ED87ULL, 0x574ED16FDFA6114AULL, 0x93465ECBAE8A8E59ULL, 
            0x1D7886CC5F4C2CBBULL, 0xE7A1877D2F0648A9ULL, 0x0C8DEA7DBE1B48FEULL, 0x8A5F28A5D5EBCC18ULL, 
            0x43FAE86A3F531F00ULL, 0xC8C7AA7F842CBE2EULL, 0x466B84C1666C1166ULL, 0x1BEA25CBFA424E80ULL, 
            0x660B2D8C0B2E6098ULL, 0xF89DF1EEF1053B0CULL, 0x22FC8D90F885368CULL, 0x1A77F2629FCF9BD6ULL
        },
        {
            0x70F6BA469857ECF8ULL, 0x5892B75B657046E9ULL, 0x366F9FECEDBA19EBULL, 0xE8340AF884E7F618ULL, 
            0x82AFBF840E56697BULL, 0x6CBA7DE7EB208D0AULL, 0x0FE0F29761BA9487ULL, 0x69E4C727A3076782ULL, 
            0xAE674DABC1D2B42EULL, 0xEDF40E119623BBADULL, 0x4CA07F3DDF5CB4C1ULL, 0x5527583B50BCF8A1ULL, 
            0xA961FA83E1C86B1EULL, 0x14BE015AA005C0C6ULL, 0xC1E89C24AB5EB4ECULL, 0xD396731F5FD24D0CULL, 
            0x6422059A4E3B3021ULL, 0x92B700A457FE510EULL, 0x01C676B68D636E23ULL, 0xFABFD56C73AA736FULL, 
            0xE788DF79F92420F2ULL, 0x0EFAF4B8C387B8DFULL, 0x8F353EE003024FFFULL, 0xC434A8429B2952E5ULL, 
            0xB7B633F2AC54DF1BULL, 0x3E37982B37A97EAFULL, 0x7187CD8183BDAFCAULL, 0x556ADD877EA451C1ULL, 
            0xF833E75E44A4D19CULL, 0x3390473C718B7E3CULL, 0xE6F9116BB28C6B91ULL, 0xE016E3314C7E1C5DULL
        },
        {
            0x11994F5DE8767EF9ULL, 0x59398844CB1C5956ULL, 0x82CC9BA18CB3D868ULL, 0x6F2BFD11A7AC4C5CULL, 
            0x9D78F9547CDE0748ULL, 0xBFE2FD183C70FD73ULL, 0x1A6D4F9809AB8E93ULL, 0xC702BCBD4C1D3386ULL, 
            0x0F776CAF07730C0FULL, 0xFDC1625269B41BA5ULL, 0x6789E6CD8045A709ULL, 0xAE86F2FD3848170BULL, 
            0x0275E14FE1683AAEULL, 0xBE19E3C69FD560CDULL, 0x1E7FB84CFB003549ULL, 0x08770171AACD4A24ULL, 
            0x589DFBEA5BAC6C45ULL, 0x03C523A3DD646900ULL, 0xA25C95AFB34EEFE5ULL, 0x88193A8E7077F6BFULL, 
            0x3317D4AE62DCE8E2ULL, 0xAF21ED4E07834709ULL, 0x88620E08AFA279AAULL, 0x87F932C04E393EBFULL, 
            0x572532BE21369C11ULL, 0xC123C2E0A035F859ULL, 0xD87A8AB3E2372C84ULL, 0x0BC1CE19AE783264ULL, 
            0x74F7C26B7D598F33ULL, 0x00174EE5B8E4B8A4ULL, 0xB3E84591C04A01D1ULL, 0x72A55AC19DA1FB13ULL
        },
        {
            0xCF81CE425D679F1CULL, 0x49AE99C68CD14927ULL, 0xDC87A77F79552BE8ULL, 0xBFCBA24068D3320CULL, 
            0x17924498DA18793FULL, 0x4C1977DDF78899C7ULL, 0xD632DBE18CF0AD98ULL, 0xB0DCB88BF26AEB83ULL, 
            0x6531011272186F35ULL, 0xE02531400B74A339ULL, 0x5D1CB94073F8A020ULL, 0x7D76DC1B810F5F09ULL, 
            0x2E56ECBF3EB07571ULL, 0x1277C7D461635E80ULL, 0x999E7D2FBBDF13D4ULL, 0xCAE5EEEEF4907F85ULL, 
            0xAD387C59089A36E3ULL, 0x75D11372DFA1A11FULL, 0x8216DF566A161B83ULL, 0xDA0FD5BC3A434CD1ULL, 
            0x52EBDD1339711592ULL, 0xBB5B8292E9253DF5ULL, 0x5A59D11A5194E3AFULL, 0x66564080BF98C686ULL, 
            0x1EE87D5CFCE00D0EULL, 0x7F1171ABF08698DEULL, 0x15AC6FD34FBB18FEULL, 0x1986FE24310D6A70ULL, 
            0x985B1A8C548E68CBULL, 0xEA3559D6A508D99BULL, 0x2A910CF7DABA3892ULL, 0x25E9FC76319FCF97ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Arcturus::kPhaseBConstants = {
    0xB293A7FAAE0328D6ULL,
    0xA149FB8FFC5E9AA8ULL,
    0x3DE656F7A39103B3ULL,
    0xB293A7FAAE0328D6ULL,
    0xA149FB8FFC5E9AA8ULL,
    0x3DE656F7A39103B3ULL,
    0x54723C4D0B9C897BULL,
    0xC1B7944DE6CCB816ULL,
    0x8E,
    0x1F,
    0xEA,
    0xA1,
    0xAE,
    0xEE,
    0x1A,
    0x37
};

const TwistDomainSaltSet TwistExpander_Arcturus::kPhaseCSalts = {
    {
        {
            0x1B8DEA83A7DE5186ULL, 0x3E061C384A13AAA5ULL, 0xB9E41C139F8FFA35ULL, 0xA122A418165907EEULL, 
            0x0734D76BEF7D0D34ULL, 0x57E269E8F55DD410ULL, 0x36A10D707FB3086AULL, 0xDB009F70FADD6ADFULL, 
            0x19016D1944333317ULL, 0x779988E6391DDB49ULL, 0xA5CFB98384C77AA8ULL, 0x9F031D8E74B3C61AULL, 
            0x40AEF4F373F0F5EEULL, 0x7845A2E821603A5BULL, 0xB97164228569E381ULL, 0xB3DB7D0E9E48F26DULL, 
            0x84C248E0670721A7ULL, 0x1F53C0EA12A83366ULL, 0xEEB74A5638E24D49ULL, 0x00E8E0A9B4923AFBULL, 
            0xAA94C01C46FB2CAAULL, 0x5F3E950CE583605EULL, 0x97E632252955B806ULL, 0xA507531BF7E0CAB7ULL, 
            0xABDD43D136C50C6FULL, 0xF48853A96DCF37EDULL, 0xAF8DDE094BDDA8B7ULL, 0x8B732296D7ACF73CULL, 
            0x834A747B29B94D69ULL, 0xD82435CF41EB3612ULL, 0x50642998B9BE2006ULL, 0x00445ADA6DBD963DULL
        },
        {
            0xFC79EFC7F2E9CBF6ULL, 0x99BB9D33D30A44A5ULL, 0x6B3CA4925CF17C5FULL, 0x2CD5FC4511A598E9ULL, 
            0x9FDE3AE1F2B9B5E4ULL, 0x499AC6E3FB3E8322ULL, 0x91DED5F632AE5937ULL, 0xC48B558A81A377E7ULL, 
            0x87163665BBFD1531ULL, 0xE6BC57670DBC4251ULL, 0x7C36809F65D5DBA2ULL, 0x826B16A8CABED1ABULL, 
            0x25963E3619B8CEEBULL, 0xD1A76E3FA0E7E605ULL, 0x9691DFA3EDFF8426ULL, 0x0EC89B6D819FE52BULL, 
            0x1DBD87B0BB3BC032ULL, 0x877B0963D4073E14ULL, 0xD90FE4E242973577ULL, 0x10874245ED2111D9ULL, 
            0x8CCC7A0EFD0EC996ULL, 0x180452FBCD8B81B6ULL, 0xCF25E7116355E51FULL, 0x0B6E791F835A37D0ULL, 
            0x696415F77FD4D1D9ULL, 0xE991158872C5A56AULL, 0x0D8B0EC259E61B9BULL, 0x2838C64E54A3E320ULL, 
            0x7DF55C524C942027ULL, 0x872ECEAD3BDE49BCULL, 0x83039121206044E7ULL, 0x1B2592FB4196E961ULL
        },
        {
            0x0EE940509D7CF2A9ULL, 0xF1A28AA63B51CB67ULL, 0x034BEA96A9D90CFBULL, 0x8A9095D1BA38226DULL, 
            0x1750D67038462822ULL, 0xC5AFD0AE061BA451ULL, 0x5F8715D9E4C112FFULL, 0x4EEB6C5D13B74E59ULL, 
            0x1CB7948CD1CE53C1ULL, 0x33550D44E345C574ULL, 0xF3A8CA8FB5B3AB8DULL, 0xB39DB3A268C0138CULL, 
            0x2037C7C9F9D959D5ULL, 0xD7489F128049EEF6ULL, 0xC2D809A2607B3B71ULL, 0x5FC98242A1C75D7AULL, 
            0xD1BA08CDEC8F3313ULL, 0x37B9D5B0F6FB02F7ULL, 0xCE64A2CE4DF5D724ULL, 0xB608343253382B76ULL, 
            0xA3BD10EAA625B532ULL, 0x54AA139B60F1EC46ULL, 0xD75DA5708CBB4DDAULL, 0x3170E155BC805588ULL, 
            0xBA5D3E705C99ACE4ULL, 0x834F74199D538C36ULL, 0x74D91DB13DBF9A5BULL, 0xF2B971C8F82CE18DULL, 
            0x22D8C6290F9FD9FDULL, 0xEC4754723CBC61DEULL, 0x13FBE28331245DD8ULL, 0x0D4DD855715F0086ULL
        },
        {
            0x6A08912809580702ULL, 0x7F22342E53C575B6ULL, 0x62A9D660217B2B05ULL, 0xFFAF8C5E637DB360ULL, 
            0x0E72461EC18D9242ULL, 0x3B6C0259583DB432ULL, 0xE750AC2E7015DF78ULL, 0xA770C38AFB909396ULL, 
            0x71CEE6E571483CE1ULL, 0xE928BA0F6E5289F8ULL, 0x293B818082A55839ULL, 0x29E261BD106B579AULL, 
            0x427374EAF9058D5BULL, 0x0104FD18DD5E2D5DULL, 0x9FAE5DC81CA31C6AULL, 0x88111A3DFA435A1BULL, 
            0x2007516AA817B1CBULL, 0x197DC9BF558C2644ULL, 0x102B13ED66046725ULL, 0x4BAA1622EFEA7E06ULL, 
            0xFB32247405A9CE51ULL, 0xA71334058AA403EAULL, 0x70F604EA4E028FA1ULL, 0x76A7BF8E040A77E9ULL, 
            0xF8187D446BD7C47EULL, 0x076F4364E74AABE7ULL, 0x074F56EC3A114E16ULL, 0xF68B0022894EAC9BULL, 
            0xACB7E261C2669371ULL, 0x0A2164F9EA1BED9FULL, 0x22704682629FA5ACULL, 0x6781E64780096642ULL
        },
        {
            0xDF5D1698F74C165EULL, 0x47EEB925319DDB44ULL, 0x31DEEE3F8790AAD5ULL, 0x5C19D0FA91B1C742ULL, 
            0xED604DAF947D1DF1ULL, 0x7BB59683C59729BAULL, 0xF30E518FA139DF91ULL, 0xD947DF2BE8AE39D9ULL, 
            0x1D836422D55B5DC1ULL, 0x33D27498AEDB6428ULL, 0xCF93565C17B7F5CCULL, 0x940F5C10A75EA266ULL, 
            0xCA897FA830476208ULL, 0xA3493152ECB247A6ULL, 0xFB600312239AAD15ULL, 0x3E98106780572C61ULL, 
            0x00642ECF221797CFULL, 0x77DD493A624BD43DULL, 0x340FE254F2D8F468ULL, 0xF5A4D424FC98B713ULL, 
            0x8D16CCB4F188C3CBULL, 0x8E31652C854940EFULL, 0xEE66C01A8B3F5B6EULL, 0x458868E3CC670A2BULL, 
            0xF5E648C833A5D524ULL, 0xF3613F9B23449B7DULL, 0xE27E6B8841BCA449ULL, 0x1E7806EA4DBD4905ULL, 
            0x7CA5AC8C126B7438ULL, 0x538C6E8A375C6BAAULL, 0x640EB5FDDF8534AEULL, 0x7A3D1DBFA560E976ULL
        },
        {
            0x7F172E7E42102BC1ULL, 0x9502FCF9DF093DF2ULL, 0x1D4C99AB9CABCEEBULL, 0x3BB99CC477C8B37AULL, 
            0x6C8D5321E8417150ULL, 0x04193516E0CFF240ULL, 0xD47B730D9215AED9ULL, 0x5CBE07AD2654FE8DULL, 
            0xB41D7FCD2808AF05ULL, 0xD816F8483DB2E1B1ULL, 0x2929BE920BA0EB43ULL, 0x43D1081262604074ULL, 
            0x2FB4A35F8D12B64BULL, 0x87F74E9AFC4BCCFBULL, 0xB112F1C34A36CBD0ULL, 0x70230AFA16B91956ULL, 
            0x43FEBEDAC9BCEA07ULL, 0x11FD9887B22EC48BULL, 0xCDB0D60C5F936829ULL, 0xA2C9867895426AF7ULL, 
            0x725E68F65196589EULL, 0x997C06853CC3FE4BULL, 0x714A1D91980FBFFCULL, 0x92E8B01BA9B5A55FULL, 
            0xA7199D32266FB5F1ULL, 0x956A302056287B2BULL, 0xC04FCCA8B3C07260ULL, 0x30EDB2CDE177706AULL, 
            0x6A9E831CB0139777ULL, 0xA94DACE3B11F629EULL, 0x2AC458AC84FF9F5BULL, 0xCDCD196482EF2A2DULL
        }
    },
    {
        {
            0x2C63D41977F52914ULL, 0x1CC955D96351AD86ULL, 0x12F6BF159A67C5BFULL, 0xB70EFA0B9C155A81ULL, 
            0x2278227714F11C12ULL, 0xF4939C10C81C2FDCULL, 0x722F72FB91557AD5ULL, 0x35142CEAC60655E8ULL, 
            0x58DFBB376F9AC98AULL, 0x235E4072F51612B0ULL, 0xADB4BFEE634DDD12ULL, 0x501C77C538F09F14ULL, 
            0xC2BCBD726EAACD13ULL, 0x44DB0FE006AF6B95ULL, 0x2A29EE7306F72141ULL, 0x3EC65DBE13C290EEULL, 
            0xB021498E9B06F268ULL, 0x122310076DA85B7BULL, 0xB0089071C963A3B9ULL, 0x3A360428B62D92FAULL, 
            0xF14E891A96FB6588ULL, 0xAE6A1F19F607F960ULL, 0x031A0F209E46F0E5ULL, 0x91F978122E899B83ULL, 
            0x252060DDF506029CULL, 0x9D2E14A44D277C8EULL, 0x471D1F954F9252EBULL, 0x10EC9A965C540D25ULL, 
            0x53A92BA79761FA08ULL, 0xB6261132A3BE93E5ULL, 0x8F0E76959A275816ULL, 0x4C9707050E59494EULL
        },
        {
            0xDED525A217732C8BULL, 0x37D2F78F49BBE3BAULL, 0x1C1129C4B7E36005ULL, 0x29BB7C1EC5B2082AULL, 
            0x9321BB6B7029A392ULL, 0x545F61B61282CFA2ULL, 0xA30B9767B9B5EA2CULL, 0x9369C12BC3108FC4ULL, 
            0xFACB08EC3956B943ULL, 0xB6D9AC4A786F1C8EULL, 0xB266975630029EB4ULL, 0xF3470E282ED67312ULL, 
            0x83A2C81C7F925185ULL, 0x87E3026048272EAAULL, 0x86CB72FAA173CA99ULL, 0xECD52156AD0CFA8EULL, 
            0x8FEFB20F205AEC0EULL, 0x30D13902E78B7D64ULL, 0xDBA5300AC3FE3C2AULL, 0x81D2792488BF8066ULL, 
            0x3762669451A1C862ULL, 0x39F4F3EBDAF6D51AULL, 0x5B1FB05A425B1D44ULL, 0xABA384333056708BULL, 
            0x7155FBD3495AFE97ULL, 0x9E2727733A7A4748ULL, 0x6686E4CE48B6261BULL, 0x628D51AC0F1904BEULL, 
            0xD697B813BE7B8994ULL, 0xCA69DA7E2DBD9BD4ULL, 0x738002DFC25C2C95ULL, 0xB9009F9C731E5EBAULL
        },
        {
            0x16DBCA24EF54E00CULL, 0xC8DDD6F08D167A04ULL, 0x5A811077029E0916ULL, 0x799B39248A55EB29ULL, 
            0xCAABC09FB656C34EULL, 0xF4C29A005B4772D1ULL, 0xA4F3E26923F56650ULL, 0xBC8F0EC4FEC84B12ULL, 
            0x105E3C5AB9AC6DF9ULL, 0xB6D15AAB4C37DFA9ULL, 0x13FC6CEDB25E5325ULL, 0x7F61974B870619A8ULL, 
            0xFD0AD99E9396F448ULL, 0x68C187AA63348A77ULL, 0x2C2DE5EC2380D10DULL, 0xA89D082A47DD6E6FULL, 
            0xD93BF73405D7D86DULL, 0xBE8AEA9A9B37B694ULL, 0xFD35615A684EFF21ULL, 0xE0BC932A898D6E2EULL, 
            0x4BC29BA970316A92ULL, 0x33751E39CFBD24BCULL, 0x245C0E819B81BCC5ULL, 0x5DD25408DE52D7C8ULL, 
            0x3EB34CF7CBB9674CULL, 0xF227E51BA7A3770EULL, 0x65B12ECA987D9D4BULL, 0x6711BBE3A9DD2787ULL, 
            0x35FF77086E59FC10ULL, 0x46BBB8F383177CDCULL, 0x1281E5E4EB1C342EULL, 0x2D875762AFC2418EULL
        },
        {
            0x6D021CA4BB71FDE3ULL, 0xB28532607C8F8510ULL, 0x541D3B61D3DF3ED9ULL, 0xFD6866B39086BBA8ULL, 
            0xFA884990FA469C08ULL, 0xCA51DDA4CBEDE6AEULL, 0xA9CA2BD95CBD8861ULL, 0xEC24B2C4286304C1ULL, 
            0x741F24ADE11248DFULL, 0xDEE1B15F698BA8E0ULL, 0x2A0BF3B357EC3D51ULL, 0xA2FBE27CF66FCFDEULL, 
            0x184A45AA9C67234FULL, 0x7FC5341C1258E12BULL, 0xCE886F97175C21A8ULL, 0x474BDD6747D997E1ULL, 
            0xD103A122D981A492ULL, 0x62FA6DDB86D4BB49ULL, 0xE5A632D7C7DCC4C2ULL, 0x56FD6F9543491777ULL, 
            0x0FD9F192C94BC4DAULL, 0xD77F5358F807FBD8ULL, 0x0F53611B9544DC81ULL, 0x3F3617274EFF3625ULL, 
            0xA8B9DD5B92CC676FULL, 0xDC3537968452897CULL, 0xC455313893282ADDULL, 0x712646EE3256EBA1ULL, 
            0xB349A5D18CAFED56ULL, 0xC98385538B0B9539ULL, 0xE1D6C6435855B53BULL, 0xE077ADA9333D1BBBULL
        },
        {
            0x3C5EC04A16B5831FULL, 0x8C9D6B062BF69279ULL, 0xFB4E20EDB56B86A6ULL, 0x9CEF9444AE9529DBULL, 
            0xE0E9DC40F0C432AAULL, 0x56518813A32D456CULL, 0x307492BD3581F0F2ULL, 0xC62279AE3D533402ULL, 
            0xFE7C84A847EBBF20ULL, 0xD16E09E88DC7D105ULL, 0xC078DBEDD7081570ULL, 0x9C5B1551823AC366ULL, 
            0x8001F66F46499AC4ULL, 0xD9FA50214E2F93EFULL, 0x181ECB8AC2970268ULL, 0xA4B851815AF9463AULL, 
            0x56069017B0D2F857ULL, 0xFA866444BE6A11ECULL, 0x8EC8FDC623E78A7CULL, 0x06BF6D12FB6D12DAULL, 
            0xC5ADDE9DBDBBFC3DULL, 0x8C0634E6E829ACA6ULL, 0xF16639BC46CE6937ULL, 0x46B415302A37E75BULL, 
            0x117E3AD0B0D35138ULL, 0x1F9AEBC6E89209B0ULL, 0x789DD1874007D6C9ULL, 0xCF465555473AC791ULL, 
            0x80CCD95582F5D864ULL, 0x99EDD2E484139D13ULL, 0x9645DDA194AFA39EULL, 0xC547B8C3A9D69B67ULL
        },
        {
            0xFE8EAF8DB8688915ULL, 0x2C4A9E047CC65E46ULL, 0xFD1E0418E29FE0F9ULL, 0x24EF95822A50860FULL, 
            0xE79BFF90D2A0F6FEULL, 0xAC93979F3BA73D76ULL, 0xB14E3E6F0D4DB741ULL, 0x4989E946D5B47E36ULL, 
            0x119BB09B796CB1E1ULL, 0xB37E78B10B91B575ULL, 0xE80EB6EDC8712CBAULL, 0xC37517A28CE16547ULL, 
            0xEE6EA557039DBC7FULL, 0xACEA502E9B6C185CULL, 0xBCB39E3997B8FD96ULL, 0x37E81A9EBADF9826ULL, 
            0x45356E127DE36C78ULL, 0x76E9DDF8A7163A29ULL, 0xF668E959E79E5194ULL, 0xF7A06224C840F663ULL, 
            0xBE8CBB086FFBB92FULL, 0x2B61A23E093BA547ULL, 0xBE70E261989B25C2ULL, 0xB94878E1CB06201AULL, 
            0xEB47B697E7DB22CDULL, 0x8D67300F93AE2E08ULL, 0x323B22D97BF7ABC4ULL, 0xFCC112859C3F1496ULL, 
            0x85DF41EAACE1C3C2ULL, 0x52A5091EC14000E7ULL, 0xAC438584A47E9B7CULL, 0x482F820CDCEA0508ULL
        }
    },
    {
        {
            0x262C7FFD84501EF7ULL, 0x15050FBB32E6A04FULL, 0x68B556B836D65A2EULL, 0xAEDE1ADAF48BE544ULL, 
            0x3ACAE519ADB7C9A2ULL, 0xC8107D9C59AB1B10ULL, 0x22FA5E821BF3D514ULL, 0xC2090A79D1CFB4E8ULL, 
            0xCC208973DBEE68C4ULL, 0x6C6EBB86D530C498ULL, 0xB7D44A5EB5B42C80ULL, 0x9B817FD95554D196ULL, 
            0xB8626034C7CA9444ULL, 0x588455243C01AC02ULL, 0xCA5ED20184522B62ULL, 0x842F9C595D38B079ULL, 
            0x381F572F88FA8268ULL, 0x7609FAB5EE3AD9B0ULL, 0xAF559BD93DDB4932ULL, 0x266BC7D1668424FBULL, 
            0x029D28F170D5CFDBULL, 0xA426E41A2D426391ULL, 0x1814DCCC1F6AB657ULL, 0xA89763A7F7FBCE23ULL, 
            0x9D174D9E90730CD6ULL, 0xD8BACED02E44FA1BULL, 0xB8F6677F6FFC2E94ULL, 0xE2A9FCCB93E9C213ULL, 
            0x3875CE76A7EC688BULL, 0xD5FEAF6B6C2C0139ULL, 0x05D98252179FD3E0ULL, 0x414744043C76CE44ULL
        },
        {
            0x2B909D60839DC6C1ULL, 0xC570ABF9E7EFD450ULL, 0x965EBEE1E63B84EFULL, 0x62E52E428845C9A1ULL, 
            0x7D8DB9C2E705DB9EULL, 0x70497D1613DD80FEULL, 0xB5129B765F5575BCULL, 0xAB447288E586F70EULL, 
            0x8EAA1621901AAC15ULL, 0x974DB38623536C0EULL, 0xF660B09003BAC219ULL, 0x7CB98E4F2D364CCEULL, 
            0x07F8ED29A1699056ULL, 0xB3F0F6793CEF1D90ULL, 0x281A4F23327D1FD6ULL, 0x5B57280A6C026243ULL, 
            0x0543A047404C5301ULL, 0xE89918D0F401B427ULL, 0x7823420E21828EE0ULL, 0x47A698B2DF8A8461ULL, 
            0x64C12806C80400DDULL, 0x0B6DA25ED2083FAAULL, 0x7268407411F394BDULL, 0x3DB083328C078952ULL, 
            0xEF1EFE9DA4D99401ULL, 0x89F855E4FE252378ULL, 0xF1E8D526776455BFULL, 0x18593D079DA0F84EULL, 
            0xCC879A4BCDCBBB70ULL, 0xC7533BF02DC6F9BAULL, 0xED637E6FC959912FULL, 0x1549C888470D88DAULL
        },
        {
            0x14C4E2DCD8639126ULL, 0x16551B19916D3E32ULL, 0x69F10E925384D0C7ULL, 0x3E3A1BA178139270ULL, 
            0xE9767E566588DF51ULL, 0x873DBB99E7FF5D83ULL, 0x1622C1889D00883CULL, 0xD27E8E2F7059CAE0ULL, 
            0x5C3F5641F30C13B7ULL, 0xE07A71843D3D7B64ULL, 0x25F714A630D193F6ULL, 0x76A765356014D2E4ULL, 
            0xB647AEB6EF763C2AULL, 0x43844A10C4AF0B4CULL, 0x24EBC35A428D9224ULL, 0x393CAD37ADF9750FULL, 
            0xFF2F626002067BF4ULL, 0x241EDF92486A25F2ULL, 0xF4C6D36BC6505782ULL, 0x1849AB4709D66A1BULL, 
            0x840AFE763975DB14ULL, 0x375FBD284AFB9B3BULL, 0x5457D0481099C3A3ULL, 0x8D88E21A6102851CULL, 
            0xED3BDF21BD89C28DULL, 0x579F7E2CED9D66AFULL, 0xB2DE3FD23F73EC0EULL, 0x17EB8A31C038940FULL, 
            0x6FEA2437DBFB5C30ULL, 0xE25F1ADC2EE5EA78ULL, 0x9395BE7D66CEEA22ULL, 0x3E355C2360AA224FULL
        },
        {
            0xA517CF9350C58382ULL, 0xA029BC6B5C924D98ULL, 0xC7F78446075DA593ULL, 0x7CFFCD5E0D79D458ULL, 
            0x677B489C270C2345ULL, 0xFB2AF352C608C651ULL, 0xC6F0D17C327D4A14ULL, 0x02D680D5C24BBE6EULL, 
            0x67ED972180E14227ULL, 0x4DA49295938FC917ULL, 0xE5E24B1DE2AFC247ULL, 0x368CAB829B2FE545ULL, 
            0x691DB57D067DCDD3ULL, 0x44E9844DEA204C47ULL, 0x83ADDBED3B234A9AULL, 0xD5078ED847A729A6ULL, 
            0x1322C87BEF4D1FA1ULL, 0xAD356F4DD39B53C3ULL, 0x19FD29B821E38FD7ULL, 0x6053F7D2714A43B6ULL, 
            0x9E59ED7BDB0C58E4ULL, 0xA0601CE21E12DA06ULL, 0xC0A1CEAE317DE0F5ULL, 0x920098FC02E94706ULL, 
            0x699E1BA2D795B858ULL, 0xAD777CAC2FB77414ULL, 0xE69CCDFE6D7606ADULL, 0x795AD24239F9CF7CULL, 
            0x5C594D32E7FBC4D1ULL, 0x792AFF4FDC5AA0B9ULL, 0x3574C20477780696ULL, 0x5F4D801C7BB07A4AULL
        },
        {
            0x980AAB6E334C871BULL, 0x14606C1500AF20EAULL, 0x52D914C222AFE9C3ULL, 0x5D8F0280B3B9D58EULL, 
            0x144FA90F3B0F9762ULL, 0x2222168AABAB8A85ULL, 0xD74684480F0D7735ULL, 0x9FA20BEDB7B90111ULL, 
            0xD46067A903D62957ULL, 0x3196A46A1B529437ULL, 0xA055054868E3A67AULL, 0xB6C05DFE884DDDEFULL, 
            0x55FD3ABF0C597B5BULL, 0x36D71366529B17D9ULL, 0xB43DD3E3444F28A3ULL, 0x4E6A38514E4F5E22ULL, 
            0x0CC6AA0DEAE340DAULL, 0x7495020F2B2BB52AULL, 0x9E6B2BCB638E7620ULL, 0x6A12958FC5F72EB4ULL, 
            0x1B0288D787CF2892ULL, 0x92D80D3EF1068BE4ULL, 0x4C148A051524C2D7ULL, 0x96E6F732024490BCULL, 
            0x149297BF54322AC7ULL, 0xD30E486B6C4B88E0ULL, 0xC51C0C689F4A6B30ULL, 0x3A3A574A314E1D3FULL, 
            0xDA4EBF73AE113866ULL, 0x09FAE1F05872271EULL, 0x12E0363BEC49527AULL, 0x26079E3B05885E72ULL
        },
        {
            0x031AB75B0BF4503DULL, 0x36A87DCF5956A105ULL, 0x4941094C6F9798A4ULL, 0xEFC4E0B47FF1F20AULL, 
            0x6A9F006DE0795E9FULL, 0x0ABD9FBEFE08930FULL, 0x907C20FAB172B171ULL, 0x7BFFFB78DAF74954ULL, 
            0x594796D7F39CE94EULL, 0x1CB671AA5012A676ULL, 0xF6641391493BB17AULL, 0x7AABA3D00751443BULL, 
            0x966EEB7B27B22DBAULL, 0xB6B63B775CC8D2D1ULL, 0x1B2257A1B77298DFULL, 0x8D0898D274D60616ULL, 
            0x7B206789C55E865DULL, 0x64902DFF39D3EB56ULL, 0x4CA4BD4BB27A370FULL, 0x6D3617322FA289DFULL, 
            0x6F3E1FDAAF8AA40CULL, 0x27DE79963A4EAF99ULL, 0x399728C999978993ULL, 0x5B489A308FA42933ULL, 
            0x5329677C4BB00462ULL, 0x7CDD553FC91D709AULL, 0x2146105FD94602A5ULL, 0x63A8AD1ADEF71F54ULL, 
            0x56BD02DD6F9EC23BULL, 0x8497A94183C86F6AULL, 0x8E9006E1B9D9A27DULL, 0x8B2D9F615A031FB8ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Arcturus::kPhaseCConstants = {
    0x5A3D1BD3EC854A5FULL,
    0xA30AC37E077803ADULL,
    0xF67484445CFFDD6BULL,
    0x5A3D1BD3EC854A5FULL,
    0xA30AC37E077803ADULL,
    0xF67484445CFFDD6BULL,
    0xB28B4F5232B5EF9CULL,
    0xF280E26D750F10E1ULL,
    0xDA,
    0xCA,
    0xF6,
    0x02,
    0x0E,
    0xFF,
    0x98,
    0x1A
};

const TwistDomainSaltSet TwistExpander_Arcturus::kPhaseDSalts = {
    {
        {
            0x2C7CDCCEDA51F822ULL, 0xB9BD3CE00C1D6C8FULL, 0xDE732559B5B8776FULL, 0x1BE56C08713F5C0AULL, 
            0xDA11D98A02E1C03DULL, 0x93DEC91BBCD88E00ULL, 0x13E9DB8B1388E3C8ULL, 0x6739504EB4CA4EA6ULL, 
            0xFA3AE2827C4DB448ULL, 0x8921380FE5962EF7ULL, 0x5814D69D9686C07CULL, 0x446FDA280764D800ULL, 
            0xA7664ACFF94F1804ULL, 0xC813B9D63140D2AEULL, 0x82DC2DDBD9132726ULL, 0x4FB9E5B6F63D4879ULL, 
            0x53FE660A3965E25FULL, 0x39CD2376891F323DULL, 0x5633D2A15A0CEA65ULL, 0x4FBA862212B1936DULL, 
            0x9394DCD384CAC55EULL, 0xC4F94B249D76C370ULL, 0x1D27DEC8E672FA03ULL, 0x8AF5B0F993EC7700ULL, 
            0xB88CC7E4AEF743C8ULL, 0x74AFFBE272CDE6D1ULL, 0x6B21B160E17F17B8ULL, 0x368A14661EFEBF72ULL, 
            0x9F7793B8EAC3E316ULL, 0x48F390CE3AE86ABFULL, 0x88F0FD9060BCD5F7ULL, 0x38A52BF87819786EULL
        },
        {
            0xB5DA3F7F92CEF533ULL, 0x0C8863D3050CE981ULL, 0xF03EE6A2404656E5ULL, 0x17B069A17972413FULL, 
            0xE95982867568F7D8ULL, 0x34519C8892E6B6A3ULL, 0x5F05A754A82D5716ULL, 0x1F50022F1B3D36C5ULL, 
            0x2F8A46D05CA2167AULL, 0xC1F044F5EAA82207ULL, 0xB543C6EBC014D240ULL, 0x731200277855B3B3ULL, 
            0xF2092F8890C0CD9BULL, 0x7753AA7D2A283629ULL, 0xC4C29E6E320E0A88ULL, 0x7903FA8175075D64ULL, 
            0xC667625C33BC26A0ULL, 0xB4664C1D2CD35D6FULL, 0x6FA7708CEDB3A9EAULL, 0x32A3FC59DD3E6E49ULL, 
            0x64971AA17B4BB5F3ULL, 0xAE73F8C239092CBAULL, 0x4230D548FC8B3C37ULL, 0xDCF8DD4C5DC7510AULL, 
            0xA8CA0CC1E3B85FE6ULL, 0x959222E085B347B1ULL, 0xF8420D87D8B279C0ULL, 0x2B70F37210E11F36ULL, 
            0xDA12C54D02A0FC46ULL, 0x7A924A58295B5AAFULL, 0x56A8EE617106614CULL, 0xCB1B52F0915DA470ULL
        },
        {
            0xE77EBB70EF7C15AEULL, 0x108441CACA084BE6ULL, 0x99A9F1018D6E3817ULL, 0xA1DE2C3F5F3FB7ECULL, 
            0x693FB4E93E32EABDULL, 0x6C8601C85CF641A7ULL, 0xA904DA97BE077D86ULL, 0x8165B9E067A6F979ULL, 
            0xE89F7379B4E83F31ULL, 0x8FCC767BD060530CULL, 0x52ECD35109674143ULL, 0xFC909AC0BA1163D6ULL, 
            0x1333F8137F47B00DULL, 0xE151D43E8E2605E5ULL, 0x100F50D8EDFF9AEEULL, 0xDB75560801EC5F5DULL, 
            0x9CDEC19849049BC8ULL, 0x2D832CA6BE5D92ABULL, 0x791194A0EF5FE4CBULL, 0x0D90A41FD59C09B1ULL, 
            0x32C1903AB4D1C1E1ULL, 0xB4F21626D49CF91CULL, 0x2463F2783CCA56ACULL, 0x4C11F796DF30B2E9ULL, 
            0x8056035B9D297E62ULL, 0x17306B3E72C1B8D2ULL, 0x2BAF9926E1C568E7ULL, 0x8AAB660A91B021B4ULL, 
            0x69696F30E23621FBULL, 0x6836E620A4227593ULL, 0x30FB4CA9F43F3CA3ULL, 0xE6107E1DFE68BC8CULL
        },
        {
            0x49508E369E67F498ULL, 0xD9CE702B29FC05AAULL, 0xDAC172970781E121ULL, 0x815CA874C9ACF5C8ULL, 
            0x3B6D4670C1AF1AEEULL, 0xCF3A1FB76379C7DFULL, 0x1763193AADF6EA83ULL, 0x39C526B0BC3DE43BULL, 
            0x01765DE20C01232BULL, 0x782616A20AB68DD4ULL, 0x90510AB6C93B6460ULL, 0x5FAE575DCE7A9A71ULL, 
            0x3368B291EB92F99AULL, 0xA234E15CE72BADA9ULL, 0x998B1FB925968321ULL, 0xC9626AB6FC252A7BULL, 
            0x1D9C9B36AC4BC7DFULL, 0x944B1E656E1A4C5EULL, 0xDD64BE25B28F55BCULL, 0x1E3EEBE5CDA08D26ULL, 
            0x921CBEFE5F12069BULL, 0xCAF17CE8CDAF8960ULL, 0x0E1C8BC868A6EBF1ULL, 0x365B1D5B98EFC5E1ULL, 
            0xCC74F117EAA92CA1ULL, 0xF0C8A44167BB7F06ULL, 0xE2767634A8C64D5DULL, 0x2AE66E835EA7B6DEULL, 
            0xF656E8EB3A9025FAULL, 0x2B8BAABC5CA31C37ULL, 0x42D1973A41418CCFULL, 0x058643455F1C58CFULL
        },
        {
            0xDAA1EDC84C8DD35DULL, 0x051BA68A879B7E59ULL, 0xB4B3ACEA4B9D6D5CULL, 0x96D7842FE83D1B6EULL, 
            0x3DBA30353F78089FULL, 0xC98079A92F358D03ULL, 0x1F28BD9BE82F7148ULL, 0x98693A7543179DC6ULL, 
            0xBA86F542E491404FULL, 0x89D2D77BF4D6B169ULL, 0x7417CA2F69974D34ULL, 0xEB4A645CE47478ACULL, 
            0xC9F7C47EBCD6263AULL, 0xF74854AE9A570104ULL, 0x257B9D82C56A08B5ULL, 0x2AF58A96F89B097EULL, 
            0xA2378BB34CABA334ULL, 0xAF4830022B8F25FAULL, 0x5BB08029FAD7AF85ULL, 0xAD497B812F00C641ULL, 
            0xDAB28851BE26E1FAULL, 0xB4A5F07FA349A68EULL, 0x3BE040C26E6A575EULL, 0x4371E218F68970CDULL, 
            0x1E7BAC95C7E5B29AULL, 0x2169AF69E1777B88ULL, 0xD2D51ECD67E3A0F5ULL, 0x7EE3992928F77A79ULL, 
            0x861BC371DB06D3F0ULL, 0x65115193A3EB3C79ULL, 0x55F29E50DE95B4F7ULL, 0x9D153855AB2D17E0ULL
        },
        {
            0xDF7D211CF5C1EBC5ULL, 0x1F1A34606D53C177ULL, 0xE43E36B8F0150FEBULL, 0xCB276D1881BCCD01ULL, 
            0x55DFD3C29CC64EDDULL, 0x3D8519847133A5F7ULL, 0x09B263CC520360CEULL, 0xF11C8D3C71360603ULL, 
            0xDFF6F205219D85A6ULL, 0x10A7A631C583EC43ULL, 0x9B835167452C775AULL, 0x7296F6047C7D123CULL, 
            0xD040CCEEA436AA68ULL, 0x911E0324800F2F1BULL, 0xDA5DE69B41C8423BULL, 0x3D7FB2D5DA3E769CULL, 
            0x4AA0AA30AEB51B83ULL, 0x30CB45619463141AULL, 0x556336995CA6A0D6ULL, 0x6F2BF71FC459F7F2ULL, 
            0x45D278F34E5BE5A9ULL, 0x05C031EEC06242D6ULL, 0xC79682050EBC0662ULL, 0x9DE71E5C37AE9B53ULL, 
            0x033425B6F290BFD5ULL, 0x4E407603222A94A6ULL, 0xB727628E72D8D858ULL, 0xBD5AACD13C085DB0ULL, 
            0x00F7F129A2707F7DULL, 0xFFDE6DC559F0B3E9ULL, 0x50B47BB4A2795F7FULL, 0x3CFEDE146C2F9F3EULL
        }
    },
    {
        {
            0x389622CFE95009BCULL, 0xD97E764830180DB0ULL, 0x345D3AA5ADEE0C67ULL, 0x7BE0B50CC25D87A1ULL, 
            0xF89241835750E964ULL, 0x7B6B48ED57878DA7ULL, 0xEAFAB9CA4836C27BULL, 0x4122BF2AEBF5310AULL, 
            0x795C2B35CC26052DULL, 0x2EFE912F025456A7ULL, 0x4A6AE081108EC443ULL, 0x9B653F2486CB10EDULL, 
            0x2B90E67E104E63CDULL, 0xA114784A3DE8972FULL, 0x2B6E6E447010BCFEULL, 0x906205CEF09F95DDULL, 
            0xA0245AD122B1CC8DULL, 0x7EE572BD460260BDULL, 0x1A8AE44BD1104DDAULL, 0xF1093811FF5C8877ULL, 
            0x4A389AD1D82741A9ULL, 0x9E0EB5E60907B3CCULL, 0x8E3958022F813C7CULL, 0xB86A5384ABCC4CF1ULL, 
            0xB3CDA9F6E843958AULL, 0x5F91673920CE5563ULL, 0x80DB113AE858C6B9ULL, 0xA13B2E8A71794DC4ULL, 
            0x673FAE60AF1BECACULL, 0x36145898CC6ECDFCULL, 0x1B1E9F05261E2617ULL, 0x1F5DAA227207CAC5ULL
        },
        {
            0x8685967960859220ULL, 0x991D06A4407C8192ULL, 0x2A8631BD17ED8F53ULL, 0x7DB4DD0D6432E70FULL, 
            0x08C02886ECFFD4E5ULL, 0x6B13A06C0484FA78ULL, 0x1AEE61E2FFE03073ULL, 0x96D92E9A08475E67ULL, 
            0x0914B9B70CA33222ULL, 0xB01758726E78ED92ULL, 0x65EFB1AD9D2C411CULL, 0x98A6CEDA5C99CD80ULL, 
            0x2FCC852B4BC85502ULL, 0x78D39CEA852442A4ULL, 0x60E4CD8D9E9D6270ULL, 0x32FBA6D7EC240A75ULL, 
            0x101E45D6A66987E1ULL, 0x4504B1D787105F1BULL, 0xE808DE4EF992946DULL, 0x8C615A37F0FA3D81ULL, 
            0xA43C55FC828A076CULL, 0x7DB41CFEBE914F79ULL, 0xF1E2E8B3C6CF98F6ULL, 0x35A587ECADFE9F59ULL, 
            0x1437A7AA87D2C39DULL, 0xE6DDE11C835D5482ULL, 0xC60097D3916D2DACULL, 0x0066C5E9A05EA8CDULL, 
            0xE62DAEF55A7BFC32ULL, 0xBE6E40EE85A29670ULL, 0xC745CB9B09F80489ULL, 0xAFE1D915784730E7ULL
        },
        {
            0x3E64318A30B63439ULL, 0xD22BF3B5756439D8ULL, 0xE0C6FA9209832A80ULL, 0x34EF645DDEDD3AFFULL, 
            0xA6D6BEDF8B888123ULL, 0x1FEB350BAE856AA7ULL, 0x1624F9657FCA6600ULL, 0x45FED1DF84043505ULL, 
            0xC01F7ED53D56938DULL, 0x382D7A613C1E54A9ULL, 0x14F5256B6F43AD5DULL, 0xBF595A86465E9B41ULL, 
            0x4098458AD7DA9124ULL, 0xDCA592F5FB41A3ECULL, 0xA2012797A753E168ULL, 0xFA21765C8027C336ULL, 
            0xDC64A3E4A2D302F9ULL, 0x0FD1150318301937ULL, 0xE7BF0C5B2D532B9AULL, 0x7ADA18A88BC12D2EULL, 
            0x55A6AD3BAC98A13AULL, 0x7CA2D9FF54B8A35DULL, 0x06E85F78B1A9F111ULL, 0x4BEF03B0035421EFULL, 
            0x7A9BBD78D145DEB4ULL, 0x8931CFD4B0AF85F9ULL, 0xC8EE37003DDDF026ULL, 0xE37A19FA870AECC6ULL, 
            0xED6FFBA71DA9BBFEULL, 0x5C11B654AFADBF61ULL, 0xB492D0551EAE1B6CULL, 0x55DC301F5FD1CC30ULL
        },
        {
            0x3F22CDFB64E51734ULL, 0x0DD3F7858997D8C6ULL, 0xADE749DEE23184AAULL, 0x9DDDD08F16BA18FDULL, 
            0x5C12BAA4D16D71C9ULL, 0x23EDF562F1F423A5ULL, 0x53B38D89387D7326ULL, 0x7F02092A58B74E5DULL, 
            0xD6AD72BD0EBF2F9CULL, 0x72F84845302140E0ULL, 0xAE24D34DAA6F13C5ULL, 0x5016A7BA51F85DF0ULL, 
            0xBB8116DF265A2E61ULL, 0x02120F513D909EFCULL, 0x44A61B839FB9B0A7ULL, 0xEA7814927EE988DBULL, 
            0xE9B880AEC461B4DBULL, 0xBFD7A23D7431CC0CULL, 0x04A325409F9AAFA4ULL, 0xFA13971FC0F5D505ULL, 
            0xAE0DB99103C50AD7ULL, 0x120B8346CFE9F3B5ULL, 0x11E4BF1D89D7B82EULL, 0xC8AD5210F639082DULL, 
            0xF5ECD7E5DEE876FBULL, 0x636D5058D8A5C5AFULL, 0x89B08B37E447EC72ULL, 0x68AEBB4A0E74F15DULL, 
            0x1235564DC46D066CULL, 0x19B78F7CDA332445ULL, 0x47524A3339D8BD3EULL, 0xC801F754A36F2C41ULL
        },
        {
            0x61C9338FB6EC4AB0ULL, 0x61F133442E759913ULL, 0xD707F97A80821689ULL, 0xFE9BB83D068C42CBULL, 
            0xE5AA7E07871AC02BULL, 0x2C74BC58D7F68836ULL, 0x1453A819CEC2B8DEULL, 0xD4E947055BF8EC31ULL, 
            0xA8404C50B1888179ULL, 0x616D754AAA2D5C6DULL, 0x2EADA60F802B1129ULL, 0xCA62DE960D6A03DEULL, 
            0xDE60C04C07AD6AABULL, 0x2803BC0B3568F7B4ULL, 0x0F0D94988D7EC810ULL, 0xD0D9499EF5DFABF0ULL, 
            0x5BD5FD6E0CD672A5ULL, 0xC4794EE45B1B3C0CULL, 0xEA0740F53F5DB2AAULL, 0x0A2587D3ED197849ULL, 
            0xA3C1AE9FF649DB38ULL, 0x9A9F2C308AF069B3ULL, 0x9F0B8B553FD7189EULL, 0xFEC4F1B89A89A297ULL, 
            0x2E9AEB466DF25888ULL, 0xE5CF47AF269DF3C2ULL, 0x959EE89AE086B5F9ULL, 0xC37E5363B58801F8ULL, 
            0x89A41AA0A37F46ADULL, 0xC3BB990835CB45AFULL, 0xE2F012862FCB8562ULL, 0xFAA6BD3F9FE23B70ULL
        },
        {
            0xD93C0DFFDF086995ULL, 0xEBC6D62116AB13D2ULL, 0xA9BB2CB03D7CF410ULL, 0x6B6C544B981DDAC4ULL, 
            0x353B8CB8D6BB22CEULL, 0x6A6A8C6E893FC2AEULL, 0x80002B965E953DD0ULL, 0x37DB10FF975D1768ULL, 
            0x1E3D39BCAA4610B9ULL, 0x4DD31FF03861B53AULL, 0x5C9551A3EAE471F7ULL, 0xDECDFFED1899FC49ULL, 
            0xD7421A1924373121ULL, 0x75E45BD97AA76D21ULL, 0x0960DC446DFFC6B2ULL, 0x5A6F29CEB1B4FF9FULL, 
            0xF84EE04765D7781CULL, 0x89FC128228F6230BULL, 0xF0D01414BED7DD89ULL, 0x5C0B31F25A8CC7F9ULL, 
            0x7DEEC82072422D4FULL, 0x612284C5BDCB5A6BULL, 0x1CBB0CA1DB22033EULL, 0x544C23F28C9EDC3BULL, 
            0xE1DC4C7A546D4C4FULL, 0xA3C37E824692D427ULL, 0x0F0D0C697490C659ULL, 0x3422B53342E42A83ULL, 
            0x04EB6D64100C3B08ULL, 0xE3F08D58BA3FFA70ULL, 0x5D6F59B4FBE3F4B9ULL, 0x5CD3047326CDBA0AULL
        }
    },
    {
        {
            0x7CD348D1AC76F40EULL, 0x2F0532E8D59941EBULL, 0x7BCC9B02AEE94222ULL, 0xB89EBCA85B795E95ULL, 
            0x20DB650D98217C56ULL, 0xBEFB9A4B8DC94EF1ULL, 0xCA2598857ED6B60FULL, 0xBA7D676A4DF8CAC6ULL, 
            0x0F9C65D6E6C2B22DULL, 0x7712E546D2528B46ULL, 0x83A5EF768DFE3367ULL, 0x4BA26B3C103CE9CAULL, 
            0xE2183462D29E1D86ULL, 0xE532669A0B65E2A8ULL, 0xBD4D09CC86794111ULL, 0x2F1A6EAC584D9A55ULL, 
            0xAF9D9E61244C27FBULL, 0x6219A10244FACA74ULL, 0x93AF25029F8C882AULL, 0xB54BC40C356189ECULL, 
            0xCE1BE4E710915EB6ULL, 0x529FAB9D8D2FB404ULL, 0x31B68F2DEAA940F9ULL, 0x8A4A0DAFED2379D5ULL, 
            0x1843F7FB2414846CULL, 0xC2104F734A9629EDULL, 0x7F1CC1CCAA077C1CULL, 0x3603DDDF55E7A3C3ULL, 
            0xD2C7B8E2898C7E38ULL, 0x4FA30D7426C55A6FULL, 0x744A5872D3442CB0ULL, 0x10DAA7D305A3FE1EULL
        },
        {
            0xE3EF86A352868717ULL, 0x3F8629FE0D082AD4ULL, 0x4F924599ABF19E91ULL, 0xFF573FABA1A12DCDULL, 
            0x4723410B42A5F985ULL, 0xD507FCE705FAD368ULL, 0x89607C69B8DD3609ULL, 0x16E37B7E24F10144ULL, 
            0xFAC8E8F9CC3C6C74ULL, 0xAAA70413C733D7E3ULL, 0x4BCCAB0F422B3903ULL, 0x7E8EFA682A6BB4D2ULL, 
            0x8EBCE3EEB9455065ULL, 0xA8BD905F40A38E7FULL, 0x89D0BEA2D901F5F5ULL, 0x95C2013729F8F583ULL, 
            0xEC4A6A2D423A3E14ULL, 0x2F695A67E96F5078ULL, 0x612A31AB694C1017ULL, 0x3B8D81FF53B52412ULL, 
            0x9F990435F991E237ULL, 0x99346A22D7702B56ULL, 0xAA0F72BD1B7AB1ECULL, 0x44A9F50B0C7F226EULL, 
            0x864FA138D34A0097ULL, 0xE16B1D384C4576DCULL, 0xC38B80CBE67EA736ULL, 0x8E9ECA66174608FEULL, 
            0xBABCEF616900AB02ULL, 0x0DD8EF16375B41EBULL, 0xFB378FACFA6EE88DULL, 0xBEF569BC2DFABFFDULL
        },
        {
            0x02E48FF1B2BA7293ULL, 0xC10BAB93B90CE0ECULL, 0xFBF7CED2DEE102B6ULL, 0x559BB968E4E6F440ULL, 
            0xF7F01752382378B6ULL, 0x3AD20B1C30430A2AULL, 0xDD015470A841892FULL, 0x3235FD9C7205BEF6ULL, 
            0x21351B1CE7B1318DULL, 0x8CE17133EF74CB5BULL, 0xD9B30B777E4F66FAULL, 0x46AAE2D1978E9150ULL, 
            0xA08727F9A8802702ULL, 0x73651EAEBD30FECBULL, 0x6AACDDD75ECE6708ULL, 0x8EBE3F25480511B3ULL, 
            0xDF99E25320DC90DBULL, 0x9D0E942652763B6BULL, 0x2F14C88EC45CDA5AULL, 0xB45CBFC9DE46AAF2ULL, 
            0x98A3C6708D97BE93ULL, 0xE3F5ADA531A080ECULL, 0x4C8068E8092BF992ULL, 0x679227931BCA9497ULL, 
            0x9E55DE1C74753C54ULL, 0xB7DF000370A7433EULL, 0x52C296949C95F0A0ULL, 0xAA7659D88986137CULL, 
            0x50B35F36F4CB4240ULL, 0x4E3D9AD502B88AF7ULL, 0x4C845747F02FADFCULL, 0x485C7CF07604F694ULL
        },
        {
            0xFD8920414A9436ABULL, 0xD35FC37538FF97FEULL, 0x7F63F9EBE9E00656ULL, 0x4A893C57EA6CF51FULL, 
            0xB5A601BE9C15D9EDULL, 0xEE1E8036F8D71F13ULL, 0x2050FEFEFA1A7289ULL, 0x491169020A9078F3ULL, 
            0xEA59F62E9D9CF87CULL, 0xD9F2A71DC91E1710ULL, 0xD6BA5F7D75468625ULL, 0x4184DC95819D985CULL, 
            0x96C6B2B9D0EE2F91ULL, 0xE8F5430C7D9F3052ULL, 0x4266A4E163184FB1ULL, 0x5CEA33B7BF56F5B4ULL, 
            0xCCD02EF9833ACCDAULL, 0xA7BE06D897C128C9ULL, 0xA1223950E8CDE800ULL, 0xB95BA0FD946E3A5DULL, 
            0x0473F9322A0F49B1ULL, 0xE76FFF4781633B37ULL, 0x188558DD924982A3ULL, 0xAC6DF6EFEAAE4F4EULL, 
            0xD5B735B5042F0E4BULL, 0x934A04D0797B5761ULL, 0x8C57D6A25AC85962ULL, 0x613A6A0EE6947DB9ULL, 
            0x127323E0F896FA8AULL, 0x43C1DF65D1129DA0ULL, 0x553F2D0F9D0BF1E8ULL, 0x854A76BEE4D72366ULL
        },
        {
            0x1705116C9B59053DULL, 0x7E5F986052EA618CULL, 0xFA23AB15709906EDULL, 0x572E8166FFA472BAULL, 
            0x66B8222AB922EEA9ULL, 0x92CDDCA56E34FC59ULL, 0x4B7A6D129C7FC082ULL, 0xA94CCF884737237AULL, 
            0xEA53FC4B435C7F87ULL, 0xB402444FB5876397ULL, 0x466A366A57193A07ULL, 0xBE5C266E44445F6FULL, 
            0x41FEF55E2643D8BAULL, 0xF40CE63D968C7642ULL, 0x4A45CA1ECB8DDDA8ULL, 0x20C0DD33D3F6104BULL, 
            0xC33F8DA3CDCDF562ULL, 0x1B7C29A628A60057ULL, 0xF6D3E09DDD4EA054ULL, 0x87C2724901FEA338ULL, 
            0x0660394CEEFD11C0ULL, 0x32BE9CD5689DDB0EULL, 0x73142BB45A847A7BULL, 0x56DFE099A91394A8ULL, 
            0x7D8FE870C9292FBAULL, 0xD4CC249646CFB2ADULL, 0x33B6933EFC0892E1ULL, 0xC117145631A2F301ULL, 
            0xBBAEFB04625AB0BDULL, 0x166279959202C747ULL, 0xBCF4C7FBBAF5F4D8ULL, 0x1C1EFEF210DEDCDEULL
        },
        {
            0x61F7064F771EA026ULL, 0x70B8634C57CA8CFCULL, 0x97C39E815CC46BDEULL, 0xAB9F2F365494E2E3ULL, 
            0x3DE2EA6449CDE460ULL, 0xBB4DAE66B61A55D3ULL, 0x2414299E3698A6FDULL, 0x776E3C0285B13AD2ULL, 
            0x6CE920230A687F96ULL, 0x1E3EE855E63A8145ULL, 0x1B451EE34A973710ULL, 0xE36ADFFCCE0F5ED9ULL, 
            0xA10CF04311AFEC3AULL, 0xC66D09D0EB45121CULL, 0xD982F37DFD952945ULL, 0x784E2103AA9A29C6ULL, 
            0x2582C282DEACCDCCULL, 0xA5A4C2677BBDEB0EULL, 0x3249EF0E93C05612ULL, 0x625E257C84730E64ULL, 
            0x7B745CE5175BA22AULL, 0x78C0B3C839193F9AULL, 0x6BC8D201D4EA0E8CULL, 0x91A83707790E4849ULL, 
            0x3165B76D1133E12EULL, 0xEDE4E9BCF9748C90ULL, 0xFDAF2CEEC82885D7ULL, 0xE29D463488A26CD4ULL, 
            0x53ABCD25E147D682ULL, 0xAC775B38DA732332ULL, 0xBFC815BD9D19C219ULL, 0x36600E9DD462C83EULL
        }
    }
};

const TwistDomainConstants TwistExpander_Arcturus::kPhaseDConstants = {
    0x701C6EDAD659B8A0ULL,
    0x7D7AD51F75A0263FULL,
    0x13483A04B1226E1BULL,
    0x701C6EDAD659B8A0ULL,
    0x7D7AD51F75A0263FULL,
    0x13483A04B1226E1BULL,
    0x7D303A87570AD733ULL,
    0xBC4CD584540628E3ULL,
    0xDD,
    0x1A,
    0x76,
    0x33,
    0x44,
    0xFC,
    0xFC,
    0x98
};

const TwistDomainSaltSet TwistExpander_Arcturus::kPhaseESalts = {
    {
        {
            0x6ECB1EACF99C5018ULL, 0x846B466EB02F0086ULL, 0x23FA964259A1EF31ULL, 0xFE7DED9928E85168ULL, 
            0x33C4FFCDB5DBC05DULL, 0x1C3A34D3A044842DULL, 0xEFB99F9A0F3BB471ULL, 0x7EF79FCE59E89179ULL, 
            0x226C685A530745F4ULL, 0xDFE2FE8D6AE33035ULL, 0x8B6184A6E0E3F056ULL, 0x4C4EFAE389BB6CCCULL, 
            0xC5DC0BAA8395D5E0ULL, 0xC360B54DA81D6076ULL, 0xE60DD9B1932386EFULL, 0x7B537E781E50FC01ULL, 
            0xFF22C283D051F55FULL, 0x9DA87C0475F7FBEDULL, 0xE9B57470D0BF2548ULL, 0xD4DE86D4E9E0FFA7ULL, 
            0x52AE710E9FC8A444ULL, 0x8DF630F79A0E0AF3ULL, 0xAB74E3E633E5540CULL, 0x6F8DCB17A300CBD6ULL, 
            0x878C45D4035BA007ULL, 0x7F4AE5CFB6D60B74ULL, 0xAD411E5614113716ULL, 0x60428B789B0409E3ULL, 
            0x4ADABAECB286E9D9ULL, 0x2CC52390BE54566EULL, 0x9C653B6E7D9C2D6EULL, 0x9CEDD7B2FB3002A6ULL
        },
        {
            0xD28045659A2A60B3ULL, 0xEA4230748A29F5EBULL, 0x21AD3754AE59891CULL, 0x6669F5961598D5B7ULL, 
            0x7ACCF6D78F9BAA2AULL, 0xA9E79EB495B244B8ULL, 0xA6CCD9D726259500ULL, 0xEECB858DAF11B69CULL, 
            0x26E1BD9CDFD151A3ULL, 0x684BC017E20830CAULL, 0x81C5B88C02D3EFCBULL, 0x0781CEE5244F90F0ULL, 
            0x57BB896BD0B6BEA5ULL, 0x2269D0249148CD0BULL, 0xFFF0C7F74D56A885ULL, 0x659A6C38466C34AEULL, 
            0x067C8F6AA7B4A174ULL, 0x99FAAAF133A45EC7ULL, 0x66D1CECA99CA4F5EULL, 0x4FA9813850D256B5ULL, 
            0x5A3CE3AFD5FEC112ULL, 0x67C9DE619C767123ULL, 0x7B951167911EDB89ULL, 0x642A81392D36C88DULL, 
            0x3777D5180549F90CULL, 0xFCE02434D564C7D8ULL, 0x5A3B53C4E49602E1ULL, 0xAA0448E60235CA10ULL, 
            0x626295A6052D350FULL, 0x760BE01ABA7867B1ULL, 0x7EE03B1072430553ULL, 0xCB1D808DCD68E5D3ULL
        },
        {
            0xB807789B8940CD86ULL, 0x0C1B085D9FE1C2B6ULL, 0x15FE9FA02C6E448FULL, 0xA94943F5645B3E5FULL, 
            0xF6EE3125C6A71246ULL, 0xD418731A40692D80ULL, 0xE92198AA68136BF5ULL, 0x1C48F223AFC161FFULL, 
            0x1CDFEED645D62DE3ULL, 0xED1ADA2105F8D74BULL, 0xDFC81B8752F79952ULL, 0x04BD3468197DE187ULL, 
            0x393A68F8D42E01E3ULL, 0x85DD56CED929F476ULL, 0xFCA20B5186DBAC01ULL, 0x293D384CAC782873ULL, 
            0x5DC6EBE13AAA8275ULL, 0x5D035C93958F9BC2ULL, 0x8229FB6B25818F2FULL, 0x0A1FFAB79E158023ULL, 
            0xB2B2D64B5D4E5BBEULL, 0x8020FEC26D174DAAULL, 0xBB80012FBD1688E7ULL, 0x7FABEB36FCFB1B53ULL, 
            0xB2F52B78A13EA4BEULL, 0x6A937E7FD698E311ULL, 0x04810E67F09C478EULL, 0xD25F98D4E4D8A3FFULL, 
            0xC866FBD7D36A38A8ULL, 0x43BE614E902F202CULL, 0x22E75A76ADA9FD43ULL, 0x7E53C172CD8CE0D1ULL
        },
        {
            0x89E3F0BAAE727044ULL, 0xAB961FDB19562C67ULL, 0xFEB3102C41B765A8ULL, 0xB08B0315707013CDULL, 
            0x6F030365D8043A81ULL, 0xACE5CE0764190288ULL, 0x3497115803A22E10ULL, 0xE85BDEBD9D6CAFDCULL, 
            0x542AC7B4E664EB0BULL, 0xC30183835192C7FDULL, 0x60072C5C6EBA789AULL, 0x2C4FC529D81F12C8ULL, 
            0x0ADDBE24DF34D92BULL, 0xEF4EBC7394216A64ULL, 0xAD49D96E4A10D8B0ULL, 0x03846B0EB8008052ULL, 
            0x3214A1E17C27D4C2ULL, 0x256343C622DB79CCULL, 0x07A1CBF6B3A36D10ULL, 0xC73FAD320C359DE7ULL, 
            0x7347BDC9CDC41468ULL, 0x1B025FB060B87808ULL, 0x51A45D4F256AFF84ULL, 0x2047F79C39A10F77ULL, 
            0xE51C870F62E94092ULL, 0x45388998060D574CULL, 0x73DEDDB94F46044CULL, 0xD6EF0AD773A8FA60ULL, 
            0x9ED7AAE79439AF39ULL, 0x1FD1E0F8464F2C60ULL, 0x7E703177D6D629C2ULL, 0x0EA02E58B55BB1C3ULL
        },
        {
            0x2AC0B8A925B555AAULL, 0xDC3658E8B2FDAFD0ULL, 0x2B07F79906E4DD6CULL, 0x6F143F696CF6414DULL, 
            0x82CF7F7E30FC2C6FULL, 0x2B2B86D72E2A3C0BULL, 0x07C7D40EA0275D68ULL, 0x3B91AD6863DE5C44ULL, 
            0xD470CEDCEDDD918DULL, 0xBD149FD85EE58474ULL, 0x28B6086E75F585A8ULL, 0x97C2763727DC29E1ULL, 
            0xEA8C2AB262701AB0ULL, 0x90031048E87E7D80ULL, 0x442C95DC1BADC660ULL, 0x223CA05D55E4E608ULL, 
            0x07752ED54B32DB3EULL, 0x2D0F97863E396AD2ULL, 0x866739B063A84E06ULL, 0xE8E19CCE6CCBC4B5ULL, 
            0xAABB1062AF4EC6B3ULL, 0x24247E9D51A87D0DULL, 0x9CEBC9D576ED22D3ULL, 0x887B8AF3141B67DCULL, 
            0x35DE14E200E60E61ULL, 0x9AB5DF913B5962C9ULL, 0x381657B134765FFAULL, 0x59959FC86A11564FULL, 
            0x59AF6BBDAD3EFA27ULL, 0x7B17E0B65682F7DFULL, 0x3C41C6D38DA4B549ULL, 0x03BC9523873B80F9ULL
        },
        {
            0x3AFD978DE574F3E0ULL, 0x426D36E8CAF9507BULL, 0x280972C1359E05DEULL, 0xD4BA3968938DCE15ULL, 
            0x174D06A438E2F9F9ULL, 0x9BF148A9A6AFE169ULL, 0x2AAAD91F231CD544ULL, 0xFB69CCC1281B0E65ULL, 
            0xDB3BF79D2FEF012DULL, 0xE8ABCB6199622780ULL, 0x3C25DAB7232A5FE7ULL, 0x92CE0E80ABDB7191ULL, 
            0xF5DBD8B2DD3E618BULL, 0x27737A80A0889A68ULL, 0xAA5DAE89AEDCC082ULL, 0xF1352F2C40BBF3C6ULL, 
            0x96CF6A4962F3A2CAULL, 0x8F449BFF921B0796ULL, 0x34C3D5747F0534CCULL, 0x6D9BD00CC3D8BAA4ULL, 
            0x3886256F339E98BCULL, 0xA01ABC30CC38D3D9ULL, 0xAB9FDE97F74E0546ULL, 0xAB18A8F4FCD08DFAULL, 
            0xD46A77E52DB30B07ULL, 0xFD923B2BE2F045ADULL, 0x1D8AF37500E2F69BULL, 0x1EDAEAC02299C4F1ULL, 
            0x440AED14EF337BF4ULL, 0xCC72F4B46DB9A1AAULL, 0x920ED0038ADE33D2ULL, 0x1AC7FD40F35396F4ULL
        }
    },
    {
        {
            0x71C5C9B1818E32A8ULL, 0x88E534AA31606D6AULL, 0x4F5A4561BF6A7DC4ULL, 0xA3F61DE5A2B5533FULL, 
            0x848BB81A026C8C9AULL, 0xF8337611A0F98AD1ULL, 0x5085332604FF9D2DULL, 0xCE4959E6B9C03BBCULL, 
            0x68144AEE6437F850ULL, 0xEA07B4720C0EF305ULL, 0x3648C4859ED50127ULL, 0xB56208F3A2F77985ULL, 
            0xFDD388FCC442FCD8ULL, 0x0161B91C7FAD22E7ULL, 0xB03E112EED7A6031ULL, 0xCBD2A388DC102CF5ULL, 
            0x7C3C81E97B1F6915ULL, 0x4ACE6D5707A5F101ULL, 0x9099B6FC650056D0ULL, 0xA8C601658FD3CA0BULL, 
            0x42CD90FB255A1C79ULL, 0xBB4279904C9A375FULL, 0x0706579C650EE3ABULL, 0x7E01768A678DBDDFULL, 
            0x03B58B4096A75409ULL, 0x5FFE488114E5967CULL, 0x09B9CB0E174E9CB6ULL, 0x93924A4A74B13C98ULL, 
            0xAEEC92770BF414ACULL, 0xB527724F286033A0ULL, 0xF658EA12B7064376ULL, 0x6CE60574F3582FFAULL
        },
        {
            0xF85602ED0B91ADBCULL, 0x837136BD597521D6ULL, 0xE1D489486267AE54ULL, 0xE616F12C4466A1D1ULL, 
            0x810D8A1B195F1ECFULL, 0xB2D4515797A502C9ULL, 0xE08CB7FDE1E2C83DULL, 0xFEA556F8047002A3ULL, 
            0xEA20756118F2C94EULL, 0xDDCA5A4A29166D5BULL, 0xBDD44B00304C6DE1ULL, 0x65FF677755336F4FULL, 
            0x270224117080F49AULL, 0xEFF2311E6806A2CAULL, 0x509350FC2335B859ULL, 0x1EEBD61EE235A78AULL, 
            0x944451A0F396FF96ULL, 0x6AD2B0124674187BULL, 0x90DB279BAD3629A4ULL, 0x632688A4543638A0ULL, 
            0xE711AF90ED088E01ULL, 0xA6DB60D93AE829F5ULL, 0x91B8CF967826A487ULL, 0x5B428C19F3EE0A02ULL, 
            0x91F111369A99D98BULL, 0xD50074D868CB9F35ULL, 0x5EB810760DA28385ULL, 0xFC36C18308D5BCECULL, 
            0xF506E1C7D9FA5DFBULL, 0x9D352CC02FFF4D71ULL, 0x6356F1BF624BF1E5ULL, 0x9E5B9FF91DC56A96ULL
        },
        {
            0x5D5688786CEBAA1FULL, 0xE8753476038688C3ULL, 0x513D3883C617C59DULL, 0x41BE9F183A0F76EFULL, 
            0x3E97DD385A36579DULL, 0xED5DDE8FE53FC6ACULL, 0x65498CEBBD281C8CULL, 0x7F1A64D297E761DEULL, 
            0x8640711AD9267ABAULL, 0x90CDB40563129B48ULL, 0xA9D3505B6D1DE65AULL, 0xEE7DBCFA94E29C5AULL, 
            0x3D7FA3D8CB411D8FULL, 0x9C89A2B86DBA916BULL, 0x9591D652598CD026ULL, 0x6B6A40816830F222ULL, 
            0xE6610AFD69703EE6ULL, 0x4E12095A98A49005ULL, 0x0DADAEE3C771CB36ULL, 0x32A0ABFD6B68573DULL, 
            0x4A0E662423B115F3ULL, 0x0366731156597E4DULL, 0x40277B1DAC07C2D0ULL, 0xB48A0F01D781BFF9ULL, 
            0x6A6E8F9D9D71C9C6ULL, 0x5B16985C41403EBCULL, 0x4AFD29AB69766F7EULL, 0x222E534E4C419F3AULL, 
            0x48B5B3FD2B3AF714ULL, 0x1D1266BBF2CCC3ACULL, 0x2D486510F6BE703BULL, 0xEB11C5AC96BABF0EULL
        },
        {
            0x01BAAC83DAA35A66ULL, 0x8239EDBFA3A2F055ULL, 0xC78946335B25CF78ULL, 0xD5388040114C243BULL, 
            0x3BB68589757B3E73ULL, 0x36DA2DC663CA63E1ULL, 0xA4B1771D37AF4918ULL, 0xAA90CC965AFA6A16ULL, 
            0xE1B919A8DDD20A9FULL, 0xF3F6F24BC63AC365ULL, 0x03B3672588C6667EULL, 0x16EEE00AC8AE04B0ULL, 
            0x9974995D74870086ULL, 0x81E2FD8D6C101DFCULL, 0xAA5CC9DC72D1A133ULL, 0xC9D5B68E93BA18C5ULL, 
            0x47DACADE6B0C8839ULL, 0x890BBD001662007EULL, 0x0B28F1B077FDC070ULL, 0x9B8F8E162E136C01ULL, 
            0x552C9AC577960476ULL, 0xDD4DAAC1D8775962ULL, 0xC24578273E0F4D1BULL, 0xA2C23D24CDE4678BULL, 
            0x17B5F7A1FAEE4901ULL, 0x602CD38564D5F3A9ULL, 0xEEF12A36CCE5E065ULL, 0xAA912AA5BB71D442ULL, 
            0x295C111269918505ULL, 0x5195CE302CA44301ULL, 0xD11D29C0380BF20EULL, 0xFC407C326D1557C8ULL
        },
        {
            0x925AE3ADC98DB73CULL, 0x5FFFFF42F10B75D8ULL, 0x1A1433DA8A2244A6ULL, 0x28FAF85D79ADE239ULL, 
            0x6B1080236814BE91ULL, 0xFAC111765B6152B8ULL, 0x903D5801CA357DF1ULL, 0x1A0DB03DCC04E9C0ULL, 
            0x1226F0297010A607ULL, 0xB2C428D1CA52A57EULL, 0x6299482E1A5D055DULL, 0x6EA920AA9182BC83ULL, 
            0x6E7501EB11800CAEULL, 0xE50C8B60E80C07BDULL, 0xF593CD35D89BD73DULL, 0xC06F7CCDF1DC9196ULL, 
            0xCF328ED7F98B41EDULL, 0x494A3F80EAA59141ULL, 0xF6C36535C765F80BULL, 0x4670A063416F6682ULL, 
            0xBA5127E293FB2017ULL, 0x32653AA24E2DFB58ULL, 0xD44CFC10B644A136ULL, 0xB4ABF2558743B819ULL, 
            0xBDEC49137948D122ULL, 0x836CAFD2A57EBF83ULL, 0x96C697C6ECA6E8F6ULL, 0x2D674C5240F8AC55ULL, 
            0xCD72F6EBC244D35CULL, 0xA047C52BA04627E9ULL, 0xD31AE3AEE9C63C5DULL, 0x36F1C9B2AB43B1C0ULL
        },
        {
            0x275BCA94ABA8C3EBULL, 0x876A821431986865ULL, 0x3E52AF72B351631EULL, 0xA25667CB687BAA0EULL, 
            0xCCF1780781DC3B21ULL, 0x350B97EA29B92DDBULL, 0x00506F2F939C37F0ULL, 0x6A269F566877C186ULL, 
            0xE6FF94D6057FF512ULL, 0x2CE23E5DDA27F326ULL, 0x5ED7CEE43C9464B1ULL, 0xF33A64204BF16836ULL, 
            0xF8471322AE5688B2ULL, 0xEECFB1A314A5F020ULL, 0x35B08ECA83B20705ULL, 0x67896FDD370235EAULL, 
            0xCA521AEDD9163EB0ULL, 0x9DB3BE098C228930ULL, 0x09CF0DEC3AE8A025ULL, 0xFCD6FC9DA5414EACULL, 
            0xAA1A13D9E898CDE5ULL, 0x5DF98239E066537AULL, 0x3063E0476B5CD808ULL, 0xB504BCC0E759C263ULL, 
            0x179098198899D814ULL, 0x79670D92471E007FULL, 0x982038EB887A0C51ULL, 0xE0CE79D26A9A8693ULL, 
            0x20910D550986B8CEULL, 0x332028FA667F7373ULL, 0x9DEBD8B6D4DF6788ULL, 0xEE1BFA1AF882272CULL
        }
    },
    {
        {
            0x1AA7E9D0ACE198B9ULL, 0x36076016F64581F5ULL, 0x7824206FFC1162CBULL, 0x8B1F1FEF2D9CC3F4ULL, 
            0xDAF5CEF4950FB86EULL, 0x23C7AB596BCAD0A9ULL, 0xBF24CFBAA9941C4BULL, 0x136A0EE353534FDAULL, 
            0x527AACB20D3F317FULL, 0x655F62DBF6282F57ULL, 0xD5D986B9942B3BB9ULL, 0xA04F15A6E9D2C90AULL, 
            0xAE95B45FE1D8DA53ULL, 0x5FE2FD1D2AA77D71ULL, 0xC2CEE9FA92622DFFULL, 0x93F7A7123E46C7FAULL, 
            0xADA9325F7DE12659ULL, 0x0B123C1DCDE911C9ULL, 0xA651193EC9F7F27CULL, 0xC4EA1556D512B5FBULL, 
            0x96465DD30DA44D7BULL, 0x150A47CB66F78FC6ULL, 0xD05E868B69FEAD8CULL, 0x72FDC893991D2866ULL, 
            0xAAD3850DAB0BC01BULL, 0xDA7A05D88877E069ULL, 0x56B1BF9D0E93D352ULL, 0x5B5518DEB9C10010ULL, 
            0x3567063DC06C90A6ULL, 0xA07B4DCF8116B7BDULL, 0x8EEEDAF2F206E464ULL, 0xA211164180A7E577ULL
        },
        {
            0xEAE61C340DB8536BULL, 0xEF26926FF7BD5248ULL, 0x6A39D84F1E43E83BULL, 0x4DAF45F06D9F7D37ULL, 
            0xEB51CCCCF28B3095ULL, 0x31DCC5C9C81B599AULL, 0x1B07710E0A8C71A7ULL, 0x937488372BACFF29ULL, 
            0x197049D1DF7855E0ULL, 0x3A59F615AE228501ULL, 0x2D231869C451CD29ULL, 0x4E7FA8951D375D5BULL, 
            0x5107A48F60C0A7EFULL, 0x240E26ACC24CB344ULL, 0xBE94B3315BB78CDBULL, 0x1C15B1406040B63BULL, 
            0x00CAF770E3EEBBE6ULL, 0xBF235422DE5AAB6DULL, 0x22BC59A33DB3D855ULL, 0xCD2A8C748397403CULL, 
            0x8002C6B52C17F5B7ULL, 0xD9FD2F8ED6E27DB6ULL, 0xF272FE21CD0D4421ULL, 0x4C6EE9FF9BDB4FDFULL, 
            0xBE524B64096F54D8ULL, 0x344D6917DFF0D379ULL, 0x730279F2E693B6C0ULL, 0x11E35A904C0871CAULL, 
            0x25BEA86B3039FE9FULL, 0x3257A681406D8BD2ULL, 0x5651AFAC6F75224AULL, 0x75C6F8A00E7C5E7CULL
        },
        {
            0xAB434F21D05CD155ULL, 0x63B2F7E368C246E3ULL, 0x73FDEEF82462026AULL, 0x5844D29CC631C13FULL, 
            0xEF8FA142772B1581ULL, 0x0BA611DA4EC53148ULL, 0xADE8DC8EA0CD736EULL, 0x716500821A4598E8ULL, 
            0xD2C71B7569A4009EULL, 0xA4550409CB1B2940ULL, 0x91C0E47D55B5CF2DULL, 0x76677527BF48B191ULL, 
            0x0852F73B200B58A1ULL, 0xF91FEC346F4DD74AULL, 0xC7C658178AF48D10ULL, 0xA569BD8399DF057FULL, 
            0xBED5791415E0E060ULL, 0x72B97B89E9BD30E0ULL, 0xAF38772B777DEBD3ULL, 0x10E68B9E6DE2E255ULL, 
            0xC6FA421A93508220ULL, 0x6B8F69F4F83A4EEDULL, 0x8186C517C0BE9418ULL, 0x4516EA555688B173ULL, 
            0x591B1A89C2DDB44EULL, 0xDCB85CA8BF6B73ECULL, 0x5AA4AB8D5EDCDEE1ULL, 0x2840CE7E7DD2B94EULL, 
            0x7AA60204ED332C8CULL, 0xBEB01DC7270AD8B4ULL, 0xB4D042C0FAAE86E5ULL, 0x43818307F1FE8033ULL
        },
        {
            0x3D4252143104593FULL, 0x8903BF78582FC92DULL, 0x8D2F6E3F15806CECULL, 0x08E637863AEF9ED0ULL, 
            0x1952FA65C59FC009ULL, 0xEFAFD26F74310163ULL, 0x588C4581BC21B574ULL, 0x15098DBC57632C10ULL, 
            0x860E20AAE19771A4ULL, 0x5A56C0890E0FB277ULL, 0xF21F0D123C99D0BAULL, 0x300B3ABA8BB0D588ULL, 
            0x98674D4D729AD835ULL, 0x502D0ED4AED5DE90ULL, 0x94D66784967E9A13ULL, 0x461378D5A2720C5FULL, 
            0xFC489281C68B6C47ULL, 0xD6DCE3610982378AULL, 0x021701D7BE873803ULL, 0x120D550BCD0EED07ULL, 
            0xF0BA473ADBAC1D52ULL, 0x95F1F02064B2A3C3ULL, 0xB1184764B57245C7ULL, 0xE57C8FBFF2DE1080ULL, 
            0xEB0AB7F583B70632ULL, 0xCCA4D77E8ADAFC69ULL, 0x1A9A22ED7309FBE1ULL, 0xEE081C0FFAB3B37AULL, 
            0xBE6A2E9650B36C06ULL, 0x2E1CE6DD8E33CCF4ULL, 0xA5B42AAADC483102ULL, 0x994ED7323CB63FDDULL
        },
        {
            0x3A75222D9BBE11ECULL, 0x8315F34755E3FF20ULL, 0xE2E09054E6D2DAB4ULL, 0x07797D6C0CEACAAAULL, 
            0x2515E2D409BE1B1EULL, 0xE58FA0D89E3C779CULL, 0x46D8EFB68B53FAA4ULL, 0x5686198295F9B081ULL, 
            0xA9DE9788777C2DA4ULL, 0x3B5F9313ACF97965ULL, 0xBBF3DA8694168ED1ULL, 0x4528DCC4257D4C0FULL, 
            0x956BC1C9FDDDCAF3ULL, 0x820ED93483B9F706ULL, 0x86B7C0070514D453ULL, 0xC4BE810FCAB0BE3DULL, 
            0x9A0ED089CC372EAFULL, 0xF44BD048FA4037FCULL, 0xE04A21FC6D844043ULL, 0x646AE3324F468CE1ULL, 
            0x9D6E8A1D2687C771ULL, 0xAECD94A961950549ULL, 0x3E014347FF1CD1E8ULL, 0x3374F1647D487F77ULL, 
            0xFAE9C4043332D51CULL, 0x2DCA22A722B193DFULL, 0xE088C353A173FDDEULL, 0xF83E6DE973C49DF8ULL, 
            0xB031207BDCD09769ULL, 0x862E75F1B2D38BDCULL, 0xC00AEE1D3D69ECA2ULL, 0x80B2C812ECFAF050ULL
        },
        {
            0x28F4B72EA701415BULL, 0xF7418A975757FC5BULL, 0x26245FF3C99891E1ULL, 0x3E58C468EF606556ULL, 
            0x4A8C68859F7276B7ULL, 0x3CA4CB1F5DA860C9ULL, 0xE54412B54C6FB9F7ULL, 0x115609143459C99AULL, 
            0x90B2836F0E57A3DDULL, 0xF89A3FA15B5848F7ULL, 0xE02F1EBE06AF5E9BULL, 0xD3A5681FE7AB63CEULL, 
            0x8F38FD958B6EBBFEULL, 0xD81D831A525D1C0BULL, 0xCD200E9FD58B2E43ULL, 0x95545CD83A53CF7CULL, 
            0x648DFB3EEF568505ULL, 0x7CB6FB7263C69151ULL, 0x18E5E23CB49102EEULL, 0x239D394699F326F1ULL, 
            0xFF5B5B704BAFBCBAULL, 0xFBDEBF69C46AFA48ULL, 0x67B488B5452191BFULL, 0x8F184B1B5D4CA7C5ULL, 
            0xA81AFB24F57DD8A4ULL, 0xC6441FC7CD0851E4ULL, 0x7D148D9E32C7EE1AULL, 0x5BD93FAA84BCF164ULL, 
            0xEC00FF72EA0957DAULL, 0x525DED39CA0A6B2CULL, 0x4055A806D44AE96DULL, 0xBE6E101E331214ABULL
        }
    }
};

const TwistDomainConstants TwistExpander_Arcturus::kPhaseEConstants = {
    0xE94D22A0F50ED529ULL,
    0xA9FAC8CEB994E9A8ULL,
    0xBB7B3433FC9813B2ULL,
    0xE94D22A0F50ED529ULL,
    0xA9FAC8CEB994E9A8ULL,
    0xBB7B3433FC9813B2ULL,
    0x2817F711C45B672FULL,
    0xD843646CDA0A3519ULL,
    0xAE,
    0x7C,
    0xAE,
    0xC4,
    0x91,
    0xEC,
    0x2C,
    0x59
};

const TwistDomainSaltSet TwistExpander_Arcturus::kPhaseFSalts = {
    {
        {
            0x72E3D2D66665CF54ULL, 0xE23CD58E4BB06B7DULL, 0xD17F0D2C29DC1773ULL, 0xD5C3338417A29803ULL, 
            0x87205E523FB50497ULL, 0xF0B0129B8E997CEDULL, 0xFBD5FDE316236F68ULL, 0xE3B558AFC6301CF1ULL, 
            0x86722C6520A5D2C4ULL, 0xB44FFA85E37BA2FFULL, 0x749838271EE0575FULL, 0x2AB8AE5F49E3E467ULL, 
            0x939532839949F1FDULL, 0x24DE96A8F64B53FFULL, 0x2E2CE59AF9835F58ULL, 0x53916EAC8DBAB1D4ULL, 
            0x3F282A2BB4347525ULL, 0x80F5DC304731A7D2ULL, 0xE75BD196530BEF03ULL, 0x1503CD7EB9BC7F75ULL, 
            0x71B17B483F40D5F0ULL, 0xF115D9AF5F5DBBEEULL, 0xD4B69A243D71BE95ULL, 0xFEC78EA89FC13644ULL, 
            0x29F3C92E15FF2E18ULL, 0xCD42E92956F43F20ULL, 0xB2A4E809776A78AAULL, 0xDD4318CA9A6C1769ULL, 
            0x0E21C6B8D800AAD9ULL, 0x2DAA25F47822DDF2ULL, 0x29792D09D0D4AC1AULL, 0x1D7299FA51FA01C1ULL
        },
        {
            0x4EEF3635925CCFFBULL, 0x60BDD497E6F71893ULL, 0xD071C7090BC1850BULL, 0xA8EBF1159F4A6667ULL, 
            0x5E0C9070C3FEAFA7ULL, 0x388CD2C21AFCCF15ULL, 0x35DD21A9ADC6C2FCULL, 0x19C278D7FD8D0D8AULL, 
            0x67C9E8D43B377253ULL, 0xDA74CF447C3BB046ULL, 0xA8977F0A47E0B668ULL, 0x1CE29D5DB72EED72ULL, 
            0xECD1EF2997BBC10AULL, 0x2DD22324DD6045DAULL, 0xADEE35686F3A136FULL, 0x97257BCE0D0DB233ULL, 
            0x842F79C194E98006ULL, 0xAE7D233F1039F556ULL, 0x2B1F7A5DC69D75D6ULL, 0xDAF017214E145E41ULL, 
            0x90CE9A3A30402557ULL, 0x27860C73906C47D0ULL, 0xEBF9DD640D5F259DULL, 0x89544848F0E40F78ULL, 
            0xCF7A577D891D28FAULL, 0x66312BCF016B0E63ULL, 0x3195E5055FA640EAULL, 0xD9AAF054DC777DABULL, 
            0xB6122C4BF916FB35ULL, 0xB4653979CF6C482CULL, 0x20D10B2F8D9D5DB7ULL, 0x384E76C652587182ULL
        },
        {
            0xB82FB7B671463AEDULL, 0x30EA5A0E889ACCC2ULL, 0x7738BC9889EEA9AFULL, 0x9188E335E7C40AF2ULL, 
            0xBF4DC7BD49456748ULL, 0x58D0839BCC5C57ACULL, 0xAAC1E8BF1ECCAD8FULL, 0xE4DBBEF41F612E64ULL, 
            0x31F274B0879F9D74ULL, 0x62D55584DF4CF060ULL, 0xB8D5852877855197ULL, 0xA61A0FD85ED64E29ULL, 
            0x5B3EACCCB301B78BULL, 0xF01F3367CDE0F1E6ULL, 0xC4B1B725F4CBF000ULL, 0xB4F2C39FB7C60996ULL, 
            0xDF1641AE4B87069AULL, 0x4A1A3777CC104386ULL, 0xA879F28B16C9328AULL, 0xC106D28B79C42510ULL, 
            0x8EE9A8605EEEA482ULL, 0xF28FB1715FE5EBE7ULL, 0x4BB10C499A9ABBB3ULL, 0xE6856D5C4D05360EULL, 
            0x21EC00BCCF07B97FULL, 0xAB74746D3A5A4F70ULL, 0xF26333EA8BD67DE8ULL, 0xCBCF26BA03B8A442ULL, 
            0xB4DEEEB90C14C8E0ULL, 0xDD8247BB3DF21CADULL, 0xB5A022629BD21DFDULL, 0x5D7ED45D4398B9C2ULL
        },
        {
            0x7AB88C8E4CA1AB6FULL, 0x6A4E8836FD4F44ECULL, 0x5E4D86E8E2D0CD3AULL, 0xB3027E83F5A74A9DULL, 
            0xC931FD43F773E649ULL, 0x985C07E02A257A4FULL, 0xDDB87F94615A9B3DULL, 0x309DB6B8353D22B5ULL, 
            0x58F5FEAD1C60B515ULL, 0xB00626C4F3026C72ULL, 0x218A0650862E1284ULL, 0xC8D116AC7B03F5D3ULL, 
            0x83CE1BFAD0AD43A7ULL, 0x5CB071357E67C9C3ULL, 0x0DBF615A7A519056ULL, 0xDA63380056E544EBULL, 
            0x87AF050B7D78BEC5ULL, 0x7B451B8B0FF4E634ULL, 0xEC8B05891881D7C7ULL, 0xE713F63A671117B3ULL, 
            0x2BB33D7787B3E667ULL, 0xA77D92D86C294A47ULL, 0x21A75C455F69C9DEULL, 0xBD91B6170BCAA195ULL, 
            0xEEEA8D1C92D02376ULL, 0x197AFEF044E17ACEULL, 0xC2FD39CB0795A318ULL, 0xE3F9BDC9B160855DULL, 
            0xA1A4CD39AF4E7D6DULL, 0x87DABDB40AABEF6EULL, 0xD6AB87BD3C71E636ULL, 0x6A3EBF543D017306ULL
        },
        {
            0x75D979EBBA3C2961ULL, 0xF2B59B300E9DC866ULL, 0xC042CCBF520632FAULL, 0xB6D065D3F15F48C1ULL, 
            0x466AA6B08810A986ULL, 0xAA695642687D620FULL, 0x17EF6D20858EF0D5ULL, 0x0F22246C4C23FE02ULL, 
            0x542E474E27D0CB28ULL, 0xEAF525EF31B8AD21ULL, 0x9C8F705F59D3AC26ULL, 0xCAD0FADC173BCF37ULL, 
            0x0F327458EB5F566CULL, 0x97FF2E22D294CE7FULL, 0x54F51D59DB9A6167ULL, 0x9541346113D4339CULL, 
            0x2E4B98D733A4D0D7ULL, 0xAF643E798D0A0C71ULL, 0x15FF939EC021BC7AULL, 0x00603E750D15D9A0ULL, 
            0xE51142153D0E565DULL, 0x6172B473280C688CULL, 0x5DACFE196AFE3F24ULL, 0xA06B4BE4120B0EA9ULL, 
            0x908A67B9D082CD59ULL, 0xE37FE036A1A5A873ULL, 0x1C97009A4F0E140CULL, 0x7FFD13A0FA3CA968ULL, 
            0xD636A7FC5A0614FDULL, 0x0FD22CBB1DF5E4C1ULL, 0x93139DE7828674E2ULL, 0xEA600879E4C9EEE1ULL
        },
        {
            0xA1DD66BCC6E8B8D5ULL, 0x77C659E2CEBFF819ULL, 0x02213E834344A25BULL, 0xE4613534E89DFB8AULL, 
            0x3CE0FBCB40F21CFFULL, 0xF33EBBC19867BB07ULL, 0x51C7B72747735237ULL, 0x3E36E7C9FE53DCCCULL, 
            0x655466D9EB153BDCULL, 0x7DBE2D8A88F4D787ULL, 0xD65D682866875BCCULL, 0x8CD3E7B3C5E29971ULL, 
            0x2B736E2F59FFECF1ULL, 0x0F7C757CC01B8A79ULL, 0xF085C7A3759C55B5ULL, 0x981AB062CE30DDACULL, 
            0xE8B64394E08BBFCEULL, 0xE553A8FF1798E99AULL, 0x3E87F264069CD466ULL, 0x457608BB6F0E0822ULL, 
            0x39A064F11082EDB7ULL, 0x1A6C349E9B35F6ACULL, 0x1D2D09FFB5A07DADULL, 0x23A95AFECDCB40CEULL, 
            0x0BDA27C3FB25240EULL, 0xAD19601123DDCE71ULL, 0x5ABE384F37243B76ULL, 0x981E841B59987271ULL, 
            0x6949815930B5648FULL, 0xF70AABAFCF93CE63ULL, 0x21FB93B45E2EEBFBULL, 0x2B5D3397D668DE7BULL
        }
    },
    {
        {
            0xDDDF9332FC0F7B00ULL, 0xDB1280CC3D5ABE01ULL, 0xC5E6A6A3CF0A75D1ULL, 0x71BBBA54F69D21CFULL, 
            0x4BFBAEF2F4C45A2CULL, 0xB92128BC93178E4EULL, 0xF202E972DD82AF3CULL, 0x97C1CC5641ECAF30ULL, 
            0x0C36E1CC0807FDF6ULL, 0x92E5EC4C6F5CDFBEULL, 0x57F4119AA5944D7EULL, 0x1F49D6683F8E751BULL, 
            0x892ED0D9FAC1B39BULL, 0xD2EC54D661844F12ULL, 0xC62F71573E12519CULL, 0x8B812FE8C4CECB1DULL, 
            0x8050FA72A96E5BB0ULL, 0xD353C264B5CC2665ULL, 0x6956D12B4D6E9B41ULL, 0x305EA1A21DFA3574ULL, 
            0x75703807486AE42BULL, 0xD2722AB7DD3FF22EULL, 0x7D6231E7ADA151A7ULL, 0xE1A1C1324DC637E8ULL, 
            0x1E01BE507BD7D0EBULL, 0x158CC34EAEB38513ULL, 0x18B5A483807A1B90ULL, 0x388CE9A0C4B221ADULL, 
            0x2E07897F0F3F6B8DULL, 0xFA983A5E43353FF3ULL, 0x0C3C4BACE7652008ULL, 0x6DE1DA8DC25F8D24ULL
        },
        {
            0x6E165CCC7184FD64ULL, 0x9649DC54F612DD71ULL, 0x15A2CBF26C68EEE2ULL, 0x28F93519CCA39E36ULL, 
            0x4BB7B5F9AF7B5ECFULL, 0x7B5E0C80487FFC2FULL, 0x922E2191E5DC0293ULL, 0x4C9BB4570EB46B36ULL, 
            0x95692B768FF513D0ULL, 0xBD3849E6D1003F2AULL, 0x98D484F946C139A5ULL, 0x668DD181A0352931ULL, 
            0xEBD8A3F510025348ULL, 0x4947F9D76D3C01ADULL, 0x5E730509A5EF06E3ULL, 0xBA6695C1556F9855ULL, 
            0x3015016B3B774489ULL, 0x29D31C40BB760EA4ULL, 0x26BD22DFB63D1655ULL, 0x930D18B4FC81771EULL, 
            0xC6E64E5D57067AD2ULL, 0xE18B5C2DA2193869ULL, 0x379EA06B9FE482E5ULL, 0x980E48E2C1D96792ULL, 
            0x997926A35694D629ULL, 0xB4FD3C213BD9447EULL, 0x22C0C865626094B5ULL, 0x3709FD51112EA727ULL, 
            0x4A8A47D0BE91C3D7ULL, 0x759C765CAC24BDA1ULL, 0x1B85802A0F6E1C1BULL, 0x5A8C144892ADEDB6ULL
        },
        {
            0x9FE0131603A66834ULL, 0xE46F838010CA1B6CULL, 0x816536F9BAF2EFD1ULL, 0xE2313730101D5354ULL, 
            0x229DBCC6CC3CB3EEULL, 0x3929248A582453EEULL, 0xD4024F99325CC7FBULL, 0xD155F34FF859F581ULL, 
            0xCDC8B3EE865A9123ULL, 0x2CC6F8EC0B8ECA67ULL, 0x76A69FC80A7CBE50ULL, 0xE323A8F8D9F49707ULL, 
            0x7F3601326416FD4AULL, 0x46E7E7E40CCCC0E0ULL, 0x8C7162AE68C016AFULL, 0xCB43C1476A07CC2EULL, 
            0x13C9E61FEABCB834ULL, 0xAD782FB7BC2F7A20ULL, 0x1333A849354000AEULL, 0xB5DB44D6D0441DA1ULL, 
            0x0A0A5CAB0CE6C6FEULL, 0x432BFD0DB44AFD5BULL, 0x4653D3AC95421870ULL, 0x5A0D7D2180AA6B18ULL, 
            0xBD2E1C3ED70832F1ULL, 0x4DAF873FC00E3EA2ULL, 0xDF6177C1928F26D7ULL, 0x1FF94F75B5F2D992ULL, 
            0x1AE5E40BC7C79CCEULL, 0x6CCBB055A19CC63FULL, 0x8E25F95F1649C339ULL, 0xAC3A95E2610EAF28ULL
        },
        {
            0x6F8CFA4173594AE0ULL, 0x56A135707CDA5D54ULL, 0x5BE2AA7D36583DB7ULL, 0x6C39E1FD1D5C4023ULL, 
            0xAA7AA1FDAEAA3EFEULL, 0xA791741AC4BA7E40ULL, 0x3B45EB9EAED5E5FEULL, 0x54CC1727A5A9C092ULL, 
            0x8F87199B669DD599ULL, 0x59B486F283B0354CULL, 0xDB08491206219277ULL, 0x487E6D98DD86DDB5ULL, 
            0x21CFF19771FD1809ULL, 0xE100116731BC6BBDULL, 0x56370B8E80A69B46ULL, 0xE2C9EDD10A28E0AFULL, 
            0x271E4F050303EE2EULL, 0xE1748AF943882729ULL, 0x0DF936CBB9FF1FF0ULL, 0x6C0CB9D887F2C02DULL, 
            0x6EC3D617BA7967F0ULL, 0xB1B669E97716EAC2ULL, 0x5ACDC3283533A12BULL, 0xD69368B6B26F98E6ULL, 
            0x09A9A32DB0A7BD44ULL, 0x71CA1E1FDB31982FULL, 0x36DCEC146A8E988DULL, 0x8D5E59EF0CB16C63ULL, 
            0x8085EF10D9F295AAULL, 0x82B118595EFA1D8CULL, 0x5DD8C9BAE4A8493FULL, 0x6678FF2F283F2D4CULL
        },
        {
            0x9F757FD6D3559475ULL, 0x0423F76C0B91067BULL, 0xF42391DF3AD0AB19ULL, 0x2A8633349E3BB15EULL, 
            0x691064CBC629D9E5ULL, 0x5745EF0CCF514F12ULL, 0x55AA1B8B9576D0EAULL, 0x76D3445895D9F291ULL, 
            0xEAFD089EEC5A98EDULL, 0xCD0263EAEC9E6D8AULL, 0xD9F82828F50FE9B8ULL, 0x9B565A1FC0BE4541ULL, 
            0x026D82E03A75F7E3ULL, 0x779676FCDD095754ULL, 0x249AA1B00A291DAEULL, 0x3385D461701DA4BCULL, 
            0xAF441D9817A9D144ULL, 0x4B39A3F04C93ABD0ULL, 0x229B80E1BE55AFEBULL, 0x3ACA32537214DC5AULL, 
            0x184DDCE2307BE3A1ULL, 0xB6A9CFB306CFFD58ULL, 0xFCC8B6A456CA0A03ULL, 0x073D07BDBC5DA36DULL, 
            0x851E499D329B5E99ULL, 0x1DBC9B8A8767558DULL, 0xC923654B292077E9ULL, 0x2E082AAA4AC737E7ULL, 
            0x931D02D1AF05830CULL, 0xB18F711C75BAE79DULL, 0x227C8D40F6503325ULL, 0xF23EAFD87AA02583ULL
        },
        {
            0x4DB34E6126438CBEULL, 0x464322DD90160046ULL, 0xB58C4C5827531EAEULL, 0xD991AD35AAE14939ULL, 
            0x88C918286FAF0460ULL, 0x95C4066325EE3F97ULL, 0xCB1AC92349172DB8ULL, 0x8C4CDE7650AED146ULL, 
            0xED4A3A82CEE2347EULL, 0xCD762AA5D0A4474BULL, 0x398DB825C5E74837ULL, 0xC520E8A1AF4E21D1ULL, 
            0xB8E5E638B1C808EDULL, 0x6250C056B5AE3B08ULL, 0x2FE2D56DD6FC900CULL, 0x695F6D71557E822CULL, 
            0xA9CAAF60E2C2D1B7ULL, 0xCB2588EDC5B148D6ULL, 0xB8FFF2AD33D18216ULL, 0xA06B9995C3F5E571ULL, 
            0xF3FEBEF589DDFF40ULL, 0x0A20A2B9DB8CDB1BULL, 0x4EC38ED2015958E6ULL, 0xE274FB20E2DEC0DFULL, 
            0xAD8CCE53A5CC5EFDULL, 0xC4D68C8D1BE42B90ULL, 0x404D69AE83B5EF61ULL, 0x415A1AD805BC145EULL, 
            0xE99F8E673AB25823ULL, 0x729981ACBA242BA3ULL, 0x49DD3EEBFFA2A9BDULL, 0xD8EB2914ED2E0115ULL
        }
    },
    {
        {
            0x611DD298AD80E132ULL, 0x8E5D4A5162C433C0ULL, 0xEF416435E6707C84ULL, 0x81A45D8CAB404056ULL, 
            0x3E634AF6E04B16ADULL, 0xBE4DC8BBE7DAEFD4ULL, 0xE791DACF0515DC12ULL, 0x81FB46E8C8931C20ULL, 
            0xD9FE7DFFBBE52DB8ULL, 0x1A03EFA1D01EEFC4ULL, 0x7C9E7EC54CB831A2ULL, 0xF93ACCF30810AA35ULL, 
            0x10F76FDD0A672BE2ULL, 0x6322F389AD607E45ULL, 0x4DE943F353B0EC62ULL, 0x0D8E8BDC92D1176FULL, 
            0xB3C5B6FAC778772DULL, 0x27B3A38DEA4D6091ULL, 0x60FD2EE5E2D71F55ULL, 0x903C1BFB6944420FULL, 
            0x2E1D2FE22D9161B3ULL, 0xF2AA06B25BDCF0A9ULL, 0x1D0F42259BBC278EULL, 0xA33C59E2ED258B72ULL, 
            0x3B2ACC4DFA72D390ULL, 0x08D8AC13D76B99F6ULL, 0xD9FC7E5C99AE74A2ULL, 0x7E33C9089D1FCFD0ULL, 
            0xA410BFD0788DCD7CULL, 0xB1FFC380753FFD0DULL, 0xF4B085B0B3DEAC35ULL, 0xFFEFCC1E07042F0DULL
        },
        {
            0x960033B5824B8067ULL, 0xE3FF151F1B4D725CULL, 0x30F1407388715A03ULL, 0x60599DD9CC634139ULL, 
            0xA8EB9B9FC725C93CULL, 0x3D0D860EB41ADC91ULL, 0xB5D9C27E4A3AE767ULL, 0xBFE719E2A7A1014FULL, 
            0xE1371CEC013B7DEDULL, 0xB86A859EBACA9E11ULL, 0xBD290013AC9BA8D2ULL, 0x82D1043D64BB6368ULL, 
            0x126A5DF1DB16CAFFULL, 0xFE63AC2AFC04DBFCULL, 0x96289F80D75844B4ULL, 0x662AA15F5DA5438FULL, 
            0xFA980191E52831FCULL, 0x8CAA2CC69F8D313DULL, 0x8A1C353585E6F7CAULL, 0xB7B04512F94D1C46ULL, 
            0xE58F182475F9A8B2ULL, 0xC2B5D7A16C96264DULL, 0x3AC5C8E799AC45C7ULL, 0x627E242F2D72CFC5ULL, 
            0x8179BEAA8A4EDE3EULL, 0xC73C596659157559ULL, 0xF4A5B55C9F71EB21ULL, 0xD35AD975537A5C1FULL, 
            0x7E9A23E4F7C71B5FULL, 0x006ADEC5826218ADULL, 0x4B980E4B2CAFE2BAULL, 0x367EAF1727A48F58ULL
        },
        {
            0x7C66ECB8B3396842ULL, 0xD837FD1FF3CF8A05ULL, 0xC3610879B706921FULL, 0x093EF69C4BD30598ULL, 
            0xAEB682DA66ED475EULL, 0x0F07E5518C65DDB9ULL, 0x8AA331737D5C7246ULL, 0xF82984CD59BD7ED1ULL, 
            0x94DA970912B9CB5BULL, 0x9DC182FCCC8E0F0DULL, 0x151E001CBDA40FFDULL, 0x0627EE05A02E39EEULL, 
            0x7AB67FAFF71BAEE2ULL, 0xE32A5EB4FEF5580EULL, 0x0310C99E95DA0CDDULL, 0xC848D52E071E234CULL, 
            0x868D5C2D9FE861E0ULL, 0x7FFEDFB18E7D5198ULL, 0x1DF9FDBF4CD2B78CULL, 0xF07AE7C09A859021ULL, 
            0xB4177CB4C5544CA3ULL, 0x026F5FC90F9FE20DULL, 0x6F000FC0BA85A6E5ULL, 0xA8CAA6133EB5871FULL, 
            0x5AD336AEDBE0D2BEULL, 0x561CDBAB047E5FD2ULL, 0x943BBAC3877AE347ULL, 0x213BD9845EFCE77EULL, 
            0x35D67B3F34FBE651ULL, 0x96A425FD61EDB7D7ULL, 0xF316BA7C571F8B0CULL, 0x60EE80CBF947048AULL
        },
        {
            0x81C9F15A72740A13ULL, 0x5925755FA06AD123ULL, 0x119753B31851C092ULL, 0x4980F89599B3F924ULL, 
            0xC0A9334AE0DD7277ULL, 0xE20E4661BB09E4AAULL, 0xCEF9F79C24400E3DULL, 0xCADA5123377F9968ULL, 
            0x751847BC7E8C6A84ULL, 0xFA4E1A2542B35766ULL, 0xB538B2C922A7F306ULL, 0xFDDCE3F05A1A9C99ULL, 
            0x1B3997B219FE46C6ULL, 0x233C24AB70DEA3F9ULL, 0x1BAB297F770CE09DULL, 0xA78050DFADD9CDA9ULL, 
            0x4A65A961649BD1B2ULL, 0x91693E020704B832ULL, 0x1C62B0E61086937CULL, 0xBFB4E6AC7534B26BULL, 
            0xC51A907AE288E81FULL, 0xDE47E92D52FD05EAULL, 0xB68412615464EDD3ULL, 0xCFB9D2226A967962ULL, 
            0x7F445235B1C26C57ULL, 0xE34669F5E49522DBULL, 0x21FA4B01D1B78316ULL, 0xE1CC57550DB7E666ULL, 
            0x821A0B6242A8C05AULL, 0x8FDB2780CB8EF65AULL, 0x7BC75E6C213B12D5ULL, 0x4707E06C2938C371ULL
        },
        {
            0xA8237D41C0D9C80BULL, 0x223E5216DB6DD5DDULL, 0xD160665E1F0028B4ULL, 0x809965AC966A2E1EULL, 
            0xDAEBC7FB5DEE2EC0ULL, 0x8D8C97449702E9CEULL, 0x48D9F409CD58C716ULL, 0x5192A36C834782ADULL, 
            0x57D4EC0D893CD82EULL, 0xC5A1DA91221066E3ULL, 0xE2BEF0D8CD0D09B7ULL, 0x8A8DFABCC4660A5DULL, 
            0x1C1701FE3FA57ED8ULL, 0x5F38F69084B00525ULL, 0x887DEBFC61AF2DDCULL, 0x58B2F35DA1197B26ULL, 
            0x4EC4FD718D46C16FULL, 0x541CAE9721434E5EULL, 0xF6D1D0B9941C73BDULL, 0x3F384C1123BF827EULL, 
            0xC19AF539BE4D4F0AULL, 0x4927212968EB2989ULL, 0xF6C0986967FF8BACULL, 0xFE6EC6F5556F1594ULL, 
            0x11EE70A646C3FB25ULL, 0x4DBC6D3035019535ULL, 0x6C430F7C88B04F11ULL, 0xCEF21489A20655E0ULL, 
            0x6E45343486201FE3ULL, 0xC4F6CFCF4229EB8FULL, 0xECE77F3520291523ULL, 0xB47E6C83D89007FAULL
        },
        {
            0xBAC2A2D00DAECA4EULL, 0x56CA604DE4A208EEULL, 0xC4C5B2FBF7FFB59BULL, 0xD21D8CB64FD55E87ULL, 
            0x87FE59750B528FE9ULL, 0xBC6B1F3C54778D0AULL, 0x6DC2482FD39504AEULL, 0x29322C3D936CE7CAULL, 
            0x72E8D7E57AE75992ULL, 0x971985C2014615CDULL, 0xDC7C76ABF3B9B37EULL, 0x9535F6E7435538B6ULL, 
            0xBB122FF64BFD7D40ULL, 0x17D91A7B217EB8FBULL, 0x0470D6A4446C75EAULL, 0xCEBA645B4640EE68ULL, 
            0xBA8DFFA34AD15303ULL, 0x4245895D833CD105ULL, 0xEB1418D622935186ULL, 0xB82E8EEF79F84ADDULL, 
            0x85C443C438E80E08ULL, 0xB60BF369449E87F8ULL, 0x9F6C91CA7D5C4EC2ULL, 0x124D9965ED6D328AULL, 
            0xEDACD8C0F009B0EBULL, 0x7028944F83C1A13EULL, 0x222ED6F0BD0CE155ULL, 0x625E44C8C5C5520EULL, 
            0xF77091F4A1AE9978ULL, 0x417CF95ABA52C95AULL, 0x807168BE3D02033BULL, 0x54D59CDDDAB24BA9ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Arcturus::kPhaseFConstants = {
    0x21AEB9D2F2CA063DULL,
    0x298A92703787B262ULL,
    0x56BDA897FC44DD6EULL,
    0x21AEB9D2F2CA063DULL,
    0x298A92703787B262ULL,
    0x56BDA897FC44DD6EULL,
    0xD2C2D9BEA4C97E8FULL,
    0xABE03105A9091D08ULL,
    0x92,
    0x77,
    0xFA,
    0xD9,
    0x04,
    0x84,
    0x67,
    0x04
};

const TwistDomainSaltSet TwistExpander_Arcturus::kPhaseGSalts = {
    {
        {
            0x976D0BE6654B18C7ULL, 0xA0D6E975A39E46BFULL, 0xB1272C3B47FC476AULL, 0x8CD43FB530E30BD7ULL, 
            0x4288B89622B037BCULL, 0xD824B70A1113F2E9ULL, 0xBFEE8802CDB97224ULL, 0x5CBA8BB22AB9E482ULL, 
            0x4EEA0A6885F3B991ULL, 0x7EE524059B0AE926ULL, 0x1B97617C8A08D0C2ULL, 0x10B0043A7C7DCF25ULL, 
            0x929B03DCD7E0B151ULL, 0xCBB83FDD1C666703ULL, 0x244995DBEF80D864ULL, 0x56AB5ED065112C21ULL, 
            0x31A6FDFFA034DEBDULL, 0x03B94F14D014694AULL, 0xB4407F43108E651DULL, 0x285DAF9A9A06EFFBULL, 
            0x4172BCF0CDBFB7C8ULL, 0x88233B9A676D1190ULL, 0xDD688BB35CAF285CULL, 0xF32A6A9A46201E13ULL, 
            0xFEEA4E052DACFDAFULL, 0x54BAD1E331643874ULL, 0xB41116ACA25ECBCFULL, 0x5943886C83F7C028ULL, 
            0xF0657F3FA07FCB37ULL, 0x3B27A179316E08B8ULL, 0x88297DAF30177778ULL, 0xCA318B3ECF4603FAULL
        },
        {
            0x8A41FD9BAF7CB411ULL, 0x729F7624A4A44FABULL, 0x349874DF4DE7BACEULL, 0x55F62B79053282ABULL, 
            0x4D5E88DCF6C36E67ULL, 0xDFD984AC87AE3429ULL, 0xF587B829389C2676ULL, 0xDF49647633AB0567ULL, 
            0xC513947D8BC358E8ULL, 0x2A65288179432898ULL, 0xE9060476E5B5995AULL, 0xB92AC66DC2967AAFULL, 
            0x4BCFCCF8A8715455ULL, 0xF5B50D981C05E66BULL, 0x42461CBFF9707C08ULL, 0xD3FC9651F1D81E7CULL, 
            0x4072EEDF254EEFB1ULL, 0x0D54BC59D9CEC629ULL, 0xBFCB9488755DCDBAULL, 0xC7BBF5FD45DF6A7FULL, 
            0x066FBF073A02E6BAULL, 0xBF826D2C565CA530ULL, 0x014C51C8790A8858ULL, 0x7FC8AA16A0C3800DULL, 
            0x8B89DC5210F0D42DULL, 0xE608ADF67FAF5182ULL, 0x94A3D6C6A16D69B4ULL, 0x697E55AAB37FC069ULL, 
            0xF807DF0D0484F4DDULL, 0x012FB1FDBB14FF70ULL, 0xE7B629354D9EF2FFULL, 0x3E1E4EC12CD4938EULL
        },
        {
            0x54224EF7A16293BDULL, 0x15B08A59EADE95D5ULL, 0xF6B98E77DFE08E2BULL, 0x5F53EF05BD3722FAULL, 
            0xCD776293B0AF680AULL, 0x9B6167867C71D172ULL, 0xC2BF0A02E5041900ULL, 0x2C748E8D87362A9CULL, 
            0x891751AA9919A7CEULL, 0x028010339623D0FDULL, 0xCA83A907F2F666E5ULL, 0xE48FF79DD46289DCULL, 
            0x288FA9724EEBA323ULL, 0xF6B8649B888F1C08ULL, 0xA609F1961A5CD239ULL, 0x3161CE8FB626F602ULL, 
            0xB1967F50949D4D4FULL, 0x7DDA7CC7BC8405F9ULL, 0x617AA4E311D28909ULL, 0xBE7D9FE92DBDC7C8ULL, 
            0x021543C214C85123ULL, 0xDDB6648C57F83470ULL, 0xED196728D4C2DD9AULL, 0x8FB281F980BAEFF6ULL, 
            0xD6C9FDCDA9551E81ULL, 0x91969558A72E4D44ULL, 0xB4329ABF5B33EC66ULL, 0xACD4EDEEA6D9A620ULL, 
            0x667CEDA580D65B58ULL, 0x440729BFFC59EBA7ULL, 0x7BEA8A84D827C61BULL, 0x6569B61CC383F8B5ULL
        },
        {
            0xA858648863936F07ULL, 0x0DD3CF5288216181ULL, 0xA3B5F1CB0F8141C5ULL, 0x91D51EF3A30C2398ULL, 
            0x512B7618D2FC675BULL, 0x6E311549CB777611ULL, 0xA54FA21435263CECULL, 0xBD9AA569FCB51EC3ULL, 
            0x77309BA7BF921544ULL, 0x3A433712FD958254ULL, 0x6AC6EB31E2760AC4ULL, 0x21DA749EA6EDA67AULL, 
            0xDC08164FF49FE4A3ULL, 0xC47A7A7284943DBBULL, 0xBF4053356A5FA25CULL, 0xCEB8F0CAEF09FE2DULL, 
            0x7D3646DD1F41CF13ULL, 0xAAE5771DA513C45FULL, 0xC0B371AE2D6D5F7CULL, 0x5D28EF1BEEF7811FULL, 
            0xEB320763594B5B28ULL, 0x84B7474053A866A8ULL, 0xECE9DAC0C5F94EEDULL, 0x42C1975E0900D171ULL, 
            0x4C3BC23588AB2D7BULL, 0x291F38D43A4E8D22ULL, 0xF5B83A6291149CDBULL, 0x1DBAC9095CAA7E85ULL, 
            0xC5B597899C268F9AULL, 0x90C0CC5D80FDE754ULL, 0x63C36606F18D92CEULL, 0x1F1F590AAA7359F8ULL
        },
        {
            0x5FB672A3C0FD2DB4ULL, 0xC5629630F9E38480ULL, 0xCE8D827C443E0AD1ULL, 0xFF07032140C8FD21ULL, 
            0x63705448B1595816ULL, 0x4D76C4E358DAE02AULL, 0xFA44189A598861B0ULL, 0x88A835D4C4555793ULL, 
            0x25FB9C6975A69EC1ULL, 0x11E3EBEE67BCA432ULL, 0x3907B4B72DFACAB7ULL, 0x7F3526657771A8F1ULL, 
            0x442E087211EAFD4AULL, 0xD1FBC840974F4940ULL, 0xDBC6EC59781AC9E6ULL, 0x9D9C0600D46F7885ULL, 
            0x33C055C5C9FDF57FULL, 0x12FA90A553DE3540ULL, 0x8C3C90AFAC8B08EEULL, 0xF20AA6E906B34738ULL, 
            0xF472C349651E606FULL, 0xF64F948163A1AACAULL, 0xDBD9F5E87DB1D4D5ULL, 0xBD869D1D390EC9EFULL, 
            0x919E28FC4F354CD3ULL, 0xAD74ED4DEB1D363AULL, 0x321C92A7BD707FE3ULL, 0x5E284509490F0D10ULL, 
            0xAFCA9BFF7081D106ULL, 0xF1523834CF001CE4ULL, 0x328A95781AE26401ULL, 0x6BF950628EC52BCCULL
        },
        {
            0x8E0FFA0733ED5C4FULL, 0x40A719F09618112EULL, 0xB0BF4687B7FFF1CFULL, 0x578C0671E908B0EBULL, 
            0xE6E56B5581D75964ULL, 0x50A56811382BCF38ULL, 0xD3C8D54B8F190B4EULL, 0xBEECF1EAAE7A9578ULL, 
            0x8F1A6ECC22B68ED0ULL, 0xDCC407A5057AB87FULL, 0x52E398355585E71BULL, 0x47BD968104B0B74AULL, 
            0x438E96FB5EB03BA4ULL, 0xBDE9006C2C3AC5DFULL, 0x39F135786927E19FULL, 0xC8E4E8A99D99E648ULL, 
            0xEC5E90879D5F5F07ULL, 0x3746564330938CE4ULL, 0x84BD713C52EF2509ULL, 0xAB215BC735AC654DULL, 
            0x53AEC9227A09D0D6ULL, 0xA1486560660E16DEULL, 0x4CBBF7BC1095566FULL, 0xE54C646AA1B93B04ULL, 
            0x178B445B2B3AD0F9ULL, 0x6FE803E271994021ULL, 0xA7C7E18114D5A9E0ULL, 0x1BB6029200BEB3A5ULL, 
            0xEF95AAEA62559DF9ULL, 0x107FC541B97CF4B8ULL, 0xEAE0C11717DE7E44ULL, 0x04745B0376E9FF9BULL
        }
    },
    {
        {
            0x792F13C6C60D014DULL, 0x12A38A04AE1E0469ULL, 0x9FE1D00E7FA5C98AULL, 0xCBBB5C2F72994093ULL, 
            0x9847FDE9C0DA79CBULL, 0x0E26C8F9C9366F21ULL, 0x21E5BC891657984FULL, 0x983AD0574B63979AULL, 
            0x305A2E2AF156A0BAULL, 0xB5A5E838CDB6D658ULL, 0xCE497E7BAF9EA9B1ULL, 0xB661DE670473A443ULL, 
            0x8D57CF918F0A5B1AULL, 0x9EE55C3CBFA85038ULL, 0xA718C64ABD475C1EULL, 0xEFA6656673C615F7ULL, 
            0xA340DECDE7A92209ULL, 0x2EA159B9879F2DB3ULL, 0xCF70824F0144F73FULL, 0x0730B82F50EA8B2CULL, 
            0x235509024C508290ULL, 0x5BA1323355535C4EULL, 0x62383CDCEE8118EFULL, 0x7A9675070DBAAEF6ULL, 
            0x9FC6239F719232B2ULL, 0x1D31C7884BF210AAULL, 0x4F2EFF3654A66CCDULL, 0x4555117A5FF350EBULL, 
            0x91DA9A46DF838D19ULL, 0xA7D5D906C40B7756ULL, 0x72E9D584878DD227ULL, 0xCCDB392FC91B4594ULL
        },
        {
            0x8B08F5F1AECD84E8ULL, 0x186E9FA6FFD884D7ULL, 0xBEF87901F86F39FFULL, 0x68B557F6985DA10CULL, 
            0x3A923DE3A4D49969ULL, 0x1DC629515FF2F613ULL, 0xCABC71A0A7C211AFULL, 0x04F882D0F9C076E6ULL, 
            0x3F223A932FC79FEAULL, 0xF94B95BB481E740DULL, 0xC4EDC0FD2C99DB2AULL, 0xA92FE6910F8669E0ULL, 
            0x36AF19A8A7709B07ULL, 0x3C90E8E299CEDF86ULL, 0xCDA5F43AFEA89E4AULL, 0x1A827C6F468F68B6ULL, 
            0x5832BD2063BD07D1ULL, 0x3C10A725DEE40468ULL, 0x3E1A6DD685623127ULL, 0x25600A2A69B2E330ULL, 
            0xB9A11DA1051E74BCULL, 0xE6F676F6E20FE138ULL, 0x6BA30F6AB4BDDC5EULL, 0xA5EFA34A9523CC15ULL, 
            0x1D47DB6D8A7AC630ULL, 0xE780F0947805E519ULL, 0x9DB2F227CA1A7006ULL, 0xB482377F567BF31EULL, 
            0xAB00A44CE68951E1ULL, 0x19854F3887CCF609ULL, 0x1E472A5BD033444AULL, 0xC37E0E54E61792ADULL
        },
        {
            0xD62EC3ABED37EBBEULL, 0x3937A2186CDE5963ULL, 0x66130550A4D00DBDULL, 0x518ECC30AE83B367ULL, 
            0xC662652D5F137CB4ULL, 0x30DA579D35051064ULL, 0x011E5895D7B6AD2DULL, 0x5C4E604A52BC5C1FULL, 
            0x027F814296DB288CULL, 0x01E810348154F026ULL, 0x75D555246BE7189BULL, 0xA2167855F89F0514ULL, 
            0x63D2A8AD29806395ULL, 0x5822433685A34B6AULL, 0x458450DF8866C8FCULL, 0xC2D903655649A777ULL, 
            0x057C86254E6F50FDULL, 0x1F5650280C26B0D5ULL, 0xB7444643FC2F2ADEULL, 0x774259FE8EB153FCULL, 
            0xCAD67626ACAA1F71ULL, 0x3AD3027707F4D54EULL, 0xE072D760FFA695D0ULL, 0x5D36891AE091CCC6ULL, 
            0xA4EB83C39041DCD0ULL, 0xC1FCBA03083CD59AULL, 0x7317CAA500696A5EULL, 0x0537B479839B848AULL, 
            0x9F66A62BC5D899CCULL, 0xDEF5849AC89B3446ULL, 0x385E74382B9E8EE6ULL, 0x9EFC9D94AFA78A25ULL
        },
        {
            0x4BD64CDD5DDC10F3ULL, 0x2995E5A8EA83F5A4ULL, 0x3CAD971C44474259ULL, 0x119338792DEB21DBULL, 
            0x73BD1D46ED40621EULL, 0x21FE6999E9666ED6ULL, 0x10373761D13B471EULL, 0x323BBBAC85B2384DULL, 
            0xA4C2222809DE5E97ULL, 0xB8BF6D67E247D1BCULL, 0x885D8C5CA784B15AULL, 0xE2305D55E469D892ULL, 
            0xC07054F129FB9879ULL, 0x92B97AF2A7E5442BULL, 0x6B7C964CCB1CFF95ULL, 0xBD284B4A21B4242DULL, 
            0x3B12743BB434B718ULL, 0x060ABE9CC79222B2ULL, 0xF228D3EDEB840FE6ULL, 0xDECD6FC25FC8CE75ULL, 
            0xCB9F2B80F4719D91ULL, 0xC020D6FDC6066B48ULL, 0xF7DD2C842BE22E7FULL, 0x16673E78EAE73F2FULL, 
            0x7C5324F1A7E5A3D0ULL, 0xC79CA52EB26130C8ULL, 0xF1C75D3A4003A466ULL, 0xE61FBCAFB6D3D7FCULL, 
            0x937E5E95E3B9AACCULL, 0x4DDACF4E2EE05B12ULL, 0xBE87D95BC7C0F108ULL, 0x2FB029D76FDF0BD9ULL
        },
        {
            0x631000ABC4897EE9ULL, 0x783E52E0155140CAULL, 0xF343F646E5AFC48EULL, 0x45E15A0821A65A4AULL, 
            0x26EA38A1FCD7C713ULL, 0xDC2EC2009848F93DULL, 0x9667C2CE9791B9CFULL, 0x8F4AE8BAC3113F37ULL, 
            0xF2F3CA31D95A4A48ULL, 0xCA51F96FCFA76645ULL, 0x636A39C01E6BDC77ULL, 0x48E3FF5D5764CF93ULL, 
            0x298E45A2D55BF644ULL, 0x6FA6216BA782C69FULL, 0x0314B4BC63B07325ULL, 0x42C55D315AE09655ULL, 
            0x4791D5976FFAFCC3ULL, 0x58BBBF16B736A4AEULL, 0x6B3D64987DC2CE22ULL, 0xF54120099BCB842DULL, 
            0x8338A8C656C065E7ULL, 0x54EB7CC6A90E5017ULL, 0xB8AC201BA2668F50ULL, 0xB37D833A561E6948ULL, 
            0x8B437EC4E41360E2ULL, 0xC2B6DE030F72F9DEULL, 0xFCA48B30CB8CDA52ULL, 0x9DA346073371C718ULL, 
            0x3082144B1171342CULL, 0xEA31736BC4FCCA99ULL, 0xCD21A6D945BE09B7ULL, 0x3C1856C4E2612BFCULL
        },
        {
            0x7787D5E7D3C28771ULL, 0x06E1DB370AEA0809ULL, 0xEF008B158E43BCF7ULL, 0xFC2BD439FD6D4E8EULL, 
            0x41C752B06B42D800ULL, 0x83408176CB3FE4E6ULL, 0xB15544CE0FB12F2EULL, 0x0415CBFC897C581BULL, 
            0x563DACC84E674E7CULL, 0x271663EB203E95C4ULL, 0xCE6F7406A9ACE060ULL, 0x663F254CAB2DE255ULL, 
            0xEC4D8F915C194140ULL, 0x1E9CAED2DD1EE14CULL, 0xFCF4346D3C2CA761ULL, 0xA665E95D8C84E2FFULL, 
            0x09EE23740E5535E5ULL, 0x7E7920128C8B7844ULL, 0xE45FB18BB95E7AB0ULL, 0x9A5DDB49509CBDCBULL, 
            0x40B3AE0A2532FADBULL, 0x445CF6C355426AFCULL, 0x355EC1A3F453EB90ULL, 0x16C8B25E16B336E8ULL, 
            0xBF8D28A37ECE5453ULL, 0xA32C5D1D109036E5ULL, 0xC1B4AE2539F4E38CULL, 0xD08C7B21F2D8326AULL, 
            0xEC05057FD6A1E2ACULL, 0xCCD51BD2CB412568ULL, 0xFFCFC04C4996B3ADULL, 0x4131AB3C13ED9745ULL
        }
    },
    {
        {
            0x55A613E295184A0EULL, 0xAF8F1313E7576491ULL, 0xAF23028360CF647EULL, 0x1B8F1547D700D840ULL, 
            0x5F08CDDE885189C7ULL, 0xFBBE7B036400D69CULL, 0xB2415F6ED365AA8AULL, 0xF2361D8DF0CF83ACULL, 
            0x388D64EB0EC198C9ULL, 0x5A7D16BA867EF302ULL, 0x3A9DE982FBB07BB4ULL, 0xD2FD9B9EF36019D1ULL, 
            0xEB98F485FFE29468ULL, 0x03D3D1970547DB6CULL, 0x6065416575A8F07AULL, 0xC3DB32917A39D548ULL, 
            0x071EDDDF1BE4A55DULL, 0x0FFB4C182B22F8FEULL, 0x0D1BA56E1882EBC3ULL, 0x7E21D858662CEF9BULL, 
            0x1328F5C3C20B6FB0ULL, 0x854272DAFC69919DULL, 0x3C4AE188D9D7F1BAULL, 0x64DB7D88478A871BULL, 
            0x08B84BAAC067146DULL, 0x688885610B0E0AE4ULL, 0xED946D6642A134B3ULL, 0x08C35230537E5DFCULL, 
            0x6810EEC76655A897ULL, 0x7AD562795027DF64ULL, 0xCFEFCB2CC94AF181ULL, 0x4CF151CF43EEADE8ULL
        },
        {
            0x7968FE95581B96C7ULL, 0x7EAD299C26D30304ULL, 0xF02EB8107E98FA74ULL, 0xC4FFC90B2C19D9B0ULL, 
            0xB73C8FD85C0A102EULL, 0xCECF369AF5F241D7ULL, 0x5F574AC3719A7D0AULL, 0x923CEA2DDB5BCD41ULL, 
            0x2CF5C56CDFF7FCE2ULL, 0x70AC71A9F4BD568DULL, 0x3AB00B5EBDA8F56DULL, 0x00F72A6396D86C0BULL, 
            0x8E9B23B4B9043848ULL, 0x575C3D58E96EFE2FULL, 0xC212905CAB96B202ULL, 0x156D5DC29E2521FCULL, 
            0xED613FA022E8E026ULL, 0xEAE5ACF21D8D7495ULL, 0xDE520783477EDFA0ULL, 0xD6A6EA51A32E5DC3ULL, 
            0xEE1DF7E4FEB8AB33ULL, 0x0A8E57B25086D9C6ULL, 0x6855C8B060098146ULL, 0x851DE1282FC4AF05ULL, 
            0xCFA4EB5C17B83B09ULL, 0xCFC290C064D0B304ULL, 0x800CD8C6BDFA664FULL, 0x31B5D94F5A080732ULL, 
            0xB6A3299F1ABDD2E0ULL, 0x2B8953B14387CE07ULL, 0x6223D2DB2809902FULL, 0x4B84B51FDFCA0821ULL
        },
        {
            0x3ACF71FC5DA5F861ULL, 0xA5D20BFBFBFC9DD8ULL, 0x3EF9CD9AAF9C0D9FULL, 0x9076DED175C86546ULL, 
            0x81FB0DFE8618B7F2ULL, 0x5B2FB3ED233B9EA4ULL, 0x40764DD5520A84D3ULL, 0xFFE4FEC3F84BE611ULL, 
            0x62BA5A88E47CCECBULL, 0xD0FF39BFBED08E1BULL, 0x6B0ACFBBEB580D1BULL, 0x2E1F5EF7F9D07B11ULL, 
            0x001B9642DA73E0DFULL, 0x129CAD784721A877ULL, 0xE5CF62861A62B8BFULL, 0xF76AB789399DCC23ULL, 
            0xC19A20BBD6BB7D56ULL, 0x139B236508728553ULL, 0x73CBE31EDC42D95BULL, 0xE50098F9B1FDD5E7ULL, 
            0x2C2E20EC6332D364ULL, 0xBFE106974BB4C758ULL, 0x1876EEB53B970C9EULL, 0x7430D3D464090E76ULL, 
            0xDC341B50CE44A30FULL, 0xD0D5F1FDE0A2792FULL, 0x2D07E36F6777F7C6ULL, 0x5CCA945E769E2C63ULL, 
            0x1B312A8A6452E95EULL, 0xF289FE26D691C131ULL, 0x72DD29BB35B8827BULL, 0x40E2AF8DB5FE1675ULL
        },
        {
            0xB56B81C35D5480F2ULL, 0xE06B0F2E21925D71ULL, 0x1329FD770BC9AA43ULL, 0x8CB951C8A72C394BULL, 
            0xFCD708125621B800ULL, 0x208FF6C474420D22ULL, 0x67581E6F69BA3236ULL, 0xBA8F4062A7C13C35ULL, 
            0x9B2CDA80B8D119B9ULL, 0x61BE90CBF2E71E0CULL, 0x163F6DCC25BB1694ULL, 0xDB16644CA35FCB15ULL, 
            0x41ABB119E0D4F5D9ULL, 0xEC716BD222A88959ULL, 0x09E52A71D35A63A1ULL, 0xE0479EBA91451B86ULL, 
            0xF3515AEC95F2953EULL, 0xAD8893441A7268C2ULL, 0x55E0663664668572ULL, 0x7678932CF85A1E3BULL, 
            0x324A66D7697A48C0ULL, 0x65ED12A22EA5EF8DULL, 0xF60AC35AA8D7083CULL, 0xD9E5017F66357729ULL, 
            0xDC57A00A835AABD0ULL, 0x4E214FCE8FEFBC3DULL, 0xC3D7B4EC3EE2F255ULL, 0x3A5784C07226C1FFULL, 
            0x787569C3455D5EA0ULL, 0x664435EFF37A3C6EULL, 0x96832FDAC79D9BF1ULL, 0xF123C57B520F4E77ULL
        },
        {
            0x5A9FD08604DD2E85ULL, 0xDC1A7995CE91CB0BULL, 0x5CFA55602C57E1ADULL, 0x5FF670958AF9A413ULL, 
            0x9905C8F670BCB428ULL, 0xE0DFF6A959FA91A4ULL, 0xC1343D192DD46C39ULL, 0xC7A89DFE82403516ULL, 
            0x6376C7909C8BBB0EULL, 0xC7ED1747A4FB7755ULL, 0xABB172C8927B9118ULL, 0xD89844C0AFCB202CULL, 
            0x40713B5E2430BAA3ULL, 0xFDE43723995558BBULL, 0x9BFB77A8184E1694ULL, 0x44AE92B09F90352CULL, 
            0x4E7568458678DE1AULL, 0xB50A81D4BB490A5DULL, 0xE4B45EF7510426C9ULL, 0xC48CF9B1D6750873ULL, 
            0xAABEFA482D652757ULL, 0x0AAD578CDC139AE8ULL, 0xF6891D157C6A1C55ULL, 0x35E34D9A965F9134ULL, 
            0x2228A21E90E9E009ULL, 0x5CEA557F0F227B7AULL, 0x05276034390B2867ULL, 0xA8E0FF9B7B5CCCC9ULL, 
            0x211E2E622A9E8078ULL, 0xA3F65317A1208BD9ULL, 0x7C36592757F4F64FULL, 0x13FBC9FCA5285831ULL
        },
        {
            0x4CEDDDD47B9B640AULL, 0x00F52387CB06E950ULL, 0x776714FDA28814E0ULL, 0xB14A5E3E1307D7A6ULL, 
            0xCE7FC0991EE96795ULL, 0xF61270DE3FED6666ULL, 0x6E4442E2BB311C61ULL, 0xB69D426134D63562ULL, 
            0x0073AD13EE61D78BULL, 0x3AB797020E200159ULL, 0x6DAB9CE6216B8617ULL, 0x803931E2A02E78C0ULL, 
            0x82EE1D244B35B38CULL, 0xA48E6A4FF8B5571FULL, 0x9BB76F3B1E3E2216ULL, 0x7321CF8732F4CA3BULL, 
            0x40E7C4A8E6D6A30CULL, 0x6CE569812AC5F0E9ULL, 0xADA664BB34FF4796ULL, 0x38DDDF33AD52B804ULL, 
            0x5D0558E1E69C72BCULL, 0x933BC994F98E97B3ULL, 0x89112992266D09F8ULL, 0xE1432708181D5739ULL, 
            0x6B7A5620F2D54731ULL, 0x32E388F7EC42058CULL, 0xE33D49DF34FF9103ULL, 0x295A8D1436DD9FEBULL, 
            0xB6A43754FA11794DULL, 0xDE74E0471AF5B02FULL, 0xB31783F80272E5FDULL, 0x29A323342B3C5B44ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Arcturus::kPhaseGConstants = {
    0x753305205BB48C1AULL,
    0x09681CC55F678323ULL,
    0x0CCBB72EB4E3C191ULL,
    0x753305205BB48C1AULL,
    0x09681CC55F678323ULL,
    0x0CCBB72EB4E3C191ULL,
    0xA2137BA38856EB12ULL,
    0xF030A10259914FA0ULL,
    0xAD,
    0xF5,
    0xF7,
    0xDB,
    0x38,
    0x8D,
    0x77,
    0x4C
};

const TwistDomainSaltSet TwistExpander_Arcturus::kPhaseHSalts = {
    {
        {
            0x9189CAF5E310367CULL, 0x3748DB99A3A30310ULL, 0x1F5C27CDED4CBFD2ULL, 0x322FD53863285AFBULL, 
            0x6ACB6CB8CF6EACE6ULL, 0x1476AD74309DD75FULL, 0xC65476D721CC39F4ULL, 0x2B8477CCF68A187BULL, 
            0xDCF191AE173F9179ULL, 0x06635D41435B3B73ULL, 0x7537DBFE9E6709ECULL, 0x6034097B0FF9D9ECULL, 
            0x38B0609EFED22994ULL, 0x08487180EC3DAFE1ULL, 0xE1403DE8EDEE1791ULL, 0x3AABD85DEBE487A9ULL, 
            0x21030D1467B2C763ULL, 0xCE41AD6B660A8CB8ULL, 0xDCB43A740C4FF6B3ULL, 0x06C5F7D684A6A716ULL, 
            0x9AFB32A3502DE10FULL, 0xF80F7C32A4F4F776ULL, 0xD90B6DEC1C75DB13ULL, 0xAFB1E1905B78D10BULL, 
            0x32004F3C03BDCC7AULL, 0x3B8511888D7EA535ULL, 0xA8E27631BB5A75BAULL, 0xE0FBD9263DF2F776ULL, 
            0xA739726E1F827672ULL, 0xF9236C11727B2441ULL, 0x5BD1930974115E2CULL, 0x3AD6A3B5C624B4D2ULL
        },
        {
            0xE4DC3C1037331CE1ULL, 0xFFB0D5532691F65EULL, 0xCF0F009A70DA5C5EULL, 0x6D21C8312A0F9581ULL, 
            0x07EF5C1E44B1DC4DULL, 0x5F50079902E0DA13ULL, 0xCA2D0A11799C49C8ULL, 0x6889E5C656587225ULL, 
            0x83E05692F2DA1E94ULL, 0xE28261CE0DF84694ULL, 0xC5737A49D026F36EULL, 0xABDB574BF16B2A2EULL, 
            0xB3A65DA205D82F09ULL, 0x26F8E0526973DF7BULL, 0xE2C636AB352CC20BULL, 0x4666F939A892D760ULL, 
            0xA495C28D9D29183FULL, 0x9A2257CA0075D04AULL, 0xA5922647AE01AA4FULL, 0xCBDD0E5D63FE6D95ULL, 
            0x3F51A327492634DBULL, 0xBD7D2D471E0D6355ULL, 0x385CC60859238DB7ULL, 0x91C192752766652AULL, 
            0xB7E1AA19D6B9D85EULL, 0x0726B678AB88CF4CULL, 0x6F8B8DCE7B535CC7ULL, 0xA7BD65EF02C6C89EULL, 
            0xCE245C57343C7D95ULL, 0xABBBC451C4B362B7ULL, 0xADBC0253AF6A504EULL, 0xA2F74FB41F92F3EDULL
        },
        {
            0x2230D81DC8C06589ULL, 0x8A207CB111E9D87BULL, 0x22B7936DCC3A4DD2ULL, 0xD7F0D548659C4D9FULL, 
            0x4E013CA6BB7FBC06ULL, 0xF71980C112E97C69ULL, 0xE4001ECBB7878FC0ULL, 0x40DCF5001D08D789ULL, 
            0xA7E24D59FD5D2878ULL, 0xC240DDC80530F27EULL, 0x53C29A0F41D6DC55ULL, 0x637B184E770E7C1FULL, 
            0x4DBF67C4759249E1ULL, 0x23E27123FC9AEE08ULL, 0x027E0E66D8E89F60ULL, 0x6C0383C88A0E1C7AULL, 
            0x7E5569222DD007A0ULL, 0xA6F993DB5F3EE643ULL, 0xCEBF35CEF0FF4820ULL, 0x6521454F7518D317ULL, 
            0x7822A194E7A836ECULL, 0x7475717AA1AC3D0EULL, 0x713FBF60390025CDULL, 0x476BD69D1A89C413ULL, 
            0x0656E8B841D39079ULL, 0x8031B5126752C100ULL, 0xCEB30A544CC78F45ULL, 0x121FFB33224043BEULL, 
            0x19B54A596F58389CULL, 0x658B45593609A999ULL, 0x712A2DA17063760DULL, 0xB98D2DB3ABC698ADULL
        },
        {
            0x15934E929AA91E17ULL, 0x2586226370EE976CULL, 0xD391629E1B74E3D4ULL, 0x10DBBFC5C5E5D273ULL, 
            0xFA6988CB526D3585ULL, 0x5EDE78C42A0569A0ULL, 0xA5321E201C6893FAULL, 0x2C61128993476554ULL, 
            0x374BA3FCC95EE773ULL, 0x7D3D981DF35685F9ULL, 0x7841D807C9EAAEEAULL, 0x362B5F3F078CEFF2ULL, 
            0xEF8B395B7081E779ULL, 0x72EB5ED889B52965ULL, 0x2F7CB7CB6261884AULL, 0x7F370A0ADF9F65FCULL, 
            0xE8BCBBB3B04AFB90ULL, 0xE188BE222BADB0DFULL, 0x8D9D42936E0DF117ULL, 0x763F4A58D4A7CFB0ULL, 
            0xC45E1E1F5AB0F92EULL, 0x66DDA870BEAFAAEFULL, 0x5B0D83BBEDC136BCULL, 0xD934A5DAA9FC37B7ULL, 
            0xFED8904DDF6A30E1ULL, 0x82716299099B3912ULL, 0xED2658AFE0A812E8ULL, 0x069ACC0CEF451069ULL, 
            0x64668823E0A74CD4ULL, 0x9815BCDFA94047E6ULL, 0xDF59F52E07821AA6ULL, 0x9F9F2EFFD9D5E065ULL
        },
        {
            0x4257D4E6E5E23244ULL, 0x5BB95C1B63347C27ULL, 0x5E68E571E3B6EE03ULL, 0x77DF1BCAA1287EC0ULL, 
            0x21A8C9454D55B9F1ULL, 0xB9534A30A08FB7D5ULL, 0x237DE2505B5A575BULL, 0x9DF8918576321984ULL, 
            0xC51DA04526B134E5ULL, 0x186DDCBDFC7B0883ULL, 0xE3FAAC6A6BD703CDULL, 0x2E3B104F6EC8EB9DULL, 
            0xCF032A77F165DA32ULL, 0x79C612287BD9936FULL, 0xC10D73C73073A326ULL, 0x26CFAF26CA4287A7ULL, 
            0x6FC62FCA1730DC9AULL, 0x9A19700F8F2D0CECULL, 0xC0F6412795C1545EULL, 0x409A950598D11E9AULL, 
            0x958B74AF3F75F934ULL, 0x303239AE37944A9FULL, 0x2F3CBE589D9D2EE8ULL, 0xB61FE3C95354D321ULL, 
            0x49B25139E699AC4FULL, 0xCC30F069A70C149FULL, 0xF87A1192502B092BULL, 0x6DE530710E7B42B4ULL, 
            0x067876CC9B8DFE92ULL, 0x65DD409B2851FB1FULL, 0x4AA9FDC8D1A1C12DULL, 0x7BA2852FE25DF3A2ULL
        },
        {
            0x99BAF57564380FCAULL, 0x31A554E606A58E76ULL, 0x08D604FFD1EFC9FDULL, 0xA35EBA4F40AED5DFULL, 
            0xF0F69F7DAE9E349DULL, 0x7BEC3DE7C270CBF3ULL, 0x55EAA44ADE6C31FCULL, 0xFEE590863209F0CEULL, 
            0x0C2B477E0E942B94ULL, 0xF8FB95D5A20DFA48ULL, 0x46DFF8E5115D0267ULL, 0xAD02C00A0FA3A455ULL, 
            0x29CA50170A0909EAULL, 0x0ED551D6CD345A8BULL, 0x9ED209B9B2782925ULL, 0x90F1D567DD68498AULL, 
            0xCF3E2A8BDF589CCBULL, 0x722B9045FF0D35CDULL, 0x13C0B3E5EE3A3A82ULL, 0xCA14B12E36A7E283ULL, 
            0x0A3D4796711460DFULL, 0xA1BEB34ECCB920E5ULL, 0xC232F1627861D67FULL, 0x28FEA3685D3F8379ULL, 
            0x7DD09D1AAD1C2AFAULL, 0x388002BBBA904E5DULL, 0xB677A942DFE0ABC1ULL, 0x972FC2844CDF65B1ULL, 
            0x9332A278D0E3C9A3ULL, 0x21EAB54B0F7D67B0ULL, 0xEAFF30C00E159569ULL, 0xD16EBB25CEF32F6BULL
        }
    },
    {
        {
            0xA144543B0CBD5F19ULL, 0x34ABF337B0EE1D3FULL, 0x30453E200FAC5D59ULL, 0x18FE294D4A20FF6BULL, 
            0x424138FD1564FF2CULL, 0x8495CD5303CE82B0ULL, 0x747EA53A7949AD19ULL, 0xF9A8798EBD4BD365ULL, 
            0x4817C32BD2E102BCULL, 0x43A845C6C0B4F091ULL, 0x2C6F92AF56BF3132ULL, 0x6053D87ECBCA33B0ULL, 
            0xBD66EBA7661239C9ULL, 0x0964C24889DF1A76ULL, 0xDE51B806C31FB7EBULL, 0x71868B631B11ED74ULL, 
            0xDE3C9D085384BC0AULL, 0x041A1E8356723B7DULL, 0x9ABC781EBEBE7C9FULL, 0x58B29C1078694C6CULL, 
            0x0B0DDF031BA9EB1DULL, 0x1087826DD1948796ULL, 0x933A8B21AFE75436ULL, 0x737569A9EE7327DDULL, 
            0x0B22A994EFBF0106ULL, 0x813B56C9761F9185ULL, 0xDDE390476FA59997ULL, 0xB1B848C09BBFBCFEULL, 
            0xA9FC9EF03A7CEF55ULL, 0x993A6E6DAE530F49ULL, 0xB942826D431C3CBCULL, 0xFDE842079134BF53ULL
        },
        {
            0xC10BBB07EA919523ULL, 0x9B0E12553FEB4BEFULL, 0x8E55B2F7B94C0946ULL, 0x910B70AC2379403DULL, 
            0xFCBA915CA3FAEA48ULL, 0x7FFC30F7B646BDDFULL, 0xF94524B312BA6E76ULL, 0xBAB73F42649FC999ULL, 
            0xA5CF609EFA03C977ULL, 0x7E95787F83D73DF1ULL, 0x08D0CB865D3C7CFAULL, 0x2A52FE6A92DC5159ULL, 
            0x9F96F13B3C1AA63CULL, 0x023C3179DE47C466ULL, 0x295575C6043AC1B3ULL, 0xE0DD292967ED4D9AULL, 
            0xC09FE813861B5DD7ULL, 0xE7329A7220D81DD6ULL, 0x65F66E850AA0302AULL, 0x33FD3781DB6E643FULL, 
            0x2012FFC8F01B905DULL, 0x31629480909C3B1BULL, 0x54C0B7FBBD7A0380ULL, 0x3D456DD67718E93CULL, 
            0x233F02A30EA6F210ULL, 0xFB9EE66AFD3B2E0FULL, 0x01540698C543E2D1ULL, 0x9E8A47B0E4D41AFBULL, 
            0x7EE5324A36CB4988ULL, 0xD24FFD3AF3D00839ULL, 0x567479F2A8C2D194ULL, 0xC19C167045D56186ULL
        },
        {
            0x6E050284EDB83A4FULL, 0x329AD3F3C262EE80ULL, 0xE180BC33A2D9EBD7ULL, 0x72FB65D25DA5ABDDULL, 
            0x46E986EC67C7F546ULL, 0xCD25649D09528F2BULL, 0xB1F4709AC883641DULL, 0x9B3202E38A1EBF98ULL, 
            0xC23F902AC29C5A8DULL, 0x81DCFC714C02B874ULL, 0xAAD25B816D0271ACULL, 0x6A7A5DC1307919E5ULL, 
            0x4EE05B1E610CE4F8ULL, 0x437730B32B148052ULL, 0x7C08331661BBF379ULL, 0x111BBE5C6B25FE61ULL, 
            0x1F36AECA0B901C5FULL, 0x8E5712A58FFE5072ULL, 0xC5F18DCA9366303DULL, 0xF4721AF79CC2AE0FULL, 
            0x33CF27795110B6A5ULL, 0x96DC95217B20C2B6ULL, 0x0CD66EE77CCF2116ULL, 0x8538473F3D06C3DEULL, 
            0x9298F11ED4E7A004ULL, 0xC07328B84333F7B9ULL, 0x3BF4FBAC1566506BULL, 0xE05E5BD601CA14EBULL, 
            0x8347543E78297420ULL, 0x7D7F9189374149E5ULL, 0x3C94F0F533143633ULL, 0xF7B663DF299CE16AULL
        },
        {
            0xE65AA1FA86F33ECBULL, 0x5F53F749356E9DB8ULL, 0xBC602DDDCAC61A8FULL, 0x174F1F9A93C47DFBULL, 
            0x325E26CB3BB4A6FBULL, 0x3EF141DB37142A27ULL, 0x2E0A5D76B85971EFULL, 0x801481572EB33263ULL, 
            0xB08E805A2C0BD7B6ULL, 0x7294724D4F67810DULL, 0x72EF9DAF5C452040ULL, 0x6D2F40B93EEA42E9ULL, 
            0x0056EBE911AC7476ULL, 0xFED126AE3293D3CAULL, 0x44CFE3C8EAB1B762ULL, 0xF4BC090196407CACULL, 
            0xB96049953CFB060DULL, 0x36293EACD7D29FB4ULL, 0x8F1E2329A667132FULL, 0x67F9179CD43ED332ULL, 
            0x05A2008AA3485419ULL, 0xD7F2B75BF0B3D95FULL, 0x18E8FAE349FAA083ULL, 0x7314A7BE0CA0F3F1ULL, 
            0x7FFEDBA28948F49AULL, 0x26C817376E40C47BULL, 0x7FDB7FDAE14798DBULL, 0xC3A667F4105811B4ULL, 
            0xCDDEF3BAACA98F54ULL, 0x781C978E72DF17EDULL, 0x433C087209D3CC05ULL, 0x532997D806D4BE59ULL
        },
        {
            0x1F9B1F01F7B3CB2FULL, 0x3F865A1780D89C6DULL, 0x682893DA245D6A32ULL, 0xB92F3ECA2C8A3134ULL, 
            0x7690B82B9A1E82ACULL, 0x6126062625641284ULL, 0x35B5115CFE8F2156ULL, 0x9214F8B3A0157F42ULL, 
            0x97319D42CD7A500AULL, 0xBAAF04CC43DDBDF7ULL, 0xC19D2E8E18DE8895ULL, 0x187B529B0C9C23B8ULL, 
            0x54A053DDE032A003ULL, 0x89740DF8B6C9B5E2ULL, 0x54E2611E87785C28ULL, 0xAB6D9A928A41D5ECULL, 
            0x1D8FF9BC1093DCCBULL, 0x801A5DCB476B12A6ULL, 0x23985B8D29B2B974ULL, 0x3F54CEB6DC223C1DULL, 
            0x1EBCCFB1F689F7D7ULL, 0x58D214B8B4D5C9F7ULL, 0x096D35123D373EA9ULL, 0xB2A31A1710FDBB07ULL, 
            0x2AA185F33027B918ULL, 0x2F98FE52F76DB671ULL, 0x7B17754747D9C550ULL, 0x5D64A3F64C797485ULL, 
            0x32FD5913C49A95E2ULL, 0x2F0C77948DE3474EULL, 0x83E358673837BFD4ULL, 0xCA2C414DBF84ED44ULL
        },
        {
            0x5D16E846BDBACCAAULL, 0x5D53D00B15E47DCFULL, 0x04E008E23D0342F4ULL, 0x4D96C33366C43E69ULL, 
            0x1FA92398C4546165ULL, 0xB0B49EE9FF668EB6ULL, 0x4A66BAC10AA6DA04ULL, 0xF6BD788D11F9DE8AULL, 
            0x0322F6FCE35ADF5EULL, 0xC14730A0872A2D85ULL, 0xD7E24C24EC1CCA85ULL, 0x916A241B393F745AULL, 
            0xBA8E2050A341AA18ULL, 0x515C0E772FC2A083ULL, 0xD2739BABF75AE16CULL, 0xA03DE09D8528A417ULL, 
            0x4A7B0DDF92A93FCCULL, 0xFDF4D749E4610960ULL, 0xD3D84983D3DE9351ULL, 0x779FF645C5DDE995ULL, 
            0x3984F41BC1ED98C7ULL, 0x708CB21DB72E89E2ULL, 0x62E4580EA890812DULL, 0xD8A4EEED993A1FB5ULL, 
            0x4D2CB9209BC9FD7FULL, 0xD0F51B22C4F92952ULL, 0x12454E5BF967AD77ULL, 0xCF478A49F4F60D95ULL, 
            0xCA1F2222B59FED09ULL, 0x7B53D1C0D26BDCE8ULL, 0xC955539EB6052916ULL, 0x29F5BBA71FC5A7BBULL
        }
    },
    {
        {
            0xF98899BF442A6A43ULL, 0xD5D069C96A300973ULL, 0x9321B84F09ECD149ULL, 0x0ABDCF3B8F42858DULL, 
            0x64279BAF5B4BE0DAULL, 0xFDB726F3D2BD886AULL, 0xC2F9FCE9E9434F5AULL, 0x2F1E645B6FB6928CULL, 
            0x2331735F06700C5BULL, 0xA6420031B675CD97ULL, 0x619340ABEA612FFBULL, 0xF0E765E266681040ULL, 
            0x4CBB5FEA34AF7A33ULL, 0x07684EB9D03897F7ULL, 0xE8C60F432ABE2C0BULL, 0x43794DBD99F784B4ULL, 
            0x637191B4B2950974ULL, 0xAC85995165B0FBC6ULL, 0xF5841ACFC46A5E34ULL, 0x93733470CE897CEAULL, 
            0xF09A130D49CF40B2ULL, 0x8F117C1453149368ULL, 0xA380B2CC816763BEULL, 0x5DBBBC1B982ABEEAULL, 
            0x79616ECEFA56D0E3ULL, 0x543CFAB0B9B93632ULL, 0x11B00A125CEB97D5ULL, 0xB5D81093D01CD391ULL, 
            0x31412E580F38F9B6ULL, 0x3D2349F92A8CF7A0ULL, 0x81E1169B670BE338ULL, 0xA1A6AC0A7B26B521ULL
        },
        {
            0xF6B8BA68485A17CBULL, 0x848D25193EB1E974ULL, 0xA2F89B3E5503A3C7ULL, 0x1B2248587616A9C6ULL, 
            0x90B2927937D310FEULL, 0x6CB9D36429E7D868ULL, 0xB492D31F11C3BFEFULL, 0x812F0283579A22E2ULL, 
            0x20F8383A62596F56ULL, 0x26AEB1DC1CA92F43ULL, 0x2779D9F7B272851CULL, 0xB948B2DABBEC8238ULL, 
            0x26552F58FE0F54CDULL, 0x5262249BD35EF264ULL, 0x6BC763EC32F3D556ULL, 0x01D1E9743D9EACB3ULL, 
            0x653E2F0C217DE790ULL, 0x1E40F43EA78B5A92ULL, 0x52376B8BA3A22BDDULL, 0x77C2385319AF708BULL, 
            0x3D0C3F7AA0481BC0ULL, 0x5235987DAAC05CAAULL, 0x6FCED3E26CC53791ULL, 0x43A86998F6C2BEEEULL, 
            0x2F60FE9AA5DC1E22ULL, 0x30384D47E6A842FCULL, 0x2A179FB4E3638262ULL, 0x618B085E06906894ULL, 
            0xDEC65D788B3BBF7BULL, 0xEA548D98FBECF262ULL, 0xEF4BCBF284F93F22ULL, 0x539CA198DF854FC2ULL
        },
        {
            0x6370B836860F3095ULL, 0x5DF8DF2A87EFA826ULL, 0x43BF755272BDEFD5ULL, 0xF9733B1F7CF39095ULL, 
            0xB317F071076D53C3ULL, 0x5666C68011BDFDA5ULL, 0x83BAB58CD254D0B7ULL, 0x6657FDC9FC0578CDULL, 
            0xD828C19C4E3A4854ULL, 0x40EFEB77B9C4D876ULL, 0x928AA6EA91AEFECFULL, 0x97AE188525D64222ULL, 
            0x28F531F2F4EC2ED8ULL, 0x5746E14867F50800ULL, 0xAA6FC80548CC3FC0ULL, 0xECF26839ADD75B1CULL, 
            0x10D49D85CD510578ULL, 0x9EF9DC6DFCB61ED1ULL, 0xD7E27A1D5A24712CULL, 0x3B9935AB20FBB15BULL, 
            0x6C89500A4BB44851ULL, 0x3F6177FC0D60B025ULL, 0x0B5A5D3595F811E2ULL, 0x5FE9D63CE994EE23ULL, 
            0x7C6ECDBACD37F271ULL, 0x28663B4F9574A5E2ULL, 0x902559BBC02A647BULL, 0xB97851338AC9511DULL, 
            0xD5F62E5A0E329009ULL, 0x85046870A934D221ULL, 0x11D6360FFEBD001BULL, 0x545B39E029950DF1ULL
        },
        {
            0xB968A6A6D693D188ULL, 0xEBCA8623F11F46B9ULL, 0x032C379B26C9973BULL, 0xF3F7389295063296ULL, 
            0x872376FF78E5D847ULL, 0x119A2C9894202477ULL, 0x56995FE9070560D1ULL, 0xC570C1BD87A436F9ULL, 
            0x7CF598B4417B63ADULL, 0x664C6F5631B23ADBULL, 0xB63C43F138BC0DABULL, 0x810A561C679A7393ULL, 
            0x2318A63527ACE3EBULL, 0x902381A8581D2A7FULL, 0x4C984F0A5014F273ULL, 0x543FB65A49B2A3F1ULL, 
            0x82616562DACEC1C8ULL, 0x9D9258712838C877ULL, 0x6BA358BDD04292C0ULL, 0x06B9A152E3AFC88CULL, 
            0x64AD3B96C97006DBULL, 0xCBB21577B998F611ULL, 0xF4A9C037A7B380CDULL, 0x00520DD3F0FB6DADULL, 
            0xEC770C7A96FB1CF4ULL, 0xCE46D929F6F334E7ULL, 0xE57001054C6C34D0ULL, 0xB1DF6208BBDC1242ULL, 
            0x4760697893C2006FULL, 0x43CA4F42226E7E7EULL, 0x9F8381D7EB97411BULL, 0xE4907AF96BAF9310ULL
        },
        {
            0x11ED8F43720ABEF6ULL, 0xBE0682293981E2A8ULL, 0x3370E41410FAB98DULL, 0x15251665075152BCULL, 
            0x99710942A110EE99ULL, 0x7415BB555729A468ULL, 0x162DDBB54E909AABULL, 0xBF9AD8613B1A2416ULL, 
            0xB3AD8C858C14587EULL, 0xAB9EC472463E608BULL, 0xC11835939DFDC06FULL, 0xCAF1532FB3FC0938ULL, 
            0x4E5C08794ADA0E1BULL, 0x8F713F9D91D5E5B8ULL, 0xF2DC412DAA8B55A5ULL, 0x13D15BFED5DD161CULL, 
            0x25EED14E2AA508C6ULL, 0xE807C79E9A2AC7CFULL, 0x75B1F80CE719ECB1ULL, 0x9463EFF4A5748979ULL, 
            0x31C904DBA3DB5948ULL, 0x402FB1B2AA2071A9ULL, 0xD6A856860C545A3EULL, 0x66353305CD7D4F6AULL, 
            0x857FD402415B7169ULL, 0xC80866CE4B86B81FULL, 0xA4D0CCE84BF2567FULL, 0xEB5EC9871E9BDF9EULL, 
            0xB5F23B6E50265605ULL, 0x3AA9B4F0BEC2DF67ULL, 0x23A7FC2F54273CF5ULL, 0xB28459B309946B71ULL
        },
        {
            0xCDA52F37B26E41BEULL, 0x53B8180C10DBECE0ULL, 0x5EFFEACDC3159753ULL, 0x4EB5A8C0F0A787DDULL, 
            0xE9100066461B2538ULL, 0xF4697FBB90747D35ULL, 0xA36BF8C2DB9B0982ULL, 0x64527B373A743E5BULL, 
            0xAFBDC42CB4D617BEULL, 0x681A1688FEAC3C68ULL, 0x606F4E95DFA70953ULL, 0xF190E3885BDD2491ULL, 
            0x682B99A50BB17DF4ULL, 0xE1D5247F9CBF04CBULL, 0x6A835093785972F2ULL, 0x9FDC4FC56D00000FULL, 
            0xFFCB425E813076F5ULL, 0xDF25271B3B857360ULL, 0xC206F1C8F632B11CULL, 0x13F592C4F28CE65BULL, 
            0x178E2AA1C66B932AULL, 0x219BD523D051E826ULL, 0xF72BB940DF7560A1ULL, 0xC816E244974234A4ULL, 
            0xED706F90BB3EDD85ULL, 0xBA957B932EA13D9FULL, 0xA545424ED8F1656EULL, 0x5852B9D660D5D23BULL, 
            0x126426B2FC9172D9ULL, 0xE0A4F46054046127ULL, 0x27CB657DBA8CA318ULL, 0x2CB0DC5454638735ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Arcturus::kPhaseHConstants = {
    0x31CE5A1A4D224053ULL,
    0x5D9E9252E361B9F0ULL,
    0xCA2A633D9E9857B9ULL,
    0x31CE5A1A4D224053ULL,
    0x5D9E9252E361B9F0ULL,
    0xCA2A633D9E9857B9ULL,
    0x2BE287C4D15E90B0ULL,
    0xEDB86E336CEB4B8EULL,
    0x61,
    0xD8,
    0x91,
    0x5A,
    0x39,
    0xD0,
    0x8A,
    0x5E
};

